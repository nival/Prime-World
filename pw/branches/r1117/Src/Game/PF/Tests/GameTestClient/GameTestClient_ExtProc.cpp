#include "GameTestClient_ExtProc.h"
#include "System/fileSystem/FilePath.h"

namespace gtc
{

Client_ExtProc::Client_ExtProc( const char * _appPath, const char * _sessionKey ) :
state( StInit )
{
  ZeroMemory( &procInfo, sizeof( procInfo ) );

  string path = NFile::GetFilePath( _appPath );

  string cmdln = string("\"") + _appPath + "\" -session_login " + _sessionKey;

  STARTUPINFO si;
  ZeroMemory( &si, sizeof( si ) );
  si.cb = sizeof( si );

  char cmdlnBuf[MAX_PATH] = "";
  strncpy( cmdlnBuf, cmdln.c_str(), MAX_PATH - 1 );

  if ( CreateProcess( NULL, cmdlnBuf, NULL, NULL, FALSE, 0, NULL, path.c_str(), &si, &procInfo ) )
    if ( procInfo.hProcess )
    {
      state = StRunning;
      MessageTrace( "Successfully launched process '%s', pid=%d", cmdlnBuf, procInfo.dwProcessId );
      return;
    }

  DWORD le = GetLastError();
  state = StFailed;
  ErrorTrace( "Failed to launch process '%s', code=%d, msg='%s'", cmdlnBuf, le, FormatWindowError( le ).c_str() );
}



Client_ExtProc::~Client_ExtProc()
{
  Close();
}



void Client_ExtProc::Close()
{
  if ( procInfo.hThread )
    CloseHandle( procInfo.hThread );
  procInfo.hThread = NULL;

  if ( procInfo.hProcess )
    CloseHandle( procInfo.hProcess );
  procInfo.hProcess = NULL;
}



StepResult Client_ExtProc::MainStep()
{
  if ( state == StRunning )
    if ( procInfo.hProcess )
      if ( WaitForSingleObject( procInfo.hProcess, 0 ) != WAIT_TIMEOUT ) {
        state = StStopped;
        Close();
      }

  return StepResult( true, state == StRunning );
}



void Client_ExtProc::TerminatePvx()
{
  if ( procInfo.hProcess ) {
    TerminateProcess( procInfo.hProcess, 0 );
    Close();

    state = StStopped;
  }
}


string Client_ExtProc::FormatWindowError( DWORD err )
{
  LPTSTR lpMsgBuffer = NULL;
  DWORD dwRet = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
			     err, 0, (LPTSTR)&lpMsgBuffer, 0, NULL);

  if ( !dwRet )
    return string();

  string msg( lpMsgBuffer );
  ::LocalFree(lpMsgBuffer);
  return msg;
}

} //namespace gtc
