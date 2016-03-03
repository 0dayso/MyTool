// CntCodeLineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CntCodeLine.h"
#include "CntCodeLineDlg.h"
#include ".\cntcodelinedlg.h"

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


// CCntCodeLineDlg �Ի���



CCntCodeLineDlg::CCntCodeLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCntCodeLineDlg::IDD, pParent),m_dCntLines()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCntCodeLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE, m_editFile);
}

BEGIN_MESSAGE_MAP(CCntCodeLineDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BTN_CNT, OnBnClickedBtnCnt)
END_MESSAGE_MAP()


// CCntCodeLineDlg ��Ϣ�������

BOOL CCntCodeLineDlg::OnInitDialog()
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
	
	SetDefID(IDC_BTN_CNT);
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CCntCodeLineDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCntCodeLineDlg::OnPaint() 
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
HCURSOR CCntCodeLineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCntCodeLineDlg::OnDropFiles(HDROP hDropInfo)
{
	CHAR pszPath[MAX_PATH] = {0};
	UINT nFileNum = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);//DragQueryFileΪ0xFFFFFFFF��ʱ�򷵻���ҷ�ļ��ĸ���
	DragQueryFile(hDropInfo, nFileNum - 1, pszPath, MAX_PATH);//�����ҷ�����һ���ļ����ļ���
	DragFinish(hDropInfo);	//����ǵ��ͷŵ�hDropInfo
	
	m_editFile.SetWindowText(pszPath);
	m_editFile.UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}

void CCntCodeLineDlg::OnBnClickedBtnCnt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_dCntLines = 0;
	CString cstrPath;
	m_editFile.GetWindowText(cstrPath);
	if (cstrPath == "")
	{
		m_editFile.SetWindowText("û�ļ�");
		return;
	}
	DWORD ulAttri = 0;
	if ( (ulAttri = GetFileAttributes(cstrPath) ) == 0xFFFFFFFF)
	{
		MessageBox("�ļ�������");
		return;
	}
	if (ulAttri == FILE_ATTRIBUTE_DIRECTORY)
	{
		Findfile(cstrPath);
	}
	else
	{
		m_dCntLines += cntLines( cstrPath );
	}

	cstrPath.Format("һ����%.0lf��", m_dCntLines);//���������ʽ
	m_editFile.SetWindowText(cstrPath);

	
}

//�����ļ���׺��,�ָ��ļ���
CString CCntCodeLineDlg::GetSuffix(const CString& cstrPath)
{
	char driver[MAX_PATH];
	char dir[MAX_PATH];
	char fname[MAX_PATH];
	char ext[MAX_PATH];
	_splitpath(cstrPath, driver, dir, fname, ext);
	return ext;
}
void CCntCodeLineDlg::Findfile(const CString& cstrFolderFile)
{
	TCHAR szFileName[MAX_PATH] = {0};
	TCHAR szFullPathFileName[MAX_PATH] = {0};
	WIN32_FIND_DATA findData = {0};
	if ( cstrFolderFile.Right(1) != '\\' )
	{
		_stprintf( szFullPathFileName, "%s\\*.*", cstrFolderFile );
	}
	else
	{
		_stprintf( szFullPathFileName, "%s*.*", cstrFolderFile );
	}
	
	HANDLE hFind = FindFirstFile( szFullPathFileName, &findData );
	if ( INVALID_HANDLE_VALUE == hFind )
	{
		m_editFile.SetWindowText("�ļ�����");
		return;
	}
	bool bFinished = false;
	while ( !bFinished )
	{
		_stprintf( szFileName, "%s\\%s", cstrFolderFile, findData.cFileName );
		if ( FILE_ATTRIBUTE_DIRECTORY & findData.dwFileAttributes )
		{
			if ( _tcscmp( findData.cFileName, "." ) && _tcscmp( findData.cFileName, ".." ) )
			{
				Findfile( szFileName );

			}			
		}
		else
		{
			if ( (GetSuffix(szFileName) == ".cpp") || (GetSuffix(szFileName) == ".c") 
				|| (GetSuffix(szFileName) == ".h")
				/*|| (GetSuffix(szFileName) == ".txt")*/)
			{
				m_dCntLines += cntLines( szFileName );
			}		
		}
		if ( !FindNextFile ( hFind, &findData) )
		{
			if (ERROR_NO_MORE_FILES == GetLastError())
			{
				bFinished = true;
			}
		}
	}
}

double CCntCodeLineDlg::cntLines( const CString& cstrFileName)
{
	FILE* fp = fopen(cstrFileName, "r");
	if (fp == NULL)
	{
		MessageBox("�ļ��򲻿�");
		return -1;
	}
	CHAR pstrTemp[READ_ONCE];
	double dResLines = 0.0;

//	MessageBox(cstrFileName);

	int iRes;
	while ((iRes = fread(pstrTemp, 1, READ_ONCE, fp)) > 0)
	{
		for (int i = 0; i < iRes; i++)//abcd\nabe\ana
		{
			//TRACE( "%c", pstrTemp[i] );
			if (pstrTemp[i] == '\n')
			{				
				dResLines++;				
			}
		}
	}
	if (dResLines > 0)
	{
		dResLines++;
	}

	fclose(fp);

	return dResLines;
}
