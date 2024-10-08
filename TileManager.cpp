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
	_tiles.clear();
}

void TileManager::InitializeTileGrid()
{
	for (int i = 0; i < _gridSizeX; i++)
	{
		_tiles.push_back(std::vector<std::shared_ptr<BaseTile>>(_gridSizeY));
		for (int j = 0; j < _gridSizeY; j++)
		{
			_tiles[i][j] = std::shared_ptr<BaseTile>(new BaseTile(Grass, 256));
			_tiles[i][j].get()->SetPossibilities();
		}
	}
}

std::vector<std::vector<std::shared_ptr<BaseTile>>>& TileManager::GetTileArray()
{
	return _tiles;
}
