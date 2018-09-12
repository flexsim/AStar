#pragma once
#include "FlexsimDefs.h"

namespace AStar {

class Point :
	public SimpleDataType
{
public:
	double x, y, z;

	Point() : x(0), y(0), z(0) {}
	Point(double x, double y) : x(x), y(y), z(0) {}
	Point(double x, double y, double z) : x(x), y(y), z(z) {}
	virtual const char * getClassFactory(void);
	virtual void bind(void);

	void addVertices(Mesh* mesh, float radius, float* color, float zOffset, unsigned int * incNumVerts = nullptr);
};

}