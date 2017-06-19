#pragma once
#include "AStarClasses.h"
#include "FlexsimDefs.h"
#include <list>
#include <deque>
#include "AStarTypes.h"

namespace AStar {


class Traveler : public CouplingDataType
{
public:
	virtual const char* getClassFactory() override { return "AStar::Traveler"; }
	virtual void bind() override;
	virtual void bindEvents() override;

	TreeNode* getEventInfoObject(const char* eventTitle) override;

	Traveler(AStarNavigator* nav, TaskExecuter* te) : navigator(nav), te(te) {}
	Traveler() : navigator(nullptr), te(nullptr) {}

	Vec3 destLoc;
	double endSpeed;
	DestinationThreshold destThreshold;
	treenode destNode;
	bool isActive = false;
	std::list<Traveler*>::iterator activeEntry;
	TravelPath travelPath;
	double nodeWidth;
	typedef std::deque<NodeAllocationIterator> TravelerAllocations;
	TravelerAllocations allocations;
	NodeAllocation* request = nullptr;
	int nextCollisionUpdateTravelIndex;
	double nextCollisionUpdateEndTime;
	

	AStarNavigator* navigator;
	TaskExecuter* te;
	bool isBlocked = false;
	bool needsContinueTrigger = false;
	void onReset();
	void onStartSimulation();
	void onCollisionIntervalUpdate() {
		if (!isBlocked && nextCollisionUpdateTravelIndex >= 0)
			navigatePath(nextCollisionUpdateTravelIndex, false, true); 
	}
	void navigatePath(int startAtPathIndex, bool isDistQueryOnly, bool isCollisionUpdateInterval = false);
	void navigatePath(TravelPath&& path, bool isDistQueryOnly)
	{
		travelPath = std::move(path);
		navigatePath(0, isDistQueryOnly);
	}
	void onBridgeArrival(int pathIndex);
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
	treenode distQueryKinematics;

	void onBlock(Traveler* collidingWith, int colliderPathIndex, AStarCell& cell);

	struct NavigationAttempt {
		TravelPath path;
		Traveler* traveler;
		double penalty = DBL_MAX;
	};
	bool navigateAroundDeadlock(std::vector<Traveler*>& deadlockList, NodeAllocation& deadlockCreatingRequest);
	class BlockEvent : public FlexSimEvent
	{
	public:
		BlockEvent() : FlexSimEvent() {}
		BlockEvent(Traveler* collider, int colliderPathIndex, int intermediateAllocationIndex, Traveler* collidingWith, const AStarCell& cell, double time) 
			: FlexSimEvent(collider->holder, time, collidingWith->holder, cell.row * 100000 + cell.col), colliderPathIndex(colliderPathIndex), intermediateAllocationIndex(intermediateAllocationIndex), cell(cell)
		{}
		virtual const char* getClassFactory() override { return "AStar::Traveler::BlockEvent"; }
		virtual void bind() override;
		virtual void execute() override
		{
			Traveler* t = partner()->objectAs(Traveler);
			if (t->blockEvent == this)
				t->blockEvent = nullptr;
			t->onBlock(involved->objectAs(Traveler), colliderPathIndex, cell);
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
		AStarCell cell;
	};
	ObjRef<BlockEvent> blockEvent;
	double lastBlockTime;
	double tinyTime = 0.0;

	bool findDeadlockCycle(Traveler* start, std::vector<Traveler*>& travelers);

	treenode onBlockTrigger = nullptr;
	treenode onContinueTrigger = nullptr;
	treenode onRerouteTrigger = nullptr;

	class BridgeArrivalEvent : public FlexSimEvent
	{
	public:
		BridgeArrivalEvent() : FlexSimEvent() {}
		BridgeArrivalEvent(Traveler* object, int pathIndex, double time)
			: pathIndex(pathIndex), FlexSimEvent(object->holder, time, nullptr, 0) {}
		virtual const char* getClassFactory() override { return "AStar::Traveler::BridgeArrivalEvent"; }
		virtual void execute() { partner()->objectAs(Traveler)->onBridgeArrival(pathIndex); }

		int pathIndex;
	};
	ObjRef<BridgeArrivalEvent> bridgeArrivalEvent;

	class BridgeCompletedEvent : public FlexSimEvent
	{
	public:
		BridgeCompletedEvent() : FlexSimEvent() {}
		BridgeCompletedEvent(Traveler* object, int pathIndex, double time)
			: pathIndex(pathIndex), FlexSimEvent(object->holder, time, nullptr, 0) {}
		virtual const char* getClassFactory() override { return "AStar::Traveler::BridgeCompletedEvent"; }
		virtual void execute() override { partner()->objectAs(Traveler)->navigatePath(pathIndex, false); }

		int pathIndex;
	};

};


}