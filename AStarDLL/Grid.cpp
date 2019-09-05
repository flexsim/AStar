#include "Grid.h"
#include "AStarNavigator.h"
#include "TemporaryBarrier.h"
#include "BridgeRoutingData.h"

namespace AStar {


void Grid::bind()
{
	if (getBindMode() == SDT_BIND_ON_LOAD)
		bindNavigator();
	bindDouble(nodeWidth, 1);
	bindNumber(isBounded);
	bindNumber(isLowestGrid);
	bindDoubleByName("minPointX", minPoint.x, 1);
	bindDoubleByName("minPointY", minPoint.y, 1);
	bindDoubleByName("minPointZ", minPoint.z, 1);
	bindDoubleByName("maxPointX", maxPoint.x, 1);
	bindDoubleByName("maxPointY", maxPoint.y, 1);
	bindDoubleByName("maxPointZ", maxPoint.z, 1);
	bindDoubleByName("gridOriginX", gridOrigin.x, 1);
	bindDoubleByName("gridOriginY", gridOrigin.y, 1);
	bindDoubleByName("gridOriginZ", gridOrigin.z, 1);
	bindDouble(isUserCustomized, 1);
	bindSubNode(bridgeData, 0);

	bindCallback(dragPressedPick, Grid);
	bindCallback(makeDirty, Grid);
}

bool Grid::isLocWithinBounds(const Vec3 & modelLoc, bool canExpand, bool addSurroundDepth) const
{

	double offset = addSurroundDepth ? (navigator->surroundDepth + 1) * nodeWidth : 0;
	double z = modelLoc.z + 0.001 * nodeWidth;
	// return false if it's not in the z range
	if ((z < minPoint.z && !isLowestGrid) || z >= maxPoint.z)
		return false;
	if ((modelLoc.x - offset >= minPoint.x && modelLoc.y - offset >= minPoint.y)
			&& (modelLoc.x + offset <= maxPoint.x && modelLoc.y + offset <= maxPoint.y))
		return true;

	if (canExpand) {
		if (!isBounded)
			return true;
		Vec2 min, max;
		findGrowthBounds(min, max);
		if ((modelLoc.x - offset >= min.x && modelLoc.y - offset >= min.y)
				&& (modelLoc.x + offset <= max.x && modelLoc.y + offset <= max.y))
			return true;
	}
	return false;
}

bool Grid::isLocWithinVerticalBounds(double z) const
{
	return (isLowestGrid || z >= minPoint.z - 0.001 * nodeWidth) && z < maxPoint.z;
}

bool Grid::intersectBoundingBox(Vec3 & min, Vec3 & max) const
{
	return false;
}

bool Grid::growToEncompassBoundingBox(Vec3 min, Vec3 max, bool addSurroundDepth)
{
	if (addSurroundDepth) {
		double offset = (navigator->surroundDepth + 2) * nodeWidth;
		min.x -= offset;
		min.y -= offset;
		max.x += offset;
		max.y += offset;
	}

	if (max.x <= maxPoint.x && min.x >= minPoint.x && max.y <= maxPoint.y && min.y >= minPoint.y)
		return true;

	Vec2 growthBoundMin, growthBoundMax;
	findGrowthBounds(growthBoundMin, growthBoundMax);

	if (growthBoundMax.x < min.x || growthBoundMax.y < min.y || growthBoundMin.x > max.x || growthBoundMin.y > max.y)
		return false;

	bool didGrowX = false;
	if (max.x > maxPoint.x && growthBoundMax.x > maxPoint.x) {
		didGrowX = true;
		maxPoint.x = min(max.x, std::nextafter(growthBoundMax.x, -DBL_MAX));
	}
	if (min.x < minPoint.x && growthBoundMin.x < minPoint.x) {
		didGrowX = true;
		minPoint.x = max(min.x, std::nextafter(growthBoundMin.x, DBL_MAX));
	}

	if (didGrowX)
		findGrowthBounds(growthBoundMin, growthBoundMax);

	if (max.y > maxPoint.y && growthBoundMax.y > maxPoint.y) {
		maxPoint.y = min(max.y, std::nextafter(growthBoundMax.y, -DBL_MAX));
	}
	if (min.y < minPoint.y && growthBoundMin.y < minPoint.y) {
		minPoint.y = max(min.y, std::nextafter(growthBoundMin.y, DBL_MAX));
	}

	navigator->setDirty();

	return isLocWithinBounds(min, false, false) && isLocWithinBounds(max, false, false);
}

bool Grid::shrinkToFitGrowthBounds()
{
	Vec2 min, max;
	findGrowthBounds(min, max);
	if (maxPoint.x > max.x || minPoint.x < min.x || maxPoint.y > max.y || minPoint.y < min.y) {
		struct BorderCompare {
			double* gridLoc;
			double* growthBound;
			bool shouldBeLess;
		};
		std::vector<BorderCompare> badBorders;
		if (maxPoint.x > max.x)
			badBorders.push_back({ &maxPoint.x, &max.x, true });
		if (minPoint.x < min.x)
			badBorders.push_back({ &minPoint.x, &min.x, false });
		if (maxPoint.y > max.y)
			badBorders.push_back({ &maxPoint.y, &max.y, true });
		if (minPoint.y < min.y)
			badBorders.push_back({ &minPoint.y, &min.y, false });
		
		std::sort(badBorders.begin(), badBorders.end(), 
			[](BorderCompare& left, BorderCompare& right) -> bool
				{ return fabs(*(left.gridLoc) - *(left.growthBound)) < fabs(*(right.gridLoc) - *(right.growthBound)); });

		for (BorderCompare& compare : badBorders) {
			if (((*compare.gridLoc) < (*compare.growthBound)) == compare.shouldBeLess)
				continue;
			*compare.gridLoc = std::nextafter(*compare.growthBound, compare.shouldBeLess ? -DBL_MAX : DBL_MAX);
			findGrowthBounds(min, max);
		}
		minPoint.x = min(minPoint.x, maxPoint.x);
		minPoint.y = min(minPoint.y, maxPoint.y);
		return true;
	}
	return false;
}

void Grid::findGrowthBounds(Vec2 & min, Vec2 & max) const
{
	min = Vec2(-DBL_MAX, -DBL_MAX);
	max = Vec2(DBL_MAX, DBL_MAX);
	for (Grid* grid : navigator->grids) {
		if (grid == this || fabs(grid->minPoint.z - minPoint.z) > nodeWidth)
			continue;
		if ((grid->minPoint.y >= minPoint.y && grid->minPoint.y <= maxPoint.y)
			|| (grid->maxPoint.y >= minPoint.y && grid->maxPoint.y <= maxPoint.y)
			|| (minPoint.y >= grid->minPoint.y && minPoint.y <= grid->maxPoint.y)
			|| (maxPoint.y >= grid->minPoint.y && maxPoint.y <= grid->maxPoint.y)) {

			if (grid->minPoint.x > minPoint.x)
				max.x = min(max.x, grid->minPoint.x);
			else min.x = max(min.x, grid->maxPoint.x);
		}

		if ((grid->minPoint.x >= minPoint.x && grid->minPoint.x <= maxPoint.x)
			|| (grid->maxPoint.x >= minPoint.x && grid->maxPoint.x <= maxPoint.x)
			|| (minPoint.x >= grid->minPoint.x && minPoint.x <= grid->maxPoint.x)
			|| (maxPoint.x >= grid->minPoint.x && maxPoint.x <= grid->maxPoint.x)) {

			if (grid->minPoint.y > minPoint.y)
				max.y = min(max.y, grid->minPoint.y);
			else min.y = max(min.y, grid->maxPoint.y);
		}

	}
}

Cell Grid::getCell(const Vec3 & modelLoc)
{
	Cell cell;
	cell.grid = rank;
	int col = (int)round((modelLoc.x - gridOrigin.x) / nodeWidth);
	cell.col = max(0, col);
	if (nodes.size() > 0)
		cell.col = min(nodes[0].size() - 1, cell.col);
	int row = (int)round((modelLoc.y - gridOrigin.y) / nodeWidth);
	cell.row = max(0, row);
	cell.row = min(nodes.size() - 1, cell.row);
	return cell;
}

void Grid::reset(AStarNavigator* nav)
{
	heatMapBuffer.reset(nullptr);
	navigator = nav;
}

void Grid::growToBarriers() 
{
	auto& barriers = navigator->barriers;
	auto& objectBarrierList = navigator->objectBarrierList;
	auto& barrierList = navigator->barrierList;
	auto& customBarriers = navigator->customBarriers;

	// Don't build edgeTable if there are no barriers
	if (content(barriers) == 0 && objectBarrierList.size() == 0)
		return;

	// go through the barriers to determine bounds
	for (int i = 0; i < barrierList.size(); i++) {
		Barrier* barrier = barrierList[i];
		Vec3 min, max;
		barrier->getBoundingBox(min, max);
		if (isLocWithinVerticalBounds(min.z)) {
			if ((!isLocWithinBounds(min, false, true) && isLocWithinBounds(min, true, true))
				|| (!isLocWithinBounds(max, false, true) && isLocWithinBounds(max, true, true)))
				growToEncompassBoundingBox(min, max, true);
		}
	}

	// go through objects to determine bounds
	for (int i = 1; i <= customBarriers.size(); i++) {
		Variant& element = customBarriers[i];
		if (element.size() == 1) {
			Vec3 min, max;
			// spatialx/y are the top left corner
			// Treat objects as a solid barrier
			AStarNavigator::getBoundingBox(element[1], min, max);
			if (isLocWithinVerticalBounds(min.z)) {
				if ((!isLocWithinBounds(min, false, true) && isLocWithinBounds(min, true, true))
					|| (!isLocWithinBounds(max, false, true) && isLocWithinBounds(max, true, true)))
					growToEncompassBoundingBox(min, max, true);
			}
		}
		else if (element.size() == 3) {
			// blockGridModelPos
			Vec3 min = Vec3(element[1], element[2], element[3]);
			Vec3 max = min;
			if (isLocWithinVerticalBounds(min.z)) {
				if ((!isLocWithinBounds(min, false, true) && isLocWithinBounds(min, true, true))
					|| (!isLocWithinBounds(max, false, true) && isLocWithinBounds(max, true, true)))
					growToEncompassBoundingBox(min, max, true);
			}
		}
		else if (customBarriers[i].size() == 7) {
			// divideGridModelLine
			Vec3 min = Vec3(min(element[1], element[4]), min(element[2], element[5]), element[3]);
			Vec3 max = Vec3(max(element[1], element[4]), max(element[2], element[5]), element[6]);

			if (isLocWithinVerticalBounds(min.z)) {
				if ((!isLocWithinBounds(min, false, true) && isLocWithinBounds(min, true, true))
					|| (!isLocWithinBounds(max, false, true) && isLocWithinBounds(max, true, true)))
					growToEncompassBoundingBox(min, max, true);
			}
		}
	}
}

void Grid::buildNodeTable()
{
	nodes.clear();

	auto& barrierList = navigator->barrierList;
	auto& customBarriers = navigator->customBarriers;

	resolveGridOrigin();

	int numCols, numRows;
	if (maxPoint.x >= gridOrigin.x && maxPoint.y >= gridOrigin.y) {
		numCols = (int)round((maxPoint.x - gridOrigin.x) / nodeWidth);
		numRows = (int)round((maxPoint.y - gridOrigin.y) / nodeWidth);
	} else {
		numCols = numRows = 1;
	}

	nodes.resize(numRows);
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i].resize(numCols);
	}

	for (int i = 0; i < numRows; i++) {
		getNode(i, 0)->canGoLeft = 0;
		getNode(i, numCols - 1)->canGoRight = 0;
	}
	for (int i = 0; i < numCols; i++) {
		getNode(0, i)->canGoDown = 0;
		getNode(numRows - 1, i)->canGoUp = 0;
	}

	// go through each barrier and add it to the table
	for (int i = 0; i < barrierList.size(); i++) {
		Barrier* barrier = barrierList[i];
		bool isConditional = barrier->conditionRule && rank == 1;
		if (isConditional) {
			barrier->conditionalBarrierChanges.reset(navigator);
			navigator->applyToTemporaryBarrier = &barrier->conditionalBarrierChanges;
		}
		Vec3 min, max;
		barrier->getBoundingBox(min, max);
		if (isLocWithinVerticalBounds(min.z) || isLocWithinVerticalBounds(max.z) || isConditional) {
			barrier->addBarriersToTable(this);
		}
		if (isConditional)
			navigator->applyToTemporaryBarrier = nullptr;
	}

	// add custom barriers
	for (int i = 1; i <= customBarriers.size(); i++) {
		if (customBarriers[i].size() == 1) {
			// Treat objects as a solid barrier
			addObjectBarrierToTable(customBarriers[i][1]);
		}
		else if (customBarriers[i].size() == 3) {
			// blockGridModelPos
			blockGridModelPos(
				Vec3(customBarriers[i][1], customBarriers[i][2], customBarriers[i][3]));
		}
		else if (customBarriers[i].size() == 7) {
			// divideGridModelLine
			divideGridModelLine(
				Vec3(customBarriers[i][1], customBarriers[i][2], customBarriers[i][3]),
				Vec3(customBarriers[i][4], customBarriers[i][5], customBarriers[i][6]),
				customBarriers[i][7].operator int());
		}
	}

	// now add passages to the table
	for (int i = 0; i < barrierList.size(); i++) {
		Barrier* barrier = barrierList[i];
		Vec3 min, max;
		barrier->getBoundingBox(min, max);
		if (isLocWithinVerticalBounds(min.z) || isLocWithinVerticalBounds(max.z)) {
			barrier->addPassagesToTable(this);
		}
	}

	for (BridgeRoutingData* data : bridgeData) {
		data->addEntriesToNodeTable(this);
	}
	isDirtyByUser = false;
}

