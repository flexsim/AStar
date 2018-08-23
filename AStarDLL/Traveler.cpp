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
	bindNumber(destLoc.x);
	bindNumber(destLoc.y);
	bindNumber(destLoc.z);
	bindNumber(lastBlockTime);
	bindNumber(isNavigatingAroundDeadlock);
	bindNumber(blockedAtTravelPathIndex);
	bindNumber(nextCollisionUpdateTravelIndex);
	bindNumber(nextCollisionUpdateEndTime);
	bindNumber(needsContinueTrigger);
	destThreshold.bind(this, "destThreshold.");
	navigator = holder->ownerObject->objectAs(AStarNavigator);
	te = partner()->ownerObject->objectAs(TaskExecuter);

	bindStlContainer(travelPath);
	if (getBindMode() == SDT_BIND_ON_DISPLAY) {
		appendToDisplayStr("allocations:");
		for (auto alloc : allocations) {
			alloc->bind(nullptr);
		}

		appendToDisplayStr("\r\nrequest: ");
		if (request)
			request->bind(nullptr);
		appendToDisplayStr("\r\n:");
	}
	bindNumber(tinyTime);
	bindObjPtr(bridgeData.bridge);
	bindObjRef(bridgeData.arrivalEvent, 0);
	bindNumber(bridgeData.entryTime);
	bindNumber(bridgeData.pathIndex);
	bindObjPtr(bridgeData.prevTraveler);
	bindObjPtr(bridgeData.nextTraveler);

	bindNumber(turnSpeed);
	bindNumber(turnDelay);
	//bindNumber(estimatedIndefiniteAllocTimeDelay);
	//bindStlContainer(allocations);
}


void Traveler::bindEvents()
{
	bindEventByName("onBlock", onBlockTrigger, "OnBlock", EVENT_TYPE_TRIGGER);
	bindEventByName("onReroute", onRerouteTrigger, "OnReroute", EVENT_TYPE_TRIGGER);
	bindEventByName("onContinue", onContinueTrigger, "OnContinue", EVENT_TYPE_TRIGGER);
}

TreeNode* Traveler::getEventInfoObject(const char* eventTitle)
{
	return node(eventTitle, node("MAIN:/project/exec/globals/DefaultEventInfo/AStarTraveler"));
}

void Traveler::BlockEvent::bind()
{
	__super::bind();
	cell.bind(this);
	bindNumber(colliderPathIndex);
	bindNumber(intermediateAllocationIndex);
}

void Traveler::onReset()
{
	navigator = holder->ownerObject->objectAs(AStarNavigator);
	te = partner()->ownerObject->objectAs(TaskExecuter);
	holder->name = te->holder->name;
	isActive = false;
	isBlocked = false;
	lastBlockTime = 0;
	isNavigatingAroundDeadlock = false;
	blockedAtTravelPathIndex = -1;
	allocations.clear();
	request = nullptr;
	te->moveToResetPosition();
	Vec3 loc = te->getLocation(0.5, 0.5, 0.0);
	AStarCell resetCell = navigator->getCellFromLoc(Vec2(loc.x, loc.y));
	travelPath.clear();
	travelPath.push_back(AStarPathEntry(resetCell, -1));
	tinyTime = 0.001 * navigator->minNodeWidth / te->v_maxspeed;
	nextCollisionUpdateEndTime = 0.0;
	nextCollisionUpdateTravelIndex = -1;
	needsContinueTrigger = false;
	destThreshold = DestinationThreshold();
	destLoc = Vec3(0.0, 0.0, 0.0);
	destNode = nullptr;
	bridgeData.bridge = nullptr;
	routingAlgorithmSnapshots.clear();
}

void Traveler::onStartSimulation()
{XS
	if (navigator->enableCollisionAvoidance && !navigator->ignoreInactiveMemberCollisions) {
		Vec3 loc = te->getLocation(0.5, 0.5, 0.0);
		AStarCell resetCell = navigator->getCellFromLoc(Vec2(loc.x, loc.y));
		travelPath.clear();
		travelPath.push_back(AStarPathEntry(resetCell, -1));
		addAllocation(NodeAllocation(this, resetCell, 0, 0, 0.0, DBL_MAX, 1.0), true, false);
	}
XE}

