#include "DieEffect.h"
#include "../Resource/Texture.h"
#include "../Resource/Animation.h"

DieEffect::DieEffect()
{
	m_ObjectType = OT_EFFECT;
	SetTag("DieEffect");
}

DieEffect::DieEffect(const DieEffect & Value)
	:Object(Value)
{
}

DieEffect::~DieEffect()
{
}

bool DieEffect::Init()
{
	SetSize(92.0f, 94.0f);
	SetPivot(0.5f, 0.5f);
	SetIsCameraMode(true);

	AddAnimationClip("DieEffect", AT_ATLAS, AO_LOOP, 92.0f, 94.0f, 4, 1, 4, 1, 0, 0, 0.3f, "DieEffect", TEXT("Effect/DieEffect.bmp"));
	ChangeClip("DieEffect");
	return true;
}

int DieEffect::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int DieEffect::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	if (m_Animation != NULL && m_Animation->GetIsEnd() == true)
		SetisActiv(false);

	return 0;
}

int DieEffect::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void DieEffect::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void DieEffect::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

DieEffect * DieEffect::Clone()
{
	return new DieEffect(*this);
}