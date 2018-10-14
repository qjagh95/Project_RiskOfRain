#include "SubBullet.h"
#include "../Coll/ColliderRect.h"

SubBullet::SubBullet()
{
	m_ObjectType = OT_BULLET;
	SetTag("SubBullet");
}

SubBullet::SubBullet(const SubBullet & Value)
	:Object(Value)
{
	DeletDistance = Value.DeletDistance;
}

SubBullet::~SubBullet()
{
}

bool SubBullet::Init()
{
	SetSize(50.0f, 50.0f);
	SetPivot(0.5f, 0.5f);
	SetMoveSpeed(500.0f);

	DeletDistance = 500.0f;

	SetTexture("Bullet", TEXT("Pistol.bmp"));
	SetColorKey(RGB(0, 248, 0));

	//中宜端持失
	ColliderRect* RC = AddCollider<ColliderRect>("SubBulletBody");
	RC->SetVirtualRect(50.0f, 50.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("SubBullet");

	SAFE_RELEASE(RC);

	return true;
}

int SubBullet::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int SubBullet::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	DeletDistance -= MoveSpeed * DeltaTime;
	MoveByAngle(DeltaTime);

	if (DeletDistance <= 0.0f)
		SetisActiv(false);

	return 0;
}

int SubBullet::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void SubBullet::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void SubBullet::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc,DeltaTime);
}

SubBullet * SubBullet::Clone()
{
	return new SubBullet(*this);
}

