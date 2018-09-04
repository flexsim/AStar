#include "AStarNavigator.h"
#include "Divider.h"
#include "OneWayDivider.h"
#include "PreferredPath.h"
#include "macros.h"
#include "Bridge.h"
#include "Traveler.h"
#include "TemporaryBarrier.h"

#include <sstream>

namespace AStar {

int AStarNode::rowInc[] = 
{
	0, // right
	0, // left
	1, // up
	-1 // down
};
int AStarNode::colInc[]
{
	1, // right
	-1, // left
	0, // up
	0 // down
};

EditMode AStarNavigator::editMode = EditMode::NONE;
std::vector<Vec4f> AStarNavigator::heatMapColorProgression =
{
	Vec4f(0.110f, 0.280f, 0.467f, 1.0f),
	Vec4f(0.106f, 0.541f, 0.353f, 1.0f),
	Vec4f(0.984f, 0.690f, 0.129f, 1.0f),
	Vec4f(0.964f, 0.533f, 0.220f, 1.0f),
	Vec4f(0.933f, 0.243f, 0.196f, 1.0f)
};


AStarNavigator::AStarNavigator()
{
}

AStarNavigator::~AStarNavigator()
{
}

void AStarNavigator::bindVariables(void)
{
	Navigator::bindVariables();
	bindVariable(defaultPathWeight);
	bindVariable(drawMode);
	bindVariable(showAllocations);
	bindVariable(surroundDepth);
	bindVariable(deepSearch);

	bindVariable(routeByTravelTime);
	bindVariable(stopForTurns);
	bindVariable(turnSpeed);
	bindVariable(turnDelay);
	//bindVariable(indefiniteAllocTimePenalty);
	//bindVariable(deadlockPenalty);
	bindVariable(deallocTimeOffset);

	bindVariable(ignoreDestBarrier);
	bindVariable(showTravelThreshold);
	bindVariable(smoothRotations);

	bindVariable(barriers);
	barrierList.init(barriers);
	bindVariable(activeBarrier);

	bindVariable(fixedResourceBarriers);
	objectBarrierList.init(fixedResourceBarriers);

	bindVariable(cachePaths);
	bindVariable(pathCount);
	bindVariable(requestCount);
	bindVariable(cacheUseCount);

	bindVariable(enableCollisionAvoidance);
	bindVariable(ignoreInactiveMemberCollisions);

	bindVariable(snapBetweenGrid);

	bindVariable(showHeatMap);
	bindVariable(heatMapMode);
	bindVariable(transparentBaseColor);

	bindVariable(collisionUpdateIntervalFactor);

	bindStateVariable(collisionUpdateInterval);
	bindStateVariable(nextCollisionUpdateTime);
	bindStateVariable(heatMapTotalTraversals);


	bindVariable(debugRoutingAlgorithm);
	bindVariable(routingAlgorithmCompletionRatio);

	bindVariable(grids);
	if (grids.size() == 0)
		grids.add(new Grid(this, getvarnum(holder, "nodeWidth")));

	bindStateVariable(minNodeWidth);
	bindVariable(hasCustomUserGrids);
	bindStateVariable(hasConditionalBarriers);

	bindVariableByName("extraData", extraDataNode, ODT_BIND_STATE_VARIABLE);

	travelers.init(node_v_travelmembers);
	if (travelers.size() > 0 && !isclasstype(first(travelers), "AStar::Traveler")) {
		for (int i = 1; i <= travelers.size(); i++) {
			treenode coupling = rank(travelers, i);
			treenode partner = tonode(get(coupling));
			Traveler* traveler = travelers.add(new Traveler(this, partner->ownerObject->objectAs(TaskExecuter)));
			nodejoin(traveler->holder, nodeadddata(nodeinsertinto(up(partner)), DATATYPE_COUPLING));
			setrank(traveler->holder, coupling->rank);
			destroyobject(coupling);
		}
	}

	if (time() > 0)
		buildActiveTravelerList();
}

void AStarNavigator::bindEvents()
{
	bindGeneralEvents();
}

void AStarNavigator::bindTEEvents(TaskExecuter* te)
{
	te->bindRelayedClassEvents<Traveler>("AStar", 0, &AStarNavigator::resolveTraveler, getTraveler(te));
}

void AStarNavigator::bindTEStatistics(TaskExecuter* te)
{

}

TreeNode* AStarNavigator::resolveTraveler()
{
	// this method is going to be called as a method on the TE
	// so this is actually a pointer to a TaskExecuter
	TaskExecuter* te = (TaskExecuter*)(void*)this;
	return AStarNavigator::getTraveler(te)->holder;
}

double AStarNavigator::onCreate(double dropx, double dropy, double dropz, int iscopy)
{
	if (objectexists(node("AStarNavigator", model())))
		destroyobject(holder);
	else
		setname(holder, "AStarNavigator");

	return 0;
}

void AStarNavigator::resolveGridBounds()
{
	if (grids.size() == 0)
		grids.add(new Grid(this, getvarnum(holder, "nodeWidth")));

	std::vector<Grid*> tempGrids;
	for (Grid* grid : grids) {
		grid->isLowestGrid = false;
		tempGrids.push_back(grid);
	}

	std::sort(tempGrids.begin(), tempGrids.end(), [&](Grid* left, Grid* right) { return left->minPoint.z < right->minPoint.z; });

	double lowestZ = tempGrids[0]->minPoint.z;

	for (auto iter = tempGrids.begin(); iter != tempGrids.end();) {
		Grid* grid = *iter;
		auto nextGreaterZIter = iter + 1;
		while (nextGreaterZIter != tempGrids.end() && (*nextGreaterZIter)->minPoint.z <= grid->minPoint.z) {
			nextGreaterZIter++;
		}

		bool isBounded = nextGreaterZIter - iter > 1;
		for (; iter < nextGreaterZIter; iter++) {
			Grid* grid = *iter;
			if (grid->minPoint.z == lowestZ)
				grid->isLowestGrid = true;
			grid->isBounded = isBounded;
			grid->maxPoint.z = (nextGreaterZIter != tempGrids.end() ? std::nextafter((*nextGreaterZIter)->minPoint.z, -DBL_MAX) : DBL_MAX);
			if (!isBounded) {
				grid->minPoint.x = grid->minPoint.y = DBL_MAX;
				grid->maxPoint.x = grid->maxPoint.y = -DBL_MAX;
			}
		}
	}

}

void AStarNavigator::resetGrids()
{
	hasConditionalBarriers = 0.0;

	for (Grid* grid : grids) {
		grid->reset(this);
	}

	resolveGridBounds();

	// Clear custom barriers
	customBarriers = Array();

	// populate array of custom barriers
	for (int i = 0; i < objectBarrierList.size(); i++) {
		TreeNode* theObj = objectBarrierList[i]->holder;
		if (function_s(theObj, "customizeAStarGrid", holder, minNodeWidth))
			continue;
		addObjectBarrierToTable(theObj);
	}

	for (Grid* grid : grids) {
		grid->buildNodeTable();
	}

	areGridNodeTablesBuilt = true;
}


double AStarNavigator::onReset()
{

	heatMapTotalTraversals = 0;
	isGridDirty = true;
	isBoundsDirty = true;
	areGridNodeTablesBuilt = false;
	applyToTemporaryBarrier = nullptr;

	pathCache.clear();
	pathCount = 0;
	requestCount = 0;
	cacheUseCount = 0;

	directionChangePenalty = 0.05;
	if (deepSearch)
		directionChangePenalty = 0.025;

	resolveMinNodeWidth();

	maxPathWeight = 0.0;
	for (int i = 0; i < barrierList.size(); i++) {
		PreferredPath* path = barrierList[i]->toPreferredPath();
		if (path)
			maxPathWeight = max(path->pathWeight, maxPathWeight);
	}
	activeTravelers.clear();

	for (size_t i = 1; i <= content(node_v_travelmembers); i++) {
		treenode teNode = ownerobject(tonode(get(rank(node_v_travelmembers, i))));
		teNode->objectAs(TaskExecuter)->moveToResetPosition();
	}

	double sumSpeed = 0.0;
	for (int i = 0; i < travelers.size(); i++) {
		travelers[i]->onReset();
		sumSpeed += travelers[i]->te->v_maxspeed;
	}

	edgeTableExtraData.clear();
	extraDataNode->subnodes.clear();

	resetGrids();

	SimulationStartEvent::addObject(this);

	setDirty();

	for (Barrier* barrier : barrierList)
		barrier->onReset(this);

	if (enableCollisionAvoidance && collisionUpdateIntervalFactor > 0 && travelers.size() > 0) {
		double avgSpeed = sumSpeed / travelers.size();
		double avgNodeMoveTime = minNodeWidth / avgSpeed;
		collisionUpdateInterval = collisionUpdateIntervalFactor * avgNodeMoveTime;
	}
	else {
		collisionUpdateInterval = DBL_MAX;
	}
	nextCollisionUpdateTime = DBL_MAX;
	return 0;
}


double AStarNavigator::onStartSimulation()
{XS
	for (int i = 0; i < travelers.size(); i++)
		travelers[i]->onStartSimulation();
	return 0;
XE}

double AStarNavigator::onRunWarm()
{
	for (auto iter = edgeTableExtraData.begin(); iter != edgeTableExtraData.end(); iter++) {
		AStarNodeExtraData* extra = iter->second;
		extra->totalTraversals = 0;
		extra->totalBlockedTime = 0.0;
		extra->totalBlocks = 0;
	}
	return 0;
}

double AStarNavigator::onDraw(TreeNode* view)
{
	// Based on the drawMode, this function
	// draws the grid, barriers, and traffic
	int drawMode = (int)this->drawMode;
	if (drawMode == 0 && (showHeatMap == 0 || heatMapMode == 0) && showAllocations == 0 && showTravelThreshold == 0)
		return 0;

	int pickingmode = getpickingmode(view);
	treenode hovered = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, -1));
	if (hovered->ownerObject != holder)
		hovered = NULL;
	treenode selObj = selectedobject(view);

	if (!pickingmode) {
		// Show the activeBarrier if the AStarNavigator is highlighted
		if (objectexists(activeBarrier)) {
			bool showActiveBarrier = selObj == this->holder;
			Barrier* b = activeBarrier->objectAs(Barrier);
			b->isActive = showActiveBarrier;
			if (showActiveBarrier != isActiveBarrierBuilt)
				isBarrierDirty = true;
		}

		// Semi highlight hovered barrier
		if (objectexists(hovered)) {
			Barrier* b = hovered->objectAs(Barrier);
			if (!objectexists(activeBarrier) || !(activeBarrier->objectAs(Barrier)->mode & Barrier::CREATE)) {
				b->isHovered = true;
				isBarrierDirty = true;
			}
		}
		else if (isHoveredBarrierBuilt)
			isBarrierDirty = true;
	}

	double lengthMultiple = getmodelunit(LENGTH_MULTIPLE);
	if (isGridDirty) {
		if (drawMode & ASTAR_DRAW_MODE_GRID)
			buildGridMesh(0.05f / lengthMultiple);
		if (isGridMeshBuilt)
			isGridDirty = false;
	}
	if (isBoundsDirty) {
		if (drawMode & ASTAR_DRAW_MODE_BOUNDS)
			buildBoundsMesh(0);
		if (isBoundsMeshBuilt)
			isBoundsDirty = false;
	}
	if (isBarrierDirty) {
		if (drawMode & ASTAR_DRAW_MODE_BARRIERS)
			buildBarrierMesh(0);
		if (isBarrierMeshBuilt)
			isBarrierDirty = false;
	}

	if (!pickingmode) {
		// Save if the active barrier is built in the barrier mesh
		if (objectexists(activeBarrier)) {
			Barrier* b = activeBarrier->objectAs(Barrier);
			if (isBarrierMeshBuilt)
				isActiveBarrierBuilt = b->isActive;
			b->isActive = true;
		}
		else if (isBarrierMeshBuilt)
			isActiveBarrierBuilt = false;

		// unset hovered barrier
		if (objectexists(hovered)) {
			Barrier* b = hovered->objectAs(Barrier);
			isHoveredBarrierBuilt = b->isHovered;
			if (b->isHovered)
				b->isHovered = false;
		}
		else
			isHoveredBarrierBuilt = false;
	}
	
	double loc[3];
	vectorproject(holder, 0, 0, 0, model(), loc);

	fglScale(1.0/b_spatialsx, 1.0/b_spatialsy, 1.0/b_spatialsz);
	fglTranslate(-loc[0], -loc[1], -loc[2]);

	float factor, units;
	bool polyOffsetFill = glIsEnabled(GL_POLYGON_OFFSET_FILL);
	glGetFloatv(GL_POLYGON_OFFSET_FACTOR, &factor);
	glGetFloatv(GL_POLYGON_OFFSET_UNITS, &units);
	fglEnable(GL_POLYGON_OFFSET_FILL);

	double vpRadius = get(viewpointradius(view));
	if (get(viewprojectiontype(view)) == 1)
		vpRadius = maxof(get(spatialsx(view)), get(spatialsy(view))) / get(viewmagnification(view));
	double offset = max(-1, -50 / (vpRadius * getmodelunit(LENGTH_MULTIPLE)));

	if (!pickingmode) {
		fglDisable(GL_TEXTURE_2D);
		fglDisable(GL_LIGHTING);

		if (isGridMeshBuilt && (drawMode & ASTAR_DRAW_MODE_GRID)) {
			for (Grid* grid : grids)
				grid->gridMesh.draw(GL_LINES);
		}

		glPolygonOffset(offset - 0.010, -2);
		if (isBoundsMeshBuilt && (drawMode & ASTAR_DRAW_MODE_BOUNDS)) {
			for (Grid* grid : grids)
				grid->boundsMesh.draw(GL_TRIANGLES);
		}

		glPolygonOffset(offset - 0.025, -5);
		if (isBarrierMeshBuilt && (drawMode & ASTAR_DRAW_MODE_BARRIERS))
			barrierMesh.draw(GL_TRIANGLES);

		fglEnable(GL_TEXTURE_2D);
		fglEnable(GL_LIGHTING);

		glPolygonOffset(offset - 0.005, -1);
		if (showHeatMap != 0 && heatMapMode != 0)
			drawHeatMap(view);

		glPolygonOffset(offset - 0.015, -3);
		if (drawMode & ASTAR_DRAW_MODE_MEMBERS)
			drawMembers(0);

		glPolygonOffset(offset - 0.020, -4);
		if (showAllocations)
			drawAllocations(0);

		glPolygonOffset(offset - 0.030, -6);
		if (showTravelThreshold)
			drawDestinationThreshold(selectedobject(view), 0);

		if (debugRoutingAlgorithm && fglInfo(FGL_INFO_SHADERTYPE, view) == SHADERTYPE_DEFAULT) {

			treenode selObj = selectedobject(view);
			if (objectexists(selObj) && isclasstype(selObj, CLASSTYPE_TASKEXECUTER)) {
				TaskExecuter* te = selObj->objectAs(TaskExecuter);
				if (te->node_v_navigator->subnodes.length > 0) {
					treenode member = te->node_v_navigator->subnodes[1]->value;
					if (member && ownerobject(member) == holder) {
						drawRoutingAlgorithm(member->objectAs(Traveler), view);
					}
				}
			}

			for (Traveler* traveler : travelers) {
				if (switch_selected(traveler->te->holder, -1))
					drawRoutingAlgorithm(traveler, view);
			}
			fglEnable(GL_TEXTURE_2D);
			fglEnable(GL_LIGHTING);
		}
	} else {
		fglDisable(GL_TEXTURE_2D);
		fglDisable(GL_LIGHTING);

		if(drawMode & ASTAR_DRAW_MODE_BARRIERS) {
			for(int i = 0; i < barrierList.size(); i++) {
				Barrier* barrier = barrierList[i];

				Vec3 min, max;
				if (!barrier->getBoundingBox(min, max))
					continue;

				setpickingdrawfocus(view, holder, 0, barrier->holder);
				barrierMesh.draw(GL_TRIANGLES, barrier->meshOffset, barrier->nrVerts);
			}
		}

		if (drawMode & ASTAR_DRAW_MODE_BOUNDS) {
			for (Grid* grid : grids) {
				setpickingdrawfocus(view, holder, PICK_TYPE_BOUNDS, grid->holder);
				grid->boundsMesh.draw(GL_TRIANGLES);
			}
		}

		fglEnable(GL_TEXTURE_2D);
		fglEnable(GL_LIGHTING);
	}

	glPolygonOffset(factor, units);
	if (polyOffsetFill == false)
		fglDisable(GL_POLYGON_OFFSET_FILL);
	
	return 0;
}

