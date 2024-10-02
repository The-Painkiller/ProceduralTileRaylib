#include "TileManager.h"

TileManager::TileManager(int gridSizeX, int gridSizeY)
{
	_gridSizeX = gridSizeX;
	_gridSizeY = gridSizeY;
}

TileManager::~TileManager()
{
	_gridSizeX = 0;
	_gridSizeY = 0;
}

void TileManager::InitializeTileGrid()
{
	for (int i = 0; i < _gridSizeX; i++)
	{
		for (int j = 0; j < _gridSizeY; j++)
		{
			_tiles[i][j].get()->SetPossibilities();
		}
	}
}