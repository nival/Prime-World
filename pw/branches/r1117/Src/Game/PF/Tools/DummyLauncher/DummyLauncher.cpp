#include "stdafx.h"
#include "application.h"
#include "UsersInfo.h"
#include "FbNetInfo.h"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

//  HMODULE richEditLib = LoadLibrary(L"msftedit.dll");
  HMODULE richEditLib = NULL;
  if(richEditLib == NULL)
    richEditLib = LoadLibrary(L"riched20.dll");
  if(richEditLib == NULL)
    richEditLib = LoadLibrary(L"riched32.dll");

  Application app(hInstance);
	app.Run();

  FreeLibrary(richEditLib);

	return 1;
}

