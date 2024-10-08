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

	_camera.rotation = 0.0f;
	_camera.zoom = 1.0f;

	InitWindow(_screenWidth, _screenHeight, "Procedural 2D Terrain");
	SetTargetFPS(60);
}

RenderManager::~RenderManager()
{
	_tilesGrid.clear();
	_camera = {};
	_tileRenderData = {};

	for (int i = 0; i < TileRenderData::TextureArraySize; i++)
	{
		_grassTextures[i] = {};
		_sandTextures[i] = {};
		_waterTextures[i] = {};
		_rockTextures[i] = {};
	}
}

void RenderManager::RenderLoop()
{
	BeginDrawing();
	ClearBackground(LIGHTGRAY);
	BeginMode2D(_camera);
	DrawTileGrid();
	EndMode2D();
	EndDrawing();
}

void RenderManager::DrawTileGrid()
{
	for (int i = 0; i < _gridSize.x; i++)
	{
		for (int j = 0; j < _gridSize.y; j++)
		{
			DrawTile(_tilesGrid[i][j].get()->GetTerrainTileType(), _tilesGrid[i][j].get()->IsTransitionTile(), i, j);
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
		DrawTexture(_rockTextures[textureIndex], gridX * _tileSize.x, gridY * _tileSize.y, WHITE);
		break;
	}
	case Grass:
	{
		DrawTexture(_grassTextures[textureIndex], gridX * _tileSize.x, gridY * _tileSize.y, WHITE);
		break;
	}
	case Sand:
	{
		DrawTexture(_sandTextures[textureIndex], gridX * _tileSize.x, gridY * _tileSize.y, WHITE);
		break;
	}
	case Water:
	{
		DrawTexture(_waterTextures[textureIndex], gridX * _tileSize.x, gridY * _tileSize.y, WHITE);
		break;
	}
	case TerrainTileTypeCount:
	case InvalidTileType:
	default:
	{
		DrawTexture(_invalidTerrainTexture, gridX * _tileSize.x, gridY * _tileSize.y, WHITE);
		break;
	}
	}
}

void RenderManager::Initialize(TileRenderData renderData)
{
	_tileRenderData = renderData;
	LoadRenderData();
}

void RenderManager::RefreshTileGrid(const std::vector<std::vector<std::shared_ptr<BaseTile>>> tileGrid)
{
	_tilesGrid = tileGrid;
}

bool RenderManager::ShouldGraphicsWindowClose()
{
	return WindowShouldClose();
}

void RenderManager::CloseGraphicsWindow()
{
	CloseWindow();
}

void RenderManager::LoadRenderData()
{
	for (int i = 0; i < TileRenderData::TextureArraySize; i++)
	{
		_grassTextures[i] = LoadTexture(_tileRenderData.GrassTexturePaths[i].c_str());
		_sandTextures[i] = LoadTexture(_tileRenderData.SandTexturePaths[i].c_str());
		_waterTextures[i] = LoadTexture(_tileRenderData.WaterTexturePaths[i].c_str());
		_rockTextures[i] = LoadTexture(_tileRenderData.RockTexturePaths[i].c_str());
	}
}