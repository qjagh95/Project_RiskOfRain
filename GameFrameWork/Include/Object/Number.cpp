#include "Number.h"
#include "../Camera.h"
#include "../Resource/Animation.h"
#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"

#include "../Coll/Collider.h"

Number::Number()
{
	isMove = false;
	isLiveTime = false;
	LiveTime = 0.0f;
	MaxRange = 0.0f;
	TimeVar = 0.0f;
	Count = 0;
	m_ZeroTexture = NULL;
}

Number::Number(const Number & number)
	:Object(number)
{
	m_Number = number.m_Number;
	isMove = number.isMove;
	MaxRange = number.MaxRange;
	LiveTime = number.LiveTime;
	TimeVar = 0.0f;
	Count = number.Count;
}

Number::~Number()
{
	SAFE_RELEASE(m_ZeroTexture);
}

bool Number::Init()
{
	m_ZeroTexture = ResourceManager::Get()->LoadTexture("Zero", TEXT("object/ZeroNumber.bmp"));

	ZeroPos = Vector2(0.0f, 0.0f);
	ZeroSize = Vector2(13.0f,24.0f);

	return true;
}

int Number::Input(float fTime)
{
	Object::Input(fTime);

	return 0;
}

int Number::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	if (Count <= 1)
	{	
		ZeroPos = Vector2(m_Pos.x - m_NumberSize.x - m_NumberSize.GetHalfX(), m_Pos.y);
		ZeroSize = Vector2(13.0f, 24.0f);
	}
	else
	{
		ZeroSize = Vector2(0.0f, 0.0f);
	}

	if (isMove == true && MoveSpeed >= 0.0f)
	{
		MoveByAngle(DeltaTime);
		MaxRange -= MoveSpeed * DeltaTime;

		if (MaxRange <= 0.0f)
			SetisActiv(false);
	}

	if (isLiveTime == true)
	{
		TimeVar += DeltaTime;

		if (LiveTime >= TimeVar)
		{
			TimeVar = 0.0f;
			SetisActiv(false);
		}
	}

	return 0;
}

int Number::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void Number::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void Number::Render(HDC hDC, float DeltaTime)
{
	Count = 0;

	//���͸� �ʱ�ȭ �Ѵ�.
	m_vecNumber.clear();

	int Number = m_Number;

	//�ڸ����� �˾Ƴ����Ѵ�. (0���� �۾��������� ��ӵ�����)
	while (Number > 0)
	{
		int a = Number % 10;
		Number /= 10; ///�Ҽ��� �����⸦ �����ϱ�����. (���ѷ���)
		Count++;

		m_vecNumber.push_back(a);
	}

	if (m_Texture == NULL)
		return;

	Vector2 CameraPos = Camera::Get()->GetPos();
	Vector2 LeftTop = m_Pos - m_Size * m_Pivot;
	Vector2 RT = LeftTop;

	RT.x = m_Pos.x + m_Size.x - m_NumberSize.x;

	//���� �����ʺ��� ����Ѵ�.
	for (int i = 0; i < m_vecNumber.size(); i++)
	{
		Vector2 tPos = RT;

		if (isCameraMode == true)
			tPos -= CameraPos;

		//��ġ������
		tPos.x -= (float)(i * m_NumberSize.x);

		int FrameX = 0;
		int FrameY = 0;
		//5 * ������ (�̹�������� ���Ѵ�)
		FrameX += m_vecNumber[i] * (int)m_NumberSize.x;
		FrameY += (int)m_Offset.y;

		if (isColorKey == false)
			BitBlt(hDC, (int)tPos.x, (int)tPos.y, (int)m_NumberSize.x, (int)m_NumberSize.y, m_Texture->GetMemDC(), FrameX, FrameY, SRCCOPY);
		else if(isColorKey == true)
			TransparentBlt(hDC, (int)tPos.x, (int)tPos.y, (int)m_NumberSize.x, (int)m_NumberSize.y, m_Texture->GetMemDC(), FrameX, FrameY, (int)m_NumberSize.x, (int)m_NumberSize.y, m_ColorKey);
		else if(m_vecNumber[i] == 0)
			TransparentBlt(hDC, (int)tPos.x, (int)tPos.y, (int)ZeroSize.x, (int)ZeroSize.y, m_ZeroTexture->GetMemDC(), 0, 0, (int)ZeroSize.x, (int)ZeroSize.y, m_ColorKey);
	}
	
	//0�̹���
	TransparentBlt(hDC, (int)ZeroPos.x, (int)ZeroPos.y, (int)ZeroSize.x, (int)ZeroSize.y, m_ZeroTexture->GetMemDC(), 0, 0, (int)ZeroSize.x, (int)ZeroSize.y, m_ColorKey);

	list<Collider*>::iterator StartIter = m_ColliderList.begin();
	list<Collider*>::iterator EndIter = m_ColliderList.end();

	for (; StartIter != EndIter; StartIter++)
		(*StartIter)->Render(hDC, DeltaTime);
}

Number * Number::Clone()
{
	return new Number(*this);
}
