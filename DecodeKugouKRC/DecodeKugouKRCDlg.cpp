
// DecodeKugouKRCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DecodeKugouKRC.h"
#include "DecodeKugouKRCDlg.h"
#include "afxdialogex.h"
#include <assert.h>
#include "Base64.h"
#include "StrAssist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDecodeKugouKRCDlg �Ի���




CDecodeKugouKRCDlg::CDecodeKugouKRCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDecodeKugouKRCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDecodeKugouKRCDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDecodeKugouKRCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_DROPFILES()
    ON_BN_CLICKED(IDC_BTN_DECODE, &CDecodeKugouKRCDlg::OnBnClickedBtnDecode) 
END_MESSAGE_MAP()


// CDecodeKugouKRCDlg ��Ϣ�������

BOOL CDecodeKugouKRCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������




	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDecodeKugouKRCDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDecodeKugouKRCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDecodeKugouKRCDlg::OnDropFiles(HDROP hDropInfo)
{
    int count = DragQueryFile(hDropInfo, -1, NULL, 0);
    for (int i = 0; i < count; ++i)
    {
        TCHAR filePath[MAX_PATH];
        if(DragQueryFile(hDropInfo, i, filePath, MAX_PATH) != 0)
        {
            CWnd* editPath = GetDlgItem(IDC_EDIT_PATH);
            editPath->SetWindowText(filePath);
        }
        else
        {
            assert(0 && L"DragQueryFile" == NULL);
        }
    }
    CDialog::OnDropFiles(hDropInfo);
}

struct AutoCloseHandle
{
    AutoCloseHandle(FILE* fp)
        : fp_(fp)
    {
    }
    ~AutoCloseHandle()
    {
        if (fp_)
        {
            fclose(fp_);
        }
    }
    void ReSet()
    {
        fclose(fp_);
        fp_ = nullptr;
    }
   FILE* fp_;
};

bool CDecodeKugouKRCDlg::DealBase64(std::wstring& target)
{
    FILE* fp = nullptr;    
    _wfopen_s(&fp, target.c_str(), L"r+");
    if (fp == nullptr)
    {
        CString path(target.c_str());
        path += L" �ļ��򲻿�";
        MessageBox(path, L"����", MB_OK);
        return false;
    }
    AutoCloseHandle closeHandle(fp);

    char szBuf[1024*10];
    std::string lyric;

    while (1)
    {
        int readed = fread(szBuf, 1, 1024*10-1, fp);
        if (readed == 0)
        {
            break;
        }
        szBuf[readed] = 0;
        lyric += szBuf;
    }

    if (lyric.find("[split:")  != std::string::npos)
    {
        return false;
    }

    std::string::size_type posBegin = lyric.find("[language:");
    if (posBegin == std::string::npos)
    {
        return false;
    }
    posBegin += strlen("[language:");
    std::string::size_type posEnd = lyric.find("]", posBegin);
    if (posEnd == std::string::npos)
    {
        return false;
    }

    std::string language(lyric, posBegin, posEnd - posBegin);
    if (language.empty())
    {
        return false;
    }
    char* pStrBase64 = nullptr;
    CBase64::Base64EnCodeAlloc(language.c_str(), &pStrBase64);
    pStrBase64 = CBase64::Base64DeCode(language.c_str(), pStrBase64);

    std::string languageReal = CStrAssist::UnicodeIntStrToAnsi(pStrBase64, true);

    lyric.replace(posBegin, posEnd - posBegin, languageReal.c_str());
    CBase64::Base64EnCodeFree(pStrBase64);
    pStrBase64 = nullptr;
    closeHandle.ReSet();
    fp = nullptr;
    _wfopen_s(&fp, target.c_str(), L"w");
    if (fp == nullptr)
    {
        CString path(target.c_str());
        path += L" �ļ��򲻿�";
        MessageBox(path, L"����", MB_OK);
        return false;
    }
    AutoCloseHandle closeHandleW(fp);

    int write = fwrite(lyric.c_str(), 1, lyric.size(), fp);
    
    if (write > 0)
    {
        return true;
    }
    return false;
}


void CDecodeKugouKRCDlg::OnBnClickedBtnDecode()
{
    TCHAR decoder[MAX_PATH] = L"E:\\0��������\\����\\lyric_decoder\\lyric_decoder.exe";//L"C:\\Program Files (x86)\\IDM Computer Solutions\\UltraEdit\\Uedit32.exe";
    FILE* fp = NULL;
    _tfopen_s(&fp, decoder, L"r");
    if (fp == NULL)
    {
        CString path(decoder);
        MessageBox(path + L"·��������");
        return;
    }
    fclose(fp);

    CWnd* editPath = GetDlgItem(IDC_EDIT_PATH);
    CString editPathText;
    editPath->GetWindowText(editPathText);
    if (editPathText.IsEmpty())
    {        
        MessageBox(L"����ļ�·��������");
        return;
    }
    std::wstring target = editPathText.GetBuffer();
    std::wstring::size_type pos = target.rfind(L'.');
    if (pos == std::wstring::npos)
    {
        pos = target.size();
    }
    target.replace(pos, target.size()-pos, L".txt");

    DeleteFile(target.c_str());

    CString cmdline = L"\"" + editPathText + L"\""+ CString(L" ") + L"\"" + CString(target.c_str()) + L"\"";
    
    SHELLEXECUTEINFOW execInfo = {0};
    execInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    execInfo.lpVerb = L"open";
    execInfo.cbSize = sizeof(execInfo);
    execInfo.lpFile = decoder;
    execInfo.lpParameters = cmdline.GetBuffer();
    execInfo.nShow = SW_SHOW;
    BOOL ret = ShellExecuteExW(&execInfo);

    if (ret == FALSE || execInfo.hProcess == NULL)
    {
        MessageBox(L"��������ʧ�ܣ�����", L"����", MB_OK);
    }
    else
    {
        WaitForSingleObject(execInfo.hProcess, INFINITE);

        if (DealBase64(target))
        {
            GetDlgItem(IDC_BTN_DECODE)->SetWindowTextW(L"�ɹ�, �����ļ���ͬһ·����");
        }
        else
        {
            GetDlgItem(IDC_BTN_DECODE)->SetWindowTextW(L"ʧ��");
            DeleteFile(target.c_str());
        }

        DWORD code = 0;;
        GetExitCodeProcess(execInfo.hProcess, &code);
        CString tips = L"�˳�����: ";
        tips.Format(L"%s %d", tips, code);
    }
}


