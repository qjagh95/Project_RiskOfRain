#include "Lemurian.h"
#include "../Coll/ColliderRect.h"
#include "../Scene/Layer.h"
#include "../Object/Object.h"
#include "../Object/Tile.h"
#include "../StageManager.h"
#include "../Resource/Animation.h"
#include "../Object/LemurinHitBox.h"

Lemurian::Lemurian()
{
}

Lemurian::Lemurian(const Lemurian & Value)
	:Monster(Value)
{
}

Lemurian::~Lemurian()
{
}

bool Lemurian::Init()
{
	Monster::Init();

	AttackRange = 100.0f;
	Attack = 30;
	TraceRange = 300.0f;
	SetGravity(true);
	isAttack = false;
	AttackDelay = 0.0f;
	isTrace = false;
	TraceTime = 0.0f;

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

	SetMoveSpeed(300.0f);
	SetHp(180);
	SetMaxHp(180);

	SetSize(45.0f, 45.0f);

	AnimationName[LS_IDLE] = "Idle";
	AnimationName[LS_MOVE] = "Move";
	AnimationName[LS_TRACE] = "Move";
	AnimationName[LS_ATTACK] = "Attack";
	
	AddAnimationClip("LIdle", AT_ATLAS, AO_LOOP, 45.0f, 45.0f, 1, 1, 1, 1, 0, 0, 0.3f, "LemurianLIdle", TEXT("Enemy/Lemurian_Left_Hold.bmp"));
	AddAnimationClip("RIdle", AT_ATLAS, AO_LOOP, 45.0f, 45.0f, 1, 1, 1, 1, 0, 0, 0.3f, "LemurianRIdle", TEXT("Enemy/Lemurian_Right_Hold.bmp"));
	AddAnimationClip("LMove", AT_ATLAS, AO_REVERS_LOOP, 45.0f, 48.0f, 9, 1, 9, 1, 8, 0, 0.4f, "LemurianLMove", TEXT("Enemy/Lemurian_Left_Move.bmp"));
	AddAnimationClip("RMove", AT_ATLAS, AO_LOOP, 45.0f, 48.0f, 9, 1, 9, 1, 0, 0, 0.4f, "LemurianRMove", TEXT("Enemy/Lemurian_Right_Move.bmp"));
	AddAnimationClip("LAttack", AT_ATLAS, AO_REVERS_BOUNCE_LOOP_LEMUIRAN, 114.0f, 67.0f, 10, 1, 10, 1, 9, 0, 0.5f, "LemurianLAttack", TEXT("Enemy/Lemurian_Left_Attack.bmp"));
	AddAnimationClip("RAttack", AT_ATLAS, AO_BOUNCE_LOOP_LEMUIRAN, 114.0f, 67.0f, 10, 1, 10, 1, 0, 0, 0.5f, "LemurianRAttack", TEXT("Enemy/Lemurian_Right_Attack.bmp"));

	SelectState(AnimationName, LS_MOVE);
	return true;
}

int Lemurian::Input(float DeltaTime)
{
	Monster::Input(DeltaTime);

	TimeToIdle(DeltaTime);

	return 0;
}

int Lemurian::Update(float DeltaTime)
{
	Monster::Update(DeltaTime);

	switch (mState)
	{
		case LS_IDLE:
			FS_IDLE(DeltaTime);
			break;
		case LS_MOVE:
			FS_MOVE(DeltaTime);
			break;
		case LS_ATTACK:
			FS_ATTACK(DeltaTime);
			break;
		case LS_TRACE:
			FS_TRACE(DeltaTime);
			break;
	}

	if (isAttack == true)
	{
		AttackDelay += DeltaTime;

		if (AttackDelay >= 1.0f)
		{
			isAttack = false;
			AttackDelay = 0.0f;
		}
	}

	if (isTrace == true)
	{
		TraceTime += DeltaTime;

		if (TraceTime >= 1.0f)
		{
			isTrace = false;
			TraceTime = 0.0f;
		}
	}
	return 0;
}

int Lemurian::LateUpdate(float DeltaTime)
{
	Monster::LateUpdate(DeltaTime);

	PrevFrame = m_Animation->GetFrameX();
	AnimationDirCheck(AnimationName, mState);
	return 0;
}

void Lemurian::Collision(float DeltaTime)
{
	Monster::Collision(DeltaTime);
}

void Lemurian::CollsionAfterUpdate(float DeltaTime)
{
	Monster::CollsionAfterUpdate(DeltaTime);
}

