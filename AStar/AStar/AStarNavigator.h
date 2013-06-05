#pragma once
#include "FlexsimDefs.h"
#include "allobjects.h"
#include "hashtable.h"
#include <vector>
#include <hash_map>

struct AStarNode
{
	bool right:1;
	bool left:1;
	bool up:1;
	bool down:1;
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
	TreeNode* openSetHeap;

	AStarNavigator();
	~AStarNavigator();
	
	virtual double OnReset();
	virtual double OnRunWarm();
	double OnTimerEvent(TreeNode* involved, int code, char *datastr);
	virtual double OnDraw(TreeNode* view);
	virtual double OnDrag(TreeNode* view);
	double AStarNavigator::OnDestroy(TreeNode* view);
	virtual double navigateto(TreeNode* traveler, TreeNode* destination, double endspeed);
	virtual double navigatetoloc(TreeNode* traveler, double x, double y, double endspeed, int driveshort = 1);
	void buildEdgeTable();
	virtual double predrawfunction();
	virtual double aborttravel(TreeNode* traveler, TreeNode* newts);

	virtual void bindVariables(void);
	
	AStarNode* edgeTable;

	// temporary variables that are used as part of the search
	//AStarNode * n;
	AStarSearchEntry shortest;
	int expandableUp;
	int expandableDown;
	int expandableRight;
	int expandableLeft;
	std::vector<AStarSearchEntry> totalSet;
	int travelFromPrevious;
	double col0x;
	double row0y;
	double destx;
	double desty;
	double preferredPathWeightCache;
	int shortestIndex;

	

	inline void expandOpenSet(int r, int c ,float multiplier, int travelVal);
	int edgeTableXSize;
	int edgetTableYSize;
	int xOffset;
	int yOffset;
	int maxTraveled;

	
	//hash_map<int> entryhash;
	//chashtableintkeysize<AStarNodeExtraData> edgetableextradata;

	virtual double savestate();
	virtual double loadstate();

	static TreeNode* gASN;
	static AStarNavigator* globalAStarNavigator();
};

