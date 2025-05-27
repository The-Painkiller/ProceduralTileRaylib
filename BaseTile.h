#pragma once
#include "GlobalHeader.h"
#include <vector>
#include <algorithm>

class BaseTile
{
public:
	BaseTile() = default;
	BaseTile(TerrainTileType tileType, unsigned int size);
	~BaseTile();

	void SetEntropy();
	void SetEntropy(const TerrainTileType types[]);
	void SetValidNeighbours(const std::vector<TerrainTileType> validNeighbours);
	void RemoveEntropyIfExists(const TerrainTileType type);
	void ForceSetTile(const TerrainTileType type, const unsigned size, const std::vector<TerrainTileType>& validNeighbours);
	void SetIterationFlag(bool isIterated);
	TerrainTileType GetTerrainTileType();
	int GetEntropyCount();
	int GetValidNeighbourCount();
	bool IsIteratedOver();
	TerrainTileType GetEntropy(int index);
	TerrainTileType GetValidNeighbour(int index);
	std::vector<TerrainTileType>& GetValidNeighbours();
	void UpdateEntropy(const std::vector<TerrainTileType>& validNeighourListOfIncomingTile);

private:
	TerrainTileType _terrainTileType = TerrainTileType::InvalidTileType;
	unsigned int _tileSize = 0;
	std::vector<TerrainTileType> _tileEntropies;
	std::vector<TerrainTileType> _validNeighbours;
	bool _isIteratedOver = false;
};