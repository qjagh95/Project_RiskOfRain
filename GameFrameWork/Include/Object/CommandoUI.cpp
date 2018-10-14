#include "CommandoUI.h"
#include "../Scene/Layer.h"

#include "../Object/Commando.h"
#include "../Object/Number.h"

#include "../Object/Bar.h"
#include "../Object/Commando.h"

#include "../Object/PerTexture.h"

#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"

CommandoUI::CommandoUI()
	:HpNumber(NULL), MaxHpNumber(NULL), LevelNumber(NULL)
{
	m_ObjectType = OT_UI;
	SetTag("CommandoUI");
}

CommandoUI::CommandoUI(const CommandoUI & Value)
	:Object(Value)
{
}

CommandoUI::~CommandoUI()
{
	SAFE_RELEASE(HpNumber);
	SAFE_RELEASE(MaxHpNumber);
	SAFE_RELEASE(LevelNumber);

	SAFE_RELEASE(HpBar);
	SAFE_RELEASE(ExpBar);
	SAFE_RELEASE(Per);
}

bool CommandoUI::Init()
{
	Texture* BlackZero = ResourceManager::Get()->LoadTexture("ZeroBlack", TEXT("object/ZeroBlack.bmp"));

	SetTexture("CommandoUI", TEXT("UI/Commando.bmp"));
	SetSize(513.0f, 185.0f);
	SetPos(Core::Get()->GetWinSizeVector2().x / 2.0f - m_Size.GetHalfX(), Core::Get()->GetWinSizeVector2().y - m_Size.y);
	SetIsCameraMode(false);
	SetColorKey(RGB(255, 0, 255));

	HpBar = Object::CreateObject<Bar>("HpBar", m_Layer);
	HpBar->SetSize(Vector2(480.f, 21.f));
	HpBar->SetPos(660.0f, 945.0f);
	HpBar->SetTexture("HpBar", TEXT("pHpBar.bmp"));
	HpBar->SetBarInfo(0, Commando::MaxHp, Commando::Hp);
	HpBar->SetIsCameraMode(false);

	ExpBar = Object::CreateObject<Bar>("ExpBar", m_Layer);
	ExpBar->SetSize(Vector2(480.0f, 6.0f));
	ExpBar->SetPos(660.0f, 984.0f);
	ExpBar->SetTexture("HPBar", TEXT("ExpBar.bmp"));
	ExpBar->SetBarInfo(30, Commando::MaxExp, Commando::Exp);
	ExpBar->SetIsCameraMode(false);

	HpNumber = Object::CreateObject<Number>("HpNumber", m_Layer);
	HpNumber->SetPos(850.0f, 948.0f);
	HpNumber->SetTexture("HpNumber", TEXT("object/TempBlack.bmp"));
	HpNumber->SetNumberSize(19.0f, 24.0f);
	HpNumber->SetColorKey(RGB(255, 0, 255));
	HpNumber->SetNumberViewSize(13.0f, 15.0f);
	HpNumber->SetZeroViewSize(13.0f, 15.0f);
	HpNumber->SetZeroTexture(BlackZero);
	HpNumber->SetIsCameraMode(false);

	Per = Object::CreateObject<PerTexture>("Per", m_Layer);

	MaxHpNumber = Object::CreateObject<Number>("MaxHpNumber", m_Layer);
	MaxHpNumber->SetPos(1000.0f, 948.0f);
	MaxHpNumber->SetTexture("MaxHpNumber", TEXT("object/TempBlack.bmp"));
	MaxHpNumber->SetNumberSize(19.0f, 24.0f);
	MaxHpNumber->SetColorKey(RGB(255, 0, 255));
	MaxHpNumber->SetNumberViewSize(13.0f, 15.0f);
	MaxHpNumber->SetZeroViewSize(13.0f, 15.0f);
	MaxHpNumber->SetZeroTexture(BlackZero);
	MaxHpNumber->SetIsCameraMode(false);

	LevelNumber = Object::CreateObject<Number>("LevelNumber", m_Layer);
	LevelNumber->SetPos(710.0f, 865.0f);
	LevelNumber->SetTexture("LevelNumber", TEXT("object/TempNumber.bmp"));
	LevelNumber->SetNumberSize(19.0f, 24.0f);
	LevelNumber->SetColorKey(RGB(255, 0, 255));
	LevelNumber->SetNumberViewSize(30.0f, 30.0f);
	LevelNumber->SetIsCameraMode(false);

	SAFE_RELEASE(BlackZero);
	return true;
}

int CommandoUI::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int CommandoUI::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	Per->SetPos(HpNumber->GetLeftPosx().x + 60.0f , HpNumber->GetLeftPosx().y - 5.0f);

	HpNumber->SetNumber(Commando::Hp);
	MaxHpNumber->SetNumber(Commando::MaxHp);
	LevelNumber->SetNumber(Commando::Level);

	HpBar->SetBarInfo(0, Commando::MaxHp, Commando::Hp);
	ExpBar->SetBarInfo(30, Commando::MaxExp, Commando::Exp);

	return 0;
}

int CommandoUI::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void CommandoUI::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void CommandoUI::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

CommandoUI * CommandoUI::Clone()
{
	return new CommandoUI(*this);
}

