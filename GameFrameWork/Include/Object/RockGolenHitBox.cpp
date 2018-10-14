#include "RockGolenHitBox.h"
#include "../Coll/ColliderRect.h"
#include "../Object/Tile.h"
#include "../StageManager.h"

RockGolenHitBox::RockGolenHitBox()
{
	m_ObjectType = OT_BULLET;
}

RockGolenHitBox::RockGolenHitBox(const RockGolenHitBox & Value)
	:Object(Value)
{
	Attack = Value.Attack;
}

RockGolenHitBox::~RockGolenHitBox()
{
}

bool RockGolenHitBox::Init()
{
	ColliderRect* RC = AddCollider<ColliderRect>("RockHit");
	RC->SetPivot(0.5f, 0.5f);
	RC->SetVirtualRect(150.0f, 60.0f);
	RC->SetCollsionTypeName("Monster");

	SAFE_RELEASE(RC);

	return true;
}

int RockGolenHitBox::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int RockGolenHitBox::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int RockGolenHitBox::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void RockGolenHitBox::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void RockGolenHitBox::CollsionAfterUpdate(float DeltaTime)
{
	Object::CollsionAfterUpdate(DeltaTime);
}

void RockGolenHitBox::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);

	SetisActiv(false);
}

RockGolenHitBox * RockGolenHitBox::Clone()
{
	return new RockGolenHitBox(*this);
}

