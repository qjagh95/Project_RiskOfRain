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
#include "../Object/BaseAttackBullet.h"
#include "../Object/Monster.h"
#include "../Object/Effect.h"
#include "../Object/DieEffect.h"
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
#include "../Object/Colossus.h"
#include "../Object/BaseAttackBullet.h"
#include "../Object/LaserBullet.h"
#include "../Object/BaseEffect.h"
#include "../Object/LaserEffect.h"
#include "../Object/ExpEffect.h"
#include "../Object/LevelUpEffect.h"
#include "../Object/AncientEffect.h"
#include "../Object/IssacTear.h"
#include "../Object/Coin.h"
#include "../Object/ExpCoin.h"
#include "../Object/MoneyCoin.h"
#include "../Sound/SoundManager.h"
#include "../StageManager.h"
#include "../Object/Monster.h"

bool MainScene::isStageOneBoss = false;
bool MainScene::SommonMode = true;

MainScene::MainScene()
	: TimeVar(0.0f), DebugTimeVar(0.0f), SummonTime(0.0f), Target(NULL)
{
}
MainScene::~MainScene()
{
	SAFE_RELEASE(Target);
}

bool MainScene::Init()
{
	Camera::Get()->SetWorldSize(Vector2(6200.0f, 3000.0f));

	SoundManager::Get()->LoadSound("BGM", true, TEXT("musicStage1.wav"));
	SoundManager::Get()->LoadSound("DNF", true, TEXT("bgm_Dnf.wav"));
	SoundManager::Get()->LoadSound("CommandoShow", false, TEXT("teleporter_receive.wav"));
	SoundManager::Get()->LoadSound("LevelUp", false, TEXT("LevelUp.wav"));

	SoundManager::Get()->LoadSound("Die", false, TEXT("your_team_lost.wav"));
	SoundManager::Get()->LoadSound("Win", false, TEXT("your_team_won.wav"));

	SoundManager::Get()->LoadSound("Miss", false, TEXT("Miss.mp3"));
	SoundManager::Get()->LoadSound("Recive", false, TEXT("teleporter_send.wav"));

	SoundManager::Get()->LoadSound("BoxOpen", false, TEXT("recharged.wav"));
	
	SoundManager::Get()->LoadSound("SkillOne", false, TEXT("Skill1.mp3"));
	SoundManager::Get()->LoadSound("SkillTwo", false, TEXT("Skill2.mp3"));
	SoundManager::Get()->LoadSound("SkillFour", false, TEXT("Skill4.mp3"));

	SoundManager::Get()->Play("BGM", true);
	SoundManager::Get()->Play("CommandoShow", false);

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

	BaseAttackBullet* baseBullet = Object::CreatePrototype<BaseAttackBullet>("BaseAttackBullet", m_Scene);
	LaserBullet* laserBullet = Object::CreatePrototype<LaserBullet>("LaserBullet", m_Scene);
	BaseEffect* baseEffect = Object::CreatePrototype<BaseEffect>("BaseEffect", m_Scene);
	LaserEffect* laserEffect = Object::CreatePrototype<LaserEffect>("LaserEffect", m_Scene);
	DieEffect* dieEffect = Object::CreatePrototype<DieEffect>("DieEffect", m_Scene);
	LevelUpEffect* levelUpEffect = Object::CreatePrototype<LevelUpEffect>("LevelUpEffect", m_Scene);
	ExpEffect* expEffect = Object::CreatePrototype<ExpEffect>("ExpEffect", m_Scene);
	AncientEffect* ancientEffect = Object::CreatePrototype<AncientEffect>("AncientEffect", m_Scene);
	
	IssacTear* issacTear = Object::CreatePrototype<IssacTear>("Tear", m_Scene);

	Commando* newPlayer = Object::CreateObject<Commando>("Commando", newLayer);
	Camera::Get()->SetTarget(newPlayer);
	Camera::Get()->SetTargetPivot(0.5f, 0.5f);

	Target = newPlayer;

	MoneyCoin* moneyCoin = Object::CreatePrototype<MoneyCoin>("MoneyCoin", m_Scene);
	moneyCoin->SetTarget(newPlayer);
	ExpCoin* expCoin = Object::CreatePrototype<ExpCoin>("ExpCoin", m_Scene);
	expCoin->SetTarget(newPlayer);

	CoinUI* newCoin = Object::CreateObject<CoinUI>("CoinUI", UiLayer);
	DollerUI* newDoller = Object::CreateObject<DollerUI>("DollerUI", UiLayer);
	CommandoUI* newCommando = Object::CreateObject<CommandoUI>("CommandoUI", UiLayer);
	TimeUI* newTime = Object::CreateObject<TimeUI>("TimeUI", UiLayer);

	SAFE_RELEASE(ancientEffect);
	SAFE_RELEASE(issacTear);
	SAFE_RELEASE(expEffect);
	SAFE_RELEASE(levelUpEffect);
	SAFE_RELEASE(moneyCoin);
	SAFE_RELEASE(expCoin);
	SAFE_RELEASE(baseEffect);
	SAFE_RELEASE(dieEffect);
	SAFE_RELEASE(laserEffect);
	SAFE_RELEASE(newPlayer);
	SAFE_RELEASE(newCoin);
	SAFE_RELEASE(newDoller);
	SAFE_RELEASE(newCommando);
	SAFE_RELEASE(newTime);
	SAFE_RELEASE(Bg);
	SAFE_RELEASE(TileLayer);
	SAFE_RELEASE(UiLayer);
	SAFE_RELEASE(BackLayer);
	SAFE_RELEASE(newLayer);
	SAFE_RELEASE(baseBullet);
	SAFE_RELEASE(laserBullet);
	SAFE_RELEASE(Stage1TileInfo);

	return true;
}

int MainScene::Input(float DeltaTime)
{
	return 0;
}

int MainScene::Update(float DeltaTime)
{
	SummonTime += DeltaTime;

	if (SummonTime >= 60.0f && SommonMode == true)
	{
		Layer* TempLayer = m_Scene->FindLayer("PlayLayer");
		StageManager::Get()->LoadMonsterListSecond(L"123.stgmon", TempLayer, Vector2(Camera::Get()->GetPos().x + Core::Get()->GetWinSizeVector2().x , Camera::Get()->GetPos().y + Core::Get()->GetWinSizeVector2().y));

		SAFE_RELEASE(TempLayer);
		SummonTime = 0.0f;
	}

	if (Monster::GetSceneMonsterCount() == 0 && SommonMode == false)
	{
		SoundManager::Get()->Play("Win");

		bool Check = false;
		SoundManager::Get()->GetisPlay("Win", &Check);
		if (Check == true)
		{
			SoundManager::Get()->Stop("DNF");
			MessageBox(NULL, L"�̱褻", L"Win", MB_OK);
		}
		DestroyWindow(Core::Get()->GetHwnd());
	}

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
		sprintf_s(Buffer, "StageMonsterCount : %d \n", Monster::GetSceneMonsterCount());
		Debug::OutputConsole(Buffer);

		DebugTimeVar = 0.0f;
	}
}
