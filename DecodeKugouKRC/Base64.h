// Base64.h: interface for the Base64 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE64_H__CC677E12_2906_4796_9395_D0E7A34C1E6F__INCLUDED_)
#define AFX_BASE64_H__CC677E12_2906_4796_9395_D0E7A34C1E6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBase64  
{
public:
	CBase64();
	virtual ~CBase64();

	enum
	{
		BASE64SRCCOUNT		= 3					// ԭ���ֽ���
		, BASE64CODECOUNT	= 4					// �����ֽ���

		, BASE64ENCODECOUNT	= 66				// ��������
		, BASE64DECODECOUNT	= 256				// ��������

		, BASE64ENCODEMASK	= 0x3f				// ��������
		, BASE64DECODEMASK	= 0x3f				// ��������

		, BYTEFST			= 0					// ��һ���ֽ�
		, BYTESEC			= 1					// �ڶ����ֽ�
		, BYTETHR			= 2					// �������ֽ�
		, BYTEFOURTH		= 3					// ���ĸ��ֽ�	// �����õ�

		, BYTEMOVE2			= 2					// �ֽ��ƶ�2��λ
		, BYTEMOVE4			= 4					// �ֽ��ƶ�4��λ
		, BYTEMOVE6			= 6					// �ֽ��ƶ�6��λ
	};

	// ��������

	// ����

	static const char strBase64EnCode[ BASE64ENCODECOUNT ];		// �����

	// Base64����
	static char* Base64EnCode( const char* strSrc, char* strBase64 );

	// Base64��������ڴ�
	static bool Base64EnCodeAlloc( const char* strSrc, char** pStrBase64 );
	
	// Base64��������ڴ�
	static bool Base64EnCodeFree( char* strBase64 );

	// ����
	static const char strBase64DeCode[ BASE64DECODECOUNT ];		// �����

	// Base64�������
	static char* Base64DeCode( const char* strBase64, char* strSrc );

	static int Base64DecodeEx(const char *input, char *des);

	// Base64��������ڴ�
	static bool Base64DeCodeAlloc( const char* strBase64, char** pStrSrc );
    static bool Base64DeCodeAllocEx( const char* strBase64, char** pStrSrc, int& len);

	// Base64��������ڴ�
	static bool Base64DeCodeFree( char* strSrc );

};

#endif // !defined(AFX_BASE64_H__CC677E12_2906_4796_9395_D0E7A34C1E6F__INCLUDED_)
