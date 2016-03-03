// ShortCutDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShortCut.h"
#include "ShortCutDlg.h"
#include ".\shortcutdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CShortCutDlg �Ի���



CShortCutDlg::CShortCutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShortCutDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShortCutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SHOW, m_editShow);
}

BEGIN_MESSAGE_MAP(CShortCutDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnBnClickedButtonChange)
	ON_EN_CHANGE(IDC_EDIT_SHOW, OnEnChangeEditShow)
	ON_BN_CLICKED(IDC_BTN_Divide, OnBnClickedBtnDivide)
END_MESSAGE_MAP()


// CShortCutDlg ��Ϣ�������

BOOL CShortCutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	ZeroMemory(m_pszPath, MAX_PATH);
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CShortCutDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CShortCutDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CShortCutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CShortCutDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	UINT nFileNum = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);//DragQueryFileΪ0xFFFFFFFF��ʱ�򷵻���ҷ�ļ��ĸ���
	DragQueryFile(hDropInfo, nFileNum - 1, m_pszPath, MAX_PATH);//�����ҷ�����һ���ļ����ļ���
	DragFinish(hDropInfo);	//����ǵ��ͷŵ�hDropInfo
	TRACEONE("%s\n",m_pszPath);
	m_editShow.SetWindowText(m_pszPath);
	m_editShow.UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}

void CShortCutDlg::OnBnClickedButtonChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pszPath[0] == 0 )
	{
		CString cstrText;
		m_editShow.GetWindowText(cstrText);
		if (cstrText[0] == 0)
		{
			m_editShow.SetWindowText("û���ļ�");
			m_editShow.UpdateData(FALSE);
			return;
		}
		sprintf(m_pszPath, "%s", cstrText);
		//strcpy(m_pszPath, cstrText);	
		TRACE("IN   %s\n",m_pszPath );

	}

	TRACE("%s\n", m_pszPath);
	FILE* fp;
	fp = fopen(m_pszPath, "r");
	if (fp == NULL)
	{
		CString cstrText = "�򲻿�";
		cstrText += m_pszPath;
		m_editShow.SetWindowText(cstrText);
		m_editShow.UpdateData(FALSE);
		return;
	}
	FILE* fpOut;
	CString cstrNewPath = RemoveSuffix(m_pszPath);
	cstrNewPath += "_cut";
	cstrNewPath += GetSuffix(m_pszPath);
	TRACEONE("%s\n", cstrNewPath);


	fpOut = fopen(cstrNewPath, "w");
	if (fpOut == NULL)
	{
		CString cstrText = "�����ļ�ʧ��";
		
		m_editShow.SetWindowText(cstrText);
		m_editShow.UpdateData(FALSE);
		return;
	}
	CHAR cstrRead[LINE_NUM];
	CHAR szAdd;
	int iRes = 0;

	CString cstrShowOut;
	CString cstrTemp;

	while( (iRes = fread(cstrRead, 1, LINE_NUM, fp)) > 0 )
	{
		cstrShowOut = "";
		TRACEONE("%d    %c\n", iRes, cstrRead[iRes -1]);
		
		fwrite(cstrRead, 1, iRes, fpOut);
		for (int j = 0; j < iRes; j++)
		{
			cstrTemp.Format("%c", cstrRead[j]);
			cstrShowOut += cstrTemp;
		}

		int i = 0;
		while(i < iRes)
		{
			if (IsDBCSLeadByte(cstrRead[i]))// ֻ�������жϵ�һ���ֽڵ�    abc��
			{
				i = i+2;
			}
			else
			{
				i++;
			}
		}

		if ( i > iRes )
		{			
			fread(cstrRead, 1, 1, fp);
			fwrite(cstrRead, 1, 1, fpOut);
			cstrTemp.Format("%c", cstrRead[0]);
			cstrShowOut += cstrTemp;		
		}

		if (iRes == LINE_NUM)
		{
			cstrRead[0] = '\r';
			cstrRead[1] = '\n';
			fwrite(cstrRead, 1,2 , fpOut);
			for (int j = 0; j < 2; j++)
			{
				cstrTemp.Format("%c", cstrRead[j]);
				cstrShowOut += cstrTemp;
			}
		}
		cstrShowOut += "\r\n";
		TRACE("%s", cstrShowOut);
		
	}	

	fclose(fp);
	fclose(fpOut);
	MessageBox("Wait");
	MessageBox("Finish");
}
CString CShortCutDlg::RemoveSuffix(CString cstrRhs)
{
	int i = 0;
	int iLen = cstrRhs.GetLength();
	int pos = 0;
	for (; i < iLen; i++ )
	{
		if ( cstrRhs.GetAt(i) == '.')
		{
			pos = i;
		}
	}
	ASSERT(pos > 0);
	CString cstrRes = cstrRhs.Left(pos);
	return cstrRes;
}
CString CShortCutDlg::GetSuffix(CString cstrRhs)
{
	int i = 0;
	int iLen = cstrRhs.GetLength();
	int pos = 0;
	for (; i < iLen; i++ )
	{
		if ( cstrRhs.GetAt(i) == '.')
		{
			pos = i;
		}
	}
	ASSERT(pos > 0);
	CString cstrRes = cstrRhs.Right(iLen - pos  ); //a.txt
	return cstrRes;
}
void CShortCutDlg::OnEnChangeEditShow()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
}

