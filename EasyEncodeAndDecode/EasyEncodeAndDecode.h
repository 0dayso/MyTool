
// EasyEncodeAndDecode.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEasyEncodeAndDecodeApp:
// �йش����ʵ�֣������ EasyEncodeAndDecode.cpp
//

class CEasyEncodeAndDecodeApp : public CWinApp
{
public:
	CEasyEncodeAndDecodeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEasyEncodeAndDecodeApp theApp;