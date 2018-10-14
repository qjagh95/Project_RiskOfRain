#include "RotBullet.h"
#include "../Coll/ColliderRect.h"

RotBullet::RotBullet()
{
	m_ObjectType = OT_BULLET;
	SetTag("RotBullet");
}

RotBullet::RotBullet(const RotBullet & Value)
	:Object(Value)
{
	LeftTop = Value.LeftTop;
	CenterPos = Value.CenterPos;
	RotAngle = Value.RotAngle;
	RotRange = Value.RotRange;
	DeleteDistance = Value.DeleteDistance;
}

RotBullet::~RotBullet()
{
}

bool RotBullet::Init()
{
	SetSize(50.0f, 50.0f);
	SetPivot(0.5f, 0.5f);
	SetDeleteDistance(2000.0f);
	SetMoveSpeed(500.0f);
	RotAngle = 0.0f;
	RotRange = 80.0f;

	SetTexture("Bullet", TEXT("Pistol.bmp"));
	SetColorKey(RGB(0, 248, 0));

	ColliderRect* RC = AddCollider<ColliderRect>("RotBulletBody");
	RC->SetVirtualRect(50.0f, 50.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Bullet");

	SAFE_RELEASE(RC);

	return true;
}

int RotBullet::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int RotBullet::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	DeleteDistance -= MoveSpeed * DeltaTime;
	//여긴 발사가 되는 방향을 정해준다
	CenterPos.x += cosf(Math::DgreeToRadian(m_Angle)) * MoveSpeed * DeltaTime;
	CenterPos.y += sinf(Math::DgreeToRadian(m_Angle)) * MoveSpeed * DeltaTime;

	RotAngle += 720.0f * DeltaTime;

	//여긴 계속 돌아라 돌아라~
	m_Pos.x = CenterPos.x + cosf(Math::DgreeToRadian(RotAngle)) * RotRange;
	m_Pos.y = CenterPos.y + sinf(Math::DgreeToRadian(RotAngle)) * RotRange;

	if (DeleteDistance <= 0.0f)
		SetisActiv(false);

	return 0;
}

int RotBullet::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void RotBullet::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void RotBullet::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc,DeltaTime);
}

RotBullet * RotBullet::Clone()
{
	return new RotBullet(*this);
}
