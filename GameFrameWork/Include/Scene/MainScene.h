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

private:
	MainScene();
	~MainScene();

	static Number* m_Second;
	static Number* m_Minit;

	int PlaySecond;
	int PlayMinit;

	Bar* m_Bar;
	Bar* m_UiBar;

	float DebugTimeVar;
	float TimeVar;
};

