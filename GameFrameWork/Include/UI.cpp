#include "UI.h"

UI::UI()
{
	m_ObjectType = OT_UI;
	isCameraMode = false;
}

UI::UI(const UI & ui)
	:Object(ui)
{
}

UI::~UI()
{
}

bool UI::Init()
{
	if (Object::Init() == false)
		return false;

	return true;
}

int UI::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int UI::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int UI::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void UI::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void UI::Render(HDC hDC, float DeltaTime)
{
	Object::Render(hDC, DeltaTime);
}