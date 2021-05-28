#include "Barrier.h"
#include "AStarNavigator.h"
#include "Grid.h"
#include "Traveler.h"
#include "macros.h"

namespace AStar {
Barrier::Barrier()
{
	return;
}

Barrier::~Barrier()
{
	return;
}

void Barrier::bindVariables(void)
{
	__super::bindVariables();

	bindVariableByName("navigator", navigatorCoupling, ODT_BIND_STATE_VARIABLE);

	bindVariable(points);
	pointList.init(points);

	bindVariable(conditionRule);
	bindVariable(patternTable);
	bindStateVariable(nodeSize.x);
	bindStateVariable(nodeSize.y);
}

void Barrier::bind(void)
{
	__super::bind();
	bindCallback(dragPressedPick, Barrier);
	bindCallback(addPoint, Barrier);
	bindCallback(removePoint, Barrier);
	bindCallback(swapPoints, Barrier);
	bindCallback(getPointCoord, Barrier);
	bindCallback(setPointCoords, Barrier);
	bindCallback(getType, Barrier);
	bindCallback(getEditMode, Barrier);
	bindCallback(setEditMode, Barrier);
	bindCallback(abortCreationMode, Barrier);
	bindCallback(setActiveIndex, Barrier);
	bindCallback(splitPatternRow, Barrier);
	bindCallback(splitPatternCol, Barrier);
	bindCallback(mergePatternRows, Barrier);
	bindCallback(mergePatternCols, Barrier);
	bindCallback(updateSpatialsToEncompassPoints, Barrier);
	bindCallback(updatePointsFromSpatials, Barrier);
	bindCallback(assertNavigator, Barrier);
	bindCallback(setSizeComponent, Barrier);
	bindCallback(finalizeSpatialChanges, Barrier);

	//int bindMode = getBindMode();
	//if (bindMode == SDT_BIND_ON_LOAD || bindMode == SDT_BIND_ON_CREATE) {
	//	if (condition->value == "") {
	//		condition->value = "treenode traveler = param(1);\r\nreturn /**/traveler.type == 1/**direct*/;\r\n";
	//	}
	//}
}

AStarNavigator * Barrier::__getNavigator()
{
	auto subnodes = navigatorCoupling->subnodes;
	if (subnodes.length > 0)
		return ownerobject(subnodes[1]->value)->objectAs(AStarNavigator);
	return nullptr;
}

void Barrier::assertNavigator()
{
	if (navigator != nullptr)
		return;

	treenode navNode = model()->find("AStarNavigator");
	if (!navNode) {
		navNode = createinstance(library()->find("?AStarNavigator"), model());
	}
	navNode->objectAs(AStarNavigator)->barrierList.add(this);
}

void Barrier::init(const Vec2& nodeSize, const Vec3& pos1, const Vec3& pos2)
{
	this->nodeSize = nodeSize;
	drawNodeSize = nodeSize;
	pointList.clear();
	addPoint(pos1);
	addPoint(pos2);

	if (isBasicBarrier()) {
		assertValidPatternTable();
	}
}


bool Barrier::getBoundingBox(Vec3& min, Vec3& max, treenode projectOnto) 
{
	if (pointList.size() < 2) 
		return false;
	
	min = Vec3(DBL_MAX, DBL_MAX, DBL_MAX);
	max = Vec3(-DBL_MAX, -DBL_MAX, -DBL_MAX);
	auto testPos = [&](Vec3 pos) {
		if (projectOnto)
			pos = pos.project(holder, projectOnto);
		for (int i = 0; i < 3; i++) {
			if (pos[i] < min[i])
				min[i] = pos[i];
			if (pos[i] > max[i])
				max[i] = pos[i];
		}
	};
	Vec3 topLeft = getPointCoords(0) - location;
	Vec3 bottomRight = getPointCoords(1) - location;
	testPos(topLeft);
	testPos(bottomRight);
	testPos(Vec3(topLeft.x, bottomRight.y, topLeft.z));
	testPos(Vec3(bottomRight.x, topLeft.y, topLeft.z));

	return true;
}

void Barrier::addBarriersToTable(Grid* grid)
	//AStarNode* edgeTable, 
	//					  std::unordered_map<unsigned int, AStarNodeExtraData>* extraData, 
	//					  double c0, double r0, unsigned int edgeTableXSize, unsigned int edgeTableYSize)
{
	Vec3 myMin, myMax;
	if (!getBoundingBox(myMin, myMax, model()))
		return;

	Table patterns(patternTable);
	bool isTrivialSolidBarrier = false;
	bool isInRotatedContainer = false;
	if (holder->up != model() && holder->up != navigator->holder) {
		treenode test = holder->up;
		while (test && test != model()) {
			if (zrot(test) != 0.0) {
				isInRotatedContainer = true;
				break;
			}
		}
	}
	if (patterns.numCols == 1 && patterns.numRows == 1) {
		PatternCell* cell = patterns.cell(1, 1)->objectAs(PatternCell);
		isTrivialSolidBarrier = !cell->canGoUp && !cell->canGoDown && !cell->canGoLeft && !cell->canGoRight;
	}

	if (!grid->isLocWithinBounds(myMin, false, false) && !grid->isLocWithinBounds(myMax, false, false)) {
		Vec3 topLeft(myMin.x, myMax.y, myMin.z);
		if (!grid->isLocWithinBounds(topLeft, false, false)) {
			Vec3 bottomRight(myMax.x, myMin.y, myMin.z);
			if (!grid->isLocWithinBounds(bottomRight, false, false))
				return;
		}
	}

	if (isInRotatedContainer) {
		grid->addObjectBarrierToTable(holder);
	}
	else if (isTrivialSolidBarrier) {
		grid->addSolidBarrierToTable(myMin, myMax, this);
	} 
	else {
		Cell minCell = grid->getCell(myMin + Vec3(0.5 * grid->nodeSize.x, 0.5 * grid->nodeSize.y, 0.0));
		Cell maxCell = grid->getCell(myMax + Vec3(-0.5 * grid->nodeSize.x, -0.5 * grid->nodeSize.y, 0.0));
		for (Cell cell = minCell; cell.row <= maxCell.row; cell.row++) {
			for (cell.col = minCell.col; cell.col <= maxCell.col; cell.col++) {
				PatternCell* patternCell = getPatternCell(grid->getLocation(cell));
				if (patternCell) {
					if (!patternCell->canGoUp)
						grid->blockNodeDirection(cell, Up, this);
					if (!patternCell->canGoDown)
						grid->blockNodeDirection(cell, Down, this);
					if (!patternCell->canGoRight)
						grid->blockNodeDirection(cell, Right, this);
					if (!patternCell->canGoLeft)
						grid->blockNodeDirection(cell, Left, this);
				}
			}
		}
	}
}

void Barrier::addMeshVertex(Mesh* mesh, float* pos, float* color)
{
	int newVertex = mesh->addVertex();
	mesh->setVertexAttrib(newVertex, MESH_POSITION, pos);
	mesh->setVertexAttrib(newVertex, MESH_DIFFUSE4, color);
}

void Barrier::addMeshVertex(Mesh* mesh, Vec3f& pos, Vec2f& tex, Vec4f& color)
{
	int newVertex = mesh->addVertex();
	mesh->setVertexAttrib(newVertex, MESH_POSITION, pos);
	mesh->setVertexAttrib(newVertex, MESH_TEX_COORD2, tex);
	mesh->setVertexAttrib(newVertex, MESH_DIFFUSE4, color);
}

void Barrier::addMeshTriangle(Mesh* mesh, float* p1, float* p2, float* p3, float* color)
{
	addMeshVertex(mesh, p1, color);
	addMeshVertex(mesh, p2, color);
	addMeshVertex(mesh, p3, color);
}

void Barrier::addMeshTriangle(Mesh* mesh, Vec3f& p1, Vec2f& tex1, Vec3f& p2, Vec2f& tex2, Vec3f& p3, Vec2f& tex3, Vec4f& color)
{
	addMeshVertex(mesh, p1, tex1, color);
	addMeshVertex(mesh, p2, tex2, color);
	addMeshVertex(mesh, p3, tex3, color);
}

void Barrier::addMeshTriangle(Mesh* mesh, Vec3f&& p1, Vec2f&& tex1, Vec3f&& p2, Vec2f&& tex2, Vec3f&& p3, Vec2f&& tex3, Vec4f& color)
{
	addMeshTriangle(mesh, p1, tex1, p2, tex2, p3, tex3, color);
}

void Barrier::addMeshLine(Mesh* mesh, Vec3f& p1, Vec3f& p2, Vec4f& color)
{
	addMeshVertex(mesh, p1, color);
	addMeshVertex(mesh, p2, color);
}

void Barrier::drawManipulationHandles(treenode view)
{
	Vec3 myMin, myMax;
	if (!getBoundingBox(myMin, myMax))
		return;

	Vec3 pos(b_spatialx, b_spatialy, b_spatialz);
	if (holder->up != model() && holder->up != navigator->holder)
		pos = pos.project(holder->up, model());
	Vec3 myModelMin(myMin + pos), myModelMax(myMax + pos);

	Grid* grid = navigator->getGrid((myMin + myMax) * 0.5, true);
	//grid->growToEncompassBoundingBox(myModelMin, myModelMax, false);
	if (grid)
		grid->resolveGridOrigin();
	auto nodeSize = grid ? grid->nodeSize : navigator->grids.front()->nodeSize;
	Vec3 size = myMax - myMin;
	float width = (float)(myMax.x - myMin.x);
	float height = (float)(myMax.y - myMin.y);
	float scale = std::max({ this->nodeSize.x, this->nodeSize.y, 0.15 * std::max(height, width) });
	float lengthMultiple = getmodelunit(LENGTH_MULTIPLE);
	float z = (float)myMin.z + 0.01 / lengthMultiple;
	Vec4f baseColor(0.4f, 0.4f, 0.4f, 1.0f);
	Mesh mesh;

	Vec3f bottomLeft((float)myMin.x, (float)myMin.y, myMin.z);
	Vec3f topRight((float)myMax.x, (float)myMax.y, myMin.z);
	Vec3f topLeft((float)myMin.x, (float)myMax.y, myMin.z);
	Vec3f bottomRight((float)myMax.x, (float)myMin.y, myMin.z);

	mesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
	addMeshTriangle(&mesh, bottomRight, topLeft, bottomLeft, baseColor);
	addMeshTriangle(&mesh, bottomRight, topRight, topLeft, baseColor);
	setpickingdrawfocus(view, holder, 0);
	mesh.draw(GL_TRIANGLES);

	int hoverType = (int)getpickingdrawfocus(view, PICK_TYPE, PICK_HOVERED);
	treenode hoverSecondary = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_HOVERED));

	mesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
	Vec3f left[3] = {
		Vec3f(myMin.x, myMin.y + height * 0.5f + 0.25f * scale, z),
		Vec3f(myMin.x, myMin.y + height * 0.5f - 0.25f * scale, z),
		Vec3f(myMin.x - 0.5f * scale, myMin.y + height * 0.5f, z)
	};
	Vec3f right[3] = {
		Vec3f(myMax.x, myMin.y + height * 0.5f + 0.25f * scale, z),
		Vec3f(myMax.x, myMin.y + height * 0.5f - 0.25f * scale, z),
		Vec3f(myMax.x + 0.5f * scale, myMin.y + height * 0.5f, z)
	};
	Vec3f top[3] = {
		Vec3f(myMin.x + width * 0.5f - 0.25f * scale, myMax.y, z),
		Vec3f(myMin.x + width * 0.5f + 0.25f * scale, myMax.y, z),
		Vec3f(myMin.x + width * 0.5f, myMax.y + 0.5f * scale, z)
	};
	Vec3f bottom[3] = {
		Vec3f(myMin.x + width * 0.5f - 0.25f * scale, myMin.y, z),
		Vec3f(myMin.x + width * 0.5f + 0.25f * scale, myMin.y, z),
		Vec3f(myMin.x + width * 0.5f, myMin.y - 0.5f * scale, z)
	};
	Vec4f red(1.0f, 0.0f, 0.0f, 1.0f);
	Vec4f lightRed(1.0f, 0.4f, 0.4f, 1.0f);
	Vec4f black(0.0f, 0.0f, 0.0f, 1.0f);
	Vec4f darkGray(0.3f, 0.3f, 0.3f, 1.0f);
	Vec4f white(1.0f, 1.0f, 1.0f, 1.0f);
	addMeshTriangle(&mesh, left[0], left[1], left[2], red);
	addMeshTriangle(&mesh, right[0], right[1], right[2], red);
	addMeshTriangle(&mesh, top[0], top[1], top[2], red);
	addMeshTriangle(&mesh, bottom[0], bottom[1], bottom[2], red);

	setpickingdrawfocus(view, holder, PICK_ARROW_LEFT, pointList[0]->holder);
	mesh.draw(GL_TRIANGLES, 0, 3);
	setpickingdrawfocus(view, holder, PICK_ARROW_RIGHT, pointList[1]->holder);
	mesh.draw(GL_TRIANGLES, 3, 3);
	setpickingdrawfocus(view, holder, PICK_ARROW_TOP, pointList[1]->holder);
	mesh.draw(GL_TRIANGLES, 6, 3);
	setpickingdrawfocus(view, holder, PICK_ARROW_BOTTOM, pointList[0]->holder);
	mesh.draw(GL_TRIANGLES, 9, 3);

	Vec3f colAddPos(myMax.x + 0.5 * nodeSize.x, myMax.y - 0.5 * nodeSize.y, z);
	Vec3f rowAddPos(myMin.x + 0.5 * nodeSize.x, myMin.y - 0.5 * nodeSize.y, z);
	Table patterns(patternTable);

	Vec4f green(0.0f, 0.6f, 0.0f, 1.0f);
	Vec4f lightGreen(0.3f, 0.8f, 0.3f, 1.0f);

	int pickingMode = getpickingmode(view);
	float gridZ = z + 0.02 / lengthMultiple;
	Vec3f cellTopLeftPos((float)myMin.x, (float)myMax.y, z);
	Mesh borderMesh;
	borderMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);

	auto drawCellSizer = [&](Vec3f&& center, float arrowDirection) {
		mesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
		Vec3f p1(0.1f * nodeSize.x, 0.2f * nodeSize.y, z);
		p1.rotateXY(arrowDirection);
		Vec3f p2(0.1f * nodeSize.x, -0.2f * nodeSize.y, z);
		p2.rotateXY(arrowDirection);
		Vec3f p3(0.3f * nodeSize.x, 0.0f, z);
		p3.rotateXY(arrowDirection);

		Vec3f p4(-0.1f * nodeSize.x, -0.2f * nodeSize.y, z);
		p4.rotateXY(arrowDirection);
		Vec3f p5(-0.1f * nodeSize.x, 0.2f * nodeSize.y, z);
		p5.rotateXY(arrowDirection);
		Vec3f p6(-0.3f * nodeSize.x, 0.0f, z);
		p6.rotateXY(arrowDirection);

		addMeshTriangle(&mesh, center + p1, center + p2, center + p3, red);
		addMeshTriangle(&mesh, center + p4, center + p5, center + p6, red);
		if (pickingMode) {
			addMeshTriangle(&mesh, center + p2, center + p1, center + p5, red);
			addMeshTriangle(&mesh, center + p2, center + p5, center + p4, red);
		}
		mesh.draw(GL_TRIANGLES);
	};

	auto drawTexButton = [&](Vec3f&& center, float rotation, int pickType, int textureIndex, PatternCell* cell, Vec4f& baseColor, Vec4f& hoverColor) {
		mesh.init(0, MESH_POSITION | MESH_DIFFUSE4 | MESH_TEX_COORD2, MESH_DYNAMIC_DRAW);
		Vec3f p1(0.2f * nodeSize.x, 0.2f * nodeSize.y, z);
		p1.rotateXY(rotation);
		Vec3f p2(-0.2f * nodeSize.x, 0.2f * nodeSize.y, z);
		p2.rotateXY(rotation);
		Vec3f p3(-0.2f * nodeSize.x, -0.2f * nodeSize.y, z);
		p3.rotateXY(rotation);
		Vec3f p4(0.2f * nodeSize.x, -0.2f * nodeSize.y, z);
		p4.rotateXY(rotation);

		bool isHovered = hoverType == pickType && hoverSecondary == cell->holder;
		Vec4f& color = isHovered ? hoverColor : baseColor;
		addMeshTriangle(&mesh,
			center + p1, Vec2f(1.0f, 1.0f),
			center + p2, Vec2f(0.0f, 1.0f),
			center + p3, Vec2f(0.0f, 0.0f),
			color);
		addMeshTriangle(&mesh,
			center + p1, Vec2f(1.0f, 1.0f),
			center + p3, Vec2f(0.0f, 0.0f),
			center + p4, Vec2f(1.0f, 0.0f),
			color);

		if (!pickingMode) {
			bindtexture(textureIndex);
			fglEnable(GL_TEXTURE_2D);
		}
		setpickingdrawfocus(view, holder, pickType, cell->holder);
		mesh.draw(GL_TRIANGLES);
		if (!pickingMode) {
			bindtexture(0);
			fglDisable(GL_TEXTURE_2D);
		}
	};

	int scissorTexture = (int)get(navigator->node_b_imageindexobject->find("split"));
	int stitchesTexture = (int)get(navigator->node_b_imageindexobject->find("merge"));

	if (pickingMode)
		glLineWidth(5.0); // make it so the pattern divider lines are easier to grab

	bool isInContainer = holder->up != model() && holder->up != navigator->holder;
	if (!isInContainer) {
		for (int row = 1; row <= patterns.numRows; row++) {
			double rowHeight = patterns.cell(row, 1)->objectAs(PatternCell)->height;
			cellTopLeftPos.x = myMin.x;

			for (int col = 1; col <= patterns.numCols; col++) {
				float colWidth = (float)patterns.cell(1, col)->objectAs(PatternCell)->width;

				Vec3f cellCenter = cellTopLeftPos + Vec3f(0.5f * colWidth, -0.5f * rowHeight, 0.0f);
				PatternCell* cell = patterns.cell(row, col)->objectAs(PatternCell);
				auto drawArrow = [&](float direction, bool condition, int pickType) {
					Vec3f p1(0.05 * nodeSize.x, -0.05 * nodeSize.y, z);
					p1.rotateXY(direction);
					Vec3f p2(0.2 * nodeSize.x, -0.05 * nodeSize.y, z);
					p2.rotateXY(direction);
					Vec3f p3(0.2 * nodeSize.x, 0.05 * nodeSize.y, z);
					p3.rotateXY(direction);
					Vec3f p4(0.05 * nodeSize.x, 0.05 * nodeSize.y, z);
					p4.rotateXY(direction);

					Vec3f p5(0.2 * nodeSize.x, -0.1 * nodeSize.y, z);
					p5.rotateXY(direction);
					Vec3f p6(0.3 * nodeSize.x, 0.0f, z);
					p6.rotateXY(direction);
					Vec3f p7(0.2 * nodeSize.x, 0.1 * nodeSize.y, z);
					p7.rotateXY(direction);

					bool isHovered = hoverType == pickType && hoverSecondary == cell->holder;
					Vec4f& color = condition ? (isHovered ? lightGreen : green) : (isHovered ? lightRed : red);
					mesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
					addMeshTriangle(&mesh, cellCenter + p1, cellCenter + p2, cellCenter + p3, color);
					addMeshTriangle(&mesh, cellCenter + p1, cellCenter + p3, cellCenter + p4, color);
					addMeshTriangle(&mesh, cellCenter + p5, cellCenter + p6, cellCenter + p7, color);
					setpickingdrawfocus(view, holder, pickType, cell->holder);
					mesh.draw(GL_TRIANGLES);
				};

				drawArrow(90.0f, cell->canGoUp != 0, PICK_PATTERN_DIRECTION_UP);
				drawArrow(-90.0f, cell->canGoDown != 0, PICK_PATTERN_DIRECTION_DOWN);
				drawArrow(180.0f, cell->canGoLeft != 0, PICK_PATTERN_DIRECTION_LEFT);
				drawArrow(0.0f, cell->canGoRight != 0, PICK_PATTERN_DIRECTION_RIGHT);

				cellTopLeftPos.x += colWidth;

				if (row == 1 && col < patterns.numCols) {
					setpickingdrawfocus(view, holder, PICK_PATTERN_SIZER_X, cell->holder);
					if (hoverType != PICK_MERGE_PATTERN_COLS || hoverSecondary != cell->holder) {
						borderMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
						addMeshVertex(&borderMesh, Vec3f(cellTopLeftPos.x, myMin.y, gridZ), darkGray);
						addMeshVertex(&borderMesh, Vec3f(cellTopLeftPos.x, myMax.y, gridZ), darkGray);
						borderMesh.draw(GL_LINES);
					}

					drawCellSizer(Vec3f(cellTopLeftPos.x, myMax.y - 0.2 * nodeSize.y, z), 0.0f);
					drawCellSizer(Vec3f(cellTopLeftPos.x, myMin.y + 0.2 * nodeSize.y, z), 0.0f);
					drawTexButton(Vec3f(cellTopLeftPos.x, myMax.y - 0.8 * nodeSize.y, z), 0.0f,
						PICK_MERGE_PATTERN_COLS, stitchesTexture, cell, black, darkGray);
					drawTexButton(Vec3f(cellTopLeftPos.x, myMin.y + 0.8 * nodeSize.y, z), 0.0f,
						PICK_MERGE_PATTERN_COLS, stitchesTexture, cell, black, darkGray);
				}

				drawTexButton(Vec3f(cellTopLeftPos.x - 0.5f * colWidth, myMax.y - 0.2 * nodeSize.y, z), 180.0f,
					PICK_SPLIT_PATTERN_COL, scissorTexture, cell, black, darkGray);
				drawTexButton(Vec3f(cellTopLeftPos.x - 0.5f * colWidth, myMin.y + 0.2 * nodeSize.y, z), 0.0f,
					PICK_SPLIT_PATTERN_COL, scissorTexture, cell, black, darkGray);

				if (hoverType == PICK_SPLIT_PATTERN_COL && hoverSecondary == cell->holder) {
					borderMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
					addMeshVertex(&borderMesh, Vec3f(cellTopLeftPos.x - 0.5f * colWidth, myMin.y, gridZ), darkGray);
					addMeshVertex(&borderMesh, Vec3f(cellTopLeftPos.x - 0.5f * colWidth, myMax.y, gridZ), darkGray);
					borderMesh.draw(GL_LINES);
				}
			}

			cellTopLeftPos.y -= rowHeight;
			PatternCell* cell = patterns.cell(row, 1)->objectAs(PatternCell);
			if (row < patterns.numRows) {
				setpickingdrawfocus(view, holder, PICK_PATTERN_SIZER_Y, cell->holder);
				if (hoverType != PICK_MERGE_PATTERN_ROWS || hoverSecondary != cell->holder) {
					borderMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
					addMeshVertex(&borderMesh, Vec3f(myMin.x, cellTopLeftPos.y, gridZ), darkGray);
					addMeshVertex(&borderMesh, Vec3f(myMax.x, cellTopLeftPos.y, gridZ), darkGray);
					borderMesh.draw(GL_LINES);
				}

				drawCellSizer(Vec3f(myMin.x + 0.2 * nodeSize.x, cellTopLeftPos.y, z), 90.0f);
				drawCellSizer(Vec3f(myMax.x - 0.2 * nodeSize.x, cellTopLeftPos.y, z), 90.0f);
				drawTexButton(Vec3f(myMin.x + 0.8 * nodeSize.x, cellTopLeftPos.y, z), 90.0f,
					PICK_MERGE_PATTERN_ROWS, stitchesTexture, cell, black, darkGray);
				drawTexButton(Vec3f(myMax.x - 0.8 * nodeSize.x, cellTopLeftPos.y, z), 90.0f,
					PICK_MERGE_PATTERN_ROWS, stitchesTexture, cell, black, darkGray);
			}

			drawTexButton(Vec3f(myMax.x - 0.2 * nodeSize.x, cellTopLeftPos.y + 0.5f * rowHeight, z), 90.0f,
				PICK_SPLIT_PATTERN_ROW, scissorTexture, cell, black, darkGray);
			drawTexButton(Vec3f(myMin.x + 0.2 * nodeSize.x, cellTopLeftPos.y + 0.5f * rowHeight, z), -90.0f,
				PICK_SPLIT_PATTERN_ROW, scissorTexture, cell, black, darkGray);

			if (hoverType == PICK_SPLIT_PATTERN_ROW && hoverSecondary == cell->holder && !pickingMode) {
				borderMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
				addMeshVertex(&borderMesh, Vec3f(myMin.x, cellTopLeftPos.y + 0.5 * rowHeight, gridZ), darkGray);
				addMeshVertex(&borderMesh, Vec3f(myMax.x, cellTopLeftPos.y + 0.5 * rowHeight, gridZ), darkGray);
				borderMesh.draw(GL_LINES);
			}
		}
	}
	if (pickingMode)
		glLineWidth(1.0);
	setpickingdrawfocus(view, holder, 0);
	if (!pickingMode && grid && grid->isBounded) {
		mesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
		Mesh gridPointsMesh;
		gridPointsMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
		Vec4f lightGray(0.7f, 0.7f, 0.7f, 1.0f);
		Cell minCell = grid->getCell(myModelMin + Vec3(0.5 * nodeSize.x, 0.5 * nodeSize.y, 0.0));
		Cell maxCell = grid->getCell(myModelMax + Vec3(-0.5 * nodeSize.x, -0.5 * nodeSize.y, 0.0));
		Vec3f offset(-b_spatialx, -b_spatialy, -b_spatialz);
		for (Cell cell = minCell; cell.row <= maxCell.row; cell.row++) {
			for (cell.col = minCell.col; cell.col <= maxCell.col; cell.col++) {
				Vec3f modelPos(grid->getLocation(cell));
				modelPos.z = gridZ;
				Vec3f localPos = modelPos + offset;
				addMeshVertex(&gridPointsMesh, localPos, lightGray);
				PatternCell* patternCell = getPatternCell(Vec3(modelPos));
				if (patternCell) {
					if (patternCell->canGoUp) {
						addMeshVertex(&mesh, localPos, lightGray);
						addMeshVertex(&mesh, localPos + Vec3f(0.0f, 0.2 * nodeSize.y, 0.0f), lightGray);
					}
					if (patternCell->canGoDown) {
						addMeshVertex(&mesh, localPos, lightGray);
						addMeshVertex(&mesh, localPos + Vec3f(0.0f, -0.2 * nodeSize.y, 0.0f), lightGray);
					}
					if (patternCell->canGoRight) {
						addMeshVertex(&mesh, localPos, lightGray);
						addMeshVertex(&mesh, localPos + Vec3f(0.2 * nodeSize.x, 0.0f, 0.0f), lightGray);
					}
					if (patternCell->canGoLeft) {
						addMeshVertex(&mesh, localPos, lightGray);
						addMeshVertex(&mesh, localPos + Vec3f(-0.2 * nodeSize.x, 0.0f, 0.0f), lightGray);
					}
				}
			}
		}
		mesh.draw(GL_LINES);
		glPointSize(3.0f);
		gridPointsMesh.draw(GL_POINTS);
		glPointSize(1.0f);
	}
}

