#include "SimulationManager.h"

SimulationManager::SimulationManager()
{
	_dataParser = std::shared_ptr<DataParser>(new DataParser());
	_tileManager = std::unique_ptr<TileManager>(new TileManager(GlobalHeader::GridSizeX, GlobalHeader::GridSizeY, _dataParser));
	_renderManager = std::unique_ptr<RenderManager>(new RenderManager(GlobalHeader::GridSizeX, GlobalHeader::GridSizeY, GlobalHeader::TileSize));
	_biasManager = std::unique_ptr<BiasManager>(new BiasManager());
	Utils(GlobalHeader::GridSizeX, GlobalHeader::GridSizeY);
}

bool SimulationManager::SimulationLoop()
{
	// Forcing 2 tiles to rock and water initially.
	SetTileToTerrainType(Vector2{ 4, 4 }, Rock);
	SetTileToTerrainType(Vector2{ 1, 3 }, Water);

	// TODO: In the future, use this loop to dynamically place tiles using a UI.
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

	InitializeTileRenderData();
	InitializeBiasManagerData();
}

void SimulationManager::InitializeBiasManagerData()
{
	std::vector<BiasData> biasData;
	for (int i = 0; i < TerrainBiasCategory::TerrainBiasCategoryCount; i++)
	{
		biasData.push_back(_dataParser->GetTerrainTypeBiasData((TerrainBiasCategory)i));
	}

	_biasManager->InitializeData(biasData);
}

void SimulationManager::InitializeTileRenderData()
{
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
	renderData.WaterGrassTexturePath = _dataParser->GetTileData(WaterGrassTransition).TileTexturePath;

	_renderManager->Initialize(renderData);
	_renderManager->RefreshTileGrid(_tileManager->GetTileArray());
}

void SimulationManager::SetTileToTerrainType(const Vector2 tileLocation, const TerrainTileType terrainType)
{
	ForceTileEntropy(tileLocation, Rock, _dataParser->GetTileData(terrainType).ValidNeighbours);
	PrintTileArray();
}

void SimulationManager::ForceTileEntropy(const Vector2 tileLocation, const TerrainTileType tileType, const std::vector<TerrainTileType> validNeighbours)
{
    _tileManager->ClearTileIterations();
    _tileManager->ForceTileEntropy(tileLocation, tileType, validNeighbours);
}

void SimulationManager::PrintTileArray()
{
    for (int i = 0; i < _tileManager->GetTileArray().size(); i++)
    {
        for (int j = 0; j < _tileManager->GetTileArray()[i].size(); j++)
        {
			Utils::PrintTileType(j, i, _tileManager->GetTileArray()[j][i]->GetTerrainTileType());
        }
    }
}