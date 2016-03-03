// FindFileDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

// CFindFileDlg �Ի���
class CFindFileDlg : public CDialog
{
// ����
public:
	CFindFileDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FINDFILE_DIALOG };

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
	afx_msg void OnBnClickedButtonFindway1();
	CEdit m_editName;
	CString m_cstrShowPath;	
	void FindPerDriver(const CHAR* pszDriver, int iType);
	int m_iShowPathLeft;
	int m_iShowPathTop;
	int m_iEnterFocus;
	
	CString m_cstrFindName;
	CEdit m_editShowPath;
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual void OnOK();
public:
	afx_msg void OnEnChangeEditName();
	afx_msg void OnEnChangeEditSize();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_btnFindWay1;
	CButton m_btnFindWay2;
	afx_msg void OnBnClickedButtonFindway2();
	CEdit m_editSize;
	DWORD m_dwLowSize;
	DWORD m_dwHighSize;
	int m_iFindByWhat;			//ͨ��ʲô��ʽ����
	int m_iLineNum;
	bool m_bIsFinding;			//�Ƿ����ڲ���,ͬһʱ��ֻ�ܽ���һ������
	
};
