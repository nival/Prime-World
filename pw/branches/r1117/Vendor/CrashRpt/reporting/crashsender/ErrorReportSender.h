/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#pragma once
#include "AssyncNotification.h"
#include "MailMsg.h"
#include "smtpclient.h"
#include "HttpRequestSender.h"
#include "tinyxml.h"
#include "CrashInfoReader.h"
#include "VideoRec.h"

// Action type
enum ActionType  
{
    COLLECT_CRASH_INFO  = 0x01, // Crash info should be collected.
    COMPRESS_REPORT     = 0x02, // Error report files should be packed into ZIP archive.
    RESTART_APP         = 0x04, // Crashed app should be restarted.
    SEND_REPORT         = 0x08, // Report should be sent.
	SEND_RECENT_REPORTS = 0x10  // Recent crash reports should be sent.
};

// Mail client launch confirmation status
enum eMailClientConfirm
{
    NOT_CONFIRMED_YET, // User didn't confirm yet
    ALLOWED,           // User allowed mail client launch
    NOT_ALLOWED        // User didn't allow mail client launch
};

// Messages sent to GUI buy the sender
#define WM_NEXT_ITEM_HINT      (WM_USER+1023)
#define WM_ITEM_STATUS_CHANGED (WM_USER+1024)
#define WM_DELIVERY_COMPLETE   (WM_USER+1025)

// The main class that collects crash report files, packs them 
// into a ZIP archive and sends the error report.
class CErrorReportSender
{
public:

    // Constructor.
    CErrorReportSender();

	// Destructor.
    virtual ~CErrorReportSender();

	// Returns singleton of this class.
	static CErrorReportSender* GetInstance();

	// Performs initialization.	
	BOOL Init(LPCTSTR szFileMappingName);
		
	// Cleans up all temp files and does other finalizing work.
    BOOL Finalize();

	// Returns pointer to object containing crash information.
	CCrashInfoReader* GetCrashInfo();
	
	// Returns last error message.
	CString GetErrorMsg();

	// Set the window that will receive notifications from this object.
	void SetNotificationWindow(HWND hWnd);

	// Compresses and sends the report(s).
	BOOL Run();
	    
    // Blocks until an assync operation finishes.
    void WaitForCompletion();

	// Cancels the assync operation.
    void Cancel();

    // Returns error report sending status.
    int GetStatus();

    // Gets current operation status.
    void GetCurOpStatus(int& nProgressPct, std::vector<CString>& msg_log);
	    
    // Unblocks waiting worker thread.
    void FeedbackReady(int code);
	    
    // Returns current error report's index.
    int GetCurReport();
	    
	// Returns path to log file.
	CString GetLogFilePath();
	    
	// Returns a localized string from lang file.
	CString GetLangStr(LPCTSTR szSection, LPCTSTR szName);

	// Allows to specify file name for exporting error report.
    void SetExportFlag(BOOL bExport, CString sExportFile);

	// Exports crash report to disc as a ZIP archive.
	void ExportReport(LPCTSTR szOutFileName);

	// Returns TRUE if currently sending error report(s).
	BOOL IsSendingNow();

	// Returns TRUE if there were errors.
	BOOL HasErrors();
	
	// This method finds and terminates all instances of CrashSender.exe process.
	static int TerminateAllCrashSenderProcesses();
		
private:

	// This method performs an action or several actions.
    BOOL DoWork(int Action);
	    
    // Worker thread proc.
    static DWORD WINAPI WorkerThread(LPVOID lpParam);  

	// Runs an action or several actions in assync mode.
    BOOL DoWorkAssync(int Action);

    // Collects crash report files.
    BOOL CollectCrashFiles();  

	// Includes a single file to crash report
	BOOL CollectSingleFile(ERIFileItem* pfi);

	// Includes all files matching search pattern to crash report
	BOOL CollectFilesBySearchTemplate(ERIFileItem* pfi, std::vector<ERIFileItem>& file_list);

