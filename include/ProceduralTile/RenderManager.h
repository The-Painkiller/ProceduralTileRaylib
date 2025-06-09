#pragma once
#include"BaseTile.h"
#include <raylib.h>
#include <memory>
#include <string>

struct TileRenderData
{
public:
	std::string InvalidTexturePath;
	std::string GrassTexturePath;
	std::string RockTexturePath;
	std::string SandTexturePath;
	std::string WaterTexturePath;
	std::string RockWaterTexturePath;
	std::string RockSandTexturePath;
	std::string RockGrassTexturePath;
	std::string SandWaterTexturePath;
	std::string SandGrassTexturePath;
	std::string WaterGrassTexturePath;
};

/// <summary>
/// Connecting to Raylib, RenderManager only takes care of trhe rendering bit.
/// It has the render loop and a method to refresh the tile grid.
/// </summary>
class RenderManager
{
public:
	RenderManager() = delete;
	RenderManager(int gridSizeX, int gridSizeY, int tileSize);
	~RenderManager();

	void Initialize(TileRenderData renderData);
	void RenderLoop();
	void RefreshTileGrid(const std::vector<std::vector<std::shared_ptr<BaseTile>>> tileGrid);
	bool ShouldGraphicsWindowClose();
	void CloseGraphicsWindow();

private:
	Vector2 _gridSize;
	int _tileSize;
	
	unsigned int _screenHeight;
	unsigned int _screenWidth;

	std::vector<std::vector<std::shared_ptr<BaseTile>>> _tilesGrid;
	
	TileRenderData _tileRenderData = {};

	float _mouseWheelScroll = 0.0f;
	Camera2D _camera = {};

	Texture2D _grassTexture = {};
	Texture2D _waterTexture = {};
	Texture2D _sandTexture = {};
	Texture2D _rockTexture = {};
	Texture2D _rockGrassTexture = {};
	Texture2D _rockSandTexture = {};
	Texture2D _rockWaterTexture = {};
	Texture2D _sandWaterTexture = {};
	Texture2D _sandGrassTexture = {};
	Texture2D _waterGrassTexture = {};
	Texture2D _invalidTerrainTexture = {};
	
	void LoadRenderData();
	void DrawTileGrid();
	void DrawTile(TerrainTileType tileType, int gridX, int gridY);
};