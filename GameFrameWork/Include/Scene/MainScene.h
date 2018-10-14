#pragma once
#include "SceneComponent.h"
class Number;
class Bar;
class MainScene : public SceneComponent
{
public:
	friend class Scene;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC hdc, float DeltaTime) override;

	void LoadMonster();

private:
	MainScene();
	~MainScene();

	Number* m_Number;
	Number* m_UiNumber;

	Bar* m_Bar;
	Bar* m_UiBar;

	float TimeVar;
};

