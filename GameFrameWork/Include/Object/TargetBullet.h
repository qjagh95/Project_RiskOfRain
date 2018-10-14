#pragma once
#include "Object.h"
class TargetBullet : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	TargetBullet* Clone() override;

	void SetDeleteDistance(float Value) { DeleteDistance = Value; }
	void SetTarget(Object* Value)
	{
		SAFE_RELEASE(Target);

		if (Value != NULL)
			Value->AddRefCount();

		Target = Value;
	}

	bool GetIsRush() const { return isRush; }

protected:
	TargetBullet();
	TargetBullet(const TargetBullet& Value);
	~TargetBullet();

private:
	float DeleteDistance;
	float Distance;
	bool isRush;
	Vector2 LeftTop;
	Object* Target;
};

