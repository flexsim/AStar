#pragma once
#include "FlexsimDefs.h"
#include "AStarClasses.h"
#include "basicutils.h"
#include "Barrier.h"
#include "AStarTypes.h"
#include "Grid.h"
#include <vector>
#include <unordered_map>
#include <queue>
#include <forward_list>

namespace AStar {

enum class EditMode : unsigned int {
	NONE = 0,
	PREFERRED_PATH = 35,
	DIVIDER = 36,
	ONE_WAY_DIVIDER = 37,
	SOLID_BARRIER = 38,
	BRIDGE = 39,
	GRID = 40
};

class AStarNavigator : public Navigator
{
	friend class Traveler;
protected:

	std::vector<AStarSearchEntry> totalSet; // The total set of all AStarSearchNodes
	std::unordered_map<unsigned int, unsigned int> entryHash; // A mapping from colRow to index in totalSet
	std::unordered_map<CachedPathID, TravelPath, CachedPathID::Hash > pathCache;

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
	Vec3 destLoc;
	double maxPathWeight;
	int shortestIndex;
	float closestSoFar;
	int closestIndex;
	TreeNode* kinematics;
	Vec3 startLoc;
	double smoothRotations;

	//int xOffset;
	//int yOffset;
	//float savedXOffset;
	//float savedYOffset;
	double directionChangePenalty;

	// Drawing variables
	Mesh barrierMesh;
	Mesh memberMesh;
	bool isGridDirty = false;
	bool isBoundsDirty = true;
	bool isBarrierDirty = true;
	bool isBoundsMeshBuilt = false;
	bool isBarrierMeshBuilt = false;
	bool isGridMeshBuilt = false;
	bool isActiveBarrierBuilt = false;
	bool isHoveredBarrierBuilt = false;

	inline AStarSearchEntry* expandOpenSet(Grid* grid, int r, int c, float multiplier, float rotOnArrival, char bridgeIndex = -1);

	void buildBoundsMesh(float z);
	void buildBarrierMesh(float z);
	void drawMembers(float z);
	void buildGridMesh(float zOffset);

public:
	void checkGetOutOfBarrier(AStarCell& cell, TaskExecuter* traveler, int rowDest, int colDest, DestinationThreshold* threshold)
	{
		getGrid(cell)->checkGetOutOfBarrier(cell, traveler, rowDest, colDest, threshold);
	}
	static const int HEAT_MAP_TRAVERSALS_PER_TIME = 1;
	static const int HEAT_MAP_BLOCKAGE_TIME_PER_TRAVERSAL = 2;
	static const int HEAT_MAP_BLOCKAGE_TIME_PERCENT = 3;
	static const int HEAT_MAP_PERCENT_OF_TOTAL_TRAVERSALS = 4;
	static std::vector<Vec4f> heatMapColorProgression;
	double showHeatMap;
	double heatMapMode;
	double transparentBaseColor;
	double heatMapTotalTraversals;
	struct HeatMapColorEntry {
		Vec4f color = Vec4f(0.0f, 0.0f, 0.0f, 0.0f);
		AStarNodeExtraData* node = nullptr;
		int vertIndex;
	};
	void drawHeatMap(TreeNode* view);

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Checks and expands the passed min/max bounds based on the object's size and location. </summary>
	///
	/// <remarks>	</remarks>
	///
	/// <param name="theObj">	[in,out] The object. </param>
	/// <param name="min">   	[in,out] The minimum. </param>
	/// <param name="max">   	[in,out] The maximum. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void getBoundingBox(TreeNode* theObj, Vec3& min, Vec3& max);

	// Current edgeTable status variables
	TreeNode* extraDataNode;
	std::unordered_map<unsigned long long, AStarNodeExtraData*> edgeTableExtraData; // A mapping from colRow to an ExtraData object


	static EditMode editMode;
	static AStarNavigator* globalASN;
	double defaultPathWeight;
	double minNodeWidth;
	double surroundDepth;

	/// <summary>Route by travel time. Boolean. If 1, the routing algorithm will use estimated travel time, including 
	/// 		 time blocked for collision avoidance, as the cost function in the A* algorithm.</summary>
	double routeByTravelTime;

	static float clampDirection(float rotDirection);
	/// <summary>Stop for turns. Boolean.</summary>
	double stopForTurns;
	/// <summary>The turn speed. Only used when stopping for turns.</summary>
	treenode turnSpeed;
	/// <summary>The turn delay. And additional delay associated with stopping and turning. This is meant 
	/// 		 to allow the user to define an additional delay because deceleration is not simulated.</summary>
	treenode turnDelay;
	/// <summary>The estimated indefinite allocate time delay. Only needed when routing based on travel time. 
	/// 		 This is an additional penalty for a route that hits an allocation that is indefinite.</summary>
	//treenode indefiniteAllocTimePenalty;
	/// <summary>The deadlock penalty.</summary>
	//treenode deadlockPenalty;

	/// <summary>The routing travel start time. Used in the routing algorithm when routing based on travel time, to 
	/// 		 estimate when collisions will happen.</summary>
	double routingTravelStartTime;

