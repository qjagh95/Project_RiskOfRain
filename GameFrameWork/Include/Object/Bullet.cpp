#include "Bullet.h"
#include "../Coll/ColliderRect.h"
#include "../Coll/ColliderCircle.h"
#include "SubBullet.h"

Bullet::Bullet()
	:Target(NULL)
{
	m_ObjectType = OT_BULLET;
	SetTag("Bullet");
}

Bullet::Bullet(const Bullet & Value)
	:Object(Value)
{
	Target = NULL;
	DeleteDistance = Value.DeleteDistance;
}

Bullet::~Bullet()
{
	SAFE_RELEASE(Target);
}

bool Bullet::Init()
{
	SetSize(50.0f, 50.0f);
	SetPivot(0.5f, 0.5f);
	SetDeleteDistance(2000.0f);
	SetMoveSpeed(200.0f);

	SetTexture("Bullet", TEXT("Pistol.bmp"));
	SetColorKey(RGB(0, 248, 0));

	//충돌체생성
	ColliderRect* RC = AddCollider<ColliderRect>("BulletBody");
	RC->SetVirtualRect(50.0f, 50.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Bullet");

	//ColliderCircle* RC = AddCollider<ColliderCircle>("BulletBody");
	//RC->SetRadius(25.0f);

	SAFE_RELEASE(RC);

	return true;
}

int Bullet::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int Bullet::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	DeleteDistance -= MoveSpeed * DeltaTime;

	if (Target != NULL)
		m_Angle = Math::GetDegree(m_Pos, Target->GetPos());

	MoveByAngle(DeltaTime);

	//사라지거라...
	if (DeleteDistance <= 0.0f)
		SetisActiv(false);

	return 0;
}

int Bullet::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void Bullet::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void Bullet::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

Bullet * Bullet::Clone()
{
	return new Bullet(*this);
}
