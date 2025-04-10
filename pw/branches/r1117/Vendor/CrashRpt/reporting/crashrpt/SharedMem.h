/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: SharedMem.h
// Description: Shared memory class. Used for transferring data from crashed app to crash sender process.
// Authors: zexspectrum
// Date: 2010

#pragma once
#include "stdafx.h"
#include "CritSec.h"

// Generic block header.
struct GENERIC_HEADER
{
    BYTE m_uchMagic[3]; // Magic sequence.
    WORD m_wSize;       // Total bytes occupied by this block.
};

// String block description.
struct STRING_DESC
{
    BYTE m_uchMagic[3]; // Magic sequence "STR".  
    WORD m_wSize;       // Total bytes occupied by this block.
    // This structure is followed by (m_wSize-sizeof(STRING_DESC) bytes of string data.
};

// File item entry.
struct FILE_ITEM
{
    BYTE m_uchMagic[3]; // Magic sequence "FIL"
    WORD m_wSize;       // Total bytes occupied by this block.
    DWORD m_dwSrcFilePathOffs; // Path to the original file.
    DWORD m_dwDstFileNameOffs; // Name of the destination file.
    DWORD m_dwDescriptionOffs; // File description.
    BOOL  m_bMakeCopy;         // Should we make a copy of this file on crash?
	BOOL  m_bAllowDelete;      // Should allow user to delete the file from crash report?
};

// Module item entry.
struct MODULE_ITEM
{
  BYTE m_uchMagic[3]; // Magic sequence "FIL"
  WORD m_wSize;       // Total bytes occupied by this block.
  DWORD m_dwModulePathOffs; // 
  DWORD m_dwCodeStartOffs; // 
  DWORD m_dwCodeEndOffs; // 
};
// Registry key entry.
struct REG_KEY
{
    BYTE m_uchMagic[3];        // Magic sequence "REG"
    WORD m_wSize;              // Total bytes occupied by this block.
	BOOL m_bAllowDelete;       // Should allow user to delete the file from crash report?
    DWORD m_dwRegKeyNameOffs;  // Registry key name.
    DWORD m_dwDstFileNameOffs; // Destination file name.
};

// User-defined property.
struct CUSTOM_PROP
{
    BYTE m_uchMagic[3];  // Magic sequence "CPR"
    WORD m_wSize;        // Total bytes occupied by this block.
    DWORD m_dwNameOffs;  // Property name.
    DWORD m_dwValueOffs; // Property value.
};

// Crash description. 
struct CRASH_DESCRIPTION
{  
    BYTE m_uchMagic[3];  // Magic sequence "CRD"
    WORD m_wSize;        // Total bytes occupied by this block.
    DWORD m_dwTotalSize; // Total size of the whole used shared mem.
    DWORD m_dwCrashRptVer;         // Version of CrashRpt.
    UINT m_uFileItems;             // Count of file item records.
    UINT m_uModuleItems;             // Count of module item records.
    UINT m_uRegKeyEntries;         // Count of registry key entries.
    UINT m_uCustomProps;           // Count of user-defined properties.  
    DWORD m_dwInstallFlags;        // Flags passed to crInstall() function.
    int m_nSmtpPort;               // Smtp port.
    int m_nSmtpProxyPort;          // Smtp proxy port.
    UINT m_uPriorities[3];         // Delivery priorities.
    MINIDUMP_TYPE m_MinidumpType;  // Minidump type.
    //BOOL m_bAppRestart;            // Packed into flags
    BOOL  m_bAddScreenshot;        // Add screenshot?
    DWORD m_dwScreenshotFlags;     // Screenshot flags.
    int m_nJpegQuality;            // Jpeg image quality.
    DWORD m_dwUrlOffs;             // Offset of recipient URL.
    DWORD m_dwAppNameOffs;         // Offset of application name.
    DWORD m_dwAppVersionOffs;      // Offset of app version.
    DWORD m_dwLangFileNameOffs;    // Offset of language INI file name.
    DWORD m_dwRestartCmdLineOffs;  // Offset of app restart command line.
    DWORD m_dwEmailToOffs;         // Offset to E-mail recipient.
    DWORD m_dwCrashGUIDOffs;       // Offset to crash GUID.
    DWORD m_dwUnsentCrashReportsFolderOffs;  // Offset of folder name where error reports are stored.
    DWORD m_dwPrivacyPolicyURLOffs; // Offset of privacy policy URL.
    DWORD m_dwEmailSubjectOffs;    // Offset of E-mail subject.
    DWORD m_dwEmailTextOffs;       // Offset of E-mail text.
    DWORD m_dwSmtpProxyServerOffs; // Offset of SMTP proxy server name.
    DWORD m_dwPathToDebugHelpDllOffs; // Offset of dbghelp path.
    DWORD m_dwCustomSenderIconOffs; // Offset of custom Error Report dialog icon resource name.
    DWORD m_dwImageNameOffs;       // Offset to image name.
    DWORD m_dwProcessId;           // Process ID.
    DWORD m_dwThreadId;            // Thread ID.
    int m_nExceptionType;          // Exception type.
    DWORD m_dwExceptionCode;       // SEH exception code.
    DWORD m_dwInvParamExprOffs;    // Invalid parameter expression.
    DWORD m_dwInvParamFunctionOffs; // Invalid parameter function.
    DWORD m_dwInvParamFileOffs;    // Invalid parameter file.
    UINT  m_uInvParamLine;         // Invalid parameter line.
    UINT m_uFPESubcode;            // FPE subcode.
    PEXCEPTION_POINTERS m_pExceptionPtrs; // Exception pointers.
    BOOL m_bSendRecentReports;     // If TRUE, CrashSender.exe needs to send queued error reports.
								   // If FALSE, CrashSender.exe needs to send single report.
	DWORD m_dwSmtpLoginOffs;       // Offset of SMTP login name.
	DWORD m_dwSmtpPasswordOffs;    // Offset of SMTP login name. 
	BOOL  m_bAddVideo;             // Wether to add video recording.
	DWORD m_dwVideoFlags;          // Flags for video recording.
	int   m_nVideoDuration;        // Video duration.
	int   m_nVideoFrameInterval;   // Video frame interval.
	SIZE  m_DesiredFrameSize;      // Video frame size.
	HWND m_hWndVideoParent;        // Parent window for video recording dialog.
	BOOL m_bClientAppCrashed;      // If TRUE, the client app has crashed; otherwise the client has exited without crash.          
};

#define SHARED_MEM_MAX_SIZE 10*1024*1024   /* 10 MB */

// Used to share memory between CrashRpt.dll and CrashSender.exe
class CSharedMem
{
public:

    // Construction/destruction
    CSharedMem();  
    ~CSharedMem();  

    // Initializes shared memory
    BOOL Init(LPCTSTR szName, BOOL bOpenExisting, ULONG64 uSize);

	// Whether initialized or not
	BOOL IsInitialized();

    // Destroys the object
    BOOL Destroy();

    // Returns file mapping name
    CString GetName(); 

    // Returns file mapping size
    ULONG64 GetSize();

    // Creates a view and returns its start pointer
    LPBYTE CreateView(DWORD dwOffset, DWORD dwLength);

    // Destroys a view
    void DestroyView(LPBYTE pViewPtr);

private:

    CString m_sName;            // Name of the file mapping.
    HANDLE m_hFileMapping;		// Memory mapped object
    DWORD m_dwAllocGranularity; // System allocation granularity  	  
    ULONG64 m_uSize;	      	// Size of the file mapping.		  
    std::map<LPBYTE, LPBYTE> m_aViewStartPtrs; // Base of the view of the file mapping.    
};


