#pragma once
#include "Object.h"
class Hider;
class UsingItemBase : public Object
{
public:
	friend class Object;

	virtual bool Init();
	virtual int Input(float DeltaTime);
	virtual int Update(float DeltaTime);
	virtual int LateUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC Hdc, float DeltaTime);
	virtual UsingItemBase* Clone();

	void SetDelayTime(float value) { DelayTime = value; }

private:
	float DelayTime;

protected:
	UsingItemBase();
	UsingItemBase(const UsingItemBase& Value);
	~UsingItemBase();
};

