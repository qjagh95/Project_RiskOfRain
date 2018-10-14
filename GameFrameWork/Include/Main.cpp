#include "stdafx.h"
#include "Core.h"
#include "resource.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	if (GET_INSTANCE(Core)->Init(hInstance, 1800, 1000, L"FrameWork", L"FrameWork", IDI_ICON1) == false)
	{
		DELETE_INSTANCE(Core);
		return 0;
	}

	int ReturnValue = GET_INSTANCE(Core)->Run();
	DELETE_INSTANCE(Core);

	return ReturnValue;
}