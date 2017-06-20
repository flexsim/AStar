#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"
#include <vector>

namespace AStar {

struct BridgeTraveler {
	BridgeTraveler(Traveler* traveler, double entryTime, int pathIndex, double spatialz)
		: traveler(traveler), entryTime(entryTime), pathIndex(pathIndex), spatialz(spatialz) {}
	Traveler* traveler;
	double entryTime;
	int pathIndex;
	double spatialz;
};

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
	std::vector<BridgeTraveler*> bridgeTravelers;
	Traveler* blockedTraveler;
	int blockedPathIndex;

	double calculateDistance(bool noVirtual = false) const;
	virtual Bridge* toBridge() override { return this; }


	virtual void addVertices(Mesh* barrierMesh, float z) override
	{
		addPathVertices(barrierMesh, z, Vec4f(0.0f, 0.3f, 1.0f, 1.0f));
	}

};

}