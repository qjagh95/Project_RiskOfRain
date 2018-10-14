#pragma once
class Timer
{
public:
	Timer();
	~Timer();
	
	bool Init();
	void Update();

	float GetDeltaTime() const { return DeltaTime; }
	float GetFps() const { return ReturnFrame; }

private:
	LARGE_INTEGER CurTime;
	LARGE_INTEGER PrevTime;
	LARGE_INTEGER Count;	
	float DeltaTime;
	float TimeVar;
	float Fps;
	float ReturnFrame;
	int LimitTime;

};

