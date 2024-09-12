#ifndef USERMESSAGE_H_966BE042_7D59_435D
#define USERMESSAGE_H_966BE042_7D59_435D

#include <Windows.h>

namespace UserMessage
{
  void Init( HWND hWnd );
  void ShowMessageAndTerminate( DWORD dwExceptionCode, LPCSTR lpText );
  void ShowMessageAndTerminate(DWORD dwExceptionCode, LPCWSTR lpTitle, LPCWSTR lpText);
}

#endif //#define USERMESSAGE_H_966BE042_7D59_435D