#pragma once
#include "DataParser.h"
#include "RenderManager.h"
#include "TileManager.h"
#include "Utils.h";

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

	const int GridSizeX = 10;
	const int GridSizeY = 10;
	const int TileSize = 64;
};