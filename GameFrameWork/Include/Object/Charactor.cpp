#include "Charactor.h"
#include "Tile.h"
#include "TileInfo.h"
#include "../StageManager.h"

Charactor::Charactor()
{
}

Charactor::~Charactor()
{
}

bool Charactor::Init()
{
	return true;
}

int Charactor::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int Charactor::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int Charactor::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	Vector2 PrevPos = m_Pos - m_TempMove;

	Tile* CurTile = StageManager::Get()->GetTile(m_Pos);
	Tile* PrevTile = StageManager::Get()->GetTile(PrevPos);

	if (CurTile == NULL)
	{
		m_Pos = PrevPos;
	}

	if (CurTile->GetTileType() == TT_NOMOVE)
	{
		m_Pos = PrevPos;

		TileCollsionActive(DeltaTime);

		ClearGravityTime();
		SetForce(0.0f);
	}

	return 0;
}

void Charactor::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void Charactor::Render(HDC hDC, float DeltaTime)
{
	Object::Render(hDC, DeltaTime);
}
