#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"
#include <vector>

namespace AStar {

class Bridge : public Divider
{
public:

	Bridge();

	virtual const char * getClassFactory(void);
	virtual void bind(void);

	virtual void addBarriersToTable(Grid* grid) override {}
	virtual void addPassagesToTable(Grid* grid) override;
	virtual void addVertices(Mesh* barrierMesh, float z) override;
	virtual void onReset(AStarNavigator* nav) override;
	virtual Bridge* toBridge() override { return this; }

	double isTwoWay = 0.0;
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
	bool isAvailable = true;
	Traveler* firstTraveler;
	Traveler* lastTraveler;
	Traveler* blockedTraveler;
	int blockedPathIndex;

	double calculateDistance() const;
	double getTravelToGeomDistScale();
	void onEntry(Traveler* traveler, int pathIndex);
	void onExit(Traveler* traveler);
	void onEndArrival(Traveler* traveler, int pathIndex);
	void onAvailable();
	void updateLocations();
	void updateLocation(Traveler* t, double geomDistAlongBridge);

	class ArrivalEvent : public FlexSimEvent
	{
	public:
		ArrivalEvent() : FlexSimEvent() {}
		ArrivalEvent(Bridge* bridge, Traveler* object, int pathIndex, double time);
		virtual const char* getClassFactory() override { return "AStar::Bridge::ArrivalEvent"; }
		virtual void execute() override;
		virtual void bind() override { __super::bind(); bindNumber(pathIndex); }

		int pathIndex;
	};

	class EndArrivalEvent : public FlexSimEvent
	{
	public:
		EndArrivalEvent() : FlexSimEvent() {}
		EndArrivalEvent(Bridge* bridge, Traveler* object, int pathIndex, double time);
		virtual const char* getClassFactory() override { return "AStar::Bridge::EndArrivalEvent"; }
		virtual void execute() { partner()->objectAs(Bridge)->onEndArrival(involved->objectAs(Traveler), pathIndex); }
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
		virtual void execute() { partner()->objectAs(Bridge)->onAvailable(); }
	};

	Grid* getGrid(Traveler* traveler);


};

}