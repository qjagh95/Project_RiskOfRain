#pragma once
#include "Collider.h"
class ColliderPoint : public Collider
{
public:
	bool Init() override;
	int Update(float DeltaTime) override;
	bool Collsion(Collider* Dest) override;
	void Render(HDC hDC, float DeltaTime) override;
	ColliderPoint* Clone() const override;
	void Save(FILE* pFile) override;
	void Load(FILE* pFile) override;

	void SetVirtualPos(const Vector2& Pos) { m_VirtualPos.x = Pos.x, m_VirtualPos.y = Pos.y; }
	void SetVirtualPos(float x, float y) { m_VirtualPos = Vector2(x, y); }
	Vector2 GetWorldPos() const { return m_WorldPos; }

protected:
	ColliderPoint();
	ColliderPoint(const ColliderPoint& Value);
	~ColliderPoint();

private:
	//LeftTop RightBottom만으로 되지않기때문에 Pivot을 또 설정해줘야한다. (부모클래스정의)
	Vector2  m_VirtualPos; ///상대적인 정보
	Vector2 m_WorldPos;    ///실제 Rect

	HBRUSH			m_hBrush;
	HBRUSH			m_hGreenBrush;
	HBRUSH			m_hRedBrush;
	HBRUSH			m_hOldBrush;

public:
	friend class Object;
	friend class CollsionManager;
};

