#pragma once
enum LEMURIAN_STATE
{
	LS_IDLE,
	LS_MOVE,
	LS_TRACE,
	LS_ATTACK,
	LS_JUMP,
	LS_MAX,
};

#include "Monster.h"
class Lemurian : public Monster
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
	Lemurian* Clone() override;
	void TileCollsionActive(float DeltaTime) override;

	void RangeCheck();

	void TimeToIdle(float DeltaTime);

	void FS_IDLE(float DeltaTime);
	void FS_MOVE(float DeltaTime);
	void FS_TRACE(float DeltaTime);
	void FS_ATTACK(float DeltaTime);
	void FS_JUMP(float DeltaTime);

private:
	float AttackRange;
	float TraceRange;
	bool isAttack;
	int Attack;
	string AnimationName[LS_MAX];

	float ChangeTime;
	float AttackDelay;
	int PrevFrame;

	bool isIdleStop = false;

	float IdleTimeVar = 0.0f;
	bool isIdle = false;

protected:
	Lemurian();
	Lemurian(const Lemurian& Value);
	~Lemurian();
};