void Grid::resolveGridOrigin()
{
	int xOffset = (int)(floor(minPoint.x / nodeWidth));
	int yOffset = (int)(floor(minPoint.y / nodeWidth));

	gridOrigin.x = (xOffset + 0.5) * nodeWidth;
	gridOrigin.y = (yOffset + 0.5) * nodeWidth;
	gridOrigin.z = minPoint.z;
}


AStarNode * Grid::getNode(int rowNum, int colNum)
{
	if (rowNum < nodes.size()) {
		auto& row = nodes[rowNum];
		if (colNum < row.size())
			return &row[colNum];
	}
	static AStarNode node;
	node.value = 0;
	return &node;
}

void Grid::addSolidBarrierToTable(const Vec3 & min, const Vec3 & max, Barrier* barrier)
{
	// minCell and maxCell are based on the min and max bounds, offset half a node with 
	// into the boundary. This makes it so it doesn't affect stuff outside the barrier
	Cell minCell = getCell(min + Vec3(0.5 * nodeWidth, 0.5 * nodeWidth, 0.0));
	Cell maxCell = getCell(max + Vec3(-0.5 * nodeWidth, -0.5 * nodeWidth, 0.0));
	int gridRank = rank;

	for (int row = minCell.row; row <= maxCell.row; row++) {
		blockNodeDirection(Cell(gridRank, row, minCell.col - 1), Right, barrier);
		blockNodeDirection(Cell(gridRank, row, maxCell.col + 1), Left, barrier);
	}

	for (int col = minCell.col; col <= maxCell.col; col++) {
		blockNodeDirection(Cell(gridRank, maxCell.row + 1, col), Down, barrier);
		blockNodeDirection(Cell(gridRank, minCell.row - 1, col), Up, barrier);
	}

	for (int row = minCell.row; row <= maxCell.row; row++) {
		for (int col = minCell.col; col <= maxCell.col; col++) {
			AStarNode* theNode = getNode(row, col);
			Cell cell(gridRank, row, col);
			blockNodeDirection(cell, Up, barrier);
			blockNodeDirection(cell, Down, barrier);
			blockNodeDirection(cell, Left, barrier);
			blockNodeDirection(cell, Right, barrier);
		}
	}

}

