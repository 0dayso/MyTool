// Test3Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <vector>
#include <string>
using namespace std;


// CTest3Dlg �Ի���
class CTest3Dlg : public CDialog
{
// ����
public:
	CTest3Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CTest3Dlg();

// �Ի�������
	enum { IDD = IDD_TEST3_DIALOG };

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
	CStatic* m_pSttShow;
	vector< CStatic* > m_vecPSttShow;
	int m_iSttID;
public:
	CStatic m_stt1;
	
};
