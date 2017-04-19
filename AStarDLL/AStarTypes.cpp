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
			travelPathIndex = x->subnodes["travelPathIndex"]->value;
			break;
		case SDT_BIND_ON_SAVE:
			assertsubnode(x, "traveler")->value = traveler->holder;
			assertsubnode(x, "acquireTime")->value = acquireTime;
			assertsubnode(x, "releaseTime")->value = releaseTime;
			assertsubnode(x, "travelPathIndex")->value = travelPathIndex;
			break;
		case SDT_BIND_ON_DISPLAY: {
			char str[1024];
			sprintf(str, "traveler: %s, acquireTime: %lf, releaseTime: %lf, travelPathIndex: %d", 
				getname(traveler->holder).c_str(), acquireTime, releaseTime, (int)travelPathIndex);
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
	bindNumber(nrFromUp);
	bindNumber(nrFromDown);
	bindNumber(nrFromLeft);
	bindNumber(nrFromRight);

	// diagonals
	bindNumber(nrFromUpRight);
	bindNumber(nrFromDownRight);
	bindNumber(nrFromUpLeft);
	bindNumber(nrFromDownLeft);

	bindNumber(numCollisions);

	bindNumber(bonusRight);
	bindNumber(bonusLeft);
	bindNumber(bonusUp);
	bindNumber(bonusDown);

	// still need to bind bridges
	//std::vector<BridgeEntry> bridges;
	
	bindStlContainer(allocations);
	bindStlContainer(requests);
	bindObjRef(releaseEvent, false);
}

void AStarNodeExtraData::removeAllocation(NodeAllocationIterator allocIter)
{
	NodeAllocation alloc = *allocIter;
	allocations.erase(allocIter);
	double curTime = time();
	if (alloc.acquireTime <= curTime && alloc.releaseTime >= curTime && requests.size() > 0)
		onRelease();
}

void AStarNodeExtraData::onRelease()
{
	releaseEvent = nullptr;
	if (requests.size() == 0)
		return;
	double curTime = time();
	auto existingAllocation = std::find_if(allocations.begin(), allocations.end(),
		[&](NodeAllocation& alloc) {return alloc.acquireTime <= curTime && alloc.releaseTime > curTime; });
	if (existingAllocation == allocations.end()) {
		NodeAllocation topRequest = requests.front();
		requests.pop_front();
		topRequest.traveler->navigatePath(topRequest.travelPathIndex - 1, false);
	} else {
		checkCreateReleaseEvent();
	}
}

NodeAllocation* AStarNodeExtraData::addRequest(NodeAllocation& request, NodeAllocation& blockingAllocation, std::vector<Traveler*>* deadlockList)
{
	requests.push_back(request);
	std::vector<Traveler*> travelers;
	bool found = request.traveler->findDeadlockCycle(request.traveler, travelers);
	if (!found) {
		checkCreateReleaseEvent();
		return &requests.back();
	} else {
		requests.pop_back();
		if (deadlockList)
			*deadlockList = std::move(travelers);
		return nullptr;
	}
}

void AStarNodeExtraData::checkCreateReleaseEvent()
{
	if (releaseEvent)
		destroyevent(releaseEvent->holder);
	double releaseTime = 0;
	double curTime = time();
	for (NodeAllocation& alloc : allocations) {
		if (alloc.acquireTime <= curTime && alloc.releaseTime > curTime)
			if (alloc.releaseTime > releaseTime)
				releaseTime = alloc.releaseTime;
	}
	if (releaseTime < FLT_MAX)
		releaseEvent = createevent(new ReleaseEvent(releaseTime, requests.front().traveler, cell))->objectAs(ReleaseEvent);

}


bool AStarNodeExtraData::findDeadlockCycle(Traveler* start, std::vector<Traveler*>& travelers)
{
	for (NodeAllocation& request : requests) {
		if (request.traveler == start)
			return true;
		if (request.traveler->findDeadlockCycle(start, travelers))
			return true;
	}
	return false;
}


void AStarNodeExtraData::ReleaseEvent::bind()
{
	__super::bind();
	bindNumber(cell.col);
	bindNumber(cell.row);
}

AStarNodeExtraData::ReleaseEvent::ReleaseEvent(double time, Traveler* traveler, AStarCell& cell) : cell(cell), FlexSimEvent(traveler->holder, time, nullptr, cell.row * 100000 + cell.col) {}
void AStarNodeExtraData::ReleaseEvent::execute()
{
	partner()->objectAs(Traveler)->navigator->getExtraData(cell)->onRelease();
}


void NodeAllocation::extendReleaseTime(double toTime)
{
	double oldReleaseTime = releaseTime;
	releaseTime = toTime;
	if (toTime <= oldReleaseTime)
		return;
	AStarNodeExtraData* nodeData = traveler->navigator->getExtraData(cell);
	NodeAllocationIterator nextIter;
	for (auto iter = nodeData->allocations.begin(); iter != nodeData->allocations.end(); iter = nextIter) {
		nextIter = iter;
		nextIter++;
		NodeAllocation& alloc = *iter;
		if (&alloc == this)
			continue;
		if (alloc.acquireTime >= oldReleaseTime && alloc.acquireTime < releaseTime) {
			NodeAllocation copy = alloc;
			alloc.traveler->clearAllocations(std::find_if(alloc.traveler->allocations.begin(), alloc.traveler->allocations.end(), 
				[&](NodeAllocationIterator& other) { return other->cell == nodeData->cell && other == iter; }));
			if (alloc.traveler->arrivalEvent)
				destroyevent(alloc.traveler->arrivalEvent->holder);
			// this will cause him to create collision event
			NodeAllocation* nullAlloc = copy.traveler->addAllocation(copy);
			_ASSERTE(nullAlloc == nullptr);
		}

	}
}

}