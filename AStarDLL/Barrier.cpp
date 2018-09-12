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

	bindSubNode(points, 0);
	pointList.init(points);

	bindDouble(useCondition, 1);
	bindSubNode(condition, DATATYPE_STRING);
	bindSubNode(patternTable, 0);

	bindCallback(addPoint, Barrier);
	bindCallback(removePoint, Barrier);
	bindCallback(swapPoints, Barrier);
	bindCallback(getPointCoord, Barrier);
	bindCallback(setPointCoords, Barrier);
	bindCallback(getType, Barrier);
	bindCallback(setEditMode, Barrier);
	bindCallback(setActiveIndex, Barrier);
	bindCallback(addPatternRow, Barrier);
	bindCallback(addPatternCol, Barrier);
	bindCallback(deletePatternRow, Barrier);
	bindCallback(deletePatternCol, Barrier);

	int bindMode = getBindMode();
	if (bindMode == SDT_BIND_ON_LOAD || bindMode == SDT_BIND_ON_CREATE) {
		if (condition->value == "") {
			condition->value = "treenode traveler = param(1);\r\nreturn /**/traveler.type == 1/**direct*/;\r\n";
		}
	}
}

AStarNavigator * Barrier::__getNavigator()
{
	return ownerobject(holder)->objectAs(AStarNavigator);
}

void Barrier::bindEvents()
{
	bindEventByName("condition", condition, "Condition", EVENT_TYPE_VALUE_GETTER);
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
	
	Vec3 p0 = getPointCoords(0);
	Vec3 p1 = getPointCoords(1);

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

	grid->addSolidBarrierToTable(myMin, myMax, this);
}

void Barrier::addMeshVertex(Mesh* mesh, float* pos, float* color, unsigned int* incNumVerts)
{
	int newVertex = mesh->addVertex();
	mesh->setVertexAttrib(newVertex, MESH_POSITION, pos);
	mesh->setVertexAttrib(newVertex, MESH_DIFFUSE4, color);
	if (incNumVerts)
		(*incNumVerts)++;
}

void Barrier::addMeshTriangle(Mesh * mesh, float * p1, float * p2, float * p3, float * color, unsigned int* incNumVerts)
{
	addMeshVertex(mesh, p1, color, incNumVerts);
	addMeshVertex(mesh, p2, color, incNumVerts);
	addMeshVertex(mesh, p3, color, incNumVerts);
}