double AStarNavigator::onClick(TreeNode* view, int clickcode)
{
	int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, 0);
	TreeNode* secondary = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, 0));

	if (objectexists(secondary) && pickType != PICK_TYPE_BOUNDS) {
		Barrier* barrier = secondary->objectAs(Barrier);

		// is there a current barrier
		if (objectexists(activeBarrier)) {
			Barrier* b = activeBarrier->objectAs(Barrier);
			// is the clicked barrier different than the current barrier
			if (b != barrier) {
				// Send the click to the activeBarrier if it's in create mode
				if (b->mode & Barrier::CREATE) {
					Vec3 pos(cursorinfo(view, 2, 1, 1), cursorinfo(view, 2, 2, 1), cursorinfo(view, 2, 3, 1));
					return b->onClick(view, (int)clickcode, pos);
				}

				// then reset the current barrier to be "not active"
				b->activePointIndex = 0;
				b->isActive = 0;
			}
		}
		// set the active barrier to the clicked barrier
		activeBarrier = barrier->holder;
		barrier->isActive = 1;
		setDirty();
		Vec3 pos(cursorinfo(view, 2, 1, 1), cursorinfo(view, 2, 2, 1), cursorinfo(view, 2, 3, 1));
		return barrier->onClick(view, (int)clickcode, pos);
	}
	if (objectexists(activeBarrier)) {
		Barrier* b = activeBarrier->objectAs(Barrier);
		b->activePointIndex = 0;
		b->isActive = 0;
		setDirty();
	}
	activeBarrier = 0;
	return FlexSimObject::onClick(view, (int)clickcode);
}

double AStarNavigator::onUndo(bool isUndo, treenode undoRecord)
{
	if (objectexists(activeBarrier)) {
		Barrier* b = activeBarrier->objectAs(Barrier);
		// Stop barrier creation
		if (b->mode & Barrier::CREATE) {
			if (b->pointList.size() > 2) {
				b->removePoint(min(b->activePointIndex, b->pointList.size() - 1));
				b->activePointIndex = b->pointList.size();
				b->mode = 0;
			}
			else
				destroyobject(b->holder);
		}
		else {
			// Fix active point index
			if(b->activePointIndex > b->pointList.size())
				b->activePointIndex = b->pointList.size();
		}
	}
	// Redraw barriers
	setDirty();
	return 0;
}

void AStarNavigator::addCreateRecord(treenode view, SimpleDataType* object, const char* name)
{
	int undoId = beginaggregatedundo(view, "Create Barrier");
	createundorecord(view, holder, UNDO_UPDATE_LINKS_ON_UNDO, 0, 0, 0);
	createundorecord(view, object->holder, UNDO_CREATE_OBJECT, 0, 0, 0);
	createundorecord(view, holder, UNDO_UPDATE_LINKS_ON_REDO, 0, 0, 0);
	endaggregatedundo(view, undoId);
}

