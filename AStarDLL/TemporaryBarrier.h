#pragma once
#include "AStarClasses.h"
#include "AStarTypes.h"

namespace AStar {

class TemporaryBarrier
{
	struct ChangeEntry {
		AStarCell cell;
		AStarNode savedValue;
		AStarNode newValue;
	};

	AStarNavigator* navigator = nullptr;
	std::vector<ChangeEntry> entries;

public:
	bool isApplied = false;
	void addEntry(const AStarCell& cell, const AStarNode& newValue);
	void apply();
	void unapply();
	void reset(AStarNavigator* nav) { navigator = nav; entries.clear(); isApplied = false; }

	TemporaryBarrier() {}
	TemporaryBarrier(AStarNavigator* nav) : navigator(nav) {}
	~TemporaryBarrier() { if (isApplied) unapply(); }


};

}