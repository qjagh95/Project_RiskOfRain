#pragma once

enum COLOSSUS_STATE
{
	CS_MOVE,
	CS_KICK,
	CS_CLAP,
	CS_MAX,
};

#include "Monster.h"
class Bar;
class Number;
class BossBarEdge;
class Colossus : public Monster
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
	Colossus* Clone() override;
	void TileCollsionActive(float DeltaTime) override;

	void RangeCheck();

	void FS_MOVE(float DeltaTime);
	void FS_CLAP(float DeltaTime);
	void FS_KICK(float DeltaTime);

	void SetKickDamege(int Value) { KickDamege = Value; }
	int GetKickDamege() const { return KickDamege; }
	void SetClapDamege(int Value) { ClapDamege = Value; }
	int GetClapDamege() const {return ClapDamege;}

private:
	int KickDamege;
	int ClapDamege;
	int PrevFrame;

	float KickRange;
	float ClapRange;

	float SerchRange;

	Number* HpNumber;
	Bar* BossHpBar;
	BossBarEdge* newEdge;

	string AnimationName[CS_MAX];

protected:
	Colossus();
	Colossus(const Colossus& Value);
	~Colossus();
};

