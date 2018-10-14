#pragma once
#include "../stdafx.h"

class Scene;
class SceneManager
{
public:
	bool Init();
	int Input(float DeltaTime);
	int Update(float DeltaTime);
	int LateUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void CollsionAfterUpdate(float DeltaTime);
	void Render(HDC Hdc, float DeltaTime);

	Scene* CreateScene(const string& TagName);
	template<typename T>
	void CreateNextScene(const string& TagName)
	{
		SAFE_RELEASE(m_NextScene);

		m_NextScene = CreateScene(TagName);
		T* newComponent = m_NextScene->CreateSceneComponent<T>("strTag");
		
		SAFE_RELEASE(newComponent);
	}

private:
	int ChangeScene();

private:
	Scene* m_Scene;
	Scene* m_NextScene;

public:
	CLASS_IN_SINGLE(SceneManager)
};

