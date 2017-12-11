#include "AStarNavigator.h"
#include "Divider.h"
#include "OneWayDivider.h"
#include "PreferredPath.h"
#include "macros.h"
#include "Bridge.h"
#include "Traveler.h"

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
#define TRAVEL_UP 0x1
#define TRAVEL_DOWN 0x2
#define TRAVEL_RIGHT 0x4
#define TRAVEL_LEFT 0x8
#define TRAVEL_FAR_UP 0x10
#define TRAVEL_FAR_DOWN 0x20
#define TRAVEL_FAR_RIGHT 0x40
#define TRAVEL_FAR_LEFT 0x80

unsigned int AStarNavigator::editMode = 0;
std::vector<Vec4f> AStarNavigator::heatMapColorProgression =
{
	Vec4f(0.110f, 0.280f, 0.467f, 1.0f),
	Vec4f(0.106f, 0.541f, 0.353f, 1.0f),
	Vec4f(0.984f, 0.690f, 0.129f, 1.0f),
	Vec4f(0.964f, 0.533f, 0.220f, 1.0f),
	Vec4f(0.933f, 0.243f, 0.196f, 1.0f)
};


AStarNavigator::AStarNavigator()
	: edgeTable(NULL)
	, xOffset(0)
	, yOffset(0)
	, edgeTableXSize(0)
	, edgeTableYSize(0)
	, isDirty(true)
{
	return;
}

AStarNavigator::~AStarNavigator()
{
	if (edgeTable) {
		delete [] edgeTable;
		edgeTable = 0;
		hasEdgeTable = 0;
	}
}