double AStarNavigator::onDrag(TreeNode* view)
{
	int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, 0);
	TreeNode* secondary = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, 0));
	double dx = draginfo(DRAG_INFO_DX);
	double dy = draginfo(DRAG_INFO_DY);
	double dz = draginfo(DRAG_INFO_DZ);

	// Move all attached barriers
	if (pickType == PICK_TYPE_BOUNDS) {
		secondary->objectAs(Grid)->onDrag(view, Vec3(dx, dy, dz));

		setDirty();
		isBoundsDirty = true;
		isGridDirty = true;
		return 1;
	}

	if (objectexists(secondary) && pickType != PICK_TYPE_BOUNDS) {
		Barrier* barrier = secondary->objectAs(Barrier);
		barrier->onMouseMove(Vec3(cursorinfo(view, 2, 1, 1), cursorinfo(view, 2, 2, 1), 0), Vec3(dx, dy, dz));
		setDirty();
		return 1;
	} 
	
	return FlexSimObject::onDrag(view);
}

double AStarNavigator::dragConnection(TreeNode* connectTo, char keyPressed, unsigned int classType)
{
	if (!objectexists(connectTo))
		return 0;

	if (isclasstype(connectTo, CLASSTYPE_TASKEXECUTER)) {
		TaskExecuter* te = connectTo->objectAs(TaskExecuter);
		TreeNode* navigatorNode = te->node_v_navigator;

		switch(keyPressed & 0x7f) {
		case 'A': {
			TreeNode* theNavigator = tonode(get(first(navigatorNode)));
			TreeNode* travelMembers = node_v_travelmembers; 
			if (validlink(theNavigator, "")) {
				if (theNavigator->parent == travelMembers)
					return 0;
			}
			Traveler* traveler = travelers.add(new Traveler);
			clearcontents(navigatorNode);
			nodejoin(traveler->holder, nodeadddata(nodeinsertinto(navigatorNode), DATATYPE_COUPLING));
			te->v_useoffsets = OFFSET_BY_NAV_LOGIC;
			traveler->onReset();
			break;
		}

		case 'Q': {
			clearcontents(navigatorNode);
			TaskExecuter* te = connectTo->objectAs(TaskExecuter);
			Navigator* navigator = te->findDefaultNavigator()->objectAs(Navigator);
			createcoupling(navigatorNode, navigator->node_v_travelmembers);
			break;
				  }
		}
	
	} else if (!isclasstype(connectTo, CLASSTYPE_NETWORKNODE)) {
		ObjectDataType* theFR = &(o(ObjectDataType, connectTo));

		switch(keyPressed & 0x7f) {
		case 'A':
			for (int i = 0; i < objectBarrierList.size(); i++) {
				TreeNode* objectNode = objectBarrierList[i]->holder;
				if (objectNode == connectTo)
					return 0;
			}
			objectBarrierList.add(theFR);
			break;
		case 'Q':
			for (int i = 0; i < objectBarrierList.size(); i++) {
				TreeNode* objectNode = objectBarrierList[i]->holder;
				if (objectNode == connectTo) {
					objectBarrierList.remove(i);
					return 0;
				}
			}
			break;
		}
	}

	return 0;
}

double AStarNavigator::onDestroy(TreeNode* view)
{
	if (objectexists(view)) {
		if (objectexists(activeBarrier)) {
			Divider* divider = activeBarrier->objectAs(Barrier)->toDivider();
			if (divider && divider->mode == 0 && divider->pointList.size() > 2
				&& divider->activePointIndex != divider->pointList.size()) {
				// Remove a divider point
				divider->removePoint(divider->activePointIndex);
				// Set the previous point as the active
				if (divider->activePointIndex != 0)
					divider->activePointIndex -= 1;
			}
			else
				destroyobject(activeBarrier);
			setDirty();
		} else {
			destroyobject(holder);
		}
		return 1;
	}
	return 0;
}

double AStarNavigator::navigateToObject(TreeNode* traveler, TreeNode* destination, double endSpeed)
{
	double loc[3];

	if (isclasstype(destination, CLASSTYPE_FLEXSIMEVENTHANDLER) && o(FlexSimEventHandler, destination).usePlaceOffsetForTravel(&o(TaskExecuter, traveler))) {
		o(FlexSimEventHandler, destination).getPlaceOffset(traveler, 0, loc);
		return navigateToLoc(traveler, loc, endSpeed);
	}

	Vec3 size = destination->objectAs(ObjectDataType)->size;
	vectorproject(destination, 0.5 * size.x, -0.5 * size.y, 0, model(), loc);

	Traveler* t = getTraveler(traveler->objectAs(TaskExecuter));
	t->destThreshold = DestinationThreshold(destination, minNodeWidth);
	t->destNode = destination;
	return navigateToLoc(t, loc, endSpeed);
}


double AStarNavigator::navigateToLoc(Traveler* traveler, double* destLoc, double endSpeed)
{
	if (barrierList.size() == 0 && objectBarrierList.size() == 0) {
		msg("AStar Error", "No barriers found.\nThere must be at least one barrier associated with the AStar Navigator.", 1);
		return 0;
	}

	traveler->destLoc = Vec3(destLoc[0], destLoc[1], destLoc[2]);
	traveler->endSpeed = endSpeed;

	if (activeTravelers.size() == 0 && collisionUpdateInterval < FLT_MAX && nextCollisionUpdateTime == DBL_MAX) {
		nextCollisionUpdateTime = time() + collisionUpdateInterval;
		createevent(new CollisionIntervalUpdateEvent(this, nextCollisionUpdateTime));
	}

	TravelPath path = calculateRoute(traveler, traveler->destLoc, traveler->destThreshold, endSpeed, false);
	traveler->navigatePath(std::move(path));
	return 0;
}



double AStarNavigator::navigateToLoc(treenode traveler, double * destLoc, double endSpeed)
{
	destLoc = Vec3(destLoc).project(traveler->findOwnerObject(), model());
	Traveler* t = getTraveler(traveler->objectAs(TaskExecuter));
	t->destThreshold = DestinationThreshold();
	t->destNode = nullptr;
	t->endSpeed = endSpeed;
	navigateToLoc(t, destLoc, endSpeed);
	return 0.0;
}

void AStarNavigator::onMemberDestroyed(TaskExecuter * te)
{
	getTraveler(te)->onTEDestroyed();
}

void AStarNavigator::onCollisionIntervalUpdate()
{
	if (activeTravelers.size() == 0) {
		nextCollisionUpdateTime = DBL_MAX;
		return;
	}

	nextCollisionUpdateTime = time() + collisionUpdateInterval;
	for (Traveler* traveler : activeTravelers) {
		traveler->onCollisionIntervalUpdate();
	}

	createevent(new CollisionIntervalUpdateEvent(this, nextCollisionUpdateTime));
}

AStarSearchEntry* AStarNavigator::checkExpandOpenSet(Grid* grid, AStarNode* node, AStarSearchEntry* entryIn, Direction direction, 
	float rotDirection, double distFactor, double bonusMod, AStarNodeExtraData* preferredPathData)
{
	if (node->canGo(direction)) {
		int theCol = entryIn->cell.col + AStarNode::colInc[direction];
		int theRow = entryIn->cell.row + AStarNode::rowInc[direction];
		double distance = distFactor;
		if (preferredPathData && preferredPathData->getBonus(direction) != 0) {
			distance *= 1.0 - (bonusMod * (double)(int)preferredPathData->getBonus(direction)) / 127;
		}
		return expandOpenSet(grid, theRow, theCol, distance, rotDirection);
	}
	return nullptr;
}

AStarSearchEntry* AStarNavigator::checkExpandOpenSetDiagonal(Grid* grid, AStarNode* node, AStarSearchEntry* entryIn,
	Direction dir1, Direction dir2, float rotDirection, double dist, AStarNodeExtraData* preferredPathData)
{
	if (!node->canGo(dir1) || !node->canGo(dir2))
		return nullptr;
	AStarCell cell;
	AStarSearchEntry* e1 = nullptr;
	cell.grid = grid->rank;
	cell.row = entryIn->cell.row + AStarNode::rowInc[dir1];
	cell.col = entryIn->cell.col;
	AStarNode* vertNode = grid->getNode(cell);
	if (vertNode->canGo(dir2)) {
		auto iter = entryHash.find(cell.value);
		if (iter != entryHash.end()) {
			AStarSearchEntry* vert = &totalSet[iter->second];
			e1 = checkExpandOpenSet(grid, vertNode, vert, dir2, rotDirection, dist, ROOT2_DIV2, preferredPathData);
		}
	}
	if (e1 == nullptr) {
		cell.row = entryIn->cell.row;
		cell.col = entryIn->cell.col + AStarNode::colInc[dir2];
		AStarNode* hrzNode = grid->getNode(cell);
		if (hrzNode->canGo(dir1)) {
			auto iter = entryHash.find(cell.value);
			if (iter != entryHash.end()) {
				AStarSearchEntry* hrz = &totalSet[iter->second];
				e1 = checkExpandOpenSet(grid, hrzNode, hrz, dir1, rotDirection, dist, ROOT2_DIV2, preferredPathData);
			}
		}
	}

	if (e1 && deepSearch == SEARCH_DEEP_DIAGONALS) {
		AStarNode* n1 = grid->getNode(e1->cell);
		AStarSearchEntry e1StackCopy = *e1;

		float deepDiagonalUpRotOffset = 22.5f;
		if (rotDirection == 135.0f || rotDirection == -45.0f)
			deepDiagonalUpRotOffset = -22.5f;

		checkExpandOpenSet(grid, n1, (&e1StackCopy), dir1, 
			clampDirection(rotDirection + deepDiagonalUpRotOffset), 
			ROOT5_DIVROOT2 * dist, ROOT5_DIV5, preferredPathData);
		
		checkExpandOpenSet(grid, n1, (&e1StackCopy), dir2, 
			clampDirection(rotDirection - deepDiagonalUpRotOffset),
			ROOT5_DIVROOT2 * dist, ROOT5_DIV5, preferredPathData);
	}
	return e1;
}


