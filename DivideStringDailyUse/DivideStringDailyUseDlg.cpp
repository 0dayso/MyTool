// DivideStringDailyUseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DivideStringDailyUse.h"
#include "DivideStringDailyUseDlg.h"
#include ".\dividestringdailyusedlg.h"


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


// CDivideStringDailyUseDlg �Ի���



CDivideStringDailyUseDlg::CDivideStringDailyUseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDivideStringDailyUseDlg::IDD, pParent)
	, m_bIsFile(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDivideStringDailyUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SOURCE, m_editSource);
	DDX_Control(pDX, IDC_EDIT_DIVIDE_SYMBOL, m_editDivideSymbol);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_editResult);
	DDX_Control(pDX, IDC_CHECK_TO_NEW_TXT, m_chkToNewTXT);
}

BEGIN_MESSAGE_MAP(CDivideStringDailyUseDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BTN_START, OnBnClickedBtnStart)
END_MESSAGE_MAP()


// CDivideStringDailyUseDlg ��Ϣ�������

BOOL CDivideStringDailyUseDlg::OnInitDialog()
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

	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CDivideStringDailyUseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDivideStringDailyUseDlg::OnPaint() 
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
HCURSOR CDivideStringDailyUseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDivideStringDailyUseDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	int iCnt = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);//������ҷ�ĸ���
	if ( iCnt >= 1 )
	{	
		char szName[MAX_PATH] = {0};
		DragQueryFile( hDropInfo, iCnt -1, szName, sizeof(szName) );
		m_editSource.SetWindowText(szName);
		m_cstrSourceName = szName;
		m_bIsFile = true;
		m_chkToNewTXT.SetCheck(BST_CHECKED);
	}


	CDialog::OnDropFiles(hDropInfo);
}

void CDivideStringDailyUseDlg::DivideStringBySymbol(const string& strIn, const vector<string>& vecSymbol,
													vector<string>& vecHasDivide)
{	
	vector<int> vecDivideIndex;			//�ָ�����±�
	vector<int>::iterator itrDivideIndex;

	vector<string>::const_iterator itrSymbol;	
	int iTempIndex;	
	
	//;,asfdsafsasd;,adfasdf;ree
	for ( itrSymbol = vecSymbol.begin(); itrSymbol != vecSymbol.end(); itrSymbol++ )//���ҵ�һ�����ŵ��±�
	{
		int iFindIndex(0);
		do 
		{
			iTempIndex = strIn.find(*itrSymbol, iFindIndex);
			if ( iTempIndex != string::npos )
			{				
				vecDivideIndex.push_back(iTempIndex);
				iFindIndex = iTempIndex + itrSymbol->size();									
			}
			else
			{
				break;
			}
		} while (1);
	}

	if ( vecDivideIndex.size() > 0 )
	{
		vecDivideIndex.push_back(strIn.size());
		//���򲢳���
		sort(vecDivideIndex.begin(), vecDivideIndex.end());
		vector<int>::iterator itNewEnd = unique(vecDivideIndex.begin(), vecDivideIndex.end());//uniqueֻ�ǽ����صķŵ�ǰ�棬����Ĳ���
		vecDivideIndex.erase( itNewEnd, vecDivideIndex.end() );//���Ա���ɾ�������
		int iIndexDivide(0);
		for ( int i(0); i <= vecDivideIndex.size(); i++ )
		{
			string strHasDivide( strIn, iIndexDivide, vecDivideIndex[i] - iIndexDivide );
			if ( strHasDivide.size() > 0 && strHasDivide != "" && strHasDivide != " " && strHasDivide != "  ")
			{
				bool bIsSameSymbol(false);
				for ( itrSymbol = vecSymbol.begin(); itrSymbol != vecSymbol.end(); itrSymbol++ )
				{
					if ( strHasDivide == *itrSymbol )
					{
						bIsSameSymbol = true;
						break;
					}

				}
				if ( bIsSameSymbol == false  )
				{
					vecHasDivide.push_back(strHasDivide);
				}
			}
			//���ָ������±곤��

			for ( itrSymbol = vecSymbol.begin(); itrSymbol != vecSymbol.end(); itrSymbol++ )
			{
				int iSymbolIndex = strIn.find(*itrSymbol,  vecDivideIndex[i]);
				if ( iSymbolIndex == vecDivideIndex[i] )
				{
					iIndexDivide = vecDivideIndex[i] + itrSymbol->size();
				}
			}

			if ( iIndexDivide >= strIn.size() )
			{
				break;
			}
		}		
	}
	if ( vecHasDivide.size() == 0 )
	{
		vecHasDivide.push_back(strIn);
	}
}

