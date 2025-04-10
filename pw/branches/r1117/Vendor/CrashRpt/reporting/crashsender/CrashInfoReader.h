/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: CrashInfoReader.h
// Description: Retrieves crash information passed from CrashRpt.dll.
// Authors: zexspectrum
// Date: 2010

#pragma once
#include "stdafx.h"
#include "tinyxml.h"
#include "SharedMem.h"
#include "ScreenCap.h"

// The structure describing a file item contained in crash report.
struct ERIFileItem
{
	// Constructor.
    ERIFileItem()
    {
        m_bMakeCopy = FALSE;
		m_bAllowDelete = FALSE;
    }

    CString m_sDestFile;    // Destination file name as it appears in ZIP archive (not including directory name).
    CString m_sSrcFile;     // Absolute path to source file.
    CString m_sDesc;        // File description.
    BOOL m_bMakeCopy;       // Should we copy source file to error report folder?
	BOOL m_bAllowDelete;    // Should allow user to delete the file from crash report?
    CString m_sErrorStatus; // Empty if OK, non-empty if error occurred.

	// Retrieves file information, such as type and size.
	BOOL GetFileInfo(HICON& hIcon, CString& sTypeName, LONGLONG& lSize);
};


// This structure describes a loaded module item.
struct ERIModuleItem
{
  ERIModuleItem()
  {
  }

  CString m_sModulePath; //  
  CString m_sCodeStart; // 
  CString m_sCodeEnd; // 
};

struct ERIRegKey
{
	ERIRegKey()
	{
		m_bAllowDelete = false;
	}

	CString m_sDstFileName; // Destination file name
	bool m_bAllowDelete;    // Whether to allow user deleting the file from context menu of Error Report Details dialog.
};

// Error report delivery statuses.
enum DELIVERY_STATUS
{  
    PENDING    = 0,  // Status pending.
	INPROGRESS = 1,  // Error report is being sent.
    DELIVERED  = 2,  // Error report was delivered ok.
    FAILED     = 3,  // Error report delivery failed.
	DELETED    = 4   // Error report was deleted by user.
};

// Error report info.
class CErrorReportInfo
{
	friend class CCrashInfoReader;

public:

	// Constructor.
    CErrorReportInfo();    

	// Destructor.
	~CErrorReportInfo();
	
	// Returns count of file in error report.
	int GetFileItemCount();

	// Method that retrieves a file item by zero-based index.
	ERIFileItem* GetFileItemByIndex(int nItem);

	// Returns file item by its name.
	ERIFileItem* GetFileItemByName(LPCTSTR szDestFileName);

	// Adds/replaces a file to crash report.
	void AddFileItem(ERIFileItem* pfi);

	// Removes an item.
	BOOL DeleteFileItemByIndex(int nItem);

  // Returns count of loaded modules in error report.
  int GetModuleItemCount();

  // Method that retrieves a module item by zero-based index.
  ERIModuleItem* GetModuleItemByIndex(int nItem);


	// Returns count of custom properties in error report.
	int GetPropCount();

	// Method that retrieves a property by zero-based index.
	BOOL GetPropByIndex(int nItem, CString& sName, CString& sVal);
	
	// Adds/replaces a property in crash report.
	void AddProp(LPCTSTR szName, LPCTSTR szVal);
  
  // Get a property in crash report.
  LPCTSTR GetProp(LPCTSTR szName);

	// Returns count of registry keys in error report.
	int GetRegKeyCount();

	// Method that retrieves a registry key by zero-based index.
	BOOL GetRegKeyByIndex(int nItem, CString& sKeyName, ERIRegKey& rki);
	
	// Adds/replaces a reg key in crash report.
	void AddRegKey(LPCTSTR szKeyName, ERIRegKey& rki);

	// Returns the name of the directory where error report files are located.
	CString GetErrorReportDirName();

	// Returns crash GUID.
	CString GetCrashGUID();

	// Returns app name.
	CString GetAppName();

	// Returns app version.
	CString GetAppVersion();

	// Returns application executable image path.
	CString GetImageName();

