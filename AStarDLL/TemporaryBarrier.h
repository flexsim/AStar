#pragma once
#include "AStarClasses.h"
#include "AStarTypes.h"

namespace AStar {

class TemporaryBarrier : public CouplingDataType
{
	const char* getClassFactory() override { return "AStar::TemporaryBarrier"; }
	virtual void bind() override { __super::bind(); bindNumber(isApplied); bindNumber(isDynamic); }
	struct ChangeEntry {
		Cell cell;
		AStarNode savedValue;
		AStarNode newValue;
		AStarNode changeMask;
		void setCanGo(Direction dir, bool toValue) {
			newValue.setCanGo(dir, toValue);
			changeMask.setCanGo(dir, true);
		}
	};
	AStarNavigator* navigator = nullptr;
	std::vector<ChangeEntry> entries;
	bool isDynamic = false;

public:
	bool isApplied = false;
	ChangeEntry& addEntry(const Cell& cell, const AStarNode& newValue);
	ChangeEntry& operator [](const Cell& cell);
	void apply();
	void applyEntry(ChangeEntry& entry, int index, bool ignoreDynamic = false);
	void revert();
	void revertEntry(ChangeEntry& entry, int index, bool ignoreDynamic = false);
	void reset(AStarNavigator* nav) { navigator = nav; entries.clear(); isApplied = false; }

	TemporaryBarrier();
	TemporaryBarrier(AStarNavigator* nav, bool isDynamic = false);
	~TemporaryBarrier() { if (isApplied) revert(); }
};

}