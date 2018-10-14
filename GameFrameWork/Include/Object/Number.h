#pragma once
#include "Object.h"
class Texture;
class Number : public Object
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC hDC, float DeltaTime) override;
	Number* Clone() override;

	void SetNumberSize(float x, float y) { m_NumberSize = Vector2(x, y); }
	void SetNumberSize(const Vector2& tSize) { m_NumberSize = tSize; }
	void SetNumber(int iNumber){ m_Number = iNumber;}
	void AddNumber(int iNumber){ m_Number += iNumber;}

	void SetLiveTime(float Time) { LiveTime = Time, isLiveTime = true; }
	void SetMaxRange(float Range, float Speed) { MaxRange = Range, isMove = true, MoveSpeed = Speed; }
	int GetNumberCount() const { return Count; }

private:
	int	m_Number;
	vector<int>	m_vecNumber;
	Vector2	m_NumberSize;

	Texture* m_ZeroTexture;
	Vector2 ZeroPos;
	Vector2 ZeroSize;

	bool isMove;
	bool isLiveTime;
	float MaxRange;
	float LiveTime;
	float TimeVar;
	int Count;

protected:
	Number();
	Number(const Number& number);
	~Number();

public:
	friend class Object;
};

