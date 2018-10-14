#include "Hider.h"
#include "Number.h"
#include "../Scene/Layer.h"
#include "../Scene/Scene.h"

Hider::Hider()
	:DelayTimeNumber(NULL), DelayTime(0.0f), Num(0)
{
	m_ObjectType = OT_EFFECT;
	SetTag("Hider");
}

Hider::Hider(const Hider & Value)
	:Object(Value)
{
}

Hider::~Hider()
{
	SAFE_RELEASE(DelayTimeNumber);
}

bool Hider::Init()
{
	SetTexture("Hider", TEXT("UI/hider.bmp"));
	SetSize(54.0f, 54.0f);
	SetIsCameraMode(false);

	DelayTimeNumber = Object::CreateObject<Number>("HiderNumber", m_Scene->FindLayer("UI"));
	DelayTimeNumber->SetTexture("HiderNumber", TEXT("object/TempNumber.bmp"));
	DelayTimeNumber->SetNumberSize(19.0f, 24.0f);
	DelayTimeNumber->SetColorKey(RGB(255, 0, 255));
	DelayTimeNumber->SetIsCameraMode(false);
	DelayTimeNumber->SetNumberViewSize(Vector2(19.0f, 24.0f));

	return true;
}

int Hider::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int Hider::Update(float DeltaTime)
{
	Object::Update(DeltaTime);
	DelayTime -= DeltaTime;
	Num = (int)DelayTime;

	DelayTimeNumber->SetNumber(Num);
	
	if (DelayTime <= 0.0f)
	{
		DelayTimeNumber->SetisActiv(false);
		SetisActiv(false);
	}

	return 0;
}

int Hider::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void Hider::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void Hider::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

Hider * Hider::Clone()
{
	return new Hider(*this);
}

void Hider::SetHider(SKILL_TYPE eType, float dTime)
{
	DelayTime = dTime;

	switch (eType)
	{
		case ST_SKILLONE:
		{
			SetPos(Vector2(568.0f, 640.0f));
			DelayTimeNumber->SetPos(Vector2(m_Pos.x + m_Size.x - 10.0f, m_Pos.y + m_Size.GetHalfY() - 10.0f));
		}
			break;
		case ST_SKILLTWO:
		{
			SetPos(Vector2(637.0f, 641.0f));
			DelayTimeNumber->SetPos(Vector2(m_Pos.x + m_Size.x - 10.0f, m_Pos.y + m_Size.GetHalfY() - 10.0f));
		}
			break;
		case ST_SKILLTHREE:
		{
			SetPos(Vector2(706.0f, 641.0f));
			DelayTimeNumber->SetPos(Vector2(m_Pos.x + m_Size.x - 10.0f, m_Pos.y + m_Size.GetHalfY() - 10.0f));
		}
			break;
		case ST_SKILLFOUR:
		{
			SetPos(Vector2(775.0f, 641.0f));
			DelayTimeNumber->SetPos(Vector2(m_Pos.x + m_Size.x - 10.0f, m_Pos.y + m_Size.GetHalfY() - 10.0f));
		}
			break;
	}
}

