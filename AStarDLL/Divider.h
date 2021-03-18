#pragma once
#include "FlexsimDefs.h"
#include "Barrier.h"

namespace AStar {

class Divider : public Barrier
{
public:
	Divider();

	virtual void bindVariables(void) override;

	// See Barrier.h for descriptions of these functions
	virtual void init(const Vec2& nodeWidth, const Vec3& pos1, const Vec3& pos2) override;
	virtual bool getLocalBoundingBox(Vec3& min, Vec3& max) override;
	virtual void addBarriersToTable(Grid* grid) override;
	void drawManipulationHandles(treenode view, float zOffset);
	virtual void drawManipulationHandles(treenode view) override;
	virtual void addVertices(treenode view, Mesh* barrierMesh, float z, DrawStyle drawStyle) override;
	virtual double onClick(treenode view, int clickCode, Vec3& pos) override;
	virtual double dragPressedPick(treenode view, Vec3& pos, Vec3& diff) override;
	virtual Divider* toDivider() override { return this; }

	void addCreatePointRecord(treenode view, Point* point);
	double onDestroy(TreeNode* view) override;

	virtual void drawPickObjects(treenode view) override;

	double isTwoWay = 1.0;
};

}