void Grid::addObjectBarrierToTable(treenode obj)
{
	Vec3 objMin(FLT_MAX, FLT_MAX, FLT_MAX), objMax(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	int rotation = ((int)round(zrot(obj) / 90) * 90);
	// if the object is rotated at 0, 90, 180 or 270, then do simple stuff
	if (fabs(zrot(obj) - rotation) < 5 && fabs(xrot(obj)) < 5 && fabs(yrot(obj)) < 5 && up(obj) == model()) {

		double halfXSize = 0.5 * xsize(obj);
		double halfYSize = 0.5 * ysize(obj);

		Vec3 modelCenter;
		vectorproject(obj, halfXSize, -halfYSize, 0, model(), modelCenter);

		if (isLocWithinVerticalBounds(modelCenter.z)) {
			double objSX = maxof(xsize(obj), nodeWidth);
			double objSY = maxof(ysize(obj), nodeWidth);


			if (rotation != 0 && rotation % 180 != 0 && rotation % 90 == 0) {
				objMin.x = modelCenter.x - halfYSize;
				objMax.x = objMin.x + objSY;
				objMax.y = modelCenter.y + halfXSize;
				objMin.y = objMax.y - objSX;
			}
			else {
				objMin.x = modelCenter.x - halfXSize;
				objMax.x = objMin.x + objSX;
				objMax.y = modelCenter.y + halfYSize;
				objMin.y = objMax.y - objSY;
			}
			// Shrink the bounding box for objects
			double halfNodeWidth = 0.5 * nodeWidth;
			objMin.x += halfNodeWidth;
			objMax.x -= halfNodeWidth;
			objMin.y += halfNodeWidth;
			objMax.y -= halfNodeWidth;

			int colleft = (int)round((objMin.x - gridOrigin.x) / nodeWidth);
			int rowbottom = (int)round((objMin.y - gridOrigin.y) / nodeWidth);
			int colright = (int)round((objMax.x - gridOrigin.x) / nodeWidth);
			int rowtop = (int)round((objMax.y - gridOrigin.y) / nodeWidth);
			for (int row = rowbottom; row <= rowtop; row++) {
				AStarNode * left = getNode(row, colleft - 1);
				left->canGoRight = 0;
				AStarNode * right = getNode(row, colright + 1);
				right->canGoLeft = 0;
			}

			for (int col = colleft; col <= colright; col++) {
				AStarNode * top = getNode(rowtop + 1, col);
				top->canGoDown = 0;
				AStarNode * bottom = getNode(rowbottom - 1, col);
				bottom->canGoUp = 0;
			}

			for (int row = rowbottom; row <= rowtop; row++) {
				for (int col = colleft; col <= colright; col++) {
					AStarNode* theNode = getNode(row, col);
					theNode->canGoUp = 0;
					theNode->canGoDown = 0;
					theNode->canGoLeft = 0;
					theNode->canGoRight = 0;
				}
			}
		}
	} else {
		// in this case, the object is rotated weird, so I need to manually go through and apply each 

		AStarNavigator::getBoundingBox(obj, objMin, objMax);
		double halfNodeWidth = 0.5 * nodeWidth;
		objMin += Vec3(halfNodeWidth, halfNodeWidth, 0.0);
		objMax -= Vec3(halfNodeWidth, halfNodeWidth, 0.0);

		if (isLocWithinVerticalBounds(objMin.z)) {
			int minCol = max(0, (int)((objMin.x - gridOrigin.x) / nodeWidth));
			int maxCol = min(numCols - 1, (int)((objMax.x - gridOrigin.x) / nodeWidth) + 1);
			int minRow = max(0, (int)((objMin.y - gridOrigin.y) / nodeWidth));
			int maxRow = min(numRows - 1, (int)((objMax.y - gridOrigin.y) / nodeWidth) + 1);

			Vec2 minThreshold(0, -ysize(obj));
			Vec2 maxThreshold(xsize(obj), 0);
			double yPadding = nodeWidth - ysize(obj);
			if (yPadding > 0) {
				minThreshold.y -= 0.5 * yPadding;
				maxThreshold.y += 0.5 * yPadding;
			}
			double xPadding = nodeWidth - xsize(obj);
			if (xPadding > 0) {
				minThreshold.x -= 0.5 * xPadding;
				maxThreshold.x += 0.5 * xPadding;
			}

			for (int row = minRow; row <= maxRow; row++) {
				for (int col = minCol; col <= maxCol; col++) {
					Vec3 modelPos(gridOrigin.x + col * nodeWidth, gridOrigin.y + row * nodeWidth, 0);
					Vec3 objPos;
					vectorproject(model(), modelPos.x, modelPos.y, modelPos.z, obj, objPos);
					if (objPos.x > minThreshold.x && objPos.x < maxThreshold.x && objPos.y > minThreshold.y && objPos.y < maxThreshold.y) {
						AStarNode& theNode = *getNode(row, col);
						theNode.canGoUp = false;
						theNode.canGoDown = false;
						theNode.canGoLeft = false;
						theNode.canGoRight = false;

						if (col > 0)
							getNode(row, col - 1)->canGoRight = false;
						if (col < numCols - 1)
							getNode(row, col + 1)->canGoLeft = false;
						if (row > 0)
							getNode(row - 1, col)->canGoUp = false;
						if (row < numRows - 1)
							getNode(row + 1, col)->canGoDown = false;
					}
				}
			}
		}
	}
}

void Grid::blockGridModelPos(const Cell& cell)
{
	if (cell.col >= 0 && cell.col < numCols && cell.row >= 0 && cell.row < numRows) {
		AStarNode& node = *getNode(cell);
		node.canGoDown = false;
		node.canGoUp = false;
		node.canGoRight = false;
		node.canGoLeft = false;

		if (cell.col > 0)
			getNode(cell.row, cell.col - 1)->canGoRight = 0;
		if (cell.col < numCols - 1)
			getNode(cell.row, cell.col + 1)->canGoLeft = 0;
		if (cell.row > 0)
			getNode(cell.row - 1, cell.col)->canGoUp = 0;
		if (cell.row < numRows - 1)
			getNode(cell.row + 1, cell.col)->canGoDown = 0;
	}
}

void Grid::blockNodeDirection(const Cell& cell, Direction direction, Barrier* barrier) {
	AStarNode* node = getNode(cell);
	bool isConditionalBarrier = barrier && barrier->conditionRule;
	if (navigator->applyToTemporaryBarrier == nullptr || !isConditionalBarrier) {
		node->setCanGo(direction, false);
	} else {
		AStarNode& entryNode = (*navigator->applyToTemporaryBarrier)[cell].newValue;
		entryNode.setCanGo(direction, false);
		navigator->assertExtraData(cell, ConditionalBarrierData)->addConditionalBarrier(barrier);
	}
}

void Grid::divideGridModelLine(const Vec3& modelPos1, const Vec3& modelPos2, bool oneWay, Barrier* barrier)
{
	double low, high, step, pos;
	int gridRank = rank;
	// calculate columns and rows from the model points
	double col = (modelPos1.x - gridOrigin.x) / nodeWidth;
	double row = (modelPos1.y - gridOrigin.y) / nodeWidth;
	double nextCol = (modelPos2.x - gridOrigin.x) / nodeWidth;
	double nextRow = (modelPos2.y - gridOrigin.y) / nodeWidth;

	// x-axis grid cross
	low = 1;
	high = 0;
	step = (nextRow - row) / (nextCol - col);
	if (nextCol > col) {
		low = ceil(col);
		high = floor(nextCol);
		pos = row + (low - col) * step + 1;
	}
	else if (nextCol < col) {
		low = ceil(nextCol);
		high = floor(col);
		pos = nextRow + (low - nextCol) * step + 1;
	}
	if (low <= high) {
		double currCol = low;
		for (int i = 0; i <= fabs(high - low); i++) {
			double currRow = nextRow < row ? pos - FLT_EPSILON : pos + FLT_EPSILON;

			// Block down and up
			if (currCol >= 0 && currCol < numCols) {
				if ((!oneWay || nextCol > col) && currRow >= 0 && currRow < numRows)
					blockNodeDirection(Cell(gridRank, (int)currRow, (int)currCol), Down, barrier);
				if ((!oneWay || nextCol < col) && currRow - 1 >= 0 && currRow - 1 < numRows)
					blockNodeDirection(Cell(gridRank, (int)currRow - 1, (int)currCol), Up, barrier);
			}

			currCol++;
			pos += step;
		}
	}

	// y-axis grid cross
	low = 1;
	high = 0;
	step = (nextCol - col) / (nextRow - row);
	if (nextRow > row) {
		low = ceil(row);
		high = floor(nextRow);
		pos = col + (low - row) * step + 1;
	}
	else if (nextRow < row) {
		low = ceil(nextRow);
		high = floor(row);
		pos = nextCol + (low - nextRow) * step + 1;
	}
	if (low <= high) {
		double currRow = low;
		for (int i = 0; i <= fabs(high - low); i++) {
			double currCol = nextCol > col ? pos - FLT_EPSILON : pos + FLT_EPSILON;

			// Block left and right
			if (currRow >= 0 && currRow < numRows) {
				if ((!oneWay || nextRow < row) && currCol >= 0 && currCol < numCols)
					blockNodeDirection(Cell(gridRank, (int)currRow, (int)currCol), Left, barrier);
				if ((!oneWay || nextRow > row) && currCol - 1 >= 0 && currCol - 1 < numCols)
					blockNodeDirection(Cell(gridRank, (int)currRow, (int)currCol - 1), Right, barrier);
			}

			currRow++;
			pos += step;
		}
	}
}


void Grid::visitGridModelLine(const Vec3& fromPos, const Vec3& toPos, std::function<void(const Cell& cell)> callback)
{
	int fromCol = (int)round((fromPos.x - gridOrigin.x) / nodeWidth);
	int fromRow = (int)round((fromPos.y - gridOrigin.y) / nodeWidth);

	// calculate the column and row numbers for that point
	int toCol = (int)round((toPos.x - gridOrigin.x) / nodeWidth);
	int toRow = (int)round((toPos.y - gridOrigin.y) / nodeWidth);

	// set dx and dy, the differences between the rows and columns
	double dx = toCol - fromCol;
	double dy = toRow - fromRow;

	// figure out the unit increment (either -1 or 1) for traversing from the
	// current point to the next point
	int colInc = (int)sign(dx);
	if (colInc == 0)
		colInc = 1;

	int rowInc = (int)sign(dy);
	if (rowInc == 0)
		rowInc = 1;

	// prevent divide by zero errors
	if (dx == 0) dx = 0.01;
	// get the slope of the line
	double goalSlope = dy / dx;

	int currCol = fromCol;
	int currRow = fromRow;
	// now step through the line, essentially walking along the edges of the grid tiles
	// under the line
	while (true) {
		Cell cell(rank, currRow, currCol);
		callback(cell);

		// the way that I essentially move along the line
		// is at each grid point, I do a test step horizontally, 
		// and a test step vertically, and then test the new slope of the line to the 
		// destination for each of those test steps. Whichever line's slope is closest
		// to the actual slope represents the step I want to take.
		int testCol = currCol + colInc;
		int testRow = currRow + rowInc;
		double dxTestCol = toCol - testCol;
		if (dxTestCol == 0) dxTestCol = 0.01;
		double dxTestRow = toCol - currCol;
		if (dxTestRow == 0) dxTestRow = 0.01;

		double colIncSlope = (toRow - currRow) / dxTestCol;
		double rowIncSlope = (toRow - testRow) / dxTestRow;

		int nextCurrCol, nextCurrRow;
		if (fabs(colIncSlope - goalSlope) <= fabs(rowIncSlope - goalSlope)) {
			// move over one column
			nextCurrCol = testCol;
			nextCurrRow = currRow;
		}
		else {
			nextCurrCol = currCol;
			nextCurrRow = testRow;
		}

		if (currRow == toRow && currCol == toCol)
			break;

		currCol = nextCurrCol;
		currRow = nextCurrRow;


	}
}


void Grid::visitCellsWidening(const Cell& centerCell, std::function<bool(const Cell& cell)> callback)
{
	if (!callback(centerCell))
		return;

	bool continueWidening = true;
	for (int i = 1; continueWidening; i++) {
		if (centerCell.col < i && centerCell.row < i && centerCell.col + i >= numCols && centerCell.row + i >= numRows)
			break;
		Cell right(centerCell.grid, centerCell.row, centerCell.col + i);
		Cell left(centerCell.grid, centerCell.row, centerCell.col - i);
		Cell top(centerCell.grid, centerCell.row + i, centerCell.col);
		Cell bottom(centerCell.grid, centerCell.row - i, centerCell.col);

		for (int j = 0; j <= i; j++) {
			if (right.row >= j) {
				Cell rightBottom(right.grid, right.row - j, right.col);
				if (!callback(rightBottom)) {
					continueWidening = false;
					break;
				}
				Cell leftBottom(left.grid, left.row - j, left.col);
				if (!callback(leftBottom)) {
					continueWidening = false;
					break;
				}
			}
			if (j != 0 && right.row + j < numRows) {
				Cell rightTop(right.grid, right.row + j, right.col);
				if (!callback(rightTop)) {
					continueWidening = false;
					break;
				}
				Cell leftTop(left.grid, left.row + j, left.col);
				if (!callback(leftTop)) {
					continueWidening = false;
					break;
				}
			}
			if (top.col >= j + 1) {
				Cell topLeft(top.grid, top.row, top.col - j);
				if (!callback(topLeft)) {
					continueWidening = false;
					break;
				}
				Cell bottomLeft(bottom.grid, bottom.row, bottom.col - j);
				if (!callback(bottomLeft)) {
					continueWidening = false;
					break;
				}
			}
			if (j != 0 && top.col + j < numCols) {
				Cell topRight(top.grid, top.row, top.col + j);
				if (!callback(topRight)) {
					continueWidening = false;
					break;
				}
				Cell bottomRight(bottom.grid, bottom.row, bottom.col + j);
				if (!callback(bottomRight)) {
					continueWidening = false;
					break;
				}
			}
		}
	}
}

void Grid::buildBoundsMesh()
{
	TreeNode* color = navigator->node_b_color;
	Vec4f boundsColor(
		(float)get(::rank(color, 1)),
		(float)get(::rank(color, 2)),
		(float)get(::rank(color, 3)),
		0.75f
	);
	buildBoundsMesh(boundsMesh, false, boundsColor);
}

void Grid::buildBoundsMesh(Mesh& mesh, bool asOutline, Vec4f& color)
{
	mesh.init(0, MESH_POSITION, MESH_FORCE_CLEANUP);

	if (maxPoint.x - minPoint.x <= 0 || maxPoint.y - minPoint.y <= 0)
		return;

	if (!asOutline) {
		Vec3f up(0.0f, 0.0f, 1.0f);
		mesh.setMeshAttrib(MESH_NORMAL, up);
	}
	mesh.setMeshAttrib(MESH_DIFFUSE4, color);

	Vec3f bottomLeft, topRight, topLeft, bottomRight, oBottomLeft, oTopRight, oTopLeft, oBottomRight;
	getBoundsVertices(bottomLeft, topRight, topLeft, bottomRight, oBottomLeft, oTopRight, oTopLeft, oBottomRight);

	if (!asOutline) {
		// left border (GL_QUADS)
		addQuad(mesh, bottomLeft, topLeft, oTopLeft, oBottomLeft);

		// top border
		addQuad(mesh, topLeft, topRight, oTopRight, oTopLeft);

		// right border
		addQuad(mesh, topRight, bottomRight, oBottomRight, oTopRight);

		// bottom border
		addQuad(mesh, bottomRight, bottomLeft, oBottomLeft, oBottomRight);
	} else {
		addVertex(mesh, bottomLeft);
		addVertex(mesh, topLeft);
		addVertex(mesh, topLeft);
		addVertex(mesh, topRight);
		addVertex(mesh, topRight);
		addVertex(mesh, bottomRight);
		addVertex(mesh, bottomRight);
		addVertex(mesh, bottomLeft);

		addVertex(mesh, oBottomLeft);
		addVertex(mesh, oTopLeft);
		addVertex(mesh, oTopLeft);
		addVertex(mesh, oTopRight);
		addVertex(mesh, oTopRight);
		addVertex(mesh, oBottomRight);
		addVertex(mesh, oBottomRight);
		addVertex(mesh, oBottomLeft);
	}
}

void Grid::buildGridMesh(float zOffset)
{
	gridMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_FORCE_CLEANUP);

	float z = minPoint.z + zOffset;
	double quarterNodeWidth = 0.25 * nodeWidth;
	float gold[4] = { 0.8f,0.8f,0.0f, 1.0f };
	float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			AStarNode* n = getNode(row, col);
			AStarSearchEntry s;
			s.cell.col = col;
			s.cell.row = row;
			AStarNodeExtraData* e = NULL;
			if (n->hasPreferredPathWeight)
				e = navigator->edgeTableExtraData[s.cell.value];
			double x = gridOrigin.x + col * nodeWidth;
			double y = gridOrigin.y + row * nodeWidth;

#define ADD_GRID_LINE(dir, x1, y1, z1, x2, y2, z2)\
	if (n->canGo##dir) {\
		int newVertex1 = gridMesh.addVertex();\
		int newVertex2 = gridMesh.addVertex();\
		\
		if (e && e->bonus##dir) {\
			float green[4] = {0.0f, (float)e->bonus##dir, 0.0f, 1.0f};\
			gridMesh.setVertexAttrib(newVertex1, MESH_DIFFUSE4, green);\
			gridMesh.setVertexAttrib(newVertex2, MESH_DIFFUSE4, green);\
		} else {\
			gridMesh.setVertexAttrib(newVertex1, MESH_DIFFUSE4, gold);\
			gridMesh.setVertexAttrib(newVertex2, MESH_DIFFUSE4, gold);\
		}\
		\
		float pos1[3] = {(float)(x1), (float)(y1), (float)(z1)};\
		float pos2[3] = {(float)(x2), (float)(y2), (float)(z2)};\
		gridMesh.setVertexAttrib(newVertex1, MESH_POSITION, pos1);\
		gridMesh.setVertexAttrib(newVertex2, MESH_POSITION, pos2);\
	}
			if (n->canGoUp && n->canGoDown && n->canGoLeft && n->canGoRight && !n->hasPreferredPathWeight) {
				ADD_GRID_LINE(Up, x, y - quarterNodeWidth, z, x, y + quarterNodeWidth, z);
				ADD_GRID_LINE(Right, x - quarterNodeWidth, y, z, x + quarterNodeWidth, y, z);
				continue;
			}

			if (n->canGoUp && n->canGoDown && !n->hasPreferredPathWeight) {
				ADD_GRID_LINE(Up, x, y - quarterNodeWidth, z, x, y + quarterNodeWidth, z);
				ADD_GRID_LINE(Right, x, y, z, x + 0.25 * nodeWidth, y, z);
				ADD_GRID_LINE(Left, x, y, z, x - 0.25 * nodeWidth, y, z);
				continue;
			}

			if (n->canGoLeft && n->canGoRight && !n->hasPreferredPathWeight) {
				ADD_GRID_LINE(Right, x - quarterNodeWidth, y, z, x + quarterNodeWidth, y, z);
				ADD_GRID_LINE(Up, x, y, z, x, y + 0.25 * nodeWidth, z);
				ADD_GRID_LINE(Down, x, y, z, x, y - 0.25 * nodeWidth, z);
				continue;
			}

			ADD_GRID_LINE(Up, x, y, z, x, y + 0.25 * nodeWidth, z);
			ADD_GRID_LINE(Down, x, y, z, x, y - 0.25 * nodeWidth, z);
			ADD_GRID_LINE(Right, x, y, z, x + 0.25 * nodeWidth, y, z);
			ADD_GRID_LINE(Left, x, y, z, x - 0.25 * nodeWidth, y, z);

			if (n->isInTotalSet) {
				mpt("Grid error at x "); mpd(col); mpt(" y "); mpd(row); mpr();
				int newVertex1 = gridMesh.addVertex();
				int newVertex2 = gridMesh.addVertex();

				gridMesh.setVertexAttrib(newVertex1, MESH_DIFFUSE4, red);
				gridMesh.setVertexAttrib(newVertex2, MESH_DIFFUSE4, red);

				float pos1[3] = { (float)x, (float)y, z };
				float pos2[3] = { (float)(x + 0.25 * nodeWidth), (float)(y + 0.25 * nodeWidth), z };
				gridMesh.setVertexAttrib(newVertex1, MESH_POSITION, pos1);
				gridMesh.setVertexAttrib(newVertex2, MESH_POSITION, pos2);
			}
		}
	}

}

