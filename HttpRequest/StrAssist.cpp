#include "StrAssist.h"
#include <sstream>

/***********************************************************************************
* name       : StrFormat
* description: ���ݴ���ĸ�ʽ�����ַ����ĸ�ʽ��;�ýӿ�ֻ�ܸ�ʽ���󳤶�Ϊ1024���ַ���
* input      : szFormat �ַ����ĸ�ʽ��... �ɱ����
* output     : NA
* return     : ת������ַ���
* remark     : NA
***********************************************************************************/
string CStrAssist::StrFormat( const char* szFormat, ... )
{
	va_list va;
	va_start( va, szFormat );
	char szTemp [ 0x400 ] = { 0 };
	vsprintf( szTemp, szFormat, va );
	va_end( va );

	string strRet;
	strRet.assign( szTemp );
	return strRet;
}

/***********************************************************************************
* name       : IntToStr
* description: ������ת��Ϊ�ַ���
* input      : iValue Ҫת����������ֵ��bHex �Ƿ���ʮ������������
* output     : NA
* return     : ת������ַ���
* remark     : NA
***********************************************************************************/
string CStrAssist::IntToStr( int iValue, bool bHex /*= false*/ )
{
	char szTmp[ 0x7f ] = { 0 };
	if( bHex )
	{
		_itoa( iValue, szTmp, 0x10 );
	}
	else
	{
		_itoa( iValue, szTmp, 0x0a );
	}	

	return string( szTmp );
}

/***********************************************************************************
* name       : StrToInt
* description: ������ת��Ϊ�ַ���
* input      : strSrc Ҫת�����ַ�����bHex �Ƿ���ʮ������������
* output     : NA
* return     : ת�����������
* remark     : NA
***********************************************************************************/
int CStrAssist::StrToInt( const string& strSrc, bool bHex /*= false*/ )
{
	int iRet = 0;	
	if( bHex )
	{
		sscanf( strSrc.c_str(), "%x", &iRet );
	}
	else
	{
		sscanf( strSrc.c_str(), "%d", &iRet );
	}	

	return iRet;
}

/***********************************************************************************
* name       : LongToStr
* description: ������ת��Ϊ�ַ���
* input      : iValue Ҫת����������ֵ��bHex �Ƿ���ʮ������������
* output     : NA
* return     : ת������ַ���
* remark     : NA
***********************************************************************************/
string CStrAssist::LongToStr ( long iValue, bool bHex /*= false*/ )
{
	char szTmp[ 0x400 ];
	if( bHex )
	{
		_ltoa( iValue, szTmp, 0x10 );
	}
	else
	{
		_ltoa( iValue, szTmp, 0x0a );
	}	

	return string( szTmp );
}

/***********************************************************************************
* name       : CharToHex
* description: ���ַ�ת��Ϊ16���Ʊ���
* input      : szChar Ҫת�����ַ�
* output     : NA
* return     : ���ص�ʮ�����Ʊ���
* remark     : NA
***********************************************************************************/
int CStrAssist::CharToHex( const char szChar )
{
	if( '0' <= szChar && '9' >= szChar )
	{
		return szChar - '0';
	}
	if( 'a' <= szChar && 'f' >= szChar )
	{
		return szChar - 'a' + 10;
	}
	else
	if( 'A' <= szChar && 'F' >= szChar )
	{
		return szChar - 'A' + 10;
	}

	return -1;
}

/***********************************************************************************
* name       : StrToHex
* description: ��һ���ַ���ת��Ϊʮ�������ַ�������
* input      : strSrc Ҫת�����ַ���;
* output     : NA
* return     : ���ص�ʮ�����Ʊ�����ַ���
* remark     : NA
***********************************************************************************/
string CStrAssist::StrToHex( const string& strData )
{
	string strRet;
	strRet.reserve( strData.size() << 1 );

	for( size_t i = 0; i < strData.size(); ++i )
	{
		char szBuffer[ 10 ];
		sprintf( szBuffer, "%02x", ( unsigned char )strData[ i ] );
		strRet.append( szBuffer, 2 );
	}

	return strRet;
}

