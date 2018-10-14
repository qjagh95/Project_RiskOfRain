#include "ColossusKickHitBox.h"
#include "../Coll/ColliderRect.h"
#include "../Object/Tile.h"
#include "../StageManager.h"

ColossusKickHitBox::ColossusKickHitBox()
{
	m_ObjectType = OT_BULLET;
}

ColossusKickHitBox::ColossusKickHitBox(const ColossusKickHitBox & Value)
	:Object(Value)
{

	Attack = Value.Attack;
}

ColossusKickHitBox::~ColossusKickHitBox()
{
}

bool ColossusKickHitBox::Init()
{
	ColliderRect* RC = AddCollider<ColliderRect>("ColossusKickHitBox");
	RC->SetVirtualRect(50.0f, 50.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Monster");

	SAFE_RELEASE(RC);

	return true;
}

int ColossusKickHitBox::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int ColossusKickHitBox::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int ColossusKickHitBox::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void ColossusKickHitBox::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void ColossusKickHitBox::CollsionAfterUpdate(float DeltaTime)
{
	Object::CollsionAfterUpdate(DeltaTime);
}

void ColossusKickHitBox::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
	SetisActiv(false);
}

ColossusKickHitBox * ColossusKickHitBox::Clone()
{
	return new ColossusKickHitBox(*this);
}