void Grid::drawHeatMap(TreeNode * view)
{
	int heatMapMode = (int)navigator->heatMapMode;
	if (heatMapMode == 0 || statisticaltime() <= 0)
		return;
	if (navigator->maxHeatValue <= 0)
		return;

	int pickMode = getpickingmode(view);
	if (pickMode)
		return;

	float z = minPoint.z;
	auto& heatMapColorProgression = navigator->heatMapColorProgression;
	int width = (numCols + 2);
	int height = (numRows + 2);
	int numPixels = width * height;
	int bufferSize = 4 * numPixels;

	if (!heatMapBuffer) {
		heatMapBuffer = std::unique_ptr<unsigned int[]>(new unsigned int[numPixels]);
		Vec4f baseColor = heatMapColorProgression[0];
		if (navigator->transparentBaseColor)
			baseColor.a = 0;
		int baseColorInt = (((int)(baseColor.a * 255)) << 24)
			| (((int)(baseColor.b * 255)) << 16)
			| (((int)(baseColor.g * 255)) << 8)
			| (((int)(baseColor.r * 255)));

		unsigned int* buffer = heatMapBuffer.get();
		memset(buffer, 0, width * 4);
		memset(buffer + (height - 1) * width * 4, 0, width * 4);
		for (int i = 1; i <= numRows; i++) {
			buffer[i * width] = 0;
			buffer[(i + 1) * width - 1] = 0;
			for (int j = 1; j <= numCols; j++) {
				buffer[i * width + j] = baseColorInt;
			}
		}
	}

	unsigned int* buffer = heatMapBuffer.get();
	int myRank = rank;
	for (auto& node : navigator->edgeTableExtraData) {
		AStarNodeExtraData* data = node.second;
		if (data->totalTraversals <= 0)
			continue;
		if (data->cell.grid != myRank)
			continue;
		double weight;
		switch (heatMapMode) {
		case AStarNavigator::HEAT_MAP_TRAVERSALS_PER_TIME: default:
			weight = (data->totalTraversals / statisticaltime());
			break;
		case AStarNavigator::HEAT_MAP_PERCENT_OF_TOTAL_TRAVERSALS:
			weight = 100.0 * data->totalTraversals / navigator->heatMapTotalTraversals;
			break;
		case AStarNavigator::HEAT_MAP_BLOCKAGE_TIME_PER_TRAVERSAL:
			weight = (data->totalBlockedTime / max(1, data->totalTraversals));
			break;
		case AStarNavigator::HEAT_MAP_BLOCKAGE_TIME_PERCENT:
			weight = 100.0 * data->totalBlockedTime / statisticaltime();
			break;
		}
		weight /= navigator->maxHeatValue;
		weight = max(0, weight);
		weight = min(0.9999, weight);

		double progressionFactor = (double)(heatMapColorProgression.size() - 1) * weight;
		Vec4f lowColor = heatMapColorProgression[(int)floor(progressionFactor)];
		Vec4f highColor = heatMapColorProgression[(int)ceil(progressionFactor)];
		Vec4f lerpColor = lowColor + ((highColor - lowColor) * frac(progressionFactor));

		buffer[(data->cell.row + 1) * width + data->cell.col + 1] =
			(((int)(lerpColor.a * 255)) << 24)
			| (((int)(lerpColor.b * 255)) << 16)
			| (((int)(lerpColor.g * 255)) << 8)
			| (((int)(lerpColor.r * 255)));
	}


	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glGenerateTextureMipMap(GL_TEXTURE_2D);

	Mesh trafficMesh;
	trafficMesh.init(6, MESH_POSITION | MESH_TEX_COORD2, MESH_DYNAMIC_DRAW);
	Vec3f verts[] = {
		Vec3f(gridOrigin.x - 1.5 * nodeWidth, gridOrigin.y - 1.5 * nodeWidth, z),
		Vec3f(gridOrigin.x - 1.5 * nodeWidth, gridOrigin.y + (numRows + 0.5) * nodeWidth, z),
		Vec3f(gridOrigin.x + (numCols + 0.5) * nodeWidth, gridOrigin.y - 1.5 * nodeWidth, z),
		Vec3f(gridOrigin.x - 1.5 * nodeWidth, gridOrigin.y + (numRows + 0.5) * nodeWidth, z),
		Vec3f(gridOrigin.x + (numCols + 0.5) * nodeWidth, gridOrigin.y + (numRows + 0.5) * nodeWidth, z),
		Vec3f(gridOrigin.x + (numCols + 0.5) * nodeWidth, gridOrigin.y - 1.5 * nodeWidth, z),
	};

	Vec2f texCoords[] = {
		Vec2f(0.0, 0.0),
		Vec2f(0.0, 1.0),
		Vec2f(1.0, 0.0),
		Vec2f(0.0, 1.0),
		Vec2f(1.0, 1.0),
		Vec2f(1.0, 0.0)
	};

	fglColor(1.0, 1.0, 1.0, 1.0);
	fglEnable(GL_TEXTURE_2D);
	fglDisable(GL_LIGHTING);

	trafficMesh.defineVertexAttribs(MESH_POSITION, verts[0]);
	trafficMesh.defineVertexAttribs(MESH_TEX_COORD2, texCoords[0]);
	trafficMesh.draw(GL_TRIANGLES);

	fglEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureID);
}

