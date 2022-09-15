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


void PreferredPath::bindVariables(void)
{
	__super::bindVariables();
	bindVariable(pathWeight);
}


void PreferredPath::bind(void)
{
	__super::bind();
	bindCallback(getWeight, PreferredPath);
	bindCallback(setWeight, PreferredPath);
}

void PreferredPath::addPassagesToTable(Grid* grid)
{
	double weight = pathWeight == 0 ? navigator->defaultPathWeight : pathWeight;
	for (int i = 0; i < pointList.size() - 1; i++) {
		
		Point* fromPoint = pointList[i];
		Point* toPoint = pointList[i + 1];
		Vec3 fromPos = fromPoint->project(holder, model());
		Vec3 toPos = toPoint->project(holder, model());

		// calculate the column and row numbers for that point
		int fromCol = (int)round((fromPos.x - grid->gridOrigin.x) / nodeSize.x);
		int fromRow = (int)round((fromPos.y - grid->gridOrigin.y) / nodeSize.y);
		int toCol = (int)round((toPos.x - grid->gridOrigin.x) / nodeSize.x);
		int toRow = (int)round((toPos.y - grid->gridOrigin.y) / nodeSize.y);

		// set dx and dy, the differences between the rows and columns
		double dx = toCol - fromCol;
		double dy = toRow - fromRow;
		
		if(dy == 0 && dx == 0)
			continue;

		// calculate the weight values for preferred paths.
		int horizontalWeight = (int)(weight * 127 * dx / (fabs(dx) + fabs(dy)));
		int verticalWeight = (int)(weight * 127 * dy / (fabs(dx) + fabs(dy)));

		grid->visitGridModelLine(fromPos, toPos, [this, grid, horizontalWeight, verticalWeight, dx, dy, fromRow, fromCol, toRow, toCol](const Cell& cell) -> void {
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

			bool isStart = cell.row == fromRow && cell.col == fromCol;
			bool isEnd = cell.row == toRow && cell.col == toCol;

			if ((dx > 0 && !isEnd) || (isTwoWay && dx < 0 && !isStart))
				node->canGoRight = true;
			if ((dx < 0 && !isEnd) || (isTwoWay && dx > 0 && !isStart))
				node->canGoLeft = true;
			if ((dy > 0 && !isEnd) || (isTwoWay && dy < 0 && !isStart))
				node->canGoUp = true;
			if ((dy < 0 && !isEnd) || (isTwoWay && dy > 0 && !isStart))
				node->canGoDown = true;			

			if (conditionRule) {
				node->hasConditionalBarrier = true;
				extra->addConditionalBarrier(this);
			}

		});
	}
}

void PreferredPath::addVertices(treenode view, Mesh* barrierMesh, float z, DrawStyle drawStyle)
{
	addPathVertices(view, barrierMesh, z, Vec4f(0.0f, 1.0f, 0.0f, 1.0f), drawStyle, isTwoWay);
}


}
