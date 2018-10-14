#include "MenuStarBg.h"
#include "../Camera.h"
#include "../Resource/Texture.h"

MenuStarBg::MenuStarBg()
{
	m_ObjectType = OT_BACKGROUND;
	SetTag("StarBg");
}

MenuStarBg::MenuStarBg(const MenuStarBg & Value)
	:Object(Value)
{
}

MenuStarBg::~MenuStarBg()
{
}

bool MenuStarBg::Init()
{
	SetPos(0.0f, 0.0f);
	SetSize(1280.0f, 720.0f);
	SetPivot(0.0f, 0.0f);
	SetIsCameraMode(false);
	SetColorKey(RGB(255, 0, 255));

	SetTexture("SelectBg", L"Window/Star.bmp");

	return true;
}

int MenuStarBg::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int MenuStarBg::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int MenuStarBg::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void MenuStarBg::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void MenuStarBg::Render(HDC Hdc, float DeltaTime)
{
	TransparentBlt(Hdc, 0, 0, (int)m_Size.x, (int)m_Size.y, m_Texture->GetMemDC(), (int)0, (int)0, (int)m_Size.x, (int)m_Size.y, m_ColorKey);
}

MenuStarBg * MenuStarBg::Clone()
{
	return new MenuStarBg(*this);
}

