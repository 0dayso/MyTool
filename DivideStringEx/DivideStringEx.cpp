// DivideStringEx.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
void DivideStringBySymbol(const string& strIn, const vector<string>& vecSymbol,	vector<string>& vecHasDivide)
{	
	vector<int> vecDivideIndex;			//�ָ�����±�
	vector<int>::iterator itrDivideIndex;

	vector<string>::const_iterator itrSymbol;	
	int iTempIndex;	

	//;,asfdsafsasd;,adfasdf;ree
	for ( itrSymbol = vecSymbol.begin(); itrSymbol != vecSymbol.end(); itrSymbol++ )//���ҵ�һ�����ŵ��±�
	{
		int iFindIndex(0);
		do 
		{
			iTempIndex = strIn.find(*itrSymbol, iFindIndex);
			if ( iTempIndex != string::npos )
			{				
				vecDivideIndex.push_back(iTempIndex);
				iFindIndex = iTempIndex + itrSymbol->size();									
			}
			else
			{
				break;
			}
		} while (1);
	}

	if ( vecDivideIndex.size() > 0 )
	{
		vecDivideIndex.push_back(strIn.size());
		//���򲢳���
		sort(vecDivideIndex.begin(), vecDivideIndex.end());
		vector<int>::iterator itNewEnd = unique(vecDivideIndex.begin(), vecDivideIndex.end());//uniqueֻ�ǽ����صķŵ�ǰ�棬����Ĳ���
		vecDivideIndex.erase( itNewEnd, vecDivideIndex.end() );//���Ա���ɾ�������
		int iIndexDivide(0);
		for ( int i(0); i <= vecDivideIndex.size(); i++ )
		{
			string strHasDivide( strIn, iIndexDivide, vecDivideIndex[i] - iIndexDivide );
			if ( strHasDivide.size() > 0 && strHasDivide != "" && strHasDivide != " " && strHasDivide != "  ")
			{
				bool bIsSameSymbol(false);
				for ( itrSymbol = vecSymbol.begin(); itrSymbol != vecSymbol.end(); itrSymbol++ )
				{
					if ( strHasDivide == *itrSymbol )
					{
						bIsSameSymbol = true;
						break;
					}

				}
				if ( bIsSameSymbol == false  )
				{
					vecHasDivide.push_back(strHasDivide);
				}
			}
			//���ָ������±곤��

			for ( itrSymbol = vecSymbol.begin(); itrSymbol != vecSymbol.end(); itrSymbol++ )
			{
				int iSymbolIndex = strIn.find(*itrSymbol,  vecDivideIndex[i]);
				if ( iSymbolIndex == vecDivideIndex[i] )
				{
					iIndexDivide = vecDivideIndex[i] + itrSymbol->size();
				}
			}

			if ( iIndexDivide >= strIn.size() )
			{
				break;
			}
		}		
	}
	if ( vecHasDivide.size() == 0 )
	{
		vecHasDivide.push_back(strIn);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	string strSrc = "***aaaa|dfadsfdas*fafdasd*&2f&";
	vector<string> vecDivideUse;
	vecDivideUse.push_back("|");
	vecDivideUse.push_back("*");
	vecDivideUse.push_back("&");
	vector<string> vecOut;
	DivideStringBySymbol(strSrc, vecDivideUse,  vecOut);
	for ( vector<string>::iterator it = vecOut.begin(); it != vecOut.end(); ++it )
	{
		printf("%s\n", it->c_str());
	}
	system("pause");
	return 0;
}

