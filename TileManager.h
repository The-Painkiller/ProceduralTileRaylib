#pragma once

#include "BaseTile.h"
#include <memory>

class TileManager
{
public:
	TileManager() = delete;
	explicit TileManager(int gridSizeX, int gridSizeY);
	~TileManager();

	void InitializeTileGrid();
	std::vector<std::vector<std::shared_ptr<BaseTile>>>& GetTileArray();

private:
	int _gridSizeX = 0;
	int _gridSizeY = 0;
	std::vector<std::vector<std::shared_ptr<BaseTile>>> _tiles;
};