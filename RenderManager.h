#pragma once
#include"BaseTile.h"
#include <raylib.h>
#include <memory>
#include <string>

/// <summary>
/// All char pointers are arrays of 2.
/// Index 0: Plain texture,
/// Index 1: Transition texture.
/// </summary>
struct TileRenderData
{
public:
	static unsigned int TextureArraySize;
	std::vector<std::string> GrassTexturePaths;
	std::vector<std::string> RockTexturePaths;
	std::vector<std::string> SandTexturePaths;
	std::vector<std::string> WaterTexturePaths;
};

class RenderManager
{
public:
	RenderManager() = delete;
	RenderManager(int gridSizeX, int gridSizeY, int tileSizeX, int tileSizeY);
	~RenderManager();

	void Initialize(TileRenderData renderData);
	void RenderLoop();
	void RefreshTileGrid(const std::vector<std::vector<std::shared_ptr<BaseTile>>> tileGrid);
	bool ShouldGraphicsWindowClose();
	void CloseGraphicsWindow();

private:
	Vector2 _gridSize;
	Vector2 _tileSize;
	
	unsigned int _screenHeight;
	unsigned int _screenWidth;

	std::vector<std::vector<std::shared_ptr<BaseTile>>> _tilesGrid;
	
	TileRenderData _tileRenderData = {};

	float _mouseWheelScroll = 0.0f;
	Camera2D _camera = {};

	Texture2D _grassTextures[2] = {};
	Texture2D _waterTextures[2] = {};
	Texture2D _sandTextures[2] = {};
	Texture2D _rockTextures[2] = {};
	Texture2D _invalidTerrainTexture = Texture2D();
	
	void LoadRenderData();
	void DrawTileGrid();
	void DrawTile(TerrainTileType tileType, bool isTransitionTile, int gridX, int gridY);
};