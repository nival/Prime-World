/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: Utility.cpp
// Description: Miscellaneous helper functions
// Authors: mikecarruth, zexspectrum
// Date: 

#include "stdafx.h"
#include "Utility.h"
#include "resource.h"
#include "strconv.h"
#include <TlHelp32.h>
#include <intrin.h>

CString Utility::getAppName()
{
    TCHAR szFileName[_MAX_PATH];
    GetModuleFileName(NULL, szFileName, _MAX_FNAME);

    CString sAppName; // Extract from last '\' to '.'
    sAppName = szFileName;
    sAppName = sAppName.Mid(sAppName.ReverseFind(_T('\\')) + 1)
        .SpanExcluding(_T("."));

    return sAppName;
}

CString Utility::GetModuleName(HMODULE hModule)
{
    CString string;
    LPTSTR buf = string.GetBuffer(_MAX_PATH);
    GetModuleFileName(hModule, buf, _MAX_PATH);
    string.ReleaseBuffer();
    return string;
}

CString Utility::GetModulePath(HMODULE hModule)
{
    CString string;
    LPTSTR buf = string.GetBuffer(_MAX_PATH);
    GetModuleFileName(hModule, buf, _MAX_PATH);
    TCHAR* ptr = _tcsrchr(buf,'\\');
    if(ptr!=NULL)
        *(ptr)=0; // remove executable name
    string.ReleaseBuffer();
    return string;
}

template <typename T>
void ZeroStructure( T & struc, DWORD * sizefield )
{
  memset( &struc, 0, sizeof( T ) );
  *sizefield = sizeof( T );
}

bool Utility::EnumModules( IModuleEnumCallback * callback )
{
  HANDLE hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, 0 );
  if ( !hSnapshot )
    return false;

  MODULEENTRY32 module;
  ZeroStructure( module, &module.dwSize );
  if ( !Module32First( hSnapshot, &module ) )
  {
    CloseHandle( hSnapshot );
    return false;
  }

  do
  {
    if ( !callback->EnumModule( module.hModule, module.szModule, module.szExePath, module.modBaseAddr, module.modBaseAddr + module.modBaseSize ) )
      break;

    ZeroStructure( module, &module.dwSize );
  }
  while ( Module32Next( hSnapshot, &module ) );

  CloseHandle( hSnapshot );
  return true;
}

bool Utility::EnumerateProcs( IProcsEnumCallback* callback )
{
  if ( !callback )
    return false;

  HANDLE pSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

  BOOL bIsok = FALSE;
  PROCESSENTRY32 ProcEntry;
  ProcEntry.dwSize = sizeof(ProcEntry);
  bIsok = Process32First(pSnap, &ProcEntry);	
  while(bIsok)
  {
    callback->EnumModule( ProcEntry.szExeFile, ProcEntry.th32ProcessID );
    bIsok = Process32Next(pSnap, &ProcEntry);
  }
  CloseHandle(pSnap);
  return true;
}

int Utility::getTempDirectory(CString& strTemp)
{
    TCHAR* pszTempVar = NULL;

#if _MSC_VER<1400
    pszTempVar = _tgetenv(_T("TEMP"));
    strTemp = CString(pszTempVar);
#else
    size_t len = 0;
    errno_t err = _tdupenv_s(&pszTempVar, &len, _T("TEMP"));
    if(err!=0)
    {
        // Couldn't get environment variable TEMP    
        return 1;
    }
    strTemp = CString(pszTempVar);
    free(pszTempVar);
#endif    

    return 0;
}

CString Utility::getTempFileName()
{
    TCHAR szTempDir[MAX_PATH - 14]   = _T("");
    TCHAR szTempFile[MAX_PATH]       = _T("");

    if (GetTempPath(MAX_PATH - 14, szTempDir))
        GetTempFileName(szTempDir, getAppName(), 0, szTempFile);

    return szTempFile;
}

