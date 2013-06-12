#include "Barrier.h"
#include "AStarNavigator.h"
#include "macros.h"

Barrier::Barrier()
{
	return;
}

Barrier::~Barrier()
{
	return;
}

const char * Barrier::getClassFactory(void)
{
	return "AStar::Barrier";
}

void Barrier::bind(void)
{
	SimpleDataType::bind();
	
	bindNumber(meshOffset);
	bindNumber(nrVerts);
	bindNumber(activePointIndex);
	bindNumber(mode);

	bindSubNode(points, 0);
	pointList.init(points);
}

void Barrier::init(double x1, double y1, double x2, double y2)
{
	addPoint(x1, y1);
	addPoint(x2, y2);
}

bool Barrier::getBoundingBox(double& x0, double& y0, double& x1, double& y1)
{
	if (pointList.size() < 2) 
		return false;
	
	getPointCoords(0, x0, y0);
	getPointCoords(1, x1, y1);

	double xmin = min(x0, x1);
	double xmax = max(x0, x1);
	double ymin = min(y0, y1);
	double ymax = max(y0, y1);

	x0 = xmin;
	x1 = xmax;
	y0 = ymin;
	y1 = ymax;
	return true;
}

void Barrier::modifyTable(AStarNode* edgeTable, double nodeWidth, 
						  double c0, double r0, unsigned int edgeTableXSize, unsigned int edgeTableYSize)
{
	double xmin, ymin, xmax, ymax;
	if (!getBoundingBox(xmin, ymin, xmax, ymax))
		return;

	int colleft = (int)round((xmin - c0) / nodeWidth);
	int rowbottom = (int)round((ymin - r0) / nodeWidth);
	int colright = (int)round((xmax - c0) / nodeWidth);
	int rowtop = (int)round((ymax - r0) / nodeWidth);
	for(int row = rowbottom; row <= rowtop; row++) {
		AStarNode * left = &(DeRefEdgeTable(row, colleft-1));
		left->canGoRight = 0;
		AStarNode * right = &(DeRefEdgeTable(row, colright+1));
		right->canGoLeft = 0;
	}

	for(int col = colleft; col <= colright; col++) {
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

void Barrier::addVertices(Mesh* barrierMesh, float z)
{
	meshOffset = 0;
	nrVerts = 0;

	double xmin, ymin, xmax, ymax;
	if (!getBoundingBox(xmin, ymin, xmax, ymax))
		return;

	double width = xmax - xmin;
	double height = ymax - ymin;

	meshOffset = barrierMesh->nrVerts;

	float black[3] = {0.0f, 0.0f, 0.0f};
	if (isActive) {
		black[0] += 0.4f;
		black[1] += 0.4f;
		black[2] += 0.4f;
	}
	float blue[3] = {0.0f, 0.0f, 0.8f};

	float bottomLeft[3] = {xmin, ymin, z};
	float topLeft[3] = {xmin, ymax, z};
	float topRight[3] = {xmax, ymax, z};
	float bottomRight[3] = {xmax, ymin, z};

	float triangleEdgeLength = sqrt(width * width + height * height) / 10.0;
	float triangleBottomRight[3] = {xmin + triangleEdgeLength, ymin, z};
	float triangleBottomTop[3] = {xmin, ymin + triangleEdgeLength, z};
	float triangleTopLeft[3] = {xmax - triangleEdgeLength, ymax, z};
	float triangleTopBottom[3] = {xmax, ymax - triangleEdgeLength, z};

#define ABV(point, color) {\
		int newVertex = barrierMesh->addVertex();\
		barrierMesh->setVertexAttrib(newVertex, MESH_POSITION, point);\
		barrierMesh->setVertexAttrib(newVertex, MESH_EMISSIVE, color);\
		nrVerts++;\
	}\

#define ABT(p1, p2, p3, color) ABV(p1, color) ABV(p2, color) ABV(p3, color)

	ABT(triangleTopBottom, topRight, triangleTopLeft, blue);
	ABT(triangleBottomRight, triangleBottomTop, bottomLeft, blue);
	ABT(triangleBottomTop, triangleTopLeft, topLeft, black);
	ABT(triangleBottomRight, triangleTopLeft, triangleBottomTop, black);
	ABT(triangleBottomRight, triangleTopBottom, triangleTopLeft, black);
	ABT(triangleBottomRight, bottomRight, triangleTopBottom, black);

#undef ABT
#undef ABV
}

double Barrier::onClick(int clickCode, double x, double y)
{
	if (clickCode == LEFT_PRESS) {

		// If already editing, don't do anything on press
		if (mode == BARRIER_MODE_POINT_EDIT) {
			return 0;
		}

		// if the user clicked on a blue triangle, set the mode and active point
		Point* bottomLeftPoint = pointList[0];
		double blx = bottomLeftPoint->x;
		double bly = bottomLeftPoint->y;
		
		// Transform click to barrier coords
		x -= blx;
		y -= bly;

		double xmin, ymin, xmax, ymax;
		if (!getBoundingBox(xmin, ymin, xmax, ymax))
			return 0;

		double width = xmax - xmin;
		double height = ymax - ymin;
		float triangleEdgeLength = sqrt(width * width + height * height) / 20.0;

		// If the click is in the bottom left corner
		if (x + y <= triangleEdgeLength) {
			activePointIndex = 0;
			mode = BARRIER_MODE_POINT_EDIT;
		
		// If the click is in the top right corner
		} else if (x + y >= width + height - triangleEdgeLength) {
			activePointIndex = 1;
			mode = BARRIER_MODE_POINT_EDIT;
		
		} else {
			activePointIndex = 0;
			mode = BARRIER_MODE_MOVE;
		}
	}

	if (clickCode == LEFT_RELEASE) {
		if (mode == BARRIER_MODE_POINT_EDIT) {
			activePointIndex = 0;
			mode = 0;
		}
	}

	if (clickCode == RIGHT_RELEASE) {
		// Right click -> abort barrier creation
		if (mode == BARRIER_MODE_POINT_EDIT) {
			destroyobject(holder);
		}
	}

	return 0;
}

double Barrier::onMouseMove(double dx, double dy)
{
	if (mode == BARRIER_MODE_POINT_EDIT) {
		Point* activePoint = pointList[(int)activePointIndex];
		activePoint->x += dx;
		activePoint->y += dy;
	}

	if (mode == BARRIER_MODE_MOVE) {
		for (int i = 0; i < pointList.size(); i++) {
			pointList[i]->x += dx;
			pointList[i]->y += dy;
		}
	}

	return 0;
}

void Barrier::addPoint(double x, double y)
{
	pointList.add(new Point(x, y));
}

void Barrier::removePoint(int pointIndex)
{
	if (pointIndex >= pointList.size())
		return;

	pointList.remove(pointIndex);
}

void Barrier::swapPoints(int index1, int index2)
{
	int maxIndex = max(index1, index2);
	int minIndex = min(index1, index2);

	if (maxIndex >= pointList.size() || minIndex < 0)
		return;

	pointList.swap(index1, index2);
}

bool Barrier::getPointCoords(int pointIndex, double& x, double& y)
{
	if (pointIndex >= pointList.size())
		return false;

	x = pointList[pointIndex]->x;
	y = pointList[pointIndex]->y;
	return true;
}

bool Barrier::setPointCoords(int pointIndex, double x, double y)
{
	if (pointIndex >= pointList.size())
		return false;

	pointList[pointIndex]->x = x;
	pointList[pointIndex]->y = y;
	return true;
}

visible void Barrier_addPoint(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	if (!isclasstype(barNode, "Barrier"))
		return;

	Barrier* b = &o(Barrier, barNode);
	b->addPoint(parval(2), parval(3));
}

visible void Barrier_removePoint(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	if (!isclasstype(barNode, "Barrier"))
		return;

	Barrier* b = &o(Barrier, barNode);
	b->removePoint((int)parval(2));
}

visible void Barrier_swapPoints(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	if (!isclasstype(barNode, "Barrier"))
		return;

	Barrier* b = &o(Barrier, barNode);
	b->swapPoints((int)parval(2), (int)parval(3));
}

visible void Barrier_setPointCoords(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	if (!isclasstype(barNode, "Barrier"))
		return;

	Barrier* b = &o(Barrier, barNode);
	b->setPointCoords((int)parval(2), parval(3), parval(4));
}
