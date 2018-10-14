#pragma once

enum ROCKGOLEN_STATE
{
	RS_IDLE,
	RS_TRACE,
	RS_MOVE,
	RS_ATTACK,
	RS_MAX,
};

#include "Monster.h"
class RockGolem : public Monster
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
	RockGolem* Clone() override;
	void TileCollsionActive(float DeltaTime) override;

	void TimeToIdle(float DeltaTime);

	void RangeCheck();

	void FS_IDLE(float DeltaTime);
	void FS_MOVE(float DeltaTime);
	void FS_TRACE(float DeltaTime);
	void FS_ATTACK(float DeltaTime);

private:
	float AttackRange;
	bool isAttack;
	int Attack;

	string AnimationName[RS_MAX];

	float ChangeTime;
	float AttackDelay;
	int PrevFrame;

	bool isIdleStop = false;

	float IdleTimeVar = 0.0f;
	bool isIdle = false;

protected:
	RockGolem();
	RockGolem(const RockGolem& Value);
	~RockGolem();
};

