// Tetris2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CTetris2App:
// �йش����ʵ�֣������ Tetris2.cpp
//

class CTetris2App : public CWinApp
{
public:
	CTetris2App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTetris2App theApp;
