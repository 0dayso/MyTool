// MyStatic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tetris2.h"
#include "MyStatic.h"


// CMyStatic

IMPLEMENT_DYNAMIC(CMyStatic, CStatic)
CMyStatic::CMyStatic()
:m_colBkgColor(RGB(255, 255, 255))
{
}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyStatic ��Ϣ�������

void CMyStatic::SetBkgColor(COLORREF col)
{
	m_colBkgColor = col;
}

void CMyStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()	
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(rect);
	dc.FillRect(rect, &CBrush(m_colBkgColor));	
}