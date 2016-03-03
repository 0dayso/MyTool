#ifndef _HTTP_REQUEST_IMPL_REF_H_
#define _HTTP_REQUEST_IMPL_REF_H_
#include "HttpRequestRef.h"
#include "UnkownBase.h"


namespace http_request
{


struct HttpRequestParam : public UnkownBase
{
    HINTERNET hOpen;
    HINTERNET hConnect;
    HINTERNET hRequest;
    bool requesstEx;
    std::string URL;
    std::string method;
    std::string header;
    std::string body;

    void* winInetCallback;
    DWORD dwContext;
    bool isAsync;
    std::function<void (const AsyncHttpRequestRet&)> userCallbackFun;
    void* userValue;    //�û��������Ĳ���, �ص�ʱԭ������
    AsyncHttpRequestRet httpRequestRet;

    PROXY_TYPE_PARAM ProxyTypeParam;
    std::string proxyIP;
    std::string proxyPort;
    std::string proxyLoginName;
    std::string proxyPassword;

    int connectTimeOut; //60*1000ms    

    HttpRequestParam()
        : hOpen(NULL)
        , hConnect(NULL)
        , hRequest(NULL)
        , winInetCallback(NULL)
        , dwContext(NULL)
        , isAsync(false)
        , requesstEx(false)
        , method("GET")
        , ProxyTypeParam(PT_PRECONFIG)
        , connectTimeOut(60*1000)
        , userValue(NULL)
    {

    }
};

}

#endif