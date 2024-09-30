#pragma once
#include "GlobalHeader.h"
#include <vector>

class BaseTile
{
public:
	BaseTile() = delete;
	BaseTile(TerrainTileType tileType, unsigned int size);
	~BaseTile();

	void SetPossibilities();
	void SetPossibilities(const TerrainTileType types[]);
	void RemovePossibilityIfExists(const TerrainTileType type);
	void ForceSetTile(const TerrainTileType type, char* texturePath, const unsigned size);
	char* GetTileTexturePath();

private:
	TerrainTileType _terrainTileType = TerrainTileType::InvalidTileType;
	unsigned int _tileSize = 0;
	std::vector<TerrainTileType> _tilePossibilities;
	char* _tileTexturePath = nullptr;
};