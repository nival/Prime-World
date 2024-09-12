#pragma once

#include "Locker.h"
#include <list>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum ELevel
{
	LEVEL_UNDEFINED,
	LEVEL_MESSAGE,
	LEVEL_DEBUG,
	LEVEL_ASSERT,
	LEVEL_CRITICAL,
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NLogg
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CDumper;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef DWORD TTime;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLogger
{
	typedef std::list<CDumper*> TDumpers;
	CLogger *pParent;
	const char *szName;
	TDumpers dumpers;

	CLocker logLocker;
	CLocker cfgLocker;
	
	CLogger() : pParent( 0 ), szName( 0 ) {}
	
	CLogger *GetParent() { return pParent; }
	void Log( const CLogger *pLogger, const char *szFileName, const DWORD dwLine, const TTime time, const ELevel eLevel, const char *szMessage );
	const bool IsDumperPresent( const CDumper *pDumper, const bool bRecursive ) const;
public:
	CLogger( CLogger *pParent, const char *szName );
	
	void Log( const char *szFileName, const DWORD dwLine, const ELevel eLevel, const char *szMessage );
	
	//returns false if dumper already linked to this logger or its parents
	const bool AddDumper( CDumper *pDumper );
	//returns false if dumper not linked to this logger
	const bool RemoveDumper( CDumper *pDumper );
	
	const CLogger *GetParent() const { return pParent; } 
	const char *GetName() const { return szName; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}