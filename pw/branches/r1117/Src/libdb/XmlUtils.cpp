#include "stdafx.h"

#include "XmlUtils.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NXml
{
struct SEntityInfo
{
	const char* pszCode;
	char value;
};

SEntityInfo entities[] =
{
	{ "amp;", '&' },
	{ "lt;", '<' },
	{ "gt;", '>' },
	{ "quot;", '\"' },
	{ "apos;", '\'' },
	{ 0, 0 }
};

void ConvertToString( string *pStr )
{
	string &str = *pStr;
	
	int i = 0;
	int nCnt = 0;
	while ( i < str.size() )
	{
		if ( str[i] == '&' )
		{
			if ( i + 5 < str.size() && str[i+1] == '#' && str[i+2] == 'x' )
			{
				char c1, c2;
				if ( isalpha( str[i+3] ) )
					c1 = ( tolower( str[i+3] ) - 'a' + 10 ) * 16;
				else						 
					c1 = ( str[i+3] - '0' ) * 16;

				if ( isalpha( str[i+4] ) ) 
					c2 = ( tolower( str[i+4] ) - 'a' + 10 );
				else						 
					c2 = ( str[i+4] - '0' );

				str[nCnt++] = c1;
				str[nCnt++] = c2;
				i += 6;
			}
			else
			{
				int j = 0;
				bool bMatch = false;
				while ( !bMatch && entities[j].pszCode != 0 )
				{
					int k1 = 0;
					int k2 = i + 1;
					while ( *(entities[j].pszCode + k1) != 0 && k2 < str.size() )
					{
						if ( *(entities[j].pszCode + k1) != str[k2] )
							break;
						++k1;
						++k2;
					}

					if ( *(entities[j].pszCode + k1) == 0 )
					{
						str[nCnt++] = entities[j].value;
						i = k2;
						bMatch = true;
						break;
					}

					++j;
				}

				if ( !bMatch )
					str[nCnt++] = str[i++];
			}
		}
		else
			str[nCnt++] = str[i++];
	}

	str.resize( nCnt );
}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
