#pragma once
enum ISSAC1_MONSTER_STATE
{
	IMS_MOVE,
	IMS_ATTACK,
	IMS_TRACE,
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
	void Render(HDC Hdc, float DeltaTime) override;
	IssacEnemy1* Clone() override;
	void TileCollsionActive(float DeltaTime) override;

	void SelectState(ISSAC1_MONSTER_STATE mState);

	void FS_MOVE(float DeltaTime);
	void FS_TRACE(float DeltaTime);
	void FS_ATTACK(float DeltaTime);

private:
	ISSAC1_MONSTER_STATE mState;
	float TraceRange;
	string AnimationName[IMS_MAX];

protected:
	IssacEnemy1();
	IssacEnemy1(const IssacEnemy1& Value);
	~IssacEnemy1();
};

