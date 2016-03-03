
// EasyEncodeAndDecodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EasyEncodeAndDecode.h"
#include "EasyEncodeAndDecodeDlg.h"
#include "afxdialogex.h"
#include <string>

using std::string;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEasyEncodeAndDecodeDlg �Ի���




CEasyEncodeAndDecodeDlg::CEasyEncodeAndDecodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEasyEncodeAndDecodeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEasyEncodeAndDecodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ENCODEING_TEXT, m_editEncodingText);
	DDX_Control(pDX, IDC_EDIT_FINISH_ENCODE_PATH, m_editFinishEncodePath);
	DDX_Control(pDX, IDC_EDIT_DECODINGPATH, m_editDecodingPath);
}

BEGIN_MESSAGE_MAP(CEasyEncodeAndDecodeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ENCODE, &CEasyEncodeAndDecodeDlg::OnBnClickedButtonEncode)
	ON_BN_CLICKED(IDC_BUTTON_DECODE, &CEasyEncodeAndDecodeDlg::OnBnClickedButtonDecode)
END_MESSAGE_MAP()


// CEasyEncodeAndDecodeDlg ��Ϣ�������

BOOL CEasyEncodeAndDecodeDlg::OnInitDialog()
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

void CEasyEncodeAndDecodeDlg::OnPaint()
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
HCURSOR CEasyEncodeAndDecodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int EnCode(char* szText, int iSize)
{
	for ( int i = 0; i<iSize; ++i )
	{
		szText[i] = ~(szText[i])+10;
	}
	return 0;
}


void CEasyEncodeAndDecodeDlg::OnBnClickedButtonEncode()
{
	CString cstreditEncodingText;
	m_editEncodingText.GetWindowText(cstreditEncodingText);
	string streditEncodingText((char*)cstreditEncodingText.GetBuffer(), cstreditEncodingText.GetLength()*2);
	EnCode((char*)streditEncodingText.c_str(), streditEncodingText.length());
	CString cstreditFinishEncodePath;
	m_editFinishEncodePath.GetWindowText(cstreditFinishEncodePath);
	if ( cstreditFinishEncodePath.IsEmpty() )
	{
		cstreditFinishEncodePath = L"D:\\EncodeFile.zb";
	}

	FILE* fp = nullptr;
	_wfopen_s(&fp, cstreditFinishEncodePath.GetBuffer(), L"wb");
	fwrite( streditEncodingText.c_str(), 1, streditEncodingText.length(), fp );
	fclose(fp);

}

void Decode(char* pDecode, int iSize)
{
	for ( int i = 0; i<iSize; ++i )
	{
		pDecode[i] = ~(pDecode[i] -10);
	}
}


void CEasyEncodeAndDecodeDlg::OnBnClickedButtonDecode()
{
	CString cstrDecodingPath;
	m_editDecodingPath.GetWindowText(cstrDecodingPath);
	if ( cstrDecodingPath.IsEmpty() )
	{
		cstrDecodingPath = L"D:\\EncodeFile.zb";
	}

	FILE* fp = nullptr;
	_wfopen_s(&fp, cstrDecodingPath.GetBuffer(), L"rb");
	fseek( fp, 0, SEEK_END );
	long filesize = ftell(fp); 
	char* pBuf = new char[filesize+2];
	pBuf[filesize] = 0;
	pBuf[filesize+1] = 0;
	fseek(fp, 0, SEEK_SET);
	fread(pBuf, 1, filesize, fp);
	fclose(fp);
	Decode(pBuf, filesize);
	CString cstBuf((WCHAR*)pBuf, filesize/2);
	m_editEncodingText.SetWindowText( cstBuf );	
}
