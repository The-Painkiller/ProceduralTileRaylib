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

class GlobalHeader
{
public:
	GlobalHeader() = default;
	~GlobalHeader() = default;

	static int TileSize;
};

/*
* The Wave Function Collapse (WFC) algorithm is a fascinating method used primarily in procedural content generation, such as creating images, textures, or even game levels. It draws inspiration from quantum mechanics, particularly the concept of a wave function collapsing into a definite state. Here’s a step-by-step breakdown of how it works:

Initialization:
- Input: Start with a set of input patterns or tiles that define the possible states.
- Grid: Create a grid where each cell can potentially be any of the input patterns.

Entropy Calculation:
Each cell in the grid has an associated entropy, representing the number of possible patterns it can take. Initially, all cells have maximum entropy because they can be any pattern.

Observation:
Select the cell with the lowest entropy (i.e., the fewest possible patterns). If multiple cells have the same entropy, one is chosen randomly.

Collapse:
Assign a specific pattern to the selected cell, effectively collapsing its wave function. This pattern is chosen based on the probabilities derived from the input patterns.

Propagation:
Update the neighboring cells’ possible patterns based on the newly collapsed cell. This step reduces the entropy of the neighboring cells by eliminating patterns that are no longer possible.

Repeat:
Continue the process of selecting the cell with the lowest entropy, collapsing it, and propagating the changes until all cells are collapsed or a contradiction is found (where no valid pattern can be assigned).

Handling Contradictions:
If a contradiction occurs, the algorithm may backtrack to a previous state and try a different pattern, or it may restart the process with different initial conditions.
*/