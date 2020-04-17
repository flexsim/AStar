#pragma once
#include "AStarClasses.h"
#include "FlexsimDefs.h"
#include <list>
#include <vector>
#include <deque>
#include <set>

namespace AStar {

enum Direction {
	Right = 1,
	Left = 2,
	Up = 3,
	Down = 4
};


struct astar_export Cell {
	union{
		struct{
			/// <summary>	The 1-based rank of the grid. Zero means undefined grid. </summary>
			unsigned int grid;
			unsigned short row;
			unsigned short col;
		};
		unsigned long long value;
	};
	static const int INVALID_ROW = USHRT_MAX;
	Cell() {}
	Cell(unsigned int grid, unsigned short row, unsigned short col) : grid(grid), row(row), col(col) {}
	Cell(unsigned long long value) : value(value) {}
	Cell& operator = (const Cell& other) { new (this) Cell(other); return *this; }
	bool operator == (const Cell& other) const { return value == other.value; }
	bool operator != (const Cell& other) const { return value != other.value; }
	bool operator < (const Cell& other) const { return value < other.value; }
	void bind(TreeNode* x, const char* prefix);
	void bind(SimpleDataType* sdt, const char* prefix = "");
	void bind(TreeNode* x);
	size_t getHash() const {
#ifdef _M_X64
		return value;
#else
		return ((unsigned long) value) ^ ((unsigned long)(value >> 32));
#endif
	}
};

enum ExtraDataReason : char {
	TraversalData = 0,
	AllocationData = 1,
	BridgeData = 2,
	PreferredPathData = 3,
	MandatoryPathData = 4,
	ConditionalBarrierData = 5
};

class AStarNode
{
public:
	union {
		struct {
			bool canGoRight : 1;
			bool canGoLeft : 1;
			bool canGoUp : 1;
			bool canGoDown : 1;
			/// <summary>	True if this node is in total search set. </summary>
			bool isInTotalSet : 1;
			/// <summary>	True if the node is still open (not closed) the path finding search 
			/// 			set, i.e. it is still in the open set. </summary>
			bool open : 1;
			bool unusedLowOrder1 : 1; // 2 bits to fill out low order byte
			bool unusedLowOrder2 : 1; 

			/// <summary>	True if this object has traversal tracking data, etc. Note that  </summary>
			bool hasTraversalData : 1;
			/// <summary>	True if this object has traversal tracking data, etc. Note that  </summary>
			bool hasAllocationData : 1;
			/// <summary>	True if this node is a start point for a bridge. Bridge information is stored in extra data </summary>
			bool hasBridgeStartPoint : 1;
			/// <summary>	True if this node is part of a preferred path and has a weight value stored in extra data. </summary>
			bool hasPreferredPathWeight : 1;
			/// <summary>	True if this node is part of a mandatory path. </summary>
			bool isOnMandatoryPath : 1;

			bool hasConditionalBarrier : 1;
			// 3 unused bits here
		};
		unsigned short value;
	};
	AStarNode() { value = 0; canGoRight = canGoLeft = canGoUp = canGoDown = open = true; }
	AStarNode(unsigned short value) : value(value) {}
	static int rowInc[];
	static int colInc[];
	bool canGo(Direction direction) { return ((0x1 << ((int)direction - 1)) & value) != 0; }
	void setCanGo(Direction direction, bool toValue) { if (toValue) value |= (0x1 << ((int)direction - 1)); else value &= ~(0x1 << ((int)direction - 1)); }
};

struct NodeAllocation
{
	NodeAllocation() : traveler(nullptr), acquireTime(0.0), releaseTime(0.0), traversalWeight(0.0), travelPathIndex(0), intermediateAllocationIndex(0) {}
	NodeAllocation(Traveler* traveler, const Cell& cell, int travelPathIndex, int intermediateAllocationIndex, double acquireTime, double releaseTime, double traversalWeight) :
		traveler(traveler), cell(cell), travelPathIndex(travelPathIndex), intermediateAllocationIndex(intermediateAllocationIndex), acquireTime(acquireTime), releaseTime(releaseTime), traversalWeight(traversalWeight)
	{}
	NodeAllocation& operator = (const NodeAllocation& other) { new (this) NodeAllocation(other); return *this; }
	Traveler* traveler;
	Cell cell;
	int travelPathIndex;
	int intermediateAllocationIndex;
	/// <summary>The acquire time of the allocation.</summary>
	double acquireTime;
	/// <summary>The release time of the allocation. If the release time is unknown, this will be DBL_MAX.</summary>
	double releaseTime;
	double traversalWeight;
	bool isMarkedForDeletion = false;

	void extendReleaseTime(double toTime);
	void truncateReleaseTime(double toTime);
	void bind(TreeNode* x);
	static void bindInterface();
	double __getAcquireTime() { return acquireTime; }
	double __getReleaseTime() { return releaseTime; }
	Traveler* __getTraveler() { return traveler; }