TravelPath AStarNavigator::calculateRoute(Traveler* traveler, double* tempDestLoc, const DestinationThreshold& destThreshold, double endSpeed, bool doFullSearch, double startTime)
{
	TreeNode* travelerNode = traveler->te->holder;
	routingTraveler = traveler;
	routingTravelStartTime = startTime < 0 ? time() : startTime;
	if (debugRoutingAlgorithm)
		traveler->routingAlgorithmSnapshots.clear();
	if (stopForTurns) {
		traveler->turnDelay = turnDelay->evaluate(traveler->te->holder);
		traveler->turnSpeed = turnSpeed->evaluate(traveler->te->holder);
	}
	//if (routeByTravelTime && enableCollisionAvoidance) {
	//	traveler->estimatedIndefiniteAllocTimeDelay = indefiniteAllocTimePenalty->evaluate(traveler->te->holder);
	//}
	double centerx = 0.5 * xsize(travelerNode);
	double centery = 0.5 * ysize(travelerNode);

	vectorproject(travelerNode, centerx, - centery, 0, model(), startLoc);
	
	destLoc.x = tempDestLoc[0];
	destLoc.y = tempDestLoc[1];
	destLoc.z = tempDestLoc[2];
	Vec3 clampedDestLoc = destLoc;

	TaskExecuter* te = traveler->te;

	AStarCell startCell = getCellFromLoc(startLoc);
	AStarCell destCell = getCellFromLoc(destLoc);

	// This will either be generated by the search, or looked up by the cache

	// Figure out if this path is in the cache
	bool shouldUseCache = false;
	CachedPathID p;
	if (cachePaths && !doFullSearch && !routeByTravelTime && !hasConditionalBarriers) {
		requestCount++;
		p.startRow = startCell.row;
		p.startCol = startCell.col;
		p.endRow = destCell.row;
		p.endCol = destCell.col;
		p.destination = traveler->destNode;
	
		auto e = pathCache.find(p);
		if (e != pathCache.end()) {
			cacheUseCount++;
			return e->second;
		}
	}

	Grid* startGrid = getGrid(startCell);
	startLoc.x = startGrid->gridOrigin.x + startCell.col * startGrid->nodeWidth;
	startLoc.y = startGrid->gridOrigin.y + startCell.row * startGrid->nodeWidth;

	Grid* destGrid = getGrid(destCell);
	// set x/y to the cetner of the dest grid point
	clampedDestLoc.x = destGrid->gridOrigin.x + destCell.col * destGrid->nodeWidth;
	clampedDestLoc.y = destGrid->gridOrigin.y + destCell.row * destGrid->nodeWidth;

	// total set includes all resolved and open nodes in the graph
	totalSet.clear();
	// opensetheap is a sorted list of the nodes in the open set
	// the value is the solution of f(x,y) for that node in the set
	openSetHeap = std::priority_queue<HeapEntry, std::vector<HeapEntry>, HeapEntryCompare>();

	visitedConditionalBarriers.clear();
	entryHash.clear();
	// add the first node to the "open set"
	totalSet.push_back(AStarSearchEntry());
	AStarSearchEntry* start = &totalSet.back();
	start->cell = startCell;

	// Set the destination outside a barrier if necessary
	if (ignoreDestBarrier) {
		AStarCell tempDestCell = destCell;
		checkGetOutOfBarrier(tempDestCell, te, startCell.row, startCell.col, &traveler->destThreshold);
	}

	// Get out of a barrier if necessary
	checkGetOutOfBarrier(start->cell, te, destCell.row, destCell.col, nullptr);

	start->g = 0;
	start->h = (1.0 - maxPathWeight) * sqrt(sqr(clampedDestLoc.x - startLoc.x) + sqr(clampedDestLoc.y - startLoc.y) + sqr(clampedDestLoc.z - startLoc.z));
	start->f = start->g + start->h;
	start->previous = ~0;
	start->closed = 0;

	start->rotOnArrival = traveler->te->b_spatialrz;

	entryHash[start->cell.value] = 0;

	// the open set stores:
	// 1. the index into totalset that references the AStarSearchEntry that i'm going to resolve
	// 2. the solution f(x, y) of that AStarSearchEntry
	openSetHeap.push(HeapEntry(start->f, 0));

	AStarNode* startNode = getNode(start->cell);
	if (startNode->hasConditionalBarrier) {
		shortest = *start;
		updateConditionalBarrierDataOnOpenSetExpanded(start->cell, startNode);
	}

	closestSoFar = 10000000000000.0f;
	closestIndex = 0;

	AStarSearchEntry * final = NULL;
	// closestSoFar is the closest h I've found so far
		
	int size;
	while ((size = openSetHeap.size()) > 0) {
		HeapEntry heapEntry(0.0f, 0); 
		AStarSearchEntry * entry = NULL;
		// here I pop off an entry from the heap.
		// the trick is that some entries may have changed their g value
		// in the mean time, so I need to throw away entries if they are 
		// older, bigger g's (i.e. the heap value doesn't match with the 
		// entry's current f value). In this case, the entry will already 
		// have been closed.
		do {
			heapEntry = openSetHeap.top();
			openSetHeap.pop();
			entry = &(totalSet[heapEntry.totalSetIndex]);
		} while(entry->closed && openSetHeap.size() > 0);

		if (!entry) break;

		shortestIndex = heapEntry.totalSetIndex;
		shortest = *entry;

		if (shortest.h < closestSoFar) {
			closestSoFar = shortest.h;
			closestIndex = heapEntry.totalSetIndex;
		}
		// close the node
		entry->closed = true;
		shortest.closed = true;
		n = getNode(shortest.cell);
		n->open = false;

		// if I am at the destination, then break out of the solve loop
		if ((shortest.cell.col == destCell.col && shortest.cell.row == destCell.row) 
				|| traveler->destThreshold.isWithinThreshold(shortest.cell, Vec2(destGrid->gridOrigin.x, destGrid->gridOrigin.y), destLoc, destGrid->nodeWidth)) {
			final = &shortest;
			break;
		}

/*

The diagram below shows a complete search order for a deep search,
which results from the expansion of the search macros.
The / should be read "depends on" or "is accesible from". The *
means that the node depends on either of the two adjacent nodes
closest to the search center. A non-deep search would not search
the outside 8 nodes.

+-----------------------------+  
|     | 9/8 |     | 6/5 |     |	 
+-----+-----+-----+-----+-----|	 
|10/8 | 8*  |  1  | 5*  | 7/5 |	 
+-----+-----+-----+-----+-----|	 
|     |  4  |  0  |  3  |     |	 
+-----+-----+-----+-----+-----|	 
|13/11| 11* |  2  | 14* |16/14|	 
+-----+-----+-----+-----+-----|	 
|     |12/11|     |15/14|     |	 
+-----------------------------+	 

*/

		Grid* grid = getGrid(shortest.cell);
		AStarNodeExtraData* preferredPathData = nullptr;
		if (n->hasPreferredPathWeight) {
			preferredPathData = edgeTableExtraData.find(shortest.cell.value)->second;
		}
		if (n->hasConditionalBarrier && preferredPathData) {
			AStarNodeExtraData* barrierData = edgeTableExtraData[shortest.cell.value];
			for (Barrier* barrier : barrierData->conditionalBarriers) {
				PreferredPath* path = barrier->toPreferredPath();
				if (path && !path->shouldApplyConditionalBarrier)
					preferredPathData = nullptr;
			}
		}

		checkExpandOpenSet(grid, n, (&shortest), Up, 90.0f, 1.0, 1.0, preferredPathData);
		checkExpandOpenSet(grid, n, (&shortest), Right, 0.0f, 1.0, 1.0, preferredPathData);
		checkExpandOpenSet(grid, n, (&shortest), Down, -90.0f, 1.0, 1.0, preferredPathData);
		checkExpandOpenSet(grid, n, (&shortest), Left, 180.0f, 1.0, 1.0, preferredPathData);

		if (deepSearch != SEARCH_RIGHT_ANGLES_ONLY) {
			checkExpandOpenSetDiagonal(grid, n, (&shortest), Up, Right, 45.0f, ROOT2, preferredPathData);
			checkExpandOpenSetDiagonal(grid, n, (&shortest), Up, Left, 135.0f, ROOT2, preferredPathData);
			checkExpandOpenSetDiagonal(grid, n, (&shortest), Down, Right, -45.0f, ROOT2, preferredPathData);
			checkExpandOpenSetDiagonal(grid, n, (&shortest), Down, Left, -135.0f, ROOT2, preferredPathData);
		}

		if (n->hasBridgeStartPoint) {
			auto e = edgeTableExtraData.find(shortest.cell.value);
			AStarNodeExtraData* extra = e->second;
			if (e != edgeTableExtraData.end() && extra->bridges.size() > 0) {
				for (int i = 0; i < extra->bridges.size(); i++) {
					auto& entry = extra->bridges[i];
					if (entry.bridge->useCondition && !entry.bridge->condition->evaluate(routingTraveler->te->holder))
						continue;
					double addedDist = entry.bridge->travelDistance + grid->nodeWidth;
					Point* endPoint = entry.isAtBridgeStart ? entry.bridge->pointList.back() : entry.bridge->pointList.front();
					AStarCell endCell = getCellFromLoc(Vec2(endPoint->x, endPoint->y));
					AStarNode* node = getNode(endCell);
					expandOpenSet(getGrid(endCell), endCell.row, endCell.col, addedDist / grid->nodeWidth, 0, i);
				}
			}
		}

		if (debugRoutingAlgorithm) {
			traveler->routingAlgorithmSnapshots.resize(traveler->routingAlgorithmSnapshots.size() + 1);
			auto& entry = traveler->routingAlgorithmSnapshots.back();
			entry.shortestIndex = shortestIndex;
			entry.totalSet = totalSet;
		}
	} // End of the while loop

	if (visitedConditionalBarriers.size() > 0) {
		for (auto iter = visitedConditionalBarriers.rbegin(); iter != visitedConditionalBarriers.rend(); iter++) {
			Barrier* barrier = *iter;
			if (barrier->conditionalBarrierChanges.isApplied)
				barrier->conditionalBarrierChanges.unapply();
		}
		visitedConditionalBarriers.clear();
	}

	// remake the start pointer (totalSet may reallocate due to push_back)
	start = totalSet.data();

	if (!final)  {
		final = &(totalSet[closestIndex]);
	}

	TravelPath travelPath;

	unsigned int startPrevVal =  ~((unsigned int)0);
	AStarSearchEntry* temp = final;
	char prevBridgeIndex = -1;
	while (1) {
		travelPath.push_back(AStarPathEntry(temp->cell, prevBridgeIndex));
		if (temp->previous != startPrevVal) {
			prevBridgeIndex = temp->prevBridgeIndex;
			temp = &(totalSet[temp->previous]);
		}
		else break;
	}

	if (startCell != start->cell) {
		// build the path into the barrier to the start cell if 
		// there is a barrier. Note that I'm building the path backwards
		// I reverse it later on.
		AStarCell curCell = start->cell;
		while (curCell != startCell) {
			int rowDiff = startCell.row - curCell.row;
			int colDiff = startCell.col - curCell.col;
			bool isMovedVertical = false;
			if (rowDiff != 0) {
				curCell.row += (short)sign(rowDiff);
				isMovedVertical = true;
			}
			if (colDiff != 0 && (deepSearch != SEARCH_RIGHT_ANGLES_ONLY || !isMovedVertical)) {
				curCell.col += (short)sign(colDiff);
			}

			if (colDiff != 0 && rowDiff != 0 && deepSearch == SEARCH_DEEP_DIAGONALS) {
				if (abs(colDiff) > 1 && abs(colDiff) > abs(rowDiff))
					curCell.col += (short)sign(colDiff);
				else if (abs(rowDiff) > 1 && abs(rowDiff) > abs(colDiff))
					curCell.row += (short)sign(rowDiff);
			}

			travelPath.push_back(AStarPathEntry(curCell, -1));
		}
	}

	for (int i = 0, totalSetSize = totalSet.size(); i < totalSetSize; i++) {
		AStarSearchEntry & e = totalSet[i];
		AStarNode* n = getNode(e.cell);
		n->isInTotalSet = false;
		n->open = true;
	}
	totalSet.clear();

	// right now the travelPath is backwards, so reverse it
	for (int i = 0; i < travelPath.size() / 2; i++) {
		auto temp = travelPath[i];
		travelPath[i] = travelPath[travelPath.size() - i - 1];
		travelPath[travelPath.size() - i - 1] = temp;
	}

	if (destThreshold.xAxisThreshold > 0 || destThreshold.yAxisThreshold > 0) {
		double threshold = sqrt(destThreshold.xAxisThreshold * destThreshold.xAxisThreshold 
			+ destThreshold.yAxisThreshold * destThreshold.yAxisThreshold);
		while (travelPath.size() > 1) {
			Vec3 pos = getLocFromCell(travelPath[travelPath.size() - 2].cell);
			Vec3 diff = pos - Vec3(destLoc.x, destLoc.y, 0);
			if (diff.magnitude > threshold)
				break;
			travelPath.pop_back();
		}
	}

	if (cachePaths && !doFullSearch && !routeByTravelTime) {
		pathCache[p] = travelPath;
		pathCount++;
	}

	routingTraveler = nullptr;

	return travelPath;
}

