
// DrawDiffFontForKugou.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDrawDiffFontForKugouApp:
// �йش����ʵ�֣������ DrawDiffFontForKugou.cpp
//

class CDrawDiffFontForKugouApp : public CWinApp
{
public:
	CDrawDiffFontForKugouApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDrawDiffFontForKugouApp theApp;