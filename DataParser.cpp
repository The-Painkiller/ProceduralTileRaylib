#include "DataParser.h"

DataParser::~DataParser()
{
	_terrainTileDataPath = nullptr;
	delete _terrainTileDataPath;

	_tileData.clear();
	_terrainTileDataJson = {};
}

void DataParser::Initialize()
{
	_tileData = std::vector<TileData>(TerrainTileTypeCount);
	_biasData = std::vector<BiasData>(TerrainBiasCategoryCount);
	std::ifstream ifs;
	ifs.open(_terrainTileDataPath, std::ifstream::in);
	if (ifs.is_open())
	{
		_terrainTileDataJson = json::parse(ifs);
	}
	ifs.close();

	auto tileDataRoot = _terrainTileDataJson["TileData"];
	for (int i = TerrainTileType::InvalidTileType; i < TerrainTileType::TerrainTileTypeCount; i++)
	{
		TerrainTileType tileType = (TerrainTileType)i;
		SetTileData(tileDataRoot, (TerrainTileType)i);
	}

	auto biasDataRoot = _terrainTileDataJson["Bias"];
	for (int i = TerrainBiasCategory::RockBias; i <= TerrainBiasCategory::GrassBias; i++)
	{
		TerrainBiasCategory terrainCategory = (TerrainBiasCategory)i;
		SetBiasData(biasDataRoot, terrainCategory);
	}
}

TileData DataParser::GetTileData(const TerrainTileType tileType)
{
	return _tileData[tileType];
}

BiasData DataParser::GetTerrainTypeBiasData(const TerrainBiasCategory terrainCategory)
{
	return _biasData[terrainCategory];
}

void DataParser::SetTileData(const json dataRoot, const TerrainTileType terrainTileType)
{
	TileData data = {};
	auto terrainData = dataRoot[Utils::GetTerrainTileTypeString(terrainTileType)];
	auto dataTexturePaths = terrainData["TexturePaths"];
	auto dataNeighbours = terrainData["Neighbours"];

	for (auto& texture : dataTexturePaths)
	{
		data.TileTexturePath = texture;
	}

	for (auto& neighbour : dataNeighbours)
	{
		data.ValidNeighbours.push_back(neighbour);
	}

    _tileData[terrainTileType] = data;
    _tileData[terrainTileType].TileType = terrainTileType;
}

void DataParser::SetBiasData(const json dataRoot, const TerrainBiasCategory biasCategory)
{
	BiasData data = {};
	auto biasData = dataRoot[Utils::GetTerrainBiasCategoryString(biasCategory)];
	float biasvalue = biasData["Bias"];
	data.Bias = biasvalue;

	auto validTerrainTypes = biasData["ValidTerrainTypes"];

	for (auto& terrainType : validTerrainTypes)
	{
		data.ValidTerrainTypes.push_back(terrainType);
	}

	_biasData[biasCategory] = data;
}