/***********************************************************************************
* name       : HexToStr
* description: ��ʮ�����Ƶ��ַ���ת��Ϊһ���ַ���
* input      : strSrc Ҫת�����ַ���
* output     : NA
* return     : ת������ַ���
* remark     : NA
***********************************************************************************/
string CStrAssist::HexToStr( const string& strData )
{
	string strRet;
	strRet.assign( ( strData.size() + 1 ) >> 1, '\0' );

	for( size_t i = 0; i < strData.size(); ++i )
	{
		int m = CharToHex( strData[ i ] );
		if ( m >= 0 )
		{
			if ( i % 2 == 0 )
			{
				strRet[ i >>  1 ] |= ( m & 0xf ) << 4;
			}
			else
			{
				strRet[ i >>  1 ] |= ( m & 0xf );
			}
		} // end of if ( m >= 0 ) ...          		        
	} // end of for ( size_t i = 0; ...

	return strRet;
}

/***********************************************************************************
* name       : Utf8ToUnicode
* description: �ַ���ת��: UTF8 - Unicode	
* input      : strSrc Ҫת����Utf8�ַ���������ַ���
* output     : NA
* return     : ת�����Unicode�ַ���������ַ���
* remark     : NA
***********************************************************************************/
wstring CStrAssist::Utf8ToUnicode( const string& strSrc )
{
	/*!< ����Ŀ��ռ� */
	int iAllocSize = static_cast< int >( strSrc.size() + 10 );
	WCHAR* pwszBuffer = new WCHAR[ iAllocSize ];
	if( NULL == pwszBuffer )
	{
		return L"";
	}
	int iCharsRet = MultiByteToWideChar( CP_UTF8, 0, strSrc.c_str(), 
		static_cast< int >( strSrc.size() ),
		pwszBuffer, iAllocSize );
	/*!< �ɹ� */
	wstring wstrRet;
	if( 0 < iCharsRet  )
	{
		wstrRet.assign( pwszBuffer, static_cast< size_t >( iCharsRet ) );
	}

	/*!< �ͷ��ڴ� */
	delete[] pwszBuffer;

	return wstrRet;
}

/***********************************************************************************
* name       : UnicodeToUtf8
* description: �ַ���ת��: Unicode - UTF8	
* input      : wstrSrc Ҫת����Unicode�ַ���������ַ���
* output     : NA
* return     : ת�����UTF8�ַ���������ַ���
* remark     : NA
***********************************************************************************/
string CStrAssist::UnicodeToUtf8( const wstring& wstrSrc )
{	
	/*!< ����Ŀ��ռ�, һ��16λUnicode�ַ�������תΪ4���ֽ� */
	int iAllocSize = static_cast< int >( ( wstrSrc.size() << 2 ) + 10 );
	char* pszBuffer = new char[ iAllocSize ];
	if( NULL == pszBuffer )
	{
		return "";
	}
	int iCharsRet = WideCharToMultiByte( CP_UTF8, 0, wstrSrc.c_str(), 
		static_cast< int >( wstrSrc.size() ),
		pszBuffer, iAllocSize, NULL, NULL );
	/*!< �ɹ� */
	string strRet;
	if( 0 < iCharsRet )
	{
		strRet.assign( pszBuffer, static_cast< size_t >( iCharsRet ) );
	}

	/*!< �ͷ��ڴ� */
	delete[] pszBuffer;

	return strRet;
}

