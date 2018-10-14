#include "AncientEffect.h"
#include "../Scene/Layer.h"
#include "../Resource/Animation.h"

#include "../Object/AncientHitBox.h"

AncientEffect::AncientEffect()
{
	m_ObjectType = OT_BULLET;
	SetTag("AncientEffect");
}

AncientEffect::AncientEffect(const AncientEffect & Value)
	:Object(Value)
{
}

AncientEffect::~AncientEffect()
{
}

bool AncientEffect::Init()
{
	PrevFrame = 0;

	SetPivot(0.5f, 1.0f);
	SetSize(165.0f, 280.0f);
	AddAnimationClip("AncientEffect", AT_ATLAS, AO_LOOP, 165.0f, 280.0f, 16, 1, 16, 1, 0, 0, 0.7f, "AncientEffect", TEXT("Effect/Ancient_Attack_Effect.bmp"));

	return true;
}

int AncientEffect::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int AncientEffect::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	if (m_Animation->GetFrameX() == 11)
	{
		if (PrevFrame == m_Animation->GetFrameX())
			return 0;

		AncientHitBox* HitBox = Object::CreateObject<AncientHitBox>("AncientHitBox", m_Layer);
		HitBox->SetPos(m_Pos);
		HitBox->SetSize(m_Size);
		HitBox->SetAttack(Attack);

		SAFE_RELEASE(HitBox);
	}

	if (m_Animation != NULL && m_Animation->GetIsEnd() == true)
		SetisActiv(false);

	return 0;
}

int AncientEffect::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	PrevFrame = m_Animation->GetFrameX();

	return 0;
}

void AncientEffect::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void AncientEffect::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

AncientEffect * AncientEffect::Clone()
{
	return new AncientEffect(*this);
}