void Barrier::addVertices(treenode view, Mesh* barrierMesh, float z, DrawStyle drawStyle)
{

	Vec3 myMin, myMax;
	if (!getBoundingBox(myMin, myMax))
		return;

	double width = myMax.x - myMin.x;
	double height = myMax.y - myMin.y;

	if (drawStyle == Highlighted) {
		z += 0.001 / getmodelunit(LENGTH_MULTIPLE);
	} else if (drawStyle == Hovered) {
		z += 0.002 / getmodelunit(LENGTH_MULTIPLE);
	} else if (drawStyle == Selected) {
		z += 0.003 / getmodelunit(LENGTH_MULTIPLE);
	}

	Vec3f bottomLeft((float)myMin.x, (float)myMin.y, z);
	Vec3f topRight((float)myMax.x, (float)myMax.y, z );
	Vec3f topLeft((float)myMin.x, (float)myMax.y, z );
	Vec3f bottomRight((float)myMax.x, (float)myMin.y, z);

	if (drawStyle == Basic) {
		Vec4f black(0.4f, 0.4f, 0.4f, 1.0f);
		addMeshTriangle(barrierMesh, bottomRight, topLeft, bottomLeft, black);
		addMeshTriangle(barrierMesh, bottomRight, topRight, topLeft, black);
	} else {
		Vec4f red(1.0f, 0.0f, 0.0f, 1.0f);
		Vec4f yellow(1.0f, 1.0f, 0.0f, drawStyle == Hovered ? 0.5f : 1.0f);
		Vec4f& color = drawStyle == Selected ? red : yellow;
		addMeshLine(barrierMesh, bottomLeft, bottomRight, color);
		addMeshLine(barrierMesh, bottomRight, topRight, color);
		addMeshLine(barrierMesh, topRight, topLeft, color);
		addMeshLine(barrierMesh, topLeft, bottomLeft, color);
	}
}


