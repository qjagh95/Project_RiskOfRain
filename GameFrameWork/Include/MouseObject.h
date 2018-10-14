#pragma once
#include "./Object/Object.h"
class MouseObject : public Object
{
public:
	virtual bool Init();
	virtual int Input(float DeltaTime);
	virtual int Update(float DeltaTime);
	virtual int LateUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual MouseObject* Clone();

	bool GetLBotton() const { return m_isLBotton; }
	bool GetLRotton() const { return m_isRBotton; }
	bool GetLMotton() const { return m_isMBotton; }

private:
	bool m_isLBotton;
	bool m_isRBotton;
	bool m_isMBotton;

protected:
	MouseObject();
	MouseObject(const MouseObject& mouse);
	~MouseObject();

public:
	friend class Object;
	friend class Input;
};

