#include "TargetBullet.h"
#include "../Coll/ColliderRect.h"

TargetBullet::TargetBullet()
	:Target(NULL)
{
	m_ObjectType = OT_BULLET;
	SetTag("TargetBullet");
}

TargetBullet::TargetBullet(const TargetBullet & Value)
	:Object(Value)
{
	LeftTop = Value.LeftTop;
	DeleteDistance = Value.DeleteDistance;
	Distance = Value.Distance;
	Target = NULL;
	isRush = false;
}

TargetBullet::~TargetBullet()
{
	SAFE_RELEASE(Target);
}

bool TargetBullet::Init()
{
	SetSize(50.0f, 50.0f);
	SetPivot(0.5f, 0.5f);
	SetDeleteDistance(2000.0f);
	SetMoveSpeed(500.0f);
	Distance = 500.0f;

	SetTexture("Bullet", TEXT("Pistol.bmp"));
	SetColorKey(RGB(0, 248, 0));

	ColliderRect* RC = AddCollider<ColliderRect>("TargetBulletBody");
	RC->SetVirtualRect(50.0f, 50.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Bullet");

	SAFE_RELEASE(RC);

	return true;
}

int TargetBullet::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int TargetBullet::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	MoveByAngle(DeltaTime);
	DeleteDistance -= MoveSpeed * DeltaTime;
	Distance -= MoveSpeed * DeltaTime;

	if (Distance <= 0.0f)
	{
		isRush = true;
		m_Angle = Math::GetDegree(m_Pos, Target->GetPos());
	}

	if (DeleteDistance <= 0.0f)
		SetisActiv(false);

	return 0;
}

int TargetBullet::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void TargetBullet::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);

}

void TargetBullet::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc,DeltaTime);
}

TargetBullet * TargetBullet::Clone()
{
	return new TargetBullet(*this);
}
