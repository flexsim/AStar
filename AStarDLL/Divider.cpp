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
			Vec3(point->x, point->y, point->z),
			Vec3(nextPoint->x, nextPoint->y, nextPoint->z),
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
	drawManipulationHandles(view, 0.001 / getmodelunit(LENGTH_MULTIPLE));
}

void Divider::addVertices(treenode view, Mesh* barrierMesh, float z, DrawStyle drawStyle)
{
	Vec4f baseColor(0.4f, 0.4f, 0.4f, 1.0f);
	switch (drawStyle) {
	case Highlighted: 
		case Hovered:
			baseColor = Vec4f(1.0f, 1.0f, 0.0f, drawStyle == Highlighted ? 1.0f : 0.5f);
			z += 0.001 / getmodelunit(LENGTH_MULTIPLE);
			break;
		case Selected:
			baseColor = Vec4f(1.0f, 0.0f, 0.0f, 1.0f);
			z += 0.002 / getmodelunit(LENGTH_MULTIPLE);
			break;
		default: break;
	}
	float radius = nodeWidth * 0.15;
	if (!isTwoWay || drawStyle != Basic) {
		nrVerts = 0;
		meshOffset = barrierMesh->numVerts;

		// Add circles at each node

		for (int i = 0; i < pointList.size(); i++) {
			Point* point = pointList[i];
			if (drawStyle == Basic 
					|| (getpickingdrawfocus(view, PICK_TYPE, PICK_HOVERED) == PICK_POINT 
						&& tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_HOVERED)) == point->holder))
				point->addVertices(barrierMesh, radius, baseColor, z, drawStyle != Basic, &nrVerts);
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
				addMeshTriangle(barrierMesh, bottomLeft, topRight, topLeft, baseColor, &nrVerts);
				addMeshTriangle(barrierMesh, bottomLeft, bottomRight, topRight, baseColor, &nrVerts);
			} else {
				//addMeshLine(barrierMesh, bottomLeft, topLeft, baseColor, &nrVerts);
				addMeshLine(barrierMesh, topLeft, topRight, baseColor, &nrVerts);
				//addMeshLine(barrierMesh, topRight, bottomRight, baseColor, &nrVerts);
				addMeshLine(barrierMesh, bottomRight, bottomLeft, baseColor, &nrVerts);
			}
		}
	} else {
		float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
		float lightGray[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
		if (drawStyle == Highlighted) {
			green[0] = 0.2f;
			green[2] = 0.2f;
			lightGray[0] = 0.6f;
			lightGray[1] = 0.6f;
			lightGray[2] = 0.6f;
			z += 0.001 / getmodelunit(LENGTH_MULTIPLE);
		}
		else if (drawStyle == Hovered) {
			green[0] = 0.2f;
			green[2] = 0.2f;
			lightGray[0] = 0.7f;
			lightGray[1] = 0.7f;
			lightGray[2] = 0.7f;
			z += 0.002 / getmodelunit(LENGTH_MULTIPLE);
		}
		nrVerts = 0;
		meshOffset = barrierMesh->numVerts;

		for (int i = 0; i < pointList.size(); i++) {
			pointList[i]->addVertices(barrierMesh, radius, lightGray, z, &nrVerts);
		}
		// Draw alternating light and dark triangles

		float maxTriangleWidth = 2 * nodeWidth;
		float distToRect = 0;// 0.4 * nodeWidth;
		float distToCorner = sqrt(distToRect * distToRect + radius * radius);
		float height = 2 * radius;
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

			float sinTheta = sin(theta);
			float cosTheta = cos(theta);
			// Find how many will fit, and stretch them to fit.
			int numLightTriangles = (int)(length / maxTriangleWidth);
			if (numLightTriangles < 1) {
				numLightTriangles = 1;
			}
			float lightTriangleWidth = length / numLightTriangles;
			float ltw = lightTriangleWidth;
			int numTriangles = 2 * numLightTriangles + 1;


			// Use the bottomleft corner of the rectangle to get every other corner
			float bottomLeft[3] = { distToCorner * cos(theta - dTheta) + (float)point->x,
				distToCorner * sin(theta - dTheta) + (float)point->y, z };

			float topLeft[3] = { bottomLeft[0] - height * sinTheta,
				bottomLeft[1] + height * cosTheta, z };

			float bottomRight[3] = { bottomLeft[0] + length * cos(theta),
				bottomLeft[1] + length * sin(theta), z };

			float topRight[3] = { bottomRight[0] - height * sinTheta,
				bottomRight[1] + height * cosTheta, z };

			float pos0[3] = { bottomLeft[0], bottomLeft[1], bottomLeft[2] };
			float pos1[3] = { bottomLeft[0] + 0.5f * ltw * cosTheta - height * sinTheta,
				topLeft[1] + 0.5f * ltw * sinTheta, z };
			float pos2[3] = { topLeft[0], topLeft[1], topLeft[2] };
			float currentX = 0.5f * ltw;
			// Draw the triangles in a triangle strip fashion, keeping the
			// in common points between light and dark triangles
			for (int j = 0; j < numTriangles; j++) {

#define ABV(pos, color)  {\
			int vertName = barrierMesh->addVertex();\
			nrVerts++;\
			barrierMesh->setVertexAttrib(vertName, MESH_DIFFUSE4, color);\
			barrierMesh->setVertexAttrib(vertName, MESH_POSITION, pos);\
		}

#define ABT(pos1, pos2, pos3, color) ABV(pos1, color) ABV(pos2, color) ABV(pos3, color)

				currentX += 0.5 * ltw;
				// Set the points for next round
				if (j % 2 == 0) {
					// Draw the dark (top) triangle
					ABT(pos0, pos1, pos2, lightGray);

					// Calculate the far right corner of the bottom triangle
					float newX = currentX;
					float newY = 0;

					float rotatedX = newX * cosTheta - newY * sinTheta;
					float rotatedY = newX * sinTheta + newY * cosTheta;

					newX = rotatedX + bottomLeft[0];
					newY = rotatedY + bottomLeft[1];

					pos2[0] = pos1[0];
					pos2[1] = pos1[1];
					pos1[0] = newX;
					pos1[1] = newY;
				}
				else {
					// Draw the light (bottom) triangle
					ABV(pos0, green); ABV(pos1, lightGray); ABV(pos2, lightGray);

					// Calculate the far right corner of the top triangle
					// New vertex location: find the new point in local coords,
					// rotate it, and then set p1 to it
					float newX = currentX;
					float newY = height;

					if (newX > length)
						newX = length;

					float rotatedX = newX * cosTheta - newY * sinTheta;
					float rotatedY = newX * sinTheta + newY * cosTheta;

					newX = rotatedX + bottomLeft[0];
					newY = rotatedY + bottomLeft[1];

					pos0[0] = pos1[0];
					pos0[1] = pos1[1];
					pos1[0] = newX;
					pos1[1] = newY;
				}
			}
#undef COPY2
#undef ABT
#undef ABV
		}

	}
}

