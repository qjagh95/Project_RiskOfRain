#pragma once
#include "../stdafx.h"
#include "Charactor.h"
class Bar;
class ColliderRect;
class Monster :	public Charactor
{
public:
	friend class Object;

	virtual bool Init();
	virtual int Input(float DeltaTime);
	virtual int Update(float DeltaTime);
	virtual int LateUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC Hdc, float DeltaTime);
	virtual void SetTarget(Object* Value);
	virtual Monster* Clone() override;
	virtual void TileCollsionActive(float DeltaTime) override;

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
	int MaxHp;
	int Hp;
	int Attack;
	float MoveDir;

	string Dir;
	Object* Target;
	Bar* HpBar;
	ColliderRect* RC;
};

