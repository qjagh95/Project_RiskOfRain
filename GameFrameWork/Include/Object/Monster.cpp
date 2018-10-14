#include "Monster.h"
#include "../Object/Bullet.h"
#include "../Coll/ColliderRect.h"
#include "TargetBullet.h"
#include "../Camera.h"
#include "../Sound/SoundManager.h"

Monster::Monster()
	:Target(NULL)
{
	m_ObjectType = OT_MONSTER;
	SetTag("Monster");
	mState = MS_IDLE;
}

Monster::Monster(const Monster & Value)
{
	MoveDir = Value.MoveDir;
	FireTime = 0;
	AttackRange = Value.AttackRange;
	TraceRange = Value.TraceRange;
	mState = Value.mState;
}

Monster::~Monster()
{
	SAFE_RELEASE(Target);
}

bool Monster::Init()
{
	SetMoveSpeed(300.0f);
	SetSize(100.0f, 100.0f);
	SetPivot(0.5f, 0.5f);
	SetGravity(true);

	MoveDir = 1;
	FireTime = 0.0f;

	AttackRange = 600.0f;
	TraceRange = 1200.0f;

	SetTexture("Yasuo", TEXT("Yasuo.bmp"));

	//�浹ü����
	ColliderRect* RC = AddCollider<ColliderRect>("MonsterBody");
	RC->SetVirtualRect(100.0f, 100.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Monster");
	RC->SetCallBack<Monster>(this, &Monster::BulletHit, CS_COLDOING);
	RC->SetCallBack<Monster>(this, &Monster::FollowBulletHit, CS_COLDOING);
	RC->SetCallBack<Monster>(this, &Monster::TargetBulletHit, CS_COLDOING);
	RC->SetCallBack<Monster>(this, &Monster::RotBulletHit, CS_COLDOING);
	RC->SetCallBack<Monster>(this, &Monster::JumpBulletHit, CS_COLDOING);

	SAFE_RELEASE(RC);

	return true;
}

int Monster::Input(float DeltaTime)
{
	Charactor::Input(DeltaTime);
	return 0;
}

int Monster::Update(float DeltaTime)
{
	Charactor::Update(DeltaTime);

	mState = MS_IDLE;

	if (Target != NULL)
	{
		float Distance = Math::GetDistance(Target->GetPos(), m_Pos);

		if (Distance <= AttackRange)
			mState = MS_ATTACK;
		else if(Distance <= TraceRange)
			mState = MS_TRACE;
	}

	switch (mState)
	{
		case MS_IDLE:
			FireTime = 0.0f;
			break;
		case MS_TRACE:
			FireTime = 0.0f;
			m_Angle = Math::GetDegree(m_Pos, Target->GetPos());
			MoveByAngle(DeltaTime);
			break;
		case MS_ATTACK:
			FireTime += DeltaTime;

			if (FireTime >= 1.0f)
			{
				SoundManager::Get()->Play("1Up");
				Bullet* pBullet = (Bullet*)Object::CreateCloneObject("Bullet", m_Layer);
				pBullet->SetPos(LineEnd);
				pBullet->SetAngle(Math::GetDegree(pBullet->GetPos(), Target->GetPos()));

				const list<class Collider*>* pCollList = pBullet->GetColliderList();
				list<Collider*>::const_iterator	StartIter = pCollList->begin();
				list<Collider*>::const_iterator	EndIter = pCollList->end();

				for (; StartIter != EndIter; ++StartIter)
					(*StartIter)->SetCollsionTypeName("Monster");

				SAFE_RELEASE(pBullet);

				FireTime = 0.0f;
			}
			break;
	}
	return 0;
}

int Monster::LateUpdate(float DeltaTime)
{
	Charactor::LateUpdate(DeltaTime);
	return 0;
}

void Monster::Collision(float DeltaTime)
{
	Charactor::Collision(DeltaTime);
}

void Monster::Render(HDC Hdc, float DeltaTime)
{	
	Charactor::Render(Hdc, DeltaTime);
}

Monster * Monster::Clone()
{
	return new Monster(*this);
}

void Monster::BulletHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "BulletBody")
	{
		Object*	newBullet = Dest->GetCurObject();

		newBullet->SetisActiv(false);

		SAFE_RELEASE(newBullet);
	}
}

void Monster::RotBulletHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "RotBulletBody")
	{
		Object*	newBullet = Dest->GetCurObject();

		newBullet->SetisActiv(false);

		SAFE_RELEASE(newBullet);
	}
}

void Monster::JumpBulletHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "JumpBulletBody")
	{
		Object*	newBullet = Dest->GetCurObject();

		newBullet->SetisActiv(false);
		newBullet->SetRefCount(2);

		SAFE_RELEASE(newBullet);
	}
}

void Monster::TargetBulletHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "TargetBulletBody")
	{
		TargetBullet* newBullet = (TargetBullet*)Dest->GetCurObject();

		if (newBullet->GetIsRush() == true)
		{
			newBullet->SetisActiv(false);
			SAFE_RELEASE(newBullet);
		}

		SAFE_RELEASE(newBullet);
	}
}

void Monster::FollowBulletHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "FollowBulletBody")
	{
		Object*	newBullet = Dest->GetCurObject();

		newBullet->SetisActiv(false);

		SAFE_RELEASE(newBullet);
	}
}

void Monster::SubBulletHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "SubBulletBody")
	{
		Object*	newBullet = Dest->GetCurObject();

		newBullet->SetisActiv(false);

		SAFE_RELEASE(newBullet);
	}
}