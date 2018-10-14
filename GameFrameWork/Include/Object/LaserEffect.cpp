#include "LaserEffect.h"
#include "../Object/LaserBullet.h"
#include "../Resource/Animation.h"

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
	SetSize(1919.0f, 192.0f);
	SetPivot(0.5f, 0.5f);

	AddAnimationClip("Laser", AT_ATLAS, AO_LOOP, 1919.0f, 192.0f, 5, 1, 5, 1, 0, 0, 0.3f, "Laser", TEXT("Effect/Laser Turbine Effect.bmp"));
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

	if (m_Animation->GetIsEnd() == true)
		SetisActiv(false);

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
