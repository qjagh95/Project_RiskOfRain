#include "ItemBox.h"
#include "Number.h"
#include "Object.h"
#include "DollerTexture.h"

#include "../Camera.h"

#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Animation.h"

#include "../Coll/ColliderRect.h"

#include "../Scene/Layer.h"

ItemBox::ItemBox()
	:PriceNumber(NULL), newDoller(NULL)
{
	m_ObjectType = OT_ITEM;
	SetTag("ItemBoxObject");
}

ItemBox::ItemBox(const ItemBox & Value)
	:Object(Value)
{
	Price = Value.Price;
	PriceNumber = Value.PriceNumber;
}

ItemBox::~ItemBox()
{
	SAFE_RELEASE(PriceNumber);
	SAFE_RELEASE(newDoller);
	SAFE_RELEASE(RC);
}

bool ItemBox::Init()
{
	isEnd = false;

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
			Price = 1;
			break;
	}

	SetSize(132.0f, 72.0f);
	SetPivot(0.5f, 0.5f);

	newDoller = Object::CreateObject<DollerTexture>("YellodwDoller", m_Layer);

	AddAnimationClip("ItemBox", AT_ATLAS, AO_LOOP, 132.0f, 72.0f, 1, 1, 1, 1, 0, 0, 1.0f, "Box", TEXT("object/ItemBox.bmp"));
	AddAnimationClip("ItemBoxOpen", AT_ATLAS, AO_ONCE_DESTROY, 132.0f, 72.0f, 6, 1, 6, 1, 1, 0, 1.0f, "BoxOpen", TEXT("object/ItemBox.bmp"));
	SetColorKey(RGB(255, 0, 255));

	RC = AddCollider<ColliderRect>("ItemBoxBody");
	RC->SetVirtualRect(Vector2(60.0f, 60.0f));
	RC->SetPivot(0.5f, 0.2f);
	RC->SetCollsionTypeName("ItemBoxObject");

	PriceNumber = Object::CreateObject<Number>("PriceNumber", m_Layer);
	PriceNumber->SetTexture("PriceNumber", TEXT("object/YellowNumber.bmp"));
	PriceNumber->SetNumber(Price);
	PriceNumber->SetNumberSize(32.0f, 24.0f);
	PriceNumber->SetColorKey(RGB(255, 0, 255));
	PriceNumber->SetIsCameraMode(true);
	PriceNumber->SetNumberViewSize(Vector2(32.0f, 24.0f));
	PriceNumber->SetZeroTextureSize(Vector2(32.0f, 24.0f));

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

	newDoller->SetPos(Vector2(m_Pos.x - m_Size.GetHalfX() + 10.0f, m_Pos.y + m_Size.y - 10.0f));

	switch (PriceNumber->GetNumberCount())
	{
		case 1:
			PriceNumber->SetPos(Vector2(m_Pos.x + m_Size.GetHalfX() - 45.0f, m_Pos.y + m_Size.y - 20.0f));
			break;
		case 2:
			PriceNumber->SetPos(Vector2(m_Pos.x + m_Size.GetHalfX() - 30.0f, m_Pos.y + m_Size.y - 20.0f));
			break;
		case 3:
			PriceNumber->SetPos(Vector2(m_Pos.x + m_Size.GetHalfX() - 5.0f, m_Pos.y + m_Size.y - 20.0f));
			break;
		default:
			break;
	}

	if (m_Animation->GetClipName() == "ItemBoxOpen")
	{
		isEnd = true;

		if (m_Animation->GetIsEnd())
		{
			SetisActiv(false);
			newDoller->SetisActiv(false);
			PriceNumber->SetisActiv(false);
		}
	}

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
