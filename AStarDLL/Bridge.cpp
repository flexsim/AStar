#include "Bridge.h"
#include "AStarNavigator.h"
#include "macros.h"

namespace AStar {

void Bridge::bind()
{
	__super::bind();
	bindDouble(isTwoWay, 1);
}

void Bridge::addPassagesToTable(AStarNavigator* nav)
{
	if (pointList.size() < 2)
		return;
	AStarCell fromCell = nav->getCellFromLoc(Vec2(pointList[0]->x, pointList[0]->y));

	auto addExtraData = [&](const AStarCell& cell, bool isAtStart) {
		AStarNodeExtraData* entry = nav->assertExtraData(fromCell);

		entry->bridges.push_back(AStarNodeExtraData::BridgeEntry());
		entry->bridges.back().bridge = this;
		entry->bridges.back().isAtBridgeStart = isAtStart;
	};

	addExtraData(nav->getCellFromLoc(Vec2(pointList[0]->x, pointList[0]->y)), true);
	if (isTwoWay)
		addExtraData(nav->getCellFromLoc(Vec2(pointList.back()->x, pointList.back()->y)), false);

}

double Bridge::calculateDistance() const
{
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
}