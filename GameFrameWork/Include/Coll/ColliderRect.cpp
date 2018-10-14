#include "ColliderRect.h"
#include "../Object/Object.h"
#include "ColliderCircle.h"
#include "ColliderPixel.h"
#include "ColliderPoint.h"
#include "../Camera.h"

ColliderRect::ColliderRect()
{
	SetTag("ColliderRect");
	m_CollType = CT_RECT;

	m_hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
	m_hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
	m_hBrush = m_hGreenBrush;

	isTop = false;
	isBottom = false;
	isLeft = false;
	isRight = false;
}

ColliderRect::ColliderRect(const ColliderRect & Value)
	:Collider(Value)
{
	m_VirtualRect = Value.m_VirtualRect;

	m_hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
	m_hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
	m_hBrush = m_hGreenBrush;

	isTop = false;
	isBottom = false;
	isLeft = false;
	isRight = false;
}

ColliderRect::~ColliderRect()
{
	DeleteObject(m_hGreenBrush);
	DeleteObject(m_hRedBrush);
}

bool ColliderRect::Init()
{
	return true;
}

int ColliderRect::Update(float DeltaTime)
{
	m_Size.x = m_VirtualRect.Right - m_VirtualRect.Left;
	m_Size.y = m_VirtualRect.Bottom - m_VirtualRect.Top;

	Vector2 ObjectPos = m_Object->GetPos();

	if (m_IsUI && m_Object->GetObjectType() != OT_UI)
		ObjectPos -= Camera::Get()->GetPos();

	//ObjectPos는 CenterPos
	//상대정보를 이용하여 실제필드정보를 만들어낸다
	m_WorldRect.Left = ObjectPos.x + m_VirtualRect.Left - m_Size.x * m_Pivot.x;
	m_WorldRect.Top = ObjectPos.y + m_VirtualRect.Top - m_Size.y * m_Pivot.y;
	m_WorldRect.Right = m_WorldRect.Left + m_Size.x;
	m_WorldRect.Bottom = m_WorldRect.Top + m_Size.y;

	return 0;
}

bool ColliderRect::Collsion(Collider* Dest)
{
	if (m_IsUI != Dest->GetIsUI())
		return false;

	switch (Dest->GetCollType())
	{
		case CT_RECT:
			return CollsionRectToRect(m_WorldRect, ((ColliderRect*)Dest)->m_WorldRect);
		case CT_CIRCLE:
			return CollsionRectToCircle(m_WorldRect, ((ColliderCircle*)Dest)->m_WorldCircle);
		case CT_POINT:
			return CollsionRectToPoint(m_WorldRect, ((ColliderPoint*)Dest)->GetWorldPos());
		case CT_PIXEL:
			return CollsionRectToPixel(m_WorldRect, ((ColliderPixel*)Dest)->GetInfo());
	}
	return false;
}

void ColliderRect::Render(HDC hDC, float DeltaTime)
{
	Rect ObjectRect = m_WorldRect;

	if (m_IsUI == false)
	{
		Vector2 CameraPos = Camera::Get()->GetPos();

		ObjectRect.Left -= CameraPos.x;
		ObjectRect.Right -= CameraPos.x;
		ObjectRect.Top -= CameraPos.y;
		ObjectRect.Bottom -= CameraPos.y;
	}

	if (Core::Get()->GetIsDebugMode() == false)
		return;

	if (m_PrevCollList.empty())
		m_hBrush = m_hGreenBrush;
	else
		m_hBrush = m_hRedBrush;

	m_hOldBrush = (HBRUSH)SelectObject(hDC, m_hBrush);

	RECT rc = { (LONG)ObjectRect.Left , (LONG)ObjectRect.Top , (LONG)ObjectRect.Right, (LONG)ObjectRect.Bottom };
	FrameRect(hDC, &rc, m_hBrush);

	SelectObject(hDC, m_hOldBrush); 
}

ColliderRect * ColliderRect::Clone() const
{
	return new ColliderRect(*this);
}

void ColliderRect::Save(FILE * pFile)
{
	Collider::Save(pFile);

	fwrite(&m_VirtualRect, sizeof(Rect), 1, pFile);
	fwrite(&m_Size, sizeof(Vector2), 1, pFile);
}

void ColliderRect::Load(FILE * pFile)
{
	Collider::Save(pFile);

	fread(&m_VirtualRect, sizeof(Rect), 1, pFile);
	fread(&m_Size, sizeof(Vector2), 1, pFile);
}
