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
	bindObjRef(blockEvent, false);
	bindNumber(nodeWidth); 
	bindNumber(destLoc.x);
	bindNumber(destLoc.y);
	bindNumber(destLoc.z);
	bindSubNode(distQueryKinematics, 0);
	bindNumber(blockTime);
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

void Traveler::BlockEvent::bind()
{
	__super::bind();
	cell.bind(this);
	bindNumber(colliderPathIndex);
}

void Traveler::onReset()
{
	holder->name = te->holder->name;
	isActive = false;
	isBlocked = false;
	blockTime = 0;
	nodeWidth = navigator->nodeWidth;
	allocations.clear();
	Vec3 loc = te->getLocation(0.5, 0.5, 0.0);
	AStarCell resetCell = navigator->getCellFromLoc(Vec2(loc.x, loc.y));
	travelPath.clear();
	travelPath.push_back(AStarPathEntry(resetCell, -1));
}

void Traveler::onStartSimulation()
{
	if (navigator->enableCollisionAvoidance) {
		Vec3 loc = te->getLocation(0.5, 0.5, 0.0);
		AStarCell resetCell = navigator->getCellFromLoc(Vec2(loc.x, loc.y));
		travelPath.clear();
		travelPath.push_back(AStarPathEntry(resetCell, -1));
		addAllocation(NodeAllocation(this, resetCell, 0, 0.0, DBL_MAX, 1.0), true);
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
	double rotLerpSize = navigator->smoothRotations;
	double rotLerpSpeed = 90 / (te->b_spatialsx * rotLerpSize / te->v_maxspeed);
	if (te->node_v_modifyrotation) {
		
		if (rotLerpSize == 0)
			kinFlags |= KINEMATIC_MANAGE_ROTATIONS;

		if (!te->canRotateOnIncline())
			kinFlags |= KINEMATIC_NO_INCLINE_ROTATION;
	}
	initkinematics(kinematics, startLoc.x, startLoc.y, te->b_spatialz, 0, 0, te->b_spatialrz, kinFlags, 0);

	AStarPathEntry e, laste;
	int numNodes = travelPath.size();
	laste.cell = travelPath[startAtPathIndex].cell;
	bool enableCollisionAvoidance = nav->enableCollisionAvoidance;
	double endTime = time();
	double releaseTime = endTime;

	int lastAllocationIndex;
	cullExpiredAllocations();
	if (enableCollisionAvoidance) {
		if (allocations.size() == 0 || (startAtPathIndex == 0 && travelPath.front().cell != allocations.front()->cell)) {
			clearAllocations();
			addAllocation(NodeAllocation(this, travelPath.front().cell, 0, time(), time(), 1.0), true);
		}
		lastAllocationIndex = 0;
	}

	int didBlockPathIndex = -1;
	double lastRotation = te->b_spatialrz;
	AStarCell deepSearchMiddleCell1;
	AStarCell deepSearchMiddleCell2;

	for (int i = startAtPathIndex + 1; i < numNodes; i++) {
		e = travelPath[i];
		double totalTravelDist;
		bool isVerticalDeepSearch = false;
		bool isHorizontalDeepSearch = false;
		if (laste.bridgeIndex == -1) {
			int numSuccessfulAllocations = 0;
			double nextX = (e.cell.col - laste.cell.col)*nodeWidth;
			double nextY = (e.cell.row - laste.cell.row)*nodeWidth;
			double startTime = endTime;
			endTime = addkinematic(kinematics, nextX, nextY, 0,
				te->v_maxspeed, 0, 0, 0, 0, startTime, KINEMATIC_TRAVEL);

			if (rotLerpSize != 0) {
				double nextRot = radianstodegrees(atan2(nextY, nextX));
				double rotDiff = nextRot - lastRotation;
				while (rotDiff > 180)
					rotDiff -= 360;
				while (rotDiff < -180)
					rotDiff += 360;

				double timeToRot = rotDiff / rotLerpSpeed;
				double rotStartTime = max(time(), startTime - 0.5 * timeToRot);
				addkinematic(kinematics, 0, 0, rotDiff, rotLerpSpeed, 0, 0, 0, 0, rotStartTime, KINEMATIC_ROTATE);
				lastRotation = nextRot;
			}

			isVerticalDeepSearch = abs(e.cell.row - laste.cell.row) == 2;
			isHorizontalDeepSearch = abs(e.cell.col - laste.cell.col) == 2;
			if (isVerticalDeepSearch) {
				deepSearchMiddleCell1 = AStarCell(laste.cell.col, (e.cell.row + laste.cell.row) / 2);
				deepSearchMiddleCell2 = AStarCell(e.cell.col, deepSearchMiddleCell1.row);
			} else if (isHorizontalDeepSearch) {
				deepSearchMiddleCell1 = AStarCell((e.cell.col + laste.cell.col) / 2, laste.cell.row);
				deepSearchMiddleCell2 = AStarCell(deepSearchMiddleCell1.col, e.cell.row);
			}

			if (enableCollisionAvoidance) {
				double middleReleaseTime = 0.5 * (startTime + endTime);
				NodeAllocation allocation(this, e.cell, i, startTime, middleReleaseTime, 1.0);
				NodeAllocation* success = &allocation;
				// if it is a diagonal move, then I need to do additional allocations
				if (e.cell.row != laste.cell.row && e.cell.col != laste.cell.col) {
					// is it a deep vertical search step
					if (isVerticalDeepSearch || isHorizontalDeepSearch) {
						allocation.cell = deepSearchMiddleCell1;
						allocation.traversalWeight = 0.5;
						success = addAllocation(allocation);
						if (success) {
							numSuccessfulAllocations++;
							allocation.cell= deepSearchMiddleCell2;
							success = addAllocation(allocation);
							numSuccessfulAllocations += success ? 1 : 0;
						}
					} else {
						AStarCell leftCell;
						AStarCell rightCell;
						if (sign(e.cell.col - laste.cell.col) == sign(e.cell.row - laste.cell.row)) {
							// it's a "forward-slash diagonal"
							leftCell = AStarCell(min(e.cell.col, laste.cell.col), max(e.cell.row, laste.cell.row));
							rightCell = AStarCell(max(e.cell.col, laste.cell.col), min(e.cell.row, laste.cell.row));
						} else {
							// it's a "back-slash diagonal"
							leftCell = AStarCell(min(e.cell.col, laste.cell.col), min(e.cell.row, laste.cell.row));
							rightCell = AStarCell(max(e.cell.col, laste.cell.col), max(e.cell.row, laste.cell.row));
						}
						allocation.cell = leftCell;
						allocation.traversalWeight = 0.0;
						success = addAllocation(allocation);
						if (success) {
							numSuccessfulAllocations++;
							allocation.cell = rightCell;
							success = addAllocation(allocation);
							numSuccessfulAllocations += success ? 1 : 0;
						}
					}
				}
				allocation.cell = e.cell;
				if (success) {
					allocation.releaseTime = std::nextafter(endTime, DBL_MAX);
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
			nav->assertExtraData(e.cell)->totalTraversals++;
			if (isVerticalDeepSearch || isHorizontalDeepSearch) {
				nav->assertExtraData(deepSearchMiddleCell1)->totalTraversals += 0.5;
				nav->assertExtraData(deepSearchMiddleCell2)->totalTraversals += 0.5;
			}
		}

		laste = e;
	}

	// remove the first allocation if I was able to allocate ahead at least one
	// This will trigger other travelers who might be waiting for me to move on 
	// from the current point I'm at.
	if (enableCollisionAvoidance && numNodes > startAtPathIndex + 1) {
		if (didBlockPathIndex == -1 || didBlockPathIndex > startAtPathIndex + 1)
			removeAllocation(allocations.begin());
	}

	if (!isDistQueryOnly) {
		if (!isActive) {
			nav->activeTravelers.push_front(this);
			isActive = true;
			activeEntry = nav->activeTravelers.begin();
		}
		if (didBlockPathIndex == -1 && !blockEvent && !isBlocked)
			arrivalEvent = createevent(new ArrivalEvent(this, endTime))->objectAs(ArrivalEvent);
	}

	_ASSERTE(allocations.size() > 0 || !enableCollisionAvoidance);
}

NodeAllocation* Traveler::addAllocation(NodeAllocation& allocation, bool force)
{
	AStarNodeExtraData* nodeData = navigator->assertExtraData(allocation.cell);

	if (!force) {
		NodeAllocation* collideWith = findCollision(nodeData, allocation);
		if (collideWith) {
			NodeAllocation* laterAllocation = allocation.acquireTime < collideWith->acquireTime ? collideWith : &allocation;
			Traveler* laterTraveler = laterAllocation->traveler;
			NodeAllocation* earlierAllocation = laterAllocation == collideWith ? &allocation : collideWith;
			Traveler* earlierTraveler = earlierAllocation->traveler;

			if (laterTraveler->blockEvent)
				destroyevent(laterTraveler->blockEvent->holder);

			double eventTime = std::nextafter(laterAllocation->acquireTime, -FLT_MAX);
			BlockEvent* event = new BlockEvent(laterTraveler, laterAllocation->travelPathIndex, 
				earlierTraveler, allocation.cell, max(time(), eventTime));
			laterTraveler->blockEvent = createevent(event)->objectAs(BlockEvent);

			if (laterAllocation != &allocation) {
				// if the guy I'm colliding with is the later allocation, then I need to get rid of any events and 
				// additional allocations that come after that guy's allocation, because he's going to be the 
				// guy to stop, so subsequent allocations are invalid at the point when he stops.
				auto iter = laterTraveler->find(laterAllocation);
				while (iter - laterTraveler->allocations.begin() >= 2 && (*(iter - 1))->acquireTime == laterAllocation->acquireTime)
					iter--;
				laterTraveler->clearAllocations(iter);
				if (laterTraveler->arrivalEvent)
					destroyevent(laterTraveler->arrivalEvent->holder);
			} else
				return nullptr;
		}
	}

	nodeData->allocations.push_front(allocation);
	allocations.push_back(nodeData->allocations.begin());

	return &(nodeData->allocations.front());
}


NodeAllocation* Traveler::findCollision(AStarNodeExtraData* nodeData, const NodeAllocation& myAllocation)
{
	NodeAllocationIterator bestIter = nodeData->allocations.end();
	double minAcquireTime = DBL_MAX;
	double curTime = time();
	for (auto iter = nodeData->allocations.begin(); iter != nodeData->allocations.end(); iter++) {
		NodeAllocation& other = *iter;
		if (&other == &myAllocation)
			continue;
		bool isCollision;
		if (other.acquireTime <= myAllocation.acquireTime)
			isCollision = other.releaseTime > myAllocation.acquireTime;
		else isCollision = myAllocation.releaseTime > other.acquireTime;
		if (isCollision) {
			if (other.acquireTime < minAcquireTime) {
				bestIter = iter;
				minAcquireTime = other.acquireTime;
				if (other.acquireTime < curTime)
					break;
			}
		}
	}

	if (bestIter != nodeData->allocations.end())
		return &(*bestIter);
	return nullptr;
}


void Traveler::removeAllocation(TravelerAllocations::iterator iter)
{
	NodeAllocationIterator inExtraData = *iter;
	allocations.erase(iter);
	navigator->getExtraData(inExtraData->cell)->removeAllocation(inExtraData);
}

void Traveler::cullExpiredAllocations()
{
	double curTime = time();
	while (allocations.size() > 1 && allocations[0]->releaseTime <= curTime)
		removeAllocation(allocations.begin());
}

void Traveler::clearAllocations()
{
	while (allocations.size() > 0)
		removeAllocation(allocations.begin());
}


void Traveler::clearAllocationsUpTo(TravelerAllocations::iterator iter)
{
	_ASSERTE(iter != allocations.end() - 1);
	int numToRemove = iter + 1 - allocations.begin();
	for (int i = 0; i < numToRemove; i++)
		removeAllocation(allocations.begin());
}

void Traveler::clearAllocations(TravelerAllocations::iterator fromPoint, bool decrementTraversalStats)
{
	_ASSERTE(fromPoint != allocations.begin());
	int numToRemove = allocations.end() - fromPoint;
	for (int i = 0; i < numToRemove; i++) {
		auto iter = allocations.end() - 1;
		if (decrementTraversalStats)
			navigator->getExtraData((*iter)->cell)->totalTraversals -= (*iter)->traversalWeight;
		removeAllocation(iter);
	}
}


Traveler::TravelerAllocations::iterator Traveler::find(NodeAllocation* alloc)
{
	return std::find_if(allocations.begin(), allocations.end(), [&](NodeAllocationIterator& iter) { return &(*iter) == alloc; });
}

void Traveler::onBlock(Traveler* collidingWith, int colliderPathIndex, AStarCell& cell)
{
	bool shouldStop = true;
	if (travelPath.size() <= colliderPathIndex)
		shouldStop = false;

	AStarNodeExtraData* nodeData = navigator->getExtraData(cell);
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
		blockTime = time();

		std::vector<Traveler*> deadlockList;

		allocations.back()->extendReleaseTime(DBL_MAX);
		NodeAllocation requestedAlloc(this, cell, colliderPathIndex, time(), DBL_MAX, 0.0);
		request = nodeData->addRequest(requestedAlloc, *foundAlloc, &deadlockList);
		isBlocked = true;
		if (request == nullptr) {
			navigateAroundDeadlock(deadlockList, requestedAlloc);
		}
	} else {
		navigatePath(colliderPathIndex - 1, false);
	}
}


bool Traveler::navigateAroundDeadlock(std::vector<Traveler*>& deadlockList, NodeAllocation& deadlockCreatingRequest)
{
	double curTime = time();
	double failedTargetDestinationPenaltyWeight = 3.0;
	double extraRouteEntriesPenaltyWeight = 1.0;
	AStarNode noTravelNode;
	noTravelNode.value = 0;

	std::vector<NavigationAttempt> attempts;

	auto applyTravelerAllocationsToBarrier = [&](Traveler* traveler, TemporaryBarrier& barrier) {
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
	};

	for (int i = 0; i < deadlockList.size(); i++) {
		Traveler* traveler = deadlockList[i];
		TemporaryBarrier barrier(navigator);
		for (Traveler* other : navigator->activeTravelers) {
			if (other == traveler || !other->isBlocked)
				continue;
			applyTravelerAllocationsToBarrier(other, barrier);
		}
		barrier.apply();
		TravelPath travelPath = navigator->calculateRoute(traveler->te->holder, destLoc, endSpeed, true);
		barrier.unapply();

		Vec2 diff(travelPath.back().cell.col - traveler->travelPath.back().cell.col, travelPath.back().cell.row - traveler->travelPath.back().cell.row);
		double penalty = failedTargetDestinationPenaltyWeight * sqrt(diff.x * diff.x + diff.y * diff.y);
		int originalRemainingSteps = traveler->travelPath.size() - traveler->allocations.back()->travelPathIndex;
		if (travelPath.size() > originalRemainingSteps)
			penalty += extraRouteEntriesPenaltyWeight * (travelPath.size() - originalRemainingSteps);

		attempts.push_back(NavigationAttempt());
		attempts.back().penalty = penalty;
		attempts.back().path = std::move(travelPath);
		attempts.back().traveler = traveler;
	}

	std::sort(attempts.begin(), attempts.end(), [](NavigationAttempt& left, NavigationAttempt& right) { return left.penalty < right.penalty; });

	bool didNavigateMe = false;
	Traveler* bestTraveler = nullptr;
	for (auto& attempt : attempts) {
		if (attempt.traveler == this)
			didNavigateMe = true;
		else if (attempt.traveler->request) {
			navigator->getExtraData(attempt.traveler->request->cell)->requests.remove_if([&](NodeAllocation& alloc) { return &alloc == attempt.traveler->request; });
			attempt.traveler->request = nullptr;
		}
		attempt.traveler->isNavigatingAroundDeadlock = true;
		attempt.traveler->navigatePath(std::move(attempt.path), false);
		attempt.traveler->isNavigatingAroundDeadlock = false;

		if (!attempt.traveler->blockEvent || attempt.traveler->blockEvent->time > time()) {
			bestTraveler = attempt.traveler;
			break;
		}
	}

	if (!didNavigateMe) {
		navigatePath(deadlockCreatingRequest.travelPathIndex - 1, false);
	}

	return bestTraveler && bestTraveler->travelPath.size() > 0;
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
	if (navigator->enableCollisionAvoidance) {
		if (allocations.size() > 1)
			clearAllocationsUpTo(allocations.end() - 2);
		allocations.front()->extendReleaseTime(DBL_MAX);
	}
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