#include "Math.h"

float Math::GetDistance(const Vector2 & Src, const Vector2 & Dest)
{
	float Width = Src.x - Dest.x;
	float Height = Src.y - Dest.y;

	//어차피 제곱을 할거기때문에 어떤걸 먼저빼던 상관없다
	return (float)(sqrt(Width * Width + Height * Height));
}

//Src : 현재위치
//Dest : 대상위치
float Math::GetDegree(const Vector2 & Src, const Vector2 & Dest)
{
	//밑변의 길이를 구한다
	float Width = Dest.x - Src.x;

	//빗변의 길이를 구한다
	float Lenth = GetDistance(Src, Dest);

	//코사인세타값을구한다
	float Angle = Width / Lenth;

	//구해준 코사인세타값을 역함수를 이용하여 라디안값으로 변환한다
	Angle = (float)acosf(Angle);

	//라디안값을 각도값으로 바꾼다
	Angle = RadianToDgree(Angle);

	//acosf는 180 ~ -180까지만 반환하기때문에 360을 맞춰주기위하여 360에서 내 각도를 뺀다.
	//대상위치의 y값이 더 작다면 더 더 높이있다는 뜻
	if (Dest.y < Src.y)
	{
		Angle = 360.0f - Angle;

		if (Angle >= 360.0f)
			Angle = 0.0f;
	}
	return Angle;
}

float Math::DgreeToRadian(float Dgree)
{
	return Dgree * PI / 180.f;
}

float Math::RadianToDgree(float Radian)
{
	return Radian * 180.f / PI;
}

int Math::RandomRange(int R1, int R2)
{
	return (int)(rand() % (R2 - R1 + 1)) + R1;
}
