#include "PreferredPath.h"
#include "OneWayDivider.h"
#include "Divider.h"
#include "Point.h"
#include "Barrier.h"
#include "AStarNavigator.h"
#include "AStar.h"
#include "Bridge.h"
#include "Traveler.h"

namespace AStar {

visible ObjectDataType* createodtderivative(char* classname)
{
	if(strcmp(classname, "AStarNavigator")==0) return new AStarNavigator;
	return NULL;
}

visible SimpleDataType* createsdtderivative(char* classname)
{
	if(strcmp(classname, "PreferredPath")==0) return new PreferredPath;
	if(strcmp(classname, "OneWayDivider")==0) return new OneWayDivider;
	if(strcmp(classname, "Divider")==0) return new Divider;
	if(strcmp(classname, "Point")==0) return new Point;
	if (strcmp(classname, "Barrier") == 0) return new Barrier;
	if (strcmp(classname, "Bridge") == 0) return new Bridge;
	if (strcmp(classname, "Traveler") == 0) return new Traveler;
	if (strcmp(classname, "Traveler::ArrivalEvent") == 0) return new Traveler::ArrivalEvent;
	return NULL;
}

visible void dllinitialize()
{

}

visible void dllcleanup()
{

}

}