#include "AStarNavigator.h"
#include "macros.h"

AStarNavigator::AStarNavigator()
	// TODO: Initialize entryhash, edgetableextradata
{
	edgeTable = NULL;
	xOffset = 0;
	yOffset = 0;
	edgeTableXSize = 0;
	edgetTableYSize = 0;
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
	bindVariable(openSetHeap);
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

double AStarNavigator::navigateto(TreeNode* traveler, TreeNode* destination, double endSpeed)
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

	return navigatetoloc(traveler, xDest, yDest, endSpeed, driveShort);
}

double AStarNavigator::navigatetoloc(TreeNode* traveler, double x, double y, double endSpeed, int driveShort)
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

	return 0;
}

void AStarNavigator::expandOpenSet(int r, int c, float multiplier, int travelVal)
{
	AStarSearchEntry* entry = NULL;
	int closed = 0;
	int totatSetIndex;
	AStarNode* n = &DeRefEdgeTable(r, c);
	if (!n->notInTotalSet) {
		if (n->open) return;
		AStarSearchEntry hashEntry;
		hashEntry.row = r;
		hashEntry.col = c;
		//TODO: a Hash line totalSetIndex = entryHash[hashentr.colRow];
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

double AStarNavigator::predrawfunction()
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
	double min[2] = {100000000.0,1000000000.0};
	double max[2] = {-100000000.0,-1000000000.0};
	// WarehouseManager?

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

double AStarNavigator::savestate()
{
	//int sizeneeded = edgetableextradata.getserializesize();
	//bbsetsize(node_v_savededgetableextradata, sizeneeded);
	//edgetableextradata.serialize(bbgetbuffer(node_v_savededgetableextradata));
	return 0;
}
double AStarNavigator::loadstate()
{
	//edgetableextradata.deserialize(bbgetbuffer(node_v_savededgetableextradata));
	return 0;
}