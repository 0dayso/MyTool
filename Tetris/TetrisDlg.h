// TetrisDlg.h : ͷ�ļ�
//

#pragma once

#include "Diamonds.h"
#include "ShapeI.h"
// CTetrisDlg �Ի���
class CTetrisDlg : public CDialog
{
// ����
public:
	CTetrisDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TETRIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	CDiamonds m_dmdLine;
	EN_DIRECTION m_enDirection;
	CShapeI m_shapeI;
	CShape m_shapeL;
};
