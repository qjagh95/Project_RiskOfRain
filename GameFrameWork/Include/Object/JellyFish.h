#pragma once

enum JELLYFISH_STATE
{
	JS_MOVE,
	JS_TRACE,
	JS_ATTACK,
	JS_MAX,
};

#include "Monster.h"
class JellyFish : public Monster
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
	JellyFish* Clone() override;
	void TileCollsionActive(float DeltaTime) override;

	void BaseAttackHitFirst(Collider* Src, Collider* Dest, float DeltaTime) override;
	void SkillTwoHitFirst(Collider* Src, Collider* Dest, float DeltaTime) override;

	void RangeCheck();
	void SelectState(JELLYFISH_STATE mState);

	void FS_MOVE(float DeltaTime);
	void FS_TRACE(float DeltaTime);
	void FS_ATTACK(float DeltaTime);

private:
	float AttackRange;
	float TraceRange;
	bool isAttack;
	int Attack;
	bool isHit;
	float BackDistance;
	string AnimationName[JS_MAX];

	float ChangeTime;
	float AttackDelay;
	int PrevFrame;

protected:
	JellyFish();
	JellyFish(const JellyFish& Value);
	~JellyFish();
};

