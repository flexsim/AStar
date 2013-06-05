#include "Barrier.h"


Barrier::Barrier()
	: x0(0)
	, y0(0)
	, x1(0)
	, y1(0)
{
	return;
}

Barrier::Barrier(double x0, double y0, double x1, double y1)
	: x0(x0)
	, y0(y0)
	, x1(x1)
	, y1(y1)
{
	return;
}

Barrier::~Barrier()
{
	return;
}

const char * Barrier::getClassFactory(void)
{
	return "AStar::Barrier";
}


void Barrier::bind(void)
{
	SimpleDataType::bind();

	bindDouble(x0, 1);
	bindDouble(y0, 1);
	bindDouble(x1, 1);
	bindDouble(y1, 1);
}

void Barrier::getBoundingBox(double& x0, double& y0, double& x1, double& y1)
{
	x0 = this->x0;
	y0 = this->y0;
	x1 = this->x1;
	y1 = this->y1;
}

void Barrier::modifyTable(AStarNode* edgeTable, unsigned int sx, unsigned int sy)
{

	return;
}
