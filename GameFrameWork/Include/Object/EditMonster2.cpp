#include "EditMonster2.h"
#include "../Coll/ColliderRect.h"

EditMonster2::EditMonster2()
{
	m_ObjectType = OT_EDITOBJECT;
	SetTag("EditMonster2");
}

EditMonster2::EditMonster2(const EditMonster2 & Value)
	:EditMonster(Value)
{
}

EditMonster2::~EditMonster2()
{
}

bool EditMonster2::Init()
{
	EditMonster::Init();
	SetSize(150.0f, 305.0f);
	RC->SetVirtualRect(m_Size);

	SetTexture("EditMonster2", TEXT("EditMonster/AncientWisp_One.bmp"));

	return true;
}

int EditMonster2::Input(float DeltaTime)
{
	EditMonster::Input(DeltaTime);

	return 0;
}

int EditMonster2::Update(float DeltaTime)
{
	EditMonster::Update(DeltaTime);

	return 0;
}

int EditMonster2::LateUpdate(float DeltaTime)
{
	EditMonster::LateUpdate(DeltaTime);

	return 0;
}

void EditMonster2::Collision(float DeltaTime)
{
	EditMonster::Collision(DeltaTime);
}

void EditMonster2::Render(HDC Hdc, float DeltaTime)
{
	EditMonster::Render(Hdc, DeltaTime);
}

EditMonster2 * EditMonster2::Clone()
{
	return new EditMonster2(*this);
}

