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
	}

	_renderManager->CloseGraphicsWindow();
	return false;
}

void SimulationManager::InitializeComponents()
{
	_dataParser->Initialize();
	_tileManager->InitializeTileGrid();

	TileRenderData renderData = {};
	TileRenderData::TextureArraySize = 2;
	for (int i = 0; i < TileRenderData::TextureArraySize; i++)
	{
		renderData.GrassTexturePaths.push_back(_dataParser->GetTileData(Grass).TileTexturePaths[i]);
		renderData.RockTexturePaths.push_back(_dataParser->GetTileData(Rock).TileTexturePaths[i]);
		renderData.SandTexturePaths.push_back(_dataParser->GetTileData(Sand).TileTexturePaths[i]);
		renderData.WaterTexturePaths.push_back(_dataParser->GetTileData(Grass).TileTexturePaths[i]);
	}

	_renderManager->Initialize(renderData);
	_renderManager->RefreshTileGrid(_tileManager->GetTileArray());
}
