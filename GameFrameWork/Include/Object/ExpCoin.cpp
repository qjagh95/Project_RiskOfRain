#include "ExpCoin.h"

ExpCoin::ExpCoin()
{
	m_ObjectType = OT_EXP;
	SetTag("ExpCoin");
}

ExpCoin::ExpCoin(const ExpCoin & Value)
	:Coin(Value)
{
}

ExpCoin::~ExpCoin()
{
}

bool ExpCoin::Init()
{
	Coin::Init();

	AddAnimationClip("ExpCoin", AT_ATLAS, AO_LOOP, 18.0f, 18.0f, 4, 1, 4, 1, 0, 0, 0.2f, "ExpCoin", TEXT("Object/Exp.bmp"));
	ChangeClip("ExpCoin");

	SetSize(18.0f, 18.0f);

	return true;
}

int ExpCoin::Input(float DeltaTime)
{
	Coin::Input(DeltaTime);
	return 0;
}

int ExpCoin::Update(float DeltaTime)
{
	Coin::Update(DeltaTime);

	return 0;
}

int ExpCoin::LateUpdate(float DeltaTime)
{
	Coin::LateUpdate(DeltaTime);
	return 0;
}

void ExpCoin::Collision(float DeltaTime)
{
	Coin::Collision(DeltaTime);
}

void ExpCoin::Render(HDC Hdc, float DeltaTime)
{
	Coin::Render(Hdc, DeltaTime);
}

ExpCoin * ExpCoin::Clone()
{
	return new ExpCoin(*this);
}