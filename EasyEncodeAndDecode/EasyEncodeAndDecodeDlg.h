
// EasyEncodeAndDecodeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CEasyEncodeAndDecodeDlg �Ի���
class CEasyEncodeAndDecodeDlg : public CDialogEx
{
// ����
public:
	CEasyEncodeAndDecodeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EASYENCODEANDDECODE_DIALOG };

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
	afx_msg void OnBnClickedButtonEncode();
	CEdit m_editEncodingText;
	CEdit m_editFinishEncodePath;
	afx_msg void OnBnClickedButtonDecode();
	CEdit m_editDecodingPath;
};
