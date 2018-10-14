#pragma once
#include "Object.h"
class BaseEffect : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	BaseEffect* Clone() override;

	void SelectAnimationClip(float Dir);

protected:
	BaseEffect();
	BaseEffect(const BaseEffect& Value);
	~BaseEffect();
};

