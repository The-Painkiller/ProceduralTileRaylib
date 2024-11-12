#pragma once
#include <string>
#include "single_include\nlohmann\json.hpp"
#include <fstream>
#include "GlobalHeader.h"

using json = nlohmann::json;

struct TileData 
{
public:
	TerrainTileType TileType;
	std::string TileTexturePath;
	std::vector<TerrainTileType> ValidNeighbours;
};

class DataParser
{
public:
	DataParser() = default;
	~DataParser();
	void Initialize();
	TileData GetTileData(TerrainTileType tileType);

private:
	json _terrainTileDataJson;

	const char* _terrainTileDataPath = "assets/JSON/TerrainTileData.json";

	std::vector<TileData> _tileData;

	void SetData(TerrainTileType terrainTileType);
	std::string GetTerrainTileTypeString(TerrainTileType type);
};