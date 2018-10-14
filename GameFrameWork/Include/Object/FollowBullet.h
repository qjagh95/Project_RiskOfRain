#pragma once
#include "Object.h"
class FollowBullet : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	FollowBullet* Clone() override;

	void SetTarget(Object* Value)
	{
		SAFE_RELEASE(Target);

		if (Value != NULL)
			Value->AddRefCount();

		Target = Value;
	}
	void SetDeleteDistance(float Value) { DeleteDistance = Value; }

protected:
	FollowBullet();
	FollowBullet(const FollowBullet& Value);
	~FollowBullet();

private:
	Vector2 LeftTop;
	float DeleteDistance;
	Object* Target;

	float TimeVar;
};

