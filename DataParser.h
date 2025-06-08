#pragma once
#include "single_include\nlohmann\json.hpp"
#include <fstream>
#include "GlobalHeader.h"
#include "Utils.h"

using json = nlohmann::json;

/// <summary>
/// Data parser will take data from the supplied json location and feed it to Tile and Bias Managers.
/// </summary>
class DataParser
{
public:
	DataParser() = default;
	~DataParser();
	void Initialize();
	TileData GetTileData(const TerrainTileType tileType);
	BiasData GetTerrainTypeBiasData(const TerrainBiasCategory terrainCategory);

private:
	json _terrainTileDataJson;

	const char* _terrainTileDataPath = "assets/JSON/TerrainTileData.json";

	std::vector<TileData> _tileData;
	std::vector<BiasData> _biasData;

	void SetTileData(const json dataRoot, const TerrainTileType terrainTileType);
	void SetBiasData(const json dataRoot, const TerrainBiasCategory biasCategory);
};