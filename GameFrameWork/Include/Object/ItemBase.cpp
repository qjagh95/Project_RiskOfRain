#include "ItemBase.h"

ItemBase::ItemBase()
{
	m_ObjectType = OT_ITEM;
	SetTag("Item");
}

ItemBase::ItemBase(const ItemBase & Value)
	:Object(Value)
{
}

ItemBase::~ItemBase()
{
}

bool ItemBase::Init()
{
	return true;
}

int ItemBase::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int ItemBase::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int ItemBase::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void ItemBase::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void ItemBase::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

ItemBase * ItemBase::Clone()
{
	return new ItemBase(*this);
}
