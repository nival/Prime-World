/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: CrashHandler.cpp
// Description: Exception handling and report generation functionality.
// Authors: mikecarruth, zexspectrum
// Date: 

#include "stdafx.h"
#include "CrashHandler.h"
#include "Utility.h"
#include "resource.h"
#include "strconv.h"

#ifndef _AddressOfReturnAddress

// Taken from: http://msdn.microsoft.com/en-us/library/s975zw7k(VS.71).aspx
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

// _ReturnAddress and _AddressOfReturnAddress should be prototyped before use 
EXTERNC void * _AddressOfReturnAddress(void);
EXTERNC void * _ReturnAddress(void);

#endif 

extern HANDLE g_hModuleCrashRpt;
CCrashHandler* CCrashHandler::m_pProcessCrashHandler = NULL;

CCrashHandler::CCrashHandler()
{
    // Init member variables to their defaults
    m_bInitialized = FALSE;  
    m_dwFlags = 0;
    m_MinidumpType = MiniDumpNormal;    
    m_nSmtpPort = 25;
    m_nSmtpProxyPort = 2525;
    memset(&m_uPriorities, 0, 3*sizeof(UINT));    
    m_lpfnCallback = NULL;
	m_bAddScreenshot = FALSE;	
    m_dwScreenshotFlags = 0;    
    m_nJpegQuality = 95;
	m_bAddVideo = FALSE;
	m_dwVideoFlags = 0;
	m_nVideoDuration = 60*1000; // 60 sec
	m_nVideoFrameInterval = 500; // 500 msec
	m_DesiredFrameSize.cx = 0; // default video frame size
	m_DesiredFrameSize.cy = 0;
	m_hWndVideoParent = NULL; 
    m_hEvent = NULL;  
	m_hEvent2 = NULL;
    m_pCrashDesc = NULL;
	m_hSenderProcess = NULL;
	m_pfnCallback2W = NULL;
	m_pfnCallback2A = NULL;    
	m_pCallbackParam = NULL;
	m_nCallbackRetCode = CR_CB_NOTIFY_NEXT_STAGE;
	m_bContinueExecution = TRUE;

    // Init exception handler pointers
    InitPrevExceptionHandlerPointers();
}

CCrashHandler::~CCrashHandler()
{
    // Clean up
    Destroy();
}

int CCrashHandler::Init(
        LPCTSTR lpcszAppName,
        LPCTSTR lpcszAppVersion,
        LPCTSTR lpcszCrashSenderPath,
        LPGETLOGFILE lpfnCallback, 
        LPCTSTR lpcszTo, 
        LPCTSTR lpcszSubject,
        LPCTSTR lpcszUrl,
        UINT (*puPriorities)[5],
        DWORD dwFlags,
        LPCTSTR lpcszPrivacyPolicyURL,
        LPCTSTR lpcszDebugHelpDLLPath,
        MINIDUMP_TYPE MiniDumpType,
        LPCTSTR lpcszErrorReportSaveDir,
        LPCTSTR lpcszRestartCmdLine,
        LPCTSTR lpcszLangFilePath,
        LPCTSTR lpcszEmailText,
        LPCTSTR lpcszSmtpProxy,
        LPCTSTR lpcszCustomSenderIcon,
		LPCTSTR lpcszSmtpLogin,
		LPCTSTR lpcszSmtpPassword)
{ 
	// This method initializes configuration parameters, 
	// creates shared memory buffer and saves the configuration parameters there,
	// installs process-wide exception handlers.

    crSetErrorMsg(_T("Unspecified error."));

	// Save flags
    m_dwFlags = dwFlags;

    // Save minidump type  
    m_MinidumpType = MiniDumpType;

    // Save user supplied callback (obsolete)
    m_lpfnCallback = lpfnCallback;
	
    // Save application name
    m_sAppName = lpcszAppName;

    // If no app name provided, use the default (EXE name)
    if(m_sAppName.IsEmpty())
    {
        m_sAppName = Utility::getAppName();
    }

    // Save app version
    m_sAppVersion = lpcszAppVersion;

    // If no app version provided, use the default (EXE product version)
    if(m_sAppVersion.IsEmpty())
    {
        // Get EXE image name
        CString sImageName = Utility::GetModuleName(NULL);
        m_sAppVersion = Utility::GetProductVersion(sImageName);
        if(m_sAppVersion.IsEmpty())
        {
            // If product version missing, return error.      
            crSetErrorMsg(_T("Application version is not specified."));
            return 1;
        }
    }

    // Get process image name
    m_sImageName = Utility::GetModuleName(NULL);

	// Save custom Crash Report dialog icon
    m_sCustomSenderIcon = lpcszCustomSenderIcon;

	// If the custom icon path specified, parse the path (extract resource file name and icon index)
    if(!m_sCustomSenderIcon.IsEmpty())
    {
        CString sResourceFile;
        CString sIconIndex;
        int nIconIndex = 0;

        int nComma = m_sCustomSenderIcon.ReverseFind(',');    
        if(nComma>=0)
        {
            sResourceFile = m_sCustomSenderIcon.Left(nComma);      
            sIconIndex = m_sCustomSenderIcon.Mid(nComma+1);
            sIconIndex.TrimLeft();
            sIconIndex.TrimRight();
            nIconIndex = _ttoi(sIconIndex);      
        }
        else
        {
            sResourceFile = m_sCustomSenderIcon;
        }

        sResourceFile.TrimRight();        

        if(nIconIndex==-1)
        {
            crSetErrorMsg(_T("Invalid index of custom icon (it should not equal to -1)."));
            return 1;
        }

    }

    // Save URL to send reports via HTTP/HTTPS
    if(lpcszUrl!=NULL)
    {
        m_sUrl = CString(lpcszUrl);
    }

    // Check that we store ZIP archives only when error reports are not being sent.
    BOOL bSendErrorReport = (dwFlags&CR_INST_DONT_SEND_REPORT)?FALSE:TRUE;
    BOOL bStoreZIPArchives = (dwFlags&CR_INST_STORE_ZIP_ARCHIVES)?TRUE:FALSE;
    if(bSendErrorReport && bStoreZIPArchives)
    {
        crSetErrorMsg(_T("The flag CR_INST_STORE_ZIP_ARCHIVES should be used with CR_INST_DONT_SEND_REPORT flag."));
        return 1;
    }

    // Save restart command line
    m_sRestartCmdLine = lpcszRestartCmdLine;

    // Save E-mail recipient(s) address
    m_sEmailTo = lpcszTo;
    m_nSmtpPort = 25;

    // Check for custom SMTP port
    int pos = m_sEmailTo.ReverseFind(':');
    if(pos>=0)
    {
        CString sServer = m_sEmailTo.Mid(0, pos);
        CString sPort = m_sEmailTo.Mid(pos+1);
        m_sEmailTo = sServer;
        m_nSmtpPort = _ttoi(sPort);
    }

    // Set up SMTP proxy
    m_nSmtpProxyPort = 25;
    if(lpcszSmtpProxy!=NULL)
    {
        m_sSmtpProxyServer = lpcszSmtpProxy;      
        int pos2 = m_sSmtpProxyServer.ReverseFind(':');
        if(pos2>=0)
        {
            CString sServer = m_sSmtpProxyServer.Mid(0, pos2);
            CString sPort = m_sSmtpProxyServer.Mid(pos2+1);
            m_sSmtpProxyServer = sServer;
            m_nSmtpProxyPort = _ttoi(sPort);
        }
    }

	// Save login and password used for SMTP authentication.
	if(lpcszSmtpLogin!=NULL)
	{
		m_sSmtpLogin = lpcszSmtpLogin;

		if(lpcszSmtpPassword!=NULL)
			m_sSmtpPassword = lpcszSmtpPassword;
	}

    // Save E-mail subject
    m_sEmailSubject = lpcszSubject;

    // If the subject is empty...
    if(m_sEmailSubject.IsEmpty())
    {
        // Generate the default subject
        m_sEmailSubject.Format(_T("%s %s Error Report"), m_sAppName, 
            m_sAppVersion.IsEmpty()?_T("[unknown_ver]"):m_sAppVersion);
    }

    // Save Email text.
    m_sEmailText = lpcszEmailText;

    // Save crash report delivery priorities
    if(puPriorities!=NULL)
        memcpy(&m_uPriorities, puPriorities, 3*sizeof(UINT));
    else
        memset(&m_uPriorities, 0, 3*sizeof(UINT));

    // Save privacy policy URL (if exists)
    if(lpcszPrivacyPolicyURL!=NULL)
        m_sPrivacyPolicyURL = lpcszPrivacyPolicyURL;

    // Get the name of CrashRpt DLL
    LPTSTR pszCrashRptModule = NULL;
    CString sCrashRptModule = _T("CrashRpt.dll");
#ifndef CRASHRPT_LIB
#ifdef USE_VERSION
#ifdef _DEBUG
    sCrashRptModule.Format(_T("CrashRpt%dd.dll"), CRASHRPT_VER);
    pszCrashRptModule = sCrashRptModule.GetBuffer(0);
#else
    sCrashRptModule.Format(_T("CrashRpt%d.dll"), CRASHRPT_VER);
    pszCrashRptModule = sCrashRptModule.GetBuffer(0);
#endif //_DEBUG
#endif
#else //!CRASHRPT_LIB
    pszCrashRptModule = NULL;
#endif

    // Save path to CrashSender.exe
    if(lpcszCrashSenderPath==NULL)
    {
        // By default assume that CrashSender.exe is located in the same dir as CrashRpt.dll    
        m_sPathToCrashSender = Utility::GetModulePath((HMODULE)g_hModuleCrashRpt);    
    }
    else
    {
        // Save user-specified path    
        m_sPathToCrashSender = CString(lpcszCrashSenderPath);    
    }

    // Get CrashSender EXE name
    CString sCrashSenderName = _T("CrashSender.exe");
#ifdef USE_VERSION
#ifdef _DEBUG
    sCrashSenderName.Format(_T("CrashSender%dd.exe"), CRASHRPT_VER);
#else
    sCrashSenderName.Format(_T("CrashSender%d.exe"), CRASHRPT_VER);
#endif //_DEBUG
#endif

    // Check that CrashSender.exe file exists
    if(m_sPathToCrashSender.Right(1)!='\\')
        m_sPathToCrashSender+="\\";    

    HANDLE hFile = CreateFile(m_sPathToCrashSender+sCrashSenderName, FILE_GENERIC_READ, 
        FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);  
    if(hFile==INVALID_HANDLE_VALUE)
    { 
        crSetErrorMsg(_T("CrashSender.exe is not found in the specified path."));
        return 1;
    }
    else
    {
        CloseHandle(hFile);   
    }

    // Determine where to look for language file.
    if(lpcszLangFilePath!=NULL)
    {
        // User has provided the custom lang file path.
        m_sLangFileName = lpcszLangFilePath;
    }
    else
    {
        // Look for crashrpt_lang.ini in the same folder as CrashSender.exe.
        m_sLangFileName = m_sPathToCrashSender + _T("crashrpt_lang.ini");
    }

    m_sPathToCrashSender += sCrashSenderName;

	// Check if lang file exists on disk
    CString sLangFileVer = Utility::GetINIString(m_sLangFileName, _T("Settings"), _T("CrashRptVersion"));
    int lang_file_ver = _ttoi(sLangFileVer);
    if(lang_file_ver!=CRASHRPT_VER)
    {    
        crSetErrorMsg(_T("Missing language file or wrong language file version."));
        return 1; // Language INI file has wrong version!
    }

	// If path to dbghelp.dll not provided, use the default one
    if(lpcszDebugHelpDLLPath==NULL)
    {
        // By default assume that debughlp.dll is located in the same dir as CrashRpt.dll    
        m_sPathToDebugHelpDll = Utility::GetModulePath((HMODULE)g_hModuleCrashRpt);       
    }
    else
    {
        m_sPathToDebugHelpDll = CString(lpcszDebugHelpDLLPath);        
    }  

    CString sDebugHelpDLL_name = "dbghelp.dll";  

    if(m_sPathToDebugHelpDll.Right(1)!='\\')
        m_sPathToDebugHelpDll+="\\";

	// Load dbghelp.dll library
    HANDLE hDbgHelpDll = LoadLibrary(m_sPathToDebugHelpDll+sDebugHelpDLL_name);    
	// and check result
    if(!hDbgHelpDll)
    {
        //try again ... fallback to dbghelp.dll in path
        m_sPathToDebugHelpDll = _T("");
        hDbgHelpDll = LoadLibrary(sDebugHelpDLL_name);
        if(!hDbgHelpDll)
        {     
            crSetErrorMsg(_T("Couldn't load dbghelp.dll."));      
            return 1;
        }    
    }

    m_sPathToDebugHelpDll += sDebugHelpDLL_name;

    if(hDbgHelpDll!=NULL)
    {
        FreeLibrary((HMODULE)hDbgHelpDll);
        hDbgHelpDll = NULL;
    }
	
	// Determine the directory where to save error reports
    if(lpcszErrorReportSaveDir==NULL)
    {
        // Create %LOCAL_APPDATA%\CrashRpt\UnsentCrashReports\AppName_AppVer folder.
        CString sLocalAppDataFolder;
        DWORD dwCSIDL = CSIDL_LOCAL_APPDATA;
        Utility::GetSpecialFolder(dwCSIDL, sLocalAppDataFolder);
        m_sUnsentCrashReportsFolder.Format(_T("%s\\CrashRpt\\UnsentCrashReports\\%s_%s"), 
            sLocalAppDataFolder, m_sAppName, m_sAppVersion);
    }
    else
    {    
        m_sUnsentCrashReportsFolder = lpcszErrorReportSaveDir;
    }

    BOOL bCreateDir = Utility::CreateFolder(m_sUnsentCrashReportsFolder);
    if(!bCreateDir)
    {
        ATLASSERT(0);
        crSetErrorMsg(_T("Couldn't create crash report directory."));
        return 1; 
    }

	// Init some fields that should be reinitialized before each new crash.
	if(0!=PerCrashInit())
		return 1;

	// Associate this handler object with the caller process.
    m_pProcessCrashHandler =  this;

    // Set exception handlers with initial values (NULLs)
    InitPrevExceptionHandlerPointers();

    // Set exception handlers that work on per-process basis
    int nSetProcessHandlers = SetProcessExceptionHandlers(dwFlags);   
    if(nSetProcessHandlers!=0)
    {
        ATLASSERT(nSetProcessHandlers==0);
        crSetErrorMsg(_T("Couldn't set C++ exception handlers for current process."));
        return 1;
    }

    // Set exception handlers that work on per-thread basis
    int nSetThreadHandlers = SetThreadExceptionHandlers(dwFlags);
    if(nSetThreadHandlers!=0)
    {
        ATLASSERT(nSetThreadHandlers==0);
        crSetErrorMsg(_T("Couldn't set C++ exception handlers for main execution thread."));
        return 1;
    }
	    
    // If user wants us to send pending error reports that were queued recently,
    // launch the CrashSender.exe and make it to alert user and send the reports.
    if(dwFlags&CR_INST_SEND_QUEUED_REPORTS)
    {
        // Create temporary shared mem.
        CSharedMem tmpSharedMem;    
        CRASH_DESCRIPTION* pCrashDesc = PackCrashInfoIntoSharedMem(&tmpSharedMem, TRUE);
        pCrashDesc->m_bSendRecentReports = TRUE;
        if(0!=LaunchCrashSender(tmpSharedMem.GetName(), TRUE, NULL))
        {
            crSetErrorMsg(_T("Couldn't launch CrashSender.exe process."));
            return 1;
        }

        m_pTmpCrashDesc = m_pCrashDesc;
        m_pTmpSharedMem = &m_SharedMem;
    }

	// The following code is intended to fix the issue with 32-bit applications in 64-bit environment.
	// http://support.microsoft.com/kb/976038/en-us
	// http://code.google.com/p/crashrpt/issues/detail?id=104

	typedef BOOL (WINAPI * SETPROCESSUSERMODEEXCEPTIONPOLICY)(DWORD dwFlags);
	typedef BOOL (WINAPI * GETPROCESSUSERMODEEXCEPTIONPOLICY)(LPDWORD lpFlags);
	#define PROCESS_CALLBACK_FILTER_ENABLED     0x1

	HMODULE hKernel32 = LoadLibrary(_T("kernel32.dll"));
	if(hKernel32!=NULL)
	{
		SETPROCESSUSERMODEEXCEPTIONPOLICY pfnSetProcessUserModeExceptionPolicy = 
			(SETPROCESSUSERMODEEXCEPTIONPOLICY)GetProcAddress(hKernel32, "SetProcessUserModeExceptionPolicy");
		GETPROCESSUSERMODEEXCEPTIONPOLICY pfnGetProcessUserModeExceptionPolicy = 
			(GETPROCESSUSERMODEEXCEPTIONPOLICY)GetProcAddress(hKernel32, "GetProcessUserModeExceptionPolicy");

		if(pfnSetProcessUserModeExceptionPolicy!=NULL && 
			pfnGetProcessUserModeExceptionPolicy!=NULL)
		{
			DWORD dwFlags = 0;
			if(pfnGetProcessUserModeExceptionPolicy(&dwFlags))
			{
				pfnSetProcessUserModeExceptionPolicy(dwFlags & ~PROCESS_CALLBACK_FILTER_ENABLED); 
			}
		}

		FreeLibrary(hKernel32);
	}

    // Initialization OK.
    m_bInitialized = TRUE;
    crSetErrorMsg(_T("Success."));
    return 0;
}

