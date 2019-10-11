#include "ElevatorBridgeRoutingData.h"
#include "AStarNavigator.h"
#include "Grid.h"
#include "ElevatorBridge.h"
#include "Traveler.h"

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
				result.push_back({false, bridge->fromCell, (grid->getLocation(bridge->fromCell) - owner->getLocation(fromCell)).magnitude });
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
	return partner()->up->up->objectAs(ElevatorBridge);
}

void ElevatorBridgeRoutingData::onBridgeArrival(Traveler* traveler, int pathIndex)
{
	auto& nextCell = traveler->travelPath[pathIndex + 1].cell;
	Vec3 destFloor = traveler->navigator->getLocation(nextCell);
	bridge->onBridgeArrival(traveler->te, destFloor);
	if (traveler->allocations.size() > 0)
		traveler->allocations.back()->extendReleaseTime(DBL_MAX);
}

void ElevatorBridgeRoutingData::onExit(Traveler* traveler)
{

}

void ElevatorBridgeRoutingData::updateLocation(Traveler* traveler)
{
	traveler->bridgeData->updateLocation(traveler->te);
}

double ElevatorBridgeRoutingData::getTravelDistance(TravelPath* path, int travelPathIndex, Grid* grid)
{
	auto& srcCell = (*path)[travelPathIndex].cell;
	Vec3 srcLoc = grid->getLocation(srcCell);
	auto& destCell = (*path)[travelPathIndex + 1].cell;
	Vec3 destLoc = grid->navigator->getLocation(destCell);
	return (destLoc - srcLoc).magnitude;
}

TravelerBridgeData * ElevatorBridgeRoutingData::createBridgeData()
{
	return bridge->createBridgeData();
}

const char * ElevatorBridgeRoutingData::getBridgeDataClassFactory()
{
	return bridge->getBridgeDataClassFactory();
}

}