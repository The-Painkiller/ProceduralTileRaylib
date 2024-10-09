#pragma once

enum TerrainTileType
{
	InvalidTileType = -1,
	Rock = 0,
	Grass = 1,
	Sand = 2,
	Water = 3,
	RockSandTransition = 4,
	RockWaterTransition = 5,
	RockGrassTransition = 6,
	SandGrassTransition = 7,
	SandWaterTransition = 8,
	TerrainTileTypeCount = 9
};

enum TerrainDirection
{
	North,
	East,
	West,
	South
};