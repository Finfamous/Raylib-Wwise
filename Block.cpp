#include "Block.h"
#include "Blocks.cpp"

Block::Block()
{
	CellSize = 30;
	RotationState = 0;
	Colors = GetCellColours();
	RowOffset = 0;
	ColumnOffset = 0;
}

void Block::Draw()
{
	std::vector<Position> Tiles = GetCellPositions();
	for (Position Item : Tiles)
	{
		DrawRectangle(Item.Column * CellSize + 1, Item.Row * CellSize + 1, CellSize - 1, CellSize - 1, Colors[id]);
	}
}

void Block::Move(int Rows, int Columns)
{
	RowOffset += Rows;
	ColumnOffset += Columns;
}

void Block::Rotate()
{
	RotationState++;
	if (RotationState == Cells.size())
	{
		RotationState = 0;
	}
}

void Block::UndoRotation()
{
	RotationState--;
	if (RotationState == -1)
	{
		RotationState = Cells.size() - 1;
	}
}

std::vector<Position> Block::GetCellPositions()
{
	std::vector<Position> Tiles = Cells[RotationState];
	std::vector<Position> MovedTiles;
	for (Position Item : Tiles)
	{
		Position NewPosition = Position(Item.Row + RowOffset, Item.Column + ColumnOffset);
		MovedTiles.push_back(NewPosition);
	}
	return MovedTiles;
}


