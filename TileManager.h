#pragma once

#include "BaseTile.h"
#include <memory>

class TileManager
{
public:
	TileManager() = delete;
	explicit TileManager(VectorCoordinates2 gridSize);
	~TileManager();

	void InitializeTileGrid();

private:
	VectorCoordinates2 _gridSize;
	std::vector<std::vector<std::unique_ptr<BaseTile>>> _tiles;
};