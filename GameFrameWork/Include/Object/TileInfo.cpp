#include "TileInfo.h"
#include "Tile.h"

#include "../Input.h"
#include "../StageManager.h"
#include "../Camera.h"

#include "../Scene/Layer.h"
#include "../Scene/Scene.h"
#include "../Scene/EditScene.h"

#include "../Resource/Texture.h"

#include "Pump.h"
#include "ItemBox.h"
#include "Rope.h"
#include "TelePoter.h"

TileInfo::TileInfo()
{
	m_ObjectType = OT_BACKGROUND;
	SetTag("BackGorund");
	m_isGrid = true;
	m_VarSize = 0;

	m_vecTile2 = NULL;
}

TileInfo::TileInfo(const TileInfo & Value)
	:Object(Value)
{
	m_WorldSize = Value.m_WorldSize;
	m_NumX = Value.m_NumX;
	m_NumY = Value.m_NumY;
	m_SizeX = Value.m_SizeX;
	m_SizeY = Value.m_SizeY;
	m_SizeMaxX = Value.m_SizeMaxX;
	m_SizeMaxY = Value.m_SizeMaxY;

	m_StartX = Value.m_StartX;
	m_StartY = Value.m_StartY;
	m_EndX = Value.m_EndX;
	m_EndY = Value.m_EndY;
	m_isGrid = Value.m_isGrid;

	m_VarSize = Value.m_VarSize;
	m_vecTile2 = new Tile*[m_VarSize];

	for (int i = 0; i < m_VarSize; i++)
		m_vecTile2[i] = Value.m_vecTile2[i]->Clone();
}

TileInfo::~TileInfo()
{
	for (int i = 0; i < m_VarSize; i++)
		SAFE_RELEASE(m_vecTile2[i]);

	SAFE_DELETE_ARRAY(m_vecTile2);
}

bool TileInfo::Init()
{
	SetPos(0.0f, 0.0f);
	SetSize(1800.0f, 1000.0f);
	SetPivot(0.0f, 0.0f);

	Input::Get()->PushKey("GridShow", VK_F1);

	return true;
}

int TileInfo::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int TileInfo::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	CameraPos = Camera::Get()->GetPos();
	CameraEnd = CameraPos + Core::Get()->GetWinSizeVector2();

	//해당위치의 인덱스를 구한다
	m_StartX = (int)(CameraPos.x / m_SizeX);
	m_StartY = (int)(CameraPos.y / m_SizeY);
	m_EndX = (int)(CameraEnd.x / m_SizeX);
	m_EndY = (int)(CameraEnd.y / m_SizeY);

	if (KEYDOWN("GridShow"))
	{
		if (m_isGrid == false)
			m_isGrid = true;
		else
			m_isGrid = false;
	}

	if (m_StartX < 0)
		m_StartX = 0;
	if (m_StartY < 0)
		m_StartY = 0;

	if (m_EndX >= (int)m_NumX)
		m_EndX = m_NumX - 1;
	if (m_EndY >= (int)m_NumY)
		m_EndY = m_NumY - 1;

	for (int y = m_StartY; y < m_EndY; y++)
	{
		for (int x = m_StartX; x < m_EndX; x++)
		{
			m_vecTile2[y * m_NumX + x]->Update(DeltaTime);
		}
	}

	return 0;
}

int TileInfo::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	for (int y = m_StartY; y < m_EndY; y++)
	{
		for (int x = m_StartX; x < m_EndX; x++)
		{
			m_vecTile2[y * m_NumX + x]->LateUpdate(DeltaTime);
		}
	}
	return 0;
}

void TileInfo::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);

	for (int y = m_StartY; y < m_EndY; y++)
	{
		for (int x = m_StartX; x < m_EndX; x++)
		{
			m_vecTile2[y * m_NumX + x]->Collision(DeltaTime);
		}
	}
}

void TileInfo::Render(HDC Hdc, float DeltaTime)
{
	//배경화면띄우기용
	//TransparentBlt(Hdc, 0, 0, (int)m_Size.x, (int)m_Size.y, m_Texture->GetMemDC(), (int)CameraPos.x, (int)CameraPos.y, (int)m_Size.x, (int)m_Size.y, m_ColorKey);

	for (int y = m_StartY; y < m_EndY; y++)
	{
		for (int x = m_StartX; x < m_EndX; x++)
		{
			m_vecTile2[y * m_NumX + x]->Render(Hdc, DeltaTime);

			if (m_isGrid == true)
				m_vecTile2[y * m_NumX + x]->RenderGrid(Hdc, DeltaTime);
		}//for(x)
	}//for(y)
}

TileInfo * TileInfo::Clone()
{
	return new TileInfo(*this);
}

