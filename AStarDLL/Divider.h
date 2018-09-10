#pragma once
#include "FlexsimDefs.h"
#include "Barrier.h"

namespace AStar {

class Divider : public Barrier
{
public:
	Divider();

	virtual const char * getClassFactory(void);
	virtual void bind(void);

	// See Barrier.h for descriptions of these functions
	virtual void init(double nodeWidth, const Vec3& pos1, const Vec3& pos2) override;
	virtual bool getBoundingBox(Vec3& min, Vec3& max) override;
	virtual void addBarriersToTable(Grid* grid) override;
	virtual void addVertices(Mesh* barrierMesh, float z) override;
	virtual double onClick(treenode view, int clickCode, Vec3& pos) override;
	virtual double onMouseMove(const Vec3& pos, const Vec3& diff) override;
	virtual Divider* toDivider() override { return this; }

	void addCreatePointRecord(treenode view, Point* point);
	double onDestroy(TreeNode* view) override;
};

}