#include "LaserEffect.h"

LaserEffect::LaserEffect()
{
	m_ObjectType = OT_EFFECT;
	SetTag("LaserEffect");
}

LaserEffect::LaserEffect(const LaserEffect & Value)
	:Object(Value)
{
}

LaserEffect::~LaserEffect()
{
}

bool LaserEffect::Init()
{
	SetColorKey(RGB(255, 0, 255));

	return true;
}

int LaserEffect::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int LaserEffect::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	MoveByAngle(DeltaTime);

	return 0;
}

int LaserEffect::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void LaserEffect::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void LaserEffect::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

LaserEffect * LaserEffect::Clone()
{
	return new LaserEffect(*this);
}