int CCrashHandler::SetCrashCallbackW(PFNCRASHCALLBACKW pfnCallback, LPVOID pUserParam)
{
	m_pfnCallback2W = pfnCallback;
	m_pCallbackParam = pUserParam;
	
	return 0;
}

int CCrashHandler::SetCrashCallbackA(PFNCRASHCALLBACKA pfnCallback, LPVOID pUserParam)
{
	m_pfnCallback2A = pfnCallback;
	m_pCallbackParam = pUserParam;
	
	return 0;
}

// Packs config info to shared mem.
CRASH_DESCRIPTION* CCrashHandler::PackCrashInfoIntoSharedMem(CSharedMem* pSharedMem, BOOL bTempMem)
{
    m_pTmpSharedMem = pSharedMem;

    CString sSharedMemName;
    if(bTempMem)
        sSharedMemName.Format(_T("%s-tmp"), m_sCrashGUID);    
    else 
        sSharedMemName = m_sCrashGUID;

	if(!pSharedMem->IsInitialized())
	{
		// Initialize shared memory.
		BOOL bSharedMem = pSharedMem->Init(sSharedMemName, FALSE, SHARED_MEM_MAX_SIZE);
		if(!bSharedMem)
		{
			ATLASSERT(0);
			crSetErrorMsg(_T("Couldn't initialize shared memory."));
			return NULL; 
		}
	}

    // Create memory view.
    m_pTmpCrashDesc = 
        (CRASH_DESCRIPTION*)pSharedMem->CreateView(0, sizeof(CRASH_DESCRIPTION));  
    if(m_pTmpCrashDesc==NULL)
    {
        ATLASSERT(0);
        crSetErrorMsg(_T("Couldn't create shared memory view."));
        return NULL; 
    }

    // Pack config information to shared memory
    memset(m_pTmpCrashDesc, 0, sizeof(CRASH_DESCRIPTION));
    memcpy(m_pTmpCrashDesc->m_uchMagic, "CRD", 3);  
    m_pTmpCrashDesc->m_wSize = sizeof(CRASH_DESCRIPTION);
    m_pTmpCrashDesc->m_dwTotalSize = sizeof(CRASH_DESCRIPTION);  
    m_pTmpCrashDesc->m_dwCrashRptVer = CRASHRPT_VER;
    m_pTmpCrashDesc->m_dwInstallFlags = m_dwFlags;
    m_pTmpCrashDesc->m_MinidumpType = m_MinidumpType;
    m_pTmpCrashDesc->m_nSmtpPort = m_nSmtpPort;
    m_pTmpCrashDesc->m_nSmtpProxyPort = m_nSmtpProxyPort;
    m_pTmpCrashDesc->m_bAddScreenshot = m_bAddScreenshot;
    m_pTmpCrashDesc->m_dwScreenshotFlags = m_dwScreenshotFlags;      
    memcpy(m_pTmpCrashDesc->m_uPriorities, m_uPriorities, sizeof(UINT)*3);
	m_pTmpCrashDesc->m_bAddVideo = m_bAddVideo;
	m_pTmpCrashDesc->m_hWndVideoParent = m_hWndVideoParent;
	m_pTmpCrashDesc->m_dwProcessId = GetCurrentProcessId();
	m_pTmpCrashDesc->m_bClientAppCrashed = FALSE;

    m_pTmpCrashDesc->m_dwAppNameOffs = PackString(m_sAppName);
    m_pTmpCrashDesc->m_dwAppVersionOffs = PackString(m_sAppVersion);
    m_pTmpCrashDesc->m_dwCrashGUIDOffs = PackString(m_sCrashGUID);
    m_pTmpCrashDesc->m_dwImageNameOffs = PackString(m_sImageName);
    m_pTmpCrashDesc->m_dwLangFileNameOffs = PackString(m_sLangFileName);
    m_pTmpCrashDesc->m_dwPathToDebugHelpDllOffs = PackString(m_sPathToDebugHelpDll);
    m_pTmpCrashDesc->m_dwRestartCmdLineOffs = PackString(m_sRestartCmdLine);
    m_pTmpCrashDesc->m_dwPrivacyPolicyURLOffs = PackString(m_sPrivacyPolicyURL);
    m_pTmpCrashDesc->m_dwUnsentCrashReportsFolderOffs = PackString(m_sUnsentCrashReportsFolder);  
    m_pTmpCrashDesc->m_dwCustomSenderIconOffs = PackString(m_sCustomSenderIcon);
    m_pTmpCrashDesc->m_dwUrlOffs = PackString(m_sUrl);    
    m_pTmpCrashDesc->m_dwEmailToOffs = PackString(m_sEmailTo);
    m_pTmpCrashDesc->m_dwEmailSubjectOffs = PackString(m_sEmailSubject);
    m_pTmpCrashDesc->m_dwEmailTextOffs = PackString(m_sEmailText);  
    m_pTmpCrashDesc->m_dwSmtpProxyServerOffs = PackString(m_sSmtpProxyServer);    
	m_pTmpCrashDesc->m_dwSmtpLoginOffs = PackString(m_sSmtpLogin);    
	m_pTmpCrashDesc->m_dwSmtpPasswordOffs = PackString(m_sSmtpPassword);    

	// Pack file items
	std::map<CString, FileItem>::iterator fit;
	for(fit=m_files.begin(); fit!=m_files.end(); fit++)
	{
		FileItem& fi = fit->second;

		// Pack this file item into shared mem.
		PackFileItem(fi);
	}

  // Pack custom props
	std::map<CString, CString>::iterator pit;
	for(pit=m_props.begin(); pit!=m_props.end(); pit++)
	{		
		// Pack this prop into shared mem.
		PackProperty(pit->first, pit->second);
	}

	// Pack reg keys
	std::map<CString, RegKeyInfo>::iterator rit;
	for(rit=m_RegKeys.begin(); rit!=m_RegKeys.end(); rit++)
	{		
		RegKeyInfo& rki = rit->second;

		// Pack this reg key into shared mem.
		PackRegKey(rit->first, rki);
	}

    return m_pTmpCrashDesc;
}