int Utility::GetSystemTimeUTC(CString& sTime)
{
    sTime.Empty();

    // Get system time in UTC format

    time_t cur_time;
    time(&cur_time);
    char szDateTime[64];

#if _MSC_VER<1400
    struct tm* timeinfo = gmtime(&cur_time);
    strftime(szDateTime, 64,  "%Y-%m-%dT%H:%M:%SZ", timeinfo);
#else
    struct tm timeinfo;
    gmtime_s(&timeinfo, &cur_time);
    strftime(szDateTime, 64,  "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
#endif

    sTime = szDateTime;

    return 0;
}

void Utility::UTC2SystemTime(CString sUTC, SYSTEMTIME& st)
{
    CString sYear = sUTC.Mid(0, 4);
    CString sMonth = sUTC.Mid(5, 2);
    CString sDay = sUTC.Mid(8, 2);
    CString sHour = sUTC.Mid(11, 2);
    CString sMin = sUTC.Mid(14, 2);
    CString sSec = sUTC.Mid(17, 2);

    SYSTEMTIME UtcTime;
    memset(&UtcTime, 0, sizeof(SYSTEMTIME));
    UtcTime.wYear = (WORD)_ttoi(sYear);
    UtcTime.wMonth = (WORD)_ttoi(sMonth);
    UtcTime.wDay = (WORD)_ttoi(sDay);
    UtcTime.wHour = (WORD)_ttoi(sHour);
    UtcTime.wMinute = (WORD)_ttoi(sMin);
    UtcTime.wSecond = (WORD)_ttoi(sSec);

    // Convert to local time
    SystemTimeToTzSpecificLocalTime(NULL, &UtcTime, &st);
}

int Utility::GenerateGUID(CString& sGUID)
{
    int status = 1;
    sGUID.Empty();

    strconv_t strconv;

    // Create GUID

    UCHAR *pszUuid = 0; 
    GUID *pguid = NULL;
    pguid = new GUID;
    if(pguid!=NULL)
    {
        HRESULT hr = CoCreateGuid(pguid);
        if(SUCCEEDED(hr))
        {
            // Convert the GUID to a string
            hr = UuidToStringA(pguid, &pszUuid);
            if(SUCCEEDED(hr) && pszUuid!=NULL)
            { 
                status = 0;
                sGUID = strconv.a2t((char*)pszUuid);
                RpcStringFreeA(&pszUuid);
            }
        }
        delete pguid; 
    }

    return status;
}

int Utility::GetOSFriendlyName(CString& sOSName)
{
    sOSName.Empty();
    CRegKey regKey;
    LONG lResult = regKey.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"), KEY_READ);
    if(lResult==ERROR_SUCCESS)
    {    
        TCHAR buf[1024];
        ULONG buf_size = 0;

        TCHAR* PRODUCT_NAME = _T("ProductName");
        TCHAR* CURRENT_BUILD_NUMBER = _T("CurrentBuildNumber");
        TCHAR* CSD_VERSION = _T("CSDVersion");

#pragma warning(disable:4996)

        buf_size = 1023;
        if(ERROR_SUCCESS == regKey.QueryValue(buf, PRODUCT_NAME, &buf_size))
        {
            sOSName += buf;
        }

        buf_size = 1023;
        if(ERROR_SUCCESS == regKey.QueryValue(buf, CURRENT_BUILD_NUMBER, &buf_size))
        {
            sOSName += _T(" Build ");
            sOSName += buf;
        }

        buf_size = 1023;
        if(ERROR_SUCCESS == regKey.QueryValue(buf, CSD_VERSION, &buf_size))
        {
            sOSName += _T(" ");
            sOSName += buf;
        }

#pragma warning(default:4996)

        regKey.Close();    
        return 0;
    }

    return 1;
}

BOOL Utility::IsOS64Bit()
{
    BOOL b64Bit = FALSE;

#ifdef _WIN64
    // 64-bit applications always run under 64-bit Windows
    return TRUE;
#endif

    // Check for 32-bit applications

    typedef BOOL (WINAPI *PFNISWOW64PROCESS)(HANDLE, PBOOL);

    HMODULE hKernel32 = LoadLibrary(_T("kernel32.dll"));
    if(hKernel32!=NULL)
    {
        PFNISWOW64PROCESS pfnIsWow64Process = 
            (PFNISWOW64PROCESS)GetProcAddress(hKernel32, "IsWow64Process");
        if(pfnIsWow64Process==NULL)
        {
            // If there is no IsWow64Process() API, than Windows is 32-bit for sure
            FreeLibrary(hKernel32);
            return FALSE;
        }

        pfnIsWow64Process(GetCurrentProcess(), &b64Bit);
        FreeLibrary(hKernel32);
    }

    return b64Bit;
}

int Utility::GetGeoLocation(CString& sGeoLocation)
{
    sGeoLocation = _T("");

    typedef GEOID (WINAPI *PFNGETUSERGEOID)(GEOCLASS);
    typedef int (WINAPI *PFNGETGEOINFOW)(GEOID, GEOTYPE, LPWSTR, int, LANGID);

    HMODULE hKernel32 = LoadLibrary(_T("kernel32.dll"));
    if(hKernel32!=NULL)
    {
        PFNGETUSERGEOID pfnGetUserGeoID = 
            (PFNGETUSERGEOID)GetProcAddress(hKernel32, "GetUserGeoID");
        PFNGETGEOINFOW pfnGetGeoInfoW = 
            (PFNGETGEOINFOW)GetProcAddress(hKernel32, "GetGeoInfoW");
        if(pfnGetUserGeoID==NULL || 
            pfnGetGeoInfoW==NULL)
            return -1;

        GEOID GeoLocation = pfnGetUserGeoID(GEOCLASS_NATION);
        if(GeoLocation!=GEOID_NOT_AVAILABLE)
        { 
            WCHAR szGeoInfo[1024] = _T("");    
            int n = pfnGetGeoInfoW(GeoLocation, GEO_RFC1766, szGeoInfo, 1024, 0);
            if(n!=0)
            {
                sGeoLocation = szGeoInfo;
                FreeLibrary(hKernel32);
                return 0;
            }
        }

        FreeLibrary(hKernel32);    
    }

    return -1;
}

int Utility::GetSpecialFolder(int csidl, CString& sFolderPath)
{
    sFolderPath.Empty();

    TCHAR szPath[_MAX_PATH];
    BOOL bResult = SHGetSpecialFolderPath(NULL, szPath, csidl, TRUE);
    if(!bResult)
        return 1;

    sFolderPath = CString(szPath);

    return 0;
}

CString Utility::ReplaceInvalidCharsInFileName(CString sFileName)
{
    sFileName.Replace(_T("*"),_T("_"));
    sFileName.Replace(_T("|"),_T("_"));
    sFileName.Replace(_T("/"),_T("_"));
    sFileName.Replace(_T("?"),_T("_"));
    sFileName.Replace(_T("<"),_T("_"));
    sFileName.Replace(_T(">"),_T("_"));
    return sFileName;
}

int Utility::RecycleFile(CString sFilePath, bool bPermanentDelete)
{
    SHFILEOPSTRUCT fop;
    memset(&fop, 0, sizeof(SHFILEOPSTRUCT));

    TCHAR szFrom[_MAX_PATH];  
    memset(szFrom, 0, sizeof(TCHAR)*(_MAX_PATH));
    _TCSCPY_S(szFrom, _MAX_PATH, sFilePath.GetBuffer(0));
    szFrom[sFilePath.GetLength()+1] = 0;

    fop.fFlags |= FOF_SILENT;                // don't report progress
    fop.fFlags |= FOF_NOERRORUI;           // don't report errors
    fop.fFlags |= FOF_NOCONFIRMATION;        // don't confirm delete
    fop.wFunc = FO_DELETE;                   // REQUIRED: delete operation
    fop.pFrom = szFrom;                      // REQUIRED: which file(s)
    fop.pTo = NULL;                          // MUST be NULL
    if (bPermanentDelete) 
    { 
        // if delete requested..
        fop.fFlags &= ~FOF_ALLOWUNDO;   // ..don't use Recycle Bin
    } 
    else 
    {                                 // otherwise..
        fop.fFlags |= FOF_ALLOWUNDO;    // ..send to Recycle Bin
    }

    return SHFileOperation(&fop); // do it!  
}

CString Utility::GetINIString(LPCTSTR pszFile, LPCTSTR pszSection, LPCTSTR pszName)
{  
    TCHAR szBuffer[1024] = _T("");  
    GetPrivateProfileString(pszSection, pszName, _T(""), szBuffer, 1024, pszFile);

    CString sResult = szBuffer;
    sResult.Replace(_T("\\n"), _T("\n"));

    return sResult;
}

void Utility::SetINIString(LPCTSTR pszFile, LPCTSTR pszSection, LPCTSTR pszName, LPCTSTR pszValue)
{   
    WritePrivateProfileString(pszSection, pszName, pszValue, pszFile);
}


void Utility::SetLayoutRTL(HWND hWnd)
{
    DWORD dwExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
    dwExStyle |= WS_EX_LAYOUTRTL;
    SetWindowLong(hWnd, GWL_EXSTYLE, dwExStyle);

    SetLayout(GetDC(hWnd), LAYOUT_RTL);

    CRect rcWnd;
    ::GetClientRect(hWnd, &rcWnd);

    HWND hWndChild = GetWindow(hWnd, GW_CHILD);
    while(hWndChild!=NULL)
    {    
        SetLayoutRTL(hWndChild);

        CRect rc;
        ::GetWindowRect(hWndChild, &rc);    
        ::MapWindowPoints(0, hWnd, (LPPOINT)&rc, 2);
        ::MoveWindow(hWndChild, rcWnd.Width()-rc.right, rc.top, rc.Width(), rc.Height(), TRUE);

        SetLayout(GetDC(hWndChild), LAYOUT_RTL);

        hWndChild = GetWindow(hWndChild, GW_HWNDNEXT);
    }  
}

CString Utility::FormatErrorMsg(DWORD dwErrorCode)
{
    LPTSTR msg = 0;
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER,
        NULL, dwErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&msg, 0, NULL);
    CString str = msg;
    str.Replace(_T("\r\n"), _T(""));
    GlobalFree(msg);
    return str;
}

