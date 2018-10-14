#include "ColossusClapHitBox.h"
#include "../Coll/ColliderRect.h"
#include "../Object/Tile.h"
#include "../StageManager.h"

ColossusClapHitBox::ColossusClapHitBox()
{
	m_ObjectType = OT_BULLET;
}

ColossusClapHitBox::ColossusClapHitBox(const ColossusClapHitBox & Value)
	:Object(Value)
{

	Attack = Value.Attack;
}

ColossusClapHitBox::~ColossusClapHitBox()
{
}

bool ColossusClapHitBox::Init()
{
	ColliderRect* RC = AddCollider<ColliderRect>("ColossusClapHitBox");
	RC->SetVirtualRect(500.0f, 360.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Monster");

	SAFE_RELEASE(RC);

	return true;
}

int ColossusClapHitBox::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int ColossusClapHitBox::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int ColossusClapHitBox::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void ColossusClapHitBox::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void ColossusClapHitBox::CollsionAfterUpdate(float DeltaTime)
{
	Object::CollsionAfterUpdate(DeltaTime);
}

void ColossusClapHitBox::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
	SetisActiv(false);
}

ColossusClapHitBox * ColossusClapHitBox::Clone()
{
	return new ColossusClapHitBox(*this);
}
