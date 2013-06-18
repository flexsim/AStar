#include "Point.h"


const char * Point::getClassFactory(void)
{
	return "AStar::Point";
}


void Point::bind(void)
{
	SimpleDataType::bind();

	bindDouble(x, 0);
	bindDouble(y, 0);
}