double AStarNavigator::queryDistance(TaskExecuter* taskexecuter, FlexSimObject* destination)
{
	taskexecuter->updateLocations();
	Traveler* traveler = getTraveler(taskexecuter);
	double destLoc[3];
	vectorproject(destination->holder, 0.5 * xsize(destination->holder), -0.5 * ysize(destination->holder), 0, model(), destLoc);

	DestinationThreshold destThreshold(destination->holder, minNodeWidth);
	TravelPath path = calculateRoute(traveler, destLoc, destThreshold, 0, true);
	return path.calculateTotalDistance(this);
}

void AStarNavigator::updateConditionalBarrierDataOnOpenSetExpanded(const AStarCell& cell, AStarNode* n)
{
	AStarNodeExtraData* barrierData = edgeTableExtraData[cell.value];
	for (Barrier* barrier : barrierData->conditionalBarriers) {
		if (visitedConditionalBarriers.find(barrier) == visitedConditionalBarriers.end()) {
			visitedConditionalBarriers.insert(barrier);
			bool shouldApplyBarrier = (bool)barrier->condition->evaluate(routingTraveler->te->holder);
			if (shouldApplyBarrier) {
				barrier->conditionalBarrierChanges.apply();
			}

			if (n->hasPreferredPathWeight) {
				PreferredPath* path = barrier->toPreferredPath();
				if (path)
					path->shouldApplyConditionalBarrier = shouldApplyBarrier;
			}
		}
	}
}

AStarSearchEntry* AStarNavigator::expandOpenSet(Grid* grid, int r, int c, float multiplier, float rotDirection, char bridgeIndex)
{
	AStarSearchEntry* entry = NULL;
	int closed = 0;
	int totalSetIndex;
	AStarNode* n = grid->getNode(r, c);
	// is he already in the total set
	if (n->isInTotalSet) {
		// if he's in the total set and he's closed, then abort
		if (!n->open) {
			return NULL;
		}

		AStarSearchEntry hashEntry;
		hashEntry.cell.grid = grid->rank;
		hashEntry.cell.row = r;
		hashEntry.cell.col = c;
		totalSetIndex = entryHash[hashEntry.cell.value];
		entry = &(totalSet[totalSetIndex]);
	}

	if (n->hasConditionalBarrier) {
		updateConditionalBarrierDataOnOpenSetExpanded(AStarCell(grid->rank, r, c), n);
	}

	float speedScale = routeByTravelTime ? 1.0 / routingTraveler->te->v_maxspeed : 1.0;
	float newG = shortest.g + multiplier * grid->nodeWidth * speedScale;

	float rotationTime = 0.0f;
	/*  Check if the guy is changing directions. If so, I want to increase the distance so it will be a penalty to make turns*/
	if(rotDirection != shortest.rotOnArrival) {
		float diff = rotDirection - shortest.rotOnArrival;
		if (diff > 180.0f)
			diff -= 360.0f;
		else if (diff < -180.0f)
			diff += 360.0f;
		// add a small penalty if he's turning
		if (routeByTravelTime && stopForTurns) {
			rotationTime = routingTraveler->turnDelay;

			rotationTime += fabs(diff) / routingTraveler->turnSpeed;
			newG += rotationTime;
		} else {
			newG += directionChangePenalty * grid->nodeWidth;
			// if it's a right angle turn or more, then add more penalty
			if (fabs(diff) >= 90.0f)
				newG += directionChangePenalty * grid->nodeWidth;
		}
	}
	
	if (!entry || newG < entry->g - 0.01 * grid->nodeWidth) {
		// if entry is NULL, that means he's not in the total set yet,
		// so I need to add him.
		if (!entry) {
			totalSetIndex = totalSet.size();
			totalSet.push_back(AStarSearchEntry());
			entry = &totalSet.back();
			entry->cell.grid = grid->rank;
			entry->cell.col = c;
			entry->cell.row = r;
			entryHash[entry->cell.value] = totalSetIndex;
			// calculate the distance heuristic h
			double diffx = destLoc.x - (grid->gridOrigin.x + entry->cell.col * grid->nodeWidth);
			double diffy = destLoc.y - (grid->gridOrigin.y + entry->cell.row * grid->nodeWidth);
			entry->h = (1.0 - maxPathWeight) * sqrt(diffx*diffx + diffy*diffy) * speedScale;
			entry->closed = 0;
			n->isInTotalSet = true;
		}
		entry->g = newG;
		entry->f = entry->g + entry->h;
		openSetHeap.push(HeapEntry(entry->f, totalSetIndex));
		entry->previous = shortestIndex;
		entry->rotOnArrival = rotDirection;
		entry->prevBridgeIndex = bridgeIndex;
	}
	return entry;
}

double AStarNavigator::abortTravel(TreeNode* travelerNode, TreeNode* newTS)
{
	TaskExecuter* te = travelerNode->objectAs(TaskExecuter);
	Traveler* traveler = getTraveler(te);
	if (!traveler->isActive)
		return 0;
	traveler->abortTravel(newTS);
	return 0;
}

double AStarNavigator::updateLocations()
{
	for (auto iter = activeTravelers.begin(); iter != activeTravelers.end(); iter++)
		(*iter)->updateLocation();
	return 0;
}

double AStarNavigator::updateLocations(TaskExecuter* te)
{
	if (!objectexists(te->activetask))
		return 0;
	
	Traveler* traveler = getTraveler(te);
	if (traveler->isActive)
		traveler->updateLocation();
	return 0;
}

void AStarNavigator::addObjectBarrierToTable(TreeNode* theObj)
{
	if (!areGridNodeTablesBuilt) {
		Array customBarrier = Array(1);
		customBarrier[1] = theObj;
		customBarriers.push(customBarrier);
		return;
	}

	for (Grid* grid : grids)
		grid->addObjectBarrierToTable(theObj);
}

void AStarNavigator::getBoundingBox(TreeNode* theObj, Vec3& min, Vec3& max)
{
	min = Vec3(DBL_MAX, DBL_MAX, DBL_MAX);
	max = Vec3(-DBL_MAX, -DBL_MAX, -DBL_MAX);
	// Shrink the bounding box for objects
	auto checkBound = [theObj, &min, &max](double x, double y, double z) {
		Vec3 outVec;
		vectorproject(theObj, x, y, z, model(), outVec);
		if (outVec.x < min.x)
			min.x = outVec.x;
		if (outVec.x > max.x)
			max.x = outVec.x;
		if (outVec.y < min.y)
			min.y = outVec.y;
		if (outVec.y > max.y)
			max.y = outVec.y;
		if (outVec.z < min.z)
			min.z = outVec.z;
		if (outVec.z > max.z)
			max.z = outVec.z;
	};
	
	checkBound(0, 0, 0);
	checkBound(xsize(theObj), 0, 0);
	checkBound(xsize(theObj), -ysize(theObj), 0);
	checkBound(0, -ysize(theObj), 0);

	checkBound(0, 0, zsize(theObj));
	checkBound(xsize(theObj), 0, zsize(theObj));
	checkBound(xsize(theObj), -ysize(theObj), zsize(theObj));
	checkBound(0, -ysize(theObj), zsize(theObj));
};

