#include "Monster.h"
#include "../Object/Bullet.h"
#include "../Coll/ColliderRect.h"
#include "../Camera.h"
#include "../Sound/SoundManager.h"

#include "../Object/Bar.h"

Monster::Monster()
	:Target(NULL), Hp(100), MaxHp(100)
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
	Hp = Value.Hp;
	MaxHp = Value.MaxHp;
	mHpBar = Value.mHpBar;
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

	//中宜端持失
	ColliderRect* RC = AddCollider<ColliderRect>("MonsterBody");
	RC->SetVirtualRect(100.0f, 100.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Monster");
	RC->SetCallBack<Monster>(this, &Monster::BaseAttackHitFirst, CS_COLFIRST);

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

void Monster::SetTarget(Object * Value)
{
	SAFE_RELEASE(Target);

	if (Target != NULL)
		Target->AddRefCount();

	Target = Value;
}

Monster * Monster::Clone()
{
	return new Monster(*this);
}

void Monster::BaseAttackHitFirst(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "BulletBody")
	{
		Object*	newBullet = Dest->GetCurObject();

		newBullet->SetisActiv(false);

		SAFE_RELEASE(newBullet);
	}
}

void Monster::BaseAttackHitDoing(Collider * Src, Collider * Dest, float DeltaTime)
{
}

void Monster::BaseAttackHitEnd(Collider * Src, Collider * Dest, float DeltaTime)
{
}

void Monster::SkillTwoHitFirst(Collider * Src, Collider * Dest, float DeltaTime)
{
}
void Monster::SkillTwoHitDoing(Collider * Src, Collider * Dest, float DeltaTime)
{
}
void Monster::SkillTwoHitEnd(Collider * Src, Collider * Dest, float DeltaTime)
{
}

void Monster::SkillThreeHitFirst(Collider * Src, Collider * Dest, float DeltaTime)
{
}

void Monster::SkillThreeHitDoing(Collider * Src, Collider * Dest, float DeltaTime)
{
}

void Monster::SkillThreeHitEnd(Collider * Src, Collider * Dest, float DeltaTime)
{
}

void Monster::SkillFourHitFirst(Collider * Src, Collider * Dest, float DeltaTime)
{
}

void Monster::SkillFourHitDoing(Collider * Src, Collider * Dest, float DeltaTime)
{
}

void Monster::SkillFourHitEnd(Collider * Src, Collider * Dest, float DeltaTime)
{
}
