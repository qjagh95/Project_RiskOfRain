#include "IssacEnemy1.h"
#include "../Object/Object.h"
#include "../Object/Tile.h"
#include "../StageManager.h"

#include "../Resource/Animation.h"

#include "../Object/IssacTear.h"

IssacEnemy1::IssacEnemy1()
	:TimeVar(0.0f), IdleTime(0.0f), Distance(0.0f), AttackTime(4.0f), isAttack(false), StopTime(0.0f)
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
	SetMoveSpeed(250.0f);
	isGravity = true;

	SetSize(78.0f, 76.0f);
	SetPivot(0.5f, 0.5f);

	AnimationName[IMS_IDLE] = "Idle";
	AnimationName[IMS_MOVE] = "Move";
	AnimationName[IMS_TRACE] = "Move";
	AnimationName[IMS_ATTACK] = "Attack";

	Dir = "R";
	MoveDir = 1.0f;

	AddAnimationClip("LIdle", AT_ATLAS, AO_LOOP, 78.0f, 76.0f, 1, 1, 1, 1, 0, 0, 0.3f, "LIdle", TEXT("Enemy/Issac1LeftIdle.bmp"));
	AddAnimationClip("RIdle", AT_ATLAS, AO_LOOP, 78.0f, 76.0f, 1, 1, 1, 1, 0, 0, 0.3f, "RIdle", TEXT("Enemy/Issac1RightIdle.bmp"));
	AddAnimationClip("LMove", AT_ATLAS, AO_LOOP, 78.0f, 76.0f, 4, 1, 4, 1, 0, 0, 0.5f, "LMove", TEXT("Enemy/Issac1LeftMove.bmp"));
	AddAnimationClip("RMove", AT_ATLAS, AO_REVERS_LOOP, 78.0f, 76.0f, 4, 1, 4, 1, 3, 0, 0.5f, "RMove", TEXT("Enemy/Issac1RightMove.bmp"));
	AddAnimationClip("LAttack", AT_ATLAS, AO_LOOP, 67.0f, 77.0f, 1, 1, 1, 1, 0, 0, 0.3f, "LAttack", TEXT("Enemy/Issac1LeftAttack.bmp"));
	AddAnimationClip("RAttack", AT_ATLAS, AO_LOOP, 67.0f, 77.0f, 1, 1, 1, 1, 0, 0, 0.3f, "RAttack", TEXT("Enemy/Issac1RightAttack.bmp"));

	SelectState(ISSAC1_MONSTER_STATE::IMS_IDLE);
	return true;
}

int IssacEnemy1::Input(float DeltaTime)
{
	Monster::Input(DeltaTime);

	return 0;
}

int IssacEnemy1::Update(float DeltaTime)
{
	Monster::Update(DeltaTime);

	Distance = Math::GetDistance(m_Pos, Target->GetPos());
	RangeCheck();
	TimeMoveIdle(DeltaTime);
	
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

	return 0;
}

