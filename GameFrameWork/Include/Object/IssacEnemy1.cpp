#include "IssacEnemy1.h"
#include "../Object/Object.h"
#include "../Object/Tile.h"
#include "../StageManager.h"
#include "../Coll/ColliderRect.h"
#include "../Resource/Animation.h"
#include "../Object/IssacTear.h"
#include "../Debug.h"

IssacEnemy1::IssacEnemy1()
	:TimeVar(0.0f), IdleTime(0.0f), AttackTime(4.0f), isAttack(false), StopTime(0.0f), isStop(false)
	,Count(0), BackDistance(100.0f), isHit(false)
{
}

IssacEnemy1::IssacEnemy1(const IssacEnemy1 & Value)
	:Monster(Value)
{
}

IssacEnemy1::~IssacEnemy1()
{
}

bool IssacEnemy1::Init()
{
	Monster::Init();

	TraceRange = 400.0f;
	AttackRange = 300.0f;
	SetMoveSpeed(150.0f);
	isGravity = true;
	SetHp(150);
	SetMaxHp(150);

	SetSize(78.0f, 76.0f);
	SetPivot(0.5f, 0.5f);

	AnimationName[IMS_IDLE] = "Idle";
	AnimationName[IMS_MOVE] = "Move";
	AnimationName[IMS_TRACE] = "Move";
	AnimationName[IMS_ATTACK] = "Attack";

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

	AddAnimationClip("LIdle", AT_ATLAS, AO_LOOP, 78.0f, 76.0f, 1, 1, 1, 1, 0, 0, 0.3f, "LIdle", TEXT("Enemy/Issac1LeftIdle.bmp"));
	AddAnimationClip("RIdle", AT_ATLAS, AO_LOOP, 78.0f, 76.0f, 1, 1, 1, 1, 0, 0, 0.3f, "RIdle", TEXT("Enemy/Issac1RightIdle.bmp"));
	AddAnimationClip("LMove", AT_ATLAS, AO_LOOP, 78.0f, 76.0f, 4, 1, 4, 1, 0, 0, 0.5f, "LMove", TEXT("Enemy/Issac1LeftMove.bmp"));
	AddAnimationClip("RMove", AT_ATLAS, AO_REVERS_LOOP, 78.0f, 76.0f, 4, 1, 4, 1, 3, 0, 0.5f, "RMove", TEXT("Enemy/Issac1RightMove.bmp"));
	AddAnimationClip("LAttack", AT_ATLAS, AO_LOOP, 67.0f, 77.0f, 1, 1, 1, 1, 0, 0, 0.3f, "LAttack", TEXT("Enemy/Issac1LeftAttack.bmp"));
	AddAnimationClip("RAttack", AT_ATLAS, AO_LOOP, 67.0f, 77.0f, 1, 1, 1, 1, 0, 0, 0.3f, "RAttack", TEXT("Enemy/Issac1RightAttack.bmp"));

	SelectState(AnimationName, IMS_IDLE);
	isIdle = true;

	return true;
}

int IssacEnemy1::Input(float DeltaTime)
{
	Monster::Input(DeltaTime);

	TimeMoveIdle(DeltaTime);

	return 0;
}

int IssacEnemy1::Update(float DeltaTime)
{
	Monster::Update(DeltaTime);
	
	AnimationDirCheck(AnimationName, mState);

	switch (mState)
	{
		case IMS_IDLE:
			FS_IDLE(DeltaTime);
			break;
		case IMS_MOVE:
			FS_MOVE(DeltaTime);
			break;
		case IMS_ATTACK:
			FS_ATTACK(DeltaTime);
			break;
		case IMS_TRACE:
			FS_TRACE(DeltaTime);
			break;
	}

	if (isAttack == true)
	{
		AttackTime -= DeltaTime;

		if (AttackTime <= 0.0f)
		{
			AttackTime = 4.0f;
			isAttack = false;
		}
	}
	if (isStop == true)
	{
		StopTime += DeltaTime;
		if (StopTime >= 0.4f)
		{
			StopTime = 0.0f;
			isStop = false;
		}
	}

	if (isIdle == true)
	{
		IdleTime += DeltaTime;

		if (IdleTime >= 1.5f)
		{
			IdleTime = 0.0f;
			isIdle = false;
		}
	}
	return 0;
}

