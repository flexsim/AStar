#pragma once
#include "AStarClasses.h"
#include "FlexsimDefs.h"
#include <list>
#include <deque>
#include "AStarTypes.h"
#include "Bridge.h"
#include "ElevatorBridge.h"

namespace AStar {



class Traveler : public CouplingDataType
{
public:
	virtual const char* getClassFactory() override { return "AStar::Traveler"; }
	virtual void bind() override;
	virtual void bindEvents() override;
	virtual void bindInterface() override;

	virtual TreeNode* getEventInfoObject(const char* eventTitle) override;

	Traveler(AStarNavigator* nav, TaskExecuter* te) : navigator(nav), te(te) {}
	Traveler() : navigator(nullptr), te(nullptr) {}


	TreeNode* resolveBridgeData();
	Vec3 destLoc;
	double endSpeed;
	double turnSpeed;
	double turnDelay;
	//double estimatedIndefiniteAllocTimeDelay;
	DestinationThreshold destThreshold;
	treenode destNode;
	enum ActiveState {
		Inactive = 0,
		Active = 1,
		DecelToStop = 2, // finished task, but still decelerating
	};
	ActiveState activeState;
	int __getIsActive() { return (int)activeState == Active; }
	std::list<ObjRef<Traveler>>::iterator activeEntry;
	astar_export TravelPath& __getTravelPath();
#ifdef COMPILING_ASTAR
	TravelPath travelPath;
#else
	__declspec(property(get = __getTravelPath)) TravelPath& travelPath;
	TravelPath privateTravelPath;
#endif
	//double nodeWidth;
	typedef std::deque<NodeAllocationIterator> TravelerAllocations;
	TravelerAllocations allocations;
	AllocationRange getAllocations(double atTime);
	NodeAllocation* request = nullptr;
	

	AStarNavigator* navigator;
	TaskExecuter* te;
	TaskExecuter* __getObject() { return te; }
	enum class BlockMode : int {
		None,
		Node,
		ControlArea
	};
	BlockMode blockMode = BlockMode::None;
	int __getIsBlocked() { return (int)(blockMode != BlockMode::None); }
	bool needsContinueTrigger = false;
	/// <summary>Zero-based index of the travel path element that could not be allocated 
	/// 		 (the next node after where the traveler is when he gets blocked).</summary>
	int blockedAtTravelPathIndex = -1;
	astar_export void onReset();
	astar_export void onStartSimulation();


	/// <summary>A result that can be returned by the user as part of the onNavigatePath trigger. 
	/// This allows the user to manually manage kinematics and allocations.</summary>
	enum UserNavigationResult : int {
		Default = 0x0, // default functionality, means A* logic controls 
		UserNavigated = 0x1, // for telling the navigator that the user has performed the navigation/allocation
		Blocked = 0x2, // for when the traveler is immediately blocked, so user wants navigatePath() to keep its current allocations and skip bridge OnExit
		KeepAllocations = 0x4, // for when the traveler does not want navigatePath() to remove any initial allocations
		AbortAll = 0x8, // for when the user wants no more logic to fire, e.g. if the user has recalculated the route and called navigatePath() again.
	};
	void navigatePath(int startAtPathIndex);
	void navigatePath_flexScript(int startAtPathIndexOneBased) { navigatePath(startAtPathIndexOneBased - 1); }
	void navigatePath(TravelPath&& path);

	void calculatePath(const Vec3& destLoc, int flags = 0);
	void calculatePath(ObjectDataType* dest, int flags = 0);
	astar_export void onBridgeArrival(int pathIndex);
	astar_export void onBridgeArrival(BridgeRoutingData* bridge, int pathIndex);
	astar_export void onBridgeComplete(int atPathIndex);
	void arriveAtBridge(int pathIndexOneBased) { onBridgeArrival(pathIndexOneBased - 1); }

	/// <summary>
	/// Updates locations to the defined travel distance, and housekeeps travel path 
	/// and allocation
	/// </summary>
	/// <param name="atTravelDist">This is the destination travel distance. This will be updated to 
	/// 0 during execution</param>
	void finalizeAtLocation(double& atTravelDist);
	void onArrival(bool isZeroSpeed);
	void finishPath() { onArrival(true); }

