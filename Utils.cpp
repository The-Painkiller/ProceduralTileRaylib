#include "Utils.h"

Vector2 Utils::GridSize = Vector2{};
int Utils::Random(int floor, int ceilingNotIncluded)
{
    return rand() % (ceilingNotIncluded - floor) + floor;
}

float Utils::Random(float floor, float ceilingNotIncluded)
{
    return  (float)rand() / RAND_MAX;
}

bool Utils::IsWithinRange(const Vector2 target)
{
    return target.x >= 0 && target.y >= 0 && target.x < GridSize.x && target.y < GridSize.y;
}

std::string Utils::GetTerrainTileTypeString(TerrainTileType type)
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
    case WaterGrassTransition:
        return "WaterGrass";
    case TerrainTileTypeCount:
        return "TerrainTileTypeCount";
    default:
        return "InvalidTileType";
    }
}

std::string Utils::GetTerrainBiasCategoryString(TerrainBiasCategory category)
{
    switch (category)
    {
    case RockBias:
        return "RockBias";
    case SandBias:
        return "SandBias";
    case WaterBias:
        return "WaterBias";
    case GrassBias:
        return "GrassBias";
    default:
        break;
    }
}

void Utils::PrintTileType(const int tileLocationX, const int tileLocationY, TerrainTileType terrainType)
{
    std::cout << "[" << tileLocationX << "][" << tileLocationY << "] = " << GetTerrainTileTypeString(terrainType) << std::endl;
}

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    return(lhs.x == rhs.x && lhs.y == rhs.y);
}
