// DivideStringDailyUse.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CDivideStringDailyUseApp:
// �йش����ʵ�֣������ DivideStringDailyUse.cpp
//

class CDivideStringDailyUseApp : public CWinApp
{
public:
	CDivideStringDailyUseApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDivideStringDailyUseApp theApp;
