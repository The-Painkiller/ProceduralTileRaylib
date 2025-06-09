#pragma once
#include "GlobalHeader.h"
#include "BiasManager.h"
#include <vector>
#include <algorithm>

/// <summary>
/// Base tile class. Every tile on the screen is basically just this class' instance with a fixed set of properties and methods.
/// </summary>
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
	void SetIterationFlag(const bool isIterated);
	TerrainTileType GetTerrainTileType();
	int GetEntropyCount();
	int GetValidNeighbourCount();
	bool IsIteratedOver();
	TerrainTileType GetEntropy(const int index);
	TerrainTileType GetValidNeighbour(const int index);
	std::vector<TerrainTileType>& GetValidNeighbours();

	/// This method acts as a way to to an intersection between the entropy of the current tile and the list of valid neighbours of the adjacent tile.
	void CollapseEntropy(const std::vector<TerrainTileType>& validNeighourListOfIncomingTile);

private:
	TerrainTileType _terrainTileType = TerrainTileType::InvalidTileType;
	unsigned int _tileSize = 0;
	std::vector<TerrainTileType> _tileEntropies;
	std::vector<TerrainTileType> _validNeighbours;
	bool _isIteratedOver = false;
};