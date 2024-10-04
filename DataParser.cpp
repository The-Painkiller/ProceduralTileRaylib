#include "DataParser.h"

void to_json(json& JSON, const JSONData& data)
{
	JSON = {
		{
			"Grass",
			{
				"TexturePaths",
				data.Grass.TileTexturePaths
			},
			{
				"Neighbours",
				data.Grass.ValidNeighbours
			}
		},
		{
			"Rock",
			{
				"TexturePaths",
				data.Rock.TileTexturePaths
			},
			{
				"Neighbours",
				data.Rock.ValidNeighbours
			}
		}

	};
}

void DataParser::Initialize()
{
	std::ifstream ifs;
	ifs.open(_terrainTileDataPath, std::ifstream::in);
	if (ifs.is_open())
	{
		_terrainTileData = json::parse(ifs);
	}
	ifs.close();

	for (int i = TerrainTileType::InvalidTileType; i < TerrainTileType::TerrainTileTypeCount; i++)
	{
		TerrainTileType tileType = (TerrainTileType)i;
		SetData((TerrainTileType)i);
	}
}

void DataParser::SetData(TerrainTileType terrainTileType)
{
	TileData data = {};
	auto dataRoot = _terrainTileData[GetTerrainTileTypeString(terrainTileType)];
	auto dataTexturePaths = dataRoot["TexturePaths"];
	auto dataNeighbours = dataRoot["Neighbours"];

	for (auto& texture : dataTexturePaths)
	{
		data.TileTexturePaths.push_back(texture);
	}

	for (auto& neighbour : dataNeighbours)
	{
		data.ValidNeighbours.push_back(neighbour);
	}
	switch (terrainTileType)
	{
	case Rock:
	{
		_rockData = data;
		break;
	}
	case Grass:
	{
		_grassData = data;
		break;
	}
	case Sand:
	{
		_sandData = data;
		break;
	}
	case Water:
	{
		_waterData = data;
		break;
	}

	case InvalidTileType:
	case TerrainTileTypeCount:
	default:
		_invalidTileData = data;
		break;
	}
}

std::string DataParser::GetTerrainTileTypeString(TerrainTileType type)
{
	switch (type)
	{
	case InvalidTileType:
		return "InvalidTileType";
	case Rock:
		return "Rock";
	case Grass:
		return "Grass";
	case Sand:
		return "Sand";
	case Water:
		return "Water";
	case TerrainTileTypeCount:
		return "TerrainTileTypeCount";
	}
}
