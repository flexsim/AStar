#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"

namespace AStar {

class MandatoryPath : public Divider
{
public:

	virtual const char * getClassFactory(void) { return "AStar::MandatoryPath"; }
	virtual void bind(void) override;

	virtual void addBarriersToTable(Grid* grid) override {}
	virtual void addPassagesToTable(Grid* grid) override;
	virtual void addVertices(Mesh* barrierMesh, float z) override;
	virtual MandatoryPath* toMandatoryPath() override { return this; }
};

}
