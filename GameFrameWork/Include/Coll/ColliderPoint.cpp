#include "ColliderPoint.h"
#include "../Object/Object.h"
#include "ColliderRect.h"
#include "ColliderCircle.h"
#include "ColliderPixel.h"
#include "../Camera.h"

ColliderPoint::ColliderPoint()
{
	SetTag("Point");
	m_CollType = CT_POINT;

	m_hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
	m_hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
	m_hBrush = m_hGreenBrush;
}

ColliderPoint::ColliderPoint(const ColliderPoint & Value)
	:Collider(Value)
{
	m_hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
	m_hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
	m_hBrush = m_hGreenBrush;
}

ColliderPoint::~ColliderPoint()
{
	DeleteObject(m_hGreenBrush);
	DeleteObject(m_hRedBrush);
}

bool ColliderPoint::Init()
{
	return true;
}

int ColliderPoint::Update(float DeltaTime)
{
	Vector2 ObjectPos = m_Object->GetPos();

	if (m_IsUI && m_Object->GetObjectType() != OT_UI)
		ObjectPos -= Camera::Get()->GetPos();

	m_WorldPos = m_VirtualPos + ObjectPos;

	return 0;
}

bool ColliderPoint::Collsion(Collider * Dest)
{
	if (m_IsUI != Dest->GetIsUI())
		return false;

	switch (Dest->GetCollType())
	{
		case CT_RECT:
			return CollsionRectToPoint(((ColliderRect*)Dest)->GetWorldRect(), m_WorldPos);
			break;
		case CT_CIRCLE:
			return CollsionCircleToPoint(((ColliderCircle*)Dest)->GetWorldCircle(), m_WorldPos);
			break;
		case CT_POINT:
			return CollsionPointToPoint(m_WorldPos, ((ColliderPoint*)Dest)->GetWorldPos());
			break;
	}

	return false;
}

void ColliderPoint::Render(HDC hDC, float DeltaTime)
{
	Vector2 RenderPos = m_WorldPos;
	if (m_IsUI == false)
		RenderPos -= Camera::Get()->GetPos();

	if (Core::Get()->GetIsDebugMode() == false)
		return;

	if (m_PrevCollList.empty())
		m_hBrush = m_hGreenBrush;

	else
		m_hBrush = m_hRedBrush;

	m_hOldBrush = (HBRUSH)SelectObject(hDC, m_hBrush);

	Ellipse(hDC, (int)(RenderPos.x - 3), (int)(RenderPos.y - 3), (int)(RenderPos.x + 3), (int)(RenderPos.y + 3));
}

ColliderPoint * ColliderPoint::Clone() const
{
	return new ColliderPoint(*this);
}

void ColliderPoint::Save(FILE * pFile)
{
	Collider::Save(pFile);

	fwrite(&m_VirtualPos, sizeof(Vector2), 1, pFile);
}

void ColliderPoint::Load(FILE * pFile)
{
	Collider::Load(pFile);

	fread(&m_VirtualPos, sizeof(Vector2), 1, pFile);
}