void Traveler::navigatePath(int startAtPathIndex, bool isCollisionUpdateInterval)
{
	XS
	if (isRoutingNow)
		return;
	isRoutingNow = true;
	AStarNavigator* nav = navigator;
	nextCollisionUpdateTravelIndex = -1;

	if (needsContinueTrigger) {
		needsContinueTrigger = false;
		FIRE_SDT_EVENT(onContinueTrigger, te->holder);
	}

	// Don't know why this was here. I'm commenting it out.
	//if (!isDistQueryOnly) {
	//	coupling = tonode(get(first(te->node_v_navigator)));
	//	while (content(holder) < 1)
	//		nodeinsertinto(holder);
	//TreeNode* idList = first(coupling);
	// TODO: figure out idLists
	//}
	if (!isCollisionUpdateInterval) {
		// update TE state
		setstate(te->holder, content(te->holder) > 0 ? STATE_TRAVEL_LOADED : STATE_TRAVEL_EMPTY);
	}

	treenode kinematics = te->node_v_kinematics;
	double outputVector[3];
	Vec3 startLoc;
	bool isExitingBridge = bridgeData.bridge != nullptr;
	if (isExitingBridge)
		startLoc = te->getLocation(0.5, 0.5, 0);
	else {
		startLoc = nav->getLocFromCell(travelPath[startAtPathIndex].cell);
		if (up(te->holder) != model())
			startLoc = startLoc.project(model(), up(te->holder));
	}

	int kinFlags = 0;
	double endTime;
	double rotLerpSize = navigator->smoothRotations;
	double rotLerpSpeed = 90 / (te->b_spatialsx * rotLerpSize / te->v_maxspeed);
	double lastRotation;
	if (!isCollisionUpdateInterval) {
		lastRotation = te->b_spatialrz;
		endTime = time();
		if (objectexists(te->node_v_modifyrotation) && te->node_v_modifyrotation->value) {

			if (rotLerpSize == 0 && !nav->stopForTurns)
				kinFlags |= KINEMATIC_MANAGE_ROTATIONS;

			if (!te->canRotateOnIncline())
				kinFlags |= KINEMATIC_NO_INCLINE_ROTATION;
		} else {
			rotLerpSize = 0;
		}
		initkinematics(kinematics, startLoc.x, startLoc.y, te->b_spatialz, 0, 0, te->b_spatialrz, kinFlags, 0);
	} else {
		endTime = nextCollisionUpdateEndTime;
		if (endTime > nav->nextCollisionUpdateTime) {
			isRoutingNow = false;
			return;
		}
		lastRotation = getkinematics(kinematics, KINEMATIC_RZ, 0, FLT_MAX);
	}

	AStarPathEntry e, laste;
	int numNodes = travelPath.size();
	laste = travelPath[startAtPathIndex];
	bool enableCollisionAvoidance = nav->enableCollisionAvoidance;

	clearAllocationsExcept(laste.cell);

	int initialAllocsSize = allocations.size();
	if (enableCollisionAvoidance && (!nav->ignoreInactiveMemberCollisions || isBlocked || isContinuingFromDeadlock)) {
		for (auto& allocation : allocations) {
			allocation->extendReleaseTime(DBL_MAX);
			allocation->isMarkedForDeletion = true;
		}
	}


	isBlocked = false;
	isContinuingFromDeadlock = false;
	blockedAtTravelPathIndex = -1;

	int didBlockPathIndex = -1;
	NodeAllocation* lastAllocation = nullptr;
	Bridge* bridgeArrival = nullptr;

	double containerRot = 0;
	if (te->holder->up != model()) {
		treenode obj = te->holder;
		while (obj != model()) {
			obj = obj->findOwnerObject();
			containerRot += zrot(obj);			
		}
	}
	int i;
	double deallocTimeOffset = nav->deallocTimeOffset;
	double firstCellDeallocTime = time() + deallocTimeOffset;
	Grid* grid = nullptr;
	int lastGridNum = -1;
	for (i = startAtPathIndex + 1; i < numNodes; i++) {
		e = travelPath[i];
		if (e.cell.grid != lastGridNum) {
			lastGridNum = e.cell.grid;
			grid = navigator->getGrid(e.cell);
		}
		AllocationStep step(laste.cell, e.cell);
		double totalTravelDist;
		bridgeArrival = nullptr;

		if (laste.bridgeIndex != -1) {
			AStarNodeExtraData* nodeData = nav->getExtraData(laste.cell);
			AStarNodeExtraData::BridgeEntry& entry = nodeData->bridges[laste.bridgeIndex];
			Bridge* bridge = entry.bridge;
			if (bridgeData.bridge != bridge) {
				bridgeArrival = bridge;
			}
		}

		if (!bridgeArrival) {
			int numSuccessfulAllocations = 0;
			Vec3 diff;
			double startTime = endTime;
			if (!isExitingBridge) {
				diff.x = (e.cell.col - laste.cell.col) * grid->nodeWidth;
				diff.y = (e.cell.row - laste.cell.row) * grid->nodeWidth;
				diff.z = 0;
				if(containerRot)
					diff.rotateXY(-containerRot);
			}
			else {
				Vec3 toLoc = nav->getLocFromCell(e.cell);
				step.isDiagonal = false;
				step.isHorizontalDeepSearch = false;
				step.isVerticalDeepSearch = false;
				diff = toLoc - startLoc;
				isExitingBridge = false;
			}

			if (rotLerpSize != 0 || nav->stopForTurns) {
				double nextRot = radianstodegrees(atan2(diff.y, diff.x));
				double rotDiff = nextRot - lastRotation;
				while (rotDiff > 180)
					rotDiff -= 360;
				while (rotDiff < -180)
					rotDiff += 360;

				if (nav->stopForTurns) {
					if (fabs(rotDiff) > 0.1) {
						startTime = addkinematic(kinematics, 0, 0, rotDiff, turnSpeed, 0, 0, 0, 0, startTime + 0.5 * turnDelay, KINEMATIC_ROTATE) + 0.5 * turnDelay;
						if (lastAllocation)
							lastAllocation->extendReleaseTime(startTime + deallocTimeOffset);
						if (i == startAtPathIndex + 1)
							firstCellDeallocTime = startTime + deallocTimeOffset;
					}
				} else {
					double timeToRot = fabs(rotDiff) / rotLerpSpeed;
					double rotStartTime = max(time(), startTime - 0.5 * timeToRot);
					addkinematic(kinematics, 0, 0, rotDiff, rotLerpSpeed, 0, 0, 0, 0, rotStartTime, KINEMATIC_ROTATE);
				}
				lastRotation = nextRot;
			}

			endTime = addkinematic(kinematics, diff.x, diff.y, diff.z,
				te->v_maxspeed, 0, 0, 0, 0, startTime, KINEMATIC_TRAVEL);

			if (enableCollisionAvoidance) {
				double middleReleaseTime = 0.5 * (startTime + endTime);
				NodeAllocation allocation(this, e.cell, i, 0, startTime, middleReleaseTime + deallocTimeOffset, 1.0);
				bool success = true;
				NodeAllocation* intermediate1 = nullptr;
				NodeAllocation* intermediate2 = nullptr;
				// if it is a diagonal move, then I need to do additional allocations
				if (step.isDiagonal) {
					// is it a deep vertical search step
					allocation.traversalWeight = (step.isVerticalDeepSearch || step.isHorizontalDeepSearch) ? 0.5 : 0.0;
					allocation.cell = step.intermediateCell1;
					intermediate1 = addAllocation(allocation, false, true);
					success = intermediate1 != nullptr;
					allocation.intermediateAllocationIndex++;
					if (intermediate1) {
						numSuccessfulAllocations++;
						allocation.cell = step.intermediateCell2;
						intermediate2 = addAllocation(allocation, false, true);
						success = intermediate2 != nullptr;
						allocation.intermediateAllocationIndex++;
						numSuccessfulAllocations += success ? 1 : 0;
					}
				}
				if (success) {
					allocation.cell = e.cell;
					allocation.releaseTime = std::nextafter(endTime + deallocTimeOffset, DBL_MAX);
					lastAllocation = addAllocation(allocation, false, true);
					success = lastAllocation != nullptr;
				}
				if (!success) {
					if (lastAllocation)
						lastAllocation->extendReleaseTime(DBL_MAX);
					if (intermediate1)
						intermediate1->extendReleaseTime(DBL_MAX);
					if (intermediate2)
						intermediate2->extendReleaseTime(DBL_MAX);
					didBlockPathIndex = i;
					break;
				}
			}
			totalTravelDist = diff.magnitude;
		}
		else {
			// travel onto a bridge
			Bridge* bridge = bridgeArrival;
			totalTravelDist = 0;

			// Create a BridgeArrivalEvent
			if (bridgeData.arrivalEvent)
				destroyevent(bridgeData.arrivalEvent->holder);
			bridgeData.arrivalEvent = createevent(new Bridge::ArrivalEvent(bridge, this, i - 1, endTime))->objectAs(Bridge::ArrivalEvent);
			didBlockPathIndex = i;
			break;
		}

		te->v_totaltraveldist += totalTravelDist;

		//Traffic info
		nav->assertExtraData(e.cell)->totalTraversals++;
		nav->heatMapTotalTraversals++;
		if (step.isVerticalDeepSearch || step.isHorizontalDeepSearch) {
			nav->assertExtraData(step.intermediateCell1)->totalTraversals += 0.5;
			nav->assertExtraData(step.intermediateCell2)->totalTraversals += 0.5;
			nav->heatMapTotalTraversals++;
		}

		if (enableCollisionAvoidance && endTime > nav->nextCollisionUpdateTime) {
			nextCollisionUpdateTravelIndex = i;
			nextCollisionUpdateEndTime = endTime;
			break;
		}

		laste = e;
	}

	// remove the original allocations and get off the bridge if I was able to allocate ahead at least one
	// This will trigger other travelers who might be waiting for me to move on 
	// from the current point I'm at.
	if (numNodes > startAtPathIndex + 1 && !isCollisionUpdateInterval && (didBlockPathIndex == -1 || didBlockPathIndex > startAtPathIndex + 1)) {
		if (bridgeData.bridge)
			bridgeData.bridge->onExit(this);

		if (enableCollisionAvoidance && initialAllocsSize > 0) {
			for (int i = initialAllocsSize - 1; i >= 0; i--) {
				if (allocations[i]->isMarkedForDeletion) {
					if (firstCellDeallocTime == time())
						removeAllocation(allocations.begin() + i);
					else allocations[i]->truncateReleaseTime(firstCellDeallocTime);
				}
			}
		}
	}

	if (!isActive) {
		nav->activeTravelers.push_front(this);
		isActive = true;
		activeEntry = nav->activeTravelers.begin();
	}
	if (didBlockPathIndex == -1 && !blockEvent && !isBlocked && i == numNodes)
		arrivalEvent = createevent(new ArrivalEvent(this, endTime))->objectAs(ArrivalEvent);

	isRoutingNow = false;
	_ASSERTE(allocations.size() > 0 || !enableCollisionAvoidance || navigator->ignoreInactiveMemberCollisions || bridgeArrival || bridgeData.bridge);
	XE
}