void Grid::drawDestinationThreshold(treenode destination, const Vec3 & loc, const Vec3 & size)
{
	float z = minPoint.z;
	DestinationThreshold dt = DestinationThreshold(destination, nodeWidth);
	// Set the desination outside a barrier if necessary
	if (navigator->ignoreDestBarrier) {
		Cell destCell = getCell(Vec3(loc));
		navigator->checkGetOutOfBarrier(destCell, nullptr, 0, 0, &dt);
	}

	Mesh mesh, mesh2;
	mesh.init(0, MESH_POSITION, MESH_DYNAMIC_DRAW);
	mesh2.init(0, MESH_POSITION, MESH_DYNAMIC_DRAW);
	double diamondRadius = 0.1 * nodeWidth;
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			AStarNode* n = getNode(row, col);
			Cell cell;
			cell.col = col;
			cell.row = row;

			int withinArrivalThreshold = 0;
			if (dt.xAxisThreshold > 0 || dt.yAxisThreshold > 0) {
				double threshold = sqrt(dt.xAxisThreshold * dt.xAxisThreshold + dt.yAxisThreshold * dt.yAxisThreshold);

				Vec3 pos = getLocation(cell);
				Vec3 diff = pos - Vec3(loc[0], loc[1], 0);
				if (diff.magnitude < threshold)
					withinArrivalThreshold = 1;
			}

			bool withinTravelThreshold = dt.isWithinThreshold(cell, this, loc);
			if (withinTravelThreshold || withinArrivalThreshold) {
				Mesh* theMesh = withinTravelThreshold ? &mesh : &mesh2;
				Vec3 centerPos = getLocation(cell);
				int vert = theMesh->addVertex();
				theMesh->setVertexAttrib(vert, MESH_POSITION, Vec3f(centerPos.x + diamondRadius, centerPos.y, z));
				vert = theMesh->addVertex();
				theMesh->setVertexAttrib(vert, MESH_POSITION, Vec3f(centerPos.x, centerPos.y + diamondRadius, z));
				vert = theMesh->addVertex();
				theMesh->setVertexAttrib(vert, MESH_POSITION, Vec3f(centerPos.x - diamondRadius, centerPos.y, z));
				vert = theMesh->addVertex();
				theMesh->setVertexAttrib(vert, MESH_POSITION, Vec3f(centerPos.x - diamondRadius, centerPos.y, z));
				vert = theMesh->addVertex();
				theMesh->setVertexAttrib(vert, MESH_POSITION, Vec3f(centerPos.x, centerPos.y - diamondRadius, z));
				vert = theMesh->addVertex();
				theMesh->setVertexAttrib(vert, MESH_POSITION, Vec3f(centerPos.x + diamondRadius, centerPos.y, z));
			}
		}
	}

	fglDisable(GL_LIGHTING);
	fglDisable(GL_TEXTURE_2D);
	fglColor(0.8f, 0.2f, 0.2f, 1.0f);
	mesh.draw(GL_TRIANGLES);
	fglColor(0.2f, 0.2f, 0.8f, 1.0f);
	mesh2.draw(GL_TRIANGLES);
	fglEnable(GL_LIGHTING);
	fglEnable(GL_TEXTURE_2D);
}

