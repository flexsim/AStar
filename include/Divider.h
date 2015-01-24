#pragma once
#include "FlexsimDefs.h"
#include "Barrier.h"
class Divider :
	public Barrier
{
public:
	Divider();

	virtual const char * getClassFactory(void);
	virtual void bind(void);

	// See Barrier.h for descriptions of these functions
	virtual bool getBoundingBox(double& x0, double& y0, double& x1, double& y1);
	virtual void addBarriersToTable(AStarNode* edgeTable, 
		std::unordered_map<unsigned int, AStarNodeExtraData>* extraData, 
		double c0, double r0, unsigned int edgeTableXSize, unsigned int edgeTableYSize) override;
	virtual void addVertices(Mesh* barrierMesh, float z);
	virtual double onClick(treenode view, int clickCode, double x, double y);
	virtual double onMouseMove(double x, double y, double dx, double dy);
};

