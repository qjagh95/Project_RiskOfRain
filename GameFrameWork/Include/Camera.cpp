#include "stdafx.h"
#include "Camera.h"
#include "Object\Object.h"

INIT_STATIC_VAR(Camera)

Camera::Camera()
	: Target(NULL)
{
}

Camera::~Camera()
{
	SAFE_RELEASE(Target);
}

bool Camera::Init()
{
	return true;
}

void Camera::Update()
{
	if (Target == NULL)
		return;

	//Ÿ���� �߽����� Ÿ���� �߽����� �ػ󵵸� �̿��Ͽ� ī�޶��� �� ����� ����ش�
	Vector2 TargetPos = Target->GetPos();
	//�� �����ġ�� Ÿ��Pos - �ػ� * Ÿ���߽���
	m_Pos = TargetPos - (m_VirtualSize * TargetPivot);

	if (m_Pos.x <= 0.0f)
		m_Pos.x = 0.0f;

	//������ ��������Ų�� (��ü����x - �ػ�x)
	else if (m_Pos.x + m_VirtualSize.x >= m_WorldSize.x)
		m_Pos.x = m_WorldSize.x - m_VirtualSize.x; 

	if (m_Pos.y <= 0.0f)
		m_Pos.y = 0.0f;

	else if (m_Pos.y + m_VirtualSize.y >= m_WorldSize.y)
		m_Pos.y = m_WorldSize.y - m_VirtualSize.y;
}

void Camera::Render(HDC Hdc)
{
	if (Core::Get()->GetIsDebugMode() == false)
		return;

	TCHAR Buffer[255] = {};
	swprintf_s(Buffer, L"CameraPos : %f, %f", m_Pos.x, m_Pos.y);
	TextOutW(Hdc, 0, 40, Buffer, lstrlen(Buffer));
}

void Camera::SetTarget(Object * Value)
{
	if (Value != NULL)
		Value->AddRefCount();

	Target = Value;
}

void Camera::Move(const Vector2 & Value)
{
	m_Pos.x += Value.x;
	m_Pos.y += Value.y;

	if (m_Pos.x <= 0.0f)
		m_Pos.x = 0.0f;

	//������ ��������Ų�� (��ü����x - �ػ�x)
	else if (m_Pos.x + m_VirtualSize.x >= m_WorldSize.x)
		m_Pos.x = m_WorldSize.x - m_VirtualSize.x;

	if (m_Pos.y <= 0.0f)
		m_Pos.y = 0.0f;

	else if (m_Pos.y + m_VirtualSize.y >= m_WorldSize.y)
		m_Pos.y = m_WorldSize.y - m_VirtualSize.y;

}

void Camera::Move(float x, float y)
{
	m_Pos.x += x;
	m_Pos.y += y;

	if (m_Pos.x <= 0.0f)
		m_Pos.x = 0.0f;

	//������ ��������Ų�� (��ü����x - �ػ�x)
	else if (m_Pos.x + m_VirtualSize.x >= m_WorldSize.x)
		m_Pos.x = m_WorldSize.x - m_VirtualSize.x;

	if (m_Pos.y <= 0.0f)
		m_Pos.y = 0.0f;

	else if (m_Pos.y + m_VirtualSize.y >= m_WorldSize.y)
		m_Pos.y = m_WorldSize.y - m_VirtualSize.y;
}