void AStarNavigator::buildBoundsMesh(float z)
{

	for (Grid* grid : grids)
		grid->buildBoundsMesh();

	if (!areGridNodeTablesBuilt) {
		isBoundsMeshBuilt = false;
		return;
	}
	isBoundsMeshBuilt = true;
}

void AStarNavigator::buildBarrierMesh(float z)
{
	resolveMinNodeWidth();
	barrierMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, 0);
	float up[3] = {0.0f, 0.0f, 1.0f};
	barrierMesh.setMeshAttrib(MESH_NORMAL, up);
	for (int i = 0; i < barrierList.size(); i++) {
		Barrier* barrier = barrierList[i];
		if (barrier->nodeWidth <= 0)
			barrier->nodeWidth = minNodeWidth;
		barrier->addVertices(&barrierMesh, z);
	}

	isBarrierMeshBuilt = true;
}

void AStarNavigator::drawHeatMap(TreeNode* view)
{
	for (Grid* grid : grids)
		grid->drawHeatMap(view);

}

float AStarNavigator::clampDirection(float rotDirection)
{
	int quadrant = (int)(((int)rotDirection + 191) / 22.5);
	switch (quadrant) {
	case 0: return 180.0f;
	case 1: return -153.434948822923f;
	case 2: return -135.0f;
	case 3: return -116.565051177095f;
	case 4: return -90.0f;
	case 5: return -63.434948822917f;
	case 6: return -45.0f;
	case 7: return -26.565051177089f;
	case 8: return 0.0f;
	case 9: return 26.565051177089f;
	case 10: return 45.0f;
	case 11: return 63.434948822917f;
	case 12: return 90.0f;
	case 13: return 116.565051177095f;
	case 14: return 135.0f;
	case 15: return 153.434948822923f;
	case 16: return 180.0f;
	}
	return 0.0;
}

void AStarNavigator::drawMembers(float z)
{
	memberMesh.init(0, MESH_POSITION, MESH_FORCE_CLEANUP);
	TreeNode* colorNode = node_b_color;
	float r = get(rank(colorNode, 1));
	float g = get(rank(colorNode, 2));
	float b = get(rank(colorNode, 3));
	float color[4] = {r, g, b, 0.3f};
	float up[3] = {0.0f, 0.0f, 1.0f};
	float black[4] = {0.0f, 0.0f, 0.0f, 0.5f};

	memberMesh.setMeshAttrib(MESH_NORMAL, up);
	memberMesh.setMeshAttrib(MESH_DIFFUSE4, color);

	// Draw rectangles under every object
	unsigned int numObjs = objectBarrierList.size();
	for (int i = 0; i < numObjs; i++) {
		ObjectDataType* theFR = objectBarrierList[i];
		TreeNode* theNode = theFR->holder;

		Vec3 topLeft, bottomLeft, topRight, bottomRight;
		vectorproject(theNode, 0, 0, 0, model(), topLeft);
		vectorproject(theNode, 0, -ysize(theNode), 0, model(), bottomLeft);
		vectorproject(theNode, xsize(theNode), -ysize(theNode), 0, model(), bottomRight);
		vectorproject(theNode, xsize(theNode), 0, 0, model(), topRight);
		topLeft.z = bottomLeft.z = topRight.z = bottomRight.z = 0;

		auto addVertex = [this](const Vec3& pos) {
			Vec3f posf(pos);
			int newVertex = memberMesh.addVertex();
			memberMesh.setVertexAttrib(newVertex, MESH_POSITION, posf);
		};

		addVertex(topLeft);
		addVertex(bottomLeft);
		addVertex(topRight);
		addVertex(bottomRight);
		addVertex(topRight);
		addVertex(bottomLeft);
	}

#define ABV(pos) {\
	int newVertex = memberMesh.addVertex();\
	memberMesh.setVertexAttrib(newVertex, MESH_POSITION, pos);\
	}

#define ABT(pos1, pos2, pos3) ABV(pos1) ABV(pos2) ABV(pos3)

	const static float TWO_PI = 2 * 3.1415926536f;
	static int numSides = 20;
	static float dTheta = TWO_PI / (float)numSides;
	// Draw circles under every traveler
	for (int i = 0; i < travelers.size(); i++) {
		Traveler * t = travelers[i];
		if (t->isActive)
			continue;
		TreeNode* traveler = t->te->holder;

		double outputVector[3];
		vectorproject(traveler, 0.5 * xsize(traveler), -0.5 * ysize(traveler), 0, model(), outputVector);
		float x = outputVector[0];
		float y = outputVector[1];

		float width = get(spatialsx(traveler));
		float height = get(spatialsy(traveler));
		float radius = sqrt(width * width / 4.0 + height * height / 4.0);
		float center[3] = {x, y, z};

		// Triangle strip
		for (int i = 0; i < numSides; i++) {
			float theta = dTheta * i;
			float nextTheta = dTheta * (i + 1);
			float sinTheta = sin(theta);
			float cosTheta = cos(theta);
			float sinNextTheta = sin(nextTheta);
			float cosNextTheta = cos(nextTheta);

			float pos1[3] = {
				radius * cosTheta + center[0], 
				radius * sinTheta + center[1], 
				z
			};

			float pos2[3] = {
				radius * cosNextTheta  + center[0], 
				radius * sinNextTheta + center[1], 
				z
			};

			ABT(center, pos1, pos2);
		}
	}

	for (auto i = activeTravelers.begin(); i != activeTravelers.end(); i++) {
		Traveler* t = *i;
		TreeNode* traveler = t->te->holder;

		double outputVector[3];
		vectorproject(traveler, 0.5 * xsize(traveler), -0.5 * ysize(traveler), 0, model(), outputVector);
		float x = outputVector[0];
		float y = outputVector[1];

		float width = get(spatialsx(traveler));
		float height = get(spatialsy(traveler));
		float radius = sqrt(width * width / 4.0 + height * height / 4.0);
		float center[3] = {x, y, z};

		// Triangle strip
		for (int i = 0; i < numSides; i++) {
			float theta = dTheta * i;
			float nextTheta = dTheta * (i + 1);
			float sinTheta = sin(theta);
			float cosTheta = cos(theta);
			float sinNextTheta = sin(nextTheta);
			float cosNextTheta = cos(nextTheta);

			float pos1[3] = {
				radius * cosTheta + center[0], 
				radius * sinTheta + center[1], 
				z
			};

			float pos2[3] = {
				radius * cosNextTheta  + center[0], 
				radius * sinNextTheta + center[1], 
				z
			};

			ABT(center, pos1, pos2);
		}
	}

#undef ABT
#undef ABV

	fglDisable(GL_LIGHTING);
	fglDisable(GL_TEXTURE_2D);
	memberMesh.draw(GL_TRIANGLES);
	fglEnable(GL_LIGHTING);
	fglEnable(GL_TEXTURE_2D);
}

void AStarNavigator::buildGridMesh(float zOffset)
{
	for (Grid* grid : grids)
		grid->buildGridMesh(zOffset);

	if (!areGridNodeTablesBuilt) {
		isGridMeshBuilt = false;
		return;
	}
	isGridMeshBuilt = true;
}

void AStarNavigator::drawAllocations(float z)
{
	if (!showAllocations || time() <= 0)
		return;
	Mesh allocMesh;
	Mesh lineMesh;
	double diamondRadius = 0.2 * minNodeWidth;
	fglColor(0.8f, 0.5f, 0.0f, 1.0f);
	Vec4f fullClr(0.8f, 0.4f, 0.0f, 1.0f);
	Vec4f partialClr(0.8f, 0.4f, 0.0f, 0.4f);
	// Draw the grid one row at a time, using the large dimension
	
	allocMesh.init(0, MESH_POSITION | MESH_AMBIENT_AND_DIFFUSE4, MESH_DYNAMIC_DRAW);
	lineMesh.init(0, MESH_POSITION, MESH_DYNAMIC_DRAW);
	for (auto iter = edgeTableExtraData.begin(); iter != edgeTableExtraData.end(); iter++) {
		AStarNodeExtraData& nodeData = *(iter->second);
		if (nodeData.allocations.size() == 0)
			continue;
		auto currentAllocation = std::find_if(nodeData.allocations.begin(), nodeData.allocations.end(),
			[](NodeAllocation& alloc) { return alloc.acquireTime <= time() && alloc.releaseTime > time(); });
		bool isAllocCurrent = currentAllocation != nodeData.allocations.end();
		Vec4f& clr = !isAllocCurrent ? partialClr : fullClr;

		Vec3 centerPos = getLocFromCell(nodeData.cell);
		int vert = allocMesh.addVertex();
		allocMesh.setVertexAttrib(vert, MESH_POSITION, Vec3f(centerPos.x + diamondRadius, centerPos.y, z));
		allocMesh.setVertexAttrib(vert, MESH_AMBIENT_AND_DIFFUSE4, clr);
		vert = allocMesh.addVertex();
		allocMesh.setVertexAttrib(vert, MESH_POSITION, Vec3f(centerPos.x, centerPos.y + diamondRadius, z));
		allocMesh.setVertexAttrib(vert, MESH_AMBIENT_AND_DIFFUSE4, clr);
		vert = allocMesh.addVertex();
		allocMesh.setVertexAttrib(vert, MESH_POSITION, Vec3f(centerPos.x - diamondRadius, centerPos.y, z));
		allocMesh.setVertexAttrib(vert, MESH_AMBIENT_AND_DIFFUSE4, clr);
		vert = allocMesh.addVertex();
		allocMesh.setVertexAttrib(vert, MESH_POSITION, Vec3f(centerPos.x - diamondRadius, centerPos.y, z));
		allocMesh.setVertexAttrib(vert, MESH_AMBIENT_AND_DIFFUSE4, clr);
		vert = allocMesh.addVertex();
		allocMesh.setVertexAttrib(vert, MESH_POSITION, Vec3f(centerPos.x, centerPos.y - diamondRadius, z));
		allocMesh.setVertexAttrib(vert, MESH_AMBIENT_AND_DIFFUSE4, clr);
		vert = allocMesh.addVertex();
		allocMesh.setVertexAttrib(vert, MESH_POSITION, Vec3f(centerPos.x + diamondRadius, centerPos.y, z));
		allocMesh.setVertexAttrib(vert, MESH_AMBIENT_AND_DIFFUSE4, clr);

		if (isAllocCurrent) {
			while (currentAllocation != nodeData.allocations.end()) {
				lineMesh.setVertexAttrib(lineMesh.addVertex(), MESH_POSITION, Vec3f(centerPos.x, centerPos.y, centerPos.z));
				TaskExecuter* te = currentAllocation->traveler->te;
				Vec3 topPos = te->getLocation(0.5, 0.5, 1.1);
				if (te->holder->up != model())
					topPos = topPos.project(te->holder->up, model());
				lineMesh.setVertexAttrib(lineMesh.addVertex(), MESH_POSITION, Vec3f(topPos.x, topPos.y, topPos.z));
				currentAllocation++;
				currentAllocation = std::find_if(currentAllocation, nodeData.allocations.end(),
					[](NodeAllocation& alloc) { return alloc.acquireTime <= time() && alloc.releaseTime > time(); });
			}
		}
	}
	fglDisable(GL_LIGHTING);
	fglDisable(GL_TEXTURE_2D);
	allocMesh.draw(GL_TRIANGLES);
	fglColor(0.0f, 0.0f, 1.0f, 1.0f);
	lineMesh.draw(GL_LINES);
	fglEnable(GL_LIGHTING);
	fglEnable(GL_TEXTURE_2D);

}


