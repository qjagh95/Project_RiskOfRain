#pragma once
#include "Object.h"
class ShotGunBullet : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	ShotGunBullet* Clone() override;

	void SetDeleteDistance(float Value) { DeleteDistance = Value; }

protected:
	ShotGunBullet();
	ShotGunBullet(const ShotGunBullet& Value);
	~ShotGunBullet();

private:
	float DeleteDistance;
};