double Barrier::onClick(treenode view, int clickCode, Vec3& pos)
{
	if (activePointIndex > 1) activePointIndex = 0;

	if (isBasicBarrier()) {
		assertValidPatternTable();
	}
	Point* activePoint = pointList[(int)activePointIndex];
	Point* bottomLeft = pointList[0];
	Point* topRight = pointList[1];

	// Swap point coordinates if they are not actually the bottom left and top right points
	if (bottomLeft->x > topRight->x) {
		double bottomLeftX = bottomLeft->x;
		bottomLeft->x = topRight->x;
		topRight->x = bottomLeftX;
	}
	if (bottomLeft->y > topRight->y) {
		double bottomLeftY = bottomLeft->y;
		bottomLeft->y = topRight->y;
		topRight->y = bottomLeftY;
	}

	// Test to see if the user is clicking on a scaling arrow of the barrier 
	// to resize it. This technically should be done just using FlexSim's 
	// picking features, but I guess Jacob didn't know how to do that at the 
	// time, so he did the math.
	if (clickCode == LEFT_PRESS && !(mode & Barrier::CREATE)) {
		for (int i = 0; i < pointList.size(); i++) {
			applicationcommand("addundotracking", view, node("x", pointList[i]->holder));
			applicationcommand("addundotracking", view, node("y", pointList[i]->holder));
		}

		double z = 0;
		Vec3 myMin, myMax;
		if (!getBoundingBox(myMin, myMax))
			return 0;

		int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, PICK_PRESSED);
		if (pickType != 0) {
			mode = Barrier::POINT_EDIT;
			bool shouldTrackPatternCellSizes = false;
			switch (pickType) {
				case PICK_ARROW_LEFT: activePointIndex = 0; shouldTrackPatternCellSizes = true; break;
				case PICK_ARROW_RIGHT: activePointIndex = 1; shouldTrackPatternCellSizes = true; break;
				case PICK_ARROW_TOP: activePointIndex = 1; shouldTrackPatternCellSizes = true;  break;
				case PICK_ARROW_BOTTOM: activePointIndex = 0; shouldTrackPatternCellSizes = true; break;
				case PICK_PATTERN_SIZER_X: shouldTrackPatternCellSizes = true; break;
				case PICK_PATTERN_SIZER_Y: shouldTrackPatternCellSizes = true; break;
			}

			if (shouldTrackPatternCellSizes) {
				visitPatternCells([view](PatternCell* cell) {
					applicationcommand("addundotracking", view, cell->holder->find("width"));
					applicationcommand("addundotracking", view, cell->holder->find("height"));
				});
			}
		} else {
			activePointIndex = 0;
			mode = Barrier::MOVE;
		}
	}

	if (clickCode == LEFT_RELEASE) {
		if (mode & Barrier::POINT_EDIT) {
			double width = topRight->x - bottomLeft->x;
			double height = topRight->y - bottomLeft->y;

			// Enforce a minimum size
			if (width < drawNodeSize.x / 2.0) {
				if (activePoint == bottomLeft)
					activePoint->x = topRight->x - drawNodeSize.x / 2;
				else
					activePoint->x = bottomLeft->x + drawNodeSize.x / 2;
			}
			if (height < drawNodeSize.y / 2.0) {
				if (activePoint == bottomLeft)
					activePoint->y = topRight->y - drawNodeSize.y / 2;
				else
					activePoint->y = bottomLeft->y + drawNodeSize.y / 2;
			}
		
			activePointIndex = 0;
		}

		int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, PICK_RELEASED);
		if (pickType != 0 && getpickingdrawfocus(view, PICK_TYPE, PICK_PRESSED) == pickType) {
			TreeNode* cellNode = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_RELEASED));
			PatternCell* cell = cellNode ? cellNode->objectAs(PatternCell) : nullptr;
			cursorinfo(view, 4, 0, 0); // update the hover (I think)
			switch (pickType) {
				case PICK_SPLIT_PATTERN_COL: splitPatternCol(cell->holder->rank, view); break;
				case PICK_SPLIT_PATTERN_ROW: splitPatternRow(cell->holder->up->rank, view); break;
				case PICK_MERGE_PATTERN_COLS: mergePatternCols(cell->holder->rank, view); break;
				case PICK_MERGE_PATTERN_ROWS: mergePatternRows(cell->holder->up->rank, view); break;
				case PICK_PATTERN_DIRECTION_DOWN:
				case PICK_PATTERN_DIRECTION_UP:
				case PICK_PATTERN_DIRECTION_LEFT:
				case PICK_PATTERN_DIRECTION_RIGHT: {
					int undoID = beginaggregatedundo(view, "Change Barrier Pattern Cell");
					switch (pickType) {
					case PICK_PATTERN_DIRECTION_DOWN: cell->holder->find("canGoDown")->value = !cell->canGoDown; break;
					case PICK_PATTERN_DIRECTION_UP: cell->holder->find("canGoUp")->value = !cell->canGoUp; break;
					case PICK_PATTERN_DIRECTION_LEFT: cell->holder->find("canGoLeft")->value = !cell->canGoLeft; break;
					case PICK_PATTERN_DIRECTION_RIGHT: cell->holder->find("canGoRight")->value = !cell->canGoRight; break;
					}
					endaggregatedundo(view, undoID);
					break;
				}
				default: break;
			}

		}
	}

	//if (clickCode == RIGHT_RELEASE) {
		// Right click -> abort barrier creation
	//	if (mode & Barrier::CREATE) {
	//		destroyobject(holder);
	//	}
	//}

	return 1;
}

