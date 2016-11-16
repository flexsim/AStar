#pragma once
#include "FlexsimDefs.h"
#include "allobjects.h"
#include "hashtable.h"
#include "basicutils.h"
#include "Barrier.h"
#include <vector>
#include <unordered_map>
#include <queue>

struct AStarNode
{
	bool canGoRight:1;
	bool canGoLeft:1;
	bool canGoUp:1;
	bool canGoDown:1;
	bool noExtraData:1;
	bool notInTotalSet:1;
	bool open:1;
};

struct AStarNodeExtraData
{
	union {
		struct{
			unsigned short col;
			unsigned short row;
		};
		unsigned int colRow;
	};

	// straights
	unsigned int nrFromUp;
	unsigned int nrFromDown;
	unsigned int nrFromLeft;
	unsigned int nrFromRight;
	
	// diagonals
	unsigned int nrFromUpRight;
	unsigned int nrFromDownRight;
	unsigned int nrFromUpLeft;
	unsigned int nrFromDownLeft;

	char bonusUp;
	char bonusDown;
	char bonusRight;
	char bonusLeft;
};

#define DeRefEdgeTable(row, col) edgeTable[(row)*edgeTableXSize + col]

struct AStarSearchEntry{
	float f;
	float g;
	float h;
	union{
		struct{
			unsigned short col;
			unsigned short row;
		};
		unsigned int colRow;
	};
	unsigned int previous;
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

class AStarNavigator :
	public Navigator
{
protected:
	AStarNode* edgeTable;

	std::vector<AStarSearchEntry> totalSet; // The total set of all AStarSearchNodes
	std::unordered_map<unsigned int, unsigned int> entryHash; // A mapping from colRow to index in totalSet
	std::unordered_map<unsigned int, AStarNodeExtraData> edgeTableExtraData; // A mapping from colRow to an ExtraData object
	std::unordered_map<unsigned __int64, std::vector<unsigned int> > pathCache;

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
	int expandableUp;
	int expandableDown;
	int expandableRight;
	int expandableLeft;
	int travelFromPrevious;
	double col0x;
	double row0y;
	double destx;
	double desty;
	double maxPathWeight;
	int shortestIndex;
	float closestSoFar;
	int closestIndex;
	double endTime;
	TreeNode* kinematics;
	AStarSearchEntry barrierStart;
	double xStart;
	double yStart;

	// Current edgeTable status variables
	int edgeTableXSize;
	int edgeTableYSize;
	int xOffset;
	int yOffset;
	float savedXOffset;
	float savedYOffset;
	int maxTraveled;
	double penalty;

	// Drawing variables
	Mesh boundsMesh;	
	Mesh barrierMesh;
	Mesh trafficMesh;
	Mesh gridMesh;
	Mesh memberMesh;
	bool isDirty;

	inline AStarSearchEntry* expandOpenSet(int r, int c ,float multiplier, int travelVal);
	void searchBarrier(AStarSearchEntry* entry, TaskExecuter* traveler, int rowDest, int colDest, bool setStartEntry = false);
	void buildEdgeTable();
	void buildBoundsMesh();
	void buildBarrierMesh();
	void drawMembers(float z);
	void drawGrid(float z);
	void drawTraffic(float z, TreeNode* view);

public:
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

	double calculateNavigateToLoc(TreeNode* traveler, double* destLoc, double endSpeed, bool queryDist = false);

	virtual double updateLocations() override;
	virtual double abortTravel(TreeNode* traveler, TreeNode* newts) override;
	virtual unsigned int getClassType() override;

	virtual void bindVariables(void) override;

	void blockGridModelPos(const Vec3& modelPos);

	void setDirty();
};

