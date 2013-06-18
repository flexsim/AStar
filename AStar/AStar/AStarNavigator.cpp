#include "AStarNavigator.h"
#include "Divider.h"
#include "OneWayDivider.h"
#include "PreferredPath.h"
#include "macros.h"

unsigned int AStarNavigator::editMode = 0;

AStarNavigator::AStarNavigator()
	// TODO: Initialize entryhash, edgetableextradata
{
	edgeTable = NULL;
	xOffset = 0;
	yOffset = 0;
	edgeTableXSize = 0;
	edgeTableYSize = 0;

}

AStarNavigator::~AStarNavigator()
{
	if (edgeTable)
		delete [] edgeTable;
}

void AStarNavigator::bindVariables(void)
{
	Navigator::bindVariables();
	bindVariable(preferredPathWeight);
	bindVariable(drawMode);
	bindVariable(nodeWidth);
	bindVariable(surroundDepth);
	bindVariable(deepSearch);

	bindVariable(barriers);
	barrierList.init(barriers);
	bindVariable(activeBarrier);

	bindVariable(fixedResourceBarriers);
	objectBarrierList.init(fixedResourceBarriers);

	bindVariable(cachePaths);
	bindVariable(pathCount);
	bindVariable(requestCount);
	bindVariable(cacheUseCount);
}

double AStarNavigator::onReset()
{
	while (content(node_v_activetravelmembers) > 0)
		transfernode(last(node_v_activetravelmembers), node_v_travelmembers);

	edgeTableExtraData.clear();
	buildEdgeTable();
	buildBoundsMesh();
	buildBarrierMesh();
	buildTrafficMesh();
	maxTraveled = 0;
	return 0;
}

double AStarNavigator::onRunWarm()
{
	for (auto iter = edgeTableExtraData.begin(); iter != edgeTableExtraData.end(); iter++) {
		AStarNodeExtraData & extra = iter->second;
		extra.nrFromUp = 0;
		extra.nrFromDown = 0;
		extra.nrFromLeft = 0;
		extra.nrFromRight = 0;

		extra.nrFromUpLeft = 0;
		extra.nrFromUpRight = 0;
		extra.nrFromDownLeft = 0;
		extra.nrFromDownRight = 0;
	}
	return 0;
}

double AStarNavigator::onDraw(TreeNode* view)
{
	// Based on the drawMode, this function
	// draws the grid, barriers, and traffic

	// This will one day use the Mesh class
	int pickingmode = getpickingmode(view);
	int drawMode = (int)this->drawMode;
	if(drawMode == 0) return 0;
	
	glScalef(1.0/b_spatialsx, 1.0/b_spatialsy, 1.0/b_spatialsz);
	glTranslatef(-b_spatialx, -b_spatialy, -b_spatialz);

	if (!pickingmode) {
		glBindTexture(GL_TEXTURE_2D, 0);
		if (drawMode & ASTAR_DRAW_MODE_GRID)
			drawGrid(0.1f);

		if (drawMode & ASTAR_DRAW_MODE_BOUNDS)
			boundsMesh.draw(GL_QUADS);

		if (drawMode & ASTAR_DRAW_MODE_BARRIERS)
			barrierMesh.draw(GL_TRIANGLES);

		if (drawMode & ASTAR_DRAW_MODE_TRAFFIC)
			trafficMesh.draw(GL_TRIANGLES);

		if (drawMode & ASTAR_DRAW_MODE_MEMBERS)
			drawMembers(0.1f);

		return 0;
	}

	#define SELECTIONMODE_MOUSEMOVE 10
	#define SELECTIONMODE_MOUSEDOWNLEFT 11
	/*
	if(pickingmode != SELECTIONMODE_MOUSEDOWNLEFT && (drawmode&ASTAR_DRAW_MODE_TRAFFIC))
	{
		glPushMatrix();
		glScaled(nodeWidth, nodeWidth, 1.0);
		glBegin(GL_TRIANGLES);
		for(auto iter = edgeTableExtraData.begin(); iter != edgeTableExtraData.end(); iter++)
		{
			AStarNodeExtraData* e = &(iter->second);
			double x = (xOffset + e->col + 0.5);
			double y = (yOffset + e->row + 0.5);
				
			if(pickingmode == SELECTIONMODE_MOUSEMOVE)
			{
				glEnd();
				setpickingdrawfocus(view, holder, PICK_TYPE_HIGHLIGHT_INFO_TRAVEL_GRID, (TreeNode*)(void*)e);
				glBegin(GL_TRIANGLES);
				glVertex3d(x-0.5,y-0.5,0.1);
				glVertex3d(x+0.5,y-0.5,0.1);
				glVertex3d(x+0.5,y+0.5,0.1);

				glVertex3d(x+0.5,y+0.5,0.1);
				glVertex3d(x-0.5,y+0.5,0.1);
				glVertex3d(x-0.5,y-0.5,0.1);
			}
			else
			{
				if(e->nrFromUp > 0) {
					double ratio = (double)e->nrFromUp / (double)maxTraveled;
					glColor4d(1,0,0,ratio);
					glVertex3d(x,y+0.1,0.1);
					glVertex3d(x+0.15,y+0.4,0.1);
					glVertex3d(x-0.15,y+0.4,0.1);
				}

				if(e->nrFromDown > 0) {
					double ratio = (double)e->nrFromDown / (double)maxTraveled;
					glColor4d(1,0,0,ratio);
					glVertex3d(x,y-0.1,0.1);
					glVertex3d(x-0.15,y-0.4,0.1);
					glVertex3d(x+0.15,y-0.4,0.1);
				}

				if(e->nrFromRight > 0) {
					double ratio = (double)e->nrFromRight / (double)maxTraveled;
					glColor4d(1,0,0,ratio);
					glVertex3d(x+0.1,y,0.1);
					glVertex3d(x+0.4,y-0.15,0.1);
					glVertex3d(x+0.4,y+0.15,0.1);
				}

				if(e->nrFromLeft > 0) {
					double ratio = (double)e->nrFromLeft / (double)maxTraveled;
					glColor4d(1,0,0,ratio);
					glVertex3d(x-0.1,y,0.1);
					glVertex3d(x-0.4,y+0.15,0.1);
					glVertex3d(x-0.4,y-0.15,0.1);
				}

				if(e->nrFromUpRight > 0) {
					double ratio = (double)e->nrFromUpRight / (double)maxTraveled;
					glColor4d(1,0,0,ratio);
					glVertex3d(x+0.1,y+0.1,0.1);
					glVertex3d(x+0.4,y+0.25,0.1);
					glVertex3d(x+0.25,y+0.4,0.1);
				}

				if(e->nrFromDownRight > 0) {
					double ratio = (double)e->nrFromDownRight / (double)maxTraveled;
					glColor4d(1,0,0,ratio);
					glVertex3d(x+0.1,y-0.1,0.1);
					glVertex3d(x+0.25,y-0.4,0.1);
					glVertex3d(x+0.4,y-0.25,0.1);
				}

				if(e->nrFromUpLeft > 0) {
					double ratio = (double)e->nrFromUpLeft / (double)maxTraveled;
					glColor4d(1,0,0,ratio);
					glVertex3d(x-0.1,y+0.1,0.1);
					glVertex3d(x-0.25,y+0.4,0.1);
					glVertex3d(x-0.4,y+0.25,0.1);
				}

				if(e->nrFromDownLeft > 0) {
					double ratio = (double)e->nrFromDownLeft / (double)maxTraveled;
					glColor4d(1,0,0,ratio);
					glVertex3d(x-0.1,y-0.1,0.1);
					glVertex3d(x-0.4,y-0.25,0.1);
					glVertex3d(x-0.25,y-0.4,0.1);
				}
			}
		}
		glEnd();
		glPopMatrix();
	}
	*/
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
		boundsMesh.draw(GL_QUADS);
	}
	return 0;
}