void AStarNavigator::drawDestinationThreshold(TreeNode* destination, float z)
{
	if (!objectexists(destination))
		return;
	if (!areGridNodeTablesBuilt)
		return;

	Vec3 loc;
	Vec3 size = destination->objectAs(ObjectDataType)->size;
	vectorproject(destination, 0.5 * size.x, -0.5 * size.y, 0, model(), loc);

	getGrid(getCellFromLoc(loc))->drawDestinationThreshold(destination, loc, size);

}

void AStarNavigator::setDirty()
{
	isBarrierDirty = true;
}

AStarCell AStarNavigator::getCellFromLoc(const Vec3& modelLoc)
{
	return getGrid(modelLoc)->getCellFromLoc(modelLoc);
}

Vec3 AStarNavigator::getLocFromCell(const AStarCell & cell)
{
	return grids[max(1, cell.grid) - 1]->getLocFromCell(cell);
}

AStarNode * AStarNavigator::getNode(const AStarCell & cell)
{
	return grids[max(1, cell.grid) - 1]->getNode(cell);
}


Grid* AStarNavigator::getGrid(const AStarCell& cell) 
{ 
	return grids[max(1, cell.grid) - 1];
}

Grid * AStarNavigator::getGrid(const Vec3 & modelPos)
{
	for (Grid* grid : grids) {
		if (grid->isLocWithinBounds(modelPos, false)) {
			return grid;
		}
	}
	for (Grid* grid : grids) {
		if (grid->isLocWithinBounds(modelPos, true)) {
			return grid;
		}
	}
	// if I get this far, then something's wrong with grid bounds, so resolve grid bounds and try again
	resolveGridBounds();
	// believe me when I say this is not infinite recursioin
	return getGrid(modelPos);
}

ASTAR_FUNCTION Variant AStarNavigator_getGrid(FLEXSIMINTERFACE)
{
	return o(AStarNavigator, c).getGrid(Vec3(param(1), param(2), param(3)))->holder;
}

unsigned int AStarNavigator::getClassType()
{
	return CLASSTYPE_WANTCONNECTLOGIC | CLASSTYPE_FLEXSIMOBJECT | CLASSTYPE_NAVIGATOR;
}

void AStarNavigator::blockGridModelPos(const Vec3& modelPos)
{
	if (!areGridNodeTablesBuilt) {
		Array customBarrier = Array(3);
		customBarrier[1] = modelPos.x;
		customBarrier[2] = modelPos.y;
		customBarrier[3] = modelPos.z;
		customBarriers.push(customBarrier);
		return;
	}

	AStarCell cell = getCellFromLoc(modelPos);
	grids[max(1, cell.grid) - 1]->blockGridModelPos(modelPos);
}

void AStarNavigator::divideGridModelLine(const Vec3& modelPos1, const Vec3& modelPos2, bool oneWay)
{
	if (!areGridNodeTablesBuilt) {
		Array customBarrier = Array(7);
		customBarrier[1] = modelPos1.x;
		customBarrier[2] = modelPos1.y;
		customBarrier[3] = modelPos1.z;
		customBarrier[4] = modelPos2.x;
		customBarrier[5] = modelPos2.y;
		customBarrier[6] = modelPos2.z;
		customBarrier[7] = oneWay;
		customBarriers.push(customBarrier);
		return;
	}


	for (Grid* grid : grids)
		grid->divideGridModelLine(modelPos1, modelPos2, oneWay);
}


AStarNodeExtraData*  AStarNavigator::assertExtraData(const AStarCell& cell, ExtraDataReason reason)
{
	AStarNodeExtraData* extra;
	auto extraIter = edgeTableExtraData.find(cell.value);
	AStarNode* node = getNode(cell);
	if (extraIter == edgeTableExtraData.end()) {
		treenode newNode = extraDataNode->subnodes.add();
		extra = new AStarNodeExtraData;
		newNode->addSimpleData(extra, false);
		edgeTableExtraData[cell.value] = extra;
		extra->cell = cell;
	} else {
		extra = extraIter->second;
	}
	switch (reason) {
		case TraversalData		: node->hasTraversalData = true; break;
		case AllocationData		: node->hasAllocationData = true; break;
		case BridgeData			: node->hasBridgeStartPoint = true; break;
		case PreferredPathData	: node->hasPreferredPathWeight = true; break;
		case MandatoryPathData	: node->hasAllocationData = true; break;
		case ConditionalBarrierData  : 
			node->hasConditionalBarrier = true; 
			hasConditionalBarriers = 1.0;
			break;
		default: break;
	}
	return extra;
}

AStarCell AStarNavigator::getPrevCell(AStarCell & toCell, float rotDirection)
{
	AStarCell cell(toCell);
	switch ((int)rotDirection) {
	case -153: case -154: cell.col += 2; cell.row++; break;
	case -135: cell.col++; cell.row++; break;
	case -116: case -117: cell.row += 2; cell.col++; break;
	case -90: cell.row++; break;
	case -63: case -64: cell.row += 2; cell.col--; break;
	case -45: cell.row++; cell.col--; break;
	case -26: case -27: cell.row++; cell.col -= 2; break;
	case 0: cell.col--; break;
	case 26: case 27: cell.row--; cell.col -= 2; break;
	case 45: cell.row--; cell.col--; break;
	case 63: case 64: cell.row -= 2; cell.col--; break;
	case 90: cell.row--; break;
	case 116: case 117: cell.row -= 2; cell.col++; break;
	case 135: cell.row--; cell.col++; break;
	case 153: case 154: cell.row--; cell.col += 2; break;
	case 180: case -180: cell.col++; break;
	}
	return cell;
}


void AStarNavigator::buildActiveTravelerList()
{
	activeTravelers.clear();
	for (int i = 0; i < travelers.size(); i++) {
		Traveler* traveler = travelers[i];
		if (traveler->isActive) {
			activeTravelers.push_front(travelers[i]);
			traveler->activeEntry = activeTravelers.begin();
		}
	}
}


void AStarNavigator::dumpBlockageData(treenode destNode)
{
	destNode->dataType = DATATYPE_BUNDLE;
	clearbundle(destNode);
	addbundlefield(destNode, "GridX", BUNDLE_FIELD_TYPE_INT);
	addbundlefield(destNode, "GridY", BUNDLE_FIELD_TYPE_INT);
	addbundlefield(destNode, "ModelX", BUNDLE_FIELD_TYPE_DOUBLE);
	addbundlefield(destNode, "ModelY", BUNDLE_FIELD_TYPE_DOUBLE);
	addbundlefield(destNode, "TotalTraversals", BUNDLE_FIELD_TYPE_DOUBLE);
	addbundlefield(destNode, "TotalBlocks", BUNDLE_FIELD_TYPE_INT);
	addbundlefield(destNode, "TotalBlockedTime", BUNDLE_FIELD_TYPE_DOUBLE);

	Table table = Table(destNode);

	std::vector<AStarNodeExtraData*> allData;

	for (auto& entry : edgeTableExtraData) {
		allData.push_back(entry.second);
	}

	std::sort(allData.begin(), allData.end(), [](AStarNodeExtraData* left, AStarNodeExtraData* right) -> bool {
		if (left->cell.row < right->cell.row)
			return true;
		else if (left->cell.row > right->cell.row)
			return false;
		else if (left->cell.col <= right->cell.col)
			return true;
		else return false;
	});

	for (auto* data : allData) {
		table.addRow(0, 0);
		table[Variant(table.numRows)][Variant("GridX")] = data->cell.col;
		table[Variant(table.numRows)][Variant("GridY")] = data->cell.row;
		Vec3 loc = getLocFromCell(data->cell);
		table[Variant(table.numRows)][Variant("ModelX")] = loc.x;
		table[Variant(table.numRows)][Variant("ModelY")] = loc.y;
		table[Variant(table.numRows)][Variant("TotalTraversals")] = data->totalTraversals;
		table[Variant(table.numRows)][Variant("TotalBlocks")] = data->totalBlocks;
		table[Variant(table.numRows)][Variant("TotalBlockedTime")] = data->totalBlockedTime;
	}
}

