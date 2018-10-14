#pragma once
#include "Object.h"
class Coin :public Object
{
public:
	friend class Object;

	virtual bool Init();
	virtual int Input(float DeltaTime);
	virtual int Update(float DeltaTime);
	virtual int LateUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC Hdc, float DeltaTime);
	virtual Coin* Clone();

	void SetTarget(Object* pTarget);
	void SetValue(int iValue) { Value = iValue; }
	int GetValue() const { return Value; }
	void SetFinishTime(float fTime) { FinishTime = fTime; }

private:
	Object* Target;
	int	Value;
	float TimeVar;
	float FinishTime;
	bool isFollow;

protected:
	Coin();
	Coin(const Coin& Value);
	~Coin();
};