	// Returns crash report sender's E-mail address.
	CString GetEmailFrom();

	// Returns user-entered problem description.
	CString GetProblemDescription();

	// Returns the time when crash occurred (UTC).
	CString GetSystemTimeUTC();

	// Returns uncompressed error report size in bytes.
	ULONG64 GetTotalSize();

	// Returns exception address.
	ULONG64 GetExceptionAddress();

	// Returns name of exception module
	CString GetExceptionModule();

	// Sets name of exception module
	void SetExceptionModule(LPCTSTR szExceptionModule);

	// Returns base address of exception module
	ULONG64 GetExceptionModuleBase();

	// Sets base address of exception module
	void SetExceptionModuleBase(ULONG64 dwExceptionModuleBase);

	// Returns version of exception module
	CString GetExceptionModuleVersion();

	// Sets version of exception module
	void SetExceptionModuleVersion(LPCTSTR szVer);

	// Return OS name.
	CString GetOSName();

	// Returns TRUE if OS is 64-bit
	BOOL IsOS64Bit();

	// Returns geographic location.
	CString GetGeoLocation();

	// Returns count of GUI resources
	DWORD GetGuiResourceCount();

	// Returns process handle count
	DWORD GetProcessHandleCount();

	// Returns memory usage
	CString GetMemUsage();

  // Returns virtual memory usage
  CString GetVirtualMemUsage();

  // Returns total memory 
  CString GetTotalMem();

  // Return number of logic processors
  DWORD GetCPUsCount();
  
  // Return CPU info
  CString GetCPUInfo();

	// Returns TRUE if crash report is selected for delivery.
	BOOL IsSelected();

	// Selects or deselects error report for delivery.
	void Select(BOOL bSelect);

	// Return crash report's delivery status.
	DELIVERY_STATUS GetDeliveryStatus();

	// Sets delivery status.
	void SetDeliveryStatus(DELIVERY_STATUS status);

	// Returns desktop screenshot parameters
	ScreenshotInfo& GetScreenshotInfo();

	// Sets desktop screenshot parameters.
	void SetScreenshotInfo(ScreenshotInfo &si);
			
private:
	
	// Calculates total size of files included into error report.
	LONG64 CalcUncompressedReportSize();
	
	/* Internal variables */ 

    CString         m_sErrorReportDirName; // Name of the directory where error report files are located.
    CString         m_sCrashGUID;          // Crash GUID.
    CString         m_sAppName;            // Application name.
    CString         m_sAppVersion;         // Application version.
    CString         m_sImageName;          // Path to the application executable file.
    CString         m_sEmailFrom;          // E-mail sender address.
    CString         m_sDescription;        // User-provided problem description.
    CString         m_sSystemTimeUTC;      // The time when crash occurred (UTC).
	ULONG64         m_dwExceptionAddress;  // Exception address (taken from exception info structure).
	CString         m_sExceptionModule;    // Module where exception occurred.
	CString         m_sExceptionModuleVersion; // File version of the module where exception occurred
	ULONG64         m_dwExceptionModuleBase; // Base address of the exception module.    
    DWORD           m_dwGuiResources;      // GUI resource count.
    DWORD           m_dwProcessHandleCount; // Process handle count.
    DWORD           m_dwCpusNumber;         // Number of logical processors in system
    CString         m_sCpuInfo;            // CPU architecture, family and model
    CString         m_sMemUsage;           // Memory usage.
    CString         m_sVirtualMemUsage;    // Virtual memory usage.
    CString         m_sTotalPhysicalMem;   // Total amount of physical memory installed in system.
    CString         m_sOSName;             // Operating system friendly name.
    BOOL            m_bOSIs64Bit;          // Is operating system 64-bit?
    CString         m_sGeoLocation;        // Geographic location.
    ScreenshotInfo  m_ScreenshotInfo;      // Screenshot info.
	ULONG64         m_uTotalSize;          // Summary size of this (uncompressed) report.
    BOOL            m_bSelected;           // Is this report selected for delivery or not?
    DELIVERY_STATUS m_DeliveryStatus;      // Error report delivery status.

