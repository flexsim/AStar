#pragma once
#include "FlexsimDefs.h"
#include "AStarClasses.h"
#include "AStarTypes.h"

namespace AStar {
class BridgeRoutingData : public CouplingDataType
{
public:
	BridgeRoutingData(Bridge* bridge) : bridge(bridge) {}
	BridgeRoutingData() {}
	virtual const char* getClassFactory() override { return "AStar::BridgeRoutingData"; }
	virtual void bind() override;
	Cell fromCell;
	Bridge* bridge = nullptr;
	struct HeuristicEntry {
		Cell toCell;
		double heuristic;
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
	virtual TravelerBridgeData* createBridgeData(Traveler* traveler, double entryTime, int pathIndex);

	virtual void onBridgeArrival(Traveler* traveler);
	virtual void onExit(Traveler* traveler);
	virtual void updateLocation(Traveler* traveler);
	virtual void checkExpandOpenSet(AStarNavigator* nav, Traveler * traveler, Grid* grid, int bridgeEntryIndex, bool isAtBridgeStart);
	virtual double getTravelDistance(TravelPath* path, int travelPathIndex, Grid* grid);

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
