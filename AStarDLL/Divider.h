#pragma once
#include "FlexsimDefs.h"
#include "Barrier.h"

namespace AStar {

class Divider :
	public Barrier
{
public:
	Divider();

	virtual const char * getClassFactory(void);
	virtual void bind(void);

	// See Barrier.h for descriptions of these functions
	virtual bool getBoundingBox(double& x0, double& y0, double& x1, double& y1) override;
	virtual void addBarriersToTable(AStarNavigator* nav) override;
	virtual void addVertices(Mesh* barrierMesh, float z) override;
	virtual double onClick(treenode view, int clickCode, double x, double y) override;
	virtual double onMouseMove(const Vec3& pos, const Vec3& diff) override;
	virtual Divider* toDivider() override { return this; }
};

}