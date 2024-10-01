#include "RenderManager.h"

RenderManager::RenderManager(Vector2 gridSize, Vector2 tileSize)
{
	_gridSize = gridSize;
	_tileSize = tileSize;
	_screenWidth = tileSize.x * gridSize.x;
	_screenHeight = tileSize.y * gridSize.y;

	InitWindow(_screenWidth, _screenHeight, "Procedural 2D Terrain");
	SetTargetFPS(60);

}

void RenderManager::RenderLoop(const BaseTile** tileArray)
{
	BeginDrawing();
	ClearBackground(LIGHTGRAY);
	BeginMode2D(_camera);
	Draw(tileArray);
	EndMode2D();
	EndDrawing();
}

void RenderManager::Draw(const BaseTile** tileArray)
{
	///DrawTextureRec
}

void RenderManager::Initialize(TileRenderData renderData)
{
	_tileRenderData = renderData;
	LoadRenderData();
}

void RenderManager::LoadRenderData()
{
	for (int i = 0; i < TileRenderData::TextureArraySize; i++)
	{
		_grassTextures[i] = LoadTexture(_tileRenderData.GrassTexturePaths[i]);
		_sandTextures[i] = LoadTexture(_tileRenderData.SandTexturePaths[i]);
		_waterTextures[i] = LoadTexture(_tileRenderData.WaterTexturePaths[i]);
		_rockTextures[i] = LoadTexture(_tileRenderData.RockTexturePaths[i]);
	}
}