	/// <summary>The dealloc time add factor. This creates an additional amount of time that a node will be allocated. The
	/// 		 value is expressed as a percentage (0 - 1.0) of a node width. The algorithm will calculate the time 
	/// 		 it takes the te to travel this distance, and add the time to the deallocation time.</summary>
	double deallocTimeOffset;

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
	/// <summary>	The barrier that is currently being edited by the user. </summary>
	NodeRef activeBarrier;
	/// <summary>	The grid that is currently being edited by the user. </summary>
	NodeRef activeGrid;
	/// <summary>	Defines a set of custom barriers that are filled by objects that are barrier members of the astar navigator.
	/// 			Each element of this array may be one of the following:
	/// 			1. If the element is a single non-array, it is a single reference to an object.  
	/// 			2. If the element is an array with 3 elements, then it is a single location, added via blockGridModelPos()  
	/// 			   that should be blocked  
	/// 			3. If the element is an array of 7 elements, then it represents two points, a min and max bounding box,  
	/// 			   that should be blocked in the grid.</summary>
	Array customBarriers;

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
	void addCreateRecord(treenode view, SimpleDataType* barrier, const char* name);
	virtual double dragConnection(TreeNode* connectTo, char keyPressed, unsigned int classType) override;
	virtual double onDestroy(TreeNode* view) override;
	virtual double navigateToObject(TreeNode* traveler, TreeNode* destination, double endspeed) override;
	double navigateToLoc(Traveler* traveler, double* destLoc, double endSpeed);
	virtual double navigateToLoc(treenode traveler, double* destLoc, double endSpeed) override;
	virtual void onMemberDestroyed(TaskExecuter* te) override;
	virtual double queryDistance(TaskExecuter* taskexecuter, FlexSimObject* destination);

	AStarSearchEntry* checkExpandOpenSet(Grid* grid, AStarNode* node, AStarSearchEntry* entryIn, Direction direction, float rotDirection, double dist, double bonusMod, AStarNodeExtraData* extraData);
	AStarSearchEntry* checkExpandOpenSetDiagonal(Grid* grid, AStarNode* node, AStarSearchEntry* entryIn,
		Direction dir1, Direction dir2, float rotDirection, double dist, AStarNodeExtraData* extraData);

	/// <summary>Calculates the route.</summary>
	///
	/// <remarks>Anthony Johnson, 2/12/2018.</remarks>
	///
	/// <param name="traveler">		  [in,out] If non-null, the traveler.</param>
	/// <param name="destLoc">		  [in,out] If non-null, destination location.</param>
	/// <param name="endSpeed">		  The end speed.</param>
	/// <param name="doFullSearch">   (Optional) True to do full search (no cached paths).</param>
	/// <param name="travelStartTime">(Optional) The travel start time.</param>
	///
	/// <returns>The calculated route.</returns>
	TravelPath calculateRoute(Traveler* traveler, double* destLoc, const DestinationThreshold& destThreshold, double endSpeed, bool doFullSearch = false, double travelStartTime = -1);

	virtual double updateLocations() override;
	virtual double updateLocations(TaskExecuter* te) override;
	virtual double abortTravel(TreeNode* traveler, TreeNode* newts) override;
	virtual unsigned int getClassType() override;

	virtual void bindVariables(void) override;
	virtual void bindEvents() override;
	virtual void bindTEEvents(TaskExecuter* te) override;
	virtual void bindTEStatistics(TaskExecuter* te) override;
	TreeNode* AStarNavigator::resolveTraveler();

	void blockGridModelPos(const Vec3& modelPos);
	void divideGridModelLine(const Vec3& modelPos1, const Vec3& modelPos2, bool oneWay = false);
	void addObjectBarrierToTable(TreeNode* obj);

	void setDirty();
	void resetGrids();

	AStarCell getCellFromLoc(const Vec2& modelLoc) { return getCellFromLoc(Vec3(modelLoc.x, modelLoc.y, 0.0)); }
	AStarCell getCellFromLoc(const Vec3& modelLoc);
	Vec3 getLocFromCell(const AStarCell& cell);

	AStarNode* getNode(const AStarCell& cell);
	Grid* getGrid(const AStarCell& cell);
	Grid* getGrid(const Vec3& modelPos);

	AStarNodeExtraData* assertExtraData(const AStarCell& cell);
	AStarNodeExtraData* getExtraData(const AStarCell& cell) {
		auto extraIter = edgeTableExtraData.find(cell.colRow);
		return extraIter != edgeTableExtraData.end() ? extraIter->second : nullptr;
	}
	static AStarCell getPrevCell(AStarCell& toCell, float rotDirection);


	NodeListArray<Traveler>::CouplingSdtSubNodeType travelers;
	std::list<Traveler*> activeTravelers;
	void buildActiveTravelerList();

	Traveler* getTraveler(TaskExecuter* te) { return tonode(get(first(te->node_v_navigator)))->objectAs(Traveler); }

	void dumpBlockageData(treenode destNode);

	double debugRoutingAlgorithm;
	double routingAlgorithmCompletionRatio;
	void drawRoutingAlgorithm(Traveler* traveler, treenode view);

	bool areGridNodeTablesBuilt = false;
	NodeListArray<Grid>::SdtSubNodeType grids;

	void resolveMinNodeWidth();

	double hasCustomUserGrids;
	TreeNode* addObject(const Vec3& pos1, const Vec3& pos2, EditMode mode);
};

}