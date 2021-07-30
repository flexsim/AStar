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
	double expectedtotaltraveldist;
	//double estimatedIndefiniteAllocTimeDelay;
	DestinationThreshold destThreshold;
	treenode destNode;
	bool isActive = false;
	int __getIsActive() { return (int)isActive; }
	std::list<Traveler*>::iterator activeEntry;
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
	bool isBlocked = false;
	int __getIsBlocked() { return (int)isBlocked; }
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
	void onArrival();
	void finishPath() { onArrival(); }

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
	void updateTravelDistOnInterrupt();
	astar_export void abortTravel(TreeNode* newTS);
	astar_export void updateLocation();

	class ArrivalEvent : public FlexSimEvent
	{
	public:
		ArrivalEvent() : FlexSimEvent() {}
		ArrivalEvent(Traveler* object, double time) : FlexSimEvent(object->holder, time, nullptr, 0) {}
		virtual const char* getClassFactory() override { return "AStar::Traveler::ArrivalEvent"; }
		virtual void execute() override { partner()->objectAs(Traveler)->onArrival(); }
	};
	ObjRef<ArrivalEvent> arrivalEvent;

	astar_export void onBlock(Traveler* collidingWith, int colliderPathIndex, Cell& cell);

	bool isNavigatingAroundDeadlock = false;
	bool isContinuingFromDeadlock = false;
	bool navigateAroundDeadlock(std::vector<Traveler*>& deadlockList, NodeAllocation& deadlockCreatingRequest);
	class BlockEvent : public FlexSimEvent
	{
	public:
		BlockEvent() : FlexSimEvent() {}
		BlockEvent(Traveler* collider, int colliderPathIndex, int intermediateAllocationIndex, Traveler* collidingWith, const Cell& cell, double time) 
			: FlexSimEvent(collider->holder, time, collidingWith->holder, cell.row * 100000 + cell.col), colliderPathIndex(colliderPathIndex), intermediateAllocationIndex(intermediateAllocationIndex), cell(cell)
		{}
		virtual const char* getClassFactory() override { return "AStar::Traveler::BlockEvent"; }
		virtual void bind() override;
		virtual void execute() override
		{
			Traveler* t = partner()->objectAs(Traveler);
			if (t->blockEvent == this)
				t->blockEvent = nullptr;
			t->onBlock(involved ? involved->objectAs(Traveler) : nullptr, colliderPathIndex, cell);
		}
		bool operator < (const BlockEvent& other) {
			if (time < other.time)
				return true;
			if (time > other.time)
				return false;
			if (colliderPathIndex < other.colliderPathIndex)
				return true;
			if (colliderPathIndex > other.colliderPathIndex)
				return false;
			if (intermediateAllocationIndex < other.intermediateAllocationIndex)
				return true;
			return false;
		}
		int colliderPathIndex;
		int intermediateAllocationIndex;
		Cell cell;
	};
	ObjRef<BlockEvent> blockEvent;
	double lastBlockTime;
	double tinyTime = 0.0;
	bool isRoutingNow = false;

	bool findDeadlockCycle(Traveler* start, std::vector<Traveler*>& travelers);

	treenode onBlockTrigger = nullptr;
	treenode onContinueTrigger = nullptr;
	treenode onRerouteTrigger = nullptr;
	treenode onBridgeArrivalTrigger = nullptr;
	treenode onBridgeContinueTrigger = nullptr;
	treenode onCalculatePath = nullptr;
	treenode onNavigatePath = nullptr;

	ObjRef<FlexSimEvent> bridgeEvent;
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
};

}