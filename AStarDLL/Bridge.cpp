#include "Bridge.h"
#include "AStarNavigator.h"
#include "macros.h"
#include "Traveler.h"

namespace AStar {

Bridge::Bridge()
	: Divider()
{
	return;
}


void Bridge::bindVariables(void)
{
	__super::bindVariables();
	bindVariable(useVirtualDistance);
	bindVariable(virtualDistance);
	bindStateVariable(geometricDistance);
	bindStateVariable(travelDistance);
	bindStateVariable(filledDistance);
	bindStateVariable(isAvailable);
	bindStateVariable(blockedTraveler);
	bindStateVariable(firstTraveler);
	bindStateVariable(lastTraveler);
	bindStateVariable(blockedPathIndex);
	bindStateVariable(nodeWidth);
	bindStateVariable(routingData);
}

void Bridge::addVertices(treenode view, Mesh* barrierMesh, float z, DrawStyle drawStyle)
{
	addPathVertices(view, barrierMesh, z, Vec4f(0.0f, 0.3f, 1.0f, 1.0f), drawStyle, isTwoWay);
}

void Bridge::onReset(AStarNavigator* nav)
{
	__super::onReset(nav);
	blockedTraveler = nullptr;
	firstTraveler = nullptr;
	lastTraveler = nullptr;
	geometricDistance = calculateDistance();
	travelDistance = useVirtualDistance ? virtualDistance : max(0.001 * nodeWidth, geometricDistance - nodeWidth);
	filledDistance = 0.0;
	isAvailable = true;
	lastUpdateTime = -1;

	Cell fromCell = nav->getCell(getPointToModelOffset() + *pointList.front());
	Cell toCell = nav->getCell(getPointToModelOffset() + *pointList.back());
	if (fromCell != toCell) {
		auto assertRoutingData = [this, nav](int index, Cell& cell) {
			Grid* grid = nav->getGrid(cell);
			nodeWidth = grid->nodeWidth;
			if (routingData.size() <= index) {
				auto data = grid->bridgeData.add(new BridgeRoutingData(this, index == 0));
				nodejoin(data->holder, ((treenode)routingData)->subnodes.add()->addData(DATATYPE_COUPLING));
			}
			auto data = routingData[index];
			data->fromCell = cell;
			if (data->grid != grid)
				data->holder->up = grid->bridgeData;
		};
		assertRoutingData(0, fromCell);
		if (isTwoWay)
			assertRoutingData(1, toCell);
		else if (routingData.size() > 1)
			routingData.remove(1);
	} else {
		routingData.clear();
	}
}

double Bridge::calculateDistance() const
{
	double total = 0;
	for (int i = 1; i < pointList.size(); i++) {
		Vec3 diff(
			pointList[i]->x - pointList[i - 1]->x,
			pointList[i]->y - pointList[i - 1]->y,
			pointList[i]->z - pointList[i - 1]->z);
		total += sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
	}
	return total;
}

double Bridge::getTravelToGeomDistScale()
{
	return (geometricDistance - nodeWidth) / travelDistance;
}

void Bridge::onEntry(Traveler * traveler, int pathIndex)
{
	AStarNavigator* nav = traveler->navigator;
	TaskExecuter* te = traveler->te;
	if (!firstTraveler)
		firstTraveler = traveler;
	traveler->bridgeData->entryTime = time();
	traveler->bridgeData->prevTraveler = lastTraveler;
	traveler->bridgeData->nextTraveler = nullptr;
	Grid* grid = nav->getGrid(traveler->travelPath[pathIndex].cell);
	if (lastTraveler)
		lastTraveler->bridgeData->nextTraveler = traveler;
	lastTraveler = traveler;
	filledDistance += grid->nodeWidth;
	if (!nav->enableCollisionAvoidance || firstTraveler == traveler) {
		traveler->bridgeEvent = createevent(new Bridge::EndArrivalEvent(this, traveler, pathIndex, time() + (travelDistance / te->v_maxspeed)))->object<FlexSimEvent>();
	}
	if (nav->enableCollisionAvoidance) {
		isAvailable = false;
		if (filledDistance < travelDistance) {
			createevent(new AvailableEvent(this, time() + (grid->nodeWidth / te->v_maxspeed)));
		}
	}
}

void Bridge::onExit(Traveler * traveler)
{
	if (traveler->bridgeData->nextTraveler)
		traveler->bridgeData->nextTraveler->bridgeData->prevTraveler = traveler->bridgeData->prevTraveler;
	if (traveler->bridgeData->prevTraveler)
		traveler->bridgeData->prevTraveler->bridgeData->nextTraveler = traveler->bridgeData->nextTraveler;

	if (traveler == firstTraveler)
		firstTraveler = traveler->bridgeData->nextTraveler;
	if (lastTraveler == traveler)
		lastTraveler = traveler->bridgeData->prevTraveler;

	Grid* grid = traveler->navigator->getGrid(traveler->travelPath[traveler->bridgeData->pathIndex].cell);

	if (firstTraveler && firstTraveler->navigator->enableCollisionAvoidance) {
		// check to see if I should adjust the firstTraveler's entryTime if he has accumulated,
		// to avoid "jumping" ahead
		double distTraveled = (time() - firstTraveler->bridgeData->entryTime) * firstTraveler->te->v_maxspeed;
		if (distTraveled > travelDistance - grid->nodeWidth) {
			distTraveled = travelDistance - grid->nodeWidth;
			firstTraveler->bridgeData->entryTime = time() - distTraveled / firstTraveler->te->v_maxspeed;
		}

		double distRemaining = travelDistance - distTraveled;
		firstTraveler->bridgeEvent = createevent(new Bridge::EndArrivalEvent(this, firstTraveler, firstTraveler->bridgeData->pathIndex,
			time() + (distRemaining / firstTraveler->te->v_maxspeed)))->object<FlexSimEvent>();
	}

	bool wasFull = !isAvailable && filledDistance >= travelDistance;
	filledDistance -= grid->nodeWidth;
	if (wasFull && (filledDistance < travelDistance || filledDistance <= 0.0)) {
		if (lastTraveler) {
			double distRemainingByTravelTime = nodeWidth - (time() - lastTraveler->bridgeData->entryTime) / lastTraveler->te->v_maxspeed;
			double distRemainingByFilledDistance = filledDistance + grid->nodeWidth - travelDistance;
			double distRemaining = max(distRemainingByFilledDistance, distRemainingByTravelTime);
			createevent(new AvailableEvent(this, time() + (distRemaining / lastTraveler->te->v_maxspeed)));
		}
		else onAvailable();
	}
}

void Bridge::onEndArrival(Traveler * traveler, int pathIndex)
{
	traveler->bridgeEvent = nullptr;
	updateLocation(traveler, geometricDistance - getGrid(traveler)->nodeWidth);
	traveler->onBridgeComplete(pathIndex);
}

void Bridge::onAvailable()
{
	isAvailable = true;
	if (blockedTraveler) {
		// move blockedTraveler onto bridge
		Traveler* traveler = blockedTraveler;
		blockedTraveler = nullptr;
		traveler->onBridgeArrival(traveler->bridgeData->routingData, (int)blockedPathIndex);
	}
}

void Bridge::updateBridgeLocations()
{
	if (lastUpdateTime == time() || !firstTraveler)
		return;
	lastUpdateTime = time();

	Vec3 offset = getPointToModelOffset();
	Traveler* t = firstTraveler;
	Grid* grid = getGrid(t);
	double distScale = getTravelToGeomDistScale();
	double curMax = travelDistance;
	double curTime = time();
	while (t) {
		double dist = min(curMax, (curTime - t->bridgeData->entryTime) * t->te->v_maxspeed);
		updateLocation(t, dist * distScale, &offset);
		curMax = dist - grid->nodeWidth;

		t = t->bridgeData->nextTraveler;
	}
}

void Bridge::updateLocation(Traveler* traveler, double geomDist, Vec3* passedOffset)
{
	Vec3 offset;
	if (passedOffset)
		offset = *passedOffset;
	else {
		offset = getPointToModelOffset();
	}
	for (int j = 1; j < pointList.size(); j++) {
		Vec3 fromLoc((Vec3)*(pointList[j - 1]) + offset);
		Vec3 toLoc((Vec3)*(pointList[j]) + offset);
		Vec3 diff = toLoc - fromLoc;
		double dist = diff.magnitude;

		if (geomDist > dist)
			geomDist -= dist;
		else {
			Vec3 interpolated = fromLoc.lerp(toLoc, geomDist / dist);

			double nextRot = diff.getXYAngle();
			while (nextRot > 180)
				nextRot -= 360;
			while (nextRot < -180)
				nextRot += 360;

			if (traveler->te->holder->up != model()) {
				interpolated = interpolated.project(model(), traveler->te->holder->up);
			}

			traveler->te->b_spatialrz = nextRot;
			traveler->te->b_spatialx = interpolated.x - 0.5 * traveler->te->b_spatialsx;
			traveler->te->b_spatialy = interpolated.y + 0.5 * traveler->te->b_spatialsx;
			traveler->te->b_spatialz = interpolated.z;
			break;
		}
	}
}

Grid * Bridge::getGrid(Traveler * traveler)
{
	return traveler->navigator->getGrid(traveler->travelPath[traveler->bridgeData->pathIndex].cell);
}

Bridge::EndArrivalEvent::EndArrivalEvent(Bridge* bridge, Traveler* object, int pathIndex, double time)
	: pathIndex(pathIndex), FlexSimEvent(bridge->holder, time, object->holder, 0) {}

}