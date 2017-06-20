#include "Bridge.h"
#include "AStarNavigator.h"
#include "macros.h"

namespace AStar {

void Bridge::bind()
{
	__super::bind();
	bindDouble(isTwoWay, 1);
	bindDouble(useVirtualDistance, 1);
	bindDouble(virtualDistance, 1);
}

void Bridge::addPassagesToTable(AStarNavigator* nav)
{
	// Clear bridgeTravelers on reset
	for (int i = bridgeTravelers.size() - 1; i >= 0; i--) {
		delete bridgeTravelers[i];
		bridgeTravelers.pop_back();
	}
	blockedTraveler = nullptr;

	if (pointList.size() < 2)
		return;

	AStarCell fromCell = nav->getCellFromLoc(Vec2(pointList[0]->x, pointList[0]->y));
	AStarCell toCell = nav->getCellFromLoc(Vec2(pointList.back()->x, pointList.back()->y));
	if (fromCell == toCell)
		return;

	// add bridge data to cells
	auto addExtraData = [&](const AStarCell& cell, bool isAtStart) {
		AStarNodeExtraData* entry = nav->assertExtraData(cell);

		entry->bridges.push_back(AStarNodeExtraData::BridgeEntry());
		entry->bridges.back().bridge = this;
		entry->bridges.back().isAtBridgeStart = isAtStart;
	};

	addExtraData(fromCell, true);
	if (isTwoWay)
		addExtraData(toCell, false);
}

double Bridge::calculateDistance(bool noVirtual) const
{
	if (!useVirtualDistance || noVirtual) {
		double total = 0;
		for (int i = 1; i < pointList.size(); i++) {
			Vec3 diff(
				pointList[i]->x - pointList[i - 1]->x,
				pointList[i]->y - pointList[i - 1]->y,
				pointList[i]->z - pointList[i - 1]->z);
			total += sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
		}
		return total;
	}
	else
		return virtualDistance;
}
}