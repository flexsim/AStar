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

class Barrier : public FlexSimEventHandler
{
private:
	float triangleEdgeLength;

public:
	TreeNode* navigatorCoupling;
	AStarNavigator * __getNavigator();
	__declspec(property(get = __getNavigator)) AStarNavigator* navigator;
	TreeNode * points;
	NodeListArray<Point>::SdtSubNodeBindingType pointList;
	TreeNode* patternTable;
	bool isMeshDirty = true;

	static const int POINT_EDIT = 0x1;
	static const int CREATE = 0x2;
	static const int DYNAMIC_CREATE = 0x3;
	static const int MOVE = 0x4;
	/// <summary>	The current editing mode. If non-zero, one of POINT_EDIT, CREATE, DYNAMIC_CREATE, and MOVE. </summary>
	unsigned int mode = 0;
	/// <summary>	The index of the point that is being edited by the user. </summary>
	unsigned int activePointIndex = 0;

	static const int PICK_ARROW_LEFT = 1;
	static const int PICK_ARROW_RIGHT = 2;
	static const int PICK_ARROW_TOP = 3;
	static const int PICK_ARROW_BOTTOM = 4;

	static const int PICK_POINT = 6;

	static const int PICK_SPLIT_PATTERN_COL = 7;
	static const int PICK_SPLIT_PATTERN_ROW = 8;
	static const int PICK_MERGE_PATTERN_COLS = 9;
	static const int PICK_MERGE_PATTERN_ROWS = 10;
	static const int PICK_PATTERN_SIZER_X = 11;
	static const int PICK_PATTERN_SIZER_Y = 12;
	static const int PICK_PATTERN_DIRECTION_LEFT = 13;
	static const int PICK_PATTERN_DIRECTION_RIGHT= 14;
	static const int PICK_PATTERN_DIRECTION_UP = 15;
	static const int PICK_PATTERN_DIRECTION_DOWN = 16;

	double nodeWidth = 1.0;
	double useCondition = 0.0;
	treenode condition = nullptr;

	TemporaryBarrier conditionalBarrierChanges;

	Mesh mesh;

	Barrier();
	virtual ~Barrier();

	virtual void bindVariables(void) override;
	virtual void bind() override;
	virtual void bindEvents() override;

	void assertNavigator();
	ASTAR_FUNCTION Variant assertNavigator(FLEXSIMINTERFACE) { assertNavigator(); return Variant(); }

	// This function adds two initial points to a barrier
	virtual void init(double nodeWidth, const Vec3& pos1, const Vec3& pos2);

protected:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the object's bounding box in local coordinates. </summary>
	///
	/// <remarks>	Anthony Johnson, 10/10/2018. </remarks>
	///
	/// <param name="min">	[in,out] The minimum. </param>
	/// <param name="max">	[in,out] The maximum. </param>
	///
	/// <returns>	True if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool getLocalBoundingBox(Vec3& min, Vec3& max);
public:
	// This function is used by the AStarNavigator to determine the size of the grid.
	// It should return the bottom left [x0, y0, z0] and top right [x1, y1, z1] corners
	// of the barrier's 3D bounding box, in model coordinates.
	bool getBoundingBox(Vec3& min, Vec3& max, bool inLocalCoords = false);

	// This function is called by the AStarNavigator to determine the effect a barrier
	// will have on the nodes it influences.
	virtual void addBarriersToTable(Grid* grid);

	// This function is called by the AStarNavigator to add "passages" to the AStar grid
	// This is used by preferred paths to add preferred weights on the nodes in the node table.
	virtual void addPassagesToTable(Grid* grid) {}

	static void addMeshVertex(Mesh* mesh, float* pos, float* color);
	static void addMeshVertex(Mesh* mesh, Vec3f& pos, Vec2f& tex, Vec4f& color);
	static void addMeshTriangle(Mesh* mesh, float* p1, float* p2, float* p3, float* color);
	static void addMeshTriangle(Mesh* mesh, Vec3f& p1, Vec2f& tex1, Vec3f& p2, Vec2f& tex2, Vec3f& p3, Vec2f& tex3, Vec4f& color);
	static void addMeshLine(Mesh* mesh, Vec3f& p1, Vec3f& p2, Vec4f& color);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Draw manipulation handles. Called when the object is the view's selected object. </summary>
	///
	/// <remarks>	Anthony Johnson, 9/25/2018. </remarks>
	///
	/// <param name="view">	The view. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void drawManipulationHandles(treenode view);

	enum DrawStyle {
		Basic,
		Selected,
		Highlighted,
		Hovered
	};
	// This function is called by the AStarNavigator class to add vertices to the 
	// given mesh. This mesh draws GL_TRIANGLES at z height and has an emissive per-vertex attribute.
	// It should also store the offset into the mesh as well as the number of vertices it stores.
	virtual void addVertices(treenode view, Mesh* barrierMesh, float z, DrawStyle drawStyle);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Draw the picking mode elements. </summary>
	///
	/// <remarks>	This is only called when picking mode is on, and it draws each of the 
	/// 			different pickable elements of the object separately. The divider overrides 
	/// 			this to draw each point.</remarks>
	///
	/// <param name="view">	The view. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void drawPickObjects(treenode view) {}

