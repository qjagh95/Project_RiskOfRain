#include "Charactor.h"
#include "Tile.h"
#include "TileInfo.h"
#include "../StageManager.h"
#include "../Resource/Animation.h"

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
	Tile* NextTile = StageManager::Get()->GetTile(m_Pos.x , m_Pos.y + m_Size.GetHalfY());

	if (CurTile == NULL)
	{
		//화면밖체크
		m_Pos = PrevPos;
	}

	if (NextTile->GetTileType() == TT_NOMOVE)
	{
		isGravity = false;
		SetForce(0.0f);

		if (m_Animation != NULL && m_Animation->GetClipName() == "RopeUp")
		{
			SAFE_RELEASE(CurTile);
			SAFE_RELEASE(NextTile);

			return 0;
		}
		if (m_Animation != NULL && m_Animation->GetClipName() == "RopeHold")
		{
			SAFE_RELEASE(CurTile);
			SAFE_RELEASE(NextTile);

			return 0;
		}

		m_Pos.y = NextTile->GetPos().y - m_Size.GetHalfY();

		TileCollsionActive(DeltaTime);
	}
	
	SAFE_RELEASE(CurTile);
	SAFE_RELEASE(NextTile);

	return 0;
}

void Charactor::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void Charactor::CollsionAfterUpdate(float DeltaTime)
{
	Object::CollsionAfterUpdate(DeltaTime);
}

void Charactor::Render(HDC hDC, float DeltaTime)
{
	Object::Render(hDC, DeltaTime);
}
