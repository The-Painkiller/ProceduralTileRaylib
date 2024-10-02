#pragma once
#include <string>
#include "single_include\nlohmann\json.hpp"
#include <fstream>
#include "GlobalHeader.h"

using json = nlohmann::json;

struct TileData 
{
public:
	std::string TileTexturePaths[2];
	TerrainTileType ValidNeighbours;
};

class DataParser
{
public:
	DataParser() = default;
	void Initialize();
	std::string GetTerrainTileData();

private:
	json _terrainTileData;

	const char* _terrainTileDataPath = "assets/JSON/TerrainTileData.json";

	TileData _grassData = {};
	TileData _rockData = {};
	TileData _sandData = {};
	TileData _waterData = {};

	void SetData(TerrainTileType terrainTileType);
};