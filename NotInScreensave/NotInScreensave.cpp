// NotInScreensave.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "NotInScreensave.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
namespace TIMER_ID
{
    enum TIMER_ID
    {    
        TIMER_SIMULATE_MOUSE_MOVE = 100,
        TIMER_SIMULATE_KEYBOARD = 101,
    };
};


// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_NOTINSCREENSAVE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NOTINSCREENSAVE));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NOTINSCREENSAVE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_NOTINSCREENSAVE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void SimulateMouseMove()
{
    MOUSEINPUT mi = {0};
    mi.dx = 0xfffff;
    mi.dy = 0xffff/2;
    mi.mouseData = 0;
    mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
    mi.dwExtraInfo = 0;
    mi.time = 0;
    INPUT inputA = {0};
    inputA.type = INPUT_MOUSE;
    inputA.mi = mi;
    SendInput(1, &inputA, sizeof(inputA));
}

void SimulateKeyboard()
{
    INPUT inputKeyboard = {0};
    inputKeyboard.type = INPUT_KEYBOARD;
    inputKeyboard.ki.wVk = VK_F24;//������û�еİ���
    SendInput(1, &inputKeyboard, sizeof(inputKeyboard));
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
    case WM_TIMER:
        {
            switch(wParam)
            {
            case TIMER_ID::TIMER_SIMULATE_MOUSE_MOVE:
                {
                    SimulateMouseMove();   
                    break;
                }
            case TIMER_ID::TIMER_SIMULATE_KEYBOARD:
                {
                    SimulateKeyboard();
                    break;
                }
            }
            
            break;
        }
    case WM_KEYDOWN:
        {
            switch(wParam)
            {
                //��������һ��ͨ��ģ������¼�
            case 'A':
                {                    
                    SetTimer(hWnd, TIMER_ID::TIMER_SIMULATE_MOUSE_MOVE, 2000, NULL);
                    break;
                }
            case  'B':
                {
                    KillTimer(hWnd, TIMER_ID::TIMER_SIMULATE_MOUSE_MOVE);
                    break;
                }
                //������������ģ������¼�
            case 'C':
                {
                    SetTimer(hWnd, TIMER_ID::TIMER_SIMULATE_KEYBOARD, 2000, NULL);
                    break;
                }
            case 'D':
                {
                    KillTimer(hWnd, TIMER_ID::TIMER_SIMULATE_KEYBOARD);
                    break;
                }
            case VK_F24:
                {
                    OutputDebugString(L"VK_F24 Key down\t");
                    break;
                }
                //������������ͨ���ر�ϵͳ�������ã� Σ�գ���ı�ϵͳֵ������������˳�����Ļ�ԭ��ֵ��
            case 'Z':
                {
                    SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, FALSE, NULL, 0);
                    break;
                }  
            }
            break;
        }
    case WM_SYSCOMMAND:
        {
            switch(wParam)
            {
            case SC_SCREENSAVE:
                {
                    OutputDebugString(L"SC_SCREENSAVE\n");
                    break;
                }
            case SC_MONITORPOWER:
                {
                    OutputDebugString(L"SC_MONITORPOWER\n");
                    break;
                }
            }
            DefWindowProc(hWnd, message, wParam, lParam);
        }   
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
