#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"

namespace AStar {

class OneWayDivider :
	public Divider
{
public:
	OneWayDivider();

	virtual const char * getClassFactory(void);
	virtual void bind(void);

	// See Barrier.h for a description of these methods
	virtual void addBarriersToTable(Grid* grid) override;
	virtual void addVertices(Mesh* barrierMesh, float z) override;
	virtual OneWayDivider* toOneWayDivider() override { return this; }
};

}
