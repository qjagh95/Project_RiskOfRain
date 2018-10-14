#include "MenuBg.h"
#include "../Camera.h"
#include "../Resource/Texture.h"

MenuBg::MenuBg()
{
	m_ObjectType = OT_BACKGROUND;
	SetTag("Bg");
}

MenuBg::MenuBg(const MenuBg & Value)
	:Object(Value)
{
}

MenuBg::~MenuBg()
{
}

bool MenuBg::Init()
{
	SetPos(0.0f, 0.0f);
	SetSize(1800.0f, 1000.0f);
	SetPivot(0.08f, 0.0f);
	SetIsCameraMode(false);
	SetColorKey(RGB(255, 0, 255));

	SetTexture("MenuBg", L"Window/Start.bmp");

	return true;
}

int MenuBg::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int MenuBg::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int MenuBg::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void MenuBg::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void MenuBg::Render(HDC Hdc, float DeltaTime)
{
	Vector2 LeftTop = m_Pos - m_Size * m_Pivot;

	TransparentBlt(Hdc, (int)LeftTop.x, (int)LeftTop.y ,(int)m_Size.x, (int)m_Size.y, m_Texture->GetMemDC(), (int)0, (int)0, (int)m_Size.x, (int)m_Size.y, m_ColorKey);
}

MenuBg * MenuBg::Clone()
{
	return new MenuBg(*this);
}
