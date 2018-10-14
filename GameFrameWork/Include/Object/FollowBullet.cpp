#include "FollowBullet.h"
#include "../Coll/ColliderRect.h"

FollowBullet::FollowBullet()
	:Target(NULL)
{
	m_ObjectType = OT_BULLET;
	SetTag("FollowBullet");
}

FollowBullet::FollowBullet(const FollowBullet & Value)
	:Object(Value)
{
	DeleteDistance = Value.DeleteDistance;
	LeftTop = Value.LeftTop;
	Target = NULL;
	TimeVar = 0.0f;
}

FollowBullet::~FollowBullet()
{
	SAFE_RELEASE(Target);
}

bool FollowBullet::Init()
{
	SetSize(50.0f, 50.0f);
	SetPivot(0.5f, 0.5f);
	SetDeleteDistance(2000.0f);
	SetMoveSpeed(500.0f);

	SetTexture("Bullet", TEXT("Pistol.bmp"));
	SetColorKey(RGB(0, 248, 0));

	ColliderRect* RC = AddCollider<ColliderRect>("FollowBulletBody");
	RC->SetVirtualRect(50.0f, 50.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Bullet");

	TimeVar = 0.0f;

	SAFE_RELEASE(RC);

	return true;
}

int FollowBullet::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int FollowBullet::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	DeleteDistance -= MoveSpeed * DeltaTime;

	if (Target != NULL)
	{
		MoveByAngle(DeltaTime);
		m_Angle = Math::GetDegree(m_Pos, Target->GetPos());
	}
	
	if (Target == NULL)
		SetisActiv(false);
	if (DeleteDistance <= 0.0f)
		SetisActiv(false);

	return 0;
}

int FollowBullet::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void FollowBullet::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void FollowBullet::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

FollowBullet * FollowBullet::Clone()
{
	return new FollowBullet(*this);
}
