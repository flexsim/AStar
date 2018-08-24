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

const char * Bridge::getClassFactory(void)
{
	return "AStar::Bridge";
}


void Bridge::bind(void)
{
	Divider::bind();
	bindDouble(isTwoWay, 1);
	bindDouble(useVirtualDistance, 1);
	bindDouble(virtualDistance, 1);
	bindNumber(geometricDistance);
	bindNumber(travelDistance);
	bindNumber(filledDistance);
	bindNumber(isAvailable);
	bindObjPtr(blockedTraveler);
	bindObjPtr(firstTraveler);
	bindObjPtr(lastTraveler);
	bindNumber(blockedPathIndex);
	bindNumber(nodeWidth);
}

void Bridge::addPassagesToTable(Grid* grid)
{
	if (pointList.size() < 2)
		return;

	AStarCell fromCell = grid->getCellFromLoc(Vec3(pointList[0]->x, pointList[0]->y, pointList[0]->z));
	AStarCell toCell = grid->getCellFromLoc(Vec3(pointList.back()->x, pointList.back()->y, pointList.back()->z));
	if (fromCell == toCell)
		return;

	// add bridge data to cells
	auto addExtraData = [&](const AStarCell& cell, bool isAtStart) {
		AStarNodeExtraData* entry = grid->navigator->assertExtraData(cell, BridgeData);
		grid->navigator->getNode(cell)->hasBridgeStartPoint = true;
		entry->bridges.push_back(AStarNodeExtraData::BridgeEntry());
		entry->bridges.back().bridge = this;
		entry->bridges.back().isAtBridgeStart = isAtStart;
	};

	addExtraData(fromCell, true);
	if (isTwoWay)
		addExtraData(toCell, false);
}

void Bridge::addVertices(Mesh* barrierMesh, float z)
{
	addPathVertices(barrierMesh, z, Vec4f(0.0f, 0.3f, 1.0f, 1.0f));
}