int IssacEnemy1::LateUpdate(float DeltaTime)
{
	Monster::LateUpdate(DeltaTime);
	PrevFrame = m_Animation->GetFrameX();

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

void IssacEnemy1::Collision(float DeltaTime)
{
	Monster::Collision(DeltaTime);
}

void IssacEnemy1::CollsionAfterUpdate(float DeltaTime)
{
	isGravity = true;
}

void IssacEnemy1::Render(HDC Hdc, float DeltaTime)
{
	Monster::Render(Hdc, DeltaTime);
}

IssacEnemy1 * IssacEnemy1::Clone()
{
	return new IssacEnemy1(*this);
}

void IssacEnemy1::TileCollsionActive(float DeltaTime)
{
	Monster::TileCollsionActive(DeltaTime);
}

void IssacEnemy1::BaseAttackHitFirst(Collider * Src, Collider * Dest, float DeltaTime)
{
	Monster::BaseAttackHitFirst(Src, Dest, DeltaTime);

	if (Dest->GetTag() == "BaseBody")
	{
		isHit = true;
	}
}

void IssacEnemy1::SkillTwoHitFirst(Collider * Src, Collider * Dest, float DeltaTime)
{
	Monster::SkillTwoHitFirst(Src, Dest, DeltaTime);

	if (Dest->GetTag() == "LaserBody")
	{
		isHit = true;
	}
}

void IssacEnemy1::RangeCheck(float DeltaTime)
{
	if (Distance < AttackRange)
	{
		if (isAttack == false)
		{
			SelectState(AnimationName,IMS_ATTACK);
			isStop = true;
			isAttack = true;
		}
	}
	else if (Distance < TraceRange)
		SelectState(AnimationName, IMS_TRACE);
	else
		SelectState(AnimationName, IMS_MOVE);
}

void IssacEnemy1::TimeMoveIdle(float DeltaTime)
{
	if (mState == IMS_MOVE || mState == IMS_IDLE)
	{
		int RandNum = 2;
		TimeVar += DeltaTime;

		if (TimeVar > 3.0f)
		{
			TimeVar = 0.0f;
			RandNum = rand() % 2;
		}

		switch (RandNum)
		{
			case 0:
				SelectState(AnimationName, IMS_IDLE);
				isIdle = true;
				break;
			case 1:
				SelectState(AnimationName, IMS_MOVE);
				break;
		}
	}
}

void IssacEnemy1::FS_IDLE(float DeltaTime)
{
	if (Distance < AttackRange)
	{
		if (isAttack == false)
		{
			SelectState(AnimationName, IMS_ATTACK);
			isAttack = true;
			isStop = true;
		}
	}
	else if (Distance < TraceRange)
		SelectState(AnimationName, IMS_TRACE);

	if (isIdle == false)
		SelectState(AnimationName, IMS_MOVE);
}

void IssacEnemy1::FS_MOVE(float DeltaTime)
{
	MonsterMove(DeltaTime);
	RangeCheck(DeltaTime);

	Count = 0;
}		

void IssacEnemy1::FS_TRACE(float DeltaTime)
{
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
	{
		if (isAttack == false)
		{
			SelectState(AnimationName, IMS_ATTACK);
			isAttack = true;
			isStop = true;
		}
	}
	else if(Distance > TraceRange)
		SelectState(AnimationName, IMS_MOVE);
}

void IssacEnemy1::FS_ATTACK(float DeltaTime)
{
 	if (isAttack == false)
	{
		SelectState(AnimationName, IMS_MOVE);
		return;
	}

	DirCheck();

	if (Count <= 7)
	{
		for (int i = 0; i < 8; i++)
		{
			Count++;
			IssacTear* newTear = (IssacTear*)Object::CreateCloneObject("Tear", m_Layer);
			newTear->SetDir(MoveDir);
			newTear->SetPos(m_Pos);
			newTear->SetForce((float)Math::RandomRange((int)MoveSpeed * (int)2.0f, (int)(MoveSpeed * 3.5f)));
			newTear->SetMoveSpeed((float)Math::RandomRange((int)MoveSpeed * (int)2.0f, (int)(MoveSpeed * 3.5f)));
			SAFE_RELEASE(newTear);
		}
	}

	if (isStop == false)
		SelectState(AnimationName, IMS_MOVE);
}