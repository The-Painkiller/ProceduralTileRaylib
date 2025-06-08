#include "RenderManager.h"

RenderManager::RenderManager(int gridSizeX, int gridSizeY, int tileSize)
{
	_gridSize.x = (float)gridSizeX;
	_gridSize.y = (float)gridSizeY;

	_tileSize = tileSize;
	_screenWidth = tileSize * gridSizeX;
	_screenHeight = tileSize * gridSizeY;

	_camera.rotation = 0.0f;
	_camera.zoom = 1.0f;

	_tilesGrid.reserve(gridSizeX);

	InitWindow(_screenWidth, _screenHeight, "Procedural 2D Terrain");
	SetTargetFPS(60);
}

RenderManager::~RenderManager()
{
	_tilesGrid.clear();
	_camera = {};
	_tileRenderData = {};

		_grassTexture = {};
		_sandTexture = {};
		_waterTexture = {};
		_rockTexture = {};
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
			DrawTile(_tilesGrid[i][j].get()->GetTerrainTileType(), i, j);
		}
	}
}

void RenderManager::DrawTile(TerrainTileType tileType, int gridX, int gridY)
{
	switch (tileType)
	{
	case Rock:
	{
		DrawTexture(_rockTexture, gridX * _tileSize, gridY * _tileSize, WHITE);
		break;
	}
	case Grass:
	{
		DrawTexture(_grassTexture, gridX * _tileSize, gridY * _tileSize, WHITE);
		break;
	}
	case Sand:
	{
		DrawTexture(_sandTexture, gridX * _tileSize, gridY * _tileSize, WHITE);
		break;
	}
	case Water:
	{
		DrawTexture(_waterTexture, gridX * _tileSize, gridY * _tileSize, WHITE);
		break;
	}
	case RockGrassTransition:
	{
		DrawTexture(_rockGrassTexture, gridX * _tileSize, gridY * _tileSize, WHITE);
		break;
	}
	case RockSandTransition:
	{
		DrawTexture(_rockSandTexture, gridX * _tileSize, gridY * _tileSize, WHITE);
		break;
	}
	case RockWaterTransition:
	{
		DrawTexture(_rockWaterTexture, gridX * _tileSize, gridY * _tileSize, WHITE);
		break;
	}
	case SandGrassTransition:
	{
		DrawTexture(_sandGrassTexture, gridX * _tileSize, gridY * _tileSize, WHITE);
		break;
	}
	case SandWaterTransition:
	{
		DrawTexture(_sandWaterTexture, gridX * _tileSize, gridY * _tileSize, WHITE);
		break;
	}
	case WaterGrassTransition:
	{
		DrawTexture(_waterGrassTexture, gridX * _tileSize, gridY * _tileSize, WHITE);
	}
	case TerrainTileTypeCount:
	case InvalidTileType:
	default:
	{
		DrawTexture(_invalidTerrainTexture, gridX * _tileSize, gridY * _tileSize, WHITE);
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
	_grassTexture = LoadTexture(_tileRenderData.GrassTexturePath.c_str());
	_sandTexture = LoadTexture(_tileRenderData.SandTexturePath.c_str());
	_waterTexture = LoadTexture(_tileRenderData.WaterTexturePath.c_str());
	_rockTexture = LoadTexture(_tileRenderData.RockTexturePath.c_str());
	_rockGrassTexture = LoadTexture(_tileRenderData.RockGrassTexturePath.c_str());
	_rockSandTexture = LoadTexture(_tileRenderData.RockSandTexturePath.c_str());
	_rockWaterTexture = LoadTexture(_tileRenderData.RockWaterTexturePath.c_str());
	_sandGrassTexture = LoadTexture(_tileRenderData.SandGrassTexturePath.c_str());
	_sandWaterTexture = LoadTexture(_tileRenderData.SandWaterTexturePath.c_str());
	_waterGrassTexture = LoadTexture(_tileRenderData.WaterGrassTexturePath.c_str());
	_invalidTerrainTexture = LoadTexture(_tileRenderData.InvalidTexturePath.c_str());
}