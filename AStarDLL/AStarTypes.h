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
			unsigned short col;
			unsigned short row;
		};
		unsigned int colRow;
	};
	AStarCell() {}
	AStarCell(unsigned short col, unsigned short row) : col(col), row(row) {}
	AStarCell(unsigned int colRow) : colRow(colRow) {}
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
	bool __extraData() { return !noExtraData; }
	bool __inTotalSet() { return !notInTotalSet; }
	void __setInTotalSet(bool toVal) { notInTotalSet = !toVal; }
	__declspec(property(get = __extraData)) bool hasExtraData;
	__declspec(property(get = __inTotalSet, put = __setInTotalSet)) bool isInTotalSet;
	static int rowInc[];
	static int colInc[];
	bool canGo(Direction direction) { return ((0x1 << (int)direction) & value) != 0; }
};

struct NodeAllocation
{
	NodeAllocation() : traveler(nullptr), acquireTime(0.0), releaseTime(0.0) {}
	NodeAllocation(Traveler* traveler, const AStarCell& cell, int travelPathIndex, double acquireTime, double releaseTime) :
		traveler(traveler), cell(cell), travelPathIndex(travelPathIndex), acquireTime(acquireTime), releaseTime(releaseTime)
	{}
	Traveler* traveler;
	AStarCell cell;
	int travelPathIndex;
	double acquireTime;
	double releaseTime;
	void extendReleaseTime(double toTime);
	void bind(TreeNode* x);
};

typedef std::list<NodeAllocation> NodeAllocationList;
typedef std::list<NodeAllocation>::iterator NodeAllocationIterator;

struct AStarNodeExtraData : public SimpleDataType
{

	AStarNodeExtraData() : cell(0, 0), bonusRight(0), bonusLeft(0), bonusUp(0), bonusDown(0) {}
	virtual const char* getClassFactory() { return "AStar::NodeExtraData"; }
	virtual void bind() override;
	AStarCell cell;

	// Traffic tracking stats:
	// straights
	unsigned int nrFromUp = 0;
	unsigned int nrFromDown = 0;
	unsigned int nrFromLeft = 0;
	unsigned int nrFromRight = 0;

	// diagonals
	unsigned int nrFromUpRight = 0;
	unsigned int nrFromDownRight = 0;
	unsigned int nrFromUpLeft = 0;
	unsigned int nrFromDownLeft = 0;

	unsigned int numCollisions = 0;

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
	void onRelease();

	/// <summary>	Adds a request to 'blockingAlloc'. </summary>
	/// <remarks>	Anthony.johnson, 4/17/2017. </remarks>
	/// <param name="request">			[in,out] The request. </param>
	/// <param name="blockingAlloc">	[in,out] The blocking allocate. </param>
	/// <returns>	A NodeAllocationIterator. If the function was successful, this will be a valid 
	/// 			iterator into requests. If the algorithm finds a cycle in the allocations, this 
	/// 			will fail and return null.</returns>
	NodeAllocation* addRequest(NodeAllocation& request, NodeAllocation& blockingAlloc, std::vector<Traveler*>* travelers = nullptr);

	void checkCreateReleaseEvent();

	bool findDeadlockCycle(Traveler* start, std::vector<Traveler*>& travelers);

	class ReleaseEvent : public FlexSimEvent
	{
	public:
		ReleaseEvent() : FlexSimEvent() {}
		ReleaseEvent(double time, Traveler* traveler, AStarCell& cell);
		virtual const char* getClassFactory() override { return "AStar::AStarNodeExtraData::ReleaseEvent"; }
		virtual void bind() override;
		AStarCell cell;
		virtual void execute() override;
	};
	ObjRef<ReleaseEvent> releaseEvent;
};

#define DeRefEdgeTable(row, col) edgeTable[(row)*edgeTableXSize + col]


struct AStarPathEntry {
	AStarPathEntry() : cell(0, 0), bridgeIndex(-1) {}
	AStarPathEntry(AStarCell cell, char bridgeIndex) : cell(cell), bridgeIndex(bridgeIndex) {}
	void bind(TreeNode* toNode);
	AStarCell cell;
	char bridgeIndex;
};

typedef std::vector<AStarPathEntry> TravelPath;

struct AStarSearchEntry {
	float f;
	float g;
	float h;
	AStarCell cell;
	unsigned int previous;
	int travelFromPrevious;
	char prevBridgeIndex;
	bool closed;
};

struct AStarPathID {
	union {
		struct {
			unsigned short startCol;
			unsigned short startRow;
			unsigned short endCol;
			unsigned short endRow;
		};
		unsigned __int64 id;
	};
};

}