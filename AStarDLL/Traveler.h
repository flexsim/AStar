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
	Traveler(AStarNavigator* nav, TaskExecuter* te) : navigator(nav), te(te) {}
	Traveler() : navigator(nullptr), te(nullptr) {}

	bool isActive = false;
	std::list<Traveler*>::iterator activeEntry;
	TravelPath travelPath;
	double nodeWidth;
	typedef std::deque<NodeAllocationIterator> TravelerAllocations;
	TravelerAllocations allocations;
	NodeAllocation* request;

	AStarNavigator* navigator;
	TaskExecuter* te;
	bool isBlocked = false;
	void onReset();
	void onStartSimulation();
	void navigatePath(int startAtPathIndex, bool isDistQueryOnly);
	void navigatePath(TravelPath&& path, bool isDistQueryOnly)
	{
		travelPath = std::move(path);
		navigatePath(0, isDistQueryOnly);
	}
	void onArrival();

	/// <summary>	Adds an allocation to the map's set of allocations. </summary>
	/// <remarks>	Anthony.johnson, 4/17/2017. </remarks>
	/// <param name="allocation">	The allocation. </param>
	/// <param name="force">	 	(Optional) the force. </param>
	/// <returns>	If it succeeds it will return the added allocation. If it fails 
	/// 			(it can't add the allocation because that would cause allocation overlaps)
	/// 			it will return nullptr and create a collision event. </returns>
	NodeAllocation* addAllocation(NodeAllocation& allocation, bool force = false);
	void checkCreateCollisionEvent(NodeAllocation& allocation, AStarNodeExtraData* nodeData = nullptr);
	static NodeAllocation* findCollision(AStarNodeExtraData* nodeData, const NodeAllocation& myAllocation);
	void removeAllocation(TravelerAllocations::iterator iter);
	void clearAllocations();
	void clearAllocationsUpTo(TravelerAllocations::iterator iter);
	/// <summary>	Clears the allocations including and after fromPoint. </summary>
	/// <remarks>	Anthony.johnson, 4/17/2017. </remarks>
	/// <param name="fromPoint">	from point. </param>
	void clearAllocations(TravelerAllocations::iterator fromPoint);
	TravelerAllocations::iterator find(NodeAllocation* alloc);
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

	class CollisionEvent;
	void onCollide(CollisionEvent* event, Traveler* collidingWith);
	class CollisionEvent : public FlexSimEvent
	{
	public:
		CollisionEvent() : FlexSimEvent() {}
		CollisionEvent(Traveler* collider, int colliderPathIndex, Traveler* collidingWith, int collidingWithPathIndex, const AStarCell& cell, double time) 
			: FlexSimEvent(collider->holder, time, collidingWith->holder, cell.row * 100000 + cell.col), colliderPathIndex(colliderPathIndex), collidingWithPathIndex(collidingWithPathIndex), cell(cell)
		{}
		virtual const char* getClassFactory() override { return "AStar::Traveler::CollisionEvent"; }
		virtual void bind() override;
		virtual void execute() override { partner()->objectAs(Traveler)->onCollide(this, involved->objectAs(Traveler)); }
		int colliderPathIndex;
		int collidingWithPathIndex;
		AStarCell cell;
	};
	ObjRef<CollisionEvent> collisionEvent;

	bool findDeadlockCycle(Traveler* start, std::vector<Traveler*> travelers);

};


}