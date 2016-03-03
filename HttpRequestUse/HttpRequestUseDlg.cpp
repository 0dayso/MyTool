
// HttpRequestUseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpRequestUse.h"
#include "HttpRequestUseDlg.h"
#include "afxdialogex.h"
#include "../HttpRequest/http_request.h"

#ifdef _DEBUG
#pragma comment(lib, "../Debug/HttpRequest.lib")
#else
#pragma comment(lib, "../Release/HttpRequest.lib")
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHttpRequestUseDlg �Ի���




CHttpRequestUseDlg::CHttpRequestUseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHttpRequestUseDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHttpRequestUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHttpRequestUseDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_SYNC_GET, &CHttpRequestUseDlg::OnBnClickedButtonSyncGet)
    ON_BN_CLICKED(IDC_BUTTON_SYNC_POST, &CHttpRequestUseDlg::OnBnClickedButtonSyncPost)
    ON_BN_CLICKED(IDC_BUTTON_ASYNC_GET, &CHttpRequestUseDlg::OnBnClickedButtonAsyncGet)
    ON_BN_CLICKED(IDC_BUTTON_ASYNC_POST, &CHttpRequestUseDlg::OnBnClickedButtonAsyncPost)
END_MESSAGE_MAP()


// CHttpRequestUseDlg ��Ϣ�������

BOOL CHttpRequestUseDlg::OnInitDialog()
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

void CHttpRequestUseDlg::OnPaint()
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
HCURSOR CHttpRequestUseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHttpRequestUseDlg::OnBnClickedButtonSyncGet()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    http_request::HttpRequest* httpRequest = 
        http_request::HttpRequest::GetInstance();
    http_request::SyncHttpRequestParam syncparam;
    syncparam.URL = "http://www.baidu.com";
    syncparam.method = "GET";
    
    http_request::HttpRequestRet httpRequestRet;
    httpRequest->SyncHttpRequest(syncparam, httpRequestRet);

}


void CHttpRequestUseDlg::OnBnClickedButtonSyncPost()
{
    
}

void AsyncGetWebCallback(const http_request::AsyncHttpRequestRet& requestRet, 
    const std::string& url)
{


}


void CHttpRequestUseDlg::OnBnClickedButtonAsyncGet()
{
    http_request::HttpRequest* httpRequest = 
        http_request::HttpRequest::GetInstance();
    http_request::AsncHttpRequestParam requestParam;
    requestParam.URL = "http://www.baidu.com";
    requestParam.method = "GET";
    requestParam.callbackFun = std::bind(AsyncGetWebCallback, 
        std::placeholders::_1, requestParam.URL);
    
    httpRequest->AsncHttpRequest(requestParam);

}

void AsyncPOSTCallback(const http_request::AsyncHttpRequestRet& requestRet, 
    const std::string& url)
{

}


void CHttpRequestUseDlg::OnBnClickedButtonAsyncPost()
{
    http_request::HttpRequest* httpRequest = 
        http_request::HttpRequest::GetInstance();
    http_request::AsncHttpRequestParam requestParam;
    requestParam.URL = "http://client.show.qq.com/cgi-bin/qqshow_user_props_info";
    requestParam.header = 
"Accept: */*\r\n\
Accept-Language: zh-CN\r\n\
x-flash-version: 11,5,502,110\r\n\
Content-Type: application/x-www-form-urlencoded\r\n\
Accept-Encoding: gzip, deflate\r\n\
User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR\3.0.30729; .NET4.0C; .NET4.0E)\r\n\
Connection: Keep-Alive\r\n\
Pragma: no-cache\r\n\
Cookie: ac=1,030,017; pt2gguin=o0237858502; RK=/UkXmgsESe; ptcz=790f8134cad4ef6aae106c15123b058e54c80069c7ca5976d490dddc8b998f63; pgv_pvid=5879667293; pgv_pvi=7525848064; uin_cookie=237858502; euin_cookie=C00ABA6DFC77188C27C69CAFAE5239B901738FB9D3319F3C\r\n";
    requestParam.method = "POST";
    requestParam.body = "uin=237858502&ckey=D03CDE9D8077B3B2188FECB09CB426C781C8E3481571AC18BB493B87371A6319&senduin=13340509";
    requestParam.callbackFun = std::bind(AsyncPOSTCallback, 
        std::placeholders::_1, requestParam.URL);

    httpRequest->AsncHttpRequest(requestParam);
}
