#include "Tile.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Texture.h"
#include "../Camera.h"

Tile::Tile()
{
	m_TileType = TT_NOMAL;
	m_TileOption = TO_NONE;
	m_LineTexture = ResourceManager::Get()->LoadTexture("TileTypeNomal", TEXT("Tile/OptionNone.bmp"));
	m_OptionTexture = NULL;
	SetColorKey(RGB(255, 0, 255));
}

Tile::Tile(const Tile & tile)
	:Object(tile)
{
	m_TileType = tile.m_TileType;
	m_TileOption = tile.m_TileOption;
	m_LineTexture = tile.m_LineTexture;
	m_OptionTexture = tile.m_OptionTexture;

	if (m_LineTexture != NULL)
		m_LineTexture->AddRefCount();
	if (m_OptionTexture != NULL)
		m_OptionTexture->AddRefCount();
}

Tile::~Tile()
{
	SAFE_RELEASE(m_LineTexture);
	SAFE_RELEASE(m_OptionTexture);
}

bool Tile::Init()
{
	return true;
}

int Tile::Input(float DeltaTime)
{
	return 0;
}

int Tile::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int Tile::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void Tile::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void Tile::Render(HDC hDC, float DeltaTime)
{
	//타일의 원본이미지
	Object::Render(hDC, DeltaTime);
}

Tile * Tile::Clone()
{
	return new Tile(*this);
}

void Tile::Save(FILE * pFile)
{
	Object::Save(pFile);

	fwrite(&m_TileType, sizeof(TILE_TYPE), 1, pFile);
	fwrite(&m_TileOption, sizeof(TILE_OPTION), 1, pFile);
	fwrite(&m_Index, sizeof(int), 1, pFile);
}

void Tile::Load(FILE * pFile, Layer* pLayer)
{
	Object::Load(pFile, pLayer);

	fread(&m_TileType, sizeof(TILE_TYPE), 1, pFile);
	fread(&m_TileOption, sizeof(TILE_OPTION), 1, pFile);
	fread(&m_Index, sizeof(int), 1, pFile);

	SAFE_RELEASE(m_LineTexture);

	switch (m_TileType)
	{
		case TT_NOMAL:
			m_LineTexture = ResourceManager::Get()->LoadTexture("TileTypeNormal", TEXT("Tile/OptionNone.bmp"));
			break;
		case TT_NOMOVE:
			m_LineTexture = ResourceManager::Get()->LoadTexture("TileTypeNoMove", TEXT("Tile/OptionNoMove.bmp"));
			break;
	}
}

void Tile::RenderGrid(HDC hDC, float DeltaTime)
{
	Vector2 CameraPos = Camera::Get()->GetPos();
	LeftTop = m_Pos - m_Size * m_Pivot;

	if (isCameraMode == true)
		LeftTop -= CameraPos;

	//타일의 라인(외곽선이미지)
	TransparentBlt(hDC, (int)LeftTop.x, (int)LeftTop.y, (int)m_Size.x, (int)m_Size.y, m_LineTexture->GetMemDC(), 0, 0, (int)m_Size.x, (int)m_Size.y, m_ColorKey);

	if(m_OptionTexture != NULL)
		TransparentBlt(hDC, (int)LeftTop.x, (int)LeftTop.y, (int)m_Size.x, (int)m_Size.y, m_OptionTexture->GetMemDC(), 0, 0, (int)m_Size.x, (int)m_Size.y, m_ColorKey);

}

void Tile::SetTileType(TILE_TYPE eType)
{
	m_TileType = eType;

	switch (m_TileType)
	{
		case TT_NOMAL:
			m_LineTexture = ResourceManager::Get()->LoadTexture("TileTypeNomal", TEXT("Tile/OptionNone.bmp"));
			break;
		case TT_NOMOVE:
			m_LineTexture = ResourceManager::Get()->LoadTexture("TileTypeNoMove", TEXT("Tile/OptionNoMove.bmp"));
			break;
	}
}

void Tile::SetTileOption(TILE_OPTION eType)
{
	m_TileOption = eType;

	switch (eType)
	{
		case TO_NONE:
			m_OptionTexture = NULL;
			break;
		case TO_ITEM:
			m_OptionTexture = ResourceManager::Get()->LoadTexture("ItemBoxOption", TEXT("Tile/ItemTileOption.bmp"));
			m_TileOption = TO_ITEM;
			break;
		case TO_ROPE:
			m_OptionTexture = ResourceManager::Get()->LoadTexture("RopeOption", TEXT("Tile/RopeTileOption.bmp"));
			m_TileOption = TO_ROPE;
			break;
		case TO_PUMP:
			m_OptionTexture = ResourceManager::Get()->LoadTexture("PumpOption", TEXT("Tile/JumpTileOption.bmp"));
			m_TileOption = TO_PUMP;
			break;
		case TO_TELEPOT:
			m_OptionTexture = ResourceManager::Get()->LoadTexture("TelePoterOption", TEXT("Tile/TelepotOption.bmp"));
			m_TileOption = TO_TELEPOT;
			break;
	}
}