/***********************************************************************************
* name       : Utf8ToAnsi
* description: �ַ���ת��: UTF8 - Ansi
* input      : strSrc Ҫת����UTF8�ַ���������ַ���
* output     : NA
* return     : ת�����Ansi�ַ���������ַ���
* remark     : NA
***********************************************************************************/
string CStrAssist::Utf8ToAnsi( const string& strSrc )
{
	wstring wstrTemp = Utf8ToUnicode( strSrc );

	/*!< ����Ŀ��ռ�, ����Ϊ Ansi ��������� */
	int iAllocSize = static_cast< int >( ( strSrc.size() << 1 ) + 10 );
	char* pszBuffer = new char[ iAllocSize ];
	if( NULL == pszBuffer )
	{
		return "";
	}
	int iCharsRet = WideCharToMultiByte( CP_ACP, 0, wstrTemp.c_str(), 
		static_cast< int >( wstrTemp.size() ),
		pszBuffer, iAllocSize, NULL, NULL );
	/*!< �ɹ� */
	string strRet;
	if( 0 < iCharsRet )
	{
		strRet.assign( pszBuffer, static_cast< size_t >( iCharsRet ) );
	}

	/*!< �ͷ��ڴ� */
	delete[] pszBuffer;

	return strRet;
}

/***********************************************************************************
* name       : AnsiToUtf8
* description: �ַ���ת��: Ansi - UTF8
* input      : strSrc Ҫת����Ansi�ַ���������ַ���
* output     : NA
* return     : ת�����UTF8�ַ���������ַ���
* remark     : NA
***********************************************************************************/
string CStrAssist::AnsiToUtf8( const string& strSrc )
{
	/*!< ����Ŀ��ռ�, ����Ϊ Ansi ��������� */
	int iAllocSize = static_cast< int >( ( strSrc.size() << 1 ) + 10 );
	WCHAR* pwszBuffer = new WCHAR[ iAllocSize ];
	if( NULL == pwszBuffer )
	{
		return "";
	}
	int iCharsRet = MultiByteToWideChar( CP_ACP, 0, strSrc.c_str(),
		static_cast< int >( strSrc.size() ),
		pwszBuffer, iAllocSize );
	/*!< �ɹ� */
	wstring wstrTemp;
	if( 0 < iCharsRet )
	{
		wstrTemp.assign( pwszBuffer, static_cast< size_t >( iCharsRet ) );
	}

	/*!< �ͷ��ڴ� */
	delete[] pwszBuffer;

	return UnicodeToUtf8( wstrTemp );
}

/***********************************************************************************
* name       : AnsiToUnicode
* description: �ַ���ת��: Ansi - Unicode
* input      : strSrc Ҫת����Ansi�ַ���������ַ���
* output     : NA
* return     : ת�����Unicode�ַ���������ַ���
* remark     : NA
***********************************************************************************/
wstring CStrAssist::AnsiToUnicode (const string& strSrc )
{
	/*!< ����Ŀ��ռ� */
	int iAllocSize = static_cast< int >( strSrc.size() + 10 );
	WCHAR* pwszBuffer = new WCHAR[ iAllocSize ];
	if( NULL == pwszBuffer )
	{
		return L"";
	}	
	int iCharsRet = MultiByteToWideChar( CP_ACP, 0, strSrc.c_str(), 
		static_cast< int >( strSrc.size() ),
		pwszBuffer, iAllocSize );
	/*!< �ɹ� */
	wstring wstrRet;
	if( 0 < iCharsRet )
	{
		wstrRet.assign( pwszBuffer, static_cast< size_t >( iCharsRet ) );
	}

	/*!< �ͷ��ڴ� */
	delete[] pwszBuffer;

	return wstrRet;
}

