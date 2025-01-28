#include <random>
#include "Traveler.h"
#include "AStarNavigator.h"
#include "Bridge.h"
#include "macros.h"

namespace AStar {

void Traveler::bind()
{
	bindNumber(activeState);
	bindNumber(blockMode);
	bindObjRef(nextEvent, false);
	bindObjRef(blockEvent, false);
	bindNumber(destLoc.x);
	bindNumber(destLoc.y);
	bindNumber(destLoc.z);
	bindNumber(lastBlockTime);
	bindNumber(isNavigatingAroundDeadlock);
	bindNumber(blockedAtTravelPathIndex);
	bindNumber(needsContinueTrigger);
	bindSubNode(kinematics, 0);
	bindSubNode(controlAreaAllocations, 0);
	//controlAreas.init((treenode)controlAreaAllocations);

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
	bindNumber(numDeadlocksSinceLastNavigate);
	bindNumber(shouldFinishTravelPath);
	bindNumber(navigatedDist);
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
	bindNumber(colliderTravelDist);
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
	blockMode = BlockMode::None;
	lastBlockTime = 0;
	lastStatUpdateTravelDist = 0;
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
	shouldFinishTravelPath = false;
	destThreshold = DestinationThreshold();
	destLoc = Vec3(0.0, 0.0, 0.0);
	destNode = nullptr;
	if (bridgeData)
		bridgeData->routingData = nullptr;
	routingAlgorithmSnapshots.clear();
	cachedPathKey.barrierConditions.resize(navigator->barrierConditions.size());
	isCachedPathKeyValid = false;
	numDeadlocksSinceLastNavigate = 0;
	isRoutingNow = false;
	controlAreaAllocations.clear();
	navigatedDist = 0;
	if (te->v_useoffsets == OFFSET_BY_TE_LOGIC && te->v_deceleration != 0.0) {
		string error = "Non-zero deceleration is not supported on A* networks when the task executer uses normal offset travel. Changing deceleration on ";
		error.append(te->holder->getPath()).append(" from ").append(std::to_string(te->v_deceleration)).append(" to 0.");
		EX("", error.c_str(), 1);
		te->v_deceleration = 0; // A* doesn't support non-zero deceleration if you offset by te logic
	}
}

void Traveler::onStartSimulation()
{XS
	Vec3 loc = te->getLocation(0.5, 0.5, 0.0);
	Cell resetCell = navigator->getCell(loc);
	if (navigator->enableCollisionAvoidance && !navigator->ignoreInactiveMemberCollisions) {
		travelPath.clear();
		travelPath.push_back(AStarPathEntry(resetCell, -1));
		travelPath.back().modelLoc = navigator->getLocation(resetCell);
		addAllocation(NodeAllocation(this, resetCell, 0, 0, 0.0, DBL_MAX, 1.0), true, false);
	}

	auto data = navigator->getExtraData(resetCell);
	if (data && data->controlAreaSetIndex >= 0) {
		auto& set = navigator->controlAreaSets[data->controlAreaSetIndex];
		for (int index : set) {
			auto obj = navigator->controlAreas[index];
			auto allocPoint = obj->allocate(te, true);
			allocPoint->holder->up = controlAreaAllocations;
		}
	}
	
XE}

void Traveler::navigatePath(int startAtPathIndex)
{
	XS
	if (isRoutingNow)
		return;
	if (nextEvent)
		destroyevent(nextEvent);
	isRoutingNow = true;
	AStarNavigator* nav = navigator;

	if (needsContinueTrigger) {
		needsContinueTrigger = false;
		FIRE_SDT_EVENT(onContinueTrigger, te->holder);
	}

	double curSpeed = getCurSpeed();
	bool startBetweenCells = te->v_deceleration > 0 && (curSpeed > 0 || blockMode != BlockMode::None) ;
	double atDist = travelPath[startAtPathIndex].atTravelDist;
	// if I'm blocked and using acc/dec, then I may be continuing from being in the middle of 
	// traveling between two cells.
	if (startAtPathIndex > 0 || startBetweenCells) {
		atDist = updateLocation(true);
		if (fabs(atDist - travelPath[startAtPathIndex].atTravelDist) < tinyDist) {
			startBetweenCells = false;
			lastStatUpdateTravelDist = atDist;
		}
		else {
			while (startAtPathIndex > 0 && travelPath[startAtPathIndex].atTravelDist > atDist + tinyDist)
				startAtPathIndex--;
		}
	}
	else {
		lastStatUpdateTravelDist = atDist;
	}

	setstate(te->holder, content(te->holder) > 0 ? STATE_TRAVEL_LOADED : STATE_TRAVEL_EMPTY);

	double outputVector[3];
	Vec3 startLoc;
	BridgeRoutingData* exitingBridgeRoutingData = (bridgeData ? bridgeData->routingData : nullptr);
	bool isExitingBridge = exitingBridgeRoutingData != nullptr;
	if (isExitingBridge || startBetweenCells) {
		startLoc = te->getLocation(0.5, 0.5, 0).project(te->holder->up, model());
		if (isExitingBridge)
			travelPath.bridgeExitLoc = startLoc;
	}
	else {
		startLoc = travelPath[startAtPathIndex].modelLoc;
	}
	travelPath.startZRot = te->b_spatialrz;
	travelPath.lastUpdateDist = -1.0;

	Vec3 prevLoc = startLoc;
	double curTime = time();
	double endTime = curTime;
	double rotLerpSize = navigator->smoothRotations;
	double rotLerpSpeed = 90 / (te->b_spatialsx * rotLerpSize / te->v_maxspeed);
	double lastRotation;
	lastRotation = Vec3(0.0, 0.0, te->b_spatialrz).projectRotation(te->holder->up, model()).z;
	bool teCanRotate = objectexists(te->node_v_modifyrotation) && te->node_v_modifyrotation->value;
	if (!teCanRotate)
		rotLerpSize = 0;

	AStarPathEntry* e, * laste;
	int numNodes = (int)travelPath.size();
	laste = &travelPath[startAtPathIndex];
	bool enableCollisionAvoidance = nav->enableCollisionAvoidance;

	//clearAllocationsExcept(laste->cell);

	if (laste->arrivalTime < endTime)
		laste->arrivalTime = endTime;

	double deallocTimeOffset = nav->deallocTimeOffset;

	cullExpiredAllocations();
	int initialAllocsSize = (int)allocations.size();
	NodeAllocation* lastAllocation = nullptr;
	if (enableCollisionAvoidance && (!nav->ignoreInactiveMemberCollisions || blockMode != BlockMode::None || isContinuingFromDeadlock)) {
		// here I want to 'clear out' the allocations that I'm no longer going to travel over. I first 
		// mark all current allocations for deletion. Then later as I go through the path I will readd 
		// them, which will unmark them for deletion. Then those that are still marked for deletion at 
		// the end will be deleted.
		for (auto& allocation : allocations) {
			//allocation->extendReleaseTime(DBL_MAX);
			if (allocation->cell != laste->cell) {
				if (allocation->releaseTime > endTime + deallocTimeOffset)
					allocation->isMarkedForDeletion = true;
				//else navigator->getExtraData(allocation->cell)->checkCreateContinueEvent();
			}
			else {
				lastAllocation = &(*allocation);
				allocation->changeReleaseTime(std::nextafter(endTime + deallocTimeOffset, DBL_MAX));
			}
		}
	}

	blockMode = BlockMode::None;
	isContinuingFromDeadlock = false;
	blockedAtTravelPathIndex = -1;
	// the navigator index of the set of control areas associated with the current cell
	int curControlAreaSetIndex = 0;
	// the set of control areas that I have allocated but which I have not yet encountered on the path
	std::set<int> unaccountedControlAreas;
	std::set<int> diagonalControlAreas;
	if (laste->node.hasControlArea) {
		auto data = navigator->getExtraData(laste->cell);
		curControlAreaSetIndex = data->controlAreaSetIndex;
	}
	if (controlAreaAllocations.size() > 0) {
		auto& activeControlAreas = navigator->controlAreaSets[curControlAreaSetIndex];
		for (auto alloc : controlAreaAllocations) {
			if (alloc->deallocateEvent)
				destroyevent(alloc->deallocateEvent);
 			alloc->traversalDist = DBL_MAX;
			int index = navigator->getControlAreaIndex(alloc->getObject());
			if (activeControlAreas.find(index) == activeControlAreas.end())
				unaccountedControlAreas.insert(index);
		}

	}

	UserNavigationResult userResult = (UserNavigationResult)(int)FIRE_SDT_EVENT_VALUE_GETTER(onNavigatePath, te->holder, startAtPathIndex + 1, kinematics);
	if ((userResult & UserNavigationResult::AbortAll))
		return;

	int didBlockPathIndex = -1;
	BridgeRoutingData* bridgeArrival = nullptr;
	int i = startAtPathIndex;
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
		initkinematics(kinematics, atDist, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0);
		auto& first = travelPath[startAtPathIndex];
		if (!startBetweenCells) {
			first.arrivalTime = curTime;
			first.atTravelDist = atDist;
			first.startSpeed = curSpeed;
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
				Vec3 diff = e->modelLoc - prevLoc;
				double dist = diff.magnitude;
				double kinDist = dist;
				double startTime = endTime;
				if (isExitingBridge) {
					step.isDiagonal = false;
					step.isHorizontalDeepSearch = false;
					step.isVerticalDeepSearch = false;
					isExitingBridge = false;
				}

				if (nav->stopForTurns) {
					double nextRot = diff.getXYAngle();
					double rotDiff = nextRot - lastRotation;
					while (rotDiff > 180)
						rotDiff -= 360;
					while (rotDiff < -180)
						rotDiff += 360;

					if (fabs(rotDiff) > 0.1 && (i > startAtPathIndex + 1 || (!startBetweenCells && te->v_modifyrotation))) {
						double timeToTurn = fabs(rotDiff / turnSpeed);
						// make him travel a tiny distance to the next point so that TravelPath::update() will actually update rotation.
						double turnDist = 0.0001 * dist;
						kinDist -= turnDist;
						addkinematic(kinematics, turnDist, 0.0, 0.0, turnDist / timeToTurn, 0, 0, 0.0, 0.0, startTime, KINEMATIC_TRAVEL);
						startTime += turnDelay + timeToTurn;
						if (lastAllocation)
							lastAllocation->extendReleaseTime(startTime + deallocTimeOffset);
						e->turnEndTime = startTime;
					}
					lastRotation = nextRot;
				}

				atDist += dist;
				e->atTravelDist = atDist;
				double startSpeed = curSpeed;
				e->startSpeed = startSpeed;
				endTime = addkinematic(kinematics, kinDist, 0, 0, maxSpeed, acc, dec, startSpeed, std::min(maxSpeed, e->maxArrivalSpeed), startTime, KINEMATIC_TRAVEL);
				if (dec == 0 || e->maxArrivalSpeed >= endSpeed)
					endArrivalTime = endTime;
				int numKinematics = getkinematics(kinematics, KINEMATIC_NR);
				curSpeed = getkinematics(kinematics, KINEMATIC_ENDSPEED, numKinematics);
				e->arrivalTime = endTime;

				double allocTime = startTime;
				// check if I need to find a proper alloc time
				if (enableCollisionAvoidance || e->node.hasControlArea) {
					if (dec > 0 && e->turnEndTime == -1.0) {
						double totalDist = 0;
						// search back through the travel path to find the point where I would need to decelerate to stop
						for (int j = i - 1; j >= startAtPathIndex; j--) {
							auto& entry = travelPath[j];
							if (entry.turnEndTime > 0) {
								allocTime = std::max(curTime, entry.turnEndTime);
								break;
							}
							totalDist += entry.distFromPrev;
							double distToDecel = 0.5 * entry.startSpeed * (entry.startSpeed / dec);
							if (j == startAtPathIndex || distToDecel <= totalDist + tinyDist) {
								// te can decelerate to stop after starting to travel to this cell, so 
								// set the allocation time to the arrival time at the previous cell
								// note I don't try to calculate some 'in-between' allocation time 
								// based on some math solution of acc/dec/startSpeed/endSpeed/etc. for 
								// simplicity's sake. Maybe at some future time I'll do that, but for 
								// now just say I allocate at arrival of the previous cell.
								allocTime = j > startAtPathIndex ? travelPath[j - 1].arrivalTime : curTime;
								break;
							}
						}
					}
				}
				bool doControlAreaProcessing = e->node.hasControlArea || curControlAreaSetIndex != AStarNavigator::EMPTY_CONTROL_AREA_SET_INDEX;
				if (!doControlAreaProcessing && step.isDiagonal)
					doControlAreaProcessing = navigator->getNode(step.intermediateCell1)->hasControlArea || navigator->getNode(step.intermediateCell2)->hasControlArea;

				if (doControlAreaProcessing) {
					auto setIndex = e->node.hasControlArea ? navigator->getExtraData(e->cell)->controlAreaSetIndex : AStarNavigator::EMPTY_CONTROL_AREA_SET_INDEX;

					doControlAreaProcessing = setIndex != curControlAreaSetIndex;
					if (!doControlAreaProcessing && step.isDiagonal) {
						for (int i = 0; i < 2; i++) {
							auto cell = i == 0 ? step.intermediateCell1 : step.intermediateCell2;
							int index = navigator->getNode(cell)->hasControlArea ? navigator->getExtraData(cell)->controlAreaSetIndex : 0;
							if (index != curControlAreaSetIndex) {
								doControlAreaProcessing = true;
								break;
							}
						}
					}
					if (doControlAreaProcessing) {
						auto& lastSet = navigator->controlAreaSets[curControlAreaSetIndex];
						auto& nextSet = navigator->controlAreaSets[setIndex];
						int loopEnd = 1;
						if (step.isDiagonal) {
							loopEnd = 2;
							diagonalControlAreas.clear();
							for (int i = 0; i < 2; i++) {
								auto cell = i == 0 ? step.intermediateCell1 : step.intermediateCell2;
								int diagSetIndex = navigator->getNode(cell)->hasControlArea ? navigator->getExtraData(cell)->controlAreaSetIndex : 0;
								if (diagSetIndex == setIndex)
									continue;
								auto& diagSet = navigator->controlAreaSets[diagSetIndex];
								for (int index : diagSet) {
									if (nextSet.find(index) == nextSet.end())
										diagonalControlAreas.insert(index);
								}
							}
						}
						nextEvent = nullptr;
						// check if I'm going to enter an area
						for (int j = 0; j < loopEnd && !nextEvent; j++) {
							auto& set = j == 0 ? nextSet : diagonalControlAreas;
							for (int index : set) {
								bool isInLastSet = lastSet.find(index) != lastSet.end();
								bool isInUnaccountedSet = unaccountedControlAreas.find(index) != unaccountedControlAreas.end();
								if (!isInLastSet && !isInUnaccountedSet) {
									nextEvent = createevent(FlexSimEvent::create(holder, allocTime, "Control Area Arrival",
										[this, index, i]() { onControlAreaArrival(index, i); }))->object<FlexSimEvent>();
									break;
								}
								else if (isInUnaccountedSet) {
									unaccountedControlAreas.erase(index);
								}
							}
							if (nextEvent)
								break;
						}
						if (nextEvent)
							break;


						for (int j = 0; j < loopEnd; j++) {
							auto& set = j == 0 ? lastSet : diagonalControlAreas;
							// check if I'm going to leave an area
							for (auto index : set) {
								if (nextSet.find(index) != nextSet.end())
									continue;
								// need to deallocate a control area
								ObjRef<ObjectDataType> ca = navigator->controlAreas[index];

								// figure out the distance at which the object crosses the line of the control area
								Vec2 corners[5] = {
									ca->getLocation(0.0, 0.0, 0.0).project(ca->holder->up, model()).xy, // top left
									ca->getLocation(1.0, 0.0, 0.0).project(ca->holder->up, model()).xy, // top right
									ca->getLocation(1.0, 1.0, 0.0).project(ca->holder->up, model()).xy, // bottom right
									ca->getLocation(0.0, 1.0, 0.0).project(ca->holder->up, model()).xy, // bottom left
									Vec2(0, 0) // top left
								};
								corners[4] = corners[0];
								auto fromLoc = navigator->getLocation(laste->cell).xy;
								auto toLoc = navigator->getLocation(e->cell).xy;
								auto lineDist = (toLoc - fromLoc).magnitude;
								Line2 travelLine(fromLoc, toLoc);
								double traversalDist = atDist - dist;
								for (int k = 0; k < 4; k++) {
									auto intersection = travelLine.intersect(Line2(corners[k], corners[k + 1]));
									if (intersection.isValid && intersection.distAlong1 >= 0.0 && intersection.distAlong1 <= lineDist) {
										auto compareDist = atDist - lineDist + intersection.distAlong1;
										if (compareDist > traversalDist)
											traversalDist = compareDist;
									}
								}

								auto allocPointIter = std::find_if(controlAreaAllocations.begin(), controlAreaAllocations.end(),
									[&ca](TravelAllocation* alloc) { return ca == alloc->getObject(); });
								if (allocPointIter != controlAreaAllocations.end()) {
									ObjRef<TravelAllocation> alloc = *(*allocPointIter);
									NodeRef validityCheck = holder;

									double releaseTime = endTime;
									alloc->traversalDist = traversalDist;
									if (atDist - traversalDist > tinyDist) {
										releaseTime = getkinematics(kinematics, KINEMATIC_ARRIVALTIME, numKinematics, traversalDist - (atDist - dist));
									}

									if (!alloc->deallocateEvent || alloc->deallocateEvent->objectAs(FlexSimEvent)->time != releaseTime) {
										auto onExit = [this, validityCheck, ca, alloc]() {
											if (!validityCheck || !ca || !alloc)
												return;
											onControlAreaExit(alloc);
										};
										if (alloc->deallocateEvent)
											destroyevent(alloc->deallocateEvent);
										alloc->deallocateEvent = createevent(FlexSimEvent::create(holder, releaseTime, "Control Area Exit", onExit));
									}
								}
							}
							curControlAreaSetIndex = setIndex;
						}
					}
				}
				if (enableCollisionAvoidance) {
					double releaseTime = std::nextafter(endTime + deallocTimeOffset, DBL_MAX);
					NodeAllocation allocation(this, e->cell, i, 0, allocTime, releaseTime, 1.0);
					bool success = true;
					NodeAllocation* intermediate1 = nullptr;
					NodeAllocation* intermediate2 = nullptr;
					// if it is a diagonal move, then I need to do additional allocations
					if (step.isDiagonal) {
						// is it a deep vertical search step
						double distToMiddle = std::max(0.0, dist - 0.5 * e->distFromPrev);
						if (distToMiddle > 0.0) {
							double middleTraverseTime = getkinematics(kinematics, KINEMATIC_ARRIVALTIME, numKinematics, distToMiddle);
							allocation.atTravelDist = atDist + distToMiddle;
							allocation.releaseTime = middleTraverseTime + deallocTimeOffset;
							allocation.traversalWeight = (step.isVerticalDeepSearch || step.isHorizontalDeepSearch) ? 0.5 : 0.0;
							allocation.cell = step.intermediateCell1;
							allocation.atTravelDist = atDist - dist + distToMiddle;
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
							allocation.atTravelDist = atDist;
							allocation.releaseTime = releaseTime;
						}
					}
					if (success) {
						allocation.cell = e->cell;
						allocation.atTravelDist = atDist;
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
			if (atDist > navigatedDist) {
				nav->assertExtraData(e->cell, TraversalData)->totalTraversals++;
				nav->heatMapTotalTraversals++;
				if (step.isVerticalDeepSearch || step.isHorizontalDeepSearch) {
					nav->assertExtraData(step.intermediateCell1, TraversalData)->totalTraversals += 0.5;
					nav->assertExtraData(step.intermediateCell2, TraversalData)->totalTraversals += 0.5;
					nav->heatMapTotalTraversals++;
				}
				navigatedDist = atDist;
			}

			laste = e;
			prevLoc = e->modelLoc;
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

	}
	if (enableCollisionAvoidance && initialAllocsSize > 0 && !(userResult & UserNavigationResult::KeepAllocations)) {
		for (int i = std::min((int)allocations.size(), initialAllocsSize) - 1; i >= 0; i--) {
			if (allocations[i]->isMarkedForDeletion) {
				removeAllocation(allocations.begin() + i);
				while (i > allocations.size())
					i--;
			}
		}
	}

	if (bridgeArrival) {
		// Create a BridgeArrivalEvent
		assertBridgeData(bridgeArrival);
		nextEvent = createevent(new BridgeRoutingData::ArrivalEvent(bridgeArrival, this, i - 1, endTime))->objectAs(BridgeRoutingData::ArrivalEvent);
	}

	if (activeState == Inactive) {
		nav->activeTravelers.push_front(this);
		activeEntry = nav->activeTravelers.begin();
	}
	activeState = Active;
	if (didBlockPathIndex == -1 && !nextEvent && blockMode == BlockMode::None && i == numNodes && userResult == UserNavigationResult::Default) {
		nextEvent = createevent(new ArrivalEvent(this, endArrivalTime, dec == 0 || endArrivalTime == endTime))->objectAs(ArrivalEvent);
	}

	// deallocate any remaining unaccounted allocated control areas
	for (auto index : unaccountedControlAreas) {
		auto ca = navigator->controlAreas[index];
		auto allocPointIter = std::find_if(controlAreaAllocations.begin(), controlAreaAllocations.end(),
			[&ca](TravelAllocation* alloc) { return ca == alloc->getObject(); });
		if (allocPointIter != controlAreaAllocations.end()) {
			auto alloc = *(*allocPointIter);
			alloc->deallocate();
		}
	}

	isRoutingNow = false;
	XE
}


void Traveler::navigatePath(TravelPath&& path)
{
	travelPath = std::move(path);
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
	if (blockMode != BlockMode::None)
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
	if (bridge)
		te->updateTotalTravelDist(bridge->travelDistance);
	// With Agent systems, the navigator isn't the A* navigator, so I shouldn't continue navigating 
	// the path
	bool isAStarNavigator = ownerobject(te->node_v_navigator->first->value) == navigator->holder;
	if (!isAStarNavigator)
		// temporary fix. In reality there should be some travel time for the agent to get out of the way
		bridgeData->routingData->onExit(this);
	FIRE_SDT_EVENT(onBridgeContinueTrigger, te->holder, bridge ? (Variant)bridge->holder : Variant());
	if (travelPath[atPathIndex].atTravelDist == DBL_MAX && atPathIndex > 0)
		travelPath[atPathIndex].atTravelDist = travelPath[atPathIndex - 1].atTravelDist;
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
			[&](NodeAllocationIterator& otherIter) {
				auto& other = *otherIter;
				auto* collideWith = &other;
				if (collideWith->traveler == this) {
					selfCollision = collideWith;
					return VISIT_CONTINUE;
				}
				NodeAllocation* laterAllocation = (allocation.acquireTime < collideWith->acquireTime || force) ? collideWith : &allocation;
				Traveler* laterTraveler = laterAllocation->traveler;
				NodeAllocation* earlierAllocation = laterAllocation == collideWith ? &allocation : collideWith;
				Traveler* earlierTraveler = earlierAllocation->traveler;

				double eventTime = laterAllocation->acquireTime;
				BlockEvent* event = new BlockEvent(laterTraveler, laterAllocation->atTravelDist, laterAllocation->intermediateAllocationIndex,
					earlierTraveler, allocation.cell, std::max(time(), eventTime));

				// check to see if I need to create a block event for the later traveler
				if (!laterTraveler->blockEvent || *(event) < *(laterTraveler->blockEvent)) {
					if (laterTraveler->blockMode == BlockMode::None) {
						if (laterTraveler->nextEvent)
							destroyevent(laterTraveler->nextEvent);
						laterTraveler->blockEvent = createevent(event)->objectAs(BlockEvent);
						laterTraveler->nextEvent = laterTraveler->blockEvent;
					}

					if (laterAllocation != &allocation) {
						// if the guy I'm colliding with is the later allocation, then I need to get rid of any events and 
						// additional allocations that come after that guy's allocation, because he's going to be the 
						// guy to stop, so subsequent allocations are invalid at the point when he stops.
						auto iter = laterTraveler->find(laterAllocation);
						while (iter - laterTraveler->allocations.begin() >= 2 && (*(iter - 1))->atTravelDist >= laterAllocation->atTravelDist)
							iter--;
						++otherIter;
						while (otherIter != nodeData->allocations.end() && otherIter->traveler == laterTraveler)
							++otherIter;
						laterTraveler->clearAllocations(iter, true);
						return VISIT_CONTINUE | VISIT_NO_INC_ITER;
					}
					else // if I am the later collision, then I should mark that I am blocked
						iAmBlocked = true;
				}
				else {
					delete event;
				}
				return VISIT_CONTINUE;
			}
		);

		if (selfCollision) {
			double oldReleaseTime = selfCollision->releaseTime;
			double oldAcquireTime = selfCollision->acquireTime;
			*selfCollision = allocation;
			if (allocation.releaseTime > oldReleaseTime) {
				selfCollision->releaseTime = oldReleaseTime;
				selfCollision->changeReleaseTime(allocation.releaseTime);
			}
			else if (nodeData->requests.size() > 0) {
				nodeData->checkCreateContinueEvent();
			}
			selfCollision->isMarkedForDeletion = false;

			// the allocations list should always be sorted in the order of atTravelDist
			// changing the allocation may have made the allocations list unordered, so I need to reorder it
			for (int i = allocations.size() - 1; i >= 0; i--) {
				if (&(*(allocations[i])) == selfCollision) {
					while (i < allocations.size() - 1 && allocations[i + 1]->atTravelDist < selfCollision->atTravelDist) {
						std::swap(allocations[i], allocations[i + 1]);
						i++;
					}
					while (i > 0 && allocations[i - 1]->atTravelDist > selfCollision->atTravelDist) {
						std::swap(allocations[i], allocations[i - 1]);
						i--;
					}

					break;
				}
			}

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
		[&](NodeAllocationIterator& otherIter) {
			auto& other = *otherIter;
			if (other.acquireTime < minAcquireTime) {
				best = &other;
				minAcquireTime = other.acquireTime;
				if (other.acquireTime < curTime)
					return VISIT_ABORT;
			}
			return VISIT_CONTINUE;
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
		removeAllocation(allocations.end() - 1);
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

	for (auto alloc : controlAreaAllocations) {
		auto shift = [atTravelDist](double& val) {
			if (val < FLT_MAX)
				val -= atTravelDist;
		};
		shift(alloc->stopAtDist);
		shift(alloc->arrivalDist);
		shift(alloc->traversalDist);
	}
	navigatedDist = 0;
	atTravelDist = 0;
}

void Traveler::onBlock(Traveler* collidingWith, double colliderTravelDist, Cell& cell)
{
	XS
	blockEvent = nullptr;
	nextEvent = nullptr;
	cullExpiredAllocations();
	double atTravelDist = updateLocation(true);
	bool shouldStop = true;
	if (travelPath.back().atTravelDist < colliderTravelDist)
		shouldStop = false;
	auto allocPathIndex = travelPath.getIndex(colliderTravelDist, true);

	AStarNodeExtraData* nodeData = navigator->getExtraData(cell);
	double curTime = time();
	auto foundAlloc = std::find_if(nodeData->allocations.begin(), nodeData->allocations.end(),
		[&](NodeAllocation& alloc) { return alloc.traveler == collidingWith && alloc.acquireTime <= curTime && alloc.releaseTime > curTime; }
		);
	
	if (shouldStop && foundAlloc == nodeData->allocations.end())
		shouldStop = false;

	int stopAtPathIndex = allocPathIndex - 1;
	int atPathIndex = stopAtPathIndex;
	double distToStop = 0;
	double dec = te->v_deceleration;

	// Look at this traveler's travel path, starting from the end working backwards.
	// Find the point just ahead of where the traveler is now.
	if (dec > 0) {
		distToStop = travelPath[stopAtPathIndex].atTravelDist - atTravelDist;
		while (atPathIndex > 0 && travelPath[atPathIndex].atTravelDist > atTravelDist + tinyDist)
			atPathIndex--;
	}

	if (shouldStop) {
		double curSpeed = getCurSpeed();
		double stopAtDist = atTravelDist + distToStop;
		initkinematics(kinematics, atTravelDist, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0);

		setstate(te->holder, STATE_BLOCKED);

		lastBlockTime = curTime;
		for (int i = atPathIndex + 1; i < travelPath.size(); i++) {
			if (travelPath[i].arrivalTime == -1.0)
				break;
			travelPath[i].arrivalTime = -1;
		}
		double stopAtTime = curTime;
		double startSpeed = curSpeed;
		double tempTime = curTime;
		double maxSpeed = te->v_maxspeed;
		double acc = te->v_acceleration;
		auto allocIter = allocations.begin();

		// For each entry in the travel path that is ahead of the traveler
		for (int i = atPathIndex + 1; i <= stopAtPathIndex; i++) {
			auto& toEntry = travelPath[i];
			// Calculate the distance to the next entry in the path
			auto dist = toEntry.atTravelDist - atTravelDist;
			if (dist > 0.0) {
				// Solve for endSpeed given travel dist, start speed, and deceleration
				// dist =    avgSpeed    *    travelTime
				// dist = (endSpeed / 2) * (endSpeed / dec);
				// dist * 2 * dec = endSpeed^2
				// endSpeed = sqrt(dist * 2 * dec)
				distToStop -= dist;
				auto endSpeed = std::min(maxSpeed, sqrt(std::max(0.0, distToStop * 2 * dec)));
				tempTime = addkinematic(kinematics, dist, 0, 0, maxSpeed, acc, dec, startSpeed, endSpeed, tempTime, KINEMATIC_TRAVEL);
				startSpeed = endSpeed;
			}
			// Mark the next arrival time given the deceleration
			toEntry.arrivalTime = tempTime;

			// For each allocation that is physically behind the current travel path
			while (allocIter != allocations.end() && (*allocIter)->atTravelDist < toEntry.atTravelDist - tinyDist) {
				auto alloc = *allocIter;
				double releaseTime = tempTime;
				if (dist > 0.0)
					releaseTime = getkinematics(kinematics, KINEMATIC_ARRIVALTIME, getkinematics(kinematics, KINEMATIC_NR), std::max(0.0, alloc->atTravelDist - atTravelDist));

				// Reset the allocation's release time to account for the slowdown.
				// releaseTime is the moment when the traveler reaches the next path entry.
				// Some allocations are already in their "deallocTimeOffset" portion.
				// For those allocations, I want them to release as normal.
				bool shouldAdjustReleaseTime = navigator->deallocTimeOffset <= 0.0
					|| alloc->releaseTime > (curTime + navigator->deallocTimeOffset);

				if (shouldAdjustReleaseTime) {
					alloc->changeReleaseTime(std::nextafter(releaseTime + navigator->deallocTimeOffset, DBL_MAX));
				}
				allocIter++;
			}
			atTravelDist = toEntry.atTravelDist;
		}
		for (; allocIter != allocations.end(); allocIter++) {
			if ((*allocIter)->atTravelDist >= stopAtDist - tinyDist)
				(*allocIter)->extendReleaseTime(DBL_MAX);
		}
		stopAtTime = tempTime;

		Array deadlockList;
		NodeAllocation requestedAlloc(this, cell, allocPathIndex, 0, curTime, DBL_MAX, 0.0);
		request = nodeData->addRequest(requestedAlloc, &deadlockList);
		bool isDeadlock = deadlockList.size() > 0;
		blockMode = BlockMode::Node;
		blockedAtTravelPathIndex = atPathIndex;
		if (onBlockTrigger && (!nodeData->continueEvent || nodeData->continueEvent->time - curTime > tinyTime)) {
			if (FIRE_SDT_EVENT_VALUE_GETTER(onBlockTrigger, te->holder, isDeadlock, atPathIndex))
				return;//???
			needsContinueTrigger = true;
		}
		if (isDeadlock) {
			navigateAroundDeadlock(deadlockList);
		}
	} else {
		navigatePath(atPathIndex);
	}
	XE
}


bool Traveler::navigateAroundDeadlock(Array& deadlockListArray)
{
	double curTime = time();
	std::multimap<Traveler*, treenode> dynamicBarriers;

	// convert the Array to std::vector, filtering out non-A*-travelers if there are any
	std::vector<Traveler*> deadlockList;
	deadlockList.reserve(deadlockListArray.length);
	for (int i = 1; i <= deadlockListArray.length - 1; i++) {
		TreeNode* travelerNode = deadlockListArray[i];
		if (isclasstype(travelerNode, CLASSTYPE_TASKEXECUTER)) {
			auto traveler = navigator->getTraveler(travelerNode->object<TaskExecuter>());
			if (traveler)
				deadlockList.push_back(traveler);
		}
	}

	std::function<void(Traveler*)> addDynamicBarrier = [&](Traveler* traveler) -> void {
		if (dynamicBarriers.find(traveler) != dynamicBarriers.end())
			return;
		for (auto& alloc : traveler->allocations) {
			if (alloc->releaseTime == DBL_MAX) {
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
	for (auto traveler : deadlockList) {
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
			if (alloc && alloc.traveler->blockMode == BlockMode::Node) {
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
		double atDist = traveler->updateLocation() - 2.0 * tinyDist;
		auto atIndex = traveler->travelPath.updateAtIndex(atDist, true);
		auto savedLoc = traveler->te->getLocation(0.5, 0.5, 0.0);
		auto startLoc = navigator->getLocation(traveler->travelPath[atIndex].cell).project(model(), traveler->te->holder->up);
		traveler->te->setLocation(startLoc, Vec3(0.5, 0.5, 0.0));
		TravelPath testPath = navigator->calculatePath(traveler, destLoc, DestinationThreshold(), AStarNavigator::DoFullSearch | AStarNavigator::KeepEndpointsConst, -1.0);
		traveler->te->setLocation(savedLoc, Vec3(0.5, 0.5, 0.0));

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
		if (bestTraveler->request) {
			navigator->getExtraData(bestTraveler->request->cell)->requests.remove_if([&](NodeAllocation& alloc) { return &alloc == bestTraveler->request; });
			bestTraveler->request = nullptr;
		}
		else if (bestTraveler->controlAreaAllocations.size() > 0 && bestTraveler->controlAreaAllocations.back()->isRequestActive())
			bestTraveler->controlAreaAllocations.back()->holder->destroy();
		FIRE_SDT_EVENT(bestTraveler->onRerouteTrigger, te->holder);
		Cell curCell = bestPath[0].cell;
		//TravelPath newPath;
		//newPath.push_back(AStarPathEntry(curCell, -1));
		//newPath.push_back(AStarPathEntry(bestCell, -1));
		bestTraveler->cullExpiredAllocations();
		double curSpeed = bestTraveler->getCurSpeed();
		double atTravelDist = bestTraveler->updateLocation(true);
		Vec3 curModelLoc = bestTraveler->te->getLocation(0.5, 0.5, 0.0).project(bestTraveler->te->holder->up, model());
		auto atIndex = bestTraveler->travelPath.updateAtIndex(atTravelDist, true);
		auto distFromCell = (bestTraveler->travelPath[atIndex].modelLoc - curModelLoc).magnitude;

		if (bestPath.back().cell != destCell)
			bestTraveler->isNavigatingAroundDeadlock = true; // flag it to reroute again on arrival if this rerouted path doesn't get me there
		bestPath.front().atTravelDist = atTravelDist + distFromCell;
		bestPath.startZRot = bestTraveler->te->b_spatialrz;
		if (atIndex > 0 && distFromCell > bestTraveler->tinyDist) {
			auto entry = bestTraveler->travelPath[atIndex - 1];
			if (navigator->smoothRotations != 0.0 && !navigator->stopForTurns == 0.0) {
				bestTraveler->travelPath.update(bestTraveler, entry.atTravelDist); // update to the previouse cell to get the proper rotation
				bestPath.startZRot = bestTraveler->te->b_spatialrz;
				// don't need to update back because he'll update anyway
			}
			bestPath.front().distFromPrev = (entry.modelLoc - bestPath.front().modelLoc).magnitude;
			// inefficient, but hopefully this won't happen often
			bestPath.insert(bestPath.begin(), entry);
		}
		bestTraveler->navigatePath(std::move(bestPath));
	} else {
		string error = "Unrecoverable deadlock encountered for ";
		error.append(holder->name.c_str()).append(". Model stopped");
		EX(error.c_str(), "", 1);
		stop();
	}

	return true;
}

bool Traveler::findDeadlockCycle(ObjectDataType* start, Array& cycle)
{
	cycle.push(te->holder);
	double curTime = time();
	if (request) {
		AStarNodeExtraData* data = navigator->getExtraData(request->cell);
		auto& allocations = data->allocations;
		cycle.push(data->holder);
		for (auto& alloc : allocations) {
			//NodeAllocation& alloc = *allocIter;
			if (alloc.acquireTime > curTime || alloc.releaseTime != DBL_MAX || alloc.traveler == this)
				continue;

			auto traveler = alloc.traveler;
			if (traveler->te == start) {
				cycle.push(traveler->te->holder);
				return true;
			}
			if (traveler->findDeadlockCycle(start, cycle)) {
				return true;
			}
		}
		cycle.pop();
	}
	if (controlAreaAllocations.size() > 0) {
		auto request = controlAreaAllocations.back();
		if (request->isRequestActive()) {
			auto allocatable = request->getObject();
			if (allocatable && isclasstype(allocatable->holder, CLASSTYPE_FLEXSIMEVENTHANDLER)) {
				cycle.push(allocatable->holder);
				if (((FlexSimEventHandler*)allocatable)->findDeadlockCycle(start, cycle))
					return true;
				cycle.pop();
			}
		}
	}
	cycle.pop();
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
	if (nextEvent)
		destroyevent(nextEvent);
	clearAllocations();
}

void Traveler::onControlAreaArrival(int areaIndex, int travelPathIndex)
{
	nextEvent = nullptr;
	double atDist = updateLocation(true);
	TravelAllocation* alloc = nullptr;
	auto controlArea = navigator->controlAreas[areaIndex];
	auto existing = std::find_if(controlAreaAllocations.begin(), controlAreaAllocations.end(), [&](TravelAllocation* alloc) { return alloc->getObject() == controlArea; });
	auto& prevEntry = travelPath[travelPathIndex - 1];
	if (existing == controlAreaAllocations.end()) {
		alloc = controlArea->allocate(te);
		if (alloc) {
			alloc->holder->up = controlAreaAllocations;
			alloc->stopAtDist = prevEntry.atTravelDist;
			alloc->arrivalDist = travelPath[travelPathIndex].atTravelDist;
			alloc->traversalDist = DBL_MAX;
		}
	}
	else if ((*existing)->isRequestActive())
		alloc = *existing;

	if (!alloc || !alloc->isRequestActive()) {
		navigatePath(travelPathIndex - 1);
	}
	else {
		double curSpeed = getCurSpeed();
		double toDist = prevEntry.atTravelDist;
		initkinematics(kinematics, atDist, 0.0, 0.0);

		blockMode = BlockMode::ControlArea;
		setstate(te->holder, STATE_BLOCKED);

		addkinematic(kinematics, toDist - atDist, 0.0, 0.0, te->v_maxspeed, te->v_acceleration, te->v_deceleration, curSpeed, 0.0, time(), KINEMATIC_TRAVEL);
		for (auto alloc : allocations) {
			if (alloc->atTravelDist >= toDist - tinyDist)
				alloc->extendReleaseTime(DBL_MAX);
		}

		Array deadlockCycle;
		deadlockCycle.reserve(10);

		NodeRef validityCheck = holder;
		auto onAllocate = [this, validityCheck, travelPathIndex]() {
			if (!validityCheck || blockMode != BlockMode::ControlArea)
				return;
			navigatePath(travelPathIndex - 1);
		};
		FlexSimEvent::listen(alloc, "OnAllocate", 0, onAllocate);

		bool foundDeadlock = findDeadlockCycle(te, deadlockCycle);
		if (foundDeadlock)
			navigateAroundDeadlock(deadlockCycle);
	}
}


void Traveler::onControlAreaExit(const ObjRef<TravelAllocation>& alloc)
{
	double dist = updateLocation();
	if (dist >= alloc->traversalDist - this->tinyDist) {
		if (navigator->deallocTimeOffset > 0) {
			createevent(FlexSimEvent::create(holder, time() + navigator->deallocTimeOffset, "Control Area Release",
				[alloc]() { if (alloc) alloc->deallocate(); }));
		}
		else alloc->deallocate();
	}
	else {
		// something has intervened in the mean time so that the guy is not all the way to the 
		// exit point (a block or something else). So figure out when I'm going to reach the exit point 
		// using kinematic queries
		double distAtEnd = getkinematics(kinematics, KINEMATIC_X, 0, FLT_MAX);
		if (distAtEnd >= alloc->traversalDist) {
			int rank = getkinematics(kinematics, KINEMATIC_NR);
			while (rank > 1 && getkinematics(kinematics, KINEMATIC_X, 0, getkinematics(kinematics, KINEMATIC_STARTTIME, rank)) > alloc->traversalDist)
				rank--;
			double startTime = getkinematics(kinematics, KINEMATIC_STARTTIME, rank);
			double distFromKinStart = alloc->traversalDist - getkinematics(kinematics, KINEMATIC_X, 0, startTime);
			if (distFromKinStart > 0) {
				double releaseTime = getkinematics(kinematics, KINEMATIC_ARRIVALTIME, rank, distFromKinStart);

				NodeRef validityCheck = holder;
				auto onExit = [this, alloc, validityCheck]() {
					if (!validityCheck || !alloc)
						return;
					onControlAreaExit(alloc);
				};
				alloc->deallocateEvent = createevent(FlexSimEvent::create(holder, releaseTime, "Control Area Exit", onExit));
			}
			else alloc->deallocate();
		}
	}
}

void Traveler::finalizeAtLocation(double& atTravelDist)
{
	AStarPathEntry back = travelPath.back();
	travelPath.clear();
	travelPath.push_back(back);
	resetTravelDist(atTravelDist);
	initkinematics(kinematics, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0);
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

void Traveler::onArrival(bool isAtZeroSpeed)
{
	nextEvent = nullptr;
	double atTravelDist = updateLocation(true);
	updateSpeedMarkers();
	cullExpiredAllocations();
	
	if (isAtZeroSpeed) {
		finalizeAtLocation(atTravelDist);
	}

	if (activeState == Active) {

		if (!isNavigatingAroundDeadlock) {
			if (isAtZeroSpeed || te->v_useoffsets == OFFSET_BY_TE_LOGIC) {
				activeState = Inactive;
				navigator->activeTravelers.erase(activeEntry);
			}
			else {
				activeState = DecelToStop;
				shouldFinishTravelPath = true;
				double endTime = getkinematics(kinematics, KINEMATIC_ENDTIME, getkinematics(kinematics, KINEMATIC_NR));
				nextEvent = createevent(new ArrivalEvent(this, endTime, true))->object<ArrivalEvent>();
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
			newPath.front().atTravelDist = atTravelDist;
			newPath.startZRot = te->b_spatialrz;
			navigatePath(std::move(newPath));
		}
	}
	else if (activeState == DecelToStop) {
		activeState = Inactive;
		shouldFinishTravelPath = false;
		navigator->activeTravelers.erase(activeEntry);
	}
}

void Traveler::abortTravel(TreeNode* newTS)
{
	if (nextEvent)
		destroyevent(nextEvent);

	double atDist = updateLocation(true);
	updateSpeedMarkers();
	auto curSpeed = getCurSpeed();
	double distToStop = 0.0;
	if (curSpeed > 0 && te->v_deceleration > 0)
		distToStop = (0.5 * curSpeed) * (curSpeed / te->v_deceleration);
	double stopAtDist = atDist + distToStop;
	double stopAtTime = time();
	if (!bridgeData || !bridgeData->routingData) {
		// reset the travel path to a shortened path that just gets me to 
		// a stop
		TravelPath newTravelPath;
		auto atIndex = travelPath.updateAtIndex(atDist, false) - 1;
		auto iter = travelPath.begin() + atIndex;
		while (iter != travelPath.end()) {
			auto& entry = *iter;
			newTravelPath.push_back(entry);
			if (entry.atTravelDist >= stopAtDist)
				break;
			++iter;
		}
		travelPath = std::move(newTravelPath);
		initkinematics(kinematics, atDist, 0.0, 0.0, 0.0, 0.0, 0.0);
		stopAtTime = addkinematic(kinematics, travelPath.back().atTravelDist - atDist, 0, 0,
			te->v_maxspeed, te->v_acceleration, te->v_deceleration, curSpeed, 0.0, time(), KINEMATIC_TRAVEL);
	}

	if (navigator->enableCollisionAvoidance) {
		if (request) {
			navigator->getExtraData(request->cell)->requests.remove_if([&](NodeAllocation& alloc) { return &alloc == request; });
			request = nullptr;
		}
		if (navigator->ignoreInactiveMemberCollisions)
			clearAllocations();
		else {
			cullExpiredAllocations();
			Vec3 loc = te->getLocation(0.5, 0.5, 0.0);
			if (te->holder->up != model())
				loc = loc.project(te->holder->up, model());
			while (allocations.size() > 1 && allocations.back()->acquireTime > time())
				clearAllocations(allocations.end() - 1);

			auto endCell = travelPath.back().cell;
			for (int i = (int)allocations.size() - 1; i >= 0; i--) {
				auto& alloc = allocations[i];
				if (alloc->atTravelDist > stopAtDist)
					removeAllocation(allocations.begin() + i);
				else if (alloc->cell == endCell)
					alloc->extendReleaseTime(DBL_MAX);
				else {
					double traversalTime = getkinematics(kinematics, KINEMATIC_ARRIVALTIME, 1, std::max(0.0, alloc->atTravelDist - atDist));
					alloc->changeReleaseTime(traversalTime + navigator->deallocTimeOffset);
				}
			}
			if (allocations.size() == 0) {
				addAllocation(NodeAllocation(this, endCell, 0, 0, time(), DBL_MAX, 0.0), true, true);
			}
		}
	}

	if (controlAreaAllocations.size() > 0 && controlAreaAllocations.back()->isRequestActive())
		controlAreaAllocations.remove(controlAreaAllocations.size() - 1);

	if (bridgeData && bridgeData->routingData) {
		bridgeData->routingData->onAbort(this);
		bridgeData->routingData = nullptr;
	}

	if (distToStop == 0.0) {
		navigator->activeTravelers.erase(activeEntry);
		activeState = Inactive;
	}
	else {
		activeState = DecelToStop;
		auto onStopped = [this]() {
			double atDist = updateLocation(true);
			updateSpeedMarkers();
			finalizeAtLocation(atDist);
			navigator->activeTravelers.erase(activeEntry);
			activeState = Inactive;
		};
		nextEvent = createevent(FlexSimEvent::create(holder, stopAtTime, "Traveler Stopped", onStopped))->object<FlexSimEvent>();
	}
}

double Traveler::updateLocation(bool updateTravelDistStats)
{
	if (activeState == Inactive)
		return 0.0; 

	if (bridgeData && bridgeData->routingData) {
		bridgeData->routingData->updateLocation(this);
	} else {
		double x = getkinematics(kinematics, KINEMATIC_X);
		travelPath.update(this, x);
		if (updateTravelDistStats) {
			te->updateTotalTravelDist(fabs(x - lastStatUpdateTravelDist));
			lastStatUpdateTravelDist = x;
		}
		return x;
	}
	return lastStatUpdateTravelDist;
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