#pragma once
#include "DataParser.h"
#include "RenderManager.h"
#include "TileManager.h"
#include "Utils.h"
#include "BiasManager.h"

/// <summary>
/// Simulation Manager is the primary class that initializes and connects other classes to each other.
/// </summary>
class SimulationManager
{
public:
	SimulationManager();
	~SimulationManager() = default;

	void InitializeComponents();
	void ForceTileEntropy(const Vector2 tileLocation, const TerrainTileType tileType, const std::vector<TerrainTileType> validNeighbours);
	bool SimulationLoop();

private:
	std::shared_ptr<DataParser> _dataParser;
	std::unique_ptr<RenderManager> _renderManager;
	std::unique_ptr<TileManager> _tileManager;
	std::unique_ptr<BiasManager> _biasManager;

	void InitializeBiasManagerData();
	void InitializeTileRenderData();
	void SetTileToTerrainType(const Vector2 tileLocation, const TerrainTileType terrainType);
	void PrintTileArray();
};