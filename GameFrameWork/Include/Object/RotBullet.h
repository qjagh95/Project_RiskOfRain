#pragma once
#include "Object.h"
class RotBullet : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	RotBullet* Clone() override;

	void SetDeleteDistance(float Value) { DeleteDistance = Value; }

	void SettingPos(float x, float y) { m_Pos.x = x, m_Pos.y = y, CenterPos = m_Pos; }
	void SettingPos(const Vector2& Value) { m_Pos = Value, CenterPos = Value; }

protected:
	RotBullet();
	RotBullet(const RotBullet& Value);
	~RotBullet();

private:
	Vector2 LeftTop;
	Vector2 CenterPos;
	float RotAngle;
	float RotRange;
	float DeleteDistance;

};

