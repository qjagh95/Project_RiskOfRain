#pragma once

#include "stdafx.h"
class Rect
{
public:
	Rect() : Left(0.0f), Top(0.0f), Right(0.0f), Bottom(0.0f) {}
	Rect(float Left, float Top, float Right, float Bottom) : Left(Left), Top(Top), Right(Right), Bottom(Bottom) {}
	Rect(const Vector2& LeftTop, const Vector2& RightBottom) : Left(LeftTop.x), Top(LeftTop.y), Right(RightBottom.x), Bottom(RightBottom.y) {}
	Rect(const Rect& Value) : Left(Value.Left), Top(Value.Top), Right(Value.Right), Bottom(Value.Bottom) {}
	~Rect() {}

	Rect& operator=(const Rect& Value) { Left = Value.Left, Top = Value.Top, Right = Value.Right, Bottom = Value.Bottom; return *this; }
	bool operator==(const Rect& Value) { return{ Left == Value.Left && Top == Value.Top && Right == Value.Right && Top == Value.Top }; }
	Rect operator+(const Rect& Value) { return{ Left + Value.Left, Top + Value.Top, Right + Value.Right, Bottom + Value.Bottom }; }
	Rect operator+(const Vector2& Value) { return{ Left + Value.x, Top + Value.y, Right + Value.x, Bottom + Value.y }; }
	Rect& operator+=(const Rect& Value) { Left += Value.Left, Top += Value.Top, Right += Value.Right, Bottom += Value.Bottom; return *this; }
	Rect& operator+=(const Vector2& Value) { Left += Value.x, Top += Value.y, Right += Value.x, Bottom += Value.y; return *this; }
	Rect operator-(const Rect& Value) { return{ Left - Value.Left, Top - Value.Top, Right - Value.Right, Bottom - Value.Bottom }; }
	Rect operator-(const Vector2& Value) { return{ Left - Value.x, Top - Value.y, Right - Value.x, Bottom - Value.y }; }
	Rect& operator-=(const Rect& Value) { Left -= Value.Left, Top -= Value.Top, Right -= Value.Right, Bottom -= Value.Bottom; return *this; }
	Rect& operator-=(const Vector2& Value) { Left -= Value.x, Top -= Value.y, Right -= Value.x, Bottom -= Value.y; return *this; }

	void SetRect(float L, float T, float R, float B) { Left = L, Top = T, Right = R, Bottom = B; }
	void SetRect(const Vector2& LeftTop, const Vector2& RightBottom) { Left = LeftTop.x, Top = LeftTop.y, Right = RightBottom.x, Bottom = RightBottom.y; }
	Rect GetRect() const { Rect ReturnRect = Rect(Left, Top, Right, Bottom); return ReturnRect; }
	void Move(float x, float y) { Left += x, Top += y, Right += x, Bottom += y; }
	void Move(const Vector2& Value) { Left += Value.x, Top += Value.y, Right += Value.x, Bottom += Value.y; }

	float GetWidth() const { return Right - Left; }
	float GetHeight() const { return Bottom - Top; }
	
	float GetRight() const { return Right; }
	float GetLeft() const { return Left; }
	float GetBottom() const { return Bottom; }
	float GetTop() const { return Top; }

	Vector2 GetLeftRight() const { return Vector2(Left,Right); }
	Vector2 GetRightLeft() const { return Vector2(Right,Left); }
	Vector2 GetLeftTop() const { return Vector2(Left,Top); }
	Vector2 GetRightTop() const { return Vector2(Right,Top); }
	Vector2 GetLeftBottom() const { return Vector2(Left,Bottom);}
	Vector2 GetRightBottom() const { return Vector2(Right, Bottom); }
	Vector2 GetBottomTop() const { return Vector2(Bottom, Top); }
	Vector2 GetTopBottom() const { return Vector2(Top, Bottom); }


	void Render(HDC hdc) { Rectangle(hdc, (int)Left, (int)Top, (int)Right, (int)Bottom); }
	void RenderEllipse(HDC hdc) { Ellipse(hdc, (int)Left, (int)Top, (int)Right, (int)Bottom); }

	float Left;
	float Top;
	float Right;
	float Bottom;
};