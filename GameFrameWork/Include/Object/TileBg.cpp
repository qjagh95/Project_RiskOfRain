#include "TileBg.h"
#include "../Resource/Texture.h"

TileBg::TileBg()
{
	m_ObjectType = OT_BACKGROUND;
	SetTag("TileBg");
}

TileBg::TileBg(const TileBg & Value)
	:Object(Value)
{
}

TileBg::~TileBg()
{
}

bool TileBg::Init()
{
	SetPos(0.0f, 0.0f);
	SetSize(1800.0f, 1000.0f);
	SetPivot(0.0f, 0.0f);
	SetIsCameraMode(false);

	SetTexture("TileBg", L"Tile/map1BackGround.bmp");

	return true;
}

int TileBg::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int TileBg::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int TileBg::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void TileBg::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void TileBg::Render(HDC Hdc, float DeltaTime)
{
	TransparentBlt(Hdc, 0, 0, (int)m_Size.x, (int)m_Size.y, m_Texture->GetMemDC(), (int)CameraPos.x, (int)CameraPos.y, (int)m_Size.x, (int)m_Size.y, m_ColorKey);
}

TileBg * TileBg::Clone()
{
	return new TileBg(*this);
}
