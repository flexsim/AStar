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
		Vec3 point = getPointCoords(i);

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
			false, this
		);
	}
}

void Divider::drawManipulationHandles(treenode view, float zOffset)
{
	Mesh mesh;
	// Add circles at each node
	float radius = nodeWidth * 0.15;
	float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	for (int i = 0; i < pointList.size(); i++) {
		mesh.init(0, MESH_POSITION | MESH_DIFFUSE4);
		pointList[i]->addVertices(&mesh, radius, black, zOffset);
		setpickingdrawfocus(view, holder, PICK_DIVIDER_POINT, pointList[i]->holder);
		mesh.draw(GL_TRIANGLES);
	}
}

void Divider::drawManipulationHandles(treenode view)
{
	drawManipulationHandles(view, 0.001 / getmodelunit(LENGTH_MULTIPLE));
}

void Divider::drawHoverHighlights(treenode view)
{
	drawManipulationHandles(view, 0.002 / getmodelunit(LENGTH_MULTIPLE));
}

void Divider::addVertices(Mesh* barrierMesh, float z)
{
	float lightGray[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	if (isActive) {
		lightGray[0] = 0.6f;
		lightGray[1] = 0.6f;
		lightGray[2] = 0.6f;
		z += 0.001 / getmodelunit(LENGTH_MULTIPLE);
	} else if (isHovered) {
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

	// For each pair of points, draw a rectangle in between
	float distToRect = 0;// 0.4 * nodeWidth;
	float distToCorner = sqrt(distToRect * distToRect + radius * radius);
	float dTheta = atan2(radius, distToRect);
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
		float bottomLeft[3] = {distToCorner * cos(theta - dTheta) + (float)point->x,
			distToCorner * sin(theta - dTheta) + (float)point->y, point->z + z};

		float topLeft[3] = {bottomLeft[0] - height * sin(theta), 
			bottomLeft[1] + height * cos(theta), point->z + z};

		float bottomRight[3] = {bottomLeft[0] + length * cos(theta),
			bottomLeft[1] + length * sin(theta), point->z + z};

		float topRight[3] = {bottomRight[0] - height * sin(theta),
			bottomRight[1] + height * cos(theta), point->z + z};

		addMeshTriangle(barrierMesh, bottomLeft, topRight, topLeft, lightGray, &nrVerts);
		addMeshTriangle(barrierMesh, bottomLeft, bottomRight, topRight, lightGray, &nrVerts);
	}
}

double Divider::onClick(treenode view, int clickCode, Vec3& pos)
{
	if (clickCode == LEFT_PRESS && !(mode & Barrier::CREATE)) {
		// If the click is on a node, make that the active node
		int clickedIndex = -1;

		int pickType = getpickingdrawfocus(view, PICK_TYPE, 0);
		if (pickType == PICK_DIVIDER_POINT) {
			treenode point = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, 0));
			applicationcommand("addundotracking", view, node("x", point));
			applicationcommand("addundotracking", view, node("y", point));
			clickedIndex = point->rank - 1;
		} else {
			for (int i = 0; i < pointList.size(); i++) {
				applicationcommand("addundotracking", view, node("x", pointList[i]->holder));
				applicationcommand("addundotracking", view, node("y", pointList[i]->holder));
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
	if ((mode & Barrier::POINT_EDIT) && activePointIndex < pointList.size()) {
		Point* activePoint = pointList[(int)activePointIndex];
		// Snap between grid points
		if (o(AStarNavigator, ownerobject(holder)).snapBetweenGrid && !toPreferredPath() && !toBridge() && !toMandatoryPath()) {
			activePoint->x = floor((pos.x + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
			activePoint->y = floor((pos.y + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
		}
		else {
			activePoint->x += diff.x;
			activePoint->y += diff.y;
		}
		if (toBridge())
			activePoint->z += diff.z;
	} else if (mode & Barrier::MOVE) {
		double diffX = diff.x;
		double diffY = diff.y;
		for (int i = 0; i < pointList.size(); i++) {
			// Snap between grid points
			if (o(AStarNavigator, ownerobject(holder)).snapBetweenGrid && !toPreferredPath() && !toBridge() && !toMandatoryPath()) {
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

double Divider::onDestroy(TreeNode * view)
{
	navigator->setDirty();
	if (mode == 0 && pointList.size() > 2
		&& activePointIndex != pointList.size()) {
		// Remove a divider point
		removePoint(activePointIndex);
		// Set the previous point as the active
		if (activePointIndex != 0)
			activePointIndex -= 1;
		return 1.0;
	}
	return 0.0;
}

}