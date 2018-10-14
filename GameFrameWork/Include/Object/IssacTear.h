#pragma once
#include "Object.h"
class IssacTear : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	IssacTear* Clone() override;

	void SetDir(float Dir) { MoveDir = Dir; }
	int GetAttack() const { return Attack; }
	void SetAttack(int iAttack) { Attack = iAttack; }
	void SetTearForce(float fForce) { SetForce(fForce); }

private:
	float MoveDir;
	int Attack;
	int RandNum;

protected:
	IssacTear();
	IssacTear(const IssacTear& Value);
	~IssacTear();
};