void Grid::checkGetOutOfBarrier(Cell & cell, TaskExecuter * traveler, int rowDest, int colDest, DestinationThreshold * threshold)
{
	AStarNode* node = getNode(cell);
	int dy = rowDest - cell.row;
	int dx = colDest - cell.col;
	Cell originalCell(cell);

	static const int up = 0;
	static const int left = 1;
	static const int down = 2;
	static const int right = 3;

	int startDir = up;
	if (dx > 0 && dx * dx > dy * dy)
		startDir = left;
	else if (dx < 0 && dx * dx > dy * dy)
		startDir = right;
	else if (dy < 0 && dy * dy > dx * dx)
		startDir = down;

	int currRow = cell.row;
	int currCol = cell.col;
	int currDir = (startDir + 3) % 4; // start one direction back 
	int distance = 0;
	int counter = 4; // counter is used to find the distance

	while (!(node->canGoUp || node->canGoDown || node->canGoRight || node->canGoLeft)) {
		currDir = (currDir + 1) % 4;
		distance = (counter++) / 4;

		if (distance == max(numRows, numCols))
			break;

		switch (currDir) {
		case 0: currRow = cell.row + distance; currCol = cell.col; break;
		case 1: currCol = cell.col + distance; currRow = cell.row; break;
		case 2: currRow = cell.row - distance; currCol = cell.col; break;
		case 3: currCol = cell.col - distance; currRow = cell.row; break;
		}

		if (currRow >= 0 && currRow < numRows && currCol >= 0 && currCol < numCols)
			node = getNode(currRow, currCol);
	}

	cell.row = currRow;
	cell.col = currCol;
	if (threshold && cell != originalCell) {
		double newRadius = nodeWidth * (0.9 + sqrt(sqr(cell.row - originalCell.row) + sqr(cell.col - originalCell.col)));
		if (newRadius > threshold->anyThresholdRadius)
			threshold->anyThresholdRadius = newRadius;
	}
}

