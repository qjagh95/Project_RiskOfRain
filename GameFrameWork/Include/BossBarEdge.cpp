#include "BossBarEdge.h"

BossBarEdge::BossBarEdge()
{
	m_ObjectType = OT_UI;
	SetTag("BossBarEdge");
}

BossBarEdge::BossBarEdge(const BossBarEdge & Value)
	:Object(Value)
{
}

BossBarEdge::~BossBarEdge()
{
}

bool BossBarEdge::Init()
{
	SetTexture("BossBarEdge", TEXT("BossBar1.bmp"));
	SetSize(1783.0f, 39.0f);
	SetPos(100.0f, 100.0f);
	SetIsCameraMode(false);

	SetColorKey(RGB(255, 0, 255));

	return true;
}

int BossBarEdge::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int BossBarEdge::Update(float DeltaTime)
{
	Object::Update(DeltaTime);
	return 0;
}

int BossBarEdge::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void BossBarEdge::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void BossBarEdge::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

BossBarEdge * BossBarEdge::Clone()
{
	return new BossBarEdge(*this);
}
