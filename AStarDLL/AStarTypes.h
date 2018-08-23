#pragma once
#include "AStarClasses.h"
#include "FlexsimDefs.h"
#include <list>
#include <vector>
#include <deque>
#include <set>

namespace AStar {

enum Direction {
	Right = 0,
	Left = 1,
	Up = 2,
	Down = 3
};


struct AStarCell {
	union{
		struct{
			/// <summary>	The 1-based rank of the grid. Zero means undefined grid. </summary>
			unsigned int grid;
			unsigned short col;
			unsigned short row;
		};
		unsigned long long colRow;
	};
	AStarCell() {}
	AStarCell(unsigned int grid, unsigned short col, unsigned short row) : grid(grid), col(col), row(row) {}
	AStarCell(unsigned long long colRow) : colRow(colRow) {}
	bool operator == (const AStarCell& other) const { return colRow == other.colRow; }
	bool operator != (const AStarCell& other) const { return colRow != other.colRow; }
	void bind(TreeNode* x, const char* prefix);
	void bind(SimpleDataType* sdt, const char* prefix = "");
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
			bool noExtraData : 1;
			bool notInTotalSet : 1;
			bool open : 1;
		};
		unsigned char value;
	};
	AStarNode() {}
	AStarNode(char value) : value(value) {}
	bool __extraData() { return !noExtraData; }
	bool __inTotalSet() { return !notInTotalSet; }
	void __setInTotalSet(bool toVal) { notInTotalSet = !toVal; }
	__declspec(property(get = __extraData)) bool hasExtraData;
	__declspec(property(get = __inTotalSet, put = __setInTotalSet)) bool isInTotalSet;
	static int rowInc[];
	static int colInc[];
	bool canGo(Direction direction) { return ((0x1 << (int)direction) & value) != 0; }
	void setCanGo(Direction direction, bool toValue) { if (toValue) value |= (0x1 << (int)direction); else value &= ~(0x1 << (int)direction); }
};

struct NodeAllocation
{
	NodeAllocation() : traveler(nullptr), acquireTime(0.0), releaseTime(0.0), traversalWeight(0.0), travelPathIndex(0), intermediateAllocationIndex(0) {}
	NodeAllocation(Traveler* traveler, const AStarCell& cell, int travelPathIndex, int intermediateAllocationIndex, double acquireTime, double releaseTime, double traversalWeight) :
		traveler(traveler), cell(cell), travelPathIndex(travelPathIndex), intermediateAllocationIndex(intermediateAllocationIndex), acquireTime(acquireTime), releaseTime(releaseTime), traversalWeight(traversalWeight)
	{}
	Traveler* traveler;
	AStarCell cell;
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
};

typedef std::list<NodeAllocation> NodeAllocationList;
typedef std::list<NodeAllocation>::iterator NodeAllocationIterator;

struct AStarNodeExtraData : public SimpleDataType
{

	AStarNodeExtraData() : cell(0, 0, 0), bonusRight(0), bonusLeft(0), bonusUp(0), bonusDown(0) {}
	virtual const char* getClassFactory() { return "AStar::NodeExtraData"; }
	virtual void bind() override;
	AStarCell cell;

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
	char getBonus(Direction direction) { return bonus[(int)direction]; }

	struct BridgeEntry {
		Bridge* bridge;
		bool isAtBridgeStart;
	};

	std::vector<BridgeEntry> bridges;
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
	NodeAllocation* addRequest(NodeAllocation& request, NodeAllocation& blockingAlloc, std::vector<Traveler*>* travelers = nullptr);

	void checkCreateContinueEvent();

	bool findDeadlockCycle(Traveler* start, std::vector<Traveler*>& travelers);

	class ContinueEvent : public FlexSimEvent
	{
	public:
		ContinueEvent() : FlexSimEvent() {}
		ContinueEvent(double time, Traveler* traveler, Traveler* blocker, AStarCell& cell);
		virtual const char* getClassFactory() override { return "AStar::AStarNodeExtraData::ContinueEvent"; }
		virtual void bind() override;
		AStarCell cell;
		virtual void execute() override;
	};
	ObjRef<ContinueEvent> continueEvent;
};


