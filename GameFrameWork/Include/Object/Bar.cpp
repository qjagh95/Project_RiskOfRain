#include "Bar.h"
#include "../Camera.h"
#include "../Resource/Texture.h"

Bar::Bar()
{
	m_ObjectType = OT_BAR;
	m_BarDir = BD_LEFT;
	m_Min = 0;
	m_Max = 0;
	m_BarValue = 0;
}

Bar::Bar(const Bar & bar)
	:Object(bar)
{
	m_BarDir = bar.m_BarDir;
	m_Min = bar.m_Min;
	m_Max = bar.m_Max;
	m_BarValue = bar.m_BarValue;
}

Bar::~Bar()
{
}

bool Bar::Init()
{
	return true;
}

int Bar::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int Bar::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int Bar::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void Bar::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void Bar::Render(HDC hDC, float fTime)
{
	//������ ���ؾ��Ѵ�.
	int Lenth = m_Max - m_Min;
	//������ ���ߴ� (������ Hp�� / �ִ� ��)
	float Ratio = m_BarValue / (float)Lenth;

	if (m_Texture == NULL)
		return;

	Vector2 CameraPos = Camera::Get()->GetPos();
	Vector2 LeftTop = m_Pos - (m_Size * m_Pivot);
	Vector2 Size = m_Size;

	switch (m_BarDir)
	{
		case BD_LEFT:
			Size.x = m_Size.x * Ratio;
			break;
		case BD_RIGHT:
			Size.x = m_Size.x * Ratio;
			//������ �ٲٰ� ��ǥ�� �Ű��ش�
			LeftTop.x = m_Pos.x - Size.x;
			break;
		case BD_UP:
			Size.y = m_Size.y * Ratio;
			break;
		case BD_DOWN:
			Size.y = m_Size.y * Ratio;
			LeftTop.y = m_Pos.y - Size.y;
			break;
	}

	if (isCameraMode == true)
		LeftTop -= CameraPos;

	int FrameX = 0;
	int FrameY = 0;

	if (isColorKey == false)
		BitBlt(hDC, (int)LeftTop.x, (int)LeftTop.y, (int)Size.x, (int)Size.y, m_Texture->GetMemDC(), FrameX, FrameY, SRCCOPY);
	else                        //��ġ                            ��»�����                                  �̹�����ġ         �̹���������(����)
		TransparentBlt(hDC, (int)LeftTop.x, (int)LeftTop.y, (int)Size.x, (int)Size.y, m_Texture->GetMemDC(), FrameX, FrameY, (int)Size.x, (int)Size.y, m_ColorKey);
}

Bar * Bar::Clone()
{
	return new Bar(*this);
}

void Bar::SetBarInfo(int Min, int Max, int Value, BAR_DIR Dir)
{
	m_Min = Min;
	m_Max = Max;
	m_BarValue = Value;
	m_BarDir = Dir;

	//���Ⱚ������ �Ǻ��� �ٲ��ش�
	switch (m_BarDir)
	{
		case BD_LEFT:
			m_Pivot = Vector2(0.0f, 0.0f);
			break;
		case BD_RIGHT:
			m_Pivot = Vector2(1.0f, 0.0f);
			break;
		case BD_UP:
			m_Pivot = Vector2(0.0f, 1.0f);
			break;
		case BD_DOWN:
			m_Pivot = Vector2(0.0f, 0.0f);
			break;
	}

	//�ִ� �ּҰ��� �����ȵ��� �Ѵ�.
	if (m_BarValue < m_Min)
		m_BarValue = m_Min;

	else if (m_BarValue > m_Max)
		m_BarValue = m_Max;
}

void Bar::SetBarDir(BAR_DIR Dir)
{
	m_BarDir = Dir;

	//���Ⱚ������ �Ǻ��� �ٲ��ش�
	switch (m_BarDir)
	{
		case BD_LEFT:
			m_Pivot = Vector2(0.0f, 0.0f);
			break;
		case BD_RIGHT:
			m_Pivot = Vector2(1.0f, 0.0f);
			break;
		case BD_UP:
			m_Pivot = Vector2(0.0f, 1.0f);
			break;
		case BD_DOWN:
			m_Pivot = Vector2(0.0f, 0.0f);
			break;
	}
}

void Bar::SetValue(int Value)
{
	m_BarValue = Value;

	if (m_BarValue < m_Min)
		m_BarValue = m_Min;

	else if (m_BarValue > m_Max)
		m_BarValue = m_Max;
}

void Bar::AddValue(int Value)
{
	m_BarValue += Value;

	if (m_BarValue < m_Min)
		m_BarValue = m_Min;

	else if (m_BarValue > m_Max)
		m_BarValue = m_Max;
}