double AStarNavigator::onClick(TreeNode* view, int clickcode)
{
	int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, 0);
	TreeNode* secondary = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, 0));

	if (objectexists(secondary)) {
		Barrier* barrier = &o(Barrier, secondary);

		if (objectexists(tonode(activeBarrier))) {
			Barrier* b = &o(Barrier, tonode(activeBarrier));
			if (b != barrier) {
				b->activePointIndex = 0;
				b->isActive = 0;
			}
		}
		activeBarrier = barrier->holder;
		barrier->isActive = 1;
		buildBarrierMesh();
		return barrier->onClick((int)clickcode, cursorinfo(view, 2, 1, 1), cursorinfo(view, 2, 2, 1));
	}
	if (objectexists(tonode(activeBarrier))) {
		Barrier* b = &o(Barrier, tonode(activeBarrier));
		b->activePointIndex = 0;
		b->isActive = 0;
		buildBarrierMesh();
	}
	activeBarrier = 0;
	return FlexsimObject::onClick(view, (int)clickcode);
}

double AStarNavigator::onDrag(TreeNode* view)
{
	int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, 0);
	TreeNode* secondary = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, 0));
	double dx = draginfo(DRAG_INFO_DX);
	double dy = draginfo(DRAG_INFO_DY);

	// Move all attached barriers and objects
	if (pickType == PICK_TYPE_BOUNDS) {
		for (int i = 0; i < barrierList.size(); i++) {
			Barrier* barrier = barrierList[i];

			for (int i = 0; i < barrier->pointList.size(); i++) {
				Point* point = barrier->pointList[i];
				point->x += dx;
				point->y += dy;
			}
		}
		buildBarrierMesh();

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
		savedXOffset += dx / nodeWidth;
		savedYOffset += dy / nodeWidth;
		buildBoundsMesh();
		return 1;
	}

	if (objectexists(secondary)) {
		Barrier* barrier = &o(Barrier, secondary);
		barrier->onMouseMove(cursorinfo(view, 2, 1, 1), cursorinfo(view, 2, 2, 1), dx, dy);
		buildBarrierMesh();
		return 1;
	} 
	
	return FlexsimObject::onDrag(view);
}

double AStarNavigator::dragConnection(TreeNode* connectTo, char keyPressed, unsigned int classType)
{
	if (!objectexists(connectTo))
		return 0;

	if (isclasstype(connectTo, CLASSTYPE_TASKEXECUTER)) {
		TreeNode* navigatorNode = o(TaskExecuter, connectTo).node_v_navigator;
		TreeNode* theNavigator = tonode(get(first(navigatorNode)));
		if (theNavigator == holder)
			return 0;

		TreeNode* travelMembers = node_v_travelmembers;

		switch(keyPressed & 0x7f) {
		case 'A':
			clearcontents(navigatorNode);
			createcoupling(navigatorNode, travelMembers);
			break;
		}
	
	} else if (isclasstype(connectTo, CLASSTYPE_FIXEDRESOURCE)) {
		FixedResource* theFR =  &(o(FixedResource, connectTo));
		TreeNode* storedNode = theFR->Nb_stored;
		for (int i = 0; i < objectBarrierList.size(); i++) {
			TreeNode* objectNode = objectBarrierList[i]->holder;
			if (objectNode == connectTo)
				return 0;
		}


		switch(keyPressed & 0x7f) {
		case 'A':
			objectBarrierList.add(theFR);
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
			buildBarrierMesh();
		} else {
			destroyobject(holder);
		}
		return 1;
	}
	return 0;
}

double AStarNavigator::navigateToObject(TreeNode* traveler, TreeNode* destination, double endSpeed)
{
	double xStart = xcenter(traveler);
	double yStart = ycenter(traveler);

	double loc[3];
	vectorproject(destination, 0.5 * xsize(destination), -0.5 * ysize(destination), 0, model(), loc);
	double xDest = loc[0];
	double yDest = loc[1];
	
	bool driveShort = isclasstype(destination, CLASSTYPE_FIXEDRESOURCE) && isclasstype(traveler, CLASSTYPE_TASKEXECUTER);
	if (driveShort) {
		double halfSx = 0.5 * xsize(destination);
		if (fabs(xDest - xStart) > halfSx) {
			if (xDest > xStart)
				xDest -= halfSx + nodeWidth;
			else
				xDest += halfSx + nodeWidth;
		}

		double halfSy = 0.5 * xsize(destination);
		if (fabs(yDest - yStart) > halfSy) {
			if (yDest > yStart)
				yDest -= halfSy + nodeWidth;
			else
				yDest += halfSy + nodeWidth;
		}
	}

	return navigateToLoc(traveler, xDest, yDest, endSpeed, driveShort);
}

