#pragma once
#include <string>
#include "single_include\nlohmann\json.hpp"
#include <fstream>
#include "GlobalHeader.h"

using json = nlohmann::json;

struct TileData 
{
public:
	std::vector<std::string> TileTexturePaths;
	std::vector<TerrainTileType> ValidNeighbours;
};

struct JSONData
{
public:
	TileData Grass;
	TileData Rock;
	TileData Sand;
	TileData Water;
};

class DataParser
{
public:
	DataParser() = default;
	void Initialize();

private:
	json _terrainTileData;

	const char* _terrainTileDataPath = "assets/JSON/TerrainTileData.json";

	JSONData jsonData = {};
	TileData _grassData = {};
	TileData _rockData = {};
	TileData _sandData = {};
	TileData _waterData = {};
	TileData _invalidTileData = {};

	void SetData(TerrainTileType terrainTileType);
	std::string GetTerrainTileTypeString(TerrainTileType type);
};