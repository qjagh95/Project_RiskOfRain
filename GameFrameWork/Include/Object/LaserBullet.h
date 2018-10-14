#pragma once
#include "Object.h"
class LaserBullet : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollsionAfterUpdate(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	LaserBullet* Clone() override;


	void SetAttack(int iAttack);
	int GetAttack() const { return Attack; }

protected:
	LaserBullet();
	LaserBullet(const LaserBullet& Value);
	~LaserBullet();

private:
	int Attack;
};

