#pragma once
#include "SceneComponent.h"

class MenuScene : public SceneComponent
{
	friend class Scene;

public:
	bool Init();
	int Input(float DeltaTime);
	int Update(float DeltaTime);
	int LateUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void Render(HDC hDC, float DeltaTime);

	void StartButtonColl(float DeltaTime);
	void EditButtonColl(float DeltaTime);
	void ExitButtonColl(float DeltaTime);

private:
	MenuScene();
	~MenuScene();
};

