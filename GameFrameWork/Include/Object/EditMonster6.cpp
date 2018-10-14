#include "EditMonster6.h"
#include "../Coll/ColliderRect.h"

EditMonster6::EditMonster6()
{
	m_ObjectType = OT_EDITOBJECT;
	SetTag("EditMonster6");
}

EditMonster6::EditMonster6(const EditMonster6 & Value)
	:EditMonster(Value)
{
}

EditMonster6::~EditMonster6()
{
}

bool EditMonster6::Init()
{
	EditMonster::Init();
	SetSize(60.0f, 90.0f);
	RC->SetVirtualRect(m_Size);

	SetTexture("EditMonster6", TEXT("EditMonster/RockGolem_Right_Hold.bmp"));

	return true;
}

int EditMonster6::Input(float DeltaTime)
{
	EditMonster::Input(DeltaTime);

	return 0;
}

int EditMonster6::Update(float DeltaTime)
{
	EditMonster::Update(DeltaTime);

	return 0;
}

int EditMonster6::LateUpdate(float DeltaTime)
{
	EditMonster::LateUpdate(DeltaTime);

	return 0;
}

void EditMonster6::Collision(float DeltaTime)
{
	EditMonster::Collision(DeltaTime);
}

void EditMonster6::Render(HDC Hdc, float DeltaTime)
{
	EditMonster::Render(Hdc, DeltaTime);
}

EditMonster6 * EditMonster6::Clone()
{
	return new EditMonster6(*this);
}

