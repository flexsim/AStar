#pragma once

#include "FlexsimDefs.h"
#include "AStarClasses.h"
#include "AStarTypes.h"
#include "BridgeRoutingData.h"

namespace AStar {

class Grid : public FlexSimEventHandler
{
public:
	Grid() : nodeSize{ 1.0, 1.0 }, gridOrigin(0.0, 0.0, 0.0) {}
	Grid(AStarNavigator* navigator, double nodeWidth) : nodeSize{ nodeWidth, nodeWidth }, gridOrigin(0.0, 0.0, 0.0), navigator(navigator) {}
	virtual ~Grid();
	virtual void bindVariables() override;
	virtual void bind() override;
	virtual const char* getClassFactory() override { return "AStar::Grid"; }
	virtual unsigned int getClassType() override { return CLASSTYPE_WANTCONNECTLOGIC; }

	typedef std::vector<std::vector<AStarNode>> NodeTable;
	NodeTable nodes;
	std::unique_ptr<unsigned int[]> heatMapBuffer;
	int heatMapWidth = 0;
	int heatMapHeight = 0;
	GLuint textureID = 0;

	AStarNavigator* navigator = nullptr;
	Vec2 nodeSize;
	double minNodeSize;
	double diagDist = 1.41421356;
	double deepDiagDist = 2.236067977;
	constexpr static double UNINITIALIZED = -1.0;
	bool __canDoDeepDiag() { return nodeSize.x == nodeSize.y; }
	__declspec(property(get = __canDoDeepDiag)) bool canDoDeepDiag;
	/// <summary>	True if there is no grid below this grid on the z axis. </summary>
	double _isLowestGrid = 0.0;
	bool _getIsLowestGrid() { return static_cast<bool>(_isLowestGrid); }
	void _setIsLowestGrid(bool newVal) { _isLowestGrid = static_cast<double>(newVal); }
	__declspec(property(get = _getIsLowestGrid, put = _setIsLowestGrid)) bool isLowestGrid;
	/// <summary>	True if this object is bounded on its xy plane, meaning there is another 
	/// 			grid on the same z plane as this grid. </summary>
	double _isBounded = 0.0;
	bool _getIsBounded() { return static_cast<bool>(_isBounded); }
	void _setIsBounded(bool newVal) { _isBounded = static_cast<double>(newVal); }
	__declspec(property(get = _getIsBounded, put = _setIsBounded)) bool isBounded;
	/// <summary>	The minimum point. This is the minimum point of all matched barriers and objects. </summary>
	Vec3 minPoint;
	/// <summary>	The maximum point. This is the maximum point of all matched barriers and objects. </summary>
	Vec3 maxPoint;
	/// <summary>	The grid origin. This is based on minPoint, but is rounded so that the center of nodes are 
	/// 			in the center of model grid units. </summary>
	Vec3 gridOrigin;
	/// <summary>	Tells if this grid is user-customized. If the user has ever manipulated this 
	/// 			grid directly, or created it directly, then it is user-customized. </summary>
	double isUserCustomized = false;
	double noSelect = false;
	bool isLocWithinBounds(const Vec3& modelLoc, bool canExpand, bool addSurroundDepth) const;
	bool isLocWithinVerticalBounds(double) const;
	bool intersectBoundingBox(Vec3& min, Vec3& max) const;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Will attempt to grow the grid's bounds to encompass the bounding box. </summary>
	///
	/// <remarks>	This method will grow the grid as far as it can without overlapping any other 
	/// 			grids on its same z plane. </remarks>
	///
	/// <param name="min">			   	The minimum point of the bounding box. </param>
	/// <param name="max">			   	The maximum point of the bounding box. </param>
	/// <param name="addSurroundDepth">	True to add surround depth. </param>
	///
	/// <returns>	True if it succeeds in fully enclosing the bounding box, false if it did not 
	/// 			fully enclose it. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool growToEncompassBoundingBox(Vec3 min, Vec3 max, bool addSurroundDepth);
	bool shrinkToFitGrowthBounds();
	void findGrowthBounds(Vec2& min, Vec2& max) const;
	Cell getCell(const Vec3& modelLoc);
	Vec3 getLocation(const Cell& cell) { return Vec3(gridOrigin.x + cell.col * nodeSize.x, gridOrigin.y + cell.row * nodeSize.y, minPoint.z); }
	void reset(AStarNavigator* nav);

	void growToBarriers();
	void buildNodeTable();
	void resolveGridOrigin();
	void updateSpatials(bool applySpatialsToGrid = false);

