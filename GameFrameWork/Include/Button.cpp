#include "Button.h"
#include "Coll/ColliderRect.h"
#include "Input.h"
#include "Resource\Texture.h"

Button::Button()
{
	m_ButtonState = BS_NOMAL;
	m_isCallBack = false;
	m_isOffset = true;
}

Button::Button(const Button & ui)
	:UI(ui)
{

}

Button::~Button()
{
	SAFE_RELEASE(RC);
}

bool Button::Init()
{
	if (UI::Init() == false)
		return false;

	m_ButtonState = BS_NOMAL;
	m_isCallBack = false;

	// ��ư�� ������ �⺻ ũ�⸦ ����ְ� �簢�� �浹ü�� �������ش�.
	SetSize(200.f, 100.f);
	SetTexture("Button", TEXT("StartButton.bmp"));
	SetPivot(0.0f, 0.0f);
	SetColorKey(RGB(255, 0, 255));

	// �浹ü ����
	RC = AddCollider<ColliderRect>("ButtonBody");
	RC->SetVirtualRect(m_Size);
	RC->SetPivot(0.0f, 0.0f);
	RC->SetCollsionTypeName("Button");
	RC->SetCollsionGroupName("UI");
	RC->SetIsUI(true);
	RC->SetCallBack(this, &Button::OnCollsionFirst, CS_COLFIRST);
	RC->SetCallBack(this, &Button::OnCollsionDoing, CS_COLDOING);
	RC->SetCallBack(this, &Button::OnCollsionEnd, CS_COLEND);

	return true;
}

int Button::Input(float DeltaTime)
{
	UI::Input(DeltaTime);

	if (m_ButtonState == BS_NOMAL)
		return 0;

	//�븻�� �ƴҶ��� ���´� (�浹�Լ����� �ٲ���)
	if (KEYDOWN("LBotton"))
		m_ButtonState = BS_CLICK;
	//Ŭ���ϴ� ������ �Լ��� �����Ѵ�
	 if (KEYUP("LBotton"))
	{
		m_ButtonState = BS_OVER;

		if (m_ClickCallBack != NULL)
			m_ClickCallBack(DeltaTime);
	}
	else
		m_ButtonState = BS_OVER;

	return 0;
}

int Button::Update(float DeltaTime)
{
	UI::Update(DeltaTime);

	RC->SetVirtualRect(m_Size);

	if (m_isOffset == false)
		return 0;

	m_Offset.x = m_ButtonState * m_Size.x;

	return 0;
}

int Button::LateUpdate(float DeltaTime)
{
	UI::LateUpdate(DeltaTime);
	return 0;
}

void Button::Collision(float DeltaTime)
{
	UI::Collision(DeltaTime);
}

void Button::Render(HDC hDC, float DeltaTime)
{
	UI::Render(hDC, DeltaTime);
}

Button * Button::Clone()
{
	return new Button(*this);
}

void Button::OnCollsionFirst(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "MouseObjectUI")
	{
		m_ButtonState = BS_OVER;
	}
}

void Button::OnCollsionDoing(Collider * Src, Collider * Dest, float DeltaTime)
{
}

void Button::OnCollsionEnd(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "MouseObjectUI")
	{
		m_ButtonState = BS_NOMAL;
	}
}

void Button::SetCallBack(void(*pFunc)(float))
{
	m_isCallBack = true;
	m_ClickCallBack = bind(pFunc, placeholders::_1);
}

