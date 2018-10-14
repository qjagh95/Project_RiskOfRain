#pragma once
class Object;
class Camera
{
public:
	bool Init();
	void Update();
	void Render(HDC Hdc);
	
	void SetVirtualSize(const Vector2& Value) { m_VirtualSize = Value; }
	void SetVirtualSize(float x, float y) { m_VirtualSize = Vector2(x, y); }

	void SetWorldSize(const Vector2& Value) { m_WorldSize = Value; }
	void SetWorldSize(float x, float y) { m_WorldSize = Vector2(x, y); }

	Vector2 GetPos() const { return m_Pos; }
	Vector2 GetWorldSize() const { return m_WorldSize; }
	Vector2 GetVirtualSize() const { return m_VirtualSize; }

	void SetTarget(Object* Value);
	void SetTargetPivot(const Vector2& _Pivot) { TargetPivot = _Pivot; }
	void SetTargetPivot(float x, float y) { TargetPivot = Vector2(x, y); }

	void Move(const Vector2& Value);
	void Move(float x, float y);

private:
	Vector2 m_Pos;         ///ī�޶� ��ġ
	Vector2 m_VirtualSize; ///������� ��ġ
	Vector2 m_WorldSize;   ///����� ũ��

	Object* Target;		   ///ī�޶� ����ٴ� Ÿ��
	Vector2 TargetPivot;   ///ī�޶� ����ٴ� Ÿ�� �߽���

public:
	CLASS_IN_SINGLE(Camera)
};

