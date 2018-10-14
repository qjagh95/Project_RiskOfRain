#include "Commando.h"
#include "Bullet.h"
#include "Effect.h"

#include "../stdafx.h"
#include "../Input.h"
#include "../Camera.h"
#include "../StageManager.h"

#include "../Object/Tile.h"
#include "../Object/Bar.h"
#include "../Object/Number.h"

#include "../Resource/Animation.h"

#include "../Coll/ColliderRect.h"
#include "../Coll/ColliderPoint.h"

#include "../Scene/Scene.h"
#include "../Scene/Layer.h"

#include "../Object/Hider.h"

#include "../Sound/SoundManager.h"

int Commando::pMoney = 100;
int Commando::Hp = 300;
int Commando::Level = 1;
int Commando::Exp = 0;
int Commando::MaxHp = 300;
int Commando::MaxExp = 500;

Commando::Commando()
	:CurTarget(NULL), MoneyNumber(NULL), AttackDamege(10)
	, SkillOneDelay(5.0f), SkillTwoDelay(6.0f), SkillThreeDelay(7.0f), SkillFourDelay(8.0f),
	isSkillOne(false), isSkillTwo(false), isSkillThree(false), isSkillFour(false), isRopeHiting(false)
{
	m_ObjectType = OT_PLAYER;
	SetTag("Commando");
}

Commando::~Commando()
{
	SAFE_RELEASE(CurTarget);
	SAFE_RELEASE(MoneyNumber);
}

bool Commando::Init()
{
	BasicInit();
	InfoInit();
	AnimationInit();
	CollsionInit();

	return true;
}

int Commando::Input(float DeltaTime)
{
	Charactor::Input(DeltaTime);

	if (isRopeHiting == true)
		isGravity = false;
	else
		isGravity = true;

	return 0;
}

int Commando::Update(float DeltaTime)
{
	Charactor::Update(DeltaTime);
	//머니머니!
	MoneyNumber->SetNumber(pMoney);

	DirCheck();
	HpCheck();
	RopeCheck();
	SkillTimeCheck(DeltaTime);

	Vector2 CameraPos = Camera::Get()->GetPos();
	Center = m_Pos - CameraPos;

	switch (pState)
	{
		case PS_IDLE:
			FS_Idle(DeltaTime);
			break;
		case PS_MOVE:
			FS_Move(DeltaTime);
			break;
		case PS_JUMPING:
			FS_Jump(DeltaTime);
			break;
		case PS_ROPE:
			FS_Rope(DeltaTime);
			break;
		case PS_SKILL1:
			FS_Skill1(DeltaTime);
			break;
		case PS_SKILL2:
			FS_Skill2(DeltaTime);
			break;
		case PS_SKILL3:
			FS_Skill3(DeltaTime);
			break;
		case PS_SKILL4:
			FS_Skill4(DeltaTime);
			break;
	}

	isRopeHiting = false;

	return 0;
}

int Commando::LateUpdate(float DeltaTime)
{
	Charactor::LateUpdate(DeltaTime);

	return 0;
}

void Commando::Collision(float DeltaTime)
{
	Charactor::Collision(DeltaTime);
}

void Commando::Render(HDC Hdc, float DeltaTime)
{
	Charactor::Render(Hdc, DeltaTime);
}

Commando * Commando::Clone()
{
	return new Commando(*this);
}

void Commando::PlayerMove(float DeltaTime)
{
	if (KEYPRESS("Right"))
		MoveByAngle(DeltaTime * MoveDir);
	else if (KEYPRESS("Left"))
		MoveByAngle(DeltaTime * MoveDir);
}

void Commando::DirCheck()
{
	if (pState == PS_SKILL1 ||
		pState == PS_SKILL2 ||
		pState == PS_SKILL3 ||
		pState == PS_SKILL4 ||
		pState == PS_ROPE
		)
		return;

	string CheckDir = Dir;

	if (KEYPRESS("Right"))
	{
		MoveDir = 1.0f;
		CheckDir = "R";
	}
	else if (KEYPRESS("Left"))
	{
		MoveDir = -1.0f;
		CheckDir = "L";
	}

	if (CheckDir != Dir)
	{
		StateName = CheckDir + AnimationName[pState];
		ChangeClip(StateName);
		Dir = CheckDir;
	}
}

void Commando::HpCheck()
{
	if (Hp <= 0)
		Hp = 0;
	else if (Hp >= MaxHp)
		Hp = MaxHp;

	if (Exp > MaxExp)
		Exp = 0;
}

void Commando::RopeCheck()
{
	if (isRopeHiting == true)
	{
		if (KEYPRESS("Up"))
			SelectState(PLAYER_STATE::PS_ROPE);
		if (KEYPRESS("Down"))
			SelectState(PLAYER_STATE::PS_ROPE);
	}
}

