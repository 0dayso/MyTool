// CopyUsefulStringToNewFile.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CCopyUsefulStringToNewFileApp:
// �йش����ʵ�֣������ CopyUsefulStringToNewFile.cpp
//

class CCopyUsefulStringToNewFileApp : public CWinApp
{
public:
	CCopyUsefulStringToNewFileApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCopyUsefulStringToNewFileApp theApp;
