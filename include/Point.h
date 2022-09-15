#pragma once
#include "FlexsimDefs.h"
class Point :
	public SimpleDataType
{
public:
	double x, y;

	Point() : x(0), y(0) {}
	Point(double x, double y) : x(x), y(y) {}
	virtual const char * getClassFactory(void);
	virtual void bind(void);
};

