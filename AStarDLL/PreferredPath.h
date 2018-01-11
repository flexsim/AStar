#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"

namespace AStar {

class PreferredPath : public Divider
{
public:
	double pathWeight;

	PreferredPath();
	PreferredPath(double pathWeight);

	virtual const char * getClassFactory(void);
	virtual void bind(void);

	// See Barrier.h for a description of these methods
	virtual void init(double nodeWidth, double x1, double y1, double x2, double y2) override;
	virtual void addBarriersToTable(AStarNavigator* nav) override {}
	virtual void addPassagesToTable(AStarNavigator* nav) override;
	virtual void addVertices(Mesh* barrierMesh, float z) override;
	virtual double onMouseMove(const Vec3& pos, const Vec3& diff) override;
	virtual PreferredPath* toPreferredPath() override { return this; }
};

}
