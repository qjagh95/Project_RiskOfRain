#include "Pump.h"
#include "Object.h"

#include "../Camera.h"

#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Animation.h"

#include "../Coll/ColliderRect.h"

#include "../Scene/Layer.h"

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
	AddAnimationClip("Pumping", AT_ATLAS, AO_LOOP, 54.0f, 174.0f, 6, 1, 6, 1, 0, 0, 0.3f, "Pumping" ,TEXT("object/Pump.bmp"));

	SetSize(54.0f, 174.0f);
	SetPivot(0.5f, 0.5f);
	SetColorKey(RGB(255, 0, 255));

	//中宜端持失
	ColliderRect* RC = AddCollider<ColliderRect>("PumpBody");
	RC->SetVirtualRect(m_Size);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCallBack(this, &Pump::PlayerColl, CS_COLFIRST);
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

void Pump::PlayerColl(Collider * Src, Collider* Dest, float DeltaTime)
{
}

