#include "BaseEffect.h"
#include "../Resource/Texture.h"
#include "../Resource/Animation.h"

BaseEffect::BaseEffect()
{
	m_ObjectType = OT_EFFECT;
	SetTag("BaseEffect");
}

BaseEffect::BaseEffect(const BaseEffect & Value)
	:Object(Value)
{
}

BaseEffect::~BaseEffect()
{
}

bool BaseEffect::Init()
{
	SetSize(30.0f, 51.0f);
	SetIsCameraMode(true);

	AddAnimationClip("LeftEffect", AT_ATLAS, AO_ONCE_DESTROY, 30.0f, 51.0f, 4, 1, 4, 1, 0, 0, 0.3f, "LeftEffect", TEXT("Effect/Left_Hit_Effect1.bmp"));
	AddAnimationClip("RightEffect", AT_ATLAS, AO_ONCE_DESTROY, 30.0f, 51.0f, 4, 1, 4, 1, 0, 0, 0.3f, "RightEffect", TEXT("Effect/Right_Hit_Effect1.bmp"));

	return true;
}

int BaseEffect::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int BaseEffect::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int BaseEffect::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void BaseEffect::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void BaseEffect::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

BaseEffect * BaseEffect::Clone()
{
	return new BaseEffect(*this);
}

void BaseEffect::SelectAnimationClip(float Dir)
{
	int a = (int)Dir;

	switch (a)
	{
		case 1:
			ChangeClip("LeftEffect");
			SetPivot(1.0f, 0.5f);
			break;
		case -1:
			ChangeClip("RightEffect");
			SetPivot(0.0f, 0.5f);
			break;
	}
}