/***********************************************************************************
* name       : UnicodeToAnsi
* description: �ַ���ת��: Unicode - Ansi
* input      : strSrc Ҫת����Unicode�ַ���������ַ���
* output     : NA
* return     : ת�����Ansi�ַ���������ַ���
* remark     : NA
***********************************************************************************/
string CStrAssist::UnicodeToAnsi ( const wstring& wstrSrc )
{
	/*!< ����Ŀ��ռ�, һ��16λUnicode�ַ�������תΪ4���ֽ�*/
	int iAllocSize = static_cast< int >( ( wstrSrc.size() << 2 ) + 10 );
	char* pwszBuffer = new char[ iAllocSize ];
	if ( NULL == pwszBuffer )
	{
		return "";
	}	
	int iCharsRet = WideCharToMultiByte( CP_ACP, 0, wstrSrc.c_str(), 
		static_cast< int >( wstrSrc.size() ),
		pwszBuffer, iAllocSize, NULL, NULL );
	/*!< �ɹ� */
	string strRet;
	if( 0 < iCharsRet )
	{
		strRet.assign( pwszBuffer, static_cast< size_t >( iCharsRet ) );
	}

	/*!< �ͷ��ڴ� */
	delete[] pwszBuffer;

	return strRet;
}

/***********************************************************************************
* name       : Utf8ToBSTR
* description: �ַ���ת��: UTF8 - BSTR
* input      : strSrc Ҫת����UTF8�ַ���������ַ���
* output     : NA
* return     : ת����ĵ�BSTR�ַ���
* remark     : NA
***********************************************************************************/
BSTR CStrAssist::Utf8ToBSTR( const string& strSrc )
{
	BSTR strRet = NULL;

	/*!< ���Ŀ��ռ�Ĵ�С */
	int iSize = static_cast< int >( strSrc.size() );
	int iAllocSize = MultiByteToWideChar( CP_UTF8, 0, strSrc.c_str(), iSize, NULL, NULL );
	if ( 0 < iAllocSize )
	{
		/*!< ����Ŀ��ռ� */
		strRet = ::SysAllocStringByteLen( NULL, iAllocSize );
		if ( NULL != strRet )
		{
			int iResult = MultiByteToWideChar( CP_UTF8, 0, strSrc.c_str(), iSize, strRet, iAllocSize );
			if ( iResult != iAllocSize )
			{
				SysFreeString( strRet );
				strRet = NULL;
			}
		} // end of if ( NULL !- strRet ) ...
	} // end of if ( 0 < iAllocSize ) ...

	/*!< ���ⷵ�ؿ�ָ�� */
	if( NULL == strRet )
	{
		strRet = ::SysAllocString( L"" );
	}

	return strRet;
}

/***********************************************************************************
* name       : BSTRToUtf8
* description: �ַ���ת��: BSTR - UTF8
* input      : bstrSrc Ҫת����BSTR�ַ���
* output     : NA
* return     : ת�����UTF8�ַ���������ַ���
* remark     : NA
***********************************************************************************/
string CStrAssist::BSTRToUtf8( const BSTR& bstrSrc )
{
	/*!< ���Ŀ��ռ�Ĵ�С */
	int iAllocSize = WideCharToMultiByte( CP_UTF8, 0, bstrSrc, -1, NULL, NULL, NULL, FALSE ) - 1;
	if ( 0 >= iAllocSize )
	{
		return "";
	}

	/*!< ����ֵ */
	string strRet( iAllocSize, '\0' );

	/*!< ����ת�� */
	int nResult = WideCharToMultiByte( CP_UTF8, 0, bstrSrc, -1, const_cast< char* >( strRet.c_str() ),
		iAllocSize, NULL, FALSE );

	return strRet;
}

/***********************************************************************************
* name       : GbkToUtf8
* description: �ַ���ת��: GBK - UTF8
* input      : strGBK:Ҫת����GBK�ַ���;
* output     : NA
* return     : ת�����UTF8�ַ���������ַ���
* remark     : NA
***********************************************************************************/
string CStrAssist::GbkToUtf8( const std::string& strGbk )
{
	string strOutUtf8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar( CP_ACP, 0, strGbk.c_str(), -1, NULL, 0 );
	str1 = new WCHAR[ n ];
	MultiByteToWideChar( CP_ACP, 0, strGbk.c_str(), -1, str1, n );
	n = WideCharToMultiByte( CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL );
	char * str2 = new char[ n ];
	WideCharToMultiByte( CP_UTF8, 0, str1, -1, str2, n, NULL, NULL );
	strOutUtf8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUtf8;
}

