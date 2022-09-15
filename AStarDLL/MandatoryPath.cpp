#include "MandatoryPath.h"
#include "Grid.h"
#include "AStarNavigator.h"

namespace AStar {
void MandatoryPath::bindVariables()
{
	__super::bindVariables();
	bindVariable(isTwoWay);
}

void MandatoryPath::onReset(AStarNavigator* nav)
{
	__super::onReset(nav);
	if (conditionRule) {
		nav->hasConditionalBarriers = 1.0;
	}
}


void MandatoryPath::addPassagesToTable(Grid * grid)
{
	grid->navigator->hasMandatoryPaths = 1.0;

	for (int i = 0; i < pointList.size() - 1; i++) {

		Point* fromPoint = pointList[i];
		Point* toPoint = pointList[i + 1];
		Vec3 fromPos(fromPoint->project(holder, model()));
		Vec3 toPos(toPoint->project(holder, model()));
		double direction = radianstodegrees(atan2(toPos.y - fromPos.y, toPos.x - fromPos.x));

		grid->visitGridModelLine(fromPos, toPos, [this, grid, direction](const Cell& cell) -> void {
			AStarNode* node = grid->getNode(cell);
			AStarNode newValue(*node);
			if (!conditionRule)
				node->isOnMandatoryPath = true;
			newValue.isOnMandatoryPath = true;
			AStarNode mask;
			mask.value = 0;
			mask.isOnMandatoryPath = true;
			if (!isTwoWay) {
				if (direction > 135.0 || direction < -135.0) {
					newValue.canGoRight = false;
					mask.canGoRight = true;
				}
				else if (direction < 45.0 && direction > -45.0) {
					newValue.canGoLeft = false;
					mask.canGoLeft = true;
				}

				if (direction < -45.0 && direction > -135.0) {
					newValue.canGoUp = false;
					mask.canGoUp = true;
				}
				else if (direction < 135.0 && direction > 45.0) {
					newValue.canGoDown = false;
					mask.canGoDown = true;
				}
			}

			auto& entry = conditionalBarrierChanges.addEntry(cell, newValue);
			entry.changeMask = mask;
		});
	}
}

void MandatoryPath::addVertices(treenode view, Mesh * barrierMesh, float z, DrawStyle drawStyle)
{
	addPathVertices(view, barrierMesh, z, Vec4f(0.75f, 0.61f, 0.25f, 1.0f), drawStyle, isTwoWay);
}
}
