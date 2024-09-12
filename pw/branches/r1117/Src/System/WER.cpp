#include "stdafx.h"
#include "WER.h"
#include "MainFrame.h"
#include <werapi.h>

#if 0

#pragma comment( lib, "wer" )

namespace WER
{

//TEMP
static const char * FormatLastLastErrorMessage( DWORD errorCode )
{
  static char buffer[512] = "";
  if ( FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, 0, errorCode, 0, buffer, 512, 0 ) )
    return buffer;
  else
    return "Eror message not found";
}


bool CreateReport()
{
  HREPORT h = 0;

  WER_REPORT_INFORMATION info;
  ZeroMemory( &info, sizeof( info ) );
  info.dwSize = sizeof( info );
  info.hProcess = NULL;
  wcscpy_s( info.wzFriendlyEventName, L"Test event to report" );
  wcscpy_s( info.wzApplicationName, L"Prime World" );
  wcscpy_s( info.wzApplicationPath, L"C:\\_work\\PF.trunk\\Bin\\PF_Game.exe" );
  wcscpy_s( info.wzDescription, L"Test description" );
  info.hwndParent = NMainFrame::GetWnd();

  HRESULT res = WerReportCreate( L"Wooa", WerReportCritical, &info, &h );
  if ( FAILED( res ) )
  {
    DebugTrace( "WER error: %s", FormatLastLastErrorMessage( res ) );
    return false;
  }

  WER_SUBMIT_RESULT result = (WER_SUBMIT_RESULT)0;
  if ( FAILED( WerReportSubmit( h, WerConsentNotAsked, 0, &result ) ) )
  {
    WerReportCloseHandle( h );
    return false;
  }

  WerReportCloseHandle( h );
  return true;
}

} //namespace WER

#else

namespace WER
{
bool CreateReport() { return true; }
} //namespace WER

#endif
