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
	virtual void CollsionAfterUpdate(float DeltaTime);
	virtual void Render(HDC Hdc, float DeltaTime);
	virtual void SetTarget(Object* Value);
	virtual Monster* Clone() override;
	virtual void TileCollsionActive(float DeltaTime) override;

	void DirCheck();
	void MonsterMove(float DeltaTime);
	void AnimationDirCheck(string *aName, int state);
	void SelectState(string* AnimationName ,int State);

	static int GetSceneMonsterCount() { return SceneMonsterCount; }
	void SetHp(int Value) { Hp = Value; }
	int GetHp() const { return Hp; }
	void SetMaxHp(int Value) { MaxHp = Value; }
	int GetMaxHp() const { return MaxHp; }
	void SetAttack(int Value) { Attack = Value; }
	int GetAttack() const { return Attack; }
	void SetMoneyCoinCount(int iCount) { MoneyCoinCount = iCount;}
	int GetMoneyCoinCount() const { return MoneyCoinCount; }
	void SetExpCoinCount(int iCount) { ExpCoinCount = iCount; }
	int GetExpCoinCount() const { return ExpCoinCount; }
	void SetBarIsShow(bool Value);

	virtual void BaseAttackHitFirst(Collider* Src, Collider* Dest, float DeltaTime);
	void BaseAttackHitDoing(Collider* Src, Collider* Dest, float DeltaTime);
	void BaseAttackHitEnd(Collider* Src, Collider* Dest, float DeltaTime);

	virtual void SkillTwoHitFirst(Collider* Src, Collider* Dest, float DeltaTime);
	void SkillTwoHitDoing(Collider* Src, Collider* Dest, float DeltaTime);
	void SkillTwoHitEnd(Collider* Src, Collider* Dest, float DeltaTime);

protected:
	Monster();
	Monster(const Monster& Value);
	~Monster();

	string Dir;
	string PrevDir;
	float MoveDir;
	Object* Target;
	float Distance;
	ColliderRect* RC;
	bool monsterColl;

	static int SceneMonsterCount;

	float PlayerDgree;
	int mState;
	int PrevState;

private:
	int MaxHp;
	int Hp;
	int Attack;
	string Name;

	int MoneyCoinCount;
	int ExpCoinCount;

	Bar* HpBar;
};

