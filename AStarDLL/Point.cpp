#include "Point.h"

namespace AStar {

const char * Point::getClassFactory(void)
{
	return "AStar::Point";
}


void Point::bind(void)
{
	SimpleDataType::bind();

	bindDouble(x, 1);
	bindDouble(y, 1);
	bindDouble(z, 1);
}

}