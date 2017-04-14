#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"
class Bridge : public Divider
{
public:

	virtual const char * getClassFactory(void) override { return "AStar::Bridge"; }
	virtual void bind() override;

	virtual void addBarriersToTable(AStarNavigator* nav) override {}
	virtual void addPassagesToTable(AStarNavigator* nav) override;

	double isTwoWay = 0.0;
	double calculateDistance() const;
	virtual Bridge* toBridge() override { return this; }


	virtual void addVertices(Mesh* barrierMesh, float z) override
	{
		addPathVertices(barrierMesh, z, Vec4f(0.0f, 0.3f, 1.0f, 1.0f));
	}

};

