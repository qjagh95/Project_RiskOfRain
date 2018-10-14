#include "MoneyCoin.h"

MoneyCoin::MoneyCoin()
{
	m_ObjectType = OT_COIN;
	SetTag("MoneyCoin");
}

MoneyCoin::MoneyCoin(const MoneyCoin & Value)
	:Coin(Value)
{
}

MoneyCoin::~MoneyCoin()
{
}

bool MoneyCoin::Init()
{
	Coin::Init();

	AddAnimationClip("MoneyCoin", AT_ATLAS, AO_LOOP, 16.0f, 15.0f, 8, 1, 8, 1, 0, 0, 0.5f, "MoneyCoin", TEXT("Object/Money.bmp"));
	ChangeClip("MoneyCoin");

	SetSize(16.0f, 15.0f);

	return true;
}

int MoneyCoin::Input(float DeltaTime)
{
	Coin::Input(DeltaTime);
	return 0;
}

int MoneyCoin::Update(float DeltaTime)
{
	Coin::Update(DeltaTime);

	return 0;
}

int MoneyCoin::LateUpdate(float DeltaTime)
{
	Coin::LateUpdate(DeltaTime);
	return 0;
}

void MoneyCoin::Collision(float DeltaTime)
{
	Coin::Collision(DeltaTime);
}

void MoneyCoin::Render(HDC Hdc, float DeltaTime)
{
	Coin::Render(Hdc, DeltaTime);
}

MoneyCoin * MoneyCoin::Clone()
{
	return new MoneyCoin(*this);
}