
// Md5CalFile2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Md5CalFile2.h"
#include "Md5CalFile2Dlg.h"
#include "afxdialogex.h"
#include "md5.h"
#include <Windows.h>
#include <string>
#include <tchar.h>
using std::string;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMd5CalFile2Dlg �Ի���




CMd5CalFile2Dlg::CMd5CalFile2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMd5CalFile2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMd5CalFile2Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_editPath);
    DDX_Control(pDX, IDC_EDIT2, m_showMd5Lower);
    DDX_Control(pDX, IDC_EDIT3, m_showMd5Upper);
}

BEGIN_MESSAGE_MAP(CMd5CalFile2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CMd5CalFile2Dlg::OnBnClickedButton1)
    ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMd5CalFile2Dlg ��Ϣ�������

BOOL CMd5CalFile2Dlg::OnInitDialog()
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

void CMd5CalFile2Dlg::OnPaint()
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
HCURSOR CMd5CalFile2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

class FileMap
{
public:
    FileMap()
        : hFileMapping(INVALID_HANDLE_VALUE)
        , lpBuffer(NULL)
    {
    }

    void* CreateFileMap(const wchar_t* szPath, LARGE_INTEGER* liSize)
    {
        void* retBuf = nullptr;
        HANDLE hFile = INVALID_HANDLE_VALUE;
        do 
        {
            hFile = CreateFile( szPath, GENERIC_READ|GENERIC_WRITE, 
                0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if ( hFile == INVALID_HANDLE_VALUE )
            {
                break;
            }

            GetFileSizeEx( hFile, liSize );
            unsigned __int64 ullSize = liSize->QuadPart;

            hFileMapping = CreateFileMapping(
                hFile, NULL, PAGE_READWRITE, 
                DWORD( liSize->HighPart ), DWORD( liSize->LowPart ), NULL );
            if( !hFileMapping )
            {
                break;
            } 
            char* lpBuffer = (char*)MapViewOfFileEx( 
                hFileMapping, FILE_MAP_WRITE, 0, 0, liSize->LowPart, NULL );

            if( !lpBuffer )
            {
                break;
            }
            retBuf = lpBuffer;
        } while (0);
        if (hFile != INVALID_HANDLE_VALUE)
        {
            CloseHandle(hFile);
        }
        return retBuf;
    }

    ~FileMap()
    {
        if (lpBuffer)
        {
            UnmapViewOfFile(lpBuffer);
            lpBuffer = nullptr;
        }
        if (hFileMapping)
        {
            CloseHandle(hFileMapping);
            hFileMapping = nullptr;
        }
    }

private:

    HANDLE hFileMapping;
    char* lpBuffer;
};

std::wstring Md5Partially( unsigned char* szInput, int iLength, int iPer )//abcde 2
{	
    MD5_CTX mc = {0};
    MD5Init( &mc );	
    for (; iLength >= iPer ; szInput += iPer, iLength -= iPer)
    {
        MD5Update(&mc, szInput, iPer);
    }
    if ( iLength >= 0 )
    {
        MD5Update(&mc, szInput, iLength);
    }	
    MD5Final(&mc);

    wchar_t szRet[3] = {0};

    std::wstring strRet;

    for (int i = 0; i < 16; ++i)
    {
        _stprintf_s(szRet, L"%02X", mc.digest[i]);
        strRet += szRet;
    }
    return strRet;
}

void CMd5CalFile2Dlg::OnBnClickedButton1()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    m_showMd5Lower.SetWindowTextW(L"");
    m_showMd5Upper.SetWindowTextW(L"");
    LARGE_INTEGER liSize = { 0 };
    CString path;
    m_editPath.GetWindowTextW(path);
    FileMap fileMap;
    char* lpBuffer = (char*)fileMap.CreateFileMap(path.GetBuffer(), &liSize);
    std::wstring strRet = Md5Partially((unsigned char*)lpBuffer, 
        liSize.LowPart, 80*1024);
   
    m_showMd5Upper.SetWindowTextW(strRet.c_str());

    for (unsigned int i = 0; i < strRet.size(); ++i)
    {
        if ( strRet[i] >= L'A' && strRet[i] <= L'Z')
        {
            strRet[i] = strRet[i] - L'A' + L'a';
        }
    }
    m_showMd5Lower.SetWindowTextW(strRet.c_str());
}


void CMd5CalFile2Dlg::OnDropFiles(HDROP hDropInfo)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    WCHAR pszPath[MAX_PATH] = {0};
    UINT nFileNum = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);//DragQueryFileΪ0xFFFFFFFF��ʱ�򷵻���ҷ�ļ��ĸ���
    DragQueryFile(hDropInfo, nFileNum - 1, pszPath, MAX_PATH);//�����ҷ�����һ���ļ����ļ���
    DragFinish(hDropInfo);	//����ǵ��ͷŵ�hDropInfo

    m_editPath.SetWindowText(pszPath);
    m_editPath.UpdateData(FALSE);
    CDialogEx::OnDropFiles(hDropInfo);
}
