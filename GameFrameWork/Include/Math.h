#pragma once
#include "stdafx.h"

class Math
{
public:
	static float GetDistance(const Vector2& Src, const Vector2& Dest);
	static float GetDegree(const Vector2& Src, const Vector2& Dest);

	static float DgreeToRadian(float Dgree);
	static float RadianToDgree(float Radian);
	static int RandomRange(int R1, int R2);
};

