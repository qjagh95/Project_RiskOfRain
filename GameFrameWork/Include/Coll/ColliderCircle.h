#pragma once
#include "Collider.h"
class ColliderCircle : public Collider
{
public:
	bool Init() override;
	int Update(float DeltaTime) override;
	bool Collsion(Collider* Dest) override;
	void Render(HDC hDC, float DeltaTime) override;
	ColliderCircle* Clone()	const override;
	void Save(FILE* pFile) override;
	void Load(FILE* pFile) override;

public:
	Circle GetWorldCircle() const { return m_WorldCircle; }
	void SetVirtualCircle(float fRadius) { m_VirtualCircle.m_Radius = fRadius; }
	void SetVirtualCircle(float x, float y, float r) { m_VirtualCircle.m_CenterPos.x = x; m_VirtualCircle.m_CenterPos.y = y; m_VirtualCircle.m_Radius = r; }
	void SetVirtualCircle(const Vector2& Pos, float r) { m_VirtualCircle.m_CenterPos = Pos, m_VirtualCircle.m_Radius = r; }
	void SetRadius(float r) { m_VirtualCircle.m_Radius = r; }

private:
	Circle	m_VirtualCircle;
	Circle	m_WorldCircle;

	HPEN	m_hBrush;
	HPEN	m_hGreenBrush;
	HPEN	m_hRedBrush;
	HPEN	m_hOldBrush;

private:
	ColliderCircle();
	ColliderCircle(const ColliderCircle& Value);
	~ColliderCircle();

public:
	friend class Object;
	friend class CollisionManager;
	friend class ColliderRect;

};

