#include "OneWayDivider.h"


const char * OneWayDivider::getClassFactory(void)
{
	return "AStar::OneWayDivider";
}


void OneWayDivider::bind(void)
{
	Divider::bind();
}

void OneWayDivider::modifyTable(AStarNode* edgeTable, double c0, double r0, 
								unsigned int edgeTableXSize, unsigned int edgeTableYSize)
{

}

void OneWayDivider::addVertices(Mesh* barrierMesh, float z)
{
	float dark[3] = {0.4f, 0.4f, 0.4f};
	float light[3] = {0.6f, 0.6f, 0.6f};
	float highlight[3] = {0.3f, 0.3f, 0.3f};
	if (isActive) {
		dark[0] += 0.2f;
		dark[1] += 0.2f;
		dark[2] += 0.2f;
		light[0] += 0.2f;
		light[1] += 0.2f;
		light[2] += 0.2f;
	}
	nrVerts = 0;
	meshOffset = barrierMesh->nrVerts;

	// Add circles at each node
	const float TWO_PI = 2 * 3.1415926536f;
	int numSides = 20;
	float radius = nodeWidth * 0.3;
	float dTheta = TWO_PI / numSides;

	for (int i = 0; i < pointList.size(); i++) {
		float center[3] = {pointList[i]->x, pointList[i]->y, z};

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
				barrierMesh->setVertexAttrib(vertName, MESH_EMISSIVE, activeColor);\
			else\
				barrierMesh->setVertexAttrib(vertName, MESH_EMISSIVE, color);\
			barrierMesh->setVertexAttrib(vertName, MESH_POSITION, pos);\
		}

			ABV(center, dark, highlight);
			ABV(pos1, dark, highlight);
			ABV(pos2, dark, highlight);

		}

		// Draw the last triangle using first and last coords
		float lastTheta = (numSides - 1) * dTheta;
		float pos2[3] = {radius + center[0], center[1], z};
		float pos1[3] = {radius * cos(lastTheta) + center[0], radius * sin(lastTheta) + center[1], z};
		ABV(center, dark, highlight);
		ABV(pos1, dark, highlight);
		ABV(pos2, dark, highlight);
	}
#undef ABV
	// Draw alternating light and dark triangles

	float maxTriangleWidth = 2 * nodeWidth;
	float distToRect = 0.4 * nodeWidth;
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
		
		// Find how many will fit, and stretch them to fit.
		int numLightTriangles = length / maxTriangleWidth;
		float lightTriangleWidth = length / numLightTriangles;
		float ltw = lightTriangleWidth;
		float numTriangles = 2 * numLightTriangles + 1;

		// Use the bottomleft corner of the rectangle to get every other corner
		float bottomLeft[3] = {distToCorner * cos(theta - dTheta) + point->x, 
			distToCorner * sin(theta - dTheta) + point->y, z};

		float topLeft[3] = {bottomLeft[0] - height * sin(theta), 
			bottomLeft[1] + height * cos(theta), z};

		float bottomRight[3] = {bottomLeft[0] + length * cos(theta),
			bottomLeft[1] + length * sin(theta), z};

		float topRight[3] = {bottomRight[0] - height * sin(theta),
			bottomRight[1] + height * cos(theta), z};

		float pos1[3] = {bottomLeft[0], bottomLeft[1], bottomLeft[2]};
		float pos2[3] = {bottomLeft[0] + 0.5 * ltw * cos(theta), bottomLeft[1] + 0.5 * ltw * sin(theta), z};
		float pos3[3] = {topLeft[0], topLeft[1], topLeft[2]};
		
		// Draw the triangles in a triangle strip fashion, keeping the
		// in common points between light and dark triangles
		for (int j = 0; j < numTriangles; j++) {

#define ABV(pos, color)  {\
			int vertName = barrierMesh->addVertex();\
			nrVerts++;\
			barrierMesh->setVertexAttrib(vertName, MESH_EMISSIVE, color);\
			barrierMesh->setVertexAttrib(vertName, MESH_POSITION, pos);\
		}

#define ABT(pos1, pos2, pos3, color) ABV(pos1, color) ABV(pos2, color) ABV(pos3, color)

#define COPY2(src, dest) dest[0] = src[0]; dest[1] = src[1];

			// Alternating colors
			if (j % 2) {
				// This one is drawn first
				ABT(pos1, pos2, pos3, dark);
				COPY2(pos2, pos1);
				pos2[0] = pos1[0] + 0.5 * ltw * cos(theta);
				pos2[1] = pos2[1] + 0.5 * ltw * sin(theta);

			} else {
				ABT(pos1, pos2, pos3, light);
				COPY2(pos2, pos3);
				pos2[0] = pos1[0] + ltw * cos(theta);
				pos2[1] = pos1[1] + ltw * sin(theta);
				if (j == numTriangles - 1) {
					pos2[0] = pos1[0] + 0.5 * ltw * cos(theta);
					pos2[1] = pos2[1] + 0.5 * ltw * sin(theta);
				}
			}
		}
#undef COPY2
#undef ABT
#undef ABV
	}
}