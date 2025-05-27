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
			_tiles[i][j] = std::shared_ptr<BaseTile>(new BaseTile(InvalidTileType, 256));
			_tiles[i][j].get()->SetEntropy();

			_tiles[i][j].get()->SetValidNeighbours(_dataParser.get()->GetTileData(_tiles[i][j].get()->GetTerrainTileType()).ValidNeighbours);
		}
	}
}

void TileManager::Obervation(const Vector2 tileLocation, BaseTile& neighbourTileWithEntropyOne)
{
	if (!Utils::IsWithinRange(tileLocation))
	{
		return;
	}
	
	BaseTile* currentTile = _tiles[tileLocation.x][tileLocation.y].get();
	
	if (currentTile->IsIteratedOver())
	{
		return;
	}


	TerrainTileType currentTileType = currentTile->GetTerrainTileType();
	auto iter = std::find(neighbourTileWithEntropyOne.GetValidNeighbours().begin(), neighbourTileWithEntropyOne.GetValidNeighbours().end(), currentTileType);
	
	///if the current tile type of this tile is among the list of valid neighbours of the tile passed, then do nothing.
	if (iter != neighbourTileWithEntropyOne.GetValidNeighbours().end())
	{
		currentTile->SetIterationFlag(true);
		return;
	}

	currentTile->UpdateEntropy(neighbourTileWithEntropyOne.GetValidNeighbours());

	///check if entropy count > 1.
	///if Yes: choose at random else force the 1.
	int currentTileEntropy = currentTile->GetEntropyCount();
	if (currentTileEntropy == 1)
	{
		ForceTileEntropy({ tileLocation.x, tileLocation.y }, currentTile->GetEntropy(0), _dataParser->GetTileData(currentTile->GetEntropy(0)).ValidNeighbours);
	}
	else
	{
        TerrainTileType randomCollapsedEntropy = CollapseEntropy(tileLocation, currentTile, currentTileEntropy);
		ForceTileEntropy({ tileLocation.x, tileLocation.y }, randomCollapsedEntropy, _dataParser->GetTileData(randomCollapsedEntropy).ValidNeighbours);
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

	BaseTile* currentTile = _tiles[tileLocation.x][tileLocation.y].get();

	currentTile->ForceSetTile(type, GlobalHeader::TileSize, validNeighbours);
	currentTile->SetIterationFlag(true);

	//Internally propagating to the neighouring cells.
	TileManager::Obervation(Vector2{ tileLocation.x + 1, tileLocation.y }, *currentTile);
	TileManager::Obervation(Vector2{ tileLocation.x, tileLocation.y - 1 }, *currentTile);
	TileManager::Obervation(Vector2{ tileLocation.x, tileLocation.y + 1 }, *currentTile);
	TileManager::Obervation(Vector2{ tileLocation.x - 1, tileLocation.y }, *currentTile);
}

void TileManager::ClearTileIterations()
{
    for (int i = 0; i < _gridSizeX; i++)
    {
        for (int j = 0; j < _gridSizeY; j++)
        {
            _tiles[i][j]->SetIterationFlag(false);
        }
    }
}

TerrainTileType TileManager::CollapseEntropy(const Vector2& tileLocation, BaseTile* currentTile, int& currentTileEntropy)
{
    if (Utils::IsWithinRange({ tileLocation.x + 1, tileLocation.y }))
    {
        currentTile->UpdateEntropy(_tiles[tileLocation.x + 1][tileLocation.y]->GetValidNeighbours());
    }

    if (Utils::IsWithinRange({ tileLocation.x - 1, tileLocation.y }))
    {
        currentTile->UpdateEntropy(_tiles[tileLocation.x - 1][tileLocation.y]->GetValidNeighbours());
    }

    if (Utils::IsWithinRange({ tileLocation.x, tileLocation.y - 1 }))
    {
        currentTile->UpdateEntropy(_tiles[tileLocation.x][tileLocation.y - 1]->GetValidNeighbours());
    }

    if (Utils::IsWithinRange({ tileLocation.x, tileLocation.y + 1 }))
    {
        currentTile->UpdateEntropy(_tiles[tileLocation.x][tileLocation.y + 1]->GetValidNeighbours());
    }

    currentTileEntropy = currentTile->GetEntropyCount();
	int rand = Utils::Random(0, currentTileEntropy);
	return currentTile->GetEntropy(rand);
}
