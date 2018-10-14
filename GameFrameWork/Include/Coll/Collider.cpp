#include "../stdafx.h"
#include "Collider.h"
#include "../Object/Object.h"

Collider::Collider()
{
	m_GroupName = "Default";
	m_IsUI = false;
}

Collider::Collider(const Collider & Value)
{
	*this = Value;
}

Collider::~Collider()
{
	list<Collider*>::iterator StartIter = m_PrevCollList.begin();
	list<Collider*>::iterator EndIter= m_PrevCollList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		(*StartIter)->DeletePrevCollider(this);
		(*StartIter)->OnCollsionEnd(this, 0.0f);
	}
}

bool Collider::Init()
{
	return true;
}

int Collider::Update(float DeltaTime)
{
	return 0;
}

void Collider::Render(HDC hDC, float DeltaTime)
{
}

Collider * Collider::Clone() const
{
	return NULL;
}

void Collider::Save(FILE * pFile)
{
	fwrite(&m_Pivot, sizeof(Vector2), 1, pFile);

	int	iLength = (int)m_GroupName.length();

	fwrite(&iLength, sizeof(int), 1, pFile);
	fwrite(m_GroupName.c_str(), sizeof(char), iLength, pFile);

	iLength = (int)m_CollsionTypeName.length();

	fwrite(&iLength, sizeof(int), 1, pFile);
	fwrite(m_CollsionTypeName.c_str(), sizeof(char), iLength, pFile);

	fwrite(&m_IsUI, sizeof(bool), 1, pFile);
}

void Collider::Load(FILE * pFile)
{
	fread(&m_Pivot, sizeof(Vector2), 1, pFile);

	int	iLength = 0;

	fread(&iLength, sizeof(int), 1, pFile);

	char strText[256] = {};

	fread(strText, sizeof(char), iLength, pFile);

	m_GroupName = strText;

	memset(strText, 0, sizeof(char) * 256);

	fread(&iLength, sizeof(int), 1, pFile);
	fread(strText, sizeof(char), iLength, pFile);

	m_CollsionTypeName = strText;

	fread(&m_IsUI, sizeof(bool), 1, pFile);
}

Object * Collider::GetCurObject() const
{
	m_Object->AddRefCount();

	return m_Object;
}

void Collider::OnCollsionFirst(Collider * pDest, float DeltaTime)
{
	list<function<void(Collider*, Collider*, float)>>::iterator StartIter = m_CallBack[CS_COLFIRST].begin();
	list<function<void(Collider*, Collider*, float)>>::iterator EndIter = m_CallBack[CS_COLFIRST].end();

	for ( ;StartIter != EndIter; StartIter++)
		(*StartIter)(this, pDest, DeltaTime);

}

void Collider::OnCollsionDoing(Collider * pDest, float DeltaTime)
{
	list<function<void(Collider*, Collider*, float)>>::iterator StartIter = m_CallBack[CS_COLDOING].begin();
	list<function<void(Collider*, Collider*, float)>>::iterator EndIter = m_CallBack[CS_COLDOING].end();

	for (;StartIter != EndIter; StartIter++)
		(*StartIter)(this, pDest, DeltaTime);
}

void Collider::OnCollsionEnd(Collider * pDest, float DeltaTime)
{
	list<function<void(Collider*, Collider*, float)>>::iterator StartIter = m_CallBack[CS_COLEND].begin();
	list<function<void(Collider*, Collider*, float)>>::iterator EndIter = m_CallBack[CS_COLEND].end();

	for (;StartIter != EndIter; StartIter++)
		(*StartIter)(this, pDest, DeltaTime);
}

Vector2 Collider::GetPos() const
{
	return m_Object->GetPos();
}

bool Collider::CollsionRectToRect(const Rect & Left, const Rect & Right)
{
	if (Left.Left > Right.Right)
		return false;
	else if (Left.Right < Right.Left)
		return false;
	else if (Left.Top > Right.Bottom)
		return false;
	else if (Left.Bottom < Right.Top)
		return false;

	//충돌된위치에 Rect를 만든다
	Rect TempRect;

	if (Left.Left > Right.Left)
		TempRect.Left = Left.Left;
	else
		TempRect.Left = Right.Left;

	if (Left.Right > Right.Right)
		TempRect.Right = Left.Right;
	else
		TempRect.Right = Left.Right;

	if (Left.Top > Right.Top)
		TempRect.Top = Left.Top;
	else
		TempRect.Top = Right.Top;

	if (Left.Bottom > Right.Bottom)
		TempRect.Bottom = Right.Bottom;
	else
		TempRect.Bottom = Left.Bottom;

	m_CollsionPos.x = (TempRect.Right + TempRect.Left) / 2.0f;
	m_CollsionPos.y = (TempRect.Bottom + TempRect.Top) / 2.0f;

	return true;
}

