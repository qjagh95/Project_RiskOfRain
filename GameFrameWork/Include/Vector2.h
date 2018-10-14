#pragma once

class Vector2
{
public:
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float _x, float _y) :x(_x), y(_y) {}
	Vector2(const Vector2& Value) : x(Value.x), y(Value.y) {}
	Vector2(const POINT& Value) : x((float)Value.x), y((float)Value.y) {}
	~Vector2() {}

	bool operator==(const Vector2& _Value) const { return{ x == _Value.x && y == _Value.y }; }
	bool operator<= (const Vector2& _Value) const { return{ x <= _Value.x && y <= _Value.y }; }
	bool operator>= (const Vector2& _Value) const { return{ x >= _Value.x && y >= _Value.y }; }
	bool operator> (const Vector2& _Value) const { return{ x > _Value.x && y > _Value.y }; }
	bool operator< (const Vector2& _Value) const { return{ x < _Value.x && y < _Value.y }; }
	bool operator!= (const Vector2& _Value) const { return{ x != _Value.x && y != _Value.y }; }
	bool operator!= (float _Value) const { return{ x != _Value && y != _Value }; }
	
	Vector2& operator=(const Vector2& _Value) { x = _Value.x, y = _Value.y; return *this; }
	Vector2 operator+(const Vector2&_Value) const { return{ x + _Value.x , y + _Value.y }; }
	Vector2 operator+(float _Value) const { return{ x + _Value , y + _Value }; }
	Vector2 operator-(const Vector2&_Value) const { return{ x - _Value.x , y - _Value.y }; }
	Vector2 operator-(float _Value) const { return{ x - _Value , y - _Value }; }
	Vector2 operator/(const Vector2&_Value) const { return{ x / _Value.x , y / _Value.y }; }
	Vector2 operator/(float _Value) const { return{ x / _Value , y / _Value }; }
	Vector2 operator*(const Vector2&_Value) const { return{ x * _Value.x , y * _Value.y }; }
	Vector2 operator*(float _Value) const { return{ x * _Value , y * _Value }; }
	Vector2& operator+=(const Vector2&_Value) { x += _Value.x, y += _Value.y; return *this; }
	Vector2& operator+=(float _Value) { x += _Value, y += _Value; return *this; }
	Vector2& operator-=(const Vector2&_Value) { x -= _Value.x, y -= _Value.y; return *this; }
	Vector2& operator-=(float _Value) { x -= _Value, y -= _Value; return *this; }
	Vector2& operator*=(const Vector2&_Value) { x *= _Value.x, y *= _Value.y; return *this; }
	Vector2& operator*=(float _Value) { x *= _Value, y *= _Value; return *this; }
	Vector2& operator/=(const Vector2& _Value) { x /= _Value.x, y /= _Value.y; return *this; }
	Vector2& operator/=(float _Value) { x /= _Value, y /= _Value; return *this; }

	float GetX() { return x; }
	float GetY() { return y; }
	float GetHalfX() { return x * 0.5f; }
	float GetHalfY() { return y * 0.5f; }
	Vector2 Half() { return{ GetHalfX(), GetHalfY() }; }

public:
	float x;
	float y;

	static const Vector2 Right;
	static const Vector2 Left;
	static const Vector2 Down;
	static const Vector2 Up;
	static const Vector2 One;
	static const Vector2 Zero;
};