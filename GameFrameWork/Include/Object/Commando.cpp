#include "Commando.h"
#include "BaseAttackBullet.h"
#include "Effect.h"

#include "../Debug.h"

#include "../stdafx.h"
#include "../Input.h"
#include "../Camera.h"
#include "../StageManager.h"

#include "../Object/Tile.h"
#include "../Object/Bar.h"
#include "../Object/Number.h"

#include "../Object/LevelUpEffect.h"

#include "../Resource/Animation.h"

#include "../Coll/ColliderRect.h"
#include "../Coll/ColliderPoint.h"

#include "../Scene/Scene.h"
#include "../Scene/Layer.h"

#include "../Object/Hider.h"

#include "../Sound/SoundManager.h"

#include "../StageManager.h"

int Commando::pMoney = 100;
int Commando::Hp = 300;
int Commando::Level = 1;
int Commando::Exp = 0;
int Commando::MaxHp = 300;
int Commando::MaxExp = 500;

Commando::Commando()
	:CurTarget(NULL), MoneyNumber(NULL), AttackDamege(12), HitCount(0), InfinityTime(0.0f)
	, SkillOneDelay(0.5f), SkillTwoDelay(5.0f), SkillThreeDelay(5.0f), SkillFourDelay(8.0f),
	isSkillOne(false), isSkillTwo(false), isSkillThree(false), isSkillFour(false), isRopeHiting(false)
	, isRopeUpHitting(false),PrevFrame(0), isLineHit(false), isInfinity(false)
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
	else if(isRopeHiting == false)
		isGravity = true;

	if (KEYDown(VK_NUMPAD0))
		pMoney += 500;
	if (KEYDown(VK_NUMPAD1))
		AttackDamege += 100;

	if (KEYDown(VK_NUMPAD9))
	{
		Hp += 50;
		MaxHp += 50;
	}


	return 0;
}

int Commando::Update(float DeltaTime)
{
	Charactor::Update(DeltaTime);

	//에구 "머니" 나!
	MoneyNumber->SetNumber(pMoney);

/////////////////////////////////////////////////////////////////////////
	ColliderRect* GetColl = (ColliderRect*)GetCollider("CommandoLine");
	if (MoveDir == 1.0f)
		GetColl->SetPivot(0.0f, 0.5f);
	else if (MoveDir == -1.0f)
		GetColl->SetPivot(1.0f, 0.5f);
	SAFE_RELEASE(GetColl);
////////////////////////////////////////////////////////////////////////
	PrevHitPos = HitPos;

	DirCheck();
	HpCheck(DeltaTime);
	RopeCheck();
	LevelUpCheck();
	SkillTimeCheck(DeltaTime);

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
		case PS_JUMPDOWN:
			Fs_JumpDown(DeltaTime);
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

	isLineHit = false;
	HitPos = { 0.0f, 0.0f };
	HitPosList.clear();

	return 0;
}

int Commando::LateUpdate(float DeltaTime)
{
	Charactor::LateUpdate(DeltaTime);

	isRopeHiting = false;
	isRopeUpHitting = false;
	PrevFrame = m_Animation->GetFrameX();

	return 0;
}

void Commando::Collision(float DeltaTime)
{
	Charactor::Collision(DeltaTime);
}

