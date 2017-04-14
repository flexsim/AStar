#pragma once
#include "FlexsimDefs.h"
#include "AStarClasses.h"
#include "basicutils.h"
#include "Barrier.h"
#include <vector>
#include <unordered_map>
#include <queue>

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

class AStarNavigator : public Navigator
{
protected:
	AStarNode* edgeTable;

	std::vector<AStarSearchEntry> totalSet; // The total set of all AStarSearchNodes
	std::unordered_map<unsigned int, unsigned int> entryHash; // A mapping from colRow to index in totalSet
	std::unordered_map<unsigned __int64, std::vector<AStarPathEntry> > pathCache;

	struct HeapEntry {
		HeapEntry(float f, unsigned int totalSetIndex) : f(f), totalSetIndex(totalSetIndex) {}
		float f;
		unsigned int totalSetIndex;
	};
	class HeapEntryCompare {
	public:
		bool operator()(HeapEntry& left, HeapEntry& right) {return left.f > right.f;}
	};

	// A heap of the open set; each value is tied to an index into the open set.
	std::priority_queue<HeapEntry, std::vector<HeapEntry>, HeapEntryCompare> openSetHeap;

	// Temporary variables that are used as part of the search
	AStarNode * n;
	AStarSearchEntry shortest;
	int travelFromPrevious;
	Vec2 destLoc;
	double maxPathWeight;
	int shortestIndex;
	float closestSoFar;
	int closestIndex;
	double endTime;
	TreeNode* kinematics;
	AStarSearchEntry barrierStart;
	double xStart;
	double yStart;

	int xOffset;
	int yOffset;
	float savedXOffset;
	float savedYOffset;
	int maxTraveled;
	double directionChangePenalty;

	// Drawing variables
	Mesh boundsMesh;	
	Mesh barrierMesh;
	Mesh trafficMesh;
	Mesh gridMesh;
	Mesh memberMesh;
	bool isDirty;

	inline AStarSearchEntry* expandOpenSet(int r, int c ,float multiplier, int travelVal, char bridgeIndex = -1);
	void searchBarrier(AStarSearchEntry* entry, TaskExecuter* traveler, int rowDest, int colDest, bool setStartEntry = false);
	void buildEdgeTable();
	void buildBoundsMesh();
	void buildBarrierMesh();
	void drawMembers(float z);
	void drawGrid(float z);
	void drawTraffic(float z, TreeNode* view);

public:
	Vec2 gridOrigin;
	// Current edgeTable status variables
	int edgeTableXSize;
	int edgeTableYSize;
	std::unordered_map<unsigned int, AStarNodeExtraData> edgeTableExtraData; // A mapping from colRow to an ExtraData object

	static unsigned int editMode;
	static AStarNavigator* globalASN;
	double defaultPathWeight;
	double nodeWidth;
	double surroundDepth;
	double deepSearch;
	double drawMode;
	double ignoreDestBarrier;

	double cachePaths;
	double pathCount;
	double requestCount;
	double cacheUseCount;

	double hasEdgeTable;
	
	TreeNode* barriers;
	NodeListArray<Barrier>::SdtSubNodeBindingType barrierList;
	NodeRef activeBarrier;
	
	TreeNode* fixedResourceBarriers;
	NodeListArray<ObjectDataType>::ObjStoredAttCouplingType objectBarrierList;

	AStarNavigator();
	~AStarNavigator();
	
	virtual double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO) override;
	virtual double onReset() override;
	virtual double onRunWarm() override;
	virtual double onTimerEvent(TreeNode* involved, int code, char *datastr) override;
	virtual double onDraw(TreeNode* view) override;
	virtual double onDrag(TreeNode* view) override;
	virtual double onClick(TreeNode* view, int clickcode) override;
	virtual double onUndo(bool isUndo, treenode undoRecord) override;
	void addCreateRecord(treenode view, Barrier* barrier);
	virtual double dragConnection(TreeNode* connectTo, char keyPressed, unsigned int classType) override;
	virtual double onDestroy(TreeNode* view) override;
	virtual double navigateToObject(TreeNode* traveler, TreeNode* destination, double endspeed) override;
	virtual double navigateToLoc(treenode traveler, double* destLoc, double endSpeed) override;
	virtual double queryDistance(TaskExecuter* taskexecuter, FlexSimObject* destination);

	AStarSearchEntry* checkExpandOpenSet(AStarNode* node, AStarSearchEntry* entryIn, Direction direction, int travelVal, double dist, double bonusMod, AStarNodeExtraData* extraData);
	AStarSearchEntry* checkExpandOpenSetDiagonal(AStarNode* node, AStarSearchEntry* entryIn,
		Direction dir1, Direction dir2, int travelVal, double dist, AStarNodeExtraData* extraData);

	double calculateRoute(TreeNode* traveler, double* destLoc, double endSpeed, bool queryDist = false);

	virtual double updateLocations() override;
	virtual double abortTravel(TreeNode* traveler, TreeNode* newts) override;
	virtual unsigned int getClassType() override;

	virtual void bindVariables(void) override;

	void blockGridModelPos(const Vec3& modelPos);

	void setDirty();

	AStarCell getCellFromLoc(const Vec2& modelLoc);
	AStarNode* getNode(const AStarCell& cell) { return &DeRefEdgeTable(cell.row, cell.col); }
	AStarNode* getNode(int row, int col) { return &DeRefEdgeTable(row, col); }
	AStarNodeExtraData* assertExtraData(const AStarCell& cell);
};

