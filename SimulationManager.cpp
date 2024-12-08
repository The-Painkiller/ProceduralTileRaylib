#include "SimulationManager.h"

SimulationManager::SimulationManager()
{
	_dataParser = std::shared_ptr<DataParser>(new DataParser());
	_tileManager = std::unique_ptr<TileManager>(new TileManager(GridSizeX, GridSizeY, _dataParser));
	_renderManager = std::unique_ptr<RenderManager>(new RenderManager(GridSizeX, GridSizeY, GlobalHeader::TileSize));
}

bool SimulationManager::SimulationLoop()
{
	while (!_renderManager->ShouldGraphicsWindowClose())
	{
		_renderManager->RenderLoop();

		//if (_tileManager->Obervation()
		//{
		//	_renderManager->RefreshTileGrid(_tileManager->GetTileArray());
		//}
	}

	_renderManager->CloseGraphicsWindow();
	return false;
}

void SimulationManager::InitializeComponents()
{
	_dataParser->Initialize();
	_tileManager->InitializeTileGrid();

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
	
	
	_tileManager->ForceTileEntropy(Vector2{ 5, 5 }, Rock, _dataParser->GetTileData(Rock).ValidNeighbours);
	_tileManager->ForceTileEntropy(Vector2{ 1, 3 }, Water, _dataParser->GetTileData(Water).ValidNeighbours);
}