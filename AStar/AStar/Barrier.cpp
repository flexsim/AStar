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

	arrow = 0;
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

void Barrier::addBarriersToTable(AStarNode* edgeTable, 
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

	meshOffset = barrierMesh->numVerts;

	float red[4] = {1.0f, 0.0f, 0.0f, 1.0f};
	float black[4] = {0.4f, 0.4f, 0.4f, 1.0f};
	if (isActive) {
		black[0] += 0.2f;
		black[1] += 0.2f;
		black[2] += 0.2f;
	}

	float scale = 0.1 * (height + width);
	
	Vec3f right[3] = {
		Vec3f(xmax, ymin + height *0.5f + 0.25f * scale, z),
		Vec3f(xmax, ymin + height *0.5f - 0.25f * scale, z),
		Vec3f(xmax + 0.5f * scale, ymin + height *0.5f, z)
	};

	Vec3f left[3] = {
		Vec3f(xmin, ymin + height *0.5f + 0.25f * scale, z),
		Vec3f(xmin, ymin + height *0.5f - 0.25f * scale, z),
		Vec3f(xmin - 0.5f * scale, ymin + height *0.5f, z)
	};

	Vec3f top[3] = {
		Vec3f(xmin + width * 0.5f - 0.25f * scale, ymax, z),
		Vec3f(xmin + width * 0.5f + 0.25f * scale, ymax, z),
		Vec3f(xmin + width * 0.5f, ymax + 0.5f * scale, z)
	};

	Vec3f bottom[3] = {
		Vec3f(xmin + width * 0.5f - 0.25f * scale, ymin, z),
		Vec3f(xmin + width * 0.5f + 0.25f * scale, ymin, z),
		Vec3f(xmin + width * 0.5f, ymin - 0.5f * scale, z)
	};

	float bottomLeft[3] = {xmin, ymin, z};
	float topRight[3] = { xmax, ymax, z }; 
	float topLeft[3] = { xmin, ymax, z };
	float bottomRight[3] = {xmax, ymin, z};
	
#define ABV(point, color) {\
		int newVertex = barrierMesh->addVertex();\
		barrierMesh->setVertexAttrib(newVertex, MESH_POSITION, point);\
		barrierMesh->setVertexAttrib(newVertex, MESH_DIFFUSE4, color);\
		nrVerts++;\
	}\

#define ABT(p1, p2, p3, color) ABV(p1, color) ABV(p2, color) ABV(p3, color)
	if (isActive) {
		ABT(left[0], left[1], left[2], red);
		ABT(right[0], right[1], right[2], red);
		ABT(top[0], top[1], top[2], red);
		ABT(bottom[0], bottom[1], bottom[2], red);
	}
	ABT(bottomRight, topLeft, bottomLeft, black);
	ABT(bottomRight, topRight, topLeft, black);
	
#undef ABT
#undef ABV
}

double Barrier::onClick(treenode view, int clickCode, double x, double y)
{
	if (clickCode == LEFT_PRESS) {

		// If creating, don't try to change the active node or the mode
		if (mode & BARRIER_MODE_CREATE) {
			o(AStarNavigator, ownerobject(holder)).addCreateRecord(view, this);
			return 0;
		}

		for (int i = 0; i < pointList.size(); i++) {
			applicationcommand("addundotracking", tonum(view), tonum(node("x", pointList[i]->holder)));
			applicationcommand("addundotracking", tonum(view), tonum(node("y", pointList[i]->holder)));
		}

		double xmin, ymin, xmax, ymax;
		if (!getBoundingBox(xmin, ymin, xmax, ymax))
			return 0;

		// Left Arrow
		if (x < xmin) {
			activePointIndex = 0;
			mode = BARRIER_MODE_POINT_EDIT;
			arrow = 1;
		
		// Right Arrow
		} else if (x > xmax) {
			activePointIndex = 1;
			mode = BARRIER_MODE_POINT_EDIT;
			arrow = 2;
		
		// Top Arrow
		} else if (y > ymax) {
			activePointIndex = 1;
			mode = BARRIER_MODE_POINT_EDIT;
			arrow = 3;
		
		// Bottom Arrow
		} else if (y < ymin) {
			activePointIndex = 0;
			mode = BARRIER_MODE_POINT_EDIT;
			arrow = 4;

		} else {
			activePointIndex = 0;
			mode = BARRIER_MODE_MOVE;
		}
	}

	if (clickCode == LEFT_RELEASE) {
		if (mode & BARRIER_MODE_POINT_EDIT) {
			activePointIndex = 0;
			mode = 0;
			arrow = 0;
		}
	}

	if (clickCode == RIGHT_RELEASE) {
		// Right click -> abort barrier creation
		if (mode & BARRIER_MODE_CREATE) {
			destroyobject(holder);
		}
	}

	return 1;
}

