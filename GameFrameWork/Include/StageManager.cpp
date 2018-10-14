#include "StageManager.h"

#include "Resource\PathManager.h"

#include "Object\Tile.h"
#include "Object\TileInfo.h"

#include "Object\Monster.h"
#include "Object/IssacEnemy1.h"

#include "Scene\Layer.h"


INIT_STATIC_VAR(StageManager)

StageManager::StageManager()
	:m_TileInfo(NULL)
{
}

StageManager::~StageManager()
{
	SAFE_RELEASE(m_TileInfo);
}

bool StageManager::Init()
{
	return true;
}

Tile * StageManager::GetTile(const Vector2 & Pos)
{
	return m_TileInfo->GetTile(Pos);
}

Tile * StageManager::GetTile(float x, float y)
{
	return GetTile(Vector2(x, y));
}

TILE_TYPE StageManager::GetTileType(const Vector2 & Pos)
{
	return m_TileInfo->GetTileType(Pos);
}

TILE_TYPE StageManager::GetTileType(float x, float y)
{
	return GetTileType(Vector2(x, y));
}

int StageManager::GetTileIndex(const Vector2 & Pos)
{
	return m_TileInfo->GetTileIndex(Pos);
}

int StageManager::GetTileIndex(float x, float y)
{
	return GetTileIndex(Vector2(x,y));
}

void StageManager::SetStageInfo(TileInfo * info)
{
	SAFE_RELEASE(m_TileInfo);

	if (info != NULL)
		info->AddRefCount();

	m_TileInfo = info;
}

int StageManager::GetWidth()
{
	return (int)(m_TileInfo->GetTileWidthCount() * m_TileInfo->GetSize().x);
}

int StageManager::GetHight()
{
	return (int)(m_TileInfo->GetTileHeightCount() * m_TileInfo->GetSize().y);
}

Vector2 StageManager::GetTileSize()
{
	return m_TileInfo->GetTileSize();
}

void StageManager::LoadMonsterList(const TCHAR * FileName, Layer * InputLayer)
{
	const char* pPath = PathManager::Get()->FindPathMultiByte(DATA_PATH);
	string FullPath;
	string pFileName;

	if (pPath != NULL)
		FullPath = pPath;

#ifdef _UNICODE
	pFileName = CW2A(FileName);
#endif // _UNICODE

	FullPath += pFileName;

	FILE* pFile = NULL;

	fopen_s(&pFile, FullPath.c_str(), "rb");

	size_t Count;
	fread(&Count, sizeof(Count), 1, pFile);

	for (size_t i = 0; i < Count; i++)
	{
		ObjectSave Saver;
		fread(&Saver, sizeof(ObjectSave), 1, pFile);

		switch (Saver.m_mType)
		{
			case MT_MONSTERONE:
			{
				IssacEnemy1* newMonster = (IssacEnemy1*)Object::CreateObject<IssacEnemy1>("Monster", InputLayer);
				newMonster->SetPos(Saver.Pos);

				SAFE_RELEASE(newMonster);
			}
			break;
			case MT_MONSTERTWO:
				break;
			case MT_MONSTERTHREE:
				break;
			case MT_MONSTERFOUR:
				break;
			case MT_MONSTERFIVE:
				break;
			case MT_MONSTERSIX:
				break;
			case MT_MONSTERSEVEN:
				break;
			case MT_MONSTEREIGHT:
				break;
			case MT_MONSTERNINE:
				break;
			case MT_MONSTERTEN:
				break;
		}
	}

	fclose(pFile);
}
