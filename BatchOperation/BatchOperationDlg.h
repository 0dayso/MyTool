
// BatchOperationDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CBatchOperationDlg �Ի���
class CBatchOperationDlg : public CDialogEx
{
// ����
public:
	CBatchOperationDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BATCHOPERATION_DIALOG };

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
    afx_msg void OnBnClickedOk();
    CEdit m_editPath;
    CEdit m_editCondition;
    CEdit m_editAddBeg;
    CEdit m_editAddEnd;
    afx_msg void OnDropFiles(HDROP hDropInfo);
    afx_msg void OnBnClickedButtonChangFileString();
};
