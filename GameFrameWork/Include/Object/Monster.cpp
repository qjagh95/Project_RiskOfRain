#include "Monster.h"
#include "../Camera.h"

#include "../Coll/ColliderRect.h"
#include "../Sound/SoundManager.h"
#include "../Object/Bar.h"
#include "../Scene/Layer.h"
#include "../Object/BaseAttackBullet.h"
#include "../Object/LaserBullet.h"

Monster::Monster()
	:Target(NULL), Hp(100), MaxHp(100), HpBar(NULL)
{
	m_ObjectType = OT_MONSTER;
	SetTag("Monster");
	Dir = "R";
}

Monster::Monster(const Monster & Value)
{
	MoveDir = Value.MoveDir;
	Hp = Value.Hp;
	MaxHp = Value.MaxHp;
	HpBar = Value.HpBar;
	Dir = Value.Dir;
}

Monster::~Monster()
{
	SAFE_RELEASE(Target);
	SAFE_RELEASE(HpBar);
	SAFE_RELEASE(RC);
}

bool Monster::Init()
{
	SetMoveSpeed(300.0f);
	SetSize(100.0f, 100.0f);
	SetPivot(0.5f, 0.5f);
	SetGravity(true);

	MoveDir = 1.0f;

	SetTexture("Yasuo", TEXT("Yasuo.bmp"));

	//충돌체생성
	RC = AddCollider<ColliderRect>("MonsterBody");
	RC->SetVirtualRect(100.0f, 100.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Monster");
	RC->SetCallBack<Monster>(this, &Monster::BaseAttackHitFirst, CS_COLFIRST);
	RC->SetCallBack<Monster>(this, &Monster::BaseAttackHitDoing, CS_COLDOING);
	RC->SetCallBack<Monster>(this, &Monster::BaseAttackHitEnd, CS_COLEND);

	RC->SetCallBack<Monster>(this, &Monster::SkillTwoHitFirst, CS_COLFIRST);
	RC->SetCallBack<Monster>(this, &Monster::SkillTwoHitDoing, CS_COLDOING);
	RC->SetCallBack<Monster>(this, &Monster::SkillTwoHitEnd, CS_COLEND);

	RC->SetCallBack<Monster>(this, &Monster::SkillThreeHitFirst, CS_COLFIRST);
	RC->SetCallBack<Monster>(this, &Monster::SkillThreeHitDoing, CS_COLDOING);
	RC->SetCallBack<Monster>(this, &Monster::SkillThreeHitEnd, CS_COLEND);

	RC->SetCallBack<Monster>(this, &Monster::SkillFourHitFirst, CS_COLFIRST);
	RC->SetCallBack<Monster>(this, &Monster::SkillFourHitDoing, CS_COLDOING);
	RC->SetCallBack<Monster>(this, &Monster::SkillFourHitEnd, CS_COLEND);

	HpBar = Object::CreateObject<Bar>("mHpBar", m_Layer);
	HpBar->SetSize(Vector2(100.0f, 6.0f));
	HpBar->SetPos(m_Pos.x, m_Pos.y - m_Size.GetHalfY());
	HpBar->SetBarInfo(0, MaxHp, Hp);
	HpBar->SetTexture("mHpBar", TEXT("MonsterHpBar.bmp"));
	HpBar->SetIsCameraMode(true);

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

	HpBar->SetPos(m_Pos.x - m_Size.GetHalfX(), m_Pos.y - m_Size.y);
	HpBar->SetBarInfo(0, MaxHp, Hp);

	if (Hp <= 0)
	{
		Hp = 0;
		SetisActiv(false);
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

void Monster::TileCollsionActive(float DeltaTime)
{
	ClearGravityTime();
	SetForce(0.0f);
}

void Monster::BaseAttackHitFirst(Collider * Src, Collider * Dest, float DeltaTime)
{
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
