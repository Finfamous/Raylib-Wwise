#include "Game.h"
#include <random>
#include "WwiseManager.h"


Game::Game(WwiseManager& audio) : mAudio(audio) , grid(audio)
{
	Blocks = GetAllBlocks();
	CurrentBlock = GetRandomBlock();
	NextBlock = GetRandomBlock();
}

Block Game::GetRandomBlock()
{
	if (Blocks.empty())
	{
		Blocks = GetAllBlocks();
	}
	int RandomIndex = rand() % Blocks.size();
	Block block = Blocks[RandomIndex];
	Blocks.erase(Blocks.begin() + RandomIndex);
	return block;
}

std::vector<Block> Game::GetAllBlocks() 
{
	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::Draw()
{
	grid.Draw();
	CurrentBlock.Draw();

}

void Game::HandleInput()
{
	int KeyPressed = GetKeyPressed();
	switch (KeyPressed)
	{
		case KEY_LEFT:
			MoveBlockLeft();
		break;

		case KEY_RIGHT:
			MoveBlockRight();
		break;

		case KEY_DOWN:
			MoveBlockDown();
		break;
		case KEY_UP:
			RotateBlock();
			break;

	}
}

void Game::MoveBlockLeft()
{
	CurrentBlock.Move(0, -1);
	mAudio.CustomPostEvent("Play_Connected_Click");
	if (IsBlockOutside() || BlockFits() == false)
	{
		CurrentBlock.Move(0, 1);
	}
}

void Game::MoveBlockRight()
{
	CurrentBlock.Move(0, 1);
	mAudio.CustomPostEvent("Play_Connected_Click");
	if (IsBlockOutside() || BlockFits() == false)
	{
		CurrentBlock.Move(0, -1);
	}
}

void Game::MoveBlockDown()
{
	CurrentBlock.Move(1, 0);
	if (IsBlockOutside() || BlockFits() == false)
	{
		CurrentBlock.Move(-1, 0);
		LockBlock();
	}
}

bool Game::IsBlockOutside()
{
	std::vector<Position> Tiles = CurrentBlock.GetCellPositions();
	for (Position Item : Tiles)
	{
		if (grid.IsCellOutside(Item.Row, Item.Column))
		{
			return true;
		}
	}
	return false;
}

void Game::LockBlock()
{
	std::vector<Position> Tiles = CurrentBlock.GetCellPositions();
	mAudio.CustomPostEvent("Play_Connected_Click");
	for (Position Item : Tiles)
	{
			grid.GridDimensions[Item.Row][Item.Column] = CurrentBlock.id;
	}
	CurrentBlock = NextBlock;
	NextBlock = GetRandomBlock();
	grid.ClearFullRows();
}

bool Game::BlockFits()
{
	std::vector<Position> Tiles = CurrentBlock.GetCellPositions();
	for (Position Item : Tiles)
	{
		if (grid.IsCellEmpty(Item.Row, Item.Column) == false)
		{
			return false;
		}
	}
	return true;
}



void Game::RotateBlock()
{
	CurrentBlock.Rotate();
	mAudio.CustomPostEvent("Play_Notes");
	if (IsBlockOutside() || BlockFits() == false)
	{
		CurrentBlock.UndoRotation();
	}
}