// GetBaseFileName
// This helper function returns file name without extension
CString Utility::GetFileName(CString sPath)
{
    CString sBase = sPath;
    int pos1 = sPath.ReverseFind('\\');
    if(pos1>=0)
        sBase = sBase.Mid(pos1+1);

    return sBase;
}

// GetBaseFileName
// This helper function returns file name without extension
CString Utility::GetBaseFileName(CString sFileName)
{
    CString sBase = sFileName;
    int pos1 = sFileName.ReverseFind('\\');
    if(pos1>=0)
        sBase = sBase.Mid(pos1+1);

    int pos2 = sBase.ReverseFind('.');
    if(pos2>=0)
    {
        sBase = sFileName.Mid(0, pos2);
    }
    return sBase;
}

// GetFileExtension
// This helper function returns file extension by file name
CString Utility::GetFileExtension(CString sFileName)
{
    CString sExt;
    int pos = sFileName.ReverseFind('.');
    if(pos>=0)
    {
        sExt = sFileName.Mid(pos+1);
    }
    return sExt;
}

CString Utility::GetProductVersion(CString sModuleName)
{
    CString sProductVer; 

    DWORD dwBuffSize = GetFileVersionInfoSize(sModuleName, 0);
    LPBYTE pBuff = (LPBYTE)GlobalAlloc(GPTR, dwBuffSize);  

    if(NULL!=pBuff && 0!=GetFileVersionInfo(sModuleName, 0, dwBuffSize, pBuff))
    {
        VS_FIXEDFILEINFO* fi = NULL;
        UINT uLen = 0;
        VerQueryValue(pBuff, _T("\\"), (LPVOID*)&fi, &uLen);

        WORD dwVerMajor = HIWORD(fi->dwProductVersionMS);
        WORD dwVerMinor = LOWORD(fi->dwProductVersionMS);
        WORD dwPatchLevel = HIWORD(fi->dwProductVersionLS);
        WORD dwVerBuild = LOWORD(fi->dwProductVersionLS);

        sProductVer.Format(_T("%u.%u.%u.%u"), 
            dwVerMajor, dwVerMinor, dwPatchLevel, dwVerBuild);    
    } 

    GlobalFree((HGLOBAL)pBuff);

    return sProductVer;
}

