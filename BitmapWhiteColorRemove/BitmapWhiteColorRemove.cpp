// BitmapWhiteColorRemove.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <GdiPlus.h>
#include <string>

using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")

int _tmain(int argc, _TCHAR* argv[])
{
    ULONG_PTR token = 0;
    GdiplusStartupInput gdiInput;
    GdiplusStartup(&token, &gdiInput, nullptr);
    RemoveBlankBitmap(L"D:\\test\\NoteBottom.png", L"image/png");

    GdiplusShutdown(token);
	return 0;
}