double Barrier::onClick(treenode view, int clickCode)
{
	AStarNavigator* nav = navigator;
	isMeshDirty = true;
	Vec3 pos(cursorinfo(view, 2, 1, 1), cursorinfo(view, 2, 2, 1), cursorinfo(view, 2, 3, 1));
	dragAnchorPointX = dragAnchorPointY = nullptr;
	return onClick(view, clickCode, pos);
}

double Barrier::dragPressedPick(treenode view, Vec3& pos, Vec3& diff)
{
	int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, PICK_PRESSED);
	treenode pointNode = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_PRESSED));
	bool isPointEdit = pointNode != nullptr 
		&& (pickType == PICK_POINT || pickType == PICK_ARROW_LEFT || pickType == PICK_ARROW_RIGHT 
			|| pickType == PICK_ARROW_TOP || pickType == PICK_ARROW_BOTTOM);
	isMeshDirty = true;
	if (isPointEdit) {
		Point* activePoint = pointNode->objectAs(Point);
		Point* activeXPoint = activePoint, *activeYPoint = activePoint;
		if (pickType == PICK_POINT) {
			if (!dragAnchorPointX) {
				dragAnchorPointX = pointList[0];
				dragAnchorPointY = pointList[0];
			}
			Vec3 ptmOffset = getPointToModelOffset();
			Vec2 anchor(dragAnchorPointX->x + ptmOffset.x, dragAnchorPointY->y + ptmOffset.y);

			if (pos.x < anchor.x) {
				activeXPoint = pointList[0];
				if (dragAnchorPointX == activeXPoint) {
					dragAnchorPointX = pointList[1];
					dragAnchorPointX->x = anchor.x - b_spatialx;
				}
			}
			else {
				activeXPoint = pointList[1];
				if (dragAnchorPointX == activeXPoint) {
					dragAnchorPointX = pointList[0];
					dragAnchorPointX->x = anchor.x - b_spatialx;
				}
			}
			if (pos.y < anchor.y) {
				activeYPoint = pointList[0];
				if (dragAnchorPointY == activeYPoint) {
					dragAnchorPointY = pointList[1];
					dragAnchorPointY->y = anchor.y - b_spatialy;
				}
			}
			else {
				activeYPoint = pointList[1];
				if (dragAnchorPointY == activeYPoint) {
					dragAnchorPointY = pointList[0];
					dragAnchorPointY->y = anchor.y - b_spatialy;
				}
			}
		}
		if (pickType == PICK_POINT || pickType == PICK_ARROW_LEFT || pickType == PICK_ARROW_RIGHT) {
			activeXPoint->x += diff.x;
			scalePatternColsOnSizeChange(fabs(pointList[1]->x - pointList[0]->x));
		}
		if (pickType == PICK_POINT || pickType == PICK_ARROW_TOP || pickType == PICK_ARROW_BOTTOM) {
			activeYPoint->y += diff.y;
			scalePatternRowsOnSizeChange(fabs(pointList[1]->y - pointList[0]->y));
		}
		updateSpatialsToEncompassPoints();
		return 1;
	} else if (pickType == 0) {
		if (mode & Barrier::CREATE) {
			mode = Barrier::MOVE;
			modeleditmode(0);
		}
		return 0;
	}
	return 0;
}

