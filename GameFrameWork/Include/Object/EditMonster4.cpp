#include "EditMonster4.h"
#include "../Coll/ColliderRect.h"

EditMonster4::EditMonster4()
{
	m_ObjectType = OT_EDITOBJECT;
	SetTag("EditMonster4");
}

EditMonster4::EditMonster4(const EditMonster4 & Value)
	:EditMonster(Value)
{
}

EditMonster4::~EditMonster4()
{
}

bool EditMonster4::Init()
{
	EditMonster::Init();
	SetSize(45.0f, 45.0f);
	RC->SetVirtualRect(m_Size);

	SetTexture("EditMonster4", TEXT("EditMonster/Lemurian_One.bmp"));

	return true;
}

int EditMonster4::Input(float DeltaTime)
{
	EditMonster::Input(DeltaTime);

	return 0;
}

int EditMonster4::Update(float DeltaTime)
{
	EditMonster::Update(DeltaTime);

	return 0;
}

int EditMonster4::LateUpdate(float DeltaTime)
{
	EditMonster::LateUpdate(DeltaTime);

	return 0;
}

void EditMonster4::Collision(float DeltaTime)
{
	EditMonster::Collision(DeltaTime);
}

void EditMonster4::Render(HDC Hdc, float DeltaTime)
{
	EditMonster::Render(Hdc, DeltaTime);
}

EditMonster4 * EditMonster4::Clone()
{
	return new EditMonster4(*this);
}
