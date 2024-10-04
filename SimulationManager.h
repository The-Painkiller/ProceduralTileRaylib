#pragma once
#include "DataParser.h"
#include "RenderManager.h"
#include "TileManager.h"

class SimulationManager
{
public:
	SimulationManager();
	~SimulationManager() = default;

private:
	std::unique_ptr<DataParser> _dataParser;
	std::unique_ptr<RenderManager> _renderManager;
	std::unique_ptr<TileManager> _tileManager;

	const int GridSizeX = 20;
	const int GridSizeY = 20;
	const int TileSizeX = 256;
	const int TileSizeY = 256;
};