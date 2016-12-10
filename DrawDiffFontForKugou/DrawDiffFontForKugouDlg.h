
// DrawDiffFontForKugouDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <string>


// CDrawDiffFontForKugouDlg �Ի���
class CDrawDiffFontForKugouDlg : public CDialogEx
{
// ����
public:
	CDrawDiffFontForKugouDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRAWDIFFFONTFORKUGOU_DIALOG };

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
public:
    afx_msg void OnBnClickedButtonRun();
    void ClearShow();
    void DrawShowText( const std::wstring& text, const std::wstring& font,
        int size, int factor);
    CEdit m_editText;
    CEdit m_editFont;
    CEdit m_editSize;
    CStatic m_staticSizeValue;
    CStatic m_staticShow;
    CStatic m_staticShowSizeValue;
    CEdit m_editFactor;
    afx_msg void OnBnClickedOk();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
};
