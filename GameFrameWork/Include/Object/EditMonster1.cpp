#include "EditMonster1.h"
#include "../Coll/ColliderRect.h"

EditMonster1::EditMonster1()
{
	m_ObjectType = OT_EDITOBJECT;
	SetTag("EditMonster1");
}

EditMonster1::EditMonster1(const EditMonster1 & Value)
	:EditMonster(Value)
{
}

EditMonster1::~EditMonster1()
{
}

bool EditMonster1::Init()
{
	EditMonster::Init();
	SetSize(78.0f, 76.0f);
	RC->SetVirtualRect(m_Size);

	SetTexture("EditMonster1", TEXT("EditMonster/IssacEnemy1_One.bmp"));

	return true;
}

int EditMonster1::Input(float DeltaTime)
{
	EditMonster::Input(DeltaTime);

	return 0;
}

int EditMonster1::Update(float DeltaTime)
{
	EditMonster::Update(DeltaTime);

	return 0;
}

int EditMonster1::LateUpdate(float DeltaTime)
{
	EditMonster::LateUpdate(DeltaTime);

	return 0;
}

void EditMonster1::Collision(float DeltaTime)
{
	EditMonster::Collision(DeltaTime);
}

void EditMonster1::Render(HDC Hdc, float DeltaTime)
{
	EditMonster::Render(Hdc, DeltaTime);
}

EditMonster1 * EditMonster1::Clone()
{
	return new EditMonster1(*this);
}

