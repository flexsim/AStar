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
	double x = pointList[0]->x;
	double y = pointList[0]->y;
	double c0 = nav->gridOrigin.x;
	double r0 = nav->gridOrigin.y;
	// here I assume the row/column number represents the slot above / right of the
	// corner I am working on 
	int col = (int)round(((x - c0) / nodeWidth) + 0.5);
	int row = (int)round(((y - r0) / nodeWidth) + 0.5);

	double nextX, nextY;
	int nextCol, nextRow;
	for (int i = 0; i < pointList.size() - 1; 
		i++, x = nextX, y = nextY, row = nextRow, col = nextCol) {
		
		nextX = pointList[i + 1]->x;
		nextY = pointList[i + 1]->y;

		// calculate the column and row numbers for that point (again, above/right of the current corner)
		nextCol = (int)round(((nextX - c0) / nodeWidth) + 0.5);
		nextRow = (int)round(((nextY - r0) / nodeWidth) + 0.5);

		// set dx and dy, the differences between the rows and columns
		double dx = nextCol - col;
		double dy = nextRow - row;
		
		if(dy == 0 && dx == 0)
			continue;

		// figure out the unit increment (either -1 or 1) for traversing from the
		// current point to the next point
		int colInc = (int)sign(dx);
		if(colInc == 0) 
			colInc = 1;

		int rowInc = (int)sign(dy);
		if(rowInc == 0) 
			rowInc = 1;

		// prevent divide by zero errors
		if(dx == 0) dx = 0.01;
		// get the slope of the line
		double goalSlope = dy/dx;

		int currCol = col;
		int currRow = row;
		// now step through the line, essentially walking along the edges of the grid tiles
		// under the line, and set the divider by zeroing out the bits on each side of the line
		// I'm walking on
		while(currCol != nextCol || currRow != nextRow) {

			// the way that I essentially move along the line
			// is at each grid point, I do a test step horizontally, 
			// and a test step vertically, and then test the new slope of the line to the 
			// destination for each of those test steps. Whichever line's slope is closest
			// to the actual slope represents the step I want to take.
			int testCol = currCol + colInc;
			int testRow = currRow + rowInc;
			double dxTestCol = nextCol - testCol;
			if(dxTestCol == 0) dxTestCol = 0.01;
			double dxTestRow = nextCol - currCol;
			if(dxTestRow == 0) dxTestRow = 0.01;
			
			double colIncSlope = (nextRow - currRow)/dxTestCol;
			double rowIncSlope = (nextRow - testRow)/dxTestRow;
			
			int nextCurrCol, nextCurrRow;
			if(fabs(colIncSlope - goalSlope) <= fabs(rowIncSlope - goalSlope)) {
				// move over one column
				nextCurrCol = testCol;
				nextCurrRow = currRow;
				

				int modifyCol = min(nextCurrCol, currCol);
				if(dx > 0)
					nav->getNode(currRow, modifyCol)->canGoDown = 0;
				if(dx < 0)
					nav->getNode(currRow - 1, modifyCol)->canGoUp = 0;
				
			} else {
				nextCurrCol = currCol;
				nextCurrRow = testRow;
				
				int modifyRow = min(nextCurrRow, currRow);
				if(dy < 0)
					nav->getNode(modifyRow, currCol)->canGoLeft = 0;
				if(dy > 0)
					nav->getNode(modifyRow, currCol - 1)->canGoRight = 0;
			}
			
			currCol = nextCurrCol;
			currRow = nextCurrRow;
		}
	}
}

void OneWayDivider::addVertices(Mesh* barrierMesh, float z)
{
	float dark[4] = {0.4f, 0.4f, 0.4f, 1.0f};
	float light[4] = {0.0, 1.0f, 0.0f, 1.0f};
	float highlight[4] = {0.3f, 0.3f, 0.3f, 1.0f};
	if (isActive) {
		dark[0] += 0.2f;
		dark[1] += 0.2f;
		dark[2] += 0.2f;
		light[0] += 0.2f;
		light[2] += 0.2f;
	}
	nrVerts = 0;
	meshOffset = barrierMesh->numVerts;

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
				ABT(pos0, pos1, pos2, dark);

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
				ABV(pos0, light); ABV(pos1, dark); ABV(pos2, dark);

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