#include "stdafx.h"
#include "UserMessage.h"

namespace UserMessage
{
static HWND g_hWnd = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Init( HWND hWnd )
{
  g_hWnd = hWnd;  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ShowMessageAndTerminate( DWORD dwExceptionCode, LPCSTR lpText )
{
  if( g_hWnd != 0 )
    ShowWindow(g_hWnd, SW_MINIMIZE);

  MessageBox( 
    NULL, lpText,
    "Prime World: The application will be terminated now.", 
    MB_ICONERROR | MB_SYSTEMMODAL | MB_SETFOREGROUND
  );

  RaiseException( dwExceptionCode, EXCEPTION_NONCONTINUABLE, 0, 0 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ShowMessageAndTerminate(DWORD dwExceptionCode, LPCWSTR lpTitle, LPCWSTR lpText)
{
  if( g_hWnd != 0 )
    ShowWindow(g_hWnd, SW_MINIMIZE);

  MessageBoxW(NULL, lpText, lpTitle, MB_ICONERROR | MB_SYSTEMMODAL | MB_SETFOREGROUND);

  RaiseException( dwExceptionCode, EXCEPTION_NONCONTINUABLE, 0, 0 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}