bool Collider::CollsionCircleToCircle(const Circle & Left, const Circle & Right)
{
	return Math::GetDistance(Left.m_CenterPos, Right.m_CenterPos) <= Left.m_Radius + Right.m_Radius;
}

bool Collider::CollsionRectToCircle(const Rect & Left, const Circle & Right)
{
	Rect LeftRect;
	Vector2 cPos = Right.m_CenterPos;

	if ((Left.Left <= cPos.x && Left.Right >= cPos.x) || (Left.Top <= cPos.y, Left.Bottom >= cPos.y))
	{
		LeftRect.Left = Left.Left - Right.m_Radius;
		LeftRect.Top = Left.Top - Right.m_Radius;
		LeftRect.Right = Left.Right + Right.m_Radius;
		LeftRect.Bottom = Left.Bottom + Right.m_Radius;

		if ((LeftRect.Left < cPos.x && LeftRect.Right > cPos.x) && (LeftRect.Top < cPos.y && LeftRect.Bottom > cPos.y))
			return true;
		else
			return false;
	}
	else
	{
		//대각선을 체크한다.
		float l = Math::GetDistance(Vector2(Left.Left, Left.Top), cPos) < Right.m_Radius;
		float t = Math::GetDistance(Vector2(Left.Right, Left.Top), cPos) < Right.m_Radius;
		float r = Math::GetDistance(Vector2(Left.Left, Left.Bottom), cPos) < Right.m_Radius;
		float b = Math::GetDistance(Vector2(Left.Right, Left.Bottom), cPos) < Right.m_Radius;

		if (l || t || r || b)
			return true;
	}
	return false;
}

bool Collider::CollsionRectToPoint(const Rect & Left, const Vector2 & Right)
{
	if (Left.Left > Right.x)
		return false;
	else if (Left.Right < Right.x)
		return false;
	else if (Left.Top > Right.y)
		return false;
	else if (Left.Bottom < Right.y)
		return false;

	return true;
}

bool Collider::CollsionPointToPoint(const Vector2 & Left, const Vector2 & Right)
{
	return Left.x == Right.x && Left.x == Right.x;
}

bool Collider::CollsionCircleToPoint(const Circle & Left, const Vector2 & Right)
{
	return Math::GetDistance(Left.m_CenterPos, Right) <= Left.m_Radius;
}

bool Collider::CollsionRectToPixel(const Rect & Left, const PixelInfo & Right)
{
	Rect TempRect = Left;

	//전체 픽셀정보의 주소를 가져온다.
	unsigned char* pPixel = (unsigned char*)Right.cPixel;

	//전체 사이즈를 벗어났는지 체크한다.
	if (TempRect.Left <= Right.Width && TempRect.Right >= 0.0f && TempRect.Top <= Right.Height && TempRect.Bottom >= 0.0f)
	{
		//사각형 영역을 체크한다.
		int StartX = (int)(TempRect.Left <= 0.0f ? 0.0f : TempRect.Left);
		int EndX = (int)(TempRect.Right >= Right.Width ? Right.Width : TempRect.Right);
		int StartY = (int)(TempRect.Top <= 0.0f ? 0.0f: TempRect.Top);
		int EndY = (int)(TempRect.Bottom >= Right.Height ? Right.Height : TempRect.Bottom);

		for (int i = StartY; i < EndY ; i++)
		{
			for (int j = StartX; j < EndX; j++)
			{
				//인덱스 구하는 공식
				int Index = (i * Right.Width + j) * Right.PixelSize;

				//오브젝트 사각형영역의 픽셀정보와 픽셀충돌RGB값을 비교한다.
				if (pPixel[Index] == Right.CollsionColor.r && pPixel[Index + 1] == Right.CollsionColor.g && pPixel[Index + 2] == Right.CollsionColor.b)
					return true;
			}//for(x)
		}//for(y)
	}//if
	return false;
}
