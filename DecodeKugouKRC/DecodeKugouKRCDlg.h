
// DecodeKugouKRCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <string>


// CDecodeKugouKRCDlg �Ի���
class CDecodeKugouKRCDlg : public CDialogEx
{
// ����
public:
	CDecodeKugouKRCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DECODEKUGOUKRC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnDropFiles(HDROP hDropInfo);
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnDecode();
    bool DealBase64(std::wstring& target);
    CEdit m_editKRCID;

};
