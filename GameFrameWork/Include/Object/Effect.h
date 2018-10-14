#pragma once
#include "../Object/Object.h"

class Effect : public Object
{
	friend class Object;

public:
	virtual bool Init();
	virtual int Input(float DeltaTime);
	virtual int Update(float DeltaTime);
	virtual int LateUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual Effect* Clone();

	void SetTarget(Object* pTarget);
	void SetRange(float fRange) { m_Range = fRange; }

private:
	Object*	m_Target;

	float m_Range;
	float m_ActiveTime;
	float m_TimeVar;

protected:
	Effect();
	Effect(const Effect& effect);
	~Effect();
};

