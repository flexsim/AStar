#include "Divider.h"
#include "macros.h"
#include "AStarNavigator.h"

namespace AStar {

Divider::Divider()
	: Barrier()
{
	return;
}


void Divider::bindVariables(void)
{
	__super::bindVariables();
	bindVariable(isTwoWay);
}

void Divider::init(double nodeWidth, const Vec3& pos1, const Vec3& pos2)
{
	Barrier::init(nodeWidth, pos1, pos2);
}

bool Divider::getLocalBoundingBox(Vec3& min, Vec3& max)
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
			point->project(holder, model()),
			nextPoint->project(holder, model()),
			!isTwoWay, this
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
		pointList[i]->addVertices(&mesh, radius, black, false, zOffset);
		setpickingdrawfocus(view, holder, PICK_POINT, pointList[i]->holder);
		mesh.draw(GL_TRIANGLES);
	}
}

void Divider::drawManipulationHandles(treenode view)
{
	drawManipulationHandles(view, 0.005 / getmodelunit(LENGTH_MULTIPLE));
}

void Divider::addVertices(treenode view, Mesh* barrierMesh, float z, DrawStyle drawStyle)
{
	Vec4f baseColor(0.4f, 0.4f, 0.4f, 1.0f);
	Vec4f black(0.0f, 0.0f, 0.0f, 1.0f);
	float oneMillimeter = 0.001 / getmodelunit(LENGTH_MULTIPLE);
	switch (drawStyle) {
		case Highlighted: 
		case Hovered:
			baseColor = Vec4f(1.0f, 1.0f, 0.0f, drawStyle == Highlighted ? 1.0f : 0.5f);
			z += 3 * oneMillimeter;
			break;
		case Selected:
			baseColor = Vec4f(1.0f, 0.0f, 0.0f, 1.0f);
			z += 6 * oneMillimeter;
			break;
		default: break;
	}
	float radius = nodeWidth * 0.15;
	if (isTwoWay || drawStyle != Basic) {

		// Add circles at each node

		for (int i = 0; i < pointList.size(); i++) {
			Point* point = pointList[i];
			bool shouldDraw = drawStyle == Basic;
			if (!shouldDraw) {
				int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, PICK_HOVERED);
				if (pickType == PICK_POINT) {
					treenode hovered = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_HOVERED));
					if (point->holder == hovered)
						shouldDraw = true;
				}
			}
			if (shouldDraw)
				point->addVertices(barrierMesh, radius, drawStyle == Basic ? black : baseColor, z + 3 * oneMillimeter, drawStyle != Basic);
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
			Vec3f bottomLeft( distToCorner * cos(theta - dTheta) + (float)point->x,
				distToCorner * sin(theta - dTheta) + (float)point->y, (float)point->z + z );

			Vec3f topLeft( bottomLeft[0] - height * sin(theta),
				bottomLeft[1] + height * cos(theta), (float)point->z + z );

			Vec3f bottomRight( bottomLeft[0] + length * cos(theta),
				bottomLeft[1] + length * sin(theta), (float)point->z + z );

			Vec3f topRight( bottomRight[0] - height * sin(theta),
				bottomRight[1] + height * cos(theta), (float)point->z + z );

			if (drawStyle == Basic) {
				addMeshTriangle(barrierMesh, bottomLeft, topRight, topLeft, baseColor);
				addMeshTriangle(barrierMesh, bottomLeft, bottomRight, topRight, baseColor);
			} else {
				addMeshLine(barrierMesh, topLeft, topRight, baseColor);
				addMeshLine(barrierMesh, bottomRight, bottomLeft, baseColor);
			}
		}
	} else {
		// draw one-way barrier
		Vec4f green( 0.0f, 1.0f, 0.0f, 1.0f );
		Vec4f lightGray( 0.5f, 0.5f, 0.5f, 1.0f );

		for (int i = 0; i < pointList.size(); i++) {
			pointList[i]->addVertices(barrierMesh, radius, lightGray, z + 3 * oneMillimeter, false);
		}
		// Draw alternating light and dark triangles

		float maxTriangleWidth = 2 * nodeWidth;
		float distToCorner = radius;
		float height = 2 * radius;
		float dTheta = atan2(radius, 0.0f);
		for (int i = 0; i < pointList.size() - 1; i++) {
			Point* point = pointList[i];
			Point* next = pointList[i + 1];

			Vec3f fromPoint(*point);
			Vec3f toPoint(*next);
			Vec3f diff = toPoint - fromPoint;
			float angle = radianstodegrees(atan2(diff.y, diff.x));

			float lengthXY = sqrt(diff.x * diff.x + diff.y * diff.y);
			if (lengthXY <= 0)
				continue;

			// Find how many will fit, and stretch them to fit.
			int numLightTriangles = (int)(lengthXY / maxTriangleWidth);
			if (numLightTriangles < 1) {
				numLightTriangles = 1;
			}
			float lightTriangleWidth = lengthXY / numLightTriangles;
			Vec3f diffPerTriangle = diff / numLightTriangles;

			Vec3f topLeft = Vec3f(0.0f, radius, fromPoint.z).rotateXY(angle) + fromPoint;
			Vec3f bottomLeft = Vec3f(0.0f, -radius, fromPoint.z).rotateXY(angle) + fromPoint;
			Vec3f topRight = Vec3f(lightTriangleWidth, radius, fromPoint.z).rotateXY(angle) + fromPoint;
			Vec3f bottomRight = Vec3f(lightTriangleWidth, -radius, fromPoint.z).rotateXY(angle) + fromPoint;
			Vec3f topCenter = Vec3f(0.5f * lightTriangleWidth, radius, fromPoint.z).rotateXY(angle) + fromPoint;


			for (int i = 0; i < numLightTriangles; i++) {
				addMeshTriangle(barrierMesh, topCenter, topLeft, bottomLeft, lightGray);
				addMeshTriangle(barrierMesh, topCenter, bottomRight, topRight, lightGray);
				
				addMeshVertex(barrierMesh, bottomLeft, green);
				addMeshVertex(barrierMesh, bottomRight, lightGray);
				addMeshVertex(barrierMesh, topCenter, lightGray);

				topLeft += diffPerTriangle;
				bottomLeft += diffPerTriangle;
				topRight += diffPerTriangle;
				bottomRight += diffPerTriangle;
				topCenter += diffPerTriangle;
			}
		}
	}
}

