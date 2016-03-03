// CopyUsefulStringToNewFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CopyUsefulStringToNewFile.h"
#include "CopyUsefulStringToNewFileDlg.h"
#include ".\copyusefulstringtonewfiledlg.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

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


// CCopyUsefulStringToNewFileDlg �Ի���



CCopyUsefulStringToNewFileDlg::CCopyUsefulStringToNewFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCopyUsefulStringToNewFileDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCopyUsefulStringToNewFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SOURCE, m_editSource);
	DDX_Control(pDX, IDC_EDIT_INCLUDE_STRING, m_eidtIncludeString);
	DDX_Control(pDX, IDC_EDIT_NEW_NAME, m_editOutput);
}

BEGIN_MESSAGE_MAP(CCopyUsefulStringToNewFileDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_GET, OnBnClickedButtonGet)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_GET_FOR_LOG, OnBnClickedButtonGetForLog)

END_MESSAGE_MAP()


// CCopyUsefulStringToNewFileDlg ��Ϣ�������

BOOL CCopyUsefulStringToNewFileDlg::OnInitDialog()
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
	SetDefID( IDC_BUTTON_GET ); // ����Ĭ�ϰ�ť
	GetDlgItem(IDC_BUTTON_GET )->SetFocus();    // ���ý���

	return FALSE; // �����ص�
	
	//return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CCopyUsefulStringToNewFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCopyUsefulStringToNewFileDlg::OnPaint() 
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
HCURSOR CCopyUsefulStringToNewFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCopyUsefulStringToNewFileDlg::OnBnClickedButtonGet()
{
	CString cstrSource;
	m_editSource.GetWindowText(cstrSource);

	FILE* fp = fopen( cstrSource.GetBuffer(), "r" );
	if ( fp == NULL )
	{
		MessageBox("fp == NULL");
		//return;
	}

	CString cstrOutput;
	m_editOutput.GetWindowText(cstrOutput);
	if ( cstrOutput == "" )
	{
		char szFileName[MAX_PATH] = {0};
		char szExt[MAX_PATH] = {0};
		_splitpath( cstrSource, NULL, NULL, szFileName, szExt );
		string strPath(cstrSource.GetBuffer());
		int iName = strPath.rfind('\\', strPath.size() -1 );// c\a
		string strNewName = "New  ";
		strNewName += szFileName;
		strNewName += szExt;
		strPath.replace( iName +1, strPath.size()  - ( iName + 1), strNewName );
		cstrOutput = strPath.c_str();
	}
	//cstrOutput = "c:\\New test.txt";



	CString cstrIncludeString;
	m_eidtIncludeString.GetWindowText(cstrIncludeString);
	int iLenth = cstrIncludeString.GetLength() + 1;
	char* szIncludeString = new char[iLenth];
	char* szTempString = szIncludeString;
	strcpy( szIncludeString, cstrIncludeString.GetBuffer() );
	vector <string> vecIncludeString;
	for ( int i(0); i < iLenth; i++ )
	{
		if ( szIncludeString[i] == ';' )//aa;bbbbb;ccccc;
		{
			string strPer( szTempString, szIncludeString + i );		
			vecIncludeString.push_back( strPer );
			szTempString = szIncludeString + i  + 1;
		}
		
	}
	if ( szIncludeString[ iLenth - 1 ] != ';' )
	{
		string strPer( szTempString, szIncludeString + i );	
		vecIncludeString.push_back( strPer );
	}	

	delete( szIncludeString );

	char szBuf[1024] = {0};
	char szPerRead[1] = {0};
	bool bOut = false;

	do
	{
		string strBuf;
		int iNCnt(0);
		do 
		{
			int iReadPer = fread(szPerRead, 1, 1, fp);
			DWORD dwError = GetLastError();
			if ( iReadPer <= 0 )
			{
				bOut = true;
			}
			strBuf += szPerRead[0];
			if ( szPerRead[0] == '\n')
			{
				iNCnt = 1;
			}
			else if ( 1 == iNCnt)
			{
				strBuf.erase(strBuf.size() -1, 1);
				fseek( fp, -1, SEEK_CUR );
				break;
			}
		} while (bOut != true);
		vector<string>::iterator iter = vecIncludeString.begin();
		for ( ;iter != vecIncludeString.end(); iter++ )
		{
			//TRACE("%s\n",iter->c_str() );
			int iIndex = strBuf.find( iter->c_str() );	
			if ( iIndex != string::npos )
			{
				int iLeftIndex(0);
				int iRightIndex = strBuf.find('\n', iIndex );
				if ( iRightIndex == string::npos )
				{
					iRightIndex = strBuf.size() - 1;
				}

				string strOutput( strBuf, iLeftIndex, iRightIndex - iLeftIndex + 1 );
				TRACE("%s", strOutput.c_str());
				FILE* fpOutput = fopen( cstrOutput.GetBuffer() , "a");
				if ( fpOutput == NULL)
				{
					MessageBox("fpOutput == NULL");
				}
				int iWrite = fwrite( strOutput.c_str(), sizeof(char) , strOutput.size(), fpOutput );	
				fclose( fpOutput );
				break;
			}
		}

	}while( bOut != true );


	fclose( fp );



}

