#include "BridgeRoutingData.h"
#include "Bridge.h"
#include "AStarNavigator.h"

namespace AStar {

void BridgeRoutingData::bind()
{
	fromCell.bind(this, "fromCell");
}

std::vector<BridgeRoutingData::HeuristicEntry> BridgeRoutingData::getAdjacentCells()
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
					auto adjacentCells = data->getAdjacentCells();
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



}
