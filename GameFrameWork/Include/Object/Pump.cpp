#include "Pump.h"
#include "../Coll/ColliderRect.h"

Pump::Pump()
{
	m_ObjectType = OT_PUMP;
	SetTag("PumpObject");
}

Pump::Pump(const Pump & Value)
	:Object(Value)
{
}

Pump::~Pump()
{
}

bool Pump::Init()
{
	SetSize(50.0f, 50.0f);
	SetPivot(0.5f, 0.5f);
	SetMoveSpeed(200.0f);

	//SetTexture("PumpObject", TEXT("Pistol.bmp"));
	SetColorKey(RGB(255, 0, 255));

	//中宜端持失
	ColliderRect* RC = AddCollider<ColliderRect>("PumpBody");
	RC->SetVirtualRect(50.0f, 50.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Pump");

	SAFE_RELEASE(RC);

	return true;
}

int Pump::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int Pump::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int Pump::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void Pump::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void Pump::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

Pump * Pump::Clone()
{
	return new Pump(*this);
}

