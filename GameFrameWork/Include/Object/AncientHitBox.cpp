#include "AncientHitBox.h"
#include "../Coll/ColliderRect.h"
#include "../Object/Tile.h"
#include "../StageManager.h"

AncientHitBox::AncientHitBox()
{
	m_ObjectType = OT_BULLET;
}

AncientHitBox::AncientHitBox(const AncientHitBox & Value)
	:Object(Value)
{

	Attack = Value.Attack;
}

AncientHitBox::~AncientHitBox()
{
}

bool AncientHitBox::Init()
{
	ColliderRect* RC = AddCollider<ColliderRect>("AcientHitBody");
	RC->SetVirtualRect(m_Size);
	RC->SetPivot(0.5f, 1.0f);
	RC->SetCollsionTypeName("Monster");

	SAFE_RELEASE(RC);

	return true;
}

int AncientHitBox::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int AncientHitBox::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	ColliderRect* getCol = (ColliderRect*)GetCollider("AcientHitBody");
	getCol->SetVirtualRect(m_Size);

	SAFE_RELEASE(getCol);

	return 0;
}

int AncientHitBox::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void AncientHitBox::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void AncientHitBox::CollsionAfterUpdate(float DeltaTime)
{
	Object::CollsionAfterUpdate(DeltaTime);
}

void AncientHitBox::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
	SetisActiv(false);
}

AncientHitBox * AncientHitBox::Clone()
{
	return new AncientHitBox(*this);
}
