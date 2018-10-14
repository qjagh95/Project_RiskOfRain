#include "TimeUI.h"
#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"

TimeUI::TimeUI()
	:DotTexture(NULL)
{
	m_ObjectType = OT_UI;
	SetTag("TimeUI");
}

TimeUI::TimeUI(const TimeUI & Value)
	:Object(Value)
{
}

TimeUI::~TimeUI()
{
	SAFE_RELEASE(DotTexture);
}

bool TimeUI::Init()
{
	SetTexture("timeUI", TEXT("UI/Difficulty.bmp"));
	SetSize(225.0f, 314.0f);
	SetPos(1300.0f, 50.0f);
	SetIsCameraMode(false);

	DotTexture = ResourceManager::Get()->LoadTexture("TimeDot",TEXT("object/Dot.bmp"));
	DotPos = Vector2(1440.0f, 70.0f);
	DotSize = Vector2(10.0f,24.0f);

	SetColorKey(RGB(255, 0, 255));

	return true;
}

int TimeUI::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int TimeUI::Update(float DeltaTime)
{
	Object::Update(DeltaTime);
	return 0;
}

int TimeUI::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void TimeUI::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void TimeUI::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);

	//DotTexture ( : )
	TransparentBlt(Hdc, (int)DotPos.x, (int)DotPos.y, (int)DotSize.x, (int)DotSize.y, DotTexture->GetMemDC(), 0, 0, (int)DotSize.x, (int)DotSize.y, (UINT)m_ColorKey);
}

TimeUI * TimeUI::Clone()
{
	return new TimeUI(*this);
}
