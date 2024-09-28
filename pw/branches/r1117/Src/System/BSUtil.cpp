#include "StdAfx.h"
#include "StackWalk.h"
#include "../MemoryLib/SymAccess.h"
#include "BSUtil.h"
#include "BSDialogFunctions.h"
#include "MiniDump.h"
#include <commctrl.h>
#include "LogFileName.h"
#include "FileSystem/FileUtils.h"
#include "TimeUtils.h"

#pragma comment( lib, "comctl32.lib" )
////////////////////////////////////////////////////////////////////////////////////////////////////
static NBSU::TIgnoresList ignores;
static HINSTANCE g_hBSUInstance = NULL;
static HWND g_hBSUWindow = NULL;
static bool g_ignoreAllAsserts = false;
static NBSU::ExceptionCallback    s_exceptionCall = NULL;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
	bool ignoreExceptions = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static LONG __stdcall ExceptionFilter( struct _EXCEPTION_POINTERS* ExceptionInfo );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CExceptionHandlerGuard
{
  bool bFilterSet;
  LPTOP_LEVEL_EXCEPTION_FILTER pOrigFilter;

  DUMMY_ASSIGNMENT( CExceptionHandlerGuard );
public:
  CExceptionHandlerGuard() : bFilterSet( false ), pOrigFilter( 0 ) {}
  ~CExceptionHandlerGuard()
  {
      if ( bFilterSet )
          SetUnhandledExceptionFilter( pOrigFilter );

      bFilterSet = false;
      pOrigFilter = 0;
  }

  void SetExceptionHandler()
  {
      NI_VERIFY( !bFilterSet, "Unhandled exception filter already setted", return );
      pOrigFilter = SetUnhandledExceptionFilter( ExceptionFilter );
      bFilterSet = true;
  }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static CExceptionHandlerGuard exceptionHandlerGuard;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef DO_NOT_USE_DLLMAIN
BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID )
{
  BOOL bRet = TRUE ;
  switch ( dwReason )
  {
  case DLL_PROCESS_ATTACH:
      // Save off the DLL hInstance.
      g_hBSUInstance = hInstance;
      InitCommonControls();
      // I don't need the thread notifications.
      DisableThreadLibraryCalls( g_hBSUInstance ) ;
      break ;
  case DLL_PROCESS_DETACH:
      break ;
  default:
      break ;
  }
  return ( bRet ) ;
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void WriteEntriesToLogFile( HANDLE logFile, const vector<SCallStackEntry>& entries )
{
  static char buffer[512];
  int bytesToWrite = 0;
  DWORD bytesWritten = 0;

  for ( int i = 0; i < entries.size(); ++i )
  {
    const SCallStackEntry &e = entries[i];
    const char* rightSlash = e.szFile.szStr;
    const char* rightSlash1 = strrchr( e.szFile.szStr, '\\' );
    const char* rightSlash2 = strrchr( e.szFile.szStr, '/' );
    if ( rightSlash1 != 0 && ( rightSlash1 > rightSlash2 || rightSlash2 == 0 ) )
      rightSlash = rightSlash1 + 1;
    else if ( rightSlash2 != 0 && ( rightSlash2 > rightSlash1 || rightSlash1 == 0 ) )
      rightSlash = rightSlash2 + 1;

    if ( strlen( rightSlash ) == 0 )
    {
      if ( strlen( e.szFunc.szStr ) == 0 )
        bytesToWrite = sprintf_s( buffer, "0x%08X\r\n", e.dwAddress );
      else
        bytesToWrite = sprintf_s( buffer, "%s (0x%08X)\r\n", e.szFunc.szStr, e.dwAddress );
    }
    else
    {
      if ( strlen( e.szFunc.szStr ) == 0 )
        bytesToWrite = sprintf_s( buffer, "%s(%d): 0x%08X\r\n", rightSlash, e.nLine, e.dwAddress );
      else
        bytesToWrite = sprintf_s( buffer, "%s(%d): %s (0x%08X)\r\n", rightSlash, e.nLine, e.szFunc.szStr, e.dwAddress );
    }
    WriteFile( logFile, buffer, bytesToWrite, &bytesWritten, 0 );
  }
}

void  NBSU::SetExceptionCallback(NBSU::ExceptionCallback callb)
{
  s_exceptionCall = callb;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static LONG __stdcall ExceptionFilter( struct _EXCEPTION_POINTERS* ExceptionInfo )
{
  if (s_exceptionCall != NULL)
		(*s_exceptionCall)();

  struct tm tim;
  GetOsUtcTime(&tim);

  CreateMiniDump( tim, ExceptionInfo, MINI_DUMP, EXCEPTION_SEH );

  vector<SCallStackEntry> entries;
  CollectCallStack( &entries, ExceptionInfo );

  NBSU::WriteExceptionLogFile( tim, ExceptionInfo, entries, 0 );
  
  NBSU::EBSUReport eBSUResult = NBSU::BSU_DEFAULT;
  if ( !ignoreExceptions )
    eBSUResult = NBSU::ShowExceptionDlg( entries, ExceptionInfo );
  else
    eBSUResult = NBSU::BSU_ABORT;

  switch ( eBSUResult )
  {
  case NBSU::BSU_DEBUG:
    if ( IsDebuggerPresent() )
      __debugbreak();
    return EXCEPTION_CONTINUE_SEARCH;
  case NBSU::BSU_ABORT:
    FatalExit( 0xDEAD );
    return EXCEPTION_CONTINUE_SEARCH;
  case NBSU::BSU_MAKE_FULL_MINIDUMP:
    CreateMiniDump( tim, ExceptionInfo, FULL_DUMP, EXCEPTION_SEH );
    FatalExit( 0xDEAD );
    return EXCEPTION_EXECUTE_HANDLER;
  default:
    return EXCEPTION_CONTINUE_SEARCH;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NBSU
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsIgnore( const char *pszFileName, int nLineNumber )
{
  if ( g_ignoreAllAsserts )
    return true;

  for ( TIgnoresList::const_iterator it = ignores.begin(); it != ignores.end(); ++it )
  {
		if ( it->szFileName == pszFileName && it->nLineNumber == nLineNumber )
			return true;
  }

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddIgnore( const char *pszFunctionName, const char *pszFileName, int nLineNumber )
{
  if ( !IsIgnore( pszFileName, nLineNumber ) )
    ignores.push_back( SIgnoresEntry( pszFunctionName, pszFileName, nLineNumber ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RemoveIgnore( const char *pszFileName, int nLineNumber )
{
  for ( TIgnoresList::iterator it = ignores.begin(); it != ignores.end(); ++it )
  {
    if ( it->szFileName == pszFileName && it->nLineNumber == nLineNumber )
    {
      ignores.erase( it );
      return;
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const TIgnoresList &GetIgnoresList()
{
  return ignores;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HINSTANCE GetBSUInstance()
{
  return g_hBSUInstance;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetBSUWindow( HWND hWindow )
{
  g_hBSUWindow = hWindow;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HWND GetBSUWindow()
{
  return g_hBSUWindow;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitUnhandledExceptionHandler()
{
  exceptionHandlerGuard.SetExceptionHandler();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WriteAssertLogFile( const struct tm& tim, const char *message, const vector<SCallStackEntry>& entries, bool dataAssert )
{
	HANDLE logFile = (HANDLE)NFile::CreateFileWithDir( NDebug::GenerateDebugFileName( tim, dataAssert ? "data" : "assert", "log" ).c_str() );
  if ( logFile == INVALID_HANDLE_VALUE )
    return;

  static char buffer[512];
  int bytesToWrite = 0;
  DWORD bytesWritten = 0;

  bytesToWrite = strlen( message );
  WriteFile( logFile, message, bytesToWrite, &bytesWritten, 0 );
  bytesToWrite = sprintf_s( buffer, "\r\n\r\n" ); 
  WriteFile( logFile, buffer, bytesToWrite, &bytesWritten, 0 );

  WriteEntriesToLogFile( logFile, entries );
  CloseHandle( logFile );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WriteExceptionLogFile( const struct tm& tim, const EXCEPTION_POINTERS* pExceptionInfo, const vector<SCallStackEntry>& entries, string * pFileName )
{
  string fileName = NDebug::GenerateDebugFileName( tim, "exception", "log" );
  HANDLE logFile = (HANDLE)NFile::CreateFileWithDir( fileName.c_str() );
  if ( logFile == INVALID_HANDLE_VALUE )
    return;

  static char buffer[512];
  int bytesToWrite = 0;
  DWORD bytesWritten = 0;
  const DWORD nBufferSize = 511 * sizeof(char);

  bytesToWrite = sprintf_s( buffer, nBufferSize, "%s\r\n%s\r\n", NBSU::ExceptionCodeToString( pExceptionInfo->ExceptionRecord->ExceptionCode ), NBSU::RegistersToString( pExceptionInfo ) ); 
  WriteFile( logFile, buffer, bytesToWrite, &bytesWritten, 0 );

  bytesToWrite = sprintf_s( buffer, nBufferSize, "%s\r\n", "Code Bytes:"); 
  char *pEoS = buffer + strlen(buffer);
  for(int i = 0; i < 50; i++)
  {
    int nCurrIdx = pEoS - buffer;
    if(IsBadCodePtr((FARPROC)((BYTE *)pExceptionInfo->ExceptionRecord->ExceptionAddress + i)) != 0)
    {
      sprintf_s(buffer + nCurrIdx, nBufferSize - nCurrIdx, " Unknown. ");
      break;
    }
    bytesToWrite = sprintf_s(buffer + nCurrIdx, nBufferSize - nCurrIdx, "%02X ",  (int)*((BYTE *)pExceptionInfo->ExceptionRecord->ExceptionAddress + i));
    pEoS += bytesToWrite;
  }
  int nCurrIdx = pEoS - buffer;
  bytesToWrite = sprintf_s(buffer + nCurrIdx, nBufferSize - nCurrIdx, "\r\n");
  pEoS += bytesToWrite;
  WriteFile( logFile, buffer, (pEoS - buffer) * sizeof(char), &bytesWritten, 0 );

  WriteEntriesToLogFile( logFile, entries );
  CloseHandle( logFile );

  if ( pFileName )
    *pFileName = fileName;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetIgnoreAll( bool ignoreAll )
{
  g_ignoreAllAsserts = ignoreAll;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
REGISTER_DEV_VAR( "ignoreExceptions", ignoreExceptions, STORAGE_NONE );

