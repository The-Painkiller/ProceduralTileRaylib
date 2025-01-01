#include "TileManager.h"

TileManager::TileManager(int gridSizeX, int gridSizeY, std::shared_ptr<DataParser>& dataParser)
{
	_gridSizeX = gridSizeX;
	_gridSizeY = gridSizeY;
	_dataParser = dataParser;
}

TileManager::~TileManager()
{
	_gridSizeX = 0;
	_gridSizeY = 0;
	_tiles.clear();
}

void TileManager::InitializeTileGrid()
{
	for (int i = 0; i < _gridSizeX; i++)
	{
		_tiles.push_back(std::vector<std::shared_ptr<BaseTile>>(_gridSizeY));
		for (int j = 0; j < _gridSizeY; j++)
		{
			_tiles[i][j] = std::shared_ptr<BaseTile>(new BaseTile(Grass, 256));
			_tiles[i][j].get()->SetEntropy();

			_tiles[i][j].get()->SetValidNeighbours(_dataParser.get()->GetTileData(_tiles[i][j].get()->GetTerrainTileType()).ValidNeighbours);
		}
	}
}

void TileManager::Obervation(const Vector2 tileLocation, BaseTile& neighbourTileWithEntropyOne)
{
	if (tileLocation.x < 0 || tileLocation.y < 0)
	{
		return;
	}
	
	if (tileLocation.x >= _tiles.size() || tileLocation.y >= _tiles[tileLocation.x].size())
	{
		return;
	}


	TerrainTileType currentTileType = _tiles[tileLocation.x][tileLocation.y].get()->GetTerrainTileType();
	auto iter = std::find(neighbourTileWithEntropyOne.GetValidNeighbours().begin(), neighbourTileWithEntropyOne.GetValidNeighbours().end(), currentTileType);
	
	///if the current tile type of this tile is among the list of valid neighbours of the tile passed, then do nothing.
	if (iter != neighbourTileWithEntropyOne.GetValidNeighbours().end())
	{
		return;
	}

	auto validNeighbours = _tiles[tileLocation.x][tileLocation.y].get()->UpdateEntropy(neighbourTileWithEntropyOne.GetValidNeighbours());

	///check if validNeighours.size > 1.
	///if Yes: choose at random else force the 1.
	if (validNeighbours.size() == 1)
	{
		ForceTileEntropy({ tileLocation.x, tileLocation.y }, validNeighbours[0], validNeighbours);
	}
	else
	{
		int rand = Utils::Random(0, validNeighbours.size());
		ForceTileEntropy({ tileLocation.x, tileLocation.y }, validNeighbours[rand], validNeighbours);
	}
}

std::vector<std::vector<std::shared_ptr<BaseTile>>>& TileManager::GetTileArray()
{
	return _tiles;
}

void TileManager::ForceTileEntropy(const Vector2 tileLocation, const TerrainTileType type, const std::vector<TerrainTileType> validNeighbours)
{
	auto iter = std::find_if(_tilesWithOneEntropy.begin(), _tilesWithOneEntropy.end(), [tileLocation](const Vector2& vec) {return tileLocation.x == vec.x && tileLocation.y == vec.y; });
	if (iter == _tilesWithOneEntropy.end())
	{
		_tilesWithOneEntropy.push_back(tileLocation);
	}

	_tiles[tileLocation.x][tileLocation.y]->ForceSetTile(type, GlobalHeader::TileSize, validNeighbours);

	TileManager::Obervation(Vector2{ tileLocation.x - 1, tileLocation.y }, *_tiles[tileLocation.x][tileLocation.y].get());
	TileManager::Obervation(Vector2{ tileLocation.x + 1, tileLocation.y }, *_tiles[tileLocation.x][tileLocation.y].get());
	TileManager::Obervation(Vector2{ tileLocation.x, tileLocation.y - 1 }, *_tiles[tileLocation.x][tileLocation.y].get());
	TileManager::Obervation(Vector2{ tileLocation.x, tileLocation.y + 1 }, *_tiles[tileLocation.x][tileLocation.y].get());
}

void TileManager::CalculateEntropies()
{
}

void TileManager::CollapseEntropies(const Vector2 tileLocation, const std::vector<TerrainTileType> entropies)
{
	//TerrainTileType entropy = _tiles[tileLocation.x][tileLocation.y].get()->GetEntropy(0);
	////_tiles[tileLocation.x][tileLocation.y].get()->ForceSetTile(entropy, GlobalHeader::TileSize, _dataParser.get()->GetTileData(neighbourTileWithEntropyOne.GetValidNeighbour(0)).ValidNeighbours);
	//ForceTileEntropy(Vector2{ tileLocation.x, tileLocation.y }, entropy, _dataParser->GetTileData(entropy).ValidNeighbours);
}
