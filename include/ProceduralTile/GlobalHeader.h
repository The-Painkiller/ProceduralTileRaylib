#pragma once
#include <string>
#include <vector>

enum TerrainTileType
{
    InvalidTileType = 0,
    Rock = 1,
    Grass = 2,
    Sand = 3,
    Water = 4,
    RockSandTransition = 5,
    RockWaterTransition = 6,
    RockGrassTransition = 7,
    SandGrassTransition = 8,
    SandWaterTransition = 9,
    WaterGrassTransition = 10,
    TerrainTileTypeCount = 11
};

enum TerrainBiasCategory
{
	RockBias = 0,
    SandBias = 1,
    WaterBias = 2,
    GrassBias = 3,
    TerrainBiasCategoryCount = 4
};

enum TraverseDirection
{
    North,
    East,
    West,
    South
};

struct TileData
{
public:
    TerrainTileType TileType;
    std::string TileTexturePath;
    std::vector<TerrainTileType> ValidNeighbours;
};

struct BiasData
{
public:
    float Bias;
    std::vector<TerrainTileType> ValidTerrainTypes;
};

class GlobalHeader
{
public:
	GlobalHeader() = default;
	~GlobalHeader() = default;

	static int TileSize;
    static int GridSizeX;
    static int GridSizeY;
};