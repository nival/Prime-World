#pragma once
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NStr
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CStrFormatter
{
	enum { FORMATTER_LENGTH = 32 };
	char szBuffer[FORMATTER_LENGTH];

	bool bBoolAlpha;
	bool bHexChar;
	bool bHexInteger;
	bool bSciFloat;
public:
	CStrFormatter() : bBoolAlpha( true ), bHexChar( false ), bHexInteger( false ), bSciFloat( false ) {}

	const char *Format( const bool bValue );

	const char *Format( const char cValue );
	
	const char *Format( const short nValue );
	const char *Format( const unsigned short nValue );
	
	const char *Format( const long nValue );
	const char *Format( const unsigned long nValue );
	const char *Format( const long long nValue );
	
	const char *Format( const float fValue );
	const char *Format( const double fValue );
	const char *Format( const long double fValue );
	
	const char *Format( const void *pValue );
	
	const char *GetBuffer() const { return szBuffer; }

	void SetBoolAlpha( const bool _bBoolAlpha ) { bBoolAlpha = _bBoolAlpha; }
	void SetHexChar( const bool _bHexChar ) { bHexChar = _bHexChar; }
	void SetHexInteger( const bool _bHexInteger ) { bHexInteger = _bHexInteger; }
	void SetSciFloat( const bool _bSciFloat ) { bSciFloat = _bSciFloat; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}