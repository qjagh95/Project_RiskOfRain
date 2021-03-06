#include "BaseAttackBullet.h"
#include "BaseEffect.h"
#include "../Coll/ColliderRect.h"
#include "../Object/Tile.h"
#include "../StageManager.h"
#include "../Resource/Animation.h"
#include "../Object/Monster.h"

#include "../Debug.h"

BaseAttackBullet::BaseAttackBullet()
	:Dir(0.0f), isStop(false), Attack(0), isHit(false), isTileCol(false)
{
	m_ObjectType = OT_BULLET;
	SetTag("BaseAttackBullet");
}

BaseAttackBullet::BaseAttackBullet(const BaseAttackBullet & Value)
	:Object(Value)
{
	Dir = 1.0f;
	isStop = false;
	Attack = Value.Attack;
	isHit = Value.isHit;
}

BaseAttackBullet::~BaseAttackBullet()
{
}

bool BaseAttackBullet::Init()
{
	SetSize(10.0f, 1.0f);
	SetPivot(0.5f, 0.5f);
	SetMoveSpeed(200.0f);

	SetColorKey(RGB(255, 0, 255));

	//충돌체생성
	ColliderRect* RC = AddCollider<ColliderRect>("BaseBody");
	RC->SetVirtualRect(10.0f, 1.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("BaseAttackBullet");
	SAFE_RELEASE(RC);

	return true;
}

int BaseAttackBullet::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int BaseAttackBullet::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	BaseEffect* newEffect = (BaseEffect*)Object::CreateCloneObject("BaseEffect", m_Layer);
	newEffect->SetPos(m_Pos);
	newEffect->SelectAnimationClip(Dir);
	SAFE_RELEASE(newEffect);

	return 0;
}

int BaseAttackBullet::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	char Buffer[255];
	sprintf_s(Buffer, "BulletPos : %f , %f\n", m_Pos.x ,m_Pos.y);
	Debug::OutputConsole(Buffer);

	return 0;
}

void BaseAttackBullet::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void BaseAttackBullet::CollsionAfterUpdate(float DeltaTime)
{
	Object::CollsionAfterUpdate(DeltaTime);

	SetisActiv(false);
}

void BaseAttackBullet::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

BaseAttackBullet * BaseAttackBullet::Clone()
{
	return new BaseAttackBullet(*this);
}

void BaseAttackBullet::SetAttack(int iAttack)
{
	//+20% ~ -20%
	Attack = (int)Math::RandomRange((int)(iAttack * 0.6f) , (int)(iAttack * 1.2f));
}