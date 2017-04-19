#include "Traveler.h"
#include "AStarNavigator.h"
#include "Bridge.h"
#include "macros.h"
#include "TemporaryBarrier.h"

namespace AStar {

void Traveler::bind()
{
	bindNumber(isActive);
	bindNumber(isBlocked);
	bindObjRef(arrivalEvent, false);
	bindObjRef(collisionEvent, false);
	bindNumber(nodeWidth); 
	bindNumber(destLoc.x);
	bindNumber(destLoc.y);
	bindNumber(destLoc.z);
	bindSubNode(distQueryKinematics, 0);
	navigator = holder->ownerObject->objectAs(AStarNavigator);
	te = partner()->ownerObject->objectAs(TaskExecuter);

	bindStlContainer(travelPath);
	if (getBindMode() == SDT_BIND_ON_DISPLAY) {
		appendToDisplayStr("allocations:");
		for (auto alloc : allocations) {
			alloc->bind(nullptr);
		}
	}
	//bindStlContainer(allocations);

}

void Traveler::CollisionEvent::bind()
{
	__super::bind();
	cell.bind(this);
	bindNumber(colliderPathIndex);
	bindNumber(collidingWithPathIndex);
}

void Traveler::onReset()
{
	holder->name = te->holder->name;
	isActive = false;
	isBlocked = false;
	nodeWidth = navigator->nodeWidth;
	allocations.clear();
	Vec3 loc = te->getLocation(0.5, 0.5, 0.0);
	AStarCell resetCell = navigator->getCellFromLoc(Vec2(loc.x, loc.y));
	travelPath.clear();
	travelPath.push_back(AStarPathEntry(resetCell, -1));
}

void Traveler::onStartSimulation()
{
	if (navigator->doCollisionAvoidance) {
		Vec3 loc = te->getLocation(0.5, 0.5, 0.0);
		AStarCell resetCell = navigator->getCellFromLoc(Vec2(loc.x, loc.y));
		travelPath.clear();
		travelPath.push_back(AStarPathEntry(resetCell, -1));
		addAllocation(NodeAllocation(this, resetCell, 0, 0.0, DBL_MAX), true);
	}
}

void Traveler::navigatePath(int startAtPathIndex, bool isDistQueryOnly)
{
	AStarNavigator* nav = navigator;

	// Don't know why this was here. I'm commenting it out.
	//if (!isDistQueryOnly) {
	//	coupling = tonode(get(first(te->node_v_navigator)));
	//	while (content(holder) < 1)
	//		nodeinsertinto(holder);
		//TreeNode* idList = first(coupling);
		// TODO: figure out idLists
	//}
	isBlocked = false;
	if (!isDistQueryOnly) {
		// update TE state
		if (content(te->holder))
			setstate(te->holder, STATE_TRAVEL_LOADED);
		else
			setstate(te->holder, STATE_TRAVEL_EMPTY);
	}

	treenode kinematics = !isDistQueryOnly ? te->node_v_kinematics : distQueryKinematics;
	double outputVector[3];
	Vec3 startLoc = nav->getLocFromCell(travelPath[startAtPathIndex].cell);
	if (up(te->holder) != model())
		startLoc = startLoc.project(model(), up(te->holder));

	int kinFlags = 0;
	if (te->node_v_modifyrotation) {
		kinFlags |= KINEMATIC_MANAGE_ROTATIONS;
		if (!te->canRotateOnIncline())
			kinFlags |= KINEMATIC_NO_INCLINE_ROTATION;
	}
	initkinematics(kinematics, startLoc.x, startLoc.y, te->b_spatialz, 0, 0, 0, kinFlags, 0);

	AStarPathEntry e, laste;
	int numNodes = travelPath.size();
	laste.cell = travelPath[startAtPathIndex].cell;
	bool doCollisionAvoidance = nav->doCollisionAvoidance;
	double endTime = time();
	double releaseTime = endTime;

	int lastAllocationIndex;
	if (doCollisionAvoidance) {
		if (startAtPathIndex == 0 && travelPath.front().cell != allocations.front()->cell) {
			clearAllocations();
			addAllocation(NodeAllocation(this, travelPath.front().cell, 0, time(), time()), true);
		} else {
			while (allocations.size() > 1 && allocations.front()->releaseTime <= time())
				removeAllocation(allocations.begin());
		}
		lastAllocationIndex = 0;
	}

	int didBlockPathIndex = -1;
	for (int i = startAtPathIndex + 1; i < numNodes; i++) {
		e = travelPath[i];
		double totalTravelDist;
		if (laste.bridgeIndex == -1) {
			int numSuccessfulAllocations = 0;
			double nextX = (e.cell.col - laste.cell.col)*nodeWidth;
			double nextY = (e.cell.row - laste.cell.row)*nodeWidth;
			double startTime = endTime;
			endTime = addkinematic(kinematics, nextX, nextY, 0,
				te->v_maxspeed, 0, 0, 0, 0, startTime, KINEMATIC_TRAVEL);

			if (doCollisionAvoidance) {
				NodeAllocation allocation(this, e.cell, i, startTime, endTime);
				NodeAllocation* success = &allocation;
				// if it is a diagonal move, then I need to do additional allocations
				if (e.cell.row != laste.cell.row && e.cell.col != laste.cell.col) {
					// is it a deep vertical search step
					if (abs(e.cell.row - laste.cell.row) == 2) {
						allocation.cell.row = (e.cell.row + laste.cell.row) / 2;
						allocation.cell.col = laste.cell.col;
						success = addAllocation(allocation);
						if (success) {
							numSuccessfulAllocations++;
							allocation.cell.col = e.cell.col;
							success = addAllocation(allocation);
							numSuccessfulAllocations += success ? 1 : 0;
						}
					} // is it a deep horizontal search step
					else if (abs(e.cell.col - laste.cell.col) == 2) {
						allocation.cell.col = (e.cell.col + laste.cell.col) / 2;
						allocation.cell.row = laste.cell.row;
						success = addAllocation(allocation);
						if (success) {
							numSuccessfulAllocations++;
							allocation.cell.row = e.cell.row;
							success = addAllocation(allocation);
							numSuccessfulAllocations += success ? 1 : 0;
						}
					} else {
						auto leftCell = e.cell.col < laste.cell.col ? e.cell : laste.cell;
						// allocate the "right quadrant" node
						allocation.cell.row = leftCell.row;
						allocation.cell.col = leftCell.col + 1;
						success = addAllocation(allocation);
						numSuccessfulAllocations += success ? 1 : 0;
					}
				}
				allocation.cell = e.cell;
				if (success) {
					success = addAllocation(allocation);
					if (success)
						lastAllocationIndex = allocations.size() - 1;
				}
				if (!success) {
					if (numSuccessfulAllocations > 0)
						clearAllocations(allocations.end() - numSuccessfulAllocations);
					allocations[lastAllocationIndex]->extendReleaseTime(DBL_MAX);
					didBlockPathIndex = i;
					break;
				}
			}
			totalTravelDist = sqrt(sqr(nextX) + sqr(nextY));
		} else {
			// travel on a bridge
			auto nodeData = nav->edgeTableExtraData.find(laste.cell.colRow);
			AStarNodeExtraData::BridgeEntry& entry = nodeData->second->bridges[laste.bridgeIndex];
			totalTravelDist = entry.bridge->calculateDistance();
			int begin, end, inc;
			if (entry.isAtBridgeStart) {
				begin = 0;
				end = entry.bridge->pointList.size();
				inc = 1;
			} else {
				begin = entry.bridge->pointList.size();
				end = -1;
				inc = -1;
			}
			Point* lastPoint = entry.bridge->pointList[begin];
			double startZ = lastPoint->z;
			for (int i = begin + inc; i != end; i += inc) {
				Point* point = entry.bridge->pointList[i];
				Vec3 diff(point->x - lastPoint->x, point->y - lastPoint->y, point->z - lastPoint->z);
				endTime = addkinematic(kinematics, diff.x, diff.y, diff.z,
					te->v_maxspeed, 0, 0, 0, 0, endTime, KINEMATIC_TRAVEL);
				lastPoint = point;
			}
			double zDiff = lastPoint->z - startZ;
			if (fabs(zDiff) > 0.001) {
				addkinematic(kinematics, 0, 0, -zDiff,
					te->v_maxspeed, 0, 0, 0, 0, endTime, KINEMATIC_TRAVEL);
			}
		}

		if (!isDistQueryOnly) {
			te->v_totaltraveldist += totalTravelDist;


			//Traffic info
			AStarNodeExtraData* extra = nav->assertExtraData(e.cell);
			unsigned int* involvedextra;
			if (e.cell.row > laste.cell.row) {
				if (e.cell.col > laste.cell.col) involvedextra = &extra->nrFromDownLeft;
				else if (e.cell.col < laste.cell.col) involvedextra = &extra->nrFromDownRight;
				else involvedextra = &extra->nrFromDown;
			} else if (e.cell.row < laste.cell.row) {
				if (e.cell.col > laste.cell.col) involvedextra = &extra->nrFromUpLeft;
				else if (e.cell.col < laste.cell.col) involvedextra = &extra->nrFromUpRight;
				else involvedextra = &extra->nrFromUp;
			} else if (e.cell.col > laste.cell.col)
				involvedextra = &extra->nrFromLeft;
			else involvedextra = &extra->nrFromRight;

			involvedextra[0]++;
			if (involvedextra[0] > nav->maxTraveled) nav->maxTraveled = involvedextra[0];
		}

		laste = e;
	}

	// remove the first allocation if I was able to allocation ahead at least one
	// This will trigger other travelers who might be waiting for me to move on 
	// from the current point I'm at.
	if (didBlockPathIndex == -1 || didBlockPathIndex > startAtPathIndex + 1)
		removeAllocation(allocations.begin());

	if (!isDistQueryOnly) {
		if (!isActive) {
			nav->activeTravelers.push_front(this);
			isActive = true;
			activeEntry = nav->activeTravelers.begin();
		}
		if (didBlockPathIndex == -1)
			arrivalEvent = createevent(new ArrivalEvent(this, endTime))->objectAs(ArrivalEvent);
	}
}

NodeAllocation* Traveler::addAllocation(NodeAllocation& allocation, bool force)
{
	AStarNodeExtraData* nodeData = navigator->assertExtraData(allocation.cell);

	if (!force) {
		NodeAllocation* collideWith = findCollision(nodeData, allocation);
		if (collideWith) {
			NodeAllocation* laterAllocation = allocation.acquireTime < collideWith->acquireTime ? collideWith : &allocation;
			NodeAllocation* earlierAllocation = laterAllocation == collideWith ? &allocation : collideWith;
			if (laterAllocation->traveler->collisionEvent)
				destroyevent(laterAllocation->traveler->collisionEvent->holder);

			CollisionEvent* event = new CollisionEvent(laterAllocation->traveler, laterAllocation->travelPathIndex,
				earlierAllocation->traveler, earlierAllocation->travelPathIndex, allocation.cell, laterAllocation->acquireTime);
			laterAllocation->traveler->collisionEvent = createevent(event)->objectAs(CollisionEvent);

			if (laterAllocation == &allocation)
				return nullptr;
			else {
				// if the guy I'm colliding with is the later allocation, then I need to get rid of any events and 
				// additional allocations that come after that guy's allocation, because he's going to be the 
				// guy to stop, so subsequent allocations are invalid at the point when he stops.
				Traveler* laterTraveler = laterAllocation->traveler;
				laterTraveler->clearAllocations(laterTraveler->find(laterAllocation));
				if (laterTraveler->arrivalEvent)
					destroyevent(laterTraveler->arrivalEvent->holder);
			}
		}
	}

	nodeData->allocations.push_front(allocation);
	allocations.push_back(nodeData->allocations.begin());
	return &(nodeData->allocations.front());
}


NodeAllocation* Traveler::findCollision(AStarNodeExtraData* nodeData, const NodeAllocation& myAllocation)
{
	auto foundCollision = std::find_if(nodeData->allocations.begin(), nodeData->allocations.end(),
		[&](NodeAllocation& other) {
		return &other != &myAllocation
				&& ((other.acquireTime <= myAllocation.acquireTime
						&& other.releaseTime > myAllocation.acquireTime)
					|| (other.acquireTime <= myAllocation.releaseTime
						&& other.releaseTime > myAllocation.releaseTime));
		});	

	if (foundCollision != nodeData->allocations.end())
		return &(*foundCollision);
	return nullptr;
}


void Traveler::removeAllocation(TravelerAllocations::iterator iter)
{
	NodeAllocationIterator inExtraData = *iter;
	allocations.erase(iter);
	navigator->getExtraData(inExtraData->cell)->removeAllocation(inExtraData);
}

void Traveler::clearAllocations()
{
	while (allocations.size() > 0)
		removeAllocation(allocations.begin());
}


void Traveler::clearAllocationsUpTo(TravelerAllocations::iterator iter)
{
	int numToRemove = iter + 1 - allocations.begin();
	for (int i = 0; i < numToRemove; i++)
		removeAllocation(allocations.begin());
}

void Traveler::clearAllocations(TravelerAllocations::iterator fromPoint)
{
	int numToRemove = allocations.end() - fromPoint;
	for (int i = 0; i < numToRemove; i++)
		removeAllocation(allocations.end() - 1);
}


Traveler::TravelerAllocations::iterator Traveler::find(NodeAllocation* alloc)
{
	return std::find_if(allocations.begin(), allocations.end(), [&](NodeAllocationIterator& iter) { return &(*iter) == alloc; });
}

void Traveler::onCollide(CollisionEvent* event, Traveler* collidingWith)
{
	if (collisionEvent == event)
		collisionEvent = nullptr;
	bool shouldStop = true;
	if (travelPath.size() <= event->colliderPathIndex || collidingWith->travelPath.size() <= event->collidingWithPathIndex)
		shouldStop = false;

	AStarNodeExtraData* nodeData = navigator->getExtraData(event->cell);
	auto foundAlloc = std::find_if(nodeData->allocations.begin(), nodeData->allocations.end(),
		[&](NodeAllocation& alloc) { return alloc.traveler == collidingWith && alloc.acquireTime <= time() && alloc.releaseTime > time(); }
		);
	
	if (shouldStop && foundAlloc == nodeData->allocations.end())
		shouldStop = false;

	if (shouldStop) {
		updateLocation();
		Vec3 pos = te->getLocation(0.5, 0.5, 0.0);
		if (up(te->holder) != model())
			pos = pos.project(model(), up(te->holder));
		initkinematics(te->node_v_kinematics, pos.x, pos.y, te->b_spatialz, 0.0, 0.0, 0.0, 1, 0);

		setstate(te->holder, STATE_BLOCKED);

		std::vector<Traveler*> deadlockList;

		allocations.back()->extendReleaseTime(DBL_MAX);
		request = nodeData->addRequest(NodeAllocation(this, event->cell, event->colliderPathIndex, time(), FLT_MAX), *foundAlloc, &deadlockList);
		isBlocked = true;
		if (request == nullptr) {
			navigateAroundDeadlock(deadlockList);
		}

	} else {
		navigatePath(event->colliderPathIndex - 1, false);
	}
}


bool Traveler::navigateAroundDeadlock(std::vector<Traveler*>& deadlockList)
{
	TemporaryBarrier barrier(navigator);
	double curTime = time();
	AStarNode noTravelNode;
	noTravelNode.value = 0;
	for (Traveler* traveler : deadlockList) {
		if (traveler == this)
			continue;
		
		for (NodeAllocationIterator iter : traveler->allocations) {
			if (iter->acquireTime <= curTime && iter->releaseTime > curTime) {
				AStarCell cell = iter->cell;
				barrier.addEntry(cell, noTravelNode);
				auto checkAddEntry = [&](int colInc, int rowInc, Direction nullifyDirection) {
					AStarCell offset(cell);
					offset.col += colInc;
					offset.row += rowInc;
					if (offset.col >= 0 && offset.col < navigator->edgeTableXSize && offset.row >= 0 && offset.row < navigator->edgeTableYSize) {
						AStarNode node = *navigator->getNode(offset);
						node.setCanGo(nullifyDirection, false);
						barrier.addEntry(offset, node);
					}
				};
				checkAddEntry(-1, 0, Right);
				checkAddEntry(1, 0, Left);
				checkAddEntry(0, 1, Down);
				checkAddEntry(0, -1, Up);
			}
		}
	}

	barrier.apply();

	TravelPath travelPath = navigator->calculateRoute(te->holder, destLoc, endSpeed, true);
	barrier.unapply();


	navigatePath(std::move(travelPath), false);

	return travelPath.size() > 0;
}

bool Traveler::findDeadlockCycle(Traveler* start, std::vector<Traveler*>& travelers)
{
	travelers.push_back(this);
	size_t startSize = travelers.size();
	double curTime = time();
	for (NodeAllocationIterator& allocIter : allocations) {
		NodeAllocation& alloc = *allocIter;
		if (alloc.acquireTime > curTime || alloc.releaseTime <= curTime)
			continue;
		AStarNodeExtraData* data = navigator->getExtraData(alloc.cell);
		if (data->findDeadlockCycle(start, travelers))
			return true;
	}
	travelers.pop_back();
	return false;
}

void Traveler::onArrival()
{
	arrivalEvent = nullptr;
	TreeNode* kinematics = te->node_v_kinematics;
	updatekinematics(kinematics, te->holder, time());
	te->b_spatialx -= 0.5*te->b_spatialsx;
	te->b_spatialy += 0.5*te->b_spatialsy;
	navigator->activeTravelers.erase(activeEntry);
	isActive = false;
	AStarPathEntry back = travelPath.back();
	travelPath.clear();
	travelPath.push_back(back);
	if (allocations.size() > 1)
		clearAllocationsUpTo(allocations.end() - 2);
	allocations.front()->extendReleaseTime(DBL_MAX);
	te->onDestinationArrival(0);
}



void Traveler::updateLocation()
{
	TreeNode* kinematics = te->node_v_kinematics;
	updatekinematics(kinematics, te->holder, time());
	te->b_spatialx -= 0.5*te->b_spatialsx;
	te->b_spatialy += 0.5*te->b_spatialsy;
}

}