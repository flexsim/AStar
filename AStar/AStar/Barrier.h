#pragma once
#include "FlexsimDefs.h"
#include "mesh.h"

/* 
This class is the base class for an AStar barrier object.
*/

struct AStarNode;

class Barrier :
	public SimpleDataType
{
protected:
	double x0, y0, x1, y1;
	static Mesh triangleMesh;
	static Mesh quadMesh;
	static Mesh triangleStripMesh;
	static Mesh quadStripMesh;

public:
	Barrier();
	Barrier(double x0, double y0, double x1, double y1);
	virtual ~Barrier();

	virtual const char * getClassFactory(void);
	virtual void bind(void);

	// This function is used by the AStarNavigator to determine the size of the grid.
	// It should return the bottom left (x0, y0) and top right (x1, y1) corners
	// of the barrier's bounding box.
	virtual void getBoundingBox(double& x0, double& y0, double& x1, double& y1);

	// This function is used by the AStarNavigator to determine the effect a barrier
	// will have on the nodes it influences.
	virtual void modifyTable(AStarNode* edgeTable, unsigned int sx, unsigned int sy);
};

