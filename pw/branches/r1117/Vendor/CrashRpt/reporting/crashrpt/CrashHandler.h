/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: CrashHandler.h
// Description: Exception handling functionality.
// Authors: mikecarruth, zexspectrum
// Date: 2009

#pragma once
#include "stdafx.h"
#include "CrashRpt.h"      
#include "Utility.h"
#include "CritSec.h"
#include "SharedMem.h"
#include "Prefastdef.h"

/* This structure contains pointer to the exception handlers for a thread.*/
struct ThreadExceptionHandlers
{
    ThreadExceptionHandlers()
    {
        m_prevTerm = NULL;
        m_prevUnexp = NULL;
        m_prevSigFPE = NULL;
        m_prevSigILL = NULL;
        m_prevSigSEGV = NULL;
    }

    terminate_handler m_prevTerm;        // Previous terminate handler   
    unexpected_handler m_prevUnexp;      // Previous unexpected handler
    void (__cdecl *m_prevSigFPE)(int);   // Previous FPE handler
    void (__cdecl *m_prevSigILL)(int);   // Previous SIGILL handler
    void (__cdecl *m_prevSigSEGV)(int);  // Previous illegal storage access handler
};

// Sets the last error message (for the caller thread).
int crSetErrorMsg(PTSTR pszErrorMsg);

// This structure describes a file item (a file included into crash report).
struct FileItem
{
	FileItem()
	{
		m_bMakeCopy = FALSE;
		m_bAllowDelete = FALSE;
	}

    CString m_sSrcFilePath; // Path to the original file. 
    CString m_sDstFileName; // Destination file name (as seen in ZIP archive).
    CString m_sDescription; // Description.
    BOOL m_bMakeCopy;       // Should we make a copy of this file on crash?
							// If set, the file will be copied to crash report folder and that copy will be included into crash report,
							// otherwise the file will be included from its original location (not guaranteing that file is the same it was
							// at the moment of crash).
	BOOL m_bAllowDelete;    // Whether to allow user deleting the file from context menu of Error Report Details dialog.
};

// This structure describes a loaded module item.
struct ModuleItem
{
  ModuleItem()
  {
  }

  CString m_sModulePath; //  
  size_t codeStart; // 
  size_t codeEnd; // 
};

// Contains information about a registry key included into a crash report.
struct RegKeyInfo
{
	RegKeyInfo()
	{
		m_bAllowDelete = false;
	}

	CString m_sDstFileName; // Destination file name (as seen in ZIP archive).
	bool m_bAllowDelete;    // Whether to allow user deleting the file from context menu of Error Report Details dialog.
};

// This class is used to set exception handlers, catch exceptions
// and launch crash report sender process.
class CCrashHandler  
{
public:

    // Default constructor.
    CCrashHandler();

	// Destructor.
    virtual ~CCrashHandler();

	// Initializes the crash handler object.
    int Init(
        __in_opt LPCTSTR lpcszAppName = NULL,
        __in_opt LPCTSTR lpcszAppVersion = NULL,
        __in_opt LPCTSTR lpcszCrashSenderPath = NULL,
        __in_opt LPGETLOGFILE lpfnCallback = NULL,           
        __in_opt LPCTSTR lpcszTo = NULL,             
        __in_opt LPCTSTR lpcszSubject = NULL,
        __in_opt LPCTSTR lpcszUrl = NULL,
        __in_opt UINT (*puPriorities)[5] = NULL,
        DWORD dwFlags = 0,
        __in_opt LPCTSTR lpcszPrivacyPolicyURL = NULL,
        __in_opt LPCTSTR lpcszDebugHelpDLLPath = NULL,
        MINIDUMP_TYPE MiniDumpType = MiniDumpNormal,
        __in_opt LPCTSTR lpcszErrorReportSaveDir = NULL,
        __in_opt LPCTSTR lpcszRestartCmdLine = NULL,
        __in_opt LPCTSTR lpcszLangFilePath = NULL,
        __in_opt LPCTSTR lpcszEmailText = NULL,
        __in_opt LPCTSTR lpcszSmtpProxy = NULL,
        __in_opt LPCTSTR lpcszCustomSenderIcon = NULL,
		__in_opt LPCTSTR lpcszSmtpLogin = NULL,
		__in_opt LPCTSTR lpcszSmtpPassword = NULL);

	// Returns TRUE if object was initialized.
    BOOL IsInitialized();

	// Frees all used resources.
    int Destroy();

	// Sets crash callback function (wide-char version).
	int SetCrashCallbackW(PFNCRASHCALLBACKW pfnCallback, LPVOID pUserParam);

	// Sets crash callback function (multi-byte version).
	int SetCrashCallbackA(PFNCRASHCALLBACKA pfnCallback, LPVOID pUserParam);
	