void TileInfo::CreateGrid(unsigned int NumX, unsigned int NumY, const Vector2 & StageSize, const string & KeyName, const TCHAR * FileName, const string & PathKey)
{
	m_NumX = NumX;
	m_NumY = NumY;

	m_SizeMaxX = StageSize.x;
	m_SizeMaxY = StageSize.y;

	m_SizeX = StageSize.x / NumX;
	m_SizeY = StageSize.y / NumY;

	m_VarSize = m_NumX * m_NumY;

	m_vecTile2 = new Tile*[m_VarSize];	

	for (unsigned int y = 0; y < NumY; y++)
	{
		for (unsigned int x = 0; x < NumX; x++)
		{
			//인덱스 구하는 공식
			int Index = y * m_NumX + x;

			Tile* newTile = new Tile();
			newTile->SetPos(Vector2(x * m_SizeX, y * m_SizeY));
			newTile->SetSize(m_SizeX, m_SizeY);
			newTile->m_Index = Index;
			newTile->AddRefCount();

			if (KeyName.empty() == false)
			{
				if (FileName != NULL)
				{
					newTile->SetTexture(KeyName, FileName, PathKey);
				}
				else
				{
					newTile->SetTexture(KeyName);
				}
			}//if(keyName)
			m_vecTile2[Index] = newTile;
			SAFE_RELEASE(newTile);
		}//for(x)
	}//for(y)
}

Tile * TileInfo::GetTile(const Vector2 & Pos)
{
	return GetTile(Pos.x, Pos.y);
}

Tile * TileInfo::GetTile(float x, float y)
{
	int IndexX = (int)(x / m_SizeX);
	int IndexY = (int)(y / m_SizeY);

	if (IndexX < 0 || IndexX > (int)m_NumX)
		return NULL;
	else if (IndexY < 0 || IndexY > (int)m_NumY)
		return NULL;

	Tile* ReturnTile = m_vecTile2[IndexY * m_NumX + IndexX];
	ReturnTile->AddRefCount();

	return ReturnTile;
}

TILE_TYPE TileInfo::GetTileType(const Vector2 & Pos)
{
	int IndexX = (int)(Pos.x / m_SizeX);
	int IndexY = (int)(Pos.y / m_SizeY);

	if (IndexX < 0 || IndexX >(int)m_NumX)
		return TT_NOMOVE;
	else if (IndexY < 0 || IndexY >(int)m_NumY)
		return TT_NOMOVE;

	return m_vecTile2[IndexY * m_NumX + IndexX]->GetTileType();
}

TILE_TYPE TileInfo::GetTileType(float x, float y)
{
	int IndexX = (int)(x / m_SizeX);
	int IndexY = (int)(y / m_SizeY);

	if (IndexX < 0 || IndexX >(int)m_NumX)
		return TT_NOMOVE;
	else if (IndexY < 0 || IndexY >(int)m_NumY)
		return TT_NOMOVE;

	return m_vecTile2[IndexY * m_NumX + IndexX]->GetTileType();
}

int TileInfo::GetTileIndex(const Vector2 & Pos)
{
	int IndexX = (int)(Pos.x / m_SizeX);
	int IndexY = (int)(Pos.y / m_SizeY);

	if (IndexX < 0 || IndexX >(int)m_NumX)
		return -1;
	else if (IndexY < 0 || IndexY >(int)m_NumY)
		return -1;

	return (IndexY * m_NumX + IndexY);
}

int TileInfo::GetTileIndex(float x, float y)
{
	int IndexX = (int)(x / m_SizeX);
	int IndexY = (int)(y / m_SizeY);

	if (IndexX < 0 || IndexX >(int)m_NumX)
		return -1;
	else if (IndexY < 0 || IndexY >(int)m_NumY)
		return -1;

	return (IndexY * m_NumX + IndexY);
}

void TileInfo::ClearTileMap()
{
	for (unsigned int y = 0; y < m_NumY - 1; y++)
	{
		for (unsigned int x = 0; x < m_NumX - 1; x++)
		{
			unsigned int Index = y * m_NumX + x;

			m_vecTile2[Index]->SetTexture("");
			m_vecTile2[Index]->SetTileOption(TO_NONE);
			m_vecTile2[Index]->SetTileType(TT_NOMAL);
		}
	}
}

