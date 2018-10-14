#include "DollerUI.h"

DollerUI::DollerUI()
{
	m_ObjectType = OT_UI;
	SetTag("DollerUI");
}

DollerUI::DollerUI(const DollerUI & Value)
	:Object(Value)
{
}

DollerUI::~DollerUI()
{
}

bool DollerUI::Init()
{
	SetTexture("DollerUI", TEXT("UI/UiDollar.bmp"));
	SetSize(30.0f, 48.0f);
	SetPos(150.0f, 100.0f);
	SetIsCameraMode(false);

	SetColorKey(RGB(255, 0, 255));

	return true;
}

int DollerUI::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int DollerUI::Update(float DeltaTime)
{
	Object::Update(DeltaTime);
	return 0;
}

int DollerUI::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void DollerUI::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void DollerUI::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

DollerUI * DollerUI::Clone()
{
	return new DollerUI(*this);
}
