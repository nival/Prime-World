#pragma once

#include "Logger.h"
#include "Locker.h"
#include "LogBuffer.h"
#include "StrFormatter.h"
#include <string>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NLogg
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLoggerStream : public CLogger
{
	CLogBuffer buffer;
	NStr::CStrFormatter formatter;
	CLocker locker;
	
	ELevel eDefaultLevel;
	ELevel eLevel;
	const char *szFileName;
	DWORD dwLine;
	
	void Reset()
	{
		szFileName = 0;
		dwLine = 0xFFFFFFFF;
		eLevel = eDefaultLevel;
	}
	
	CLoggerStream();
public:
	CLoggerStream( CLogger *pParent, const char *szName, const ELevel _eDefaultLevel ) :
		CLogger( pParent, szName ), eDefaultLevel( _eDefaultLevel ) { Reset(); }
	
	void Lock()
	{
		locker.Lock();
		szFileName = 0;
		dwLine = 0xFFFFFFFF;
		eLevel = eDefaultLevel;
	}
	
	void Lock( const ELevel _eLevel )
	{
		locker.Lock();
		szFileName = 0;
		dwLine = 0xFFFFFFFF;
		eLevel = _eLevel;
	}
	
	void Lock( const char *_szFileName, const DWORD _dwLine )
	{
		locker.Lock();
		szFileName = _szFileName;
		dwLine = _dwLine;
		eLevel = eDefaultLevel;
	}

	void Lock( const char *_szFileName, const DWORD _dwLine, const ELevel _eLevel )
	{
		locker.Lock();
		szFileName = _szFileName;
		dwLine = _dwLine;
		eLevel = _eLevel;
	}
	
	CLoggerStream &operator<<( CLoggerStream &(*pFunc)(CLoggerStream &) ) { return ((*pFunc)(*this)); }
	
	CLoggerStream &operator<<( const char *szString ) { buffer.Push( szString ); return *this; }
	CLoggerStream &operator<<( const std::string &szString ) { buffer.Push( szString.c_str() ); return *this; }
	CLoggerStream &operator<<( std::string &szString ) { buffer.Push( szString.c_str() ); return *this; }

	//CLoggerStream &operator<<( const wstring &wszString ) { buffer.Push( NStr::ToMBCS( wszString ).c_str() ); return *this; }
	//CLoggerStream &operator<<( wstring &wszString ) { buffer.Push( NStr::ToMBCS( wszString ).c_str() ); return *this; }

	CLoggerStream &operator<<( const bool bValue ) { buffer.Push( formatter.Format( bValue ) ); return *this; }

	CLoggerStream &operator<<( const char cValue ) { buffer.Push( formatter.Format( cValue ) ); return *this; }

	CLoggerStream &operator<<( const short nValue ) { buffer.Push( formatter.Format( nValue ) ); return *this; }
	CLoggerStream &operator<<( const unsigned short nValue ) { buffer.Push( formatter.Format( nValue ) ); return *this; }

	CLoggerStream &operator<<( const int nValue ) { buffer.Push( formatter.Format( (long)nValue ) ); return *this; }
	CLoggerStream &operator<<( const unsigned int nValue ) { buffer.Push( formatter.Format( (unsigned long)nValue ) ); return *this; }
	CLoggerStream &operator<<( const long nValue ) { buffer.Push( formatter.Format( nValue ) ); return *this; }
	CLoggerStream &operator<<( const unsigned long nValue ) { buffer.Push( formatter.Format( nValue ) ); return *this; }
	CLoggerStream &operator<<( const long long nValue ) { buffer.Push( formatter.Format( nValue ) ); return *this; }

	CLoggerStream &operator<<( const float fValue ) { buffer.Push( formatter.Format( fValue ) ); return *this; }
	CLoggerStream &operator<<( const double fValue ) { buffer.Push( formatter.Format( fValue ) ); return *this; }
	CLoggerStream &operator<<( const long double fValue ) { buffer.Push( formatter.Format( fValue ) ); return *this; }

	CLoggerStream &operator<<( const void *pValue ) { buffer.Push( formatter.Format( pValue ) ); return *this; }
	
	//template<class T>
	//CLoggerStream &operator<<( const T &obj ) { T::Log( *this, obj ); return *this; }

	void Dump()
	{
		Log( szFileName, dwLine, eLevel, buffer.GetBuffer() );
		buffer.Reset();
		Reset();
		locker.Unlock();
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline NLogg::CLoggerStream &endl( NLogg::CLoggerStream &logger )
{
	logger.Dump();
	return logger;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LOG( logger, level ) logger.Lock( __FILE__, __LINE__, level ); logger
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
