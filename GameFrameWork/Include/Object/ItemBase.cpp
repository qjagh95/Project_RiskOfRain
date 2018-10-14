#include "ItemBase.h"
#include "../Coll/ColliderRect.h"
#include "../Scene/Layer.h"
#include "../Object/Commando.h"

ItemBase::ItemBase()
	:ItemCount(1), isNumberShow(false), Target(NULL)
{
	m_ObjectType = OT_ITEM;
	SetTag("Item");
	ItemKind = ITEM_NONE;
}

ItemBase::ItemBase(const ItemBase & Value)
	:Object(Value)
{
}

ItemBase::~ItemBase()
{
	SAFE_RELEASE(RC);
	SAFE_RELEASE(Target);
}

bool ItemBase::Init()
{
	SetIsCameraMode(true);
	isStop = false;

	isUp = false;

	SetMoveSpeed(50.0f);
	SetPivot(0.5f, 0.5f);
	SetSize(99.0f, 99.0f);
	SetColorKey(RGB(255, 0, 255));

	//포지션값 나중셋팅.
	RC = AddCollider<ColliderRect>("ItemBody");
	RC->SetVirtualRect(99.0f, 99.0f);
	RC->SetPivot(0.5f, 0.5f);

	//숫자는 나중에 Coll함수에서
	//CountNumber = Object::CreateObject<Number>("ItemCountNumber", m_Layer);
	//CountNumber->SetPos(m_Pos.x, m_Pos.y);
	//CountNumber->SetTexture("ItemCountNumber", TEXT("object/TempNumber.bmp"));
	//CountNumber->SetNumberSize(19.0f, 24.0f);
	//CountNumber->SetColorKey(RGB(255, 0, 255));
	//CountNumber->SetIsCameraMode(false);
	//CountNumber->SetNumberViewSize(Vector2(19.0f, 24.0f));

	return true;
}

int ItemBase::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int ItemBase::Update(float DeltaTime)
{
	SAFE_RELEASE(Target);

	Object::Update(DeltaTime);

	Target = FindSceneObject("Commando");

	if (isStop == false)
	{
		if (m_Pos.y < TempPos.y - 10.0f)
			isUp = false;
		else if(m_Pos.y > TempPos.y + 10.0f)
			isUp = true;

		if (isUp == false)
			m_Pos.y += MoveSpeed * DeltaTime;
		else
			m_Pos.y -= MoveSpeed * DeltaTime;
	}

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
