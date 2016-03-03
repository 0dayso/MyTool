// Test3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test3.h"
#include "Test3Dlg.h"

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


// CTest3Dlg �Ի���



CTest3Dlg::CTest3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTest3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CTest3Dlg::~CTest3Dlg()
{
	vector<CStatic*>::iterator iter = m_vecPSttShow.begin();
	for ( ; iter != m_vecPSttShow.end(); iter++ )
	{
		if ( *iter != NULL )
		{
			delete *iter;
			*iter = NULL;
		}
	}
}


void CTest3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT1, m_stt1);
}

BEGIN_MESSAGE_MAP(CTest3Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CTest3Dlg ��Ϣ�������

BOOL CTest3Dlg::OnInitDialog()
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

	m_stt1.MoveWindow(-10, -20, 50, 50);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_pSttShow = new CStatic;
	CRect rect(100,100, 150, 150);
	m_iSttID = 2000;
	m_pSttShow->Create("aaaa", WS_CHILD|WS_VISIBLE, rect, this, m_iSttID++);	
	m_vecPSttShow.push_back(m_pSttShow);
	m_pSttShow = new CStatic;
	rect.OffsetRect(0, 50);
	m_pSttShow->Create("BB", WS_CHILD|WS_VISIBLE, rect, this, m_iSttID++);	
	m_vecPSttShow.push_back(m_pSttShow);

	m_pSttShow = new CStatic;
	rect.OffsetRect(0, 50);
	m_pSttShow->Create("BB", WS_CHILD|WS_VISIBLE, rect, this, m_iSttID++);	
	m_vecPSttShow.push_back(m_pSttShow);
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CTest3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTest3Dlg::OnPaint() 
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
HCURSOR CTest3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
