#include "CoinUI.h"

CoinUI::CoinUI()
{
	m_ObjectType = OT_UI;
	SetTag("CoinUI");
}

CoinUI::CoinUI(const CoinUI & Value)
	:Object(Value)
{
}

CoinUI::~CoinUI()
{
}

bool CoinUI::Init()
{
	SetTexture("CoinUI",TEXT("UI/Coin.bmp"));
	SetSize(40.0f, 48.0f);
	SetPos(100.0f, 100.0f);
	SetIsCameraMode(false);

	SetColorKey(RGB(255, 0, 255));

	return true;
}

int CoinUI::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int CoinUI::Update(float DeltaTime)
{
	Object::Update(DeltaTime);
	return 0;
}

int CoinUI::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void CoinUI::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void CoinUI::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

CoinUI * CoinUI::Clone()
{
	return new CoinUI(*this);
}