// Creates a folder. If some intermediate folders in the path do not exist,
// it creates them.
BOOL Utility::CreateFolder(CString sFolderName)
{  
    CString sIntermediateFolder;

    // Skip disc drive name "X:\" if presents
    int start = sFolderName.Find(':', 0);
    if(start>=0)
        start+=2; 

    int pos = start;  
    for(;;)
    {
        pos = sFolderName.Find('\\', pos);
        if(pos<0)
        {
            sIntermediateFolder = sFolderName;
        }
        else
        {
            sIntermediateFolder = sFolderName.Left(pos);
        }

        BOOL bCreate = CreateDirectory(sIntermediateFolder, NULL);
        if(!bCreate && GetLastError()!=ERROR_ALREADY_EXISTS)
            return FALSE;

        DWORD dwAttrs = GetFileAttributes(sIntermediateFolder);
        if((dwAttrs&FILE_ATTRIBUTE_DIRECTORY)==0)
            return FALSE;

        if(pos==-1)
            break;

        pos++;
    }

    return TRUE;
}

ULONG64 Utility::SystemTimeToULONG64( const SYSTEMTIME& st )
{
    FILETIME ft ;
    SystemTimeToFileTime( &st, &ft ) ;
    ULARGE_INTEGER integer ;
    integer.LowPart = ft.dwLowDateTime ;
    integer.HighPart = ft.dwHighDateTime ;
    return integer.QuadPart ;
}

