// FindFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FindFile.h"
#include "FindFileDlg.h"
#include ".\findfiledlg.h"
#include "process.h"
#include <vector>
#include <string>
using std::vector;
using std::string;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int FIND_BY_NAME = 1;
const int FIND_BY_SIZE = 2;




void GetHardDisks(vector<string>& vecHardDisks)
{
	
	TCHAR pszPerDriver[10];
	TCHAR szBuf[100];
	memset(szBuf, 0, sizeof(szBuf));
	DWORD dwLenth = GetLogicalDriveStrings(sizeof(szBuf)/sizeof(TCHAR), szBuf);
	for (TCHAR* pTemp = szBuf; *pTemp; pTemp += _tcslen(pTemp) + 1)//"C:\<>D:\<><>"
	{
		sprintf(szBuf, "%s",pTemp);
		UINT uType = GetDriveType(szBuf);
		if (uType == DRIVE_FIXED)
		{
			vecHardDisks.push_back(szBuf);			
		}
	}	
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

unsigned __stdcall FindThread(void* pArguments)
{
	CFindFileDlg* pThisDlg = (CFindFileDlg*)(pArguments);
	pThisDlg->m_bIsFinding = true;
		
	vector<string> vecHardDisks;

	GetHardDisks(vecHardDisks);	

	
	for (vector<string>::iterator itHardDisks = vecHardDisks.begin(); 
		itHardDisks != vecHardDisks.end(); 
		itHardDisks++)
	{
		//itHardDisks[itHardDisks->size() - 1] = 0;
		pThisDlg->FindPerDriver(itHardDisks->c_str(), pThisDlg->m_iFindByWhat);
	}
	if ( pThisDlg->m_iFindByWhat == FIND_BY_NAME )
	{
		pThisDlg->m_btnFindWay1.SetWindowText("�����꿩");
	}
	else
	{
		pThisDlg->m_btnFindWay2.SetWindowText("�����꿩");
	}
	

	pThisDlg->m_bIsFinding = false;
	return 0;
}

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


// CFindFileDlg �Ի���



CFindFileDlg::CFindFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindFileDlg::IDD, pParent),m_dwHighSize(0),m_iLineNum(0),m_iFindByWhat(FIND_BY_NAME),
	m_bIsFinding(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFindFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_SHOW, m_editShowPath);
	DDX_Control(pDX, IDC_BUTTON_FINDWAY1, m_btnFindWay1);
	DDX_Control(pDX, IDC_BUTTON_FINDWAY2, m_btnFindWay2);
	DDX_Control(pDX, IDC_EDIT_SIZE, m_editSize);
}

BEGIN_MESSAGE_MAP(CFindFileDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_FINDWAY1, OnBnClickedButtonFindway1)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_EDIT_NAME, OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_SIZE, OnEnChangeEditSize)
	ON_BN_CLICKED(IDC_BUTTON_FINDWAY2, OnBnClickedButtonFindway2)
END_MESSAGE_MAP()


// CFindFileDlg ��Ϣ�������

BOOL CFindFileDlg::OnInitDialog()
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

	CRect rect;
	GetDlgItem(IDC_EDIT_SHOW)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	
	m_iShowPathLeft = rect.left;
	m_iShowPathTop = rect.top;

	m_editShowPath.SetLimitText(0xFFFFFFFF);//����edit��������
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CFindFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFindFileDlg::OnPaint() 
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
HCURSOR CFindFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFindFileDlg::OnBnClickedButtonFindway1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if ( m_bIsFinding == true )
	{
		MessageBox("���ڲ�����");
		return;
	}

	m_editShowPath.SetWindowText("");
	m_iLineNum = 0;

	 m_editName.GetWindowText(m_cstrFindName);

	if (m_cstrFindName == "")
	{
		MessageBox("����Ϊ��");
		return;
	}

	m_btnFindWay1.SetWindowText("���ڲ�����........");

	this->m_iFindByWhat = FIND_BY_NAME;

	CloseHandle( (HANDLE)_beginthreadex(NULL, 0, FindThread, this, 0 , NULL) );

}


