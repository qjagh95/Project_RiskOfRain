#pragma once
#include "stdafx.h"

class Number;
class Layer;
class PlayTime
{
public:
	void Init(Layer* pLayer);
	void Update(float DeltaTime);
	void Render(HDC Hdc, float DeltaTime);

	void SetPlaySecond(int Value) { PlaySecond = Value; }
	void SetPlayMinit(int Value) { PlayMinit = Value; }

private:
	Number* m_Second;
	Number* m_Minit;

	static int PlaySecond;
	static int PlayMinit;

	float TimeVar;

public:
	PlayTime();
	~PlayTime();
};

