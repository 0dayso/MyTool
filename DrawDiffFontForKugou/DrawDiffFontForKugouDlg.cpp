
// DrawDiffFontForKugouDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawDiffFontForKugou.h"
#include "DrawDiffFontForKugouDlg.h"
#include "afxdialogex.h"
#include <string>
#include <wingdi.h>
#include <WindowsX.h>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDrawDiffFontForKugouDlg �Ի���




CDrawDiffFontForKugouDlg::CDrawDiffFontForKugouDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrawDiffFontForKugouDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawDiffFontForKugouDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_TEXT, m_editText);
    DDX_Control(pDX, IDC_EDIT_FONT, m_editFont);
    DDX_Control(pDX, IDC_EDIT_SIZE, m_editSize);
    DDX_Control(pDX, IDC_STATIC_SIZE_VALUE, m_staticSizeValue);
    DDX_Control(pDX, IDC_STATIC_SHOW, m_staticShow);
    DDX_Control(pDX, IDC_STATIC_SIZE_VALUE3, m_staticShowSizeValue);
    DDX_Control(pDX, IDC_EDIT_FACTOR, m_editFactor);
}

BEGIN_MESSAGE_MAP(CDrawDiffFontForKugouDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_RUN, &CDrawDiffFontForKugouDlg::OnBnClickedButtonRun)
    ON_BN_CLICKED(IDOK, &CDrawDiffFontForKugouDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDrawDiffFontForKugouDlg ��Ϣ�������

BOOL CDrawDiffFontForKugouDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
    m_editText.SetWindowTextW(L"����Ҫһ�� GoGo!@");
    m_editFont.SetWindowTextW(L"����");
    m_editSize.SetWindowTextW(L"48");
    m_editFactor.SetWindowTextW(L"3");

    m_staticShow.ShowWindow(SW_HIDE);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDrawDiffFontForKugouDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDrawDiffFontForKugouDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
        CString text;
        m_editText.GetWindowTextW(text);

        CString font;
        m_editFont.GetWindowTextW(font);

        CString size;
        m_editSize.GetWindowTextW(size);
        int isize = _wtoi(size.GetBuffer());

        CString factor;
        m_editFactor.GetWindowTextW(factor);

        DrawShowText(text.GetBuffer(), font.GetBuffer(), isize,
            _wtoi(factor.GetBuffer()));
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDrawDiffFontForKugouDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





int ConvertWinFontHeightToNeg(int fontSize)
{
    if (fontSize > 0)
    {
        HDC dc = ::GetDC(nullptr);
        int nCaps = ::GetDeviceCaps(dc, LOGPIXELSY);
        if (nCaps == 0)
            nCaps = 72;
        ::ReleaseDC(nullptr, dc);

        return -::MulDiv(fontSize, nCaps, 72);
    }

    return fontSize;
}


bool GetFontSize(const std::wstring& text, const std::wstring& font,
    int size, int factor, int* fontWidth, int* fontHeight)
{
    LOGFONTW logFont = {0};
    wcscpy_s(logFont.lfFaceName, font.c_str());
    logFont.lfCharSet = GB2312_CHARSET;
    logFont.lfHeight = ConvertWinFontHeightToNeg(size) * factor;
    logFont.lfWidth *= 0;
    HFONT newFont = ::CreateFontIndirect(&logFont);
    HDC hdc = GetDC(nullptr);
    HFONT oldFont = (HFONT)::SelectObject(hdc, newFont);
    CSize curSize;
    BOOL ret = ::GetTextExtentPoint32W(
        hdc, text.c_str(), text.length(), &curSize);
    ::SelectObject(hdc, oldFont);

    ReleaseDC(nullptr, hdc);

    if (fontWidth && factor)
    {
        *fontWidth = curSize.cx / factor;
    }
    if (fontHeight && factor)
    {
        *fontHeight = curSize.cy / factor;
    }
    return !!ret;
}


void CDrawDiffFontForKugouDlg::ClearShow()
{
    m_staticShow.SetWindowTextW(L"");
    m_staticSizeValue.SetWindowTextW(L"");
    m_staticShowSizeValue.SetWindowTextW(L"");
}


void CDrawDiffFontForKugouDlg::OnBnClickedButtonRun()
{
    ClearShow();
    {
        CString text;
        m_editText.GetWindowTextW(text);

        CString font;
        m_editFont.GetWindowTextW(font);

        CString size;
        m_editSize.GetWindowTextW(size);
        int isize = _wtoi(size.GetBuffer());

        CString factor;
        m_editFactor.GetWindowTextW(factor);

        int fontWidth = 0;
        int fontHeight = 0; 
        GetFontSize(text.GetBuffer(), font.GetBuffer(), isize,
            _wtoi(factor.GetBuffer()), &fontWidth, &fontHeight);
        std::wstringstream ss;
        ss << L"Ҫ��ʾ �� Size��" << fontWidth << L" , " << fontHeight;
        m_staticShowSizeValue.SetWindowTextW(ss.str().c_str());

    }

    {
        CString font;
        m_editFont.GetWindowTextW(font);

        CString size;
        m_editSize.GetWindowTextW(size);
        int isize = _wtoi(size.GetBuffer());

        CString factor;
        m_editFactor.GetWindowTextW(factor);

        int fontWidth = 0;
        int fontHeight = 0; 
        GetFontSize(L"Wg", font.GetBuffer(), isize,
            _wtoi(factor.GetBuffer()), &fontWidth, &fontHeight);
        std::wstringstream ss;
        ss << L"Wg �� Size��" << fontWidth << L" , " << fontHeight;
        m_staticSizeValue.SetWindowTextW(ss.str().c_str());
    }

    Invalidate();
}

void CDrawDiffFontForKugouDlg::DrawShowText(
    const std::wstring& text, const std::wstring& font,
    int size, int factor)
{
    CPaintDC hdc(this);
    LOGFONTW logFont = {0};
    wcscpy_s(logFont.lfFaceName, font.c_str());
    logFont.lfCharSet = GB2312_CHARSET;
    logFont.lfHeight = ConvertWinFontHeightToNeg(size);
    logFont.lfWidth = 0;
    HFONT newFont = ::CreateFontIndirect(&logFont);
    HFONT oldFont = (HFONT)::SelectObject(hdc, newFont);
    CSize curSize;
    BOOL ret = ::GetTextExtentPoint32W(
        hdc, text.c_str(), text.length(), &curSize);
    RECT rc = {20, 250, 600,400};
    int drawLen = DrawText(hdc, text.c_str(), text.length(), 
        &rc,  DT_LEFT | DT_NOPREFIX);
    ::SelectObject(hdc, oldFont);
}

void CDrawDiffFontForKugouDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    return;
}


BOOL CDrawDiffFontForKugouDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: �ڴ����ר�ô����/����û���

    return CDialogEx::PreTranslateMessage(pMsg);
}
