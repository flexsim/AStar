#include "Barrier.h"
#include "AStarNavigator.h"
#include "macros.h"

namespace AStar {

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

void Barrier::addBarriersToTable(AStarNavigator* nav)
	//AStarNode* edgeTable, 
	//					  std::unordered_map<unsigned int, AStarNodeExtraData>* extraData, 
	//					  double c0, double r0, unsigned int edgeTableXSize, unsigned int edgeTableYSize)
{
	double xmin, ymin, xmax, ymax;
	if (!getBoundingBox(xmin, ymin, xmax, ymax))
		return;

	double c0 = nav->gridOrigin.x;
	double r0 = nav->gridOrigin.y;

	int colleft = (int)round((xmin - c0) / nodeWidth);
	int rowbottom = (int)round((ymin - r0) / nodeWidth);
	int colright = (int)round((xmax - c0) / nodeWidth);
	int rowtop = (int)round((ymax - r0) / nodeWidth);
	for(int row = rowbottom; row <= rowtop; row++) {
		AStarNode * left = nav->getNode(row, colleft-1);
		left->canGoRight = 0;
		AStarNode * right = nav->getNode(row, colright + 1);
		right->canGoLeft = 0;
	}

	for(int col = colleft; col <= colright; col++) {
		AStarNode * top = nav->getNode(rowtop + 1, col);
		top->canGoDown = 0;
		AStarNode * bottom = nav->getNode(rowbottom - 1, col);
		bottom->canGoUp = 0;
	}

	for (int row = rowbottom; row <= rowtop; row++) {
		for (int col = colleft; col <= colright; col++) {
			AStarNode* theNode = nav->getNode(row, col);
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

	float scale = max(this->nodeWidth, 0.15 * max(height, width));

	Vec3f left[3] = {
		Vec3f(xmin, ymin + height *0.5f + 0.25f * scale, z),
		Vec3f(xmin, ymin + height *0.5f - 0.25f * scale, z),
		Vec3f(xmin - 0.5f * scale, ymin + height *0.5f, z)
	};
	Vec3f right[3] = {
		Vec3f(xmax, ymin + height *0.5f + 0.25f * scale, z),
		Vec3f(xmax, ymin + height *0.5f - 0.25f * scale, z),
		Vec3f(xmax + 0.5f * scale, ymin + height *0.5f, z)
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
		Point* bottomLeft = pointList[0];
		Point* topRight = pointList[1];

		// Fix the points
		if (bottomLeft->x > topRight->x) {
			double bottomLeftX = bottomLeft->x;
			bottomLeft->x = topRight->x;
			topRight->x = bottomLeftX;
		}
		if (bottomLeft->y > topRight->y) {
			double bottomLeftY = bottomLeft->y;
			bottomLeft->y = topRight->y;
			topRight->y = bottomLeftY;
		}

		// If creating, don't try to change the active node or the mode
		if (mode & BARRIER_MODE_CREATE) {
			Point* bottomLeft = pointList[0];
			Point* topRight = pointList[1];
			Point* activePoint = pointList[(int)activePointIndex];
			double width = topRight->x - bottomLeft->x;
			double height = topRight->y - bottomLeft->y;

			// Enforce a minimum size
			if (width < nodeWidth) {
				if (activePoint == bottomLeft) {
					activePoint->x = topRight->x - nodeWidth;
				}
				else {
					activePoint->x = bottomLeft->x + nodeWidth;
				}
			}

			if (height < nodeWidth) {
				if (activePoint == bottomLeft) {
					activePoint->y = topRight->y - nodeWidth;
				}
				else {
					activePoint->y = bottomLeft->y + nodeWidth;
				}
			}

			o(AStarNavigator, ownerobject(holder)).addCreateRecord(view, this);
			return 0;
		}

		for (int i = 0; i < pointList.size(); i++) {
			applicationcommand("addundotracking", view, node("x", pointList[i]->holder));
			applicationcommand("addundotracking", view, node("y", pointList[i]->holder));
		}

		double z = 0;
		double xmin, ymin, xmax, ymax;
		if (!getBoundingBox(xmin, ymin, xmax, ymax))
			return 0;

		double width = xmax - xmin;
		double height = ymax - ymin;

		float scale = max(this->nodeWidth, 0.15 * max(height, width));

		Vec3f left[3] = {
			Vec3f(xmin, ymin + height *0.5f + 0.25f * scale, z),
			Vec3f(xmin, ymin + height *0.5f - 0.25f * scale, z),
			Vec3f(xmin - 0.5f * scale, ymin + height *0.5f, z)
		};
		Vec3f right[3] = {
			Vec3f(xmax, ymin + height *0.5f + 0.25f * scale, z),
			Vec3f(xmax, ymin + height *0.5f - 0.25f * scale, z),
			Vec3f(xmax + 0.5f * scale, ymin + height *0.5f, z)
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
		
		auto PointInTriangle = [](Vec3f P, Vec3f A, Vec3f B, Vec3f C) {
			// Prepare our barycentric variables
			Vec3f u = B - A;
			Vec3f v = C - A;
			Vec3f w = P - A;

			Vec3f vCrossW = v.cross(w);
			Vec3f vCrossU = v.cross(u);

			// Test sign of r
			if (vCrossW.dot(vCrossU) < 0)
				return false;

			Vec3f uCrossW = u.cross(w);
			Vec3f uCrossV = u.cross(v);

			// Test sign of t
			if (uCrossW.dot(uCrossV) < 0)
				return false;

			// At this point, we know that r and t and both > 0.
			// Therefore, as long as their sum is <= 1, each must be less <= 1
			float denom = uCrossV.getLength();
			float r = vCrossW.getLength() / denom;
			float t = uCrossW.getLength() / denom;

			return (r + t <= 1);
		};

		Vec3f point = Vec3f(x, y, 0);
		// Left Arrow
		if (PointInTriangle(point, left[0], left[1], left[2])) {
			activePointIndex = 0;
			mode = BARRIER_MODE_POINT_EDIT;
			arrow = 1;
		
		// Right Arrow
		} else if (PointInTriangle(point, right[0], right[1], right[2])) {
			activePointIndex = 1;
			mode = BARRIER_MODE_POINT_EDIT;
			arrow = 2;
		
		// Top Arrow
		} else if (PointInTriangle(point, top[0], top[1], top[2])) {
			activePointIndex = 1;
			mode = BARRIER_MODE_POINT_EDIT;
			arrow = 3;
		
		// Bottom Arrow
		} else if (PointInTriangle(point, bottom[0], bottom[1], bottom[2])) {
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

double Barrier::onMouseMove(const Vec3& pos, const Vec3& diff)
{
	if ((mode & BARRIER_MODE_POINT_EDIT) && activePointIndex < pointList.size()) {
		Point* activePoint = pointList[(int)activePointIndex];

		if (arrow <= 2) {
			activePoint->x += diff.x;
		}
		if (arrow == 0 || arrow > 2) {
			activePoint->y += diff.y;
		}
	}

	if (mode & BARRIER_MODE_MOVE) {
		if (mode & BARRIER_MODE_CREATE) {
			mode = BARRIER_MODE_MOVE;
			modeleditmode(0);
		}
		for (int i = 0; i < pointList.size(); i++) {
			pointList[i]->x += diff.x;
			pointList[i]->y += diff.y;
		}
	}

	return 1;
}

void Barrier::addPoint(double x, double y, double z)
{
	pointList.add(new Point(x, y, z));
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

bool Barrier::getPointCoords(int pointIndex, double& x, double& y, double& z)
{
	if (pointIndex >= pointList.size())
		return false;

	x = pointList[pointIndex]->x;
	y = pointList[pointIndex]->y;
	z = pointList[pointIndex]->z;
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

bool Barrier::setPointCoords(int pointIndex, double x, double y, double z)
{
	if (pointIndex >= pointList.size())
		return false;

	pointList[pointIndex]->x = x;
	pointList[pointIndex]->y = y;
	pointList[pointIndex]->z = z;
	return true;
}

void Barrier::addPathVertices(Mesh* barrierMesh, float z, const Vec4f& color)
{
	float dark[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	float light[4] = { color.r, color.g, color.b, color.a };
	float highlight[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
	if (isActive) {
		dark[0] += 0.2f;
		dark[1] += 0.2f;
		dark[2] += 0.2f;
		light[0] = min(1.0f, light[0] + 0.2f);
		light[1] = min(1.0f, light[1] + 0.2f);
		light[2] = min(1.0f, light[2] + 0.2f);
	}
	nrVerts = 0;
	meshOffset = barrierMesh->numVerts;

	// Add circles at each node
	const float TWO_PI = 2 * 3.1415926536f;
	int numSides = 20;
	float radius = nodeWidth * 0.3;
	float dTheta = TWO_PI / numSides;

	bool isBridge = toBridge() ? true : false;

	for (int i = 0; i < pointList.size(); i++) {
		float center[3] = { pointList[i]->x, pointList[i]->y, isBridge ? pointList[i]->z : z };

		// For each side, draw a triangle
		for (int j = 0; j < numSides - 1; j++) {
			float theta = j * dTheta;
			float x = radius * cos(theta) + center[0];
			float y = radius * sin(theta) + center[1];
			float x2 = radius * cos(theta + dTheta) + center[0];
			float y2 = radius * sin(theta + dTheta) + center[1];

			float pos1[3] = { x, y, center[2] };
			float pos2[3] = { x2, y2, center[2] };

#define ABV(pos, color, activeColor) {\
			int vertName = barrierMesh->addVertex();\
			nrVerts++;\
			if (i == activePointIndex)\
				barrierMesh->setVertexAttrib(vertName, MESH_DIFFUSE4, activeColor);\
				else\
				barrierMesh->setVertexAttrib(vertName, MESH_DIFFUSE4, color);\
			barrierMesh->setVertexAttrib(vertName, MESH_POSITION, pos);\
							}

			ABV(center, dark, highlight);
			ABV(pos1, dark, highlight);
			ABV(pos2, dark, highlight);

		}

		// Draw the last triangle using first and last coords
		float lastTheta = (numSides - 1) * dTheta;
		float pos2[3] = { radius + center[0], center[1], center[2] };
		float pos1[3] = { radius * cos(lastTheta) + center[0], radius * sin(lastTheta) + center[1], center[2] };
		ABV(center, dark, highlight);
		ABV(pos1, dark, highlight);
		ABV(pos2, dark, highlight);
	}
#undef ABV

	// Draw a series of triangles
	float maxTriangleWidth = nodeWidth;
	float distToRect = 0.4 * nodeWidth;
	float distToCorner = sqrt(distToRect * distToRect + radius * radius);
	float height = 2 * radius;
	dTheta = atan2(radius, distToRect);
	for (int i = 0; i < pointList.size() - 1; i++) {
		Point* point = pointList[i];
		Point* next = pointList[i + 1];

		float dx = next->x - point->x;
		float dy = next->y - point->y;
		float dz = next->z - point->z;
		float theta = atan2(dy, dx);

		float length = sqrt(dx * dx + dy * dy) - 2 * distToRect;
		if (length <= 0)
			continue;

		float sinTheta = sin(theta);
		float cosTheta = cos(theta);
		// Find how many will fit, and stretch them to fit.
		int numTriangles = (int)(length / maxTriangleWidth);
		if (numTriangles < 1) {
			numTriangles = 1;
		}
		float triangleWidth = length / numTriangles;
		float tw = triangleWidth;

		float pointZ = isBridge ? point->z : z;

		// Use the bottomleft corner of the rectangle to get every other corner
		float bottomLeft[3] = { distToCorner * cos(theta - dTheta) + point->x,
			distToCorner * sin(theta - dTheta) + point->y, pointZ };

		float topLeft[3] = { bottomLeft[0] - height * sinTheta,
			bottomLeft[1] + height * cosTheta, pointZ };

		float pos0[3] = { 0.0f, 0.0f, pointZ };
		float pos1[3] = { 0.0f, 0.0f, pointZ };
		float pos2[3] = { 0.0f, 0.0f, pointZ };

		for (int j = 0; j < numTriangles; j++) {

#define ROTATE_POINT(rx, ry, x, y) \
	rx = x * cosTheta - y * sinTheta;\
	ry = x * sinTheta + y * cosTheta;

#define ABV(pos, color)  {\
	int vertName = barrierMesh->addVertex();\
	nrVerts++;\
	barrierMesh->setVertexAttrib(vertName, MESH_DIFFUSE4, color);\
	barrierMesh->setVertexAttrib(vertName, MESH_POSITION, pos);\
			}

#define ABT(pos1, pos2, pos3, dark, green) ABV(pos1, green) ABV(pos2, dark) ABV(pos3, dark)


			float triangleTipX = (j + 1) * tw;
			float triangleTipY = height / 2.0;
			float triangleTopX = j * tw;
			float triangleTopY = height;
			float triangleBottomX = triangleTopX;
			float triangleBottomY = 0;

			float rtX, rtY;

			ROTATE_POINT(rtX, rtY, triangleTipX, triangleTipY);
			triangleTipX = rtX + bottomLeft[0];
			triangleTipY = rtY + bottomLeft[1];

			ROTATE_POINT(rtX, rtY, triangleTopX, triangleTopY);
			triangleTopX = rtX + bottomLeft[0];
			triangleTopY = rtY + bottomLeft[1];

			ROTATE_POINT(rtX, rtY, triangleBottomX, triangleBottomY);
			triangleBottomX = rtX + bottomLeft[0];
			triangleBottomY = rtY + bottomLeft[1];

			pos0[0] = triangleTipX;
			pos0[1] = triangleTipY;
			pos0[2] = point->z + dz * (j + 1) / numTriangles;
			pos1[0] = triangleTopX;
			pos1[1] = triangleTopY;
			pos1[2] = point->z + dz * j / numTriangles;
			pos2[0] = triangleBottomX;
			pos2[1] = triangleBottomY;
			pos2[2] = point->z + dz * j / numTriangles;

			ABT(pos0, pos1, pos2, dark, light);
		}
	}
#undef ABT
#undef ABV
#undef ROTATE_POINT
}

}

using namespace AStar;


ASTAR_FUNCTION Variant Barrier_setMode(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* barNode = param(1);

	try {
		Barrier* b = barNode->objectAs(Barrier);
		b->mode = (int)param(2);
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

	TreeNode* barNode = param(1);

	try {
		Barrier* b = barNode->objectAs(Barrier);
		if (parqty() == 4)
			b->addPoint(param(2), param(3), param(4));
		else
			b->addPoint(param(2), param(3));
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

	TreeNode* barNode = param(1);

	try {
		Barrier* b = barNode->objectAs(Barrier);
		b->removePoint((int)param(2));
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

	TreeNode* barNode = param(1);

	try {
		Barrier* b = barNode->objectAs(Barrier);
		b->swapPoints((int)param(2), (int)param(3));
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

	TreeNode* barNode = param(1);

	try {
		Barrier* b = barNode->objectAs(Barrier);
		if(parqty() == 5)
			b->setPointCoords((int)param(2), param(3), param(4), param(5));
		else
			b->setPointCoords((int)param(2), param(3), param(4));
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

	TreeNode* barNode = param(1);
	double x = 0;
	double y = 0;
	double z = 0;

	try {
		Barrier* b = barNode->objectAs(Barrier);
		b->getPointCoords((int)param(2), x, y, z);
	} catch (...) {
		return 0;
	}

	if ((int)param(3) == POINT_X)
		return x;

	if ((int)param(3) == POINT_Y)
		return y;

	if ((int)param(3) == POINT_Z)
		return z;

	return 1;
}

ASTAR_FUNCTION Variant Barrier_getBarrierType(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* barNode = param(1);
	TreeNode* resultNode = param(2);

	if (!validlink(resultNode, ""))
		return 0;

	try {
		Barrier* b = barNode->objectAs(Barrier);
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

	TreeNode* barNode = param(1);

	try {
		Barrier* b = barNode->objectAs(Barrier);
		b->activePointIndex = (int)param(2);
	} catch (...) {
		return 0;
	}
	return 1;
}

