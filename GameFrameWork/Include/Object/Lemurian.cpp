#include "Lemurian.h"
#include "../Coll/ColliderRect.h"
#include "../Scene/Layer.h"
#include "../Object/Object.h"
#include "../Object/Tile.h"
#include "../StageManager.h"
#include "../Resource/Animation.h"

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
	Attack = 15;
	TraceRange = 300.0f;
	SetGravity(true);

	//int randn = rand() % 2;
	//if (randn == 0)
	//{
	//	Dir = "R";
	//	MoveDir = 1.0f;
	//}
	//else
	//{
	//	Dir = "L";
	//	MoveDir = -1.0f;
	//}

	Dir = "R";
	MoveDir = 1.0f;

	SetMoveSpeed(150.0f);
	SetHp(180);
	SetMaxHp(180);

	SetSize(45.0f, 45.0f);

	AnimationName[LS_IDLE] = "Idle";
	AnimationName[LS_MOVE] = "Move";
	AnimationName[LS_TRACE] = "Move";
	AnimationName[LS_ATTACK] = "Attack";
	AnimationName[LS_JUMP] = "Jump";
	
	AddAnimationClip("LIdle", AT_ATLAS, AO_LOOP, 45.0f, 45.0f, 1, 1, 1, 1, 0, 0, 0.3f, "LemurianLIdle", TEXT("Enemy/Lemurian_Left_Hold.bmp"));
	AddAnimationClip("RIdle", AT_ATLAS, AO_LOOP, 45.0f, 45.0f, 1, 1, 1, 1, 0, 0, 0.3f, "LemurianRIdle", TEXT("Enemy/Lemurian_Right_Hold.bmp"));
	AddAnimationClip("LMove", AT_ATLAS, AO_REVERS_LOOP, 45.0f, 48.0f, 9, 1, 9, 1, 8, 0, 0.4f, "LemurianLMove", TEXT("Enemy/Lemurian_Left_Move.bmp"));
	AddAnimationClip("RMove", AT_ATLAS, AO_LOOP, 45.0f, 48.0f, 9, 1, 9, 1, 0, 0, 0.4f, "LemurianRMove", TEXT("Enemy/Lemurian_Right_Move.bmp"));
	AddAnimationClip("LAttack", AT_ATLAS, AO_REVERS_BOUNCE_LOOP_LEMUIRAN, 114.0f, 67.0f, 10, 1, 10, 1, 9, 0, 0.8f, "LemurianLAttack", TEXT("Enemy/Lemurian_Left_Attack.bmp"));
	AddAnimationClip("RAttack", AT_ATLAS, AO_BOUNCE_LOOP_LEMUIRAN, 114.0f, 67.0f, 10, 1, 10, 1, 0, 0, 0.8f, "LemurianRAttack", TEXT("Enemy/Lemurian_Right_Attack.bmp"));
	AddAnimationClip("LJump", AT_ATLAS, AO_LOOP, 48.0f, 51.0f, 1, 1, 1, 1, 0, 0, 0.3f, "LemurianLJump", TEXT("Enemy/Lemurian_Left_Jump.bmp"));
	AddAnimationClip("RJump", AT_ATLAS, AO_LOOP, 48.0f, 51.0f, 1, 1, 1, 1, 0, 0, 0.3f, "LemurianRJump", TEXT("Enemy/Lemurian_Right_Jump.bmp"));

	SelectState(AnimationName, LS_ATTACK);
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

	AnimationDirCheck(AnimationName, mState);

	switch (mState)
	{
		case LS_IDLE:
			FS_IDLE(DeltaTime);
			break;
		case LS_JUMP:
			FS_JUMP(DeltaTime);
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

	return 0;
}

int Lemurian::LateUpdate(float DeltaTime)
{
	Monster::LateUpdate(DeltaTime);

	PrevFrame = m_Animation->GetFrameX();

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
		SelectState(AnimationName, LS_TRACE);
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
}

void Lemurian::FS_MOVE(float DeltaTime)
{
	MonsterMove(DeltaTime);
	RangeCheck();
}

void Lemurian::FS_TRACE(float DeltaTime)
{
	if (Distance < AttackRange)
		SelectState(AnimationName, LS_ATTACK);
}

void Lemurian::FS_ATTACK(float DeltaTime)
{

	if (m_Animation->GetIsEnd() == true)
	{
		SelectState(AnimationName, LS_MOVE);
	}
}

void Lemurian::FS_JUMP(float DeltaTime)
{
}
