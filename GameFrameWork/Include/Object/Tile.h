#pragma once
#include "Object.h"
class Texture;
class BackGround;
class Tile : public Object
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC hDC, float DeltaTime) override;
	void RenderGrid(HDC hDC, float DeltaTime);
	Tile* Clone();
	void Save(FILE* pFile) override;
	void Load(FILE* pFile, Layer* pLayer) override;

	void SetTileType(TILE_TYPE eType);
	void SetTileOption(TILE_OPTION eType);
	TILE_TYPE GetTileType() const { return m_TileType; }
	TILE_OPTION GetTileOption() const { return m_TileOption; }
	Vector2 GetLeftTop() const { return LeftTop; }
	int GetIndex() const { return m_Index; }

private:
	TILE_TYPE	m_TileType;
	TILE_OPTION	m_TileOption;
	int	m_Index;
	Texture* m_LineTexture;
	Texture* m_OptionTexture;
	Vector2 LeftTop;

protected:
	Tile();
	Tile(const Tile& tile);
	~Tile();

public:
	friend class Object;
	friend class TileInfo;
};

