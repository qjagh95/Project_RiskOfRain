#pragma once
#include "Object.h"
class Bullet :	public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	Bullet* Clone() override;

	void SetDeleteDistance(float Value) { DeleteDistance = Value; }
	void SetTarget(Object* Value)
	{
		SAFE_RELEASE(Target);

		if (Value != NULL)
			Value->AddRefCount();

		Target = Value;
	}

protected:
	Bullet();
	Bullet(const Bullet& Value);
	~Bullet();

private:
	float DeleteDistance;
	Object* Target;
};