// Packs a string to shared memory
DWORD CCrashHandler::PackString(CString str)
{
    DWORD dwTotalSize = m_pTmpCrashDesc->m_dwTotalSize;
    int nStrLen = str.GetLength()*sizeof(TCHAR);
    WORD wLength = (WORD)(sizeof(STRING_DESC)+nStrLen);

    LPBYTE pView = m_pTmpSharedMem->CreateView(dwTotalSize, wLength);  
    STRING_DESC* pStrDesc = (STRING_DESC*)pView;
    memcpy(pStrDesc->m_uchMagic, "STR", 3);
    pStrDesc->m_wSize = wLength;
    memcpy(pView+sizeof(STRING_DESC), str.GetBuffer(0), nStrLen); 

    m_pTmpCrashDesc->m_dwTotalSize += wLength;

    m_pTmpSharedMem->DestroyView(pView);
    return dwTotalSize;
}

// Packs file item to shared memory
DWORD CCrashHandler::PackFileItem(FileItem& fi)
{
    DWORD dwTotalSize = m_pTmpCrashDesc->m_dwTotalSize;
    WORD wLength = sizeof(FILE_ITEM);
    m_pTmpCrashDesc->m_dwTotalSize += wLength;
    m_pTmpCrashDesc->m_uFileItems++;

    LPBYTE pView = m_pTmpSharedMem->CreateView(dwTotalSize, wLength);    
    FILE_ITEM* pFileItem = (FILE_ITEM*)pView;

    memcpy(pFileItem->m_uchMagic, "FIL", 3);  
    pFileItem->m_dwSrcFilePathOffs = PackString(fi.m_sSrcFilePath);
    pFileItem->m_dwDstFileNameOffs = PackString(fi.m_sDstFileName);
    pFileItem->m_dwDescriptionOffs = PackString(fi.m_sDescription);
    pFileItem->m_bMakeCopy = fi.m_bMakeCopy;
	pFileItem->m_bAllowDelete = fi.m_bAllowDelete;
    pFileItem->m_wSize = (WORD)(m_pTmpCrashDesc->m_dwTotalSize-dwTotalSize);

    m_pTmpSharedMem->DestroyView(pView);
    return dwTotalSize;
}

// Packs file item to shared memory
DWORD CCrashHandler::PackModuleItem(ModuleItem& item)
{
  DWORD dwTotalSize = m_pTmpCrashDesc->m_dwTotalSize;
  WORD wLength = sizeof(MODULE_ITEM);
  m_pTmpCrashDesc->m_dwTotalSize += wLength;
  m_pTmpCrashDesc->m_uModuleItems++;

  LPBYTE pView = m_pTmpSharedMem->CreateView(dwTotalSize, wLength);    
  MODULE_ITEM* pItem = (MODULE_ITEM*)pView;

  memcpy(pItem->m_uchMagic, "MIL", 3);  
  pItem->m_dwModulePathOffs = PackString(item.m_sModulePath);
  CString sVal;
  sVal.Format(_T("0x%08x"), item.codeStart);
  pItem->m_dwCodeStartOffs = PackString(sVal);
  sVal.Format(_T("0x%08x"), item.codeEnd);
  pItem->m_dwCodeEndOffs = PackString(sVal);
  pItem->m_wSize = (WORD)(m_pTmpCrashDesc->m_dwTotalSize-dwTotalSize);

  m_pTmpSharedMem->DestroyView(pView);
  return dwTotalSize;
}

// Packs custom property to shared memory
DWORD CCrashHandler::PackProperty(CString sName, CString sValue)
{
    DWORD dwTotalSize = m_pTmpCrashDesc->m_dwTotalSize;
    WORD wLength = sizeof(CUSTOM_PROP);
    m_pTmpCrashDesc->m_dwTotalSize += wLength;
    m_pTmpCrashDesc->m_uCustomProps++;

    LPBYTE pView = m_pTmpSharedMem->CreateView(dwTotalSize, wLength);    
    CUSTOM_PROP* pProp = (CUSTOM_PROP*)pView;

    memcpy(pProp->m_uchMagic, "CPR", 3); 
    pProp->m_dwNameOffs = PackString(sName);
    pProp->m_dwValueOffs = PackString(sValue);
    pProp->m_wSize = (WORD)(m_pTmpCrashDesc->m_dwTotalSize-dwTotalSize);

    m_pTmpSharedMem->DestroyView(pView);
    return dwTotalSize;
}

// Packs registry key to shared memory
DWORD CCrashHandler::PackRegKey(CString sKeyName, RegKeyInfo& rki)
{
    DWORD dwTotalSize = m_pTmpCrashDesc->m_dwTotalSize;
    WORD wLength = sizeof(REG_KEY);
    m_pTmpCrashDesc->m_dwTotalSize += wLength;
    m_pTmpCrashDesc->m_uRegKeyEntries++;

    LPBYTE pView = m_pTmpSharedMem->CreateView(dwTotalSize, wLength);    
    REG_KEY* pKey = (REG_KEY*)pView;

    memcpy(pKey->m_uchMagic, "REG", 3); 
	pKey->m_bAllowDelete = rki.m_bAllowDelete;
    pKey->m_dwRegKeyNameOffs = PackString(sKeyName);
	pKey->m_dwDstFileNameOffs = PackString(rki.m_sDstFileName);
    pKey->m_wSize = (WORD)(m_pTmpCrashDesc->m_dwTotalSize-dwTotalSize);

    m_pTmpSharedMem->DestroyView(pView);
    return dwTotalSize;
}


// Returns TRUE if initialized, otherwise FALSE
BOOL CCrashHandler::IsInitialized()
{
    return m_bInitialized;
}

// Destroys the object
int CCrashHandler::Destroy()
{
    crSetErrorMsg(_T("Unspecified error."));

    if(!m_bInitialized)
    {
        crSetErrorMsg(_T("Can't destroy not initialized crash handler."));
        return 1;
    }  

	// If we are recording video, we need to notify the CrashSender.exe about
	// our exit.
	if(m_bAddVideo)
	{
		// Set event 2, so CrashSender.exe will exit from video recording loop
		SetEvent(m_hEvent2);

		// Wait until CrashSender.exe completes its task
		WaitForSingleObject(m_hEvent, INFINITE);		
	}

	// Free handle to CrashSender.exe process.
	if(m_hSenderProcess!=NULL)
		CloseHandle(m_hSenderProcess);

	// Free events
	if(m_hEvent)
	{
		CloseHandle(m_hEvent);
		m_hEvent = NULL;
	}

	if(m_hEvent2)
	{
		CloseHandle(m_hEvent2);
		m_hEvent2 = NULL;
	}

    // Reset SEH exception filter
    if (m_oldSehHandler)
        SetUnhandledExceptionFilter(m_oldSehHandler);

    m_oldSehHandler = NULL;

    // All installed per-thread C++ exception handlers should be uninstalled 
    // using crUninstallFromCurrentThread() before calling Destroy()

    {
        CAutoLock lock(&m_csThreadExceptionHandlers);
        ATLASSERT(m_ThreadExceptionHandlers.size()==0);          
    }

	// 
    m_pProcessCrashHandler = NULL;

    // OK.
    m_bInitialized = FALSE;
    crSetErrorMsg(_T("Success."));
    return 0;
}

