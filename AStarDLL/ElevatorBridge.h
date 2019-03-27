#pragma once
#include "FlexsimDefs.h"

namespace AStar {
class AStarNavigator;
class Traveler;
class BridgeRoutingData;

class TravelerBridgeData : public SimpleDataType {
public:
	virtual const char* getClassFactory() override { return "AStar::TravelerBridgeData"; }

	virtual void bind() override
	{
		bindObjPtr(routingData);
		bindNumber(entryTime);
		bindNumber(pathIndex);
		bindObjPtr(prevTraveler);
		bindObjPtr(nextTraveler);
	}
	virtual void bindEvents() override
	{
		bindEvent(ElevatorBankArrival);
		bindEvent(ElevatorBankContinue);
		bindEvent(ElevatorEntry);
		bindEvent(ElevatorExit);
	}

	TravelerBridgeData() : routingData(nullptr), entryTime(DBL_MAX) {}
	TravelerBridgeData(BridgeRoutingData* routingData, double entryTime, int pathIndex, double spatialz)
		: routingData(routingData), entryTime(entryTime), pathIndex(pathIndex), spatialz(spatialz) {}
	int pathIndex;

	BridgeRoutingData* routingData;
	double spatialz;
	double entryTime;
	Traveler* nextTraveler = nullptr;
	Traveler* prevTraveler = nullptr;

	TreeNode* onElevatorBankArrival = nullptr;
	TreeNode* onElevatorEntry = nullptr;
	TreeNode* onElevatorExit = nullptr;
	TreeNode* onElevatorBankContinue = nullptr;

	virtual void updateLocation(TaskExecuter* te) {}
};

class ElevatorBridge : public CouplingDataType {
	friend class AStarNavigator;
public:
	class AStarDelegate : public SimpleDataType {
	public:
		AStarNavigator* navigator;
		virtual const char* getClassFactory() { return "AStar::ElevatorBridge::AStarDelegate"; }
		virtual void bind() override;
		virtual void onBridgeComplete(TaskExecuter* te);
		virtual TravelerBridgeData* getBridgeData(TaskExecuter* te);
		virtual void clearAllocations(TaskExecuter* te);
	};

	treenode bridgeData = nullptr;
	AStarDelegate* aStarDelegate = nullptr;
	ObjectDataType* elevator = nullptr;
	virtual void bind() override { bindSubNode(bridgeData, 0); bindObjPtr(aStarDelegate); bindObjPtr(elevator); }
private:
	void reset();
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Executes the bridge arrival action. </summary>
	/// <remarks>	This is called by the A* travel functionality, and passes control
	/// 			to the elevator for getting the te onto the elevator and to 
	/// 			the destination floor. </remarks>
	/// <param name="te">			[in,out] If non-null, the te. </param>
	/// <param name="destFloor">	Destination floor. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void onBridgeArrival(TaskExecuter* te, const Vec3& destFloor) = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the desired arrival location for a certain floor. </summary>
	/// <remarks>	The returned location should be in the elevator's parent coordinate space. </remarks>
	/// <param name="floorZ">	The floor z coordinate. </param>
	/// <returns>	The arrival location. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual Vec3 getArrivalLoc(double floorZ) = 0;

	virtual void getBoundingBox(Vec3& outMin, Vec3& outMax) = 0;
	virtual TravelerBridgeData* createBridgeData() = 0;
	virtual const char* getBridgeDataClassFactory() = 0;
};

}