#include "Player.h"
#include "../stdafx.h"
#include "../Input.h"
#include "../Coll/ColliderRect.h"
#include "../Coll/ColliderCircle.h"
#include "../Coll/ColliderPixel.h"
#include "../Coll/CollsionManager.h"
#include "../Resource/Animation.h"
#include "../Scene/Layer.h"
#include "Bullet.h"
#include "TargetBullet.h"
#include "FollowBullet.h"
#include "../Camera.h"
#include "Effect.h"
#include "../Sound/SoundManager.h"
#include "../Object/Tile.h"
#include "../StageManager.h"

Player::Player()
	:CurTarget(NULL)
{
	m_ObjectType = OT_PLAYER;
	SetTag("Players");
}

Player::~Player()
{
	SAFE_RELEASE(CurTarget);
}

bool Player::Init()
{
	Input::Get()->PushKey("Up", VK_UP);
	Input::Get()->PushKey("Down", VK_DOWN);
	Input::Get()->PushKey("Left", VK_LEFT);
	Input::Get()->PushKey("Right", VK_RIGHT);

	Input::Get()->PushKey("Fire", 'X');
	Input::Get()->PushKey("Skill1", 'A');
	Input::Get()->PushKey("Skill2", 'S');
	Input::Get()->PushKey("Skill3", 'D');
	Input::Get()->PushKey("Skill4", 'F');
	Input::Get()->PushKey("Jump", VK_SPACE);

	SetMoveSpeed(300.0f);
	SetPos(300.0f, 200.0f);
	SetSize(100.0f, 100.0f);
	SetPivot(0.5f, 0.5f);
	MoveDir = 1.0f;
	SetGravity(true);
	isJumping = false;
	JumpPower = 300.0f;

	//충돌체생성
	ColliderRect* RC = AddCollider<ColliderRect>("PlayerBody");
	RC->SetVirtualRect(45.0f, 60.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCallBack<Player>(this, &Player::BulletHit, CS_COLDOING);
	RC->SetCollsionTypeName("Player");
	SAFE_RELEASE(RC);

	AnimationName[PS_IDLE] = "Idle";
	AnimationName[PS_BASEATTACK] = "BaseAttack";
	AnimationName[PS_MOVE] = "Move";
	AnimationName[PS_JUMPING] = "Jump";

	pState = PS_IDLE;
	Dir = "R";
					//애니이름, 아틀라스?, 루프?, 1개당 사이즈,1줄갯수. 전체갯수. 시작위치. 행동시간
	AddAnimationClip("LIdle", AT_ATLAS, AO_LOOP, 45.0f, 60.0f, 14, 1, 21, 8, 0, 1, 1.0f, "HalBae", TEXT("Left.bmp"));
	AddAnimationClip("LAttack", AT_ATLAS, AO_LOOP, 45.0f, 60.0f, 14, 1, 21, 8, 0, 4, 1.0f, "HalBae", TEXT("Left.bmp"));
	AddAnimationClip("LMove", AT_ATLAS, AO_LOOP, 45.0f, 60.0f, 14, 1, 21, 8, 0, 3, 1.0f, "HalBae", TEXT("Left.bmp"));
	AddAnimationClip("LJump", AT_ATLAS, AO_LOOP, 45.0f, 60.0f, 14, 1, 21, 8, 0, 3, 1.0f, "HalBae", TEXT("Left.bmp"));
	AddAnimationClip("RIdle", AT_ATLAS, AO_LOOP, 45.0f, 60.0f, 14, 1, 21, 8, 0, 1, 1.0f, "HalBae", TEXT("Left.bmp"));
	AddAnimationClip("RAttack", AT_ATLAS, AO_LOOP, 45.0f, 60.0f, 14, 1, 21, 8, 0, 4, 1.0f, "HalBae", TEXT("Left.bmp"));
	AddAnimationClip("RMove", AT_ATLAS, AO_LOOP, 45.0f, 60.0f, 14, 1, 21, 8, 0, 3, 1.0f, "HalBae", TEXT("Left.bmp"));
	AddAnimationClip("RJump", AT_ATLAS, AO_LOOP, 45.0f, 60.0f, 14, 1, 21, 8, 0, 3, 1.0f, "HalBae", TEXT("Left.bmp"));

	return true;
}

int Player::Input(float DeltaTime)
{
	Charactor::Input(DeltaTime);

	//그냥발사
	if (KEYPRESS("Fire"))
	{
		Object* bullet = Object::CreateCloneObject("Bullet", m_Layer);
		bullet->SetPos(LineEnd);
		bullet->SetAngle(m_Angle);

		const list<class Collider*>* pCollList = bullet->GetColliderList();
		list<Collider*>::const_iterator	StartIter = pCollList->begin();
		list<Collider*>::const_iterator	EndIter = pCollList->end();

		for (; StartIter != EndIter; ++StartIter)
			(*StartIter)->SetCollsionTypeName("Player");

		SAFE_RELEASE(bullet);
	}

	//락온발사
	if (KEYPRESS("Skill3"))
	{
		FollowBullet* bullet = (FollowBullet*)Object::CreateCloneObject("FollowBullet", m_Layer);
		bullet->SetPos(LineEnd);

		//태그이름이 몬스터인 오브젝트의 목록을 얻어온다
		const list<Object*>* TargetList = Object::FindSceneObjects("Monster");
		list<Object*>::const_iterator StartIter = TargetList->begin();
		list<Object*>::const_iterator EndIter = TargetList->end();

		//콜리전리스트를 불러온다//같은것들끼린 충돌하지않음
		const list<class Collider*>* pCollList = bullet->GetColliderList();
		list<Collider*>::const_iterator	StartIter1 = pCollList->begin();
		list<Collider*>::const_iterator	EndIter1 = pCollList->end();

		for (; StartIter1 != EndIter1; StartIter1++)
			(*StartIter1)->SetCollsionTypeName("Players");

		for (; StartIter != EndIter; StartIter++)
		{
			if (CurTarget == NULL)
			{
				CurTarget = *StartIter;
				continue;
			}
			else
			{
				//거리를 체크한다
				//총구위치에서 타겟까지의 거리중 가장 작은놈
				float SmallDist = Math::GetDistance(LineEnd, CurTarget->GetPos());
				float BigDist = Math::GetDistance(LineEnd, (*StartIter)->GetPos());

				if (SmallDist > BigDist)
					CurTarget = *StartIter;

				//만약 중간과정에서 몹이 죽으면 CurTarget를 NULL로 바꾸면된다
				//여기서 돌면서 죽음체크를 해줘야한다.
			}
		}
		bullet->SetTarget(CurTarget);

		SAFE_RELEASE(bullet);
	}

	//if (isnan(Var)); //NULL체크를 한다.
	return 0;
}

int Player::Update(float DeltaTime)
{
	Charactor::Update(DeltaTime);

	DirCheck();

	CameraPos = Camera::Get()->GetPos();
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
		case PS_BASEATTACK:
			FS_BaseAttack(DeltaTime);
			break;
		case PS_ROPEUP:
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

	return 0;
}

int Player::LateUpdate(float DeltaTime)
{
	Charactor::LateUpdate(DeltaTime);
	return 0;
}

void Player::Collision(float DeltaTime)
{
	Charactor::Collision(DeltaTime);
}

void Player::Render(HDC Hdc, float DeltaTime)
{
	Charactor::Render(Hdc, DeltaTime);

	LineEnd.x = m_Pos.x + 150.0f * cosf(Math::DgreeToRadian(m_Angle));
	LineEnd.y = m_Pos.y + 150.0f * sinf(Math::DgreeToRadian(m_Angle));

	if (Core::Get()->GetIsDebugMode() == false)
		return;

	MoveToEx(Hdc, (int)Center.x, (int)Center.y, NULL);

	Vector2 TempPos;
	TempPos.x = Center.x + 150.0f * cosf(Math::DgreeToRadian(m_Angle));
	TempPos.y = Center.y + 150.0f * sinf(Math::DgreeToRadian(m_Angle));

	LineTo(Hdc, (int)TempPos.x, (int)TempPos.y);
}

Player * Player::Clone()
{
	return new Player(*this);
}

void Player::TileCollsionActive(float DeltaTime)
{
	if (isJumping == true)
		isJumping = false;
}

void Player::BulletHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "BulletBody")
	{
		SoundManager::Get()->Play("Stun");

		Object*	newBullet = Dest->GetCurObject();
		newBullet->SetisActiv(false);

		Effect* newEffect = (Effect*)Object::CreateCloneObject("BomeEffect",m_Layer);
		newEffect->SetPos(newBullet->GetPos());

		SAFE_RELEASE(newEffect);
		SAFE_RELEASE(newBullet);
	}
}

void Player::PlayerMove(float DeltaTime)
{
	if (KEYPRESS("Right"))
	{
		MoveByAngle(DeltaTime * MoveDir);
	}
	else if (KEYPRESS("Left"))
	{
		MoveByAngle(DeltaTime * MoveDir);
	}
}

void Player::DirCheck()
{
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

void Player::SelectState(PLAYER_STATE eState)
{
	pState = eState;

	StateName = Dir + AnimationName[pState];
	ChangeClip(StateName);
}
