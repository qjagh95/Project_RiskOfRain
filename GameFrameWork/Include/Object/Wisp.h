#pragma once
#include "Monster.h"

enum WISP_STATE
{
	WS_MOVE,
	WS_TRACE,
	WS_ATTACK,
	WS_MAX,
};

class Wisp :public Monster
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
	Wisp* Clone() override;
	void TileCollsionActive(float DeltaTime) override;

	void RangeCheck();

	void FS_MOVE(float DeltaTime);
	void FS_TRACE(float DeltaTime);
	void FS_ATTACK(float DeltaTime);

private:
	float AttackRange;
	float TraceRange;
	bool isAttack;
	bool isTrace;
	float TraceTime;
	int Attack;
	string AnimationName[WS_MAX];

	float ChangeTime;
	float AttackDelay;
	int PrevFrame;

	bool isIdleStop = false;

	float IdleTimeVar = 0.0f;
	bool isIdle = false;

protected:
	Wisp();
	Wisp(const Wisp& Value);
	~Wisp();
};

