#include <random>
#include "Traveler.h"
#include "AStarNavigator.h"
#include "Bridge.h"
#include "macros.h"

namespace AStar {

void Traveler::bind()
{
	bindNumber(activeState);
	bindNumber(isBlocked);
	bindObjRef(arrivalEvent, false);
	bindObjRef(blockEvent, false);
	bindNumber(destLoc.x);
	bindNumber(destLoc.y);
	bindNumber(destLoc.z);
	bindNumber(lastBlockTime);
	bindNumber(isNavigatingAroundDeadlock);
	bindNumber(blockedAtTravelPathIndex);
	bindNumber(needsContinueTrigger);
	bindSubNode(kinematics, 0);
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
	bindNumber(numDeadlocksSinceLastNavigate);
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
	bindEventByName("onNavigatePath", onNavigatePath, "OnNavigatePath", EVENT_TYPE_TRIGGER);
	bindEventByName("onCalculatePath", onCalculatePath, "OnCalculatePath", EVENT_TYPE_TRIGGER);

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
	bindTypedProperty(isActive, int, &Traveler::__getIsActive, nullptr);
	bindTypedProperty(isBlocked, int, &Traveler::__getIsBlocked, nullptr);

	auto np = (void (Traveler::*)(int)) & Traveler::navigatePath_flexScript;
	bindMethodByName<decltype(np)>("navigatePath", np, "void navigatePath(int startAtIndex)");

	auto aa = (NodeAllocation(Traveler::*)(NodeAllocation&, int, int)) & Traveler::addAllocation_flexScript;
	bindMethodByName<decltype(aa)>("addAllocation", aa, "AStar.Allocation addAllocation(AStar.Allocation& alloc, int force, int notifyPendingAllocations)");

	auto fc = (NodeAllocation(*)(NodeAllocation&, int)) &Traveler::findCollision;
	bindMethodByName<decltype(fc)>("findCollision", fc, "AStar.Allocation findCollision(AStar.Allocation& alloc, int ignoreSameTravelerAllocs)", BIND_METHOD_STATIC);

	bindTypedProperty(object, TaskExecuter, &Traveler::__getObject, nullptr);

	bindMethod(finishPath, Traveler, "void finishPath()");
	bindMethod(arriveAtBridge, Traveler, "void arriveAtBridge(int pathIndex)");

	auto cp1 = (void(Traveler::*)(ObjectDataType *, int)) & Traveler::calculatePath;
	bindMethodByName<decltype(cp1)>("calculatePath", cp1, "void calculatePath(Object obj, int flags = 0)");
	auto cp2 = (void(Traveler::*)(const Vec3 &, int)) &Traveler::calculatePath;
	bindMethodByName<decltype(cp2)>("calculatePath", cp2, "void calculatePath(Vec3& dest, int flags = 0)");
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
	activeState = Inactive;
	isBlocked = false;
	lastBlockTime = 0;
	lastUpdateTravelDist = 0;
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
	travelPath.back().modelLoc = navigator->getLocation(resetCell);
	tinyTime = 0.001 * navigator->minNodeSize.x / te->v_maxspeed;
	tinyDist = 0.001 * navigator->minNodeSize.x;
	needsContinueTrigger = false;
	destThreshold = DestinationThreshold();
	destLoc = Vec3(0.0, 0.0, 0.0);
	destNode = nullptr;
	if (bridgeData)
		bridgeData->routingData = nullptr;
	routingAlgorithmSnapshots.clear();
	cachedPathKey.barrierConditions.resize(navigator->barrierConditions.size());
	isCachedPathKeyValid = false;
	numDeadlocksSinceLastNavigate = 0;
}

void Traveler::onStartSimulation()
{XS
	if (navigator->enableCollisionAvoidance && !navigator->ignoreInactiveMemberCollisions) {
		Vec3 loc = te->getLocation(0.5, 0.5, 0.0);
		Cell resetCell = navigator->getCell(loc);
		travelPath.clear();
		travelPath.push_back(AStarPathEntry(resetCell, -1));
		travelPath.back().modelLoc = navigator->getLocation(resetCell);
		addAllocation(NodeAllocation(this, resetCell, 0, 0, 0.0, DBL_MAX, 1.0), true, false);
	}
XE}

void Traveler::navigatePath(int startAtPathIndex)
{
	XS
	if (isRoutingNow)
		return;
	if (arrivalEvent)
		destroyevent(arrivalEvent);
	isRoutingNow = true;
	AStarNavigator* nav = navigator;

	if (needsContinueTrigger) {
		needsContinueTrigger = false;
		FIRE_SDT_EVENT(onContinueTrigger, te->holder);
	}

	double curSpeed = getCurSpeed();
	bool shouldTravelToFirstCell = te->v_deceleration > 0 && (curSpeed > 0 || isBlocked) ;
	double atDist = 0.0;
	// if I'm blocked and using acc/dec, then I may be continuing from being in the middle of 
	// traveling between two cells.
	if (shouldTravelToFirstCell) {
		atDist = updateLocation(true);
		while (startAtPathIndex > 0 && travelPath[startAtPathIndex - 1].atTravelDist > atDist - tinyTime)
			startAtPathIndex--;
	}
	else lastUpdateTravelDist = 0.0;

	setstate(te->holder, content(te->holder) > 0 ? STATE_TRAVEL_LOADED : STATE_TRAVEL_EMPTY);

	double outputVector[3];
	Vec3 startLoc;
	BridgeRoutingData* exitingBridgeRoutingData = (bridgeData ? bridgeData->routingData : nullptr);
	bool isExitingBridge = exitingBridgeRoutingData != nullptr;
	if (isExitingBridge || shouldTravelToFirstCell) {
		startLoc = te->getLocation(0.5, 0.5, 0).project(te->holder->up, model());
	}
	else {
		startLoc = travelPath[startAtPathIndex].modelLoc;
	}
	travelPath.startIndex = startAtPathIndex;
	travelPath.startZRot = te->b_spatialrz;
	travelPath.startModelLoc = startLoc;
	travelPath.startDist = atDist;
	travelPath.lastUpdateDist = -1.0;

	int kinFlags = 0;
	double endTime = time();
	double rotLerpSize = navigator->smoothRotations;
	double rotLerpSpeed = 90 / (te->b_spatialsx * rotLerpSize / te->v_maxspeed);
	double lastRotation;
	lastRotation = Vec3(0.0, 0.0, te->b_spatialrz).projectRotation(te->holder->up, model()).z;
	bool teCanRotate = objectexists(te->node_v_modifyrotation) && te->node_v_modifyrotation->value;
	if (teCanRotate) {

		if (rotLerpSize == 0 && !nav->stopForTurns)
			kinFlags |= KINEMATIC_MANAGE_ROTATIONS;

		if (!te->canRotateOnIncline())
			kinFlags |= KINEMATIC_NO_INCLINE_ROTATION;
	}
	else {
		rotLerpSize = 0;
	}


	AStarPathEntry* e, * laste;
	int numNodes = (int)travelPath.size();
	laste = &travelPath[startAtPathIndex];
	bool enableCollisionAvoidance = nav->enableCollisionAvoidance;

	//clearAllocationsExcept(laste->cell);

	if (laste->arrivalTime < endTime)
		laste->arrivalTime = endTime;

	double deallocTimeOffset = nav->deallocTimeOffset;

	int initialAllocsSize = (int)allocations.size();
	if (enableCollisionAvoidance && (!nav->ignoreInactiveMemberCollisions || isBlocked || isContinuingFromDeadlock)) {
		// here I want to 'clear out' the allocations that I'm no longer going to travel over. I first 
		// mark all current allocations for deletion. Then later as I go through the path I will readd 
		// them, which will unmark them for deletion. Then those that are still marked for deletion at 
		// the end will be deleted.
		for (auto& allocation : allocations) {
			//allocation->extendReleaseTime(DBL_MAX);
			if (allocation->cell != laste->cell)
				allocation->isMarkedForDeletion = true;
			else if (!shouldTravelToFirstCell) {
				allocation->changeReleaseTime(endTime + deallocTimeOffset);
			}
		}
	}

	isBlocked = false;
	isContinuingFromDeadlock = false;
	blockedAtTravelPathIndex = -1;

	UserNavigationResult userResult = (UserNavigationResult)(int)FIRE_SDT_EVENT_VALUE_GETTER(onNavigatePath, te->holder, startAtPathIndex + 1, kinematics);
	if ((userResult & UserNavigationResult::AbortAll))
		return;

	int didBlockPathIndex = -1;
	NodeAllocation* lastAllocation = nullptr;
	BridgeRoutingData* bridgeArrival = nullptr;
	int i = startAtPathIndex;
	double firstCellDeallocTime = time() + deallocTimeOffset;
	Grid* grid = nullptr;
	int lastGridNum = -1;
	double endArrivalTime = endTime;
	double tinyDist = navigator->grids.front()->diagDist * 0.001;

	double dec = te->v_deceleration;
	double acc = te->v_acceleration;
	double maxSpeed = te->v_maxspeed;

	if (!(userResult & UserNavigationResult::UserNavigated)) {

		double containerRot = 0;
		if (te->holder->up != model()) {
			treenode obj = te->holder;
			while (obj != model()) {
				obj = obj->findOwnerObject();
				containerRot += zrot(obj);
			}
		}
		initkinematics(kinematics, atDist, 0, 0, 0, 0, te->b_spatialrz, kinFlags, 0);
		auto& first = travelPath[startAtPathIndex];
		if (shouldTravelToFirstCell) {
			auto& toLoc = first.modelLoc;
			auto diff = toLoc - startLoc;
			auto dist = diff.magnitude;
			if (dist > tinyDist) {
				endTime = addkinematic(kinematics, dist, 0, 0, maxSpeed, acc, dec, curSpeed, first.maxArrivalSpeed, time(), KINEMATIC_TRAVEL);
				first.arrivalTime = endTime;
				first.atTravelDist = atDist + dist;
				curSpeed = getkinematics(kinematics, KINEMATIC_ENDSPEED, 1);
				atDist = first.atTravelDist;
			}
			else {
				first.arrivalTime = time();
				first.atTravelDist = atDist;
			}
			if (navigator->enableCollisionAvoidance) {
				NodeAllocation allocation(this, first.cell, startAtPathIndex, 0, time(), std::nextafter(endTime + deallocTimeOffset, DBL_MAX), 1.0);
				addAllocation(allocation, true, true);
			}
		}
		else {
			first.arrivalTime = time();
			first.atTravelDist = 0.0;
		}

		for (i = startAtPathIndex + 1; i < numNodes; i++) {
			e = &travelPath[i];
			if (e->cell.grid != lastGridNum) {
				lastGridNum = e->cell.grid;
				grid = navigator->getGrid(e->cell);
			}
			AllocationStep step(laste->cell, e->cell);
			bridgeArrival = nullptr;

			if (laste->isBridgePoint) {
				AStarNodeExtraData* nodeData = nav->getExtraData(laste->cell);
				BridgeRoutingData* data = nodeData->bridges[laste->bridgeIndex];
				if (!bridgeData || bridgeData->routingData != data) {
					bridgeArrival = data;
				}
			}

			if (!bridgeArrival) {
				int numSuccessfulAllocations = 0;
				Vec3 diff;
				double startTime = endTime;
				if (!isExitingBridge) {
					diff.x = (e->cell.col - laste->cell.col) * grid->nodeSize.x;
					diff.y = (e->cell.row - laste->cell.row) * grid->nodeSize.y;
					diff.z = 0;
				}
				else {
					Vec3 toLoc = e->modelLoc;
					step.isDiagonal = false;
					step.isHorizontalDeepSearch = false;
					step.isVerticalDeepSearch = false;
					diff = toLoc - startLoc;
					isExitingBridge = false;
				}

				if (nav->stopForTurns) {
					double nextRot = diff.getXYAngle();
					double rotDiff = nextRot - lastRotation;
					while (rotDiff > 180)
						rotDiff -= 360;
					while (rotDiff < -180)
						rotDiff += 360;

					if (nav->stopForTurns) {
						if (fabs(rotDiff) > 0.1) {
							e->turnStartTime = startTime;
							startTime += turnDelay + fabs(rotDiff / turnSpeed);
							if (lastAllocation)
								lastAllocation->extendReleaseTime(startTime + deallocTimeOffset);
							if (i == startAtPathIndex + 1)
								firstCellDeallocTime = startTime + deallocTimeOffset;
						}
					}
					lastRotation = nextRot;
				}

				double dist = diff.magnitude;
				atDist += dist;
				e->atTravelDist = atDist;
				double startSpeed = curSpeed;
				endTime = addkinematic(kinematics, dist, 0, 0, maxSpeed, acc, dec, startSpeed, e->maxArrivalSpeed, startTime, KINEMATIC_TRAVEL);
				if (dec == 0 || e->maxArrivalSpeed >= endSpeed)
					endArrivalTime = endTime;
				curSpeed = getkinematics(kinematics, KINEMATIC_ENDSPEED, getkinematics(kinematics, KINEMATIC_NR));
				e->arrivalTime = endTime;

				if (enableCollisionAvoidance) {
					double allocTime = startTime;
					if (dec > 0) {
						double totalDist = 0;
						// search back through the travel path to find the point where I would need to decelerate to stop
						for (int j = i - 1; j >= 0; j--) {
							auto& entry = travelPath[j];
							totalDist += entry.distFromPrev;
							double distToDecel = 0.5 * startSpeed * (startSpeed / dec);
							if (distToDecel <= totalDist + tinyDist) {
								// te can decelerate to stop after starting to travel to this cell, so 
								// set the allocation time to the arrival time at the previous cell
								// note I don't try to calculate some 'in-between' allocation time 
								// based on some math solution of acc/dec/startSpeed/endSpeed/etc. for 
								// simplicity's sake. Maybe at some future time I'll do that, but for 
								// now just say I allocate at arrival of the previous cell.
								allocTime = j > startAtPathIndex ? travelPath[j - 1].arrivalTime : time();
								break;
							}
						}
					}
					double middleReleaseTime = 0.5 * (startTime + endTime);
					NodeAllocation allocation(this, e->cell, i, 0, allocTime, middleReleaseTime + deallocTimeOffset, 1.0);
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
						allocation.cell = e->cell;
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
			}
			else {
				// travel onto a bridge
				didBlockPathIndex = i;
				break;
			}

			//Traffic info
			nav->assertExtraData(e->cell, TraversalData)->totalTraversals++;
			nav->heatMapTotalTraversals++;
			if (step.isVerticalDeepSearch || step.isHorizontalDeepSearch) {
				nav->assertExtraData(step.intermediateCell1, TraversalData)->totalTraversals += 0.5;
				nav->assertExtraData(step.intermediateCell2, TraversalData)->totalTraversals += 0.5;
				nav->heatMapTotalTraversals++;
			}

			laste = e;
		}
	}

	// remove the original allocations and get off the bridge if I was able to allocate ahead at least one
	// This will trigger other travelers who might be waiting for me to move on 
	// from the current point I'm at.
	if (numNodes > startAtPathIndex + 1 && (didBlockPathIndex == -1 || didBlockPathIndex > startAtPathIndex + 1) && !(userResult & UserNavigationResult::Blocked)) {
		if (exitingBridgeRoutingData) {
			if (bridgeData->routingData == exitingBridgeRoutingData)
				bridgeData->routingData = nullptr;
			exitingBridgeRoutingData->onExit(this);
		}

		if (enableCollisionAvoidance && initialAllocsSize > 0 && !(userResult & UserNavigationResult::KeepAllocations)) {
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

	if (activeState == Inactive) {
		nav->activeTravelers.push_front(this);
		activeEntry = nav->activeTravelers.begin();
	}
	activeState = Active;
	if (didBlockPathIndex == -1 && !blockEvent && !isBlocked && i == numNodes && userResult == UserNavigationResult::Default) {
		arrivalEvent = createevent(new ArrivalEvent(this, endArrivalTime, dec == 0 || endArrivalTime == endTime))->objectAs(ArrivalEvent);
	}

	isRoutingNow = false;
	XE
}


void Traveler::navigatePath(TravelPath&& path)
{
	if (activeState != DecelToStop || travelPath.size() == 0)
		travelPath = std::move(path);
	else {
		// If I'm decelerating to a stop, then I should continue at least to the first 
		// cell in the path before going to the path

		// first find the first cell that is still ahead of me
		auto firstAhead = travelPath.end() - 1;
		while (firstAhead != travelPath.begin() && (firstAhead - 1)->arrivalTime > time() - tinyTime)
			firstAhead--;
		// if that's the same cell as the path's first cell, then just move the path
		if (firstAhead->cell == path[0].cell)
			travelPath = std::move(path);
		else { // otherwise first go to the first cell, then copy the path to my travel path
			auto firstEntry = *firstAhead;
			travelPath.clear();
			travelPath.push_back(firstEntry);
			for (auto& entry : path) {
				travelPath.push_back(entry);
			}
			path.clear();
		}
	}
	navigatePath(0);
}


void Traveler::calculatePath(const Vec3& destLoc, int flags)
{
	navigator->calculatePath(this, (double*)(Vec3&)destLoc, DestinationThreshold(), flags);
}

void Traveler::calculatePath(ObjectDataType* dest, int flags)
{
	Vec3 center = dest->getLocation(0.5, 0.5, 0.5).project(dest->holder->up, model());
	navigator->calculatePath(this, (double*)center, DestinationThreshold(dest->holder, navigator->minNodeSize), flags);
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

	updateLocation(true);
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
	te->updateTotalTravelDist(bridge->travelDistance);
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
	bool iAmBlocked = false;

	if (!force || notifyPendingAllocations) {
		NodeAllocation* selfCollision = nullptr;
		visitCollisions(nodeData, allocation, false,
			[&](NodeAllocation& other) {
				auto* collideWith = &other;
				if (collideWith->traveler == this) {
					selfCollision = collideWith;
					return false;
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
					else // if I am the later collision, then I should mark that I am blocked
						iAmBlocked = true;
				}
				else {
					delete event;
				}
				return false;
			}
		);

		if (selfCollision) {
			double oldReleaseTime = selfCollision->releaseTime;
			double oldAcquireTime = selfCollision->acquireTime;
			*selfCollision = allocation;
			if (allocation.releaseTime > oldReleaseTime) {
				selfCollision->releaseTime = oldReleaseTime;
				selfCollision->extendReleaseTime(allocation.releaseTime);
			}
			else if (nodeData->requests.size() > 0) {
				nodeData->checkCreateContinueEvent();
			}
			if (allocation.acquireTime > oldAcquireTime) // don't push acquireTime back
				allocation.acquireTime = oldAcquireTime;
			selfCollision->isMarkedForDeletion = false;

			return selfCollision;
		}
	}

	if (!iAmBlocked) {
		nodeData->allocations.push_front(allocation);
		allocations.push_back(nodeData->allocations.begin());

		return &(nodeData->allocations.front());
	}
	else return nullptr;
	XE
}

NodeAllocation* Traveler::addAllocation(NodeAllocation&& allocation, bool force, bool notifyPendingAllocations)
{
	return addAllocation(allocation, force, notifyPendingAllocations);
}


NodeAllocation Traveler::addAllocation_flexScript(NodeAllocation& allocation, int force, int notifyPendingAllocations)
{
	NodeAllocation* alloc = addAllocation(allocation, (bool)force, (bool)notifyPendingAllocations);
	if (alloc)
		return *alloc;
	return NodeAllocation();
}


NodeAllocation* Traveler::findCollision(AStarNodeExtraData* nodeData, const NodeAllocation& myAllocation, bool ignoreSameTravelerAllocs)
{
	XS
	NodeAllocation* best = nullptr;
	double minAcquireTime = DBL_MAX;
	double curTime = time();
	visitCollisions(nodeData, myAllocation, ignoreSameTravelerAllocs,
		[&](NodeAllocation& other) {
			if (other.acquireTime < minAcquireTime) {
				best = &other;
				minAcquireTime = other.acquireTime;
				if (other.acquireTime < curTime)
					return true;
			}
			return false;
		}
	);

	return best;
	XE
}

NodeAllocation Traveler::findCollision(NodeAllocation& test, int ignoreSameTravelerAllocs)
{
	if (!AStarNavigator::instance)
		return NodeAllocation();
	AStarNodeExtraData* nodeData = AStarNavigator::instance->getExtraData(test.cell);
	if (!nodeData)
		return NodeAllocation();
	auto found = findCollision(nodeData, test, (bool)ignoreSameTravelerAllocs);
	if (found)
		return *found;
	return NodeAllocation();
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

void Traveler::resetTravelDist(double& atTravelDist)
{
	for (auto& entry : travelPath) {
		if (entry.atTravelDist == DBL_MAX)
			break;
		entry.atTravelDist -= atTravelDist;
	}

	for (auto& alloc : allocations) {
		alloc->atTravelDist -= atTravelDist;
	}
	atTravelDist = 0;
}

void Traveler::onBlock(Traveler* collidingWith, int allocPathIndex, Cell& cell)
{
	XS
	cullExpiredAllocations();
	bool shouldStop = true;
	if (travelPath.size() <= allocPathIndex)
		shouldStop = false;

	AStarNodeExtraData* nodeData = navigator->getExtraData(cell);
	double curTime = time();
	auto foundAlloc = std::find_if(nodeData->allocations.begin(), nodeData->allocations.end(),
		[&](NodeAllocation& alloc) { return alloc.traveler == collidingWith && alloc.acquireTime <= curTime && alloc.releaseTime > curTime; }
		);
	
	if (shouldStop && foundAlloc == nodeData->allocations.end())
		shouldStop = false;

	double atTravelDist = updateLocation(true);
	if (shouldStop) {
		double curSpeed = getCurSpeed();
		int atPathIndex = allocPathIndex - 1;
		double distToStop = 0;
		double dec = te->v_deceleration;
		if (dec > 0) {
			while (atPathIndex > 0) {
				auto& entry = travelPath[atPathIndex];
				if (entry.arrivalTime > curTime + tinyTime) {
					distToStop += entry.distFromPrev;
					atPathIndex--;
				}
				else break;
			}
		}
		Vec3 pos = te->getLocation(0.5, 0.5, 0.0);
		initkinematics(kinematics, atTravelDist, 0, 0, 0.0, 0.0, 0.0, 1, 0);

		setstate(te->holder, STATE_BLOCKED);

		lastBlockTime = curTime;
		for (int i = atPathIndex + 1; i < travelPath.size(); i++) {
			if (travelPath[i].arrivalTime == -1.0)
				break;
			travelPath[i].arrivalTime = -1;
		}
		if (distToStop > 0) {
			double startSpeed = curSpeed;
			double tempTime = curTime;
			double maxSpeed = te->v_maxspeed;
			double acc = te->v_acceleration;
			for (int i = atPathIndex - 1; i < allocPathIndex - 1; i++) {
				auto fromLoc = i == atPathIndex - 1 ? pos : navigator->getLocation(travelPath[i].cell);
				auto& toEntry = travelPath[i + 1];
				auto toLoc = navigator->getLocation(toEntry.cell);
				auto diff = toLoc - fromLoc;
				auto dist = diff.magnitude;
				if (dist > 0.0) {
					// Solve for endSpeed given travel dist, start speed, and deceleration
					// dist =    avgSpeed    *    travelTime
					// dist = (endSpeed / 2) * (endSpeed / dec);
					// dist * 2 * dec = endSpeed^2
					// endSpeed = sqrt(dist * 2 * dec)
					double endSpeed = startSpeed;
					if (i > atPathIndex - 1) {
						distToStop -= toEntry.distFromPrev;
						endSpeed = sqrt(std::max(0.0, distToStop * 2 * dec));
					}
					tempTime = addkinematic(kinematics, dist, 0, 0, maxSpeed, acc, dec, startSpeed, endSpeed, tempTime, KINEMATIC_TRAVEL);
					startSpeed = endSpeed;
				}
				toEntry.arrivalTime = tempTime;
			}
		}

		std::vector<Traveler*> deadlockList;
		for (auto& allocation : allocations) {
			if (allocation->travelPathIndex == allocPathIndex - 1 && allocation->cell == travelPath[allocPathIndex - 1].cell)
				allocation->extendReleaseTime(DBL_MAX);
			else if (allocation->travelPathIndex < travelPath.size() - 1) {
				auto& nextEntry = travelPath[allocation->travelPathIndex + 1];
				if (nextEntry.arrivalTime > allocation->releaseTime)
					allocation->extendReleaseTime(nextEntry.arrivalTime);
			}
		}
		NodeAllocation requestedAlloc(this, cell, allocPathIndex, 0, curTime, DBL_MAX, 0.0);
		request = nodeData->addRequest(requestedAlloc, &deadlockList);
		bool isDeadlock = deadlockList.size() > 0;
		isBlocked = true;
		blockedAtTravelPathIndex = atPathIndex;
		if (onBlockTrigger && (!nodeData->continueEvent || nodeData->continueEvent->time - curTime > tinyTime)) {
			if (FIRE_SDT_EVENT_VALUE_GETTER(onBlockTrigger, te->holder, isDeadlock, atPathIndex))
				return;//???
			needsContinueTrigger = true;
		}
		if (isDeadlock) {
			blockEvent = nullptr;
			navigateAroundDeadlock(deadlockList, requestedAlloc);
		}
	} else {
		navigatePath(allocPathIndex - 1);
	}
	XE
}


bool Traveler::navigateAroundDeadlock(std::vector<Traveler*>& deadlockList, NodeAllocation& deadlockCreatingRequest)
{
	double curTime = time();
	std::multimap<Traveler*, treenode> dynamicBarriers;

	std::function<void(Traveler*)> addDynamicBarrier = [&](Traveler* traveler) -> void {
		if (dynamicBarriers.find(traveler) != dynamicBarriers.end())
			return;
		for (auto& alloc : traveler->allocations) {
			if (alloc->acquireTime <= curTime && alloc->releaseTime > curTime) {
				Grid* grid = navigator->getGrid(alloc->cell);
				Vec3 loc = grid->getLocation(alloc->cell);
				double width = grid->minNodeSize * 0.1;
				Vec3 size(width, width, width);
				dynamicBarriers.insert({ traveler, navigator->addDynamicBarrier(loc + Vec3(-0.5 * width, 0.5 * width, 0.0), size, Vec3(0.0, 0.0, 0.0), 1) });
			}
		}
		if (traveler->allocations.size() > 0) {
			auto node = navigator->getExtraData(traveler->allocations.back()->cell);
			for (auto request : node->requests) {
				if (dynamicBarriers.find(request.traveler) == dynamicBarriers.end())
					addDynamicBarrier(request.traveler);
			}
		}
	};
	for (Traveler* traveler : deadlockList) {
		addDynamicBarrier(traveler);
	}
	
	TravelPath bestPath, secondBestPath;
	Traveler* bestTraveler = nullptr, *secondBestTraveler = nullptr;
	if (numDeadlocksSinceLastNavigate > 0) {
		std::minstd_rand rand;
		rand.seed(numDeadlocksSinceLastNavigate * 10283);
		std::shuffle(deadlockList.begin(), deadlockList.end(), rand);
	}

	int startAt = numDeadlocksSinceLastNavigate == 0 ? 0 : 1;
	for (int i = startAt; i <= deadlockList.size() && !bestTraveler; i++) {
		Traveler* traveler = (i == 0 ? this : deadlockList[i - 1]);
		if (traveler == this && i > 0 && numDeadlocksSinceLastNavigate == 0)
			continue;

		Direction directions[] = { Up, Down, Left, Right };
		for (int i = 0; i < 4; i++) {
			auto neighborCell = ExtendedCell(traveler->allocations.back()->cell.adjacentCell(directions[i]));
			auto alloc = neighborCell.getAllocation(time());
			if (alloc && alloc.traveler->isBlocked) {
				if (dynamicBarriers.find(alloc.traveler) == dynamicBarriers.end())
					addDynamicBarrier(alloc.traveler);
			}
		}

		auto range = dynamicBarriers.equal_range(traveler);
		for (auto iter = range.first; iter != range.second; iter++) {
			navigator->removeDynamicBarrier(iter->second, 1);
		}
		dynamicBarriers.erase(traveler);

		Cell destCell = traveler->travelPath.back().cell;
		Vec3 destLoc = navigator->getGrid(destCell)->getLocation(destCell);
		auto atCurrent = traveler->travelPath.findNearestNext(traveler, getkinematics(traveler->kinematics, KINEMATIC_X));
		TravelPath testPath = navigator->calculatePath(traveler, destLoc, DestinationThreshold(), AStarNavigator::DoFullSearch | AStarNavigator::KeepEndpointsConst, -1.0, atCurrent);

		bool isBestTraveler = testPath.back().cell == destCell;
		if (!isBestTraveler && !secondBestTraveler) {
			if (testPath.size() > 1) {
				secondBestPath = std::move(testPath);
				secondBestPath.resize(2);
				secondBestTraveler = traveler;
			}
			else {
				for (int i = 0; i < 4; i++) {
					auto neighborCell = traveler->allocations.back()->cell.adjacentCell(directions[(i + numDeadlocksSinceLastNavigate) % 4]);
					destLoc = navigator->getGrid(neighborCell)->getLocation(neighborCell);
					testPath = navigator->calculatePath(traveler, destLoc, DestinationThreshold(), AStarNavigator::DoFullSearch | AStarNavigator::KeepEndpointsConst, -1.0);
					if (testPath.size() > 1) {
						secondBestPath = std::move(testPath);
						secondBestTraveler = traveler;
						break;
					}
				}

			}
		}

		addDynamicBarrier(traveler);

		if (isBestTraveler) {
			bestPath = std::move(testPath);
			bestTraveler = traveler;
			break;
		}

	}

	for (auto entry : dynamicBarriers)
		navigator->removeDynamicBarrier(entry.second);

	numDeadlocksSinceLastNavigate++;
	if (!bestTraveler && secondBestTraveler) {
		bestTraveler = secondBestTraveler;
		bestPath = std::move(secondBestPath);
	}

	if (bestTraveler) {
		Cell destCell = bestTraveler->travelPath.back().cell;
		navigator->getExtraData(bestTraveler->request->cell)->requests.remove_if([&](NodeAllocation& alloc) { return &alloc == bestTraveler->request; });
		bestTraveler->request = nullptr;
		FIRE_SDT_EVENT(bestTraveler->onRerouteTrigger, te->holder);
		Cell curCell = bestPath[0].cell;
		//TravelPath newPath;
		//newPath.push_back(AStarPathEntry(curCell, -1));
		//newPath.push_back(AStarPathEntry(bestCell, -1));
		bestTraveler->cullExpiredAllocations();
		double curSpeed = bestTraveler->getCurSpeed();
		double atTravelDist = bestTraveler->updateLocation(true);
		Vec3 curModelLoc = bestTraveler->te->getLocation(0.5, 0.5, 0.0).project(bestTraveler->te->holder->up, model());
		if (bestPath.back().cell != destCell)
			bestTraveler->isNavigatingAroundDeadlock = true; // flag it to reroute again on arrival if this rerouted path doesn't get me there
		bestPath[0].atTravelDist = atTravelDist + (bestPath[0].modelLoc - curModelLoc).magnitude;
		bestPath.startModelLoc = curModelLoc;
		bestPath.startIndex = 0;
		bestPath.startZRot = bestTraveler->te->b_spatialrz;
		bestTraveler->navigatePath(std::move(bestPath));
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



void Traveler::onArrival(bool isAtZeroSpeed)
{
	arrivalEvent = nullptr;
	double atTravelDist = updateLocation(true);
	updateSpeedMarkers();
	cullExpiredAllocations();
	
	if (isAtZeroSpeed) {
		AStarPathEntry back = travelPath.back();
		travelPath.clear();
		travelPath.push_back(back);
		resetTravelDist(atTravelDist);
		if (navigator->enableCollisionAvoidance && !isNavigatingAroundDeadlock) {
			if (navigator->ignoreInactiveMemberCollisions)
				clearAllocations();
			else if (allocations.size() > 0) {
				if (allocations.size() > 1)
					clearAllocationsUpTo(allocations.end() - 2);
				allocations.front()->extendReleaseTime(DBL_MAX);
			}
		}
	}

	if (activeState == Active) {

		if (!isNavigatingAroundDeadlock) {
			if (isAtZeroSpeed) {
				activeState = Inactive;
				navigator->activeTravelers.erase(activeEntry);
			}
			else {
				activeState = DecelToStop;
				double endTime = getkinematics(kinematics, KINEMATIC_ENDTIME, getkinematics(kinematics, KINEMATIC_NR));
				arrivalEvent = createevent(new ArrivalEvent(this, endTime, true))->object<ArrivalEvent>();
			}
			te->onDestinationArrival(te->v_lastupdatedspeed);
		}
		else {
			if (!isAtZeroSpeed)
				activeState = DecelToStop;
			if (allocations.size() > 1)
				clearAllocationsUpTo(allocations.end() - 2);
			allocations.front()->extendReleaseTime(DBL_MAX);
			isNavigatingAroundDeadlock = false;
			isContinuingFromDeadlock = true;
			auto newPath = navigator->calculatePath(this, destLoc, destThreshold, 0, -1.0);
			navigatePath(std::move(newPath));
		}
	}
	else if (activeState == DecelToStop) {
		activeState = Inactive;
		navigator->activeTravelers.erase(activeEntry);
	}
}

void Traveler::abortTravel(TreeNode* newTS)
{
	updateLocation(true);
	updateSpeedMarkers();
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

			for (int i = (int)allocations.size() - 1; i >= 0; i--) {
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
	activeState = Inactive;
}

double Traveler::updateLocation(bool updateTravelDistStats)
{
	if (activeState == Inactive)
		return 0.0;

	double updateTime = time();

	if (bridgeData && bridgeData->routingData && bridgeData->entryTime <= updateTime) {
		bridgeData->routingData->updateLocation(this);
	} else {
		double x = getkinematics(kinematics, KINEMATIC_X);
		travelPath.update(this, x);
		if (updateTravelDistStats) {
			te->updateTotalTravelDist(fabs(x - lastUpdateTravelDist));
			lastUpdateTravelDist = x;
		}
	}
	return lastUpdateTravelDist;
}

astar_export void Traveler::updateSpeedMarkers()
{
	if (activeState == Inactive)
		return;
	double updateTime = time();
	te->v_lastspeedupdatetime = updateTime;
	double updatedSpeed = getkinematics(kinematics, KINEMATIC_VELOCITY, 0, std::max(0.0, std::nextafter(updateTime, -DBL_MAX)));
	if (updatedSpeed < 0.001 * te->v_maxspeed)
		updatedSpeed = 0;
	te->v_lastupdatedspeed = updatedSpeed;
}

double Traveler::getCurSpeed()
{
	double updateTime = time();
	if (bridgeData && bridgeData->routingData && bridgeData->entryTime <= updateTime) {
		return 0;
	}
	else if (activeState == Inactive)
		return 0;
	else if (updateTime == te->v_lastspeedupdatetime)
		return te->v_lastupdatedspeed;
	else 
		return getkinematics(kinematics, KINEMATIC_VELOCITY, 0, updateTime);
}

}