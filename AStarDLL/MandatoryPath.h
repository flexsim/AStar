#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"

namespace AStar {

class MandatoryPath : public Divider
{
public:
	virtual void bindVariables() override;
	virtual void onReset(AStarNavigator* nav) override;

	virtual void addBarriersToTable(Grid* grid) override {}
	virtual void addPassagesToTable(Grid* grid) override;
	virtual void addVertices(treenode view, Mesh* barrierMesh, float z, DrawStyle drawStyle) override;
	virtual MandatoryPath* toMandatoryPath() override { return this; }
};

}
