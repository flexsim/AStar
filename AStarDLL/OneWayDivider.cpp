#include "OneWayDivider.h"
#include "AStarNavigator.h"

namespace AStar {

OneWayDivider::OneWayDivider()
	: Divider()
{
	return;
}

const char * OneWayDivider::getClassFactory(void)
{
	return "AStar::OneWayDivider";
}


void OneWayDivider::bind(void)
{
	Divider::bind();
}

void OneWayDivider::addBarriersToTable(AStarNavigator* nav)
{
	Point* point = pointList[0];
	Point* nextPoint;

	// Add each segment of pointList to the edge table as a one way divider
	for (int i = 0; i < pointList.size() - 1; i++, point = nextPoint) {
		nextPoint = pointList[i + 1];

		nav->divideGridModelLine(
			Vec3(point->x, point->y, point->z),
			Vec3(nextPoint->x, nextPoint->y, nextPoint->z),
			true
		);
	}
}

void OneWayDivider::addVertices(Mesh* barrierMesh, float z)
{
	float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float lightGray[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	float darkGray[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	float black[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	if (isActive) {
		green[0] = 0.2f;
		green[2] = 0.2f;
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
		green[0] = 0.2f;
		green[2] = 0.2f;
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
		float pos2[3] = {radius + center[0], center[1], z};
		float pos1[3] = {radius * cos(lastTheta) + center[0], radius * sin(lastTheta) + center[1], z};
		ABV(center, darkGray, black);
		ABV(pos1, darkGray, black);
		ABV(pos2, darkGray, black);
	}
#undef ABV
	// Draw alternating light and dark triangles

	float maxTriangleWidth = 2 * nodeWidth;
	float distToRect = 0;// 0.4 * nodeWidth;
	float distToCorner = sqrt(distToRect * distToRect + radius * radius);
	float height = 2 * radius;
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
		float bottomLeft[3] = {distToCorner * cos(theta - dTheta) + point->x, 
			distToCorner * sin(theta - dTheta) + point->y, z};

		float topLeft[3] = {bottomLeft[0] - height * sinTheta, 
			bottomLeft[1] + height * cosTheta, z};

		float bottomRight[3] = {bottomLeft[0] + length * cos(theta),
			bottomLeft[1] + length * sin(theta), z};

		float topRight[3] = {bottomRight[0] - height * sinTheta,
			bottomRight[1] + height * cosTheta, z};

		float pos0[3] = {bottomLeft[0], bottomLeft[1], bottomLeft[2]};
		float pos1[3] = {bottomLeft[0] + 0.5 * ltw *cosTheta - height * sinTheta, 
			topLeft[1] + 0.5 * ltw * sinTheta, z};
		float pos2[3] = {topLeft[0], topLeft[1], topLeft[2]};
		float currentX = 0.5 * ltw;
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
			} else {
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