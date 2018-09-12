#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"

namespace AStar {

class MandatoryPath : public Divider
{
public:

	virtual const char * getClassFactory(void) { return "AStar::MandatoryPath"; }
	virtual void bind() override;
	virtual void onReset(AStarNavigator* nav) override;

	double isTwoWay = 0.0;

	virtual void addBarriersToTable(Grid* grid) override {}
	virtual void addPassagesToTable(Grid* grid) override;
	virtual void addVertices(Mesh* barrierMesh, float z) override;
	virtual MandatoryPath* toMandatoryPath() override { return this; }
};

}