int IssacEnemy1::LateUpdate(float DeltaTime)
{
	Monster::LateUpdate(DeltaTime);

	PrevFrame = m_Animation->GetFrameX();
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

void IssacEnemy1::RangeCheck()
{
	if (Distance < AttackRange)
	{
		if (isAttack == false)
		{
			SelectState(IMS_ATTACK);
			isAttack = true;
		}
	}
	else if (Distance < TraceRange)
		SelectState(IMS_TRACE);
}

void IssacEnemy1::TimeMoveIdle(float DeltaTime)
{
	int RandNum = 2;
	TimeVar += DeltaTime;

	if (TimeVar > 2.0f)
	{
		TimeVar = 0.0f;
		RandNum = rand() % 2;
	}

	switch (RandNum)
	{
		case 0:
			SelectState(IMS_IDLE);
			break;
		case 1:
			SelectState(IMS_MOVE);
			break;
	}

}

void IssacEnemy1::SelectState(ISSAC1_MONSTER_STATE mState)
{
	PrevState = this->mState;
	this->mState = mState;
	ChangeClip(Dir + AnimationName[mState]);
}

void IssacEnemy1::FS_IDLE(float DeltaTime)
{
	IdleTime += DeltaTime;

	if (Distance < AttackRange)
	{
		if (isAttack == false)
		{
			SelectState(IMS_ATTACK);
			isAttack = true;
		}
	}
	else if (Distance < TraceRange)
		SelectState(IMS_TRACE);
	else 
		SelectState(IMS_MOVE);

	if (IdleTime > 1.5f)
		SelectState(IMS_MOVE);
}

void IssacEnemy1::FS_MOVE(float DeltaTime)
{
	Tile* NextTile = NULL;
	Tile* FootTile = NULL;

	if (MoveDir == 1.0f)
	{
		NextTile = StageManager::Get()->GetTile(m_Pos.x + m_Size.GetHalfX(), m_Pos.y);
		FootTile = StageManager::Get()->GetTile(m_Pos.x + (m_Size.GetHalfX() * 2.0f), m_Pos.y + m_Size.GetHalfY());
		
		if (NextTile->GetTileType() != TT_NOMOVE)
		{
			if(m_Pos.x >= 0 || m_Pos.x < StageManager::Get()->GetWidth())
				m_Pos.x += MoveSpeed * MoveDir * DeltaTime;

			if (FootTile->GetTileType() != TT_NOMOVE)
			{
				MoveDir = -1.0f;
				Dir = "L";
			}
		}
		else if (NextTile->GetTileType() == TT_NOMOVE)
			MoveDir = -1.0f;

	}
	else if(MoveDir == -1.0f)
	{
		NextTile = StageManager::Get()->GetTile(m_Pos.x - m_Size.GetHalfX(), m_Pos.y);
		FootTile = StageManager::Get()->GetTile(m_Pos.x - (m_Size.GetHalfX() * 2.0f), m_Pos.y + m_Size.GetHalfY());

		if (NextTile->GetTileType() != TT_NOMOVE)
		{
			if (m_Pos.x >= 0 || m_Pos.x < StageManager::Get()->GetWidth())
				m_Pos.x += MoveSpeed * MoveDir * DeltaTime;

			if (FootTile->GetTileType() != TT_NOMOVE)
			{
				MoveDir = 1.0f;
				Dir = "R";
			}
		}
		else if (NextTile->GetTileType() == TT_NOMOVE)
			MoveDir = 1.0f;
	}

	RangeCheck();

	SAFE_RELEASE(FootTile);
	SAFE_RELEASE(NextTile);
}		

void IssacEnemy1::FS_TRACE(float DeltaTime)
{
 	DirCheck();
	Tile* NextTile = NULL;

	if (MoveDir == 1.0f)
	{
		Tile* NextTile2 = NULL;

		NextTile = StageManager::Get()->GetTile(m_Pos.x + m_Size.GetHalfX(), m_Pos.y);
		NextTile2 = StageManager::Get()->GetTile(m_Pos.x + NextTile->GetSize().x * 2.0f, m_Pos.y - NextTile->GetSize().y);

		if (NextTile->GetTileType() != TT_NOMOVE)
		{
			if (m_Pos.x >= 0 || m_Pos.x < StageManager::Get()->GetWidth())
				m_Pos.x += MoveSpeed * MoveDir * DeltaTime;
		}
		if (NextTile->GetTileType() == TT_NOMOVE)
		{
			if (NextTile2->GetTileType() == TT_NOMAL)
			{
				m_Pos.y--;
				SetForce(600.0f);
			}
		}
		SAFE_RELEASE(NextTile2);
	}
	else if (MoveDir == -1.0f)
	{
		Tile* NextTile2 = NULL;

		NextTile = StageManager::Get()->GetTile(m_Pos.x - m_Size.GetHalfX(), m_Pos.y);
		NextTile2 = StageManager::Get()->GetTile(m_Pos.x - NextTile->GetSize().x * 2.0f, m_Pos.y - NextTile->GetSize().y);

		if (NextTile->GetTileType() != TT_NOMOVE)
		{
			if (m_Pos.x >= 0 || m_Pos.x < StageManager::Get()->GetWidth())
				m_Pos.x += MoveSpeed * MoveDir * DeltaTime;
		}
		if (NextTile->GetTileType() == TT_NOMOVE)
		{
			if (NextTile2->GetTileType() == TT_NOMAL)
			{
				m_Pos.y--;
				SetForce(600.0f);
			}
		}
		SAFE_RELEASE(NextTile2);
	}

	SAFE_RELEASE(NextTile);

	if (Distance < AttackRange)
	{
		if (isAttack == false)
		{
			SelectState(IMS_ATTACK);
			isAttack = true;
		}
	}
	else
		SelectState(IMS_MOVE);

}

void IssacEnemy1::FS_ATTACK(float DeltaTime)
{
	if (isAttack == false)
	{
		SelectState(IMS_MOVE);
		return;
	}

	DirCheck();
	isStop = true;

	if (isStop == true)
		StopTime += DeltaTime;
	if (StopTime >= 0.4f)
	{
		isStop = false;
		StopTime = 0.0f;
		SelectState(PrevState);
	}

	if (PrevFrame != m_Animation->GetFrameX())
	{
		for (int i = 0; i < 8; i++)
		{
			IssacTear* newTear = (IssacTear*)Object::CreateCloneObject("Tear", m_Layer);
			newTear->SetDir(MoveDir);
			newTear->SetPos(m_Pos);
			newTear->SetForce((float)Math::RandomRange((int)MoveSpeed, (int)(MoveSpeed * 3.0f)));
			newTear->SetMoveSpeed((float)Math::RandomRange((int)MoveSpeed, (int)(MoveSpeed * 3.0f)));
			SAFE_RELEASE(newTear);
		}
	}

}