double Barrier::dragPressedPick(treenode view, Vec3&& pos, Vec3&& diff)
{
	return dragPressedPick(view, pos, diff);
}

double Barrier::onDrag(treenode view)
{
	Vec3 diff(draginfo(DRAG_INFO_DX), draginfo(DRAG_INFO_DY), draginfo(DRAG_INFO_DZ));
	Vec3 pos(cursorinfo(view, 2, 1, 1), cursorinfo(view, 2, 2, 1), cursorinfo(view, 2, 3, 1));
	double returnVal = dragPressedPick(view, pos, diff);
	int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, PICK_PRESSED);
	if (pickType != 0) {
		switch (pickType) {
		case PICK_PATTERN_SIZER_X: {
			dragPatternCellSizer(tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_PRESSED))->objectAs(PatternCell), diff.x, true);
			returnVal = 1;
			break;
		}
		case PICK_PATTERN_SIZER_Y: {
			dragPatternCellSizer(tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_PRESSED))->objectAs(PatternCell), -diff.y, false);
			returnVal = 1;
			break;
		}
		}
	}
	isMeshDirty = true;
	return returnVal;
}

double Barrier::onPreDraw(treenode view)
{
	b_spatialrx = b_spatialry = b_spatialrz = 0.0;
	return 0.0;
}

