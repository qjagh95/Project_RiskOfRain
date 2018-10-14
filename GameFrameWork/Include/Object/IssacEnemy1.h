#pragma once
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
	void Render(HDC Hdc, float DeltaTime) override;
	IssacEnemy1* Clone() override;
	void TileCollsionActive(float DeltaTime) override;

protected:
	IssacEnemy1();
	IssacEnemy1(const IssacEnemy1& Value);
	~IssacEnemy1();

private:
	enum MONSTER_STATE
	{
		MS_MOVE,
		MS_TRACE,
		MS_ATTACK,
	};
};

