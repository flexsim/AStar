#include "AStarNavigator.h"
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
	bindVariable(barriers);
	//barrierList.init(barriers);
}

double AStarNavigator::onReset()
{
	while (content(node_v_activetravelmembers) > 0)
		transfernode(last(node_v_activetravelmembers), node_v_travelmembers);

	edgeTableExtraData.clear();
	buildEdgeTable();
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
	int editmode = editMode;
	int istravelmode = (
		editmode == EDITMODE_PREFERRED_PATH
		|| editmode == EDITMODE_DIVIDER
		|| editmode == EDITMODE_ONE_WAY_DIVIDER
		|| editmode == EDITMODE_SOLID_BARRIER
		);
	int drawmode = (int)drawMode;
	if(istravelmode) drawmode = ~0;
	if(drawmode == 0) return 0;

	glScalef(1.0/b_spatialsx, 1.0/b_spatialsy, 1.0/b_spatialsz);
	glTranslatef(-b_spatialx, -b_spatialy, -b_spatialz);
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glColor3f(1,0,0);

	if(!pickingmode && (drawmode & ASTAR_DRAW_MODE_GRID))
	{
		glColor3f(0.8f,0.8f,0.0f);
		glBegin(GL_LINES);
		for(int i = 0; i < edgeTableYSize; i++)
		{
			for(int j = 0; j < edgeTableXSize; j++)
			{
				AStarNode* n = &(DeRefEdgeTable(i,j));
				AStarSearchEntry s;
				s.col = j;
				s.row = i;
				AStarNodeExtraData* e = NULL;
				if(!n->noExtraData)
					e = &edgeTableExtraData[s.colRow];
				double x = (xOffset + j + 0.5) * nodeWidth;
				double y = (yOffset + i + 0.5) * nodeWidth;
				glColor3f(0.8f,0.8f,0.0f);
				if(n->canGoUp) 	{
					if(e && e->bonusUp) 
						glColor3ub(0, e->bonusUp, 0);
					glVertex3d(x,y,0.1);
					glVertex3d(x,y+0.25*nodeWidth,0.1);
				}
				glColor3f(0.8f,0.8f,0.0f);
				if(n->canGoDown) {
					if(e && e->bonusDown) 
						glColor3ub(0, e->bonusDown, 0);
					glVertex3d(x,y,0.1);
					glVertex3d(x,y-0.25*nodeWidth,0.1);
				}
				glColor3f(0.8f,0.8f,0.0f);
				if(n->canGoRight) {
					if(e && e->bonusRight) 
						glColor3ub(0, e->bonusRight, 0);
					glVertex3d(x,y,0.1);
					glVertex3d(x+0.25*nodeWidth,y,0.1);
				}
				glColor3f(0.8f,0.8f,0.0f);
				if(n->canGoLeft) {
					if(e && e->bonusLeft) 
						glColor3ub(0, e->bonusLeft, 0);
					glVertex3d(x,y,0.1);
					glVertex3d(x-0.25*nodeWidth,y,0.1);
				}
				if(!n->notInTotalSet) {
					mpt("Grid error at x ");mpd(j);mpt(" y ");mpd(i);mpr();
					glVertex3d(x,y,0.1);
					glVertex3d(x + 0.25 * nodeWidth, y + 0.25 * nodeWidth, 0.1);
				}
			}
		}
		glEnd();
	}

	#define SELECTIONMODE_MOUSEMOVE 10
	#define SELECTIONMODE_MOUSEDOWNLEFT 11
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

	if(drawmode&ASTAR_DRAW_MODE_BARRIERS)
	{
		glColor3d(0,0,0);
		glPointSize(8);
		for(int i = 1; i <= content(barriers); i++)
		{
			TreeNode* barrier = rank(barriers, i);
			int barriertype = (int)get(rank(barrier, BARRIER_TYPE));

			double x1 = get(rank(barrier, BARRIER_X1));
			double y1 = get(rank(barrier, BARRIER_Y1));
			double x2 = get(rank(barrier, BARRIER_X2));
			double y2 = get(rank(barrier, BARRIER_Y2));

			switch(barriertype)
			{
				case BARRIER_TYPE_ONE_WAY_DIVIDER:
				case BARRIER_TYPE_DIVIDER:
				case BARRIER_TYPE_PREFERRED_PATH:
				{
					glPushMatrix();
					glTranslatef(x1, y1, 0);
					double x = x1, y = y1;
					double nextx, nexty;
					int temprank = BARRIER_X2;
					while(content(barrier) >= temprank)
					{
						nextx = get(rank(barrier, temprank));
						nexty = get(rank(barrier, temprank+1));
						double dx = nextx - x;
						double dy = nexty - y;

						if(pickingmode) setpickingdrawfocus(view, holder, PICK_DIVIDER_NODE, rank(barrier, temprank - 2));
						glColor3d(0,0,0);
						glBegin(GL_POINTS);
							glVertex3d(0, 0, 0);
						glEnd();

						if(pickingmode) setpickingdrawfocus(view, holder, PICK_DIVIDER_EDGE, rank(barrier, temprank - 2));
						
						double rz = radianstodegrees(atan2(dy, dx));
						glPushMatrix();
						glRotated(rz, 0,0,1);
						double dist = sqrt(dx*dx + dy*dy);
						glBegin(GL_QUADS);

						switch(barriertype)
						{
						case BARRIER_TYPE_DIVIDER:
							if(dist > nodeWidth)
							{
								glVertex3d(0.5*nodeWidth, -0.25*nodeWidth, 0);
								glVertex3d(dist-0.5*nodeWidth, -0.25*nodeWidth, 0);
								glVertex3d(dist-0.5*nodeWidth, 0.25*nodeWidth, 0);
								glVertex3d(0.5*nodeWidth, 0.25*nodeWidth, 0);
							}
							break;

						case BARRIER_TYPE_ONE_WAY_DIVIDER:
							if(dist > 2*nodeWidth)
							{
								int nrarrows = (int)(dist / (2*nodeWidth) - 1);
								double tempx = 0.5*(dist - (nrarrows*2*nodeWidth));
								double startx = tempx;
								glColor3d(0.1,0.1,0.1);
								glVertex3d(0.5*nodeWidth, -0.25*nodeWidth, 0);
								glVertex3d(tempx, -0.25*nodeWidth, 0);
								glVertex3d(tempx, 0.25*nodeWidth, 0);
								glVertex3d(0.5*nodeWidth, 0.25*nodeWidth, 0);
								
								glVertex3d(dist - tempx, -0.25*nodeWidth, 0);
								glVertex3d(dist - 0.5*nodeWidth, -0.25*nodeWidth, 0);
								glVertex3d(dist - 0.5*nodeWidth, 0.25*nodeWidth, 0);
								glVertex3d(dist - tempx, 0.25*nodeWidth, 0);
								while(tempx < dist - 2*nodeWidth)
								{
									glColor3d(0.1,0.1,0.1);
									
									glVertex3d(tempx, -0.25*nodeWidth, 0);
									glVertex3d(tempx + 0.5*nodeWidth, -0.25*nodeWidth, 0);
									glVertex3d(tempx + 1*nodeWidth, 0.25*nodeWidth, 0);
									glVertex3d(tempx, 0.25*nodeWidth, 0);
									
									glVertex3d(tempx + nodeWidth, 0.25*nodeWidth, 0);
									glVertex3d(tempx + 1.5*nodeWidth, -0.25*nodeWidth, 0);
									glVertex3d(tempx + 2*nodeWidth, -0.25*nodeWidth, 0);
									glVertex3d(tempx + 2*nodeWidth, 0.25*nodeWidth, 0);

									if(barriertype == BARRIER_TYPE_ONE_WAY_DIVIDER)
										glColor3d(0.2,0.8,0.2);
									else glColor3d(0.1, 0.1,0.1);

									glVertex3d(tempx + 0.5*nodeWidth, -0.25*nodeWidth, 0);
									glVertex3d(tempx + 0.5*nodeWidth, -0.25*nodeWidth, 0);
									glVertex3d(tempx + 1.5*nodeWidth, -0.25*nodeWidth, 0);
									glVertex3d(tempx + 1*nodeWidth, 0.25*nodeWidth, 0);

									tempx += 2*nodeWidth;
								}
							}
							break;

						case BARRIER_TYPE_PREFERRED_PATH:
							if(dist > 2*nodeWidth)
							{
								int nrarrows = (int)(dist / (2*nodeWidth) - 1);
								double tempx = 0.5*(dist - (nrarrows*2*nodeWidth));
								double startx = tempx;
								double colors[2][3] = {0.1,0.1,0.1, 0.2, 0.8, 0.2};
								int colorindex = 1;

								glColor3d(0.1,0.1,0.1);
								while(tempx < dist - 2*nodeWidth)
								{
									glColor3dv(colors[colorindex]);
									double offset = nodeWidth;
									
									glVertex3d(tempx, -0.25*nodeWidth, 0);
									glVertex3d(tempx + offset, -0.25*nodeWidth, 0);
									glVertex3d(tempx + 0.5*nodeWidth + offset, 0, 0);
									glVertex3d(tempx + 0.5*nodeWidth, 0, 0);
									
									glVertex3d(tempx + 0.5*nodeWidth, 0, 0);
									glVertex3d(tempx + 0.5*nodeWidth + offset, 0, 0);
									glVertex3d(tempx + offset, 0.25*nodeWidth, 0);
									glVertex3d(tempx, 0.25*nodeWidth, 0);

									tempx += 2*offset;
									//colorindex = !colorindex;
								}
							}
							break;
						}
						
						glEnd();
						glColor3d(0,0,0);
						glPopMatrix();
						glTranslatef(dx, dy, 0);

						x = nextx;
						y = nexty;
						temprank += 2;
					}

					if(pickingmode) setpickingdrawfocus(view, holder, PICK_DIVIDER_NODE, prev(last(barrier)));
					glBegin(GL_POINTS);
						glVertex3d(0, 0, 0);
					glEnd();
					glPopMatrix();
					break;
				}

				case BARRIER_TYPE_SOLID:
				{
					glColor3d(0.1, 0.1,0.1);
					if(pickingmode) setpickingdrawfocus(view, holder, PICK_SOLID_BARRIER, barrier);
					glBegin(GL_QUADS);
					double xmin = min(x1, x2);
					double xmax = max(x1, x2);
					double ymin = min(y1, y2);
					double ymax = max(y1, y2);
					glVertex3d(xmin, ymin, 0);
					glVertex3d(xmax, ymin, 0);
					glVertex3d(xmax, ymax, 0);
					glVertex3d(xmin, ymax, 0);
					glEnd();
					break;
				}
			}
		}
	}

	glPopAttrib();
	return 0;
}