void TileInfo::Save(FILE * pFile)
{
	Object::Save(pFile);
	
	fwrite(&m_WorldSize, sizeof(Vector2), 1, pFile);
	fwrite(&m_NumX, sizeof(unsigned int), 1, pFile);
	fwrite(&m_NumY, sizeof(unsigned int), 1, pFile);
	fwrite(&m_SizeX, sizeof(float), 1, pFile);
	fwrite(&m_SizeY, sizeof(float), 1, pFile);
	fwrite(&m_SizeMaxX, sizeof(float), 1, pFile);
	fwrite(&m_SizeMaxY, sizeof(float), 1, pFile);
	fwrite(&m_StartX, sizeof(int), 1, pFile);
	fwrite(&m_StartY, sizeof(int), 1, pFile);
	fwrite(&m_EndX, sizeof(int), 1, pFile);
	fwrite(&m_EndY, sizeof(int), 1, pFile);
	fwrite(&m_VarSize, sizeof(int), 1, pFile);

	for (int i = 0; i < m_VarSize; ++i)
		m_vecTile2[i]->Save(pFile);
}

void TileInfo::Load(FILE* pFile, Layer* pLayer)
{
	Object::Load(pFile, pLayer);

	fread(&m_WorldSize, sizeof(Vector2), 1, pFile);
	fread(&m_NumX, sizeof(unsigned int), 1, pFile);
	fread(&m_NumY, sizeof(unsigned int), 1, pFile);
	fread(&m_SizeX, sizeof(float), 1, pFile);
	fread(&m_SizeY, sizeof(float), 1, pFile);
	fread(&m_SizeMaxX, sizeof(float), 1, pFile);
	fread(&m_SizeMaxY, sizeof(float), 1, pFile);
	fread(&m_StartX, sizeof(int), 1, pFile);
	fread(&m_StartY, sizeof(int), 1, pFile);
	fread(&m_EndX, sizeof(int), 1, pFile);
	fread(&m_EndY, sizeof(int), 1, pFile);

	fread(&m_VarSize, sizeof(int), 1, pFile);

	m_vecTile2 = new Tile*[m_VarSize];

	for (int i = 0; i < m_VarSize; ++i)
	{
		Tile* newTile = new Tile();
		newTile->Init();
		newTile->Load(pFile, pLayer);

		//////////////////////////////////////////////
		if (newTile->GetTileOption() == TO_ITEM)
		{
			if (pLayer->GetTag() == "PlayLayer")
			{
				ItemBox* newBox = Object::CreateObject<ItemBox>("ItemBox", pLayer);
				newBox->SetPos(Vector2(newTile->GetPos().x + 25.0f, newTile->GetPos().y - newBox->GetSize().GetHalfY()));
				SAFE_RELEASE(newBox);
			}
			newTile->SetTileOption(TO_ITEM);
		}
		else if (newTile->GetTileOption() == TO_TELEPOT)
		{
			if (pLayer->GetTag() == "PlayLayer")
			{
				TelePoter* newTelePoter = Object::CreateObject<TelePoter>("TelePoter", pLayer);
				newTelePoter->SetPos(Vector2(newTile->GetPos().x, newTile->GetPos().y - newTelePoter->GetSize().GetHalfY()));
				SAFE_RELEASE(newTelePoter);
			}

			newTile->SetTileOption(TO_TELEPOT);
		}
		else if (newTile->GetTileOption() == TO_PUMP)
		{
			if (pLayer->GetTag() == "PlayLayer")
			{
				Pump* newPump = Object::CreateObject<Pump>("Pump", pLayer);
				newPump->SetPos(Vector2(newTile->GetPos().x + 25.0f, newTile->GetPos().y - newPump->GetSize().GetHalfY()));
				SAFE_RELEASE(newPump);
			}
			newTile->SetTileOption(TO_PUMP);
		}
		m_vecTile2[i] = newTile;
	}

	for (unsigned int y = 0; y < m_NumY - 1; y++)
	{
		for (unsigned int x = 0; x < m_NumX - 1; x++)
		{
			Tile* SerchTile = m_vecTile2[y * m_NumX + x];

			if (SerchTile->GetTileOption() != TO_ROPE)
				continue;

			if (pLayer->GetTag() != "PlayLayer")
			{
				SerchTile->SetTileOption(TO_ROPE);
				continue;
			}

			Vector2 TempPos = SerchTile->GetPos();
			Vector2 TempSize = { 12,0 };
			Tile* TempTile = SerchTile;

			SerchTile->SetTileOption(TO_ROPE);

			Rope* newRope = Object::CreateObject<Rope>("Rope", pLayer);
			newRope->SetPos(Vector2(TempPos.x + SerchTile->GetSize().GetHalfX(), TempPos.y + 30.0f));

			TempTile = GetTile(Vector2(TempPos.x, TempPos.y + SerchTile->GetSize().y));

			while(TempTile->GetTileType() != TT_NOMOVE)
			{
				TempPos.y++;
				TempSize.y++;

				TempTile = GetTile(Vector2(TempPos.x, TempPos.y + SerchTile->GetSize().y + 30.0f));

				newRope->SetSize(TempSize.x, TempSize.y - SerchTile->GetSize().y);
			}//while(true)
		}
	}

	StageManager::Get()->SetStageInfo(this);
}