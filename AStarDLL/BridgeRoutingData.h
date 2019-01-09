#pragma once
#include "FlexsimDefs.h"
#include "AStarClasses.h"
#include "AStarTypes.h"

namespace AStar {
class BridgeRoutingData : public CouplingDataType
{
public:
	virtual const char* getClassFactory() override { return "AStar::BridgeRoutingData"; }
	virtual void bind() override;
	Cell fromCell;
	struct HeuristicEntry {
		Cell toCell;
		double heuristic;
	};
	/// <summary>	to cell heuristics vector. This will be a vector with an 
	/// 			entry for each grid, indexed by grid number.</summary>
	std::vector<HeuristicEntry> toCellHeuristics;
	void buildDijkstraTable(Grid* owner);

protected:
	virtual std::vector<HeuristicEntry> getAdjacentCells();
};

}