	int __getRank() { return getrank(stored(holder)->first->value); }
	__declspec(property(get = __getRank)) int rank;
	int __getNumRows() { return (int)nodes.size(); }
	__declspec(property(get = __getNumRows)) int numRows;
	int __getNumCols() { return nodes.size() > 0 ? (int)nodes[0].size() : 0; }
	__declspec(property(get = __getNumCols)) int numCols;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the A* node associated with the given cell. </summary>
	/// <remarks>	 </remarks>
	/// <param name="cell">	The cell. </param>
	/// <returns>	Null if it fails, else the node. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	AStarNode* getNode(const Cell& cell) { 
		return getNode(cell.row, cell.col);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the A* node associated with the given row and column in the table. </summary>
	/// <remarks>
	/// Note that this is a "safe" returning method, meaning it will always return a valid node even
	/// if it is an incorrect node.
	/// </remarks>
	/// <param name="row">	The cell. </param>
	/// <param name="col">	The col. </param>
	/// <returns>	Null if it fails, else the node. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	AStarNode* getNode(int row, int col);

	void addSolidBarrierToTable(const Vec3 & min, const Vec3 & max, Barrier* barrier = nullptr);
	void addObjectBarrierToTable(treenode obj);
	void blockGridModelPos(const Cell& cell);
	void blockGridModelPos(const Vec3& pos) { blockGridModelPos(getCell(pos)); }
	void blockNodeDirection(const Cell& cell, Direction direction, Barrier* barrier);
	void divideGridModelLine(const Vec3& fromPos, const Vec3& toPos, bool isOneWay, Barrier* barrier = nullptr);
	void visitGridModelLine(const Vec3& fromPos, const Vec3& toPos, std::function<void(const Cell& cell)>);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Visits cells around a given cell, expanding outward from the cell. </summary>
	///
	/// <remarks>	Anthony Johnson, 9/5/2018. </remarks>
	///
	/// <param name="centerCell">	The center cell. </param>
	/// <param name="callback">  	The cellback. If this callback returns false, the visiting loop 
	/// 							will be discontinued. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void visitCellsWidening(const Cell& centerCell, std::function<bool(const Cell& cell)> callback);
	void visitCellsWidening(const Vec3& center, std::function<bool(const Cell& cell)> callback)
	{
		visitCellsWidening(getCell(center), callback);
	}


	Mesh boundsMesh;
	bool isDirtyByUser = false;
	Mesh gridMesh;
	void buildBoundsMesh(Mesh& mesh, bool asOutline, Vec4f& color);
	void buildBoundsMesh();
	void buildGridMesh(float zOffset);
	void drawHeatMap(TreeNode* view);
	void drawDestinationThreshold(treenode obj, const Vec3& loc, const Vec3& size);
	void checkGetOutOfBarrier(Cell& cell, TaskExecuter* traveler, int rowDest, int colDest, const DestinationThreshold* threshold);
	void buildBridgeDijkstraTables();


	void onDrag(treenode view, Vec3& offset);
	void onDrag(treenode view, Vec3&& offset);
	virtual double onDrag(treenode view) override;
	void onClick(treenode view, int clickCode, const Vec3& pos);
	double onClick(treenode view, int clickCode) override;
	double onCreate(bool isCopy) override;
	static void onPostCreate(void* data);

	double onPreDraw(TreeNode* view) override;
	double onDraw(TreeNode* view) override;
	void drawSizerHandles(treenode view, int pickingMode);
	void drawBounds(treenode view, treenode selObj, treenode hoverObj, int pickingMode);

	void getBoundsVertices(Vec3f& bottomLeft, Vec3f& topRight, Vec3f& topLeft, Vec3f& bottomRight,
		Vec3f& oBottomLeft, Vec3f& oTopRight, Vec3f& oTopLeft, Vec3f& oBottomRight);
	static void addVertex(Mesh& mesh, Vec3f& point);
	static void addTriangle(Mesh& mesh, Vec3f& p1, Vec3f& p2, Vec3f& p3);
	static void addQuad(Mesh& mesh, Vec3f& p1, Vec3f& p2, Vec3f& p3, Vec3f& p4);
	virtual double dragConnection(TreeNode* connectTo, char keyPressed, unsigned int classType) override;
	void dragPressedPick(treenode view, Vec3& pos, Vec3& diff);
	void dragPressedPick(treenode view, Vec3&& pos, Vec3&& diff);
	Variant dragPressedPick(FLEXSIMINTERFACE)
	{
		dragPressedPick(param(1), Vec3(param(2), param(3), param(4)), Vec3(param(5), param(6), param(7)));
		return Variant();
	}
	void makeDirty();
	Variant makeDirty(FLEXSIMINTERFACE) { makeDirty(); return Variant(); }

	NodeListArray<BridgeRoutingData>::CouplingSdtSubNodeType bridgeData;
	virtual double onDestroy(treenode view) override;
	void bindNavigator();
	virtual double onUndo(bool isUndo, treenode undoRecord) override;
};

}