    // Adds a file to the crash report.
    int AddFile(__in_z LPCTSTR lpFile, __in_opt LPCTSTR lpDestFile, 
				__in_opt LPCTSTR lpDesc, DWORD dwFlags);

    // Adds a named text property to the report.
    int AddProperty(CString sPropName, CString sPropValue);

    // Adds desktop screenshot of crash into error report.
    int AddScreenshot(DWORD dwFlags, int nJpegQuality);

	// Starts a video recording of desktop state; 
	// if crash will happen sometime, the video will be included into crash report.
	int AddVideo(DWORD dwFlags, int nDuration, int nFrameInterval, SIZE* pDesiredFrameSize, HWND hWndParent);

    // Adds a registry key to crash report.
    int AddRegKey(__in_z LPCTSTR szRegKey, __in_z LPCTSTR szDstFileName, DWORD dwFlags);

    // Generates error report	
    int GenerateErrorReport(__in_opt PCR_EXCEPTION_INFO pExceptionInfo = NULL);


    void FillLoadedModulesInfo( BYTE * CrashAddress );

    // Sets/unsets exception handlers for the entire process
    int SetProcessExceptionHandlers(DWORD dwFlags);
    int UnSetProcessExceptionHandlers();

    // Sets/unsets exception handlers for the caller thread
    int SetThreadExceptionHandlers(DWORD dwFlags);   
    int UnSetThreadExceptionHandlers();

	// Returns flags.
	DWORD GetFlags();

    // Returns the crash handler object (singleton).
    static CCrashHandler* GetCurrentProcessCrashHandler();
	
	// Releases the singleton of this crash handler object.
    static void ReleaseCurrentProcessCrashHandler();

    /* Exception handler functions. */

	// Structured exception handler (SEH handler)
    static LONG WINAPI SehHandler(__in PEXCEPTION_POINTERS pExceptionPtrs);
	static DWORD WINAPI StackOverflowThreadFunction(LPVOID threadParameter);
	// C++ terminate handler
    static void __cdecl TerminateHandler();
	// C++ unexpected handler
    static void __cdecl UnexpectedHandler();

#if _MSC_VER>=1300
	// C++ pure virtual call handler
    static void __cdecl PureCallHandler();
#endif 

#if _MSC_VER>=1300 && _MSC_VER<1400
	// Buffer overrun handler (deprecated in newest versions of Visual C++).
    static void __cdecl SecurityHandler(int code, void *x);
#endif

#if _MSC_VER>=1400
	// C++ Invalid parameter handler.
    static void __cdecl InvalidParameterHandler(const wchar_t* expression, 
        const wchar_t* function, const wchar_t* file, unsigned int line, uintptr_t pReserved);
#endif

#if _MSC_VER>=1300
	// C++ new operator fault (memory exhaustion) handler
    static int __cdecl NewHandler(size_t);
#endif

	// Signal handlers
    static void SigabrtHandler(int);
    static void SigfpeHandler(int /*code*/, int subcode);
    static void SigintHandler(int);
    static void SigillHandler(int);
    static void SigsegvHandler(int);
    static void SigtermHandler(int);

    /* Crash report generation methods */

    // Collects current state of CPU registers.
    void GetExceptionPointers(
        DWORD dwExceptionCode, 
        EXCEPTION_POINTERS* pExceptionPointers);

    // Packs crash description into shared memory.
    CRASH_DESCRIPTION* PackCrashInfoIntoSharedMem(__in CSharedMem* pSharedMem, BOOL bTempMem);
    // Packs a string.
    DWORD PackString(CString str);
    // Packs a file item.
    DWORD PackFileItem(FileItem& fi);
    // Packs a module item.
    DWORD PackModuleItem(ModuleItem& fi);
    // Packs a custom user property.
    DWORD PackProperty(CString sName, CString sValue);
    // Packs a registry key.
    DWORD PackRegKey(CString sKeyName, RegKeyInfo& rki);
		
    // Launches the CrashSender.exe process.
    int LaunchCrashSender(
        LPCTSTR szCmdLineParams, 
        BOOL bWait, 
        __out_opt HANDLE* phProcess); 

	// Returns TRUE if CrashSender.exe process is still alive.
	BOOL IsSenderProcessAlive();

    // Sets internal pointers to exception handlers to NULL.
    void InitPrevExceptionHandlerPointers();

	// Initializes several internal fields before each crash.
	int PerCrashInit();

    // Acqure exclusive access to this crash handler.
    void CrashLock(BOOL bLock);

	// Calls the crash callback function (if the callback function was specified by user).
	int CallBack(int nStage, CR_EXCEPTION_INFO* pExInfo);

    /* Private member variables. */

	// Singleton of the CCrashHandler class.
    static CCrashHandler* m_pProcessCrashHandler; 

