
// Md5CalFile2Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMd5CalFile2Dlg �Ի���
class CMd5CalFile2Dlg : public CDialogEx
{
// ����
public:
	CMd5CalFile2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MD5CALFILE2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
    CEdit m_editPath;
    CEdit m_showMd5Lower;
    CEdit m_showMd5Upper;
    afx_msg void OnDropFiles(HDROP hDropInfo);
};
