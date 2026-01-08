#pragma once
#include "Grid.h"
#include "Blocks.cpp"

class WwiseManager;

class Game
{
public: 
	Game(WwiseManager& audio);
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void Draw();
	void HandleInput();
	void MoveBlockLeft();
	void MoveBlockRight();
	void MoveBlockDown();
	Grid grid; 

private: 

	WwiseManager& mAudio;

	bool IsBlockOutside();
	void LockBlock();
	bool BlockFits();
	std::vector<Block> Blocks;
	Block CurrentBlock;
	Block NextBlock;
	void RotateBlock();

};