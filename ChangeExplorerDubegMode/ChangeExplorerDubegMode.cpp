// ChangeExplorerDubegMode.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	printf("��������explorer.exe����shell���Եķ���:\n");
	printf("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer");
	printf("DesktopProcess DWORD:����ֵ(0�ر� 1��) \n");
	DWORD iExporerMode=0;
	scanf("%d", &iExporerMode);
	HKEY hKey;
	LONG lRet(-1);
	lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer", 0, KEY_WRITE,&hKey);	
	if ( lRet == ERROR_SUCCESS )
	{
		DWORD dwLen = sizeof(iExporerMode);
		lRet = RegSetValueEx(hKey,"DesktopProcess",NULL,REG_DWORD,(BYTE*)(&iExporerMode), dwLen );
	}

	if (  lRet == ERROR_SUCCESS )
	{
		printf("���óɹ�\n");
	}
	else
	{
		printf("����ʧ��\n");
	}	
	system("pause");
	return 0;
}

