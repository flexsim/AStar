#pragma once
#include "AStarClasses.h"
#include "FlexsimDefs.h"
#include <list>
#include <deque>
#include "AStarTypes.h"
#include "Bridge.h"

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
	bool isActive = false;
	std::list<Traveler*>::iterator activeEntry;
	TravelPath travelPath;
	TravelPath& __getTravelPath() { return travelPath; }
	//double nodeWidth;
	typedef std::deque<NodeAllocationIterator> TravelerAllocations;
	TravelerAllocations allocations;
	AllocationRange getAllocations(double atTime);
	NodeAllocation* request = nullptr;
	int nextCollisionUpdateTravelIndex;
	double nextCollisionUpdateEndTime;
	

	AStarNavigator* navigator;
	TaskExecuter* te;
	bool isBlocked = false;
	bool needsContinueTrigger = false;
	/// <summary>Zero-based index of the travel path element that could not be allocated 
	/// 		 (the next node after where the traveler is when he gets blocked).</summary>
	int blockedAtTravelPathIndex = -1;
	void onReset();
	void onStartSimulation();
	void onCollisionIntervalUpdate() {
		if (!isBlocked && nextCollisionUpdateTravelIndex >= 0)
			navigatePath(nextCollisionUpdateTravelIndex, true); 
	}
	void navigatePath(int startAtPathIndex, bool isCollisionUpdateInterval = false);
	void navigatePath(TravelPath&& path)
	{
		travelPath = std::move(path);
		navigatePath(0);
	}
	void onBridgeArrival(BridgeRoutingData* bridge, int pathIndex);
	void onArrival();

	/// <summary>	Adds an allocation to the map's set of allocations. </summary>
	/// <remarks>	Anthony.johnson, 4/17/2017. </remarks>
	/// <param name="allocation">	The allocation. </param>
	/// <param name="force">	 	(Optional) the force. </param>
	/// <returns>	If it succeeds it will return the added allocation. If it fails 
	/// 			(it can't add the allocation because that would cause allocation overlaps)
	/// 			it will return nullptr and create a collision event. </returns>
	NodeAllocation* addAllocation(NodeAllocation& allocation, bool force, bool notifyPendingAllocations);
	void checkCreateCollisionEvent(NodeAllocation& allocation, AStarNodeExtraData* nodeData = nullptr);
	static NodeAllocation* findCollision(AStarNodeExtraData* nodeData, const NodeAllocation& myAllocation, bool ignoreSameTravelerAllocs);
	void removeAllocation(TravelerAllocations::iterator iter);
	void cullExpiredAllocations();
	void clearAllocationsExcept(const Cell& cell);
	void clearAllocations();
	void clearAllocationsUpTo(TravelerAllocations::iterator iter);
	/// <summary>	Clears the allocations including and after fromPoint. </summary>
	/// <remarks>	Anthony.johnson, 4/17/2017. </remarks>
	/// <param name="fromPoint">	from point. </param>
	void clearAllocations(TravelerAllocations::iterator fromPoint, bool decrementTraversal = false);
	TravelerAllocations::iterator find(NodeAllocation* alloc);
	void abortTravel(TreeNode* newTS);
	void updateLocation();

	class ArrivalEvent : public FlexSimEvent
	{
	public:
		ArrivalEvent() : FlexSimEvent() {}
		ArrivalEvent(Traveler* object, double time) : FlexSimEvent(object->holder, time, nullptr, 0) {}
		virtual const char* getClassFactory() override { return "AStar::Traveler::ArrivalEvent"; }
		virtual void execute() override { partner()->objectAs(Traveler)->onArrival(); }
	};
	ObjRef<ArrivalEvent> arrivalEvent;

	void onBlock(Traveler* collidingWith, int colliderPathIndex, Cell& cell);

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

	ObjRef<BridgeRoutingData::ArrivalEvent> bridgeArrivalEvent;
	treenode bridgeDataNode = nullptr;
	TravelerBridgeData* bridgeData = nullptr;
	void assertBridgeData(BridgeRoutingData* routing);

	void onTEDestroyed();

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