#include "stdafx.h"
#include "Keyboard.h"

Keyboard* Keyboard::instance = NULL;
Keyboard * Keyboard::Get()
{
	if (instance == NULL)
		instance = new Keyboard();

	return instance;
}

void Keyboard::Delete()
{
	if (instance != NULL)
		delete instance;
}

//메인의 업데이트가 돌아가기 전 무조건 업데이트 실행
void Keyboard::Update()
{
	//현재값변수를 이전값에 복사
	memcpy(PrevKeyState, CurKeyState, sizeof(PrevKeyState));
	//복사해주고 초기화
	ZeroMemory(CurKeyState, sizeof(CurKeyState));
	ZeroMemory(keyMap, sizeof(keyMap));
	//256개의 키값의 상태를 keyState변수에 저장하는 함수
	GetKeyboardState(CurKeyState); 
	//256개의 키를 전부 검사해줘야하기때문에 256번반복
	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{
		//0x80 들어온키값이 아스키코드가 맞니? 를 찾아내기위함
		//아스키값이면 0 아니면 128
		BYTE key = CurKeyState[i] & 0x80;
		//keystate에 아스키값이면 0 아니면 1
		CurKeyState[i] = key ? 1 : 0;
		//이전상태와 비교한다
		if (PrevKeyState[i] == 0 && CurKeyState[i] == 1)
			keyMap[i] = KEY_INPUT_STATUS_DOWN; //이전 0, 현재 1 - KeyDown
		else if (PrevKeyState[i] == 1 && CurKeyState[i] == 0)
			keyMap[i] = KEY_INPUT_STATUS_UP; //이전 1, 현재 0 - KeyUp
		else if (PrevKeyState[i] == 1 && CurKeyState[i] == 1)
			keyMap[i] = KEY_INPUT_STATUS_PRESS; //이전 1, 현재 1 - KeyPress
		else
			keyMap[i] = KEY_INPUT_STATUS_NONE;
	}
}

Keyboard::Keyboard()
{
	//생성때 메모리 0으로 초기화
	ZeroMemory(CurKeyState, sizeof(CurKeyState));
	ZeroMemory(PrevKeyState, sizeof(PrevKeyState));
	ZeroMemory(keyMap, sizeof(keyMap));
}

Keyboard::~Keyboard()
{
}
