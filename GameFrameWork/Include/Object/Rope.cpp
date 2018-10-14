#include "Rope.h"
#include "../Coll/ColliderRect.h"

Rope::Rope()
{
	m_ObjectType = OT_ROPE;
	SetTag("RopeObject");
}

Rope::Rope(const Rope & Value)
	:Object(Value)
{
}

Rope::~Rope()
{
}

bool Rope::Init()
{
	SetSize(50.0f, 50.0f);
	SetPivot(0.5f, 0.5f);
	SetMoveSpeed(200.0f);

	//SetTexture("RopeObject", TEXT("Pistol.bmp"));
	SetColorKey(RGB(255, 0, 255));

	//中宜端持失
	ColliderRect* RC = AddCollider<ColliderRect>("RopeBody");
	RC->SetVirtualRect(50.0f, 50.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Rope");

	SAFE_RELEASE(RC);

	return true;
}

int Rope::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int Rope::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int Rope::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void Rope::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void Rope::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

Rope * Rope::Clone()
{
	return new Rope(*this);
}

