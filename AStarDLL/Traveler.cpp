#include "Traveler.h"
#include "AStarNavigator.h"
#include "Bridge.h"
#include "macros.h"

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
	bindSubNodeByName("bridgeData", bridgeDataNode, 0);
	bridgeData = bridgeDataNode->objectAs(TravelerBridgeData);

	bindNumber(turnSpeed);
	bindNumber(turnDelay);

	bindDouble(useMandatoryPath, 1);
	bindObjRef(bridgeEvent, 0);
	//bindNumber(estimatedIndefiniteAllocTimeDelay);
	//bindStlContainer(allocations);
}


void Traveler::bindEvents()
{
	bindEventByName("onBlock", onBlockTrigger, "OnBlock", EVENT_TYPE_TRIGGER);
	bindEventByName("onReroute", onRerouteTrigger, "OnReroute", EVENT_TYPE_TRIGGER);
	bindEventByName("onContinue", onContinueTrigger, "OnContinue", EVENT_TYPE_TRIGGER);
	bindEventByName("onBridgeArrival", onBridgeArrivalTrigger, "OnBridgeArrival", EVENT_TYPE_TRIGGER);
	bindEventByName("onBridgeContinue", onBridgeContinueTrigger, "OnBridgeContinue", EVENT_TYPE_TRIGGER);

	bindRelayedClassEvents<TravelerBridgeData>("", 0, &Traveler::resolveBridgeData, bridgeData);
}


TreeNode* Traveler::resolveBridgeData()
{
	// this method is going to be called as a method on the TE
	// so this is actually a pointer to a TaskExecuter
	TaskExecuter* te = (TaskExecuter*)(void*)this;
	Traveler* traveler;
	if (te->holder->dataType == DATATYPE_OBJECT)
		traveler = AStarNavigator::getTraveler(te);
	else traveler = (Traveler*)(void*)te;

	if (!traveler->bridgeData)
		traveler->assertBridgeData(nullptr);
	return traveler->bridgeData->holder;
}


TravelPath& Traveler::__getTravelPath()
{
	return travelPath;
}

