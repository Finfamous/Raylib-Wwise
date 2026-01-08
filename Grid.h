#pragma once

#include <vector>
#include <raylib.h>

class WwiseManager;

class Grid 
{
public:
	Grid(WwiseManager& audio);
	void Initialise();
	int GridDimensions[20][10];
	void Print();
	void Draw();
	int ClearFullRows();
	bool IsCellOutside(int Row, int Column);
	bool IsCellEmpty(int Row, int Column);

private:
	WwiseManager& mAudio;
	bool IsRowFull(int Row);
	void ClearRow(int Row);
	void MoveRowDown(int Row, int NumRows);
	int NumRows;
	int NumColumns;
	int CellSize;
	std::vector<Color> Colors;
};