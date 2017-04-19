#pragma once
#include "AStarTypes.h"

namespace AStar {

class TemporaryBarrier
{
	struct ChangeEntry {
		AStarCell cell;
		AStarNode savedValue;
		AStarNode newValue;
	};

	std::vector<ChangeEntry> entries;
	AStarNavigator* navigator;
	bool isApplied = false;

public:
	void addEntry(const AStarCell& cell, const AStarNode& newValue);
	void apply();
	void unapply();

	TemporaryBarrier(AStarNavigator* navigator) : navigator(navigator) {}
	~TemporaryBarrier() { if (isApplied) unapply(); }


};

}