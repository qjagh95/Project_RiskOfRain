#pragma once
#include "Object.h"
class Tile;
class TileInfo : public Object
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	TileInfo* Clone() override;

	void Save(FILE* pFile);
	void Load(FILE* pFile, Layer* pLayer);

	void SetWorldSize(const Vector2& _Size) { m_WorldSize = _Size; }
	void SetWorldSize(float x, float y) { m_WorldSize = Vector2(x, y); }
	void SetGridShow(bool Value) { m_isGrid = Value; }
	bool GetGridSohw() const { return m_isGrid; }
	unsigned int GetTileWidthCount() const { return m_NumX; }
	unsigned int GetTileHeightCount() const { return m_NumY; }

	Tile* GetTile(const Vector2& Pos);
	Tile* GetTile(float x, float y);
	TILE_TYPE GetTileType(const Vector2& Pos);
	TILE_TYPE GetTileType(float x, float y);
	int GetTileIndex(const Vector2& Pos);
	int GetTileIndex(float x, float y);
	void SetIsGrid(bool Value) { m_isGrid = Value; }
	void ClearTileMap();
	void CreateGrid(unsigned int NumX, unsigned int NumY, const Vector2& StageSize, const string& KeyName = "", const TCHAR* FileName = NULL, const string& PathKey = TEXTURE_PATH);

private:
	Vector2 m_WorldSize;
	Vector2 CameraPos;
	Vector2 CameraEnd;

	unsigned int m_NumX;     ///타일갯수X
	unsigned int m_NumY;     ///타일갯수Y
	float m_SizeX;           ///타일사이즈X (총길이 / 갯수)
	float m_SizeY;           ///타일사이즈Y (총길이 / 갯수)        
	float m_SizeMaxX;        ///스테이지 사이즈X(총길이)
	float m_SizeMaxY;        ///스테이지 사이즈Y

	int m_StartX;            ///화면위치에만 뿌리기하여 인덱스를 찾기위한 변수
	int m_StartY;            ///화면위치에만 뿌리기하여 인덱스를 찾기위한 변수
	int m_EndX;              ///화면위치에만 뿌리기하여 인덱스를 찾기위한 변수
	int m_EndY;				 ///화면위치에만 뿌리기하여 인덱스를 찾기위한 변수
	bool m_isGrid;

	int m_VarSize;

	Tile** m_vecTile2;

protected:
	TileInfo();
	TileInfo(const TileInfo& Value);
	~TileInfo();

public:
	friend class Object;
	friend class Scene;
};

