
// BatchOperationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatchOperation.h"
#include "BatchOperationDlg.h"
#include "afxdialogex.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBatchOperationDlg �Ի���




CBatchOperationDlg::CBatchOperationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBatchOperationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBatchOperationDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_PATH, m_editPath);
    DDX_Control(pDX, IDC_EDIT_CONDITION, m_editCondition);
    DDX_Control(pDX, IDC_EDIT_ADD_BEG, m_editAddBeg);
    DDX_Control(pDX, IDC_EDIT_ADD_END, m_editAddEnd);
}

BEGIN_MESSAGE_MAP(CBatchOperationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &CBatchOperationDlg::OnBnClickedOk)
    ON_WM_DROPFILES()
    ON_BN_CLICKED(IDC_BUTTON_CHANG_FILE_STRING, &CBatchOperationDlg::OnBnClickedButtonChangFileString)
END_MESSAGE_MAP()


// CBatchOperationDlg ��Ϣ�������

BOOL CBatchOperationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    DragAcceptFiles(TRUE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBatchOperationDlg::OnPaint()
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
HCURSOR CBatchOperationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void FindAndRename(wstring pszPath, wstring codition, wstring addBegin,
    map<wstring,wstring>* namePair)
{    
    wstring dir = pszPath;
    WIN32_FIND_DATA findData = {0};
    pszPath += _T("\\*.*");    
    HANDLE hFind = FindFirstFile(pszPath.c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        return;
    }
    do 
    {
        wstring fileName(findData.cFileName);
        wstring::size_type pos = fileName.find(codition);
        if (pos != wstring::npos)
        {
            wstring newName(fileName);
            newName.insert(0, addBegin);
            namePair->insert(
                make_pair(dir + L"\\" + fileName, dir + L"\\" + newName));
        }
    } while (FindNextFile(hFind, &findData));
    FindClose(hFind);
}

void RenameMap(const map<wstring,wstring>& namePair)
{
    int ret = -1;
    for (auto per = namePair.begin(); per != namePair.end(); ++per)
    {
        ret = _trename(per->first.c_str(), per->second.c_str());
    }

}


void CBatchOperationDlg::OnBnClickedOk()
{
    CString pathText;
    m_editPath.GetWindowText(pathText);  
    CString codition;
    m_editCondition.GetWindowText(codition);
    CString editAddBeg;
    m_editAddBeg.GetWindowText(editAddBeg);
    CString editAddEnd;
    m_editAddEnd.GetWindowText(editAddEnd);
    map<wstring,wstring> namePair;
    FindAndRename(pathText.GetBuffer(), codition.GetBuffer(),
    editAddBeg.GetBuffer(), &namePair);
    RenameMap(namePair);    
}


void CBatchOperationDlg::OnDropFiles(HDROP hDropInfo)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    UINT uFileNum=::DragQueryFile(hDropInfo,0xffffffff,NULL,0); 
    WCHAR strFileName[MAX_PATH]; 
    for (UINT i=0;i<uFileNum;i++) 
    { 
        ::DragQueryFileW(hDropInfo,i,strFileName,MAX_PATH);
        CString str(strFileName);
    } 

    POINT pt = {0};
    GetCursorPos(&pt);
    {
        CRect rectPath;
        m_editPath.GetWindowRect(rectPath);
        if (rectPath.PtInRect(pt))
        {
            m_editPath.SetWindowText(strFileName);
        }
    }

    {
        CRect rectCondition;
        m_editCondition.GetWindowRect(rectCondition);
        if (rectCondition.PtInRect(pt))
        {
            m_editCondition.SetWindowText(strFileName);
        }
    }

    {
        CRect rectAddBeg;
        m_editAddBeg.GetWindowRect(rectAddBeg);
        if (rectAddBeg.PtInRect(pt))
        {
            m_editAddBeg.SetWindowText(strFileName);
        }
    }

    {
        CRect rectAddEnd;
        m_editAddEnd.GetWindowRect(rectAddEnd);
        if (rectAddEnd.PtInRect(pt))
        {
            m_editAddEnd.SetWindowText(strFileName);
        }
    }

    ::DragFinish(hDropInfo); 
    CDialogEx::OnDropFiles(hDropInfo);
}

#include <queue>

void CBatchOperationDlg::OnBnClickedButtonChangFileString()
{
    queue<int> que;
    que
    string path = "E:\\GitCode\\Fazheng\\bin\\kugou_d\\MakeRingForm.xml";
    FILE* fp = fopen(path.c_str(), "r+");
    assert(fp);
    if (fp == nullptr)
    {
        return;
    }
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp) + 1;
    char* szBuf = new char[size + 1];
    fseek(fp, 0, SEEK_SET);
    int readed = fread(szBuf, 1, size, fp);
    szBuf[readed] = 0;
    string text(szBuf);
    delete szBuf;
    string::size_type posBeg = 0;
    string::size_type posEnd = 0;
    string findwhat(".png\"");

    while(1)
    {   
        posEnd = text.find(findwhat, posBeg);
        int writed = -1;
        if (posEnd != string::npos)
        {
            posBeg = text.rfind("\"", posEnd);
            if (posBeg != string::npos &&posBeg < posEnd)
            {
                string addText("make_ring_");
                text.insert(++posBeg, addText);
                posBeg = posEnd + findwhat.length() + addText.length() + 1;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    fseek(fp, 0, SEEK_SET);
    int wri = fwrite(text.c_str(), 1, text.length(), fp);
    fclose(fp);
}
