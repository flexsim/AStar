#include "AStarNavigator.h"
#include "macros.h"

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
		flexsimfree(edgeTable);
}

void AStarNavigator::bindVariables(void)
{
	Navigator::bindVariables();
	bindVariable(preferredPathWeight);
	bindVariable(drawMode);
	bindVariable(nodeWidth);
	bindVariable(savedEdgeTableExtraData);
	bindVariable(barriers);
	barrierList.init(barriers);
}

double AStarNavigator::OnReset()
{
	while (content(node_v_travelmembers) > 0)
		transfernode(last(node_v_activetravelmembers), node_v_travelmembers);

	for (int i = 1; i <= content(node_v_travelmembers); i++) {
		TreeNode* coupling = rank(node_v_travelmembers, i);
		while (content(coupling) < 1)
			nodeinsertinto(coupling);
		//TODO: figure out resetidlist
	}

	buildEdgeTable();
	maxTraveled = 0;
	return 0;
}

double AStarNavigator::OnRunWarm()
{
	// Set directional data in each egdeTableExtraData entry
	// to zero
	return 0;
}

double AStarNavigator::OnDraw(TreeNode* view)
{
	// Based on the drawMode, this function
	// draws the grid, barriers, and traffic

	// This will one day use the Mesh class
	return 0;
}

double AStarNavigator::OnDrag(TreeNode* view)
{
	int pickType = getpickingdrawfocus(view, PICK_TYPE, 0);
	TreeNode* secondary = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, 0));
	double dx = draginfo(DRAG_INFO_DX);
	double dy = draginfo(DRAG_INFO_DY);
	switch (pickType) {
	case PICK_DIVIDER_NODE:
		inc(secondary, dx);
		inc(next(secondary), dy);
		break;
	case PICK_DIVIDER_EDGE:
		inc(secondary, dx);
		inc(next(secondary), dy);
		inc(next(next(secondary)), dx);
		inc(next(next(next(secondary))), dy);
		break;
	case PICK_SOLID_BARRIER:
		inc(rank(secondary, BARRIER_X1), dx);
		inc(rank(secondary, BARRIER_Y1), dy);
		inc(rank(secondary, BARRIER_X2), dx);
		inc(rank(secondary, BARRIER_Y2), dy);
		break;

	}
	return 1;
}

double AStarNavigator::OnDestroy(TreeNode* view)
{
	if(objectexists(view))
	{
		int picktype = getpickingdrawfocus(view, PICK_TYPE,0);
		TreeNode* secondary = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT,0));
		TreeNode* barrier = NULL;
		switch(picktype) {
		case PICK_SOLID_BARRIER:
			destroyobject(secondary);
			break;
		case PICK_DIVIDER_NODE:
			barrier = up(secondary);
			destroyobject(next(secondary));
			destroyobject(secondary);
			if(content(barrier) < BARRIER_CONTENT)
				destroyobject(barrier);
			break;
		
		case PICK_DIVIDER_EDGE:
			barrier = up(secondary);
			destroyobject(barrier);
			break;
		
		}
		return 1;
	}
	return 0;
}

