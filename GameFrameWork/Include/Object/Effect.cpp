#include "Effect.h"

Effect::Effect()
	:m_Target(NULL), m_ActiveTime(0.0f), m_Range(0.0f), m_TimeVar(0.0f)
{
	m_ObjectType = OT_EFFECT;
	SetTag("Effect");
}

Effect::Effect(const Effect & effect)
	:Object(effect)
{
	m_Target = NULL;
	m_ActiveTime = effect.m_ActiveTime;
	m_Range = 0.0f;
	m_TimeVar = 0.0f;
}

Effect::~Effect()
{
}

bool Effect::Init()
{
	return true;
}

int Effect::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int Effect::Update(float DeltaTime)
{
	Object::Update(DeltaTime);
	return 0;
}

int Effect::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void Effect::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void Effect::Render(HDC hDC, float DeltaTime)
{
	Object::Render(hDC, DeltaTime);
}

Effect * Effect::Clone()
{
	return new Effect(*this);
}

void Effect::SetTarget(Object * pTarget)
{
	SAFE_RELEASE(m_Target);

	m_Target = pTarget;

	if (m_Target)
		m_Target->AddRefCount();
}