double AStarNavigator::navigateToLoc(TreeNode* traveler, double x, double y, double endSpeed, int driveShort)
{
	setstate(traveler, STATE_TRAVEL_LOADED);
	preferredPathWeightCache = preferredPathWeight;
	double xStart = xcenter(traveler);
	double yStart = ycenter(traveler);
	
	destx = x;
	desty = y;

	TaskExecuter* te = &o(TaskExecuter, traveler);
	TreeNode* coupling = tonode(get(first(te->node_v_navigator)));
	while(content(coupling) < 1) 
		nodeinsertinto(coupling);
	TreeNode* idList = first(coupling);
	// TODO: figure out idLists
	
	// get the x/y location of the bottom left corner of my grid
	col0x = (xOffset + 0.5) * nodeWidth;
	row0y = (yOffset + 0.5) * nodeWidth;

	// figure out the column and row that the traveler is starting from
	int colstart = (int)round((xStart - col0x) / nodeWidth);	
	colstart = max(0, colstart); 
	colstart = min(edgeTableXSize - 1, colstart);
	int rowstart = (int)round((yStart - row0y) / nodeWidth);	
	rowstart = max(0, rowstart); 
	rowstart = min(edgeTableYSize - 1, rowstart);

	// figure out the column and row that the traveler is going to
	int coldest = (int)round((x - col0x) / nodeWidth);	
	coldest = max(0, coldest); 
	coldest = min(edgeTableXSize - 1, coldest);
	int rowdest = (int)round((y - row0y) / nodeWidth);	
	rowdest = max(0, rowdest); 
	rowdest = min(edgeTableYSize - 1, rowdest);

	// This will either be generated by the search, or looked up by the cache
	std::vector<unsigned int> backwardsList;

	// Figure out if this path is in the cache
	bool shouldUseCache = false;
	AStarPathID p;
	if (cachePaths) {
		requestCount++;
		p.startRow = rowstart;
		p.startCol = colstart;
		p.endRow = rowdest;
		p.endCol = coldest;
	
		auto e = pathCache.find(p.id);
		if (e != pathCache.end())
			shouldUseCache = true;
	}

	if (!shouldUseCache) {
		// set xStart/yStart to the center of the start grid point
		xStart = col0x + colstart * nodeWidth;
		yStart = row0y + rowstart * nodeWidth;

		// set x/y to the cetner of the dest grid point
		x = col0x + coldest * nodeWidth;
		y = row0y + rowdest  *nodeWidth;

		// total set includes all resolved and open nodes in the graph
		totalSet.clear();
		// opensetheap is a sorted list of the nodes in the open set
		// the value is the solution of f(x,y) for that node in the set
		while(openSetHeap.size() > 0)
			openSetHeap.pop();

		entryHash.clear();
		// add the first node to the "open set"
		totalSet.push_back(AStarSearchEntry());
		AStarSearchEntry & start = totalSet.back();
		DeRefEdgeTable(rowstart, colstart).notInTotalSet = false;
		start.g = 0;
		start.h = sqrt(sqr(x-xStart)+sqr(y-yStart));
		start.f = start.h;
		start.col = colstart;
		start.row = rowstart;
		start.previous = ~0;
		start.closed = 0;
		entryHash[start.colRow] = 0;

		// the open set stores:
		// 1. the index into totalset that references the AStarSearchEntry that i'm going to resolve
		// 2. the solution f(x, y) of that AStarSearchEntry
		openSetHeap.push(HeapEntry(start.f, 0));
		AStarSearchEntry * final = NULL;
		// closestSoFar is the closest h I've found so far
		float closestSoFar = 10000000000000.0f;
		int closestIndex = 0;
		int size;
		while ((size = openSetHeap.size()) > 0) {
			int shortesti = -1;
			float shortestdist = 100000000000000.0f;
			HeapEntry he(0.0f, 0); AStarSearchEntry * entry = NULL;
			// here I pop off an entry from the heap.
			// the trick is that some entries may have changed their g value
			// in the mean time, so I need to throw away entries if they are 
			// older, bigger g's (i.e. the heap value doesn't match with the 
			// entry's current f value). In this case, the entry will already 
			// have been closed.
			do {
				he = openSetHeap.top();
				openSetHeap.pop();
				entry = &(totalSet[he.totalSetIndex]);
			} while(entry->closed && openSetHeap.size() > 0);

			if (!entry) break;

			shortestIndex = he.totalSetIndex;
			shortest = *entry;
			if (shortest.h < closestSoFar) {
				closestSoFar = shortest.h;
				closestIndex = he.totalSetIndex;
			}
			// close the node
			shortest.closed = 1;
			n = &(DeRefEdgeTable(shortest.row, shortest.col));
			n->open = false;

			// if I am at the destination, then break out of the solve loop
			if (shortest.col == coldest && shortest.row == rowdest) {
				final = &shortest;
				break;
			}

			expandableUp = 0;
			expandableRight = 0;
			expandableDown = 0;
			expandableLeft = 0;

			#define TRAVEL_UP 0x1
			#define TRAVEL_DOWN 0x2
			#define TRAVEL_RIGHT 0x4
			#define TRAVEL_LEFT 0x8
			#define TRAVEL_FAR_UP 0x11
			#define TRAVEL_FAR_DOWN 0x22
			#define TRAVEL_FAR_RIGHT 0x44
			#define TRAVEL_FAR_LEFT 0x88

			// travelFromPrevious is used to figure out the direction he's currently
			// going because if there are multiple path solutions with the same 
			// total distance, then I want to give priority to those solutions that
			// keep him traveling in the same direction, i.e. make him turn the fewest
			// times
			travelFromPrevious = 0;
			// if the node I'm resolving is not the first node in the set ...
			if (shortest.previous != ~0) {
				AStarSearchEntry& lastEntry = totalSet[shortest.previous];

				if (deepSearch) {
					int colDiff = lastEntry.col - shortest.col;
					if (colDiff < -1) {
						travelFromPrevious |= TRAVEL_FAR_RIGHT;
					} else if (colDiff < 0) {
						travelFromPrevious |= TRAVEL_RIGHT;
					} else if (colDiff > 1) {
						travelFromPrevious |= TRAVEL_FAR_LEFT;
					} else if (colDiff) {
						travelFromPrevious |= TRAVEL_LEFT;
					}

					int rowDiff = lastEntry.row - shortest.row;
					if (rowDiff < -1) {
						travelFromPrevious |= TRAVEL_FAR_UP;
					} else if (rowDiff < 0) {
						travelFromPrevious |= TRAVEL_UP;
					} else if (rowDiff > 1) {
						travelFromPrevious |= TRAVEL_FAR_DOWN;
					} else if (rowDiff) {
						travelFromPrevious |= TRAVEL_DOWN;
					}
				} else {
					// then see if he's travel right or left ...
					if(lastEntry.col < shortest.col) travelFromPrevious |= TRAVEL_RIGHT;
					else if(lastEntry.col > shortest.col) travelFromPrevious |= TRAVEL_LEFT;
					// and see if he's traveling up or down
					if(lastEntry.row < shortest.row) travelFromPrevious |= TRAVEL_UP;
					else if(lastEntry.row > shortest.row) travelFromPrevious |= TRAVEL_DOWN;
				}
			}


#define CHECK_EXPAND_OPEN_SET(node, entry, direction, boundarycondition, rowInc, colInc, travelval, dist)\
	if(node->canGo##direction && boundarycondition){\
			int theCol = entry->col + colInc;\
			int theRow = entry->row + rowInc;\
			expandable##direction = 1;\
			double distance = dist;\
			if(!node->noExtraData) {\
				auto e = edgeTableExtraData.find(entry->colRow);\
				if (e != edgeTableExtraData.end() && e->second.bonus##direction)\
				distance *= 1.0 - (preferredPathWeightCache * e->second.bonus##direction)/127;\
			}\
			expandOpenSet(theRow, theCol, distance, travelval);\
		}
		
#define CHECK_EXPAND_OPEN_SET_DIAGONAL(theNode, entry, vertdirection, hordirection, rowInc, colInc, travelval)\
		if(expandable##vertdirection && expandable##hordirection \
			&& DeRefEdgeTable(entry->row, entry->col + colInc).canGo##vertdirection \
			&& DeRefEdgeTable(entry->row + rowInc, entry->col).canGo##hordirection) \
		{\
			int col = entry->col + colInc;\
			int row = entry->row + rowInc;\
			double diagDistance = 1.4142135623;\
			AStarNode* diagNode = &(DeRefEdgeTable(row, col));\
			if(!diagNode->noExtraData) {\
				auto e = edgeTableExtraData.find(entry->colRow);\
				if (e != edgeTableExtraData.end()) {\
					if(e->second.bonus##vertdirection)\
						diagDistance *= 1.0 - (0.70*preferredPathWeightCache * e->second.bonus##vertdirection)/127;\
					if(e->second.bonus##hordirection)\
						diagDistance *= 1.0 - (0.70*preferredPathWeightCache * e->second.bonus##hordirection)/127;\
				}\
			}\
			AStarSearchEntry* nextEntry = expandOpenSet(row, col, diagDistance, travelval);\
			if (nextEntry && deepSearch) {\
				unsigned int vertTravelVal = travelval | (travelval & TRAVEL_UP ? TRAVEL_FAR_UP : TRAVEL_FAR_DOWN);\
				unsigned int hzntlTravelVal = travelval | (travelval & TRAVEL_RIGHT ? TRAVEL_FAR_RIGHT : TRAVEL_FAR_LEFT);\
				CHECK_EXPAND_OPEN_SET(diagNode, nextEntry, vertdirection, row < edgeTableYSize - 1 && row > 0, rowInc, 0, \
					vertTravelVal, diagDistance * 1.58113883);\
				CHECK_EXPAND_OPEN_SET(diagNode, nextEntry, hordirection, col < edgeTableXSize - 1 && col > 0, 0, colInc, \
					hzntlTravelVal, diagDistance * 1.58113883);\
			}\
		}\

		
		CHECK_EXPAND_OPEN_SET(n, (&shortest), Up, shortest.row < edgeTableYSize - 1, 1, 0, TRAVEL_UP, 1.0)
		CHECK_EXPAND_OPEN_SET(n, (&shortest), Right, shortest.col < edgeTableXSize - 1, 0, 1, TRAVEL_RIGHT, 1.0)
		CHECK_EXPAND_OPEN_SET(n, (&shortest), Down, shortest.row > 0, -1, 0, TRAVEL_DOWN, 1.0)
		CHECK_EXPAND_OPEN_SET(n, (&shortest), Left, shortest.col > 0, 0, -1, TRAVEL_LEFT, 1.0)

		CHECK_EXPAND_OPEN_SET_DIAGONAL(n, (&shortest), Up, Right, 1, 1, TRAVEL_UP|TRAVEL_RIGHT)
		CHECK_EXPAND_OPEN_SET_DIAGONAL(n, (&shortest), Up, Left, 1, -1, TRAVEL_UP|TRAVEL_LEFT)
		CHECK_EXPAND_OPEN_SET_DIAGONAL(n, (&shortest), Down, Right, -1, 1, TRAVEL_DOWN|TRAVEL_RIGHT)
		CHECK_EXPAND_OPEN_SET_DIAGONAL(n, (&shortest), Down, Left, -1, -1, TRAVEL_DOWN|TRAVEL_LEFT)
	}


		if (!final) 
			final = &(totalSet[closestIndex]);

		unsigned int startPrevVal =  ~((unsigned int)0);
		AStarSearchEntry* temp = final;
		while (1) {
			backwardsList.push_back(temp->colRow);
			if(temp->previous != startPrevVal)
				temp = &(totalSet[temp->previous]);
			else break;
		}

		if (cachePaths) {
			pathCache[p.id] = backwardsList;
			pathCount++;
		}
	
	} else { // if I am looking up the cache
		backwardsList = pathCache[p.id];
		cacheUseCount++;
	}

	int nrNodes = backwardsList.size();

	treenode kinematics = te->node_v_kinematics;
	initkinematics(kinematics, xStart, yStart, 0, 0,0,0, 1, 0);

	AStarSearchEntry e, laste;
	laste.colRow = backwardsList[nrNodes - 1];
	double endtime = time();
	if(driveShort) 
		driveShort = (int)round(0.4*xsize(traveler) / nodeWidth);
	for(int i = nrNodes - 2; i >= driveShort; i--) {
		e.colRow = backwardsList[i];
		endtime = addkinematic(kinematics, (e.col - laste.col)*nodeWidth, (e.row - laste.row)*nodeWidth, 0, 
			te->v_maxspeed, 0,0,0,0,endtime, KINEMATIC_TRAVEL);
		
		AStarNodeExtraData* extra;
		auto extraIter = edgeTableExtraData.find(e.colRow);
		if (extraIter == edgeTableExtraData.end()) {
			extra = &(edgeTableExtraData[e.colRow]);
			memset(extra, 0, sizeof(AStarNodeExtraData));
			extra->colRow = e.colRow;
			DeRefEdgeTable(e.row, e.col).noExtraData = 0;
		} else {
			extra = &extraIter->second;
		}
		unsigned int* involvedextra;
		if (e.row > laste.row) {
			if(e.col > laste.col) involvedextra = &extra->nrFromDownLeft;
			else if(e.col < laste.col) involvedextra = &extra->nrFromDownRight;
			else involvedextra = &extra->nrFromDown;
		}
		else if(e.row < laste.row)
		{
			if(e.col > laste.col) involvedextra = &extra->nrFromUpLeft;
			else if(e.col < laste.col) involvedextra = &extra->nrFromUpRight;
			else involvedextra = &extra->nrFromUp;
		}
		else if(e.col > laste.col) involvedextra = &extra->nrFromLeft;
		else involvedextra = &extra->nrFromRight;

		involvedextra[0]++;
		if(involvedextra[0] > maxTraveled) maxTraveled = involvedextra[0];

		laste.colRow = e.colRow;
	}

	int totalsetsize = totalSet.size();
	for(int i = 0; i < totalsetsize; i++) {
		AStarSearchEntry & e = totalSet[i];
		AStarNode* n = &DeRefEdgeTable(e.row, e.col);
		n->notInTotalSet = true;
		n->open = true;
	}

	transfernode(coupling, node_v_activetravelmembers);
	createevent(holder, endtime - time(), EVENT_A_STAR_END_TRAVEL, "End Travel", coupling);

	return 0;
}

AStarSearchEntry* AStarNavigator::expandOpenSet(int r, int c, float multiplier, int travelVal)
{
	AStarSearchEntry* entry = NULL;
	int closed = 0;
	int totalSetIndex;
	AStarNode* n = &DeRefEdgeTable(r, c);
	// is he already in the total set
	if (!n->notInTotalSet) {
		// if he's in the total set and he's open, then abort
		if (n->open) 
			return NULL;
		// if he's not in the open set, then 
		AStarSearchEntry hashEntry;
		hashEntry.row = r;
		hashEntry.col = c;
		totalSetIndex = entryHash[hashEntry.colRow];
		entry = &(totalSet[totalSetIndex]);
	}
	float newG = shortest.g + multiplier * nodeWidth;
	/*  Check if the guy is changing directions. If so, I want to increase the distance so it will be a penalty to make turns*/ \
	if(travelFromPrevious != travelVal) {
		// add a small penalty if he's turning
		newG += 0.05*nodeWidth;
		// if it's a right angle turn or more, then add more penalty
		if((travelFromPrevious & travelVal) == 0)
			newG += 0.05*nodeWidth;
	}
	
	if (!entry || newG < entry->g-0.01*nodeWidth) {
		// if entry is NULL, that means he's not in the total set yet,
		// so I need to add him.
		if (!entry) {
			totalSetIndex = totalSet.size();
			totalSet.push_back(AStarSearchEntry());
			entry = &totalSet.back();
			entry->col = c;
			entry->row = r;
			entryHash[entry->colRow] = totalSetIndex;
			// calculate the distance heuristic h
			double diffx = destx - (col0x + entry->col * nodeWidth);
			double diffy = desty - (row0y + entry->row * nodeWidth);
			entry->h = (1.0 - preferredPathWeightCache) * sqrt(diffx*diffx + diffy*diffy);
			entry->closed = 0;
			n->notInTotalSet = false;
		}
		entry->g = newG;
		entry->f = entry->g + entry->h;
		openSetHeap.push(HeapEntry(entry->f, totalSetIndex));
		entry->previous = shortestIndex;
	}
	return entry;
}

double AStarNavigator::abortTravel(TreeNode* traveler, TreeNode* newTS)
{
	//fsnode* mycoupling = tonode(get(first(o(TaskExecuter, traveler).node_v_navigator)));
	//destroyeventsofobject(holder, -1, EVENT_A_STAR_END_TRAVEL, NULL, mycoupling);
	return 0;
}

double AStarNavigator::onTimerEvent(TreeNode* involved, int code, char* datastr)
{
	switch(code) {
	case EVENT_A_STAR_END_TRAVEL:
		TreeNode* object = ownerobject(tonode(get(involved)));
		TaskExecuter* te = &o(TaskExecuter, object);
		TreeNode* kinematics = te->node_v_kinematics;
		updatekinematics(kinematics, object, time());
		te->b_spatialx -= 0.5*te->b_spatialsx;
		te->b_spatialy += 0.5*te->b_spatialsy;
		transfernode(involved, node_v_travelmembers);
		int tasktype = gettasktype(object, 0);
		
		te->onDestinationArrival(0);
	}
	return 0;
}

double AStarNavigator::updateLocations()
{
	TreeNode* members = node_v_activetravelmembers;
	for(int i = 1; i <= content(members); i++)
	{
		TreeNode* coupling = rank(members, i);
		TreeNode* traveller = ownerobject(tonode(get(coupling)));
		TaskExecuter* te = &o(TaskExecuter, traveller);
		TreeNode* kinematics = te->node_v_kinematics;
		updatekinematics(kinematics, traveller, time());
		te->b_spatialx -= 0.5*te->b_spatialsx;
		te->b_spatialy += 0.5*te->b_spatialsy;
	}
	return 0;
}

void AStarNavigator::buildEdgeTable()
{
	// Determine the grid bounds
	double min[2] = {100000000.0,1000000000.0};
	double max[2] = {-100000000.0,-1000000000.0};

	pathCache.clear();
	pathCount = 0;
	requestCount = 0;
	cacheUseCount = 0;
	if (content(barriers) == 0 && objectBarrierList.size() == 0) {
		if (edgeTable)
			delete [] edgeTable;
		edgeTable = 0;
		return;
	}

	for (int i = 0; i < barrierList.size(); i++) {
		Barrier* barrier = barrierList[i];
		double x1, y1, x2, y2;
		barrier->getBoundingBox(x1, y1, x2, y2);

		if(x1 < min[0]) min[0] = x1;
		if(x1 > max[0]) max[0] = x1;
		if(y1 < min[1]) min[1] = y1;
		if(y1 > max[1]) max[1] = y1;
		if(x2 < min[0]) min[0] = x2;
		if(x2 > max[0]) max[0] = x2;
		if(y2 < min[1]) min[1] = y2;
		if(y2 > max[1]) max[1] = y2;
	}

	for (int i = 0; i < objectBarrierList.size(); i++) {
		// spatialx/y are the top left corner
		// Treat objects as a solid barrier
		TreeNode* theObj = objectBarrierList[i]->holder;
		double x1 = get(spatialx(theObj));
		double y1 = get(spatialy(theObj)) - get(spatialsy(theObj));
		double x2 = x1 + get(spatialsx(theObj));
		double y2 = get(spatialy(theObj));

		// Shrink the bounding box for objects
		double halfNodeWidth = 0.5 * nodeWidth;
		x1 += halfNodeWidth;
		x2 -= halfNodeWidth;
		y1 += halfNodeWidth;
		y2 -= halfNodeWidth;
		
		if(x1 < min[0]) min[0] = x1;
		if(x1 > max[0]) max[0] = x1;
		if(y1 < min[1]) min[1] = y1;
		if(y1 > max[1]) max[1] = y1;
		if(x2 < min[0]) min[0] = x2;
		if(x2 > max[0]) max[0] = x2;
		if(y2 < min[1]) min[1] = y2;
		if(y2 > max[1]) max[1] = y2;
	}

	xOffset = (int)(floor(min[0] / nodeWidth) - surroundDepth);
	yOffset = (int)(floor(min[1] / nodeWidth) - surroundDepth);
	savedXOffset = xOffset;
	savedYOffset = yOffset;

	edgeTableXSize = (int)(ceil((max[0] - min[0]) / nodeWidth) + surroundDepth * 2 + 1);
	edgeTableYSize = (int)(ceil((max[1] - min[1]) / nodeWidth) + surroundDepth * 2 + 1);

	double col0xloc = (xOffset + 0.5) * nodeWidth;
	double row0yloc = (yOffset + 0.5) * nodeWidth;

	// Create a new fully connected table
	unsigned int tableSize = edgeTableYSize * edgeTableXSize;
	if (edgeTable)
		delete [] edgeTable;
	edgeTable = new AStarNode[tableSize];
	memset(edgeTable, 0xFFFFFFFF, tableSize * sizeof(AStarNode));

	for(int i = 0; i < barrierList.size(); i++) {
		Barrier* barrier = barrierList[i];
		barrier->modifyTable(edgeTable, &edgeTableExtraData, col0xloc, row0yloc, edgeTableXSize, edgeTableYSize);
	}
	

	for (int i = 0; i < objectBarrierList.size(); i++) {
		TreeNode* theObj = objectBarrierList[i]->holder;
		double x1 = get(spatialx(theObj));
		double y1 = get(spatialy(theObj)) - get(spatialsy(theObj));
		double x2 = x1 + get(spatialsx(theObj));
		double y2 = get(spatialy(theObj));

		// Shrink the bounding box for objects
		double halfNodeWidth = 0.5 * nodeWidth;
		x1 += halfNodeWidth;
		x2 -= halfNodeWidth;
		y1 += halfNodeWidth;
		y2 -= halfNodeWidth;

		double xmin = min(x1, x2);
		double xmax = max(x1, x2);
		double ymin = min(y1, y2);
		double ymax = max(y1, y2);

		int colleft = (int)round((xmin - col0xloc) / nodeWidth);
		int rowbottom = (int)round((ymin - row0yloc) / nodeWidth);
		int colright = (int)round((xmax - col0xloc) / nodeWidth);
		int rowtop = (int)round((ymax - row0yloc) / nodeWidth);
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
	}
}
void AStarNavigator::buildBoundsMesh()
{
	boundsMesh.init(0, MESH_POSITION, 
		MESH_NORMAL | MESH_EMISSIVE | MESH_AMBIENT_AND_DIFFUSE, MESH_FORCE_CLEANUP);
	float up[3] = {0.0f, 0.0f, 1.0f};
	TreeNode* color = node_b_color;
	float boundsColor[3] = {
		(float)get(rank(color, 1)), 
		(float)get(rank(color, 2)), 
		(float)get(rank(color, 3))
	};
	float black[3] = {0.0f, 0.0f, 0.0f};

	boundsMesh.setVertexAttrib(0, MESH_NORMAL, up);
	boundsMesh.setVertexAttrib(0, MESH_EMISSIVE, boundsColor);
	boundsMesh.setVertexAttrib(0, MESH_AMBIENT_AND_DIFFUSE, black);

	float width = edgeTableXSize * nodeWidth;
	float height = edgeTableYSize * nodeWidth;
	float borderWidth = nodeWidth;

	float midBW = 0.4 * borderWidth;
	float z = 0.1f;
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
	barrierMesh.init(0, MESH_POSITION | MESH_EMISSIVE, 
		MESH_NORMAL | MESH_AMBIENT_AND_DIFFUSE, 0);
	float up[3] = {0.0f, 0.0f, 1.0f};
	float black[3] = {0.0f, 0.0f, 0.0f};
	barrierMesh.setVertexAttrib(0, MESH_NORMAL, up);
	barrierMesh.setVertexAttrib(0, MESH_AMBIENT_AND_DIFFUSE, black);
	for (int i = 0; i < barrierList.size(); i++) {
		barrierList[i]->nodeWidth = nodeWidth;
		barrierList[i]->addVertices(&barrierMesh, 0.1f);
	}
}

void AStarNavigator::buildTrafficMesh()
{
	trafficMesh.init(0, MESH_POSITION | MESH_EMISSIVE, 0, 0);
}

void AStarNavigator::drawMembers(float z)
{
	memberMesh.init(0, MESH_POSITION, 
		MESH_EMISSIVE | MESH_NORMAL | MESH_AMBIENT_AND_DIFFUSE, MESH_FORCE_CLEANUP);
	TreeNode* colorNode = node_b_color;
	float r = get(rank(colorNode, 1));
	float g = get(rank(colorNode, 2));
	float b = get(rank(colorNode, 3));
	float color[3] = {r, g, b};
	float up[3] = {0.0f, 0.0f, 1.0f};
	float black[3] = {0.0f, 0.0f, 0.0f};

	memberMesh.setVertexAttrib(0, MESH_NORMAL, up);
	memberMesh.setVertexAttrib(0, MESH_EMISSIVE, color);
	memberMesh.setVertexAttrib(0, MESH_AMBIENT_AND_DIFFUSE, black);

	// Draw rectangles under every object
	unsigned int numObjs = objectBarrierList.size();
	for (int i = 0; i < numObjs; i++) {
		FixedResource* theFR = objectBarrierList[i];
		TreeNode* theNode = theFR->holder;

		// The position is the top left corner
		float x = spatialx(theNode)->dataasdouble[0];
		float y = spatialy(theNode)->dataasdouble[0];
		float width = spatialsx(theNode)->dataasdouble[0];
		float height = spatialsy(theNode)->dataasdouble[0];
		float topLeft[3] = {x, y, z};
		float bottomLeft[3] = {x, y - height, z};
		float topRight[3] = {x + width, y, z};
		float bottomRight[3] = {topRight[0], bottomLeft[1], z};

#define ABV(pos) {\
	int newVertex = memberMesh.addVertex();\
	memberMesh.setVertexAttrib(newVertex, MESH_POSITION, pos);\
	}

#define ABT(pos1, pos2, pos3) ABV(pos1) ABV(pos2) ABV(pos3)

		ABT(topLeft, bottomLeft, topRight);
		ABT(bottomRight, topRight, bottomLeft);

#undef ABV
#undef ABT

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
	TreeNode* travelers = node_v_travelmembers;
	unsigned int numTravelers = content(travelers);
	for (int i = 1; i <= numTravelers; i++) {
		TreeNode* traveler = ownerobject(tonode(get(rank(travelers, i))));

		float x = spatialx(traveler)->dataasdouble[0];
		float y = spatialy(traveler)->dataasdouble[0];
		float width = spatialsx(traveler)->dataasdouble[0];
		float height = spatialsy(traveler)->dataasdouble[0];
		float radius = sqrt(width * width / 4.0 + height * height / 4.0);
		float center[3] = {x + width / 2.0, y - height / 2.0, z};

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

	travelers = node_v_activetravelmembers;
	numTravelers = content(travelers);
	for (int i = 1; i <= numTravelers; i++) {
		TreeNode* traveler = ownerobject(tonode(get(rank(travelers, i))));

		float x = spatialx(traveler)->dataasdouble[0];
		float y = spatialy(traveler)->dataasdouble[0];
		float width = spatialsx(traveler)->dataasdouble[0];
		float height = spatialsy(traveler)->dataasdouble[0];
		float radius = sqrt(width * width / 4.0 + height * height / 4.0);
		float center[3] = {x + width / 2.0, y - height / 2.0, z};

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
	float gold[3] = {0.8f,0.8f,0.0f};
	float red[3] = {1.0f, 0.0f, 0.0f};
	// Draw the grid one row at a time, using the large dimension
	bool drawByRow = edgeTableXSize >= edgeTableYSize;
	int maxDim = drawByRow ? edgeTableXSize : edgeTableYSize;
	int minDim = !drawByRow ? edgeTableXSize : edgeTableYSize;
	for(int i = 0; i < maxDim; i++) {
		gridMesh.init(0, MESH_POSITION | MESH_EMISSIVE, 0, MESH_FORCE_CLEANUP);
		for(int j = 0; j < minDim; j++) {
			int row = !drawByRow ? i : j;
			int col = drawByRow ? i : j;
			AStarNode* n = &DeRefEdgeTable(row, col);
			AStarSearchEntry s;
			s.col = col;
			s.row = row;
			AStarNodeExtraData* e = NULL;
			if(!n->noExtraData)
				e = &edgeTableExtraData[s.colRow];
			double x = (xOffset + col + 0.5) * nodeWidth;
			double y = (yOffset + row + 0.5) * nodeWidth;

#define ADD_GRID_LINE(dir, x1, y1, z1, x2, y2, z2)\
	if (n->canGo##dir) {\
		int newVertex1 = gridMesh.addVertex();\
		int newVertex2 = gridMesh.addVertex();\
		\
		if (e && e->bonus##dir) {\
			float green[3] = {0.0f, e->bonus##dir, 0.0f};\
			gridMesh.setVertexAttrib(newVertex1, MESH_EMISSIVE, green);\
			gridMesh.setVertexAttrib(newVertex2, MESH_EMISSIVE, green);\
		} else {\
			gridMesh.setVertexAttrib(newVertex1, MESH_EMISSIVE, gold);\
			gridMesh.setVertexAttrib(newVertex2, MESH_EMISSIVE, gold);\
		}\
		\
		float pos1[3] = {(float)x1, (float)y1, (float)z1};\
		float pos2[3] = {(float)x2, (float)y2, (float)z2};\
		gridMesh.setVertexAttrib(newVertex1, MESH_POSITION, pos1);\
		gridMesh.setVertexAttrib(newVertex2, MESH_POSITION, pos2);\
	}
			if (n->canGoUp && n->canGoDown && n->canGoLeft && n->canGoRight) {
				ADD_GRID_LINE(Up, x, y - quarterNodeWidth, z, x, y + quarterNodeWidth, z);
				ADD_GRID_LINE(Right, x - quarterNodeWidth, y, z, x + quarterNodeWidth, y, z);
				continue;
			}

			if (n->canGoUp && n->canGoDown) {
				ADD_GRID_LINE(Up, x, y - quarterNodeWidth, z, x, y + quarterNodeWidth, z);
				ADD_GRID_LINE(Right, x, y, z, x + 0.25 * nodeWidth, y,z);
				ADD_GRID_LINE(Left, x, y, z, x - 0.25 * nodeWidth, y, z);
				continue;
			}

			if (n->canGoLeft && n->canGoRight) {
				ADD_GRID_LINE(Right, x - quarterNodeWidth, y, z, x + quarterNodeWidth, y, z);
				ADD_GRID_LINE(Up, x, y, z, x, y + 0.25 * nodeWidth, z);
				ADD_GRID_LINE(Down, x, y, z, x, y - 0.25 * nodeWidth, z);
				continue;
			}


			ADD_GRID_LINE(Up, x, y, z, x, y + 0.25 * nodeWidth, z);
			ADD_GRID_LINE(Down, x, y, z, x, y - 0.25 * nodeWidth, z);
			ADD_GRID_LINE(Right, x, y, z, x + 0.25 * nodeWidth, y, z);
			ADD_GRID_LINE(Left, x, y, z, x - 0.25 * nodeWidth, y, z);
			
			if(!n->notInTotalSet) {
				mpt("Grid error at x ");mpd(j);mpt(" y ");mpd(i);mpr();
				int newVertex1 = gridMesh.addVertex();
				int newVertex2 = gridMesh.addVertex();

				gridMesh.setVertexAttrib(newVertex1, MESH_EMISSIVE, red);
				gridMesh.setVertexAttrib(newVertex2, MESH_EMISSIVE, red);

				float pos1[3] = {(float)x, (float)y, z};
				float pos2[3] = {(float)(x + 0.25 * nodeWidth), (float)(y + 0.25 * nodeWidth), z};
				gridMesh.setVertexAttrib(newVertex1, MESH_POSITION, pos1);
				gridMesh.setVertexAttrib(newVertex2, MESH_POSITION, pos2);
			}
		}
		gridMesh.draw(GL_LINES);
	}
	gridMesh.init(0, MESH_POSITION | MESH_EMISSIVE, 0, MESH_FORCE_CLEANUP);
}


unsigned int AStarNavigator::getClassType()
{
	return CLASSTYPE_WANTCONNECTLOGIC | CLASSTYPE_FLEXSIMOBJECT | CLASSTYPE_NAVIGATOR;
}

visible void AStarNavigator_setEditMode(FLEXSIMINTERFACE)
{
	int mode = (int)parval(1);
	if (mode < 0)
		mode = 0;
	AStarNavigator::editMode = mode;
}

visible void AStarNavigator_addBarrier(FLEXSIMINTERFACE)
{
	TreeNode* navNode = parnode(1);
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return;

	AStarNavigator* a = &o(AStarNavigator, navNode);
	Barrier* newBarrier = NULL;
	switch (AStarNavigator::editMode) {
	case EDITMODE_SOLID_BARRIER: newBarrier = a->barrierList.add(new Barrier); break;
	case EDITMODE_DIVIDER: newBarrier = a->barrierList.add(new Divider); break;
	case EDITMODE_ONE_WAY_DIVIDER: newBarrier = a->barrierList.add(new OneWayDivider); break;
	case EDITMODE_PREFERRED_PATH: newBarrier = a->barrierList.add(new PreferredPath); break;
	default: return;
	}

	newBarrier->init(a->nodeWidth, parval(2), parval(3), parval(4), parval(5));
	newBarrier->mode = BARRIER_MODE_DYNAMIC_CREATE;
	newBarrier->activePointIndex = 1;
	newBarrier->isActive = 1;
	if (objectexists(a->activeBarrier)) {
		Barrier* activeBarrier = &o(Barrier, tonode(a->activeBarrier));
		activeBarrier->isActive = 0;
	}

	a->activeBarrier = newBarrier->holder;
}

visible void AStarNavigator_removeBarrier(FLEXSIMINTERFACE)
{
	TreeNode* navNode = parnode(1);
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return;

	AStarNavigator* a = &o(AStarNavigator, navNode);
	int index = (int)parval(2);
	if (index >= a->barrierList.size())
		return;

	a->barrierList.remove((int)parval(2));
}

visible void AStarNavigator_swapBarriers(FLEXSIMINTERFACE)
{
	TreeNode* navNode = parnode(1);
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return;

	AStarNavigator* a = &o(AStarNavigator, navNode);
	int index1 = (int)parval(2);
	int index2 = (int)parval(3);

	int maxIndex = max(index1, index2);
	int minIndex = min(index1, index2);
	if (maxIndex > a->barrierList.size() || minIndex < 0)
		return;

	a->barrierList.swap(index1, index2);
}

visible void AStarNavigator_onClick(FLEXSIMINTERFACE)
{
	TreeNode* navNode = parnode(1);
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return;

	AStarNavigator* a = &o(AStarNavigator, navNode);
	if (objectexists(tonode(a->activeBarrier))) {
		Barrier* b = &o(Barrier, tonode(a->activeBarrier));
		b->onClick((int)parval(2), parval(3), parval(4));
	}
}

visible void AStarNavigator_onMouseMove(FLEXSIMINTERFACE)
{
	TreeNode* navNode = parnode(1);
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return;

	AStarNavigator* a = &o(AStarNavigator, navNode);
	if (objectexists(tonode(a->activeBarrier))) {
		Barrier* b = &o(Barrier, tonode(a->activeBarrier));
		b->onMouseMove(parval(2), parval(3), parval(4), parval(5));
		a->buildBarrierMesh();
	}
}

visible double AStarNavigator_getActiveBarrierMode(FLEXSIMINTERFACE)
{
	TreeNode* navNode = parnode(1);
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	AStarNavigator* a = &o(AStarNavigator, navNode);
	if (objectexists(tonode(a->activeBarrier))) {
		Barrier* b = &o(Barrier, tonode(a->activeBarrier));
		return b->mode;
	}

	return 0;
}

visible void AStarNavigator_rebuildMeshes(FLEXSIMINTERFACE)
{
	TreeNode* navNode = parnode(1);
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return;

	AStarNavigator* a = &o(AStarNavigator, navNode);
	int drawMode = (int)a->drawMode;
	if (parval(2))
		drawMode = (int)parval(2);

	if (drawMode & ASTAR_DRAW_MODE_BARRIERS)
		a->buildBarrierMesh();

	if (drawMode & ASTAR_DRAW_MODE_BOUNDS)
		a->buildBoundsMesh();

	if (drawMode & ASTAR_DRAW_MODE_TRAFFIC)
		a->buildTrafficMesh();
}