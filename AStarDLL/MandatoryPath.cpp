#include "MandatoryPath.h"
#include "Grid.h"
#include "AStarNavigator.h"

namespace AStar {
void MandatoryPath::bind(void)
{
	__super::bind();
}

void MandatoryPath::addPassagesToTable(Grid * grid)
{
	for (int i = 0; i < pointList.size() - 1; i++) {

		Point* fromPoint = pointList[i];
		Point* toPoint = pointList[i + 1];
		Vec3 fromPos(fromPoint->x, fromPoint->y, fromPoint->z);
		Vec3 toPos(toPoint->x, toPoint->y, toPoint->z);
		double direction = radianstodegrees(atan2(toPos.y - fromPos.y, toPos.x - fromPos.x));

		grid->visitGridModelLine(fromPos, toPos, [this, grid, direction](const AStarCell& cell) -> void {
			AStarNode* node = grid->getNode(cell);
			node->isOnMandatoryPath = true;
			AStarNode newValue(*node);
			if (direction > 135.0 || direction < -135.0)
				newValue.setCanGo(Right, false);
			else if (direction < 45.0 && direction > -45.0)
				newValue.setCanGo(Left, false);

			if (direction < -45.0 && direction > -135.0)
				newValue.setCanGo(Up, false);
			else if (direction < 135.0 && direction > 45.0)
				newValue.setCanGo(Down, false);

			conditionalBarrierChanges.addEntry(cell, newValue);
		});
	}
}

void MandatoryPath::addVertices(Mesh * barrierMesh, float z)
{
	addPathVertices(barrierMesh, z, Vec4f(0.75f, 0.61f, 0.25f, 1.0f));
}

void MandatoryPath::onReset(AStarNavigator * nav)
{
	__super::onReset(nav);
}
}
