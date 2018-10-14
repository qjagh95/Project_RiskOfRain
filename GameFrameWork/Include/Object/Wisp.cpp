#include "Wisp.h"
#include "../Coll/ColliderRect.h"
#include "../Scene/Layer.h"
#include "../Object/Object.h"
#include "../Object/Tile.h"
#include "../StageManager.h"
#include "../Resource/Animation.h"
#include "../Object/WispHitBox.h"

Wisp::Wisp()
{
}

Wisp::Wisp(const Wisp & Value)
	:Monster(Value)
{
}

Wisp::~Wisp()
{
}

bool Wisp::Init()
{
	Monster::Init();

	AttackRange = 100.0f;
	Attack = 35;
	TraceRange = 300.0f;
	SetGravity(true);
	isAttack = false;
	AttackDelay = 0.0f;
	isTrace = false;
	TraceTime = 0.0f;
	isHit = false;
	BackDistance = 100.0f;

	int randn = rand() % 2;
	if (randn == 0)
	{
		Dir = "R";
		MoveDir = 1.0f;
	}
	else
	{
		Dir = "L";
		MoveDir = -1.0f;
	}

	SetMoveSpeed(200.0f);
	SetHp(250);
	SetMaxHp(250);

	SetSize(27.0f, 50.0f);

	AnimationName[WS_MOVE] = "Move";
	AnimationName[WS_TRACE] = "Move";
	AnimationName[WS_ATTACK] = "Attack";

	AddAnimationClip("LMove", AT_ATLAS, AO_LOOP, 27.0f, 50.0f, 5, 1, 5, 1, 0, 0, 0.4f, "WispLMove", TEXT("Enemy/Wisp_Left_Move.bmp"));
	AddAnimationClip("RMove", AT_ATLAS, AO_LOOP, 27.0f, 50.0f, 5, 1, 5, 1, 0, 0, 0.4f, "WispRMove", TEXT("Enemy/Wisp_Right_Move.bmp"));
	AddAnimationClip("LAttack", AT_ATLAS, AO_LOOP_WISP, 275.0f, 60.0f, 11, 1, 11, 1, 0, 0, 1.0f, "WispLAttack", TEXT("Enemy/Wisp_Left_Attack.bmp"));
	AddAnimationClip("RAttack", AT_ATLAS, AO_REVERS_WISP, 275.0f, 60.0f, 11, 1, 11, 1, 10, 0, 1.0f, "WispRAttack", TEXT("Enemy/Wisp_Right_Attack.bmp"));

	SelectState(AnimationName, WS_MOVE);
	return true;
}

int Wisp::Input(float DeltaTime)
{
	Monster::Input(DeltaTime);

	return 0;
}

int Wisp::Update(float DeltaTime)
{
	Monster::Update(DeltaTime);

	switch (mState)
	{
		case WS_MOVE:
			FS_MOVE(DeltaTime);
			break;
		case WS_TRACE:
			FS_TRACE(DeltaTime);
			break;
		case WS_ATTACK:
			FS_ATTACK(DeltaTime);
			break;
	}

	return 0;
}

int Wisp::LateUpdate(float DeltaTime)
{
	Monster::LateUpdate(DeltaTime);

	PrevFrame = m_Animation->GetFrameX();
	AnimationDirCheck(AnimationName, mState);

	if (isHit == true)
	{
		Tile* NextTile = NULL;

		NextTile = StageManager::Get()->GetTile(m_Pos.x + m_Size.GetHalfX() * (MoveDir * -1.0f), m_Pos.y);

		if (NextTile->GetTileType() != TT_NOMOVE)
		{
			BackDistance -= MoveSpeed * 3.0f * DeltaTime;
			m_Pos.x += MoveSpeed * 3.0f * (MoveDir * -1.0f) * DeltaTime;
		}

		if (BackDistance <= 0.0f)
		{
			isHit = false;
			BackDistance = 50.0f;
		}

		SAFE_RELEASE(NextTile);
	}

	return 0;
}

void Wisp::Collision(float DeltaTime)
{
	Monster::Collision(DeltaTime);
}

void Wisp::CollsionAfterUpdate(float DeltaTime)
{
	Monster::CollsionAfterUpdate(DeltaTime);
}

