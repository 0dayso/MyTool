// ShortCut.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CShortCutApp:
// �йش����ʵ�֣������ ShortCut.cpp
//

class CShortCutApp : public CWinApp
{
public:
	CShortCutApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CShortCutApp theApp;
