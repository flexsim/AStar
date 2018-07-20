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

void Divider::init(double nodeWidth, const Vec3& pos1, const Vec3& pos2)
{
	Barrier::init(nodeWidth, pos1, pos2);
}

bool Divider::getBoundingBox(Vec3& min, Vec3& max)
{
	if (pointList.size() < 2)
		return false;

	min = Vec3(DBL_MAX, DBL_MAX, DBL_MAX);
	max = Vec3(-DBL_MAX, -DBL_MAX, -DBL_MAX);
	for (int i = 0; i < pointList.size(); i++) {
		Vec3 point;
		getPointCoords(i, point);

		min.x = min(min.x, point.x);
		max.x = max(max.x, point.x);
		min.y = min(min.y, point.y);
		max.y = max(max.y, point.y);
		min.z = min(min.z, point.z);
		max.z = max(max.z, point.z);
	}

	return true;
}
void Divider::addBarriersToTable(Grid* grid)
{
	Point* point = pointList[0];
	Point* nextPoint;

	// Add each segment of pointList to the edge table as a divider
	for (int i = 0; i < pointList.size() - 1; i++, point = nextPoint) {
		nextPoint = pointList[i + 1];
		
		grid->divideGridModelLine(
			Vec3(point->x, point->y, point->z),
			Vec3(nextPoint->x, nextPoint->y, nextPoint->z),
			false
		);
	}
}

void Divider::addVertices(Mesh* barrierMesh, float z)
{
	float lightGray[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	float darkGray[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	float black[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	if (isActive) {
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

	for (int i = 0; i < pointList.size(); i++) {
		float center[3] = {pointList[i]->x, pointList[i]->y, z + 0.001 / getmodelunit(LENGTH_MULTIPLE)};

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

double Divider::onClick(treenode view, int clickCode, Vec3& pos)
{
	if (clickCode == LEFT_PRESS && !(mode & Barrier::CREATE)) {
		// If the click is on a node, make that the active node
		int clickedIndex = -1;
		for (int i = 0; i < pointList.size(); i++) {
			applicationcommand("addundotracking", view, node("x", pointList[i]->holder));
			applicationcommand("addundotracking", view, node("y", pointList[i]->holder));

			double pointX = pointList[i]->x;
			double pointY = pointList[i]->y;
			double dx = pos.x - pointX;
			double dy = pos.y - pointY;

			double radius = nodeWidth * 0.15;
			if (sqrt(dx * dx + dy * dy) <= radius) {
				clickedIndex = i;
				break;
			}
		}

		if (clickedIndex > -1) {
			activePointIndex = clickedIndex;
			mode = Barrier::POINT_EDIT;
		
		} else {
			activePointIndex = pointList.size();
			mode = Barrier::MOVE;
		}
	}

	if (clickCode == LEFT_RELEASE) {
		// If creating, make a new point, and make it the active one
		if (mode & Barrier::CREATE) {
			// Snap between grid points
			if (o(AStarNavigator, ownerobject(holder)).snapBetweenGrid && !toPreferredPath() && !toBridge()) {
				pos.x = floor((pos.x + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
				pos.y = floor((pos.y + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
			}

			if (activePointIndex == 0) {
				// Add undo record
				if (pointList.size() > 2 && lastMode & Barrier::CREATE)
					addCreatePointRecord(view, pointList[activePointIndex]);
				// Add to the start of the pointlist
				pointList.unshift(new Point(pos.x, pos.y, pos.z));
				activePointIndex = 0;
			}
			else if (activePointIndex == pointList.size() - 1) {
				// Add undo record
				if (pointList.size() > 2 && lastMode & Barrier::CREATE)
					addCreatePointRecord(view, pointList[activePointIndex]);
				// Add to the end of the pointlist
				addPoint(pos);
				activePointIndex = pointList.size() - 1;
			}
			else {
				mode = 0;
			}
		} else {
			mode = 0;
		}
	}

	if (clickCode == RIGHT_RELEASE) {
		// Right click -> abort barrier creation
		if (mode & Barrier::CREATE) {
			removePoint(activePointIndex);
			mode = 0;
			activePointIndex = pointList.size();
			if (pointList.size() < 2)
				destroyobject(holder);
		}
	}

	lastMode = mode;

	return 0;
}

double Divider::onMouseMove(const Vec3& pos, const Vec3& diff)
{
	if (mode & Barrier::POINT_EDIT && activePointIndex < pointList.size()) {
		Point* activePoint = pointList[(int)activePointIndex];
		// Snap between grid points
		if (o(AStarNavigator, ownerobject(holder)).snapBetweenGrid && !toPreferredPath() && !toBridge()) {
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
	else if (mode & Barrier::MOVE) {
		double diffX = diff.x;
		double diffY = diff.y;
		for (int i = 0; i < pointList.size(); i++) {
			// Snap between grid points
			if (o(AStarNavigator, ownerobject(holder)).snapBetweenGrid && !toPreferredPath() && !toBridge()) {
				diffX = floor((pos.x + 0.5 * nodeWidth) / nodeWidth) * nodeWidth
					- floor((pos.x - diffX + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
				diffY = floor((pos.y + 0.5 * nodeWidth) / nodeWidth) * nodeWidth
					- floor((pos.y - diffY + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
			}
			pointList[i]->x += diffX;
			pointList[i]->y += diffY;
			if (toBridge())
				pointList[i]->z += diff.z;
		}
	}

	return 0;
}

void Divider::addCreatePointRecord(treenode view, Point* point)
{
	int undoId = beginaggregatedundo(view, "Create Divider Point");
	createundorecord(view, ownerobject(holder), UNDO_UPDATE_LINKS_ON_UNDO, 0, 0, 0);
	createundorecord(view, point->holder, UNDO_CREATE_OBJECT, 0, 0, 0);
	createundorecord(view, ownerobject(holder), UNDO_UPDATE_LINKS_ON_REDO, 0, 0, 0);
	endaggregatedundo(view, undoId);
}

}