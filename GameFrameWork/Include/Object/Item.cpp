#include "../stdafx.h"
#include "Item.h"

Item::Item()
	:Target(NULL)
{
	m_ObjectType = OT_ITEM;
	SetTag("Item");
}

Item::Item(const Item & Value)
	:Object(Value)
{
	Target = NULL;
	isRush = Value.isRush;
}

Item::~Item()
{
}

bool Item::Init()
{
	SetTexture("Item", L"Item.bmp");
	SetSize(100.0f, 100.0f);
	SetPivot(0.5f, 0.5f);
	SetMoveSpeed(1000.0f);
	isRush = false;

	return true;
}

int Item::Input(float DeltaTime)
{
	return 0;
}

int Item::Update(float DeltaTime)
{
	if (isRush == true)
	{
		m_Angle = Math::GetDegree(m_Pos, Target->GetPos());
		MoveByAngle(DeltaTime);
	}

	if (m_Pos >= Target->GetPos())
		SetisActiv(false);

	//if (m_Pos.x + m_Size.GetHalfX() >= GET_INSTANCE(Core)->GetWinSize().Width || m_Pos.x - m_Size.GetHalfX() <= 0.0f)
	//{
	//	Count++;
	//	m_Angle = 180.0f - m_Angle;
	//}
	//if (m_Pos.y + m_Size.GetHalfY() >= GET_INSTANCE(Core)->GetWinSize().Height || m_Pos.y - m_Size.GetHalfY() <= 0.0f)
	//{
	//	Count++;
	//	m_Angle = 360.0f - m_Angle;
	//}

	//if (Count >= 5)
	//{
	//	Count = 0;
	//	SetisActiv(false);
	//}



	return 0;
}

int Item::LateUpdate(float DeltaTime)
{
	return 0;
}

void Item::Collision(float DeltaTime)
{
}

void Item::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

Item * Item::Clone()
{
	return new Item(*this);
}
