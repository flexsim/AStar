#include "Barrier.h"
#include "AStarNavigator.h"
#include "Grid.h"
#include "macros.h"

namespace AStar {
Barrier::Barrier()
	: meshOffset(0)
	, nrVerts(0)
	, activePointIndex(0)
	, mode(0)
	, lastMode(0)
	//, nodeWidth(1.0)
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
	
	//bindNumber(meshOffset);
	//bindNumber(nrVerts);
	//bindNumber(isActive);
	//bindNumber(activePointIndex);
	//bindNumber(mode);

	bindVariableByName("navigator", navigatorCoupling, ODT_BIND_STATE_VARIABLE);

	bindVariable(points);
	pointList.init(points);

	bindVariable(useCondition);
	bindVariable(condition);
	bindVariable(patternTable);
	bindStateVariable(nodeWidth);
}

void Barrier::bind(void)
{
	__super::bind();
	bindCallback(onMouseMove, Barrier);
	bindCallback(addPoint, Barrier);
	bindCallback(removePoint, Barrier);
	bindCallback(swapPoints, Barrier);
	bindCallback(getPointCoord, Barrier);
	bindCallback(setPointCoords, Barrier);
	bindCallback(getType, Barrier);
	bindCallback(getEditMode, Barrier);
	bindCallback(setEditMode, Barrier);
	bindCallback(setActiveIndex, Barrier);
	bindCallback(splitPatternRow, Barrier);
	bindCallback(splitPatternCol, Barrier);
	bindCallback(mergePatternRows, Barrier);
	bindCallback(mergePatternCols, Barrier);

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

void Barrier::bindEvents()
{
	bindEventByName("condition", condition, "Condition", EVENT_TYPE_VALUE_GETTER);
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

void Barrier::init(double nodeWidth, const Vec3& pos1, const Vec3& pos2)
{
	this->nodeWidth = nodeWidth;
	pointList.clear();
	addPoint(pos1);
	addPoint(pos2);

	if (isBasicBarrier()) {
		assertValidPatternTable();
	}
}


bool Barrier::getLocalBoundingBox(Vec3& min, Vec3& max) 
{
	if (pointList.size() < 2) 
		return false;
	
	Vec3 p0 = getPointCoords(0);
	Vec3 p1 = getPointCoords(1);

	min = Vec3(min(p0.x, p1.x), min(p0.y, p1.y), min(p0.z, p1.z));
	max = Vec3(max(p0.x, p1.x), max(p0.y, p1.y), max(p0.z, p1.z));
	return true;
}

bool Barrier::getBoundingBox(Vec3& min, Vec3& max, bool inLocalCoords)
{
	if (!getLocalBoundingBox(min, max))
		return false;

	if (!inLocalCoords) {
		Vec3 pos(b_spatialx, b_spatialy, b_spatialz);
		if (holder->up != model() && holder->up != navigator->holder)
			pos = pos.project(holder->up, model());
		min += pos;
		max += pos;
	}

	return true;
}

void Barrier::addBarriersToTable(Grid* grid)
	//AStarNode* edgeTable, 
	//					  std::unordered_map<unsigned int, AStarNodeExtraData>* extraData, 
	//					  double c0, double r0, unsigned int edgeTableXSize, unsigned int edgeTableYSize)
{
	Vec3 myMin, myMax;
	if (!getBoundingBox(myMin, myMax))
		return;

	Table patterns(patternTable);
	bool isTrivialSolidBarrier = false;
	if (patterns.numCols == 1 && patterns.numRows == 1) {
		PatternCell* cell = patterns.cell(1, 1)->objectAs(PatternCell);
		isTrivialSolidBarrier = !cell->canGoUp && !cell->canGoDown && !cell->canGoLeft && !cell->canGoRight;
	}

	if (isTrivialSolidBarrier) {
		grid->addSolidBarrierToTable(myMin, myMax, this);
	} else {
		AStarCell minCell = grid->getCellFromLoc(myMin + Vec3(0.5 * grid->nodeWidth, 0.5 * grid->nodeWidth, 0.0));
		AStarCell maxCell = grid->getCellFromLoc(myMax + Vec3(-0.5 * grid->nodeWidth, -0.5 * grid->nodeWidth, 0.0));
		for (AStarCell cell = minCell; cell.row <= maxCell.row; cell.row++) {
			for (cell.col = minCell.col; cell.col <= maxCell.col; cell.col++) {
				PatternCell* patternCell = getPatternCell(grid->getLocFromCell(cell));
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

void Barrier::addMeshVertex(Mesh* mesh, float* pos, float* color, unsigned int* incNumVerts)
{
	int newVertex = mesh->addVertex();
	mesh->setVertexAttrib(newVertex, MESH_POSITION, pos);
	mesh->setVertexAttrib(newVertex, MESH_DIFFUSE4, color);
	if (incNumVerts)
		(*incNumVerts)++;
}

void Barrier::addMeshVertex(Mesh * mesh, Vec3f & pos, Vec2f & tex, Vec4f & color, unsigned int * incNumVerts)
{
	int newVertex = mesh->addVertex();
	mesh->setVertexAttrib(newVertex, MESH_POSITION, pos);
	mesh->setVertexAttrib(newVertex, MESH_TEX_COORD2, tex);
	mesh->setVertexAttrib(newVertex, MESH_DIFFUSE4, color);
	if (incNumVerts)
		(*incNumVerts)++;
}

void Barrier::addMeshTriangle(Mesh * mesh, float * p1, float * p2, float * p3, float * color, unsigned int* incNumVerts)
{
	addMeshVertex(mesh, p1, color, incNumVerts);
	addMeshVertex(mesh, p2, color, incNumVerts);
	addMeshVertex(mesh, p3, color, incNumVerts);
}

void Barrier::addMeshTriangle(Mesh * mesh, Vec3f & p1, Vec2f & tex1, Vec3f & p2, Vec2f & tex2, Vec3f & p3, Vec2f & tex3, Vec4f & color, unsigned int * incNumVerts)
{
	addMeshVertex(mesh, p1, tex1, color, incNumVerts);
	addMeshVertex(mesh, p2, tex2, color, incNumVerts);
	addMeshVertex(mesh, p3, tex3, color, incNumVerts);
}

void Barrier::addMeshLine(Mesh * mesh, Vec3f & p1, Vec3f & p2, Vec4f & color, unsigned int * incNumVerts)
{
	addMeshVertex(mesh, p1, color, incNumVerts);
	addMeshVertex(mesh, p2, color, incNumVerts);
}

void Barrier::drawManipulationHandles(treenode view)
{
	Vec3 myMin, myMax;
	if (!getBoundingBox(myMin, myMax, true))
		return;

	Vec3 pos(b_spatialx, b_spatialy, b_spatialz);
	if (holder->up != model() && holder->up != navigator->holder)
		pos = pos.project(holder->up, model());
	Vec3 myModelMin(myMin + pos), myModelMax(myMax + pos);

	Grid* grid = navigator->getGrid(myMin);
	grid->growToEncompassBoundingBox(myModelMin, myModelMax, false);
	grid->resolveGridOrigin();
	nodeWidth = grid->nodeWidth;
	Vec3 size = myMax - myMin;
	float width = (float)(myMax.x - myMin.x);
	float height = (float)(myMax.y - myMin.y);
	float scale = max(this->nodeWidth, 0.15 * max(height, width));
	float lengthMultiple = getmodelunit(LENGTH_MULTIPLE);
	float z = (float)myMin.z + 0.01 / lengthMultiple;
	Vec4f baseColor(0.6f, 0.6f, 0.6f, 1.0f);
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

	int hoverType = getpickingdrawfocus(view, PICK_TYPE, PICK_HOVERED);
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

	Vec3f colAddPos(myMax.x + 0.5 * nodeWidth, myMax.y - 0.5 * nodeWidth, z);
	Vec3f rowAddPos(myMin.x + 0.5 * nodeWidth, myMin.y - 0.5 * nodeWidth, z);
	Table patterns(patternTable);

	Vec4f green(0.0f, 0.6f, 0.0f, 1.0f);
	Vec4f lightGreen(0.3f, 0.8f, 0.3f, 1.0f);

	int pickingMode = getpickingmode(view);
	float gridZ = z + 0.02 / lengthMultiple;
	Vec3f cellTopLeftPos((float)myMin.x, (float)myMax.y, z);
	Mesh borderMesh;
	borderMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);

	auto drawCellSizer = [&](Vec3f& center, float arrowDirection) {
		mesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
		Vec3f p1(0.1f * nodeWidth, 0.2f * nodeWidth, z);
		p1.rotateXY(arrowDirection);
		Vec3f p2(0.1f * nodeWidth, -0.2f * nodeWidth, z);
		p2.rotateXY(arrowDirection);
		Vec3f p3(0.3f * nodeWidth, 0.0f, z);
		p3.rotateXY(arrowDirection);

		Vec3f p4(-0.1f * nodeWidth, -0.2f * nodeWidth, z);
		p4.rotateXY(arrowDirection);
		Vec3f p5(-0.1f * nodeWidth, 0.2f * nodeWidth, z);
		p5.rotateXY(arrowDirection);
		Vec3f p6(-0.3f * nodeWidth, 0.0f, z);
		p6.rotateXY(arrowDirection);

		addMeshTriangle(&mesh, center + p1, center + p2, center + p3, red);
		addMeshTriangle(&mesh, center + p4, center + p5, center + p6, red);
		if (pickingMode) {
			addMeshTriangle(&mesh, center + p2, center + p1, center + p5, red);
			addMeshTriangle(&mesh, center + p2, center + p5, center + p4, red);
		}
		mesh.draw(GL_TRIANGLES);
	};

	auto drawTexButton = [&](Vec3f& center, float rotation, int pickType, int textureIndex, PatternCell* cell, Vec4f& baseColor, Vec4f& hoverColor) {
		mesh.init(0, MESH_POSITION | MESH_DIFFUSE4 | MESH_TEX_COORD2, MESH_DYNAMIC_DRAW);
		Vec3f p1(0.2f * nodeWidth, 0.2f * nodeWidth, z);
		p1.rotateXY(rotation);
		Vec3f p2(-0.2f * nodeWidth, 0.2f * nodeWidth, z);
		p2.rotateXY(rotation);
		Vec3f p3(-0.2f * nodeWidth, -0.2f * nodeWidth, z);
		p3.rotateXY(rotation);
		Vec3f p4(0.2f * nodeWidth, -0.2f * nodeWidth, z);
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

	int scissorTexture = get(navigator->node_b_imageindexobject->find("split"));
	int stitchesTexture = get(navigator->node_b_imageindexobject->find("merge"));

	if (pickingMode)
		glLineWidth(5.0); // make it so the pattern divider lines are easier to grab

	for (int row = 1; row <= patterns.numRows; row++) {
		double rowHeight = patterns.cell(row, 1)->objectAs(PatternCell)->height;
		cellTopLeftPos.x = myMin.x;

		for (int col = 1; col <= patterns.numCols; col++) {
			float colWidth = (float)patterns.cell(1, col)->objectAs(PatternCell)->width;

			Vec3f cellCenter = cellTopLeftPos + Vec3f(0.5f * colWidth, -0.5f * rowHeight, 0.0f);
			PatternCell* cell = patterns.cell(row, col)->objectAs(PatternCell);
			auto drawArrow = [&](float direction, bool condition, int pickType) {
				Vec3f p1(0.05 * nodeWidth, -0.05 * nodeWidth, z);
				p1.rotateXY(direction);
				Vec3f p2(0.2 * nodeWidth, -0.05 * nodeWidth, z);
				p2.rotateXY(direction);
				Vec3f p3(0.2 * nodeWidth, 0.05 * nodeWidth, z);
				p3.rotateXY(direction);
				Vec3f p4(0.05 * nodeWidth, 0.05 * nodeWidth, z);
				p4.rotateXY(direction);

				Vec3f p5(0.2 * nodeWidth, -0.1 * nodeWidth, z);
				p5.rotateXY(direction);
				Vec3f p6(0.3 * nodeWidth, 0.0f, z);
				p6.rotateXY(direction);
				Vec3f p7(0.2 * nodeWidth, 0.1 * nodeWidth, z);
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

				drawCellSizer(Vec3f(cellTopLeftPos.x, myMax.y - 0.2 * nodeWidth, z), 0.0f);
				drawCellSizer(Vec3f(cellTopLeftPos.x, myMin.y + 0.2 * nodeWidth, z), 0.0f);
				drawTexButton(Vec3f(cellTopLeftPos.x, myMax.y - 0.8 * nodeWidth, z), 0.0f, 
					PICK_MERGE_PATTERN_COLS, stitchesTexture, cell, black, darkGray);
				drawTexButton(Vec3f(cellTopLeftPos.x, myMin.y + 0.8 * nodeWidth, z), 0.0f, 
					PICK_MERGE_PATTERN_COLS, stitchesTexture, cell, black, darkGray);
			}

			drawTexButton(Vec3f(cellTopLeftPos.x - 0.5f * colWidth, myMax.y - 0.2 * nodeWidth, z), 180.0f, 
				PICK_SPLIT_PATTERN_COL, scissorTexture, cell, black, darkGray);
			drawTexButton(Vec3f(cellTopLeftPos.x - 0.5f * colWidth, myMin.y + 0.2 * nodeWidth, z), 0.0f, 
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

			drawCellSizer(Vec3f(myMin.x + 0.2 * nodeWidth, cellTopLeftPos.y, z), 90.0f);
			drawCellSizer(Vec3f(myMax.x - 0.2 * nodeWidth, cellTopLeftPos.y, z), 90.0f);
			drawTexButton(Vec3f(myMin.x + 0.8 * nodeWidth, cellTopLeftPos.y, z), 90.0f, 
				PICK_MERGE_PATTERN_ROWS, stitchesTexture, cell, black, darkGray);
			drawTexButton(Vec3f(myMax.x - 0.8 * nodeWidth, cellTopLeftPos.y, z), 90.0f, 
				PICK_MERGE_PATTERN_ROWS, stitchesTexture, cell, black, darkGray);
		}

		drawTexButton(Vec3f(myMax.x - 0.2 * nodeWidth, cellTopLeftPos.y + 0.5f * rowHeight, z), 90.0f, 
			PICK_SPLIT_PATTERN_ROW, scissorTexture, cell, black, darkGray);
		drawTexButton(Vec3f(myMin.x + 0.2 * nodeWidth, cellTopLeftPos.y + 0.5f * rowHeight, z), -90.0f, 
			PICK_SPLIT_PATTERN_ROW, scissorTexture, cell, black, darkGray);

		if (hoverType == PICK_SPLIT_PATTERN_ROW && hoverSecondary == cell->holder && !pickingMode) {
			borderMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
			addMeshVertex(&borderMesh, Vec3f(myMin.x, cellTopLeftPos.y + 0.5 * rowHeight, gridZ), darkGray);
			addMeshVertex(&borderMesh, Vec3f(myMax.x, cellTopLeftPos.y + 0.5 * rowHeight, gridZ), darkGray);
			borderMesh.draw(GL_LINES);
		}
	}
	if (pickingMode)
		glLineWidth(1.0);
	setpickingdrawfocus(view, holder, 0);
	if (!pickingMode) {
		mesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
		Mesh gridPointsMesh;
		gridPointsMesh.init(0, MESH_POSITION | MESH_DIFFUSE4, MESH_DYNAMIC_DRAW);
		Vec4f lightGray(0.7f, 0.7f, 0.7f, 1.0f);
		AStarCell minCell = grid->getCellFromLoc(myModelMin + Vec3(0.5 * nodeWidth, 0.5 * nodeWidth, 0.0));
		AStarCell maxCell = grid->getCellFromLoc(myModelMax + Vec3(-0.5 * nodeWidth, -0.5 * nodeWidth, 0.0));
		Vec3f offset(-b_spatialx, -b_spatialy, -b_spatialz);
		for (AStarCell cell = minCell; cell.row <= maxCell.row; cell.row++) {
			for (cell.col = minCell.col; cell.col <= maxCell.col; cell.col++) {
				Vec3f modelPos = Vec3f(grid->getLocFromCell(cell));
				modelPos.z = gridZ;
				Vec3f localPos = modelPos + offset;
				addMeshVertex(&gridPointsMesh, localPos, lightGray);
				PatternCell* patternCell = getPatternCell(Vec3(modelPos));
				if (patternCell) {
					if (patternCell->canGoUp) {
						addMeshVertex(&mesh, localPos, lightGray);
						addMeshVertex(&mesh, localPos + Vec3f(0.0f, 0.2 * nodeWidth, 0.0f), lightGray);
					}
					if (patternCell->canGoDown) {
						addMeshVertex(&mesh, localPos, lightGray);
						addMeshVertex(&mesh, localPos + Vec3f(0.0f, -0.2 * nodeWidth, 0.0f), lightGray);
					}
					if (patternCell->canGoRight) {
						addMeshVertex(&mesh, localPos, lightGray);
						addMeshVertex(&mesh, localPos + Vec3f(0.2 * nodeWidth, 0.0f, 0.0f), lightGray);
					}
					if (patternCell->canGoLeft) {
						addMeshVertex(&mesh, localPos, lightGray);
						addMeshVertex(&mesh, localPos + Vec3f(-0.2 * nodeWidth, 0.0f, 0.0f), lightGray);
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
	meshOffset = 0;
	nrVerts = 0;

	Vec3 myMin, myMax;
	if (!getBoundingBox(myMin, myMax, true))
		return;

	double width = myMax.x - myMin.x;
	double height = myMax.y - myMin.y;

	meshOffset = barrierMesh->numVerts;

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
		addMeshTriangle(barrierMesh, bottomRight, topLeft, bottomLeft, black, &nrVerts);
		addMeshTriangle(barrierMesh, bottomRight, topRight, topLeft, black, &nrVerts);
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
			if (width < nodeWidth / 2) {
				if (activePoint == bottomLeft)
					activePoint->x = topRight->x - nodeWidth / 2;
				else
					activePoint->x = bottomLeft->x + nodeWidth / 2;
			}
			if (height < nodeWidth / 2) {
				if (activePoint == bottomLeft)
					activePoint->y = topRight->y - nodeWidth / 2;
				else
					activePoint->y = bottomLeft->y + nodeWidth / 2;
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
				case PICK_SPLIT_PATTERN_ROW: splitPatternRow(cell->holder->parent->rank, view); break;
				case PICK_MERGE_PATTERN_COLS: mergePatternCols(cell->holder->rank, view); break;
				case PICK_MERGE_PATTERN_ROWS: mergePatternRows(cell->holder->parent->rank, view); break;
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

	if (clickCode == RIGHT_RELEASE) {
		// Right click -> abort barrier creation
		if (mode & Barrier::CREATE) {
			destroyobject(holder);
		}
	}

	return 1;
}

double Barrier::onClick(treenode view, int clickCode)
{
	AStarNavigator* nav = navigator;
	isMeshDirty = true;
	Vec3 pos(cursorinfo(view, 2, 1, 1), cursorinfo(view, 2, 2, 1), cursorinfo(view, 2, 3, 1));
	return onClick(view, clickCode, pos);
}

double Barrier::onMouseMove(treenode view, Vec3& pos, Vec3& diff)
{
	int pickType = getpickingdrawfocus(view, PICK_TYPE, PICK_PRESSED);
	treenode pointNode = tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_PRESSED));
	bool isPointEdit = pointNode != nullptr 
		&& (pickType == PICK_POINT || pickType == PICK_ARROW_LEFT || pickType == PICK_ARROW_RIGHT 
			|| pickType == PICK_ARROW_TOP || pickType == PICK_ARROW_BOTTOM);
	isMeshDirty = true;
	if (isPointEdit) {
		Point* activePoint = pointNode->objectAs(Point);
		Point* activeXPoint = activePoint, *activeYPoint = activePoint;
		if (pickType == PICK_POINT) {
			Vec3 min, max;
			getBoundingBox(min, max);
			Vec3 center = (min + max) * 0.5;
			if (pos.x < center.x)
				activeXPoint = pointList[0];
			else activeXPoint = pointList[1];
			if (pos.y < center.y)
				activeYPoint = pointList[0];
			else activeYPoint = pointList[1];
			//diff.x = pos.x - activeXPoint->x;
			//diff.y = pos.y - activeYPoint->y;
		}
		if (pickType == PICK_POINT || pickType == PICK_ARROW_LEFT || pickType == PICK_ARROW_RIGHT) {
			double oldXSize = fabs(pointList[1]->x - pointList[0]->x);
			activeXPoint->x += diff.x;
			scalePatternColsOnSizeChange(oldXSize, fabs(pointList[1]->x - pointList[0]->x));
		}
		if (pickType == PICK_POINT || pickType == PICK_ARROW_TOP || pickType == PICK_ARROW_BOTTOM) {
			double oldYSize = fabs(pointList[1]->y - pointList[0]->y);
			activeYPoint->y += diff.y;
			scalePatternRowsOnSizeChange(oldYSize, fabs(pointList[1]->y - pointList[0]->y));
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
}

double Barrier::onDrag(treenode view)
{
	double dx = draginfo(DRAG_INFO_DX);
	double dy = draginfo(DRAG_INFO_DY);
	double dz = draginfo(DRAG_INFO_DZ);
	double returnVal = onMouseMove(view, Vec3(cursorinfo(view, 2, 1, 1), cursorinfo(view, 2, 2, 1), 0), Vec3(dx, dy, dz));
	int pickType = getpickingdrawfocus(view, PICK_TYPE, PICK_PRESSED);
	if (pickType != 0) {
		switch (pickType) {
		case PICK_PATTERN_SIZER_X: {
			dragPatternCellSizer(tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_PRESSED))->objectAs(PatternCell), dx, true);
			break;
		}
		case PICK_PATTERN_SIZER_Y: {
			dragPatternCellSizer(tonode(getpickingdrawfocus(view, PICK_SECONDARY_OBJECT, PICK_PRESSED))->objectAs(PatternCell), -dy, false);
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
	float factor, units;
	bool polyOffsetFill = glIsEnabled(GL_POLYGON_OFFSET_FILL);
	glGetFloatv(GL_POLYGON_OFFSET_FACTOR, &factor);
	glGetFloatv(GL_POLYGON_OFFSET_UNITS, &units);
	fglEnable(GL_POLYGON_OFFSET_FILL);

	double vpRadius = get(viewpointradius(view));
	if (get(viewprojectiontype(view)) == 1)
		vpRadius = maxof(get(spatialsx(view)), get(spatialsy(view))) / get(viewmagnification(view));
	double offset = max(-1, -50 / (vpRadius * getmodelunit(LENGTH_MULTIPLE)));

	glPolygonOffset(offset - 0.025, -5);

	if (isMeshDirty) {
		mesh.init(0, MESH_POSITION | MESH_DIFFUSE4);
		addVertices(view, &mesh, 0.0f, Basic);
		isMeshDirty = false;
	}

	setpickingdrawfocus(view, holder, 0, 0, OVERRIDE_DRAW_ALL);
	fglDisable(GL_TEXTURE_2D);
	fglDisable(GL_LIGHTING);

	fglRotate(-90.0f, 1.0f, 0.0f, 0.0f);
	fglScale(1.0 / b_spatialsx, 1.0 / b_spatialsy, 1.0 / b_spatialsz);
	if (holder->up == navigator->holder) {
		fglTranslate(-navigator->b_spatialx, -navigator->b_spatialy, -navigator->b_spatialz);
	}

	int pickingMode = getpickingmode(view);
	if (pickingMode) {
		drawPickObjects(view);
	}

	treenode selObj = selectedobject(view);
	treenode hoverObj = tonode(getpickingdrawfocus(view, PICK_OBJECT, PICK_HOVERED));
	if (selObj == holder || hoverObj == holder || switch_selected(holder, -1)) {
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

		if (selObj == holder) {
			drawManipulationHandles(view);
		}
	}
	
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
	AStarNavigator* nav = navigator;
	isMeshDirty = true;

	// Stop barrier creation
	if (mode & Barrier::CREATE) {
		if (pointList.size() > 2) {
			removePoint(min(activePointIndex, pointList.size() - 1));
			activePointIndex = pointList.size();
			mode = 0;
		}
		else
			destroyobject(holder);
	}
	else {
		// Fix active point index
		if (activePointIndex > pointList.size())
			activePointIndex = pointList.size();
	}
	return 0.0;
}

double Barrier::onCreate(double dropx, double dropy, double dropz, int iscopy)
{
	assertNavigator();

	if (holder->up == model()) {
		holder->up = navigator->holder;
	}
	if (isBasicBarrier())
		assertValidPatternTable();
	return 0.0;
}

void Barrier::updateSpatialsToEncompassPoints()
{
	Vec3 min, max;
	getLocalBoundingBox(min, max);
	node_b_spatialsx->value = max.x - min.x;
	node_b_spatialsy->value = max.y - min.y;
	if (min.x == 0.0 && max.y == 0.0)
		return;
	node_b_spatialx->value += min.x;
	node_b_spatialy->value += max.y;

	for (Point* point : pointList) {
		point->holder->find("x")->value -= min.x;
		point->holder->find("y")->value -= max.y;
	}
}

void Barrier::addPoint(const Vec3& pos)
{
	pointList.add(new Point(pos.x, pos.y, pos.z));
}

void Barrier::removePoint(int pointIndex)
{
	if (pointIndex >= pointList.size())
		return;

	pointList.remove(pointIndex);
}

void Barrier::swapPoints(int index1, int index2)
{
	int maxIndex = max(index1, index2);
	int minIndex = min(index1, index2);

	if (maxIndex >= pointList.size() || minIndex < 0)
		return;

	pointList.swap(index1, index2);
}

Vec3 Barrier::getPointCoords(int pointIndex)
{
	if (pointIndex >= pointList.size())
		throw "Invalid Barrier point index";

	Point* point = pointList[pointIndex];
	return Vec3(point->x, point->y, point->z);
}

ASTAR_FUNCTION Variant Barrier::getPointCoord(FLEXSIMINTERFACE)
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

bool Barrier::setPointCoords(int pointIndex, const Vec3& point)
{
	if (pointIndex >= pointList.size())
		return false;

	Vec2 oldSize;
	if (pointList.size() > 1 && isBasicBarrier()) {
		oldSize = Vec2(pointList[1]->x - pointList[0]->x, pointList[1]->y - pointList[0]->y);
	}

	pointList[pointIndex]->x = point.x;
	pointList[pointIndex]->y = point.y;
	pointList[pointIndex]->z = point.z;

	if (pointList.size() > 1 && isBasicBarrier()) {
		Vec2 newSize(pointList[1]->x - pointList[0]->x, pointList[1]->y - pointList[0]->y);
		if (oldSize.x != newSize.x)
			scalePatternColsOnSizeChange(oldSize.x, newSize.x);
		if (oldSize.y != newSize.y)
			scalePatternRowsOnSizeChange(oldSize.y, newSize.y);
	}

	return true;
}

void Barrier::addPathVertices(Mesh* barrierMesh, float z, const Vec4f& color, DrawStyle drawStyle)
{
	float theColor[4] = { min(1.0f, color.r + 0.2f), min(1.0f, color.g + 0.2f), min(1.0f, color.b + 0.2f), color.a };
	float lightGray[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	if (drawStyle == Highlighted) {
		theColor[0] = color.r;
		theColor[1] = color.g;
		theColor[2] = color.b;
		lightGray[0] = 0.6f;
		lightGray[1] = 0.6f;
		lightGray[2] = 0.6f;
		z += 0.001 / getmodelunit(LENGTH_MULTIPLE);
	}
	else if (drawStyle == Hovered) {
		theColor[0] = min(1.0f, color.r + 0.1f);
		theColor[1] = min(1.0f, color.g + 0.1f);
		theColor[2] = min(1.0f, color.b + 0.1f);
		lightGray[0] = 0.7f;
		lightGray[1] = 0.7f;
		lightGray[2] = 0.7f;
		z += 0.002 / getmodelunit(LENGTH_MULTIPLE);
	}
	nrVerts = 0;
	meshOffset = barrierMesh->numVerts;

	// Add circles at each node
	float radius = nodeWidth * 0.15;
	for (int i = 0; i < pointList.size(); i++) {
		pointList[i]->addVertices(barrierMesh, radius, lightGray, z, &nrVerts);
	}

	// Draw a series of triangles
	float maxTriangleWidth = nodeWidth;
	float distToRect = 0;// 0.4 * nodeWidth;
	float distToCorner = sqrt(distToRect * distToRect + radius * radius);
	float height = 2 * radius;
	bool isBridge = toBridge() ? true : false;
	float dTheta = atan2(radius, distToRect);

	for (int i = 0; i < pointList.size() - 1; i++) {
		Point* point = pointList[i];
		Point* next = pointList[i + 1];
		float pointZ = isBridge ? point->z + z : z;
		float nextZ = isBridge ? next->z + z : z;

		float dx = next->x - point->x;
		float dy = next->y - point->y;
		float dz = pointZ - nextZ;
		float theta = atan2(dy, dx);

		float length = sqrt(dx * dx + dy * dy) - 2 * distToRect;
		if (length <= 0)
			continue;

		float sinTheta = sin(theta);
		float cosTheta = cos(theta);
		// Find how many will fit, and stretch them to fit.
		int numTriangles = (int)(length / maxTriangleWidth);
		if (numTriangles < 1) {
			numTriangles = 1;
		}
		float triangleWidth = length / numTriangles;
		float tw = triangleWidth;

		// Use the bottomleft corner of the rectangle to get every other corner
		float bottomLeft[3] = { distToCorner * cos(theta - dTheta) + (float)point->x,
			distToCorner * sin(theta - dTheta) + (float)point->y, pointZ };

		float topLeft[3] = { bottomLeft[0] - height * sinTheta,
			bottomLeft[1] + height * cosTheta, pointZ };

		float pos0[3] = { 0.0f, 0.0f, pointZ };
		float pos1[3] = { 0.0f, 0.0f, pointZ };
		float pos2[3] = { 0.0f, 0.0f, pointZ };

		for (int j = 0; j < numTriangles; j++) {

#define ROTATE_POINT(rx, ry, x, y) \
	rx = x * cosTheta - y * sinTheta;\
	ry = x * sinTheta + y * cosTheta;

#define ABV(pos, color)  {\
	int vertName = barrierMesh->addVertex();\
	nrVerts++;\
	barrierMesh->setVertexAttrib(vertName, MESH_DIFFUSE4, color);\
	barrierMesh->setVertexAttrib(vertName, MESH_POSITION, pos);\
			}

#define ABT(pos1, pos2, pos3, dark, color) ABV(pos1, color) ABV(pos2, dark) ABV(pos3, dark)


			float triangleTipX = (j + 1) * tw;
			float triangleTipY = height / 2.0;
			float triangleTopX = j * tw;
			float triangleTopY = height;
			float triangleBottomX = triangleTopX;
			float triangleBottomY = 0;

			float rtX, rtY;

			ROTATE_POINT(rtX, rtY, triangleTipX, triangleTipY);
			triangleTipX = rtX + bottomLeft[0];
			triangleTipY = rtY + bottomLeft[1];

			ROTATE_POINT(rtX, rtY, triangleTopX, triangleTopY);
			triangleTopX = rtX + bottomLeft[0];
			triangleTopY = rtY + bottomLeft[1];

			ROTATE_POINT(rtX, rtY, triangleBottomX, triangleBottomY);
			triangleBottomX = rtX + bottomLeft[0];
			triangleBottomY = rtY + bottomLeft[1];

			pos0[0] = triangleTipX;
			pos0[1] = triangleTipY;
			pos0[2] = pointZ + dz * (j + 1) / numTriangles;
			pos1[0] = triangleTopX;
			pos1[1] = triangleTopY;
			pos1[2] = pointZ + dz * j / numTriangles;
			pos2[0] = triangleBottomX;
			pos2[1] = triangleBottomY;
			pos2[2] = pointZ + dz * j / numTriangles;

			ABT(pos0, pos1, pos2, lightGray, theColor);
		}
	}
#undef ABT
#undef ABV
#undef ROTATE_POINT
}

void Barrier::onReset(AStarNavigator * nav)
{
	Vec3 min, max;
	getBoundingBox(min, max);
	nodeWidth = nav->getGrid(min)->nodeWidth;
	isMeshDirty = true;
	if (isBasicBarrier()) {
		assertValidPatternTable();
	}
	conditionalBarrierChanges = TemporaryBarrier(nav);
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

void Barrier::scalePatternRowsOnSizeChange(double oldYSize, double newYSize)
{	
	Table patterns(patternTable);
	if (patterns.numRows == 1) {
		patterns.cell(1, 1)->objectAs(PatternCell)->height = maxof(0.00000001, newYSize);
	} else {
		double scaleFactor = newYSize / oldYSize;

		for (int row = 1; row <= patterns.numRows; row++) {
			PatternCell* cell = patterns.cell(row, 1)->objectAs(PatternCell);
			if (oldYSize != 0)
				cell->height *= scaleFactor;
			else cell->height = newYSize / patterns.numRows;
		}
	}
}

void Barrier::scalePatternColsOnSizeChange(double oldXSize, double newXSize)
{
	Table patterns(patternTable);
	if (patterns.numCols == 1) {
		patterns.cell(1, 1)->objectAs(PatternCell)->width = maxof(0.00000001, newXSize);
	} else {
		double scaleFactor = newXSize / oldXSize;
		for (int col = 1; col <= patterns.numCols; col++) {
			PatternCell* cell = patterns.cell(1, col)->objectAs(PatternCell);
			if (oldXSize != 0)
				cell->width *= scaleFactor;
			else cell->width = newXSize / patterns.numCols;
		}
	}
}

Barrier::PatternCell * Barrier::getPatternCell(Vec3 & modelPos)
{
	Vec3 myMin, myMax;
	if (!getBoundingBox(myMin, myMax))
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

Barrier::PatternCell* Barrier::getPatternCell(const AStarCell& cell) 
{ 
	return getPatternCell(navigator->getLocFromCell(cell)); 
}

void Barrier::dragPatternCellSizer(PatternCell * cell, double diff, bool isXSizer)
{
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
