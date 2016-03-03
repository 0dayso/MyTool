// CntCodeLineDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

const int READ_ONCE = 1024;
// CCntCodeLineDlg �Ի���
class CCntCodeLineDlg : public CDialog
{
// ����
public:
	CCntCodeLineDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CNTCODELINE_DIALOG };

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
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CEdit m_editFile;
	afx_msg void OnBnClickedBtnCnt();
	double m_dCntLines;
	double cntLines(const CString& cstrFileName);
	void Findfile( const CString& cstrFolderFile);

	//�����ļ���׺��,�ָ��ļ���
	CString GetSuffix(const CString& cstrPath);
};
