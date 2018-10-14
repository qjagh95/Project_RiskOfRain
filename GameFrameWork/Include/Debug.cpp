#include "Debug.h"
#include "Core.h"

void Debug::OutputConsole(char * Test)
{
#ifdef _DEBUG
	_cprintf(Test);
#endif
}

void Debug::OutputVisual(char * Test)
{
#ifdef _DEBUG
	OutputDebugStringA(Test);
#endif
}

void Debug::OutputTitle(char * Test)
{
#ifdef _DEBUG
	SetWindowTextA(Core::Get()->GetHwnd(), Test);
#endif
}