	operator bool() const { return traveler != nullptr; }
	bool operator !() const { return traveler == nullptr; }
	void construct() { new (this) NodeAllocation(); }
	void copyConstruct(const NodeAllocation& other) { new (this) NodeAllocation(other); }

};

struct astar_export ExtendedCell : public Cell {
	ExtendedCell(unsigned int grid, unsigned short row, unsigned short col) : Cell(grid, row, col) {}
	ExtendedCell(const Cell& other) : Cell(other) {}
	void construct(unsigned int grid, unsigned int row, unsigned int col) {
		new (this) ExtendedCell(grid, (unsigned short)row, (unsigned short)col);
	}
	void copyConstruct(const ExtendedCell& other) {
		new (this) ExtendedCell(other);
	}
	ExtendedCell& operator = (const ExtendedCell& other) { new (this) ExtendedCell(other); return *this; }
	int __getRow() { return *((short*)&row); }
	void __setRow(int toVal) { row = (unsigned short)toVal; node = nullptr; extra = nullptr; }
	int __getCol() { return *((short*)&col); }
	void __setCol(int toVal) { col = (unsigned short)toVal; node = nullptr; extra = nullptr; }
	operator bool();
	int operator !() { return !operator bool(); }
	static void bindInterface();
	AStarNode* node = nullptr;
	AStarNodeExtraData * extra = nullptr;
private:
	void __assertCachedPointers();
	void assertCachedPointers() { if (node) return; __assertCachedPointers(); }

public:
	NodeAllocation getAllocation(double atTime = -1);

	ExtendedCell adjacentCell(int direction);
	int canGo(int direction);
	Vec3 getLocation(AStarNavigator* nav);
	double getNodeWidth(AStarNavigator* nav);
};

typedef std::list<NodeAllocation> NodeAllocationList;
typedef std::list<NodeAllocation>::iterator NodeAllocationIterator;

struct AStarNodeExtraData : public SimpleDataType
{

	AStarNodeExtraData() : cell(0, 0, 0), bonusRight(0), bonusLeft(0), bonusUp(0), bonusDown(0) {}
	virtual const char* getClassFactory() { return "AStar::NodeExtraData"; }
	virtual void bind() override;
	Cell cell;

	double totalTraversals = 0;
	double totalBlockedTime = 0.0;
	int totalBlocks = 0;

	// preferred path weights
	union {
		struct {
			char bonusRight;
			char bonusLeft;
			char bonusUp;
			char bonusDown;
		};
		char bonus[4];
	};
	char getBonus(Direction direction) { return bonus[(int)direction - 1]; }

	std::vector<BridgeRoutingData*> bridges;

	std::vector<Barrier*> conditionalBarriers;
	void addConditionalBarrier(Barrier* barrier);

	NodeAllocationList allocations;
	NodeAllocationList requests;
	void removeAllocation(NodeAllocationIterator allocation);
	void onContinue(Traveler* blocker);
	void fulfillTopRequest();
	void onReleaseTimeExtended(NodeAllocation& alloc, double oldReleaseTime);
	void onReleaseTimeTruncated(NodeAllocation& alloc, double oldReleaseTime);

	/// <summary>	Adds a request to 'blockingAlloc'. </summary>
	/// <remarks>	Anthony.johnson, 4/17/2017. </remarks>
	/// <param name="request">			[in,out] The request. </param>
	/// <param name="blockingAlloc">	[in,out] The blocking allocate. </param>
	/// <returns>	The request that was added.</returns>
	NodeAllocation* addRequest(NodeAllocation& request, std::vector<Traveler*>* travelers = nullptr);

	void checkCreateContinueEvent();

	bool findDeadlockCycle(Traveler* start, std::vector<Traveler*>& travelers);

	class ContinueEvent : public FlexSimEvent
	{
	public:
		ContinueEvent() : FlexSimEvent() {}
		ContinueEvent(double time, Traveler* traveler, Traveler* blocker, Cell& cell);
		virtual const char* getClassFactory() override { return "AStar::AStarNodeExtraData::ContinueEvent"; }
		virtual void bind() override;
		Cell cell;
		virtual void execute() override;
	};
	ObjRef<ContinueEvent> continueEvent;
};


struct astar_export AStarPathEntry {
	AStarPathEntry() : cell(0, 0, 0), bridgeIndex(-1) {}
	AStarPathEntry(Cell cell, char bridgeIndex) : cell(cell), bridgeIndex(bridgeIndex) {}
	void bind(TreeNode* toNode);
	static void bindInterface();
	Cell cell;
	int bridgeIndex;

	ExtendedCell __getCell();
	__declspec(property(get = __getCell)) ExtendedCell extendedCell;
};

class TravelPath : public std::vector<AStarPathEntry>
{
public:
	astar_export double calculateTotalDistance(AStarNavigator* nav);
	AStarPathEntry __oneBasedIndex(int index) { return operator [](index - 1); }
	astar_export int __getLength();
	astar_export int indexOf(Cell& cell);
	astar_export AStarPathEntry& at(int index);
#ifndef COMPILING_ASTAR
	AStarPathEntry& operator [](int index) { return at(index); }
	int size() { return __getLength(); }
#endif
	static void bindInterface();
};

class AllocationRange {
public:
	Traveler* traveler = nullptr;
	int startIndex = 0;
	int size = 0;
	AllocationRange() {}
	AllocationRange& operator = (const AllocationRange& other) { new (this) AllocationRange(other); return *this; }
	void construct() { new (this) AllocationRange(); }
	void copyConstruct(const AllocationRange& other) { new (this) AllocationRange(other); }
	AllocationRange(Traveler* traveler, int startIndex, int size) 
		: traveler(traveler), startIndex(startIndex), size(size) {}

