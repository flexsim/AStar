#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"
class PreferredPath :
	public Divider
{
public:
	double pathWeight;

	PreferredPath();
	PreferredPath(double pathWeight);
	virtual const char * getClassFactory(void);
	virtual void bind(void);

	// See Barrier.h for a description of these methods
	virtual void addBarriersToTable(AStarNode* edgeTable,
		std::unordered_map<unsigned int, AStarNodeExtraData>* extraData,
		double c0, double r0, unsigned int edgeTableXSize, unsigned int edgeTableYSize) override
	{}

	virtual void addPassagesToTable(AStarNode* edgeTable,
		std::unordered_map<unsigned int, AStarNodeExtraData>* extraData,
		double c0, double r0, unsigned int edgeTableXSize, unsigned int edgeTableYSize) override;

	virtual void addVertices(Mesh* barrierMesh, float z);
};

