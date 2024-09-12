#include "DebugTraceDumper.h"
#include "LogHelpers.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NLogg
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDebugTraceDumper::OnDump( const CLogger *, const char *szFileName, const DWORD dwLine, const TTime , const ELevel eLevel, const char *szMessage )
{
#ifdef _DEBUG
	static char szBuffer[4096];
	if ( szFileName == 0 )
		sprintf_s( szBuffer, 4096, "%s: %s\n", MessageLevelToString( eLevel ), szMessage ); 
	else if ( dwLine == 0xFFFFFFFF )
		sprintf_s( szBuffer, 4096, "%s: %s: %s\n", szFileName, MessageLevelToString( eLevel ), szMessage ); 
	else
		sprintf_s( szBuffer, 4096, "%s(%d): %s: %s\n", szFileName, dwLine, MessageLevelToString( eLevel ), szMessage ); 
	
	OutputDebugString( szBuffer );
#else
	OutputDebugString( szMessage );
	OutputDebugString( "\n" );
#endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
