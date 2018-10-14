#pragma once
#include "stdafx.h"
#include <list>

struct WindowSize
{
	WindowSize() : Width(0), Height(0) {}
	WindowSize(UINT Width, UINT Height) : Width(Width), Height(Height) {}
	WindowSize(int Width, int Height) : Width((UINT)Width), Height((UINT)Height) {}

	~WindowSize() {}

	UINT Width;
	UINT Height;
};

class Texture;
class Timer;
class Core
{
public:
	bool Init(HINSTANCE hInst, UINT iWidth, UINT iHeight, const TCHAR* TitleName, const TCHAR* ClassName, int IconID);
	int Run();

	HINSTANCE GetHinstance() const { return m_hInst; }
	HWND GetHwnd() const { return m_Hwnd; }
	static WindowSize GetWinSize() { return m_WinSize; }
	static Vector2 GetWinSizeVector2() { Vector2 Temp; Temp.x = (float)m_WinSize.Width, Temp.y = (float)m_WinSize.Height; return Temp; }
	HDC GetHDC() const { return m_HDC; }
	void ResizeWindow() { RECT rc = {}; GetClientRect(m_Hwnd, &rc); m_WinSize.Width = rc.right - rc.left; m_WinSize.Height = rc.bottom - rc.top; }
	void DebugModeOn() { isDebug = true; }
	void DebugModeOff() { isDebug = false; }
	bool GetIsDebugMode() { return isDebug; }

private:
	HINSTANCE m_hInst;
	HWND m_Hwnd;
	static WindowSize m_WinSize;
	HDC m_HDC;
	Timer *m_Timer;
	Texture* m_BackBuffer;
	static bool isDebug;

	float StopTime = 1.0f;

private:
	void Register(const TCHAR* ClassName, int IconID);
	void CreateWnd(const TCHAR* TitleName, const TCHAR* ClassName);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Logic();
	int Input(float DeltaTime);
	int Update(float DeltaTime);
	int Collision(float DeltaTime);
	int CollsionAfterUpdate(float DeltaTime);
	int Render(float DeltaTime);

	static bool m_Loop;

	CLASS_IN_SINGLE(Core)
};

