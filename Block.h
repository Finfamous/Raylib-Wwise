#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "Colors.h"

class Block
{
public:
	Block();
	int id;
	std::map<int, std::vector<Position>> Cells;
	void Draw();
	void Move(int Rows, int Columns);
	void Rotate();
	void UndoRotation();
	std::vector<Position> GetCellPositions();

private:
	int CellSize;
	int RotationState;
	std::vector<Color> Colors;
	int RowOffset;
	int ColumnOffset;
};