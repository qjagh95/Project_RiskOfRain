#pragma once
#include "Object.h"
class BaseAttackBullet : public Object
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
	BaseAttackBullet* Clone() override;

	void SetDir(float fDir) { Dir = fDir; }
	void SetAttack(int iAttack);
	int GetAttack() const { return Attack; }
	void SetIsStop(bool bStop) { isStop = bStop; }

protected:
	BaseAttackBullet();
	BaseAttackBullet(const BaseAttackBullet& Value);
	~BaseAttackBullet();

private:
	float Dir;
	bool isStop;
	bool isTileCol;
	int Attack;
	bool isHit;
};

