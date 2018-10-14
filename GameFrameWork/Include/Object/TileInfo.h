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

	unsigned int m_NumX;     ///Ÿ�ϰ���X
	unsigned int m_NumY;     ///Ÿ�ϰ���Y
	float m_SizeX;           ///Ÿ�ϻ�����X (�ѱ��� / ����)
	float m_SizeY;           ///Ÿ�ϻ�����Y (�ѱ��� / ����)        
	float m_SizeMaxX;        ///�������� ������X(�ѱ���)
	float m_SizeMaxY;        ///�������� ������Y

	int m_StartX;            ///ȭ����ġ���� �Ѹ����Ͽ� �ε����� ã������ ����
	int m_StartY;            ///ȭ����ġ���� �Ѹ����Ͽ� �ε����� ã������ ����
	int m_EndX;              ///ȭ����ġ���� �Ѹ����Ͽ� �ε����� ã������ ����
	int m_EndY;				 ///ȭ����ġ���� �Ѹ����Ͽ� �ε����� ã������ ����
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