	// Previous SEH exception filter.
    LPTOP_LEVEL_EXCEPTION_FILTER  m_oldSehHandler;  

#if _MSC_VER>=1300
    _purecall_handler m_prevPurec;   // Previous pure virtual call exception filter.
    _PNH m_prevNewHandler; // Previous new operator exception filter.
#endif

#if _MSC_VER>=1400
    _invalid_parameter_handler m_prevInvpar; // Previous invalid parameter exception filter.
#endif

#if _MSC_VER>=1300 && _MSC_VER<1400
    _secerr_handler_func m_prevSec; // Previous security exception filter.
#endif

    void (__cdecl *m_prevSigABRT)(int); // Previous SIGABRT handler.  
    void (__cdecl *m_prevSigINT)(int);  // Previous SIGINT handler.
    void (__cdecl *m_prevSigTERM)(int); // Previous SIGTERM handler.

    // List of exception handlers installed for worker threads of this process.
    std::map<DWORD, ThreadExceptionHandlers> m_ThreadExceptionHandlers;
    CCritSec m_csThreadExceptionHandlers; // Synchronization lock for m_ThreadExceptionHandlers.

    BOOL m_bInitialized;           // Flag telling if this object was initialized.  
    CString m_sAppName;            // Application name.
    CString m_sAppVersion;         // Application version.  
    CString m_sCrashGUID;          // Crash GUID.
    CString m_sImageName;          // Process image name.
    DWORD m_dwFlags;               // Flags.
    MINIDUMP_TYPE m_MinidumpType;  // Minidump type.
    CString m_sRestartCmdLine;     // App restart command line.
    CString m_sUrl;                // Url to use when sending error report over HTTP.  
    CString m_sEmailTo;            // E-mail recipient.
    int m_nSmtpPort;               // SMTP port.
    CString m_sSmtpProxyServer;    // SMTP proxy.
    int m_nSmtpProxyPort;          // SMTP proxy port.
	CString m_sSmtpLogin;           // SMTP login.
	CString m_sSmtpPassword;        // SMTP password.
    CString m_sEmailSubject;       // E-mail subject.
    CString m_sEmailText;          // E-mail text.
    UINT m_uPriorities[3];         // Delivery priorities.
    CString m_sPrivacyPolicyURL;   // Privacy policy URL.
    CString m_sPathToCrashSender;  // Path to CrashSender.exe
    CString m_sLangFileName;       // Language file.
    CString m_sPathToDebugHelpDll; // Path to dbghelp.dll.
    CString m_sUnsentCrashReportsFolder; // Path to the folder where to save error reports.
    LPGETLOGFILE m_lpfnCallback;   // Client crash callback (deprecated).
	BOOL m_bAddScreenshot;         // Should we add screenshot?
    DWORD m_dwScreenshotFlags;     // Screenshot flags.
    int m_nJpegQuality;            // Quality of JPEG screenshot images.
	BOOL  m_bAddVideo;             // Wether to add video recording.
	DWORD m_dwVideoFlags;          // Flags for video recording.
	int   m_nVideoDuration;        // Video duration.
	int   m_nVideoFrameInterval;   // Video frame interval.
	SIZE   m_DesiredFrameSize;     // Video frame size.
	HWND m_hWndVideoParent;        // Parent window for video recording dialog.
    CString m_sCustomSenderIcon;   // Resource name that can be used as custom Error Report dialog icon.
    std::map<CString, FileItem> m_files; // File items to include.
    std::map<CString, ModuleItem> m_modules; // Loaded modules info.
    std::map<CString, CString> m_props;  // User-defined properties to include.
    std::map<CString, RegKeyInfo> m_RegKeys; // Registry keys to dump.  
    CCritSec m_csCrashLock;        // Critical section used to synchronize thread access to this object. 
    HANDLE m_hEvent;               // Event used to synchronize CrashRpt.dll with CrashSender.exe.
	HANDLE m_hEvent2;              // Another event used to synchronize CrashRpt.dll with CrashSender.exe.
    CSharedMem m_SharedMem;        // Shared memory.  
    CRASH_DESCRIPTION* m_pCrashDesc; // Pointer to crash description shared mem view.
    CSharedMem* m_pTmpSharedMem;   // Used temporarily
    CRASH_DESCRIPTION* m_pTmpCrashDesc; // Used temporarily
	HANDLE m_hSenderProcess;       // Handle to CrashSender.exe process.
	PFNCRASHCALLBACKW m_pfnCallback2W; // Client crash callback.
	PFNCRASHCALLBACKA m_pfnCallback2A; // Client crash callback.
	LPVOID m_pCallbackParam;       // User-specified argument for callback function.
	std::string m_sErrorReportDirA;  // Error report directory name (multi-byte).
	std::wstring m_sErrorReportDirW; // Error report directory name (wide-char).
	int m_nCallbackRetCode;        // Return code of the callback function.
	BOOL m_bContinueExecution;     // Whether to terminate process (the default) or to continue execution after crash.
};


