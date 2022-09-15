#pragma once
#include "FlexsimDefs.h"
#include "AStarClasses.h"
#include "AStarTypes.h"

namespace AStar {
class BridgeRoutingData : public CouplingDataType
{
public:
	BridgeRoutingData(Bridge* bridge, bool isAtBridgeStart) : bridge(bridge), isAtBridgeStart(isAtBridgeStart) {}
	BridgeRoutingData() {}
	virtual const char* getClassFactory() override { return "AStar::BridgeRoutingData"; }
	virtual void bind() override;
	Cell fromCell;
	Bridge* bridge = nullptr;
	bool isAtBridgeStart = false;
	Grid* __getGrid();
	__declspec(property(get = __getGrid)) Grid* grid;
	struct HeuristicEntry {
		bool isAdjacent;
		Cell toCell;
		double heuristic;
		void bind(TreeNode* toNode);
	};
	/// <summary>	to cell heuristics vector. This will be a vector with an 
	/// 			entry for each grid, indexed by grid number. It is built 
	/// 			as part of buildDijkstraTable(), and accessed as part of 
	/// 			the routing search algorithm heuristic to calculate a 
	/// 			traveler's estimated distance to a destination.</summary>
	std::vector<HeuristicEntry> toCellHeuristics;
	void buildDijkstraTable(Grid* owner);
	virtual ElevatorBridgeRoutingData* toElevator() { return nullptr; }
	virtual const char* getBridgeDataClassFactory();
	virtual TravelerBridgeData* createBridgeData();

	virtual void onBridgeArrival(Traveler* traveler, int pathIndex);
	virtual void onExit(Traveler* traveler);
	virtual void onAbort(Traveler* traveler);
	virtual void updateLocation(Traveler* traveler);
	void checkExpandOpenSet(AStarNavigator* nav, Traveler * traveler, Grid* grid, int bridgeEntryIndex);
	virtual double getTravelDistance(TravelPath* path, int travelPathIndex, Grid* grid);
	virtual void addEntriesToNodeTable(Grid* grid);

	class ArrivalEvent : public FlexSimEvent
	{
	public:
		ArrivalEvent() : FlexSimEvent() {}
		ArrivalEvent(BridgeRoutingData* bridge, Traveler* object, int pathIndex, double time);
		virtual const char* getClassFactory() override { return "AStar::BridgeRoutingData::ArrivalEvent"; }
		virtual void execute() override;
		virtual void bind() override { __super::bind(); bindNumber(pathIndex); }

		int pathIndex;
	};


protected:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets all adjacent cells. </summary>
	/// <remarks>	buildDijkstraTable() calls this method to get which nodes are adjacently accessible 
	/// 			from this bridge point. This should be custom-implemented by subclasses like the 
	/// 			ElevatorBridgeRoutingData.</remarks>
	/// <param name="owner">	[in,out] The owning grid. </param>
	/// <returns>	The adjacent cells. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual std::vector<HeuristicEntry> getAdjacentCells(Grid* owner);
};

}
