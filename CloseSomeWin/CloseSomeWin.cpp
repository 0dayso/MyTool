// CloseSomeWin.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 0; i < 10; ++i)
	{
		HWND hWnd = FindWindow(nullptr, L"����");
		if (!hWnd)
		{
			hWnd = FindWindow(nullptr, L"��ʽ");
			if (!hWnd)
			{
				break;
			}
		}
		SendMessage(hWnd, WM_CLOSE, 0, 0);
		Sleep(2000);
	}

	return 0;
}