// Sets internal pointers to previously used exception handlers to NULL
void CCrashHandler::InitPrevExceptionHandlerPointers()
{
    m_oldSehHandler = NULL;

#if _MSC_VER>=1300
    m_prevPurec = NULL;
    m_prevNewHandler = NULL;
#endif

#if _MSC_VER>=1300 && _MSC_VER<1400    
    m_prevSec = NULL;
#endif

#if _MSC_VER>=1400
    m_prevInvpar = NULL;
#endif  

    m_prevSigABRT = NULL;  
    m_prevSigINT = NULL;  
    m_prevSigTERM = NULL;
}

// Returns singleton of the crash handler
CCrashHandler* CCrashHandler::GetCurrentProcessCrashHandler()
{   
    return m_pProcessCrashHandler;
}

// Releases the crash handler pointer
void CCrashHandler::ReleaseCurrentProcessCrashHandler()
{
    if(m_pProcessCrashHandler!=NULL)
    {
        delete m_pProcessCrashHandler;
        m_pProcessCrashHandler = NULL;
    }
}

// Sets exception handlers that work on per-process basis
int CCrashHandler::SetProcessExceptionHandlers(DWORD dwFlags)
{
    crSetErrorMsg(_T("Unspecified error."));

    // If 0 is specified as dwFlags, assume all handlers should be
    // installed
    if((dwFlags&CR_INST_ALL_POSSIBLE_HANDLERS)==0)
        dwFlags |= CR_INST_ALL_POSSIBLE_HANDLERS;

    if(dwFlags&CR_INST_STRUCTURED_EXCEPTION_HANDLER)
    {
        // Install top-level SEH handler
        m_oldSehHandler = SetUnhandledExceptionFilter(SehHandler);    
    }

    _set_error_mode(_OUT_TO_STDERR);

#if _MSC_VER>=1300
    if(dwFlags&CR_INST_PURE_CALL_HANDLER)
    {
        // Catch pure virtual function calls.
        // Because there is one _purecall_handler for the whole process, 
        // calling this function immediately impacts all threads. The last 
        // caller on any thread sets the handler. 
        // http://msdn.microsoft.com/en-us/library/t296ys27.aspx
        m_prevPurec = _set_purecall_handler(PureCallHandler);    
    }

    if(dwFlags&CR_INST_NEW_OPERATOR_ERROR_HANDLER)
    {
        // Catch new operator memory allocation exceptions
        _set_new_mode(1); // Force malloc() to call new handler too
        m_prevNewHandler = _set_new_handler(NewHandler);
    }
#endif

#if _MSC_VER>=1400
    if(dwFlags&CR_INST_INVALID_PARAMETER_HANDLER)
    {
        // Catch invalid parameter exceptions.
        m_prevInvpar = _set_invalid_parameter_handler(InvalidParameterHandler); 
    }
#endif


#if _MSC_VER>=1300 && _MSC_VER<1400    
    if(dwFlags&CR_INST_SECURITY_ERROR_HANDLER)
    {
        // Catch buffer overrun exceptions
        // The _set_security_error_handler is deprecated in VC8 C++ run time library
        m_prevSec = _set_security_error_handler(SecurityHandler);
    }
#endif

    // Set up C++ signal handlers


    if(dwFlags&CR_INST_SIGABRT_HANDLER)
    {
#if _MSC_VER>=1400  
        _set_abort_behavior(_CALL_REPORTFAULT, _CALL_REPORTFAULT);
#endif
        // Catch an abnormal program termination
        m_prevSigABRT = signal(SIGABRT, SigabrtHandler);  
    }

    if(dwFlags&CR_INST_SIGINT_HANDLER)
    {
        // Catch illegal instruction handler
        m_prevSigINT = signal(SIGINT, SigintHandler);     
    }

    if(dwFlags&CR_INST_TERMINATE_HANDLER)
    {
        // Catch a termination request
        m_prevSigTERM = signal(SIGTERM, SigtermHandler);          
    }

    crSetErrorMsg(_T("Success."));
    return 0;
}

// Unsets exception pointers that work on per-process basis
int CCrashHandler::UnSetProcessExceptionHandlers()
{
    crSetErrorMsg(_T("Unspecified error."));

    // Unset all previously set handlers

#if _MSC_VER>=1300
    if(m_prevPurec!=NULL)
        _set_purecall_handler(m_prevPurec);

    if(m_prevNewHandler!=NULL)
        _set_new_handler(m_prevNewHandler);
#endif

#if _MSC_VER>=1400
    if(m_prevInvpar!=NULL)
        _set_invalid_parameter_handler(m_prevInvpar);
#endif //_MSC_VER>=1400  

#if _MSC_VER>=1300 && _MSC_VER<1400    
    if(m_prevSec!=NULL)
        _set_security_error_handler(m_prevSec);
#endif //_MSC_VER<1400

    if(m_prevSigABRT!=NULL)
        signal(SIGABRT, m_prevSigABRT);  

    if(m_prevSigINT!=NULL)
        signal(SIGINT, m_prevSigINT);     

    if(m_prevSigTERM!=NULL)
        signal(SIGTERM, m_prevSigTERM);    

    crSetErrorMsg(_T("Success."));
    return 0;
}

// Installs C++ exception handlers that function on per-thread basis
int CCrashHandler::SetThreadExceptionHandlers(DWORD dwFlags)
{
    crSetErrorMsg(_T("Unspecified error."));

    // If 0 is specified as dwFlags, assume all available exception handlers should be
    // installed  
    if((dwFlags&CR_INST_ALL_POSSIBLE_HANDLERS)==0)
        dwFlags |= CR_INST_ALL_POSSIBLE_HANDLERS;

	// Get current thread ID.
    DWORD dwThreadId = GetCurrentThreadId();

	// Lock the critical section.
    CAutoLock lock(&m_csThreadExceptionHandlers);

	// Try and find our thread ID in the list of threads.
    std::map<DWORD, ThreadExceptionHandlers>::iterator it = 
        m_ThreadExceptionHandlers.find(dwThreadId);

    if(it!=m_ThreadExceptionHandlers.end())
    {
        // handlers are already set for the thread    
        crSetErrorMsg(_T("Can't install handlers for current thread twice."));
        return 1; // failed
    }

    ThreadExceptionHandlers handlers;

    if(dwFlags&CR_INST_TERMINATE_HANDLER)
    {
        // Catch terminate() calls. 
        // In a multithreaded environment, terminate functions are maintained 
        // separately for each thread. Each new thread needs to install its own 
        // terminate function. Thus, each thread is in charge of its own termination handling.
        // http://msdn.microsoft.com/en-us/library/t6fk7h29.aspx
        handlers.m_prevTerm = set_terminate(TerminateHandler);       
    }

    if(dwFlags&CR_INST_UNEXPECTED_HANDLER)
    {
        // Catch unexpected() calls.
        // In a multithreaded environment, unexpected functions are maintained 
        // separately for each thread. Each new thread needs to install its own 
        // unexpected function. Thus, each thread is in charge of its own unexpected handling.
        // http://msdn.microsoft.com/en-us/library/h46t5b69.aspx  
        handlers.m_prevUnexp = set_unexpected(UnexpectedHandler);    
    }

    if(dwFlags&CR_INST_SIGFPE_HANDLER)
    {
        // Catch a floating point error
        typedef void (*sigh)(int);
        handlers.m_prevSigFPE = signal(SIGFPE, (sigh)SigfpeHandler);     
    }


    if(dwFlags&CR_INST_SIGILL_HANDLER)
    {
        // Catch an illegal instruction
        handlers.m_prevSigILL = signal(SIGILL, SigillHandler);     
    }

    if(dwFlags&CR_INST_SIGSEGV_HANDLER)
    {
        // Catch illegal storage access errors
        handlers.m_prevSigSEGV = signal(SIGSEGV, SigsegvHandler);   
    }

    // Insert the structure to the list of handlers  
    m_ThreadExceptionHandlers[dwThreadId] = handlers;

    // OK.
    crSetErrorMsg(_T("Success."));
    return 0;
}

// Unsets exception handlers for the current thread
int CCrashHandler::UnSetThreadExceptionHandlers()
{
    crSetErrorMsg(_T("Unspecified error."));

    DWORD dwThreadId = GetCurrentThreadId();

    CAutoLock lock(&m_csThreadExceptionHandlers);

    std::map<DWORD, ThreadExceptionHandlers>::iterator it = 
        m_ThreadExceptionHandlers.find(dwThreadId);

    if(it==m_ThreadExceptionHandlers.end())
    {
        // No exception handlers were installed for the caller thread?    
        crSetErrorMsg(_T("Crash handler wasn't previously installed for current thread."));
        return 1;
    }

    ThreadExceptionHandlers* handlers = &(it->second);

    if(handlers->m_prevTerm!=NULL)
        set_terminate(handlers->m_prevTerm);

    if(handlers->m_prevUnexp!=NULL)
        set_unexpected(handlers->m_prevUnexp);

    if(handlers->m_prevSigFPE!=NULL)
        signal(SIGFPE, handlers->m_prevSigFPE);     

    if(handlers->m_prevSigILL!=NULL)
        signal(SIGINT, handlers->m_prevSigILL);     

    if(handlers->m_prevSigSEGV!=NULL)
        signal(SIGSEGV, handlers->m_prevSigSEGV); 

    // Remove from the list
    m_ThreadExceptionHandlers.erase(it);

    // OK.
    crSetErrorMsg(_T("Success."));
    return 0;
}

