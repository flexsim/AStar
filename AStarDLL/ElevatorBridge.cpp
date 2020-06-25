#include "ElevatorBridge.h"
#include "AStarNavigator.h"
#include "ElevatorBridgeRoutingData.h"
#include "Traveler.h"

namespace AStar {
void ElevatorBridge::AStarDelegate::bind()
{
	bindObjPtr(navigator);
}

void ElevatorBridge::AStarDelegate::onBridgeComplete(TaskExecuter * te)
{
	Traveler* traveler = AStarNavigator::getTraveler(te);
	traveler->onBridgeComplete(traveler->bridgeData->pathIndex + 1);
}

TravelerBridgeData * ElevatorBridge::AStarDelegate::getBridgeData(TaskExecuter * te)
{
	return AStarNavigator::getTraveler(te)->bridgeData;
}

void ElevatorBridge::AStarDelegate::clearAllocations(TaskExecuter * te)
{
	AStarNavigator::getTraveler(te)->clearAllocations();
}

void ElevatorBridge::reset()
{
	Vec3 min, max;
	getBoundingBox(min, max);
	NodeListArray<ElevatorBridgeRoutingData>::CouplingSdtPtrType bridgeData(this->bridgeData);
	bridgeData.clear();
	AStarNavigator* nav = aStarDelegate->navigator;
	for (Grid* grid : nav->grids) {
		if (grid->minPoint.z >= min.z - 0.0001 * grid->nodeWidth && grid->minPoint.z <= max.z + 0.0001 * grid->nodeWidth) {
			Vec3 arrivalPoint = getArrivalLoc(grid->minPoint.z);
			if (grid->isLocWithinBounds(arrivalPoint, false, false)) {
				auto data = new ElevatorBridgeRoutingData;
				grid->bridgeData.add(data);
				nodejoin(data->holder, nodeadddata(this->bridgeData->subnodes.add(), DATATYPE_COUPLING));
				data->fromCell = grid->getCell(arrivalPoint);
			}
		}
	}
}

}
