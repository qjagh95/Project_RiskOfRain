#pragma once
#include "Object.h"
class LaserEffect : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	LaserEffect* Clone() override;

	void SelectAnimationClip(const string& ClipName);

protected:
	LaserEffect();
	LaserEffect(const LaserEffect& Value);
	~LaserEffect();
};

