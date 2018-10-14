#include "TimeUI.h"
#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Object/Number.h"
#include "../Scene/Layer.h"

int TimeUI::PlayMinit = 0;
int TimeUI::PlaySecond = 0;

TimeUI::TimeUI()
	:DotTexture(NULL), m_Second(NULL), m_Minit(NULL)
	,TimeVar(0.0f)
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
	SAFE_RELEASE(m_Second);
	SAFE_RELEASE(m_Minit);
}

bool TimeUI::Init()
{
	SetTexture("timeUI", TEXT("UI/Difficulty.bmp"));
	SetSize(225.0f, 314.0f);
	SetPos(Core::Get()->GetWinSizeVector2().x - m_Size.x, 50.0f);
	SetIsCameraMode(false);
	SetColorKey(RGB(255, 0, 255));

	DotTexture = ResourceManager::Get()->LoadTexture("TimeDot",TEXT("object/Dot.bmp"));
	DotPos = Vector2(1715.0f, 70.0f);
	DotSize = Vector2(10.0f,24.0f);

	m_Second = Object::CreateObject<Number>("NumberSecond", m_Layer);
	m_Second->SetPos(1760.0f, 70.0f);
	m_Second->SetTexture("NumberSecond", TEXT("object/TempNumber.bmp"));
	m_Second->SetNumber(PlaySecond);
	m_Second->SetNumberSize(19.0f, 24.0f);
	m_Second->SetNumberViewSize(19.0f, 24.0f);
	m_Second->SetColorKey(RGB(255, 0, 255));
	m_Second->SetIsCameraMode(false);

	m_Minit = Object::CreateObject<Number>("Number", m_Layer);
	m_Minit->SetPos(1700.0f, 70.0f);
	m_Minit->SetTexture("NumberMinit", TEXT("object/TempNumber.bmp"));
	m_Minit->SetNumber(PlayMinit);
	m_Minit->SetNumberSize(19.0f, 24.0f);
	m_Minit->SetNumberViewSize(19.0f, 24.0f);
	m_Minit->SetColorKey(RGB(255, 0, 255));
	m_Minit->SetIsCameraMode(false);

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
	
	TimeVar += DeltaTime;

	if (TimeVar >= 1.0f)
	{
		PlaySecond++;
		TimeVar = 0.0f;
	}

	if (PlaySecond == 60)
	{
		PlaySecond = 0;
		PlayMinit++;
	}
	if (PlayMinit == 60)
		PlayMinit = 0;

	m_Second->SetNumber(PlaySecond);
	m_Minit->SetNumber(PlayMinit);

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