double AStarNavigator::navigateTo(TreeNode* traveler, TreeNode* destination, double endSpeed)
{
	double xStart = xcenter(traveler);
	double yStart = ycenter(traveler);

	double loc[3];
	vectorproject(destination, 0.5 * xsize(destination), -0.5 * ysize(destination), 0, model(), loc);
	double xDest = loc[0];
	double yDest = loc[1];
	
	bool driveShort = isclasstype(destination, "StorageObject") && isclasstype(traveler, "TeamMember");
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
	setstate(traveler, WORKER_STATE_TRAVEL, WORKER_STATE_PROFILE);
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
	int colstart = round((xStart - col0x) / nodeWidth);	
	colstart = max(0, colstart); 
	colstart = min(edgeTableXSize - 1, colstart);
	int rowstart = round((yStart - row0y) / nodeWidth);	
	rowstart = max(0, rowstart); 
	rowstart = min(edgeTableYSize - 1, rowstart);

	// figure out the column and row that the traveler is going to
	int coldest = round((x - col0x) / nodeWidth);	
	coldest = max(0, coldest); 
	coldest = min(edgeTableXSize - 1, coldest);
	int rowdest = round((y - row0y) / nodeWidth);	
	rowdest = max(0, rowdest); 
	rowdest = min(edgeTableYSize - 1, rowdest);

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
		float shortestdist = 100000000000000;
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

		// travelFromPrevious is used to figure out the direction he's currently
		// going because if there are multiple path solutions with the same 
		// total distance, then I want to give priority to those solutions that
		// keep him traveling in the same direction, i.e. make him turn the fewest
		// times
		travelFromPrevious = 0;
		// if the node I'm resolving is not the first node in the set ...
		if (shortest.previous != ~0) {
			AStarSearchEntry& lastEntry = totalSet[shortest.previous];
			// then see if he's travel right or left ...
			if(lastEntry.col < shortest.col) travelFromPrevious |= TRAVEL_RIGHT;
			else if(lastEntry.col > shortest.col) travelFromPrevious |= TRAVEL_LEFT;
			// and see if he's traveling up or down
			if(lastEntry.row < shortest.row) travelFromPrevious |= TRAVEL_UP;
			else if(lastEntry.row > shortest.row) travelFromPrevious |= TRAVEL_DOWN;
		}


#define CHECK_EXPAND_OPEN_SET(direction, boundarycondition, rowInc, colInc, travelval)\
	if(n->canGo##direction && boundarycondition){\
			int col = shortest.col + colInc;\
			int row = shortest.row + rowInc;\
			expandable##direction = 1;\
			double distance = 1.0;\
			if(!n->noExtraData) {\
				auto e = edgeTableExtraData.find(shortest.colRow);\
				if (e != edgeTableExtraData.end() && e->second.bonus##direction)\
				distance *= 1.0 - (preferredPathWeightCache * e->second.bonus##direction)/127;\
			}\
			expandOpenSet(row, col, distance, travelval);\
		}

#define CHECK_EXPAND_OPEN_SET_DIAGONAL(vertdirection, hordirection, rowInc, colInc, travelval)\
		if(expandable##vertdirection && expandable##hordirection \
		&& DeRefEdgeTable(shortest.row, shortest.col + colInc).canGo##vertdirection \
			&& DeRefEdgeTable(shortest.row + rowInc, shortest.col).canGo##hordirection) \
		{\
			int col = shortest.col + colInc;\
			int row = shortest.row + rowInc;\
			double distance = 1.4142135623;\
			if(!n->noExtraData) {\
				auto e = edgeTableExtraData.find(shortest.colRow);\
				if (e != edgeTableExtraData.end()) {\
					if(e->second.bonus##vertdirection)\
						distance *= 1.0 - (0.70*preferredPathWeightCache * e->second.bonus##vertdirection)/127;\
					if(e->second.bonus##hordirection)\
						distance *= 1.0 - (0.70*preferredPathWeightCache * e->second.bonus##hordirection)/127;\
				}\
			}\
			expandOpenSet(row, col, distance, travelval);\
		}
		
		CHECK_EXPAND_OPEN_SET(Up, shortest.row < edgetableysize - 1, 1, 0, TRAVEL_UP)
		CHECK_EXPAND_OPEN_SET(Right, shortest.col < edgetablexsize - 1, 0, 1, TRAVEL_RIGHT)
		CHECK_EXPAND_OPEN_SET(Down, shortest.row > 0, -1, 0, TRAVEL_DOWN)
		CHECK_EXPAND_OPEN_SET(Left, shortest.col > 0, 0, -1, TRAVEL_LEFT)

		CHECK_EXPAND_OPEN_SET_DIAGONAL(Up, Right, 1, 1, TRAVEL_UP|TRAVEL_RIGHT)
		CHECK_EXPAND_OPEN_SET_DIAGONAL(Up, Left, 1, -1, TRAVEL_UP|TRAVEL_LEFT)
		CHECK_EXPAND_OPEN_SET_DIAGONAL(Down, Right, -1, 1, TRAVEL_DOWN|TRAVEL_RIGHT)
		CHECK_EXPAND_OPEN_SET_DIAGONAL(Down, Left, -1, -1, TRAVEL_DOWN|TRAVEL_LEFT)
	}


	if (!final) 
		final = &(totalSet[closestIndex]);

	AStarSearchEntry* temp = final;
	std::vector<unsigned int> backwardsList;
	while (1) {
		backwardsList.push_back(temp->colRow);
		if(temp->previous != ~0)
			temp = &(totalSet[temp->previous]);
		else break;
	}

	int nrNodes = backwardsList.size();

	treenode kinematics = te->node_v_kinematics;
	initkinematics(kinematics, xStart, yStart, 0, 0,0,0, 1, 0);

	AStarSearchEntry e, laste;
	laste.colRow = backwardsList[nrNodes - 1];
	double endtime = time();
	if(driveShort) 
		driveShort = round(0.4*xsize(traveler) / nodeWidth);
	for(int i = nrNodes - 2; i >= driveShort; i--)
	{
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

void AStarNavigator::expandOpenSet(int r, int c, float multiplier, int travelVal)
{
	AStarSearchEntry* entry = NULL;
	int closed = 0;
	int totalSetIndex;
	AStarNode* n = &DeRefEdgeTable(r, c);
	// is he already in the total set
	if (!n->notInTotalSet) {
		// if he's in the toal set and he's open, then abort
		if (n->open) 
			return;
		// if he's not in the open set, then 
		AStarSearchEntry hashEntry;
		hashEntry.row = r;
		hashEntry.col = c;
		totalSetIndex = entryHash[hashEntry.colRow];
		entry = &(totalSet[totalSetIndex]);
	}
	float newG = shortest.g + multiplier * nodeWidth;
	/*  Check if the guy is changing directions. If so, I want to increase the distance so it will be a penalty to make turns*/ \
	if(travelFromPrevious != (travelVal)) 
	{
		// add a small penalty if he's turning
		newG += 0.05*nodeWidth;
		// if it's a right angle turn or more, then add more penalty
		if((travelFromPrevious & (travelVal)) == 0)
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


}

double AStarNavigator::aborttravel(TreeNode* traveler, TreeNode* newTS)
{
	//fsnode* mycoupling = tonode(get(first(o(TaskExecuter, traveler).node_v_navigator)));
	//destroyeventsofobject(holder, -1, EVENT_A_STAR_END_TRAVEL, NULL, mycoupling);
	return 0;
}

double AStarNavigator::OnTimerEvent(TreeNode* involved, int code, char* datastr)
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
		if(tasktype == TASKTYPE_LOAD 
			|| tasktype == TASKTYPE_FRLOAD 
			|| tasktype == TASKTYPE_UNLOAD 
			|| tasktype == TASKTYPE_FRUNLOAD) {
			TreeNode* obj = gettaskinvolved(object, 0, 1);
				if(getitemtype(obj) == ITEM_TYPE_CASE)
					setstate(object, WORKER_STATE_CASE_PICKING, WORKER_STATE_PROFILE);
				else setstate(object, WORKER_STATE_PALLET_LOAD_UNLOAD, WORKER_STATE_PROFILE);
		}
		te->onDestinationArrival(0);
	}
	return 0;
}

double AStarNavigator::preDrawFunction()
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

	for (int i = 1; i <= content(barriers); i++) {
		TreeNode* barrier = rank(barriers, i);
		int barriertype = get(rank(barrier, BARRIER_TYPE));
		switch(barriertype)
		{
		case BARRIER_TYPE_SOLID: {
			double x1 = get(rank(barrier, BARRIER_X1));
			double y1 = get(rank(barrier, BARRIER_Y1));
			double x2 = get(rank(barrier, BARRIER_X2));
			double y2 = get(rank(barrier, BARRIER_Y2));

			if(x1 < min[0]) min[0] = x1;
			if(x1 > max[0]) max[0] = x1;
			if(y1 < min[1]) min[1] = y1;
			if(y1 > max[1]) max[1] = y1;
			if(x2 < min[0]) min[0] = x2;
			if(x2 > max[0]) max[0] = x2;
			if(y2 < min[1]) min[1] = y2;
			if(y2 > max[1]) max[1] = y2;
			break;
		}

		case BARRIER_TYPE_DIVIDER:
		case BARRIER_TYPE_ONE_WAY_DIVIDER:
		case BARRIER_TYPE_PREFERRED_PATH: {
			int temprank = BARRIER_X1;
			while(temprank <= content(barrier)) {
				double x = get(rank(barrier, temprank));
				double y = get(rank(barrier, temprank + 1));
				if(x < min[0]) min[0] = x;
				if(x > max[0]) max[0] = x;
				if(y < min[1]) min[1] = y;
				if(y > max[1]) max[1] = y;
				temprank += 2;
			}
			break;
		}
		}
	}
}



	// All Kinds of stuff
}

TreeNode* AStarNavigator::gASN = NULL;
AStarNavigator* AStarNavigator::globalAStarNavigator()
{
	if (objectexists(gASN))
		return &o(AStarNavigator, gASN);

	gASN = node("AStarNavigator", model());
	if (!objectexists(gASN)) {
		gASN = createinstance(node("/?AStarNavigator", library()), model());
		setname(gASN, "AStarNavigator");
	}
	return &o(AStarNavigator, gASN);
}

double AStarNavigator::saveState()
{
	//int sizeneeded = edgetableextradata.getserializesize();
	//bbsetsize(node_v_savededgetableextradata, sizeneeded);
	//edgetableextradata.serialize(bbgetbuffer(node_v_savededgetableextradata));
	return 0;
}
double AStarNavigator::loadState()
{
	//edgetableextradata.deserialize(bbgetbuffer(node_v_savededgetableextradata));
	return 0;
}