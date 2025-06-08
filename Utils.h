#pragma once
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include <iostream>
#include "GlobalHeader.h"

/// <summary>
/// Utils is a simple class with mostly static methods for returning Random ints/floats and checking whether a vector2 value is within range.
/// </summary>
class Utils
{
public:
    inline Utils(const float gridSizeX, const float gridSizeY)
    {
        srand(time(NULL));
        GridSize = Vector2{ gridSizeX, gridSizeY };
    };
    static int Random(int floor, int ceilingNotIncluded);
    static float Random(float floor, float ceilingNotIncluded);
    static bool IsWithinRange(const Vector2 target);
    static std::string GetTerrainTileTypeString(TerrainTileType type);
    static std::string GetTerrainBiasCategoryString(TerrainBiasCategory category);
    static void PrintTileType(const int tileLocationX, const int tileLocationY, TerrainTileType terrainType);

private:
    static Vector2 GridSize;
};
bool operator == (const Vector2& lhs, const Vector2& rhs);