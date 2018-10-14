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
#include "../Object/Commando.h"
#include "../Object/Bullet.h"
#include "../Object/Monster.h"
#include "../Object/Effect.h"

#include "../Object/Number.h"
#include "../Object/Bar.h"

#include "../Object/TileInfo.h"
#include "../Object/TileBg.h"

#include "../Object/ItemBox.h"
#include "../Object/Pump.h"
#include "../Object/Rope.h"
#include "../Object/TelePoter.h"

#include "../Object/CoinUI.h"
#include "../Object/DollerUI.h"
#include "../Object/CommandoUI.h"
#include "../Object/TimeUI.h"

#include "../Sound/SoundManager.h"

#include "../StageManager.h"


MainScene::MainScene()
	: TimeVar(0.0f), DebugTimeVar(0.0f)
{
}
MainScene::~MainScene()
{
}

bool MainScene::Init()
{
	Camera::Get()->SetWorldSize(Vector2(6200.0f, 3000.0f));

	SoundManager::Get()->LoadSound("BGM", true, TEXT("musicStage1.wav"));
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

	Bullet* pBullet1 = Object::CreatePrototype<Bullet>("Bullet", m_Scene);

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

	Commando* newPlayer = Object::CreateObject<Commando>("Players", newLayer);
	Camera::Get()->SetTarget(newPlayer);
	Camera::Get()->SetTargetPivot(0.5f, 0.5f);

	CoinUI* newCoin = Object::CreateObject<CoinUI>("CoinUI", UiLayer);
	DollerUI* newDoller = Object::CreateObject<DollerUI>("DollerUI", UiLayer);
	CommandoUI* newCommando = Object::CreateObject<CommandoUI>("CommandoUI", UiLayer);
	TimeUI* newTime = Object::CreateObject<TimeUI>("TimeUI", UiLayer);

	SAFE_RELEASE(pEffect);
	SAFE_RELEASE(bEffect);
	SAFE_RELEASE(newCoin);
	SAFE_RELEASE(newDoller);
	SAFE_RELEASE(newCommando);
	SAFE_RELEASE(newTime);
	SAFE_RELEASE(Bg);
	SAFE_RELEASE(TileLayer);
	SAFE_RELEASE(UiLayer);
	SAFE_RELEASE(BackLayer);
	SAFE_RELEASE(newLayer);
	SAFE_RELEASE(newPlayer);
	SAFE_RELEASE(pBullet1);
	SAFE_RELEASE(Stage1TileInfo);

	return true;
}

int MainScene::Input(float DeltaTime)
{
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

	DebugTimeVar += DeltaTime;

	if (DebugTimeVar >= 1.0f)
	{
		char Buffer[255] = {};
		sprintf_s(Buffer, "All_ObjectCount : %d \n", m_Scene->GetObjectCount());
		Debug::OutputConsole(Buffer);

		DebugTimeVar = 0.0f;
	}
}
