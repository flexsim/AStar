#pragma once
#include "FlexsimDefs.h"
#include "AStarClasses.h"
#include "Point.h"
#include "Grid.h"
#include "TemporaryBarrier.h"
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
	AStarNavigator * __getNavigator();
	__declspec(property(get = __getNavigator)) AStarNavigator* navigator;
	TreeNode * points;
	NodeListArray<Point>::SdtSubNodeBindingType pointList;
	TreeNode* patternTable;
	double patternTotalWidth;
	double patternTotalHeight;
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
	static const int DIVIDER_POINT = 5;
	/// <summary>	For a standard rectangular barrier, arrow tells which arrow . </summary>
	unsigned int arrow;

	double nodeWidth;
	double useCondition = 0.0;
	treenode condition = nullptr;

	TemporaryBarrier conditionalBarrierChanges;

	Mesh drawMesh;

	Barrier();
	virtual ~Barrier();

	virtual const char * getClassFactory(void);
	virtual void bind(void);
	virtual void bindEvents() override;

	// This function adds two initial points to a barrier
	virtual void init(double nodeWidth, const Vec3& pos1, const Vec3& pos2);

	// This function is used by the AStarNavigator to determine the size of the grid.
	// It should return the bottom left [x0, y0, z0] and top right [x1, y1, z1] corners
	// of the barrier's 3D bounding box.
	virtual bool getBoundingBox(Vec3& min, Vec3& max);

	// This function is called by the AStarNavigator to determine the effect a barrier
	// will have on the nodes it influences.
	virtual void addBarriersToTable(Grid* grid);

	// This function is called by the AStarNavigator to add "passages" to the AStar grid
	// This is used by preferred paths to add preferred weights on the nodes in the node table.
	virtual void addPassagesToTable(Grid* grid) {}

	static void addMeshVertex(Mesh* mesh, float* pos, float* color, unsigned int* incNumVerts = nullptr);
	static void addMeshTriangle(Mesh* mesh, float* p1, float* p2, float* p3, float* color, unsigned int* incNumVerts = nullptr);

	virtual void drawManipulationHandles(treenode view);
	virtual void drawHoverHighlights(treenode view);
	// This function is called by the AStarNavigator class to add vertices to the 
	// given mesh. This mesh draws GL_TRIANGLES at z height and has an emissive per-vertex attribute.
	// It should also store the offset into the mesh as well as the number of vertices it stores.
	virtual void addVertices(Mesh* barrierMesh, float z);

	// These functions handle mouse events. [x, y] are model coords
	virtual double onClick(treenode view, int clickCode, Vec3& pos);
	virtual double onClick(treenode view, int clickCode) override;
	virtual double onMouseMove(const Vec3& pos, const Vec3& diff);
	virtual double onDrag(treenode view) override; 
	unsigned int getClassType() override;
	virtual double dragConnection(TreeNode* connectTo, char keyPressed, unsigned int classType) override;
	double onDestroy(TreeNode* view) override;
	double onUndo(bool isUndo, treenode undoRecord) override;


	// These functions are for modifying barrier points. They each 
	// check bounds before making any modifications.
	void addPoint(const Vec3& pos);
	ASTAR_FUNCTION Variant addPoint(FLEXSIMINTERFACE) { addPoint(Vec3(param(1), param(2), param(3))); return Variant(); }
	void removePoint(int pointIndex);
	ASTAR_FUNCTION Variant removePoint(FLEXSIMINTERFACE) { removePoint((int)param(1));  return Variant(); }
	void swapPoints(int index1, int index2);
	ASTAR_FUNCTION Variant swapPoints(FLEXSIMINTERFACE) { swapPoints((int)param(1), (int)param(2)); return Variant(); }
	Vec3 getPointCoords(int pointIndex);
	ASTAR_FUNCTION Variant getPointCoord(FLEXSIMINTERFACE);
	bool setPointCoords(int pointIndex, const Vec3& point);
	ASTAR_FUNCTION Variant setPointCoords(FLEXSIMINTERFACE) {
		setPointCoords((int)param(1), Vec3(param(2), param(3), param(4)));
		return Variant();
	}

	// These functions are for checking if the barrier is subclassed
	virtual Divider* toDivider() { return nullptr; }
	virtual OneWayDivider* toOneWayDivider() { return nullptr; }
	virtual PreferredPath* toPreferredPath() { return nullptr; }
	virtual Bridge* toBridge() { return nullptr; }
	virtual MandatoryPath* toMandatoryPath() { return nullptr; }

	void addPathVertices(Mesh* barrierMesh, float z, const Vec4f& color);
	virtual void onReset(AStarNavigator* nav);

	std::string getType() { return getClassFactory(); }
	ASTAR_FUNCTION Variant getType(FLEXSIMINTERFACE) { return getType(); }

	void setEditMode(int toMode) { mode = toMode; }
	ASTAR_FUNCTION Variant setEditMode(FLEXSIMINTERFACE) { setEditMode((int)param(1)); return Variant(); }

	void setActiveIndex(int toIndex) { activePointIndex = toIndex; }
	ASTAR_FUNCTION Variant setActiveIndex(FLEXSIMINTERFACE) { setActiveIndex((int)param(1)); return Variant(); }


	class PatternCell : public SimpleDataType
	{
	public:
		virtual const char* getClassFactory() override { return "AStar::Barrier::PatternCell"; }
		virtual void bind() override;
		double width = 1.0;
		double height = 1.0;
		double canGoUp = 0.0;
		double canGoDown = 0.0;
		double canGoLeft = 0.0;
		double canGoRight = 0.0;
	};
	void addPatternRow();
	Variant addPatternRow(FLEXSIMINTERFACE) { addPatternRow(); return Variant(); }
	void addPatternCol();
	Variant addPatternCol(FLEXSIMINTERFACE) { addPatternCol(); return Variant(); }
	void deletePatternRow();
	Variant deletePatternRow(FLEXSIMINTERFACE) { deletePatternRow(); return Variant(); }
	void deletePatternCol();
	Variant deletePatternCol(FLEXSIMINTERFACE) { deletePatternCol(); return Variant(); }

};

}