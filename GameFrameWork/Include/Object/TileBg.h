#pragma once
#include "Object.h"
class TileBg : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	TileBg* Clone() override;

	void SetWorldSize(const Vector2& _Size) { m_WorldSize = _Size; }
	void SetWorldSize(float x, float y) { m_WorldSize = Vector2(x, y); }

private:
	Vector2 m_WorldSize;
	Vector2 CameraPos;

protected:
	TileBg();
	TileBg(const TileBg& Value);
	~TileBg();
};

