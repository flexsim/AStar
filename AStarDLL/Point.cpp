#include "Point.h"


const char * Point::getClassFactory(void)
{
	return "AStar::Point";
}


void Point::bind(void)
{
	SimpleDataType::bind();

	bindDouble(x, 1);
	bindDouble(y, 1);
}