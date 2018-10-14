#include "MainScene.h"
#include "Layer.h"
#include "Scene.h"

#include "../stdafx.h"
#include "../Camera.h"
#include "../Debug.h"

#include "../Scene/EditScene.h"

#include "../Resource/PathManager.h"

#include "../Object/BackGround.h"
#include "../Object/Object.h"
#include "../Object/Player.h"
#include "../Object/Bullet.h"
#include "../Object/Monster.h"
#include "../Object/TargetBullet.h"
#include "../Object/FollowBullet.h"
#include "../Object/Effect.h"

#include "../Object/Number.h"
#include "../Object/Bar.h"

#include "../Object/TileInfo.h"
#include "../Object/TileBg.h"

#include "../Object/ItemBox.h"
#include "../Object/Pump.h"
#include "../Object/Rope.h"
#include "../Object/TelePoter.h"

#include "../Sound/SoundManager.h"

#include "../StageManager.h"

MainScene::MainScene() : TimeVar(0.0f)
{
}
MainScene::~MainScene()
{
	SAFE_RELEASE(m_UiNumber);
	SAFE_RELEASE(m_Number);

	SAFE_RELEASE(m_Bar);
	SAFE_RELEASE(m_UiBar);
}

bool MainScene::Init()
{
	Camera::Get()->SetWorldSize(Vector2(6200.0f, 3000.0f));

	SoundManager::Get()->LoadSound("BGM", true, TEXT("MainBgm.mp3"));
	SoundManager::Get()->LoadSound("1Up", false, TEXT("1Up.wav"));
	SoundManager::Get()->LoadSound("Stun", false, TEXT("Stun.wav"));

	SoundManager::Get()->Play("BGM", true);

	Layer* BackLayer = m_Scene->FindLayer("BackGround");
	Layer* TileLayer = m_Scene->FindLayer("TileLayer");
	Layer* newLayer = m_Scene->FindLayer("PlayLayer");
	Layer* UiLayer = m_Scene->FindLayer("UI");

	TileBg* Bg = Object::CreateObject<TileBg>("Bg", BackLayer);
	Bg->SetIsCameraMode(false);

	TileInfo* Stage1TileInfo = Object::CreateObject<TileInfo>("BackGround", TileLayer);
	Stage1TileInfo->LoadFile("123.stg", newLayer);
	Stage1TileInfo->SetIsGrid(false);
	StageManager::Get()->SetStageInfo(Stage1TileInfo);
	StageManager::LoadMonsterList(L"123.stgmon", newLayer);

	Player* newPlayer = Object::CreateObject<Player>("Players", newLayer);
	Camera::Get()->SetTarget(newPlayer);
	Camera::Get()->SetTargetPivot(0.5f, 0.5f);


	Bullet* pBullet1 = Object::CreatePrototype<Bullet>("Bullet", m_Scene);
	FollowBullet* pBullet2 = Object::CreatePrototype<FollowBullet>("FollowBullet", m_Scene);
	TargetBullet* pBullet5 = Object::CreatePrototype<TargetBullet>("TargetBullet", m_Scene);

	Effect* pEffect = Object::CreatePrototype<Effect>("BomeEffect", m_Scene);
	pEffect->SetPivot(0.0f, 1.0f);
	pEffect->SetSize(100.0f, 200.0f);
	pEffect->SetColorKey(RGB(255, 0, 255));
	pEffect->AddAnimationClip("BombEffect", AT_ATLAS, AO_ONCE_DESTROY, 100.0f, 200.0f, 23, 1, 23, 1, 0, 0, 1.0f, "BombEffect", TEXT("player_bomb.bmp"));

	Effect* bEffect = Object::CreatePrototype<Effect>("BuffEffect", m_Scene);
	bEffect->SetPivot(0.5f, 0.5f);
	bEffect->SetSize(100.0f, 200.0f);
	bEffect->SetColorKey(RGB(255, 0, 255));
	bEffect->AddAnimationClip("BuffEffect", AT_ATLAS, AO_LOOP, 100.0f, 200.0f, 23, 1, 23, 1, 0, 0, 1.0f, "BuffEffect", TEXT("player_bomb.bmp"));

	m_UiNumber = Object::CreateObject<Number>("Number", UiLayer);
	m_UiNumber->SetPos(1280, 50.f);
	m_UiNumber->SetTexture("Number", TEXT("Number.bmp"));
	m_UiNumber->SetNumber(1000);
	m_UiNumber->SetNumberSize(62.6f, 88.f);
	m_UiNumber->SetColorKey(RGB(255,255,255));
	m_UiNumber->SetIsCameraMode(false);

	m_Number = Object::CreateObject<Number>("Number", UiLayer);
	m_Number->SetPos(1280, 600.f);
	m_Number->SetTexture("Number", TEXT("Number.bmp"));
	m_Number->SetNumber(123);
	m_Number->SetNumberSize(62.6f, 88.f);
	m_Number->SetColorKey(RGB(255,255,255));

	m_Bar = Object::CreateObject<Bar>("Bar", UiLayer);
	m_Bar->SetSize(100.f, 40.f);
	m_Bar->SetPos(50.f, 600.f);
	m_Bar->SetTexture("MPBar", TEXT("MPBar.bmp"));
	m_Bar->SetBarInfo(0, 5000, 5000);

	m_UiBar = Object::CreateObject<Bar>("Bar", UiLayer);
	m_UiBar->SetSize(100.f, 40.f);
	m_UiBar->SetPos(150.f, 50.f);
	m_UiBar->SetTexture("HPBar", TEXT("HPBar.bmp"));
	m_UiBar->SetBarInfo(0, 5000, 5000);
	m_UiBar->SetIsCameraMode(false);

	SAFE_RELEASE(UiLayer);
	SAFE_RELEASE(bEffect);
	SAFE_RELEASE(pEffect);
	SAFE_RELEASE(BackLayer);
	SAFE_RELEASE(newPlayer);
	SAFE_RELEASE(pBullet1);
	SAFE_RELEASE(pBullet2);
	SAFE_RELEASE(pBullet5);
	SAFE_RELEASE(newLayer);
	SAFE_RELEASE(Stage1TileInfo);
	SAFE_RELEASE(Bg);

	return true;
}

