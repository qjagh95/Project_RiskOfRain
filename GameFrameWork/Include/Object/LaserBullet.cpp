#include "LaserBullet.h"
#include "../Coll/ColliderRect.h"

LaserBullet::LaserBullet()
{
	m_ObjectType = OT_BULLET;
	SetTag("LaserBullet");
}

LaserBullet::LaserBullet(const LaserBullet & Value)
	:Object(Value)
{
}

LaserBullet::~LaserBullet()
{
}

bool LaserBullet::Init()
{
	SetColorKey(RGB(255, 0, 255));

	return true;
}

int LaserBullet::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int LaserBullet::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	MoveByAngle(DeltaTime);

	return 0;
}

int LaserBullet::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void LaserBullet::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void LaserBullet::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

LaserBullet * LaserBullet::Clone()
{
	return new LaserBullet(*this);
}