	/// <summary>	Adds an allocation to the map's set of allocations. </summary>
	/// <remarks>	Anthony.johnson, 4/17/2017. </remarks>
	/// <param name="allocation">	The allocation. </param>
	/// <param name="force">	 	(Optional) force. </param>
	/// <returns>	If it succeeds it will return the added allocation. If it fails 
	/// 			(it can't add the allocation because that would cause allocation overlaps)
	/// 			it will return nullptr and create a collision event. </returns>
	NodeAllocation* addAllocation(NodeAllocation& allocation, bool force, bool notifyPendingAllocations);
	NodeAllocation* addAllocation(NodeAllocation&& allocation, bool force, bool notifyPendingAllocations);
	NodeAllocation addAllocation_flexScript(NodeAllocation& allocation, int force, int notifyPendingAllocations);
	void checkCreateCollisionEvent(NodeAllocation& allocation, AStarNodeExtraData* nodeData = nullptr);

	static const int VISIT_CONTINUE = 0x0;
	static const int VISIT_ABORT = 0x1;
	static const int VISIT_NO_INC_ITER = 0x2;
	template<class Callback>
	static NodeAllocation* visitCollisions(AStarNodeExtraData* nodeData, const NodeAllocation& myAllocation, bool ignoreSameTravelerAllocs, Callback predicate)
	{
		NodeAllocationIterator bestIter = nodeData->allocations.end();
		double minAcquireTime = DBL_MAX;
		double curTime = time();

		for (auto iter = nodeData->allocations.begin(); iter != nodeData->allocations.end();) {
			NodeAllocation& other = *iter;
			if (&other == &myAllocation)
				continue;
			if (ignoreSameTravelerAllocs && other.traveler == myAllocation.traveler)
				continue;
			bool isCollision;
			int result = VISIT_CONTINUE;
			if (other.acquireTime <= myAllocation.acquireTime)
				isCollision = other.releaseTime > myAllocation.acquireTime;
			else isCollision = myAllocation.releaseTime > other.acquireTime;
			if (isCollision) {
				result = predicate(iter);
				if ((result & VISIT_ABORT) != 0)
					return &other;
			}
			if ((result & VISIT_NO_INC_ITER) == 0)
				++iter;
		}
		return nullptr;
	}

	static NodeAllocation* findCollision(AStarNodeExtraData* nodeData, const NodeAllocation& myAllocation, bool ignoreSameTravelerAllocs);

	// FlexScript-accessible method
	static NodeAllocation findCollision(NodeAllocation& test, int ignoreSameTravelerAllocs);
	
	astar_export void removeAllocation(TravelerAllocations::iterator iter);
	astar_export void cullExpiredAllocations();
	astar_export void clearAllocationsExcept(const Cell& cell);
	astar_export void clearAllocations();
	void clearAllocationsUpTo(TravelerAllocations::iterator iter);
	/// <summary>	Clears the allocations including and after fromPoint. </summary>
	/// <remarks>	Anthony.johnson, 4/17/2017. </remarks>
	/// <param name="fromPoint">	from point. </param>
	void clearAllocations(TravelerAllocations::iterator fromPoint, bool decrementTraversal = false);
	TravelerAllocations::iterator find(NodeAllocation* alloc);
	void resetTravelDist(double& atTravelDist);
	astar_export void abortTravel(TreeNode* newTS);
	double lastStatUpdateTravelDist = 0.0;
	astar_export double updateLocation(bool updateTravelDistStats = false);
	astar_export void updateSpeedMarkers();
	astar_export double getCurSpeed();
	bool isTEInModelSceneGraph();

