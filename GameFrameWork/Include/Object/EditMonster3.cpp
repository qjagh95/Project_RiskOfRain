#include "EditMonster3.h"
#include "../Coll/ColliderRect.h"

EditMonster3::EditMonster3()
{
	m_ObjectType = OT_EDITOBJECT;
	SetTag("EditMonster3");
}

EditMonster3::EditMonster3(const EditMonster3 & Value)
	:EditMonster(Value)
{
}

EditMonster3::~EditMonster3()
{
}

bool EditMonster3::Init()
{
	EditMonster::Init();
	SetSize(30.0f, 30.0f);
	RC->SetVirtualRect(m_Size);

	SetTexture("EditMonster3", TEXT("EditMonster/EditorJellyFish.bmp"));

	return true;
}

int EditMonster3::Input(float DeltaTime)
{
	EditMonster::Input(DeltaTime);

	return 0;
}

int EditMonster3::Update(float DeltaTime)
{
	EditMonster::Update(DeltaTime);

	return 0;
}

int EditMonster3::LateUpdate(float DeltaTime)
{
	EditMonster::LateUpdate(DeltaTime);

	return 0;
}

void EditMonster3::Collision(float DeltaTime)
{
	EditMonster::Collision(DeltaTime);
}

void EditMonster3::Render(HDC Hdc, float DeltaTime)
{
	EditMonster::Render(Hdc, DeltaTime);
}

EditMonster3 * EditMonster3::Clone()
{
	return new EditMonster3(*this);
}
