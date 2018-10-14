#include "PlayTime.h"
#include "Object\Number.h"
#include "Object\Object.h"
#include "Scene\Layer.h"

int PlayTime::PlayMinit = 0;
int PlayTime::PlaySecond = 0;

PlayTime::PlayTime()
	:m_Minit(NULL), m_Second(NULL)
{
	TimeVar = 0.0f;
}

PlayTime::~PlayTime()
{
	SAFE_RELEASE(m_Minit);
	SAFE_RELEASE(m_Second);
}

void PlayTime::Init(Layer * pLayer)
{
	m_Second = Object::CreateObject<Number>("TimeSecond", pLayer);
	m_Second->SetPos(300.0f, 300.0f);
	m_Second->SetTexture("NumberSecond", TEXT("object/TempNumber.bmp"));
	m_Second->SetNumber(PlaySecond);
	m_Second->SetNumberSize(16.0f,24.0f);
	m_Second->SetColorKey(RGB(255,0,255));
	m_Second->SetIsCameraMode(false);
	m_Second->SetPos(100.0f, 100.0f);

	m_Minit = Object::CreateObject<Number>("TimeMinit", pLayer);
	m_Minit->SetPos(300.0f, 300.0f);
	m_Minit->SetTexture("NumberSecond", TEXT("object/TempNumber.bmp"));
	m_Minit->SetNumber(PlayMinit);
	m_Minit->SetNumberSize(16.0f, 24.0f);
	m_Minit->SetColorKey(RGB(255, 0, 255));
	m_Minit->SetIsCameraMode(false);
	m_Minit->SetPos(300.0f, 100.0f);
}

void PlayTime::Update(float DeltaTime)
{
	TimeVar += DeltaTime;

	if (TimeVar >= 1.0f)
	{
		PlaySecond += 1;
		TimeVar = 0.0f;
	}

	if (PlaySecond == 60)
	{
		PlaySecond = 0;
		PlayMinit++;
	}

	if (PlayMinit == 60)
		PlayMinit = 0;
}

void PlayTime::Render(HDC Hdc, float DeltaTime)
{
	m_Second->Render(Hdc, DeltaTime);
	m_Minit->Render(Hdc, DeltaTime);
}
