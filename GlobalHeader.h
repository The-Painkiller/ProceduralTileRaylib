#pragma once

enum TerrainTileType
{
	InvalidTileType = -1,
	Rock = 0,
	Grass = 1,
	Sand = 2,
	Water = 3,
	TerrainTileTypeCount = 4
};

enum TerrainDirection
{
	North,
	East,
	West,
	South
};

struct Vector2 
{
public:
	int X = 0;
	int Y = 0;

	Vector2() = default;
	Vector2(int x, int y);
};