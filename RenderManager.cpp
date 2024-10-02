#include "RenderManager.h"

unsigned int TileRenderData::TextureArraySize = 2;

RenderManager::RenderManager(int gridSizeX, int gridSizeY, int tileSizeX, int tileSizeY)
{
	_gridSize.x = gridSizeX;
	_gridSize.y = gridSizeY;

	_tileSize.x = tileSizeX;
	_tileSize.y = tileSizeY;
	_screenWidth = tileSizeX * gridSizeX;
	_screenHeight = tileSizeY * gridSizeY;

	InitWindow(_screenWidth, _screenHeight, "Procedural 2D Terrain");
	SetTargetFPS(60);

}

void RenderManager::RenderLoop(BaseTile** tileArray)
{
	BeginDrawing();
	ClearBackground(LIGHTGRAY);
	BeginMode2D(_camera);
	DrawTileGrid(tileArray);
	EndMode2D();
	EndDrawing();
}

void RenderManager::DrawTileGrid(BaseTile** tileArray)
{
	for (int i = 0; i < _gridSize.x; i++)
	{
		for (int j = 0; j < _gridSize.y; j++)
		{
			DrawTile(tileArray[i][j].GetTerrainTileType(), tileArray[i][j].IsTransitionTile(), i, j);
		}
	}
}

void RenderManager::DrawTile(TerrainTileType tileType, bool isTransitionTile, int gridX, int gridY)
{
	int textureIndex = isTransitionTile ? 1 : 0;
	switch (tileType)
	{
	case Rock:
	{
		DrawTexture(_rockTextures[textureIndex], gridX * _gridSize.x, gridY * _gridSize.y, WHITE);
		break;
	}
	case Grass:
	{
		DrawTexture(_grassTextures[textureIndex], gridX * _gridSize.x, gridY * _gridSize.y, WHITE);
		break;
	}
	case Sand:
	{
		DrawTexture(_sandTextures[textureIndex], gridX * _gridSize.x, gridY * _gridSize.y, WHITE);
		break;
	}
	case Water:
	{
		DrawTexture(_waterTextures[textureIndex], gridX * _gridSize.x, gridY * _gridSize.y, WHITE);
		break;
	}
	case TerrainTileTypeCount:
	case InvalidTileType:
	default:
	{
		DrawTexture(_invalidTerrainTexture, gridX * _gridSize.x, gridY * _gridSize.y, WHITE);
		break;
	}
	}
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