void Commando::SelectState(PLAYER_STATE eState)
{
	pState = eState;

	if (pState != PS_ROPE)
	{
		StateName = Dir + AnimationName[pState];
		ChangeClip(StateName);
	}
}

void Commando::SkillState()
{
	if (KEYDOWN("Skill1"))
	{
		if (isSkillOne == false)
		{
			Hider* OneHider = Object::CreateObject<Hider>("HiderOne", m_Scene->FindLayer("UI"));
			OneHider->SetHider(ST_SKILLONE, SkillOneDelay);
			SAFE_RELEASE(OneHider);

			SelectState(PLAYER_STATE::PS_SKILL1);
		}
		isSkillOne = true;
	}

	if (KEYDOWN("Skill2"))
	{
		if (isSkillTwo == false)
		{
			Hider* OneHider = Object::CreateObject<Hider>("HiderOne", m_Scene->FindLayer("UI"));
			OneHider->SetHider(ST_SKILLTWO, SkillTwoDelay);
			SAFE_RELEASE(OneHider);

			SelectState(PLAYER_STATE::PS_SKILL2);
		}
		isSkillTwo = true;
	}
	if (KEYDOWN("Skill3"))
	{
		if (isSkillThree == false)
		{
			Hider* OneHider = Object::CreateObject<Hider>("HiderOne", m_Scene->FindLayer("UI"));
			OneHider->SetHider(ST_SKILLTHREE, SkillThreeDelay);
			SAFE_RELEASE(OneHider);

			SelectState(PLAYER_STATE::PS_SKILL3);
		}
		isSkillThree = true;
	}
	if (KEYDOWN("Skill4"))
	{
		if (isSkillFour == false)
		{
			Hider* OneHider = Object::CreateObject<Hider>("HiderOne", m_Scene->FindLayer("UI"));
			OneHider->SetHider(ST_SKILLFOUR, SkillFourDelay);
			SAFE_RELEASE(OneHider);

			SelectState(PLAYER_STATE::PS_SKILL4);
		}
		isSkillFour = true;
	}
}

void Commando::SkillTimeCheck(float DeltaTime)
{
	if (isSkillOne == true)
	{
		SkillOneDelay -= DeltaTime;

		if (SkillOneDelay <= 0.0f)
		{
			SkillOneDelay = 5.0f;
			isSkillOne = false;
		}
	}

	if (isSkillTwo == true)
	{
		SkillTwoDelay -= DeltaTime;

		if (SkillTwoDelay <= 0.0f)
		{
			SkillTwoDelay = 6.0f;
			isSkillTwo = false;
		}
	}

	if (isSkillThree == true)
	{
		SkillThreeDelay -= DeltaTime;

		if (SkillThreeDelay <= 0.0f)
		{
			SkillThreeDelay = 7.0f;
			isSkillThree = false;
		}
	}

	if (isSkillFour == true)
	{
		SkillFourDelay -= DeltaTime;

		if (SkillFourDelay <= 0.0f)
		{
			SkillFourDelay = 7.0f;
			isSkillFour = false;
		}
	}
}

void Commando::BasicInit()
{
	Input::Get()->PushKey("Up", VK_UP);
	Input::Get()->PushKey("Down", VK_DOWN);
	Input::Get()->PushKey("Left", VK_LEFT);
	Input::Get()->PushKey("Right", VK_RIGHT);

	Input::Get()->PushKey("RopeLeft", VK_SPACE, VK_LEFT);
	Input::Get()->PushKey("RopeRight", VK_SPACE, VK_RIGHT);

	Input::Get()->PushKey("Skill1", 'Z');
	Input::Get()->PushKey("Skill2", 'X');
	Input::Get()->PushKey("Skill3", 'C');
	Input::Get()->PushKey("Skill4", 'V');
	Input::Get()->PushKey("Jump", VK_SPACE);

	MoneyNumber = Object::CreateObject<Number>("MoneyNumber", m_Layer);
	MoneyNumber->SetPos(Vector2(240.0f, 110.0f));
	MoneyNumber->SetTexture("MoneyNumber", TEXT("object/TempNumber.bmp"));
	MoneyNumber->SetNumberSize(19.0f, 24.0f);
	MoneyNumber->SetColorKey(RGB(255, 0, 255));
	MoneyNumber->SetIsCameraMode(false);
	MoneyNumber->SetNumberViewSize(Vector2(25.0f, 25.0f));
	MoneyNumber->SetZeroViewSize(Vector2(25.0f, 25.0f));
}