double Barrier::onDraw(treenode view)
{
	AStarNavigator* nav = navigator;
	if (!((int)nav->drawMode & ASTAR_DRAW_MODE_BARRIERS))
		return 0;

	if (drawNodeSize != nav->minNodeSize)
		isMeshDirty = true;

	float factor, units;
	bool polyOffsetFill = glIsEnabled(GL_POLYGON_OFFSET_FILL);
	glGetFloatv(GL_POLYGON_OFFSET_FACTOR, &factor);
	glGetFloatv(GL_POLYGON_OFFSET_UNITS, &units);
	fglEnable(GL_POLYGON_OFFSET_FILL);

	double vpRadius = get(viewpointradius(view));
	if (get(viewprojectiontype(view)) == 1)
		vpRadius = maxof(get(spatialsx(view)), get(spatialsy(view))) / get(viewmagnification(view));
	double offset = std::max(-1.0, -50.0 / (vpRadius * getmodelunit(LENGTH_MULTIPLE)));

	glPolygonOffset(offset - 0.025, -5);

	if (isMeshDirty || mode != 0) {
		drawNodeSize = nav->minNodeSize;
		mesh.init(0, MESH_POSITION | MESH_DIFFUSE4);
		addVertices(view, &mesh, 0.0f, Basic);
		isMeshDirty = false;
	}

	fglDisable(GL_TEXTURE_2D);
	fglDisable(GL_LIGHTING);

	fglRotate(-90.0f, 1.0f, 0.0f, 0.0f);
	fglScale(1.0 / b_spatialsx, 1.0 / b_spatialsy, 1.0 / b_spatialsz);

	int pickingMode = getpickingmode(view);
	if (pickingMode) {
		drawPickObjects(view);
		setpickingdrawfocus(view, holder, 0, 0, 0);
	}

	treenode selObj = selectedobject(view);
	treenode hoverObj = tonode(getpickingdrawfocus(view, PICK_OBJECT, PICK_HOVERED));
	if ((selObj == holder || hoverObj == holder || switch_selected(holder, -1)) && !pickingMode) {
		glLineWidth(5.0f);
		Mesh temp;
		if (selObj == holder || hoverObj == holder) {
			temp.init(0, MESH_POSITION | MESH_DIFFUSE4);
			addVertices(view, &temp, 0.0f, selObj == holder ? Highlighted : Hovered);
			temp.draw(GL_LINES);
		}

		if (switch_selected(holder, -1)) {
			temp.init(0, MESH_POSITION | MESH_DIFFUSE4);
			addVertices(view, &temp, 0.0f, Selected);
			temp.draw(GL_LINES);
		}
		glLineWidth(1.0f);

	}
	if (selObj == holder) {
		drawManipulationHandles(view);
	}

	setpickingdrawfocus(view, holder, 0, 0, OVERRIDE_DRAW_ALL);
	mesh.draw(GL_TRIANGLES);

	fglEnable(GL_TEXTURE_2D);
	fglEnable(GL_LIGHTING);

	glPolygonOffset(factor, units);
	if (polyOffsetFill == false)
		fglDisable(GL_POLYGON_OFFSET_FILL);
	return 0;
}

unsigned int Barrier::getClassType()
{
	return CLASSTYPE_WANTCONNECTLOGIC;
}

double Barrier::dragConnection(TreeNode * connectTo, char keyPressed, unsigned int classType)
{
	return navigator->dragConnection(connectTo, keyPressed, classType, this);
}

double Barrier::onDestroy(TreeNode * view)
{
	isMeshDirty = true;
	return 0.0;
}

double Barrier::onUndo(bool isUndo, treenode undoRecord)
{
	isMeshDirty = true;

	// Fix active point index
	if (activePointIndex > pointList.size())
		activePointIndex = pointList.size();
	return 0.0;
}

double Barrier::onCreate(double dropx, double dropy, double dropz, int iscopy)
{
	assertNavigator();

	drawNodeSize = navigator->minNodeSize;
	nodeSize = drawNodeSize;

	if (holder->up == model()) {
		holder->name = applicationcommand("getuniquename", getname(classobject(holder)), navigator->holder);
		holder->up = navigator->holder;
	}
	if (isBasicBarrier())
		assertValidPatternTable();
	return 0.0;
}

void Barrier::updateSpatialsToEncompassPoints()
{
	Vec3 min, max;
	getBoundingBox(min, max);
	double oneMillimeter = 0.001 / getmodelunit(LENGTH_MULTIPLE);
	node_b_spatialsx->value = maxof(oneMillimeter, max.x - min.x);
	node_b_spatialsy->value = maxof(oneMillimeter, max.y - min.y);
	node_b_spatialsz->value = maxof(oneMillimeter, max.z - min.z);
	if (min.x == 0.0 && max.y == 0.0 && min.z == 0.0)
		return;
	node_b_spatialx->value += min.x;
	node_b_spatialy->value += max.y;
	node_b_spatialz->value += min.z;

	for (Point* point : pointList) {
		point->holder->find("x")->value -= min.x;
		point->holder->find("y")->value -= max.y;
		point->holder->find("z")->value -= min.z;
	}
}

void Barrier::updatePointsFromSpatials()
{
	if (pointList.size() != 2)
		return;
	*(pointList.front()) = Vec3(0, -size.y, 0);
	*(pointList.back()) = Vec3(size.x, 0, 0);
}

Point* Barrier::addPoint(const Vec3& modelPos)
{
	Vec3 pos = modelPos.project(model(), holder);
	Point* point = new Point(pos.x, pos.y, pos.z);
	pointList.add(point);
	if (!toBridge() && pointList.size() > 1) // everything but bridges should have the same z
		point->z = pointList.front()->z;
	return point;
}

void Barrier::removePoint(int pointIndex)
{
	if (pointIndex >= pointList.size())
		return;

	pointList.remove(pointIndex);
}

void Barrier::swapPoints(int index1, int index2)
{
	int maxIndex = std::max(index1, index2);
	int minIndex = std::min(index1, index2);

	if (maxIndex >= pointList.size() || minIndex < 0)
		return;

	pointList.swap(index1, index2);
}

Vec3 Barrier::getLocalPointCoords(int pointIndex)
{
	if (pointIndex >= pointList.size())
		throw "Invalid Barrier point index";

	return *pointList[pointIndex];
}

Vec3 Barrier::getPointCoords(int pointIndex)
{
	Vec3 pos = getLocalPointCoords(pointIndex);
	pos += location;
	return pos;
}

astar_export Variant Barrier::getPointCoord(FLEXSIMINTERFACE)
{
	Vec3 coord = getPointCoords((int)param(1));
	int coordID = param(2);
	if (coordID == POINT_X)
		return coord.x;
	if (coordID == POINT_Y)
		return coord.y;
	if (coordID == POINT_Z)
		return coord.z;

	return 0.0;
}

bool Barrier::setPointCoords(int pointIndex, const Vec3& parentPoint)
{
	if (pointIndex >= pointList.size())
		return false;

	Vec3 localPoint = parentPoint - location;
	Vec2 oldSize;
	if (pointList.size() > 1 && isBasicBarrier()) {
		oldSize = Vec2(pointList[1]->x - pointList[0]->x, pointList[1]->y - pointList[0]->y);
	}

	pointList[pointIndex]->x = localPoint.x;
	pointList[pointIndex]->y = localPoint.y;
	bool applyToAllZ = fabs(localPoint.z != pointList[pointIndex]->z) > 0.0001 && !toBridge();
	// for anything but a bridge, z locations should be the same for all points
	if (applyToAllZ) {
		for (int i = 0; i < pointList.size(); i++)
			pointList[i]->z = localPoint.z;
	} else 
		pointList[pointIndex]->z = localPoint.z;

	if (pointList.size() > 1 && isBasicBarrier()) {
		Vec2 newSize(pointList[1]->x - pointList[0]->x, pointList[1]->y - pointList[0]->y);
		if (oldSize.x != newSize.x)
			scalePatternColsOnSizeChange(newSize.x);
		if (oldSize.y != newSize.y)
			scalePatternRowsOnSizeChange(newSize.y);
	}
	updateSpatialsToEncompassPoints();
	isMeshDirty = true;
	return true;
}

