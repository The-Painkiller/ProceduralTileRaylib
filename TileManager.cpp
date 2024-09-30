#include "TileManager.h"

TileManager::TileManager(Vector2 gridSize)
{
	_gridSize = gridSize;
	_tiles.assign(_gridSize.X, std::vector<std::unique_ptr<BaseTile>>(_gridSize.Y));
}

TileManager::~TileManager()
{
	_gridSize.X = 0;
	_gridSize.Y = 0;
}

void TileManager::InitializeTileGrid()
{
	for (int i = 0; i < _gridSize.X; i++)
	{
		for (int j = 0; j < _gridSize.Y; j++)
		{
			_tiles[i][j].get()->SetPossibilities();
		}
	}
}