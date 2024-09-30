#include "BaseTile.h"

BaseTile::BaseTile(TerrainTileType tileType, unsigned int size)
{
	_terrainTileType = tileType;
	_tileSize = size;
}

BaseTile::~BaseTile()
{
	_tileSize = 0;
	_terrainTileType = TerrainTileType::InvalidTileType;
	_tilePossibilities.clear();
	
	delete _tileTexturePath;
	_tileTexturePath = nullptr;
}

void BaseTile::SetPossibilities()
{
	for (int i = 0; i < TerrainTileType::TerrainTileTypeCount; i++)
	{
		_tilePossibilities.push_back((TerrainTileType)i);
	}
}

void BaseTile::SetPossibilities(const TerrainTileType types[])
{
	int typesCount = sizeof(types) / sizeof(types[0]);
	for (int i = 0; i < typesCount; i++)
	{
		_tilePossibilities.push_back(types[i]);
	}
}

void BaseTile::RemovePossibilityIfExists(TerrainTileType type)
{
	auto iter = std::find(_tilePossibilities.begin(), _tilePossibilities.end(), type);
	
	if (iter != _tilePossibilities.end())
	{
		_tilePossibilities.erase(iter);
	}
}

void BaseTile::ForceSetTile(const TerrainTileType type, char* texturePath, const unsigned size)
{
	_terrainTileType = type;
	_tileTexturePath = texturePath;
	_tileSize = size;
	_tilePossibilities.clear();
}

char* BaseTile::GetTileTexturePath()
{
	return _tileTexturePath;
}