#include "TileManager.h"

TileManager::TileManager(int gridSizeX, int gridSizeY)
{
	_gridSizeX = gridSizeX;
	_gridSizeY = gridSizeY;
	_tiles.assign(_gridSizeX, std::vector<std::unique_ptr<BaseTile>>(_gridSizeY, std::unique_ptr<BaseTile>(new BaseTile(TerrainTileType::Grass, _gridSizeX))));
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