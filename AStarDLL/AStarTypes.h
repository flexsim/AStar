#pragma once
#include "AStarClasses.h"
#include <list>

namespace AStar {

enum Direction {
	Right = 0,
	Left = 1,
	Up = 2,
	Down = 3
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

struct NodeTraversal
{
	Traveler* traveler;
	double collisionStartTime;
	double collisionEndTime;
};

typedef std::list<NodeTraversal>::iterator NodeTraversalIterator;

struct AStarNodeExtraData
{
	AStarNodeExtraData() : colRow(0), bonusRight(0), bonusLeft(0), bonusUp(0), bonusDown(0) {}
	union {
		struct {
			unsigned short col;
			unsigned short row;
		};
		unsigned int colRow;
	};

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
	std::list<NodeTraversal> pendingTraversals;
};

#define DeRefEdgeTable(row, col) edgeTable[(row)*edgeTableXSize + col]

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
};

struct AStarPathEntry {
	AStarPathEntry() : cell(0, 0), bridgeIndex(-1) {}
	AStarPathEntry(AStarCell cell, char bridgeIndex) : cell(cell), bridgeIndex(bridgeIndex) {}
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