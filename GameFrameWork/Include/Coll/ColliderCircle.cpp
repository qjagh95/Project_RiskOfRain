#include "ColliderCircle.h"
#include "../Object/Object.h"
#include "ColliderRect.h"
#include "ColliderPixel.h"
#include "ColliderPoint.h"
#include "../Camera.h"

ColliderCircle::ColliderCircle()
{
	SetTag("Circle");
	m_CollType = CT_CIRCLE;

	m_hGreenBrush = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_hRedBrush = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_hBrush = m_hGreenBrush;
}

ColliderCircle::~ColliderCircle()
{
	DeleteObject(m_hGreenBrush);
	DeleteObject(m_hRedBrush);
}

ColliderCircle::ColliderCircle(const ColliderCircle& Value)
	:Collider(Value)
{
	m_VirtualCircle = Value.m_VirtualCircle;
		
	m_hGreenBrush = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_hRedBrush = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_hBrush = m_hGreenBrush;
}

bool ColliderCircle::Init()
{
	return true;
}

int ColliderCircle::Update(float DeltaTime)
{
	// 상대 정보를 이용하여 월드정보를 만들어낸다.
	Vector2	ObjectPos = m_Object->GetPos();
	
	if (m_IsUI && m_Object->GetObjectType() != OT_UI)
		ObjectPos -= Camera::Get()->GetPos();

	m_WorldCircle.m_Radius = m_VirtualCircle.m_Radius;

	//센터포지션을 Pivot 0,0으로 가정한다.
	m_WorldCircle.m_CenterPos.x = m_VirtualCircle.m_CenterPos.x + ObjectPos.x + (m_Pivot.x * m_VirtualCircle.m_Radius);
	m_WorldCircle.m_CenterPos.y = m_VirtualCircle.m_CenterPos.y + ObjectPos.y + (m_Pivot.y * m_VirtualCircle.m_Radius);

	return 0;
}

bool ColliderCircle::Collsion(Collider * Dest)
{
	//둘중하나라도 UI라면 둘이 충돌하지 않겠다
	if (m_IsUI != Dest->GetIsUI())
		return false;

	switch (Dest->GetCollType())
	{
		case CT_CIRCLE:
			return CollsionCircleToCircle(m_WorldCircle, ((ColliderCircle*)Dest)->m_WorldCircle);
		case CT_RECT:
			return CollsionRectToCircle(((ColliderRect*)Dest)->m_WorldRect, m_WorldCircle);
		case CT_POINT:
			return CollsionCircleToPoint(m_WorldCircle, ((ColliderPoint*)Dest)->GetWorldPos());
	}
	return false;
}

void ColliderCircle::Render(HDC hDC, float DeltaTime)
{
	Circle ObjectCircle = m_WorldCircle;

	if (m_IsUI == false)
	{
		Vector2 CameraPos = Camera::Get()->GetPos();
		ObjectCircle.m_CenterPos -= CameraPos;
	}

	if (Core::Get()->GetIsDebugMode() == false)
		return;

	if (m_PrevCollList.empty())
		m_hBrush = m_hGreenBrush;
	else
		m_hBrush = m_hRedBrush;
	
	m_hOldBrush = (HPEN)SelectObject(hDC, m_hBrush);

	ObjectCircle.RenderFrame(hDC);

	SelectObject(hDC, m_hOldBrush);
}


ColliderCircle * ColliderCircle::Clone() const
{
	return new ColliderCircle(*this);
}

void ColliderCircle::Save(FILE * pFile)
{
	Collider::Save(pFile);

	fwrite(&m_VirtualCircle, sizeof(Circle), 1, pFile);
}

void ColliderCircle::Load(FILE * pFile)
{
	Collider::Save(pFile);
	
	fread(&m_VirtualCircle, sizeof(Circle), 1, pFile);

}
