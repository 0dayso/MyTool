
// HttpRequestUse.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHttpRequestUseApp:
// �йش����ʵ�֣������ HttpRequestUse.cpp
//

class CHttpRequestUseApp : public CWinApp
{
public:
	CHttpRequestUseApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHttpRequestUseApp theApp;