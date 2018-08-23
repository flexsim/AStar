#include "Barrier.h"
#include "AStarNavigator.h"
#include "macros.h"

namespace AStar {

Barrier::Barrier()
	: meshOffset(0)
	, nrVerts(0)
	, isActive(0)
	, isHovered(0)
	, activePointIndex(0)
	, mode(0)
	, lastMode(0)
	//, nodeWidth(1.0)
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
	//bindDouble(nodeWidth, 0);

	bindSubNode(points, 0);
	pointList.init(points);
}

void Barrier::init(double nodeWidth, const Vec3& pos1, const Vec3& pos2)
{
	this->nodeWidth = nodeWidth;
	addPoint(pos1);
	addPoint(pos2);

	arrow = 0;
}

bool Barrier::getBoundingBox(Vec3& min, Vec3& max)
{
	if (pointList.size() < 2) 
		return false;
	
	Vec3 p0, p1;
	getPointCoords(0, p0);
	getPointCoords(1, p1);

	min = Vec3(min(p0.x, p1.x), min(p0.y, p1.y), min(p0.z, p1.z));
	max = Vec3(max(p0.x, p1.x), max(p0.y, p1.y), max(p0.z, p1.z));
	return true;
}

void Barrier::addBarriersToTable(Grid* grid)
	//AStarNode* edgeTable, 
	//					  std::unordered_map<unsigned int, AStarNodeExtraData>* extraData, 
	//					  double c0, double r0, unsigned int edgeTableXSize, unsigned int edgeTableYSize)
{
	Vec3 myMin, myMax;
	if (!getBoundingBox(myMin, myMax))
		return;

	double c0 = grid->minPoint.x;
	double r0 = grid->minPoint.y;

	int colleft = (int)round((myMin.x - c0) / grid->nodeWidth);
	int rowbottom = (int)round((myMin.y - r0) / grid->nodeWidth);
	int colright = (int)round((myMax.x - c0) / grid->nodeWidth);
	int rowtop = (int)round((myMax.y - r0) / grid->nodeWidth);
	for(int row = rowbottom; row <= rowtop; row++) {
		AStarNode * left = grid->getNode(row, colleft-1);
		left->canGoRight = 0;
		AStarNode * right = grid->getNode(row, colright + 1);
		right->canGoLeft = 0;
	}

	for(int col = colleft; col <= colright; col++) {
		AStarNode * top = grid->getNode(rowtop + 1, col);
		top->canGoDown = 0;
		AStarNode * bottom = grid->getNode(rowbottom - 1, col);
		bottom->canGoUp = 0;
	}

	for (int row = rowbottom; row <= rowtop; row++) {
		for (int col = colleft; col <= colright; col++) {
			AStarNode* theNode = grid->getNode(row, col);
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

	Vec3 myMin, myMax;
	if (!getBoundingBox(myMin, myMax))
		return;

	double width = myMax.x - myMin.x;
	double height = myMax.y - myMin.y;

	meshOffset = barrierMesh->numVerts;

	float red[4] = {1.0f, 0.0f, 0.0f, 1.0f};
	float black[4] = {0.4f, 0.4f, 0.4f, 1.0f};
	if (isActive) {
		black[0] += 0.2f;
		black[1] += 0.2f;
		black[2] += 0.2f;
		z += 0.001 / getmodelunit(LENGTH_MULTIPLE);
	}
	else if (isHovered) {
		black[0] += 0.3f;
		black[1] += 0.3f;
		black[2] += 0.3f;
		z += 0.002 / getmodelunit(LENGTH_MULTIPLE);
	}

	float scale = max(this->nodeWidth, 0.15 * max(height, width));

	Vec3f left[3] = {
		Vec3f(myMin.x, myMin.y + height *0.5f + 0.25f * scale, z),
		Vec3f(myMin.x, myMin.y + height *0.5f - 0.25f * scale, z),
		Vec3f(myMin.x - 0.5f * scale, myMin.y + height *0.5f, z)
	};
	Vec3f right[3] = {
		Vec3f(myMax.x, myMin.y + height *0.5f + 0.25f * scale, z),
		Vec3f(myMax.x, myMin.y + height *0.5f - 0.25f * scale, z),
		Vec3f(myMax.x + 0.5f * scale, myMin.y + height *0.5f, z)
	};
	Vec3f top[3] = {
		Vec3f(myMin.x + width * 0.5f - 0.25f * scale, myMax.y, z),
		Vec3f(myMin.x + width * 0.5f + 0.25f * scale, myMax.y, z),
		Vec3f(myMin.x + width * 0.5f, myMax.y + 0.5f * scale, z)
	};
	Vec3f bottom[3] = {
		Vec3f(myMin.x + width * 0.5f - 0.25f * scale, myMin.y, z),
		Vec3f(myMin.x + width * 0.5f + 0.25f * scale, myMin.y, z),
		Vec3f(myMin.x + width * 0.5f, myMin.y - 0.5f * scale, z)
	};

	float bottomLeft[3] = {myMin.x, myMin.y, z};
	float topRight[3] = { myMax.x, myMax.y, z }; 
	float topLeft[3] = { myMin.x, myMax.y, z };
	float bottomRight[3] = {myMax.x, myMin.y, z};
	
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

double Barrier::onClick(treenode view, int clickCode, Vec3& pos)
{
	if (activePointIndex > 1) activePointIndex = 0;

	Point* activePoint = pointList[(int)activePointIndex];
	Point* bottomLeft = pointList[0];
	Point* topRight = pointList[1];

	if (clickCode == LEFT_PRESS && (mode & Barrier::CREATE)) {
		// Set activePoint to current mouse position
		activePoint->x = pos.x;
		activePoint->y = pos.y;
	}

	// Swap point coordinates if they are not actually the bottom left and top right points
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

	// Test to see if the user is clicking on a scaling arrow of the barrier 
	// to resize it. This technically should be done just using FlexSim's 
	// picking features, but I guess Jacob didn't know how to do that at the 
	// time, so he did the math.
	if (clickCode == LEFT_PRESS && !(mode & Barrier::CREATE)) {
		for (int i = 0; i < pointList.size(); i++) {
			applicationcommand("addundotracking", view, node("x", pointList[i]->holder));
			applicationcommand("addundotracking", view, node("y", pointList[i]->holder));
		}

		double z = 0;
		Vec3 myMin, myMax;
		if (!getBoundingBox(myMin, myMax))
			return 0;

		double width = myMax.x - myMin.x;
		double height = myMax.y - myMin.y;

		float scale = max(this->nodeWidth, 0.15 * max(height, width));

		Vec3f left[3] = {
			Vec3f(myMin.x, myMin.y + height *0.5f + 0.25f * scale, z),
			Vec3f(myMin.x, myMin.y + height *0.5f - 0.25f * scale, z),
			Vec3f(myMin.x - 0.5f * scale, myMin.y + height *0.5f, z)
		};
		Vec3f right[3] = {
			Vec3f(myMax.x, myMin.y + height *0.5f + 0.25f * scale, z),
			Vec3f(myMax.x, myMin.y + height *0.5f - 0.25f * scale, z),
			Vec3f(myMax.x + 0.5f * scale, myMin.y + height *0.5f, z)
		};
		Vec3f top[3] = {
			Vec3f(myMin.x + width * 0.5f - 0.25f * scale, myMax.y, z),
			Vec3f(myMin.x + width * 0.5f + 0.25f * scale, myMax.y, z),
			Vec3f(myMin.x + width * 0.5f, myMax.y + 0.5f * scale, z)
		};
		Vec3f bottom[3] = {
			Vec3f(myMin.x + width * 0.5f - 0.25f * scale, myMin.y, z),
			Vec3f(myMin.x + width * 0.5f + 0.25f * scale, myMin.y, z),
			Vec3f(myMin.x + width * 0.5f, myMin.y - 0.5f * scale, z)
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

		Vec3f point = Vec3f(pos.x, pos.y, 0);
		// Left Arrow
		if (PointInTriangle(point, left[0], left[1], left[2])) {
			activePointIndex = 0;
			mode = Barrier::POINT_EDIT;
			arrow = ARROW_LEFT;
		
		// Right Arrow
		} else if (PointInTriangle(point, right[0], right[1], right[2])) {
			activePointIndex = 1;
			mode = Barrier::POINT_EDIT;
			arrow = ARROW_RIGHT;
		
		// Top Arrow
		} else if (PointInTriangle(point, top[0], top[1], top[2])) {
			activePointIndex = 1;
			mode = Barrier::POINT_EDIT;
			arrow = ARROW_TOP;
		
		// Bottom Arrow
		} else if (PointInTriangle(point, bottom[0], bottom[1], bottom[2])) {
			activePointIndex = 0;
			mode = Barrier::POINT_EDIT;
			arrow = ARROW_BOTTOM;

		} else {
			activePointIndex = 0;
			mode = Barrier::MOVE;
		}
	}

	if (clickCode == LEFT_RELEASE) {
		if (mode & Barrier::POINT_EDIT) {
			double width = topRight->x - bottomLeft->x;
			double height = topRight->y - bottomLeft->y;

			// Enforce a minimum size
			if (width < nodeWidth / 2) {
				if (activePoint == bottomLeft)
					activePoint->x = topRight->x - nodeWidth / 2;
				else
					activePoint->x = bottomLeft->x + nodeWidth / 2;
			}
			if (height < nodeWidth / 2) {
				if (activePoint == bottomLeft)
					activePoint->y = topRight->y - nodeWidth / 2;
				else
					activePoint->y = bottomLeft->y + nodeWidth / 2;
			}
		
			activePointIndex = 0;
			mode = 0;
			arrow = 0;
		}
	}

	if (clickCode == RIGHT_RELEASE) {
		// Right click -> abort barrier creation
		if (mode & Barrier::CREATE) {
			destroyobject(holder);
		}
	}

	return 1;
}

double Barrier::onMouseMove(const Vec3& pos, const Vec3& diff)
{
	if ((mode & Barrier::POINT_EDIT) && activePointIndex < pointList.size()) {
		Point* activePoint = pointList[(int)activePointIndex];

		if (arrow == ARROW_LEFT || arrow == ARROW_RIGHT) {
			activePoint->x += diff.x;
		}
		if (arrow == 0 || arrow == ARROW_TOP || arrow == ARROW_BOTTOM) {
			activePoint->y += diff.y;
		}
	}
	else if (mode & Barrier::MOVE) {
		if (mode & Barrier::CREATE) {
			mode = Barrier::MOVE;
			modeleditmode(0);
		}
		for (int i = 0; i < pointList.size(); i++) {
			pointList[i]->x += diff.x;
			pointList[i]->y += diff.y;
		}
	}

	return 1;
}

void Barrier::addPoint(const Vec3& pos)
{
	pointList.add(new Point(pos.x, pos.y, pos.z));
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

bool Barrier::getPointCoords(int pointIndex, Vec3& point)
{
	if (pointIndex >= pointList.size())
		return false;

	point.x = pointList[pointIndex]->x;
	point.y = pointList[pointIndex]->y;
	point.z = pointList[pointIndex]->z;
	return true;
}

bool Barrier::setPointCoords(int pointIndex, const Vec3& point)
{
	if (pointIndex >= pointList.size())
		return false;

	pointList[pointIndex]->x = point.x;
	pointList[pointIndex]->y = point.y;
	pointList[pointIndex]->z = point.z;
	return true;
}

void Barrier::addPathVertices(Mesh* barrierMesh, float z, const Vec4f& color)
{
	float theColor[4] = { min(1.0f, color.r + 0.2f), min(1.0f, color.g + 0.2f), min(1.0f, color.b + 0.2f), color.a };
	float lightGray[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	float darkGray[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	float black[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	if (isActive) {
		theColor[0] = color.r;
		theColor[1] = color.g;
		theColor[2] = color.b;
		lightGray[0] = 0.6f;
		lightGray[1] = 0.6f;
		lightGray[2] = 0.6f;
		darkGray[0] = 0.3f;
		darkGray[1] = 0.3f;
		darkGray[2] = 0.3f;
		black[0] = 0.0f;
		black[1] = 0.0f;
		black[2] = 0.0f;
		z += 0.001 / getmodelunit(LENGTH_MULTIPLE);
	}
	else if (isHovered) {
		theColor[0] = min(1.0f, color.r + 0.1f);
		theColor[1] = min(1.0f, color.g + 0.1f);
		theColor[2] = min(1.0f, color.b + 0.1f);
		lightGray[0] = 0.7f;
		lightGray[1] = 0.7f;
		lightGray[2] = 0.7f;
		darkGray[0] = 0.45f;
		darkGray[1] = 0.45f;
		darkGray[2] = 0.45f;
		black[0] = 0.45f;
		black[1] = 0.45f;
		black[2] = 0.45f;
		z += 0.002 / getmodelunit(LENGTH_MULTIPLE);
	}
	nrVerts = 0;
	meshOffset = barrierMesh->numVerts;

	// Add circles at each node
	const float TWO_PI = 2 * 3.1415926536f;
	int numSides = 20;
	float radius = nodeWidth * 0.15;
	float dTheta = TWO_PI / numSides;

	bool isBridge = toBridge() ? true : false;

	for (int i = 0; i < pointList.size(); i++) {
		float center[3] = { pointList[i]->x, pointList[i]->y, (isBridge ? pointList[i]->z + z : z) + 0.001 / getmodelunit(LENGTH_MULTIPLE)};

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

			ABV(center, darkGray, black);
			ABV(pos1, darkGray, black);
			ABV(pos2, darkGray, black);

		}

		// Draw the last triangle using first and last coords
		float lastTheta = (numSides - 1) * dTheta;
		float pos2[3] = { radius + center[0], center[1], center[2] };
		float pos1[3] = { radius * cos(lastTheta) + center[0], radius * sin(lastTheta) + center[1], center[2] };
		ABV(center, darkGray, black);
		ABV(pos1, darkGray, black);
		ABV(pos2, darkGray, black);
	}
#undef ABV

	// Draw a series of triangles
	float maxTriangleWidth = nodeWidth;
	float distToRect = 0;// 0.4 * nodeWidth;
	float distToCorner = sqrt(distToRect * distToRect + radius * radius);
	float height = 2 * radius;
	dTheta = atan2(radius, distToRect);
	for (int i = 0; i < pointList.size() - 1; i++) {
		Point* point = pointList[i];
		Point* next = pointList[i + 1];
		float pointZ = isBridge ? point->z + z : z;
		float nextZ = isBridge ? next->z + z : z;

		float dx = next->x - point->x;
		float dy = next->y - point->y;
		float dz = pointZ - nextZ;
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

#define ABT(pos1, pos2, pos3, dark, color) ABV(pos1, color) ABV(pos2, dark) ABV(pos3, dark)


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
			pos0[2] = pointZ + dz * (j + 1) / numTriangles;
			pos1[0] = triangleTopX;
			pos1[1] = triangleTopY;
			pos1[2] = pointZ + dz * j / numTriangles;
			pos2[0] = triangleBottomX;
			pos2[1] = triangleBottomY;
			pos2[2] = pointZ + dz * j / numTriangles;

			ABT(pos0, pos1, pos2, lightGray, theColor);
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
		b->addPoint(Vec3(param(2), param(3), param(4)));
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
			b->setPointCoords((int)param(2), Vec3(param(3), param(4), param(5)));
		else
			b->setPointCoords((int)param(2), Vec3(param(3), param(4), 0.0));
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
	Vec3 point;

	try {
		Barrier* b = barNode->objectAs(Barrier);
		b->getPointCoords((int)param(2), point);
	} catch (...) {
		return 0;
	}

	if ((int)param(3) == POINT_X)
		return point.x;

	if ((int)param(3) == POINT_Y)
		return point.y;

	if ((int)param(3) == POINT_Z)
		return point.z;

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

