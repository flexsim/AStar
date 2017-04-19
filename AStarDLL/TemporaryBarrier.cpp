#include "TemporaryBarrier.h"
#include "AStarNavigator.h"

namespace AStar {

void TemporaryBarrier::addEntry(const AStarCell& cell, const AStarNode& newValue)
{
	entries.push_back(ChangeEntry());
	entries.back().cell = cell;
	entries.back().newValue = newValue;
	entries.back().savedValue = *navigator->getNode(cell);
}

void TemporaryBarrier::apply()
{
	if (isApplied)
		return;
	for (int i = 0; i < entries.size(); i++) {
		AStarNode* toNode = navigator->getNode(entries[i].cell);
		AStarNode& fromNode = entries[i].newValue;
		toNode->canGoUp = fromNode.canGoUp;
		toNode->canGoDown = fromNode.canGoDown;
		toNode->canGoLeft = fromNode.canGoLeft;
		toNode->canGoRight = fromNode.canGoRight;
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
		toNode->canGoUp = fromNode.canGoUp;
		toNode->canGoDown = fromNode.canGoDown;
		toNode->canGoLeft = fromNode.canGoLeft;
		toNode->canGoRight = fromNode.canGoRight;
	}
	isApplied = false;
}

}