#include "ItemBox.h"
#include "Number.h"
#include "../Coll/ColliderRect.h"
#include "Object.h"

ItemBox::ItemBox()
{
	m_ObjectType = OT_ITEM;
	SetTag("ItemBoxObject");
}

ItemBox::ItemBox(const ItemBox & Value)
	:Object(Value)
{
}

ItemBox::~ItemBox()
{
}

bool ItemBox::Init()
{
	SetSize(50.0f, 50.0f);
	SetPivot(0.5f, 0.5f);

	int RendPer = rand() % 4;

	switch (RendPer)
	{
		case 0:
			Price = 100;
			break;
		case 1:
			Price = 150;
			break;
		case 2:
			Price = 200;
			break;
		case 3:
			Price = 250;
			break;
		default:
			Price = 0;
			break;
	}
	//아이템수졍..

	//PriceNumber = Object::CreateObject<Number>("PriceObject", m_Layer);
	//SetTexture("ItemBoxObject", TEXT("Pistol.bmp"));
	SetColorKey(RGB(255, 0, 255));

	//충돌체생성
	ColliderRect* RC = AddCollider<ColliderRect>("ItemBoxBody");
	RC->SetVirtualRect(50.0f, 50.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("ItemBoxObject");

	SAFE_RELEASE(RC);

	return true;
}

int ItemBox::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int ItemBox::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int ItemBox::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void ItemBox::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void ItemBox::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

ItemBox * ItemBox::Clone()
{
	return new ItemBox(*this);
}
