#include "stdafx.h"
#include "IniFiles.h"
#include "FileSystem/FilePath.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
int inline FindAndReplace(T& source, const T& find, const T& replace)
{
    int num = 0;
    size_t fLen = find.size();
    size_t rLen = replace.size();
    for (size_t pos = 0; (pos = source.find(find, pos)) != T::npos; pos += rLen)
    {
        num++;
        source.replace(pos, fLen, replace);
    }
    return num;
}

} // namespace


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NIniFiles
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetINIString(string * dest, LPCTSTR pszDir, LPCTSTR pszFile, LPCTSTR pszSection, LPCTSTR pszName)
{
  if (dest && pszFile && pszSection && pszName)
  {
    TCHAR szBuffer[1024] = "";
    string fileName = pszDir ? pszDir : "";
    if (fileName.empty())
    {
      fileName += NFile::GetBinDir();
    }
    fileName = fileName + pszFile;
    GetPrivateProfileString( pszSection, pszName, "", szBuffer, 1024, fileName.c_str());
    *dest = szBuffer;
    FindAndReplace( *dest, string("\\n"), string("\n") );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetINIString(wstring * dest, LPCWSTR pszDir, LPCWSTR pszFile, LPCWSTR pszSection, LPCWSTR pszName)
{
  if (dest && pszSection && pszName)
  {
    WCHAR szBuffer[1024] = L"";
    wstring fileName = pszDir ? pszDir : L"";
    if (fileName.empty())
    {
      NStr::ToUnicode( &fileName, NFile::GetBinDir());
    }
    fileName += pszFile;
    GetPrivateProfileStringW( pszSection, pszName, L"", szBuffer, 1024, fileName.c_str());
    *dest = szBuffer;
    FindAndReplace( *dest, wstring(L"\\n"), wstring(L"\n") );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string GetINIString(LPCTSTR pszDir, LPCTSTR pszFile, LPCTSTR pszSection, LPCTSTR pszName)
{
  string sResult;
  GetINIString(&sResult, pszDir, pszFile, pszSection, pszName);
  return sResult;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wstring GetINIString(LPCWSTR pszDir, LPCWSTR pszFile, LPCWSTR pszSection, LPCWSTR pszName)
{
  wstring sResult;
  GetINIString(&sResult, pszDir, pszFile, pszSection, pszName);
  return sResult;
}

} // namespace NIniFiles
