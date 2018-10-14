#pragma once
enum ISSAC1_MONSTER_STATE
{
	IMS_IDLE,
	IMS_MOVE,
	IMS_TRACE,
	IMS_ATTACK,
	IMS_MAX,
};

#include "Monster.h"
class IssacEnemy1 : public Monster
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
	IssacEnemy1* Clone() override;
	void TileCollsionActive(float DeltaTime) override;

	void BaseAttackHitFirst(Collider* Src, Collider* Dest, float DeltaTime) override;
	void SkillTwoHitFirst(Collider* Src, Collider* Dest, float DeltaTime) override;

	void RangeCheck(float DeltaTime);
	void TimeMoveIdle(float DeltaTime);

	void SetTraceRange(float Value) { TraceRange = Value; }

	void FS_IDLE(float DeltaTime);
	void FS_MOVE(float DeltaTime);
	void FS_TRACE(float DeltaTime);
	void FS_ATTACK(float DeltaTime);

private:
	float TraceRange;
	float AttackRange;
	bool isAttack;
	bool isStop;
	bool isIdle;
	string AnimationName[IMS_MAX];
	
	float BackDistance;
	bool isHit;

	float TimeVar;
	float IdleTime;
	float AttackTime;
	float StopTime;
	int PrevFrame;
	int Count;

protected:
	IssacEnemy1();
	IssacEnemy1(const IssacEnemy1& Value);
	~IssacEnemy1();
};