// Adds a file item to the error report
int CCrashHandler::AddFile(LPCTSTR pszFile, LPCTSTR pszDestFile, LPCTSTR pszDesc, DWORD dwFlags)
{
    crSetErrorMsg(_T("Unspecified error."));

	// Check if source file name or search pattern is specified
	if(pszFile==NULL)
	{
		crSetErrorMsg(_T("Invalid file name specified."));
        return 1; 
	}

    // Check that the destination file name is valid
    if(pszDestFile!=NULL)
    {
        CString sDestFile = pszDestFile;
        sDestFile.TrimLeft();
        sDestFile.TrimRight();
        if(sDestFile.GetLength()==0)
        {
            crSetErrorMsg(_T("Invalid destination file name specified."));
            return 1; 
        }
    }

	// Check if pszFile is a search pattern or not
	BOOL bPattern = Utility::IsFileSearchPattern(pszFile);

	if(!bPattern) // Usual file name
	{
		// Make sure the file exists
		DWORD dwAttrs = GetFileAttributes(pszFile);

		BOOL bIsFile = dwAttrs!=INVALID_FILE_ATTRIBUTES && (dwAttrs&FILE_ATTRIBUTE_DIRECTORY)==0;

		if (!bIsFile && (dwFlags&CR_AF_MISSING_FILE_OK)==0)
		{    
			crSetErrorMsg(_T("The file does not exists or not a regular file."));
			return 1;
		}

		// Add file to file list.
		FileItem fi;
		fi.m_sDescription = pszDesc;
		fi.m_sSrcFilePath = pszFile;
		fi.m_bMakeCopy = (dwFlags&CR_AF_MAKE_FILE_COPY)!=0;
		fi.m_bAllowDelete = (dwFlags&CR_AF_ALLOW_DELETE)!=0;
		if(pszDestFile!=NULL)
		{
			fi.m_sDstFileName = pszDestFile;        
		}
		else
		{
			CString sDestFile = pszFile;
			int pos = -1;
			sDestFile.Replace('/', '\\');
			pos = sDestFile.ReverseFind('\\');
			if(pos!=-1)
				sDestFile = sDestFile.Mid(pos+1);

			fi.m_sDstFileName = sDestFile;        
		}

		// Check if file is already in our list
		std::map<CString, FileItem>::iterator it = m_files.find(fi.m_sDstFileName);
		if(it!=m_files.end())
		{
			crSetErrorMsg(_T("A file with such a destination name already exists."));
			return 1;
		}

		m_files[fi.m_sDstFileName] = fi;

		// Pack this file item into shared mem.
		PackFileItem(fi);
	}
	else // Search pattern
	{			
		// Add file search pattern to file list.
		FileItem fi;
		fi.m_sDescription = pszDesc;
		fi.m_sSrcFilePath = pszFile;
		fi.m_sDstFileName = Utility::GetFileName(pszFile);
		fi.m_bMakeCopy = (dwFlags&CR_AF_MAKE_FILE_COPY)!=0;
		fi.m_bAllowDelete = (dwFlags&CR_AF_ALLOW_DELETE)!=0;		
		m_files[fi.m_sDstFileName] = fi;

		// Pack this file item into shared mem.
		PackFileItem(fi);
	}	 

    // OK.
    crSetErrorMsg(_T("Success."));
    return 0;
}

// Adds a custom property to the error report
int CCrashHandler::AddProperty(CString sPropName, CString sPropValue)
{
    crSetErrorMsg(_T("Unspecified error."));

    if(sPropName.IsEmpty())
    {
        crSetErrorMsg(_T("Invalid property name specified."));
        return 1;
    }

    m_props[sPropName] = sPropValue;

    PackProperty(sPropName, sPropValue);

    // OK.
    crSetErrorMsg(_T("Success."));
    return 0;
}

// Adds a screen shot to the error report
int CCrashHandler::AddScreenshot(DWORD dwFlags, int nJpegQuality)
{ 
    crSetErrorMsg(_T("Unspecified error."));

    if(nJpegQuality<0 || nJpegQuality>100)
    {
        crSetErrorMsg(_T("Invalid Jpeg quality."));
        return 1;
    }

    m_bAddScreenshot = TRUE;
    m_dwScreenshotFlags = dwFlags;
    m_nJpegQuality = nJpegQuality;

    // Pack this info into shared memory
    m_pCrashDesc->m_bAddScreenshot = TRUE;
    m_pCrashDesc->m_dwScreenshotFlags = dwFlags;
    m_pCrashDesc->m_nJpegQuality = nJpegQuality;

    crSetErrorMsg(_T("Success."));
    return 0;
}

// Adds a video recording of desktop state just before crash.
int CCrashHandler::AddVideo(DWORD dwFlags, int nDuration, int nFrameInterval, 
	SIZE* pDesiredFrameSize, HWND hWndParent)
{
	// Check duration - it should be less than 10 minutes
	if(nDuration<0 || nDuration>10*60*1000)
	{
		crSetErrorMsg(_T("Invalid video duration."));
		return 2;
	}
		
	// If not specified, set default
	if(nDuration==0)
	{
		// Default duration - 1 min
		nDuration = 60*1000;
	}

	// Check frame interval
	if(nFrameInterval<0 || nFrameInterval>nDuration)
	{
		crSetErrorMsg(_T("Invalid frame interval."));
        return 3;
	}

	// If not specified, set default
	if(nFrameInterval==0)
	{
		// Default frame interval - 500 msec
		nFrameInterval = 500;
	}

	// Check if we already have a video recording enabled.
	if(m_bAddVideo==TRUE)
	{
        crSetErrorMsg(_T("Can not add video recording twice."));
        return 4;
	}

	// Save video recording parameters
	m_bAddVideo = TRUE;
    m_dwVideoFlags = dwFlags;
	m_nVideoDuration = nDuration;
	m_nVideoFrameInterval = nFrameInterval;
	if(pDesiredFrameSize)
		m_DesiredFrameSize = *pDesiredFrameSize;
	else
	{
		m_DesiredFrameSize.cx = 0;
	}

	// Determine parent window for our notification dialog.
	if(hWndParent!=NULL)
		m_hWndVideoParent = hWndParent;
	else
		m_hWndVideoParent = GetActiveWindow();

	// Pack this info into shared memory
    m_pTmpCrashDesc->m_bAddVideo = TRUE;
    m_pTmpCrashDesc->m_dwVideoFlags = dwFlags;
	m_pTmpCrashDesc->m_nVideoDuration = nDuration;
	m_pTmpCrashDesc->m_nVideoFrameInterval = nFrameInterval;
    m_pTmpCrashDesc->m_DesiredFrameSize = m_DesiredFrameSize;
	m_pTmpCrashDesc->m_hWndVideoParent = m_hWndVideoParent;
	
	// Create sync event (we will use it for synchronizing with CrashSender.exe).
	CString sEventName;
    sEventName.Format(_T("Local\\CrashRptEvent_%s_2"), m_sCrashGUID);
    m_hEvent2 = CreateEvent(NULL, FALSE, FALSE, sEventName);
    if(m_hEvent2==NULL)
    {
        crSetErrorMsg(_T("Couldn't create synchronization event."));
        return 5; 
    }

	// Launch the CrashSender.exe process that will continuously record video 
	// in background.    
    if(0!=LaunchCrashSender(m_SharedMem.GetName(), FALSE, &m_hSenderProcess))
    {
		crSetErrorMsg(_T("Couldn't launch CrashSender.exe process."));
        return 6;
    }

	// OK
	crSetErrorMsg(_T("Success."));
	return 0;
}

void CCrashHandler::FillLoadedModulesInfo( BYTE * CrashAddress )
{
  struct SModuleEnum : public Utility::IModuleEnumCallback
  {
    BYTE * address;
    std::map<CString, ModuleItem>& modules;
    /*
    CString strCrashedModule;
    size_t relativeAddress;
    */
    
    SModuleEnum( BYTE * _address, std::map<CString, ModuleItem>& _modules ) : 
      address( _address ), modules(_modules) {}

    virtual bool EnumModule( HMODULE, TCHAR * pszModuleName, TCHAR * pszModuleFullPath, BYTE * codeStart, BYTE * codeEnd )
    {
      UNREFERENCED_PARAMETER(pszModuleName);

      if (!pszModuleFullPath)
        return false;

      strconv_t strconv;
      ModuleItem item;
      item.m_sModulePath = pszModuleFullPath;
      item.codeStart = (size_t)codeStart;
      item.codeEnd = (size_t)codeEnd;

      modules[item.m_sModulePath] = item;
      return true;
    }
  };


  SModuleEnum modEnum( CrashAddress, m_modules );
  EnumModules( &modEnum );
}

