#include "MenuScene.h"
#include "Scene.h"
#include "Layer.h"
#include "../Object/Commando.h"
#include "../Object/BackGround.h"
#include "../Object/BaseAttackBullet.h"
#include "../Button.h"
#include "../Camera.h"
#include "../Core.h"
#include "SceneManager.h"
#include "MainScene.h"
#include "EditScene.h"
#include "../Object/MenuBg.h"
#include "../Object/MenuStarBg.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

bool MenuScene::Init()
{
	Vector2 WinSize = Core::Get()->GetWinSizeVector2();
	Camera::Get()->SetWorldSize(1800.0f, 1000.0f);

	Layer* DefaultLayer = m_Scene->FindLayer("Default");
	Layer* BackLayer = m_Scene->FindLayer("BackGround");
	Layer* UiLayer = m_Scene->FindLayer("UI");

	MenuBg* newBG = Object::CreateObject<MenuBg>("MenuBg", BackLayer);
	MenuStarBg* newBG2 = Object::CreateObject<MenuStarBg>("StarBackGround", BackLayer);

	Button* StartButton = Object::CreateObject<Button>("StartButton",UiLayer);
	StartButton->SetPos(WinSize.x / 2.0f - 100.0f, WinSize.y / 2.0f - 50.0f);
	StartButton->SetCallBack<MenuScene>(&MenuScene::StartButtonColl, this);
	StartButton->SetTexture("StartButton", TEXT("Window/StartButton.bmp"));
	StartButton->SetSize(200.0f, 26.0f);
	StartButton->SetIsOffset(false);
	SAFE_RELEASE(StartButton);

	StartButton = Object::CreateObject<Button>("EditButton", UiLayer);
	StartButton->SetPos(WinSize.x / 2.0f - 100.0f, WinSize.y / 2.0f);
	StartButton->SetCallBack<MenuScene>(&MenuScene::EditButtonColl, this);
	StartButton->SetTexture("EditButton", TEXT("Window/EditorButton.bmp"));
	StartButton->SetSize(200.0f, 26.0f);
	StartButton->SetIsOffset(false);
	SAFE_RELEASE(StartButton);

	StartButton = Object::CreateObject<Button>("ExitButton", UiLayer);
	StartButton->SetPos(WinSize.x / 2.0f - 100.0f, WinSize.y / 2.0f + 50.0f);
	StartButton->SetCallBack<MenuScene>(&MenuScene::ExitButtonColl, this);
	StartButton->SetTexture("ExitButton", TEXT("Window/ExitButton.bmp"));
	StartButton->SetSize(200.0f, 26.0f);
	StartButton->SetIsOffset(false);
	SAFE_RELEASE(StartButton);

	SAFE_RELEASE(DefaultLayer);
	SAFE_RELEASE(UiLayer);
	SAFE_RELEASE(BackLayer);
	SAFE_RELEASE(newBG);
	SAFE_RELEASE(newBG2);
	return true;
}

int MenuScene::Input(float DeltaTime)
{
	return 0;
}

int MenuScene::Update(float DeltaTime)
{
	return 0;
}

int MenuScene::LateUpdate(float DeltaTime)
{
	return 0;
}

void MenuScene::Collision(float DeltaTime)
{
}

void MenuScene::Render(HDC hDC, float DeltaTime)
{
}

void MenuScene::StartButtonColl(float DeltaTime)
{
	SceneManager::Get()->CreateNextScene<MainScene>("MainScene");
}

void MenuScene::EditButtonColl(float DeltaTime)
{
	SceneManager::Get()->CreateNextScene<EditScene>("EditScene");
}

void MenuScene::ExitButtonColl(float DeltaTimes)
{
	DestroyWindow(Core::Get()->GetHwnd());
}
