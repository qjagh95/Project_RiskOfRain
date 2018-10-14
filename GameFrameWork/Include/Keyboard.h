#pragma once

#define MAX_INPUT_KEY 255
#define MAX_INPUT_MOUSE 8
class Keyboard
{
public:
	static Keyboard* Get();
	static void Delete();

	void Update();

	//키가 눌렸는지에 대한 확인
	//DWORD key 값은 아스키코드또는 가상키보드값
	bool KeyDown(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_DOWN; }
	bool KeyUp(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_UP; }
	bool KeyPress(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_PRESS; }

private:
	Keyboard();
	~Keyboard();
	static Keyboard* instance;

	//byte형(unsigned char)배열 255개 선언
	BYTE CurKeyState[MAX_INPUT_KEY]; //상태
	BYTE PrevKeyState[MAX_INPUT_KEY]; //이전상태
	BYTE keyMap[MAX_INPUT_KEY]; //true false리턴

	//키보드 상태에따른 enum
	enum 
	{ 
		KEY_INPUT_STATUS_NONE = 0, 
		KEY_INPUT_STATUS_DOWN, 
		KEY_INPUT_STATUS_UP, 
		KEY_INPUT_STATUS_PRESS,
	};
};