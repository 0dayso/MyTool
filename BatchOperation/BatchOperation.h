
// BatchOperation.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBatchOperationApp:
// �йش����ʵ�֣������ BatchOperation.cpp
//

class CBatchOperationApp : public CWinApp
{
public:
	CBatchOperationApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBatchOperationApp theApp;