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

	AStarNavigator* navigator;
	bool isApplied = true;
	std::vector<ChangeEntry> entries;

public:
	void addEntry(const AStarCell& cell, const AStarNode& newValue);
	void apply();
	void unapply();

	TemporaryBarrier(AStarNavigator* navigator) : navigator(navigator) {
	}
	~TemporaryBarrier() { if (isApplied) unapply(); }


};

}