#include "Math.h"

float Math::GetDistance(const Vector2 & Src, const Vector2 & Dest)
{
	float Width = Src.x - Dest.x;
	float Height = Src.y - Dest.y;

	//������ ������ �Ұű⶧���� ��� �������� �������
	return (float)(sqrt(Width * Width + Height * Height));
}

//Src : ������ġ
//Dest : �����ġ
float Math::GetDegree(const Vector2 & Src, const Vector2 & Dest)
{
	//�غ��� ���̸� ���Ѵ�
	float Width = Dest.x - Src.x;

	//������ ���̸� ���Ѵ�
	float Lenth = GetDistance(Src, Dest);

	//�ڻ��μ�Ÿ�������Ѵ�
	float Angle = Width / Lenth;

	//������ �ڻ��μ�Ÿ���� ���Լ��� �̿��Ͽ� ���Ȱ����� ��ȯ�Ѵ�
	Angle = (float)acosf(Angle);

	//���Ȱ��� ���������� �ٲ۴�
	Angle = RadianToDgree(Angle);

	//acosf�� 180 ~ -180������ ��ȯ�ϱ⶧���� 360�� �����ֱ����Ͽ� 360���� �� ������ ����.
	//�����ġ�� y���� �� �۴ٸ� �� �� �����ִٴ� ��
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
