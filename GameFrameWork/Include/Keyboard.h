#pragma once

#define MAX_INPUT_KEY 255
#define MAX_INPUT_MOUSE 8
class Keyboard
{
public:
	static Keyboard* Get();
	static void Delete();

	void Update();

	//Ű�� ���ȴ����� ���� Ȯ��
	//DWORD key ���� �ƽ�Ű�ڵ�Ǵ� ����Ű���尪
	bool KeyDown(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_DOWN; }
	bool KeyUp(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_UP; }
	bool KeyPress(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_PRESS; }

private:
	Keyboard();
	~Keyboard();
	static Keyboard* instance;

	//byte��(unsigned char)�迭 255�� ����
	BYTE CurKeyState[MAX_INPUT_KEY]; //����
	BYTE PrevKeyState[MAX_INPUT_KEY]; //��������
	BYTE keyMap[MAX_INPUT_KEY]; //true false����

	//Ű���� ���¿����� enum
	enum 
	{ 
		KEY_INPUT_STATUS_NONE = 0, 
		KEY_INPUT_STATUS_DOWN, 
		KEY_INPUT_STATUS_UP, 
		KEY_INPUT_STATUS_PRESS,
	};
};