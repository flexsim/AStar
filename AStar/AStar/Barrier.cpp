#include "Barrier.h"
#include "AStarNavigator.h"

Barrier::Barrier()
{
	creating = false;
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
	bindNumber(creating);
	bindNumber(meshOffset);
	bindNumber(nrVerts);
	bindNumber(active);
	bindNumber(hover);
	bindNodePtr(points);
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
	if (active) {
		black[2] += 0.5;
	}

	if (hover) {
		black[0] += 0.2;
		black[1] += 0.2;
		black[2] += 0.2;
	}

	float bottomLeft[3] = {xmin, ymin, z};
	float topLeft[3] = {xmin, ymax, z};
	float topRight[3] = {xmax, ymax, z};
	float bottomRight[3] = {xmax, ymin, z};

#define ABV(point, color) {\
		int newVertex = barrierMesh->addVertex();\
		barrierMesh->setVertexAttrib(newVertex, MESH_POSITION, point);\
		barrierMesh->setVertexAttrib(newVertex, MESH_EMISSIVE, color);\
		nrVerts++;\
	}\

	ABV(bottomLeft, black);
	ABV(bottomRight, black);
	ABV(topLeft, black);
	ABV(topLeft, black);
	ABV(bottomRight, black);
	ABV(topRight, black);

#undef ABV
}

double Barrier::onClick(int clickCode, double x, double y)
{

	return 0;
}

double Barrier::onMouseMove(double x, double y)
{
	
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
	b->removePoint(parval(2));
}

visible void Barrier_swapPoints(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	if (!isclasstype(barNode, "Barrier"))
		return;

	Barrier* b = &o(Barrier, barNode);
	b->swapPoints(parval(2), parval(3));
}

visible void Barrier_setPointCoords(FLEXSIMINTERFACE)
{
	TreeNode* barNode = parnode(1);
	if (!isclasstype(barNode, "Barrier"))
		return;

	Barrier* b = &o(Barrier, barNode);
	b->setPointCoords(parval(2), parval(3), parval(4));
}