struct AStarPathEntry {
	AStarPathEntry() : cell(0, 0, 0), bridgeIndex(-1) {}
	AStarPathEntry(AStarCell cell, char bridgeIndex) : cell(cell), bridgeIndex(bridgeIndex) {}
	void bind(TreeNode* toNode);
	AStarCell cell;
	int bridgeIndex;
};

class TravelPath : public std::vector<AStarPathEntry>
{
public:
	double calculateTotalDistance(AStarNavigator* nav);
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
	AStarCell cell;
	unsigned int previous;
	float rotOnArrival;
	char prevBridgeIndex;
	bool closed;
};

struct CachedPathID {
	union {
		struct {
			unsigned short startCol;
			unsigned short startRow;
			unsigned short endCol;
			unsigned short endRow;
		};
		struct {
			unsigned int startID;
			unsigned int endID;
		};
		unsigned long long gridID;
	};
	treenode destination;
	bool operator == (const CachedPathID& other) const { return gridID == other.gridID && destination == other.destination; }
	struct Hash {
		size_t operator()(const CachedPathID& key) const
		{	// hash _Keyval to size_t value by pseudorandomizing transform
#ifdef _M_X64
			return (size_t)key.gridID ^ (size_t)key.destination;
#else
			return key.startID ^ key.endID ^ (size_t)key.destination;
#endif
		}
	};
};

struct AllocationStep {
	AllocationStep(const AStarCell& fromCell, const AStarCell& toCell) :
		fromCell(fromCell), toCell(toCell) {

		isDiagonal = toCell.row != fromCell.row && toCell.col != fromCell.col;
		if (isDiagonal) {
			isVerticalDeepSearch = abs(toCell.row - fromCell.row) == 2;
			isHorizontalDeepSearch = abs(toCell.col - fromCell.col) == 2;
			if (isVerticalDeepSearch) {
				intermediateCell1 = AStarCell(fromCell.grid, fromCell.col, (toCell.row + fromCell.row) / 2);
				intermediateCell2 = AStarCell(fromCell.grid, toCell.col, intermediateCell1.row);
			} else if (isHorizontalDeepSearch) {
				intermediateCell1 = AStarCell(fromCell.grid, (toCell.col + fromCell.col) / 2, fromCell.row);
				intermediateCell2 = AStarCell(fromCell.grid, intermediateCell1.col, toCell.row);
			} else {
				if (sign(toCell.col - fromCell.col) == sign(toCell.row - fromCell.row)) {
					// it's a "forward-slash diagonal"
					intermediateCell1 = AStarCell(fromCell.grid, min(toCell.col, fromCell.col), max(toCell.row, fromCell.row));
					intermediateCell2 = AStarCell(fromCell.grid, max(toCell.col, fromCell.col), min(toCell.row, fromCell.row));
				}
				else {
					// it's a "back-slash diagonal"
					intermediateCell1 = AStarCell(fromCell.grid, min(toCell.col, fromCell.col), min(toCell.row, fromCell.row));
					intermediateCell2 = AStarCell(fromCell.grid, max(toCell.col, fromCell.col), max(toCell.row, fromCell.row));
				}

			}
		} else isVerticalDeepSearch = isHorizontalDeepSearch = false;

	}
	bool isVerticalDeepSearch;
	bool isHorizontalDeepSearch;
	bool isDiagonal;
	AStarCell fromCell;
	AStarCell toCell;
	AStarCell intermediateCell1;
	AStarCell intermediateCell2;

	bool isImmediatelyBlocked(Traveler* traveler);
};

struct DestinationThreshold
{
	DestinationThreshold() : xAxisThreshold(0), yAxisThreshold(0), rotation(0), anyThresholdRadius(0) {}
	DestinationThreshold(treenode dest, double fudgeFactor);
	double xAxisThreshold;
	double yAxisThreshold;
	double rotation;
	double anyThresholdRadius;
	bool isWithinThreshold(const AStarCell& cell, const Vec2& gridOrigin, const Vec2& destLoc, double nodeWidth);
	void bind(SimpleDataType* sdt, const char* prefix);
};

}