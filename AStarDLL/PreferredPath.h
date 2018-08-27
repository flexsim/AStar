#pragma once
#include "FlexsimDefs.h"
#include "Divider.h"

namespace AStar {

class PreferredPath : public Divider
{
public:
	double pathWeight;

	PreferredPath();
	PreferredPath(double pathWeight);

	virtual const char * getClassFactory(void);
	virtual void bind(void);

	// See Barrier.h for a description of these methods
	virtual void addBarriersToTable(Grid* grid) override {}
	virtual void addPassagesToTable(Grid* grid) override;
	virtual void addVertices(Mesh* barrierMesh, float z) override;
	virtual PreferredPath* toPreferredPath() override { return this; }

	/// <summary>	True if the navigator should apply this preferred path as a conditional barrier. 
	/// 			This is set when the navigator first encounters the preferred path as part of a 
	/// 			route calculation, and is then used on subsequent encounters of the same preferred
	/// 			path in the routing calculation.</summary>
	bool shouldApplyConditionalBarrier = true;
};

}
