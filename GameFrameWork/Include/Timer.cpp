#include "stdafx.h"
#include "Timer.h"
#include "Debug.h"

Timer::Timer()
	:DeltaTime(0.0f), Fps(0.0f), LimitTime(0), TimeVar(0.0f)
	,CurTime(), PrevTime(), Count()
{
}

Timer::~Timer()
{
}

bool Timer::Init()
{
	//�ʴ� 1�ʿ� �󸶳� �����ִ�?
	QueryPerformanceFrequency(&Count);

	//�󸶳� �������׾�?
	QueryPerformanceCounter(&CurTime);

	PrevTime = CurTime;

	return true;
}

void Timer::Update()
{
	QueryPerformanceCounter(&CurTime);

	//���紩���ð� - ���������ð��� �ʴ�ī��Ʈ�� �����ָ� �����Ӱ��� ������ ���´�
	DeltaTime = (CurTime.QuadPart - PrevTime.QuadPart) / (float)Count.QuadPart;
	PrevTime = CurTime;

	Fps++;
	TimeVar += DeltaTime;
	
	if (TimeVar >= 1.0f)
	{
		ReturnFrame = Fps;
		Fps = 0.0f;
		TimeVar = 0.0f;
	}
}