#include "Core.h"
#include "Input.h"
#include "Timer.h"
#include "Camera.h"
#include "Debug.h"
#include "StageManager.h"

#include "./Scene/SceneManager.h"
#include "./Resource/PathManager.h"
#include "./Resource/ResourceManager.h"
#include "./Resource/Texture.h"

#include "./Coll/CollsionManager.h"

#include "./Sound/SoundManager.h"

WindowSize Core::m_WinSize;

INIT_STATIC_VAR(Core);
bool Core::m_Loop = true;
bool Core::isDebug = true;

Core::Core()
	:m_BackBuffer(NULL)
{
	m_HDC = NULL;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//어디서 릭났는지 잡아주는 함수 (괄호는 블럭이름)
	_CrtSetBreakAlloc(32074);

//#ifdef _DEBUG
	AllocConsole();
//#endif
}

Core::~Core()
{
	SceneManager::Delete();
	PathManager::Delete();
	StageManager::Delete();
	Input::Delete();
	ResourceManager::Delete();
	CollsionManager::Delete();
	Camera::Delete();
	SoundManager::Delete();
	Keyboard::Delete();
	SAFE_DELETE(m_Timer);
	SAFE_RELEASE(m_BackBuffer);
	//GetDC를 이용하여 생성한 DC는 반드시 ReleaseDC를 해줘야한다.
	if (m_HDC != NULL)
		ReleaseDC(m_Hwnd, m_HDC);

//#ifdef _DEBUG
	FreeConsole();
//#endif
}

bool Core::Init(HINSTANCE hInst, UINT iWidth, UINT iHeight, const TCHAR* TitleName, const TCHAR* ClassName, int IconID)
{
	srand((unsigned int)time(NULL));

	m_hInst = hInst;
	m_WinSize.Width = iWidth;
	m_WinSize.Height = iHeight;

	Register(ClassName, IconID);
	CreateWnd(TitleName, ClassName);
	//현재 생성된 윈도우에 출력할 DC를 만들어준다
	m_HDC = GetDC(m_Hwnd);
	
	m_Timer = new Timer();
	if (m_Timer->Init() == false)
	{
		SAFE_DELETE(m_Timer);
		return false;
	}

	if (PathManager::Get()->Init() == false)
		return false;

	if (Input::Get()->Init() == false)
		return false;

	if (SceneManager::Get()->Init() == false)
		return false;

	if (ResourceManager::Get()->Init() == false)
		return false;

	if (CollsionManager::Get()->Init() == false)
		return false;

	if (Camera::Get()->Init() == false)
		return false;

	if (StageManager::Get()->Init() == false)
		return false;

	Camera::Get()->SetVirtualSize((float)iWidth, (float)iHeight);

	if (SoundManager::Get()->Init() == false)
		return false;

	m_BackBuffer = ResourceManager::Get()->FindTexture("BackBuffer");

	return true;
}

int Core::Run()
{
	MSG msg;

	while (m_Loop)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			Logic();
	}
	
	return (int)msg.wParam;
}

void Core::Register(const TCHAR * ClassName, int IconID)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Core::WndProc;	///함수포인터로 넘겨주는것.
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IconID));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = ClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IconID));

	RegisterClassEx(&wcex);
}

void Core::CreateWnd(const TCHAR * TitleName, const TCHAR * ClassName)
{
	m_Hwnd = CreateWindowW(ClassName, TitleName, WS_OVERLAPPEDWINDOW,	CW_USEDEFAULT, 0, m_WinSize.Width, m_WinSize.Height, NULL , NULL , m_hInst, NULL);

	if (!m_Hwnd)
		return;

	RECT rc = { 0, 0, (LONG)m_WinSize.Width, (LONG)m_WinSize.Height };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(m_Hwnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
	ShowWindow(m_Hwnd, SW_SHOW);

	UpdateWindow(m_Hwnd);
}

LRESULT Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//키보드에관한것은 wParam
	//마우스에관한것은 lParam

	//스태틱멤버함수의 특징은 this포인터가 먹지않는다.
	//그래서 스태틱함수는 스태틱변수만 사용가능하다.
	static POINT MousePos;

	switch (message)
	{
		case WM_PAINT: 
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			EndPaint(hWnd, &ps); 
		}
		break;
		case WM_SIZE:
			Core::Get()->ResizeWindow();
			break;
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					DestroyWindow(hWnd);
					break;
			}
			break;
		case WM_MOUSEMOVE:
		{
			MousePos.x = LOWORD(lParam);
			MousePos.y = HIWORD(lParam);
		}
			break;

		case WM_DESTROY:
			m_Loop = false;
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Core::Logic()
{
	m_Timer->Update();

	float Delta = m_Timer->GetDeltaTime();

	Input::Get()->Update(Delta);	
	Keyboard::Get()->Update();
	SoundManager::Get()->Update();

	if (KEYDOWN("Puase"))
	{
		if (StopTime == 1.0f)
			StopTime = 0.0f;
		else
			StopTime = 1.0f;
	}

	if (KEYPress(VK_F11))
		StopTime = 3.0f;
	else if(KEYUp(VK_F11))
		StopTime = 1.0f;

	Input(Delta * StopTime);
	Update(Delta * StopTime);
	Collision(Delta * StopTime);
	CollsionAfterUpdate(Delta * StopTime);
	Render(Delta * StopTime);
}

int Core::Input(float DeltaTime)
{
	SceneManager::Get()->Input(DeltaTime);
	return 0;
}

int Core::Update(float DeltaTime)
{
	if (KEYDOWN("DebugOnOff"))
	{
		if (isDebug == false)
			isDebug = true;
		else
			isDebug = false;
	}

	SceneManager::Get()->Update(DeltaTime);
	SceneManager::Get()->LateUpdate(DeltaTime);

	Camera::Get()->Update();
	return 0;
}	

int Core::Render(float DeltaTime)
{
	SceneManager::Get()->Render(m_BackBuffer->GetMemDC(), DeltaTime);
	Camera::Get()->Render(m_BackBuffer->GetMemDC());
	Input::Get()->RenderMouse(m_BackBuffer->GetMemDC(), DeltaTime);

	BitBlt(m_HDC, 0, 0, m_WinSize.Width, m_WinSize.Height, m_BackBuffer->GetMemDC(), 0, 0, SRCCOPY);

	char buffer[255] = {};
	sprintf_s(buffer, "Frame : %f", m_Timer->GetFps());
	Debug::OutputTitle(buffer);

	if (isDebug == false)
		return 0;

	TCHAR Buffer[255] = {};
	swprintf_s(Buffer, L"Frame : %f", m_Timer->GetFps());
	TextOutW(m_HDC, 0, 0, Buffer, lstrlen(Buffer));

	swprintf_s(Buffer, L"DeltaTime : %f", m_Timer->GetDeltaTime());
	TextOutW(m_HDC, 0, 20, Buffer, lstrlen(Buffer));

	return 0;
}

int Core::Collision(float DeltaTime)
{
	SceneManager::Get()->Collision(DeltaTime);
	CollsionManager::Get()->Collsion(DeltaTime);
	return 0;
}

int Core::CollsionAfterUpdate(float DeltaTime)
{
	SceneManager::Get()->CollsionAfterUpdate(DeltaTime);
	return 0;
}
