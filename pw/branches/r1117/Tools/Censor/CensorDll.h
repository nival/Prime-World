#ifndef CENSORDLL_H_994965EC_C76C_4ED9_8
#define CENSORDLL_H_994965EC_C76C_4ED9_8

//#define CENSORDLL_API 
#ifdef CENSORLIB_EXPORT
#define CENSORDLL_API __declspec(dllexport)
#else
#define CENSORDLL_API __declspec(dllimport)
#endif

#include <string>

#define FILTER_ERROR -1
namespace CensorFilter
{

extern "C"
{
  CENSORDLL_API void __cdecl Filter(wchar_t* text);
  CENSORDLL_API int __cdecl FilterAsync(const wchar_t* text);
  CENSORDLL_API int __cdecl GetFilteredAsync(int& messageId, wchar_t* text, size_t size);
  CENSORDLL_API int __cdecl LoadDictionary(const wchar_t* fileName, bool isWhiteList = false);
}
}
#endif //#define CENSORDLL_H_994965EC_C76C_4ED9_8