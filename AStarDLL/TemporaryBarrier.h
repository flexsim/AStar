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
	AStarNode valueMask;
	bool isApplied = false;
	ChangeEntry& addEntry(const AStarCell& cell, const AStarNode& newValue);
	ChangeEntry& operator [](const AStarCell& cell);
	void apply();
	void unapply();
	void reset(AStarNavigator* nav) { navigator = nav; entries.clear(); isApplied = false; }

	TemporaryBarrier();
	TemporaryBarrier(AStarNavigator* nav);
	~TemporaryBarrier() { if (isApplied) unapply(); }


};

}