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
	_tileEntropies.clear();	
}

void BaseTile::SetEntropy()
{
	for (int i = 0; i < TerrainTileType::TerrainTileTypeCount; i++)
	{
		_tileEntropies.push_back((TerrainTileType)i);
	}
}

void BaseTile::SetEntropy(const TerrainTileType types[])
{
	int typesCount = sizeof(types) / sizeof(types[0]);
	for (int i = 0; i < typesCount; i++)
	{
		_tileEntropies.push_back(types[i]);
	}
}

void BaseTile::RemoveEntropyIfExists(TerrainTileType type)
{
	if (_tileEntropies.size() <= 0)
	{
		return;
	}

	auto iter = std::find(_tileEntropies.begin(), _tileEntropies.end(), type);
	
	if (iter != _tileEntropies.end())
	{
		_tileEntropies.erase(iter);
	}
}

void BaseTile::ForceSetTile(const TerrainTileType type, const unsigned size, const std::vector<TerrainTileType>& validNeighbours)
{
	_terrainTileType = type;
	_tileSize = size;
	_tileEntropies.clear();
	_tileEntropies.push_back(type);
}

void BaseTile::SetTransitionFlag(bool isTransitionTile)
{
	_isTransitionTile = isTransitionTile;
}

std::vector<TerrainTileType>& BaseTile::IntersectNeighbourWithEntropy(const std::vector<TerrainTileType>& validNeighourListOfIncomingTile)
{
	std::vector<TerrainTileType> intersectionOfTileTypes;
	std::set_intersection(_tileEntropies.begin(), _tileEntropies.end(), validNeighourListOfIncomingTile.begin(), validNeighourListOfIncomingTile.end(), intersectionOfTileTypes);
	return intersectionOfTileTypes;
}

TerrainTileType BaseTile::GetTerrainTileType()
{
	return _terrainTileType;
}

bool BaseTile::IsTransitionTile()
{
	return _isTransitionTile;
}

int BaseTile::GetEntropyCount()
{
	return _tileEntropies.size();
}

int BaseTile::GetValidNeighbourCount()
{
	return _validNeighbours.size();
}

TerrainTileType BaseTile::GetEntropy(int index)
{
	if (_tileEntropies.size() == 0)
	{
		return TerrainTileType::InvalidTileType;
	}

	return _tileEntropies[index];
}

TerrainTileType BaseTile::GetValidNeighbour(int index)
{
	if (_validNeighbours.size() == 0)
	{
		return TerrainTileType::InvalidTileType;
	}

	return _validNeighbours[index];
}

std::vector<TerrainTileType>& BaseTile::GetValidNeighbours()
{
	return _validNeighbours;
}