    std::map<CString, ERIFileItem>  m_FileItems; // The list of files that are included into this error report.
    std::map<CString, ERIModuleItem>  m_ModuleItems; // The list of loaded modules.
    std::map<CString, ERIRegKey> m_RegKeys; // The list of registry keys included into this error report.
    std::map<CString, CString> m_Props;   // The list of custom properties included into this error report.
};

// Remind policy. Defines the way user is notified about recently queued crash reports.
enum REMIND_POLICY 
{
    REMIND_LATER,   // Remind later.
    NEVER_REMIND    // Never remind.
};

// Class responsible for reading the crash info passed by the crashed application.
class CCrashInfoReader
{
public:

    /* Public member variables. */

    int         m_nCrashRptVersion;     // CrashRpt version sent through shared memory
    CString     m_sUnsentCrashReportsFolder; // Path to UnsentCrashReports folder for the application.
    CString     m_sLangFileName;        // Path to language INI file.
    CString     m_sDbgHelpPath;         // Path to dbghelp.dll.
    CString     m_sAppName;             // Application name.
    CString     m_sCustomSenderIcon;    // Custom icon resource for Error Report dialog.
    CString     m_sEmailTo;             // E-mail recipient address.
    CString     m_sEmailSubject;        // E-mail subject.
    CString     m_sEmailText;           // E-mail text.
    int         m_nSmtpPort;            // SMTP port.
    CString     m_sSmtpProxyServer;     // SMTP proxy server.
    int         m_nSmtpProxyPort;       // SMTP proxy port.
	CString     m_sSmtpLogin;           // SMTP login.
	CString     m_sSmtpPassword;        // SMTP password.
    CString     m_sUrl;                 // URL (used for HTTP connection).    
    BOOL        m_bSilentMode;          // Should we show GUI?
    BOOL        m_bSendErrorReport;     // Should we send error report now?
	BOOL		m_bSendMandatory;       // Disable "Close" and "Other actions.." buttons on Error Report dialog.
	BOOL		m_bShowAdditionalInfoFields; // Make "Your E-mail" and "Describe what you were doing when the problem occurred" fields of Error Report dialog always visible.
	BOOL		m_bAllowAttachMoreFiles; // Whether to allow user to attach more files to crash report by clicking "Attach More File(s)" item from context menu of Error Report Details dialog.
    BOOL        m_bStoreZIPArchives;    // Should we store zipped error report files?
    BOOL        m_bSendRecentReports;   // Should we send recently queued reports now?
    BOOL        m_bLogEnabled;
    BOOL        m_bAppRestart;          // Should we restart the crashed application?
    CString     m_sRestartCmdLine;      // Command line for crashed app restart.
    UINT        m_uPriorities[3];       // Error report delivery priorities.
    CString     m_sPrivacyPolicyURL;    // Privacy policy URL.
    BOOL        m_bGenerateMinidump;    // Should we generate crash minidump file?
    MINIDUMP_TYPE m_MinidumpType;       // Minidump type.
    BOOL        m_bAddScreenshot;       // Should we add a desktop screenshot to error report?
    DWORD       m_dwScreenshotFlags;    // Screenshot taking options.
    int         m_nJpegQuality;         // Jpeg image quality (used when taking screenshot).
    CPoint      m_ptCursorPos;          // Mouse cursor position on crash.
    CRect       m_rcAppWnd;             // Rectangle of the application's main window.  
	BOOL        m_bAddVideo;            // Wether to add video recording.
	DWORD       m_dwVideoFlags;         // Flags for video recording.
	int         m_nVideoDuration;       // Video duration.
	int         m_nVideoFrameInterval;  // Video frame interval.
	int         m_nVideoQuality;        // Video quality.
	SIZE        m_DesiredFrameSize;     // Desired video frame size.
	HWND        m_hWndVideoParent;      // Video recording dialog parent.
	BOOL        m_bClientAppCrashed;    // If TRUE, the client app has crashed; otherwise the client app exited successfully.
	BOOL        m_bQueueEnabled;        // Can reports be sent later or not (queue enabled)?
	// Below are exception information fields.
    DWORD       m_dwProcessId;          // Parent process ID (used for minidump generation).
    DWORD       m_dwThreadId;           // Parent thread ID (used for minidump generation).
    PEXCEPTION_POINTERS m_pExInfo;      // Address of exception info (used for minidump generation).
	int         m_nExceptionType;       // Exception type (what handler caught the exception).
    DWORD       m_dwExceptionCode;      // SEH exception code.
    UINT        m_uFPESubcode;          // FPE exception subcode.
    CString     m_sInvParamExpr;        // Invalid parameter expression.
    CString     m_sInvParamFunction;    // Invalid parameter function.
    CString     m_sInvParamFile;        // Invalid parameter file.
    UINT        m_uInvParamLine;        // Invalid parameter line.

