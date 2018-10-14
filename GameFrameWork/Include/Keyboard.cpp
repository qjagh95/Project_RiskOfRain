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

//������ ������Ʈ�� ���ư��� �� ������ ������Ʈ ����
void Keyboard::Update()
{
	//���簪������ �������� ����
	memcpy(PrevKeyState, CurKeyState, sizeof(PrevKeyState));
	//�������ְ� �ʱ�ȭ
	ZeroMemory(CurKeyState, sizeof(CurKeyState));
	ZeroMemory(keyMap, sizeof(keyMap));
	//256���� Ű���� ���¸� keyState������ �����ϴ� �Լ�
	GetKeyboardState(CurKeyState); 
	//256���� Ű�� ���� �˻�������ϱ⶧���� 256���ݺ�
	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{
		//0x80 ����Ű���� �ƽ�Ű�ڵ尡 �´�? �� ã�Ƴ�������
		//�ƽ�Ű���̸� 0 �ƴϸ� 128
		BYTE key = CurKeyState[i] & 0x80;
		//keystate�� �ƽ�Ű���̸� 0 �ƴϸ� 1
		CurKeyState[i] = key ? 1 : 0;
		//�������¿� ���Ѵ�
		if (PrevKeyState[i] == 0 && CurKeyState[i] == 1)
			keyMap[i] = KEY_INPUT_STATUS_DOWN; //���� 0, ���� 1 - KeyDown
		else if (PrevKeyState[i] == 1 && CurKeyState[i] == 0)
			keyMap[i] = KEY_INPUT_STATUS_UP; //���� 1, ���� 0 - KeyUp
		else if (PrevKeyState[i] == 1 && CurKeyState[i] == 1)
			keyMap[i] = KEY_INPUT_STATUS_PRESS; //���� 1, ���� 1 - KeyPress
		else
			keyMap[i] = KEY_INPUT_STATUS_NONE;
	}
}

Keyboard::Keyboard()
{
	//������ �޸� 0���� �ʱ�ȭ
	ZeroMemory(CurKeyState, sizeof(CurKeyState));
	ZeroMemory(PrevKeyState, sizeof(PrevKeyState));
	ZeroMemory(keyMap, sizeof(keyMap));
}

Keyboard::~Keyboard()
{
}
