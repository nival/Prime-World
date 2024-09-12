#ifndef _LIGHTXMLUTILS_H_
#define _LIGHTXMLUTILS_H_

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../System/StrFormatter.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NLightXml
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** convertors
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CToStringConvertor
{
	NStr::CStrFormatter format;
public:
	CToStringConvertor( const char value ) { format.Format( long(value) ); }
	CToStringConvertor( const signed char value ) { format.Format( long(value) ); }
	CToStringConvertor( const unsigned char value ) { format.Format( (unsigned long)value ); }
	CToStringConvertor( const short value ) { format.Format( long(value) ); }
	CToStringConvertor( const unsigned short value ) { format.Format( (unsigned long)value ); }
	CToStringConvertor( const long value ) { format.Format( long(value) ); }
	CToStringConvertor( const unsigned long value ) { format.Format( (unsigned long)value ); }
	CToStringConvertor( const int value ) { format.Format( long(value) ); }
	CToStringConvertor( const unsigned int value ) { format.Format( (unsigned long)value ); }
	CToStringConvertor( const float value ) { format.Format( value ); }
	CToStringConvertor( const double value ) { format.Format( value ); }
	//
	operator const char *() const { return format.GetBuffer(); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** string composing buffer
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CStringComposer
{
	vector<char> chars;
	//
	void Reserve( const int nSize )
	{
		if ( chars.capacity() < nSize )
			chars.reserve( (int)(nSize * 1.5f) );
	}
	void AddString( const char *pszStringBegin, const int nLength )
	{
		Reserve( chars.size() + nLength );
		chars.insert( chars.end(), pszStringBegin, pszStringBegin + nLength );
	}
	void AddChar( const char chr )
	{
		Reserve( chars.size() + 1 );
		chars.push_back( chr );
	}
public:
	explicit CStringComposer( const int nBufferSize = 256 )
	{
		chars.reserve( nBufferSize < 8 ? 8 : nBufferSize );
	}
	//
	CStringComposer& operator<<( const string &szString )
	{
		AddString( szString.c_str(), szString.size() );
		return *this;
	}
	CStringComposer& operator<<( const char *pszString )
	{
		AddString( pszString, strlen(pszString) );
		return *this;
	}
	CStringComposer& operator<<( const char chr )
	{
		AddChar( chr );
		return *this;
	}
	//
	const char* str() const { return chars.empty() ? "" : &( chars[0] ); }
	int GetSize() const { return chars.size(); }
	bool IsEmpty() const { return chars.empty(); }
	void Clear() { chars.resize( 0 ); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** Xml write stream
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CWriteStream
{
	Stream *pStream;
	CStringComposer buffer;
	//
	void Dump()
	{
		if ( buffer.GetSize() > 1024 ) 
		{
			pStream->Write( buffer.str(), buffer.GetSize() );
			buffer.Clear();
		}
	}
	void DumpForced()
	{
		if ( !buffer.IsEmpty() ) 
		{
			pStream->Write( buffer.str(), buffer.GetSize() );
			buffer.Clear();
		}
	}
public:
	CWriteStream( Stream *_pStream )
		: pStream( _pStream ), buffer( 2048 ) {	}
	~CWriteStream() { DumpForced(); }
	//
	CWriteStream& operator<<( const string &szString )
	{
		buffer << szString;
		Dump();
		return *this;
	}
	CWriteStream& operator<<( const char *pszString )
	{
		buffer << pszString;
		Dump();
		return *this;
	}
	CWriteStream& operator<<( const char chr )
	{
		buffer << chr;
		Dump();
		return *this;
	}
	//
	void WriteChecked( const string &szString );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** helper functions
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline bool IsWhiteSpace( const char chr )
{
	return (chr == ' ') || ( chr == '\n' ) || ( chr =='\r' ) || ((chr >= 0x09) && (chr <= 0x0d));
}
inline const char* SkipWhiteSpace( const char *p )
{
	while ( (*p != 0) && IsWhiteSpace(*p) ) 
		++p;
	//
	return p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsEqualSubstring( const string &szString, const char *pszBegin, const char *pszEnd )
{
	if ( pszEnd - pszBegin < szString.length() ) 
		return false;
	//
	for ( string::const_iterator it = szString.begin(); it != szString.end(); ++it, ++pszBegin )
	{
		if ( *it != *pszBegin ) 
			return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsEqualSubstring( const string &szString, const char *p )
{
	for ( string::const_iterator it = szString.begin(); it != szString.end(); ++it, ++p )
	{
		if ( *it != *p ) 
			return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsEqualSubstringIC( const string &szString, const char *p )
{
	for ( string::const_iterator it = szString.begin(); it != szString.end(); ++it, ++p )
	{
		if ( *it != tolower(*p) ) 
			return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* GetEntity( const char *p, char *pValue );
const char* ReadName( const char *p, string *pszName );
const char* ReadText( string *pszText, const char *pszBegin, const char *pszEnd, 
														 const string &szEndTag, const bool bTrimWhiteSpace );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline const char* GetChar( const char *p, char *pValue )
{
	if ( *p == '&' )
		return GetEntity( p + 1, pValue );
	else
	{
		*pValue = *p;
		return p + 1;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif


