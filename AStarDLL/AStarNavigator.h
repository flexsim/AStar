#pragma once
#include "FlexsimDefs.h"
#include "AStarClasses.h"
#include "basicutils.h"
#include "Barrier.h"
#include "AStarTypes.h"
#include <vector>
#include <unordered_map>
#include <queue>
#include <forward_list>

namespace AStar {

class AStarNavigator : public Navigator
{
	friend class Traveler;
protected:
	AStarNode* edgeTable;

	std::vector<AStarSearchEntry> totalSet; // The total set of all AStarSearchNodes
	std::unordered_map<unsigned int, unsigned int> entryHash; // A mapping from colRow to index in totalSet
	std::unordered_map<CachedPathID, std::vector<AStarPathEntry>, CachedPathID::Hash > pathCache;

	struct HeapEntry {
		HeapEntry(float f, unsigned int totalSetIndex) : f(f), totalSetIndex(totalSetIndex) {}
		float f;
		unsigned int totalSetIndex;
	};
	class HeapEntryCompare {
	public:
		bool operator()(HeapEntry& left, HeapEntry& right) { return left.f > right.f; }
	};

	// A heap of the open set; each value is tied to an index into the open set.
	std::priority_queue<HeapEntry, std::vector<HeapEntry>, HeapEntryCompare> openSetHeap;

	// Temporary variables that are used as part of the search
	AStarNode * n;
	AStarSearchEntry shortest;
	Traveler* routingTraveler = nullptr;
	int travelFromPrevious;
	Vec2 destLoc;
	double maxPathWeight;
	int shortestIndex;
	float closestSoFar;
	int closestIndex;
	TreeNode* kinematics;
	AStarSearchEntry barrierStart;
	double xStart;
	double yStart;
	double smoothRotations;

	int xOffset;
	int yOffset;
	float savedXOffset;
	float savedYOffset;
	double savedNodeWidth;
	double directionChangePenalty;

	// Drawing variables
	Mesh boundsMesh;
	Mesh barrierMesh;
	Mesh gridMesh;
	Mesh memberMesh;
	bool isGridDirty = false;
	bool isBoundsDirty = true;
	bool isBarrierDirty = true;
	bool isBoundsMeshBuilt = false;
	bool isBarrierMeshBuilt = false;
	bool isGridMeshBuilt = false;
	bool isActiveBarrierBuilt = false;
	bool isHoveredBarrierBuilt = false;

	inline AStarSearchEntry* expandOpenSet(int r, int c, float multiplier, int travelVal, char bridgeIndex = -1);
	void checkGetOutOfBarrier(AStarCell& cell, TaskExecuter* traveler, int rowDest, int colDest, DestinationThreshold* threshold, bool setStartEntry);
	void checkBounds(TreeNode* theObj, Vec2& min, Vec2& max);
	void buildBoundsMesh(float z);
	void buildBarrierMesh(float z);
	void drawMembers(float z);
	void buildGridMesh(float z);

	static const int HEAT_MAP_TRAVERSALS_PER_TIME = 1;
	static const int HEAT_MAP_BLOCKAGE_TIME_PER_TRAVERSAL = 2;
	static const int HEAT_MAP_BLOCKAGE_TIME_PERCENT = 3;
	static std::vector<Vec4f> heatMapColorProgression;
	double showHeatMap;
	double heatMapMode;
	double maxHeatValue;
	double transparentBaseColor;
	struct HeatMapColorEntry {
		Vec4f color = Vec4f(0.0f, 0.0f, 0.0f, 0.0f);
		AStarNodeExtraData* node = nullptr;
		int vertIndex;
	};
	void drawHeatMap(float z, TreeNode* view);

public:
	Vec2 gridOrigin;
	// Current edgeTable status variables
	int edgeTableXSize;
	int edgeTableYSize;
	TreeNode* extraDataNode;
	std::unordered_map<unsigned int, AStarNodeExtraData*> edgeTableExtraData; // A mapping from colRow to an ExtraData object

	static unsigned int editMode;
	static AStarNavigator* globalASN;
	double defaultPathWeight;
	double nodeWidth;
	double surroundDepth;

	double routeByTravelTime;
	double activeReroute;

	static double getRotationFromTravelDirection(int travelDir);
	double stopForTurns;
	treenode turnSpeed;
	treenode turnDelay;
	treenode estimatedIndefiniteAllocTimeDelay;
	double routingTravelStartTime;
	/// <summary>The dealloc time add factor. This creates an additional amount of time that a node will be allocated. The
	/// 		 value is expressed as a percentage (0 - 1.0) of a node width. The algorithm will calculate the time 
	/// 		 it takes the te to travel this distance, and add the time to the deallocation time.</summary>
	double deallocTimeAddFactor;

	static const int SEARCH_DIAGONALS = 0;
	static const int SEARCH_DEEP_DIAGONALS = 1;
	static const int SEARCH_RIGHT_ANGLES_ONLY = 2;
	double deepSearch;
	double drawMode;
	double showAllocations;
	double showTravelThreshold;
	void drawAllocations(float z);
	void drawDestinationThreshold(TreeNode* destination, float z);

	double ignoreDestBarrier;

	double cachePaths;
	double pathCount;
	double requestCount;
	double cacheUseCount;

	double enableCollisionAvoidance;
	double ignoreInactiveMemberCollisions;

	double snapBetweenGrid;

	double collisionUpdateIntervalFactor;
	double collisionUpdateInterval;
	double nextCollisionUpdateTime; 
	void onCollisionIntervalUpdate();
	class CollisionIntervalUpdateEvent : public FlexSimEvent {
	public:
		virtual const char* getClassFactory() override { return "AStar::AStarNavigator::CollisionIntervalUpdateEvent"; }
		CollisionIntervalUpdateEvent() : FlexSimEvent() {}
		CollisionIntervalUpdateEvent(AStarNavigator* nav, double time) : FlexSimEvent(nav->holder, time, nullptr, 0) {}
		virtual void execute() override { partner()->objectAs(AStarNavigator)->onCollisionIntervalUpdate(); }
	};

	TreeNode* barriers;
	NodeListArray<Barrier>::SdtSubNodeBindingType barrierList;
	NodeRef activeBarrier;

	TreeNode* fixedResourceBarriers;
	NodeListArray<ObjectDataType>::ObjStoredAttCouplingType objectBarrierList;

	AStarNavigator();
	~AStarNavigator();

	virtual double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO) override;
	virtual double onReset() override;
	virtual double onStartSimulation() override;
	virtual double onRunWarm() override;
	virtual double onDraw(TreeNode* view) override;
	virtual double onDrag(TreeNode* view) override;
	virtual double onClick(TreeNode* view, int clickcode) override;
	virtual double onUndo(bool isUndo, treenode undoRecord) override;
	void addCreateRecord(treenode view, Barrier* barrier);
	virtual double dragConnection(TreeNode* connectTo, char keyPressed, unsigned int classType) override;
	virtual double onDestroy(TreeNode* view) override;
	virtual double navigateToObject(TreeNode* traveler, TreeNode* destination, double endspeed) override;
	double navigateToLoc(Traveler* traveler, double* destLoc, double endSpeed);
	virtual double navigateToLoc(treenode traveler, double* destLoc, double endSpeed) override;
	virtual void onMemberDestroyed(TaskExecuter* te) override;
	virtual double queryDistance(TaskExecuter* taskexecuter, FlexSimObject* destination);

	AStarSearchEntry* checkExpandOpenSet(AStarNode* node, AStarSearchEntry* entryIn, Direction direction, int travelVal, double dist, double bonusMod, AStarNodeExtraData* extraData);
	AStarSearchEntry* checkExpandOpenSetDiagonal(AStarNode* node, AStarSearchEntry* entryIn,
		Direction dir1, Direction dir2, int travelVal, double dist, AStarNodeExtraData* extraData);

	TravelPath calculateRoute(Traveler* traveler, double* destLoc, double endSpeed, bool doFullSearch = false, double travelStartTime = -1);

	virtual double updateLocations() override;
	virtual double updateLocations(TaskExecuter* te) override;
	virtual double abortTravel(TreeNode* traveler, TreeNode* newts) override;
	virtual unsigned int getClassType() override;

	virtual void bindVariables(void) override;
	virtual void bindTEEvents(TaskExecuter* te) override;
	virtual void bindTEStatistics(TaskExecuter* te) override;
	TreeNode* AStarNavigator::resolveTraveler();

	void blockGridModelPos(const Vec3& modelPos);
	void addObjectBarrierToTable(TreeNode* obj);

	void setDirty();
	void buildEdgeTable();

	AStarCell getCellFromLoc(const Vec2& modelLoc);
	Vec3 getLocFromCell(const AStarCell& cell) { return Vec3(gridOrigin.x + cell.col * nodeWidth, gridOrigin.y + cell.row * nodeWidth, 0.0);	}
	AStarNode* getNode(const AStarCell& cell) { return &DeRefEdgeTable(cell.row, cell.col); }
	AStarNode* getNode(int row, int col) { return &DeRefEdgeTable(row, col); }
	AStarNodeExtraData* assertExtraData(const AStarCell& cell);
	AStarNodeExtraData* getExtraData(const AStarCell& cell) {
		auto extraIter = edgeTableExtraData.find(cell.colRow);
		return extraIter != edgeTableExtraData.end() ? extraIter->second : nullptr;
	}


	NodeListArray<Traveler>::CouplingSdtSubNodeType travelers;
	std::list<Traveler*> activeTravelers;
	void buildActiveTravelerList();

	Traveler* getTraveler(TaskExecuter* te) { return tonode(get(first(te->node_v_navigator)))->objectAs(Traveler); }

	std::unique_ptr<unsigned int[]> heatMapBuffer;
	void dumpBlockageData(treenode destNode);
};

}