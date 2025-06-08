#pragma once

#include "BaseTile.h"
#include <memory>
#include <Vector2.hpp>
#include "DataParser.h"
#include "Utils.h"

/// <summary>
/// TileManager manages the array of tiles along with their BaseTile class attributes.
/// </summary>
class TileManager
{
public:
	TileManager() = delete;
	explicit TileManager(int gridSizeX, int gridSizeY, std::shared_ptr<DataParser>& dataParser);
	~TileManager();

	void InitializeTileGrid();
	void Obervation(const Vector2 tileLocation, BaseTile& neighbourTileWithEntropyOne, const TraverseDirection direction);
	std::vector<std::vector<std::shared_ptr<BaseTile>>>& GetTileArray();
	void ForceTileEntropy(const Vector2 tileLocation, const TerrainTileType type, const std::vector<TerrainTileType> validNeighbours);
	void ClearTileIterations();
	TerrainTileType CollapseEntropyInDirection(const Vector2& tileLocation, BaseTile& currentTile, int currentTileEntropy, const TraverseDirection direction);

private:
	int _gridSizeX = 0;
	int _gridSizeY = 0;
	std::vector<std::vector<std::shared_ptr<BaseTile>>> _tiles;
	std::vector<Vector2> _tilesWithOneEntropy;
	std::shared_ptr<DataParser> _dataParser;
};