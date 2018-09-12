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
	bindDouble(isTwoWay, 1);
	bindCallback(getWeight, PreferredPath);
	bindCallback(setWeight, PreferredPath);
}

void PreferredPath::addPassagesToTable(Grid* grid)
{

	for (int i = 0; i < pointList.size() - 1; i++) {
		
		Point* fromPoint = pointList[i];
		Point* toPoint = pointList[i + 1];
		Vec3 fromPos(fromPoint->x, fromPoint->y, fromPoint->z);
		Vec3 toPos(toPoint->x, toPoint->y, toPoint->z);

		// calculate the column and row numbers for that point
		int fromCol = (int)round((fromPos.x - grid->gridOrigin.x) / nodeWidth);
		int fromRow = (int)round((fromPos.y - grid->gridOrigin.y) / nodeWidth);
		int toCol = (int)round((toPos.x - grid->gridOrigin.x) / nodeWidth);
		int toRow = (int)round((toPos.y - grid->gridOrigin.y) / nodeWidth);

		// set dx and dy, the differences between the rows and columns
		double dx = toCol - fromCol;
		double dy = toRow - fromRow;
		
		if(dy == 0 && dx == 0)
			continue;

		// calculate the weight values for preferred paths.
		int horizontalWeight = (int)(pathWeight * 127 * dx / (fabs(dx) + fabs(dy)));
		int verticalWeight = (int)(pathWeight * 127 * dy / (fabs(dx) + fabs(dy)));

		grid->visitGridModelLine(fromPos, toPos, [this, grid, horizontalWeight, verticalWeight, dx, dy](const AStarCell& cell) -> void {
			AStarNode* node = grid->getNode(cell);
			AStarNodeExtraData * extra = grid->navigator->assertExtraData(cell, PreferredPathData);
			node->hasPreferredPathWeight = true;

			if (!isTwoWay) {
				extra->bonusRight = (char)maxof(-128, minof(127, extra->bonusRight + horizontalWeight));
				extra->bonusLeft = (char)maxof(-128, minof(127, extra->bonusLeft - horizontalWeight));
				extra->bonusUp = (char)maxof(-128, minof(127, extra->bonusUp + verticalWeight));
				extra->bonusDown = (char)maxof(-128, minof(127, extra->bonusDown - verticalWeight));
			} else {
				extra->bonusRight = (char)maxof(-128, minof(127, extra->bonusRight + fabs(horizontalWeight)));
				extra->bonusLeft = (char)maxof(-128, minof(127, extra->bonusLeft + fabs(horizontalWeight)));
				extra->bonusUp = (char)maxof(-128, minof(127, extra->bonusUp + fabs(verticalWeight)));
				extra->bonusDown = (char)maxof(-128, minof(127, extra->bonusDown + fabs(verticalWeight)));
			}

			if (dx > 0)
				node->canGoRight = true;
			if (dx < 0)
				node->canGoLeft = true;
			if (dy > 0)
				node->canGoUp = true;
			if (dy < 0)
				node->canGoDown = true;

			if (useCondition) {
				node->hasConditionalBarrier = true;
				extra->addConditionalBarrier(this);
			}

		});
	}
}

void PreferredPath::addVertices(Mesh* barrierMesh, float z)
{
	addPathVertices(barrierMesh, z, Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
}


}
