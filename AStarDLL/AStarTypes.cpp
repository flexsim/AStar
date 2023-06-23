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

Cell Cell::adjacentCell(int direction)
{
	Cell cell(*this);
	cell.row += AStarNode::rowInc[direction];
	cell.col += AStarNode::colInc[direction];
	return cell;
}


void ExtendedCell::bindInterface()
{
	SimpleDataType::bindDocumentationXMLPath("help\\FlexScriptAPIReference\\AStar\\AStar.Cell.xml");
	SimpleDataType::bindConstructor(force_cast<void*>(&ExtendedCell::construct), "void Cell(int grid, int row, int col)");
	SimpleDataType::bindCopyConstructor(&ExtendedCell::copyConstruct);
	SimpleDataType::bindCopyAssigner(&ExtendedCell::operator =);
	bindTypedProperty(row, int, &ExtendedCell::__getRow, &ExtendedCell::__setRow);
	bindTypedProperty(col, int, &ExtendedCell::__getCol, &ExtendedCell::__setCol);
	SimpleDataType::bindOperator(bool, ExtendedCell, "int bool()");
	SimpleDataType::bindOperator(!, ExtendedCell, "int not()");
	SimpleDataType::bindOperator(== , Cell, "int equal(AStar.Cell& other)");
	SimpleDataType::bindOperator(!= , Cell, "int notEqual(AStar.Cell& other)");
	auto ga1 = (NodeAllocation(ExtendedCell::*)(double)) & ExtendedCell::getAllocation;
	SimpleDataType::bindMethodByName<decltype(ga1)>("getAllocation", ga1, "AStar.Allocation getAllocation(double time = -1)");
	auto ga2 = (NodeAllocation(ExtendedCell::*)(double, double)) & ExtendedCell::getAllocation;
	SimpleDataType::bindMethodByName<decltype(ga2)>("getAllocation", ga2, "AStar.Allocation getAllocation(double fromTime, double toTime)");
	auto ga3 = (NodeAllocation(ExtendedCell::*)(Traveler*)) & ExtendedCell::getAllocation;
	SimpleDataType::bindMethodByName<decltype(ga3)>("getAllocation", ga3, "AStar.Allocation getAllocation(AStar.Traveler traveler)");
	bindMethod(adjacentCell, ExtendedCell, "AStar.Cell adjacentCell(int direction)");
	bindMethod(canGo, ExtendedCell, "int canGo(int direction)");

	bindTypedProperty(totalTraversals, double, &ExtendedCell::__getTotalTraversals, &ExtendedCell::__setTotalTraversals);
	SimpleDataType::bindToVariantFunc(&ExtendedCell::s_toVariant);
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

NodeAllocation ExtendedCell::getAllocation(double fromTime, double toTime)
{
	assertCachedPointers();
	if (!extra)
		return NodeAllocation(nullptr, *this, 0, 0, -1.0, -1.0, 1.0);

	auto found = std::min_element(extra->allocations.begin(), extra->allocations.end(), 
		[fromTime, toTime](NodeAllocation& left, NodeAllocation& right) {
			bool leftIsValid = left.acquireTime <= toTime && left.releaseTime > fromTime;
			bool rightIsValid = left.acquireTime <= toTime && left.releaseTime > fromTime;
			if (!leftIsValid && !rightIsValid)
				return false;
			if (leftIsValid && rightIsValid)
				return left.acquireTime < right.acquireTime;
			return leftIsValid;
		});
	if (found != extra->allocations.end() && found->acquireTime <= toTime && found->releaseTime > fromTime)
		return *found;
	else return NodeAllocation(nullptr, *this, 0, 0, -1.0, -1.0, 1.0);
}

NodeAllocation ExtendedCell::getAllocation(Traveler* t)
{
	assertCachedPointers();
	if (!extra)
		return NodeAllocation(nullptr, *this, 0, 0, -1.0, -1.0, 1.0);

	auto found = std::find_if(extra->allocations.begin(), extra->allocations.end(),[t](NodeAllocation& alloc) { return alloc.traveler == t; });
	if (found != extra->allocations.end() && found->traveler == t)
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

Vec2 ExtendedCell::getNodeSize(AStarNavigator* nav)
{
	return nav->getGrid(*this)->nodeSize;
}

ExtendedCell::operator bool()
{
	assertCachedPointers();

	return node != nullptr;
}


double ExtendedCell::__getTotalTraversals()
{
	assertCachedPointers();
	if (!extra)
		return 0.0;
	return extra->totalTraversals;
}

void ExtendedCell::__setTotalTraversals(double toVal)
{
	assertCachedPointers();
	if (!node)
		return;
	if (!extra)
		extra = AStarNavigator::instance->assertExtraData(*this, TraversalData);
	extra->totalTraversals = toVal;
}

ExtendedCell::operator Variant()
{
	Map map;
	map["grid"] = grid;
	map["row"] = row;
	map["col"] = col;
	return map;
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
	SimpleDataType::bindNumber(atTravelDist, x);
}

struct ExtendedNodeAllocation : public NodeAllocation
{
	ExtendedCell __getCell() { return ExtendedCell(cell.grid, cell.row, cell.col); }
};

void NodeAllocation::bindInterface()
{
	SimpleDataType::bindDocumentationXMLPath("help\\FlexScriptAPIReference\\AStar\\AStar.Allocation.xml");
	auto construct1 = (void (NodeAllocation::*)()) & NodeAllocation::construct;
	SimpleDataType::bindConstructor(construct1, "void Allocation()");
	auto construct2 = (void (NodeAllocation::*)(Traveler * traveler, const Cell & cell, int travelPathIndexOneBased, double acquireTime, double releaseTime)) & NodeAllocation::construct;
	SimpleDataType::bindConstructor(construct2, "void Allocation(AStar.Traveler traveler, AStar.Cell cell, int travelPathIndex, double acquireTime, double releaseTime)");
	SimpleDataType::bindCopyConstructor(&NodeAllocation::copyConstruct);
	SimpleDataType::bindCopyAssigner(&NodeAllocation::operator =);
	bindCastOperator(bool, &NodeAllocation::operator bool);
	SimpleDataType::bindOperator(!, NodeAllocation, "int not()");
	bindTypedProperty(acquireTime, double, &NodeAllocation::__getAcquireTime, nullptr);
	bindTypedProperty(releaseTime, double, &NodeAllocation::__getReleaseTime, nullptr);
	SimpleDataType::bindTypedPropertyByName<ExtendedCell>("cell", "AStar.Cell", force_cast<void*>(&ExtendedNodeAllocation::__getCell), nullptr);
	SimpleDataType::bindTypedPropertyByName<Traveler>("traveler", "AStar.Traveler", force_cast<void*>(&NodeAllocation::__getTraveler), nullptr);
	auto ert = &NodeAllocation::extendReleaseTime_flexScript;
	SimpleDataType::bindMethodByName<decltype(ert)>("extendReleaseTime", ert, "void extendReleaseTime(double toTime)");
	auto trt = &NodeAllocation::truncateReleaseTime_flexScript;
	SimpleDataType::bindMethodByName<decltype(trt)>("truncateReleaseTime", trt, "void truncateReleaseTime(double toTime)");
	bindTypedProperty("travelPathIndex", int, &NodeAllocation::__getTravelPathIndex, nullptr);
	SimpleDataType::bindToVariantFunc(&NodeAllocation::s_toVariant);
}

int NodeAllocation::getTravelPathIndex()
{
	if (!traveler)
		return 0;
	return traveler->travelPath.getIndex(atTravelDist, true);
}

NodeAllocation::operator Variant()
{
	Map map;
	map["traveler"] = traveler->holder;
	map["cell.grid"] = cell.grid;
	map["cell.row"] = cell.row;
	map["cell.col"] = cell.col;
	map["travelPathIndex"] = getTravelPathIndex() + 1;
	map["acquireTime"] = acquireTime;
	map["releaseTime"] = releaseTime;
	return map;
}

void AStarPathEntry::bind(TreeNode* toNode)
{
	int bindMode = SimpleDataType::getBindMode();
	if (bindMode == SDT_BIND_ON_DISPLAY && SimpleDataType::isDisplayVerbose())
		SimpleDataType::appendToDisplayStr("\r\n");
	cell.bind(toNode);
	SimpleDataType::bindNumber(bridgeIndex, toNode);
	SimpleDataType::bindNumber(arrivalTime, toNode);
	SimpleDataType::bindNumber(atTravelDist, toNode);
	SimpleDataType::bindNumber(distToNextStop, toNode);
	SimpleDataType::bindNumber(maxArrivalSpeed, toNode);
	SimpleDataType::bindNumber(distFromPrev, toNode);
	SimpleDataType::bindNumber(turnEndTime, toNode);
	SimpleDataType::bindNumber(modelLoc.x, toNode);
	SimpleDataType::bindNumber(modelLoc.y, toNode);
	SimpleDataType::bindNumber(modelLoc.z, toNode);
}

void AStarPathEntry::bindInterface()
{
	SimpleDataType::bindTypedPropertyByName<ExtendedCell>("cell", "AStar.Cell", force_cast<void*>(&AStarPathEntry::__getCell), nullptr);
	bindTypedProperty(isBridgePoint, int, &AStarPathEntry::__getIsBridgePoint, nullptr);
	bindTypedProperty(arrivalTime, double, &AStarPathEntry::__getArrivalTime, &AStarPathEntry::__setArrivalTime);
	SimpleDataType::bindToVariantFunc(&AStarPathEntry::s_toVariant);
}

ExtendedCell AStarPathEntry::__getCell()
{
	return ExtendedCell(cell.grid, cell.row, cell.col);
}

AStarPathEntry::operator Variant()
{
	Map map;
	map["cell.grid"] = cell.grid;
	map["cell.row"] = cell.row;
	map["cell.col"] = cell.col;
	map["arrivalTime"] = arrivalTime;
	map["isBridgePoint"] = isBridgePoint;
	return map;
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
	auto atIndex = traveler->travelPath.getIndex(topRequest.atTravelDist, false);
	if (traveler->isBlocked && blockedTime > traveler->tinyTime) {
		Cell cell;
		if (traveler->allocations.size() > 0)
			cell = traveler->allocations.back()->cell;
		else cell = traveler->travelPath[atIndex].cell;
		AStarNodeExtraData* blockedCell = traveler->navigator->getExtraData(cell);
		if (blockedCell != nullptr) {
			blockedTime = std::min(blockedTime, statisticaltime());
			blockedCell->totalBlockedTime += blockedTime;
			blockedCell->totalBlocks++;
		}
	}
	traveler->navigatePath(atIndex - 1);
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
			while (found - alloc.traveler->allocations.begin() > 1 && (*(found - 1))->atTravelDist >= alloc.atTravelDist)
				found--;
			alloc.traveler->clearAllocations(found);
			if (copy.traveler->nextEvent)
				destroyevent(copy.traveler->nextEvent);
			// this will cause him to create collision event
			NodeAllocation* nullAlloc = copy.traveler->addAllocation(copy, false, true);
#ifdef _WINDOWS
			_ASSERTE(nullAlloc == nullptr);
#endif
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
		continueEvent = createevent(new ContinueEvent(std::nextafter(std::max(releaseTime, time()), FLT_MAX), requests.front().traveler, blocker, cell))->objectAs(ContinueEvent);

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

NodeAllocation::NodeAllocation(Traveler* traveler, const Cell& cell, int travelPathIndex, int intermediateAllocationIndex, double acquireTime, double releaseTime, double traversalWeight) :
	traveler(traveler), cell(cell), intermediateAllocationIndex(intermediateAllocationIndex), acquireTime(acquireTime), releaseTime(releaseTime), traversalWeight(traversalWeight)
{
	atTravelDist = traveler ? traveler->travelPath[travelPathIndex].atTravelDist : 0.0;
}

void NodeAllocation::extendReleaseTime(double toTime)
{
	double oldReleaseTime = releaseTime;
	if (toTime <= oldReleaseTime)
		return;
	releaseTime = toTime;
	AStarNodeExtraData* nodeData = traveler->navigator->getExtraData(cell);
	nodeData->onReleaseTimeExtended(*this, oldReleaseTime);
}

void NodeAllocation::extendReleaseTime_flexScript(double toTime)
{
	if (toTime <= releaseTime)
		return;
	releaseTime = toTime;
	AStarNodeExtraData* nodeData = AStarNavigator::instance->getExtraData(cell);
	if (!nodeData)
		throw "AStar.Allocation.extendReleaseTime(): invalid allocation cannot extend release time";
	auto found = std::find_if(nodeData->allocations.begin(), nodeData->allocations.end(), 
		[this](NodeAllocation& alloc) { return alloc.traveler == traveler && alloc.acquireTime == acquireTime; });
	if (found != nodeData->allocations.end())
		found->extendReleaseTime(toTime);
}

void NodeAllocation::truncateReleaseTime(double toTime)
{
	double oldReleaseTime = releaseTime;
	if (toTime >= oldReleaseTime)
		return;
	releaseTime = toTime;
	AStarNodeExtraData* nodeData = traveler->navigator->getExtraData(cell);
	nodeData->onReleaseTimeTruncated(*this, oldReleaseTime);
}


void NodeAllocation::truncateReleaseTime_flexScript(double toTime)
{
	if (toTime >= releaseTime)
		return;
	releaseTime = toTime;
	AStarNodeExtraData* nodeData = AStarNavigator::instance->getExtraData(cell);
	if (!nodeData)
		throw "AStar.Allocation.extendReleaseTime(): invalid allocation cannot truncate release time";
	auto found = std::find_if(nodeData->allocations.begin(), nodeData->allocations.end(),
		[this](NodeAllocation& alloc) { return alloc.traveler == traveler && alloc.acquireTime == acquireTime; });
	if (found != nodeData->allocations.end())
		found->truncateReleaseTime(toTime);
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

DestinationThreshold::DestinationThreshold(treenode dest, const Vec2& fudgeFactor)
{
	Vec3 size = dest->objectAs(ObjectDataType)->size;
	xAxisThreshold = 0.5 * size.x + fudgeFactor.x;
	yAxisThreshold = 0.5 * size.y + fudgeFactor.y;
	rotation = dest->objectAs(ObjectDataType)->rotation.z;
	while (dest->findOwnerObject() != model()) {
		dest = dest->findOwnerObject();
		rotation += dest->objectAs(ObjectDataType)->rotation.z;
	}
	anyThresholdRadius = 0.0;
}

bool DestinationThreshold::isWithinThreshold(const Cell & cell, Grid* grid, const Vec3& destLoc) const
{
	if (anyThresholdRadius <= 0 && xAxisThreshold <= 0 && yAxisThreshold <= 0)
		return false;

	Vec3 cellLoc(grid->gridOrigin.x + cell.col * grid->nodeSize.x, 
		grid->gridOrigin.y + cell.row * grid->nodeSize.y,
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
	for (int i = 1; i < size(); i++) {
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
				dist += grid->deepDiagDist;
			else {
				if (from.cell.row != to.cell.row) {
					if (from.cell.col != to.cell.col)
						dist += grid->diagDist;
					else dist += grid->nodeSize.y;
				}
				else dist += grid->nodeSize.x;
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
	SimpleDataType::bindOperatorByName<decltype(funcPtr)>("[]", funcPtr, "AStar.TravelPathEntry& arrayDeref(int index)");
	bindMethod(indexOf, TravelPath, "int indexOf(AStar.Cell& cell)");
	bindMethod(isBlocked, TravelPath, "int isBlocked(int startAtIndex = 0)");
}

int TravelPath::isBlocked(int startIndexOneBased)
{
	if (startIndexOneBased == 0) {
		startIndexOneBased = 1;
		double curTime = time();
		for (int i = 0; i < size(); i++) {
			auto& entry = operator[](i);
			if (entry.arrivalTime != -1) {
				startIndexOneBased = i + 1;
				if (entry.arrivalTime >= curTime)
					break;
			}
		}
	}
	auto* navigator = AStarNavigator::instance;
	int startIndex = startIndexOneBased - 1;// startIndex is one-based, so
	for (int i = startIndex; i < size() - 1; i++) {
		auto& prevCell = operator[](i).cell;
		auto& nextCell = operator[](i + 1).cell;
		if (nextCell.grid != prevCell.grid)
			continue;

		AStarNode* node = navigator->getNode(prevCell);
		Direction horDir = nextCell.col > prevCell.col ? Right : Left;
		Direction vertDir = nextCell.row > prevCell.row ? Up : Down;
		if (prevCell.col == nextCell.col) { // vertical move
			if (!node->canGo(vertDir))
				return true;
		}
		else if (prevCell.row == nextCell.row) { // horizontal move
			if (!node->canGo(horDir))
				return true;
		}
		else  { // diagonal move
			auto horCell = prevCell.adjacentCell(horDir);
			AStarNode* middleHorThenVert = navigator->getNode(horCell);
			bool canGoHorThenVert = node->canGo(horDir) && middleHorThenVert->canGo(vertDir);

			auto vertCell = prevCell.adjacentCell(vertDir);
			AStarNode* middleVertThenHor = navigator->getNode(vertCell);
			bool canGoVertThenHor = node->canGo(vertDir) && middleVertThenHor->canGo(horDir);

			bool canGoDiagonal = navigator->strictDiagonals ? canGoHorThenVert && canGoVertThenHor : canGoHorThenVert || canGoVertThenHor;
			if (!canGoDiagonal)
				return true;
			auto diagCell = horCell.adjacentCell(vertDir);
			if (diagCell != nextCell) { // deep diagonal
				if (abs(prevCell.row - nextCell.row) == 2) {
					if (!navigator->getNode(diagCell)->canGo(vertDir))
						return true;
				}
				else {
					if (!navigator->getNode(diagCell)->canGo(horDir))
						return true;
				}
			}
		}
	}
	return false;
}


void TravelPath::update(Traveler* traveler, double atDist)
{
	auto te = traveler->te;
	if (lastUpdateDist != atDist) {
		if (size() > 1 && atDist > 0.0) {
			updateAtIndex(atDist);

			auto& fromEntry = operator[](atIndex - 1);
			Vec3 fromLoc = (fromEntry.bridgeIndex == -1 ? fromEntry.modelLoc : bridgeExitLoc).project(model(), traveler->te->holder->up);
			auto& toEntry = operator[](atIndex);
			Vec3 toLoc = toEntry.modelLoc.project(model(), traveler->te->holder->up);
			double lerpRatio = (atDist - fromEntry.atTravelDist) / (toEntry.atTravelDist - fromEntry.atTravelDist);
			lerpRatio = std::max(0.0, std::min(1.0, lerpRatio));
			auto diff = toLoc - fromLoc;
			updateLoc = fromLoc + diff * lerpRatio;
			auto boundAngle = [](double angle) {
				if (angle < -180)
					angle += 360;
				if (angle > 180)
					angle -= 360;
				return angle;
			};
			if (te->v_modifyrotation) {
				if (traveler->navigator->stopForTurns) {
					// do logic for stopping and turning
					auto toAngle = (toLoc - fromLoc).getXYAngle();
					if (toEntry.turnEndTime >= 0 && time() < toEntry.turnEndTime) {
						double fromAngle = startZRot;
						double turnSpeed = traveler->turnSpeed;
						if (atIndex > 1) {
							auto& prevEntry = operator[](atIndex - 2);
							fromAngle = (fromLoc - prevEntry.modelLoc.project(model(), traveler->te->holder->up)).getXYAngle();
						}
						double maxTurnAngle = boundAngle(toAngle - fromAngle);
						double startTime = fromEntry.arrivalTime;
						double turnAngle = sign(maxTurnAngle) * turnSpeed * (time() - startTime);
						updateZRot = fromAngle + turnAngle;
					}
					else updateZRot = toAngle;
				}
				else if (traveler->navigator->smoothRotations != 0.0) {
					double sx = te->b_spatialsx;
					double maxSpeed = te->v_maxspeed;
					// speed based on the ability to rotate 90 degrees in traveling te's x size
					double rotLerpSpeed = 90.0 / (sx / maxSpeed);
					// go backwards along the travel path to at least 2 * sx before this point
					// (which means he can rotate at least 180 degrees)
					int startRotIndex = atIndex - 1;
					while (startRotIndex > 0 && operator[](startRotIndex - 1).atTravelDist > atDist - 2 * sx && operator[](startRotIndex - 1).bridgeIndex == -1)
						startRotIndex--;
					double fromAngle = startZRot;
					updateZRot = startZRot;
					// Now go forward along the path and linearly interpolate rotation changes 
					for (int i = startRotIndex; i < size(); i++) {
						auto& fromEntry = operator[](std::max(0, i - 1));
						Vec3 fromLoc = (fromEntry.bridgeIndex == -1 ? fromEntry.modelLoc : bridgeExitLoc).project(model(), traveler->te->holder->up);;
						auto& toEntry = operator[](i);
						Vec3 toLoc = toEntry.modelLoc.project(model(), traveler->te->holder->up);
						auto diff = toLoc - fromLoc;
						double toAngle = diff.getXYAngle();
						if (fromEntry.bridgeIndex != -1) {
							updateZRot = toAngle;
							fromAngle = toAngle;
							continue;
						}
						if (i == startRotIndex && diff.magnitude < traveler->tinyDist) {
							startRotIndex++; // will cause it to do this again next loop so it can get a proper angle
						}
						else {
							double diffAngle = boundAngle(toAngle - fromAngle);

							double timeToRotate = fabs(diffAngle) / rotLerpSpeed;
							double distToRotate = maxSpeed * timeToRotate;
							double startDist = std::max(0.0, fromEntry.atTravelDist - 0.5 * distToRotate);
							if (atDist > startDist) {
								double endDist = startDist + distToRotate;
								double lerpRatio = std::min(1.0, (atDist - startDist) / (endDist - startDist));
								updateZRot = boundAngle(updateZRot + lerpRatio * diffAngle);
							}
							if (toEntry.atTravelDist > atDist + 2.0 * sx || (toEntry.bridgeIndex != -1 && toEntry.atTravelDist > atDist))
								break;
							fromAngle = toAngle;
						}
					}
				}
				else {
					updateZRot = diff.getXYAngle();
				}
			}
			else updateZRot = te->b_spatialrz;
		}
		else {
			updateLoc = operator[](0).modelLoc.project(model(), te->holder->up);
			updateZRot = te->rotation.z;
		}
		lastUpdateDist = atDist;
	}
	te->setLocation(updateLoc, Vec3(0.5, 0.5, 0.0));
	te->rotation.z = updateZRot;
}

inline int TravelPath::getIndex(double atDist, bool canReturnZero) const
{
	int index = atIndex;
	while (index > 1 && atDist <= operator[](index - 1).atTravelDist)
		index--;
	while (index < size() - 1 && atDist > operator[](index).atTravelDist)
		index++;
	if (canReturnZero && index == 1 && operator[](0).atTravelDist >= atDist)
		return 0;
	return index;
}

int TravelPath::updateAtIndex(double atDist, bool canReturnZero)
{
	atIndex = getIndex(atDist, canReturnZero);
	if (atIndex == 0 && !canReturnZero)
		atIndex = 1;
	return atIndex;
}

void AStarNamespace::bindInterface()
{
	SimpleDataType::bindDocumentationXMLPath("help\\FlexScriptAPIReference\\AStar\\AStar.xml");
	SimpleDataType::bindStaticTypedPropertyByName<AStarNavigator*>("navigator", "AStar.Navigator", force_cast<void*>(&AStarNamespace::__getNavigator), nullptr);
}

AStarNavigator * AStarNamespace::__getNavigator()
{
	return AStarNavigator::instance;
}

NodeAllocation AllocationRange::operator[](int oneBasedIndex)
{
	if (!traveler || oneBasedIndex > size || startIndex + oneBasedIndex > traveler->allocations.size())
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
	SimpleDataType::bindDocumentationXMLPath("help\\FlexScriptAPIReference\\AStar\\AStar.Direction.xml");
	SimpleDataType::bindStaticConstIntProperty(Left, (int)Direction::Left);
	SimpleDataType::bindStaticConstIntProperty(Right, (int)Direction::Right);
	SimpleDataType::bindStaticConstIntProperty(Up, (int)Direction::Up);
	SimpleDataType::bindStaticConstIntProperty(Down, (int)Direction::Down);
}

}