void AStarNavigator::drawRoutingAlgorithm(Traveler * traveler, treenode view)
{
	if (traveler->routingAlgorithmSnapshots.size() == 0)
		return;

	float diamondRadius = 0.1f * (float)minNodeWidth;

	size_t index = (size_t)(routingAlgorithmCompletionRatio * traveler->routingAlgorithmSnapshots.size());
	if (index >= traveler->routingAlgorithmSnapshots.size())
		index = traveler->routingAlgorithmSnapshots.size() - 1;

	auto& snapshot = traveler->routingAlgorithmSnapshots[index];

	Mesh dotMesh;
	dotMesh.init(6, MESH_POSITION, MESH_DYNAMIC_DRAW);
	float position[][3] = {
		{0.0f, diamondRadius, 0.0f},
		{-diamondRadius, 0.0f, 0.0f},
		{ 0.0f, -diamondRadius, 0.0f },
		{ 0.0f, diamondRadius, 0.0f },
		{0.0f, -diamondRadius, 0.0f},
		{diamondRadius, 0.0f, 0.0f}
	};
	dotMesh.defineVertexAttribs(MESH_POSITION, position[0]);

	for (size_t i = 0; i < snapshot.totalSet.size(); i++) {
		AStarSearchEntry& entry = snapshot.totalSet[i];
		fglPushMatrix();

		Vec3 centerPos = getLocFromCell(entry.cell);
		//centerPos = centerPos / scale;
		fglTranslate(centerPos.x, centerPos.y, centerPos.z);

		if (i == snapshot.shortestIndex)
			fglColor(0.0f, 0.0f, 1.0f, 1.0f);
		else if (entry.closed)
			fglColor(1.0f, 0.0f, 0.0f, 1.0f);
		else fglColor(0.0f, 0.5f, 0.0f, 1.0f);

		dotMesh.draw(GL_TRIANGLES);
		char buffer[200];

		sprintf(buffer, "g%.2f + h%.2f = %.2f", entry.g, entry.h, entry.f);
		drawtext(view, buffer, -4 * diamondRadius, 0, diamondRadius, diamondRadius, diamondRadius, 0.01 * diamondRadius, 90, 0, 0, 0, 0, 0);
		fglDisable(GL_LIGHTING);

		fglPopMatrix();
	}

}

void AStarNavigator::resolveMinNodeWidth()
{
	minNodeWidth = DBL_MAX;
	for (Grid* grid : grids) {
		minNodeWidth = min(grid->nodeWidth, minNodeWidth);
	}
	if (minNodeWidth == DBL_MAX)
		minNodeWidth = 1.0;
}

TreeNode* AStarNavigator::addObject(const Vec3& pos1, const Vec3& pos2, EditMode barrierType) 
{
	EditMode editMode = barrierType != EditMode::NONE ? barrierType : AStarNavigator::editMode;
	Barrier* newBarrier = nullptr;
	Grid* newGrid = nullptr;
	switch (editMode) {
	default:
	case EditMode::SOLID_BARRIER: newBarrier = barrierList.add(new Barrier); break;
	case EditMode::DIVIDER: newBarrier = barrierList.add(new Divider); break;
	case EditMode::ONE_WAY_DIVIDER: newBarrier = barrierList.add(new OneWayDivider); break;
	case EditMode::PREFERRED_PATH: newBarrier = barrierList.add(new PreferredPath(defaultPathWeight)); break;
	case EditMode::BRIDGE: newBarrier = barrierList.add(new Bridge); break;
	case EditMode::GRID: {
		if (!hasCustomUserGrids && fabs(pos1.z - grids[0]->minPoint.z) < 0.01 * grids[0]->nodeWidth) {
			newGrid = grids[0];
			setname(newGrid->holder, "");
		}
		else {
			newGrid = grids.add(new Grid);
		}
		hasCustomUserGrids = 1.0;
		break;
	}
	}
	TreeNode* newNode = nullptr;
	if (activeBarrier) {
		activeBarrier->objectAs(Barrier)->isActive = 0;
		activeBarrier = nullptr;
	}
	if (activeGrid) {
		activeGrid = nullptr;
	}
	string className;
	if (newBarrier) {
		newBarrier->init(minNodeWidth, pos1, pos2);
		newBarrier->activePointIndex = 1;
		newBarrier->isActive = 1;
		newNode = newBarrier->holder;
		className = newBarrier->getClassFactory();
		className = className.substr(strlen("AStar::"));
		activeBarrier = newNode;
	} else if (newGrid) {
		newNode = newGrid->holder;
		className = newBarrier->getClassFactory();
		className = className.substr(strlen("AStar::"));
		activeGrid = newNode;
	}
	std::stringstream ss;
	int num = content(barriers);
	ss << className << num;
	while (objectexists(newNode->up->find(ss.str().c_str()))) {
		num++;
		ss.str("");
		ss << className << num;
	}

	setname(newNode, ss.str().c_str());
	setDirty();

	// Create undo record on the active view
	addCreateRecord(nodefromwindow(activedocumentview()), newBarrier, "Create Barrier");

	return newNode;

}

ASTAR_FUNCTION Variant AStarNavigator_dumpBlockageData(FLEXSIMINTERFACE)
{
	c->objectAs(AStarNavigator)->dumpBlockageData(param(1));
	return 0;
}


} // end AStar namespace

using namespace AStar;

ASTAR_FUNCTION Variant AStarNavigator_blockGridModelPos(FLEXSIMINTERFACE)
{
	o(AStarNavigator, c).blockGridModelPos(Vec3(param(1), param(2), param(3)));
	return 0;
}

ASTAR_FUNCTION Variant AStarNavigator_divideGridModelLine(FLEXSIMINTERFACE)
{
	o(AStarNavigator, c).divideGridModelLine(
		Vec3(param(1), param(2), param(3)),
		Vec3(param(4), param(5), param(6)),
		parqty() == 7 ? param(7).operator int() : false
	);
	return 0;
}

ASTAR_FUNCTION Variant AStarNavigator_addObjectBarrierToTable(FLEXSIMINTERFACE)
{
	o(AStarNavigator, c).addObjectBarrierToTable(param(1));
	return 0;
}

ASTAR_FUNCTION Variant AStarNavigator_setEditMode(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	int mode = (int)param(1);
	if (mode < 0)
		mode = 0;
	AStarNavigator::editMode = (EditMode)mode;

	return 0;
}

ASTAR_FUNCTION Variant AStarNavigator_addObject(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;
	AStarNavigator* a = navNode->objectAs(AStarNavigator);
	return a->addObject(Vec3(param(1), param(2), param(3)), Vec3(param(4), param(5), param(6)), (EditMode)(unsigned int) param(7));
}

ASTAR_FUNCTION Variant AStarNavigator_removeBarrier(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	AStarNavigator* a = navNode->objectAs(AStarNavigator);
	int index = (int)param(1);
	if (index >= a->barrierList.size())
		return 0;

	a->barrierList.remove((int)param(1));
	a->setDirty();

	return 1;
}

ASTAR_FUNCTION Variant AStarNavigator_swapBarriers(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	AStarNavigator* a = navNode->objectAs(AStarNavigator);
	int index1 = (int)param(1);
	int index2 = (int)param(2);

	int maxIndex = max(index1, index2);
	int minIndex = min(index1, index2);
	if (maxIndex > a->barrierList.size() || minIndex < 0)
		return 0;

	a->barrierList.swap(index1, index2);
	return 1;
}

ASTAR_FUNCTION Variant AStarNavigator_onClick(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	AStarNavigator* a = navNode->objectAs(AStarNavigator);
	if (objectexists(a->activeBarrier)) {
		Barrier* b = a->activeBarrier->objectAs(Barrier);
		b->onClick(param(1), (int)param(2), Vec3(param(3), param(4), param(5)));
		a->setDirty();
	}
	if (objectexists(a->activeGrid)) {
		Grid* g = a->activeGrid->objectAs(Grid);
		g->onClick(param(1), (int)param(2), Vec3(param(3), param(4), param(5)));
		a->setDirty();
	}
	return 1;
}

ASTAR_FUNCTION Variant AStarNavigator_onMouseMove(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	AStarNavigator* a = navNode->objectAs(AStarNavigator);
	if (objectexists(a->activeBarrier)) {
		Barrier* b = a->activeBarrier->objectAs(Barrier);
		b->onMouseMove(Vec3(param(1), param(2), param(3)), Vec3(param(4), param(5), 0));
		a->setDirty();
	}

	return 1;
}

ASTAR_FUNCTION Variant AStarNavigator_getActiveBarrierMode(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	AStarNavigator* a = navNode->objectAs(AStarNavigator);
	if (objectexists(a->activeBarrier)) {
		Barrier* b = a->activeBarrier->objectAs(Barrier);
		return b->mode;
	}

	return 1;
}

ASTAR_FUNCTION Variant AStarNavigator_setActiveBarrier(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	TreeNode* barrierNode = param(1);
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;
	if (!isclasstype(ownerobject(barrierNode), "AStar::AStarNavigator"))
		return 0;

	AStarNavigator* a = navNode->objectAs(AStarNavigator);
	if (objectexists(a->activeBarrier)) {
		Barrier* b = a->activeBarrier->objectAs(Barrier);
		b->activePointIndex = 0;
		b->isActive = 0;
	}
	Barrier* b = barrierNode->objectAs(Barrier);
	b->isActive = 1;
	a->activeBarrier = b->holder;

	return 1;
}

ASTAR_FUNCTION Variant AStarNavigator_rebuildMeshes(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	AStarNavigator* a = navNode->objectAs(AStarNavigator);
	a->setDirty();
	return 1;
}

ASTAR_FUNCTION Variant AStarNavigator_rebuildEdgeTable(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	AStarNavigator* a = navNode->objectAs(AStarNavigator);
	a->resetGrids();
	return 1;
}

ASTAR_FUNCTION Variant AStarNavigator_addMember(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	TreeNode* connectTo = param(1);
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	AStarNavigator* a = navNode->objectAs(AStarNavigator);
	a->dragConnection(connectTo, 'A', o(FlexSimObject, connectTo).getClassType());
	return 1;
}

ASTAR_FUNCTION Variant AStarNavigator_removeMember(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	TreeNode* disconnect = param(1);
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	AStarNavigator* a = navNode->objectAs(AStarNavigator);
	a->dragConnection(disconnect, 'Q', o(FlexSimObject, disconnect).getClassType());
	return 1;
}