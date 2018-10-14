#pragma once
#include "Object.h"
class Texture;
class Number;
class CommandoUI : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	CommandoUI* Clone() override;

private:
	Texture* PerTexture;
	Vector2 PerPos;
	Vector2 PerSize;

	Number* HpNumber;
	Number* MaxHpNumber;
	Number* LevelNumber;

protected:
	CommandoUI();
	CommandoUI(const CommandoUI& Value);
	~CommandoUI();
};