void CShortCutDlg::OnBnClickedBtnDivide()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pszPath[0] == 0 )
	{
		CString cstrText;
		m_editShow.GetWindowText(cstrText);
		if (cstrText[0] == 0)
		{
			m_editShow.SetWindowText("û���ļ�");
			m_editShow.UpdateData(FALSE);
			return;
		}
		sprintf(m_pszPath, "%s", cstrText);
		//strcpy(m_pszPath, cstrText);	
		TRACE("IN   %s\n",m_pszPath );

	}

	TRACE("%s\n", m_pszPath);
	FILE* fp;
	fp = fopen(m_pszPath, "r");
	if (fp == NULL)
	{
		CString cstrText = "�򲻿�";
		cstrText += m_pszPath;
		m_editShow.SetWindowText(cstrText);
		m_editShow.UpdateData(FALSE);
		return;
	}
	FILE* fpOut;
	CString cstrNewPath;
	CString cstrFileName = RemoveSuffix(m_pszPath);
	cstrNewPath += cstrFileName;
	cstrNewPath += "_001";
	CString cstrSuffix = GetSuffix(m_pszPath);
	cstrNewPath += cstrSuffix;
	TRACEONE("%s\n", cstrNewPath);


	fpOut = fopen(cstrNewPath, "w");
	if (fpOut == NULL)
	{
		CString cstrText = "�����ļ�ʧ��";

		m_editShow.SetWindowText(cstrText);
		m_editShow.UpdateData(FALSE);
		return;
	}
	CHAR cstrRead[BOOK_FULL_COUNT];
	CHAR szAdd;
	int iRes = 0;
	int ibook = 1;

	CString cstrShowOut;
	CString cstrTemp;

	while( (iRes = fread(cstrRead, 1, BOOK_FULL_COUNT, fp)) > 0 )
	{
		cstrShowOut = "";
		//TRACEONE("%d    %c\n", iRes, cstrRead[iRes -1]);
		fwrite(cstrRead, 1, iRes, fpOut);
		ibook++;
		fclose(fpOut);	

		cstrTemp.Format("_%03d", ibook);
		cstrNewPath = "";		
		cstrNewPath += cstrFileName;
		cstrNewPath += cstrTemp;	
		cstrNewPath += cstrSuffix;

		fpOut = fopen(cstrNewPath, "w");
		if (fpOut == NULL)
		{
			CString cstrText = "�����ļ�ʧ��";

			m_editShow.SetWindowText(cstrText);
			m_editShow.UpdateData(FALSE);
			return;
		}

	}	

	fclose(fp);
	
}
