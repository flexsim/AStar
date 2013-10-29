#pragma once
#include "FlexsimDefs.h"
#include "Point.h"
#include <vector>
#include <unordered_map>

/* 
This class is the base class for an AStar barrier object.
*/

struct AStarNode;
struct AStarNodeExtraData;
class Mesh;

class Barrier :
	public SimpleDataType
{
private:
	float triangleEdgeLength;

public:
	TreeNode* points;
	NodeListArray<Point>::SdtSubNodeBindingType pointList;
	unsigned int meshOffset;
	unsigned int nrVerts;
	unsigned int isActive;

	unsigned int mode;
	unsigned int activePointIndex;

	double nodeWidth;

	Barrier();
	virtual ~Barrier();

	virtual const char * getClassFactory(void);
	virtual void bind(void);

	// This function adds two initial points to a barrier
	virtual void init(double nodeWidth, double x1, double y1, double x2, double y2);

	// This function is used by the AStarNavigator to determine the size of the grid.
	// It should return the bottom left [x0, y0] and top right [x1, y1] corners
	// of the barrier's 2D bounding box.
	virtual bool getBoundingBox(double& x0, double& y0, double& x1, double& y1);

	// This function is used by the AStarNavigator to determine the effect a barrier
	// will have on the nodes it influences. [c0, r0] are the coords of the bottom left
	// corner of the grid.
	virtual void modifyTable(AStarNode* edgeTable, 
		std::unordered_map<unsigned int, AStarNodeExtraData>* extraData, 
		double c0, double r0, unsigned int edgeTableXSize, unsigned int edgeTableYSize);

	// This function is called by the AStarNavigator class to add vertices to the 
	// given mesh. This mesh draws GL_TRIANGLES at z height and has an emissive per-vertex attribute.
	// It should also store the offset into the mesh as well as the number of vertices it stores.
	virtual void addVertices(Mesh* barrierMesh, float z);

	// These functions handle mouse events. [x, y] are model coords
	virtual double onClick(treenode view, int clickCode, double x, double y);
	virtual double onMouseMove(double x, double y, double dx, double dy);

	// These functions are for modifying barrier points. They each 
	// check bounds before making any modifications.
	void addPoint(double x, double y);
	void removePoint(int pointIndex);
	void swapPoints(int index1, int index2);
	bool getPointCoords(int pointIndex, double& x, double& y);
	bool setPointCoords(int pointIndex, double x, double y);
};

