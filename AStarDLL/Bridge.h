#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"
#include <vector>

namespace AStar {

class Bridge : public Divider
{
public:

	virtual const char * getClassFactory(void) override { return "AStar::Bridge"; }
	virtual void bind() override;

	virtual void addBarriersToTable(AStarNavigator* nav) override {}
	virtual void addPassagesToTable(AStarNavigator* nav) override;

	double isTwoWay = 0.0;
	double useVirtualDistance = 0.0;
	double virtualDistance = 0.0;
	double geometricDistance = 0.0;
	double travelDistance = 0.0;
	double filledDistance = 0.0;
	double lastUpdateTime = -1.0;
	double nodeWidth = 1.0;
	bool isAvailable = true;
	Traveler* firstTraveler;
	Traveler* lastTraveler;
	Traveler* blockedTraveler;
	int blockedPathIndex;

	double calculateDistance(bool noVirtual = false) const;
	double getTravelToGeomDistScale() { return geometricDistance / (travelDistance + nodeWidth); }
	virtual Bridge* toBridge() override { return this; }


	virtual void addVertices(Mesh* barrierMesh, float z) override
	{
		addPathVertices(barrierMesh, z, Vec4f(0.0f, 0.3f, 1.0f, 1.0f));
	}

	virtual void onReset(AStarNavigator* nav) override;

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
	void onEntry(Traveler* traveler, int pathIndex);
	void onExit(Traveler* traveler);

	void onEndArrival(Traveler* traveler, int pathIndex);
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

	void onAvailable();
	class AvailableEvent : public FlexSimEvent
	{
	public:
		AvailableEvent() : FlexSimEvent() {}
		AvailableEvent(Bridge* bridge, double time)
			: FlexSimEvent(bridge->holder, time, nullptr, 0) {}
		virtual const char* getClassFactory() override { return "AStar::Bridge::AvailableEvent"; }
		virtual void execute() { partner()->objectAs(Bridge)->onAvailable(); }
	};

	void updateLocations();
	void updateLocation(Traveler* t, double geomDistAlongBridge);
};

}