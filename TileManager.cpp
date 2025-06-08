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

/// <summary>
/// This method combines the Observation step in Wave Function Collapse with the Collapse step.
/// </summary>
void TileManager::Obervation(const Vector2 tileLocation, BaseTile& neighbourTileWithEntropyOne, const TraverseDirection direction)
{
	// Check if the passed tilelocation is within range.
	if (!Utils::IsWithinRange(tileLocation))
	{
		return;
	}
	
	BaseTile* currentTile = _tiles[tileLocation.x][tileLocation.y].get();
    TerrainTileType currentTileType = currentTile->GetTerrainTileType();
	TerrainTileType neighbourType = neighbourTileWithEntropyOne.GetTerrainTileType();
    auto currentEntropies = currentTile->GetEntropyCount();
	
	// If the tile has already been iterated over, but it doesn't belong to the list of valid neighbours of the adjacent tile with entropy 1,
	// it will have to run through a repeat iteration.
    if (currentTile->IsIteratedOver())
    {
        auto iter = std::find(neighbourTileWithEntropyOne.GetValidNeighbours().begin(), neighbourTileWithEntropyOne.GetValidNeighbours().end(), currentTileType);

        ///if the current tile type of this tile is among the list of valid neighbours of the tile passed, then do nothing.
        if (iter != neighbourTileWithEntropyOne.GetValidNeighbours().end())
        {
            return;
        }
    }

	auto iter = std::find(neighbourTileWithEntropyOne.GetValidNeighbours().begin(), neighbourTileWithEntropyOne.GetValidNeighbours().end(), currentTileType);
	
	///if the current tile type of this tile is among the list of valid neighbours of the tile passed, then do nothing.
	if (iter != neighbourTileWithEntropyOne.GetValidNeighbours().end())
	{
		currentTile->SetIterationFlag(true);
		return;
	}

	// Run a set intersection between the entropy of the currentTile and the list of valid neighbours of the adjacent tile with entropy 1,
	// to collapse it's entropy.
	currentTile->CollapseEntropy(neighbourTileWithEntropyOne.GetValidNeighbours());

	///check if entropy count > 1.
	///if Yes: choose at random else force the 1.
	/// if No: Collapse it's entropy further with another tile in the same direction.
	int currentTileEntropy = currentTile->GetEntropyCount();
	if (currentTileEntropy == 1)
	{
		ForceTileEntropy({ tileLocation.x, tileLocation.y }, currentTile->GetEntropy(0), _dataParser->GetTileData(currentTile->GetEntropy(0)).ValidNeighbours);
	}
	else
	{
        TerrainTileType randomCollapsedEntropy = CollapseEntropyInDirection(tileLocation, *currentTile, currentTileEntropy, direction);
		if ((randomCollapsedEntropy == WaterGrassTransition))
		{
			int temp = 0;
		}
		ForceTileEntropy({ tileLocation.x, tileLocation.y }, randomCollapsedEntropy, _dataParser->GetTileData(randomCollapsedEntropy).ValidNeighbours);
	}
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
	TileManager::Obervation(Vector2{ tileLocation.x + 1, tileLocation.y }, *currentTile, East);
	TileManager::Obervation(Vector2{ tileLocation.x, tileLocation.y - 1 }, *currentTile, North);
	TileManager::Obervation(Vector2{ tileLocation.x, tileLocation.y + 1 }, *currentTile, South);
	TileManager::Obervation(Vector2{ tileLocation.x - 1, tileLocation.y }, *currentTile, West);
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

TerrainTileType TileManager::CollapseEntropyInDirection(const Vector2& tileLocation, BaseTile& currentTile, int currentTileEntropy, const TraverseDirection direction)
{
    switch (direction)
    {
    case North:
        if (Utils::IsWithinRange({ tileLocation.x, tileLocation.y - 1 })
            && _tiles[tileLocation.x][tileLocation.y - 1]->GetTerrainTileType() != InvalidTileType)
        {
            currentTile.CollapseEntropy(_tiles[tileLocation.x][tileLocation.y - 1]->GetValidNeighbours());
        }
        break;
    case East:
        if (Utils::IsWithinRange({ tileLocation.x + 1, tileLocation.y })
            && _tiles[tileLocation.x + 1][tileLocation.y]->GetTerrainTileType() != InvalidTileType)
        {
            currentTile.CollapseEntropy(_tiles[tileLocation.x + 1][tileLocation.y]->GetValidNeighbours());
        }
        break;
    case West:
        if (Utils::IsWithinRange({ tileLocation.x - 1, tileLocation.y })
            && _tiles[tileLocation.x - 1][tileLocation.y]->GetTerrainTileType() != InvalidTileType)
        {
            currentTile.CollapseEntropy(_tiles[tileLocation.x - 1][tileLocation.y]->GetValidNeighbours());
        }
        break;
    case South:
        if (Utils::IsWithinRange({ tileLocation.x, tileLocation.y + 1 })
            && _tiles[tileLocation.x][tileLocation.y + 1]->GetTerrainTileType() != InvalidTileType)

        {
            currentTile.CollapseEntropy(_tiles[tileLocation.x][tileLocation.y + 1]->GetValidNeighbours());
        }
        break;
    default:
        break;
    }

    currentTileEntropy = currentTile.GetEntropyCount();
	int rand = Utils::Random(0, currentTileEntropy);
	return currentTile.GetEntropy(rand);
}

std::vector<std::vector<std::shared_ptr<BaseTile>>>& TileManager::GetTileArray()
{
    return _tiles;
}