void Wisp::Render(HDC Hdc, float DeltaTime)
{
	Monster::Render(Hdc, DeltaTime);
}

Wisp * Wisp::Clone()
{
	return new Wisp(*this);
}

void Wisp::TileCollsionActive(float DeltaTime)
{
	Monster::TileCollsionActive(DeltaTime);
}

void Wisp::BaseAttackHitFirst(Collider * Src, Collider * Dest, float DeltaTime)
{
	Monster::BaseAttackHitFirst(Src, Dest, DeltaTime);

	if (Dest->GetTag() == "BaseBody")
	{
		isHit = true;
	}
}

void Wisp::SkillTwoHitFirst(Collider * Src, Collider * Dest, float DeltaTime)
{
	Monster::SkillTwoHitFirst(Src, Dest, DeltaTime);

	if (Dest->GetTag() == "LaserBody")
	{
		isHit = true;
	}
}

void Wisp::RangeCheck()
{
	if (Distance < TraceRange)
		SelectState(AnimationName, WS_TRACE);
}

void Wisp::FS_MOVE(float DeltaTime)
{
	Tile* CurTile = NULL;
	Tile* FootTile = NULL;
	Tile* NextTile = NULL;

	NextTile = StageManager::Get()->GetTile(m_Pos.x + m_Size.GetHalfX() * MoveDir, m_Pos.y);
	CurTile = StageManager::Get()->GetTile(m_Pos.x, m_Pos.y - m_Size.GetHalfY());
	FootTile = StageManager::Get()->GetTile(m_Pos.x + (m_Size.GetHalfX() * MoveDir) + StageManager::Get()->GetTileSize().GetHalfX(), m_Pos.y + m_Size.GetHalfY() + StageManager::Get()->GetTileSize().GetHalfY());

	if (m_Pos.x >= 0 || m_Pos.x < StageManager::Get()->GetWidth())
	{
		if (FootTile != NULL && FootTile->GetTileType() != TT_NOMAL)
			m_Pos.x += MoveSpeed * MoveDir * DeltaTime;
		else if (FootTile != NULL && FootTile->GetTileType() == TT_NOMAL)
			MoveDir *= -1.0f;

		if (NextTile->GetTileType() == TT_NOMOVE)
			MoveDir *= -1.0f;
	}

	if (CurTile->GetTileType() == TT_NOMOVE && FootTile->GetTileType() == TT_NOMAL)
		MoveDir *= -1.0f;

	SAFE_RELEASE(NextTile);
	SAFE_RELEASE(FootTile);
	SAFE_RELEASE(CurTile);

	RangeCheck();
}

void Wisp::FS_TRACE(float DeltaTime)
{
	Tile* NextTile = NULL;
	Tile* NextTile2 = NULL;

	NextTile = StageManager::Get()->GetTile(m_Pos.x + m_Size.GetHalfX() * MoveDir, m_Pos.y);

	SAFE_RELEASE(NextTile2);
	SAFE_RELEASE(NextTile);

	MonsterMove(DeltaTime);
	DirCheck();

	if (Distance < AttackRange)
		SelectState(AnimationName, WS_ATTACK);
	else if (Distance > TraceRange)
		SelectState(AnimationName, WS_MOVE);
}

void Wisp::FS_ATTACK(float DeltaTime)
{
	if (PrevFrame == m_Animation->GetFrameX())
		return;

	if (MoveDir == 1.0f)
	{
		if (m_Animation->GetFrameX() == 3)
		{
			WispHitBox* newBox = Object::CreateObject<WispHitBox>("WispHitBox", m_Layer);
			newBox->SetPos(m_Pos.x + m_Size.GetHalfX(), m_Pos.y);
			newBox->SetAttack(Attack);

			SAFE_RELEASE(newBox);
		}
	}
	else
	{
		if (m_Animation->GetFrameX() == m_Animation->GetMaxCountX() - 3)
		{
			WispHitBox* newBox = Object::CreateObject<WispHitBox>("WispHitBox", m_Layer);
			newBox->SetPos(m_Pos.x - m_Animation->GetFrameSize().x, m_Pos.y);
			newBox->SetAttack(Attack);

			SAFE_RELEASE(newBox);
		}
	}
	
	if (m_Animation->GetIsEnd() == true)
		SelectState(AnimationName, WS_MOVE);
}
