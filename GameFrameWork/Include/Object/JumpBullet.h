#pragma once
#include "Object.h"
class JumpBullet : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	JumpBullet* Clone() override;

	void SetDeleteDistance(float Value) { DeleteDistance = Value; }
	void SetIsFire(bool Value) { isFire = Value; }
	void SetPowerPlus(float Value) { Power += Value; }
	void SetMaxPosPlus(float Value) { MoveSpeed += Value; }

protected:
	JumpBullet();
	JumpBullet(const JumpBullet& Value);
	~JumpBullet();

private:
	float DeleteDistance;
	float Gravity;
	float Power;
	bool isFire;
};

