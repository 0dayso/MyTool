// CopyUsefulStringToNewFileDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CCopyUsefulStringToNewFileDlg �Ի���
class CCopyUsefulStringToNewFileDlg : public CDialog
{
// ����
public:
	CCopyUsefulStringToNewFileDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COPYUSEFULSTRINGTONEWFILE_DIALOG };

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
	afx_msg void OnBnClickedButtonGet();
	CEdit m_editSource;
	CEdit m_eidtIncludeString;
	CEdit m_editOutput;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButtonGetForLog();

};