void Grid::buildBridgeDijkstraTables()
{
	for (BridgeRoutingData* data : bridgeData)
		data->buildDijkstraTable(this);
}

void Grid::onDrag(treenode view, Vec3& offset)
{
	int pickType = getpickingdrawfocus(view, PICK_TYPE, 0);
	Vec3 originalMin(minPoint), originalMax(maxPoint);
	switch (pickType) {
		case 0: {
			minPoint += offset;
			maxPoint += offset;
			break;
		}
		case PICK_SIZERX: maxPoint.x = max(minPoint.x, maxPoint.x + offset.x); break;
		case PICK_SIZERXNEG: minPoint.x = min(maxPoint.x, minPoint.x + offset.x); break;
		case PICK_SIZERY: maxPoint.y = max(minPoint.y, maxPoint.y + offset.y); break;
		case PICK_SIZERYNEG: minPoint.y = min(maxPoint.y, minPoint.y + offset.y); break;
	}
	bool didShrink = shrinkToFitGrowthBounds();
	if (didShrink && pickType == 0) {
		bool isZeroSize = (maxPoint - minPoint).magnitude < 0.1 * nodeWidth;
		minPoint = originalMin;
		maxPoint = originalMax;
		if (isZeroSize) {
			minPoint += offset;
			maxPoint += offset;
		}
	}

	resolveGridOrigin();
}

double Grid::onDrag(treenode view)
{
	double dx = draginfo(DRAG_INFO_DX);
	double dy = draginfo(DRAG_INFO_DY);
	double dz = draginfo(DRAG_INFO_DZ);

	// Move all attached barriers
	onDrag(view, Vec3(dx, dy, dz));

	navigator->setDirty();
	isUserCustomized = true;
	isDirtyByUser = true;
	return 1;
}

double Grid::onClick(treenode view, int clickCode)
{
	return 0.0;
}

double Grid::onCreate(bool isCopy)
{
	Vec3 size = maxPoint - minPoint;
	maxPoint.x += size.x;
	minPoint.x += size.x;
	if (holder->up->name != "grids") {
		PostMessage(systemwindow(0), FLEXSIM_MESSAGE_USER_CALLBACK, (WPARAM)&Grid::onPostCreate, (LPARAM)this);
	}
	return 0;
}


