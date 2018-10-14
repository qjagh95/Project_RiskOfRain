#include "EditMonster5.h"
#include "../Coll/ColliderRect.h"

EditMonster5::EditMonster5()
{
	m_ObjectType = OT_EDITOBJECT;
	SetTag("EditMonster5");
}

EditMonster5::EditMonster5(const EditMonster5 & Value)
	:EditMonster(Value)
{
}

EditMonster5::~EditMonster5()
{
}

bool EditMonster5::Init()
{
	EditMonster::Init();
	SetSize(27.0f, 50.0f);
	RC->SetVirtualRect(m_Size);

	SetTexture("EditMonster5", TEXT("EditMonster/Wisp_Right_Stun.bmp"));

	return true;
}

int EditMonster5::Input(float DeltaTime)
{
	EditMonster::Input(DeltaTime);

	return 0;
}

int EditMonster5::Update(float DeltaTime)
{
	EditMonster::Update(DeltaTime);

	return 0;
}

int EditMonster5::LateUpdate(float DeltaTime)
{
	EditMonster::LateUpdate(DeltaTime);

	return 0;
}

void EditMonster5::Collision(float DeltaTime)
{
	EditMonster::Collision(DeltaTime);
}

void EditMonster5::Render(HDC Hdc, float DeltaTime)
{
	EditMonster::Render(Hdc, DeltaTime);
}

EditMonster5 * EditMonster5::Clone()
{
	return new EditMonster5(*this);
}

