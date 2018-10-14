#include "RockGolem.h"
#include "../Coll/ColliderRect.h"
#include "../Scene/Layer.h"
#include "../Object/Object.h"
#include "../Object/Tile.h"
#include "../StageManager.h"
#include "../Resource/Animation.h"
#include "../Object/RockGolenHitBox.h"

RockGolem::RockGolem()
{
}

RockGolem::RockGolem(const RockGolem & Value)
	:Monster(Value)
{
}

RockGolem::~RockGolem()
{
}

bool RockGolem::Init()
{
	Monster::Init();

	AttackRange = 100.0f;
	Attack = 55;
	SetGravity(true);
	AttackDelay = 0.0f;

	int randn = rand() % 2;
	if (randn == 0)
	{
		Dir = "R";
		MoveDir = 1.0f;
	}
	else
	{
		Dir = "L";
		MoveDir = 1.0f;
	}

	SetMoveSpeed(200.0f);
	SetHp(300);
	SetMaxHp(300);

	SetSize(60.0f, 90.0f);

	AnimationName[RS_IDLE] = "Idle";
	AnimationName[RS_MOVE] = "Move";
	AnimationName[RS_ATTACK] = "Attack";

	AddAnimationClip("LIdle", AT_ATLAS, AO_LOOP, 60.0f, 90.0f, 1, 1, 1, 1, 0, 0, 0.4f, "RockLIdle", TEXT("Enemy/RockGolem_Left_Hold.bmp"));
	AddAnimationClip("RIdle", AT_ATLAS, AO_LOOP, 60.0f, 90.0f, 1, 1, 1, 1, 0, 0, 0.4f, "RockRIdle", TEXT("Enemy/RockGolem_Right_Hold.bmp"));
	AddAnimationClip("LMove", AT_ATLAS, AO_LOOP, 60.0f, 90.0f, 7, 1, 11, 1, 0, 0, 1.0f, "RockLMove", TEXT("Enemy/RockGolem_Left_Move.bmp"));
	AddAnimationClip("RMove", AT_ATLAS, AO_LOOP, 60.0f, 90.0f, 7, 1, 11, 1, 0, 0, 1.0f, "RockRMove", TEXT("Enemy/RockGolem_Right_Move.bmp"));
	AddAnimationClip("LAttack", AT_ATLAS, AO_LOOP, 126.0f, 88.0f, 20, 1, 20, 1, 0, 0, 1.5f, "RockLAttack", TEXT("Enemy/RockGolem_Left_Attack.bmp"));
	AddAnimationClip("RAttack", AT_ATLAS, AO_REVERS_BOUNCE_LOOP, 126.0f, 88.0f, 20, 1, 20, 1, 19, 0, 1.5f, "RockRAttack", TEXT("Enemy/RockGolem_Right_Attack.bmp"));

	SelectState(AnimationName, RS_ATTACK);
	return true;
}

int RockGolem::Input(float DeltaTime)
{
	Monster::Input(DeltaTime);

	return 0;
}

int RockGolem::Update(float DeltaTime)
{
	Monster::Update(DeltaTime);

	switch (mState)
	{
		case RS_IDLE:
			FS_IDLE(DeltaTime);
			break;
		case RS_MOVE:
			FS_MOVE(DeltaTime);
			break;
		case RS_TRACE:
			FS_TRACE(DeltaTime);
			break;
		case RS_ATTACK:
			FS_ATTACK(DeltaTime);
			break;
	}
	return 0;
}

int RockGolem::LateUpdate(float DeltaTime)
{
	Monster::LateUpdate(DeltaTime);
	PrevFrame = m_Animation->GetFrameX();

	AnimationDirCheck(AnimationName, mState);

	return 0;
}

void RockGolem::Collision(float DeltaTime)
{
	Monster::Collision(DeltaTime);
}

void RockGolem::CollsionAfterUpdate(float DeltaTime)
{
	Monster::CollsionAfterUpdate(DeltaTime);
}

void RockGolem::Render(HDC Hdc, float DeltaTime)
{
	Monster::Render(Hdc, DeltaTime);
}

RockGolem * RockGolem::Clone()
{
	return new RockGolem(*this);
}

void RockGolem::TileCollsionActive(float DeltaTime)
{
	Monster::TileCollsionActive(DeltaTime);
}

void RockGolem::TimeToIdle(float DeltaTime)
{
	if (mState == RS_IDLE || mState == RS_MOVE)
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
				SelectState(AnimationName, RS_IDLE);
				isIdle = true;
				break;
			case 1:
				SelectState(AnimationName, RS_MOVE);
				break;
		}
	}
}

void RockGolem::RangeCheck()
{
	if (Distance < AttackRange)
		SelectState(AnimationName, RS_ATTACK);
}

void RockGolem::FS_IDLE(float DeltaTime)
{
	if (isIdle == false)
		SelectState(AnimationName, RS_MOVE);
}

void RockGolem::FS_MOVE(float DeltaTime)
{
	Tile* NextTile = NULL;
	Tile* FootNextTile = NULL;
	Tile* TempTile = NULL;

	NextTile = StageManager::Get()->GetTile(m_Pos.x + m_Size.GetHalfX() * MoveDir, m_Pos.y + m_Size.GetHalfY() - StageManager::Get()->GetTileSize().y);
	FootNextTile = StageManager::Get()->GetTile(m_Pos.x + m_Size.GetHalfX() * MoveDir, m_Pos.y + m_Size.GetHalfY() + StageManager::Get()->GetTileSize().GetHalfY());

	if (m_Pos.x >= 0 || m_Pos.x < StageManager::Get()->GetWidth())
		m_Pos.x += MoveSpeed * MoveDir * DeltaTime;

	if (FootNextTile->GetTileType() == TT_NOMAL)
		MoveDir *= -1.0f;

	if (NextTile->GetTileType() == TT_NOMOVE)
		MoveDir *= -1.0f;

	SAFE_RELEASE(NextTile);
	SAFE_RELEASE(FootNextTile);
	SAFE_RELEASE(TempTile);

	RangeCheck();
}

void RockGolem::FS_TRACE(float DeltaTime)
{
}

void RockGolem::FS_ATTACK(float DeltaTime)
{
	DirCheck();

	if (PrevFrame == m_Animation->GetFrameX())
		return;

	if (MoveDir == 1.0f)
	{
		if (m_Animation->GetFrameX() == 9)
		{
			RockGolenHitBox* newBox = Object::CreateObject<RockGolenHitBox>("RockHitBox", m_Layer);
			newBox->SetPos(m_Pos.x + m_Size.x, m_Pos.y);
			newBox->SetAttack(Attack);

			SAFE_RELEASE(newBox);
		}
	}
	else
	{
		if (m_Animation->GetFrameX() == m_Animation->GetMaxCountX() - 9)
		{
			RockGolenHitBox* newBox = Object::CreateObject<RockGolenHitBox>("RockHitBox", m_Layer);
			newBox->SetPos(m_Pos.x - m_Size.x, m_Pos.y);
			newBox->SetAttack(Attack);

			SAFE_RELEASE(newBox);
		}
	}

	if(m_Animation->GetIsEnd() == true)
		SelectState(AnimationName, RS_MOVE);
}