void CCopyUsefulStringToNewFileDlg::OnDropFiles(HDROP hDropInfo)
{
	CHAR pszPath[MAX_PATH] = {0};
	UINT nFileNum = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);//DragQueryFileΪ0xFFFFFFFF��ʱ�򷵻���ҷ�ļ��ĸ���
	DragQueryFile(hDropInfo, nFileNum - 1, pszPath, MAX_PATH);//�����ҷ�����һ���ļ����ļ���
	DragFinish(hDropInfo);	//����ǵ��ͷŵ�hDropInfo

	m_editSource.SetWindowText(pszPath);
	m_editSource.UpdateData(FALSE);

	CDialog::OnDropFiles(hDropInfo);
}

void CCopyUsefulStringToNewFileDlg::OnBnClickedButtonGetForLog()
{	
	CString cstrSource;
	m_editSource.GetWindowText(cstrSource);

	FILE* fp = fopen( cstrSource.GetBuffer(), "r" );
	if ( fp == NULL )
	{
		MessageBox("fp == NULL");
		//return;
	}

	CString cstrOutput;
	m_editOutput.GetWindowText(cstrOutput);
	if ( cstrOutput == "" )
	{
		char szFileName[MAX_PATH] = {0};
		char szExt[MAX_PATH] = {0};
		_splitpath( cstrSource, NULL, NULL, szFileName, szExt );
		string strPath(cstrSource.GetBuffer());
		int iName = strPath.rfind('\\', strPath.size() -1 );// c\a
		string strNewName = "New  ";
		strNewName += szFileName;
		strNewName += szExt;
		strPath.replace( iName +1, strPath.size()  - ( iName + 1), strNewName );
		cstrOutput = strPath.c_str();
	}
	//cstrOutput = "c:\\New test.txt";



	CString cstrIncludeString;
	m_eidtIncludeString.GetWindowText(cstrIncludeString);
	int iLenth = cstrIncludeString.GetLength() + 1;
	char* szIncludeString = new char[iLenth];
	char* szTempString = szIncludeString;
	strcpy( szIncludeString, cstrIncludeString.GetBuffer() );
	vector <string> vecIncludeString;
	for ( int i(0); i < iLenth; i++ )
	{
		if ( szIncludeString[i] == ';' )//aa;bbbbb;ccccc;
		{
			string strPer( szTempString, szIncludeString + i );		
			vecIncludeString.push_back( strPer );
			szTempString = szIncludeString + i  + 1;
		}

	}
	if ( szIncludeString[ iLenth - 1 ] != ';' )
	{
		string strPer( szTempString, szIncludeString + i );	
		vecIncludeString.push_back( strPer );
	}	

	delete( szIncludeString );

	char szBuf[1024] = {0};
	char szPerRead[1] = {0};
	bool bOut = false;

	do
	{
		string strBuf;
		int iNCnt(0);
		do 
		{
			int iReadPer = fread(szPerRead, 1, 1, fp);//  [asdd]asdafsdaf[asdafs]1222
			DWORD dwError = GetLastError();
			if ( iReadPer <= 0 )
			{
				bOut = true;
				break;
			}
			if ( szPerRead[0] == '[' )
			{
				iNCnt++;
			}			
			if ( 1 == iNCnt )
			{				
				strBuf += szPerRead[0];
			}
				
			if ( iNCnt == 2 )
			{
				iNCnt = 0;					
				fseek( fp, -1, SEEK_CUR );
				break;
			}					
		} while (1);
		vector<string>::iterator iter = vecIncludeString.begin();
		for ( ;iter != vecIncludeString.end(); iter++ )
		{
			//TRACE("%s\n",iter->c_str() );
			int iIndex = strBuf.find( iter->c_str() );	
			if ( iIndex != string::npos )
			{
				string strOutput( strBuf );
				TRACE("%s", strOutput.c_str());
				FILE* fpOutput = fopen( cstrOutput.GetBuffer() , "a");
				if ( fpOutput == NULL)
				{
					MessageBox("fpOutput == NULL");
				}
				int iWrite = fwrite( strOutput.c_str(), sizeof(char) , strOutput.size(), fpOutput );	
				fclose( fpOutput );
				break;
			}
		}

	}while( bOut != true );


	fclose( fp );


}

