#pragma once
#include "Object.h"
class Texture;
class Number;
class TimeUI : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	TimeUI* Clone() override;

private:
	Texture* DotTexture;
	Vector2 DotSize;
	Vector2 DotPos;

	Number* m_Second;
	Number* m_Minit;

	static int PlaySecond;
	static int PlayMinit;

	float TimeVar;

protected:
	TimeUI();
	TimeUI(const TimeUI& Value);
	~TimeUI();
};

