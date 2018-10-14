#include "CommandoUI.h"

CommandoUI::CommandoUI()
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
}

bool CommandoUI::Init()
{
	SetTexture("CommandoUI", TEXT("UI/Commando.bmp"));
	SetSize(513.0f, 185.0f);
	SetPos(450.0f, 600 - 300.0f); //TODO : -300
	SetIsCameraMode(false);

	SetColorKey(RGB(255, 0, 255));

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

