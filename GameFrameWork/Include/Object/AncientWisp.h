#pragma once
enum ANCIENTWISP_STATE
{
	AS_MOVE,
	AS_ATTACK,
	AS_MAX
};

#include "Monster.h"
class AncientWisp : public Monster
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
	AncientWisp* Clone() override;
	void TileCollsionActive(float DeltaTime) override;

	void RangeCheck();

	void SelectState(ANCIENTWISP_STATE mState);

	void FS_IDLE(float DeltaTime);
	void FS_MOVE(float DeltaTime);
	void FS_ATTACK(float DeltaTime);

private:
	ANCIENTWISP_STATE mState;
	ANCIENTWISP_STATE PrevState;
	float TraceRange;
	float AttackRange;
	float Distance;
	bool isAttack;
	string AnimationName[AS_MAX];

	float TimeVar;
	float IdleTime;
	float AttackTime;
	float StopTime;
	int PrevFrame;

protected:
	AncientWisp();
	AncientWisp(const AncientWisp& Value);
	~AncientWisp();
};

