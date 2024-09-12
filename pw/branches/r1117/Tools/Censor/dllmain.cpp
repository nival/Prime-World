// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <Game/PF/Server/CensorshipCore/Censor.h>
#include <Game/PF/Server/CensorshipCore/CensorAsyncManager.h>
#include <sstream>
#include "CensorDll.h"
#include "resource.h"
#include <iostream>

namespace CensorFilter
{ 

typedef CensorFilter::CensorAsyncManager TAsyncCensor;
typedef CensorFilter::Censor TCensor;

TCensor* pCensor = 0;
TAsyncCensor* pAsyncCensor = 0;


extern "C"
{
  CENSORDLL_API void __cdecl Filter(wchar_t* text)
  {
    if (pCensor)
      pCensor->Filter(text);
  }

  CENSORDLL_API int __cdecl FilterAsync(const wchar_t* text)
  {
    if (pAsyncCensor)
      return pAsyncCensor->FilterMessageAsync(text);

    return FILTER_ERROR;
  }

  CENSORDLL_API int __cdecl GetFilteredAsync(int& messageId, wchar_t* text, size_t size)
  {
    if (pAsyncCensor)
      return pAsyncCensor->GetFilteredMessage(messageId, text, size);

    return FILTER_ERROR;
  }

  CENSORDLL_API int __cdecl LoadDictionary(const wchar_t* fileName, bool isWhiteList /*= false*/)
  {
    if (pCensor)
    {
      std::wstring msg = L"[Censor] load library ";
      msg += fileName;
      msg += L" ... ";
      OutputDebugString(msg.c_str());
      int res = pCensor->LoadDictionary(fileName, isWhiteList);
      if (res != 0)
        OutputDebugString(L"Failed!\n");
      else
        OutputDebugString(L"Successfully!\n");
      return res;
    }

    return FILTER_ERROR;
  }
};



BOOL WINAPI EnumNamesFunc(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG lParam)
{
  nstl::vector< nstl::wstring >* resources = (nstl::vector< nstl::wstring >*)lParam;
  TCHAR buffer[100];
  if ((ULONG)lpName & 0xFFFF0000) 
  { 
    wsprintf(buffer,L"%s\n", lpName); 
  } 
  else 
  { 
    wsprintf(buffer, L"%u\n",(USHORT)lpName); 
  } 
  resources->push_back(buffer);

  return true;
}
//////////////////////////////////////////////////////////////////////////
void Initialize(HMODULE hModule)
{
  nstl::vector< nstl::wstring > resources;
  pCensor = new TCensor();
  pAsyncCensor = new TAsyncCensor(pCensor);
 // NI_ASSERT( pCensor, "Censor must be created befor dictionary initialization" );
  EnumResourceNames(hModule,RT_RCDATA, (ENUMRESNAMEPROC)EnumNamesFunc, (LONG)&resources);

  for( nstl::vector<nstl::wstring>::iterator rcDict = resources.begin(); rcDict != resources.end(); ++rcDict )
  { 
    nstl::wstring resName = L"#" + *rcDict;
    HRSRC hres = FindResource(hModule, resName.c_str(), RT_RCDATA);
    if (hres == 0)
      continue; 

    DWORD size = SizeofResource(hModule, hres);
    HGLOBAL hbytes = LoadResource(hModule, hres);
    const wchar_t* pS = (const wchar_t*)LockResource(hbytes);
    std::wstring str(pS+1, size / sizeof(wchar_t) - sizeof(wchar_t));
    std::wstringstream data(str);
    UnlockResource(hbytes);
    
    
    int rcID = _wtoi(rcDict->c_str());
    pCensor->AddDictionary(data, rcID >= IDR_WHITELIST1);
  }
}

void Release()
{
  CensorFilter::pAsyncCensor->Stop();
  delete CensorFilter::pAsyncCensor;
  delete CensorFilter::pCensor;
}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
    CensorFilter::Initialize(hModule);
    OutputDebugStringA("[Censor]: Censor atached\n");
    break;
	case DLL_THREAD_ATTACH:
    break;
	case DLL_THREAD_DETACH:
    break;
	case DLL_PROCESS_DETACH:
    CensorFilter::Release();
    OutputDebugStringA("[Censor]: Censor detached\n");
		break;
	}
	return TRUE;
}