void CDivideStringDailyUseDlg::OnBnClickedBtnStart()
{
	vector<string>::iterator iter;
	m_editDivideSymbol.GetWindowText(m_cstrDivideSymbol);
	vector<string> vecDivide;
	vector<string> vecSymbol;
	vecSymbol.push_back("$");
	DivideStringBySymbol(m_cstrDivideSymbol.GetBuffer(), vecSymbol, vecDivide);
	for ( iter = vecDivide.begin(); iter!= vecDivide.end(); iter++ )
	{
		TRACE("%s\t\t", iter->c_str());
	}

	string strSource;
	
	if ( m_bIsFile )
	{
		FILE* fpRead= fopen( m_cstrSourceName.GetBuffer(), "r" );
		if ( fpRead == NULL )
		{
			TRACE("fpRead!\n");
			return;
		}
		char szRead[1024];		
		int iRead;

		while ( ( iRead = fread( szRead, sizeof(szRead[0]), sizeof(szRead), fpRead ) ) > 0 )
		{
			if ( iRead < sizeof(szRead) )
			{
				szRead[iRead] = 0;
			}
			strSource += szRead;
		}
		fclose(fpRead);

	}
	else
	{
		m_editSource.GetWindowText(m_cstrSourceName);
		strSource = m_cstrSourceName.GetBuffer();
	}
	vector<string> vecOut;
	DivideStringBySymbol(strSource, vecDivide , vecOut);
	string strResult;
	string strResultTXT;

	for ( iter = vecOut.begin(); iter!= vecOut.end(); iter++ )
	{
		TRACE("%s\t", iter->c_str());
		strResult += *iter;	
		string strTemp = *iter;		
		if ( strTemp[0] == '\n' )
		{
			strTemp.erase(0, 1);
		}
		if ( strTemp[strTemp.size() -1] == '\n' )
		{
			strTemp.erase(strTemp.size() -1, 1);
		}
		strResultTXT += strTemp;
		strResult += "\r\n";	
		strResultTXT += "\r\n";
	}

	m_editResult.SetWindowText(strResult.c_str());
	m_editResult.UpdateData(FALSE);

	//�Ƿ�д���ı�	
	if ( m_chkToNewTXT.GetCheck() || m_bIsFile )
	{
		if ( m_bIsFile == false )
		{
			m_cstrSourceName = "D:\\Temp.txt";
		}
		char szDrive[MAX_PATH];
		char szDir[MAX_PATH];
		char szFile[MAX_PATH];
		char szExt[MAX_PATH]; 
		_splitpath(m_cstrSourceName.GetBuffer(), szDrive, szDir, szFile, szExt );
		string strFile("New  ");
		strFile += szFile;
		char szFullPath[1024];
		_makepath(szFullPath, szDrive, szDir, strFile.c_str(), szExt);

		FILE* fpWrite =fopen(szFullPath, "w");
		if ( fpWrite == NULL  )
		{		
			TRACE("fpWrite!\n");
			return;
		}
		
		int len = fwrite( strResultTXT.c_str(), sizeof(char), strResultTXT.size(), fpWrite );
		fclose(fpWrite);
	}

	m_bIsFile = false;
}
