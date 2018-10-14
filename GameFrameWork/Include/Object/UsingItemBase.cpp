#include "UsingItemBase.h"
#include "../Coll/ColliderRect.h"
#include "../Object/Hider.h"

UsingItemBase::UsingItemBase()
{
	m_ObjectType = OT_ITEM;
	SetTag("Item");
}

UsingItemBase::UsingItemBase(const UsingItemBase & Value)
	:Object(Value)
{
}

UsingItemBase::~UsingItemBase()
{
}

bool UsingItemBase::Init()
{
	return true;
}

int UsingItemBase::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int UsingItemBase::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int UsingItemBase::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void UsingItemBase::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void UsingItemBase::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

UsingItemBase * UsingItemBase::Clone()
{
	return new UsingItemBase(*this);
}