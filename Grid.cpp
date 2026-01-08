#include "Grid.h"
#include <iostream>
#include "Colors.h"
#include "WwiseManager.h"

Grid::Grid(WwiseManager& audio) : mAudio(audio)
{
	NumRows = 20;
	NumColumns = 10;
	CellSize = 30;
	Initialise();
	Colors = GetCellColours();
}

void Grid::Initialise()
{
	for (int Row = 0; Row < NumRows; Row++)
	{
		for (int Column = 0; Column < NumColumns; Column++)
		{
			GridDimensions[Row][Column] = 0;
		}
	}
}

void Grid::Print()
{
	for (int Row = 0; Row < NumRows; Row++)
	{
		for (int Column = 0; Column < NumColumns; Column++)
		{
			//std::cout << GridDimensions[Row][Column] << " ";
		}
		std::cout << std::endl;
	}
}



void Grid::Draw()
{
	for (int Row = 0; Row < NumRows; Row++)
	{
		for (int Column = 0; Column < NumColumns; Column++)
		{
			int CellValue = GridDimensions[Row][Column];
			DrawRectangle(Column * CellSize+1, Row * CellSize+1, CellSize-1, CellSize-1, Colors[CellValue]);
		}
	}
}

int Grid::ClearFullRows()
{
	int Completed = 0;
	for (int Row = NumRows - 1; Row >= 0; Row--)
	{
		if (IsRowFull(Row))
		{
			ClearRow(Row);
			Completed++;
		}
		else if (Completed > 0)
		{
			MoveRowDown(Row, Completed);
		}
	}
	return Completed;
}

bool Grid::IsCellOutside(int Row, int Column)
{
	if (Row >= 0 && Row < NumRows && Column >= 0 && Column < NumColumns)
	{
		return false;
	}
	return true;
	
}

bool Grid::IsCellEmpty(int Row, int Column)
{
	if (GridDimensions[Row][Column] == 0)
	{
		return true;
	}
	return false;
}

bool Grid::IsRowFull(int Row)
{
	for (int Column = 0; Column < NumColumns; Column++)
	{
		if (GridDimensions[Row][Column] == 0)
		{
			return false;
		}
	}
	return true;
}

void Grid::ClearRow(int Row)
{
	mAudio.CustomPostEvent("Play_Chords");
	for (int Column = 0; Column < NumColumns; Column++)
	{
		if (GridDimensions[Row][Column] == 0)
		{
			GridDimensions[Row][Column] = 0;
		}
			
	
	}
}

void Grid::MoveRowDown(int Row, int NumRows)
{
	for (int Column = 0; Column < NumColumns; Column++)
	{
		GridDimensions[Row + NumRows][Column] = GridDimensions[Row][Column];
		GridDimensions[Row][Column] = 0;
	}
}
