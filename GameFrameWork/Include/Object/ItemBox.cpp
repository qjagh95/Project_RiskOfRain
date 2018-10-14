#include "ItemBox.h"
#include "Number.h"
#include "Object.h"
#include "../Coll/ColliderRect.h"
#include "../Resource/Texture.h"
#include "../Scene/Layer.h"

ItemBox::ItemBox()
	:PriceNumber(NULL), DollerTexture(NULL)
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
	SAFE_RELEASE(PriceNumber);
	SAFE_RELEASE(DollerTexture);
}

bool ItemBox::Init()
{
	int RendPer = rand() % 5;
	switch (RendPer)
	{
		case 0:
			Price = 25;
			break;
		case 1:
			Price = 50;
			break;
		case 2:
			Price = 100;
			break;
		case 3:
			Price = 150;
			break;
		case 4:
			Price = 200;
			break;
		case 5:
			Price = 250;
			break;
		default:
			Price = 0;
			break;
	}

	SetSize(132.0f, 72.0f);
	SetPivot(0.5f, 0.5f);
	//PriceNumber = Object::CreateObject<Number>("PriceObject", m_Layer);

	AddAnimationClip("ItemBox", AT_ATLAS, AO_LOOP, 132.0f, 72.0f, 1, 1, 1, 1, 0, 0, 1.0f, "Box", TEXT("object/ItemBox.bmp"));
	AddAnimationClip("ItemBoxOpen", AT_ATLAS, AO_ONCE_DESTROY, 132.0f, 72.0f, 6, 1, 6, 1, 1, 0, 1.0f, "BoxOpen", TEXT("object/ItemBox.bmp"));
	SetColorKey(RGB(255, 0, 255));

	//충돌체생성
	ColliderRect* RC = AddCollider<ColliderRect>("ItemBoxBody");
	RC->SetVirtualRect(m_Size);
	RC->SetPivot(0.5f, 0.5f);
	//RC->SetCallBack(this, ItemBox::PlayerCollBack, CS_COLDOING);
	RC->SetCollsionTypeName("ItemBoxObject");

	SAFE_RELEASE(RC);

	PriceNumber = Object::CreateObject<Number>("Number", m_Layer);
	PriceNumber->SetPos(m_Pos);
	PriceNumber->SetTexture("PriceNumber", TEXT("Object/YellowNmber.bmp"));
	PriceNumber->SetNumber(Price);
	PriceNumber->SetNumberSize(32.0f, 24.0f);
	PriceNumber->SetColorKey(RGB(255, 0, 255));
	PriceNumber->SetIsCameraMode(true);

	ChangeClip("ItemBox");

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
	int a = 0;
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

void ItemBox::PlayerCollBack(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "PlayerBody")
	{
		//아이템추가코드, 체인지애니메이션
	}
}
