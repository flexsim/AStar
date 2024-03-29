#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"
#include <vector>

namespace AStar {

class Bridge : public Divider
{
public:

	Bridge();

	virtual void bindVariables(void) override;

	virtual void addBarriersToTable(Grid* grid) override {}
	virtual void addPassagesToTable(Grid* grid) override {}
	virtual void addVertices(treenode view, Mesh* barrierMesh, float z, DrawStyle drawStyle) override;
	virtual void onReset(AStarNavigator* nav) override;
	virtual Bridge* toBridge() override { return this; }

	double useVirtualDistance = 0.0;
	double virtualDistance = 0.0;
	double geometricDistance = 0.0;
	/// <summary>The travel distance from arriving at the beginning of the 
	/// 		 bridge, to arriving one node width short of the end of the 
	/// 		 bridge, on node width. If virtual distance is used, this is 
	/// 		 the virtual distance. If not, it is the geometric distance 
	/// 		 minus one node width.</summary>
	double travelDistance = 0.0;
	double filledDistance = 0.0;
	double lastUpdateTime = -1.0;
	double nodeWidth = 1.0;
	double isAvailable = true;
	ObjRef<Traveler> firstTraveler = nullptr;
	ObjRef<Traveler> lastTraveler = nullptr;
	ObjRef<Traveler> blockedTraveler = nullptr;
	double blockedPathIndex;

	NodeListArray<BridgeRoutingData>::CouplingSdtPtrType routingData;

	double calculateDistance() const;
	double getTravelToGeomDistScale();
	/// fired when the bridge is available for a traveler to enter
	void onEntry(Traveler* traveler, int pathIndex);
	/// 
	void onExit(Traveler* traveler);
	/// fired when the traveler reaches the end of the bridge, and is ready to 
	/// continue on its path
	void onEndArrival(Traveler* traveler, int pathIndex);
	/// fired on "accumulating" bridges, when the traveler is fully "on" the bridge, 
	/// meaning the bridge is available for the next entrant
	void onAvailable();
	void updateBridgeLocations();
	void updateLocation(Traveler* t, double geomDistAlongBridge, Vec3* offset = nullptr);


	class EndArrivalEvent : public FlexSimEvent
	{
	public:
		EndArrivalEvent() : FlexSimEvent() {}
		EndArrivalEvent(Bridge* bridge, Traveler* object, int pathIndex, double time);
		virtual const char* getClassFactory() override { return "AStar::Bridge::EndArrivalEvent"; }
		virtual void execute() override { partner()->objectAs(Bridge)->onEndArrival(involved->objectAs(Traveler), pathIndex); }
		virtual void bind() override { __super::bind(); bindNumber(pathIndex); }

		int pathIndex;
	};

	class AvailableEvent : public FlexSimEvent
	{
	public:
		AvailableEvent() : FlexSimEvent() {}
		AvailableEvent(Bridge* bridge, double time)
			: FlexSimEvent(bridge->holder, time, nullptr, 0) {}
		virtual const char* getClassFactory() override { return "AStar::Bridge::AvailableEvent"; }
		virtual void execute() override { partner()->objectAs(Bridge)->onAvailable(); }
	};

	Grid* getGrid(Traveler* traveler);

};

}