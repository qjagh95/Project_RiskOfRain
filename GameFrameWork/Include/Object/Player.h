#pragma once
#include "Charactor.h"
#include "../stdafx.h"
class Tile;
class Collider;
class Bullet;
class FollowBullet;
class Effect;
class Bar;
class Player : public Charactor
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	Player* Clone() override;
	void TileCollsionActive(float DeltaTime) override;

	void BulletHit(Collider* Src, Collider* Dest, float DeltaTime);
	void PlayerMove(float DeltaTime);

	void DirCheck();

	void SetMoney(int Value) { pMoney = Value; }
	static int GetMoney() { return pMoney; }
	void SetExp(int Value) { Exp = Value; }

	///-------------FSMÇÔ¼ö-------------
	void FS_Idle(float DeltaTime);
	void FS_Move(float DeltaTime);
	void FS_Jump(float DeltaTime);
	void FS_BaseAttack(float DeltaTime);
	void FS_Skill1(float DeltaTime);
	void FS_Skill2(float DeltaTime);
	void FS_Skill3(float DeltaTime);
	void FS_Skill4(float DeltaTime);
	void FS_Rope(float DeltaTime);
	///---------------------------------

	void SelectState(PLAYER_STATE eState);

protected:
	Player();
	Player(const Player& Value) : Charactor(Value) {}
	~Player();

private:
	Vector2 LeftTop;

	static int pMoney;
	int Exp;

	bool isDown;
	bool isJumping;
	float JumpPower;

	Object* CurTarget;

	Vector2	CameraPos;
	Vector2 Center;

	Vector2 LineEnd;

	PLAYER_STATE pState;
	float MoveDir;
	string Dir;
	string AnimationName[PS_MAX];
	string StateName;

	Bar* HpBar;
	Bar* ExpBar;
};

