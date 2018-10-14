#include "JellyFishHitBox.h"

#include "../Coll/ColliderRect.h"
#include "../Object/Tile.h"
#include "../StageManager.h"

JellyFishHitBox::JellyFishHitBox()
{
	m_ObjectType = OT_BULLET;
}

JellyFishHitBox::JellyFishHitBox(const JellyFishHitBox & Value)
	:Object(Value)
{
	Attack = Value.Attack;
}

JellyFishHitBox::~JellyFishHitBox()
{
}

bool JellyFishHitBox::Init()
{
	ColliderRect* RC = AddCollider<ColliderRect>("JellyFishHit");
	RC->SetVirtualRect(80.0f, 80.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Monster");

	SAFE_RELEASE(RC);

	return true;
}

int JellyFishHitBox::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int JellyFishHitBox::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int JellyFishHitBox::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void JellyFishHitBox::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void JellyFishHitBox::CollsionAfterUpdate(float DeltaTime)
{
	Object::CollsionAfterUpdate(DeltaTime);
}

void JellyFishHitBox::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);

	SetisActiv(false);
}

JellyFishHitBox * JellyFishHitBox::Clone()
{
	return new JellyFishHitBox(*this);
}
