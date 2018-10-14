#pragma once
#include "Charactor.h"
#include "../stdafx.h"
class Tile;
class Collider;
class Bullet;
class FollowBullet;
class Effect;
class Bar;
class Number;
class Hider;
class ColliderPoint;
class Commando : public Charactor
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollsionAfterUpdate(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	Commando* Clone() override;
	void TileCollsionActive(float DeltaTime) override;

	void BulletHit(Collider* Src, Collider* Dest, float DeltaTime);
	void RopeHit(Collider* Src, Collider* Dest, float DeltaTime);
	void PumpHit(Collider* Src, Collider* Dest, float DeltaTime);
	void RopeUpHit(Collider* Src, Collider* Dest, float DeltaTime);
	void LineHit(Collider* Src, Collider* Dest, float DeltaTime);
	void CoinHit(Collider* Src, Collider* Dest, float DeltaTime);
	void ItemBoxHit(Collider* Src, Collider* Dest, float DeltaTime);
	void TearHit(Collider* Src, Collider* Dest, float DeltaTime);

	void PlayerMove(float DeltaTime);

	void DirCheck();
	void HpCheck();
	void RopeCheck();
	void LevelUpCheck();

	void SetMoney(int Value) { pMoney = Value; }
	static int GetMoney() { return pMoney; }
	void SetExp(int Value) { Exp = Value; }
	void AddExp(int Value) { Exp += Value; }
	void SetHp(int Value) { Hp = Value; }
	static int GetHp() { return Hp; }
	void AddHp(int Value) { Hp += Value; }

	///-------------FSMÇÔ¼ö-------------
	void FS_Idle(float DeltaTime);
	void FS_Move(float DeltaTime);
	void FS_Jump(float DeltaTime);
	void Fs_JumpDown(float DeltaTime);
	void FS_Skill1(float DeltaTime);
	void FS_Skill2(float DeltaTime);
	void FS_Skill3(float DeltaTime);
	void FS_Skill4(float DeltaTime);
	void FS_Rope(float DeltaTime);
	///---------------------------------

	void SelectState(PLAYER_STATE eState);
	void SkillState();
	void SkillTimeCheck(float DeltaTime);

	void BasicInit();
	void AnimationInit();
	void CollsionInit();
	void InfoInit();

protected:
	Commando();
	Commando(const Commando& Value) : Charactor(Value) {}
	~Commando();

private:
	static int pMoney;
	Number* MoneyNumber;
	static int Hp;
	static int MaxHp;
	static int Exp;
	static int MaxExp;
	static int Level;
	int AttackDamege;

	float SkillOneDelay;
	float SkillTwoDelay;
	float SkillThreeDelay;
	float SkillFourDelay;

	bool isSkillOne;
	bool isSkillTwo;
	bool isSkillThree;
	bool isSkillFour;
	
	bool isRopeHiting;
	bool isRopeUpHitting;
	bool isJumping;

	bool isLineHit;
	Vector2 HitPos;
	Vector2 HitSize;
	Vector2 PrevHitPos;
	list<Vector2> HitPosList;

	PLAYER_STATE pState;
	PLAYER_STATE PrevState;

	float MoveDir;
	string Dir;
	string AnimationName[PS_MAX];
	string StateName;
	Vector2 RopePos;
	Object* CurTarget;
	Vector2 Center;
	float TimeVar;

	int PrevFrame;

public:
	friend class Object;
	friend class CommandoUI;
};

