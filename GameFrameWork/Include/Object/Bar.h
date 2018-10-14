#pragma once
#include "Object.h"
class Bar : public Object
{
public:
	bool Init();
	int Input(float DeltaTime);
	int Update(float DeltaTime);
	int LateUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void Render(HDC hDC, float DeltaTime);
	Bar* Clone();

	void SetBarInfo(int Min, int Max, int Value, BAR_DIR Dir = BD_LEFT);
	void SetBarDir(BAR_DIR Dir);
	void SetValue(int Value);
	void AddValue(int Value);

private:
	BAR_DIR	m_BarDir;///�پ�� ����
	int	m_Min;       ///�ּҰ�
	int	m_Max;       ///�ִ밪
	int	m_BarValue;  ///BarValue(HP)��

protected:
	Bar();
	Bar(const Bar& bar);
	~Bar();

public:
	friend class Object;
};

