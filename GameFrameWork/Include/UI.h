#pragma once
#include "./Object/Object.h"
class UI : public Object
{
public:
	virtual bool Init();
	virtual int Input(float DeltaTime);
	virtual int Update(float DeltaTime);
	virtual int LateUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual UI* Clone() = 0;

protected:
	UI();
	UI(const UI& ui);
	~UI();

public:
	friend class Object;
};