/***********************************************************************************
* name       : Utf8ToGbk
* description: �ַ���ת��: UTF8 - GBK
* input      : strUTF8 Ҫת����UTF8�ַ���
* output     : NA
* return     : ת�����GBK�ַ���������ַ���
* remark     : NA
***********************************************************************************/
string CStrAssist::Utf8ToGbk( const std::string& strUtf8 )
{
	int len = MultiByteToWideChar( CP_UTF8, 0, strUtf8.c_str(), -1, NULL, 0 );	
	WCHAR * wszGbk = new WCHAR[ len + 1 ];
	memset( wszGbk, 0, ( len << 1 ) + 2 );
	MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)strUtf8.c_str(), -1, wszGbk, len );

	len = WideCharToMultiByte( CP_ACP, 0, wszGbk, -1, NULL, 0, NULL, NULL );
	char* szGbk = new char[ len + 1 ];
	memset( szGbk, 0, len + 1 );
	WideCharToMultiByte( CP_ACP, 0, wszGbk, -1, szGbk, len, NULL, NULL );

	std::string strTemp( szGbk );
	delete[]szGbk;
	delete[]wszGbk;
	return strTemp;
}

//\Uab12QQ\u2387pp -> Ansi 
string CStrAssist::UnicodeIntStrToAnsi( const std::string& strIntStr, bool bHex /*= false*/ )
{
	string strRet;
	for ( int i(0); i < (int)strIntStr.size(); i++ )
	{
		string::const_iterator itor = strIntStr.begin() + i;
		if ( *itor == '\\' )
		{
			itor++;
			if ( *itor == 'u' ||  *itor == 'U' )//  \u79fb\u52a8QQ(\u624b\u673a\u53f7\u7801)
			{
				itor++;
				string strTempName(itor, itor + 4);	
				WCHAR wc = (WCHAR)CStrAssist::StrToInt( strTempName, bHex );	
				wstring strAnsi;
				strAnsi.push_back(wc);						
				strRet += CStrAssist::UnicodeToAnsi(strAnsi) ;
				i = i + 5;
			}
			else
			{
				itor--;
				strRet += *itor;

			}
		}
		else
		{
			strRet += *itor;
		}	

	}
	return strRet;
}

string CStrAssist::UrlEncode( const std::string& normal )
{
	std::stringstream ss;
	char tmp[4] = {0};
	const char* p = normal.c_str();
	for(; *p; ++p){
		if (isalnum(*p)){
			ss<<*p;
		} else if (*p == ' '){
			ss<<'+';
		} else {
			sprintf(tmp, "%%%2X", (int)*p);
			ss<<tmp;
		}	
	}

	return ss.str();
}

bool hexDidit(int c)
{
	char up = toupper(c);
	return (isdigit(c) || (up >= 'A' && up <= 'F'));
}
int CStrAssist::UrlDecode( const std::string& normal, string &dec )
{
	stringstream ss;
	int hh;
	char tmp[5] = "0X";
	const char* p = normal.c_str();
	const char* end = p+normal.length();
	for(; *p; ++p){
		if (*p != '%'){
			ss<<*p;
		} else if(*p == '+'){
			ss<<' ';
		} else {
			if(p+2 > end)
				return -1;
			tmp[2] = toupper(*(p+1));
			tmp[3] = toupper(*(p+2));
			if (!hexDidit(tmp[2]) || !hexDidit(tmp[3]))
				return -1;
			if(sscanf(tmp, "%X", &hh) == 1)
				ss<<char(hh);
			else
				return -1;
			p += 2;
		}			
	}
	dec = ss.str();
	return 0;
}