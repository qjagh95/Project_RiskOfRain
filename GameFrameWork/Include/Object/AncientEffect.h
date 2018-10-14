#pragma once
#include "Object.h"
class AncientEffect : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	AncientEffect* Clone() override;
	
	void SetAttack(int Value) { Attack = Value;}
	int GetAttack() const { return Attack; }

private:
	int Attack;
	int PrevFrame;

protected:
	AncientEffect();
	AncientEffect(const AncientEffect& Value);
	~AncientEffect();
};

