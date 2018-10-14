#pragma once
#include "../stdafx.h"
#include "Charactor.h"
class Bar;
class Monster :	public Charactor
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	void SetTarget(Object* Value);
	Monster* Clone() override;

	void SetHp(int Value) { Hp = Value; }
	int GetHp() const { return Hp; }
	void SetAttack(int Value) { Attack = Value; }
	int GetAttack() const { return Attack; }

	void BaseAttackHitFirst(Collider* Src, Collider* Dest, float DeltaTime);
	void BaseAttackHitDoing(Collider* Src, Collider* Dest, float DeltaTime);
	void BaseAttackHitEnd(Collider* Src, Collider* Dest, float DeltaTime);

	void SkillTwoHitFirst(Collider* Src, Collider* Dest, float DeltaTime);
	void SkillTwoHitDoing(Collider* Src, Collider* Dest, float DeltaTime);
	void SkillTwoHitEnd(Collider* Src, Collider* Dest, float DeltaTime);

	void SkillThreeHitFirst(Collider* Src, Collider* Dest, float DeltaTime);
	void SkillThreeHitDoing(Collider* Src, Collider* Dest, float DeltaTime);
	void SkillThreeHitEnd(Collider* Src, Collider* Dest, float DeltaTime);

	void SkillFourHitFirst(Collider* Src, Collider* Dest, float DeltaTime);
	void SkillFourHitDoing(Collider* Src, Collider* Dest, float DeltaTime);
	void SkillFourHitEnd(Collider* Src, Collider* Dest, float DeltaTime);

protected:
	Monster();
	Monster(const Monster& Value);
	~Monster();

private:
	int MoveDir;
	float FireTime;
	float TraceRange;
	float AttackRange;

	int MaxHp;
	int Hp;
	int Attack;

	MONSTER_STATE mState;

	Vector2 LineEnd;
	Object* Target;

	Bar* mHpBar;
};