void Lemurian::Render(HDC Hdc, float DeltaTime)
{
	Monster::Render(Hdc, DeltaTime);
}

Lemurian * Lemurian::Clone()
{
	return new Lemurian(*this);
}

void Lemurian::TileCollsionActive(float DeltaTime)
{
	Monster::TileCollsionActive(DeltaTime);
}

void Lemurian::RangeCheck()
{
	if (Distance < TraceRange)
	{
		SelectState(AnimationName, LS_TRACE);
		isTrace = true;
	}
}

void Lemurian::TimeToIdle(float DeltaTime)
{
	if (mState == LS_IDLE || mState == LS_MOVE)
	{
		int RandNum = 2;
		IdleTimeVar += DeltaTime;

		if (IdleTimeVar > 3.0f)
		{
			IdleTimeVar = 0.0f;
			RandNum = rand() % 2;
		}

		switch (RandNum)
		{
			case 0:
				SelectState(AnimationName, LS_IDLE);
				isIdle = true;
				break;
			case 1:	
				SelectState(AnimationName, LS_MOVE);
				break;
		}
	}
}

void Lemurian::FS_IDLE(float DeltaTime)
{
	if (isIdle == false)
		SelectState(AnimationName, LS_MOVE);
}

void Lemurian::FS_MOVE(float DeltaTime)
{
	Tile* NextTile = NULL;
	Tile* FootNextTile = NULL;
	Tile* TempTile = NULL;

	NextTile = StageManager::Get()->GetTile(m_Pos.x + m_Size.GetHalfX() * MoveDir, m_Pos.y + m_Size.GetHalfY() - StageManager::Get()->GetTileSize().y);
	FootNextTile = StageManager::Get()->GetTile(m_Pos.x + m_Size.GetHalfX() * MoveDir, m_Pos.y + m_Size.GetHalfY() + StageManager::Get()->GetTileSize().GetHalfY());

	if (m_Pos.x >= 0 || m_Pos.x < StageManager::Get()->GetWidth())
		m_Pos.x += MoveSpeed * MoveDir * DeltaTime;

	if(FootNextTile->GetTileType() == TT_NOMAL)
		MoveDir *= -1.0f;

	if (NextTile->GetTileType() == TT_NOMOVE)
		MoveDir *= -1.0f;

	SAFE_RELEASE(NextTile);
	SAFE_RELEASE(FootNextTile);
	SAFE_RELEASE(TempTile);

	RangeCheck();
}

void Lemurian::FS_TRACE(float DeltaTime)
{
	if (isTrace == false)
	{
		SelectState(AnimationName, LS_MOVE);
		return;
	}

	Tile* NextTile = NULL;
	Tile* NextTile2 = NULL;

	NextTile = StageManager::Get()->GetTile(m_Pos.x + m_Size.GetHalfX() * MoveDir, m_Pos.y);
	NextTile2 = StageManager::Get()->GetTile(m_Pos.x + (NextTile->GetSize().x * 2.0f) * MoveDir, m_Pos.y - NextTile->GetSize().y);

	if (NextTile->GetTileType() == TT_NOMOVE)
	{
		if (NextTile2->GetTileType() == TT_NOMAL)
		{
			m_Pos.y--;
			SetForce(600.0f);
		}
	}

	SAFE_RELEASE(NextTile2);
	SAFE_RELEASE(NextTile);

	MonsterMove(DeltaTime);
	DirCheck();

	if (Distance < AttackRange)
		SelectState(AnimationName, LS_ATTACK);
	else if (Distance > TraceRange)
		SelectState(AnimationName, LS_MOVE);
}

void Lemurian::FS_ATTACK(float DeltaTime)
{
	if (PrevFrame == m_Animation->GetFrameX())
		return;

	if (m_Animation->GetFrameX() == 3)
	{
		LemurinHitBox* newBox = Object::CreateObject<LemurinHitBox>("lHitBox", m_Layer);

		if (MoveDir == 1.0f)
			newBox->SetPos(m_Pos.x + m_Size.x, m_Pos.y);
		else
			newBox->SetPos(m_Pos.x - m_Size.GetHalfX() - 117.0f, m_Pos.y);
		
		newBox->SetAttack(Attack);

		SAFE_RELEASE(newBox);
	}

	if (m_Animation->GetIsEnd() == true)
		SelectState(AnimationName, LS_MOVE);
}
