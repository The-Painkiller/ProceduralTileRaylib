#include "SimulationManager.h"

SimulationManager::SimulationManager()
{
	_dataParser = std::unique_ptr<DataParser>(new DataParser());
	_tileManager = std::unique_ptr<TileManager>(new TileManager(GridSizeX, GridSizeY));
	_renderManager = std::unique_ptr<RenderManager>(new RenderManager(GridSizeX, GridSizeY, TileSizeX, TileSizeY));

	_dataParser.get()->Initialize();
}
