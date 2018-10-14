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
	void SetNumber(int iNumber) { m_Number = iNumber; }
	void AddNumber(int iNumber) { m_Number += iNumber; }

	void SetMaxRange(float Range, float Speed) { MaxRange = Range, isMove = true, MoveSpeed = Speed; }
	int GetNumberCount() const { return Count; }

	void SetZeroTexturePos(const Vector2& Pos) { ZeroPos = Pos; }
	void SetZeroTextureSize(const Vector2& Size) { ZeroSize = Size; }
	void SetZeroTexturePos(float x, float y) { ZeroPos = Vector2(x, y); }
	void SetZeroTextureSize(float x, float y) { ZeroSize = Vector2(x, y); }

	void SetZeroViewSize(const Vector2& Size) { ZeroViewSize = Size; }
	void SetNumberViewSize(const Vector2& Size) { m_NumberViewSize = Size; }

	void SetZeroViewSize(float x, float y) { ZeroViewSize = Vector2(x, y); }
	void SetNumberViewSize(float x, float y) { m_NumberViewSize = Vector2(x, y); }

	void SetZeroTexture(Texture* pTexture) { m_ZeroTexture = pTexture; }

	Vector2 GetRightPos() const { return RightPos; }
	Vector2 GetLeftPosx() const { return LeftPos; }

private:
	int	m_Number;
	vector<int>	m_vecNumber;
	Vector2	m_NumberSize;
	Vector2 m_NumberViewSize;

	Texture* m_ZeroTexture;
	Vector2 ZeroPos;
	Vector2 ZeroSize;
	Vector2 ZeroViewSize;

	Vector2 LeftPos;
	Vector2 RightPos;

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

