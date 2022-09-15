#include "TemporaryBarrier.h"
#include "AStarNavigator.h"

namespace AStar {

TemporaryBarrier::ChangeEntry& TemporaryBarrier::addEntry(const Cell& cell, const AStarNode& newValue)
{
	entries.push_back(ChangeEntry());
	auto& entry = entries.back();
	entry.cell = cell;
	entry.newValue = newValue;
	AStarNode& node = *navigator->getNode(cell);
	entry.savedValue = node;
	entry.changeMask = 0;
	return entries.back();
}

TemporaryBarrier::ChangeEntry& TemporaryBarrier::operator[](const Cell & cell)
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
		applyEntry(entries[i], i);
	}
	isApplied = true;
}

void TemporaryBarrier::applyEntry(ChangeEntry& entry, int index, bool ignoreDynamic)
{
	AStarNode* toNode = navigator->getNode(entry.cell);
	AStarNode& fromNode = entry.newValue;
	entry.savedValue = *toNode;
	toNode->value = (toNode->value & ~entry.changeMask.value) | (fromNode.value & entry.changeMask.value);
	if (isDynamic && !ignoreDynamic) {
		auto extra = navigator->assertExtraData(entry.cell, DynamicBarrierData);
		extra->dynamicBarrierChanges.push_back(DynamicBarrierChange(this, index));
	}
}

void TemporaryBarrier::revert()
{
	if (!isApplied)
		return;
	for (int i = entries.size() - 1; i >= 0; i--) {
		revertEntry(entries[i], i);
	}
	isApplied = false;
}

void TemporaryBarrier::revertEntry(ChangeEntry& entry, int index, bool ignoreDynamic)
{
	if (isDynamic && !ignoreDynamic) {
		// when it's a dynamic barrier (added/removed dynamically during simulation), then I need to 
		// do some special stuff to make sure that things will be restored to the proper state when 
		// they are removed. To solve this, I store the set of current dynamic barrier changes 
		// in a vector on the node's extra data. The main point is, when I revert, I need to revert 
		// the *first change made by this barrier (if this barrier applied multiple changes to the 
		// same node), then re-apply each of the changes that were applied after this barrier's changes 
		// were made
		AStarNodeExtraData* extra = navigator->assertExtraData(entry.cell, DynamicBarrierData);
		bool found = false;
		auto& changes = extra->dynamicBarrierChanges;
		// find the first change made by this barrier
		for (int i = 0; i < (int)changes.size(); i++) {
			if (changes[i].barrier == this) {
				// revert all changes in backwards order from that point
				int index = changes[i].entryIndex;
				revertEntry(entries[index], index, true);
				for (int j = (int)changes.size() - 1; j >= i;  j--) {
					auto& entry = changes[j];
					int index = entry.entryIndex;
					entry.barrier->revertEntry(entry.barrier->entries[index], index, true);
				}
				// erase the range of changes associated with this barrier
				changes.erase(changes.begin() + i);
				// re-apply each of the changes made after this barrier's changes
				for (int j = i; j < changes.size(); j++) {
					auto& entry = changes[j];
					int index = entry.entryIndex;
					entry.barrier->applyEntry(entry.barrier->entries[index], index, true);
				}
				break;
			}
		}
	}
	else {
		AStarNode* toNode = navigator->getNode(entry.cell);
		AStarNode& fromNode = entry.savedValue;
		toNode->value = (toNode->value & ~entry.changeMask.value) | (fromNode.value & entry.changeMask.value);
	}
}

TemporaryBarrier::TemporaryBarrier()
{
}

TemporaryBarrier::TemporaryBarrier(AStarNavigator * nav, bool isDynamic) : navigator(nav), isDynamic(isDynamic)
{
}

}