void Grid::onPostCreate(void * data)
{
	Grid* grid = (Grid*)data;

	if (grid->holder->up->name != "grids") {
		auto found = model()->find("AStarNavigator>variables/grids");
		if (found) {
			beginignoreundo();
			transfernode(grid->holder, found);
			endignoreundo();
		}
	}
	grid->bindNavigator();
	if (grid->navigator)
		grid->navigator->isGridDirty = grid->navigator->isBoundsDirty = true;
}

void Grid::drawSizerHandles(treenode view, int pickingMode)
{
	Vec3f bottomLeft, topRight, topLeft, bottomRight, oBottomLeft, oTopRight, oTopLeft, oBottomRight;
	getBoundsVertices(bottomLeft, topRight, topLeft, bottomRight, oBottomLeft, oTopRight, oTopLeft, oBottomRight);

	float arrowSize = 0.5 * min(oTopRight.x - oTopLeft.x, oTopRight.y - oBottomRight.y);
	arrowSize = min(arrowSize, 2 * nodeWidth);
	Mesh tempMesh;
	tempMesh.init(0, MESH_POSITION);
	Vec3f arrowRight(arrowSize, 0.0f, 0.0f);
	Vec3f arrowLeft(-arrowSize, 0.0f, 0.0f);
	Vec3f arrowTop(0.0f, arrowSize, 0.0f);
	addTriangle(tempMesh, arrowLeft, arrowRight, arrowTop);

	auto drawSizer = [pickingMode, this, &tempMesh, view](Vec3f& arrowBase, int pickType, float rotation)
	{
		fglPushMatrix();
		fglTranslate(arrowBase.x, arrowBase.y, arrowBase.z);
		fglRotate(rotation, 0.0f, 0.0f, 1.0f);
		if (pickingMode)
			setpickingdrawfocus(view, holder, pickType);
		tempMesh.draw(GL_TRIANGLES);
		fglPopMatrix();
	};

	fglColor(1.0f, 0.0f, 0.0f);
	drawSizer((oTopRight + oTopLeft) * 0.5f, PICK_SIZERY, 0.0f);
	drawSizer((oBottomRight + oBottomLeft) * 0.5f, PICK_SIZERYNEG, 180.0f);
	drawSizer((oTopRight + oBottomRight) * 0.5f, PICK_SIZERX, -90.0f);
	drawSizer((oTopLeft + oBottomLeft) * 0.5f, PICK_SIZERXNEG, 90.0f);
}

void Grid::drawBounds(treenode view, treenode selObj, treenode hoverObj, int pickingMode)
{
	if (pickingMode == PICK_PRESSED)
	if (!pickingMode && (selObj == holder || hoverObj == holder)) {
		Mesh tempMesh;
		Vec4f color(1.0f, 1.0f, 0.0f, selObj == holder ? 1.0f : 0.2f);
		buildBoundsMesh(tempMesh, true, color);
		glLineWidth(5.0f);
		tempMesh.draw(GL_LINES);
		glLineWidth(1.0f);
	}


	if (selObj == holder) {
		drawSizerHandles(view, pickingMode);
	}
	if (pickingMode)
		setpickingdrawfocus(view, holder, 0);
	boundsMesh.draw(GL_TRIANGLES);
}

void Grid::getBoundsVertices(Vec3f & bottomLeft, Vec3f & topRight, Vec3f & topLeft, Vec3f & bottomRight, Vec3f & oBottomLeft, Vec3f & oTopRight, Vec3f & oTopLeft, Vec3f & oBottomRight)
{
	int numCols, numRows;
	if (isDirtyByUser || this->numRows == 0 || this->numCols == 0) {
		resolveGridOrigin();
		numCols = (int)round((maxPoint.x - gridOrigin.x) / nodeWidth);
		numRows = (int)round((maxPoint.y - gridOrigin.y) / nodeWidth);
	} else {
		numCols = this->numCols;
		numRows = this->numRows;
	}
	float width = (float)numCols * nodeWidth;
	float height = (float)numRows * nodeWidth;

	float borderWidth = nodeWidth;
	float z = minPoint.z;
	bottomLeft = Vec3f((float)(gridOrigin.x - 0.5 * nodeWidth), (float)(gridOrigin.y - 0.5 * nodeWidth), (float)minPoint.z);
	topRight = Vec3f(bottomLeft.x + width, bottomLeft.y + height, z);
	topLeft = Vec3f(bottomLeft.x, topRight.y, z);
	bottomRight = Vec3f(topRight.x, bottomLeft.y, z);

	oBottomLeft = Vec3f(bottomLeft.x - borderWidth, bottomLeft.y - borderWidth, z);
	oTopRight = Vec3f(topRight.x + borderWidth, topRight.y + borderWidth, z);
	oTopLeft = Vec3f(topLeft.x - borderWidth, topLeft.y + borderWidth, z);
	oBottomRight = Vec3f(bottomRight.x + borderWidth, bottomRight.y - borderWidth, z);
}

void Grid::addVertex(Mesh & mesh, Vec3f& point)
{
	int newVertex = mesh.addVertex();
	mesh.setVertexAttrib(newVertex, MESH_POSITION, point);
}

void Grid::addTriangle(Mesh & mesh, Vec3f & p1, Vec3f & p2, Vec3f & p3)
{
	addVertex(mesh, p1);
	addVertex(mesh, p2);
	addVertex(mesh, p3);
}

void Grid::addQuad(Mesh & mesh, Vec3f & p1, Vec3f & p2, Vec3f & p3, Vec3f & p4)
{
	addTriangle(mesh, p1, p2, p3);
	addTriangle(mesh, p1, p3, p4);
}


void Grid::dragPressedPick(treenode view, Vec3& pos, Vec3& diff)
{
	Vec3 midPoint = (minPoint + maxPoint) * 0.5;
	double* xFocus, *yFocus;
	if (pos.x > midPoint.x)
		xFocus = &maxPoint.x;
	else xFocus = &minPoint.x;

	if (pos.y > midPoint.y)
		yFocus = &maxPoint.y;
	else yFocus = &minPoint.y;

	*xFocus = pos.x;
	*yFocus = pos.y;

	navigator->setDirty();
	isUserCustomized = true;
	isDirtyByUser = true;
}

void Grid::makeDirty()
{
	resolveGridOrigin();
	navigator->setDirty();
	isUserCustomized = true;
	isDirtyByUser = true;
}

double Grid::onDestroy(treenode view)
{
	if (holder->up->subnodes.length == 1) {
		msg("Grid Deletion Not Allowed", "You cannot delete all A* grids.", 1);
		return 1.0;
	}
	return 0.0;
}

void Grid::bindNavigator()
{
	if (holder->up && holder->up->name == "grids")
		navigator = ownerobject(holder->up)->objectAs(AStarNavigator);
	else {
		navigator = nullptr;
	}
}

double Grid::onUndo(bool isUndo, treenode undoRecord) 
{ 
	bindNavigator(); 
	if (navigator) 
		navigator->setDirty(); 
	return 0;
}

}
