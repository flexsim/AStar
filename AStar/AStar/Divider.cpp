#include "Divider.h"
#include "macros.h"

const char * Divider::getClassFactory(void)
{
	return "AStar::Divider";
}


void Divider::bind(void)
{
	Barrier::bind();
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
void Divider::modifyTable(AStarNode* edgeTable, double c0, double r0,
		unsigned int edgeTableXSize, unsigned int edgeTableYSize)
{
	
}

void Divider::addVertices(Mesh* barrierMesh, float z)
{
	float gray[3] = {0.4f, 0.4f, 0.4f};
	float black[3] = {0.4f, 0.4f, 0.4f};
	if (isActive) {
		black[0] += 0.2f;
		black[1] += 0.2f;
		black[2] += 0.2f;
		gray[0] += 0.3f;
		gray[1] += 0.3f;
		gray[2] += 0.3f;
	}
	nrVerts = 0;
	meshOffset = barrierMesh->nrVerts;

	// Add circles at each node
	const float TWO_PI = 2 * 3.1415926536f;
	int numSides = 20;
	float radius = nodeWidth * 0.3;
	float dTheta = TWO_PI / numSides;

	for (int i = 0; i < pointList.size(); i++) {
		float center[3] = {pointList[i]->x, pointList[i]->y, z};

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
				barrierMesh->setVertexAttrib(vertName, MESH_EMISSIVE, activeColor);\
			else\
				barrierMesh->setVertexAttrib(vertName, MESH_EMISSIVE, color);\
			barrierMesh->setVertexAttrib(vertName, MESH_POSITION, pos);\
		}

			ABV(centerVert, center, black, gray);
			ABV(vert1, pos1, black, gray);
			ABV(vert2, pos2, black, gray);

		}

		// Draw the last triangle using first and last coords
		float lastTheta = (numSides - 1) * dTheta;
		float pos2[3] = {radius + center[0], center[1], z};
		float pos1[3] = {radius * cos(lastTheta) + center[0], radius * sin(lastTheta) + center[1], z};
		ABV(centerVert, center, black, gray);
		ABV(vert1, pos1, black, gray);
		ABV(vert2, pos2, black, gray);
#undef ABV
	}

	// For each pair of points, draw a rectangle in between
	float distToRect = 0.6 * nodeWidth;
	float distToCorner = sqrt(distToRect * distToRect + radius * radius);
	dTheta = atan2(radius, distToRect);
	for (int i = 0; i < pointList.size() - 1; i++) {
		Point* point = pointList[i];
		Point* next = pointList[i + 1];

		float dx = next->x - point->x;
		float dy = next->y - point->y;
		float theta = atan2(dy, dx);
		
		float length = sqrt(dx * dx + dy * dy) - 2 * distToRect;
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
	barrierMesh->setVertexAttrib(theVert, MESH_EMISSIVE, color);\
	barrierMesh->setVertexAttrib(theVert, MESH_POSITION, pos);\
	}\

#define ABT(pos1, pos2, pos3, color) ABV(pos1, color) ABV(pos2, color) ABV(pos3, color)

		ABT(bottomLeft, topRight, topLeft, black);
		ABT(bottomLeft, bottomRight, topRight, black);

#undef ABT
#undef ABV
	}
}

double Divider::onClick(int clickCode, double x, double y)
{
	if (clickCode == LEFT_PRESS) {

		// If creating, don't try to change the active node or the mode
		if (mode & BARRIER_MODE_CREATE) {
			return 0;
		}

		// If the click is on a node, make that the active node
		int clickedIndex = -1;
		for (int i = 0; i < pointList.size(); i++) {
			double pointX = pointList[i]->x;
			double pointY = pointList[i]->y;
			double dx = x - pointX;
			double dy = y - pointY;

			double radius = nodeWidth * 0.3;
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
		if (activePointIndex > 0) {
			pointList.remove(activePointIndex);
		}
		if ((mode & BARRIER_MODE_CREATE)) {
			modeleditmode(0);
			if (pointList.size() < 2)
				destroyobject(holder);
		}
	}

	return 0;
}

double Divider::onMouseMove(double x, double y, double dx, double dy)
{
	if (mode & BARRIER_MODE_MOVE) {
		for (int i = 0; i < pointList.size(); i++) {
			pointList[i]->x += dx;
			pointList[i]->y += dy;
		}
	}

	if (mode & BARRIER_MODE_POINT_EDIT) {
		Point* activePoint = pointList[(int)activePointIndex];
		activePoint->x = x;
		activePoint->y = y;

		double radius = nodeWidth * 0.6;
		double x, y;
		getPointCoords(activePointIndex, x, y);
		// Don't get closer than nodeWidth to a neighbor
		// Most nodes have a lesser neighbor
		if (activePointIndex > 0) {
			int prevIndex = (int)activePointIndex - 1;
			Point* prev = pointList[prevIndex];
			double prevX, prevY;
			getPointCoords(prevIndex, prevX, prevY);

			double dx = prevX - x;
			double dy = prevY - y;
			if (sqrt(dx * dx + dy * dy) < radius) {
				double theta = atan2(dy, dx);
				x = prevX + cos(theta) * radius;
				y = prevY + sin(theta) * radius;
				setPointCoords(activePointIndex, x, y);
			}
		}

		if (activePointIndex < pointList.size() - 1) {
			int nextIndex = (int)activePointIndex + 1;
			Point* next = pointList[nextIndex];
			double nextX, nextY;
			getPointCoords(nextIndex, nextX, nextY);

			double dx = nextX - x;
			double dy = nextY - y;
			if (sqrt(dx * dx + dy * dy) < radius) {
				double theta = atan2(dy, dx);
				x = nextX + cos(theta) * radius;
				y = nextY + sin(theta) * radius;
				setPointCoords(activePointIndex, x, y);
			}
		}
	}

	return 0;
}
