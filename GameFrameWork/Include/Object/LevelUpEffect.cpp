#include "LevelUpEffect.h"
#include "../Resource/Texture.h"
#include "../Resource/Animation.h"

LevelUpEffect::LevelUpEffect()
{
	m_ObjectType = OT_EFFECT;
	SetTag("LevelUpEffect");
}

LevelUpEffect::LevelUpEffect(const LevelUpEffect & Value)
	:Object(Value)
{
}

LevelUpEffect::~LevelUpEffect()
{
}

bool LevelUpEffect::Init()
{
	SetSize(854.0f, 131.0f);
	SetPivot(0.5f, 0.5f);
	SetIsCameraMode(true);

	AddAnimationClip("LevelUpEffect", AT_ATLAS, AO_LOOP, 854.0f, 131.0f, 23, 1, 23, 1, 0, 0, 2.0f, "LevelUpEffect", TEXT("Effect/LevelUpEffect.bmp"));
	ChangeClip("LevelUpEffect");
	return true;
}

int LevelUpEffect::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int LevelUpEffect::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	m_Pos.y -= 80.0f * DeltaTime;

	if (m_Animation != NULL && m_Animation->GetIsEnd() == true)
		SetisActiv(false);

	return 0;
}

int LevelUpEffect::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void LevelUpEffect::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void LevelUpEffect::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

LevelUpEffect * LevelUpEffect::Clone()
{
	return new LevelUpEffect(*this);
}