// Generates error report
int CCrashHandler::GenerateErrorReport(
        PCR_EXCEPTION_INFO pExceptionInfo)
{  
    crSetErrorMsg(_T("Unspecified error."));

    EXCEPTION_RECORD ExceptionRecord;
    EXCEPTION_POINTERS ExceptionPointers;

	// Allocate memory in stack for storing exception pointers.
	  CONTEXT ContextRecord;    
    ExceptionPointers.ExceptionRecord = &ExceptionRecord;
    ExceptionPointers.ContextRecord = &ContextRecord;  

    // Validate input parameters 
    if(pExceptionInfo==NULL)
    {
        crSetErrorMsg(_T("Exception info is NULL."));
        return 1;
    }

    // Get exception pointers if they were not provided by the caller. 
    if(pExceptionInfo->pexcptrs==NULL)
    {
        GetExceptionPointers(pExceptionInfo->code, &ExceptionPointers);
		    pExceptionInfo->pexcptrs = &ExceptionPointers;
    }

    if (pExceptionInfo->pexcptrs)
    {
      ATLASSERT(pExceptionInfo->pexcptrs->ExceptionRecord);
      ATLASSERT(pExceptionInfo->pexcptrs->ExceptionRecord->ExceptionAddress);
      FillLoadedModulesInfo((BYTE *)pExceptionInfo->pexcptrs->ExceptionRecord->ExceptionAddress);

      // Pack file items
      std::map<CString, ModuleItem>::iterator mit;
      for(mit=m_modules.begin(); mit!=m_modules.end(); mit++)
      {
        ModuleItem& mi = mit->second;

        // Pack this file item into shared mem.
        PackModuleItem(mi);
      }
    }
		
	// If error report is being generated manually, 
	// temporarily disable app restart feature.
    if(pExceptionInfo->bManual)
	{		
		// Force disable app restart.
        m_pCrashDesc->m_dwInstallFlags &= ~CR_INST_APP_RESTART;
	}

	// Set "client app crashed" flag.
	m_pCrashDesc->m_bClientAppCrashed = TRUE;
	
	// Reset "add video" flag (to ensure CrashSender.exe won't start video recording loop the second time).
	m_pCrashDesc->m_bAddVideo = FALSE;
    
	// Save current process ID, thread ID and exception pointers address to shared mem.
    m_pCrashDesc->m_dwProcessId = GetCurrentProcessId();
    m_pCrashDesc->m_dwThreadId = GetCurrentThreadId();
    m_pCrashDesc->m_pExceptionPtrs = pExceptionInfo->pexcptrs;  
    m_pCrashDesc->m_bSendRecentReports = FALSE;
    m_pCrashDesc->m_nExceptionType = pExceptionInfo->exctype;

    if(pExceptionInfo->exctype==CR_SEH_EXCEPTION)
    {
		// Set SEH exception code
        m_pCrashDesc->m_dwExceptionCode = pExceptionInfo->code;
    }
    else if(pExceptionInfo->exctype==CR_CPP_SIGFPE)
    {
		// Set FPE (floating point exception) subcode
        m_pCrashDesc->m_uFPESubcode = pExceptionInfo->fpe_subcode;
    }
    else if(pExceptionInfo->exctype==CR_CPP_INVALID_PARAMETER)
    {
		// Set invalid parameter exception info fields
        m_pCrashDesc->m_dwInvParamExprOffs = PackString(pExceptionInfo->expression);
        m_pCrashDesc->m_dwInvParamFunctionOffs = PackString(pExceptionInfo->function);
        m_pCrashDesc->m_dwInvParamFileOffs = PackString(pExceptionInfo->file);
        m_pCrashDesc->m_uInvParamLine = pExceptionInfo->line;
    }
	    
    // Let client know about the crash via the crash callback function. 
    //if (m_lpfnCallback!=NULL && m_lpfnCallback(NULL)==FALSE)
    if (m_lpfnCallback!=NULL && m_lpfnCallback(pExceptionInfo->pexcptrs, NULL)==FALSE)
    {
		  // User has canceled error report generation!

		  // Prepare for the next crash
		  PerCrashInit();

        crSetErrorMsg(_T("The operation was cancelled by client."));
        return 2;
    }

	  // New-style callback
	  if(CR_CB_CANCEL==CallBack(CR_CB_STAGE_PREPARE, pExceptionInfo))
	  {
		  // User has canceled error report generation!

		  // Prepare for the next crash
		  PerCrashInit();

      crSetErrorMsg(_T("The operation was cancelled by client."));
      return 2;
    }	

    // Start the CrashSender.exe process which will take the dekstop screenshot, 
    // copy user-specified files to the error report folder, create minidump, 
    // notify user about crash, compress the report into ZIP archive and send 
    // the error report. 

    int result = 0; // result of launching CrashSender.exe
	
	// If we are not recording video or video recording process has been terminated by some reason...
	if(!m_bAddVideo || (m_bAddVideo && !IsSenderProcessAlive())) 
	{
		// Run new CrashSender.exe process
		result = LaunchCrashSender(m_sCrashGUID, TRUE, &pExceptionInfo->hSenderProcess);
	}
	else // we are recording video
	{		
		// The CrashSender.exe process is already launched by the AddVideo method.
		// We need to signal the event to make CrashSender.exe generate error report.
		SetEvent(m_hEvent2);
		
		// Wait until CrashSender finishes with making screenshot, 
        // copying files, creating minidump and encoding recorded video. 
        WaitForSingleObject(m_hEvent, INFINITE);

		// Free sync event (it is not needed since now).
		CloseHandle(m_hEvent2);
		m_hEvent2 = NULL;
		
		// Return handle to CrashSender.exe process to the caller.		
		pExceptionInfo->hSenderProcess = m_hSenderProcess;
	}
    
	// New-style callback. Notify client about the second stage 
	// (CR_CB_STAGE_FINISH) of crash report generation.
	CallBack(CR_CB_STAGE_FINISH, pExceptionInfo);
	
	// Check if the client program requests to continue its execution
	// after crash.
	if(m_bContinueExecution)
	{
		// Prepare for the next crash
		PerCrashInit();

		if(m_bAddVideo)
		{
			// Relaunch video recording loop for the next crash.
			// Avoid displaying video notification dialog (as the user already has 
			// approved video recording).
			m_bAddVideo = FALSE;
			AddVideo(m_dwVideoFlags|CR_AV_NO_GUI, m_nVideoDuration, m_nVideoFrameInterval, 
				&m_DesiredFrameSize, m_hWndVideoParent);
		}
	}

	// Check the result of launching the crash sender process.
	if(result!=0)
    {
        ATLASSERT(result==0);
        crSetErrorMsg(_T("Error launching CrashSender.exe"));

        // Failed to launch crash sender process.
        // Try notifying user about crash using message box.
        CString szCaption;
        szCaption.Format(_T("%s has stopped working"), Utility::getAppName());
        CString szMessage;
        szMessage.Format(_T("Error launching CrashSender.exe"));
        MessageBox(NULL, szMessage, szCaption, MB_OK|MB_ICONERROR);    
        return 3;
    }
		
    // OK
    crSetErrorMsg(_T("Success."));
    return 0; 
}

BOOL CCrashHandler::IsSenderProcessAlive()
{
	// If process handle is still accessible, check its exit code
	DWORD dwExitCode = 1;
	BOOL bRes = GetExitCodeProcess(m_hSenderProcess, &dwExitCode);
	if(!bRes || (bRes && dwExitCode!=STILL_ACTIVE))
	{
		return FALSE; // Process seems to exit!
	}

	return TRUE;
}

// Adds a registry key dump to the error report
int CCrashHandler::AddRegKey(LPCTSTR szRegKey, LPCTSTR szDstFileName, DWORD dwFlags)
{
    crSetErrorMsg(_T("Unspecified error."));

    if(szDstFileName==NULL ||
        szRegKey==NULL)
    {
        // Invalid param
        crSetErrorMsg(_T("Invalid registry key or invalid destination file is specified."));
        return 1;
    }

    CString sDstFileName = CString(szDstFileName);
    if(sDstFileName.Find(_T("\\"))>=0 ||
        sDstFileName.Find(_T("\r"))>=0 ||
        sDstFileName.Find(_T("\n"))>=0 ||
        sDstFileName.Find(_T("\t"))>=0)
    {
        // Inacceptable character found.
        return 1;
    }

    HKEY hKey = NULL;
    CString sKey = szRegKey;  
    int nSkip = 0;
    if(sKey.Left(19).Compare(_T("HKEY_LOCAL_MACHINE\\"))==0)
    {
        hKey = HKEY_LOCAL_MACHINE;
        nSkip = 18;
    }
    else if(sKey.Left(18).Compare(_T("HKEY_CURRENT_USER\\"))==0)
    {
        hKey = HKEY_CURRENT_USER;
        nSkip = 17;
    }    
    else 
    {
        crSetErrorMsg(_T("Invalid registry branch is specified."));
        return 1; // Invalid key.
    }

    CString sSubKey = sKey.Mid(nSkip+1);  
    if(sSubKey.IsEmpty())
    {
        crSetErrorMsg(_T("Empty subkey is not allowed."));
        return 2; // Empty subkey not allowed
    }

    HKEY hKeyResult = NULL;
    LRESULT lResult = RegOpenKeyEx(hKey, sSubKey, 0, KEY_READ, &hKeyResult);
    if(lResult!=ERROR_SUCCESS)
    {
        crSetErrorMsg(_T("The registry key coudn't be open."));
        return 3; // Invalid key.
    }
    RegCloseKey(hKeyResult);

	RegKeyInfo rki;
	rki.m_sDstFileName = sDstFileName;
	rki.m_bAllowDelete = (dwFlags&CR_AR_ALLOW_DELETE)!=0;

    m_RegKeys[CString(szRegKey)] = rki;

    PackRegKey(szRegKey, rki);

    // OK
    crSetErrorMsg(_T("Success."));
    return 0;
}

// The following code gets exception pointers using a workaround found in CRT code.
void CCrashHandler::GetExceptionPointers(DWORD dwExceptionCode, 
                                         EXCEPTION_POINTERS* pExceptionPointers)
{
    // The following code was taken from VC++ 8.0 CRT (invarg.c: line 104)

	CONTEXT ContextRecord;
    memset(&ContextRecord, 0, sizeof(CONTEXT));

#ifdef _X86_

    __asm {
            mov dword ptr [ContextRecord.Eax], eax
            mov dword ptr [ContextRecord.Ecx], ecx
            mov dword ptr [ContextRecord.Edx], edx
            mov dword ptr [ContextRecord.Ebx], ebx
            mov dword ptr [ContextRecord.Esi], esi
            mov dword ptr [ContextRecord.Edi], edi
            mov word ptr [ContextRecord.SegSs], ss
            mov word ptr [ContextRecord.SegCs], cs
            mov word ptr [ContextRecord.SegDs], ds
            mov word ptr [ContextRecord.SegEs], es
            mov word ptr [ContextRecord.SegFs], fs
            mov word ptr [ContextRecord.SegGs], gs
            pushfd
            pop [ContextRecord.EFlags]
    }

    ContextRecord.ContextFlags = CONTEXT_CONTROL;
#pragma warning(push)
#pragma warning(disable:4311)
    ContextRecord.Eip = (ULONG)_ReturnAddress();
    ContextRecord.Esp = (ULONG)_AddressOfReturnAddress();
#pragma warning(pop)
    ContextRecord.Ebp = *((ULONG *)_AddressOfReturnAddress()-1);
	
#elif defined (_IA64_) || defined (_AMD64_)

    /* Need to fill up the Context in IA64 and AMD64. */
    RtlCaptureContext(&ContextRecord);

#else  /* defined (_IA64_) || defined (_AMD64_) */

    ZeroMemory(&ContextRecord, sizeof(ContextRecord));

#endif  /* defined (_IA64_) || defined (_AMD64_) */

	memcpy(pExceptionPointers->ContextRecord, &ContextRecord, sizeof(CONTEXT));

	ZeroMemory(pExceptionPointers->ExceptionRecord, sizeof(EXCEPTION_RECORD));

    pExceptionPointers->ExceptionRecord->ExceptionCode = dwExceptionCode;
    pExceptionPointers->ExceptionRecord->ExceptionAddress = _ReturnAddress();    
}