void Barrier::addPathVertices(treenode view, Mesh* barrierMesh, float z, const Vec4f& color, DrawStyle drawStyle, bool twoWay)
{
	Vec4f theColor( std::min(1.0f, color.r + 0.2f), std::min(1.0f, color.g + 0.2f), std::min(1.0f, color.b + 0.2f), color.a );
	Vec4f lightGray( 0.4f, 0.4f, 0.4f, 1.0f );
	Vec4f highlightColor(1.0f, 1.0f, 0.0f, 1.0f);
	if (drawStyle == Highlighted) {
		z += 0.001 / getmodelunit(LENGTH_MULTIPLE);
	} else if (drawStyle == Hovered) {
		highlightColor.a = 0.5f;
		z += 0.002 / getmodelunit(LENGTH_MULTIPLE);
	}
	else if (drawStyle == Selected) {
		highlightColor.g = 0.0f;
	}

	// Add circles at each node
	float radius = drawNodeWidth * 0.15;
	for (int i = 0; i < pointList.size(); i++) {
		Point* point = pointList[i];
		bool shouldDraw = drawStyle == Basic;
		if (!shouldDraw) {
			int pickType = (int)getpickingdrawfocus(view, PICK_TYPE, PICK_HOVERED);
			if (pickType == PICK_POINT) {
				treenode hovered = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_HOVERED));
				if (point->holder == hovered)
					shouldDraw = true;
			}
			if (drawStyle == Highlighted && i == activePointIndex)
				shouldDraw = true;
		}
		if (shouldDraw)
			point->addVertices(barrierMesh, radius, drawStyle == Basic ? lightGray : highlightColor, z, drawStyle != Basic);
	}

	// Draw a series of triangles
	float maxTriangleWidth = drawNodeWidth;
	float distToCorner = radius;
	float height = 2 * radius;
	bool isBridge = toBridge() ? true : false;
	float dTheta = atan2(radius, 0);

	for (int i = 0; i < pointList.size() - 1; i++) {
		Point* point = pointList[i];
		Point* next = pointList[i + 1];

		Vec3f fromPoint(*point);
		Vec3f toPoint(*next);
		Vec3f diff = toPoint - fromPoint;
		float angle = radianstodegrees(atan2(diff.y, diff.x));

		float lengthXY = sqrt(diff.x * diff.x + diff.y * diff.y);
		if (lengthXY <= 2 * radius)
			continue;

		double radiusRatio = radius / lengthXY;
		fromPoint.x += diff.x * radiusRatio;
		fromPoint.y += diff.y * radiusRatio;
		toPoint.x -= diff.x * radiusRatio;
		toPoint.y -= diff.y * radiusRatio;
		diff = toPoint - fromPoint;
		lengthXY -= 2 * radius;

		// Find how many will fit, and stretch them to fit.
		int numTriangles = (int)(lengthXY / maxTriangleWidth);
		if (numTriangles < 1) {
			numTriangles = 1;
		}
		float triangleWidth = lengthXY / numTriangles;
		Vec3f diffPerTriangle = diff / (float)numTriangles;
		
		Vec3f tip = Vec3f(triangleWidth, 0.0f, diffPerTriangle.z).rotateXY(angle) + fromPoint;
		Vec3f top = Vec3f(0.0f, 0.5f * height, 0.0f).rotateXY(angle) + fromPoint;
		Vec3f bottom = Vec3f(0.0f, -0.5f * height, 0.0f).rotateXY(angle) + fromPoint;

		Vec3f backwardsTip, backwardsTop, backwardsBottom;
		if (twoWay) {
			backwardsTip = Vec3f(0.0f, 0.0f, 0.0f).rotateXY(angle) + fromPoint;
			backwardsTop = Vec3f(triangleWidth, 0.5f * height, diffPerTriangle.z).rotateXY(angle) + fromPoint;
			backwardsBottom = Vec3f(triangleWidth, -0.5f * height, diffPerTriangle.z).rotateXY(angle) + fromPoint;
		}

		for (int j = 0; j < numTriangles; j++) {
			if (!twoWay || j % 2 == 0) {
				if (drawStyle == Basic) {
					addMeshVertex(barrierMesh, tip, theColor);
					addMeshVertex(barrierMesh, top, lightGray);
					addMeshVertex(barrierMesh, bottom, lightGray);
				}
				else {
					addMeshVertex(barrierMesh, tip, highlightColor);
					addMeshVertex(barrierMesh, top, highlightColor);
					addMeshVertex(barrierMesh, top, highlightColor);
					addMeshVertex(barrierMesh, bottom, highlightColor);
					addMeshVertex(barrierMesh, bottom, highlightColor);
					addMeshVertex(barrierMesh, tip, highlightColor);
				}
			} else {
				if (drawStyle == Basic) {
					addMeshVertex(barrierMesh, backwardsTip, theColor);
					addMeshVertex(barrierMesh, backwardsTop, lightGray);
					addMeshVertex(barrierMesh, backwardsBottom, lightGray);
				}
				else {
					addMeshVertex(barrierMesh, backwardsTip, highlightColor);
					addMeshVertex(barrierMesh, backwardsTop, highlightColor);
					addMeshVertex(barrierMesh, backwardsTop, highlightColor);
					addMeshVertex(barrierMesh, backwardsBottom, highlightColor);
					addMeshVertex(barrierMesh, backwardsBottom, highlightColor);
					addMeshVertex(barrierMesh, backwardsTip, highlightColor);
				}

			}

			tip += diffPerTriangle;
			top += diffPerTriangle;
			bottom += diffPerTriangle;
			if (twoWay) {
				backwardsTip += diffPerTriangle;
				backwardsTop += diffPerTriangle;
				backwardsBottom += diffPerTriangle;
			}
		}
	}
}

void Barrier::onReset(AStarNavigator * nav)
{
	Vec3 min, max;
	getBoundingBox(min, max, model());
	nodeSize = nav->getGrid(min)->nodeSize;
	drawNodeSize = nav->minNodeSize;
	isMeshDirty = true;
	if (isBasicBarrier()) {
		assertValidPatternTable();
	}
	conditionalBarrierChanges = TemporaryBarrier(nav);
}

void Barrier::abortCreationMode()
{
	mode = 0;
	if (pointList.size() <= 2)
		destroyobject(holder);
	else {
		Point* lastPoint = pointList.back();
		destroyobject(lastPoint->holder);
		isMeshDirty = true;
	}
}


void Barrier::splitPatternRow(int row, treenode view)
{
	Table table(patternTable);

	int undoID = view ? beginaggregatedundo(view, "Split Barrier Pattern Row") : 0;
	table.addRow(row + 1);

	for (int col = 1; col <= table.numCols; col++) {
		PatternCell* cell = new PatternCell;
		table.cell(row + 1, col)->addSimpleData(cell, true);
		PatternCell* prevCell = table.cell(row, col)->objectAs(PatternCell);
		// set height in a undo-able way
		prevCell->holder->find("height")->value = prevCell->height * 0.5;
		cell->height = prevCell->height;
		cell->width = prevCell->width;
		cell->canGoUp = prevCell->canGoUp;
		cell->canGoDown = prevCell->canGoDown;
		cell->canGoLeft = prevCell->canGoLeft;
		cell->canGoRight = prevCell->canGoRight;
	}
	if (view)
		endaggregatedundo(view, undoID);
}

void Barrier::splitPatternCol(int col, treenode view)
{
	Table table(patternTable);

	int undoID = view ? beginaggregatedundo(view, "Split Barrier Pattern Column") : 0;
	table.addCol(col + 1);

	for (int row = 1; row <= table.numRows; row++) {
		PatternCell* cell = new PatternCell;
		table.cell(row, col + 1)->addSimpleData(cell, true);
		PatternCell* prevCell = table.cell(row, col)->objectAs(PatternCell);
		// set width in a undo-able way
		prevCell->holder->find("width")->value = prevCell->width * 0.5;
		cell->width = prevCell->width;
		cell->height = prevCell->height;
		cell->canGoUp = prevCell->canGoUp;
		cell->canGoDown = prevCell->canGoDown;
		cell->canGoLeft = prevCell->canGoLeft;
		cell->canGoRight = prevCell->canGoRight;
	}
	if (view)
		endaggregatedundo(view, undoID);
}

void Barrier::mergePatternRows(int firstRow, treenode view)
{
	Table table(patternTable);
	if (table.numRows < firstRow + 1)
		return;

	int undoID = view ? beginaggregatedundo(view, "Merge Barrier Pattern Rows") : 0;

	treenode heightNode = table.cell(firstRow, 1)->find("height");
	heightNode->value = heightNode->value + table.cell(firstRow + 1, 1)->objectAs(PatternCell)->height;
	table.deleteRow(firstRow + 1);
	
	if (view)
		endaggregatedundo(view, undoID);
}

void Barrier::mergePatternCols(int firstCol, treenode view)
{
	Table table(patternTable);
	if (table.numCols < firstCol + 1)
		return;

	int undoID = view ? beginaggregatedundo(view, "Merge Barrier Pattern Columns") : 0;

	treenode widthNode = table.cell(1, firstCol)->find("width");
	widthNode->value = widthNode->value + table.cell(1, firstCol + 1)->objectAs(PatternCell)->width;
	table.deleteCol(firstCol + 1);
	if (view)
		endaggregatedundo(view, undoID);
}

