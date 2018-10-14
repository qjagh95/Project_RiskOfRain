#include "CommandoUI.h"
#include "../Scene/Layer.h"

#include "../Object/Commando.h"
#include "../Object/Number.h"

#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"

CommandoUI::CommandoUI()
	:PerTexture(NULL), HpNumber(NULL), MaxHpNumber(NULL), LevelNumber(NULL)
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
	SAFE_RELEASE(PerTexture);
	SAFE_RELEASE(HpNumber);
	SAFE_RELEASE(MaxHpNumber);
	SAFE_RELEASE(LevelNumber);
}

bool CommandoUI::Init()
{
	PerTexture = ResourceManager::Get()->LoadTexture("Per", TEXT("object/Per.bmp"));
	PerPos = Vector2(695.0f, 726.0f);
	PerSize = Vector2(10.0f, 24.0f);

	Texture* BlackZero = ResourceManager::Get()->LoadTexture("ZeroBlack", TEXT("object/ZeroBlack.bmp"));

	SetTexture("CommandoUI", TEXT("UI/Commando.bmp"));
	SetSize(513.0f, 185.0f);
	SetPos(450.0f, 600.0f);
	SetIsCameraMode(false);
	SetColorKey(RGB(255, 0, 255));

	HpNumber = Object::CreateObject<Number>("HpNumber", m_Layer);
	HpNumber->SetPos(685.0f, 730.0f);
	HpNumber->SetTexture("HpNumber", TEXT("object/TempBlack.bmp"));
	HpNumber->SetNumberSize(19.0f, 24.0f);
	HpNumber->SetColorKey(RGB(255, 0, 255));
	HpNumber->SetNumberViewSize(13.0f, 15.0f);
	HpNumber->SetZeroViewSize(13.0f, 15.0f);
	HpNumber->SetZeroTexture(BlackZero);
	HpNumber->SetIsCameraMode(false);

	MaxHpNumber = Object::CreateObject<Number>("MaxHpNumber", m_Layer);
	MaxHpNumber->SetPos(770.0f, 730.0f);
	MaxHpNumber->SetTexture("MaxHpNumber", TEXT("object/TempBlack.bmp"));
	MaxHpNumber->SetNumberSize(19.0f, 24.0f);
	MaxHpNumber->SetColorKey(RGB(255, 0, 255));
	MaxHpNumber->SetNumberViewSize(13.0f, 15.0f);
	MaxHpNumber->SetZeroViewSize(13.0f, 15.0f);
	MaxHpNumber->SetZeroTexture(BlackZero);
	MaxHpNumber->SetIsCameraMode(false);

	LevelNumber = Object::CreateObject<Number>("LevelNumber", m_Layer);
	LevelNumber->SetPos(520.0f, 650.0f);
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

	HpNumber->SetNumber(Commando::Hp);
	MaxHpNumber->SetNumber(Commando::MaxHp);
	LevelNumber->SetNumber(Commando::Level);

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

	//PerÅØ½ºÃÄ
	TransparentBlt(Hdc, (int)PerPos.x, (int)PerPos.y, (int)PerSize.x, (int)PerSize.y, PerTexture->GetMemDC(), 0, 0, (int)PerSize.x, (int)PerSize.y, m_ColorKey);
}

CommandoUI * CommandoUI::Clone()
{
	return new CommandoUI(*this);
}