void Traveler::onBridgeArrival(Bridge* bridge, int pathIndex) 
{
	XS
	if (isBlocked)
		return;

	AStarPathEntry e = travelPath[pathIndex];
	AStarNodeExtraData::BridgeEntry& entry = navigator->getExtraData(e.cell)->bridges[e.bridgeIndex];

	updateLocation();
	bridgeData = BridgeData(bridge, DBL_MAX, pathIndex, te->b_spatialz);

	if (bridge->isAvailable) {
		// move onto bridge
		clearAllocations();
		bridge->onEntry(this, pathIndex);
	}
	else {
		if (allocations.size() > 0)
			allocations.back()->extendReleaseTime(DBL_MAX);
		_ASSERTE(bridge->blockedTraveler == nullptr);
		// Traveler is blocked trying to get on the bridge
		bridge->blockedTraveler = this;
		bridge->blockedPathIndex = pathIndex;
	}
	XE
}

NodeAllocation* Traveler::addAllocation(NodeAllocation& allocation, bool force, bool notifyPendingAllocations)
{
	XS
	AStarNodeExtraData* nodeData = navigator->assertExtraData(allocation.cell);

	if (!force || notifyPendingAllocations) {
		NodeAllocation* collideWith = findCollision(nodeData, allocation, false);
		if (collideWith) {
			if (collideWith->traveler == this) {
				double oldReleaseTime = collideWith->releaseTime;
				*collideWith = allocation;
				if (allocation.releaseTime > collideWith->releaseTime) {
					collideWith->releaseTime = oldReleaseTime;
					collideWith->extendReleaseTime(allocation.releaseTime);
				} else if (nodeData->requests.size() > 0) {
					nodeData->checkCreateContinueEvent();
				}
				collideWith->isMarkedForDeletion = false;

				auto iter = find(collideWith);
				NodeAllocationIterator val = *iter;
				allocations.erase(iter);
				allocations.push_back(val);
				return collideWith;
			}
			NodeAllocation* laterAllocation = (allocation.acquireTime < collideWith->acquireTime || force) ? collideWith : &allocation;
			Traveler* laterTraveler = laterAllocation->traveler;
			NodeAllocation* earlierAllocation = laterAllocation == collideWith ? &allocation : collideWith;
			Traveler* earlierTraveler = earlierAllocation->traveler;

			double eventTime = laterAllocation->acquireTime;
			BlockEvent* event = new BlockEvent(laterTraveler, laterAllocation->travelPathIndex, laterAllocation->intermediateAllocationIndex,
				earlierTraveler, allocation.cell, max(time(), eventTime));

			// check to see if I need to create a block event for the later traveler
			if (!laterTraveler->blockEvent || *(event) < *(laterTraveler->blockEvent)) {
				if (!laterTraveler->isBlocked) {
					if (laterTraveler->blockEvent)
						destroyevent(laterTraveler->blockEvent->holder);
					laterTraveler->blockEvent = createevent(event)->objectAs(BlockEvent);

					if (laterTraveler->bridgeData.arrivalEvent)
						destroyevent(laterTraveler->bridgeData.arrivalEvent->holder);
				}

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
				}
				else
					return nullptr;
			}
			else {
				delete event;
			}
		}
	}

	nodeData->allocations.push_front(allocation);
	allocations.push_back(nodeData->allocations.begin());

	return &(nodeData->allocations.front());
	XE
}


