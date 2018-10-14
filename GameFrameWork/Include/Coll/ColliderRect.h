#pragma once
#include "Collider.h"
class ColliderRect : public Collider
{
public:
	bool Init() override;
	int Update(float DeltaTime) override;
	bool Collsion(Collider* Dest) override;
	void Render(HDC hDC, float DeltaTime) override;
	ColliderRect* Clone() const override;
	void Save(FILE* pFile) override;
	void Load(FILE* pFile) override;

	void SetVirtualRect(const Vector2& tSize) { m_VirtualRect.Right = tSize.x, m_VirtualRect.Bottom = tSize.y, m_Size = tSize; }
	void SetVirtuaRect(const Rect& tRect) { m_VirtualRect = tRect, m_Size.x = tRect.Right - tRect.Left, m_Size.y = tRect.Bottom - tRect.Top; }
	void SetVirtualRect(float Width, float Height) { m_Size = Vector2(Width, Height), m_VirtualRect.Right = m_Size.x, m_VirtualRect.Bottom = m_Size.y; }
	Rect GetWorldRect() const { return m_WorldRect; }
	void MoveWorldRect(float x, float y) { m_WorldRect.Left += x, m_WorldRect.Right += x, m_WorldRect.Bottom += y, m_WorldRect.Top += y; }
	void MoveWorldRect(const Vector2& Pos) { m_WorldRect.Left += Pos.x, m_WorldRect.Right += Pos.x, m_WorldRect.Bottom += Pos.y, m_WorldRect.Top += Pos.y; }
	Vector2 GetSize() const { return m_Size; }

protected:
	ColliderRect();
	ColliderRect(const ColliderRect& Value);
	~ColliderRect();

private:
	//LeftTop RightBottom만으로 되지않기때문에 Pivot을 또 설정해줘야한다. (부모클래스정의)
	Rect  m_VirtualRect; ///상대적인 정보
	Rect m_WorldRect;    ///실제 Rect
	Vector2 m_Size;      ///가로세로의 길이

	HBRUSH			m_hBrush;
	HBRUSH			m_hGreenBrush;
	HBRUSH			m_hRedBrush;
	HBRUSH			m_hOldBrush;

public:
	friend class Object;
	friend class CollsionManager;
	friend class ColliderCircle;
};

