#pragma once
#include "SceneComponent.h"
class Commando;
class Object;
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
	static void SetSommonMode(bool Value) { SommonMode = Value; }
	static bool GetSommonMode() { return SommonMode; }

private:
	MainScene();
	~MainScene();

	float SummonTime;
	float DebugTimeVar;
	float TimeVar;
	static bool isStageOneBoss;
	static bool SommonMode;
	
	Object* Target;
};

