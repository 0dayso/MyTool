// ShapeX.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tetris2.h"
#include "ShapeX.h"
#include ".\shapex.h"
#include "Define.h"


const int STT1_ID = 5001 + 1;
const int STT2_ID = 5001 + 2;
const int STT3_ID = 5001 + 3;
const int STT4_ID = 5001 + 4;

// CShapeX

IMPLEMENT_DYNAMIC(CShapeX, CStatic)
CShapeX::CShapeX()
: m_shape(SHAPE_I)
{
	CRect rect(PER_DIAMOND_LENTH, PER_DIAMOND_LENTH, PER_DIAMOND_LENTH*2, PER_DIAMOND_LENTH*2);
	m_stt1.Create("",WS_CHILD |	WS_VISIBLE, rect, this, STT1_ID );
	m_stt1.ShowWindow(SW_SHOW);
	m_stt2.Create("",WS_CHILD |	WS_VISIBLE, rect, this, STT2_ID );
	m_stt3.Create("",WS_CHILD |	WS_VISIBLE, rect, this, STT3_ID );
	m_stt4.Create("",WS_CHILD |	WS_VISIBLE, rect, this, STT4_ID );
}

CShapeX::~CShapeX()
{
}


BEGIN_MESSAGE_MAP(CShapeX, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CShapeX ��Ϣ�������


void CShapeX::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	
	CStatic::PreSubclassWindow();
}

void CShapeX::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
	
}

void CShapeX::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	switch(m_shape)
	{
	case SHAPE_I:
		{

		}

	}
}