void Barrier::scalePatternRowsOnSizeChange(double newYSize)
{	
	Table patterns(patternTable);
	if (patterns.numRows == 1) {
		patterns.cell(1, 1)->objectAs(PatternCell)->height = maxof(0.00000001, newYSize);
	} else {
		double oldYSize = 0;
		for (int row = 1; row <= patterns.numRows; row++)
			oldYSize += patterns.cell(row, 1)->objectAs(PatternCell)->height;

		double scaleFactor = newYSize / oldYSize;
		for (int row = 1; row <= patterns.numRows; row++) {
			PatternCell* cell = patterns.cell(row, 1)->objectAs(PatternCell);
			if (oldYSize != 0)
				cell->height *= scaleFactor;
			else cell->height = newYSize / patterns.numRows;
		}
	}
}

void Barrier::scalePatternColsOnSizeChange(double newXSize)
{
	Table patterns(patternTable);
	if (patterns.numCols == 1) {
		patterns.cell(1, 1)->objectAs(PatternCell)->width = maxof(0.00000001, newXSize);
	} else {
		double oldXSize = 0;
		for (int col = 1; col <= patterns.numCols; col++)
			oldXSize += patterns.cell(1, col)->objectAs(PatternCell)->width;

		double scaleFactor = newXSize / oldXSize;
		for (int col = 1; col <= patterns.numCols; col++) {
			PatternCell* cell = patterns.cell(1, col)->objectAs(PatternCell);
			if (oldXSize != 0)
				cell->width *= scaleFactor;
			else cell->width = newXSize / patterns.numCols;
		}
	}
}

Barrier::PatternCell* Barrier::getPatternCell(Vec3& modelPos)
{
	Vec3 myMin, myMax;
	if (!getBoundingBox(myMin, myMax, model()))
		return nullptr;
	if (modelPos.x < myMin.x || modelPos.x > myMax.x || modelPos.y < myMin.y || modelPos.y > myMax.y)
		return nullptr;
	Table patterns(patternTable);
	double cellX = myMin.x;
	int col;
	for (col = 1; true; col++) {
		if (col > patterns.numCols)
			col = 1;
		double width = patterns.cell(1, col)->objectAs(PatternCell)->width;
		cellX += width;
		if (cellX > modelPos.x)
			break;
	}
	double cellY = myMax.y;
	int row;
	for (row = 1; true; row++) {
		if (row > patterns.numRows)
			row = 1;
		double height = patterns.cell(row, 1)->objectAs(PatternCell)->height;
		cellY -= height;
		if (cellY < modelPos.y)
			break;
	}
	if (col <= patterns.numCols && row <= patterns.numRows)
		return patterns.cell(row, col)->objectAs(PatternCell);
	return nullptr;
}

Barrier::PatternCell* Barrier::getPatternCell(Vec3&& modelPos)
{
	return getPatternCell(modelPos);
}

Barrier::PatternCell* Barrier::getPatternCell(const Cell& cell) 
{ 
	return getPatternCell(navigator->getLocation(cell)); 
}

void Barrier::dragPatternCellSizer(PatternCell * cell, double diff, bool isXSizer)
{
	// Limit cell growth
	if (diff > 0) {
		double sizeBeforeGrow = 0;
		bool didVisitCell = false;
		visitPatternCells([&](PatternCell* temp) {
			if (!didVisitCell) {
				double val = isXSizer ? temp->width : temp->height;
				sizeBeforeGrow += val;
				if (temp == cell)
					didVisitCell = true;
			}
		}, isXSizer ? VISIT_FIRST_ROW_ONLY : VISIT_FIRST_COL_ONLY);
		double maxDiff = (isXSizer ? fabs(pointList[1]->x - pointList[0]->x) : fabs(pointList[1]->y - pointList[0]->y)) - sizeBeforeGrow;
		if (diff > maxDiff) diff = maxDiff;
	}
	double& val = isXSizer ? cell->width : cell->height;
	val += diff;
	if (val < 0) {
		double overflow = -val;
		val = 0;
		bool didVisitCell = false;
		visitPatternCells([&](PatternCell* temp) {
			if (overflow != 0) {
				if (!didVisitCell) {
					if (temp == cell)
						didVisitCell = true;
				} else {
					double& val = isXSizer ? temp->width : temp->height;
					val -= overflow;
					if (val <= 0) {
						overflow = -val;
						val = 0;
					}
					else overflow = 0;
				}
			}
		}, (isXSizer ? VISIT_FIRST_ROW_ONLY : VISIT_FIRST_COL_ONLY) | VISIT_BACKWARDS);
		if (overflow != 0)
			diff += overflow;
	}
	bool didVisitCell = false;
	visitPatternCells([&](PatternCell* temp) {
		if (diff != 0) {
			if (!didVisitCell) {
				if (temp == cell)
					didVisitCell = true;
			} else {
				double& val = isXSizer ? temp->width : temp->height;
				val -= diff;
				if (val <= 0) {
					diff = -val;
					val = 0;
				} else diff = 0;
			}
		}
	}, isXSizer ? VISIT_FIRST_ROW_ONLY : VISIT_FIRST_COL_ONLY);
}

void Barrier::assertValidPatternTable()
{
	Table patterns(patternTable);
	if (patterns.numRows == 0 || patterns.numCols == 0) {
		patterns.setSize(1, 1, 0, 0);
		PatternCell* cell = new PatternCell;
		nodeaddsimpledata(patterns.cell(1, 1), cell, 1);
		Vec3 min, max;
		getBoundingBox(min, max);
		cell->width = maxof(0.0000001, fabs(max.x - min.x));
		cell->height = maxof(0.0000001, fabs(max.y - min.y));
	}
}

void Barrier::visitPatternCells(std::function<void(PatternCell*)> callback, int flags)
{
	Table patterns(patternTable);

	int incVal = 1, startRow = 1, startCol = 1;
	int endRow = (flags & VISIT_FIRST_ROW_ONLY) ? 2 : patterns.numRows + 1;
	int endCol = (flags & VISIT_FIRST_COL_ONLY) ? 2 : patterns.numCols + 1;
	if (flags & VISIT_BACKWARDS) {
		startRow = patterns.numRows;
		startCol = patterns.numCols;
		endRow = 0;
		endCol = 0;
		incVal = -1;
	}

	for (int row = startRow; row != endRow; row += incVal) {
		for (int col = startCol; col != endCol; col += incVal) {
			callback(patterns.cell(row, col)->objectAs(PatternCell));
		}
	}
}

Vec3 Barrier::getPointToModelOffset()
{
	Vec3 offset(b_spatialx, b_spatialy, b_spatialz);
	if (holder->up != navigator->holder && holder->up != model())
		offset = offset.project(holder->up, model());
	return offset;
}

void Barrier::setSizeComponent(treenode sizeAtt, double toSize)
{
	if (toSize <= 0)
		toSize = 1;
	if (sizeAtt == node_b_spatialsy) {
		pointList.front()->holder->find("y")->value = pointList.back()->y - toSize;
		scalePatternRowsOnSizeChange(fabs(pointList[1]->y - pointList[0]->y));
	} else if (sizeAtt == node_b_spatialsx) {
		pointList.back()->holder->find("x")->value = pointList.front()->x + toSize;
		scalePatternColsOnSizeChange(fabs(pointList[1]->x - pointList[0]->x));
	}
	updateSpatialsToEncompassPoints();
	isMeshDirty = true;
}

bool Barrier::evaluateCondition(Traveler * traveler)
{
	if (conditionRule) {
		if (traveler->isCachedPathKeyValid)
			return traveler->cachedPathKey.barrierConditions[conditionRule->rank - 1];
		return (bool)conditionRule->evaluate(traveler->te->holder);
	} else return true;
}


void Barrier::PatternCell::bind()
{
	bindDouble(width, 1);
	bindDouble(height, 1);
	bindDouble(canGoUp, 1);
	bindDouble(canGoDown, 1);
	bindDouble(canGoLeft, 1);
	bindDouble(canGoRight, 1);
}

}
