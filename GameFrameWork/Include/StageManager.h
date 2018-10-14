#pragma once

#include "stdafx.h"

class TileInfo;
class Tile;
class Layer;
class StageManager
{
public:
	bool Init();

	Tile* GetTile(const Vector2& Pos);
	Tile* GetTile(float x, float y);
	TILE_TYPE GetTileType(const Vector2& Pos);
	TILE_TYPE GetTileType(float x, float y);
	int GetTileIndex(const Vector2& Pos);
	int GetTileIndex(float x, float y);
	void SetStageInfo(TileInfo* info);
	int GetWidth();
	int GetHight();
	Vector2 GetTileSize();

	static int LoadMonsterList(const TCHAR* FileName, Layer* InputLayer);
	static int LoadMonsterListSecond(const TCHAR* FileName, Layer* InputLayer, Vector2 Range);

private:
	TileInfo* m_TileInfo;

public:
	CLASS_IN_SINGLE(StageManager);
};

