#include "ExpEffect.h"
#include "../Resource/Texture.h"
#include "../Resource/Animation.h"

ExpEffect::ExpEffect()
{
	m_ObjectType = OT_EFFECT;
	SetTag("ExpEffect");
}

ExpEffect::ExpEffect(const ExpEffect & Value)
	:Object(Value)
{
}

ExpEffect::~ExpEffect()
{
}

bool ExpEffect::Init()
{
	SetSize(57.0f, 12.0f);
	SetPivot(0.5f, 0.5f);
	SetIsCameraMode(true);

	AddAnimationClip("ExpEffect", AT_ATLAS, AO_LOOP, 57.0f, 12.0f, 5, 1, 5, 1, 0, 0, 0.3f, "ExpEffect", TEXT("Effect/getExp.bmp"));
	ChangeClip("ExpEffect");
	return true;
}

int ExpEffect::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int ExpEffect::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	if (m_Animation != NULL && m_Animation->GetIsEnd() == true)
		SetisActiv(false);

	return 0;
}

int ExpEffect::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void ExpEffect::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void ExpEffect::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

ExpEffect * ExpEffect::Clone()
{
	return new ExpEffect(*this);
}