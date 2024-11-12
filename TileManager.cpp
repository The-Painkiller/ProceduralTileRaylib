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
		}
	}
}

void TileManager::Obervation(const Vector2 tileLocation, BaseTile& neighbourTileWithEntropyOne)
{
	if (tileLocation.x < 0 || tileLocation.y >= _tiles[tileLocation.x].size())
	{
		return;
	}

	if (tileLocation.x >= _tiles.size() || tileLocation.y < 0)
	{
		return;
	}

	if (_tiles[tileLocation.x][tileLocation.y].get()->GetEntropyCount() == 1)
	{
		///check if it complies otherwise change.
	}

	std::vector<TerrainTileType> intersectedEntropy = _tiles[tileLocation.x][tileLocation.y].get()->IntersectNeighbourWithEntropy(neighbourTileWithEntropyOne.GetValidNeighbours());
	if (intersectedEntropy.size() == 0)
	{
		_tiles[tileLocation.x][tileLocation.y].get()->ForceSetTile(neighbourTileWithEntropyOne.GetValidNeighbour(0), GlobalHeader::TileSize ,_dataParser.get()->GetTileData(neighbourTileWithEntropyOne.GetValidNeighbour(0)).ValidNeighbours);
	}
	else
	{
		_tiles[tileLocation.x][tileLocation.y].get()->ForceSetTile(_tiles[tileLocation.x][tileLocation.y].get()->GetEntropy(0), GlobalHeader::TileSize, _dataParser.get()->GetTileData(_tiles[tileLocation.x][tileLocation.y].get()->GetEntropy(0)).ValidNeighbours);
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

	TileManager::Obervation(const Vector2{ tileLocation.x - 1, tileLocation.y }, *_tiles[tileLocation.x][tileLocation.y].get());
	TileManager::Obervation(const Vector2{ tileLocation.x + 1, tileLocation.y }, *_tiles[tileLocation.x][tileLocation.y].get());
	TileManager::Obervation(const Vector2{ tileLocation.x, tileLocation.y - 1 }, *_tiles[tileLocation.x][tileLocation.y].get());
	TileManager::Obervation(const Vector2{ tileLocation.x, tileLocation.y + 1 }, *_tiles[tileLocation.x][tileLocation.y].get());
}
