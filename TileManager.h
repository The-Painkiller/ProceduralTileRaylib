#pragma once

#include "BaseTile.h"
#include <memory>
#include <Vector2.hpp>
#include "DataParser.h"

class TileManager
{
public:
	TileManager() = delete;
	explicit TileManager(int gridSizeX, int gridSizeY, std::shared_ptr<DataParser>& dataParser);
	~TileManager();

	void InitializeTileGrid();
	void Obervation(const Vector2 tileLocation, BaseTile& neighbourTileWithEntropyOne);
	std::vector<std::vector<std::shared_ptr<BaseTile>>>& GetTileArray();
	void ForceTileEntropy(const Vector2 tileLocation, const TerrainTileType type, const std::vector<TerrainTileType> validNeighbours);
	void CalculateEntropies();
	void CollapseEntropies(const Vector2 tileLocation, const std::vector<TerrainTileType> entropies);


private:
	int _gridSizeX = 0;
	int _gridSizeY = 0;
	std::vector<std::vector<std::shared_ptr<BaseTile>>> _tiles;
	std::vector<Vector2> _tilesWithOneEntropy;
	std::shared_ptr<DataParser> _dataParser;
};