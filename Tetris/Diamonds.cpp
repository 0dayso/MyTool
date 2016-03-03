// Diamonds.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Diamonds.h"
#include ".\diamonds.h"


// CDiamonds

IMPLEMENT_DYNAMIC(CDiamonds, CWnd)
CDiamonds::CDiamonds()
: m_colDiamonds( RGB(0, 255, 0) )
, m_colBorder( RGB(0, 255, 0) )

{
	m_sizePos.cx = 0;
	m_sizePos.cy = 0;
	m_sizeWidth.cx = 10;
	m_sizeWidth.cy = 10;
}

CDiamonds::~CDiamonds()
{
}


BEGIN_MESSAGE_MAP(CDiamonds, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CDiamonds ��Ϣ�������


void CDiamonds::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	CBrush brush(m_colDiamonds);
	CBrush* pOldBrush = dc.SelectObject(&brush);
	CPen pen(PS_SOLID, 1, m_colBorder);
	CPen* pOldPen = dc.SelectObject(&pen);
	dc.Rectangle( m_sizePos.cx, m_sizePos.cy, m_sizeWidth.cx + m_sizePos.cx, m_sizeWidth.cy + m_sizePos.cy );
	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}

int CDiamonds::GetWidth()
{
	return m_sizeWidth.cx;
}

void CDiamonds::MoveWindowBySize()
{	
	MoveWindow(m_sizePos.cx, m_sizePos.cy, m_sizeWidth.cx, m_sizeWidth.cy);
}

//BOOL CDiamonds::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//	if ( pMsg->message == WM_KEYDOWN )
//	{
//		CRect rect;
//		GetWindowRect(&rect);
//
//		switch( pMsg->wParam )
//		{
//		case VK_LEFT:
//			{
//				rect.OffsetRect(-m_iLenth, 0);
//				this->MoveWindow(rect);
//			}
//		}		
//	
//	}
//
//	return CWnd::PreTranslateMessage(pMsg);
//}
