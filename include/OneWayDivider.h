#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"
class OneWayDivider :
	public Divider
{
public:
	virtual const char * getClassFactory(void);
	virtual void bind(void);

	// See Barrier.h for a description of these methods
	virtual void modifyTable(AStarNode* edgeTable, double c0, double r0,
		 unsigned int edgeTableXSize, unsigned int edgeTableYSize);
	virtual void addVertices(Mesh* barrierMesh, float z);
};