double AStarNavigator::onDrag(TreeNode* view)
{
	int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, 0);
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
	default:
		inc(spatialx(holder), dx);
		inc(spatialy(holder), dy);
		break;
	}
	return 1;
}

double AStarNavigator::dragConnection(TreeNode* connectTo, char keyPressed, unsigned int classType)
{
	if (!objectexists(connectTo))
		return 0;

	if (!isclasstype(connectTo, CLASSTYPE_TASKEXECUTER))
		return 0;

	TreeNode* navigatorNode = o(TaskExecuter, connectTo).node_v_navigator;
	TreeNode* theNavigator = tonode(get(first(navigatorNode)));
	if (theNavigator == holder)
		return 0;

	TreeNode* travelMembers = node_v_travelmembers;

	switch(keyPressed) {
	case 'A':
		clearcontents(navigatorNode);
		createcoupling(navigatorNode, travelMembers);
		break;
	}

	return 0;
}

double AStarNavigator::onDestroy(TreeNode* view)
{
	if(objectexists(view))
	{
		int picktype = (int)getpickingdrawfocus(view, PICK_TYPE,0);
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
		default:
			destroyobject(holder);
			break;
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
		
		CHECK_EXPAND_OPEN_SET(Up, shortest.row < edgeTableYSize - 1, 1, 0, TRAVEL_UP)
		CHECK_EXPAND_OPEN_SET(Right, shortest.col < edgeTableXSize - 1, 0, 1, TRAVEL_RIGHT)
		CHECK_EXPAND_OPEN_SET(Down, shortest.row > 0, -1, 0, TRAVEL_DOWN)
		CHECK_EXPAND_OPEN_SET(Left, shortest.col > 0, 0, -1, TRAVEL_LEFT)

		CHECK_EXPAND_OPEN_SET_DIAGONAL(Up, Right, 1, 1, TRAVEL_UP|TRAVEL_RIGHT)
		CHECK_EXPAND_OPEN_SET_DIAGONAL(Up, Left, 1, -1, TRAVEL_UP|TRAVEL_LEFT)
		CHECK_EXPAND_OPEN_SET_DIAGONAL(Down, Right, -1, 1, TRAVEL_DOWN|TRAVEL_RIGHT)
		CHECK_EXPAND_OPEN_SET_DIAGONAL(Down, Left, -1, -1, TRAVEL_DOWN|TRAVEL_LEFT)
	}


	if (!final) 
		final = &(totalSet[closestIndex]);

	unsigned int startPrevVal =  ~((unsigned int)0);
	AStarSearchEntry* temp = final;
	std::vector<unsigned int> backwardsList;
	while (1) {
		backwardsList.push_back(temp->colRow);
		if(temp->previous != startPrevVal)
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

	if (content(barriers) == 0) {
		if (edgeTable)
			delete [] edgeTable;
		edgeTable = 0;
		return;
	}

	for (int i = 1; i <= content(barriers); i++) {
		TreeNode* barrier = rank(barriers, i);
		int barriertype = (int)get(rank(barrier, BARRIER_TYPE));
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

	xOffset = (int)(floor(min[0] / nodeWidth) - surroundDepth);
	yOffset = (int)(floor(min[1] / nodeWidth) - surroundDepth);

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

	for(int i = 1; i <= content(barriers); i++)
	{
		TreeNode* barrier = rank(barriers, i);
		int barriertype = (int)get(rank(barrier, BARRIER_TYPE));
		switch(barriertype)
		{
			case BARRIER_TYPE_SOLID:
			{
				double x1 = get(rank(barrier, BARRIER_X1));
				double y1 = get(rank(barrier, BARRIER_Y1));
				double x2 = get(rank(barrier, BARRIER_X2));
				double y2 = get(rank(barrier, BARRIER_Y2));
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

				break;
			}

			case BARRIER_TYPE_DIVIDER:
			case BARRIER_TYPE_ONE_WAY_DIVIDER:
			case BARRIER_TYPE_PREFERRED_PATH:
			{
				double x = get(rank(barrier, BARRIER_X1));
				double y = get(rank(barrier, BARRIER_Y1));
				// here I assume the row/column number represents the slot above / right of the
				// corner I am working on for dividers, but the tile itself for preferred paths
				int col = (int)round((x - col0xloc) / nodeWidth);
				int row = (int)round((y - row0yloc) / nodeWidth);
				if(barriertype != BARRIER_TYPE_PREFERRED_PATH) {
					if(x > col0xloc + col * nodeWidth) col++;
					if(y > row0yloc + row * nodeWidth) row++;
				}
				
				double nextx, nexty;
				int nextcol, nextrow;
				for(int temprank = BARRIER_X2; temprank <= content(barrier);
					x=nextx, y=nexty, col=nextcol, row=nextrow, temprank+=2) {
					// get the x/y location of the next barrier point
					nextx = get(rank(barrier, temprank));
					nexty = get(rank(barrier, temprank + 1));
					// calculate the column and row numbers for that point (again, above/right of the current corner)
					nextcol = (int)round((nextx - col0xloc) / nodeWidth);
					nextrow = (int)round((nexty - row0yloc) / nodeWidth);
					if(barriertype != BARRIER_TYPE_PREFERRED_PATH) {
						if(nextx > col0xloc + nextcol * nodeWidth) nextcol++;
						if(nexty > row0yloc + nextrow * nodeWidth) nextrow++;
					}

					// set dx and dy, the differences between the rows and columns
					double dx = nextcol - col;
					double dy = nextrow - row;

					if(dy == 0 && dx == 0)
						continue;

					// calculate the weight values for preferred paths.
					int horizontalweight = (int)(127 * dx / (fabs(dx) + fabs(dy)));
					int verticalweight = (int)(127 * dy / (fabs(dx) + fabs(dy)));

					// figure out the unit increment (either -1 or 1) for traversing from the
					// current point to the next point
					int colinc = (int)sign(dx);
					if(colinc == 0) colinc = 1;
					int rowinc = (int)sign(dy);
					if(rowinc == 0) rowinc = 1;

					// prevent divide by zero errors
					if(dx == 0) dx = 0.01;
					// get the slope of the line
					double goalslope = dy/dx;

					int curcol = col;
					int currow = row;
					// now step through the line, essentially walking along the edges of the grid tiles
					// under the line, and set the divider by zeroing out the bits on each side of the line
					// I'm walking on
					while(curcol != nextcol || currow != nextrow) {
						// If I'm traversing a preferred path, then I need to set the weighting values on 
						// the up/down/left/right of the path
						if(barriertype == BARRIER_TYPE_PREFERRED_PATH)	{
							AStarSearchEntry e;
							e.col = curcol;
							e.row = currow;
							AStarNodeExtraData * extra;
							auto extraIter = edgeTableExtraData.find(e.colRow);
							if(extraIter == edgeTableExtraData.end()) {
								extra = &(edgeTableExtraData[e.colRow]);
								memset(extra, 0, sizeof(AStarNodeExtraData));
								extra->colRow = e.colRow;
								DeRefEdgeTable(e.row, e.col).noExtraData = 0;
							} else {
								extra = &(extraIter->second);
							}
							extra->bonusRight = (char)maxof(-128,minof(127, extra->bonusRight + horizontalweight));
							extra->bonusLeft = (char)maxof(-128,minof(127, extra->bonusLeft - horizontalweight));
							extra->bonusUp = (char)maxof(-128,minof(127, extra->bonusUp + verticalweight));
							extra->bonusDown = (char)maxof(-128,minof(127, extra->bonusDown - verticalweight));
						}

						// the way that I essentially move along the line
						// is at each grid point, I do a test step horizontally, 
						// and a test step vertically, and then test the new slope of the line to the 
						// destination for each of those test steps. Whichever line's slope is closest
						// to the actual slope represents the step I want to take.
						int testcol = curcol+colinc;
						int testrow = currow+rowinc;
						double dxtestcol = nextcol - testcol;
						if(dxtestcol == 0) dxtestcol = 0.01;
						double dxtestrow = nextcol - curcol;
						if(dxtestrow == 0) dxtestrow = 0.01;

						double colincslope = (nextrow - currow)/dxtestcol;
						double rowincslope = (nextrow - testrow)/dxtestrow;

						int nextcurcol, nextcurrow;
						if(fabs(colincslope - goalslope) <= fabs(rowincslope - goalslope))
						{
							// move over one column
							nextcurcol = testcol;
							nextcurrow = currow;
							if(barriertype != BARRIER_TYPE_PREFERRED_PATH)
							{
								int modifycol = min(nextcurcol, curcol);
								if(barriertype == BARRIER_TYPE_DIVIDER || dx > 0)
									DeRefEdgeTable(currow, modifycol).canGoDown = 0;
								if(barriertype == BARRIER_TYPE_DIVIDER || dx < 0)
									DeRefEdgeTable(currow-1, modifycol).canGoUp = 0;
							}
						}
						else
						{
							nextcurcol = curcol;
							nextcurrow = testrow;
							if(barriertype != BARRIER_TYPE_PREFERRED_PATH)
							{
								int modifyrow = min(nextcurrow, currow);
								if(barriertype == BARRIER_TYPE_DIVIDER || dy < 0)
									DeRefEdgeTable(modifyrow, curcol).canGoLeft = 0;
								if(barriertype == BARRIER_TYPE_DIVIDER || dy > 0)
									DeRefEdgeTable(modifyrow, curcol - 1).canGoRight = 0;
							}
						}

						curcol = nextcurcol;
						currow = nextcurrow;
					}
				}
			}
		}
	}
}

// implement global astar navigator accessor
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

visible void AStarNavigator_setEditMode(FLEXSIMINTERFACE)
{
	int mode = (int)parval(1);
	if (mode < 0)
		mode = 0;
	AStarNavigator::editMode = mode;
}