CString Utility::FileSizeToStr(ULONG64 uFileSize)
{
    CString sFileSize;

    if(uFileSize==0)
    {
        sFileSize = _T("0 KB");
    }
    else if(uFileSize<1024)
    {
        float fSizeKbytes = (float)uFileSize/(float)1024;
        TCHAR szStr[64];
#if _MSC_VER<1400
        _stprintf(szStr, _T("%0.1f KB"), fSizeKbytes);    
#else
        _stprintf_s(szStr, 64, _T("%0.1f KB"), fSizeKbytes);    
#endif
        sFileSize = szStr;
    }
    else if(uFileSize<1024*1024)
    {
        sFileSize.Format(_T("%I64u KB"), uFileSize/1024);
    }
    else
    {
        float fSizeMbytes = (float)uFileSize/(float)(1024*1024);
        TCHAR szStr[64];
#if _MSC_VER<1400
        _stprintf(szStr, _T("%0.1f MB"), fSizeMbytes);    
#else
        _stprintf_s(szStr, 64, _T("%0.1f MB"), fSizeMbytes);    
#endif
        sFileSize = szStr;
    }

    return sFileSize;
}

CString Utility::AddEllipsis(LPCTSTR szString, int nMaxLength)
{
	if(szString==NULL)
		return CString("");

	CString sResult = szString;
	if(sResult.GetLength()>nMaxLength)
	{
		if(nMaxLength>=3)
			sResult = sResult.Mid(0, nMaxLength-3)+_T("...");		
	}

	return sResult;
}

std::vector<CString> Utility::ExplodeStr(LPCTSTR szString, LPCTSTR szSeparators)
{
	std::vector<CString> aTokens;

	CString copy = szString;	
	TCHAR  *context = 0;
	TCHAR  *token = _tcstok_s(const_cast<LPTSTR>((LPCTSTR)copy), szSeparators, &context);	
	while (token != 0) 
	{
		aTokens.push_back(token);
		token=_tcstok_s(NULL, szSeparators, &context);		
	};

	return aTokens;
}

long Utility::GetFileSize(const TCHAR *fileName)
{
    BOOL                        fOk;
    WIN32_FILE_ATTRIBUTE_DATA   fileInfo;

    if (NULL == fileName)
        return -1;

    fOk = GetFileAttributesEx(fileName, GetFileExInfoStandard, (void*)&fileInfo);
    if (!fOk)
        return -1;
    //assert(0 == fileInfo.nFileSizeHigh);
    return (long)fileInfo.nFileSizeLow;
}

BOOL Utility::IsFileSearchPattern(CString sFileName)
{
	// Check if the file name is a search template.		
	BOOL bSearchPattern = FALSE;	
	int nPos = sFileName.FindOneOf(_T("*?"));
	if(nPos>=0)
		bSearchPattern = true;
	return bSearchPattern;
}

void Utility::GetCpuDescription( CString & sDescr, DWORD & dwProcessorsNumber )
{
  int cpuId[4];
  __cpuid( cpuId, 0 );
  char szCpuVendor[16] = "";
  (int&)szCpuVendor[0] = cpuId[1];
  (int&)szCpuVendor[4] = cpuId[3];
  (int&)szCpuVendor[8] = cpuId[2];
  szCpuVendor[12] = 0;

  //Get CPU Information
  SYSTEM_INFO si;
  GetSystemInfo( &si );
  const char * pszCpuArch = "Unknown Architecture";
  switch ( si.wProcessorArchitecture )
  {
  case PROCESSOR_ARCHITECTURE_INTEL:  pszCpuArch = "x86";   break;
  case PROCESSOR_ARCHITECTURE_AMD64:  pszCpuArch = "x64";   break;
  case PROCESSOR_ARCHITECTURE_IA64:   pszCpuArch = "IPF";   break;
  }
  sDescr.Format( _T("%S %S family %u, model %u"), szCpuVendor, pszCpuArch, (unsigned)si.wProcessorLevel, (unsigned)( ( si.wProcessorRevision & 0xff00 ) >> 8 ) );

  dwProcessorsNumber = si.dwNumberOfProcessors;
}