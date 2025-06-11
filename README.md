# ProceduralTileRaylib

I created this small project just to play around with procedural tile map generation using the very basic understanding I have of Wave Collapse Function (WFC). The project is made in C++ and uses [Raylib](https://github.com/raysan5/raylib#:~:text=raylib%20is%20a%20simple%20and,library%20to%20enjoy%20videogames%20programming) for graphics. The implementation is fairly simple as it was done as a personal project in many many short bursts of personal time across many months. The idea was to just understand the basic flow of how WFC could work and basically how procedural terrains/images/etc., could be generated.

As for the inspiration, this video I saw more than a year ago on YouTube, intrigued me into trying this practically myself. [Link](https://www.youtube.com/watch?v=2SuvO4Gi7uY). My primary thought was to use Unity, but I thought a more fun thing would be to try it in C++ using a native library!
<br/>
<br/>
## Enums

All the enums can be found under GlobalHeader.h

### TerrainTileType
Contains all the types of terrain a tile can be. It could be Water, Rock, Grass, Sand or a transition type between any of the 2, like, RockSand, GrassWater, etc.

### TerrainBiasCategory
This category is used for the bias. Any terrain bias category that has a higher bias between 0-1 will give a higher chance to the terrain type to be selected for the next tile. So you can make more grassy, more rocky, more watery or more desert like tilemaps.

### TraverseDirection
Traverse direction basically indicates which direction did the observation and entropy collapse trigger from. In entropy collapse method it's then useful to look at a 2nd tile in the same direction to check it's entropy and list of valid neighbours for collapsing the given tile's entropy further.
<br/>
<br/>

## Classes

### BaseTile
BaseTile is the generic tile class that holds the attributes for each tile, including it's entropy and set of valid neighbours. Every tile on the screen is just an instance of this class.

### BiasManager
Bias manager is a simple manager that will initialize with the bias data from the JSON through the data parser, and then for every tile type, runs a bias to return whether that type should be applied to a tile or not. It maintains a list of a biases based on Water, Sand, Grass and Rock type tiles and a sub-list of valid terrain types for each. Bias goes from 0-1. So anything falling under the more biased terrain type, will be more visible.

### DatParser
Data parser will take data from the supplied json location and feed it to Tile and Bias Managers.

### RenderManager
Connecting to Raylib, RenderManager only takes care of trhe rendering bit. It has the render loop and a method to refresh the tile grid.

### SimulationManager
Simulation Manager is the primary class that initializes and connects other classes to each other. The instance of this class is created in main.cpp

### TileManager
TileManager manages the array of tiles along with their BaseTile class attributes. Most of the WFC logic goes in the methods of this.

### Utils
Utils is a simple class with mostly static methods for returning Random ints/floats and checking whether a vector2 value is within range. This can be extended to add more such globally utilzed generic functions.
<br/>
<br/>
## Implementaiton
- Initialize all the components through SimulationManager::InitializeComponents(). This will also initialize a grid of tiles of predecided dimensions.
- The entropy count of every tile at the beginning is 10, which means every tile of any TerrainTileType at this point at the same time, e.g, Rock, Grass, ROckGrassTransition, Water, SandWaterTransition, etc.
- SimulationManager::SetTileToTerrainType() is called to force one of the tiles in the grid to a particular TerrainTileType and force it's entropy to 1. TileManager::ForceTileEntropy() gets called which sets the given tile to a particular type and triggers a chain reaction on every other tile on the grid, starting with this current tile's neighbours.
- TileManager::Observation() is called for every neighbour of a tile whose entropy has been forced to 1. One of the arguments it takes is the direction of observation, which is explained a little later. Let's now consider one of the neighour tiles to be the "current tile".
- Within TileManager::Observation(), multiple checks and return conditions are run before anything else to make sure it doesn't end up in an infinite loop. As it will get clear, Observation() is called recursively for each tile. If all the checks pass, Observation() then calls to collapse the entropy of the tile by running an set intersection of the tile's entropy with the list of valid neighbours of the previous tile whose entropy was forced to 1. This is done through a method called BaseTile::CollapseEntropy(). The set intersection makes sure that the entropy of the current tile is reduced and is in line with the valid TerrainTileTypes the previous tile could have around it.
- If the set intersection in BaseTile::CollapseEntropy() collapses the entropy of the current tile to 1, TileManager::ForceTileEntropy() is simply called internally to properly set the tile to that 1 TerrainTileType left in the entropy.
- If the set intersection in BaseTile::CollapseEntropy() collapses the entropy but the entropy is still > 1, TileManager::CollapseEntropyInDirection() is called to further try to collapse the entropy of the current tile.
- How TileManager::CollapseEntropyInDirection() works is, when the previous tile, whose entropy was forced to 1 starts an Observation on it's neighbours, each neighour is in a particular direction, North (x, y-1), South (x, y+1), East (x+1, y), West (x-1, y). Now when TileManager::CollapseEntropyInDirection() is called on the current tile, a set intersection is run on the entropy of the current tile with a 2nd neighbour in the same direction.
- BaseTile::CollapseEntropy() first checks whether a set intersection between the current tile's entropy and the neighbouring tile's list of valid neighbours yields an entropy of at least 1. If the result of this intersection is 0, then a the method continues forward to check if the intersection betwween the current tile's list of valid neighour's and neighbouring tile's list of valid neighbours yields an entropy of at least 1. If, in case the result of even that is 0, then the method just picks the 1st TerrainTileType from the list of valid neighours of the neighouring tile and gives makes it the entropy of the current tile.
- BaseTile::CollapseEntropy() also uses BiasManager while running the set intersections in each case. Each possible TerrainTileType is passed to the BiasManager and it basically in turn decides whether that TerrainTileType should be a part of the entropy list or not, based on bias values passed to it from the JSON by the SimulationManager during initialization.
- This way, each tile goes through steps of Observation, Entropy Collapse, Repeatation, and the TileManager also automatically takes care of the Propagation steps internally.
<br/>
<br/>
The results are something like this:

![image](https://github.com/user-attachments/assets/a381bab5-395a-454e-b16b-569f3e1b99fa)
![image](https://github.com/user-attachments/assets/081f265e-d1fd-4394-8711-d06ea9a33187)

