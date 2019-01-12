#include "ElevatorBridge.h"
#include "AStarNavigator.h"
#include "ElevatorBridgeRoutingData.h"

namespace AStar {
void ElevatorBridge::AStarDelegate::bind()
{
	bindObjPtr(navigator);
}

void ElevatorBridge::AStarDelegate::onDestArrival(TaskExecuter * te)
{

}

void ElevatorBridge::reset()
{
	Vec3 min, max;
	getBoundingBox(min, max);
	NodeListArray<ElevatorBridgeRoutingData>::CouplingSdtPtrType bridgeData(this->bridgeData);
	bridgeData.clear();
	AStarNavigator* nav = aStarDelegate->navigator;
	for (Grid* grid : nav->grids) {
		if (grid->minPoint.z >= min.z && grid->minPoint.z <= max.z) {
			Vec3 arrivalPoint = getArrivalLoc(grid->minPoint.z);
			if (grid->isLocWithinBounds(arrivalPoint, false)) {
				auto data = new ElevatorBridgeRoutingData;
				grid->bridgeData.add(data);
				nodejoin(data->holder, nodeadddata(this->bridgeData->subnodes.add(), DATATYPE_COUPLING));
				data->fromCell = grid->getCell(arrivalPoint);
			}
		}
	}
}

}
