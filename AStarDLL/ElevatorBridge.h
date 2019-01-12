#pragma once
#include "FlexsimDefs.h"

namespace AStar {
class AStarNavigator;
class ElevatorBridge : public CouplingDataType {
	friend class AStarNavigator;
public:
	class AStarDelegate : public SimpleDataType {
	public:
		AStarNavigator* navigator;
		virtual const char* getClassFactory() { return "AStar::ElevatorBridge::AStarDelegate"; }
		virtual void bind() override;
		virtual void onDestArrival(TaskExecuter* te);
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
};
}