int MainScene::Input(float DeltaTime)
{
	if (GetAsyncKeyState(VK_NUMPAD0) & 0x8000)
		m_Number->AddNumber(1);

	if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
		m_Number->Move(Vector2(300.0f, 0.0f), DeltaTime);

	if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
		m_UiBar->AddValue(-50);

	if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000)
		m_UiBar->AddValue(50);

	return 0;
}

int MainScene::Update(float DeltaTime)
{
	return 0;
}

int MainScene::LateUpdate(float DeltaTime)
{
	return 0;
}

void MainScene::Collision(float DeltaTime)
{
}

void MainScene::Render(HDC hdc, float DeltaTime)
{
	if (Core::Get()->GetIsDebugMode() == false)
		return;

	TimeVar += DeltaTime;

	if (TimeVar >= 1.0f)
	{
		char Buffer[255] = {};
		sprintf_s(Buffer, "AllObjectCount : %d \n", m_Scene->GetObjectCount());
		Debug::OutputConsole(Buffer);

		TimeVar = 0.0f;
	}
}

void MainScene::LoadMonster()
{
	const char* pPath = PathManager::Get()->FindPathMultiByte(DATA_PATH);

	string FullPath;

	if (pPath != NULL)
		FullPath = pPath;

	FullPath += "123.stgmon";

	FILE* pFile = NULL;

	fopen_s(&pFile, FullPath.c_str(), "rb");
	{
		size_t ObjSize;
		fread(&ObjSize, sizeof(size_t), 1, pFile);

		for (size_t i = 0; i < ObjSize; i++)
		{
			ObjectSave Loader;
			fread(&Loader, sizeof(ObjectSave), 1, pFile);

			switch (Loader.m_mType)
			{
				case MT_MONSTERONE:
				{
					Monster* newMonster = Object::CreateObject<Monster>("Monster", m_Scene->FindLayer("PlayLayer"));
					newMonster->SetPos(Loader.Pos);
					SAFE_RELEASE(newMonster);
				}
					break;
				case MT_MONSTERTWO:
					break;
				case MT_MONSTERTHREE:
					break;
				case MT_MONSTERFOUR:
					break;
				case MT_MONSTERFIVE:
					break;
				case MT_MONSTERSIX:
					break;
				case MT_MONSTERSEVEN:
					break;
				case MT_MONSTEREIGHT:
					break;
				case MT_MONSTERNINE:
					break;
				case MT_MONSTERTEN:
					break;
			}//switch
		}//for
	}//fopen_s

	fclose(pFile);
}