void Traveler::bindInterface()
{
	bindDocumentationXMLPath("help\\FlexScriptAPIReference\\AStar\\AStar.Traveler.xml");
	bindConstructor(&AStarNavigator::getTraveler, "AStar.Traveler Traveler(TaskExecuter te)");
	SimpleDataType::bindTypedPropertyByName<TravelPath>("travelPath", "AStar.TravelPath&", force_cast<void*>(&Traveler::__getTravelPath), nullptr);
	bindMethod(getAllocations, Traveler, "AStar.AllocationRange getAllocations(double time = -1)");
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

AllocationRange Traveler::getAllocations(double atTime)
{
	if (atTime < 0) 
		atTime = time();
	for (int i = 0; i < allocations.size(); i++) {
		if (allocations[i]->acquireTime <= atTime && allocations[i]->releaseTime > atTime) {
			int j = i + 1;
			while (j < allocations.size() && allocations[j]->acquireTime <= atTime)
				j++;
			return AllocationRange(this, i, j - i);
		}
	}
	return AllocationRange();
}

void Traveler::onReset()
{
	navigator = holder->ownerObject->objectAs(AStarNavigator);
	te = partner()->ownerObject->objectAs(TaskExecuter);
	holder->name = te->holder->name;
	isActive = false;
	isBlocked = false;
	lastBlockTime = 0;
	expectedtotaltraveldist = 0;
	isNavigatingAroundDeadlock = false;
	blockedAtTravelPathIndex = -1;
	allocations.clear();
	request = nullptr;
	te->moveToResetPosition();
	Vec3 loc = te->getLocation(0.5, 0.5, 0.0);
	Cell resetCell = navigator->getCell(loc);

	if (useMandatoryPath) {
		Grid* grid = navigator->getGrid(resetCell);
		Cell originalResetCell = resetCell;
		grid->visitCellsWidening(resetCell, [&](const Cell& cell) -> bool {
			AStarNode* node = navigator->getNode(cell);
			if (node->isOnMandatoryPath) {
				resetCell = cell;
				return false;
			}
			return true;
		});
		if (originalResetCell != resetCell) {
			te->setLocation(grid->getLocation(resetCell), Vec3(0.5, 0.5, 0.0));
		}
	}

	travelPath.clear();
	travelPath.push_back(AStarPathEntry(resetCell, -1));
	tinyTime = 0.001 * navigator->minNodeSize.x / te->v_maxspeed;
	nextCollisionUpdateEndTime = 0.0;
	nextCollisionUpdateTravelIndex = -1;
	needsContinueTrigger = false;
	destThreshold = DestinationThreshold();
	destLoc = Vec3(0.0, 0.0, 0.0);
	destNode = nullptr;
	if (bridgeData)
		bridgeData->routingData = nullptr;
	routingAlgorithmSnapshots.clear();
	cachedPathKey.barrierConditions.resize(navigator->barrierConditions.size());
	isCachedPathKeyValid = false;
}

void Traveler::onStartSimulation()
{XS
	if (navigator->enableCollisionAvoidance && !navigator->ignoreInactiveMemberCollisions) {
		Vec3 loc = te->getLocation(0.5, 0.5, 0.0);
		Cell resetCell = navigator->getCell(loc);
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
	BridgeRoutingData* exitingBridgeRoutingData = (bridgeData ? bridgeData->routingData : nullptr);
	bool isExitingBridge = exitingBridgeRoutingData != nullptr;
	if (isExitingBridge)
		startLoc = te->getLocation(0.5, 0.5, 0);
	else {
		startLoc = nav->getLocation(travelPath[startAtPathIndex].cell);
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
		}
		else {
			rotLerpSize = 0;
		}
		initkinematics(kinematics, startLoc.x, startLoc.y, te->b_spatialz, 0, 0, te->b_spatialrz, kinFlags, 0);
	}
	else {
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
	BridgeRoutingData* bridgeArrival = nullptr;

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
			BridgeRoutingData* data = nodeData->bridges[laste.bridgeIndex];
			if (!bridgeData || bridgeData->routingData != data) {
				bridgeArrival = data;
			}
		}

		if (!bridgeArrival) {
			int numSuccessfulAllocations = 0;
			Vec3 diff;
			double startTime = endTime;
			if (!isExitingBridge) {
				diff.x = (e.cell.col - laste.cell.col) * grid->nodeSize.x;
				diff.y = (e.cell.row - laste.cell.row) * grid->nodeSize.y;
				diff.z = 0;
				if (containerRot)
					diff.rotateXY(-containerRot);
			}
			else {
				Vec3 toLoc = nav->getLocation(e.cell).project(model(), up(te->holder));
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
				}
				else {
					double timeToRot = fabs(rotDiff) / rotLerpSpeed;
					double rotStartTime = std::max(time(), startTime - 0.5 * timeToRot);
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
			totalTravelDist = 0;
			didBlockPathIndex = i;
			break;
		}
		expectedtotaltraveldist += totalTravelDist;
		//te->v_totaltraveldist += totalTravelDist;

		//Traffic info
		nav->assertExtraData(e.cell, TraversalData)->totalTraversals++;
		nav->heatMapTotalTraversals++;
		if (step.isVerticalDeepSearch || step.isHorizontalDeepSearch) {
			nav->assertExtraData(step.intermediateCell1, TraversalData)->totalTraversals += 0.5;
			nav->assertExtraData(step.intermediateCell2, TraversalData)->totalTraversals += 0.5;
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
		if (exitingBridgeRoutingData) {
			if (bridgeData->routingData == exitingBridgeRoutingData)
				bridgeData->routingData = nullptr;
			exitingBridgeRoutingData->onExit(this);
		}

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

	if (bridgeArrival) {
		// Create a BridgeArrivalEvent
		if (bridgeEvent)
			destroyevent(bridgeEvent->holder);
		assertBridgeData(bridgeArrival);
		bridgeEvent = createevent(new BridgeRoutingData::ArrivalEvent(bridgeArrival, this, i - 1, endTime))->objectAs(BridgeRoutingData::ArrivalEvent);
	}

	if (!isActive) {
		nav->activeTravelers.push_front(this);
		isActive = true;
		activeEntry = nav->activeTravelers.begin();
	}
	if (didBlockPathIndex == -1 && !blockEvent && !isBlocked && i == numNodes)
		arrivalEvent = createevent(new ArrivalEvent(this, endTime))->objectAs(ArrivalEvent);

	isRoutingNow = false;
#ifdef _WINDOWS
	_ASSERTE(allocations.size() > 0 || !enableCollisionAvoidance || navigator->ignoreInactiveMemberCollisions || bridgeArrival || (bridgeData && bridgeData->routingData));
#endif
	XE
}


void Traveler::navigatePath(TravelPath&& path)
{
	travelPath = std::move(path);
	navigatePath(0);
}

void Traveler::onBridgeArrival(int pathIndex)
{
	auto& pathEntry = travelPath[pathIndex];
	if (pathEntry.bridgeIndex != -1) {
		AStarNodeExtraData* nodeData = navigator->getExtraData(pathEntry.cell);
		BridgeRoutingData* data = nodeData->bridges[pathEntry.bridgeIndex];
		onBridgeArrival(data, pathIndex);
	}
}

void Traveler::onBridgeArrival(BridgeRoutingData* data, int pathIndex)
{
	XS
	if (isBlocked)
		return;

	AStarPathEntry e = travelPath[pathIndex];

	updateLocation();
	assertBridgeData(data);
	FIRE_SDT_EVENT(onBridgeArrivalTrigger, te->holder, bridgeData->routingData->bridge->holder);
	bridgeData->routingData = data;
	bridgeData->spatialz = te->location.z;
	bridgeData->pathIndex = pathIndex;

	data->onBridgeArrival(this, pathIndex);
	XE
}

void Traveler::onBridgeComplete(int atPathIndex)
{
	TaskExecuter* te = this->te;
	Bridge* bridge = bridgeData->routingData->bridge;
	// With Agent systems, the navigator isn't the A* navigator, so I shouldn't continue navigating 
	// the path
	bool isAStarNavigator = ownerobject(te->node_v_navigator->first->value) == navigator->holder;
	if (!isAStarNavigator)
		// temporary fix. In reality there should be some travel time for the agent to get out of the way
		bridgeData->routingData->onExit(this);
	FIRE_SDT_EVENT(onBridgeContinueTrigger, te->holder, bridge ? (Variant)bridge->holder : Variant());
	if (isAStarNavigator)
		navigatePath(atPathIndex);

}

NodeAllocation* Traveler::addAllocation(NodeAllocation& allocation, bool force, bool notifyPendingAllocations)
{
	XS
	AStarNodeExtraData* nodeData = navigator->assertExtraData(allocation.cell, AllocationData);

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
				earlierTraveler, allocation.cell, std::max(time(), eventTime));

			// check to see if I need to create a block event for the later traveler
			if (!laterTraveler->blockEvent || *(event) < *(laterTraveler->blockEvent)) {
				if (!laterTraveler->isBlocked) {
					if (laterTraveler->blockEvent)
						destroyevent(laterTraveler->blockEvent->holder);
					laterTraveler->blockEvent = createevent(event)->objectAs(BlockEvent);

					if (laterTraveler->bridgeEvent)
						destroyevent(laterTraveler->bridgeEvent->holder);
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

NodeAllocation* Traveler::addAllocation(NodeAllocation&& allocation, bool force, bool notifyPendingAllocations)
{
	return addAllocation(allocation, force, notifyPendingAllocations);
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

void Traveler::clearAllocationsExcept(const Cell & cell)
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

void Traveler::onBlock(Traveler* collidingWith, int atPathIndex, Cell& cell)
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
		request = nodeData->addRequest(requestedAlloc, &deadlockList);
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

	Cell bestCell, bestAlternateCell;
	Traveler* bestTraveler = nullptr, * bestAlternateTraveler = nullptr;

	for (int i = 0; i <= deadlockList.size() && !bestTraveler; i++) {
		Traveler* traveler = (i == 0 ? this : deadlockList[i - 1]);
		if (traveler == this && i > 0)
			continue;

		Cell curCell = traveler->travelPath[traveler->blockedAtTravelPathIndex - 1].cell;

		Cell blockingCell = traveler->request->cell;
		AStarNodeExtraData* extra = navigator->getExtraData(blockingCell);
		auto found = std::find_if(extra->allocations.begin(), extra->allocations.end(),
			[&](NodeAllocation& alloc) -> bool {return alloc.acquireTime <= curTime && alloc.releaseTime >= curTime; });
		Traveler* blockingTraveler = found->traveler;

		struct ShimmyInfo {
			Cell cell;
			bool isValid = true;
			ShimmyInfo(unsigned int grid, unsigned short row, unsigned short col, bool isValid) : cell(grid, row, col), isValid(isValid) {}
			ShimmyInfo() {}
		};
		AStarNode* curNode = navigator->getNode(curCell);
		ShimmyInfo leftCell(curCell.grid, curCell.row, curCell.col - 1, curNode->canGoLeft);
		ShimmyInfo rightCell(curCell.grid, curCell.row, curCell.col + 1, curNode->canGoRight);
		ShimmyInfo upCell(curCell.grid, curCell.row + 1, curCell.col, curNode->canGoUp);
		ShimmyInfo downCell(curCell.grid, curCell.row - 1, curCell.col, curNode->canGoDown);

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
		Cell curCell = bestTraveler->travelPath[bestTraveler->blockedAtTravelPathIndex - 1].cell;
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

void Traveler::assertBridgeData(BridgeRoutingData * routing)
{
	if (!bridgeData || !bridgeData->isClassType(routing->getBridgeDataClassFactory())) {
		TravelerBridgeData* data;
		if (routing)
			data = routing->createBridgeData();
		else data = new TravelerBridgeData;
		bridgeData = data;
		nodeaddsimpledata(bridgeDataNode, data, 1);
		bridgeData->bindEventNodes();
	}
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
	Task* taskdata = &o(Task, te->activetask);
	switch (taskdata->type) {
	case TASKTYPE_TRAVELTOLOC:
	case TASKTYPE_TRAVELRELATIVE:
	case TASKTYPE_PICKOFFSET:
	case TASKTYPE_PLACEOFFSET:
		te->updateTotalTravelDist(expectedtotaltraveldist - getkinematics(kinematics, KINEMATIC_TOTALDIST));
		break;
	default:
		te->updateTotalTravelDist(expectedtotaltraveldist);
		break;
	}
	expectedtotaltraveldist = 0;
	
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
	double x = getkinematics(te->node_v_kinematics, KINEMATIC_X, 1, time());
	double y = getkinematics(te->node_v_kinematics, KINEMATIC_Y, 1, time());
	double z = getkinematics(te->node_v_kinematics, KINEMATIC_Z, 1, time());
	double curdist = sqrt(sqr(x) + sqr(y) + sqr(z));
	double distancetraveled = expectedtotaltraveldist- getkinematics(te->node_v_kinematics, KINEMATIC_TOTALDIST) + curdist;
	te->updateTotalTravelDist(distancetraveled);
	expectedtotaltraveldist = 0;
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
			Cell cell = navigator->getCell(loc);
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

	if (bridgeEvent) {
		destroyevent(bridgeEvent->holder);
	}

	if (bridgeData && bridgeData->routingData) {
		bridgeData->routingData->onAbort(this);
		bridgeData->routingData = nullptr;
	}

	navigator->activeTravelers.erase(activeEntry);
	isActive = false;
}

void Traveler::updateLocation()
{
	if (!isActive)
		return;

	double updateTime = time();

	if (bridgeData && bridgeData->routingData && bridgeData->entryTime <= updateTime) {
		bridgeData->routingData->updateLocation(this);
	} else {
		TreeNode* kinematics = te->node_v_kinematics;
		updatekinematics(kinematics, te->holder, updateTime);
		te->b_spatialx -= 0.5*te->b_spatialsx;
		te->b_spatialy += 0.5*te->b_spatialsy;
	}
}

}