void Bridge::onReset(AStarNavigator* nav)
{
	blockedTraveler = nullptr;
	firstTraveler = nullptr;
	lastTraveler = nullptr;
	geometricDistance = calculateDistance();
	Vec3 modelPos(pointList[0]->x, pointList[0]->y, pointList[0]->z);
	Grid* grid = nav->getGrid(nav->getCellFromLoc(modelPos));
	nodeWidth = grid->nodeWidth;
	travelDistance = useVirtualDistance ? virtualDistance : max(0.001 * nodeWidth, geometricDistance - nodeWidth);
	filledDistance = 0.0;
	isAvailable = true;
	lastUpdateTime = -1;
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
	traveler->bridgeData.entryTime = time();
	traveler->bridgeData.prevTraveler = lastTraveler;
	traveler->bridgeData.nextTraveler = nullptr;
	Grid* grid = nav->getGrid(traveler->travelPath[pathIndex].cell);
	if (lastTraveler)
		lastTraveler->bridgeData.nextTraveler = traveler;
	lastTraveler = traveler;
	filledDistance += grid->nodeWidth;
	if (!nav->enableCollisionAvoidance || firstTraveler == traveler) {
		createevent(new Bridge::EndArrivalEvent(this, traveler, pathIndex, time() + (travelDistance / te->v_maxspeed)));
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
	traveler->bridgeData.bridge = nullptr;
	if (traveler->bridgeData.nextTraveler)
		traveler->bridgeData.nextTraveler->bridgeData.prevTraveler = traveler->bridgeData.prevTraveler;
	if (traveler->bridgeData.prevTraveler)
		traveler->bridgeData.prevTraveler->bridgeData.nextTraveler = traveler->bridgeData.nextTraveler;

	if (traveler == firstTraveler)
		firstTraveler = traveler->bridgeData.nextTraveler;
	if (lastTraveler == traveler)
		lastTraveler = traveler->bridgeData.prevTraveler;

	Grid* grid = traveler->navigator->getGrid(traveler->travelPath[traveler->bridgeData.pathIndex].cell);

	if (firstTraveler && firstTraveler->navigator->enableCollisionAvoidance) {
		// check to see if I should adjust the firstTraveler's entryTime if he has accumulated,
		// to avoid "jumping" ahead
		double distTraveled = (time() - firstTraveler->bridgeData.entryTime) * firstTraveler->te->v_maxspeed;
		if (distTraveled > travelDistance - grid->nodeWidth) {
			distTraveled = travelDistance - grid->nodeWidth;
			firstTraveler->bridgeData.entryTime = time() - distTraveled / firstTraveler->te->v_maxspeed;
		}

		double distRemaining = travelDistance - distTraveled;
		createevent(new Bridge::EndArrivalEvent(this, firstTraveler, firstTraveler->bridgeData.pathIndex,
			time() + (distRemaining / firstTraveler->te->v_maxspeed)));
	}

	bool wasFull = !isAvailable && filledDistance >= travelDistance;
	filledDistance -= grid->nodeWidth;
	if (wasFull && (filledDistance < travelDistance || filledDistance <= 0.0)) {
		if (lastTraveler) {
			double distRemaining = nodeWidth - (time() - lastTraveler->bridgeData.entryTime) / lastTraveler->te->v_maxspeed;
			createevent(new AvailableEvent(this, time() + (distRemaining / lastTraveler->te->v_maxspeed)));
		}
		else onAvailable();
	}
}

void Bridge::onEndArrival(Traveler * traveler, int pathIndex)
{
	updateLocation(traveler, geometricDistance - getGrid(traveler)->nodeWidth);
	traveler->navigatePath(pathIndex);
}

void Bridge::onAvailable()
{
	isAvailable = true;
	if (blockedTraveler) {
		// move blockedTraveler onto bridge
		Traveler* traveler = blockedTraveler;
		blockedTraveler = nullptr;
		traveler->onBridgeArrival(this, blockedPathIndex);
	}
}

void Bridge::updateLocations()
{
	if (lastUpdateTime == time() || !firstTraveler)
		return;
	lastUpdateTime = time();

	Traveler* t = firstTraveler;
	Grid* grid = getGrid(t);
	double distScale = getTravelToGeomDistScale();
	double curMax = travelDistance;
	double curTime = time();
	while (t) {
		double dist = min(curMax, (curTime - t->bridgeData.entryTime) * t->te->v_maxspeed);
		updateLocation(t, dist * distScale);
		curMax = dist - grid->nodeWidth;

		t = t->bridgeData.nextTraveler;
	}
}

void Bridge::updateLocation(Traveler* traveler, double geomDist)
{
	for (int j = 1; j < pointList.size(); j++) {
		Vec3 fromLoc(
			pointList[j - 1]->x,
			pointList[j - 1]->y,
			pointList[j - 1]->z);
		Vec3 toLoc(
			pointList[j]->x,
			pointList[j]->y,
			pointList[j]->z);
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

			traveler->te->b_spatialrz = nextRot;
			traveler->te->b_spatialx = interpolated.x - 0.5 * traveler->te->b_spatialsx;
			traveler->te->b_spatialy = interpolated.y + 0.5 * traveler->te->b_spatialsx;
			traveler->te->b_spatialz = interpolated.z + traveler->bridgeData.spatialz;
			break;
		}
	}
}

Grid * Bridge::getGrid(Traveler * traveler)
{
	return traveler->navigator->getGrid(traveler->travelPath[traveler->bridgeData.pathIndex].cell);
}


Bridge::ArrivalEvent::ArrivalEvent(Bridge* bridge, Traveler* object, int pathIndex, double time)
	: pathIndex(pathIndex), FlexSimEvent(bridge->holder, time, object->holder, 0) 
{
}

void Bridge::ArrivalEvent::execute() 
{ 
	involved->objectAs(Traveler)->onBridgeArrival(partner()->objectAs(Bridge), pathIndex); 
}

Bridge::EndArrivalEvent::EndArrivalEvent(Bridge* bridge, Traveler* object, int pathIndex, double time)
	: pathIndex(pathIndex), FlexSimEvent(bridge->holder, time, object->holder, 0) {}

}