double Divider::onClick(treenode view, int clickCode, Vec3& pos)
{
	if (clickCode == LEFT_PRESS && !(mode & Barrier::CREATE)) {
		// If the click is on a node, make that the active node
		int clickedIndex = -1;

		int pickType = getpickingdrawfocus(view, PICK_TYPE, PICK_PRESSED);
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
				setpickingdrawfocus(view, holder, PICK_POINT, pointList.front()->holder, OVERRIDE_SET_MOUSE_DOWN_PICK);
			}
			else if (activePointIndex == pointList.size() - 1) {
				// Add undo record
				if (pointList.size() > 2 && lastMode & Barrier::CREATE)
					addCreatePointRecord(view, pointList[activePointIndex]);
				// Add to the end of the pointlist
				addPoint(pos);
				activePointIndex = pointList.size() - 1;
				setpickingdrawfocus(view, holder, PICK_POINT, pointList.back()->holder, OVERRIDE_SET_MOUSE_DOWN_PICK);
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

double Divider::onMouseMove(treenode view, Vec3& pos, Vec3& diff)
{
	int pickType = getpickingdrawfocus(view, PICK_TYPE, 0);
	treenode pointNode = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_PRESSED));
	if (pickType == PICK_POINT && pointNode) {
		Point* activePoint = pointNode->objectAs(Point);
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
	} else {
		// Snap between grid points
		if (o(AStarNavigator, ownerobject(holder)).snapBetweenGrid && !toPreferredPath() && !toBridge() && !toMandatoryPath()) {
			diff.x = floor((pos.x + 0.5 * nodeWidth) / nodeWidth) * nodeWidth
				- floor((pos.x - diff.x + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
			diff.y = floor((pos.y + 0.5 * nodeWidth) / nodeWidth) * nodeWidth
				- floor((pos.y - diff.y + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
		}
		for (int i = 0; i < pointList.size(); i++) {
			pointList[i]->x += diff.x;
			pointList[i]->y += diff.y;
			pointList[i]->z += diff.z;
		}
		updateSpatialsToEncompassPoints();
	}

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