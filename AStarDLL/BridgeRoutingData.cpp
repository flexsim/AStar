#include "BridgeRoutingData.h"
#include "Bridge.h"
#include "AStarNavigator.h"
#include "Traveler.h"

namespace AStar {

void BridgeRoutingData::bind()
{
	fromCell.bind(this, "fromCell");
	bindObjPtr(bridge);
}

std::vector<BridgeRoutingData::HeuristicEntry> BridgeRoutingData::getAdjacentCells(Grid* owner)
{
	Bridge* bridge = partner()->ownerObject->objectAs(Bridge);
	Cell toCell = bridge->navigator->getCell(bridge->getPointToModelOffset() + *bridge->pointList.back());
	std::vector<HeuristicEntry> toCells;
	toCells.push_back({ toCell, bridge->travelDistance });
	return toCells;
}

void BridgeRoutingData::buildDijkstraTable(Grid* owner)
{
	AStarNavigator* nav = owner->navigator;
	auto& grids = owner->navigator->grids;
	toCellHeuristics.resize(grids.size() + 1);

	for (int i = 1; i < toCellHeuristics.size(); i++) {
		toCellHeuristics[i].heuristic = DBL_MAX;
	}

	std::deque<HeuristicEntry> openSet;
	openSet.push_back({ fromCell, 0 });

	while (openSet.size() > 0) {
		std::partial_sort(openSet.begin(), openSet.begin() + 1, openSet.end(), [](HeuristicEntry& left, HeuristicEntry& right) {
			return left.heuristic < right.heuristic;
		});
		HeuristicEntry entry = openSet.front();
		openSet.pop_front();
		HeuristicEntry& destEntry = toCellHeuristics[entry.toCell.grid];
		if (destEntry.heuristic > entry.heuristic) {
			destEntry = entry;
			Vec3 entryLoc = nav->getLocation(entry.toCell);
			Grid* grid = owner->navigator->getGrid(entry.toCell);
			for (BridgeRoutingData* data : grid->bridgeData) {
				if (data->fromCell != entry.toCell || (entry.toCell == fromCell)) {
					Vec3 fromLoc = nav->getLocation(data->fromCell);
					double baseHeuristic = entry.heuristic + (fromLoc - entryLoc).magnitude;
					auto adjacentCells = data->getAdjacentCells(owner);
					for (auto& adjacentCell : adjacentCells) {
						double newHeuristic = baseHeuristic + adjacentCell.heuristic;
						HeuristicEntry& destEntry = toCellHeuristics[adjacentCell.toCell.grid];
						if (destEntry.heuristic > newHeuristic)
							openSet.push_back({ adjacentCell.toCell, newHeuristic });
					}
				}
			}
		}
	}
}

const char * BridgeRoutingData::getBridgeDataClassFactory()
{
	return TravelerBridgeData::s_getClassFactory();
}

TravelerBridgeData * BridgeRoutingData::createBridgeData(Traveler * traveler, double entryTime, int pathIndex)
{
	return new TravelerBridgeData(this, entryTime, pathIndex, traveler->te->b_spatialz - (bridge->getPointToModelOffset().z + bridge->pointList.front()->z));
}

void BridgeRoutingData::onBridgeArrival(Traveler * traveler)
{
	if (bridge->isAvailable) {
		// move onto bridge
		traveler->clearAllocations();
		bridge->onEntry(traveler, traveler->bridgeData->pathIndex);
	} else {
		if (traveler->allocations.size() > 0)
			traveler->allocations.back()->extendReleaseTime(DBL_MAX);
		_ASSERTE(bridge->blockedTraveler == nullptr);
		// Traveler is blocked trying to get on the bridge
		bridge->blockedTraveler = traveler;
		bridge->blockedPathIndex = traveler->bridgeData->pathIndex;
	}
}

void BridgeRoutingData::onExit(Traveler * traveler)
{
	bridge->onExit(traveler);
}

void BridgeRoutingData::updateLocation(Traveler * traveler)
{
	bridge->updateLocations();
}

void BridgeRoutingData::checkExpandOpenSet(AStarNavigator* nav, Traveler * traveler, Grid* grid, int bridgeEntryIndex, bool isAtBridgeStart)
{
	if (bridge->useCondition && !bridge->condition->evaluate(traveler->te->holder))
		return;
	double addedDist = bridge->travelDistance + grid->nodeWidth;
	Point* endPoint = isAtBridgeStart ? bridge->pointList.back() : bridge->pointList.front();
	Cell endCell = nav->getCell(*endPoint + bridge->getPointToModelOffset());
	AStarNode* node = nav->getNode(endCell);
	nav->expandOpenSet(nav->getGrid(endCell), endCell.row, endCell.col, addedDist / grid->nodeWidth, 0, bridgeEntryIndex);
}

double BridgeRoutingData::getTravelDistance(TravelPath * path, int travelPathIndex, Grid* grid)
{
	return bridge->travelDistance + grid->nodeWidth;
}

BridgeRoutingData::ArrivalEvent::ArrivalEvent(BridgeRoutingData* data, Traveler* object, int pathIndex, double time)
	: pathIndex(pathIndex), FlexSimEvent(data->holder, time, object->holder, 0)
{
}

void BridgeRoutingData::ArrivalEvent::execute()
{
	Traveler* traveler = involved->objectAs(Traveler); \
	BridgeRoutingData* data = partner()->objectAs(BridgeRoutingData);
	traveler->onBridgeArrival(data, pathIndex);
}

}
