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
	std::ifstream ifs;
	ifs.open(_terrainTileDataPath, std::ifstream::in);
	if (ifs.is_open())
	{
		_terrainTileDataJson = json::parse(ifs);
	}
	ifs.close();

	for (int i = TerrainTileType::InvalidTileType; i < TerrainTileType::TerrainTileTypeCount; i++)
	{
		TerrainTileType tileType = (TerrainTileType)i;
		SetData((TerrainTileType)i);
	}
}

TileData DataParser::GetTileData(TerrainTileType tileType)
{
	return _tileData[tileType];
}

void DataParser::SetData(TerrainTileType terrainTileType)
{
	TileData data = {};
	auto dataRoot = _terrainTileDataJson[GetTerrainTileTypeString(terrainTileType)];
	auto dataTexturePaths = dataRoot["TexturePaths"];
	auto dataNeighbours = dataRoot["Neighbours"];

	for (auto& texture : dataTexturePaths)
	{
		data.TileTexturePath = texture;
	}

	for (auto& neighbour : dataNeighbours)
	{
		data.ValidNeighbours.push_back(neighbour);
	}

	switch (terrainTileType)
	{
	case InvalidTileType:
		break;
	default:
		_tileData[terrainTileType] = data;
		_tileData[terrainTileType].TileType = terrainTileType;
		break;
	}
}

std::string DataParser::GetTerrainTileTypeString(TerrainTileType type)
{
	switch (type)
	{
	case Rock:
		return "Rock";
	case Grass:
		return "Grass";
	case Sand:
		return "Sand";
	case Water:
		return "Water";
	case RockGrassTransition:
		return "RockGrass";
	case RockSandTransition:
		return "RockSand";
	case RockWaterTransition:
		return "RockWater";
	case SandGrassTransition:
		return "SandGrass";
	case SandWaterTransition:
		return "SandWater";
	case TerrainTileTypeCount:
		return "TerrainTileTypeCount";
	default:
		return "InvalidTileType";
	}
}