
// HttpRequestUseDlg.h : ͷ�ļ�
//

#pragma once


// CHttpRequestUseDlg �Ի���
class CHttpRequestUseDlg : public CDialogEx
{
// ����
public:
	CHttpRequestUseDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HTTPREQUESTUSE_DIALOG };

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
    afx_msg void OnBnClickedButtonSyncGet();
    afx_msg void OnBnClickedButtonSyncPost();
    afx_msg void OnBnClickedButtonAsyncGet();
    afx_msg void OnBnClickedButtonAsyncPost();
};