void CFindFileDlg::FindPerDriver(const CHAR* pszDriver, int iType)
{
	LPSTR pszFindName = m_cstrFindName.GetBuffer();

	CHAR pszPath[1024] = {0};
	sprintf(pszPath, "%s//*.*", pszDriver);
	WIN32_FIND_DATA findData = {0};
	HANDLE hFind = FindFirstFile(pszPath, &findData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	try
	{
		do 
		{
			if (findData.cFileName[0] == '.')
			{
				continue;
			}
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{

				TCHAR szFile[1024];
				sprintf(szFile, "%s\\%s", pszDriver, findData.cFileName);
				//TRACE("%s\n", szFile);

				int iFind = 0;
				if (iType == FIND_BY_NAME)
				{
					if (strstr(findData.cFileName, pszFindName) != NULL)
					{
						iFind = 1;
					}
					else
					{
						iFind = 0;
					}
				}
				if (iFind > 0)
				{
					//m_cstrShowPath.Format("%d", m_iLineNum++);
					m_cstrShowPath = szFile;
					m_cstrShowPath += "\r\n";
					int iLen = ::GetWindowTextLength(m_editShowPath.m_hWnd);
					m_editShowPath.SetSel(iLen, iLen);
					m_editShowPath.ReplaceSel(m_cstrShowPath);
					m_editShowPath.LineScroll(m_editShowPath.GetLineCount());
				
				}		
								
				FindPerDriver(szFile, iType);
			}
			else
			{
				TCHAR szFile[1024];
				sprintf(szFile, "%s\\%s", pszDriver, findData.cFileName);
				//TRACE("%s\n", szFile);
				int iFind = 0;
				if (iType == FIND_BY_NAME)
				{
					if (strstr(findData.cFileName, pszFindName) != NULL)
					{
						iFind = 1;
					}
					else
					{
						iFind = 0;
					}
				}
				else
				{
					if ( findData.nFileSizeHigh > m_dwHighSize || (findData.nFileSizeLow > m_dwLowSize && m_dwHighSize == 0) )
					{
						iFind = 1;
					}
					else
					{
						iFind = 0;
					}
				}
				if (iFind > 0)
				{
					//m_cstrShowPath.Format("%d", m_iLineNum++);
					m_cstrShowPath = szFile;
					m_cstrShowPath += "\r\n";
					int iLen = ::GetWindowTextLength(m_editShowPath.m_hWnd);
					m_editShowPath.SetSel(iLen, iLen);
					m_editShowPath.ReplaceSel(m_cstrShowPath);
					m_editShowPath.LineScroll(m_editShowPath.GetLineCount());
				}	
			}
		} while (FindNextFile(hFind, &findData));
	}
	catch (CMemoryException* e)
	{
		TRACE("CMemoryException\n");
	}
	catch (CFileException* e)
	{
		TRACE("CFileException\n");
	}
	catch (CException* e)
	{
		TRACE("CException\n");
	}
	
}


void CFindFileDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	HDWP hDwp = BeginDeferWindowPos(1);
	DeferWindowPos(hDwp, ::GetDlgItem(m_hWnd, IDC_EDIT_SHOW), NULL, m_iShowPathLeft, m_iShowPathTop, cx - m_iShowPathLeft*2, cy - m_iShowPathTop - 10, SWP_NOACTIVATE|SWP_NOZORDER);
	//m_editShowPath.SetWindowPos(&wndTop, m_iShowPathLeft, m_iShowPathTop, cx - m_iShowPathLeft*2, cy - m_iShowPathTop - 10, SWP_SHOWWINDOW);
	EndDeferWindowPos(hDwp);
}

void CFindFileDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���


	//CDialog::OnOK();
}

void CFindFileDlg::OnEnChangeEditName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	m_iEnterFocus = 1;
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CFindFileDlg::OnEnChangeEditSize()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	m_iEnterFocus = 2;
	// TO	DO:  �ڴ���ӿؼ�֪ͨ����������
}

BOOL CFindFileDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			if (m_iEnterFocus == 1)
			{
				OnBnClickedButtonFindway1();
			}
			if (m_iEnterFocus == 2)
			{
				OnBnClickedButtonFindway2();
			}
		}
		
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CFindFileDlg::OnBnClickedButtonFindway2()
{
	if ( m_bIsFinding == true )
	{
		MessageBox("���ڲ�����");
		return;
	}
	

	m_editShowPath.SetWindowText("");
	m_iLineNum = 0;

	CString cstrSize;
	m_editSize.GetWindowText(cstrSize);//��MBΪ��λ��
	if (cstrSize == "")
	{
		MessageBox("��С����Ϊ�ջ�Ϊ��Ϊ0");
		return;
	}
	double dSize = double(atof(cstrSize) * 1024 * 1024);
	if (dSize < 0)
	{
		MessageBox("��С����Ϊ�ջ�Ϊ��Ϊ0");
		return;
	}
	DWORD dwBigist = 0xFFFFFFFF;
	double dDwordBigist = double(dwBigist);
	if (dSize > dDwordBigist )
	{
		m_dwHighSize = 1;
	}
	else
	{
		m_dwHighSize = 0;
		m_dwLowSize = (DWORD)dSize;
	}

	if (m_dwLowSize == 0)
	{
		MessageBox("��С����Ϊ�ջ�Ϊ��Ϊ0");
		return;
	}

	m_btnFindWay2.SetWindowText("���ڲ�����........");

	m_iFindByWhat = FIND_BY_SIZE;

	CloseHandle( (HANDLE)_beginthreadex(NULL, 0, FindThread, this, 0, NULL) );
}
