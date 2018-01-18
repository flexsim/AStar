#include "Divider.h"
#include "macros.h"
#include "AStarNavigator.h"

namespace AStar {

Divider::Divider()
	: Barrier()
{
	return;
}

const char * Divider::getClassFactory(void)
{
	return "AStar::Divider";
}


void Divider::bind(void)
{
	Barrier::bind();
}

void Divider::init(double nodeWidth, double x1, double y1, double x2, double y2)
{
	// Snap to grid points
	if (!toPreferredPath() && !toBridge()) {
		x1 = floor((x1 + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
		y1 = floor((y1 + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
		x2 = floor((x2 + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
		y2 = floor((y2 + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
	}
	Barrier::init(nodeWidth, x1, y1, x2, y2);
}

bool Divider::getBoundingBox(double& x0, double& y0, double& x1, double& y1)
{
	if (pointList.size() < 2)
		return false;

	getPointCoords(0, x0, y0);
	getPointCoords(1, x1, y1);
	for (int i = 0; i < pointList.size(); i++) {
		double x, y;
		getPointCoords(i, x, y);

		x0 = min(x, x0);
		x1 = max(x, x1);
		y0 = min(y, y0);
		y1 = max(y, y1);
	}

	return true;
}
void Divider::addBarriersToTable(AStarNavigator* nav)
	//AStarNode* edgeTable, 
	//					  std::unordered_map<unsigned int, AStarNodeExtraData>* extraData, 
	//					  double c0, double r0, unsigned int edgeTableXSize, unsigned int edgeTableYSize)
{
	double x = pointList[0]->x;
	double y = pointList[0]->y;

	double c0 = nav->gridOrigin.x;
	double r0 = nav->gridOrigin.y;
	// here I assume the row/column number represents the slot above / right of the
	// corner I am working on 
	int col = (int)round(((x - c0) / nodeWidth) + 0.5);
	int row = (int)round(((y - r0) / nodeWidth) + 0.5);

	double nextX, nextY;
	int nextCol, nextRow;
	for (int i = 0; i < pointList.size() - 1; 
		i++, x = nextX, y = nextY, row = nextRow, col = nextCol) {
		
		nextX = pointList[i + 1]->x;
		nextY = pointList[i + 1]->y;

		// calculate the column and row numbers for that point (again, above/right of the current corner)
		nextCol = (int)round(((nextX - c0) / nodeWidth) + 0.5);
		nextRow = (int)round(((nextY - r0) / nodeWidth) + 0.5);

		// set dx and dy, the differences between the rows and columns
		double dx = nextCol - col;
		double dy = nextRow - row;
		
		if(dy == 0 && dx == 0)
			continue;

		// figure out the unit increment (either -1 or 1) for traversing from the
		// current point to the next point
		int colInc = (int)sign(dx);
		if(colInc == 0) 
			colInc = 1;

		int rowInc = (int)sign(dy);
		if(rowInc == 0) 
			rowInc = 1;

		// prevent divide by zero errors
		if(dx == 0) dx = 0.01;
		// get the slope of the line
		double goalSlope = dy/dx;

		int currCol = col;
		int currRow = row;
		// now step through the line, essentially walking along the edges of the grid tiles
		// under the line, and set the divider by zeroing out the bits on each side of the line
		// I'm walking on
		while(currCol != nextCol || currRow != nextRow) {

			// the way that I essentially move along the line
			// is at each grid point, I do a test step horizontally, 
			// and a test step vertically, and then test the new slope of the line to the 
			// destination for each of those test steps. Whichever line's slope is closest
			// to the actual slope represents the step I want to take.
			int testCol = currCol + colInc;
			int testRow = currRow + rowInc;
			double dxTestCol = nextCol - testCol;
			if(dxTestCol == 0) dxTestCol = 0.01;
			double dxTestRow = nextCol - currCol;
			if(dxTestRow == 0) dxTestRow = 0.01;
			
			double colIncSlope = (nextRow - currRow)/dxTestCol;
			double rowIncSlope = (nextRow - testRow)/dxTestRow;
			
			int nextCurrCol, nextCurrRow;
			if(fabs(colIncSlope - goalSlope) <= fabs(rowIncSlope - goalSlope)) {
				// move over one column
				nextCurrCol = testCol;
				nextCurrRow = currRow;
				
				int modifyCol = min(nextCurrCol, currCol);
				nav->getNode(currRow, modifyCol)->canGoDown = 0;
				nav->getNode(currRow - 1, modifyCol)->canGoUp = 0;
				
			} else {
				nextCurrCol = currCol;
				nextCurrRow = testRow;
				
				int modifyRow = min(nextCurrRow, currRow);
				nav->getNode(modifyRow, currCol)->canGoLeft = 0;
				nav->getNode(modifyRow, currCol - 1)->canGoRight = 0;
			}
			
			currCol = nextCurrCol;
			currRow = nextCurrRow;
		}
	}
}

void Divider::addVertices(Mesh* barrierMesh, float z)
{
	float lightGray[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
	float darkGray[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	if (!isActive) {
		lightGray[0] = 0.4f;
		lightGray[1] = 0.4f;
		lightGray[2] = 0.4f;
		darkGray[0] = 0.4f;
		darkGray[1] = 0.4f;
		darkGray[2] = 0.4f;
		black[0] = 0.4f;
		black[1] = 0.4f;
		black[2] = 0.4f;
	}
	nrVerts = 0;
	meshOffset = barrierMesh->numVerts;

	// Add circles at each node
	const float TWO_PI = 2 * 3.1415926536f;
	int numSides = 20;
	float radius = nodeWidth * 0.15;
	float dTheta = TWO_PI / numSides;

	for (int i = 0; i < pointList.size(); i++) {
		float center[3] = {pointList[i]->x, pointList[i]->y, z + 0.01 / getmodelunit(LENGTH_MULTIPLE)};

		// For each side, draw a triangle
		for (int j = 0; j < numSides - 1; j++) {
			float theta = j * dTheta;
			float x = radius * cos(theta) + center[0];
			float y = radius * sin(theta) + center[1];
			float x2 = radius * cos(theta + dTheta) + center[0];
			float y2 = radius * sin(theta + dTheta) + center[1];
			
			float pos1[3] = {x, y, z};
			float pos2[3] = {x2, y2, z};

#define ABV(vertName, pos, color, activeColor) {\
			int vertName = barrierMesh->addVertex();\
			nrVerts++;\
			if (i == activePointIndex)\
				barrierMesh->setVertexAttrib(vertName, MESH_DIFFUSE4, activeColor);\
			else\
				barrierMesh->setVertexAttrib(vertName, MESH_DIFFUSE4, color);\
			barrierMesh->setVertexAttrib(vertName, MESH_POSITION, pos);\
		}

			ABV(centerVert, center, darkGray, black);
			ABV(vert1, pos1, darkGray, black);
			ABV(vert2, pos2, darkGray, black);

		}

		// Draw the last triangle using first and last coords
		float lastTheta = (numSides - 1) * dTheta;
		float pos2[3] = {radius + center[0], center[1], z};
		float pos1[3] = {radius * cos(lastTheta) + center[0], radius * sin(lastTheta) + center[1], z};
		ABV(centerVert, center, darkGray, black);
		ABV(vert1, pos1, darkGray, black);
		ABV(vert2, pos2, darkGray, black);
#undef ABV
	}

	// For each pair of points, draw a rectangle in between
	float distToRect = 0;// 0.4 * nodeWidth;
	float distToCorner = sqrt(distToRect * distToRect + radius * radius);
	dTheta = atan2(radius, distToRect);
	for (int i = 0; i < pointList.size() - 1; i++) {
		Point* point = pointList[i];
		Point* next = pointList[i + 1];

		float dx = next->x - point->x;
		float dy = next->y - point->y;
		float theta = atan2(dy, dx);
		
		float length = sqrt(dx * dx + dy * dy) - 2 * distToRect;
		if (length <= 0)
			continue;
		float height = 2 * radius;

		// Use the bottomleft corner of the rectangle to get every other corner
		float bottomLeft[3] = {distToCorner * cos(theta - dTheta) + point->x, 
			distToCorner * sin(theta - dTheta) + point->y, z};

		float topLeft[3] = {bottomLeft[0] - height * sin(theta), 
			bottomLeft[1] + height * cos(theta), z};

		float bottomRight[3] = {bottomLeft[0] + length * cos(theta),
			bottomLeft[1] + length * sin(theta), z};

		float topRight[3] = {bottomRight[0] - height * sin(theta),
			bottomRight[1] + height * cos(theta), z};

#define ABV(pos, color) {\
	int theVert = barrierMesh->addVertex();\
	nrVerts++;\
	barrierMesh->setVertexAttrib(theVert, MESH_DIFFUSE4, color);\
	barrierMesh->setVertexAttrib(theVert, MESH_POSITION, pos);\
	}\

#define ABT(pos1, pos2, pos3, color) ABV(pos1, color) ABV(pos2, color) ABV(pos3, color)

		ABT(bottomLeft, topRight, topLeft, lightGray);
		ABT(bottomLeft, bottomRight, topRight, lightGray);

#undef ABT
#undef ABV
	}
}

double Divider::onClick(treenode view, int clickCode, double x, double y)
{
	if (clickCode == LEFT_PRESS) {
		// If creating, don't try to change the active node or the mode
		if (mode & BARRIER_MODE_CREATE) {
			if (modeleditmode(-1) == 0) {
				o(AStarNavigator, ownerobject(holder)).addCreateRecord(view, this);
				mode = 0;
			}
			return 0;
		}

		// If the click is on a node, make that the active node
		int clickedIndex = -1;
		for (int i = 0; i < pointList.size(); i++) {
			applicationcommand("addundotracking", view, node("x", pointList[i]->holder));
			applicationcommand("addundotracking", view, node("y", pointList[i]->holder));

			double pointX = pointList[i]->x;
			double pointY = pointList[i]->y;
			double dx = x - pointX;
			double dy = y - pointY;

			double radius = nodeWidth * 0.15;
			if (sqrt(dx * dx + dy * dy) <= radius) {
				clickedIndex = i;
				break;
			}
		}

		if (clickedIndex > -1) {
			activePointIndex = clickedIndex;
			mode = BARRIER_MODE_POINT_EDIT;
		
		} else {
			activePointIndex = pointList.size();
			mode = BARRIER_MODE_MOVE;
		}
	}

	if (clickCode == LEFT_RELEASE) {
		// If creating, make a new point, and make it the active one
		if (mode & BARRIER_MODE_CREATE) {
			addPoint(x, y);
			activePointIndex = pointList.size() - 1;
		} else {
			activePointIndex = pointList.size();
			mode = 0;
		}
	}

	if (clickCode == RIGHT_RELEASE) {
		// Right click -> abort barrier creation
		if ((mode & BARRIER_MODE_CREATE)) {
			pointList.remove(pointList.size() - 1);
			mode = 0;
			activePointIndex = pointList.size();
			if (pointList.size() < 2)
				destroyobject(holder);
			else
				o(AStarNavigator, ownerobject(holder)).addCreateRecord(view, this);
		}
	}

	return 0;
}

double Divider::onMouseMove(const Vec3& pos, const Vec3& diff)
{
	if (mode & BARRIER_MODE_POINT_EDIT) {
		Point* activePoint = pointList[(int)activePointIndex];
		// Snap to grid points
		if (!toPreferredPath() && !toBridge()) {
			activePoint->x = floor((pos.x + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
			activePoint->y = floor((pos.y + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
		}
		else {
			activePoint->x += diff.x;
			activePoint->y += diff.y;
		}
		if (toBridge())
			activePoint->z += diff.z;
	}
	else if (mode & BARRIER_MODE_MOVE) {
		for (int i = 0; i < pointList.size(); i++) {
			pointList[i]->x += diff.x;
			pointList[i]->y += diff.y;
			if (toBridge())
				pointList[i]->z += diff.z;
		}
	}

	return 0;
}

}