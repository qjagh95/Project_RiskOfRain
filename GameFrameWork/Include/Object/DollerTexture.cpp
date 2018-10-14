#include "DollerTexture.h"
#include "../Resource/Texture.h"

DollerTexture::DollerTexture()
{
}

DollerTexture::DollerTexture(const DollerTexture & Value)
	:Object(Value)
{
}

DollerTexture::~DollerTexture()
{
}

bool DollerTexture::Init()
{
	SetSize(20.0f, 48.0f);
	SetPivot(0.5f, 0.5f);
	SetIsCameraMode(true);
	SetTexture("YellodwDoller", TEXT("ui/ItemBoxDollar.bmp"));
	SetColorKey(RGB(255, 0, 255));

	return true;
}

int DollerTexture::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int DollerTexture::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int DollerTexture::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void DollerTexture::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void DollerTexture::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

DollerTexture * DollerTexture::Clone()
{
	return new DollerTexture(*this);
}

void DollerTexture::SetDifferntTexture(Texture * pTexture)
{
	SetTexture(pTexture);
}

void DollerTexture::SetDifferntTexture(const string & KeyName, const TCHAR * FileName)
{
	SetTexture(KeyName, FileName);
}

