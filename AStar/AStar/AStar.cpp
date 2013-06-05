#include "Barrier.h"
#include "AStarNavigator.h"
#include "AStar.h"

visible ObjectDataType* createodtderivative(char* classname)
{
	if(strcmp(classname, "AStarNavigator")==0) return new AStarNavigator;
	return NULL;
}

visible SimpleDataType* createsdtderivative(char* classname)
{
	if(strcmp(classname, "Barrier")==0) return new Barrier;
	return NULL;
}

visible void dllinitialize()
{

}

visible void dllcleanup()
{

}
