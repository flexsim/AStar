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
};

}