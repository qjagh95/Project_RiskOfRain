#pragma once
#include "../stdafx.h"
#include "Charactor.h"
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
	void SetTarget(Object* Value)
	{
		SAFE_RELEASE(Target);

		if (Target != NULL)
			Target->AddRefCount();

		Target = Value;
	}
	Monster* Clone() override;

	void BulletHit(Collider* Src, Collider* Dest, float DeltaTime);

protected:
	Monster();
	Monster(const Monster& Value);
	~Monster();

private:
	int MoveDir;
	float FireTime;
	float TraceRange;
	float AttackRange;

	MONSTER_STATE mState;

	Vector2 LineEnd;
	Object* Target;
};

