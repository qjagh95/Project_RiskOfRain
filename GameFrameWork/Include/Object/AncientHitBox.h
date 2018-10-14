#pragma once
#include "Object.h"
class AncientHitBox : public Object
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
	AncientHitBox* Clone() override;

	int GetAttack() const { return Attack; }
	void SetAttack(int iAttack) { Attack = iAttack; }
	void SetTearForce(float fForce) { SetForce(fForce); }

private:
	int Attack;

protected:
	AncientHitBox();
	AncientHitBox(const AncientHitBox& Value);
	~AncientHitBox();
};

