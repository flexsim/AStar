#include "ElevatorBridgeRoutingData.h"
#include "AStarNavigator.h"
#include "Grid.h"

namespace AStar {

void ElevatorBridgeRoutingData::bind()
{
	__super::bind();
}

std::vector<BridgeRoutingData::HeuristicEntry> ElevatorBridgeRoutingData::getAdjacentCells(Grid* owner)
{
	AStarNavigator* nav = owner->navigator;
	std::vector<HeuristicEntry> result;
	for (Grid* grid : nav->grids) {
		for (BridgeRoutingData* bridge : grid->bridgeData) {
			if (bridge != this && bridge->toElevator() && bridge->toElevator()->elevator == elevator) {
				result.push_back({ bridge->fromCell, (grid->getLocation(bridge->fromCell) - owner->getLocation(fromCell)).magnitude });
			}
		}
	}
	return result;
}

ObjectDataType * ElevatorBridgeRoutingData::__getElevator()
{
	return bridge->elevator;
}

ElevatorBridge * ElevatorBridgeRoutingData::__getBridge()
{
	return holder->up->up->objectAs(ElevatorBridge);
}

}