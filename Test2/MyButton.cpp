// MyButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test2.h"
#include "MyButton.h"
#include ".\mybutton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)
CMyButton::CMyButton()
{
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()



// CMyButton ��Ϣ�������


void CMyButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	MoveWindow(100, 100, 100, 200);

	CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyButton::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	MoveWindow(0, 0, 100, 200);
	CButton::OnKeyUp(nChar, nRepCnt, nFlags);
}
