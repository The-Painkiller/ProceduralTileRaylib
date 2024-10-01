#pragma once
#include"BaseTile.h"
#include <raylib.h>

/// <summary>
/// All char pointers are arrays of 2.
/// Index 0: Plain texture,
/// Index 1: Transition texture.
/// </summary>
struct TileRenderData
{
public:
	static unsigned int TextureArraySize;
	char* GrassTexturePaths[2];
	char* RockTexturePaths[2];
	char* SandTexturePaths[2];
	char* WaterTexturePaths[2];
};

unsigned int TileRenderData::TextureArraySize = 2;

class RenderManager
{
public:
	RenderManager() = delete;
	RenderManager(Vector2 gridSize, Vector2 tileSize);

	void Initialize(TileRenderData renderData);
	void RenderLoop(const BaseTile** tileArray);

private:
	Vector2 _gridSize;
	Vector2 _tileSize;
	
	unsigned int _screenHeight;
	unsigned int _screenWidth;
	
	TileRenderData _tileRenderData = {};

	float _mouseWheelScroll = 0.0f;
	Camera2D _camera = {};

	Texture2D _grassTextures[2];
	Texture2D _waterTextures[2];
	Texture2D _sandTextures[2];
	Texture2D _rockTextures[2];
	
	void LoadRenderData();
	void Draw(const BaseTile** tileArray);
};