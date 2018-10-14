#include "Monster.h"
#include "../Camera.h"

#include "../Coll/ColliderRect.h"
#include "../Sound/SoundManager.h"
#include "../Object/Bar.h"
#include "../Scene/Layer.h"
#include "../Object/BaseAttackBullet.h"
#include "../Object/LaserBullet.h"
#include "../Object/Number.h"
#include "../Object/DieEffect.h"
#include "../Object/MoneyCoin.h"
#include "../Object/ExpCoin.h"

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
	MoneyCoinCount = Value.MoneyCoinCount;
	ExpCoinCount = Value.ExpCoinCount;
}

Monster::~Monster()
{
	SAFE_RELEASE(Target);
	SAFE_RELEASE(HpBar);
	SAFE_RELEASE(RC);
}

bool Monster::Init()
{
	MoneyCoinCount = 6;
	ExpCoinCount = 8;

	SetMoveSpeed(300.0f);
	SetPivot(0.5f, 0.5f);
	SetGravity(true);

	MoveDir = 1.0f;

	SetTexture("Yasuo", TEXT("Yasuo.bmp"));

	//충돌체생성
	RC = AddCollider<ColliderRect>("MonsterBody");
	RC->SetVirtualRect(m_Size);
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
	HpBar->SetBarInfo(0, MaxHp, Hp);
	HpBar->SetTexture("mHpBar", TEXT("MonsterHpBar.bmp"));
	HpBar->SetIsCameraMode(true);

	return true;
}

int Monster::Input(float DeltaTime)
{
	Charactor::Input(DeltaTime);

	if (MoveDir == 1.0f)
		Dir = "R";
	else if (MoveDir == -1.0f)
		Dir = "L";

	return 0;
}

int Monster::Update(float DeltaTime)
{
	Charactor::Update(DeltaTime);

	RC->SetVirtualRect(m_Size);

	HpBar->SetPos(m_Pos.x - HpBar->GetSize().GetHalfX(), m_Pos.y - m_Size.y);
	HpBar->SetBarInfo(0, MaxHp, Hp);

	Target = FindSceneObject("Commando");

	if (Hp <= 0)
	{
		Hp = 0;

		DieEffect* newEffect = (DieEffect*)Object::CreateCloneObject("DieEffect", m_Layer);
		newEffect->SetPos(m_Pos);
		SAFE_RELEASE(newEffect);

		//-50% ~ 원래숫자
		int a = Math::RandomRange((int)(MoneyCoinCount * 0.5f), MoneyCoinCount);
		int b = Math::RandomRange((int)(ExpCoinCount * 0.5f), ExpCoinCount);

		for (int i = 0; i < a; i++)
		{
			//Money
			float x = (float)(Math::RandomRange((int)m_Pos.x - (int)m_Size.GetHalfX(), (int)RightBottom.x));
			float y = (float)(Math::RandomRange((int)m_Pos.y - (int)m_Size.GetHalfY(), (int)RightBottom.y));

			MoneyCoin* newMoney = (MoneyCoin*)Object::CreateCloneObject("MoneyCoin", m_Layer);
			newMoney->SetPos(Vector2(x,y));
			SAFE_RELEASE(newMoney)
		}
		for (int i = 0; i < b; i++)
		{
			//Exp
			float x = (float)(Math::RandomRange((int)m_Pos.x - (int)m_Size.GetHalfX(), (int)RightBottom.x));
			float y = (float)(Math::RandomRange((int)m_Pos.y - (int)m_Size.GetHalfY(), (int)RightBottom.y));

			ExpCoin* newExp = (ExpCoin*)Object::CreateCloneObject("ExpCoin", m_Layer);
			newExp->SetPos(Vector2(x, y));
			SAFE_RELEASE(newExp)
		}
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

void Monster::CollsionAfterUpdate(float DeltaTime)
{
	Charactor::CollsionAfterUpdate(DeltaTime);

	SAFE_RELEASE(Target);
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
}

void Monster::DirCheck()
{
	if (Target->GetPos().x - m_Pos.x < 0)
	{
		MoveDir = -1.0f;
		Dir = "L";
	}
	else if (Target->GetPos().x - m_Pos.x >= 0)
	{
		MoveDir = 1;
		Dir = "R";
	}
}

void Monster::BaseAttackHitFirst(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "BaseBody")
	{
		BaseAttackBullet* GetBullet = (BaseAttackBullet*)Dest->GetCurObject();
		Hp -= GetBullet->GetAttack();

		Number* DamegaNumber = Object::CreateObject<Number>("DamegaNumber", m_Layer);
		DamegaNumber->SetPos(m_Pos.x, m_Pos.y - m_Size.GetHalfY());
		DamegaNumber->SetTexture("DamegaNumber", TEXT("object/TempNumber.bmp"));
		DamegaNumber->SetNumberSize(19.0f, 24.0f);
		DamegaNumber->SetNumber(GetBullet->GetAttack());
		DamegaNumber->SetNumberViewSize(10.0f, 13.0f);
		DamegaNumber->SetMaxRange(50.0f, 100.0f);
		DamegaNumber->SetIsCameraMode(true);

		SAFE_RELEASE(DamegaNumber);
		SAFE_RELEASE(GetBullet);
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
	if (Dest->GetTag() == "LaserBody")
	{
		LaserBullet* GetBullet = (LaserBullet*)Dest->GetCurObject();
		Hp -= GetBullet->GetAttack();

		Number* DamegaNumber = Object::CreateObject<Number>("DamegaNumber", m_Layer);
		DamegaNumber->SetPos(m_Pos.x, m_Pos.y - m_Size.GetHalfY());
		DamegaNumber->SetTexture("DamegaNumber", TEXT("object/TempNumber.bmp"));
		DamegaNumber->SetNumberSize(19.0f, 24.0f);
		DamegaNumber->SetNumber(GetBullet->GetAttack());
		DamegaNumber->SetNumberViewSize(10.0f, 13.0f);
		DamegaNumber->SetMaxRange(50.0f, 100.0f);
		DamegaNumber->SetIsCameraMode(true);

		SAFE_RELEASE(DamegaNumber);
		SAFE_RELEASE(GetBullet);
	}
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
