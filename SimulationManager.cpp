#include "SimulationManager.h"

SimulationManager::SimulationManager()
{
	_dataParser = std::unique_ptr<DataParser>(new DataParser());
	_tileManager = std::unique_ptr<TileManager>(new TileManager(GridSizeX, GridSizeY));
	_renderManager = std::unique_ptr<RenderManager>(new RenderManager(GridSizeX, GridSizeY, TileSizeX, TileSizeY));
}

bool SimulationManager::SimulationLoop()
{
	while (!_renderManager->ShouldGraphicsWindowClose())
	{
		_renderManager->RenderLoop();

		if (_tileManager->ReiteratePossibilities())
		{
			_renderManager->RefreshTileGrid(_tileManager->GetTileArray());
		}
	}

	_renderManager->CloseGraphicsWindow();
	return false;
}

void SimulationManager::InitializeComponents()
{
	_dataParser->Initialize();
	_tileManager->InitializeTileGrid();

	_tileManager->GetTileArray()[5][5].get()->ForceSetTile(Rock, TileSizeX);
	_tileManager->GetTileArray()[1][19].get()->ForceSetTile(Water, TileSizeX);

	TileRenderData renderData = {};
	renderData.GrassTexturePath = _dataParser->GetTileData(Grass).TileTexturePath;
	renderData.RockTexturePath = _dataParser->GetTileData(Rock).TileTexturePath;
	renderData.SandTexturePath = _dataParser->GetTileData(Sand).TileTexturePath;
	renderData.WaterTexturePath = _dataParser->GetTileData(Water).TileTexturePath;
	renderData.RockGrassTexturePath = _dataParser->GetTileData(RockGrassTransition).TileTexturePath;
	renderData.RockSandTexturePath = _dataParser->GetTileData(RockSandTransition).TileTexturePath;
	renderData.RockWaterTexturePath = _dataParser->GetTileData(RockWaterTransition).TileTexturePath;
	renderData.SandGrassTexturePath = _dataParser->GetTileData(SandGrassTransition).TileTexturePath;
	renderData.SandWaterTexturePath = _dataParser->GetTileData(SandWaterTransition).TileTexturePath;

	_renderManager->Initialize(renderData);
	_renderManager->RefreshTileGrid(_tileManager->GetTileArray());
}
