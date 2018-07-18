#include "PreferredPath.h"
#include "AStarNavigator.h"


namespace AStar {

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

void PreferredPath::addPassagesToTable(Grid* grid)
{
	double x = pointList[0]->x;
	double y = pointList[0]->y;
	double c0 = grid->gridOrigin.x;
	double r0 = grid->gridOrigin.y;

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

			AStarCell cell((unsigned int)grid, currCol, currRow);
			AStarNode* node = grid->getNode(cell);
			AStarNodeExtraData * extra = grid->navigator->assertExtraData(cell);
			
			extra->bonusRight = (char)maxof(-128,minof(127, extra->bonusRight + horizontalWeight));
			extra->bonusLeft = (char)maxof(-128,minof(127, extra->bonusLeft - horizontalWeight));
			extra->bonusUp = (char)maxof(-128,minof(127, extra->bonusUp + verticalWeight));
			extra->bonusDown = (char)maxof(-128,minof(127, extra->bonusDown - verticalWeight));

			if (dx > 0)
				node->canGoRight = true;
			if (dx < 0)
				node->canGoLeft = true;
			if (dy > 0)
				node->canGoUp = true;
			if (dy < 0)
				node->canGoDown = true;

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
	addPathVertices(barrierMesh, z, Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
}


}

using namespace AStar;

ASTAR_FUNCTION Variant PreferredPath_setWeight(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* pathNode = param(1);
	
	try {
		PreferredPath* path = pathNode->objectAs(PreferredPath);
		path->pathWeight = param(2);
	} catch (...) {;}

	return 0;
}

ASTAR_FUNCTION Variant PreferredPath_getWeight(FLEXSIMINTERFACE)
{
	TreeNode* navNode = c;
	if (!isclasstype(navNode, "AStar::AStarNavigator"))
		return 0;

	TreeNode* pathNode = param(1);
	try {
		PreferredPath* path = pathNode->objectAs(PreferredPath);
		return path->pathWeight;
	} catch (...) {;}
	return 0;
}