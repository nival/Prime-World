#include "stdafx.h"

#include "StrProc.h"
#include "ThreadLocal.h"

#include <cstdio>
#include <System/ported/cwfn.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NStr 
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int gs_nCodePage = GetACP();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// разделить строку на массив строк по заданному разделителю
__forceinline int Len( const char )
{
	return 1;
}
__forceinline int Len( const wchar_t )
{
	return 1;
}
__forceinline int Len( const string &t )
{
	return t.size();
}
__forceinline int Len( const wstring &t )
{
	return t.size();
}
template <class T1, class T2>
void SplitStringT( const basic_string<T1> &szString, vector< basic_string<T1> > *pVector, const T2 tSeparator )
{
	int nPos = 0, nLastPos = 0;
	//
	do
	{
		nPos = szString.find( tSeparator, nLastPos );
		// add string
		pVector->push_back( szString.substr( nLastPos, nPos - nLastPos ) );
		nLastPos = nPos + Len(tSeparator);
		//
	} while( nPos != basic_string<T1>::npos );
}
void SplitString( const string &szString, vector<string> *pVector, const char cSeparator )
{
	SplitStringT( szString, pVector, cSeparator );
}
void SplitString( const string &szString, vector<string> *pVector, const string &szSeparator )
{
	SplitStringT( szString, pVector, szSeparator );
}
void SplitString( const wstring &szString, vector<wstring> *pVector, const wchar_t cSeparator )
{
	SplitStringT( szString, pVector, cSeparator );
}
void SplitString( const wstring &szString, vector<wstring> *pVector, const wstring &szSeparator )
{
	SplitStringT( szString, pVector, szSeparator );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class TChar>
void SplitStringWithMultipleBracketsT( const basic_string<TChar> &szString, vector<basic_string<TChar> > &szVector, const TChar cSeparator )
{
	for ( CStringIterator<TChar, const basic_string<TChar>&, CBracketSeparator<TChar, SBracketsQuoteTest<TChar> > > it(szString, cSeparator); !it.IsEnd(); it.Next() )
		szVector.push_back( it.Get() );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SplitStringWithMultipleBrackets( const string &szString, vector<string> &szVector, const char cSeparator )
{
	SplitStringWithMultipleBracketsT( szString, szVector, cSeparator );
}
void SplitStringWithMultipleBrackets( const wstring &szString, vector<wstring> &szVector, const wchar_t cSeparator )
{
	SplitStringWithMultipleBracketsT( szString, szVector, cSeparator );
}
// вырезать все символы 'cTrim' из строки
template <class T>
class CSymbolCheckFunctional
{
private:
	const T *pszSymbols;
public:
	explicit CSymbolCheckFunctional( const T *pszNewSymbols ) : pszSymbols( pszNewSymbols ) {	}
	bool operator()( const T cSymbol )
	{
		for ( const T *p = pszSymbols; *p != 0; ++p )
		{
			if ( *p == cSymbol )
				return true;
		}
		return false;
	}
};
void TrimInside( wstring &wszString, const wchar_t *pwszTrim )
{
	wszString.erase( remove_if(wszString.begin(), wszString.end(), CSymbolCheckFunctional<wchar_t>(pwszTrim)), wszString.end() );
}
void TrimInside( string &szString, const char *pszTrim )
{
	szString.erase( remove_if(szString.begin(), szString.end(), CSymbolCheckFunctional<char>(pszTrim)), szString.end() );
}
int ExtractIndex(const char * s)
{
		if ( !s )
		return -1;
	const int ln = strlen(s);
	if ( ln <= 0 )
		return -1;
	int lastNotDigit = ln-1;
	while ( lastNotDigit > 0 )
	{
		if ( !isdigit(s[lastNotDigit]) )
			break;
		--lastNotDigit;
	}
	if ( ln - lastNotDigit <= 0 )
		return -1;
	return atoi( s + lastNotDigit + 1 );

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ToInt( const char *pszString )
{
	int nNumber = atoi( pszString );
	return nNumber;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ToInt( const wchar_t *pwszString )
{
	int nNumber = _wtoi( pwszString );
	return nNumber;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ToFloat( const char *pszString )
{
	return (float)ToDouble( pszString );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ToFloat( const wchar_t *pwszString )
{
	return (float)ToDouble( pwszString );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double ToDouble( const char *pszString )
{
	double fNumber = atof( pszString );
	return fNumber;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double ToDouble( const wchar_t *pszString )
{
	double fNumber = _wtof( pszString );
	return fNumber;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned long ToULong( const char *pszString )
{
	unsigned long ulNumber = atoi( pszString );
	return ulNumber;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <[+/-]>[dec digit]*
bool IsDecNumber( const string &szString )
{
	if ( szString.empty() )
		return false;
	int i, nFirstDigit = IsSign( szString[0] ) ? 1 : 0;
	int nNumDigits = szString.size() - nFirstDigit;
	if ( nNumDigits == 0 )
		return false;												// this is not a number at all => zero length digits
	if ( (nNumDigits > 1) && (szString[nFirstDigit] == '0') )
		return false;												// hex number
	for ( i=nFirstDigit; (i < szString.size()) && IsDecDigit(szString[i]); ++i ) { ; }
	return ( (i > nFirstDigit) && (i == szString.size()) );
}
// <[+/-]>[dec digit]*
bool IsDecNumber( const char* str )
{
	if ( !str )
		return false;
	const int firstDigit = IsSign( str[0] ) ? 1 : 0;
	if ( str[firstDigit] == 0 )
		return false;												// this is not a number at all => zero length digits
	if ( str[firstDigit] == '0' && str[firstDigit+1] != 0 )
		return false;												// hex number

  for( int i = firstDigit; str[i] != 0; ++i )
  {
    if ( !IsDecDigit( str[i] ) )
      return false;
  }

  return true;
}
// [+|-](dec digit)*[.(dec digit)*]
bool IsFloatNumber( const char* str )
{
	if ( !str )
		return false;
	const int firstDigit = IsSign( str[0] ) ? 1 : 0;
	if ( str[firstDigit] == 0 )
		return false;

  bool dotFound = false;
  for( int i = firstDigit; str[i] != 0; ++i )
  {
    if ( str[i] == '.' )
    {
      if ( dotFound )
        return false;

      dotFound = true;
    }
    else if ( !IsDecDigit( str[i] ) )
      return false;
  }

  return true;
}
// <[+/-]>[0][oct digit]*
bool IsOctNumber( const string &szString )
{
	if ( szString.empty() )
		return false;
	int i, nFirstDigit = IsSign( szString[0] ) ? 1 : 0;
	int nNumDigits = szString.size() - nFirstDigit;
	if ( nNumDigits == 0 )
		return false;
	if ( szString[nFirstDigit] != '0' )
		return false;
	if ( nNumDigits < 2 )
		return false;

	for ( i=nFirstDigit; (i < szString.size()) && IsOctDigit(szString[i]); ++i ) { ; }
	return ( (i > nFirstDigit) && (i == szString.size()) );
}
// <[+/-]>[0x][hex digit]*
bool IsHexNumber( const string &szString )
{
	if ( szString.empty() )
		return false;
	int i, nFirstDigit = IsSign( szString[0] ) ? 1 : 0;
	int nNumDigits = szString.size() - nFirstDigit;
	if ( nNumDigits < 3 )
		return false;
	if ( (szString[nFirstDigit] != '0') || (szString[nFirstDigit + 1] != 'x') )
		return false;
	for ( i=nFirstDigit + 2; (i < szString.size()) && IsHexDigit(szString[i]); ++i ) { ; }
	return ( (i > nFirstDigit) && (i == szString.size()) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** string-to-bin and vice versa
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* BinToString( const void *pData, int nSize, char *pszBuffer )
{
	char *pszCurr = pszBuffer;
	for ( const unsigned char *it = (unsigned char*)pData; it != (unsigned char*)pData + nSize; ++it )
	{
		*pszCurr++ = HalfByteToHexSymbol( ((*it) >> 4) & 0x0f );
		*pszCurr++ = HalfByteToHexSymbol( (*it) & 0x0f );
	}
	return pszBuffer;
}
void* StringToBin( const char *pszData, void *pBuffer, int *pnSize )
{
	BYTE *pData = (BYTE*)pBuffer;
	for ( const char *it = pszData; *it != 0; it += 2 )
		*pData++ = ( HexSymbolToHalfByte( *it ) << 4 ) | HexSymbolToHalfByte( *(it +1) );
	if ( pnSize ) 
		*pnSize = int( pData - (BYTE*)pBuffer );
	return pBuffer;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** перевод Unicode <=> UTF-8
// ** bytes | bits | representation
// **		 1 |		7 | 0vvvvvvv
// **		 2 |	 11 | 110vvvvv 10vvvvvv
// **		 3 |	 16 | 1110vvvv 10vvvvvv 10vvvvvv
// **		 4 |	 21 | 11110vvv 10vvvvvv 10vvvvvv 10vvvvvv
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnicodeToUTF8( string *pRes, const wstring &szString )
{
	pRes->resize( 0 );
	pRes->reserve( szString.size() * 2 );
	for ( wstring::const_iterator it = szString.begin(); it != szString.end(); ++it )
	{
		const wchar_t chr = *it;
		if ( chr < 0x80 )
			*pRes += ( chr );
		else if ( chr < 0x800 ) 
		{
			*pRes += ( 0xC0 | chr>>6 );
			*pRes += ( 0x80 | chr & 0x3F );
		}
		else
		{
			*pRes += ( 0xE0 | chr>>12 );
			*pRes += ( 0x80 | chr>>6 & 0x3F );
			*pRes += ( 0x80 | chr & 0x3F );
		}
	}
}
void UTF8ToUnicode( wstring *pRes, const string &szString )
{
	pRes->resize( 0 );
	pRes->reserve( szString.size() );
	string::const_iterator it = szString.begin();
	while ( it != szString.end() ) 
	{
		BYTE chr = BYTE( *it );
		if ( (chr & 0x80) == 0 ) 
			*pRes += chr;
		else if ( (chr & 0xe0) == 0xc0 )	// check first 3 bits ( wchar < 0x800 )
		{
			wchar_t res = (chr & 0x1f) << 6;
			++it;
			chr = BYTE( *it );
			res |= ( chr & 0x3f );
			*pRes += res;
		}
		else if ( (*it & 0xf0) == 0xe0 ) 	// check first 4 bits ( wchar < 0xffff )
		{
			wchar_t res = ( chr & 0x0f ) << 12;
			++it;
			chr = BYTE( *it );
			res |= ( chr & 0x3f ) << 6;
			++it;
			chr = BYTE( *it );
			res |= chr & 0x3f;
			*pRes += res;
		}
		++it;
	}
}



inline bool IsStringBeginsWith( const wstring & text, int & offset, const wchar_t * word )
{
  size_t len = wcslen( word );
  
  if ( offset + (int)len > text.size() )
    return false;

  for ( int i = 0; i < (int)len; ++i )
    if ( text[offset + i] != word[i] )
      return false;

  offset += len;
  return true;
}



void StripXmlEscapes( wstring & result, const wstring & text )
{
  result.clear();
  result.reserve( text.size() );

  for ( int i = 0; i < text.size(); )
  {
    if ( text[i] != L'&' )
    {
      result += text[i];
      ++i;
      continue;
    }

    if ( IsStringBeginsWith( text, i, L"&quot;" ) )
      result += L'\"';
    else if ( IsStringBeginsWith( text, i, L"&apos;" ) )
      result += L'\'';
    else if ( IsStringBeginsWith( text, i, L"&amp;" ) )
      result += L'&';
    else if ( IsStringBeginsWith( text, i, L"&lt;" ) )
      result += L'<';
    else if ( IsStringBeginsWith( text, i, L"&gt;" ) )
      result += L'>';
    else
      ++i;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// перевод MBCS <=> Unicode
void SetCodePage( const int nCodePage )
{
	gs_nCodePage = nCodePage;
}
void ToMBCS( string *pRes, const wstring &szSrc )
{
  int nStrSize       = szSrc.length();
  if(nStrSize == 0)
  {
    pRes->clear();
    return;
  }
	const int nBuffLen = nStrSize * 6 + 10;      //codepage can be UTF-8
	pRes->resize( nBuffLen );
	const int nLength = WideCharToMultiByte( gs_nCodePage, 0, szSrc.c_str(), nStrSize, &(*(pRes->begin())), nBuffLen, 0, 0 );
	pRes->resize( nLength );
}
void ToUnicode( wstring *pRes, const string &szSrc )
{
  int nStrSize       = szSrc.length();
  if(nStrSize == 0)
  {
    pRes->clear();
    return;
  }
	const int nBuffLen = nStrSize + 3;
	pRes->resize( nBuffLen );
	const int nLength  = MultiByteToWideChar( gs_nCodePage, 0, szSrc.c_str(), nStrSize, &(*(pRes->begin())), nBuffLen );
	pRes->resize( nLength );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UTF8ToMBCS( string *pRes, const string &szSrc )
{
	wstring wszTemp;
	UTF8ToUnicode( &wszTemp, szSrc );
	ToMBCS( pRes, wszTemp );
}
void MBCSToUTF8( string *pRes, const string &szSrc )
{
	wstring wszTemp;
	ToUnicode( &wszTemp, szSrc );
	UnicodeToUTF8( pRes, wszTemp );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GUID => string
void GUID2String( string *pString, const GUID &guid )
{
	*pString = NStr::StrFmt( "%.8X-%.4X-%.4X-%.2X%.2X-%.2X%.2X%.2X%.2X%.2X%.2X", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], 
		guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7] );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static inline unsigned char HexSymbolToByte( const char *c )
{
  return HexSymbolToHalfByte( c[0] ) << 8 | HexSymbolToHalfByte( c[1] );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool String2GUID( const char* str, GUID *result )
{
  if ( str == 0 )
    return false;

  char guidValue[32];
  int guidIndex = 0;
  for( const char* c = str; *c; ++c )
  {
    if ( *c >= '0' && *c <= '9' || *c >= 'A' && *c <= 'F' || *c >= 'a' && *c <= 'f' )
    {
      if ( guidIndex == 32 )
        return false;
      guidValue[guidIndex++] = *c;
    }
    else if ( *c != '-' && *c != '{' && *c != '}' && *c != '(' && *c != ')' )
      return false;
  }

  if ( guidIndex != 32 )
    return false;

  result->Data1 = HexSymbolToByte( &guidValue[0] ) << 24 | HexSymbolToByte( &guidValue[2] ) << 16 | HexSymbolToByte( &guidValue[4] ) << 8 | HexSymbolToByte( &guidValue[6] );
  result->Data2 = HexSymbolToByte( &guidValue[8] ) << 8 | HexSymbolToByte( &guidValue[10] );
  result->Data3 = HexSymbolToByte( &guidValue[12] ) << 8 | HexSymbolToByte( &guidValue[14] );
  for( int i = 0; i < 8; ++i )
    result->Data4[i] = HexSymbolToByte( &guidValue[2*i + 16] );

  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int ReadInt( const char *p, const int nSize )
{
  if ( p == NULL )
  {
    NI_ASSERT(false, "ReadInt(). Invalid pointer p. Maybe somebody missed the value in the xml file.");
    return 0;
  }
	/*	
	int n = 0;
	_snscanf(	p, nSize, "%i", &n );
	return n;
	*/
	const char *pEnd = p + nSize;
	int n = 0;
	int nSign = 1;

	if ( nSize >= 2 && *p == '0' && *(p+1) == 'x' )
	{
		p += 2;
		while ( p < pEnd )
		{
			int nDst = 0;
			if ( *p >= '0' && *p <= '9' )
				nDst = *p - '0';
			else if ( *p >= 'a' && *p <= 'f' )
				nDst = *p - 'a' + 10;
			else if ( *p >= 'A' && *p <= 'F' )
				nDst = *p - 'A' + 10;
			else break;

			n = n * 16 + nDst;
			++p;
		}
	}
	else
	{
		if ( *p == '-' )
		{
			nSign = -1;
			++p;
		}

		while ( p < pEnd && *p >= '0' && *p <= '9' )
		{
			n = n*10 + *p - '0';
			++p;
		}
	}

	return n * nSign;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float ReadFloat( const char *p, const int nSize )
{
  if ( !p || nSize == 0 )
    return 0.0f;

	const char *pEnd = p + nSize;
	float f = 0.0f;
	int nSign = 1;
	if ( *p == '-' )
	{
		nSign = -1;
		++p;
	}

	while ( p < pEnd && *p >= '0' && *p <= '9' )
	{
		f = f * 10.0f + *p - '0';
		++p;
	}

	if ( p == pEnd )
		return f * nSign;

	if ( *p == '.' )
	{
		++p;
		float fPower = 1.0f;
		while ( p < pEnd && *p >= '0' && *p <= '9' )
		{
			//fPower /= 10.0f;
			fPower *= 0.1f;
			f += (*p - '0') * fPower;
			++p;
		}
	}

	if ( *p == 'e' || *p == 'E' )
	{
		++p;
		if ( p < pEnd )
		{
			int nESign = 1;
			if ( *p == '-' )
			{
				nESign = -1;
				++p;
			}
			else if ( *p == '+' )
				++p;

			int nPower = 0;
			while ( p < pEnd && *p >= '0' && *p <= '9' )
			{
				nPower = nPower * 10.0f + *p - '0';
				++p;
			}
			nPower *= nESign;

			f *= pow( 10.0f, nPower );
		}
	}

	return f * nSign;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wstring ReplaceInnerStr( const wstring &wszString, const wstring &wszToCut, const wstring &wszToPaste )
{
	wstring wszResult = wszString;
	vector<wstring> tmpResult;
	SplitString( wszString, &tmpResult, wszToCut );
	if ( tmpResult.size() > 1 )
	{
		wszResult = L"";
		for ( int i = 0; i < ( tmpResult.size() - 1 ); ++i )
			wszResult += ( tmpResult[ i ] + wszToPaste );
		wszResult += tmpResult.back();
	}
	return wszResult;
}

struct NChar64
{
	char buffer[64];
};

struct WChar64
{
	wchar_t buffer[64];
};

template <typename T>
class NStrFmtBuffer
{
  static const int bufferCount = 4;
  int nCurrIdx;
  T buffer[bufferCount];
public:
  NStrFmtBuffer(): nCurrIdx(0) {}
  void next()
  {
    nCurrIdx += 1;
    nCurrIdx = nCurrIdx % bufferCount;
  }
  T& Get()
  {
    return buffer[nCurrIdx];
  }
};
struct NChar16384
{
	char buffer[16384];
};

struct WChar16384
{
	wchar_t buffer[16384];
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string IntToStr( int nValue )
{
	static ThreadLocal<NChar64> buffer;
  NStr::Printf( buffer.GetValue().buffer, 64, "%d", nValue );
	return buffer.GetValue().buffer;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wstring IntToWStr( int nValue )
{
	static ThreadLocal<WChar64> buffer;
  NStr::SWPrintf( buffer.GetValue().buffer, 64, L"%d", nValue );
	return buffer.GetValue().buffer;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char * StrFmt( const char *pszFormat, ... )
{
	static ThreadLocal<NStrFmtBuffer<NChar16384> > charBuff;
  NStrFmtBuffer<NChar16384> &buff = charBuff.GetValue();
	buff.Get().buffer[0] = '\0';
	va_list va;
	va_start( va, pszFormat );
	_vsnprintf_s( buff.Get().buffer, 16384 - 1, pszFormat, va );
	va_end( va );
  const char* res = buff.Get().buffer;
  buff.next();
	return res;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const wchar_t * StrFmtW( const wchar_t *pszFormat, ... )
{
  static ThreadLocal<NStrFmtBuffer<WChar16384> > charBuff;
  NStrFmtBuffer<WChar16384> &buff = charBuff.GetValue();
	buff.Get().buffer[0] = '\0';
	va_list va;
	va_start( va, pszFormat );
	_vsnwprintf_s( buff.Get().buffer, 16384 - 1, pszFormat, va );
	va_end( va );

  const wchar_t* res = buff.Get().buffer;
  buff.next();

  return res;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static const char * strnistr( const char * pszString, const char * pszSearch, size_t searchLength )
{
  size_t srchLen = strlen(pszSearch);
  if(srchLen == 0)
    return NULL;
  if(srchLen < searchLength)
    searchLength = srchLen;

  size_t length = strlen(pszString);
  for(size_t i = searchLength; i <= length; i++, pszString++)
    if(_strnicmp(pszString, pszSearch, searchLength) == 0)
      return pszString;
  return NULL;
}



static bool WildRecursion( const char * text, const char * wild, size_t wildLen )
{
  bool fixed = true;

  while(true)
  {
    if( !wildLen )
    {
      //Текст в маске исчерпан
      if ( text[0] != '\0' ) //если остался непроверенный текст
        if ( fixed )
          return false;
        else //если в конце маски была звездочка, то ок, иначе - несовпадение текста и маски
          return true;
      return true;
    }

    if( wild[0] == '?' )
    {
      wild++;
      text++;
      wildLen--;
      continue;
    }

    if( wild[0] == '*' )
    {
      fixed = false;
      wild++;
      wildLen--;
      continue;
    }

    //любой другой символ - начало блока текста
    size_t blockLen = strcspn( wild, "*?" );
    NI_ASSERT( blockLen > 0, "" );

    //Если перед блоком встретилсо символ '*', будем искать все вхождения блока wild[blockLen) в тексте text
    //и пробовать рекурсивно распознать их все
    //Если перед блоком не было ничего, или только символы '?', то просто проверим наличие блока в тексте и будем распознавать дальше
    if( fixed )
    {
      if ( _strnicmp( text, wild, blockLen ) != 0 ) //Текст должен быть в начале строки text
        return false;
      return WildRecursion( text + blockLen, wild + blockLen, wildLen - blockLen );
    }
    else
      while(true)
      {
        const char * find = strnistr( text, wild, blockLen ); //Текст должен быть ГДЕ-ТО в строке text
        
        if( !find )
          return false;

        text = find + blockLen;
        if ( WildRecursion( text, wild + blockLen, wildLen - blockLen ) )
          return true;
      }
  }
}



bool WildcardCompare( const char * text, const char * wildcard )
{
  return WildRecursion( text, wildcard, strlen( wildcard ) );
}



inline void AppendHex( string & out, char c ) {
  static const char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

  out += '%';
  out += hex[(c & 0xf0) >> 4];
  out += hex[c & 0xf];
}

void UrlEncode( string & out, const string & src, bool formUrl, bool softRules )
{
  out.reserve( src.length() + src.length() / 10 );

  for( string::const_iterator i = src.begin(); i != src.end(); ++i )
  {
    const char c = *i;
    if ( formUrl && c == ' ' )
      out += '+';
    else if ( softRules && ( c=='{' || c=='}' || c=='"' || c=='!' || c=='*' || c=='(' || c==')' ) )
      out += c;
    else if (
        ( '0' <= c && c <= '9' ) ||
        ( 'a' <= c && c <= 'z' ) || ( 'A' <= c && c <= 'Z' ) ||
        ( c=='~' || c=='\'' || c=='-' || c=='.' || c=='_' )
      )
      out += c;
    else
      AppendHex( out, c );
  }
}



inline int hextoi( char c ) {
  int cc = tolower( (unsigned char)c );
  return isdigit( cc ) ? cc - '0' : cc - 'W';
}

void UrlDecode( string & out, const string & src,int is_form_url_encoded)
{
  for ( int i = 0; i < src.length(); i++ )
  {
    if ( src[i] == '%' && ( i + 2 < src.size() ) && isxdigit( (unsigned char)src[i + 1] ) && isxdigit( (unsigned char)src[i + 2] ) )
    {
      out += (char)( ( hextoi( src[i+1] ) << 4 ) | hextoi( src[i+2] ) );
      i += 2;
    }
    else if ( is_form_url_encoded && src[i] == '+' ) {
      out += ' ';
    }
    else
      out += src[i];
  }
}

}; // end of namespace NStr
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
