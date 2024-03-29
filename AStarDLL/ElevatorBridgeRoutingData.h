#pragma once
#include "FlexsimDefs.h"
#include "AStarClasses.h"
#include "BridgeRoutingData.h"

namespace AStar {

class ElevatorBridgeRoutingData : public BridgeRoutingData {
public:
	virtual const char* getClassFactory() override { return "AStar::ElevatorBridgeRoutingData"; }
	virtual void bind() override;
	virtual ElevatorBridgeRoutingData* toElevator() override { return this; }

protected:
	virtual std::vector<HeuristicEntry> getAdjacentCells(Grid* owner) override;
	ObjectDataType* __getElevator();
	__declspec(property(get = __getElevator)) ObjectDataType* elevator;
	ElevatorBridge* __getBridge();
	__declspec(property(get = __getBridge)) ElevatorBridge* bridge;

	virtual void onBridgeArrival(Traveler* traveler, int pathIndex) override;
	virtual void onExit(Traveler* traveler) override;
	virtual void updateLocation(Traveler* traveler) override;
	virtual double getTravelDistance(TravelPath* path, int travelPathIndex, Grid* grid) override;
	virtual TravelerBridgeData* createBridgeData() override;
	virtual const char* getBridgeDataClassFactory() override;
	void onAbort(Traveler* traveler) override;
};

}