// Launches CrashSender.exe process
int CCrashHandler::LaunchCrashSender(LPCTSTR szCmdLineParams, BOOL bWait, HANDLE* phProcess)
{
    crSetErrorMsg(_T("Unspecified error."));

    /* Create CrashSender.exe process */

    STARTUPINFO si;
    memset(&si, 0, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    PROCESS_INFORMATION pi;
    memset(&pi, 0, sizeof(PROCESS_INFORMATION));    

	// Format command line
    TCHAR szCmdLine[_MAX_PATH]=_T("");
	_tcscat_s(szCmdLine, _MAX_PATH, _T("\""));
	_tcscat_s(szCmdLine, _MAX_PATH, m_sPathToCrashSender.GetBuffer(0));
	_tcscat_s(szCmdLine, _MAX_PATH, _T("\" \""));    
	_tcscat_s(szCmdLine, _MAX_PATH, szCmdLineParams);
	_tcscat_s(szCmdLine, _MAX_PATH, _T("\""));    

    BOOL bCreateProcess = CreateProcess(
        m_sPathToCrashSender, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    if(pi.hThread)
    {
        CloseHandle(pi.hThread);
        pi.hThread = NULL;
    }
    if(!bCreateProcess)
    {
        ATLASSERT(bCreateProcess);
        crSetErrorMsg(_T("Error creating CrashSender process."));
        return 1;
    }

    if(bWait)
    {
        /* Wait until CrashSender finishes with making screenshot, 
        copying files, creating minidump. */  

        WaitForSingleObject(m_hEvent, INFINITE);  
    }

    // Return handle to the CrashSender.exe process.    
    if(phProcess!=NULL)
    {
        *phProcess = pi.hProcess;
    }
    else
    {
        // Handle not required by caller so close it.
        CloseHandle( pi.hProcess );
        pi.hProcess = NULL;
    }

	// Done
	crSetErrorMsg(_T("Success."));
    return 0;
}

// Acquires the crash lock. Other threads that may crash while we are 
// inside of a crash handler function, will wait until we unlock.
void CCrashHandler::CrashLock(BOOL bLock)
{
    if(bLock)
        m_csCrashLock.Lock();
    else
        m_csCrashLock.Unlock();
}

int CCrashHandler::PerCrashInit()
{
	// This method performs per-crash initialization actions.
	// For example, we have to generate a new GUID string and repack 
	// configuration info into shared memory each time.

	// Consider the next crash as non-critical.
	m_bContinueExecution = TRUE;

	// Set default ret code for callback func.	
	m_nCallbackRetCode = CR_CB_NOTIFY_NEXT_STAGE;

	// Reset video flag to let user add new videos.
	//m_bAddVideo = FALSE;

	// Generate new GUID for new crash report 
	// (if, for example, user will generate new error report manually).
    Utility::GenerateGUID(m_sCrashGUID);
    
	// Recreate the event that will be used to synchronize with CrashSender.exe process.
	if(m_hEvent!=NULL)
		CloseHandle(m_hEvent); // Free old event
    CString sEventName;
    sEventName.Format(_T("Local\\CrashRptEvent_%s"), m_sCrashGUID);
    m_hEvent = CreateEvent(NULL, FALSE, FALSE, sEventName);
    
	// Format error report dir name for the next crash report.
	CString sErrorReportDirName;
	sErrorReportDirName.Format(_T("%s\\%s_%s\\%s"), 
		m_sUnsentCrashReportsFolder.GetBuffer(0),
		m_sAppName.GetBuffer(0),
		m_sAppVersion.GetBuffer(0),
		m_sCrashGUID.GetBuffer(0)
		);

	// Convert it to wide-char and multi-byte charsets.
	strconv_t strconv;
	m_sErrorReportDirW = strconv.t2w(sErrorReportDirName);
	m_sErrorReportDirA = strconv.t2a(sErrorReportDirName);

	// Reset shared memory
	if(m_SharedMem.IsInitialized())
	{
		m_SharedMem.Destroy();
		m_pCrashDesc = NULL;
	}

	// Pack configuration info into shared memory.
    // It will be passed to CrashSender.exe later.
    m_pCrashDesc = PackCrashInfoIntoSharedMem(&m_SharedMem, FALSE);
	
	// OK
	return 0;
}

int CCrashHandler::CallBack(int nStage, CR_EXCEPTION_INFO* pExInfo)
{	
	// This method calls the new-style crash callback function.
	// The client (calee) is able to either permit crash report generation (return CR_CB_DODEFAULT)
	// or prevent it (return CR_CB_CANCEL).

	strconv_t strconv;

	if(m_nCallbackRetCode!=CR_CB_NOTIFY_NEXT_STAGE)
		return CR_CB_DODEFAULT;
	
	if(m_pfnCallback2W!=NULL)
	{
		// Call the wide-char version of the callback function.

		// Prepare callback info structure
		CR_CRASH_CALLBACK_INFOW cci;
		memset(&cci, 0, sizeof(CR_CRASH_CALLBACK_INFOW));
		cci.cb = sizeof(CR_CRASH_CALLBACK_INFOW);
		cci.nStage = nStage;
		cci.pExceptionInfo = pExInfo;
		cci.pUserParam = m_pCallbackParam;
		cci.pszErrorReportFolder = m_sErrorReportDirW.c_str();
		cci.bContinueExecution = m_bContinueExecution;
		// Call the function and get the ret code
		m_nCallbackRetCode = m_pfnCallback2W(&cci);

		// Save continue execution flag
		m_bContinueExecution = cci.bContinueExecution;
	}
	else if(m_pfnCallback2A!=NULL)
	{
		// Call the multi-byte version of the callback function.

		// Prepare callback info structure
		CR_CRASH_CALLBACK_INFOA cci;
		memset(&cci, 0, sizeof(CR_CRASH_CALLBACK_INFOA));
		cci.cb = sizeof(CR_CRASH_CALLBACK_INFOA);
		cci.nStage = nStage;
		cci.pExceptionInfo = pExInfo;
		cci.pUserParam = m_pCallbackParam;
		cci.pszErrorReportFolder = m_sErrorReportDirA.c_str();
		cci.bContinueExecution = m_bContinueExecution;
		// Call the function and get the ret code
		m_nCallbackRetCode = m_pfnCallback2A(&cci);

		// Save continue execution flag
		m_bContinueExecution = cci.bContinueExecution;
	}

	return m_nCallbackRetCode;
}

// Structured exception handler (SEH)
LONG WINAPI CCrashHandler::SehHandler(PEXCEPTION_POINTERS pExceptionPtrs)
{ 
    CCrashHandler* pCrashHandler = CCrashHandler::GetCurrentProcessCrashHandler();
    ATLASSERT(pCrashHandler!=NULL);  

	// Handle stack overflow in a separate thread.
	// Vojtech: Based on martin.bis...@gmail.com comment in
	//	http://groups.google.com/group/crashrpt/browse_thread/thread/a1dbcc56acb58b27/fbd0151dd8e26daf?lnk=gst&q=stack+overflow#fbd0151dd8e26daf
	if (pExceptionPtrs != 0 && pExceptionPtrs->ExceptionRecord != 0 &&
		pExceptionPtrs->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW) 
	{
		// Special case to handle the stack overflow exception.
		// The dump will be realized from another thread.
		// Create another thread that will do the dump.
		HANDLE thread = ::CreateThread(0, 0,
			&StackOverflowThreadFunction, pExceptionPtrs, 0, 0);
		::WaitForSingleObject(thread, INFINITE);
		::CloseHandle(thread);
		// Terminate process
		TerminateProcess(GetCurrentProcess(), 1);
	}

	if(pCrashHandler!=NULL)
	{
		// Acquire lock to avoid other threads (if exist) to crash while we are 
		// inside. 
		pCrashHandler->CrashLock(TRUE);

		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

		// Generate error report.
		CR_EXCEPTION_INFO ei;
		memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
		ei.cb = sizeof(CR_EXCEPTION_INFO);
		ei.exctype = CR_SEH_EXCEPTION;
		ei.pexcptrs = pExceptionPtrs;
		pCrashHandler->GenerateErrorReport(&ei);

		if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE);
	}   

    // Unreacheable code  
    return EXCEPTION_EXECUTE_HANDLER;
}

//Vojtech: Based on martin.bis...@gmail.com comment in
// http://groups.google.com/group/crashrpt/browse_thread/thread/a1dbcc56acb58b27/fbd0151dd8e26daf?lnk=gst&q=stack+overflow#fbd0151dd8e26daf
// Thread procedure doing the dump for stack overflow.
DWORD WINAPI CCrashHandler::StackOverflowThreadFunction(LPVOID lpParameter)
{
	PEXCEPTION_POINTERS pExceptionPtrs =
		reinterpret_cast<PEXCEPTION_POINTERS>(lpParameter);
	
	CCrashHandler *pCrashHandler =
		CCrashHandler::GetCurrentProcessCrashHandler();
	ATLASSERT(pCrashHandler != NULL);

	if (pCrashHandler != NULL) 
	{
		// Acquire lock to avoid other threads (if exist) to crash while we	are inside.
		pCrashHandler->CrashLock(TRUE);
		
		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

		// Generate error report.
		CR_EXCEPTION_INFO ei;
		memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
		ei.cb = sizeof(CR_EXCEPTION_INFO);
		ei.exctype = CR_SEH_EXCEPTION;
		ei.pexcptrs = pExceptionPtrs;
		pCrashHandler->GenerateErrorReport(&ei);
		
		if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE);
	}

	return 0;
}

// CRT terminate() call handler
void __cdecl CCrashHandler::TerminateHandler()
{
    // Abnormal program termination (terminate() function was called)

    CCrashHandler* pCrashHandler = CCrashHandler::GetCurrentProcessCrashHandler();
    ATLASSERT(pCrashHandler!=NULL);

    if(pCrashHandler!=NULL)
    {
        // Acquire lock to avoid other threads (if exist) to crash while we are 
        // inside. We do not unlock, because process is to be terminated.
        pCrashHandler->CrashLock(TRUE);

		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

        // Fill in the exception info
        CR_EXCEPTION_INFO ei;
        memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
        ei.cb = sizeof(CR_EXCEPTION_INFO);
        ei.exctype = CR_CPP_TERMINATE_CALL;

		// Generate crash report
        pCrashHandler->GenerateErrorReport(&ei);

        if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE);   
    }    
}

