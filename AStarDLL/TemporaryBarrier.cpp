#include "TemporaryBarrier.h"
#include "AStarNavigator.h"

namespace AStar {

TemporaryBarrier::ChangeEntry& TemporaryBarrier::addEntry(const AStarCell& cell, const AStarNode& newValue)
{
	entries.push_back(ChangeEntry());
	entries.back().cell = cell;
	entries.back().newValue = newValue;
	AStarNode& node = *navigator->getNode(cell);
	entries.back().savedValue = node;
	return entries.back();
}

TemporaryBarrier::ChangeEntry& TemporaryBarrier::operator[](const AStarCell & cell)
{
	for (int i = (int)entries.size() - 1; i >= 0; i--) {
		if (entries[i].cell == cell)
			return entries[i];
	}
	AStarNode& node = *navigator->getNode(cell);
	return addEntry(cell, node);
}

void TemporaryBarrier::apply()
{
	if (isApplied)
		return;
	for (int i = 0; i < entries.size(); i++) {
		AStarNode* toNode = navigator->getNode(entries[i].cell);
		AStarNode& fromNode = entries[i].newValue;
		entries[i].savedValue = *toNode;
		toNode->value = (toNode->value & ~valueMask.value) | (fromNode.value & valueMask.value);
	}
	isApplied = true;
}

void TemporaryBarrier::unapply()
{
	if (!isApplied)
		return;
	for (int i = entries.size() - 1; i >= 0; i--) {
		AStarNode* toNode = navigator->getNode(entries[i].cell);
		AStarNode& fromNode = entries[i].savedValue;
		toNode->value = (toNode->value & ~valueMask.value) | (fromNode.value & valueMask.value);
	}
	isApplied = false;
}

TemporaryBarrier::TemporaryBarrier()
{
	valueMask.value = 0;
	valueMask.canGoDown = true;
	valueMask.canGoUp = true;
	valueMask.canGoLeft = true;
	valueMask.canGoRight = true;
}

TemporaryBarrier::TemporaryBarrier(AStarNavigator * nav) : navigator(nav)
{
	valueMask.value = 0;
	valueMask.canGoDown = true;
	valueMask.canGoUp = true;
	valueMask.canGoLeft = true;
	valueMask.canGoRight = true;
}

}