    /* Member functions */

	// Constructor
	CCrashInfoReader();
	
    // Gets crash info from shared memory.
    int Init(LPCTSTR szFileMappingName);

    // Loads custom icon (if defined).
    HICON GetCustomIcon();

    // Returns report by its index in the list.
    CErrorReportInfo* GetReport(int nIndex);

    // Returns count of error reports.
    int GetReportCount();
		
	// Deletes n-th report.
	void DeleteReport(int nIndex);

	// Deletes all reports.
	void DeleteAllReports();

    // Returns TRUE if it is time to remind user about recently queued error reports.
    BOOL IsRemindNowOK();

    // Sets remind policy.
    BOOL SetRemindPolicy(REMIND_POLICY Policy);

    // Updates last remind date.
    BOOL SetLastRemindDateToday();
	    
	// Returns last error message.
	CString GetErrorMsg();
	
	// Validates and updates user Email and and problem description.
	// Returns TRUE if validated successfully, otherwise FALSE.
    BOOL UpdateUserInfo(CString sEmail, CString sDesc);

	// Reads the E-mail last entered by user and stored in INI file.
	CString GetPersistentUserEmail();

	// Saves user's E-mail to INI file for later reuse.
	void SetPersistentUserEmail(LPCTSTR szEmail);

	// Adds the list of files to crash report.
    BOOL AddFilesToCrashReport(int nReport, std::vector<ERIFileItem>);

	// Removes several files by names.
	BOOL RemoveFilesFromCrashReport(int nReport, std::vector<CString> FilesToRemove);
	
private:

    // Retrieves some crash info from crash description XML.
    int ParseCrashDescription(CString sFileName, BOOL bParseFileItems, CErrorReportInfo& eri);  
	    
	// Adds user information.
    BOOL AddUserInfoToCrashDescriptionXML(CString sEmail, CString sDesc);

	// Returns last remind date.
    BOOL GetLastRemindDate(SYSTEMTIME& LastDate);

    // Returns current remind policy.
    REMIND_POLICY GetRemindPolicy();

    // Unpacks crash description from shared memory.
    int UnpackCrashDescription(CErrorReportInfo& eri);

    // Unpacks a string.
    int UnpackString(DWORD dwOffset, CString& str);

    // Collects misc info about the crash.
    void CollectMiscCrashInfo(CErrorReportInfo& eri);

    // Gets the list of file items. 
    int ParseFileList(TiXmlHandle& hRoot, CErrorReportInfo& eri);

    int ParseModuleList(TiXmlHandle& hRoot, CErrorReportInfo& eri);

    // Gets the list of registry keys.
    int ParseRegKeyList(TiXmlHandle& hRoot, CErrorReportInfo& eri);

    // Calculates size of an uncompressed error report.
    LONG64 GetUncompressedReportSize(CErrorReportInfo& eri);

    std::vector<CErrorReportInfo> m_Reports; // Array of error reports.   
    CString m_sINIFile;                     // Path to ~CrashRpt.ini file.
    CSharedMem m_SharedMem;                 // Shared memory
    CRASH_DESCRIPTION* m_pCrashDesc;        // Pointer to crash descritpion
	CString m_sErrorMsg;                    // Last error message.
};

