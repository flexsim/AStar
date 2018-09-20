#include "Point.h"
#include "Barrier.h"

namespace AStar {

const char * Point::getClassFactory(void)
{
	return "AStar::Point";
}


void Point::bind(void)
{
	SimpleDataType::bind();

	bindDouble(x, 1);
	bindDouble(y, 1);
	bindDouble(z, 1);
}

void Point::addVertices(Mesh * mesh, float radius, float * color, float zOffset, bool linesOnly, unsigned int* incNumVerts)
{
	const float TWO_PI = 2 * 3.1415926536f;
	int numSides = 20;
	float dTheta = TWO_PI / numSides;
	float z = (float)this->z + zOffset;
	float center[3] = { (float)x, (float)y, z};

	// For each side, draw a triangle
	for (int j = 0; j < numSides - 1; j++) {
		float theta = j * dTheta;
		float x = radius * cos(theta) + center[0];
		float y = radius * sin(theta) + center[1];
		float x2 = radius * cos(theta + dTheta) + center[0];
		float y2 = radius * sin(theta + dTheta) + center[1];

		float pos1[3] = { x, y, z };
		float pos2[3] = { x2, y2, z };

		if (!linesOnly)
			Barrier::addMeshVertex(mesh, center, color, incNumVerts);
		Barrier::addMeshVertex(mesh, pos1, color, incNumVerts);
		Barrier::addMeshVertex(mesh, pos2, color, incNumVerts);
	}

	// Draw the last triangle using first and last coords
	float lastTheta = (numSides - 1) * dTheta;
	float pos2[3] = { radius + center[0], center[1], z };
	float pos1[3] = { radius * cos(lastTheta) + center[0], radius * sin(lastTheta) + center[1], z };
	if (!linesOnly)
		Barrier::addMeshVertex(mesh, center, color, incNumVerts);
	Barrier::addMeshVertex(mesh, pos1, color, incNumVerts);
	Barrier::addMeshVertex(mesh, pos2, color, incNumVerts);

}

}