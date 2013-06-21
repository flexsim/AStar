#include "Barrier.h"
#include "AStarNavigator.h"
#include "macros.h"

Barrier::Barrier()
	: meshOffset(0)
	, nrVerts(0)
	, isActive(0)
	, activePointIndex(0)
	, mode(0)
	, nodeWidth(1.0)
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
	bindNumber(isActive);
	bindNumber(activePointIndex);
	bindNumber(mode);
	bindDouble(nodeWidth, 0);

	bindSubNode(points, 0);
	pointList.init(points);
}

void Barrier::init(double nodeWidth, double x1, double y1, double x2, double y2)
{
	this->nodeWidth = nodeWidth;
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

void Barrier::modifyTable(AStarNode* edgeTable, 
						  std::unordered_map<unsigned int, AStarNodeExtraData>* extraData, 
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
	

	float bottomLeft[3] = {xmin, ymin, z};
	float topLeft[3] = {xmin, ymax, z};
	float topRight[3] = {xmax, ymax, z};
	float bottomRight[3] = {xmax, ymin, z};

	float triangleEdgeLength = sqrt(width * width + height * height) / 10.0;
	triangleEdgeLength = max(0.8 * nodeWidth, triangleEdgeLength);
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

	ABT(triangleTopBottom, topRight, triangleTopLeft, gray);
	ABT(triangleBottomRight, triangleBottomTop, bottomLeft, gray);
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

		// If creating, don't try to change the active node or the mode
		if (mode & BARRIER_MODE_CREATE) {
			return 0;
		}

		// if the user clicked on a triangle, set the mode and active point
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
		float triangleEdgeLength = sqrt(width * width + height * height) / 10.0;
		triangleEdgeLength = max(0.8 * nodeWidth, triangleEdgeLength);
		// If the click is in the bottom left corner
		if ((x + y) <= triangleEdgeLength) {
			activePointIndex = 0;
			mode = BARRIER_MODE_POINT_EDIT;
		
		// If the click is in the top right corner
		} else if ((x + y) >= width + height - triangleEdgeLength) {
			activePointIndex = 1;
			mode = BARRIER_MODE_POINT_EDIT;
		
		} else {
			activePointIndex = 0;
			mode = BARRIER_MODE_MOVE;
		}
	}

	if (clickCode == LEFT_RELEASE) {
		if (mode & BARRIER_MODE_POINT_EDIT) {
			activePointIndex = 0;
			mode = 0;
		}
	}

	if (clickCode == RIGHT_RELEASE) {
		// Right click -> abort barrier creation
		if (mode & BARRIER_MODE_CREATE) {
			destroyobject(holder);
		}
	}

	return 0;
}

double Barrier::onMouseMove(double x, double y, double dx, double dy)
{
	if (mode & BARRIER_MODE_POINT_EDIT) {
		Point* activePoint = pointList[(int)activePointIndex];
		activePoint->x = x + 0.2 * nodeWidth * (activePointIndex ? 1 : -1);
		activePoint->y = y + 0.2 * nodeWidth * (activePointIndex ? 1 : -1);

		Point* bottomLeft = pointList[0];
		Point* topRight = pointList[1];
		double width = topRight->x - bottomLeft->x;
		double height = topRight->y - bottomLeft->y;

		if (width < nodeWidth) {
			if (activePoint == bottomLeft) {
				activePoint->x = topRight->x - nodeWidth;
			} else {
				activePoint->x = bottomLeft->x + nodeWidth;
			}
		}

		if (height < nodeWidth) {
			if (activePoint == bottomLeft) {
				activePoint->y = topRight->y - nodeWidth;
			} else {
				activePoint->y = bottomLeft->y + nodeWidth;
			}
		}
	}

	if (mode & BARRIER_MODE_MOVE) {
		if (mode & BARRIER_MODE_CREATE) {
			mode = BARRIER_MODE_MOVE;
			modeleditmode(0);
		}
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

visible void Barrier_setMode(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	if (!isclasstype(ownerobject(barNode), "AStar::AStarNavigator"))
		return;

	if ((int)parnode(2) == 0)
		return;

	Barrier* b = &o(Barrier, barNode);
	b->mode = (int)parnode(2);
}

visible void Barrier_addPoint(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	if (!isclasstype(ownerobject(barNode), "AStar::AStarNavigator"))
		return;

	Barrier* b = &o(Barrier, barNode);
	b->addPoint(parval(2), parval(3));
}

visible void Barrier_removePoint(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	if (!isclasstype(ownerobject(barNode), "AStar::AStarNavigator"))
		return;

	Barrier* b = &o(Barrier, barNode);
	b->removePoint((int)parval(2));
}

visible void Barrier_swapPoints(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	if (!isclasstype(ownerobject(barNode), "AStar::AStarNavigator"))
		return;

	Barrier* b = &o(Barrier, barNode);
	b->swapPoints((int)parval(2), (int)parval(3));
}

visible void Barrier_setPointCoords(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	if (!isclasstype(ownerobject(barNode), "AStar::AStarNavigator"))
		return;

	Barrier* b = &o(Barrier, barNode);
	b->setPointCoords((int)parval(2), parval(3), parval(4));
}

visible double Barrier_getPointCoord(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	if (!isclasstype(ownerobject(barNode), "AStar::AStarNavigator"))
		return 0;

	Barrier* b = &o(Barrier, barNode);
	double x = 0;
	double y = 0;
	b->getPointCoords((int)parval(2), x, y);
	if ((int)parval(3) == POINT_X)
		return x;

	if ((int)parval(3) == POINT_Y)
		return y;

	return 0;
}

visible void Barrier_getBarrierType(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	TreeNode* resultNode = parnode(2);
	if (!isclasstype(ownerobject(barNode), "AStar::AStarNavigator"))
		return;
	if (!validlink(resultNode, ""))
		return;

	Barrier* b = &o(Barrier, barNode);
	sets(resultNode, b->getClassFactory());
}

visible void Barrier_setActiveIndex(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	if (!isclasstype(ownerobject(barNode), "AStar::AStarNavigator"))
		return;

	Barrier* b = &o(Barrier, barNode);
	b->activePointIndex = (int)parval(2);
}