double Divider::onClick(treenode view, int clickCode, Vec3& pos)
{
	if (clickCode == LEFT_PRESS && !(mode & Barrier::CREATE)) {
		// If the click is on a node, make that the active node
		int clickedIndex = -1;

		int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, PICK_PRESSED);
		if (pickType == PICK_POINT) {
			treenode point = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_PRESSED));
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

	return 0;
}

double Divider::dragPressedPick(treenode view, Vec3& modelPos, Vec3& diff)
{
	int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, 0);
	Vec3 localPos = modelPos.project(model(), holder);
	treenode pointNode = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_PRESSED));
	if (pickType == PICK_POINT && pointNode) {
		Point* activePoint = pointNode->objectAs(Point);
		// Snap between grid points
		if (o(AStarNavigator, ownerobject(holder)).snapBetweenGrid && !toPreferredPath() && !toBridge() && !toMandatoryPath()) {
			activePoint->x = floor((localPos.x + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
			activePoint->y = floor((localPos.y + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
		} else {
			activePoint->x += diff.x;
			activePoint->y += diff.y;
		}
		if (toBridge())
			activePoint->z += diff.z;
	} else {
		// Snap between grid points
		if (o(AStarNavigator, ownerobject(holder)).snapBetweenGrid && !toPreferredPath() && !toBridge() && !toMandatoryPath()) {
			diff.x = floor((localPos.x + 0.5 * nodeWidth) / nodeWidth) * nodeWidth
				- floor((localPos.x - diff.x + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
			diff.y = floor((localPos.y + 0.5 * nodeWidth) / nodeWidth) * nodeWidth
				- floor((localPos.y - diff.y + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
		}
		for (int i = 0; i < pointList.size(); i++) {
			pointList[i]->x += diff.x;
			pointList[i]->y += diff.y;
			pointList[i]->z += diff.z;
		}
	}
	updateSpatialsToEncompassPoints();
	isMeshDirty = true;

	return 1;
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
	isMeshDirty = true;
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

void Divider::drawPickObjects(treenode view)
{
	Mesh mesh;
	float radius = 0.15 * nodeWidth;
	float zOffset = 0.004 / getmodelunit(LENGTH_MULTIPLE);
	Vec4f color(0.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < pointList.length; i++) {
		mesh.init(0, MESH_POSITION | MESH_DIFFUSE4);
		Point* point = pointList[i];
		point->addVertices(&mesh, radius, color, zOffset, false);
		setpickingdrawfocus(view, holder, PICK_POINT, point->holder);
		mesh.draw(GL_TRIANGLES);
	}
}

}