double Barrier::onMouseMove(double x, double y, double dx, double dy)
{
	if ((mode & BARRIER_MODE_POINT_EDIT) && activePointIndex < pointList.size()) {
		Point* activePoint = pointList[(int)activePointIndex];

		if (arrow <= 2) {
			activePoint->x = x + 0.2 * nodeWidth * (activePointIndex ? 1 : -1);
		}
		if (arrow == 0 || arrow > 2) {
			activePoint->y = y + 0.2 * nodeWidth * (activePointIndex ? 1 : -1);
		}

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

	return 1;
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

ASTAR_FUNCTION Variant Barrier_setMode(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* barNode = parnode(1);



	try {
		Barrier* b = &o(Barrier, barNode);
		b->mode = (int)parnode(2);
	} catch (...) {
		return 0;
	}
	return 1;
}

ASTAR_FUNCTION Variant Barrier_addPoint(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* barNode = parnode(1);

	try {
		Barrier* b = &o(Barrier, barNode);
		b->addPoint(parval(2), parval(3));
	} catch (...) {
		return 0;
	}
	return 1;
}

ASTAR_FUNCTION Variant Barrier_removePoint(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* barNode = parnode(1);

	try {
		Barrier* b = &o(Barrier, barNode);
		b->removePoint((int)parval(2));
	} catch (...) {
		return 0;
	}
	return 1;
}

ASTAR_FUNCTION Variant Barrier_swapPoints(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* barNode = parnode(1);

	try {
		Barrier* b = &o(Barrier, barNode);
		b->swapPoints((int)parval(2), (int)parval(3));
	} catch (...) {
		return 0;
	}
	return 1;
}

ASTAR_FUNCTION Variant Barrier_setPointCoords(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* barNode = parnode(1);

	try {
		Barrier* b = &o(Barrier, barNode);
		b->setPointCoords((int)parval(2), parval(3), parval(4));
	} catch (...) {
		return 0;
	}
	return 1;
}

ASTAR_FUNCTION Variant Barrier_getPointCoord(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* barNode = parnode(1);
	double x = 0;
	double y = 0;

	try {
		Barrier* b = &o(Barrier, barNode);
		b->getPointCoords((int)parval(2), x, y);
	} catch (...) {
		return 0;
	}

	if ((int)parval(3) == POINT_X)
		return x;

	if ((int)parval(3) == POINT_Y)
		return y;

	return 1;
}

ASTAR_FUNCTION Variant Barrier_getBarrierType(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* barNode = parnode(1);
	TreeNode* resultNode = parnode(2);

	if (!validlink(resultNode, ""))
		return 0;

	try {
		Barrier* b = &o(Barrier, barNode);
		sets(resultNode, b->getClassFactory());
	} catch (...) {
		return 0;
	}
	return 1;
}

ASTAR_FUNCTION Variant Barrier_setActiveIndex(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* barNode = parnode(1);

	try {
		Barrier* b = &o(Barrier, barNode);
		b->activePointIndex = (int)parval(2);
	} catch (...) {
		return 0;
	}
	return 1;
}

