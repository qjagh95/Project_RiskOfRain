#include "SceneManager.h"
#include "Scene.h"
#include "MainScene.h"
#include "MenuScene.h"
#include "EditScene.h"

INIT_STATIC_VAR(SceneManager)

SceneManager::SceneManager() : m_Scene(NULL), m_NextScene(NULL)
{
}

SceneManager::~SceneManager()
{
	SAFE_RELEASE(m_Scene);
	SAFE_RELEASE(m_NextScene);
}

bool SceneManager::Init()
{
	m_Scene = CreateScene("EditScene");
	EditScene* newEditSceneCom = m_Scene->CreateSceneComponent<EditScene>("EditScene");

	m_Scene = CreateScene("MenuScene");
	MenuScene* newSceneCom = m_Scene->CreateSceneComponent<MenuScene>("MenuScene");

	SAFE_RELEASE(newEditSceneCom);
	SAFE_RELEASE(newSceneCom);

	return true;
}

int SceneManager::Input(float DeltaTime)
{
	m_Scene->Input(DeltaTime);

	return ChangeScene();
}

int SceneManager::Update(float DeltaTime)
{
	m_Scene->Update(DeltaTime);

	return ChangeScene();
}

int SceneManager::LateUpdate(float DeltaTime)
{
	m_Scene->LateUpdate(DeltaTime);

	return ChangeScene();
}

void SceneManager::Collision(float DeltaTime)
{
	m_Scene->Collision(DeltaTime);
}

void SceneManager::Render(HDC Hdc, float DeltaTime)
{
	m_Scene->Render(Hdc,DeltaTime);
}

Scene * SceneManager::CreateScene(const string & TagName)
{
	m_Scene = new Scene();
	m_Scene->SetTag(TagName);
	m_Scene->AddRefCount();

	if (m_Scene->Init() == false)
	{
		SAFE_RELEASE(m_Scene);
		return NULL;
	}
	return m_Scene;
}

int SceneManager::ChangeScene()
{
	if (m_NextScene != NULL)
	{
		SAFE_RELEASE(m_Scene);

		m_Scene = m_NextScene;
		m_NextScene = NULL;
		return 1;
	}

	return 0;
}
