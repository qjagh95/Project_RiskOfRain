#pragma once

class Circle
{
public:
	Vector2 m_CenterPos;
	float m_Radius;

	Circle() :m_Radius(0) {}
	Circle(float x, float y, float Radius) :m_CenterPos(Vector2(x,y)), m_Radius(Radius) {}
	Circle(const Vector2& Pos, float Radius) : m_CenterPos(Pos), m_Radius(Radius) {}
	Circle(const Circle& circle) { m_CenterPos = circle.m_CenterPos, m_Radius = circle.m_Radius; }
	~Circle() {}

	void SetCircle(float x, float y, float Radius) { m_CenterPos = Vector2(x, y), m_Radius = Radius; }
	void SetCircle(const Vector2& Pos, float Radius) { m_CenterPos = Pos, m_Radius = Radius; }
	void SetCircle(const Circle& circle) { m_CenterPos = circle.m_CenterPos, m_Radius = circle.m_Radius; }
	Vector2 GetCenterPos() const { return m_CenterPos; }
	float GetRadius() const { return m_Radius; }

	void Move(float x, float y) { m_CenterPos.x += x, m_CenterPos.y += y; }
	void Move(float x, float y, float Radius) { m_CenterPos.x += x, m_CenterPos.y += y, m_Radius += Radius; }
	void Move(const Vector2& MovePos, float Radius) { m_CenterPos.x += MovePos.x, m_CenterPos.y += MovePos.y, m_Radius += Radius; }
	void Move(const Vector2& Value) { m_CenterPos.x += Value.x, m_CenterPos.y += Value.y; }

	void Render(HDC hdc) { Ellipse(hdc, (int)(m_CenterPos.x - m_Radius), (int)(m_CenterPos.y - m_Radius), (int)(m_CenterPos.x + m_Radius), (int)(m_CenterPos.y + m_Radius)); }
	void RenderFrame(HDC hdc)
	{
		Vector2 Temp;

		Temp.x = m_CenterPos.x + m_Radius;
		Temp.y = m_CenterPos.y;

		MoveToEx(hdc, (int)Temp.x, (int)Temp.y, NULL);

		for (int i = 2; i < 180; i++)
		{
			Temp.x = m_CenterPos.x + m_Radius * cosf(i * 2.0f * PI / 180.0f);
			Temp.y = m_CenterPos.y + m_Radius * sinf(i * 2.0f * PI / 180.0f);

			LineTo(hdc, (int)Temp.x, (int)Temp.y);
		}
	}
};