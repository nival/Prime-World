#include "stdafx.h"
#include "MiniDump.h"

#include "LogFileName.h"
#include "FileSystem/FileUtils.h"
#include "Vendor/DTW/inc/dbghelp.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const MINIDUMP_TYPE miniMiniDumpFlags = (MINIDUMP_TYPE)( MiniDumpWithIndirectlyReferencedMemory );
static const MINIDUMP_TYPE fullMiniDumpFlags = (MINIDUMP_TYPE)( MiniDumpWithDataSegs | MiniDumpWithThreadInfo |
																															 MiniDumpWithFullMemoryInfo | MiniDumpWithProcessThreadData |
																															 MiniDumpWithHandleData | MiniDumpWithPrivateReadWriteMemory );
static MINIDUMP_EXCEPTION_INFORMATION dumpExceptionInfo;

DEV_VAR_STATIC bool g_fullDump = false;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateMiniDump( const struct tm &tim, EXCEPTION_POINTERS* ExceptionInfo, MiniDumpType dumpFlags, ExceptionType exceptionType )
{
	static char desc[64];
  
  if ( g_fullDump )
    dumpFlags = FULL_DUMP;

	sprintf_s( desc, "%s%s", exceptionType == EXCEPTION_ASSERT ? "assert" : "exception", dumpFlags == MINI_DUMP ? "" : "-full" );

	static int dumpFileHandle;
	dumpFileHandle = NFile::CreateFileWithDir( NDebug::GenerateDebugFileName( tim, desc, "dmp" ).c_str() );
	//dumpFileHandle = CreateFile( NDebug::GenerateDebugFileName( time, desc, "dmp" ).c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );

	if( dumpFileHandle != (int)INVALID_HANDLE_VALUE ) //just to avoid any exception
	{
		dumpExceptionInfo.ThreadId = GetCurrentThreadId();
		dumpExceptionInfo.ExceptionPointers	= ExceptionInfo;
		dumpExceptionInfo.ClientPointers	= true;

		MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), (HANDLE)dumpFileHandle
			, dumpFlags == MINI_DUMP ? miniMiniDumpFlags : fullMiniDumpFlags
			,	&dumpExceptionInfo, NULL, NULL );
		CloseHandle( (HANDLE)dumpFileHandle );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DEV_VAR( "full_dump", g_fullDump, STORAGE_NONE );