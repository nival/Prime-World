#include "Logger.h"
#include "Dumper.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NLogg
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const static TTime g_timeStartTime = (TTime)GetTickCount();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CLogger::CLogger( CLogger *_pParent, const char *_szName ) : szName( _szName )
{

	for ( const CLogger *it = _pParent; it != 0; it = it->GetParent() )
	{
		if ( it == this )
			return;
	}
	pParent = _pParent;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool CLogger::IsDumperPresent( const CDumper *pDumper, const bool bRecursive ) const
{
	for ( TDumpers::const_iterator it = dumpers.begin(); it != dumpers.end(); ++it )
	{
		if ( *it == pDumper )
			return true;
	}
	
	if ( bRecursive && GetParent() != 0 )	
		return GetParent()->IsDumperPresent( pDumper, bRecursive );
	
	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogger::Log( const char *szFileName, const DWORD dwLine, const ELevel eLevel, const char *szMessage )
{
	Log( this, szFileName, dwLine, GetTickCount() - g_timeStartTime, eLevel, szMessage );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogger::Log( const CLogger *pLogger, const char *szFileName, const DWORD dwLine, const TTime time, const ELevel eLevel, const char *szMessage )
{
	CLockerAutoIncDec logAutoIncDec( logLocker );
	{ CLockerGuard cfgGuard( cfgLocker ); }

	for ( TDumpers::const_iterator it = dumpers.begin(); it != dumpers.end(); ++it )
		(*it)->Dump( pLogger, szFileName, dwLine, time, eLevel, szMessage );
	
	if ( GetParent() != 0 )
		GetParent()->Log( pLogger, szFileName, dwLine, time, eLevel, szMessage );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool CLogger::AddDumper( CDumper *pDumper )
{
	CLockerAutoIncDec cfgAutoIncDec( cfgLocker );
	{ CLockerGuard logGuard( logLocker ); }

	if ( IsDumperPresent( pDumper, true ) )
		return false;
	
	dumpers.push_back( pDumper );
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool CLogger::RemoveDumper( CDumper *pDumper )
{
	CLockerAutoIncDec cfgAutoIncDec( cfgLocker );
	{ CLockerGuard logGuard( logLocker ); }

	TDumpers::iterator it = dumpers.begin();
	while ( it != dumpers.end() && *it != pDumper )
		++it;
		
	if ( it == dumpers.end() )
		return false;

	dumpers.erase( it );
	return true;		
}	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}