#include "TelePoter.h"
#include "../Coll/ColliderRect.h"

TelePoter::TelePoter()
{
	m_ObjectType = OT_TELEPOT;
	SetTag("TelePoter");
}

TelePoter::TelePoter(const TelePoter & Value)
	:Object(Value)
{
}

TelePoter::~TelePoter()
{
}

bool TelePoter::Init()
{
	SetSize(144.0f, 75.0f);
	SetPivot(0.5f, 0.5f);

	SetTexture("TelePoterObject", TEXT("object/TelePoter1.bmp"));
	SetColorKey(RGB(255, 0, 255));

	//中宜端持失
	ColliderRect* RC = AddCollider<ColliderRect>("TelePoterBody");
	RC->SetVirtualRect(144.0f, 75.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("TelePoter");

	SAFE_RELEASE(RC);

	return true;
}

int TelePoter::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int TelePoter::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int TelePoter::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void TelePoter::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void TelePoter::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

TelePoter * TelePoter::Clone()
{
	return new TelePoter(*this);
}


