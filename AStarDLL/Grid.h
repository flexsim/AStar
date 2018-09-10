#pragma once

#include "FlexsimDefs.h"
#include "AStarClasses.h"
#include "AStarTypes.h"

namespace AStar {

class Grid : public SimpleDataType
{
public:
	Grid() {}
	Grid(AStarNavigator* navigator, double nodeWidth) : navigator(navigator), nodeWidth(nodeWidth) {}
	virtual void bind();
	virtual const char* getClassFactory() { return "AStar::Grid"; }

	typedef std::vector<std::vector<AStarNode>> NodeTable;
	NodeTable nodes;
	std::unique_ptr<unsigned int[]> heatMapBuffer;

	AStarNavigator* navigator = nullptr;
	double nodeWidth = 1.0;
	/// <summary>	True if there is no grid below this grid on the z axis. </summary>
	bool isLowestGrid = false;
	/// <summary>	True if this object is bounded on its xy plane, meaning there is another 
	/// 			grid on the same z plane as this grid. </summary>
	bool isBounded = false;
	/// <summary>	The minimum point. This is the minimum point of all matched barriers and objects. </summary>
	Vec3 minPoint;
	/// <summary>	The maximum point. This is the maximum point of all matched barriers and objects. </summary>
	Vec3 maxPoint;
	/// <summary>	The grid origin. This is based on minPoint, but is rounded so that the center of nodes are 
	/// 			in the center of model grid units. </summary>
	Vec3 gridOrigin;
	bool isLocWithinBounds(const Vec3& modelLoc, bool canExpand) const;
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
	void findGrowthBounds(Vec2& min, Vec2& max) const;
	AStarCell getCellFromLoc(const Vec3& modelLoc);
	Vec3 getLocFromCell(const AStarCell& cell) { return Vec3(gridOrigin.x + cell.col * nodeWidth, gridOrigin.y + cell.row * nodeWidth, minPoint.z); }
	void reset(AStarNavigator* nav);
	void buildNodeTable();
	void resolveGridOrigin();

	int __getRank() { return holder->rank; }
	__declspec(property(get = __getRank)) int rank;
	int __getNumRows() { return nodes.size(); }
	__declspec(property(get = __getNumRows)) int numRows;
	int __getNumCols() { return nodes.size() > 0 ? nodes[0].size() : 0; }
	__declspec(property(get = __getNumCols)) int numCols;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the A* node associated with the given cell. </summary>
	/// <remarks>	 </remarks>
	/// <param name="cell">	The cell. </param>
	/// <returns>	Null if it fails, else the node. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	AStarNode* getNode(const AStarCell& cell) { 
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
	void blockGridModelPos(const AStarCell& cell);
	void blockGridModelPos(const Vec3& pos) { blockGridModelPos(getCellFromLoc(pos)); }
	void blockNodeDirection(const AStarCell& cell, Direction direction, Barrier* barrier);
	void divideGridModelLine(const Vec3& fromPos, const Vec3& toPos, bool isOneWay, Barrier* barrier = nullptr);
	void visitGridModelLine(const Vec3& fromPos, const Vec3& toPos, std::function<void(const AStarCell& cell)>);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Visits cells around a given cell, expanding outward from the cell. </summary>
	///
	/// <remarks>	Anthony Johnson, 9/5/2018. </remarks>
	///
	/// <param name="centerCell">	The center cell. </param>
	/// <param name="callback">  	The cellback. If this callback returns false, the visiting loop 
	/// 							will be discontinued. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void visitCellsWidening(const AStarCell& centerCell, std::function<bool(const AStarCell& cell)> callback);
	void visitCellsWidening(const Vec3& center, std::function<bool(const AStarCell& cell)> callback)
	{
		visitCellsWidening(getCellFromLoc(center), callback);
	}


	Mesh boundsMesh;
	Mesh gridMesh;
	void buildBoundsMesh();
	void buildGridMesh(float zOffset);
	double maxHeatValue = 0.0;
	void drawHeatMap(TreeNode* view);
	void drawDestinationThreshold(treenode obj, const Vec3& loc, const Vec3& size);
	void checkGetOutOfBarrier(AStarCell& cell, TaskExecuter* traveler, int rowDest, int colDest, DestinationThreshold* threshold);

	void onDrag(treenode view, Vec3& offset);
	double onDrag(treenode view) override;
	void onClick(treenode view, int clickCode, const Vec3& pos);
	double onClick(treenode view, int clickCode) override;
};

}

