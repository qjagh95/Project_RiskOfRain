#pragma once
#include "Charactor.h"
#include "../stdafx.h"

class ItemBase;
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
	
	void TelePoterHit(Collider* Src, Collider* Dest, float DeltaTime);
	void BulletHit(Collider* Src, Collider* Dest, float DeltaTime);
	void RopeHit(Collider* Src, Collider* Dest, float DeltaTime);
	void PumpHit(Collider* Src, Collider* Dest, float DeltaTime);
	void RopeUpHit(Collider* Src, Collider* Dest, float DeltaTime);
	void LineHit(Collider* Src, Collider* Dest, float DeltaTime);
	void CoinHit(Collider* Src, Collider* Dest, float DeltaTime);
	void ItemBoxHit(Collider* Src, Collider* Dest, float DeltaTime);
	void TearHit(Collider* Src, Collider* Dest, float DeltaTime);
	void AncientHit(Collider* Src, Collider* Dest, float DeltaTime);
	void JellyFishHit(Collider* Src, Collider* Dest, float DeltaTime);
	void LemuiranHit(Collider* Src, Collider* Dest, float DeltaTime);
	void WispHit(Collider* Src, Collider* Dest, float DeltaTime);
	void RockHit(Collider* Src, Collider* Dest, float DeltaTime);
	void ColocussKickHit(Collider* Src, Collider* Dest, float DeltaTime);
	void ColocussClapHit(Collider* Src, Collider* Dest, float DeltaTime);
	void ItemHit(Collider* Src, Collider* Dest, float DeltaTime);

	void PlayerMove(float DeltaTime);

	void DirCheck();
	void HpCheck(float DeltaTime);
	void RopeCheck();
	void LevelUpCheck();

	void SetMoney(int Value) { pMoney = Value; }
	static int GetMoney() { return pMoney; }
	void SetExp(int Value) { Exp = Value; }
	void AddExp(int Value) { Exp += Value; }
	void SetHp(int Value) { Hp = Value; }
	static int GetHp() { return Hp; }
	void AddHp(int Value) { Hp += Value; }
	int GetHitCount() const { return HitCount; }
	void SetHitCount(int Value) { HitCount = Value; }

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

	static PLAYER_STATE GetPlayerState() { return pState; }
	static bool GetIsBooster() { return isBooster; }

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
	static bool isBooster;

	int AttackDamege;
	int HitCount;

	float SkillOneDelay;
	float SkillTwoDelay;
	float SkillThreeDelay;
	float SkillFourDelay;

	float InfinityTime;
	bool isInfinity;

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
	list<Vector2> HitSizeList;
	Vector2 PrevPos;
	list<ItemBase*> myItemList;
	static PLAYER_STATE pState;
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
	float HpTimeVar;
	Number* CountNumber;

public:
	friend class Object;
	friend class CommandoUI;
};