	// These functions handle mouse events. [x, y] are model coords
	virtual double onClick(treenode view, int clickCode, Vec3& pos);
	virtual double onClick(treenode view, int clickCode) override;
	virtual double dragPressedPick(treenode view, Vec3& pos, Vec3& diff);
	ASTAR_FUNCTION Variant dragPressedPick(FLEXSIMINTERFACE) { return dragPressedPick(param(1), Vec3(param(2), param(3), param(4)), Vec3(param(5), param(6), param(7))); }
	virtual double onDrag(treenode view) override;
	double onPreDraw(treenode view);
	double onDraw(treenode view);
	unsigned int getClassType() override;
	virtual double dragConnection(TreeNode* connectTo, char keyPressed, unsigned int classType) override;
	double onDestroy(TreeNode* view) override;
	double onUndo(bool isUndo, treenode undoRecord) override;
	double onCreate(double dropx, double dropy, double dropz, int iscopy) override;

	void updateSpatialsToEncompassPoints();
	ASTAR_FUNCTION Variant updateSpatialsToEncompassPoints(FLEXSIMINTERFACE) { updateSpatialsToEncompassPoints(); return Variant(); }

	// These functions are for modifying barrier points. They each 
	// check bounds before making any modifications.
	Point* addPoint(const Vec3& pos);
	ASTAR_FUNCTION Variant addPoint(FLEXSIMINTERFACE) { return addPoint(Vec3(param(1), param(2), param(3)))->holder; }
	void removePoint(int pointIndex);
	ASTAR_FUNCTION Variant removePoint(FLEXSIMINTERFACE) { removePoint((int)param(1));  return Variant(); }
	void swapPoints(int index1, int index2);
	ASTAR_FUNCTION Variant swapPoints(FLEXSIMINTERFACE) { swapPoints((int)param(1), (int)param(2)); return Variant(); }
	Vec3 getLocalPointCoords(int pointIndex);
	Vec3 getPointCoords(int pointIndex);
	ASTAR_FUNCTION Variant getPointCoord(FLEXSIMINTERFACE);
	bool setPointCoords(int pointIndex, const Vec3& point);
	ASTAR_FUNCTION Variant setPointCoords(FLEXSIMINTERFACE) {
		setPointCoords((int)param(1), Vec3(param(2), param(3), param(4)));
		return Variant();
	}

	// These functions are for checking if the barrier is subclassed
	virtual Divider* toDivider() { return nullptr; }
	virtual PreferredPath* toPreferredPath() { return nullptr; }
	virtual Bridge* toBridge() { return nullptr; }
	virtual MandatoryPath* toMandatoryPath() { return nullptr; }
	bool isBasicBarrier() { return toDivider() == nullptr && toPreferredPath() == nullptr && toBridge() == nullptr && toMandatoryPath() == nullptr; }

	void addPathVertices(treenode view, Mesh* barrierMesh, float z, const Vec4f& color, DrawStyle drawStyle, bool twoWay);
	virtual void onReset(AStarNavigator* nav);

	std::string getType() { return node_b_classes->subnodes[1]->name.c_str(); }
	ASTAR_FUNCTION Variant getType(FLEXSIMINTERFACE) { return getType(); }

	Variant getEditMode(FLEXSIMINTERFACE) { return mode; }
	void setEditMode(int toMode) { mode = toMode; }
	ASTAR_FUNCTION Variant setEditMode(FLEXSIMINTERFACE) { setEditMode((int)param(1)); return Variant(); }
	void abortCreationMode();
	ASTAR_FUNCTION Variant abortCreationMode(FLEXSIMINTERFACE) { abortCreationMode(); return Variant(); }

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
	void splitPatternRow(int row, treenode view);
	Variant splitPatternRow(FLEXSIMINTERFACE) { splitPatternRow((int)param(1), param(2)); return Variant(); }
	void splitPatternCol(int col, treenode view);
	Variant splitPatternCol(FLEXSIMINTERFACE) { splitPatternCol((int)param(1), param(2)); return Variant(); }
	void mergePatternRows(int firstRow, treenode view);
	Variant mergePatternRows(FLEXSIMINTERFACE) { mergePatternRows((int)param(1), param(2)); return Variant(); }
	void mergePatternCols(int firstCol, treenode view);
	Variant mergePatternCols(FLEXSIMINTERFACE) { mergePatternCols((int)param(1), param(2)); return Variant(); }
	void scalePatternRowsOnSizeChange(double oldYSize, double newYSize);
	void scalePatternColsOnSizeChange(double oldXSize, double newXSize);

	PatternCell* getPatternCell(Vec3& modelPos);
	PatternCell* getPatternCell(const Cell& cell);

	void dragPatternCellSizer(PatternCell* cell, double diff, bool isXSizer);
	void assertValidPatternTable();

	static const int VISIT_FIRST_ROW_ONLY = 0x1;
	static const int VISIT_FIRST_COL_ONLY = 0x2;
	static const int VISIT_BACKWARDS = 0x4;
	void visitPatternCells(std::function<void(PatternCell*)> func, int flags = 0);

	Vec3 getPointToModelOffset();
	void setSizeComponent(treenode sizeAtt, double toSize);
	ASTAR_FUNCTION Variant setSizeComponent(FLEXSIMINTERFACE) { setSizeComponent(param(1), param(2)); return Variant(); }
};

}