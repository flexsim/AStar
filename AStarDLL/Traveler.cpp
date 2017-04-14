#include "Traveler.h"
#include "AStarNavigator.h"
#include "Bridge.h"
#include "macros.h"

namespace AStar {

void Traveler::bind()
{
	bindNumber(isActive);
	bindObjRef(arrivalEvent, false);
	bindNumber(nodeWidth);
}

void Traveler::onReset()
{
	isActive = false;
	nodeWidth = getNavigator()->nodeWidth;
}

void Traveler::navigatePath(TravelPath&& path, bool isDistQueryOnly)
{
	travelPath = std::move(path);
	TaskExecuter* te = getTE();
	AStarNavigator* nav = getNavigator();

	// Don't know why this was here. I'm commenting it out.
	//if (!isDistQueryOnly) {
	//	coupling = tonode(get(first(te->node_v_navigator)));
	//	while (content(holder) < 1)
	//		nodeinsertinto(holder);
		//TreeNode* idList = first(coupling);
		// TODO: figure out idLists
	//}

	//If this method is being called to get the distance from the TE to the destination, don't set
	//anything on the TE
	if (!isDistQueryOnly) {
		if (content(te->holder))
			setstate(te->holder, STATE_TRAVEL_LOADED);
		else
			setstate(te->holder, STATE_TRAVEL_EMPTY);
	}

	treenode kinematics;
	if (!isDistQueryOnly)
		kinematics = te->node_v_kinematics;
	else
		kinematics = nodeinsertinto(te->node_v_kinematics);
	double outputVector[3];
	Vec3 startLoc = nav->getLocFromCell(travelPath[0].cell);
	if (up(te->holder) != model())
		startLoc = startLoc.project(model(), up(te->holder));

	int kinFlags = 0;
	if (te->node_v_modifyrotation) {
		kinFlags |= KINEMATIC_MANAGE_ROTATIONS;
		if (!te->canRotateOnIncline())
			kinFlags |= KINEMATIC_NO_INCLINE_ROTATION;
	}
	initkinematics(kinematics, startLoc.x, startLoc.y, te->b_spatialz, 0, 0, 0, kinFlags, 0);
	double endTime = time();

	AStarPathEntry e, laste;
	int numNodes = travelPath.size();
	laste.cell = travelPath[0].cell;
	for (int i = 1; i < numNodes; i++) {
		e = travelPath[i];
		double totalTravelDist;
		if (laste.bridgeIndex == -1) {
			double nextX = (e.cell.col - laste.cell.col)*nodeWidth;
			double nextY = (e.cell.row - laste.cell.row)*nodeWidth;
			endTime = addkinematic(kinematics, nextX, nextY, 0,
				te->v_maxspeed, 0, 0, 0, 0, endTime, KINEMATIC_TRAVEL);
			totalTravelDist = sqrt(sqr(nextX) + sqr(nextY));
		} else {
			auto e = nav->edgeTableExtraData.find(laste.cell.colRow);
			AStarNodeExtraData::BridgeEntry& entry = e->second.bridges[laste.bridgeIndex];
			totalTravelDist = entry.bridge->calculateDistance();
			int begin, end, inc;
			if (entry.isAtBridgeStart) {
				begin = 0;
				end = entry.bridge->pointList.size();
				inc = 1;
			} else {
				begin = entry.bridge->pointList.size();
				end = -1;
				inc = -1;
			}
			Point* lastPoint = entry.bridge->pointList[begin];
			double startZ = lastPoint->z;
			for (int i = begin + inc; i != end; i += inc) {
				Point* point = entry.bridge->pointList[i];
				Vec3 diff(point->x - lastPoint->x, point->y - lastPoint->y, point->z - lastPoint->z);
				endTime = addkinematic(kinematics, diff.x, diff.y, diff.z,
					te->v_maxspeed, 0, 0, 0, 0, endTime, KINEMATIC_TRAVEL);
				lastPoint = point;
			}
			double zDiff = lastPoint->z - startZ;
			if (fabs(zDiff) > 0.001) {
				addkinematic(kinematics, 0, 0, -zDiff,
					te->v_maxspeed, 0, 0, 0, 0, endTime, KINEMATIC_TRAVEL);
			}
		}

		if (!isDistQueryOnly) {
			te->v_totaltraveldist += totalTravelDist;


			//Traffic info
			AStarNodeExtraData* extra = nav->assertExtraData(e.cell);
			unsigned int* involvedextra;
			if (e.cell.row > laste.cell.row) {
				if (e.cell.col > laste.cell.col) involvedextra = &extra->nrFromDownLeft;
				else if (e.cell.col < laste.cell.col) involvedextra = &extra->nrFromDownRight;
				else involvedextra = &extra->nrFromDown;
			} else if (e.cell.row < laste.cell.row) {
				if (e.cell.col > laste.cell.col) involvedextra = &extra->nrFromUpLeft;
				else if (e.cell.col < laste.cell.col) involvedextra = &extra->nrFromUpRight;
				else involvedextra = &extra->nrFromUp;
			} else if (e.cell.col > laste.cell.col)
				involvedextra = &extra->nrFromLeft;
			else involvedextra = &extra->nrFromRight;

			involvedextra[0]++;
			if (involvedextra[0] > nav->maxTraveled) nav->maxTraveled = involvedextra[0];
		}

		laste = e;
	}

	if (!isDistQueryOnly) {
		nav->activeTravelers.push_front(this);
		isActive = true;
		activeEntry = nav->activeTravelers.begin();
		arrivalEvent = createevent(new ArrivalEvent(this, endTime))->objectAs(ArrivalEvent);
	}
}

void Traveler::onArrival()
{
	TaskExecuter* te = getTE();
	TreeNode* kinematics = te->node_v_kinematics;
	updatekinematics(kinematics, te->holder, time());
	te->b_spatialx -= 0.5*te->b_spatialsx;
	te->b_spatialy += 0.5*te->b_spatialsy;
	getNavigator()->activeTravelers.erase(activeEntry);
	isActive = false;
	te->onDestinationArrival(0);
}

AStarNavigator* Traveler::getNavigator()
{
	return ownerobject(holder)->objectAs(AStarNavigator);
}

void Traveler::updateLocation()
{
	TaskExecuter* te = getTE();
	TreeNode* kinematics = te->node_v_kinematics;
	updatekinematics(kinematics, te->holder, time());
	te->b_spatialx -= 0.5*te->b_spatialsx;
	te->b_spatialy += 0.5*te->b_spatialsy;
}

}