void Commando::AnimationInit()
{
	AnimationName[PS_IDLE] = "Idle";
	AnimationName[PS_MOVE] = "Move";
	AnimationName[PS_JUMPING] = "Jump";
	AnimationName[PS_SKILL1] = "Skill1";
	AnimationName[PS_SKILL2] = "Skill2";
	AnimationName[PS_SKILL3] = "Skill3";
	AnimationName[PS_SKILL4] = "Skill4";
	AnimationName[PS_ROPE] = "Rope";

	pState = PS_IDLE;
	Dir = "R";

	//				애니이름, 아틀라스?, 루프?, 1개당 사이즈,  1줄갯수.  전체갯수. 시작위치. 행동시간
	//리버스시 시작위치 마지막 - 1
	AddAnimationClip("LIdle", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 1, 1, 1, 1, 0, 0, 0.5f, "LeftIdle", TEXT("Commando/LeftIdle.bmp"));
	AddAnimationClip("LMove", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 8, 1, 8, 1, 0, 0, 0.6f, "LeftMove", TEXT("Commando/LeftMove.bmp"));
	AddAnimationClip("LJump", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 1, 1, 1, 1, 0, 0, 0.5f, "LeftJump", TEXT("Commando/LeftJump.bmp"));

	AddAnimationClip("RIdle", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 1, 1, 1, 1, 0, 0, 0.5f, "RightIdle", TEXT("Commando/RightIdle.bmp"));
	AddAnimationClip("RMove", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 8, 1, 8, 1, 0, 0, 0.6f, "RightMove", TEXT("Commando/RightMove.bmp"));
	AddAnimationClip("RJump", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 1, 1, 1, 1, 0, 0, 0.5f, "RightJump", TEXT("Commando/RightJump.bmp"));

	AddAnimationClip("LSkill1", AT_ATLAS, AO_REVERS_LOOP, 54.0f, 40.0f, 4, 1, 4, 1, 3, 0, 0.4f, "LeftSkill1", TEXT("Commando/LeftSkill1.bmp"));
	AddAnimationClip("LSkill2", AT_ATLAS, AO_REVERS_LOOP, 94.0f, 40.0f, 4, 1, 4, 1, 3, 0, 0.4f, "LeftSkill2", TEXT("Commando/LeftSkill2.bmp"));
	AddAnimationClip("LSkill3", AT_ATLAS, AO_REVERS_LOOP, 40.0f, 40.0f, 9, 1, 9, 1, 8, 0, 0.4f, "LeftSkill3", TEXT("Commando/LeftSkill3.bmp"));
	AddAnimationClip("LSkill4", AT_ATLAS, AO_REVERS_LOOP, 66.0f, 40.0f, 13, 1, 13, 1, 12, 0, 0.4f, "LeftSkill4", TEXT("Commando/LeftSkill4.bmp"));

	AddAnimationClip("RSkill1", AT_ATLAS, AO_LOOP, 54.0f, 40.0f, 4, 1, 4, 1, 0, 0, 0.4f, "RightSkill1", TEXT("Commando/RightSkill1.bmp"));
	AddAnimationClip("RSkill2", AT_ATLAS, AO_LOOP, 94.0f, 40.0f, 4, 1, 4, 1, 0, 0, 0.4f, "RightSkill2", TEXT("Commando/RightSkill2.bmp"));
	AddAnimationClip("RSkill3", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 9, 1, 9, 1, 0, 0, 0.4f, "RightSkill3", TEXT("Commando/RightSkill3.bmp"));
	AddAnimationClip("RSkill4", AT_ATLAS, AO_LOOP, 66.0f, 40.0f, 13, 1, 13, 1, 0, 0, 0.4f, "RightSkill4", TEXT("Commando/RightSkill4.bmp"));

	AddAnimationClip("RopeUp", AT_ATLAS, AO_LOOP, 18.0f, 36.0f, 6, 1, 6, 1, 0, 0, 0.4f, "RopeUp", TEXT("Commando/Ladder_Move.bmp"));
	AddAnimationClip("RopeHold", AT_ATLAS, AO_LOOP, 18.0f, 36.0f, 1, 1, 1, 1, 0, 0, 0.4f, "RopeHold", TEXT("Commando/Ladder_Hold.bmp"));
}

void Commando::CollsionInit()
{
	//충돌체생성
	ColliderRect* RC = AddCollider<ColliderRect>("PlayerBody");
	RC->SetVirtualRect(40.0f, 40.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCallBack<Commando>(this, &Commando::BulletHit, CS_COLFIRST);
	RC->SetCollsionTypeName("Commando");
	SAFE_RELEASE(RC);

	//로프판단.
	ColliderPoint* RP = AddCollider<ColliderPoint>("PlayerPoint");
	RP->SetPivot(0.5f, 0.5f);
	RP->SetCallBack<Commando>(this, &Commando::RopeHit, CS_COLDOING);
	RP->SetCollsionTypeName("Commando");
	SAFE_RELEASE(RP);
}

void Commando::InfoInit()
{
	SetMoveSpeed(300.0f);
	SetPos(300.0f, 200.0f);
	SetSize(40.0f, 40.0f);
	SetPivot(0.5f, 0.5f);
	MoveDir = 1.0f;
	SetGravity(true);
	isJumping = false;
}