NodeAllocation* Traveler::findCollision(AStarNodeExtraData* nodeData, const NodeAllocation& myAllocation, bool ignoreSameTravelerAllocs)
{
	XS
	NodeAllocationIterator bestIter = nodeData->allocations.end();
	double minAcquireTime = DBL_MAX;
	double curTime = time();


	for (auto iter = nodeData->allocations.begin(); iter != nodeData->allocations.end(); iter++) {
		NodeAllocation& other = *iter;
		if (&other == &myAllocation)
			continue;
		if (ignoreSameTravelerAllocs && other.traveler == myAllocation.traveler)
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
	XE
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

void Traveler::clearAllocationsExcept(const AStarCell & cell)
{
	double curTime = time();
	while (allocations.size() > 0 && allocations[0]->cell != cell)
		removeAllocation(allocations.begin());
	while (allocations.size() > 1)
		removeAllocation(allocations.begin() + (allocations.size() - 1));
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

void Traveler::clearAllocations(TravelerAllocations::iterator fromPoint, bool decrementTraversalStats)
{
	int numToRemove = allocations.end() - fromPoint;
	for (int i = 0; i < numToRemove; i++) {
		auto iter = allocations.end() - 1;
		if (decrementTraversalStats) {
			double weight = (*iter)->traversalWeight;
			navigator->getExtraData((*iter)->cell)->totalTraversals -= weight;
			navigator->heatMapTotalTraversals -= weight;
		}
		removeAllocation(iter);
	}
}


Traveler::TravelerAllocations::iterator Traveler::find(NodeAllocation* alloc)
{
	return std::find_if(allocations.begin(), allocations.end(), [&](NodeAllocationIterator& iter) { return &(*iter) == alloc; });
}

void Traveler::onBlock(Traveler* collidingWith, int atPathIndex, AStarCell& cell)
{
	cullExpiredAllocations();
	bool shouldStop = true;
	if (travelPath.size() <= atPathIndex)
		shouldStop = false;

	AStarNodeExtraData* nodeData = navigator->getExtraData(cell);
	double curTime = time();
	auto foundAlloc = std::find_if(nodeData->allocations.begin(), nodeData->allocations.end(),
		[&](NodeAllocation& alloc) { return alloc.traveler == collidingWith && alloc.acquireTime <= curTime && alloc.releaseTime > curTime; }
		);
	
	if (shouldStop && foundAlloc == nodeData->allocations.end())
		shouldStop = false;

	updateLocation();
	if (shouldStop) {
		Vec3 pos = te->getLocation(0.5, 0.5, 0.0);
		initkinematics(te->node_v_kinematics, pos.x, pos.y, te->b_spatialz, 0.0, 0.0, 0.0, 1, 0);

		setstate(te->holder, STATE_BLOCKED);
		lastBlockTime = curTime;

		std::vector<Traveler*> deadlockList;
		for (auto& allocation : allocations)
			allocation->extendReleaseTime(DBL_MAX);
		NodeAllocation requestedAlloc(this, cell, atPathIndex, 0, curTime, DBL_MAX, 0.0);
		request = nodeData->addRequest(requestedAlloc, *foundAlloc, &deadlockList);
		bool isDeadlock = deadlockList.size() > 0;
		if (onBlockTrigger && (!nodeData->continueEvent || nodeData->continueEvent->time - curTime > tinyTime)) {
			FIRE_SDT_EVENT(onBlockTrigger, te->holder, isDeadlock);
			needsContinueTrigger = true;
		}
		isBlocked = true;
		blockedAtTravelPathIndex = atPathIndex;
		if (isDeadlock) {
			blockEvent = nullptr;
			navigateAroundDeadlock(deadlockList, requestedAlloc);
		}
	} else {
		navigatePath(atPathIndex - 1);
	}
}


bool Traveler::navigateAroundDeadlock(std::vector<Traveler*>& deadlockList, NodeAllocation& deadlockCreatingRequest)
{
	double curTime = time();

	AStarCell bestCell, bestAlternateCell;
	Traveler* bestTraveler = nullptr, * bestAlternateTraveler = nullptr;

	for (int i = 0; i <= deadlockList.size() && !bestTraveler; i++) {
		Traveler* traveler = (i == 0 ? this : deadlockList[i - 1]);
		if (traveler == this && i > 0)
			continue;

		AStarCell curCell = traveler->travelPath[traveler->blockedAtTravelPathIndex - 1].cell;

		AStarCell blockingCell = traveler->request->cell;
		AStarNodeExtraData* extra = navigator->getExtraData(blockingCell);
		auto found = std::find_if(extra->allocations.begin(), extra->allocations.end(),
			[&](NodeAllocation& alloc) -> bool {return alloc.acquireTime <= curTime && alloc.releaseTime >= curTime; });
		Traveler* blockingTraveler = found->traveler;

		struct ShimmyInfo {
			AStarCell cell;
			bool isValid = true;
			ShimmyInfo(unsigned int grid, unsigned short col, unsigned short row, bool isValid) : cell(grid, col, row), isValid(isValid) {}
			ShimmyInfo() {}
		};
		AStarNode* curNode = navigator->getNode(curCell);
		ShimmyInfo leftCell(curCell.grid, curCell.col - 1, curCell.row, curNode->canGoLeft);
		ShimmyInfo rightCell(curCell.grid, curCell.col + 1, curCell.row, curNode->canGoRight);
		ShimmyInfo upCell(curCell.grid, curCell.col, curCell.row + 1, curNode->canGoUp);
		ShimmyInfo downCell(curCell.grid, curCell.col, curCell.row - 1, curNode->canGoDown);

		ShimmyInfo check[4];
		if (blockingCell.col > curCell.col) {
			check[0] = downCell;
			check[1] = upCell;
			check[2] = leftCell;
			check[3] = rightCell;
		} else if (blockingCell.col < curCell.col) {
			check[0] = upCell;
			check[1] = downCell;
			check[2] = rightCell;
			check[3] = leftCell;
		} else if (blockingCell.row > curCell.row) {
			check[0] = rightCell;
			check[1] = leftCell;
			check[2] = downCell;
			check[3] = upCell;
		} else {
			check[0] = leftCell;
			check[1] = rightCell;
			check[2] = upCell;
			check[3] = downCell;
		}

		Grid* grid = navigator->getGrid(check[i].cell);

		for (int i = 0; i < 4; i++) {
			if (!check[i].isValid || check[i].cell.col >= grid->numCols || check[i].cell.row >= grid->numRows)
				continue;

			AStarNodeExtraData* extra = navigator->getExtraData(check[i].cell);
			if (extra) {
				auto found = std::find_if(extra->allocations.begin(), extra->allocations.end(),
					[&](NodeAllocation& alloc) -> bool {return alloc.acquireTime <= curTime && alloc.releaseTime >= curTime && alloc.traveler != traveler; });
				if (found == extra->allocations.end()) {
					if (!bestAlternateTraveler) {
						bestAlternateCell = check[i].cell;
						bestAlternateTraveler = traveler;
					}
					if (blockingTraveler->blockedAtTravelPathIndex >= blockingTraveler->travelPath.size() - 1
						|| blockingTraveler->travelPath[blockingTraveler->blockedAtTravelPathIndex + 1].cell != check[i].cell)
					{
						bestCell = check[i].cell;
						bestTraveler = traveler;
						break;
					}
				}
			} else {
				bestCell = check[i].cell;
				bestTraveler = traveler;
				break;
			}
		}
	}

	if (!bestTraveler) {
		bestTraveler = bestAlternateTraveler;
		bestCell = bestAlternateCell;
	}

	if (bestTraveler) {
		navigator->getExtraData(bestTraveler->request->cell)->requests.remove_if([&](NodeAllocation& alloc) { return &alloc == bestTraveler->request; });
		bestTraveler->request = nullptr;
		FIRE_SDT_EVENT(bestTraveler->onRerouteTrigger, te->holder);
		AStarCell curCell = bestTraveler->travelPath[bestTraveler->blockedAtTravelPathIndex - 1].cell;
		TravelPath newPath;
		newPath.push_back(AStarPathEntry(curCell, -1));
		newPath.push_back(AStarPathEntry(bestCell, -1));
		while (bestTraveler->allocations.size() > 1 && bestTraveler->allocations.front()->cell != curCell)
			bestTraveler->removeAllocation(bestTraveler->allocations.begin());
		while (bestTraveler->allocations.size() > 1)
			bestTraveler->removeAllocation(bestTraveler->allocations.end() - 1);
		bestTraveler->isNavigatingAroundDeadlock = true;
		bestTraveler->navigatePath(std::move(newPath));
	} else {
		string error = "Unrecoverable deadlock encountered for ";
		error.append(holder->name.c_str()).append(". Model stopped");
		EX(error.c_str(), "", 1);
		stop();
	}

	return true;
}

bool Traveler::findDeadlockCycle(Traveler* start, std::vector<Traveler*>& travelers)
{
	travelers.push_back(this);
	size_t startSize = travelers.size();
	double curTime = time();
	for (NodeAllocationIterator& allocIter : allocations) {
		NodeAllocation& alloc = *allocIter;
		if (alloc.acquireTime > curTime)
			break;
		else if (alloc.releaseTime <= curTime)
			continue;
		AStarNodeExtraData* data = navigator->getExtraData(alloc.cell);
		if (data->findDeadlockCycle(start, travelers))
			return true;
	}
	travelers.pop_back();
	return false;
}

void Traveler::onTEDestroyed()
{
	if (!navigator->enableCollisionAvoidance)
		return;
	if (blockEvent)
		destroyevent(blockEvent);
	if (arrivalEvent)
		destroyevent(arrivalEvent);
	clearAllocations();
}

void Traveler::onArrival()
{
	arrivalEvent = nullptr;
	TreeNode* kinematics = te->node_v_kinematics;
	updatekinematics(kinematics, te->holder, time());
	te->b_spatialx -= 0.5*te->b_spatialsx;
	te->b_spatialy += 0.5*te->b_spatialsy;
	if (!isNavigatingAroundDeadlock) {
		navigator->activeTravelers.erase(activeEntry);
		isActive = false;
		AStarPathEntry back = travelPath.back();
		travelPath.clear();
		travelPath.push_back(back);
		if (navigator->enableCollisionAvoidance) {
			if (navigator->ignoreInactiveMemberCollisions)
				clearAllocations();
			else {
				if (allocations.size() > 1)
					clearAllocationsUpTo(allocations.end() - 2);
				allocations.front()->extendReleaseTime(DBL_MAX);
			}
		}
		te->onDestinationArrival(te->v_maxspeed);
	} else {
		if (allocations.size() > 1)
			clearAllocationsUpTo(allocations.end() - 2);
		allocations.front()->extendReleaseTime(DBL_MAX);
		isNavigatingAroundDeadlock = false;
		isContinuingFromDeadlock = true; 
		travelPath = navigator->calculateRoute(this, destLoc, destThreshold, endSpeed, false);
		navigatePath(0);
	}
}

void Traveler::abortTravel(TreeNode* newTS)
{
	updateLocation();

	if (navigator->enableCollisionAvoidance) {
		if (request) {
			navigator->getExtraData(request->cell)->requests.remove_if([&](NodeAllocation& alloc) { return &alloc == request; });
			request = nullptr;
		}
		if (blockEvent)
			destroyevent(blockEvent->holder);
		if (navigator->ignoreInactiveMemberCollisions)
			clearAllocations();
		else {
			cullExpiredAllocations();
			Vec3 loc = te->getLocation(0.5, 0.5, 0.0);
			if (te->holder->up != model())
				loc = loc.project(te->holder->up, model());
			AStarCell cell = navigator->getCellFromLoc(Vec2(loc.x, loc.y));
			while (allocations.size() > 1 && allocations.back()->acquireTime > time())
				clearAllocations(allocations.end() - 1);

			for (int i = allocations.size() - 1; i >= 0; i--) {
				if (allocations[i]->cell != cell)
					removeAllocation(allocations.begin() + i);
				else allocations[i]->extendReleaseTime(DBL_MAX);
			}
			if (allocations.size() == 0) {
				addAllocation(NodeAllocation(this, cell, 0, 0, time(), DBL_MAX, 0.0), true, true);
			}
		}
	}

	if (arrivalEvent)
		destroyevent(arrivalEvent->holder);

	navigator->activeTravelers.erase(activeEntry);
	isActive = false;
}

void Traveler::updateLocation()
{
	if (!isActive)
		return;

	double updateTime = time();

	if (bridgeData.bridge && bridgeData.entryTime <= updateTime) {
		bridgeData.bridge->updateLocations();
	} else {
		TreeNode* kinematics = te->node_v_kinematics;
		updatekinematics(kinematics, te->holder, updateTime);
		te->b_spatialx -= 0.5*te->b_spatialsx;
		te->b_spatialy += 0.5*te->b_spatialsy;
	}
}

}