// CRT unexpected() call handler
void __cdecl CCrashHandler::UnexpectedHandler()
{
    // Unexpected error (unexpected() function was called)

    CCrashHandler* pCrashHandler = CCrashHandler::GetCurrentProcessCrashHandler();
    ATLASSERT(pCrashHandler!=NULL);

    if(pCrashHandler!=NULL)
    {
        // Acquire lock to avoid other threads (if exist) to crash while we are 
        // inside. We do not unlock, because process is to be terminated.
        pCrashHandler->CrashLock(TRUE);

		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

        // Fill in the exception info
        CR_EXCEPTION_INFO ei;
        memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
        ei.cb = sizeof(CR_EXCEPTION_INFO);
        ei.exctype = CR_CPP_UNEXPECTED_CALL;

		// Generate crash report
        pCrashHandler->GenerateErrorReport(&ei);

        if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE);   
    }    
}

// CRT Pure virtual method call handler
#if _MSC_VER>=1300
void __cdecl CCrashHandler::PureCallHandler()
{
    // Pure virtual function call

    CCrashHandler* pCrashHandler = CCrashHandler::GetCurrentProcessCrashHandler();
    ATLASSERT(pCrashHandler!=NULL);

    if(pCrashHandler!=NULL)
    {
        // Acquire lock to avoid other threads (if exist) to crash while we are 
        // inside. We do not unlock, because process is to be terminated.
        pCrashHandler->CrashLock(TRUE);

		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

        // Fill in the exception info
        CR_EXCEPTION_INFO ei;
        memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
        ei.cb = sizeof(CR_EXCEPTION_INFO);
        ei.exctype = CR_CPP_PURE_CALL;

		// Generate error report.
        pCrashHandler->GenerateErrorReport(&ei);

        if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE);   
    }  
}
#endif

// CRT buffer overrun handler. Available in CRT 7.1 only
#if _MSC_VER>=1300 && _MSC_VER<1400
void __cdecl CCrashHandler::SecurityHandler(int code, void *x)
{
    // Security error (buffer overrun).

    code;
    x;

    CCrashHandler* pCrashHandler = CCrashHandler::GetCurrentProcessCrashHandler();
    ATLASSERT(pCrashHandler!=NULL);

    if(pCrashHandler!=NULL)
    {    
        // Acquire lock to avoid other threads (if exist) to crash while we are 
        // inside. We do not unlock, because process is to be terminated.
        pCrashHandler->CrashLock(TRUE);

		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

        // Fill in the exception info
        CR_EXCEPTION_INFO ei;
        memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
        ei.cb = sizeof(CR_EXCEPTION_INFO);
        ei.exctype = CR_CPP_SECURITY_ERROR;

        pCrashHandler->GenerateErrorReport(&ei);

        if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE);
    }
}
#endif 

// CRT invalid parameter handler
#if _MSC_VER>=1400
void __cdecl CCrashHandler::InvalidParameterHandler(
    const wchar_t* expression, 
    const wchar_t* function, 
    const wchar_t* file, 
    unsigned int line, 
    uintptr_t pReserved)
{
    pReserved;

    // Invalid parameter exception

    CCrashHandler* pCrashHandler = CCrashHandler::GetCurrentProcessCrashHandler();
    ATLASSERT(pCrashHandler!=NULL);

    if(pCrashHandler!=NULL)
    {
        // Acquire lock to avoid other threads (if exist) to crash while we are 
        // inside. We do not unlock, because process is to be terminated.
        pCrashHandler->CrashLock(TRUE);

		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

        // Fill in the exception info
        CR_EXCEPTION_INFO ei;
        memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
        ei.cb = sizeof(CR_EXCEPTION_INFO);
        ei.exctype = CR_CPP_INVALID_PARAMETER;
        ei.expression = expression;
        ei.function = function;
        ei.file = file;
        ei.line = line;    

		// Generate error report.
        pCrashHandler->GenerateErrorReport(&ei);

        if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE);   
    }   
}
#endif

// CRT new operator fault handler
#if _MSC_VER>=1300
int __cdecl CCrashHandler::NewHandler(size_t)
{
    // 'new' operator memory allocation exception

    CCrashHandler* pCrashHandler = CCrashHandler::GetCurrentProcessCrashHandler();
    ATLASSERT(pCrashHandler!=NULL);

    if(pCrashHandler!=NULL)
    {     
        // Acquire lock to avoid other threads (if exist) to crash while we are 
        // inside. We do not unlock, because process is to be terminated.
        pCrashHandler->CrashLock(TRUE);

		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

        // Fill in the exception info
        CR_EXCEPTION_INFO ei;
        memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
        ei.cb = sizeof(CR_EXCEPTION_INFO);
        ei.exctype = CR_CPP_NEW_OPERATOR_ERROR;
        ei.pexcptrs = NULL;    

		// Generate error report.
        pCrashHandler->GenerateErrorReport(&ei);

        if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE);
    }

    // Unreacheable code
    return 0;
}
#endif //_MSC_VER>=1300

// CRT SIGABRT signal handler
void CCrashHandler::SigabrtHandler(int)
{
    // Caught SIGABRT C++ signal

    CCrashHandler* pCrashHandler = CCrashHandler::GetCurrentProcessCrashHandler();
    ATLASSERT(pCrashHandler!=NULL);

    if(pCrashHandler!=NULL)
    {     
        // Acquire lock to avoid other threads (if exist) to crash while we are 
        // inside. We do not unlock, because process is to be terminated.
        pCrashHandler->CrashLock(TRUE);

		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

        // Fill in the exception info
        CR_EXCEPTION_INFO ei;
        memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
        ei.cb = sizeof(CR_EXCEPTION_INFO);
        ei.exctype = CR_CPP_SIGABRT;    

        pCrashHandler->GenerateErrorReport(&ei);

        if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE); 
    }
}

// CRT SIGFPE signal handler
void CCrashHandler::SigfpeHandler(int /*code*/, int subcode)
{
    // Floating point exception (SIGFPE)

    CCrashHandler* pCrashHandler = CCrashHandler::GetCurrentProcessCrashHandler();
    ATLASSERT(pCrashHandler!=NULL);

    if(pCrashHandler!=NULL)
    {     
        // Acquire lock to avoid other threads (if exist) to crash while we are 
        // inside. We do not unlock, because process is to be terminated.
        pCrashHandler->CrashLock(TRUE);

		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

        // Fill in the exception info
        CR_EXCEPTION_INFO ei;
        memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
        ei.cb = sizeof(CR_EXCEPTION_INFO);
        ei.exctype = CR_CPP_SIGFPE;
        ei.pexcptrs = (PEXCEPTION_POINTERS)_pxcptinfoptrs;
        ei.fpe_subcode = subcode;

		//Generate crash report.
        pCrashHandler->GenerateErrorReport(&ei);

        if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE);
    }
}

// CRT sigill signal handler
void CCrashHandler::SigillHandler(int)
{
    // Illegal instruction (SIGILL)

    CCrashHandler* pCrashHandler = CCrashHandler::GetCurrentProcessCrashHandler();
    ATLASSERT(pCrashHandler!=NULL);

    if(pCrashHandler!=NULL)
    {    
        // Acquire lock to avoid other threads (if exist) to crash while we are 
        // inside. We do not unlock, because process is to be terminated.
        pCrashHandler->CrashLock(TRUE);

		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

        // Fill in the exception info
        CR_EXCEPTION_INFO ei;
        memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
        ei.cb = sizeof(CR_EXCEPTION_INFO);
        ei.exctype = CR_CPP_SIGILL;

		// Generate crash report
        pCrashHandler->GenerateErrorReport(&ei);

        if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE);    
    }
}

// CRT sigint signal handler
void CCrashHandler::SigintHandler(int)
{
    // Interruption (SIGINT)

    CCrashHandler* pCrashHandler = CCrashHandler::GetCurrentProcessCrashHandler();
    ATLASSERT(pCrashHandler!=NULL);

    if(pCrashHandler!=NULL)
    { 
        // Acquire lock to avoid other threads (if exist) to crash while we are 
        // inside. We do not unlock, because process is to be terminated.
        pCrashHandler->CrashLock(TRUE);

		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

        // Fill in the exception info
        CR_EXCEPTION_INFO ei;
        memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
        ei.cb = sizeof(CR_EXCEPTION_INFO);
        ei.exctype = CR_CPP_SIGINT;

		// Generate crash report.
        pCrashHandler->GenerateErrorReport(&ei);

        if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE);   
    }
}

// CRT SIGSEGV signal handler
void CCrashHandler::SigsegvHandler(int)
{
    // Invalid storage access (SIGSEGV)

    CCrashHandler* pCrashHandler = CCrashHandler::GetCurrentProcessCrashHandler();

    if(pCrashHandler!=NULL)
    {     
        // Acquire lock to avoid other threads (if exist) to crash while we are 
        // inside. We do not unlock, because process is to be terminated.
        pCrashHandler->CrashLock(TRUE);

		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

        // Fill in exception info
        CR_EXCEPTION_INFO ei;
        memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
        ei.cb = sizeof(CR_EXCEPTION_INFO);    
        ei.exctype = CR_CPP_SIGSEGV;
        ei.pexcptrs = (PEXCEPTION_POINTERS)_pxcptinfoptrs;

		// Generate crash report
        pCrashHandler->GenerateErrorReport(&ei);

        if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE);   
    }
}

// CRT SIGTERM signal handler
void CCrashHandler::SigtermHandler(int)
{
    // Termination request (SIGTERM)

    CCrashHandler* pCrashHandler = CCrashHandler::GetCurrentProcessCrashHandler();
    ATLASSERT(pCrashHandler!=NULL);

    if(pCrashHandler!=NULL)
    {    
        // Acquire lock to avoid other threads (if exist) to crash while we are 
        // inside. We do not unlock, because process is to be terminated.
        pCrashHandler->CrashLock(TRUE);

		// Treat this type of crash critical by default
		pCrashHandler->m_bContinueExecution = FALSE;

        // Fill in the exception info
        CR_EXCEPTION_INFO ei;
        memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
        ei.cb = sizeof(CR_EXCEPTION_INFO);
        ei.exctype = CR_CPP_SIGTERM;

		// Generate crash report
        pCrashHandler->GenerateErrorReport(&ei);

        if(!pCrashHandler->m_bContinueExecution)
		{
			// Terminate process
			TerminateProcess(GetCurrentProcess(), 1);
		}

		// Free lock
		pCrashHandler->CrashLock(FALSE);  
    }
}

DWORD CCrashHandler::GetFlags()
{
	return m_dwFlags;
}


