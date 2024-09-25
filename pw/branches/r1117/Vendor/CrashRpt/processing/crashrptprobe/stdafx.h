/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#include <errno.h>
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <atldef.h>
#if ( _ATL_VER < 0x0710 )
#define _WTL_SUPPORT_SDK_ATL3 // Support of VC++ Express 2005 and ATL 3.0
#endif

// Support for VS2005 Express & SDK ATL
#ifdef _WTL_SUPPORT_SDK_ATL3
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS
#pragma conform(forScope, off)
#pragma comment(linker, "/NODEFAULTLIB:atlthunk.lib")  
#endif // _WTL_SUPPORT_SDK_ATL3

#include <atlbase.h>

// Support for VS2005 Express & SDK ATL
#if defined(_WTL_SUPPORT_SDK_ATL3) && !defined(_WTLSUP_INCLUDED)
#define _WTLSUP_INCLUDED
namespace ATL
{
    inline void * __stdcall __AllocStdCallThunk()
    {
        return ::HeapAlloc(::GetProcessHeap(), 0, sizeof(_stdcallthunk));
    }

    inline void __stdcall __FreeStdCallThunk(void *p)
    {
        ::HeapFree(::GetProcessHeap(), 0, p);
    }
};
#endif // _WTL_SUPPORT_SDK_ATL3

#include <atlapp.h>
extern CAppModule _Module;
#include <atlwin.h>

// CString-related includes
#define _WTL_USE_CSTRING
#include <atlmisc.h>

#if _MSC_VER<1400
#define WCSNCPY_S(strDest, sizeInBytes, strSource, count) wcsncpy(strDest, strSource, count)
#define WCSCPY_S(strDestination, numberOfElements, strSource) wcscpy(strDestination, strSource)
#define STRCPY_S(strDestination, numberOfElements, strSource) strcpy(strDestination, strSource)
#define _TCSCPY_S(strDestination, numberOfElements, strSource) _tcscpy(strDestination, strSource)
#define _LTOT_S(value, str, sizeOfStr, radix) _ltot(value, str, radix)
#define _ULTOT_S(value, str, sizeOfStr, radix) _ultot(value, str, radix)
#define _TCSCAT_S(strDestination, size, strSource) _tcscat(strDestination, strSource)
#else
#define WCSNCPY_S(strDest, sizeInBytes, strSource, count) wcsncpy_s(strDest, sizeInBytes, strSource, count)
#define WCSCPY_S(strDestination, numberOfElements, strSource) wcscpy_s(strDestination, numberOfElements, strSource)
#define STRCPY_S(strDestination, numberOfElements, strSource) strcpy_s(strDestination, numberOfElements, strSource)
#define _TCSCPY_S(strDestination, numberOfElements, strSource) _tcscpy_s(strDestination, numberOfElements, strSource)
#define _LTOT_S(value, str, sizeOfStr, radix) _ltot_s(value, str, sizeOfStr, radix)
#define _ULTOT_S(value, str, sizeOfStr, radix) _ultot_s(value, str, sizeOfStr, radix)
#define _TCSCAT_S(strDestination, size, strSource) _tcscat_s(strDestination, size, strSource)
#endif

int _STPRINTF_S(TCHAR* buffer, size_t sizeOfBuffer, const TCHAR* format, ... );



