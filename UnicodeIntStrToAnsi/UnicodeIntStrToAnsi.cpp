// UnicodeIntStrToAnsi.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <Windows.h>
#include <xstring>
using namespace std;
string UnicodeIntStrToAnsi( const std::string& strIntStr, bool bHex /*= false*/ );
int _tmain(int argc, _TCHAR* argv[])
{

	string strSrc = "\u1234 QQ\uabcds";
	string strRet = UnicodeIntStrToAnsi( strSrc, true);
	printf("%s\n", strRet.c_str());

	system("PAUSE");
	return 0;
}


/***********************************************************************************
* name       : StrToInt
* description: ������ת��Ϊ�ַ���
* input      : strSrc Ҫת�����ַ�����bHex �Ƿ���ʮ������������
* output     : NA
* return     : ת�����������
* remark     : NA
***********************************************************************************/
int StrToInt ( const string& strSrc, bool bHex /*= false*/ )
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
* name       : UnicodeToAnsi
* description: �ַ���ת��: Unicode - Ansi
* input      : strSrc Ҫת����Unicode�ַ���������ַ���
* output     : NA
* return     : ת�����Ansi�ַ���������ַ���
* remark     : NA
***********************************************************************************/
string UnicodeToAnsi ( const wstring& wstrSrc )
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

//\Uab12QQ\u2387pp -> Ansi 
string UnicodeIntStrToAnsi( const std::string& strIntStr, bool bHex /*= false*/ )
{
	string strRet;
	for ( int i(0); i < strIntStr.size(); i++ )
	{
		string::const_iterator itor = strIntStr.begin() + i;
		if ( *itor == '\\' )
		{
			itor++;
			if ( *itor == 'u' ||  *itor == 'U' )//  \u79fb\u52a8QQ(\u624b\u673a\u53f7\u7801)
			{
				itor++;
				string strTempName(itor, itor + 4);	
				WCHAR wc = (WCHAR)StrToInt( strTempName, bHex );	
				wstring strAnsi;
				strAnsi.push_back(wc);						
				strRet +=UnicodeToAnsi(strAnsi) ;
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

