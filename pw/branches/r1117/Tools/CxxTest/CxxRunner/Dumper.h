#pragma once

#include "Logger.h"
#include "Locker.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NLogg
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CDumper
{
	const char *szName;
	DWORD dwLevelFilter;
	CLocker locker;
	
	CDumper() : dwLevelFilter( 0xFFFFFFFF ), szName( 0 ) {}
protected:
	virtual void OnDump( const CLogger *pLogger, const char *szFileName, const DWORD dwLine, const TTime time, const ELevel eLevel, const char *szMessage ) = 0;
public:
	CDumper( CLogger *pDefaultLogger, const char *szName );

	//by default dumper dump all messages, but first call of AddLevel( ... ) removes all levels except specified
	void AddLevel( const ELevel eLevel );
	void RemoveLevel( const ELevel eLevel );

	void Dump( const CLogger *pLogger, const char *szFileName, const DWORD dwLine, const TTime time, const ELevel eLevel, const char *szMessage );
	
	const char *GetName() const { return szName; } 
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
