#pragma once
#include "GlobalHeader.h"
#include <vector>

class BaseTile
{
public:
	BaseTile() = default;
	BaseTile(TerrainTileType tileType, unsigned int size);
	~BaseTile();

	void SetPossibilities();
	void SetPossibilities(const TerrainTileType types[]);
	void RemovePossibilityIfExists(const TerrainTileType type);
	void ForceSetTile(const TerrainTileType type, const unsigned size);
	void SetTransitionFlag(bool isTransitionTile);
	TerrainTileType GetTerrainTileType();
	bool IsTransitionTile();

private:
	TerrainTileType _terrainTileType = TerrainTileType::InvalidTileType;
	unsigned int _tileSize = 0;
	std::vector<TerrainTileType> _tilePossibilities;
	bool _isTransitionTile = false;
};