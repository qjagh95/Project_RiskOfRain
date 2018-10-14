#include "Hider.h"
#include "Number.h"
#include "../Scene/Layer.h"

Hider::Hider()
	:DelayTimeNumber(NULL)
{
	m_ObjectType = OT_UI;
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

	if (DelayTime == 0)
		return 0;

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

void Hider::SetHider(Layer * pLayer, SKILL_TYPE eType, int dTime)
{
	switch (eType)
	{
		case ST_SKILLONE:
		{
			//플레이어에선 누를때마다 CreateObject, SetHider
			//포지션셋팅,
		}
			break;
		case ST_SKILLTWO:
		{

		}
			break;
		case ST_SKILLTHREE:
		{

		}
			break;
		case ST_SKILLFOUR:
		{

		}
			break;
	}
}