	class ArrivalEvent : public FlexSimEvent
	{
	public:
		bool isZeroSpeedEvent = false;
		ArrivalEvent() : FlexSimEvent() {}
		ArrivalEvent(Traveler* object, double time, bool isZeroSpeedEvent) : FlexSimEvent(object->holder, time, nullptr, 0), isZeroSpeedEvent(isZeroSpeedEvent) {}
		virtual const char* getClassFactory() override { return "AStar::Traveler::ArrivalEvent"; }
		virtual void execute() override { if (partner()) partner()->objectAs(Traveler)->onArrival(isZeroSpeedEvent); }
	};
	ObjRef<FlexSimEvent> nextEvent;

	astar_export void onBlock(Traveler* collidingWith, double colliderTravelDist, Cell& cell);

	bool isNavigatingAroundDeadlock = false;
	bool isContinuingFromDeadlock = false;
	bool navigateAroundDeadlock(Array& deadlockList);
	class BlockEvent : public FlexSimEvent
	{
	public:
		BlockEvent() : FlexSimEvent() {}
		BlockEvent(Traveler* collider, double colliderTravelDist, int intermediateAllocationIndex, Traveler* collidingWith, const Cell& cell, double time) 
			: FlexSimEvent(collider->holder, time, collidingWith->holder, cell.row * 100000 + cell.col), colliderTravelDist(colliderTravelDist), intermediateAllocationIndex(intermediateAllocationIndex), cell(cell)
		{}
		virtual const char* getClassFactory() override { return "AStar::Traveler::BlockEvent"; }
		virtual void bind() override;
		virtual void execute() override
		{
			Traveler* t = partner()->objectAs(Traveler);
			t->onBlock(involved ? involved->objectAs(Traveler) : nullptr, colliderTravelDist, cell);
		}
		bool operator < (const BlockEvent& other) {
			if (time < other.time)
				return true;
			if (time > other.time)
				return false;
			double tinyDist = involved->object<Traveler>()->tinyDist;
			if (colliderTravelDist < other.colliderTravelDist - tinyDist)
				return true;
			if (colliderTravelDist > other.colliderTravelDist + tinyDist)
				return false;
			if (intermediateAllocationIndex < other.intermediateAllocationIndex)
				return true;
			return false;
		}
		double colliderTravelDist;
		int intermediateAllocationIndex;
		Cell cell;
	};
	/// <summary>
	/// Duplicates nextEvent if nextEvent is to block
	/// </summary>
	ObjRef<BlockEvent> blockEvent;
	double lastBlockTime;
	double tinyTime = 0.0;
	double tinyDist = 0.0;
	bool isRoutingNow = false;

	bool findDeadlockCycle(ObjectDataType* start, Array& travelers);

	treenode kinematics;

	treenode onBlockTrigger = nullptr;
	treenode onContinueTrigger = nullptr;
	treenode onRerouteTrigger = nullptr;
	treenode onBridgeArrivalTrigger = nullptr;
	treenode onBridgeContinueTrigger = nullptr;
	treenode onCalculatePath = nullptr;
	treenode onNavigatePath = nullptr;

	treenode bridgeDataNode = nullptr;
	TravelerBridgeData* bridgeData = nullptr;
	astar_export void assertBridgeData(BridgeRoutingData* routing);

	astar_export void onTEDestroyed();

	struct RoutingAlgorithmSnapshot {
		std::vector<AStarSearchEntry> totalSet;
		int shortestIndex;
	};
	std::vector<RoutingAlgorithmSnapshot> routingAlgorithmSnapshots;

	double useMandatoryPath = 0.0;

	CachedPathKey cachedPathKey;
	bool isCachedPathKeyValid = false;
	int numDeadlocksSinceLastNavigate = 0;

	/// <summary>
	/// True if the traveler finished a previous task with non-zero speed (was not preempted) and 
	/// is given a new task. In this case, I want him to finish his previous travel path.
	/// </summary>
	bool shouldFinishTravelPath;

	NodeListArray<TravelAllocation>::SdtSubNodeType controlAreaAllocations;
	//NodeListArray<ObjectDataType>::ObjCouplingType controlAreas;
	void onControlAreaArrival(int areaIndex, int travelPathIndex);
	void onControlAreaExit(const ObjRef<TravelAllocation>& alloc);

	double navigatedDist = 0.0;
};

}