    // Calculates MD5 hash for a file.
    int CalcFileMD5Hash(CString sFileName, CString& sMD5Hash);
	    
    // Takes desktop screenshot.
    BOOL TakeDesktopScreenshot();

	// This method enters the video recording loop.
	BOOL RecordVideo();

	// Writes video to a webm file
	BOOL EncodeVideo();

    // Creates crash dump file.
    BOOL CreateMiniDump();  

	// This method is used to have the current process be able to call MiniDumpWriteDump.
	BOOL SetDumpPrivileges();

    // Creates crash description XML file.
    BOOL CreateCrashDescriptionXML(CErrorReportInfo& eri);
	
    // Adds an element to XML file.
    void AddElemToXML(CString sName, CString sValue, TiXmlNode* root);

    void AddModulesInformationToXML( BYTE * CrashAddress, TiXmlNode* root );
    void AddProcessInformationToXML(  TiXmlNode* root );

    // Minidump callback.
    static BOOL CALLBACK MiniDumpCallback(PVOID CallbackParam, PMINIDUMP_CALLBACK_INPUT CallbackInput,
        PMINIDUMP_CALLBACK_OUTPUT CallbackOutput); 

    // Minidump callback.
    BOOL OnMinidumpProgress(const PMINIDUMP_CALLBACK_INPUT CallbackInput,
        PMINIDUMP_CALLBACK_OUTPUT CallbackOutput);

    // Restarts the application.
    BOOL RestartApp();

	// Dumps registry key to the XML file.
    int DumpRegKey(CString sRegKey, CString sDestFile, CString& sErrorMsg);
	
	// Used internally for dumping a registry key.
    int DumpRegKey(HKEY hKeyParent, CString sSubKey, TiXmlElement* elem);

    // Packs error report files to ZIP archive.
    BOOL CompressReportFiles(CErrorReportInfo* eri);

    // Unblocks parent process.
    void UnblockParentProcess();

    // Sends error report.
    BOOL SendReport();

    // Sends error report over HTTP.
    BOOL SendOverHTTP();

    // Encodes attachment file with Base-64 encoding.
    int Base64EncodeAttachment(CString sFileName, std::string& sEncodedFileData);

    // Formats Email text.
    CString FormatEmailText();

    // Sends error report over SMTP.
    BOOL SendOverSMTP();

    // Sends error report over Simple MAPI.
    BOOL SendOverSMAPI();

	// Sends all recently queued error reports in turn.
	BOOL SendRecentReports();

	// Send the next queued report.
	BOOL SendNextReport(int nReport);
    
	// Internal variables
	static CErrorReportSender* m_pInstance; // Singleton
	CCrashInfoReader m_CrashInfo;       // Contains crash information.
	CVideoRecorder m_VideoRec;            // Video recorder.
	CString m_sErrorMsg;                // Last error message.
	HWND m_hWndNotify;                  // Notification window.
    int m_nStatus;                      // Error report sending status.
    int m_nCurReport;                   // Index of current error report.
    HANDLE m_hThread;                   // Handle to the worker thread.
    int m_SendAttempt;                  // Number of current sending attempt.
    AssyncNotification m_Assync;        // Used for communication with the main thread.
    CEmailMessage m_EmailMsg;           // Email message to send.
    CSmtpClient m_SmtpClient;           // Used to send report over SMTP.
    CHttpRequestSender m_HttpSender;    // Used to send report over HTTP.
    CMailMsg m_MapiSender;              // Used to send report over SMAPI.
    CString m_sZipName;                 // Name of the ZIP archive to send.
    int m_Action;                       // Current assynchronous action.
    BOOL m_bExport;                     // If TRUE than export should be performed.
    CString m_sExportFileName;          // File name for exporting.
	eMailClientConfirm m_MailClientConfirm;  // Mail program confirmation result.
    BOOL m_bSendingNow;                 // TRUE if in progress of sending reports.
	BOOL m_bErrors;                     // TRUE if there were errors.
};


