#include "BaseTile.h"
#include <iterator>

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

void BaseTile::SetValidNeighbours(const std::vector<TerrainTileType> validNeighbours)
{
	_validNeighbours = validNeighbours;
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
	_validNeighbours = validNeighbours;
}

void BaseTile::SetIterationFlag(const bool isIterated)
{
	_isIteratedOver = isIterated;
}

void BaseTile::CollapseEntropy(const std::vector<TerrainTileType>& validNeighourListOfIncomingTile)
{
	// When create a set intersection to bring down the entropy of the current tile,
	// first a set intersection is done between the entropy of the current tile and the list of valid neighbours of the adjacent tile that's passed.
	// A bias is used to select the most favourable tile type.

	std::vector<TerrainTileType> intersection = std::vector<TerrainTileType>();
	for (int i = 0; i < _tileEntropies.size(); i++)
	{
		if (std::find(validNeighourListOfIncomingTile.begin(), validNeighourListOfIncomingTile.end(), _tileEntropies[i]) != validNeighourListOfIncomingTile.end())
		{
            if (_terrainTileType == InvalidTileType)
            {
                if (BiasManager::IsBiasValid(_tileEntropies[i]))
                {
                    intersection.push_back(_tileEntropies[i]);
                }
            }
            else
            {
                intersection.push_back(_tileEntropies[i]);
            }
		}
	}

	// In case the set intersection with the passed list of valid neighbours of the adjacent tile and current tile's entropy returns 0,
	// a set intersection is run between the lists of valid neighbours of both the tiles and run through a bias.

	if (intersection.size() == 0 && !_validNeighbours.empty())
	{
		for (int i = 0; i < _validNeighbours.size(); i++)
		{
			if (std::find(validNeighourListOfIncomingTile.begin(), validNeighourListOfIncomingTile.end(), _validNeighbours[i]) != validNeighourListOfIncomingTile.end()
				 && BiasManager::IsBiasValid(_validNeighbours[i]))
			{
				intersection.push_back(_validNeighbours[i]);
			}
		}
	}

	// If it still returns 0, the running through bias, the most favourable tile from the list of valid neighbours of the adjacent tile is chosen.
	
	if (intersection.size() == 0)
	{
		for (int i = 0; i < validNeighourListOfIncomingTile.size(); i++)
		{
			if (!BiasManager::IsBiasValid(validNeighourListOfIncomingTile[i]))
			{
				continue;
			}
			intersection.push_back(validNeighourListOfIncomingTile[i]);
		}
	}

	// If everything returns an intersection set of 0, then the first valid tile type from the list of valid neighbours of 
	// the adjacent tile is selected outright as a last resort.
	if (intersection.size() == 0)
	{
		intersection.push_back(validNeighourListOfIncomingTile[0]);
	}

	_tileEntropies = intersection;
}

TerrainTileType BaseTile::GetTerrainTileType()
{
	return _terrainTileType;
}

int BaseTile::GetEntropyCount()
{
	return _tileEntropies.size();
}

int BaseTile::GetValidNeighbourCount()
{
	return _validNeighbours.size();
}

bool BaseTile::IsIteratedOver()
{
	return _isIteratedOver;
}

TerrainTileType BaseTile::GetEntropy(const int index)
{
	if (_tileEntropies.size() == 0 || _tileEntropies.size() <= index)
	{
		return TerrainTileType::InvalidTileType;
	}

	return _tileEntropies[index];
}

TerrainTileType BaseTile::GetValidNeighbour(const int index)
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