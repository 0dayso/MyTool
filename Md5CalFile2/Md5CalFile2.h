
// Md5CalFile2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMd5CalFile2App:
// �йش����ʵ�֣������ Md5CalFile2.cpp
//

class CMd5CalFile2App : public CWinApp
{
public:
	CMd5CalFile2App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMd5CalFile2App theApp;