#pragma once
#include "SceneComponent.h"
class Commando;
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

	static bool GetStageOneBoss() { return isStageOneBoss; }
	static void SetStageOneBoss(bool Value) { isStageOneBoss = Value; }

private:
	MainScene();
	~MainScene();

	float DebugTimeVar;
	float TimeVar;
	static bool isStageOneBoss;
};

