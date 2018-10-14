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

#include "../Object/CoinUI.h"
#include "../Object/DollerUI.h"
#include "../Object/CommandoUI.h"
#include "../Object/TimeUI.h"

#include "../Sound/SoundManager.h"

#include "../StageManager.h"

Number* MainScene::m_Second = NULL;
Number* MainScene::m_Minit = NULL;

MainScene::MainScene()
	: TimeVar(0.0f), DebugTimeVar(0.0f),
	 PlaySecond(0), PlayMinit(0)
{
}
MainScene::~MainScene()
{
	SAFE_RELEASE(m_Second);
	SAFE_RELEASE(m_Minit);

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
	SAFE_RELEASE(Bg);

	CoinUI* newCoin = Object::CreateObject<CoinUI>("CoinUI", UiLayer);
	SAFE_RELEASE(newCoin);
	DollerUI* newDoller = Object::CreateObject<DollerUI>("DollerUI", UiLayer);
	SAFE_RELEASE(newDoller);
	CommandoUI* newCommando = Object::CreateObject<CommandoUI>("CommandoUI", UiLayer);
	SAFE_RELEASE(newCommando);
	TimeUI* newTime = Object::CreateObject<TimeUI>("TimeUI", UiLayer);
	SAFE_RELEASE(newTime);

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
	SAFE_RELEASE(pEffect);

	Effect* bEffect = Object::CreatePrototype<Effect>("BuffEffect", m_Scene);
	bEffect->SetPivot(0.5f, 0.5f);
	bEffect->SetSize(100.0f, 200.0f);
	bEffect->SetColorKey(RGB(255, 0, 255));
	bEffect->AddAnimationClip("BuffEffect", AT_ATLAS, AO_LOOP, 100.0f, 200.0f, 23, 1, 23, 1, 0, 0, 1.0f, "BuffEffect", TEXT("player_bomb.bmp"));
	SAFE_RELEASE(bEffect);

	m_Second = Object::CreateObject<Number>("NumberSecond", UiLayer);
	m_Second->SetPos(1490 - 1000.0f, 70.0f); //TODO : -1000
	m_Second->SetTexture("NumberSecond", TEXT("object/TempNumber.bmp"));
	m_Second->SetNumber(PlaySecond);
	m_Second->SetNumberSize(19.0f, 24.0f);
	m_Second->SetColorKey(RGB(255, 0, 255));
	m_Second->SetIsCameraMode(false);

	m_Minit = Object::CreateObject<Number>("Number", UiLayer);
	m_Minit->SetPos(1430 - 1000.0f, 70.0f); //TODO : -1000
	m_Minit->SetTexture("NumberMinit", TEXT("object/TempNumber.bmp"));
	m_Minit->SetNumber(PlayMinit);
	m_Minit->SetNumberSize(19.0f, 24.0f);
	m_Minit->SetColorKey(RGB(255, 0, 255));
	m_Minit->SetIsCameraMode(false);

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
	SAFE_RELEASE(BackLayer);
	SAFE_RELEASE(newPlayer);
	SAFE_RELEASE(pBullet1);
	SAFE_RELEASE(pBullet2);
	SAFE_RELEASE(pBullet5);
	SAFE_RELEASE(newLayer);
	SAFE_RELEASE(Stage1TileInfo);

	return true;
}

int MainScene::Input(float DeltaTime)
{
	if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
		m_UiBar->AddValue(-50);

	if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000)
		m_UiBar->AddValue(50);

	return 0;
}

int MainScene::Update(float DeltaTime)
{
	TimeVar += DeltaTime;

	if (TimeVar >= 1.0f)
	{
		PlaySecond++;
		TimeVar = 0.0f;
	}

	if (PlaySecond == 15)
	{
		PlaySecond = 0;
		PlayMinit++;
	}
	if (PlayMinit == 60)
		PlayMinit = 0;

	m_Second->SetNumber(PlaySecond);
	m_Minit->SetNumber(PlayMinit);

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
		sprintf_s(Buffer, "AllObjectCount : %d \n", m_Scene->GetObjectCount());
		Debug::OutputConsole(Buffer);

		DebugTimeVar = 0.0f;
	}
}
