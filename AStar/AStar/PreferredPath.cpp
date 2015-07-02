#include "PreferredPath.h"
#include "AStarNavigator.h"

PreferredPath::PreferredPath()
	: pathWeight(0.0)
	, Divider()
{
	return;
}

PreferredPath::PreferredPath(double pathWeight)
	: pathWeight(pathWeight)
	, Divider()
{
	return;
}

const char * PreferredPath::getClassFactory(void)
{
	return "AStar::PreferredPath";
}


void PreferredPath::bind(void)
{
	Divider::bind();
	bindDouble(pathWeight, 0);
}

void PreferredPath::addPassagesToTable(AStarNode* edgeTable, 
						  std::unordered_map<unsigned int, AStarNodeExtraData>* extraData, 
						  double c0, double r0, unsigned int edgeTableXSize, unsigned int edgeTableYSize)
{
	double x = pointList[0]->x;
	double y = pointList[0]->y;

	// here I assume the row/column number represents the tile of the row and column
	int col = (int)round((x - c0) / nodeWidth);
	int row = (int)round((y - r0) / nodeWidth);

	double nextX, nextY;
	int nextCol, nextRow;
	for (int i = 0; i < pointList.size() - 1; 
		i++, x = nextX, y = nextY, row = nextRow, col = nextCol) {
		
		nextX = pointList[i + 1]->x;
		nextY = pointList[i + 1]->y;

		// calculate the column and row numbers for that point
		nextCol = (int)round((nextX - c0) / nodeWidth);
		nextRow = (int)round((nextY - r0) / nodeWidth);

		// set dx and dy, the differences between the rows and columns
		double dx = nextCol - col;
		double dy = nextRow - row;
		
		if(dy == 0 && dx == 0)
			continue;

		// calculate the weight values for preferred paths.
		int horizontalWeight = (int)(pathWeight * 127 * dx / (fabs(dx) + fabs(dy)));
		int verticalWeight = (int)(pathWeight * 127 * dy / (fabs(dx) + fabs(dy)));

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
		// under the line
		while(currCol != nextCol || currRow != nextRow) {

			AStarSearchEntry e;
			e.col = currCol;
			e.row = currRow;
			AStarNodeExtraData * extra;
			auto extraIter = extraData->find(e.colRow);
			AStarNode& node = DeRefEdgeTable(e.row, e.col);
			if(extraIter == extraData->end()) {
				extra = &((*extraData)[e.colRow]);
				memset(extra, 0, sizeof(AStarNodeExtraData));
				extra->colRow = e.colRow;
				node.noExtraData = 0;
			} else {
				extra = &(extraIter->second);
			}
			extra->bonusRight = (char)maxof(-128,minof(127, extra->bonusRight + horizontalWeight));
			extra->bonusLeft = (char)maxof(-128,minof(127, extra->bonusLeft - horizontalWeight));
			extra->bonusUp = (char)maxof(-128,minof(127, extra->bonusUp + verticalWeight));
			extra->bonusDown = (char)maxof(-128,minof(127, extra->bonusDown - verticalWeight));

			if (dx > 0)
				node.canGoRight = true;
			if (dx < 0)
				node.canGoLeft = true;
			if (dy > 0)
				node.canGoUp = true;
			if (dy < 0)
				node.canGoDown = true;

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
				
			} else {
				nextCurrCol = currCol;
				nextCurrRow = testRow;
				
			}
			
			currCol = nextCurrCol;
			currRow = nextCurrRow;
		}
	}
}

void PreferredPath::addVertices(Mesh* barrierMesh, float z)
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

	// Draw a series of triangles
	float maxTriangleWidth = nodeWidth;
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
		int numTriangles = (int)(length / maxTriangleWidth);
		if (numTriangles < 1) {
			numTriangles = 1;
		}
		float triangleWidth = length / numTriangles;
		float tw = triangleWidth;
		
		// Use the bottomleft corner of the rectangle to get every other corner
		float bottomLeft[3] = {distToCorner * cos(theta - dTheta) + point->x, 
			distToCorner * sin(theta - dTheta) + point->y, z};

		float topLeft[3] = {bottomLeft[0] - height * sinTheta, 
			bottomLeft[1] + height * cosTheta, z};

		float pos0[3] = {0.0f, 0.0f, z};
		float pos1[3] = {0.0f, 0.0f, z};
		float pos2[3] = {0.0f, 0.0f, z};

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

#define ABT(pos1, pos2, pos3, dark, green) ABV(pos1, green) ABV(pos2, dark) ABV(pos3, dark)


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
			pos1[0] = triangleTopX;
			pos1[1] = triangleTopY;
			pos2[0] = triangleBottomX;
			pos2[1] = triangleBottomY;

			ABT(pos0, pos1, pos2, dark, light);
		}
	}
#undef ABT
#undef ABV
#undef ROTATE_POINT
}

ASTAR_FUNCTION Variant PreferredPath_setWeight(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* pathNode = parnode(1);
	
	try {
		PreferredPath* path = &o(PreferredPath, pathNode);
		path->pathWeight = parval(2);
	} catch (...) {;}

	return 0;
}

ASTAR_FUNCTION Variant PreferredPath_getWeight(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* pathNode = parnode(1);
	try {
		PreferredPath* path = &o(PreferredPath, pathNode);
		return path->pathWeight;
	} catch (...) {;}
	return 0;
}