void Commando::CollsionAfterUpdate(float DeltaTime)
{
	Charactor::CollsionAfterUpdate(DeltaTime);

	char Buffer[255];
	sprintf_s(Buffer, "Hp : %d \n", Hp);
	Debug::OutputConsole(Buffer);
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
	{
		if (m_Pos.x + m_Size.GetHalfX() >= StageManager::Get()->GetWidth())
			return;

		Tile* CurTile = StageManager::Get()->GetTile(m_Pos);
		Tile* NextTile = StageManager::Get()->GetTile(m_Pos.x + m_Size.GetHalfX(), m_Pos.y);

		if (NextTile->GetTileType() == TT_NOMOVE)
		{
			SAFE_RELEASE(CurTile);
			SAFE_RELEASE(NextTile);
			return;
		}
		MoveByAngle(DeltaTime * MoveDir);

		SAFE_RELEASE(CurTile);
		SAFE_RELEASE(NextTile);
	}

	else if (KEYPRESS("Left"))
	{
		if (m_Pos.x - m_Size.GetHalfX() <= 0.0f)
			return;

		Tile* CurTile = StageManager::Get()->GetTile(m_Pos);
		Tile* NextTile = StageManager::Get()->GetTile(m_Pos.x - m_Size.GetHalfX(), m_Pos.y);

		if (NextTile->GetTileType() == TT_NOMOVE)
		{
			SAFE_RELEASE(CurTile);
			SAFE_RELEASE(NextTile);
			return;
		}

		MoveByAngle(DeltaTime * MoveDir);

		SAFE_RELEASE(CurTile);
		SAFE_RELEASE(NextTile);
	}
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

void Commando::HpCheck(float DeltaTime)
{
	HpTimeVar += DeltaTime;

	if (HpTimeVar >= 1.0f)
	{
		HpTimeVar = 0.0f;

		if(Hp < MaxHp)
			Hp += 3;
	}

	if (Hp <= 0)
	{
		Hp = 0;
	}
	else if (Hp >= MaxHp)
	{
		Hp = MaxHp;
	}
}

void Commando::RopeCheck()
{
	if (isRopeHiting == true)
	{
		if (KEYPRESS("Up") == false && KEYPRESS("Down") == false)
			return;

		if (KEYPRESS("Up") == true && isRopeUpHitting == true)
			SelectState(PLAYER_STATE::PS_ROPE);
		else if (KEYPRESS("Down"))
			SelectState(PLAYER_STATE::PS_ROPE);
	}
}

void Commando::LevelUpCheck()
{
	if (Exp >= MaxExp)
	{
		LevelUpEffect* newEffect = (LevelUpEffect*)Object::CreateCloneObject("LevelUpEffect", m_Layer);
		newEffect->SetPos(Vector2(m_Pos.x, m_Pos.y - m_Size.GetHalfY()));
		SAFE_RELEASE(newEffect);

		SoundManager::Get()->Play("LevelUp");

		Level += 1;

		AttackDamege += 5;

		MaxExp += 130;

		Exp = 0;

		int Temp = (int)(MaxHp * 1.2f) - MaxHp;
		MaxHp = (int)(MaxHp * 1.2f);
		Hp += Temp;
	}
}

void Commando::SelectState(PLAYER_STATE eState)
{
	PrevState = pState;
	pState = eState;

	if (pState != PS_ROPE)
	{
		StateName = Dir + AnimationName[pState];
		ChangeClip(StateName);
	}
}

void Commando::SkillState()
{
	if (KEYPress('Z'))
	{
		if (isSkillOne == false)
		{
			SelectState(PLAYER_STATE::PS_SKILL1);
			HitCount++;
		}

		isSkillOne = true;
	}

	if (KEYDown('X'))
	{
		if (isSkillTwo == false)
		{
			Layer* TempLayer = m_Scene->FindLayer("UI");

			Hider* OneHider = Object::CreateObject<Hider>("HiderOne", TempLayer);
			OneHider->SetHider(ST_SKILLTWO, SkillTwoDelay);
			SAFE_RELEASE(OneHider);
			SAFE_RELEASE(TempLayer);

			SelectState(PLAYER_STATE::PS_SKILL2);
		}
		isSkillTwo = true;
	}
	if (KEYDown('C'))
	{
		if (isSkillThree == false)
		{
			Layer* TempLayer = m_Scene->FindLayer("UI");

			Hider* OneHider = Object::CreateObject<Hider>("HiderOne", TempLayer);
			OneHider->SetHider(ST_SKILLTHREE, SkillThreeDelay);
			SAFE_RELEASE(OneHider);
			SAFE_RELEASE(TempLayer);

			SelectState(PLAYER_STATE::PS_SKILL3);
		}
		isSkillThree = true;
	}
	if (KEYDown('V'))
	{
		if (isSkillFour == false)
		{
			Layer* TempLayer = m_Scene->FindLayer("UI");

			Hider* OneHider = Object::CreateObject<Hider>("HiderOne", TempLayer);
			OneHider->SetHider(ST_SKILLFOUR, SkillFourDelay);
			SAFE_RELEASE(OneHider);
			SAFE_RELEASE(TempLayer);

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
			SkillOneDelay = 0.5f;
			isSkillOne = false;
		}
	}

	if (isSkillTwo == true)
	{
		SkillTwoDelay -= DeltaTime;

		if (SkillTwoDelay <= 0.0f)
		{
			SkillTwoDelay = 5.0f;
			isSkillTwo = false;
		}
	}

	if (isSkillThree == true)
	{
		SkillThreeDelay -= DeltaTime;

		if (SkillThreeDelay <= 0.0f)
		{
			SkillThreeDelay = 5.0f;
			isSkillThree = false;
		}
	}

	if (isSkillFour == true)
	{
		SkillFourDelay -= DeltaTime;

		if (SkillFourDelay <= 0.0f)
		{
			SkillFourDelay = 6.0f;
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
	AnimationName[PS_JUMPDOWN] = "JumpDown";

	pState = PS_IDLE;
	Dir = "R";

	//				애니이름, 아틀라스?, 루프?, 1개당 사이즈,  1줄갯수.  전체갯수. 시작위치. 행동시간
	//리버스시 시작위치 마지막 - 1
	//REVERS_BOUNCE 시작위치 마지막 - 1
	AddAnimationClip("LIdle", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 1, 1, 1, 1, 0, 0, 0.5f, "LeftIdle", TEXT("Commando/LeftIdle.bmp"));
	AddAnimationClip("LMove", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 8, 1, 8, 1, 0, 0, 0.6f, "LeftMove", TEXT("Commando/LeftMove.bmp"));
	AddAnimationClip("LJump", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 1, 1, 1, 1, 0, 0, 0.5f, "LeftJump", TEXT("Commando/LeftJump.bmp"));

	AddAnimationClip("RIdle", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 1, 1, 1, 1, 0, 0, 0.5f, "RightIdle", TEXT("Commando/RightIdle.bmp"));
	AddAnimationClip("RMove", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 8, 1, 8, 1, 0, 0, 0.6f, "RightMove", TEXT("Commando/RightMove.bmp"));
	AddAnimationClip("RJump", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 1, 1, 1, 1, 0, 0, 0.5f, "RightJump", TEXT("Commando/RightJump.bmp"));

	AddAnimationClip("LJumpDown", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 1, 1, 1, 1, 0, 0, 0.5f, "LeftJumpDown", TEXT("Commando/LeftJump.bmp"));
	AddAnimationClip("RJumpDown", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 1, 1, 1, 1, 0, 0, 0.5f, "RightJumpDown", TEXT("Commando/RightJump.bmp"));

	AddAnimationClip("LSkill1", AT_ATLAS, AO_REVERS_BOUNCE_LOOP, 54.0f, 40.0f, 4, 1, 4, 1, 3, 0, 0.4f, "LeftSkill1", TEXT("Commando/LeftSkill1.bmp"));
	AddAnimationClip("LSkill2", AT_ATLAS, AO_REVERS_BOUNCE_LOOP, 94.0f, 40.0f, 4, 1, 4, 1, 3, 0, 0.4f, "LeftSkill2", TEXT("Commando/LeftSkill2.bmp"));
	AddAnimationClip("LSkill3", AT_ATLAS, AO_REVERS_LOOP, 40.0f, 40.0f, 9, 1, 9, 1, 8, 0, 0.4f, "LeftSkill3", TEXT("Commando/LeftSkill3.bmp"));
	AddAnimationClip("LSkill4", AT_ATLAS, AO_REVERS_BOUNCE_LOOP, 66.0f, 40.0f, 13, 1, 13, 1, 12, 0, 0.7f, "LeftSkill4", TEXT("Commando/LeftSkill4.bmp"));

	AddAnimationClip("RSkill1", AT_ATLAS, AO_LOOP, 54.0f, 40.0f, 4, 1, 4, 1, 0, 0, 0.4f, "RightSkill1", TEXT("Commando/RightSkill1.bmp"));
	AddAnimationClip("RSkill2", AT_ATLAS, AO_LOOP, 94.0f, 40.0f, 4, 1, 4, 1, 0, 0, 0.4f, "RightSkill2", TEXT("Commando/RightSkill2.bmp"));
	AddAnimationClip("RSkill3", AT_ATLAS, AO_LOOP, 40.0f, 40.0f, 9, 1, 9, 1, 0, 0, 0.4f, "RightSkill3", TEXT("Commando/RightSkill3.bmp"));
	AddAnimationClip("RSkill4", AT_ATLAS, AO_LOOP, 66.0f, 40.0f, 13, 1, 13, 1, 0, 0, 0.7f, "RightSkill4", TEXT("Commando/RightSkill4.bmp"));

	AddAnimationClip("RopeUp", AT_ATLAS, AO_LOOP, 18.0f, 36.0f, 6, 1, 6, 1, 0, 0, 0.4f, "RopeUp", TEXT("Commando/Ladder_Move.bmp"));
	AddAnimationClip("RopeHold", AT_ATLAS, AO_LOOP, 18.0f, 36.0f, 1, 1, 1, 1, 0, 0, 0.4f, "RopeHold", TEXT("Commando/Ladder_Hold.bmp"));
}

void Commando::CollsionInit()
{
	//충돌체생성
	ColliderRect* RC = AddCollider<ColliderRect>("CommandoBody");
	RC->SetVirtualRect(40.0f, 40.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCallBack<Commando>(this, &Commando::BulletHit, CS_COLFIRST);
	RC->SetCallBack<Commando>(this, &Commando::PumpHit, CS_COLFIRST);
	RC->SetCallBack<Commando>(this, &Commando::CoinHit, CS_COLFIRST);
	RC->SetCallBack<Commando>(this, &Commando::ItemBoxHit, CS_COLDOING);
	RC->SetCallBack<Commando>(this, &Commando::TearHit, CS_COLFIRST);
	RC->SetCallBack<Commando>(this, &Commando::AncientHit, CS_COLFIRST);
	RC->SetCallBack<Commando>(this, &Commando::JellyFishHit, CS_COLFIRST);
	RC->SetCallBack<Commando>(this, &Commando::LemuiranHit, CS_COLFIRST);
	RC->SetCallBack<Commando>(this, &Commando::WispHit, CS_COLFIRST);
	RC->SetCollsionTypeName("Commando");
	SAFE_RELEASE(RC);

	ColliderRect* RC2 = AddCollider<ColliderRect>("CommandoLine");
	RC2->SetVirtualRect(Core::Get()->GetWinSizeVector2().x, 5.0f);
	RC2->SetPivot(0.0f, 0.5f);
	RC2->SetCallBack(this, &Commando::LineHit, CS_COLDOING);
	RC2->SetCollsionTypeName("CommandoLine");
	SAFE_RELEASE(RC2);

	//로프판단.
	ColliderPoint* RP = AddCollider<ColliderPoint>("CommandoMiddlePoint");
	RP->SetPivot(0.0f, -0.5f);
	RP->SetCallBack<Commando>(this, &Commando::RopeHit, CS_COLDOING);
	RP->SetCollsionTypeName("Commando");
	SAFE_RELEASE(RP);

	ColliderPoint* RP2 = AddCollider<ColliderPoint>("CommandoUpPoint");
	RP2->SetPivot(0.0f, 0.5f);
	RP2->SetCallBack<Commando>(this, &Commando::RopeUpHit, CS_COLDOING);
	RP2->SetCollsionTypeName("Commando");
	SAFE_RELEASE(RP2);
}

void Commando::InfoInit()
{
	SetMoveSpeed(BASESPEED);
	SetPos(150.0f, 1950.0f);
	SetSize(40.0f, 40.0f);
	SetPivot(0.5f, 0.5f);
	MoveDir = 1.0f;
	SetGravity(true);
	isJumping = false;
	HpTimeVar = 0.0f;
	TimeVar = 0.0f;
}