void Barrier::drawManipulationHandles(treenode view)
{
	Vec3 myMin, myMax;
	if (!getBoundingBox(myMin, myMax))
		return;

	float width = (float)(myMax.x - myMin.x);
	float height = (float)(myMax.y - myMin.y);
	float scale = max(this->nodeWidth, 0.15 * max(height, width));
	float z = (float)myMin.z;

	Mesh mesh;
	mesh.init(0, MESH_POSITION | MESH_DIFFUSE4);
	Vec3f left[3] = {
		Vec3f(myMin.x, myMin.y + height * 0.5f + 0.25f * scale, z),
		Vec3f(myMin.x, myMin.y + height * 0.5f - 0.25f * scale, z),
		Vec3f(myMin.x - 0.5f * scale, myMin.y + height * 0.5f, z)
	};
	Vec3f right[3] = {
		Vec3f(myMax.x, myMin.y + height * 0.5f + 0.25f * scale, z),
		Vec3f(myMax.x, myMin.y + height * 0.5f - 0.25f * scale, z),
		Vec3f(myMax.x + 0.5f * scale, myMin.y + height * 0.5f, z)
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
	float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	addMeshTriangle(&mesh, left[0], left[1], left[2], red);
	addMeshTriangle(&mesh, right[0], right[1], right[2], red);
	addMeshTriangle(&mesh, top[0], top[1], top[2], red);
	addMeshTriangle(&mesh, bottom[0], bottom[1], bottom[2], red);

	setpickingdrawfocus(view, holder, ARROW_LEFT);
	mesh.draw(GL_TRIANGLES, 0, 3);
	setpickingdrawfocus(view, holder, ARROW_RIGHT);
	mesh.draw(GL_TRIANGLES, 3, 3);
	setpickingdrawfocus(view, holder, ARROW_TOP);
	mesh.draw(GL_TRIANGLES, 6, 3);
	setpickingdrawfocus(view, holder, ARROW_BOTTOM);
	mesh.draw(GL_TRIANGLES, 9, 3);
}

void Barrier::drawHoverHighlights(treenode view)
{
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

	float black[4] = {0.4f, 0.4f, 0.4f, 1.0f};
	if (isActive) {
		black[0] += 0.2f;
		black[1] += 0.2f;
		black[2] += 0.2f;
		z += 0.001 / getmodelunit(LENGTH_MULTIPLE);
	} else if (isHovered) {
		black[0] += 0.3f;
		black[1] += 0.3f;
		black[2] += 0.3f;
		z += 0.002 / getmodelunit(LENGTH_MULTIPLE);
	}


	float bottomLeft[3] = {(float)myMin.x, (float)myMin.y, z};
	float topRight[3] = { (float)myMax.x, (float)myMax.y, z };
	float topLeft[3] = { (float)myMin.x, (float)myMax.y, z };
	float bottomRight[3] = { (float)myMax.x, (float)myMin.y, z};

	addMeshTriangle(barrierMesh, bottomRight, topLeft, bottomLeft, black, &nrVerts);
	addMeshTriangle(barrierMesh, bottomRight, topRight, topLeft, black, &nrVerts);
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

		int pickType = getpickingdrawfocus(view, PICK_TYPE, 0);
		if (pickType != 0) {
			arrow = pickType;
			mode = Barrier::POINT_EDIT;
			switch (pickType) {
				case ARROW_LEFT: activePointIndex = 0; break;
				case ARROW_RIGHT: activePointIndex = 1; break;
				case ARROW_TOP: activePointIndex = 1; break;
				case ARROW_BOTTOM: activePointIndex = 0; break;
			}
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

double Barrier::onClick(treenode view, int clickCode)
{
	AStarNavigator* nav = navigator;
	// is there a current barrier
	if (objectexists(nav->activeBarrier)) {
		Barrier* b = nav->activeBarrier->objectAs(Barrier);
		// is the clicked barrier different than the current barrier
		if (b != this) {
			// Send the click to the activeBarrier if it's in create mode
			if (mode & Barrier::CREATE) {
				Vec3 pos(cursorinfo(view, 2, 1, 1), cursorinfo(view, 2, 2, 1), cursorinfo(view, 2, 3, 1));
				return b->onClick(view, (int)clickcode, pos);
			}

			// then reset the current barrier to be "not active"
			b->activePointIndex = 0;
			b->isActive = 0;
		}
	}
	// set the active barrier to the clicked barrier
	nav->activeBarrier = holder;
	isActive = 1;
	nav->setDirty();
	Vec3 pos(cursorinfo(view, 2, 1, 1), cursorinfo(view, 2, 2, 1), cursorinfo(view, 2, 3, 1));
	return onClick(view, clickCode, pos);
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

double Barrier::onDrag(treenode view)
{
	double dx = draginfo(DRAG_INFO_DX);
	double dy = draginfo(DRAG_INFO_DY);
	double dz = draginfo(DRAG_INFO_DZ);
	onMouseMove(Vec3(cursorinfo(view, 2, 1, 1), cursorinfo(view, 2, 2, 1), 0), Vec3(dx, dy, dz));
	navigator->setDirty();
	return 1;
}

unsigned int Barrier::getClassType()
{
	return CLASSTYPE_WANTCONNECTLOGIC;
}

double Barrier::dragConnection(TreeNode * connectTo, char keyPressed, unsigned int classType)
{
	return navigator->dragConnection(connectTo, keyPressed, classType, this);
}

double Barrier::onDestroy(TreeNode * view)
{
	navigator->setDirty();
	return 0.0;
}

double Barrier::onUndo(bool isUndo, treenode undoRecord)
{
	AStarNavigator* nav = navigator;
	if (nav)
		nav->setDirty();

	// Stop barrier creation
	if (mode & Barrier::CREATE) {
		if (pointList.size() > 2) {
			removePoint(min(activePointIndex, pointList.size() - 1));
			activePointIndex = pointList.size();
			mode = 0;
		}
		else
			destroyobject(holder);
	}
	else {
		// Fix active point index
		if (activePointIndex > pointList.size())
			activePointIndex = pointList.size();
	}
	return 0.0;
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

Vec3 Barrier::getPointCoords(int pointIndex)
{
	if (pointIndex >= pointList.size())
		throw "Invalid Barrier point index";

	Point* point = pointList[pointIndex];
	return Vec3(point->x, point->y, point->z);
}

ASTAR_FUNCTION Variant Barrier::getPointCoord(FLEXSIMINTERFACE)
{
	Vec3 coord = getPointCoords((int)param(1));
	int coordID = param(2);
	if (coordID == POINT_X)
		return coord.x;
	if (coordID == POINT_Y)
		return coord.y;
	if (coordID == POINT_Z)
		return coord.z;

	return 0.0;
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
	if (isActive) {
		theColor[0] = color.r;
		theColor[1] = color.g;
		theColor[2] = color.b;
		lightGray[0] = 0.6f;
		lightGray[1] = 0.6f;
		lightGray[2] = 0.6f;
		z += 0.001 / getmodelunit(LENGTH_MULTIPLE);
	}
	else if (isHovered) {
		theColor[0] = min(1.0f, color.r + 0.1f);
		theColor[1] = min(1.0f, color.g + 0.1f);
		theColor[2] = min(1.0f, color.b + 0.1f);
		lightGray[0] = 0.7f;
		lightGray[1] = 0.7f;
		lightGray[2] = 0.7f;
		z += 0.002 / getmodelunit(LENGTH_MULTIPLE);
	}
	nrVerts = 0;
	meshOffset = barrierMesh->numVerts;

	// Add circles at each node
	float radius = nodeWidth * 0.15;
	for (int i = 0; i < pointList.size(); i++) {
		pointList[i]->addVertices(barrierMesh, radius, lightGray, z, &nrVerts);
	}

	// Draw a series of triangles
	float maxTriangleWidth = nodeWidth;
	float distToRect = 0;// 0.4 * nodeWidth;
	float distToCorner = sqrt(distToRect * distToRect + radius * radius);
	float height = 2 * radius;
	bool isBridge = toBridge() ? true : false;
	float dTheta = atan2(radius, distToRect);

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
		float bottomLeft[3] = { distToCorner * cos(theta - dTheta) + (float)point->x,
			distToCorner * sin(theta - dTheta) + (float)point->y, pointZ };

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

void Barrier::onReset(AStarNavigator * nav)
{
	conditionalBarrierChanges = TemporaryBarrier(nav);
}


void Barrier::addPatternRow()
{
	Table table(patternTable);
	int numRowsBefore = table.numRows;
	table.addRow();
	if (table.numCols == 0)
		table.addCol();

	for (int col = 1; col <= table.numCols; col++) {
		treenode cell = table.cell(table.numRows, col);
		cell->addSimpleData(new PatternCell, true);
	}
}

void Barrier::addPatternCol()
{
	Table table(patternTable);
	int numRowsBefore = table.numRows;
	if (table.numRows == 0)
		table.addRow();
	table.addCol();

	for (int row = 1; row <= table.numRows; row++) {
		treenode cell = table.cell(row, table.numCols);
		cell->addSimpleData(new PatternCell, true);
	}
}

void Barrier::deletePatternRow()
{
	Table table(patternTable);
	if (table.numRows > 0)
		table.deleteRow(table.numRows);
}

void Barrier::deletePatternCol()
{
	Table table(patternTable);
	if (table.numCols > 0)
		table.deleteCol(table.numCols);
}

void Barrier::PatternCell::bind()
{
	bindDouble(width, 1);
	bindDouble(height, 1);
	bindDouble(canGoUp, 1);
	bindDouble(canGoDown, 1);
	bindDouble(canGoLeft, 1);
	bindDouble(canGoRight, 1);
}

}