void AStarNavigator::bindVariables(void)
{
	Navigator::bindVariables();
	bindVariable(defaultPathWeight);
	bindVariable(drawMode);
	bindVariable(showAllocations);
	bindVariable(nodeWidth);
	bindVariable(surroundDepth);
	bindVariable(deepSearch);
	bindVariable(ignoreDestBarrier);
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

	bindVariable(showHeatMap);
	bindVariable(heatMapMode);
	bindVariable(maxHeatValue);
	bindVariable(transparentBaseColor);

	bindVariable(collisionUpdateIntervalFactor);

	bindStateVariable(collisionUpdateInterval);
	bindStateVariable(nextCollisionUpdateTime);


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

void AStarNavigator::bindTEEvents(TaskExecuter* te)
{
	te->bindRelayedClassEvents<Traveler>("AStar", 0, &AStarNavigator::resolveTraveler);
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

double AStarNavigator::onReset()
{
	heatMapBuffer.reset(nullptr);

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


	SimulationStartEvent::addObject(this);

	edgeTableExtraData.clear();
	extraDataNode->subnodes.clear();
	buildEdgeTable();
	setDirty();

	for (Barrier* barrier : barrierList)
		barrier->onReset(this);

	if (enableCollisionAvoidance && collisionUpdateIntervalFactor > 0 && travelers.size() > 0) {
		double avgSpeed = sumSpeed / travelers.size();
		double avgNodeMoveTime = nodeWidth / avgSpeed;
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

	if (isDirty) {
		if (!edgeTable && hasEdgeTable)
			buildEdgeTable();

		if (drawMode && ASTAR_DRAW_MODE_BARRIERS)
			buildBarrierMesh();

		if (drawMode && ASTAR_DRAW_MODE_BOUNDS && edgeTable)
			buildBoundsMesh();

		isDirty = false;
	}

	int pickingmode = getpickingmode(view);
	int drawMode = (int)this->drawMode;
	if(drawMode == 0 && (showHeatMap == 0 || heatMapMode == 0) && showAllocations == 0) return 0;

	fglDisable(GL_TEXTURE_2D);
	fglDisable(GL_LIGHTING);
	
	double loc[3];
	vectorproject(holder, 0, 0, 0, model(), loc);

	fglScale(1.0/b_spatialsx, 1.0/b_spatialsy, 1.0/b_spatialsz);
	fglTranslate(-loc[0], -loc[1], -loc[2]);

	double lengthMultiple = getmodelunit(LENGTH_MULTIPLE);
	if (!pickingmode) {
		if (drawMode & ASTAR_DRAW_MODE_GRID)
			drawGrid(0.01f / lengthMultiple);

		if (drawMode & ASTAR_DRAW_MODE_BOUNDS)
			boundsMesh.draw(GL_TRIANGLES);

		if (drawMode & ASTAR_DRAW_MODE_BARRIERS)
			barrierMesh.draw(GL_TRIANGLES);

		if (showHeatMap != 0 && heatMapMode != 0)
			drawHeatMap(0.015f / lengthMultiple, view);

		if (drawMode & ASTAR_DRAW_MODE_MEMBERS)
			drawMembers(0.02f / lengthMultiple);

		if (showAllocations)
			drawAllocations(0.02f / lengthMultiple);
	} else {

		if(drawMode & ASTAR_DRAW_MODE_BARRIERS) {
			for(int i = 0; i < barrierList.size(); i++) {
				Barrier* barrier = barrierList[i];

				double x1, y1, x2, y2;
				if (!barrier->getBoundingBox(x1, y1, x2, y2))
					continue;

				setpickingdrawfocus(view, holder, 0, barrier->holder);
				barrierMesh.draw(GL_TRIANGLES, barrier->meshOffset, barrier->nrVerts);
			}
		}

		if (drawMode & ASTAR_DRAW_MODE_BOUNDS) {
			setpickingdrawfocus(view, holder, PICK_TYPE_BOUNDS);
			boundsMesh.draw(GL_TRIANGLES);
		}
	}
	fglEnable(GL_TEXTURE_2D);
	fglEnable(GL_LIGHTING);
	return 0;
}

double AStarNavigator::onClick(TreeNode* view, int clickcode)
{
	int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, 0);
	TreeNode* secondary = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, 0));

	if (objectexists(secondary)) {
		Barrier* barrier = secondary->objectAs(Barrier);

		// is there a current barrier
		if (objectexists(activeBarrier)) {
			Barrier* b = activeBarrier->objectAs(Barrier);
			// is the clicked barrier different than the current barrier
			if (b != barrier) {
				// then reset the current barrier to be "not active"
				b->activePointIndex = b->pointList.size();
				b->isActive = 0;
			}
		}
		// set the active barrier to the clicked barrier
		activeBarrier = barrier->holder;
		barrier->isActive = 1;
		setDirty();
		return barrier->onClick(view, (int)clickcode, cursorinfo(view, 2, 1, 1), cursorinfo(view, 2, 2, 1));
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
	setDirty();
	return 0;
}

void AStarNavigator::addCreateRecord(treenode view, Barrier* barrier)
{
	int undoId = beginaggregatedundo(view, "Create Barrier");
	createundorecord(view, holder, UNDO_UPDATE_LINKS_ON_UNDO, 0, 0, 0);
	createundorecord(view, barrier->holder, UNDO_CREATE_OBJECT, 0, 0, 0);
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
		for (int i = 0; i < barrierList.size(); i++) {
			Barrier* barrier = barrierList[i];

			for (int i = 0; i < barrier->pointList.size(); i++) {
				Point* point = barrier->pointList[i];
				point->x += dx;
				point->y += dy;
			}
		}
		//Don't move objects associated with AStar, just the barriers
		/*
		for (int i = 0; i < objectBarrierList.size(); i++) {
			TreeNode* obj = objectBarrierList[i]->holder;
			inc(spatialx(obj), dx);
			inc(spatialy(obj), dy);
		}
		
		TreeNode* travelers = node_v_travelmembers;
		for (int i = 1; i <= content(travelers); i++) {
			TreeNode* traveler = ownerobject(tonode(get(rank(travelers, i))));
			inc(spatialx(traveler), dx);
			inc(spatialy(traveler), dy);
		}

		travelers = node_v_activetravelmembers;
		for (int i = 1; i <= content(travelers); i++) {
			TreeNode* traveler = ownerobject(tonode(get(rank(travelers, i))));
			inc(spatialx(traveler), dx);
			inc(spatialy(traveler), dy);
		}
		*/
		savedXOffset += dx / nodeWidth;
		savedYOffset += dy / nodeWidth;
		setDirty();
		return 1;
	}

	if (objectexists(secondary)) {
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
		int picktype = (int)getpickingdrawfocus(view, PICK_TYPE,0);
		TreeNode* secondary = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT,0));
		
		if (objectexists(secondary)) {
			destroyobject(secondary);
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
	Vec3 size = destination->objectAs(ObjectDataType)->size;
	vectorproject(destination, 0.5 * size.x, -0.5 * size.y, 0, model(), loc);

	Traveler* t = getTraveler(traveler->objectAs(TaskExecuter));
	t->destThreshold = DestinationThreshold(destination, nodeWidth);
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

	TravelPath path = calculateRoute(traveler, traveler->destLoc, endSpeed, false);
	traveler->navigatePath(std::move(path), false);
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

AStarSearchEntry* AStarNavigator::checkExpandOpenSet(AStarNode* node, AStarSearchEntry* entryIn, Direction direction, 
	int travelVal, double dist, double bonusMod, AStarNodeExtraData* extraData)
{
	if (node->canGo(direction)) {
		int theCol = entryIn->cell.col + AStarNode::colInc[direction];
		int theRow = entryIn->cell.row + AStarNode::rowInc[direction];
		double distance = dist;
		if (extraData && extraData->getBonus(direction) != 0) {
			distance *= 1.0 - (bonusMod * (double)(int)extraData->getBonus(direction)) / 127;
		}
		return expandOpenSet(theRow, theCol, distance, travelVal);
	}
	return nullptr;
}

AStarSearchEntry* AStarNavigator::checkExpandOpenSetDiagonal(AStarNode* node, AStarSearchEntry* entryIn,
	Direction dir1, Direction dir2, int travelVal, double dist, AStarNodeExtraData* extraData)
{
	if (!node->canGo(dir1) || !node->canGo(dir2))
		return nullptr;
	AStarCell cell;
	AStarSearchEntry* e1 = nullptr;
	cell.row = entryIn->cell.row + AStarNode::rowInc[dir1];
	cell.col = entryIn->cell.col;
	if (getNode(cell)->canGo(dir2)) {
		auto iter = entryHash.find(cell.colRow);
		if (iter != entryHash.end()) {
			AStarSearchEntry* vert = &totalSet[iter->second];
			AStarNode* vertNode = &DeRefEdgeTable(vert->cell.row, vert->cell.col);
			e1 = checkExpandOpenSet(vertNode, vert, dir2, travelVal, dist, ROOT2_DIV2, extraData);
		}
	}
	if (e1 == nullptr) {
		cell.row = entryIn->cell.row;
		cell.col = entryIn->cell.col + AStarNode::colInc[dir2];
		if (getNode(cell)->canGo(dir1)) {
			auto iter = entryHash.find(cell.colRow);
			if (iter != entryHash.end()) {
				AStarSearchEntry* hrz = &totalSet[iter->second];
				AStarNode* hrzNode = &DeRefEdgeTable(hrz->cell.row, hrz->cell.col);
				e1 = checkExpandOpenSet(hrzNode, hrz, dir1, travelVal, dist, ROOT2_DIV2, extraData);
			}
		}
	}

	if (e1 && deepSearch) {
		AStarNode* n1 = &DeRefEdgeTable(e1->cell.row, e1->cell.col);
		AStarSearchEntry e1StackCopy = *e1;

		checkExpandOpenSet(n1, (&e1StackCopy), dir1, 
			(travelVal | ((travelVal & TRAVEL_UP) ? TRAVEL_FAR_UP : TRAVEL_FAR_DOWN)), 
			ROOT5_DIVROOT2 * dist, ROOT5_DIV5, extraData);
		
		checkExpandOpenSet(n1, (&e1StackCopy), dir2, 
			(travelVal | ((travelVal & TRAVEL_RIGHT) ? TRAVEL_FAR_RIGHT : TRAVEL_FAR_LEFT)), 
			ROOT5_DIVROOT2 * dist, ROOT5_DIV5, extraData);
	}
	return e1;
}


TravelPath AStarNavigator::calculateRoute(Traveler* traveler, double* tempDestLoc, double endSpeed, bool doFullSearch)
{
	TreeNode* travelerNode = traveler->te->holder;
	double centerx = 0.5 * xsize(travelerNode);
	double centery = 0.5 * ysize(travelerNode);

	double outputVector[3];
	vectorproject(travelerNode, centerx, - centery, 0, model(), outputVector);
	xStart = outputVector[0];
	yStart = outputVector[1];
	
	double x = tempDestLoc[0];
	double y = tempDestLoc[1];
	destLoc.x = x;
	destLoc.y = y;

	TaskExecuter* te = traveler->te;
	
	// get the x/y location of the bottom left corner of my grid
	gridOrigin.x = (xOffset + 0.5) * nodeWidth;
	gridOrigin.y = (yOffset + 0.5) * nodeWidth;

	AStarCell startCell = getCellFromLoc(Vec2(xStart, yStart));
	AStarCell destCell = getCellFromLoc(destLoc);

	// This will either be generated by the search, or looked up by the cache
	TravelPath travelPath;

	// Figure out if this path is in the cache
	bool shouldUseCache = false;
	CachedPathID p;
	if (cachePaths && !doFullSearch) {
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

	// set xStart/yStart to the center of the start grid point
	xStart = gridOrigin.x + startCell.col * nodeWidth;
	yStart = gridOrigin.y + startCell.row * nodeWidth;

	// set x/y to the cetner of the dest grid point
	x = gridOrigin.x + destCell.col * nodeWidth;
	y = gridOrigin.y + destCell.row * nodeWidth;

	// total set includes all resolved and open nodes in the graph
	totalSet.clear();
	// opensetheap is a sorted list of the nodes in the open set
	// the value is the solution of f(x,y) for that node in the set
	while(openSetHeap.size() > 0)
		openSetHeap.pop();

	entryHash.clear();
	// add the first node to the "open set"
	totalSet.push_back(AStarSearchEntry());
	AStarSearchEntry* start = &totalSet.back();
	start->cell.col = startCell.col;
	start->cell.row = startCell.row;

	// Set the desination outside a barrier if necessary
	if (ignoreDestBarrier) {
		AStarCell tempDestCell = destCell;

		checkGetOutOfBarrier(tempDestCell, te, startCell.row, startCell.col, &traveler->destThreshold, false);
	}

	// Get out of a barrier if necessary
	checkGetOutOfBarrier(start->cell, te, destCell.row, destCell.col, nullptr, true);

	start->g = 0;
	start->h = (1.0 - maxPathWeight) * sqrt(sqr(x-xStart)+sqr(y-yStart));
	start->f = start->g + start->h;
	start->previous = ~0;
	start->closed = 0;

	start->travelFromPrevious = 0;

	double zRot = fmod(zrot(travelerNode), 360);
	if (zRot < 0) zRot += 360;

	if (zRot < 80 || zRot > 280)
		start->travelFromPrevious |= TRAVEL_RIGHT;
	else if (zRot < 260 && zRot > 100)
		start->travelFromPrevious |= TRAVEL_LEFT;
	if (zRot < 170 && zRot > 10)
		start->travelFromPrevious |= TRAVEL_UP;
	else if (zRot < 350 && zRot > 190)
		start->travelFromPrevious |= TRAVEL_DOWN;

	entryHash[start->cell.colRow] = 0;

	// the open set stores:
	// 1. the index into totalset that references the AStarSearchEntry that i'm going to resolve
	// 2. the solution f(x, y) of that AStarSearchEntry
	openSetHeap.push(HeapEntry(start->f, 0));

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
		shortest.closed = 1;
		n = &(DeRefEdgeTable(shortest.cell.row, shortest.cell.col));
		n->open = false;

		// if I am at the destination, then break out of the solve loop
		if ((shortest.cell.col == destCell.col && shortest.cell.row == destCell.row) || traveler->destThreshold.isWithinThreshold(shortest.cell, gridOrigin, destLoc, nodeWidth)) {
			final = &shortest;
			break;
		}

		// travelFromPrevious is used to figure out the direction he's currently
		// going because if there are multiple path solutions with the same 
		// total distance, then I want to give priority to those solutions that
		// keep him traveling in the same direction, i.e. make him turn the fewest
		// times
		travelFromPrevious = shortest.travelFromPrevious;

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

		AStarNodeExtraData* extraData = nullptr;
		if (!n->noExtraData) {
			auto found = edgeTableExtraData.find(shortest.cell.colRow);
			if (found != edgeTableExtraData.end())
				extraData = found->second;
		}
		checkExpandOpenSet(n, (&shortest), Up, TRAVEL_UP, 1.0, 1.0, extraData);
		checkExpandOpenSet(n, (&shortest), Right, TRAVEL_RIGHT, 1.0, 1.0, extraData);
		checkExpandOpenSet(n, (&shortest), Down, TRAVEL_DOWN, 1.0, 1.0, extraData);
		checkExpandOpenSet(n, (&shortest), Left, TRAVEL_LEFT, 1.0, 1.0, extraData);

		checkExpandOpenSetDiagonal(n, (&shortest), Up, Right, TRAVEL_UP | TRAVEL_RIGHT, ROOT2, extraData);
		checkExpandOpenSetDiagonal(n, (&shortest), Up, Left, TRAVEL_UP | TRAVEL_LEFT, ROOT2, extraData);
		checkExpandOpenSetDiagonal(n, (&shortest), Down, Right, TRAVEL_DOWN | TRAVEL_RIGHT, ROOT2, extraData);
		checkExpandOpenSetDiagonal(n, (&shortest), Down, Left, TRAVEL_DOWN | TRAVEL_LEFT, ROOT2, extraData);

		if (n->hasExtraData) {
			auto e = edgeTableExtraData.find(shortest.cell.colRow);
			AStarNodeExtraData* extra = e->second;
			if (e != edgeTableExtraData.end() && extra->bridges.size() > 0) {
				for (int i = 0; i < extra->bridges.size(); i++) {
					auto& entry = extra->bridges[i];
					double addedDist = entry.bridge->travelDistance + nodeWidth;
					Point* endPoint = entry.isAtBridgeStart ? entry.bridge->pointList.back() : entry.bridge->pointList.front();
					AStarCell endCell = getCellFromLoc(Vec2(endPoint->x, endPoint->y));
					AStarNode* node = getNode(endCell);
					expandOpenSet(endCell.row, endCell.col, addedDist / nodeWidth, 0, i);
				}
			}
		}
	} // End of the while loop

	// remake the start pointer (totalSet may reallocate due to push_back)
	start = totalSet.data();

	if (!final)  {
		final = &(totalSet[closestIndex]);
	}

	// Tack on the barrierStart if necessary
	if (barrierStart.cell.colRow != ~0) {
		// Add barrierStart to the totalSet
		totalSet.push_back(barrierStart);

		// set start's previous to be the barrierStart
		start->previous = totalSet.size() - 1;
	}

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

	int totalsetsize = totalSet.size();
	for (int i = 0; i < totalsetsize; i++) {
		AStarSearchEntry & e = totalSet[i];
		AStarNode* n = &DeRefEdgeTable(e.cell.row, e.cell.col);
		n->isInTotalSet = false;
		n->open = true;
	}
	totalSet.clear();

	// right now the travelPath is backwards, to reverse it
	for (int i = 0; i < travelPath.size() / 2; i++) {
		auto temp = travelPath[i];
		travelPath[i] = travelPath[travelPath.size() - i - 1];
		travelPath[travelPath.size() - i - 1] = temp;
	}

	if (traveler->destThreshold.xAxisThreshold > 0 || traveler->destThreshold.yAxisThreshold > 0) {
		double threshold = sqrt(traveler->destThreshold.xAxisThreshold * traveler->destThreshold.xAxisThreshold 
			+ traveler->destThreshold.yAxisThreshold * traveler->destThreshold.yAxisThreshold);
		while (travelPath.size() > 1) {
			Vec3 pos = getLocFromCell(travelPath[travelPath.size() - 2].cell);
			Vec3 diff = pos - Vec3(traveler->destLoc.x, traveler->destLoc.y, 0);
			if (diff.magnitude > threshold)
				break;
			travelPath.pop_back();
		}
	}

	if (cachePaths && !doFullSearch) {
		pathCache[p] = travelPath;
		pathCount++;
	}

	return travelPath;

}

double AStarNavigator::queryDistance(TaskExecuter* taskexecuter, FlexSimObject* destination)
{
	updatelocations(taskexecuter->holder);

	Traveler* traveler = getTraveler(taskexecuter);
	double destLoc[3];
	vectorproject(destination->holder, 0.5 * xsize(destination->holder), -0.5 * ysize(destination->holder), 0, model(), destLoc);

	DestinationThreshold saved = traveler->destThreshold;
	traveler->destThreshold = DestinationThreshold(destination->holder, 0.9 * nodeWidth);
	TravelPath path = calculateRoute(traveler, destLoc, 0, true);
	traveler->destThreshold = saved;
	traveler->navigatePath(std::move(path), true);

	return getkinematics(traveler->distQueryKinematics, KINEMATIC_TOTALDIST);
}

void AStarNavigator::checkGetOutOfBarrier(AStarCell& cell, TaskExecuter* traveler, int rowDest, int colDest, DestinationThreshold* threshold, bool setStartEntry)
{
	AStarNode* node = &DeRefEdgeTable(cell.row, cell.col);
	int dy = rowDest - cell.row;
	int dx = colDest - cell.col;
	AStarCell originalCell(cell);

	static const int up = 0;
	static const int left = 1;
	static const int down = 2;
	static const int right = 3;

	int startDir = up;
	if (dx > 0 && dx * dx > dy * dy)
		startDir = left;
	else if (dx < 0 && dx * dx > dy * dy) 
		startDir = right;
	else if (dy < 0 && dy * dy > dx * dx)
		startDir = down;

	int currRow = cell.row;
	int currCol = cell.col;
	int currDir = (startDir + 3) % 4; // start one direction back 
	int distance = 0;
	int counter = 4; // counter is used to find the distance

	while (!(node->canGoUp || node->canGoDown || node->canGoRight || node->canGoLeft)) {
		currDir = (currDir + 1) % 4;
		distance = (counter++) / 4;
		switch (currDir) {
		case 0: currRow = cell.row + distance; currCol = cell.col; break;
		case 1: currCol = cell.col + distance; currRow = cell.row; break;
		case 2: currRow = cell.row - distance; currCol = cell.col; break;
		case 3: currCol = cell.col - distance; currRow = cell.row; break;
		}

		if(currRow >= 0 && currCol >= 0)
			node = &DeRefEdgeTable(currRow, currCol);
	}

	if (setStartEntry) {
		barrierStart.cell.colRow = ~0;
		barrierStart.previous = ~0;
		if (cell.row != currRow || cell.col != currCol) {
			barrierStart.cell.row = cell.row;
			barrierStart.cell.col = cell.col;
		} 
	}
	cell.row = currRow;
	cell.col = currCol;
	if (threshold && cell != originalCell) {
		double newRadius = nodeWidth * (0.9 + sqrt(sqr(cell.row - originalCell.row) + sqr(cell.col - originalCell.col)));
		if (newRadius > threshold->anyThresholdRadius)
			threshold->anyThresholdRadius = newRadius;
	}
}

AStarSearchEntry* AStarNavigator::expandOpenSet(int r, int c, float multiplier, int travelVal, char bridgeIndex)
{
	AStarSearchEntry* entry = NULL;
	int closed = 0;
	int totalSetIndex;
	AStarNode* n = &DeRefEdgeTable(r, c);
	// is he already in the total set
	if (n->isInTotalSet) {
		// if he's in the total set and he's closed, then abort
		if (!n->open) {
			return NULL;
		}

		AStarSearchEntry hashEntry;
		hashEntry.cell.row = r;
		hashEntry.cell.col = c;
		totalSetIndex = entryHash[hashEntry.cell.colRow];
		entry = &(totalSet[totalSetIndex]);
	}
	float newG = shortest.g + multiplier * nodeWidth;
	/*  Check if the guy is changing directions. If so, I want to increase the distance so it will be a penalty to make turns*/ \
	if(travelVal != travelFromPrevious) {
		// add a small penalty if he's turning
		newG += directionChangePenalty * nodeWidth;
		// if it's a right angle turn or more, then add more penalty
		if((travelFromPrevious & travelVal) == 0)
			newG += directionChangePenalty * nodeWidth;
	}
	
	if (!entry || newG < entry->g-0.01*nodeWidth) {
		// if entry is NULL, that means he's not in the total set yet,
		// so I need to add him.
		if (!entry) {
			totalSetIndex = totalSet.size();
			totalSet.push_back(AStarSearchEntry());
			entry = &totalSet.back();
			entry->cell.col = c;
			entry->cell.row = r;
			entryHash[entry->cell.colRow] = totalSetIndex;
			// calculate the distance heuristic h
			double diffx = destLoc.x - (gridOrigin.x + entry->cell.col * nodeWidth);
			double diffy = destLoc.y - (gridOrigin.y + entry->cell.row * nodeWidth);
			entry->h = (1.0 - maxPathWeight) * sqrt(diffx*diffx + diffy*diffy);
			entry->closed = 0;
			n->isInTotalSet = true;
		}
		entry->g = newG;
		entry->f = entry->g + entry->h;
		openSetHeap.push(HeapEntry(entry->f, totalSetIndex));
		entry->previous = shortestIndex;
		entry->travelFromPrevious = travelVal;
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

void AStarNavigator::buildEdgeTable()
{
	heatMapBuffer.reset(nullptr);
	// Determine the grid bounds
	Vec2 min = Vec2(FLT_MAX,FLT_MAX);
	Vec2 max = Vec2(-FLT_MAX,-FLT_MAX);

	pathCache.clear();
	pathCount = 0;
	requestCount = 0;
	cacheUseCount = 0;

	directionChangePenalty = 0.05;
	if (deepSearch)
		directionChangePenalty = 0.025;


	if (content(barriers) == 0 && objectBarrierList.size() == 0) {
		if (edgeTable)
			delete [] edgeTable;
		edgeTable = 0;
		hasEdgeTable = 0;
		boundsMesh.init(0, 0, 0);
		return;
	}

	// go through the barriers to determine bounds
	for (int i = 0; i < barrierList.size(); i++) {
		Barrier* barrier = barrierList[i];
		double x1, y1, x2, y2;
		barrier->getBoundingBox(x1, y1, x2, y2);

		if(x1 < min.x) min.x = x1;
		if(x1 > max.x) max.x = x1;
		if(y1 < min.y) min.y = y1;
		if(y1 > max.y) max.y = y1;
		if(x2 < min.x) min.x = x2;
		if(x2 > max.x) max.x = x2;
		if(y2 < min.y) min.y = y2;
		if(y2 > max.y) max.y = y2;
	}

	// Shrink the bounding box for objects
	double halfNodeWidth = 0.5 * nodeWidth;


	auto checkBounds = [halfNodeWidth](TreeNode* theObj, Vec2& min, Vec2& max) {

		auto checkBound = [halfNodeWidth, theObj, &min, &max](double x, double y, double z) {
			Vec3 outVec;
			vectorproject(theObj, x, y, z, model(), outVec);
			if (outVec.x + halfNodeWidth < min.x)
				min.x = outVec.x + halfNodeWidth;
			if (outVec.x - halfNodeWidth > max.x)
				max.x = outVec.x - halfNodeWidth;
			if (outVec.y + halfNodeWidth < min.y)
				min.y = outVec.y + halfNodeWidth;
			if (outVec.y - halfNodeWidth > max.y)
				max.y = outVec.y - halfNodeWidth;
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

	// go through objects to determine bounds
	for (int i = 0; i < objectBarrierList.size(); i++) {
		// spatialx/y are the top left corner
		// Treat objects as a solid barrier
		TreeNode* theObj = objectBarrierList[i]->holder;
		checkBounds(theObj, min, max);

	}

	xOffset = (int)(floor(min.x / nodeWidth) - surroundDepth);
	yOffset = (int)(floor(min.y / nodeWidth) - surroundDepth);
	savedXOffset = (float)xOffset;
	savedYOffset = (float)yOffset;

	edgeTableXSize = (int)(ceil((max.x - min.x) / nodeWidth) + surroundDepth * 2 + 1);
	edgeTableYSize = (int)(ceil((max.y - min.y) / nodeWidth) + surroundDepth * 2 + 1);

	double col0xloc = (xOffset + 0.5) * nodeWidth;
	double row0yloc = (yOffset + 0.5) * nodeWidth;
	gridOrigin.x = col0xloc;
	gridOrigin.y = row0yloc;

	// Create a new fully connected table
	unsigned int tableSize = edgeTableYSize * edgeTableXSize;
	if (edgeTable)
		delete [] edgeTable;
	edgeTable = new AStarNode[tableSize];
	memset(edgeTable, 0xFFFFFFFF, tableSize * sizeof(AStarNode));

	for (int i = 0; i < edgeTableYSize; i++) {
		getNode(i, 0)->canGoLeft = 0;
		getNode(i, edgeTableXSize - 1)->canGoRight = 0;
	}
	for (int i = 0; i < edgeTableXSize; i++) {
		getNode(0, i)->canGoDown = 0;
		getNode(edgeTableYSize - 1, i)->canGoUp = 0;
	}

	// The maxPathWeight ensures that the estimated distance
	// to the goal is not overestimated.
	maxPathWeight = 0.0;
	for(int i = 0; i < barrierList.size(); i++) {
		Barrier* barrier = barrierList[i];
		barrier->addBarriersToTable(this);
	}

	for (int i = 0; i < objectBarrierList.size(); i++) {
		TreeNode* theObj = objectBarrierList[i]->holder;
		if (function_s(theObj, "customizeAStarGrid", holder, nodeWidth))
			continue;
		
		Vec2 objMin(FLT_MAX, FLT_MAX), objMax(-FLT_MAX, -FLT_MAX);
		int rotation = ((int)round(zrot(theObj) / 90) * 90);
		// if the object is rotated at 0, 90, 180 or 270, then do simple stuff
		if (fabs(zrot(theObj) - rotation) < 5 && fabs(xrot(theObj)) < 5 && fabs(yrot(theObj)) < 5 && up(theObj) == model()) {

			double halfXSize = 0.5 * xsize(theObj);
			double halfYSize = 0.5 * ysize(theObj);

			Vec3 modelCenter;
			vectorproject(theObj, halfXSize, -halfYSize, 0, model(), modelCenter);
			double objSX = maxof(xsize(theObj), nodeWidth);
			double objSY = maxof(ysize(theObj), nodeWidth);


			if (rotation != 0 && rotation % 180 != 0 && rotation % 90 == 0) {
				objMin.x = modelCenter.x - halfYSize;
				objMax.x = objMin.x + objSY;
				objMax.y = modelCenter.y + halfXSize;
				objMin.y = objMax.y - objSX;
			} else {
				objMin.x = modelCenter.x - halfXSize;
				objMax.x = objMin.x + objSX;
				objMax.y = modelCenter.y + halfYSize;
				objMin.y = objMax.y - objSY;
			}
			// Shrink the bounding box for objects
			double halfNodeWidth = 0.5 * nodeWidth;
			objMin.x += halfNodeWidth;
			objMax.x -= halfNodeWidth;
			objMin.y += halfNodeWidth;
			objMax.y -= halfNodeWidth;

			int colleft = (int)round((objMin.x - col0xloc) / nodeWidth);
			int rowbottom = (int)round((objMin.y - row0yloc) / nodeWidth);
			int colright = (int)round((objMax.x - col0xloc) / nodeWidth);
			int rowtop = (int)round((objMax.y - row0yloc) / nodeWidth);
			for(int row = rowbottom; row <= rowtop; row++)
			{
				AStarNode * left = &(DeRefEdgeTable(row, colleft-1));
				left->canGoRight = 0;
				AStarNode * right = &(DeRefEdgeTable(row, colright+1));
				right->canGoLeft = 0;
			}

			for(int col = colleft; col <= colright; col++)
			{
				AStarNode * top = &(DeRefEdgeTable(rowtop+1, col));
				top->canGoDown = 0;
				AStarNode * bottom = &(DeRefEdgeTable(rowbottom-1, col));
				bottom->canGoUp = 0;
			}

			for (int row = rowbottom; row <= rowtop; row++) {
				for (int col = colleft; col <= colright; col++) {
					AStarNode* theNode = &(DeRefEdgeTable(row, col));
					theNode->canGoUp = 0;
					theNode->canGoDown = 0;
					theNode->canGoLeft = 0;
					theNode->canGoRight = 0;
				}
			}
		} else {
			// in this case, the object is rotated weird, so I need to manually go through and apply each 

			checkBounds(theObj, objMin, objMax);

			int minCol = (int)((objMin.x - col0xloc) / nodeWidth);
			int maxCol = (int)((objMax.x - col0xloc) / nodeWidth) + 1;
			int minRow = (int)((objMin.y - row0yloc) / nodeWidth);
			int maxRow = (int)((objMax.y - row0yloc) / nodeWidth) + 1;

			Vec2 minThreshold(0, -ysize(theObj));
			Vec2 maxThreshold(xsize(theObj), 0);
			double yPadding = nodeWidth - ysize(theObj);
			if (yPadding > 0) {
				minThreshold.y -= 0.5 * yPadding;
				maxThreshold.y += 0.5 * yPadding;
			}
			double xPadding = nodeWidth - xsize(theObj);
			if (xPadding > 0) {
				minThreshold.x -= 0.5 * xPadding;
				maxThreshold.x += 0.5 * xPadding;
			}

			for (int row = minRow; row <= maxRow; row++) {
				for (int col = minCol; col <= maxCol; col++) {
					Vec3 modelPos(col0xloc + col * nodeWidth, row0yloc + row * nodeWidth, 0);
					Vec3 objPos;
					vectorproject(model(), modelPos.x, modelPos.y, modelPos.z, theObj, objPos);
					if (objPos.x > minThreshold.x && objPos.x < maxThreshold.x && objPos.y > minThreshold.y && objPos.y < maxThreshold.y) {
						AStarNode& theNode = DeRefEdgeTable(row, col);
						theNode.canGoUp = false;
						theNode.canGoDown = false;
						theNode.canGoLeft = false;
						theNode.canGoRight = false;

						if (col > 0)
							DeRefEdgeTable(row, col - 1).canGoRight = false;
						if (col < edgeTableXSize - 1)
							DeRefEdgeTable(row, col + 1).canGoLeft = false;
						if (row > 0)
							DeRefEdgeTable(row - 1, col).canGoUp = false;
						if (row < edgeTableYSize)
							DeRefEdgeTable(row + 1, col).canGoDown = false;
					}
				}
			}
		}
	}

	for (int i = 0; i < barrierList.size(); i++) {
		Barrier* barrier = barrierList[i];
		barrier->addPassagesToTable(this);
		PreferredPath* path = barrier->toPreferredPath();
		if (path)
			maxPathWeight = max(path->pathWeight, maxPathWeight);
	}

	hasEdgeTable = 1;
}
void AStarNavigator::buildBoundsMesh()
{
	boundsMesh.init(0, MESH_POSITION, MESH_FORCE_CLEANUP);
	float up[3] = {0.0f, 0.0f, 1.0f};
	TreeNode* color = node_b_color;
	float boundsColor[4] = {
		(float)get(rank(color, 1)), 
		(float)get(rank(color, 2)), 
		(float)get(rank(color, 3)), 
		0.75f
	};
	float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};

	boundsMesh.setMeshAttrib(MESH_NORMAL, up);
	boundsMesh.setMeshAttrib(MESH_DIFFUSE4, boundsColor);

	float width = edgeTableXSize * nodeWidth;
	float height = edgeTableYSize * nodeWidth;
	float borderWidth = nodeWidth;

	float midBW = 0.4 * borderWidth;
	float z = 0.1f / getmodelunit(LENGTH_MULTIPLE);
	float bottomLeft[3] = {savedXOffset * nodeWidth, savedYOffset * nodeWidth, z};
	float topRight[3] = {bottomLeft[0] + width, bottomLeft[1] + height, z};
	float topLeft[3] = {bottomLeft[0], topRight[1], z};
	float bottomRight[3] = {topRight[0], bottomLeft[1], z};

	float oBottomLeft[3] = {bottomLeft[0] - borderWidth, bottomLeft[1] - borderWidth, z};
	float oTopRight[3] = {topRight[0] + borderWidth, topRight[1] + borderWidth, z};
	float oTopLeft[3] = {topLeft[0] - borderWidth, topLeft[1] + borderWidth, z};
	float oBottomRight[3] = {bottomRight[0] + borderWidth, bottomRight[1] - borderWidth, z};

	float mBottomLeft[3] = {bottomLeft[0] - midBW, bottomLeft[1] - midBW, z};
	float mTopRight[3] = {topRight[0] + midBW, topRight[1] + midBW, z};
	float mTopLeft[3] = {topLeft[0] - midBW, topLeft[1] + midBW, z};
	float mBottomRight[3] = {bottomRight[0] + midBW, bottomRight[1] - midBW, z};

#define ADD_VERTEX(point)\
	{\
		int newVertex = boundsMesh.addVertex();\
		boundsMesh.setVertexAttrib(newVertex, MESH_POSITION, point);\
	}\

#define ADD_PLAIN_QUAD(p1, p2, p3, p4)\
	ADD_VERTEX(p1);\
	ADD_VERTEX(p2);\
	ADD_VERTEX(p3);\
	ADD_VERTEX(p1);\
	ADD_VERTEX(p3);\
	ADD_VERTEX(p4);

	// left border (GL_QUADS)
	ADD_PLAIN_QUAD(bottomLeft, topLeft, oTopLeft, oBottomLeft);

	// top border
	ADD_PLAIN_QUAD(topLeft, topRight, oTopRight, oTopLeft);

	// right border
	ADD_PLAIN_QUAD(topRight, bottomRight, oBottomRight, oTopRight);

	// bottom border
	ADD_PLAIN_QUAD(bottomRight, bottomLeft, oBottomLeft, oBottomRight);
}

void AStarNavigator::buildBarrierMesh()
{
	barrierMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, 0);
	float up[3] = {0.0f, 0.0f, 1.0f};
	float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	barrierMesh.setMeshAttrib(MESH_NORMAL, up);
	for (int i = 0; i < barrierList.size(); i++) {
		barrierList[i]->nodeWidth = nodeWidth;
		barrierList[i]->addVertices(&barrierMesh, 0.1f / getmodelunit(LENGTH_MULTIPLE));
	}
}

void AStarNavigator::drawHeatMap(float z, TreeNode* view)
{
	if (heatMapMode == 0 || statisticaltime() <= 0)
		return;
	if (maxHeatValue <= 0)
		return;

	int pickMode = getpickingmode(view);
	if (pickMode)
		return;

	int width = (edgeTableXSize + 2);
	int height = (edgeTableYSize + 2);
	int numPixels = width * height;
	int bufferSize = 4 * numPixels;

	if (!heatMapBuffer) {
		heatMapBuffer = std::unique_ptr<unsigned int[]>(new unsigned int[numPixels]);
		Vec4f baseColor = heatMapColorProgression[0];
		if (transparentBaseColor)
			baseColor.a = 0;
		int baseColorInt = (((int)(baseColor.a * 255)) << 24)
			| (((int)(baseColor.b * 255)) << 16)
			| (((int)(baseColor.g * 255)) << 8)
			| (((int)(baseColor.r * 255)));

		unsigned int* buffer = heatMapBuffer.get();
		memset(buffer, 0, width * 4);
		memset(buffer + (height - 1) * width * 4, 0, width * 4);
		for (int i = 1; i <= edgeTableYSize; i++) {
			buffer[i * width] = 0;
			buffer[(i + 1) * width - 1] = 0;
			for (int j = 1; j <= edgeTableXSize; j++) {
				buffer[i * width + j] = baseColorInt;
			}
		}
	}

	unsigned int* buffer = heatMapBuffer.get();
	//memset(buffer, 0, bufferSize);
	for (auto& node : edgeTableExtraData) {
		AStarNodeExtraData* data = node.second;
		if (data->totalTraversals <= 0)
			continue;
		double weight;
		switch ((int)heatMapMode) {
			case HEAT_MAP_TRAVERSALS_PER_TIME: default:
				weight = (data->totalTraversals / statisticaltime());
				break;
			case HEAT_MAP_BLOCKAGE_TIME_PER_TRAVERSAL: 
				weight = (data->totalBlockedTime / max(1, data->totalTraversals));
				break;
			case HEAT_MAP_BLOCKAGE_TIME_PERCENT:
				weight = 100.0 * data->totalBlockedTime / statisticaltime();
				break;
		}
		weight /= maxHeatValue;
		weight = max(0, weight);
		weight = min(0.9999, weight);

		double progressionFactor = (double)(heatMapColorProgression.size() - 1) * weight;
		Vec4f lowColor = heatMapColorProgression[(int)floor(progressionFactor)];
		Vec4f highColor = heatMapColorProgression[(int)ceil(progressionFactor)];
		Vec4f lerpColor = lowColor + ((highColor - lowColor) * frac(progressionFactor));

		buffer[(data->cell.row + 1) * width + data->cell.col + 1] =
			(((int)(lerpColor.a * 255)) << 24)
			| (((int)(lerpColor.b * 255)) << 16)
			| (((int)(lerpColor.g * 255)) << 8)
			| (((int)(lerpColor.r * 255)));
	}


	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glGenerateTextureMipMap(GL_TEXTURE_2D);
	
	Mesh trafficMesh;
	trafficMesh.init(6, MESH_POSITION | MESH_TEX_COORD2, MESH_DYNAMIC_DRAW);
	Vec3f verts[] = {
		Vec3f(gridOrigin.x - 1.5 * nodeWidth, gridOrigin.y - 1.5 * nodeWidth, z),
		Vec3f(gridOrigin.x - 1.5 * nodeWidth, gridOrigin.y + (edgeTableYSize + 0.5) * nodeWidth, z),
		Vec3f(gridOrigin.x + (edgeTableXSize + 0.5) * nodeWidth, gridOrigin.y - 1.5 * nodeWidth, z),
		Vec3f(gridOrigin.x - 1.5 * nodeWidth, gridOrigin.y + (edgeTableYSize + 0.5) * nodeWidth, z),
		Vec3f(gridOrigin.x + (edgeTableXSize + 0.5) * nodeWidth, gridOrigin.y + (edgeTableYSize + 0.5) * nodeWidth, z),
		Vec3f(gridOrigin.x + (edgeTableXSize + 0.5) * nodeWidth, gridOrigin.y - 1.5 * nodeWidth, z),
	};

	Vec2f texCoords[] = {
		Vec2f(0.0, 0.0),
		Vec2f(0.0, 1.0),
		Vec2f(1.0, 0.0),
		Vec2f(0.0, 1.0),
		Vec2f(1.0, 1.0),
		Vec2f(1.0, 0.0)
	};

	fglColor(1.0, 1.0, 1.0, 1.0);
	fglEnable(GL_TEXTURE_2D);
	fglDisable(GL_LIGHTING);

	trafficMesh.defineVertexAttribs(MESH_POSITION, verts[0]);
	trafficMesh.defineVertexAttribs(MESH_TEX_COORD2, texCoords[0]);
	trafficMesh.draw(GL_TRIANGLES);

	fglEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureID);

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

	memberMesh.draw(GL_TRIANGLES);
}

void AStarNavigator::drawGrid(float z)
{
	if (!((int)drawMode & ASTAR_DRAW_MODE_GRID))
		return;
	
	double quarterNodeWidth = 0.25 * nodeWidth;
	float gold[4] = {0.8f,0.8f,0.0f, 1.0f};
	float red[4] = {1.0f, 0.0f, 0.0f, 1.0f};
	// Draw the grid one row at a time, using the large dimension
	bool drawByRow = edgeTableXSize >= edgeTableYSize;
	int maxDim = drawByRow ? edgeTableXSize : edgeTableYSize;
	int minDim = !drawByRow ? edgeTableXSize : edgeTableYSize;
	for(int i = 0; i < maxDim; i++) {
		gridMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_FORCE_CLEANUP);
		for(int j = 0; j < minDim; j++) {
			int row = !drawByRow ? i : j;
			int col = drawByRow ? i : j;
			AStarNode* n = &DeRefEdgeTable(row, col);
			AStarSearchEntry s;
			s.cell.col = col;
			s.cell.row = row;
			AStarNodeExtraData* e = NULL;
			if(n->hasExtraData)
				e = edgeTableExtraData[s.cell.colRow];
			double x = (xOffset + col + 0.5) * nodeWidth;
			double y = (yOffset + row + 0.5) * nodeWidth;

#define ADD_GRID_LINE(dir, x1, y1, z1, x2, y2, z2)\
	if (n->canGo##dir) {\
		int newVertex1 = gridMesh.addVertex();\
		int newVertex2 = gridMesh.addVertex();\
		\
		if (e && e->bonus##dir) {\
			float green[4] = {0.0f, e->bonus##dir, 0.0f, 1.0f};\
			gridMesh.setVertexAttrib(newVertex1, MESH_DIFFUSE4, green);\
			gridMesh.setVertexAttrib(newVertex2, MESH_DIFFUSE4, green);\
		} else {\
			gridMesh.setVertexAttrib(newVertex1, MESH_DIFFUSE4, gold);\
			gridMesh.setVertexAttrib(newVertex2, MESH_DIFFUSE4, gold);\
		}\
		\
		float pos1[3] = {(float)x1, (float)y1, (float)z1};\
		float pos2[3] = {(float)x2, (float)y2, (float)z2};\
		gridMesh.setVertexAttrib(newVertex1, MESH_POSITION, pos1);\
		gridMesh.setVertexAttrib(newVertex2, MESH_POSITION, pos2);\
	}
			if (n->canGoUp && n->canGoDown && n->canGoLeft && n->canGoRight && n->noExtraData) {
				ADD_GRID_LINE(Up, x, y - quarterNodeWidth, z, x, y + quarterNodeWidth, z);
				ADD_GRID_LINE(Right, x - quarterNodeWidth, y, z, x + quarterNodeWidth, y, z);
				continue;
			}

			if (n->canGoUp && n->canGoDown && n->noExtraData) {
				ADD_GRID_LINE(Up, x, y - quarterNodeWidth, z, x, y + quarterNodeWidth, z);
				ADD_GRID_LINE(Right, x, y, z, x + 0.25 * nodeWidth, y,z);
				ADD_GRID_LINE(Left, x, y, z, x - 0.25 * nodeWidth, y, z);
				continue;
			}

			if (n->canGoLeft && n->canGoRight && n->noExtraData) {
				ADD_GRID_LINE(Right, x - quarterNodeWidth, y, z, x + quarterNodeWidth, y, z);
				ADD_GRID_LINE(Up, x, y, z, x, y + 0.25 * nodeWidth, z);
				ADD_GRID_LINE(Down, x, y, z, x, y - 0.25 * nodeWidth, z);
				continue;
			}


			ADD_GRID_LINE(Up, x, y, z, x, y + 0.25 * nodeWidth, z);
			ADD_GRID_LINE(Down, x, y, z, x, y - 0.25 * nodeWidth, z);
			ADD_GRID_LINE(Right, x, y, z, x + 0.25 * nodeWidth, y, z);
			ADD_GRID_LINE(Left, x, y, z, x - 0.25 * nodeWidth, y, z);
			
			if(n->isInTotalSet) {
				mpt("Grid error at x ");mpd(j);mpt(" y ");mpd(i);mpr();
				int newVertex1 = gridMesh.addVertex();
				int newVertex2 = gridMesh.addVertex();

				gridMesh.setVertexAttrib(newVertex1, MESH_DIFFUSE4, red);
				gridMesh.setVertexAttrib(newVertex2, MESH_DIFFUSE4, red);

				float pos1[3] = {(float)x, (float)y, z};
				float pos2[3] = {(float)(x + 0.25 * nodeWidth), (float)(y + 0.25 * nodeWidth), z};
				gridMesh.setVertexAttrib(newVertex1, MESH_POSITION, pos1);
				gridMesh.setVertexAttrib(newVertex2, MESH_POSITION, pos2);
			}
		}
		gridMesh.draw(GL_LINES);
	}
	gridMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_FORCE_CLEANUP);
}


void AStarNavigator::drawAllocations(float z)
{
	if (!showAllocations || time() <= 0)
		return;
	Mesh allocMesh;
	Mesh lineMesh;
	double diamondRadius = 0.2 * nodeWidth;
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

void AStarNavigator::setDirty()
{
	isDirty = true;
}

AStarCell AStarNavigator::getCellFromLoc(const Vec2& modelLoc)
{
	// get the x/y location of the bottom left corner of my grid
	AStarCell cell;
	cell.col = (int)round((modelLoc.x - gridOrigin.x) / nodeWidth);
	cell.col = max(0, cell.col);
	cell.col = min(edgeTableXSize - 1, cell.col);
	cell.row = (int)round((modelLoc.y - gridOrigin.y) / nodeWidth);
	cell.row = max(0, cell.row);
	cell.row = min(edgeTableYSize - 1, cell.row);
	return cell;
}

unsigned int AStarNavigator::getClassType()
{
	return CLASSTYPE_WANTCONNECTLOGIC | CLASSTYPE_FLEXSIMOBJECT | CLASSTYPE_NAVIGATOR;
}

void AStarNavigator::blockGridModelPos(const Vec3& modelPos)
{
	AStarCell cell = getCellFromLoc(Vec2(modelPos.x, modelPos.y));

	if (cell.col >= 0 && cell.col < edgeTableXSize && cell.row >= 0 && cell.row < edgeTableYSize) {
		AStarNode& node = DeRefEdgeTable(cell.row, cell.col);
		node.canGoDown = false;
		node.canGoUp = false;
		node.canGoRight = false;
		node.canGoLeft = false;

		if (cell.col > 0)
			DeRefEdgeTable(cell.row, cell.col - 1).canGoRight = 0;
		if (cell.col < edgeTableXSize - 1)
			DeRefEdgeTable(cell.row, cell.col + 1).canGoLeft = 0;
		if (cell.row > 0)
			DeRefEdgeTable(cell.row - 1, cell.col).canGoUp = 0;
		if (cell.row < edgeTableYSize - 1)
			DeRefEdgeTable(cell.row + 1, cell.col).canGoDown = 0;
	}
}


AStarNodeExtraData*  AStarNavigator::assertExtraData(const AStarCell& cell)
{
	AStarNodeExtraData* extra;
	auto extraIter = edgeTableExtraData.find(cell.colRow);
	if (extraIter == edgeTableExtraData.end()) {
		AStarNode* node = getNode(cell);
		treenode newNode = extraDataNode->subnodes.add();
		extra = new AStarNodeExtraData;
		newNode->addSimpleData(extra, false);
		edgeTableExtraData[cell.colRow] = extra;
		extra->cell = cell;
		node->noExtraData = 0;
	} else {
		extra = extraIter->second;
	}
	return extra;
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

ASTAR_FUNCTION Variant AStarNavigator_setEditMode(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	int mode = (int)param(1);
	if (mode < 0)
		mode = 0;
	AStarNavigator::editMode = mode;

	return 0;
}

ASTAR_FUNCTION Variant AStarNavigator_addBarrier(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	int barrierType = (int)param(5);
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	int editMode = barrierType ? barrierType : AStarNavigator::editMode;

	AStarNavigator* a = navNode->objectAs(AStarNavigator);
	Barrier* newBarrier = NULL;
	switch (editMode) {
	default:
	case EDITMODE_SOLID_BARRIER: newBarrier = a->barrierList.add(new Barrier); break;
	case EDITMODE_DIVIDER: newBarrier = a->barrierList.add(new Divider); break;
	case EDITMODE_ONE_WAY_DIVIDER: newBarrier = a->barrierList.add(new OneWayDivider); break;
	case EDITMODE_PREFERRED_PATH: newBarrier = a->barrierList.add(new PreferredPath(a->defaultPathWeight)); break;
	case EDITMODE_BRIDGE: newBarrier = a->barrierList.add(new Bridge); break;
	}

	newBarrier->init(a->nodeWidth, param(1), param(2), param(3), param(4));
	newBarrier->activePointIndex = 1;
	newBarrier->isActive = 1;
	if (objectexists(a->activeBarrier)) {
		Barrier* activeBarrier = a->activeBarrier->objectAs(Barrier);
		activeBarrier->isActive = 0;
	}
	TreeNode* newNode = newBarrier->holder;
	std::string name = newBarrier->getClassFactory();
	name = name.substr(strlen("AStar::"));
	std::stringstream ss;
	int num = content(a->barriers);
	ss << name << num;
	while (objectexists(node(ss.str().c_str(), a->barriers))) {
		num++;
		ss.str("");
		ss << name << num;
	}

	setname(newNode, ss.str().c_str());
	a->activeBarrier = newNode;
	a->setDirty();

	return newNode;
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
		b->onClick(param(1), (int)param(2), param(3), param(4));
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
		b->onMouseMove(Vec3(param(1), param(2), 0), Vec3(param(3), param(4), 0));
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