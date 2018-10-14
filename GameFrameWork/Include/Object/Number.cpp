#include "Number.h"
#include "../Camera.h"
#include "../Resource/Animation.h"
#include "../Resource/Texture.h"
#include "../Coll/Collider.h"

Number::Number()
{
	isMove = false;
	isLiveTime = false;
	LiveTime = 0.0f;
	MaxRange = 0.0f;
	TimeVar = 0.0f;
}

Number::Number(const Number & number)
	:Object(number)
{
	m_Number = number.m_Number;
	isMove = number.isMove;
	MaxRange = number.MaxRange;
	LiveTime = number.LiveTime;
	TimeVar = 0.0f;
}

Number::~Number()
{
}

bool Number::Init()
{
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
	//벡터를 초기화 한다.
	m_vecNumber.clear();

	int Number = m_Number;

	//자릿수를 알아내야한다. (0보다 작아질때까지 계속돌린다)
	while (Number > 0)
	{
		int a = Number % 10;
		Number /= 10; ///소수점 나누기를 방지하기위함. (무한루프)

		m_vecNumber.push_back(a);
	}

	if (m_Texture == NULL)
		return;

	Vector2 CameraPos = Camera::Get()->GetPos();
	Vector2 LeftTop = m_Pos - m_Size * m_Pivot;
	Vector2 RT = LeftTop;

	RT.x = m_Pos.x + m_Size.x - m_NumberSize.x;

	//가장 오른쪽부터 출력한다.
	for (int i = 0; i < m_vecNumber.size(); i++)
	{
		Vector2 tPos = RT;

		if (isCameraMode == true)
			tPos -= CameraPos;

		//위치값세팅
		tPos.x -= (float)(i * m_NumberSize.x);

		int FrameX = 0;
		int FrameY = 0;
		//5 * 사이즈 (이미지사이즈를 정한다)
		FrameX += m_vecNumber[i] * (int)m_NumberSize.x;
		FrameY += (int)m_Offset.y;

		if (isColorKey == false)
			BitBlt(hDC, (int)tPos.x, (int)tPos.y, (int)m_NumberSize.x, (int)m_NumberSize.y, m_Texture->GetMemDC(), FrameX, FrameY, SRCCOPY);
		else
			TransparentBlt(hDC, (int)tPos.x, (int)tPos.y, (int)m_NumberSize.x, (int)m_NumberSize.y, m_Texture->GetMemDC(), FrameX, FrameY, (int)m_NumberSize.x, (int)m_NumberSize.y, m_ColorKey);
	}


	list<Collider*>::iterator StartIter = m_ColliderList.begin();
	list<Collider*>::iterator EndIter = m_ColliderList.end();

	for (; StartIter != EndIter; StartIter++)
		(*StartIter)->Render(hDC, DeltaTime);
}

Number * Number::Clone()
{
	return new Number(*this);
}
