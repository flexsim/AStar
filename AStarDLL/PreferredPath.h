#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"
class PreferredPath : public Divider
{
public:
	double pathWeight;

	PreferredPath();
	PreferredPath(double pathWeight);
	virtual const char * getClassFactory(void);
	virtual void bind(void);

	// See Barrier.h for a description of these methods
	virtual void addBarriersToTable(AStarNavigator* nav) override
	{}

	virtual void addPassagesToTable(AStarNavigator* nav) override;

	virtual void addVertices(Mesh* barrierMesh, float z);
	virtual PreferredPath* toPreferredPath() override { return this; }
};