	int __getLength() { return size; }
	NodeAllocation operator [] (int oneBasedIndex);
	static void bindInterface();
};

struct AStarSearchEntry {
	AStarSearchEntry() : prevBridgeIndex(-1) {}
	// f, g and h are the elements of the formula f(x) = g(n) + h(n)
	// where g is the calculated cost to get to n, and h is the 
	// heuristic that defines the estimated cost to get from n to x
	// where n is the current node being resolved and x is the destination
	float f;
	float g;
	float h;
	Cell cell;
	unsigned int previous;
	float rotOnArrival;
	char prevBridgeIndex;
	bool closed;
};

struct CachedPathKey {
	Cell startCell;
	Cell endCell;
	bool isUsingMandatoryPaths;

	treenode destination;
	std::vector<bool> barrierConditions;
	bool operator == (const CachedPathKey& other) const { 
		return startCell == other.startCell
			&& endCell == other.endCell
			&& destination == other.destination 
			&& isUsingMandatoryPaths == other.isUsingMandatoryPaths
			&& barrierConditions == other.barrierConditions; }

	struct Hash {
		size_t operator()(const CachedPathKey& key) const
		{	// hash _Keyval to size_t value by pseudorandomizing transform
			int bits = sizeof(void*) == 4 ? 32 : 64;
			size_t val = key.startCell.getHash() ^ key.endCell.getHash() ^ (size_t)key.destination ^ (size_t)key.isUsingMandatoryPaths;
			for (int i = 0; i < key.barrierConditions.size(); i++) {
				val ^= (((size_t)key.barrierConditions[i]) << (i % bits));
			}
			return val;
		}
	};
};

struct AllocationStep {
	AllocationStep(const Cell& fromCell, const Cell& toCell) :
		fromCell(fromCell), toCell(toCell) {

		isDiagonal = toCell.row != fromCell.row && toCell.col != fromCell.col;
		if (isDiagonal) {
			isVerticalDeepSearch = abs(toCell.row - fromCell.row) == 2;
			isHorizontalDeepSearch = abs(toCell.col - fromCell.col) == 2;
			if (isVerticalDeepSearch) {
				intermediateCell1 = Cell(fromCell.grid, (toCell.row + fromCell.row) / 2, fromCell.col);
				intermediateCell2 = Cell(fromCell.grid, intermediateCell1.row, toCell.col);
			} else if (isHorizontalDeepSearch) {
				intermediateCell1 = Cell(fromCell.grid, fromCell.row, (toCell.col + fromCell.col) / 2);
				intermediateCell2 = Cell(fromCell.grid, toCell.row, intermediateCell1.col);
			} else {
				if (sign(toCell.col - fromCell.col) == sign(toCell.row - fromCell.row)) {
					// it's a "forward-slash diagonal"
					intermediateCell1 = Cell(fromCell.grid, max(toCell.row, fromCell.row), min(toCell.col, fromCell.col));
					intermediateCell2 = Cell(fromCell.grid, min(toCell.row, fromCell.row), max(toCell.col, fromCell.col));
				}
				else {
					// it's a "back-slash diagonal"
					intermediateCell1 = Cell(fromCell.grid, min(toCell.row, fromCell.row), min(toCell.col, fromCell.col));
					intermediateCell2 = Cell(fromCell.grid, max(toCell.row, fromCell.row), max(toCell.col, fromCell.col));
				}

			}
		} else isVerticalDeepSearch = isHorizontalDeepSearch = false;

	}
	bool isVerticalDeepSearch;
	bool isHorizontalDeepSearch;
	bool isDiagonal;
	Cell fromCell;
	Cell toCell;
	Cell intermediateCell1;
	Cell intermediateCell2;

	bool isImmediatelyBlocked(Traveler* traveler);
};

struct astar_export DestinationThreshold
{
	DestinationThreshold() : xAxisThreshold(0), yAxisThreshold(0), rotation(0), anyThresholdRadius(0) {}
	DestinationThreshold(treenode dest, double fudgeFactor);
	double xAxisThreshold;
	double yAxisThreshold;
	double rotation;
	double anyThresholdRadius;
	bool isWithinThreshold(const Cell& cell, Grid* grid, const Vec3& destLoc);
	void bind(SimpleDataType* sdt, const char* prefix);
};

class AStarNamespace { // for FlexScript access
public:
	static void bindInterface();
	static AStarNavigator* __getNavigator();
};


class AStarDirection { // for FlexScript access
public:
	static void bindInterface();
};

}