#include "LemurinHitBox.h"
#include "../Coll/ColliderRect.h"
#include "../Object/Tile.h"
#include "../StageManager.h"

LemurinHitBox::LemurinHitBox()
{
	m_ObjectType = OT_BULLET;
}

LemurinHitBox::LemurinHitBox(const LemurinHitBox & Value)
	:Object(Value)
{
	Attack = Value.Attack;
}

LemurinHitBox::~LemurinHitBox()
{
}

bool LemurinHitBox::Init()
{
	ColliderRect* RC = AddCollider<ColliderRect>("LemurianHit");
	RC->SetPivot(0.5f, 0.5f);
	RC->SetVirtualRect(114.0f , 67.0f);
	RC->SetCollsionTypeName("Monster");

	SAFE_RELEASE(RC);

	return true;
}

int LemurinHitBox::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int LemurinHitBox::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int LemurinHitBox::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void LemurinHitBox::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void LemurinHitBox::CollsionAfterUpdate(float DeltaTime)
{
	Object::CollsionAfterUpdate(DeltaTime);
}

void LemurinHitBox::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);

	SetisActiv(false);
}

LemurinHitBox * LemurinHitBox::Clone()
{
	return new LemurinHitBox(*this);
}
