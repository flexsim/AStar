#pragma once
#include "FlexsimDefs.h"
#include "AStarClasses.h"
#include "Point.h"
#include "Grid.h"
#include <vector>
#include <unordered_map>

namespace AStar {

/* 
This class is the base class for an AStar barrier object.
*/

class AStarNode;
struct AStarNodeExtraData;

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
	unsigned int isHovered;


	static const int POINT_EDIT = 0x1;
	static const int CREATE = 0x2;
	static const int DYNAMIC_CREATE = 0x3;
	static const int MOVE = 0x4;
	/// <summary>	The current editing mode. If non-zero, one of POINT_EDIT, CREATE, DYNAMIC_CREATE, and MOVE. </summary>
	unsigned int mode;

	unsigned int lastMode;
	/// <summary>	The index of the point that is being edited by the user. </summary>
	unsigned int activePointIndex;

	static const int ARROW_LEFT = 1;
	static const int ARROW_RIGHT = 2;
	static const int ARROW_TOP = 3;
	static const int ARROW_BOTTOM = 4;
	/// <summary>	For a standard rectangular barrier, arrow tells which arrow . </summary>
	unsigned int arrow;

	double nodeWidth;
	NodeListArray<Grid>::SdtSubSubNodeCouplingType grids;
	bool isMemberOfGrid(Grid* grid) {
		return std::find(grids.begin(), grids.end(), grid) != grids.end();
	}
	bool isMemberOfGrid(int gridRank) {
		return std::find_if(grids.begin(), grids.end(), [&](Grid* grid) { return grid->rank == gridRank; }) != grids.end();
	}

	Barrier();
	virtual ~Barrier();

	virtual const char * getClassFactory(void);
	virtual void bind(void);

	// This function adds two initial points to a barrier
	virtual void init(double nodeWidth, double x1, double y1, double x2, double y2);

	// This function is used by the AStarNavigator to determine the size of the grid.
	// It should return the bottom left [x0, y0, z0] and top right [x1, y1, z1] corners
	// of the barrier's 3D bounding box.
	virtual bool getBoundingBox(Vec3& min, Vec3& max);

	// This function is used by the AStarNavigator to determine the effect a barrier
	// will have on the nodes it influences. [c0, r0] are the coords of the bottom left
	// corner of the grid.
	virtual void addBarriersToTable(Grid* grid);

	// This function is used by the AStarNavigator to determine the effect a barrier
	// will have on the nodes it influences. [c0, r0] are the coords of the bottom left
	// corner of the grid.
	virtual void addPassagesToTable(Grid* grid){}

	// This function is called by the AStarNavigator class to add vertices to the 
	// given mesh. This mesh draws GL_TRIANGLES at z height and has an emissive per-vertex attribute.
	// It should also store the offset into the mesh as well as the number of vertices it stores.
	virtual void addVertices(Mesh* barrierMesh, float z);

	// These functions handle mouse events. [x, y] are model coords
	virtual double onClick(treenode view, int clickCode, double x, double y);
	virtual double onMouseMove(const Vec3& pos, const Vec3& diff);

	// These functions are for modifying barrier points. They each 
	// check bounds before making any modifications.
	void addPoint(double x, double y, double z = 0);
	void removePoint(int pointIndex);
	void swapPoints(int index1, int index2);
	bool getPointCoords(int pointIndex, Vec3& point);
	bool setPointCoords(int pointIndex, const Vec3& point);

	// These functions are for checking if the barrier is subclassed
	virtual Divider* toDivider() { return nullptr; }
	virtual OneWayDivider* toOneWayDivider() { return nullptr; }
	virtual PreferredPath* toPreferredPath() { return nullptr; }
	virtual Bridge* toBridge() { return nullptr; }

	void addPathVertices(Mesh* barrierMesh, float z, const Vec4f& color);
	virtual void onReset(AStarNavigator* nav) {}
};

}