#pragma once
#include "AStarClasses.h"
#include "AStarTypes.h"
#include "FlexsimDefs.h"
#include "Traveler.h"
#include "AStarNavigator.h"
#include <algorithm>

namespace AStar {


int AStarNode::rowInc[] =
{
	0, // none
	0, // right
	0, // left
	1, // up
	-1 // down
};
int AStarNode::colInc[]
{
	0,
	1, // right
	-1, // left
	0, // up
	0 // down
};

void Cell::bind(TreeNode* x, const char* prefix)
{
	string gridName = string(prefix) + "grid";
	string rowName = string(prefix) + "row";
	string colName = string(prefix) + "col";
	SimpleDataType::bindNumberByName(gridName.c_str(), grid, x);
	SimpleDataType::bindNumberByName(rowName.c_str(), row, x);
	SimpleDataType::bindNumberByName(colName.c_str(), col, x);
}


void Cell::bind(SimpleDataType* sdt, const char* prefix)
{
	sdt->bindNumberByName((string(prefix) + "Grid").c_str(), grid);
	sdt->bindNumberByName((string(prefix) + "Col").c_str(), col);
	sdt->bindNumberByName((string(prefix) + "Row").c_str(), row);
}

void Cell::bind(TreeNode * x)
{
	SimpleDataType::bindNumber(grid, x);
	SimpleDataType::bindNumber(row, x);
	SimpleDataType::bindNumber(col, x);
}


void ExtendedCell::bindInterface()
{
	SimpleDataType::bindDocumentationXMLPath("manual\\Reference\\CodingInFlexSim\\FlexScriptAPIReference\\AStar\\AStar.Cell.xml");
	SimpleDataType::bindConstructor(force_cast<void*>(&ExtendedCell::construct), "void Cell(int grid, int row, int col)");
	SimpleDataType::bindCopyConstructor(&ExtendedCell::copyConstruct);
	SimpleDataType::bindCopyAssigner(&ExtendedCell::operator =);
	bindTypedProperty(row, int, &ExtendedCell::__getRow, &ExtendedCell::__setRow);
	bindTypedProperty(col, int, &ExtendedCell::__getCol, &ExtendedCell::__setCol);
	SimpleDataType::bindOperator(bool, ExtendedCell, "int bool()");
	SimpleDataType::bindOperator(!, ExtendedCell, "int not()");
	SimpleDataType::bindOperator(== , Cell, "int equal(AStar.Cell& other)");
	SimpleDataType::bindOperator(!= , Cell, "int notEqual(AStar.Cell& other)");
	bindMethod(getAllocation, ExtendedCell, "AStar.Allocation getAllocation(double time = -1)");
	bindMethod(adjacentCell, ExtendedCell, "AStar.Cell adjacentCell(int direction)");
	bindMethod(canGo, ExtendedCell, "int canGo(int direction)");

}

void ExtendedCell::__assertCachedPointers()
{
	if (!AStarNavigator::instance)
		return;

	if (grid == 0 || grid > AStarNavigator::instance->grids.size())
		return;
	Grid* grid = AStarNavigator::instance->getGrid(*this);
	if (col >= grid->numCols || row >= grid->numRows)
		return;

	node = &(grid->nodes[row][col]);

	auto found = AStarNavigator::instance->edgeTableExtraData.find(value);
	if (found != AStarNavigator::instance->edgeTableExtraData.end())
		extra = found->second;
}

NodeAllocation ExtendedCell::getAllocation(double atTime)
{
	if (atTime < 0)
		atTime = time();

	assertCachedPointers();
	if (!extra)
		return NodeAllocation(nullptr, *this, 0, 0, -1.0, -1.0, 1.0);

	auto found = std::find_if(extra->allocations.begin(), extra->allocations.end(), [atTime](NodeAllocation& alloc) {return alloc.acquireTime <= atTime && alloc.releaseTime > atTime; });
	if (found != extra->allocations.end())
		return *found;
	else return NodeAllocation(nullptr, *this, 0, 0, -1.0, -1.0, 1.0);
}

ExtendedCell ExtendedCell::adjacentCell(int direction)
{
	ExtendedCell cell(*this);
	cell.row += AStarNode::rowInc[direction];
	cell.col += AStarNode::colInc[direction];
	cell.node = nullptr;
	cell.extra = nullptr;
	return cell;
}

int ExtendedCell::canGo(int direction)
{
	assertCachedPointers();
	if (!node)
		return 0;
	return node->canGo((Direction)direction);
}

Vec3 ExtendedCell::getLocation(AStarNavigator* nav)
{
	return nav->getGrid(*this)->getLocation(*this);
}

double ExtendedCell::getNodeWidth(AStarNavigator* nav)
{
	return nav->getGrid(*this)->nodeWidth;
}

ExtendedCell::operator bool()
{
	assertCachedPointers();

	return node != nullptr;
}



void NodeAllocation::bind(TreeNode* x)
{
	int bindMode = SimpleDataType::getBindMode();
	if (bindMode == SDT_BIND_ON_DISPLAY && SimpleDataType::isDisplayVerbose())
		SimpleDataType::appendToDisplayStr("\r\n");
	cell.bind(x);
	SimpleDataType::bindObjPtr(traveler, x);
	SimpleDataType::bindNumber(acquireTime, x);
	SimpleDataType::bindNumber(releaseTime, x);
	SimpleDataType::bindNumber(traversalWeight, x);
	SimpleDataType::bindNumber(travelPathIndex, x);
}

struct ExtendedNodeAllocation : public NodeAllocation
{
	ExtendedCell __getCell() { return ExtendedCell(cell.grid, cell.row, cell.col); }
};

void NodeAllocation::bindInterface()
{
	SimpleDataType::bindDocumentationXMLPath("manual\\Reference\\CodingInFlexSim\\FlexScriptAPIReference\\AStar\\AStar.Allocation.xml");
	SimpleDataType::bindConstructor(force_cast<void*>(&NodeAllocation::construct), "void Cell(int grid, int row, int col)");
	SimpleDataType::bindCopyConstructor(&NodeAllocation::copyConstruct);
	SimpleDataType::bindCopyAssigner(&NodeAllocation::operator =);
	SimpleDataType::bindOperator(bool, NodeAllocation, "int bool()");
	SimpleDataType::bindOperator(!, NodeAllocation, "int not()");
	bindTypedProperty(acquireTime, double, &NodeAllocation::__getAcquireTime, nullptr);
	bindTypedProperty(releaseTime, double, &NodeAllocation::__getReleaseTime, nullptr);
	SimpleDataType::bindTypedPropertyByName<ExtendedCell>("cell", "AStar.Cell", force_cast<void*>(&ExtendedNodeAllocation::__getCell), nullptr);
	SimpleDataType::bindTypedPropertyByName<Traveler>("traveler", "AStar.Traveler", force_cast<void*>(&NodeAllocation::__getTraveler), nullptr);
}

void AStarPathEntry::bind(TreeNode* toNode)
{
	int bindMode = SimpleDataType::getBindMode();
	if (bindMode == SDT_BIND_ON_DISPLAY && SimpleDataType::isDisplayVerbose())
		SimpleDataType::appendToDisplayStr("\r\n");
	cell.bind(toNode);
	SimpleDataType::bindNumber(bridgeIndex, toNode);
}

void AStarPathEntry::bindInterface()
{
	SimpleDataType::bindTypedPropertyByName<ExtendedCell>("cell", "AStar.Cell", force_cast<void*>(&AStarPathEntry::__getCell), nullptr);
}

ExtendedCell AStarPathEntry::__getCell()
{
	return ExtendedCell(cell.grid, cell.row, cell.col);
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

	bindStlContainer(conditionalBarriers);
}

void AStarNodeExtraData::addConditionalBarrier(Barrier * barrier)
{
	auto found = std::find(conditionalBarriers.begin(), conditionalBarriers.end(), barrier);
	if (found == conditionalBarriers.end())
		conditionalBarriers.push_back(barrier);
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
		Cell cell;
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
	traveler->navigatePath(topRequest.travelPathIndex - 1);
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

NodeAllocation* AStarNodeExtraData::addRequest(NodeAllocation& request, std::vector<Traveler*>* deadlockList)
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

AStarNodeExtraData::ContinueEvent::ContinueEvent(double time, Traveler* traveler, Traveler* blocker, Cell& cell) : cell(cell), FlexSimEvent(traveler->holder, time, blocker ? blocker->holder : nullptr, cell.row * 100000 + cell.col) {}
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
		if (Traveler::findCollision(traveler->navigator->assertExtraData(intermediateCell1, AllocationData), allocation, true))
			return true;
		allocation.cell = intermediateCell2;
		if (Traveler::findCollision(traveler->navigator->assertExtraData(intermediateCell2, AllocationData), allocation, true))
			return true;
	}
	allocation.cell = toCell;
	if (Traveler::findCollision(traveler->navigator->assertExtraData(toCell, AllocationData), allocation, true))
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

bool DestinationThreshold::isWithinThreshold(const Cell & cell, Grid* grid, const Vec3& destLoc)
{
	if (anyThresholdRadius <= 0 && xAxisThreshold <= 0 && yAxisThreshold <= 0)
		return false;

	Vec3 cellLoc(grid->gridOrigin.x + cell.col * grid->nodeWidth, 
		grid->gridOrigin.y + cell.row * grid->nodeWidth,
		grid->gridOrigin.z);
	Vec3 diff(destLoc - cellLoc);
	if (anyThresholdRadius > 0 && anyThresholdRadius >= diff.getLength())
		return true;

	if (rotation != 0)
		diff.rotateXY(-rotation);
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

double TravelPath::calculateTotalDistance(AStarNavigator * nav)
{
	double dist = 0.0;
	for (size_t i = 1; i < size(); i++) {
		AStarPathEntry& from = operator [](i - 1);
		AStarPathEntry& to = operator [](i);
		Grid* grid = nav->getGrid(from.cell);
		if (from.bridgeIndex >= 0) {
			AStarNodeExtraData* nodeData = nav->getExtraData(from.cell);
			BridgeRoutingData* routingData = nodeData->bridges[from.bridgeIndex];
			dist += routingData->getTravelDistance(this, i, grid);
		} else {
			bool isDeepDiagonal = (abs(from.cell.row - to.cell.row) >= 2 || abs(from.cell.col - to.cell.col) >= 2);
			if (isDeepDiagonal)
				dist += grid->nodeWidth * 2.236067977499789696409;
			else {
				bool isDiagonal = from.cell.row != to.cell.row && from.cell.col != to.cell.col;
				if (isDiagonal)
					dist += grid->nodeWidth * 1.4142135623730950488;
				else dist += grid->nodeWidth;
			}
		}
	}
	return dist;
}

int TravelPath::__getLength()
{
	return (int)size();
}

int TravelPath::indexOf(Cell & cell)
{
	for (int i = 0; i < size(); i++) {
		if (operator [](i).cell == cell)
			return i + 1;
	}
	return -1;
}


AStarPathEntry& TravelPath::at(int index)
{
	return operator[](index);
}

void TravelPath::bindInterface()
{
	bindTypedProperty(length, int, &TravelPath::__getLength, nullptr);
	auto funcPtr = &TravelPath::__oneBasedIndex;
	SimpleDataType::bindOperatorByName<decltype(funcPtr)>("[]", funcPtr, "AStar.TravelPathEntry arrayDeref(int index)");
	bindMethod(indexOf, TravelPath, "int indexOf(AStar.Cell& cell)");
}

void AStarNamespace::bindInterface()
{
	SimpleDataType::bindDocumentationXMLPath("manual\\Reference\\CodingInFlexSim\\FlexScriptAPIReference\\AStar\\AStar.xml");
	SimpleDataType::bindStaticTypedPropertyByName<AStarNavigator*>("navigator", "AStar.Navigator", force_cast<void*>(&AStarNamespace::__getNavigator), nullptr);
}

AStarNavigator * AStarNamespace::__getNavigator()
{
	return AStarNavigator::instance;
}

NodeAllocation AllocationRange::operator[](int oneBasedIndex)
{
	if (!traveler || oneBasedIndex > size || startIndex + oneBasedIndex >= traveler->allocations.size())
		return NodeAllocation();

	return *(traveler->allocations[startIndex + oneBasedIndex - 1]);
}

void AllocationRange::bindInterface()
{
	SimpleDataType::bindConstructor(force_cast<void*>(&AllocationRange::construct), "void AllocationRange()");
	SimpleDataType::bindCopyConstructor(&AllocationRange::copyConstruct);
	SimpleDataType::bindCopyAssigner(&AllocationRange::operator =);
	bindTypedProperty(length, int, &AllocationRange::__getLength, nullptr);
	SimpleDataType::bindOperator([], AllocationRange, "AStar.Allocation arrayDeref(int index)");
}

void AStarDirection::bindInterface()
{
	SimpleDataType::bindDocumentationXMLPath("manual\\Reference\\CodingInFlexSim\\FlexScriptAPIReference\\AStar\\AStar.Direction.xml");
	SimpleDataType::bindStaticConstIntProperty(Left, (int)Direction::Left);
	SimpleDataType::bindStaticConstIntProperty(Right, (int)Direction::Right);
	SimpleDataType::bindStaticConstIntProperty(Up, (int)Direction::Up);
	SimpleDataType::bindStaticConstIntProperty(Down, (int)Direction::Down);
}

}