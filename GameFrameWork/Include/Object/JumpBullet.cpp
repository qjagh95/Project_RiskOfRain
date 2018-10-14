#include "JumpBullet.h"
#include "../Coll/ColliderRect.h"
#include "../Camera.h"

JumpBullet::JumpBullet()
{
	m_ObjectType = OT_BULLET;
	SetTag("JumpBullet");
}

JumpBullet::JumpBullet(const JumpBullet & Value)
	:Object(Value)
{
	DeleteDistance = Value.DeleteDistance;
	Gravity = Value.Gravity;
	Power = Value.Power;
	isFire = Value.isFire;
}

JumpBullet::~JumpBullet()
{
}

bool JumpBullet::Init()
{
	SetSize(50.0f, 50.0f);
	SetPivot(0.5f, 0.5f);
	SetDeleteDistance(2000.0f);
	SetMoveSpeed(200.0f);
	isFire = false;
	Gravity = 500.0f;
	Power = 100.0f;

	SetTexture("Bullet", TEXT("Pistol.bmp"));
	SetColorKey(RGB(0, 248, 0));

	ColliderRect* RC = AddCollider<ColliderRect>("JumpBulletBody");
	RC->SetVirtualRect(50.0f, 50.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Bullet");

	SAFE_RELEASE(RC);

	return true;
}

int JumpBullet::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int JumpBullet::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	if (isFire == false)
		return 0;

	Gravity += 300.0f * DeltaTime;

	m_Pos.y -= Power * DeltaTime;
	Power -= Gravity * DeltaTime;

	m_Pos.x += MoveSpeed * DeltaTime;

	if (m_Pos.y >= 1000.0f)
		SetisActiv(false);

	return 0;
}

int JumpBullet::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void JumpBullet::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void JumpBullet::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

JumpBullet * JumpBullet::Clone()
{
	return new JumpBullet(*this);
}
