#include "PerTexture.h"

PerTexture::PerTexture()
{
	m_ObjectType = OT_UI;
	SetTag("PerTexture");
}

PerTexture::PerTexture(const PerTexture & Value)
	:Object(Value)
{
}

PerTexture::~PerTexture()
{
}

bool PerTexture::Init()
{
	SetTexture("Per", TEXT("object/Per.bmp"));
	SetPos(Vector2(890.0f, 943.0f));
	SetSize(Vector2(10.0f, 24.0f));
	SetIsCameraMode(false);

	SetColorKey(RGB(255, 0, 255));

	return true;
}

int PerTexture::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int PerTexture::Update(float DeltaTime)
{
	Object::Update(DeltaTime);
	return 0;
}

int PerTexture::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void PerTexture::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void PerTexture::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

PerTexture * PerTexture::Clone()
{
	return new PerTexture(*this);
}

