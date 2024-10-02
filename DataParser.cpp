#include "DataParser.h"

void DataParser::Initialize()
{
	std::ifstream ifs(_terrainTileDataPath);
	_terrainTileData = json::parse(ifs);

	for (int i = 0; i < TerrainTileType::TerrainTileTypeCount; i++)
	{
		std::string type = std::to_string((TerrainTileType)i);
		std::string s = json::string_t(_terrainTileData[type]["TexturePath"]);
		for (auto& elem : _terrainTileData[type]["Neighbours"])
		{
			//elem[0]
		}
	}
}

std::string DataParser::GetTerrainTileData()
{
	return json::string_t(_terrainTileData["Grass"]["TexturePath"]);
}

void DataParser::SetData(TerrainTileType terrainTileType)
{

}
