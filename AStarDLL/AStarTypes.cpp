#pragma once
#include "AStarClasses.h"
#include "AStarTypes.h"
#include "FlexsimDefs.h"
#include "Traveler.h"
#include "AStarNavigator.h"
#include <algorithm>

namespace AStar {


void AStarCell::bind(TreeNode* x, const char* prefix)
{
	string rowName = string(prefix) + "row";
	string colName = string(prefix) + "col";
	switch (SimpleDataType::getBindMode()) {
		case SDT_BIND_ON_LOAD:
			col = x->subnodes[colName.c_str()]->value;
			row = x->subnodes[rowName.c_str()]->value;
			break;
		case SDT_BIND_ON_SAVE:
			assertsubnode(x, (char*)colName.c_str())->value = col;
			assertsubnode(x, (char*)rowName.c_str())->value = row;
			break;
		case SDT_BIND_ON_DISPLAY: {
			char str[256];
			sprintf(str, "%s: %d, %s: %d ", colName.c_str(), (int)col, rowName.c_str(), (int)row);
			SimpleDataType::appendToDisplayStr(str);
			break;
		}
		default: break;
	}
}


void AStarCell::bind(SimpleDataType* sdt, const char* prefix)
{
	sdt->bindNumberByName((string(prefix) + "col").c_str(), col);
	sdt->bindNumberByName((string(prefix) + "row").c_str(), row);
}

void NodeAllocation::bind(TreeNode* x)
{
	int bindMode = SimpleDataType::getBindMode();
	if (bindMode == SDT_BIND_ON_DISPLAY && SimpleDataType::isDisplayVerbose())
		SimpleDataType::appendToDisplayStr("\r\n");
	cell.bind(x, "");

	switch (SimpleDataType::getBindMode()) {
		case SDT_BIND_ON_LOAD:
			traveler = ((TreeNode*)(x->subnodes["traveler"]->value))->objectAs(Traveler);
			acquireTime = x->subnodes["acquireTime"]->value;
			releaseTime = x->subnodes["releaseTime"]->value;
			traversalWeight = x->subnodes["traversalWeight"]->value;
			travelPathIndex = x->subnodes["travelPathIndex"]->value;
			break;
		case SDT_BIND_ON_SAVE:
			assertsubnode(x, "traveler")->value = traveler->holder;
			assertsubnode(x, "acquireTime")->value = acquireTime;
			assertsubnode(x, "releaseTime")->value = releaseTime;
			assertsubnode(x, "traversalWeight")->value = traversalWeight;
			assertsubnode(x, "travelPathIndex")->value = travelPathIndex;
			break;
		case SDT_BIND_ON_DISPLAY: {
			char str[1024];
			sprintf(str, "traveler: %s, acquireTime: %lf, releaseTime: %lf, travelPathIndex: %d, traversalWeight: %lf", 
				getname(traveler->holder).c_str(), acquireTime, releaseTime, (int)travelPathIndex, traversalWeight);
			SimpleDataType::appendToDisplayStr(str);
			break;
		}
		default: break;
	}
}

void AStarPathEntry::bind(TreeNode* toNode)
{
	int bindMode = SimpleDataType::getBindMode();
	if (bindMode == SDT_BIND_ON_DISPLAY && SimpleDataType::isDisplayVerbose())
		SimpleDataType::appendToDisplayStr("\r\n");
	cell.bind(toNode, "");
	switch (bindMode) {
		case SDT_BIND_ON_LOAD:
			bridgeIndex = (int)toNode->subnodes["bridgeIndex"]->value;
			break;
		case SDT_BIND_ON_SAVE:
			assertsubnode(toNode, "bridgeIndex")->value = bridgeIndex;
			break;
		case SDT_BIND_ON_DISPLAY: {
			char str[100];
			sprintf(str, "bridgeIndex: %d", (int)bridgeIndex);
			SimpleDataType::appendToDisplayStr(str);
			break;
		}
		default: break;
	}
}

void AStarNodeExtraData::bind()
{
	cell.bind(this);


	// Traffic tracking stats:
	// straights
	bindNumber(totalTraversals);

	bindNumber(totalBlockedTime);

	bindNumber(bonusRight);
	bindNumber(bonusLeft);
	bindNumber(bonusUp);
	bindNumber(bonusDown);

	// still need to bind bridges
	//std::vector<BridgeEntry> bridges;
	
	bindStlContainer(allocations);
	bindStlContainer(requests);
	bindObjRef(continueEvent, false);
}

void AStarNodeExtraData::removeAllocation(NodeAllocationIterator allocIter)
{
	NodeAllocation alloc = *allocIter;
	allocations.erase(allocIter);
	double curTime = time();
	if (alloc.acquireTime <= curTime && alloc.releaseTime > curTime && requests.size() > 0) {
		if (continueEvent)
			destroyevent(continueEvent->holder);
		onContinue(nullptr);
	}
}

void AStarNodeExtraData::onContinue(Traveler* blocker)
{
	continueEvent = nullptr;
	if (requests.size() == 0)
		return;
	if (blocker && blocker->blockEvent && blocker->blockEvent->time <= time())
		return;
	double curTime = time();
	auto existingAllocation = std::find_if(allocations.begin(), allocations.end(),
		[&](NodeAllocation& alloc) {return alloc.acquireTime <= curTime && alloc.releaseTime > curTime; });
	if (existingAllocation == allocations.end()) {
		fulfillTopRequest();
	} else {
		checkCreateContinueEvent();
	}
}


void AStarNodeExtraData::fulfillTopRequest()
{
	NodeAllocation topRequest = requests.front();
	Traveler* traveler = topRequest.traveler;
	traveler->request = nullptr;
	requests.pop_front();
	double blockedTime = time() - traveler->lastBlockTime;
	if (traveler->isBlocked && blockedTime > traveler->tinyTime) {
		AStarCell cell;
		if (traveler->allocations.size() > 0)
			cell = traveler->allocations.back()->cell;
		else cell = traveler->travelPath[topRequest.travelPathIndex - 1].cell;
		AStarNodeExtraData* blockedCell = traveler->navigator->getExtraData(cell);
		if (blockedCell != nullptr) {
			blockedTime = min(blockedTime, statisticaltime());
			blockedCell->totalBlockedTime += blockedTime;
			blockedCell->totalBlocks++;
		}
	}
	traveler->navigatePath(topRequest.travelPathIndex - 1, false);
	if (requests.size() > 0)
		checkCreateContinueEvent();
}


void AStarNodeExtraData::onReleaseTimeExtended(NodeAllocation& changedAlloc, double oldReleaseTime)
{
	NodeAllocationIterator nextIter;
	for (auto iter = allocations.begin(); iter != allocations.end(); iter = nextIter) {
		nextIter = iter;
		nextIter++;
		NodeAllocation& alloc = *iter;
		if (&alloc == &changedAlloc)
			continue;
		if (alloc.acquireTime >= oldReleaseTime && alloc.acquireTime < changedAlloc.releaseTime) {
			NodeAllocation copy = alloc;
			auto found = std::find_if(alloc.traveler->allocations.begin(), alloc.traveler->allocations.end(),
				[&](NodeAllocationIterator& other) { return other->cell == cell && other == iter; });
			while (found - alloc.traveler->allocations.begin() > 1 && (*(found - 1))->acquireTime == alloc.acquireTime)
				found--;
			alloc.traveler->clearAllocations(found, true);
			if (copy.traveler->arrivalEvent)
				destroyevent(copy.traveler->arrivalEvent->holder);
			// this will cause him to create collision event
			NodeAllocation* nullAlloc = copy.traveler->addAllocation(copy, false, true);
			_ASSERTE(nullAlloc == nullptr);
		}
	}

	if (requests.size() > 0 && continueEvent && continueEvent->time == std::nextafter(oldReleaseTime, FLT_MAX)) {
		destroyevent(continueEvent->holder);
		if (changedAlloc.releaseTime < FLT_MAX)
			continueEvent = createevent(new ContinueEvent(std::nextafter(changedAlloc.releaseTime, FLT_MAX), requests.front().traveler, changedAlloc.traveler, cell))->objectAs(ContinueEvent);
	}
}



void AStarNodeExtraData::onReleaseTimeTruncated(NodeAllocation& changedAlloc, double oldReleaseTime)
{
	NodeAllocationIterator nextIter;

	if (changedAlloc.acquireTime <= time() && requests.size() > 0) {
		if (continueEvent)
			destroyevent(continueEvent->holder);
		if (changedAlloc.releaseTime < FLT_MAX)
			continueEvent = createevent(new ContinueEvent(std::nextafter(changedAlloc.releaseTime, FLT_MAX), requests.front().traveler, changedAlloc.traveler, cell))->objectAs(ContinueEvent);
	}
}

NodeAllocation* AStarNodeExtraData::addRequest(NodeAllocation& request, NodeAllocation& blockingAllocation, std::vector<Traveler*>* deadlockList)
{
	requests.push_back(request);
	std::vector<Traveler*> travelers;
	bool found = request.traveler->findDeadlockCycle(request.traveler, travelers);
	if (!found) {
		checkCreateContinueEvent();
	} else {
		if (deadlockList)
			*deadlockList = std::move(travelers);
	}
	return &requests.back();
}

void AStarNodeExtraData::checkCreateContinueEvent()
{
	if (continueEvent)
		destroyevent(continueEvent->holder);
	double releaseTime = 0;
	double curTime = time();
	Traveler* blocker = nullptr;
	for (NodeAllocation& alloc : allocations) {
		if (alloc.acquireTime <= curTime && alloc.releaseTime > curTime) {
			if (alloc.releaseTime > releaseTime) {
				blocker = alloc.traveler;
				releaseTime = alloc.releaseTime;
			}
		}
	}
	if (releaseTime < FLT_MAX)
		continueEvent = createevent(new ContinueEvent(std::nextafter(max(releaseTime, time()), FLT_MAX), requests.front().traveler, blocker, cell))->objectAs(ContinueEvent);

}


bool AStarNodeExtraData::findDeadlockCycle(Traveler* start, std::vector<Traveler*>& travelers)
{
	for (NodeAllocation& request : requests) {
		if (request.traveler == start)
			return true;
		if (std::find(travelers.begin(), travelers.end(), request.traveler) != travelers.end())
			continue;
		if (request.traveler->findDeadlockCycle(start, travelers))
			return true;
	}
	return false;
}


void AStarNodeExtraData::ContinueEvent::bind()
{
	__super::bind();
	bindNumber(cell.col);
	bindNumber(cell.row);
}

AStarNodeExtraData::ContinueEvent::ContinueEvent(double time, Traveler* traveler, Traveler* blocker, AStarCell& cell) : cell(cell), FlexSimEvent(traveler->holder, time, blocker ? blocker->holder : nullptr, cell.row * 100000 + cell.col) {}
void AStarNodeExtraData::ContinueEvent::execute()
{
	partner()->objectAs(Traveler)->navigator->getExtraData(cell)->onContinue(involved ? involved->objectAs(Traveler) : nullptr);
}


void NodeAllocation::extendReleaseTime(double toTime)
{
	double oldReleaseTime = releaseTime;
	releaseTime = toTime;
	if (toTime <= oldReleaseTime)
		return;
	AStarNodeExtraData* nodeData = traveler->navigator->getExtraData(cell);
	nodeData->onReleaseTimeExtended(*this, oldReleaseTime);
}

void NodeAllocation::truncateReleaseTime(double toTime)
{
	double oldReleaseTime = releaseTime;
	releaseTime = toTime;
	if (toTime >= oldReleaseTime)
		return;
	AStarNodeExtraData* nodeData = traveler->navigator->getExtraData(cell);
	nodeData->onReleaseTimeTruncated(*this, oldReleaseTime);
}



bool AllocationStep::isImmediatelyBlocked(Traveler* traveler)
{
	NodeAllocation allocation(traveler, toCell, 1, 0, time(), std::nextafter(time(), FLT_MAX), 1.0);
	NodeAllocation* collision;
	if (isDiagonal) {
		allocation.cell = intermediateCell1;
		if (Traveler::findCollision(traveler->navigator->assertExtraData(intermediateCell1), allocation, true))
			return true;
		allocation.cell = intermediateCell2;
		if (Traveler::findCollision(traveler->navigator->assertExtraData(intermediateCell2), allocation, true))
			return true;
	}
	allocation.cell = toCell;
	if (Traveler::findCollision(traveler->navigator->assertExtraData(toCell), allocation, true))
		return true;
	return false;

}

DestinationThreshold::DestinationThreshold(treenode dest, double fudgeFactor)
{
	Vec3 size = dest->objectAs(ObjectDataType)->size;
	xAxisThreshold = 0.5 * size.x + fudgeFactor;
	yAxisThreshold = 0.5 * size.y + fudgeFactor;
	rotation = dest->objectAs(ObjectDataType)->rotation.z;
	while (dest->findOwnerObject() != model()) {
		dest = dest->findOwnerObject();
		rotation += dest->objectAs(ObjectDataType)->rotation.z;
	}
	anyThresholdRadius = 0.0;
}

bool DestinationThreshold::isWithinThreshold(const AStarCell & cell, const Vec2& gridOrigin, const Vec2& destLoc, double nodeWidth)
{
	if (anyThresholdRadius <= 0 && xAxisThreshold <= 0 && yAxisThreshold <= 0)
		return false;

	Vec2 cellLoc(gridOrigin.x + cell.col *nodeWidth, gridOrigin.y + cell.row * nodeWidth);
	Vec2 diff(destLoc - cellLoc);
	if (anyThresholdRadius > 0 && anyThresholdRadius >= diff.getLength())
		return true;

	if (rotation != 0)
		diff.rotate(-rotation);
	if (xAxisThreshold >= fabs(diff.x) && yAxisThreshold >= fabs(diff.y))
		return true;

	return false;
}

void DestinationThreshold::bind(SimpleDataType * sdt, const char* prefix)
{
	sdt->bindNumberByName(string(prefix).append("xAxisThreshold").c_str(), xAxisThreshold);
	sdt->bindNumberByName(string(prefix).append("yAxisThreshold").c_str(), yAxisThreshold);
	sdt->bindNumberByName(string(prefix).append("rotation").c_str(), rotation);
	sdt->bindNumberByName(string(prefix).append("anyThresholdRadius").c_str(), anyThresholdRadius);
}

}