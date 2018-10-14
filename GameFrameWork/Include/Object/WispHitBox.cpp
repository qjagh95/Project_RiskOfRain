#include "WispHitBox.h"
#include "../Coll/ColliderRect.h"
#include "../Object/Tile.h"
#include "../StageManager.h"

WispHitBox::WispHitBox()
{
	m_ObjectType = OT_BULLET;
}

WispHitBox::WispHitBox(const WispHitBox & Value)
	:Object(Value)
{
	Attack = Value.Attack;
}

WispHitBox::~WispHitBox()
{
}

bool WispHitBox::Init()
{
	ColliderRect* RC = AddCollider<ColliderRect>("WispHit");
	RC->SetPivot(0.0f, 0.5f);
	RC->SetVirtualRect(275.0f, 60.0f);
	RC->SetCollsionTypeName("Monster");

	SAFE_RELEASE(RC);

	return true;
}

int WispHitBox::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int WispHitBox::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int WispHitBox::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void WispHitBox::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void WispHitBox::CollsionAfterUpdate(float DeltaTime)
{
	Object::CollsionAfterUpdate(DeltaTime);
}

void WispHitBox::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);

	SetisActiv(false);
}

WispHitBox * WispHitBox::Clone()
{
	return new WispHitBox(*this);
}
