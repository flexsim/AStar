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

class AStarNavigator :
	public Navigator
{
public:
	double preferredPathWeight;
	double drawMode;
	double nodeWidth;
	
	TreeNode* savedEdgeTableExtraData;
	TreeNode* barriers;
	NodeListArray<Barrier>::SdtSubNodeBindingType barrierList;

	AStarNavigator();
	~AStarNavigator();
	
	virtual double OnReset();
	virtual double OnRunWarm();
	double OnTimerEvent(TreeNode* involved, int code, char *datastr);
	virtual double OnDraw(TreeNode* view);
	virtual double OnDrag(TreeNode* view);
	double AStarNavigator::OnDestroy(TreeNode* view);
	virtual double navigateTo(TreeNode* traveler, TreeNode* destination, double endspeed);
	virtual double navigateToLoc(TreeNode* traveler, double x, double y, double endspeed, int driveshort = 1);
	void buildEdgeTable();
	virtual double preDrawFunction();
	virtual double abortTravel(TreeNode* traveler, TreeNode* newts);
	virtual double saveState();
	virtual double loadState();

	virtual void bindVariables(void);
	
	AStarNode* edgeTable;

	// temporary variables that are used as part of the search
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
	double preferredPathWeightCache;
	int shortestIndex;

	inline void expandOpenSet(int r, int c ,float multiplier, int travelVal);
	int edgeTableXSize;
	int edgeTableYSize;
	int xOffset;
	int yOffset;
	int maxTraveled;

	static TreeNode* gASN;
	static AStarNavigator* globalAStarNavigator();

	std::vector<AStarSearchEntry> totalSet; // The total set of all AStarSearchNodes
	std::unordered_map<unsigned int, unsigned int> entryHash; // A mapping from rowCol to index in TotalSet
	std::unordered_map<unsigned int, AStarNodeExtraData> edgeTableExtraData; // A mapping from rowCol to a ExtraData object

	struct HeapEntry {
		HeapEntry(float f, unsigned int totalSetIndex) : f(f), totalSetIndex(totalSetIndex) {}
		float f;
		unsigned int totalSetIndex;
	};
	class HeapEntryCompare {
		bool operator()(HeapEntry& left, HeapEntry& right) {return left.f < right.f;}
	};

	// A heap of the open set; each value is tied to and index into the open set.
	std::priority_queue<HeapEntry, std::vector<HeapEntry>, HeapEntryCompare> openSetHeap;
};

