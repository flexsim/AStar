#pragma once
#include "FlexsimDefs.h"

namespace AStar {

class Point : public SimpleDataType, public Vec3
{
public:

	Point() : Vec3(0.0, 0.0, 0.0) {}
	Point(double x, double y) : Vec3(x, y, 0.0) {}
	Point(double x, double y, double z) : Vec3(x, y, z) {}
	virtual const char * getClassFactory(void);
	virtual void bind(void);
	Point& operator = (const Vec3& pos) { x = pos.x; y = pos.y; z = pos.z; return *this; }

	void addVertices(Mesh* mesh, float radius, float* color, float zOffset, bool linesOnly);
};

}