/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#include "stdafx.h"
#include "ErrorReportSender.h"
#include "MailMsg.h"
#include "smtpclient.h"
#include "HttpRequestSender.h"
#include "CrashRpt.h"
#include "md5.h"
#include "Utility.h"
#include "zip.h"
#include "CrashInfoReader.h"
#include "strconv.h"
#include "ScreenCap.h"
#include "base64.h"
#include <sys/stat.h>
#include "dbghelp.h"
#include "VideoRec.h"
#include "VideoRecDlg.h"

CErrorReportSender* CErrorReportSender::m_pInstance = NULL;

// Constructor
CErrorReportSender::CErrorReportSender()
{
    // Init variables
    m_nStatus = 0;
    m_nCurReport = 0;
    m_hThread = NULL;
    m_SendAttempt = 0;
    m_Action=COLLECT_CRASH_INFO;
    m_bExport = FALSE;
	m_MailClientConfirm = NOT_CONFIRMED_YET;	
    m_bSendingNow = FALSE;        
	m_bErrors = FALSE;
}

// Destructor
CErrorReportSender::~CErrorReportSender()
{
	Finalize();
}

CErrorReportSender* CErrorReportSender::GetInstance()
{
	// Return singleton object
	if(m_pInstance==NULL)	
		m_pInstance = new CErrorReportSender();
	return m_pInstance;
}

BOOL CErrorReportSender::Init(LPCTSTR szFileMappingName)
{
	m_sErrorMsg = _T("Unspecified error.");
		
	// Read crash information from the file mapping object.
    int nInit = m_CrashInfo.Init(szFileMappingName);
    if(nInit!=0)
    {
		m_sErrorMsg.Format(_T("Error reading crash info: %s"), m_CrashInfo.GetErrorMsg().GetBuffer(0));
        return FALSE;
    }
		
	// Check window mirroring settings 
    CString sRTL = Utility::GetINIString(m_CrashInfo.m_sLangFileName, _T("Settings"), _T("RTLReading"));
    if(sRTL.CompareNoCase(_T("1"))==0)
    {
		// Set Right-to-Left reading order
        SetProcessDefaultLayout(LAYOUT_RTL);  
    }

	// Determine whether to record video
	if(GetCrashInfo()->m_bAddVideo)
	{
		// The following enters the video recording loop
		// and returns when the parent process signals the event.
		BOOL bRec = RecordVideo();		
		if(!bRec)
		{
			// Clean up temp files
			m_VideoRec.Destroy();
			return FALSE;
		}

		// Reread crash information from the file mapping object.
		int nInit = m_CrashInfo.Init(szFileMappingName);
		if(nInit!=0)
		{
			m_sErrorMsg.Format(_T("Error reading crash info: %s"), m_CrashInfo.GetErrorMsg().GetBuffer(0));
			return FALSE;
		}

		// Check if the client app has crashed or exited successfully.
		if(!m_CrashInfo.m_bClientAppCrashed)
		{
			// Let the parent process to continue its work
			UnblockParentProcess();

			// Clean up temp files
			m_VideoRec.Destroy();

			return FALSE;
		}
	}
	
    if(!m_CrashInfo.m_bSendRecentReports)
    {
        // Start crash info collection work assynchronously
        DoWorkAssync(COLLECT_CRASH_INFO);
    }
	else
	{
		// Check if another instance of CrashSender.exe is running.
        ::CreateMutex( NULL, FALSE,_T("Local\\43773530-129a-4298-88f2-20eea3e4a59b"));
        if (::GetLastError() == ERROR_ALREADY_EXISTS)
        {		
            m_sErrorMsg = _T("Another CrashSender.exe already tries to resend recent reports.");
            return FALSE;
        }

        if(m_CrashInfo.GetReportCount()==0)
		{
			m_sErrorMsg = _T("There are no reports for us to send.");
            return FALSE; 
		}

        // Check if it is ok to remind user now.
        if(!m_CrashInfo.IsRemindNowOK())
		{
			m_sErrorMsg = _T("Not enough time elapsed to remind user about recent crash reports.");
            return FALSE;
		}
	}

	// Done.
	m_sErrorMsg = _T("Success.");
	return TRUE;
}

CCrashInfoReader* CErrorReportSender::GetCrashInfo()
{
	return &m_CrashInfo;
}

CString CErrorReportSender::GetErrorMsg()
{
	return m_sErrorMsg;
}

void CErrorReportSender::SetNotificationWindow(HWND hWnd)
{
	// Set notification window
	m_hWndNotify = hWnd;
}

BOOL CErrorReportSender::Run()
{
	if(m_CrashInfo.m_bSendRecentReports)
	{
		// We should send recently queued error reports.
		DoWorkAssync(SEND_RECENT_REPORTS);    
	}
	else
	{
		// Wait for completion of crash info collector.
		WaitForCompletion();

		// Determine whether to send crash report now 
		// or to exit without sending report.
		if(m_CrashInfo.m_bSendErrorReport) // If we should send error report now
		{
			// Compress report files and send the report
			SetExportFlag(FALSE, _T(""));
			DoWorkAssync(COMPRESS_REPORT|RESTART_APP|SEND_REPORT);    
		}
		else // If we shouldn't send error report now
		{      
			// Exit        

		}
	}

	return TRUE;
}

int CErrorReportSender::GetStatus()
{
    // Return global error report delivery status
    return m_nStatus;
}

int CErrorReportSender::GetCurReport()
{
    // Returns the index of error report currently being sent
    return m_nCurReport;
}

// This method performs crash files collection and/or
// error report sending work in a worker thread.
BOOL CErrorReportSender::DoWorkAssync(int nAction)
{
    // Save the action code
    m_Action = nAction;

    // Create worker thread which will do all work assynchronously
    m_hThread = CreateThread(NULL, 0, WorkerThread, (LPVOID)this, 0, NULL);

    // Check if the thread was created ok
    if(m_hThread==NULL)
        return FALSE; // Failed to create worker thread

    // Done, return
    return TRUE;
}

// This method is the worker thread procedure that delegates further work 
// back to the CErrorReportSender class
DWORD WINAPI CErrorReportSender::WorkerThread(LPVOID lpParam)
{
    // Delegate the action to the CErrorReportSender::DoWorkAssync() method
    CErrorReportSender* pSender = (CErrorReportSender*)lpParam;
    pSender->DoWork(pSender->m_Action);
	  pSender->m_hThread = NULL; // clean up
    // Exit code can be ignored
    return 0;
}

// This method unblocks the parent process
void CErrorReportSender::UnblockParentProcess()
{
    // Notify the parent process that we have finished with minidump,
    // so the parent process is able to unblock and terminate itself.

	// Open the event the parent process had created for us
    CString sEventName;
    sEventName.Format(_T("Local\\CrashRptEvent_%s"), GetCrashInfo()->GetReport(0)->GetCrashGUID());
    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, sEventName);
    if(hEvent!=NULL)
        SetEvent(hEvent); // Signal event
}

// This method collects required crash report files (minidump, screenshot etc.)
// and then sends the error report over the Internet.
BOOL CErrorReportSender::DoWork(int Action)
{
    // Reset the completion event
    m_Assync.Reset();

    if(Action&SEND_RECENT_REPORTS) // If we are currently sending pending error reports
    {
		  return SendRecentReports();		        
    }

    if(Action&COLLECT_CRASH_INFO) // Collect crash report files
    {
      // Init log file
      if (m_CrashInfo.m_bLogEnabled)
      {
        Utility::RecycleFile(GetLogFilePath(), TRUE);
        CString sCurTime;
        Utility::GetSystemTimeUTC(sCurTime);
        sCurTime.Replace(':', '-');    
        CString sLogFile;
        sLogFile.Format(_T("CrashRpt-Log-%s.txt"), sCurTime);
        m_Assync.InitLogFile(sLogFile);
      }

        // Add a message to log
        m_Assync.SetProgress(_T("Start collecting information about the crash..."), 0, false);

        // First take a screenshot of user's desktop (if needed).
        TakeDesktopScreenshot();

        if(m_Assync.IsCancelled()) // Check if user-cancelled
        {      
            // Parent process can now terminate
            UnblockParentProcess();

            // Add a message to log
            m_Assync.SetProgress(_T("[exit_silently]"), 0, false);
            return FALSE;
        }

        // Create crash dump.
        CreateMiniDump();

        if(m_Assync.IsCancelled()) // Check if user-cancelled
        {      
            // Parent process can now terminate
            UnblockParentProcess();

            // Add a message to log
            m_Assync.SetProgress(_T("[exit_silently]"), 0, false);
            return FALSE;
        }

        // Notify the parent process that we have finished with minidump,
        // so the parent process is able to unblock and terminate itself.
        UnblockParentProcess();
		
        // Copy user-provided files.
        CollectCrashFiles();

        if(m_Assync.IsCancelled()) // Check if user-cancelled
        {      
            // Add a message to log
            m_Assync.SetProgress(_T("[exit_silently]"), 0, false);
            return FALSE;
        }

		    // Encode recorded video to an .OGG file
		    EncodeVideo();
		
		    if(m_Assync.IsCancelled()) // Check if user-cancelled
        {      
            // Add a message to log
            m_Assync.SetProgress(_T("[exit_silently]"), 0, false);
            return FALSE;
        }

		    // Create crash description XML
		    CreateCrashDescriptionXML(*m_CrashInfo.GetReport(m_nCurReport));
    	
		    // Add a message to log
        m_Assync.SetProgress(_T("[confirm_send_report]"), 100, false);
    }

	  if(Action&RESTART_APP) // We need to restart the parent process
    { 
        // Restart the application
        RestartApp();
    }

    if(Action&COMPRESS_REPORT) // We have to compress error report file into ZIP archive
    { 
        // Compress error report files
        BOOL bCompress = CompressReportFiles(m_CrashInfo.GetReport(m_nCurReport));
        if(!bCompress)
        {
            // Add a message to log
            m_Assync.SetProgress(_T("[status_failed]"), 100, false);
            return FALSE; // Error compressing files
        }
    }
	
    if(Action&SEND_REPORT) // We need to send the report over the Internet
    {
        // Send the error report.
        if(!SendReport())
			return FALSE;
    }

    // Done
    return TRUE;
}

// Returns the export flag (the flag is set if we are exporting error report as a ZIP archive)
void CErrorReportSender::SetExportFlag(BOOL bExport, CString sExportFile)
{
    // This is used when we need to export error report files as a ZIP archive
    m_bExport = bExport;
    m_sExportFileName = sExportFile;
}

// This method blocks until worker thread is exited
void CErrorReportSender::WaitForCompletion()
{	
	if(m_hThread!=NULL)
		WaitForSingleObject(m_hThread, INFINITE);	
}

// Gets status of the local operation
void CErrorReportSender::GetCurOpStatus(int& nProgressPct, std::vector<CString>& msg_log)
{
    m_Assync.GetProgress(nProgressPct, msg_log); 
}

// This method cancels the current operation
void CErrorReportSender::Cancel()
{
    // User-cancelled
    m_Assync.Cancel();
}

// This method notifies the main thread that we have finished assync operation
void CErrorReportSender::FeedbackReady(int code)
{
    m_Assync.FeedbackReady(code);
}

// This method cleans up temporary files
BOOL CErrorReportSender::Finalize()
{  
	// Wait until worker thread exits.
	WaitForCompletion();

    if((m_CrashInfo.m_bSendErrorReport && !m_CrashInfo.m_bQueueEnabled) ||
		(m_CrashInfo.m_bAddVideo && !m_CrashInfo.m_bClientAppCrashed))
    {
        // Remove report files if queue disabled (or if client app not crashed).
        Utility::RecycleFile(m_CrashInfo.GetReport(0)->GetErrorReportDirName(), true);    
    }

	if(m_CrashInfo.m_bSendRecentReports)
	{
		// Delete log file
		Utility::RecycleFile(m_Assync.GetLogFilePath(), true);
	}

    if(!m_CrashInfo.m_bSendErrorReport && 
        m_CrashInfo.m_bStoreZIPArchives) // If we should generate a ZIP archive
    {
        // Compress error report files
        DoWork(COMPRESS_REPORT);            
    }

    // If needed, restart the application
    if(!m_CrashInfo.m_bSendRecentReports)
    {
        DoWork(RESTART_APP);         
    }

    // Done OK
    return TRUE;
}

// This method takes the desktop screenshot (screenshot of entire virtual screen
// or screenshot of the main window). 
BOOL CErrorReportSender::TakeDesktopScreenshot()
{
    CScreenCapture sc; // Screen capture object
    ScreenshotInfo ssi; // Screenshot params    

    // Add a message to log
    m_Assync.SetProgress(_T("[taking_screenshot]"), 0);    

    // Check if screenshot capture is allowed
    if(!m_CrashInfo.m_bAddScreenshot)
    {
        // Add a message to log
        m_Assync.SetProgress(_T("Desktop screenshot generation disabled; skipping."), 0);    
        // Exit, nothing to do here
        return TRUE;
    }

    // Add a message to log
    m_Assync.SetProgress(_T("Taking desktop screenshot"), 0);    

    // Get screenshot flags passed by the parent process
    DWORD dwFlags = m_CrashInfo.m_dwScreenshotFlags;

	BOOL bAllowDelete = (dwFlags&CR_AS_ALLOW_DELETE)!=0;

    // Determine what image format to use (JPG or PNG)
    SCREENSHOT_IMAGE_FORMAT fmt = SCREENSHOT_FORMAT_PNG; // PNG by default

    if((dwFlags&CR_AS_USE_JPEG_FORMAT)!=0)
        fmt = SCREENSHOT_FORMAT_JPG; // Use JPEG format

    // Determine what to use - color or grayscale image
    BOOL bGrayscale = (dwFlags&CR_AS_GRAYSCALE_IMAGE)!=0;

	SCREENSHOT_TYPE type = SCREENSHOT_TYPE_VIRTUAL_SCREEN;
    if((dwFlags&CR_AS_MAIN_WINDOW)!=0) // We need to capture the main window
		type = SCREENSHOT_TYPE_MAIN_WINDOW;
    else if((dwFlags&CR_AS_PROCESS_WINDOWS)!=0) // Capture all process windows
		type = SCREENSHOT_TYPE_ALL_PROCESS_WINDOWS;
    else // (dwFlags&CR_AS_VIRTUAL_SCREEN)!=0 // Capture the virtual screen
		type = SCREENSHOT_TYPE_VIRTUAL_SCREEN;
    
    // Take the screen shot
    BOOL bTakeScreenshot = sc.TakeDesktopScreenshot(		
        m_CrashInfo.GetReport(m_nCurReport)->GetErrorReportDirName(), 
		ssi, type, m_CrashInfo.m_dwProcessId, fmt, m_CrashInfo.m_nJpegQuality, bGrayscale);
    if(bTakeScreenshot==FALSE)
    {
        return FALSE;
    }

	// Save screenshot info
    m_CrashInfo.GetReport(m_nCurReport)->SetScreenshotInfo(ssi);

    // Prepare the list of screenshot files we will add to the error report
    std::vector<ERIFileItem> FilesToAdd;
    size_t i;
	for(i=0; i<ssi.m_aMonitors.size(); i++)
    {
		CString sFileName = ssi.m_aMonitors[i].m_sFileName;
        CString sDestFile;
        int nSlashPos = sFileName.ReverseFind('\\');
        sDestFile = sFileName.Mid(nSlashPos+1);
        ERIFileItem fi;
        fi.m_sSrcFile = sFileName;
        fi.m_sDestFile = sDestFile;		
        fi.m_sDesc = Utility::GetINIString(m_CrashInfo.m_sLangFileName, _T("DetailDlg"), _T("DescScreenshot")); 		
		fi.m_bAllowDelete = bAllowDelete;
        m_CrashInfo.GetReport(m_nCurReport)->AddFileItem(&fi);
    }

    // Done
    return TRUE;
}

// This callback function is called by MinidumpWriteDump
BOOL CALLBACK CErrorReportSender::MiniDumpCallback(
    PVOID CallbackParam,
    PMINIDUMP_CALLBACK_INPUT CallbackInput,
    PMINIDUMP_CALLBACK_OUTPUT CallbackOutput )
{
    // Delegate back to the CErrorReportSender
    CErrorReportSender* pErrorReportSender = (CErrorReportSender*)CallbackParam;  
    return pErrorReportSender->OnMinidumpProgress(CallbackInput, CallbackOutput);  
}

// This method is called when MinidumpWriteDump notifies us about
// currently performed action
BOOL CErrorReportSender::OnMinidumpProgress(const PMINIDUMP_CALLBACK_INPUT CallbackInput,
                                            PMINIDUMP_CALLBACK_OUTPUT CallbackOutput)
{
    switch(CallbackInput->CallbackType)
    {
    case CancelCallback: 
        {
            // This callback allows to cancel minidump generation
            if(m_Assync.IsCancelled())
            {
                CallbackOutput->Cancel = TRUE;      
                m_Assync.SetProgress(_T("Dump generation cancelled by user"), 0, true);
            }
        }
        break;

    case ModuleCallback:
        {
            // We are currently dumping some module
            strconv_t strconv;
            CString sMsg;
            sMsg.Format(_T("Dumping info for module %s"), 
                strconv.w2t(CallbackInput->Module.FullPath));

			// Here we want to collect module information
			CErrorReportInfo* eri = m_CrashInfo.GetReport(m_nCurReport);
			if(eri->GetExceptionAddress()!=0)
			{
				// Check if this is the module where exception has happened
				ULONG64 dwExcAddr = eri->GetExceptionAddress();
				if(dwExcAddr>=CallbackInput->Module.BaseOfImage && 
					dwExcAddr<=CallbackInput->Module.BaseOfImage+CallbackInput->Module.SizeOfImage)
				{
					// Save module information to the report
					eri->SetExceptionModule(CallbackInput->Module.FullPath);
					eri->SetExceptionModuleBase(CallbackInput->Module.BaseOfImage);

					// Save module version info
					VS_FIXEDFILEINFO* fi = &CallbackInput->Module.VersionInfo;
					if(fi)
					{
						WORD dwVerMajor = HIWORD(fi->dwProductVersionMS);
						WORD dwVerMinor = LOWORD(fi->dwProductVersionMS);
						WORD dwPatchLevel = HIWORD(fi->dwProductVersionLS);
						WORD dwVerBuild = LOWORD(fi->dwProductVersionLS);

						CString sVer;
						sVer.Format(_T("%u.%u.%u.%u"), 
									dwVerMajor, dwVerMinor, dwPatchLevel, dwVerBuild);
						eri->SetExceptionModuleVersion(sVer);  					
					}
				}
			}

			// Update progress
            m_Assync.SetProgress(sMsg, 0, true);
        }
        break;
    case ThreadCallback:
        {      
            // We are currently dumping some thread 
            CString sMsg;
            sMsg.Format(_T("Dumping info for thread 0x%X"), 
                CallbackInput->Thread.ThreadId);
            m_Assync.SetProgress(sMsg, 0, true);
        }
        break;

    }

    return TRUE;
}

// This method creates the minidump of the process
BOOL CErrorReportSender::CreateMiniDump()
{   
    BOOL bStatus = FALSE;
    HMODULE hDbgHelp = NULL;
    HANDLE hFile = NULL;
    MINIDUMP_EXCEPTION_INFORMATION mei;
    MINIDUMP_CALLBACK_INFORMATION mci;
    CString sMinidumpFile = m_CrashInfo.GetReport(m_nCurReport)->
        GetErrorReportDirName() + _T("\\crashdump.dmp");
    std::vector<ERIFileItem> files_to_add;
    ERIFileItem fi;
    CString sErrorMsg;

	// Check our config - should we generate the minidump or not?
    if(m_CrashInfo.m_bGenerateMinidump==FALSE)
    {
        m_Assync.SetProgress(_T("Crash dump generation disabled; skipping."), 0, false);
        return TRUE;
    }

	// Update progress
    m_Assync.SetProgress(_T("Creating crash dump file..."), 0, false);
    m_Assync.SetProgress(_T("[creating_dump]"), 0, false);
	
    // Load dbghelp.dll
    hDbgHelp = LoadLibrary(m_CrashInfo.m_sDbgHelpPath);
    if(hDbgHelp==NULL)
    {
        // Try again ... fallback to dbghelp.dll in path
        const CString sDebugHelpDLL_name = "dbghelp.dll";
        hDbgHelp = LoadLibrary(sDebugHelpDLL_name);    
    }

    if(hDbgHelp==NULL)
    {
        sErrorMsg = _T("dbghelp.dll couldn't be loaded");
        m_Assync.SetProgress(_T("dbghelp.dll couldn't be loaded."), 0, false);
        goto cleanup;
    }

	// Try to adjust process privilegies to be able to generate minidumps.
	SetDumpPrivileges();

    // Create the minidump file
    hFile = CreateFile(
        sMinidumpFile,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

	// Check if file has been created
    if(hFile==INVALID_HANDLE_VALUE)
    {
        DWORD dwError = GetLastError();
        CString sMsg;    
        sMsg.Format(_T("Couldn't create minidump file: %s"), 
            Utility::FormatErrorMsg(dwError));
        m_Assync.SetProgress(sMsg, 0, false);
        sErrorMsg = sMsg;
        return FALSE;
    }

    // Set valid dbghelp API version  
    typedef LPAPI_VERSION (WINAPI* LPIMAGEHLPAPIVERSIONEX)(LPAPI_VERSION AppVersion);  
    LPIMAGEHLPAPIVERSIONEX lpImagehlpApiVersionEx = 
        (LPIMAGEHLPAPIVERSIONEX)GetProcAddress(hDbgHelp, "ImagehlpApiVersionEx");
    ATLASSERT(lpImagehlpApiVersionEx!=NULL);
    if(lpImagehlpApiVersionEx!=NULL)
    {    
        API_VERSION CompiledApiVer;
        CompiledApiVer.MajorVersion = 6;
        CompiledApiVer.MinorVersion = 1;
        CompiledApiVer.Revision = 11;    
        CompiledApiVer.Reserved = 0;
        LPAPI_VERSION pActualApiVer = lpImagehlpApiVersionEx(&CompiledApiVer);    
        pActualApiVer;
        ATLASSERT(CompiledApiVer.MajorVersion==pActualApiVer->MajorVersion);
        ATLASSERT(CompiledApiVer.MinorVersion==pActualApiVer->MinorVersion);
        ATLASSERT(CompiledApiVer.Revision==pActualApiVer->Revision);    
    }

    // Write minidump to the file
    mei.ThreadId = m_CrashInfo.m_dwThreadId;
    mei.ExceptionPointers = m_CrashInfo.m_pExInfo;
    mei.ClientPointers = TRUE;

    mci.CallbackRoutine = MiniDumpCallback;
    mci.CallbackParam = this;

    typedef BOOL (WINAPI *LPMINIDUMPWRITEDUMP)(
        HANDLE hProcess, 
        DWORD ProcessId, 
        HANDLE hFile, 
        MINIDUMP_TYPE DumpType, 
        CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, 
        CONST PMINIDUMP_USER_STREAM_INFORMATION UserEncoderParam, 
        CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);

	// Get address of MiniDumpWirteDump function
    LPMINIDUMPWRITEDUMP pfnMiniDumpWriteDump = 
        (LPMINIDUMPWRITEDUMP)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
    if(!pfnMiniDumpWriteDump)
    {    
        m_Assync.SetProgress(_T("Bad MiniDumpWriteDump function."), 0, false);
        sErrorMsg = _T("Bad MiniDumpWriteDump function");
        return FALSE;
    }

	// Open client process
    HANDLE hProcess = OpenProcess(
        PROCESS_ALL_ACCESS, 
        FALSE, 
        m_CrashInfo.m_dwProcessId);

	// Now actually write the minidump
    BOOL bWriteDump = pfnMiniDumpWriteDump(
        hProcess,
        m_CrashInfo.m_dwProcessId,
        hFile,
        m_CrashInfo.m_MinidumpType,
        &mei,
        NULL,
        &mci);

	// Check result
    if(!bWriteDump)
    {    
        CString sMsg = Utility::FormatErrorMsg(GetLastError());
        m_Assync.SetProgress(_T("Error writing dump."), 0, false);
        m_Assync.SetProgress(sMsg, 0, false);
        sErrorMsg = sMsg;
        goto cleanup;
    }

	// Update progress
    bStatus = TRUE;
    m_Assync.SetProgress(_T("Finished creating dump."), 100, false);

cleanup:

    // Close file
    if(hFile)
        CloseHandle(hFile);

    // Unload dbghelp.dll
    if(hDbgHelp)
        FreeLibrary(hDbgHelp);

	// Add the minidump file to error report
    fi.m_bMakeCopy = false;
    fi.m_sDesc = Utility::GetINIString(m_CrashInfo.m_sLangFileName, _T("DetailDlg"), _T("DescCrashDump"));
    fi.m_sDestFile = _T("crashdump.dmp");
    fi.m_sSrcFile = sMinidumpFile;
    fi.m_sErrorStatus = sErrorMsg;
    files_to_add.push_back(fi);

    // Add file to the list
    m_CrashInfo.GetReport(m_nCurReport)->AddFileItem(&fi);
	
    return bStatus;
}

BOOL CErrorReportSender::SetDumpPrivileges()
{
	// This method is used to have the current process be able to call MiniDumpWriteDump
	// This code was taken from:
	// http://social.msdn.microsoft.com/Forums/en-US/vcgeneral/thread/f54658a4-65d2-4196-8543-7e71f3ece4b6/
	

	BOOL       fSuccess  = FALSE;
	HANDLE      TokenHandle = NULL;
	TOKEN_PRIVILEGES TokenPrivileges;

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&TokenHandle))
	{
		m_Assync.SetProgress(_T("SetDumpPrivileges: Could not get the process token"), 0);		
		goto Cleanup;
	}

	TokenPrivileges.PrivilegeCount = 1;

	if (!LookupPrivilegeValue(NULL,
		SE_DEBUG_NAME,
		&TokenPrivileges.Privileges[0].Luid))
	{
		m_Assync.SetProgress(_T("SetDumpPrivileges: Couldn't lookup SeDebugPrivilege name"), 0);				
		goto Cleanup;
	}

	TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	//Add privileges here.
	if (!AdjustTokenPrivileges(TokenHandle,
		FALSE,
		&TokenPrivileges,
		sizeof(TokenPrivileges),
		NULL,
		NULL))
	{
		m_Assync.SetProgress(_T("SetDumpPrivileges: Could not revoke the debug privilege"), 0);						
		goto Cleanup;
	}

	fSuccess = TRUE;

Cleanup:

	if (TokenHandle)
	{
		CloseHandle(TokenHandle);
	}

	return fSuccess;
}

// This method adds an element to XML file
void CErrorReportSender::AddElemToXML(CString sName, CString sValue, TiXmlNode* root)
{
    strconv_t strconv;
    TiXmlHandle hElem = new TiXmlElement(strconv.t2utf8(sName));
    root->LinkEndChild(hElem.ToNode());
    TiXmlText* text = new TiXmlText(strconv.t2utf8(sValue));
    hElem.ToElement()->LinkEndChild(text);
}

void CErrorReportSender::AddProcessInformationToXML(  TiXmlNode* root )
{
  struct SProcsEnum : public Utility::IProcsEnumCallback
  {
    TiXmlNode* root;
    strconv_t strconv;

    SProcsEnum( TiXmlNode* _root ) : root( _root ) {}
    virtual bool EnumModule( TCHAR* pszModuleName, DWORD processID )
    {
      //fprintf(f, "    <Process name=\"%s\" ID=\"0x%08x\"/>\n",  XmlEncodeStr( pszModuleName ).c_str(), processID );
      strconv_t strconv;
      TiXmlHandle hProccess = new TiXmlElement("Process");
      hProccess.ToElement()->SetAttribute("name", strconv.t2utf8(pszModuleName));
      CString sProcessInfo; 
      sProcessInfo.Format( _T("0x%08x"), (size_t)processID );
      hProccess.ToElement()->SetAttribute("ID", strconv.t2utf8(sProcessInfo));
      root->LinkEndChild( hProccess.ToNode() );

      return true;
    }
  };

  TiXmlHandle hElem = new TiXmlElement("Processes");
  root->LinkEndChild(hElem.ToNode());
  SProcsEnum procsEnum( hElem.ToElement() );
  EnumerateProcs( &procsEnum );
}


// This method generates an XML file describing the crash
BOOL CErrorReportSender::CreateCrashDescriptionXML(CErrorReportInfo& eri)
{
    BOOL bStatus = FALSE;
    ERIFileItem fi;
    CString sFileName = eri.GetErrorReportDirName() + _T("\\crashrpt.xml");
    CString sErrorMsg;
    strconv_t strconv;
    TiXmlDocument doc;
    FILE* f = NULL; 
    CString sNum;
    CString sCrashRptVer;
    CString sOSIs64Bit;
    CString sExceptionType;

    fi.m_bMakeCopy = false;
    fi.m_sDesc = Utility::GetINIString(m_CrashInfo.m_sLangFileName, _T("DetailDlg"), _T("DescXML"));
    fi.m_sDestFile = _T("crashrpt.xml");
    fi.m_sSrcFile = sFileName;
    fi.m_sErrorStatus = sErrorMsg;  
    // Add this file to the list
    eri.AddFileItem(&fi);

    TiXmlNode* root = root = new TiXmlElement("CrashRpt");
    doc.LinkEndChild(root);  
    sCrashRptVer.Format(_T("%d"), CRASHRPT_VER);
    TiXmlHandle(root).ToElement()->SetAttribute("version", strconv.t2utf8(sCrashRptVer));

    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
    doc.InsertBeforeChild(root, *decl);
	
    AddElemToXML(_T("CrashGUID"), eri.GetCrashGUID(), root);
    AddElemToXML(_T("AppName"), eri.GetAppName(), root);
    AddElemToXML(_T("AppVersion"), eri.GetAppVersion(), root);  
    AddElemToXML(_T("ImageName"), eri.GetImageName(), root);
    AddElemToXML(_T("OperatingSystem"), eri.GetOSName(), root);


    sOSIs64Bit.Format(_T("%d"), eri.IsOS64Bit());
    AddElemToXML(_T("OSIs64Bit"), sOSIs64Bit, root);

    AddElemToXML(_T("GeoLocation"), eri.GetGeoLocation(), root);
    AddElemToXML(_T("SystemTimeUTC"), eri.GetSystemTimeUTC(), root);
		
	if(eri.GetExceptionAddress()!=0)
	{
		sNum.Format(_T("0x%I64x"), eri.GetExceptionAddress());
		AddElemToXML(_T("ExceptionAddress"), sNum, root);

		AddElemToXML(_T("ExceptionModule"), eri.GetExceptionModule(), root);

		sNum.Format(_T("0x%I64x"), eri.GetExceptionModuleBase());
		AddElemToXML(_T("ExceptionModuleBase"), sNum, root);

		AddElemToXML(_T("ExceptionModuleVersion"), eri.GetExceptionModuleVersion(), root);
	}

    LPCTSTR res = eri.GetProp( _T("IsStarforceCrash") );
    if ( res && _tcscmp(res, _T("True"))==0 )
    {
      AddElemToXML( _T("CrashedModule"), "Starforce", root );
    }
    else
    {
        sExceptionType.Format(_T("%d"), m_CrashInfo.m_nExceptionType);
        AddElemToXML(_T("ExceptionType"), sExceptionType, root);
        if(m_CrashInfo.m_nExceptionType==CR_SEH_EXCEPTION)
        {
            CString sExceptionCode;
            sExceptionCode.Format(_T("%d"), m_CrashInfo.m_dwExceptionCode);
            AddElemToXML(_T("ExceptionCode"), sExceptionCode, root);

            CString sCrashedModule = Utility::GetFileName(eri.GetExceptionModule());
            AddElemToXML( _T("CrashedModule"), sCrashedModule, root );

            CString sRelativeAddr;
            ULONG64 relativeAddress =  eri.GetExceptionAddress() - eri.GetExceptionModuleBase();
            //sRelativeAddr.Format(_T("0x%08x"), relativeAddress);
            sRelativeAddr.Format(_T("0x%08x"), relativeAddress);
            AddElemToXML( _T("RelativeExceptionAddress"), sRelativeAddr, root );
        }
        else if(m_CrashInfo.m_nExceptionType==CR_CPP_SIGFPE)
        {
            CString sFPESubcode;
            sFPESubcode.Format(_T("%d"), m_CrashInfo.m_uFPESubcode);
            AddElemToXML(_T("FPESubcode"), sFPESubcode, root);
        }
        else if(m_CrashInfo.m_nExceptionType==CR_CPP_INVALID_PARAMETER)
        {
            AddElemToXML(_T("InvParamExpression"), m_CrashInfo.m_sInvParamExpr, root);
            AddElemToXML(_T("InvParamFunction"), m_CrashInfo.m_sInvParamFunction, root);
            AddElemToXML(_T("InvParamFile"), m_CrashInfo.m_sInvParamFile, root);

            CString sInvParamLine;
            sInvParamLine.Format(_T("%d"), m_CrashInfo.m_uInvParamLine);
            AddElemToXML(_T("InvParamLine"), sInvParamLine, root);
        }

        if (eri.GetModuleItemCount())
        {
          TiXmlHandle hModulesItems = new TiXmlElement("LoadedModules");
          root->LinkEndChild(hModulesItems.ToNode());

          for(int i=0; i<eri.GetModuleItemCount(); i++)
          {    
            ERIModuleItem* rfi = eri.GetModuleItemByIndex(i);
            ATLASSERT(rfi);
            TiXmlHandle hItem = new TiXmlElement("Module");

            hItem.ToElement()->SetAttribute("path", strconv.t2utf8(rfi->m_sModulePath));
            hItem.ToElement()->SetAttribute("codeStart", strconv.t2utf8(rfi->m_sCodeStart));
            hItem.ToElement()->SetAttribute("codeEnd", strconv.t2utf8(rfi->m_sCodeEnd));

            hModulesItems.ToElement()->LinkEndChild(hItem.ToNode());                  
          }
        }
        
    }
    
    AddProcessInformationToXML( root );

    CString sGuiResources;
    sGuiResources.Format(_T("%d"), eri.GetGuiResourceCount());
    AddElemToXML(_T("GUIResourceCount"), sGuiResources, root);

    CString sProcessHandleCount;
    sProcessHandleCount.Format(_T("%d"), eri.GetProcessHandleCount());
    AddElemToXML(_T("OpenHandleCount"), sProcessHandleCount, root);

    if(eri.GetScreenshotInfo().m_bValid)
    {
        TiXmlHandle hScreenshotInfo = new TiXmlElement("ScreenshotInfo");
        root->LinkEndChild(hScreenshotInfo.ToNode());

        TiXmlHandle hVirtualScreen = new TiXmlElement("VirtualScreen");    

        sNum.Format(_T("%d"), eri.GetScreenshotInfo().m_rcVirtualScreen.left);
        hVirtualScreen.ToElement()->SetAttribute("left", strconv.t2utf8(sNum));

        sNum.Format(_T("%d"), eri.GetScreenshotInfo().m_rcVirtualScreen.top);
        hVirtualScreen.ToElement()->SetAttribute("top", strconv.t2utf8(sNum));

        sNum.Format(_T("%d"), eri.GetScreenshotInfo().m_rcVirtualScreen.Width());
        hVirtualScreen.ToElement()->SetAttribute("width", strconv.t2utf8(sNum));

        sNum.Format(_T("%d"), eri.GetScreenshotInfo().m_rcVirtualScreen.Height());
        hVirtualScreen.ToElement()->SetAttribute("height", strconv.t2utf8(sNum));

        hScreenshotInfo.ToNode()->LinkEndChild(hVirtualScreen.ToNode());

        TiXmlHandle hMonitors = new TiXmlElement("Monitors");
        hScreenshotInfo.ToElement()->LinkEndChild(hMonitors.ToNode());                  

        size_t i;
        for(i=0; i<eri.GetScreenshotInfo().m_aMonitors.size(); i++)
        { 
            MonitorInfo& mi = eri.GetScreenshotInfo().m_aMonitors[i];      
            TiXmlHandle hMonitor = new TiXmlElement("Monitor");

            sNum.Format(_T("%d"), mi.m_rcMonitor.left);
            hMonitor.ToElement()->SetAttribute("left", strconv.t2utf8(sNum));

            sNum.Format(_T("%d"), mi.m_rcMonitor.top);
            hMonitor.ToElement()->SetAttribute("top", strconv.t2utf8(sNum));

            sNum.Format(_T("%d"), mi.m_rcMonitor.Width());
            hMonitor.ToElement()->SetAttribute("width", strconv.t2utf8(sNum));

            sNum.Format(_T("%d"), mi.m_rcMonitor.Height());
            hMonitor.ToElement()->SetAttribute("height", strconv.t2utf8(sNum));

            hMonitor.ToElement()->SetAttribute("file", strconv.t2utf8(Utility::GetFileName(mi.m_sFileName)));

            hMonitors.ToElement()->LinkEndChild(hMonitor.ToNode());                  
        }

        TiXmlHandle hWindows = new TiXmlElement("Windows");
        hScreenshotInfo.ToElement()->LinkEndChild(hWindows.ToNode());                  

        for(i=0; i<eri.GetScreenshotInfo().m_aWindows.size(); i++)
        { 
            WindowInfo& wi = eri.GetScreenshotInfo().m_aWindows[i];      
            TiXmlHandle hWindow = new TiXmlElement("Window");

            sNum.Format(_T("%d"), wi.m_rcWnd.left);
            hWindow.ToElement()->SetAttribute("left", strconv.t2utf8(sNum));

            sNum.Format(_T("%d"), wi.m_rcWnd.top);
            hWindow.ToElement()->SetAttribute("top", strconv.t2utf8(sNum));

            sNum.Format(_T("%d"), wi.m_rcWnd.Width());
            hWindow.ToElement()->SetAttribute("width", strconv.t2utf8(sNum));

            sNum.Format(_T("%d"), wi.m_rcWnd.Height());
            hWindow.ToElement()->SetAttribute("height", strconv.t2utf8(sNum));

            hWindow.ToElement()->SetAttribute("title", strconv.t2utf8(wi.m_sTitle));

            hWindows.ToElement()->LinkEndChild(hWindow.ToNode());                  
        }
    }

    //////////////////////////////////////////////////////////////////////////
    AddElemToXML(_T("MemoryUsageKbytes"), eri.GetMemUsage(), root);
    AddElemToXML(_T("VirtualMemoryUsageKbytes"), eri.GetVirtualMemUsage(), root);
    AddElemToXML(_T("TotalPhysicalMemoryKbytes"), eri.GetTotalMem(), root);

    //Write CPU Info
    AddElemToXML(_T("CPUInfo"), eri.GetCPUInfo(), root);
    CString sCPUsCount;
    sCPUsCount.Format(_T("%lu"), eri.GetCPUsCount());
    AddElemToXML(_T("NumberOfProcessors"), sCPUsCount, root);

    TiXmlHandle hCustomProps = new TiXmlElement("CustomProps");
    root->LinkEndChild(hCustomProps.ToNode());

	int i;
	for(i=0; i<eri.GetPropCount(); i++)
    { 
		CString sName;
		CString sVal;
		eri.GetPropByIndex(i, sName, sVal);

        TiXmlHandle hProp = new TiXmlElement("Prop");

        hProp.ToElement()->SetAttribute("name", strconv.t2utf8(sName));
        hProp.ToElement()->SetAttribute("value", strconv.t2utf8(sVal));

        hCustomProps.ToElement()->LinkEndChild(hProp.ToNode());                  
    }

    TiXmlHandle hFileItems = new TiXmlElement("FileList");
    root->LinkEndChild(hFileItems.ToNode());

    for(i=0; i<eri.GetFileItemCount(); i++)
    {    
		    ERIFileItem* rfi = eri.GetFileItemByIndex(i);
        TiXmlHandle hFileItem = new TiXmlElement("FileItem");

        hFileItem.ToElement()->SetAttribute("name", strconv.t2utf8(rfi->m_sDestFile));
        hFileItem.ToElement()->SetAttribute("description", strconv.t2utf8(rfi->m_sDesc));
		    if(rfi->m_bAllowDelete)
			    hFileItem.ToElement()->SetAttribute("optional", "1");
       /* if(rfi->m_bMakeCopy)
          hFileItem.ToElement()->SetAttribute("makecopy", "1");
*/
        if(!rfi->m_sErrorStatus.IsEmpty())
          hFileItem.ToElement()->SetAttribute("error", strconv.t2utf8(rfi->m_sErrorStatus));

        hFileItems.ToElement()->LinkEndChild(hFileItem.ToNode());                  
    }

#if _MSC_VER<1400
    f = _tfopen(sFileName, _T("w"));
#else
    _tfopen_s(&f, sFileName, _T("w"));
#endif

    if(f==NULL)
    {
        sErrorMsg = _T("Error opening file for writing");
        goto cleanup;
    }

    doc.useMicrosoftBOM = true;
    bool bSave = doc.SaveFile(f); 
    if(!bSave)
    {
        sErrorMsg = doc.ErrorDesc();
        goto cleanup;
    }

    fclose(f);
    f = NULL;

    bStatus = TRUE;

cleanup:

    if(f)
        fclose(f);

    if(!bStatus)
    {
		eri.GetFileItemByName(fi.m_sDestFile)->m_sErrorStatus = sErrorMsg;
    }

    return bStatus;
}

// This method collects user-specified files
BOOL CErrorReportSender::CollectCrashFiles()
{ 
	BOOL bStatus = FALSE;
    CString str;
    CString sErrorReportDir = m_CrashInfo.GetReport(m_nCurReport)->GetErrorReportDirName();
    CString sSrcFile;
    CString sDestFile;    
	std::vector<ERIFileItem> file_list;
	
    // Copy application-defined files that should be copied on crash
    m_Assync.SetProgress(_T("[copying_files]"), 0, false);
	
	// Walk through error report files
    int i;
	for(i=0; i<m_CrashInfo.GetReport(m_nCurReport)->GetFileItemCount(); i++)
    {
		ERIFileItem* pfi = m_CrashInfo.GetReport(m_nCurReport)->GetFileItemByIndex(i);

		// Check if operation has been cancelled by user
        if(m_Assync.IsCancelled())
            goto cleanup;

		// Check if the file name is a search template.		
		BOOL bSearchPattern = Utility::IsFileSearchPattern(pfi->m_sSrcFile);
		if(bSearchPattern)
			CollectFilesBySearchTemplate(pfi, file_list);
		else
			CollectSingleFile(pfi);
    }

	// Add newly collected files to the list of file items
	for(i=0; i<(int)file_list.size(); i++)
	{
		m_CrashInfo.GetReport(m_nCurReport)->AddFileItem(&file_list[i]);
	}				

	// Remove file items that are search patterns
	BOOL bFound = FALSE;
	do
	{
		bFound = FALSE;
		for(i=0; i<m_CrashInfo.GetReport(m_nCurReport)->GetFileItemCount(); i++)
		{
			ERIFileItem* pfi = m_CrashInfo.GetReport(m_nCurReport)->GetFileItemByIndex(i);
				
			// Check if the file name is a search template.		
			BOOL bSearchPattern = Utility::IsFileSearchPattern(pfi->m_sSrcFile);
			if(bSearchPattern)
			{
				// Delete this item
				m_CrashInfo.GetReport(m_nCurReport)->DeleteFileItemByIndex(i);
				bFound = TRUE;
				break;
			}
		}
	}
	while(bFound);

    // Create dump of registry keys

    CErrorReportInfo* eri = m_CrashInfo.GetReport(m_nCurReport);  
	  if(eri->GetRegKeyCount()!=0)
    {
        m_Assync.SetProgress(_T("Dumping registry keys..."), 0, false);    
    }

	// Walk through our registry key list	
    for(i=0; i<eri->GetRegKeyCount(); i++)
    {
		CString sKeyName;
		ERIRegKey rki;
		eri->GetRegKeyByIndex(i, sKeyName, rki);

        if(m_Assync.IsCancelled())
            goto cleanup;

		CString sFilePath = eri->GetErrorReportDirName() + _T("\\") + rki.m_sDstFileName;

        str.Format(_T("Dumping registry key '%s' to file '%s' "), sKeyName, sFilePath);
        m_Assync.SetProgress(str, 0, false);    

        // Create registry key dump
        CString sErrorMsg;
        DumpRegKey(sKeyName, sFilePath, sErrorMsg);
        ERIFileItem fi;
        fi.m_sSrcFile = sFilePath;
		fi.m_sDestFile = rki.m_sDstFileName;
        fi.m_sDesc = Utility::GetINIString(m_CrashInfo.m_sLangFileName, _T("DetailDlg"), _T("DescRegKey"));
        fi.m_bMakeCopy = FALSE;
		fi.m_bAllowDelete = rki.m_bAllowDelete;
        fi.m_sErrorStatus = sErrorMsg;
        std::vector<ERIFileItem> file_list;
        file_list.push_back(fi);
        // Add file to the list of file items
        m_CrashInfo.GetReport(m_nCurReport)->AddFileItem(&fi);
    }
	    
    // Success
    bStatus = TRUE;

cleanup:
		
	// Clean up
    m_Assync.SetProgress(_T("Finished copying files."), 100, false);

    return 0;
}

BOOL CErrorReportSender::CollectSingleFile(ERIFileItem* pfi)
{
	BOOL bStatus = false;
	CString str;
	HANDLE hSrcFile = INVALID_HANDLE_VALUE;
	HANDLE hDestFile = INVALID_HANDLE_VALUE;
	BOOL bGetSize = FALSE;
	LARGE_INTEGER lFileSize;
	LARGE_INTEGER lTotalWritten;
	CString sDestFile;
	BOOL bRead = FALSE;
	BOOL bWrite = FALSE;
	LPBYTE buffer[1024];
	DWORD dwBytesRead = 0;
	DWORD dwBytesWritten = 0;

	CString sErrorReportDir = m_CrashInfo.GetReport(m_nCurReport)->GetErrorReportDirName();

	// If we should make a copy of the file
    if(pfi->m_bMakeCopy)
    {
        str.Format(_T("Copying file %s."), pfi->m_sSrcFile);
        m_Assync.SetProgress(str, 0, false);

        // Open source file with read/write sharing permissions.
        hSrcFile = CreateFile(pfi->m_sSrcFile, GENERIC_READ, 
            FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
        if(hSrcFile==INVALID_HANDLE_VALUE)
        {
            pfi->m_sErrorStatus = Utility::FormatErrorMsg(GetLastError());
            str.Format(_T("Error opening file %s."), pfi->m_sSrcFile);
            m_Assync.SetProgress(str, 0, false);
        }

        bGetSize = GetFileSizeEx(hSrcFile, &lFileSize);
        if(!bGetSize)
        {
            pfi->m_sErrorStatus = Utility::FormatErrorMsg(GetLastError());
            str.Format(_T("Couldn't get file size of %s"), pfi->m_sSrcFile);
            m_Assync.SetProgress(str, 0, false);
            CloseHandle(hSrcFile);
            hSrcFile = INVALID_HANDLE_VALUE;
            goto cleanup;
        }

        if ( lFileSize.QuadPart > CR_AF_MAX_FILE_SIZE ) {
          SetFilePointer( hSrcFile, -(LONG)CR_AF_MAX_FILE_SIZE, NULL, FILE_END );
          lFileSize.QuadPart = CR_AF_MAX_FILE_SIZE;
        }

        sDestFile = sErrorReportDir + _T("\\") + pfi->m_sDestFile;

        hDestFile = CreateFile(sDestFile, GENERIC_WRITE, 
            FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, NULL);
        if(hDestFile==INVALID_HANDLE_VALUE)
        {
            pfi->m_sErrorStatus = Utility::FormatErrorMsg(GetLastError());
            str.Format(_T("Error creating file %s."), sDestFile);
            m_Assync.SetProgress(str, 0, false);
            CloseHandle(hSrcFile);
            hSrcFile = INVALID_HANDLE_VALUE;
            goto cleanup;
        }

        lTotalWritten.QuadPart = 0;

        for(;;)
        {        
            if(m_Assync.IsCancelled())
                goto cleanup;

            bRead = ReadFile(hSrcFile, buffer, 1024, &dwBytesRead, NULL);
            if(!bRead || dwBytesRead==0)
                break;

            bWrite = WriteFile(hDestFile, buffer, dwBytesRead, &dwBytesWritten, NULL);
            if(!bWrite || dwBytesRead!=dwBytesWritten)
                break;

            lTotalWritten.QuadPart += dwBytesWritten;

            int nProgress = (int)(100.0f*lTotalWritten.QuadPart/lFileSize.QuadPart);

            m_Assync.SetProgress(nProgress, false);
        }

        CloseHandle(hSrcFile);
        hSrcFile = INVALID_HANDLE_VALUE;
        CloseHandle(hDestFile);
        hDestFile = INVALID_HANDLE_VALUE;

		// Use the copy for display and zipping.
		pfi->m_sSrcFile = sDestFile;
    }

	bStatus = true;

cleanup:

    if(hSrcFile!=INVALID_HANDLE_VALUE)
        CloseHandle(hSrcFile);

    if(hDestFile!=INVALID_HANDLE_VALUE)
        CloseHandle(hDestFile);

	
	return bStatus;
}

BOOL CErrorReportSender::CollectFilesBySearchTemplate(ERIFileItem* pfi, std::vector<ERIFileItem>& file_list)
{
	CString sMsg;
	sMsg.Format(_T("Looking for files using search template: %s"), pfi->m_sSrcFile);
	m_Assync.SetProgress(sMsg, 0);

	// Look for files matching search pattern
	WIN32_FIND_DATA ffd;		
	HANDLE hFind = FindFirstFile(pfi->m_sSrcFile, &ffd);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		// Nothing found
		m_Assync.SetProgress(_T("Could not find any files matching the search template."), 0);
		return FALSE;
	} 
	else
	{		
		// Get owning directory name
		int nPos = pfi->m_sSrcFile.ReverseFind(_T('\\'));
		CString sDir = pfi->m_sSrcFile.Mid(0, nPos);
		
		// Enumerate matching files 
		BOOL bFound = TRUE;
		int nFileCount = 0;
		while(bFound)
		{
			if(m_Assync.IsCancelled())
				break;

			if((ffd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)==0)
			{					
				CString sFile = sDir + _T("\\");
				sFile += ffd.cFileName;					

				// Add file to file list.
				ERIFileItem fi;
				fi.m_sSrcFile = sFile;
				fi.m_sDestFile = ffd.cFileName;
				fi.m_sDesc = pfi->m_sDesc;
				fi.m_bMakeCopy = pfi->m_bMakeCopy;
				fi.m_bAllowDelete = pfi->m_bAllowDelete;								
				file_list.push_back(fi);
				
				CollectSingleFile(&fi);

				nFileCount++;								
			}

			// Go to next file
			bFound = FindNextFile(hFind, &ffd);
		}

		// Clean up
		FindClose(hFind);
	}
	
	// Done
	return TRUE;
}

// This method dumps a registry key contents to an XML file
int CErrorReportSender::DumpRegKey(CString sRegKey, CString sDestFile, CString& sErrorMsg)
{
    strconv_t strconv;
    TiXmlDocument document; 

    // Load document if file already exists
    // otherwise create new document.

    FILE* f = NULL;
#if _MSC_VER<1400
    f = _tfopen(sDestFile, _T("rb"));
#else
    _tfopen_s(&f, sDestFile, _T("rb"));
#endif
    if(f!=NULL)
    { 
        document.LoadFile(f);
        fclose(f);
        f = NULL;
    }  

    TiXmlHandle hdoc(&document);

    TiXmlElement* registry = document.RootElement();

    if(registry==NULL)
    {
        registry = new TiXmlElement("registry");
        document.LinkEndChild(registry);
    }

    TiXmlNode* declaration = hdoc.Child(0).ToNode();
    if(declaration==NULL || declaration->Type()!=TiXmlNode::TINYXML_DECLARATION)
    {
        TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
        document.InsertBeforeChild(registry, *decl);
    }   

    DumpRegKey(NULL, sRegKey, registry);

#if _MSC_VER<1400
    f = _tfopen(sDestFile, _T("wb"));
#else
    _tfopen_s(&f, sDestFile, _T("wb"));
#endif
    if(f==NULL)
    {
        sErrorMsg = _T("Error opening file for writing.");
        return 1;
    }

    bool bSave = document.SaveFile(f);

    fclose(f);

    if(!bSave)
    {
        sErrorMsg = _T("Error saving XML document to file: ");
        sErrorMsg += document.ErrorDesc();
    }

    return (bSave==true)?0:1;
}

int CErrorReportSender::DumpRegKey(HKEY hParentKey, CString sSubKey, TiXmlElement* elem)
{
    strconv_t strconv;
    HKEY hKey = NULL;  

    if(hParentKey==NULL)
    {    
        int nSkip = 0;
        if(sSubKey.Left(19).Compare(_T("HKEY_LOCAL_MACHINE\\"))==0)
        {
            hKey = HKEY_LOCAL_MACHINE;
            nSkip = 18;
        }
        else if(sSubKey.Left(18).Compare(_T("HKEY_CURRENT_USER\\"))==0)
        {
            hKey = HKEY_CURRENT_USER;
            nSkip = 17;
        }    
        else 
        {
            return 1; // Invalid key.
        }

        CString sKey = sSubKey.Mid(0, nSkip);
        LPCSTR szKey = strconv.t2utf8(sKey);
        sSubKey = sSubKey.Mid(nSkip+1);

        TiXmlHandle key_node = elem->FirstChild(szKey);
        if(key_node.ToElement()==NULL)
        {
            key_node = new TiXmlElement("k");
            elem->LinkEndChild(key_node.ToNode());
            key_node.ToElement()->SetAttribute("name", szKey);
        }

        DumpRegKey(hKey, sSubKey, key_node.ToElement());
    }
    else
    {
        int pos = sSubKey.Find('\\');
        CString sKey = sSubKey;
        if(pos>0)
            sKey = sSubKey.Mid(0, pos);
        LPCSTR szKey = strconv.t2utf8(sKey);

        TiXmlHandle key_node = elem->FirstChild(szKey);
        if(key_node.ToElement()==NULL)
        {
            key_node = new TiXmlElement("k");
            elem->LinkEndChild(key_node.ToNode());
            key_node.ToElement()->SetAttribute("name", szKey);
        }

        if(ERROR_SUCCESS==RegOpenKeyEx(hParentKey, sKey, 0, GENERIC_READ, &hKey))
        {
            if(pos>0)
            {
                sSubKey = sSubKey.Mid(pos+1);
                DumpRegKey(hKey, sSubKey, key_node.ToElement());
            }
            else
            {
                DWORD dwSubKeys = 0;
                DWORD dwMaxSubKey = 0;
                DWORD dwValues = 0;
                DWORD dwMaxValueNameLen = 0;
                DWORD dwMaxValueLen = 0;
                LONG lResult = RegQueryInfoKey(hKey, NULL, 0, 0, &dwSubKeys, &dwMaxSubKey, 
                    0, &dwValues, &dwMaxValueNameLen, &dwMaxValueLen, NULL, NULL); 
                if(lResult==ERROR_SUCCESS)
                {
                    // Enumerate and dump subkeys          
                    int i;
                    for(i=0; i<(int)dwSubKeys; i++)
                    { 
                        LPWSTR szName = new WCHAR[dwMaxSubKey + 1];
						DWORD dwLen = dwMaxSubKey + 1;
						lResult = RegEnumKeyEx(hKey, i, szName, &dwLen, 0, NULL, 0, NULL);
                        if(lResult==ERROR_SUCCESS)
                        {
                            DumpRegKey(hKey, CString(szName), key_node.ToElement());
                        }

                        delete [] szName;
                    }         

                    // Dump key values 
                    for(i=0; i<(int)dwValues; i++)
                    { 
                        LPWSTR szName = new WCHAR[dwMaxValueNameLen + 1];
						LPBYTE pData = new BYTE[dwMaxValueLen];
						DWORD dwNameLen = dwMaxValueNameLen + 1;
						DWORD dwValueLen = dwMaxValueLen;
						DWORD dwType = 0;

                        lResult = RegEnumValue(hKey, i, szName, &dwNameLen, 0, &dwType, pData, &dwValueLen);
                        if(lResult==ERROR_SUCCESS)
                        {
                            TiXmlHandle val_node = key_node.ToElement()->FirstChild(strconv.w2utf8(szName));
                            if(val_node.ToElement()==NULL)
                            {
                                val_node = new TiXmlElement("v");
                                key_node.ToElement()->LinkEndChild(val_node.ToNode());
                            }

                            val_node.ToElement()->SetAttribute("name", strconv.w2utf8(szName));

                            char str[128] = "";
                            LPSTR szType = NULL;
                            if(dwType==REG_BINARY)
                                szType = "REG_BINARY";
                            else if(dwType==REG_DWORD)
                                szType = "REG_DWORD";
                            else if(dwType==REG_EXPAND_SZ)
                                szType = "REG_EXPAND_SZ";
                            else if(dwType==REG_MULTI_SZ)
                                szType = "REG_MULTI_SZ";
                            else if(dwType==REG_QWORD)
                                szType = "REG_QWORD";
                            else if(dwType==REG_SZ)
                                szType = "REG_SZ";
                            else 
                            {
#if _MSC_VER<1400
                                sprintf(str, "Unknown type (0x%08x)", dwType);
#else
                                sprintf_s(str, 128, "Unknown type (0x%08x)", dwType);
#endif
                                szType = str;                
                            }

                            val_node.ToElement()->SetAttribute("type", szType);              

                            if(dwType==REG_BINARY)
                            {
                                std::string str2;
                                int j;
								for(j=0; j<(int)dwValueLen; j++)
								{
									char num[10];
#if _MSC_VER<1400
									sprintf(num, "%02X", pData[j]);
#else
									sprintf_s(num, 10, "%02X", pData[j]);
#endif
									str2 += num;
									if(j<(int)dwValueLen)
										str2 += " ";
								}

                                val_node.ToElement()->SetAttribute("value", str2.c_str());
                            }
                            else if(dwType==REG_DWORD)
                            {
                                LPDWORD pdwValue = (LPDWORD)pData;
                                char str3[64]="";
#if _MSC_VER<1400
                                sprintf(str3, "0x%08x (%lu)", *pdwValue, *pdwValue);                
#else
                                sprintf_s(str3, 64, "0x%08x (%lu)", *pdwValue, *pdwValue);                
#endif
                                val_node.ToElement()->SetAttribute("value", str3);
                            }
                            else if(dwType==REG_SZ || dwType==REG_EXPAND_SZ)
                            {
                                LPCSTR szValue = strconv.t2utf8((LPCTSTR)pData);
                                val_node.ToElement()->SetAttribute("value", szValue);                
                            }
                            else if(dwType==REG_MULTI_SZ)
                            {                
                                LPCTSTR szValues = (LPCTSTR)pData;
                                int prev = 0;
                                int pos2 = 0;
                                for(;;)
                                {
                                    if(szValues[pos2]==0)
                                    {
                                        CString sValue = CString(szValues+prev, pos2-prev);
                                        LPCSTR szValue = strconv.t2utf8(sValue);

                                        TiXmlHandle str_node = new TiXmlElement("str");
                                        val_node.ToElement()->LinkEndChild(str_node.ToNode());                    
                                        str_node.ToElement()->SetAttribute("value", szValue);              

                                        prev = pos2+1;
                                    }

                                    if(szValues[pos2]==0 && szValues[pos2+1]==0)
                                        break; // Double-null

                                    pos2++;
                                }                     
                            }
                        }

                        delete [] szName;
                        delete [] pData;
                    }         
                }
            }

            RegCloseKey(hKey);
        }
        else
        {      
            CString sErrMsg = Utility::FormatErrorMsg(GetLastError());
            LPCSTR szErrMsg = strconv.t2utf8(sErrMsg);
            key_node.ToElement()->SetAttribute("error", szErrMsg);
        }
    }

    return 0;
}

// This method calculates an MD5 hash for the file
int CErrorReportSender::CalcFileMD5Hash(CString sFileName, CString& sMD5Hash)
{
    FILE* f = NULL;  // Handle to file
    BYTE buff[512];  // Read buffer
    MD5 md5;         // MD5 hash
    MD5_CTX md5_ctx; // MD5 context
    unsigned char md5_hash[16]; // MD5 hash as sequence of bytes
    int i;

	// Clear output
    sMD5Hash.Empty();

	// Open file
#if _MSC_VER<1400
    f = _tfopen(sFileName.GetBuffer(0), _T("rb"));
#else
    _tfopen_s(&f, sFileName.GetBuffer(0), _T("rb"));
#endif

	// Check if file has been opened
    if(f==NULL) 
        return -1;

	// Init MD5 context
    md5.MD5Init(&md5_ctx);

	// Read file contents and update MD5 hash as each portion is being read
    while(!feof(f))
    {
        size_t count = fread(buff, 1, 512, f);
        if(count>0)
        {
            md5.MD5Update(&md5_ctx, buff, (unsigned int)count);
        }
    }

	// Close file
    fclose(f);

	// Finalize MD5 hash calculation
    md5.MD5Final(md5_hash, &md5_ctx);

	// Format hash as a string
    for(i=0; i<16; i++)
    {
        CString number;
        number.Format(_T("%02x"), md5_hash[i]);
        sMD5Hash += number;
    }

	// Done
    return 0;
}

// This method restarts the client application
BOOL CErrorReportSender::RestartApp()
{
	// Check our config - if we should restart the client app or not?
    if(m_CrashInfo.m_bAppRestart==FALSE)
        return FALSE; // No need to restart

	// Reset restart flag to avoid restarting the app twice
	// (if app has been restarted already).
	m_CrashInfo.m_bAppRestart = FALSE;

	// Add a message to log and reset progress 
    m_Assync.SetProgress(_T("Restarting the application..."), 0, false);

	// Set up process start up info
    STARTUPINFO si;
    memset(&si, 0, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

	// Set up process information
    PROCESS_INFORMATION pi;
    memset(&pi, 0, sizeof(PROCESS_INFORMATION));  

	// Format command line
    CString sCmdLine;
    if(m_CrashInfo.m_sRestartCmdLine.IsEmpty())
    {
        // Format with double quotes to avoid first empty parameter
        sCmdLine.Format(_T("\"%s\""), m_CrashInfo.GetReport(m_nCurReport)->GetImageName());
    }
    else
    {
		// Format with double quotes to avoid first empty parameters
        sCmdLine.Format(_T("\"%s\" %s"), m_CrashInfo.GetReport(m_nCurReport)->GetImageName(), 
            m_CrashInfo.m_sRestartCmdLine.GetBuffer(0));
    }

	// Create process using the command line prepared earlier
    BOOL bCreateProcess = CreateProcess(
        m_CrashInfo.GetReport(m_nCurReport)->GetImageName(), 
		sCmdLine.GetBuffer(0), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    
	// The following is to avoid a handle leak
	if(pi.hProcess)
    {
        CloseHandle(pi.hProcess);
        pi.hProcess = NULL;
    }

	// The following is to avoid a handle leak
    if(pi.hThread)
    {
        CloseHandle(pi.hThread);
        pi.hThread = NULL;
    }

	// Check if process was created
    if(!bCreateProcess)
    {    
		// Add error message
        m_Assync.SetProgress(_T("Error restarting the application!"), 0, false);
        return FALSE;
    }

	// Success
    m_Assync.SetProgress(_T("Application restarted OK."), 0, false);
    return TRUE;
}

// This method compresses the files contained in the report and produces a ZIP archive.
BOOL CErrorReportSender::CompressReportFiles(CErrorReportInfo* eri)
{ 
    BOOL bStatus = FALSE;
    strconv_t strconv;
    zipFile hZip = NULL;
    CString sMsg;
    LONG64 lTotalSize = 0;
    LONG64 lTotalCompressed = 0;
    BYTE buff[1024];
    DWORD dwBytesRead=0;
    HANDLE hFile = INVALID_HANDLE_VALUE;  
    std::map<CString, ERIFileItem>::iterator it;
    FILE* f = NULL;
    CString sMD5Hash;

	// Add a different log message depending on the current mode.
    if(m_bExport)
        m_Assync.SetProgress(_T("[exporting_report]"), 0, false);
    else
        m_Assync.SetProgress(_T("[compressing_files]"), 0, false);

	// Calculate the total size of error report files
	lTotalSize = eri->GetTotalSize();

	// Add a message to log
    sMsg.Format(_T("Total file size for compression is %I64d bytes"), lTotalSize);
    m_Assync.SetProgress(sMsg, 0, false);

	// Determine what name to use for the output ZIP archive file.
    if(m_bExport)
        m_sZipName = m_sExportFileName;  
    else
        m_sZipName = eri->GetErrorReportDirName() + _T(".zip");  

	// Update progress
    sMsg.Format(_T("Creating ZIP archive file %s"), m_sZipName);
    m_Assync.SetProgress(sMsg, 1, false);

	// Create ZIP archive
    hZip = zipOpen((const char*)m_sZipName.GetBuffer(0), APPEND_STATUS_CREATE);
    if(hZip==NULL)
    {
        m_Assync.SetProgress(_T("Failed to create ZIP file."), 100, true);
        goto cleanup;
    }

	// Enumerate files contained in the report
	int i;
	for(i=0; i<eri->GetFileItemCount(); i++)
    { 
		ERIFileItem* pfi = eri->GetFileItemByIndex(i);

		// Check if the operation was cancelled by user
        if(m_Assync.IsCancelled())    
            goto cleanup;

		// Define destination file name in ZIP archive
        CString sDstFileName = pfi->m_sDestFile.GetBuffer(0);
		// Define source file name
        CString sFileName = pfi->m_sSrcFile.GetBuffer(0);
		// Define file description
        CString sDesc = pfi->m_sDesc;

		// Update progress
        sMsg.Format(_T("Compressing file %s"), sDstFileName);
        m_Assync.SetProgress(sMsg, 0, false);

		// Open file for reading
        hFile = CreateFile(sFileName, 
            GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL); 
        if(hFile==INVALID_HANDLE_VALUE)
        {
            sMsg.Format(_T("Couldn't open file %s"), sFileName);
            m_Assync.SetProgress(sMsg, 0, false);
            continue;
        }

		// Get file information.
        BY_HANDLE_FILE_INFORMATION fi;
        GetFileInformationByHandle(hFile, &fi);

        if ( fi.nFileSizeHigh > 0 || ( fi.nFileSizeLow > (DWORD)CR_AF_MAX_FILE_SIZE ) ) {
          SetFilePointer( hFile, -(LONG)CR_AF_MAX_FILE_SIZE, 0, FILE_END );
        }

		// Convert file creation time to system file time.
        SYSTEMTIME st;
        FileTimeToSystemTime(&fi.ftLastWriteTime, &st);

		// Fill in the ZIP file info
        zip_fileinfo info;
        info.dosDate = 0;
        info.tmz_date.tm_year = st.wYear;
        info.tmz_date.tm_mon = st.wMonth-1;
        info.tmz_date.tm_mday = st.wDay;
        info.tmz_date.tm_hour = st.wHour;
        info.tmz_date.tm_min = st.wMinute;
        info.tmz_date.tm_sec = st.wSecond;
        info.external_fa = FILE_ATTRIBUTE_NORMAL;
        info.internal_fa = FILE_ATTRIBUTE_NORMAL;

		// Create new file inside of our ZIP archive
        int n = zipOpenNewFileInZip( hZip, (const char*)strconv.t2a(sDstFileName.GetBuffer(0)), &info,
            NULL, 0, NULL, 0, strconv.t2a(sDesc), Z_DEFLATED, Z_DEFAULT_COMPRESSION);
        if(n!=0)
        {
            sMsg.Format(_T("Couldn't compress file %s"), sDstFileName);
            m_Assync.SetProgress(sMsg, 0, false);
            continue;
        }

		// Read source file contents and write it to ZIP archive
        for(;;)
        {
			// Check if operation was cancelled by user
            if(m_Assync.IsCancelled())    
                goto cleanup;

			// Read a portion of source file
            BOOL bRead = ReadFile(hFile, buff, 1024, &dwBytesRead, NULL);
            if(!bRead || dwBytesRead==0)
                break;

			// Write a portion into destination file
            int res = zipWriteInFileInZip(hZip, buff, dwBytesRead);
            if(res!=0)
            {
                zipCloseFileInZip(hZip);
                sMsg.Format(_T("Couldn't write to compressed file %s"), sDstFileName);
                m_Assync.SetProgress(sMsg, 0, false);        
                break;
            }

			// Update totals
            lTotalCompressed += dwBytesRead;

			// Update progress
            float fProgress = 100.0f*lTotalCompressed/lTotalSize;
            m_Assync.SetProgress((int)fProgress, false);
        }

		// Close file
        zipCloseFileInZip(hZip);
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
    }

	// Close ZIP archive
    if(hZip!=NULL)
    {
        zipClose(hZip, NULL);
        hZip = NULL;
    }

    // Save MD5 hash file
    if(!m_bExport)
    {
        sMsg.Format(_T("Calculating MD5 hash for file %s"), m_sZipName);
        m_Assync.SetProgress(sMsg, 0, false);

        int nCalcMD5 = CalcFileMD5Hash(m_sZipName, sMD5Hash);
        if(nCalcMD5!=0)
        {
            sMsg.Format(_T("Couldn't calculate MD5 hash for file %s"), m_sZipName);
            m_Assync.SetProgress(sMsg, 0, false);
            goto cleanup;
        }

#if _MSC_VER <1400
        f = _tfopen(m_sZipName + _T(".md5"), _T("wt"));
#else
        _tfopen_s(&f, m_sZipName + _T(".md5"), _T("wt"));
#endif
        if(f==NULL)
        {
            sMsg.Format(_T("Couldn't save MD5 hash for file %s"), m_sZipName);
            m_Assync.SetProgress(sMsg, 0, false);
            goto cleanup;
        }

        _ftprintf(f, sMD5Hash);
        fclose(f);
        f = NULL;
    }

	// Check if totals match
    if(lTotalSize==lTotalCompressed)
        bStatus = TRUE;

cleanup:

	// Clean up

    if(hZip!=NULL)
        zipClose(hZip, NULL);

    if(hFile!=INVALID_HANDLE_VALUE)
        CloseHandle(hFile);

    if(f!=NULL)
        fclose(f);

    if(bStatus)
        m_Assync.SetProgress(_T("Finished compressing files...OK"), 100, true);
    else
        m_Assync.SetProgress(_T("File compression failed."), 100, true);

    if(m_bExport)
    {
        if(bStatus)
            m_Assync.SetProgress(_T("[end_exporting_report_ok]"), 100, false);    
        else
            m_Assync.SetProgress(_T("[end_exporting_report_failed]"), 100, false);    
    }
    else
    {    
        m_Assync.SetProgress(_T("[end_compressing_files]"), 100, false);   
    }

    return bStatus;
}

// This method sends the error report over the Internet
BOOL CErrorReportSender::SendReport()
{
    int status = 1;

    m_Assync.SetProgress(_T("[sending_report]"), 0);

	// Arrange priorities in reverse order
    std::multimap<int, int> order;

    std::pair<int, int> pair3(m_CrashInfo.m_uPriorities[CR_SMAPI], CR_SMAPI);
    order.insert(pair3);

    std::pair<int, int> pair2(m_CrashInfo.m_uPriorities[CR_SMTP], CR_SMTP);
    order.insert(pair2);

    std::pair<int, int> pair1(m_CrashInfo.m_uPriorities[CR_HTTP], CR_HTTP);
    order.insert(pair1);

    std::multimap<int, int>::reverse_iterator rit;

	// Walk through priorities
    for(rit=order.rbegin(); rit!=order.rend(); rit++)
    {
        m_Assync.SetProgress(_T("[sending_attempt]"), 0);
        m_SendAttempt++;    

		// Check if operation was cancelled.
        if(m_Assync.IsCancelled()){ break; }

        int id = rit->second;

        BOOL bResult = FALSE;

		// Send the report
        if(id==CR_HTTP)
            bResult = SendOverHTTP();    
        else if(id==CR_SMTP)
            bResult = SendOverSMTP();  
        else if(id==CR_SMAPI)
            bResult = SendOverSMAPI();

		// Check if this attempt has failed
        if(bResult==FALSE)
            continue;

		// If currently sending through Simple MAPI, do not wait for completion
        if(id==CR_SMAPI && bResult==TRUE)
        {
            status = 0;
            break;
        }

		// else wait for completion
        if(0==m_Assync.WaitForCompletion())
        {
            status = 0;
            break;
        }
    }

    // Remove compressed ZIP file and MD5 file
    Utility::RecycleFile(m_sZipName, true);
    Utility::RecycleFile(m_sZipName+_T(".md5"), true);

	// Check status
    if(status==0)
    {
		// Success
        m_Assync.SetProgress(_T("[status_success]"), 0);
        m_CrashInfo.GetReport(m_nCurReport)->SetDeliveryStatus(DELIVERED);
        // Delete report files
        Utility::RecycleFile(m_CrashInfo.GetReport(m_nCurReport)->GetErrorReportDirName(), true);    
    }
    else
    {
		// Some error occurred
        m_CrashInfo.GetReport(m_nCurReport)->SetDeliveryStatus(FAILED);    
        m_Assync.SetProgress(_T("[status_failed]"), 0);    

        // Check if we should store files for later delivery or we should remove them
        if(!m_CrashInfo.m_bQueueEnabled)
        {
            // Delete report files
            Utility::RecycleFile(m_CrashInfo.GetReport(m_nCurReport)->GetErrorReportDirName(), true);    
        }
    }

	// Done
    m_nStatus = status;
    m_Assync.SetCompleted(status);  
    return status==0?TRUE:FALSE;
}

// This method sends the report over HTTP request
BOOL CErrorReportSender::SendOverHTTP()
{  
    strconv_t strconv;

	// Check our config - should we send the report over HTTP or not?
    if(m_CrashInfo.m_uPriorities[CR_HTTP]==CR_NEGATIVE_PRIORITY)
    {
        m_Assync.SetProgress(_T("Sending error report over HTTP is disabled (negative priority); skipping."), 0);
        return FALSE;
    }

	// Check URL
    if(m_CrashInfo.m_sUrl.IsEmpty())
    {
        m_Assync.SetProgress(_T("No URL specified for sending error report over HTTP; skipping."), 0);
        return FALSE;
    }

	// Update progress
    m_Assync.SetProgress(_T("Sending error report over HTTP..."), 0);
    m_Assync.SetProgress(_T("Preparing HTTP request data..."), 0);

	// Create HTTP request
    CHttpRequest request;
    request.m_sUrl = m_CrashInfo.m_sUrl;  

	CErrorReportInfo* eri = m_CrashInfo.GetReport(m_nCurReport);

	// Fill in the request fields
	CString sNum;
	sNum.Format(_T("%d"), CRASHRPT_VER);
	request.m_aTextFields[_T("crashrptver")] = strconv.t2utf8(sNum);
    request.m_aTextFields[_T("appname")] = strconv.t2utf8(eri->GetAppName());
    request.m_aTextFields[_T("appversion")] = strconv.t2utf8(eri->GetAppVersion());
    request.m_aTextFields[_T("crashguid")] = strconv.t2utf8(eri->GetCrashGUID());
    request.m_aTextFields[_T("emailfrom")] = strconv.t2utf8(eri->GetEmailFrom());
    request.m_aTextFields[_T("emailsubject")] = strconv.t2utf8(m_CrashInfo.m_sEmailSubject);
    request.m_aTextFields[_T("description")] = strconv.t2utf8(eri->GetProblemDescription());
	request.m_aTextFields[_T("exceptionmodule")] = strconv.t2utf8(eri->GetExceptionModule());
	request.m_aTextFields[_T("exceptionmoduleversion")] = strconv.t2utf8(eri->GetExceptionModuleVersion());	
	sNum.Format(_T("%I64u"), eri->GetExceptionModuleBase());
	request.m_aTextFields[_T("exceptionmodulebase")] = strconv.t2utf8(sNum);
	sNum.Format(_T("%I64u"), eri->GetExceptionAddress());
	request.m_aTextFields[_T("exceptionaddress")] = strconv.t2utf8(sNum);

	// Add an MD5 hash of file attachment
    CString sMD5Hash;
    CalcFileMD5Hash(m_sZipName, sMD5Hash);
    request.m_aTextFields[_T("md5")] = strconv.t2utf8(sMD5Hash);

	// Set content type 
    CHttpRequestFile f;
    f.m_sSrcFileName = m_sZipName;
    f.m_sContentType = _T("application/zip");  
    request.m_aIncludedFiles[_T("crashrpt")] = f;  

	// Send HTTP request assynchronously
    BOOL bSend = m_HttpSender.SendAssync(request, &m_Assync);  
    return bSend;
}

int CErrorReportSender::Base64EncodeAttachment(CString sFileName, 
                                               std::string& sEncodedFileData)
{
    strconv_t strconv;

    int uFileSize = 0;
    BYTE* uchFileData = NULL;  
    struct _stat st;  

	// Get file information
    int nResult = _tstat(sFileName, &st);
    if(nResult != 0)
        return 1;  // File not found.

    // Allocate buffer of file size
    uFileSize = (int)st.st_size;
    uchFileData = new BYTE[uFileSize];

    // Read file data to buffer.
    FILE* f = NULL;
#if _MSC_VER<1400
    f = _tfopen(sFileName, _T("rb"));
#else
    /*errno_t err = */_tfopen_s(&f, sFileName, _T("rb"));  
#endif 

    if(!f || fread(uchFileData, uFileSize, 1, f)!=1)
    {
        delete [] uchFileData;
        uchFileData = NULL;
        return 2; // Coudln't read file data.
    }

	// Close file
    fclose(f);

	// BASE-64 ecode data
    sEncodedFileData = base64_encode(uchFileData, uFileSize);

	// Clean up
    delete [] uchFileData;

    // OK.
    return 0;
}

// This method formats the E-mail message text
CString CErrorReportSender::FormatEmailText()
{
    CString sFileTitle = m_sZipName;
    sFileTitle.Replace('/', '\\');
    int pos = sFileTitle.ReverseFind('\\');
    if(pos>=0)
        sFileTitle = sFileTitle.Mid(pos+1);

    CString sText;

    sText += _T("This is the error report from ") + m_CrashInfo.m_sAppName + 
        _T(" ") + m_CrashInfo.GetReport(m_nCurReport)->GetAppVersion()+_T(".\n\n");

    if(!m_CrashInfo.GetReport(m_nCurReport)->GetEmailFrom().IsEmpty())
    {
        sText += _T("This error report was sent by ") + m_CrashInfo.GetReport(m_nCurReport)->GetEmailFrom() + _T(".\n");
        sText += _T("If you need additional info about the problem, you may want to contact this user again.\n\n");
    }     

    if(!m_CrashInfo.GetReport(m_nCurReport)->GetProblemDescription().IsEmpty())
    {
        sText += _T("The user has provided the following problem description:\n<<< ") + 
            m_CrashInfo.GetReport(m_nCurReport)->GetProblemDescription() + _T(" >>>\n\n");    
    }

    sText += _T("You may find detailed information about the error in files attached to this message:\n\n");
    sText += sFileTitle + _T(" is a ZIP archive which contains crash description XML (crashrpt.xml), crash minidump (crashdump.dmp) ");
    sText += _T("and possibly other files that your application added to the crash report.\n\n");

    sText += sFileTitle + _T(".md5 file contains MD5 hash for the ZIP archive. You might want to use this file to check integrity of the error report.\n\n");

    sText += _T("For additional information, see FAQ http://code.google.com/p/crashrpt/wiki/FAQ\n");

    return sText;
}

// This method sends the report over SMTP 
BOOL CErrorReportSender::SendOverSMTP()
{  
	strconv_t strconv;

	// Check our config - should we send the report over SMTP or not?
    if(m_CrashInfo.m_uPriorities[CR_SMTP]==CR_NEGATIVE_PRIORITY)
    {
        m_Assync.SetProgress(_T("Sending error report over SMTP is disabled (negative priority); skipping."), 0);
        return FALSE;
    }

	// Check recipient's email
    if(m_CrashInfo.m_sEmailTo.IsEmpty())
    {
        m_Assync.SetProgress(_T("No E-mail address is specified for sending error report over SMTP; skipping."), 0);
        return FALSE;
    }

	// Fill in email fields
    // If the sender is not defined, use the first e-mail address from the recipient list.
	if (m_CrashInfo.GetReport(m_nCurReport)->GetEmailFrom().IsEmpty()) 
	{
		// Force a copy of the string. Simple assignment just references the data of g_CrashInfo.m_sEmailTo. 
		// The copy string will be modified by strtok.
		CString copy((LPCTSTR)m_CrashInfo.m_sEmailTo, m_CrashInfo.m_sEmailTo.GetLength());
		TCHAR   separators[] = _T(";, ");
		TCHAR  *context		 = 0;
		TCHAR  *to			 = _tcstok_s(const_cast<LPTSTR>((LPCTSTR)copy), separators, &context);
		m_EmailMsg.SetSenderAddress((to == 0 || *to == 0) ? m_CrashInfo.m_sEmailTo : to);
	} 
	else
		m_EmailMsg.SetSenderAddress(m_CrashInfo.GetReport(m_nCurReport)->GetEmailFrom());
	m_EmailMsg.AddRecipients(m_CrashInfo.m_sEmailTo);    
	m_EmailMsg.SetSubject(m_CrashInfo.m_sEmailSubject);

    if(m_CrashInfo.m_sEmailText.IsEmpty())
        m_EmailMsg.SetText(FormatEmailText());
    else
        m_EmailMsg.SetText(m_CrashInfo.m_sEmailText);

	m_EmailMsg.AddAttachment(m_sZipName);  

    // Create and attach MD5 hash file
    CString sErrorRptHash;
    CalcFileMD5Hash(m_sZipName, sErrorRptHash);
    CString sFileTitle = m_sZipName;
    sFileTitle.Replace('/', '\\');
    int pos = sFileTitle.ReverseFind('\\');
    if(pos>=0)
        sFileTitle = sFileTitle.Mid(pos+1);
    sFileTitle += _T(".md5");
    CString sTempDir;
    Utility::getTempDirectory(sTempDir);
    CString sTmpFileName = sTempDir +_T("\\")+ sFileTitle;
    FILE* f = NULL;
    _TFOPEN_S(f, sTmpFileName, _T("wt"));
    if(f!=NULL)
    {   
        LPCSTR szErrorRptHash = strconv.t2a(sErrorRptHash.GetBuffer(0));
        fwrite(szErrorRptHash, strlen(szErrorRptHash), 1, f);
        fclose(f);
        m_EmailMsg.AddAttachment(sTmpFileName);  
    }

    // Set SMTP proxy server (if specified)
    if ( !m_CrashInfo.m_sSmtpProxyServer.IsEmpty())
        m_SmtpClient.SetSmtpServer( m_CrashInfo.m_sSmtpProxyServer, m_CrashInfo.m_nSmtpProxyPort);

	// Set SMTP login and password
	m_SmtpClient.SetAuthParams(m_CrashInfo.m_sSmtpLogin, m_CrashInfo.m_sSmtpPassword);

    // Send mail assynchronously
    int res = m_SmtpClient.SendEmailAssync(&m_EmailMsg, &m_Assync); 
    return (res==0);
}

// This method sends the report over Simple MAPI
BOOL CErrorReportSender::SendOverSMAPI()
{  
    strconv_t strconv;

	// Check our config - should we send the report over Simple MAPI or not?
    if(m_CrashInfo.m_uPriorities[CR_SMAPI]==CR_NEGATIVE_PRIORITY)
    {
        m_Assync.SetProgress(_T("Sending error report over SMAPI is disabled (negative priority); skipping."), 0);
        return FALSE;
    }

	// Check recipient's email address
    if(m_CrashInfo.m_sEmailTo.IsEmpty())
    {
        m_Assync.SetProgress(_T("No E-mail address is specified for sending error report over Simple MAPI; skipping."), 0);
        return FALSE;
    }

	// Do not send if we are in silent mode
    if(m_CrashInfo.m_bSilentMode)
    {
        m_Assync.SetProgress(_T("Simple MAPI may require user interaction (not acceptable for non-GUI mode); skipping."), 0);
        return FALSE;
    }

	// Update progress
    m_Assync.SetProgress(_T("Sending error report using Simple MAPI"), 0, false);
    m_Assync.SetProgress(_T("Initializing MAPI"), 1);

	// Initialize MAPI
    BOOL bMAPIInit = m_MapiSender.MAPIInitialize();
    if(!bMAPIInit)
    {
        m_Assync.SetProgress(m_MapiSender.GetLastErrorMsg(), 100, false);
        return FALSE;
    }

	// Request user confirmation
    if(m_SendAttempt!=0 && m_MailClientConfirm==NOT_CONFIRMED_YET)
    {
        m_Assync.SetProgress(_T("[confirm_launch_email_client]"), 0);
        int confirm = 1;
        m_Assync.WaitForFeedback(confirm);
        if(confirm!=0)
        {
			m_MailClientConfirm = NOT_ALLOWED;
            m_Assync.SetProgress(_T("Cancelled by user"), 100, false);
            return FALSE;
        }
		else
		{
			m_MailClientConfirm = ALLOWED;
		}
    }

	if(m_MailClientConfirm != ALLOWED)
	{
		m_Assync.SetProgress(_T("Not allowed to launch E-mail client."), 100, false);
		return FALSE;
	}

	// Detect mail client (Microsoft Outlook, Mozilla Thunderbird and so on)
    CString msg;
    CString sMailClientName;
    m_MapiSender.DetectMailClient(sMailClientName);

	msg.Format(_T("Launching the default email client (%s)"), sMailClientName);
    m_Assync.SetProgress(msg, 10);

	// Fill in email fields
    m_MapiSender.SetFrom(m_CrashInfo.GetReport(m_nCurReport)->GetEmailFrom());
	
	// The copy string will be modified by strtok.
	CString copy		 = m_CrashInfo.m_sEmailTo;
	TCHAR   separators[] = _T(";, ");
	TCHAR  *context		 = 0;
	TCHAR  *to			 = _tcstok_s(const_cast<LPTSTR>((LPCTSTR)copy), separators, &context);	
	while (to != 0) 
	{
		m_MapiSender.AddRecipient(_T("SMTP:")+CString(to));
		to=_tcstok_s(NULL, separators, &context);		
	};    

    m_MapiSender.SetSubject(m_CrashInfo.m_sEmailSubject);
    CString sFileTitle = m_sZipName;
    sFileTitle.Replace('/', '\\');
    int pos = sFileTitle.ReverseFind('\\');
    if(pos>=0)
        sFileTitle = sFileTitle.Mid(pos+1);

    if(m_CrashInfo.m_sEmailText.IsEmpty())
        m_MapiSender.SetMessage(FormatEmailText());
    else
        m_MapiSender.SetMessage(m_CrashInfo.m_sEmailText);
    m_MapiSender.AddAttachment(m_sZipName, sFileTitle);

    // Create and attach MD5 hash file
    CString sErrorRptHash;
    CalcFileMD5Hash(m_sZipName, sErrorRptHash);
    sFileTitle += _T(".md5");
    CString sTempDir;
    Utility::getTempDirectory(sTempDir);
    CString sTmpFileName = sTempDir +_T("\\")+ sFileTitle;
    FILE* f = NULL;
    _TFOPEN_S(f, sTmpFileName, _T("wt"));
    if(f!=NULL)
    { 
        LPCSTR szErrorRptHash = strconv.t2a(sErrorRptHash.GetBuffer(0));
        fwrite(szErrorRptHash, strlen(szErrorRptHash), 1, f);
        fclose(f);
        m_MapiSender.AddAttachment(sTmpFileName, sFileTitle);  
    }

	// Send email
    BOOL bSend = m_MapiSender.Send();
    if(!bSend)
        m_Assync.SetProgress(m_MapiSender.GetLastErrorMsg(), 100, false);
    else
        m_Assync.SetProgress(_T("Sent OK"), 100, false);

    return bSend;
}

CString CErrorReportSender::GetLangStr(LPCTSTR szSection, LPCTSTR szName)
{
	return Utility::GetINIString(m_CrashInfo.m_sLangFileName, szSection, szName);
}

void CErrorReportSender::ExportReport(LPCTSTR szOutFileName)
{
	SetExportFlag(TRUE, szOutFileName);
    DoWork(COMPRESS_REPORT);    
}

BOOL CErrorReportSender::SendRecentReports()
{
	// This method sends all queued error reports in turn.
	m_bSendingNow = TRUE;
	m_bErrors = FALSE;

	// Init log file
	Utility::RecycleFile(GetLogFilePath(), TRUE);
	CString sCurTime;
    Utility::GetSystemTimeUTC(sCurTime);
    sCurTime.Replace(':', '-');    
	CString sLogFile;
	sLogFile.Format(_T("%s\\CrashRpt-Log-%s.txt"), 
		m_CrashInfo.m_sUnsentCrashReportsFolder, sCurTime);
	m_Assync.InitLogFile(sLogFile);

	// Send error reports in turn
	BOOL bSend = TRUE;
	int nReport = -1;
	while(bSend)
	{
		// Ask GUI for hint what report to send next.
		// This is needed to send error report in the same order they appear in the list
		// (list may be sorted in different order).
		if(IsWindow(m_hWndNotify))
			nReport = (int)::SendMessage(m_hWndNotify, WM_NEXT_ITEM_HINT, 0, 0);

		bSend = SendNextReport(nReport);
	}
	
	// Close log
	m_Assync.CloseLogFile();

	// Notify GUI about completion
	if(IsWindow(m_hWndNotify))
		::PostMessage(m_hWndNotify, WM_DELIVERY_COMPLETE, 0, 0);	

	// Done
	m_bSendingNow = FALSE;
    return TRUE;
}

BOOL CErrorReportSender::SendNextReport(int nReport)
{  	
	if(m_Assync.IsCancelled())
		return FALSE;	// Return FALSE to prevent sending next report

	CErrorReportInfo* eri = NULL;
	if(nReport != -1)
	{
		eri = m_CrashInfo.GetReport(nReport);
		if(!eri->IsSelected() || eri->GetDeliveryStatus()!=PENDING)
			eri = NULL;
	}

	if(eri==NULL)
	{
		// Walk through error reports 
		int i;
		for(i=0; i<m_CrashInfo.GetReportCount(); i++)
		{
			if(!m_CrashInfo.GetReport(i)->IsSelected())
				continue; // Skip this (not selected item)
			            
			if(m_CrashInfo.GetReport(i)->GetDeliveryStatus()==PENDING)
			{
				nReport = i;
				eri = m_CrashInfo.GetReport(i);
				break;
			}
		}
	}
    
	if(eri==NULL)
	{
		// Return FALSE to prevent sending next report
		return FALSE;
	}

	// Save current report index			
	m_nCurReport = nReport;

	eri->SetDeliveryStatus(INPROGRESS);

	// Notify GUI about current item change
	if(IsWindow(m_hWndNotify))
		::PostMessage(m_hWndNotify, WM_ITEM_STATUS_CHANGED, (WPARAM)m_nCurReport, (LPARAM)eri->GetDeliveryStatus());	
						
    // Add a message to log
	CString sMsg;
	sMsg.Format(_T(">>> Performing actions with error report: '%s'"), 
					m_CrashInfo.GetReport(m_nCurReport)->GetErrorReportDirName());
	m_Assync.SetProgress(sMsg, 0, false);

	// Send report
    if(!DoWork(COMPRESS_REPORT|SEND_REPORT))
	{
		m_bErrors = TRUE;
		eri->SetDeliveryStatus(FAILED);
	}
	else
	{
		eri->SetDeliveryStatus(DELIVERED);
	}

	// Notify GUI about current item change
	if(IsWindow(m_hWndNotify))
		::PostMessage(m_hWndNotify, WM_ITEM_STATUS_CHANGED, (WPARAM)m_nCurReport, (LPARAM)eri->GetDeliveryStatus());

	// Return TRUE to indicate next report can be sent
    return TRUE;
}

BOOL CErrorReportSender::IsSendingNow()
{
	// Return TRUE if currently sending error report(s)
	return m_bSendingNow;
}


BOOL CErrorReportSender::HasErrors()
{
	return m_bErrors;
}

CString CErrorReportSender::GetLogFilePath()
{
	// Return path to log file
	return m_Assync.GetLogFilePath();
}

int CErrorReportSender::TerminateAllCrashSenderProcesses()
{
	// This method looks for all runing CrashSender.exe processes
	// and terminates each one. This may be needed when an application's installer
	// wants to shutdown all crash sender processes running in background
	// to replace the locked files.
	
	// Format process name.
	CString sProcessName = _T("CrashSender.exe");
#ifdef USE_VERSION
#ifdef _DEBUG
	sProcessName.Format(_T("CrashSender%dd.exe"), CRASHRPT_VER);
#else
	sProcessName.Format(_T("CrashSender%d.exe"), CRASHRPT_VER);
#endif
#endif

	PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

	// Create the list of all processes in the system
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
		// Walk through processes
        while (Process32Next(snapshot, &entry) == TRUE)
        {
			// Compare process name
            if (_tcsicmp(entry.szExeFile, sProcessName) == 0 &&
				entry.th32ProcessID != GetCurrentProcessId())
            {  				
				// Open process handle
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, entry.th32ProcessID);

				// Terminate process.
                TerminateProcess(hProcess, 1);

                CloseHandle(hProcess);
            }
        }
    }

	// Clean up
    CloseHandle(snapshot);

    return 0;
}

BOOL CErrorReportSender::RecordVideo()
{	
	// The following method enters the video recording loop
	// and returns when the parent process signals the event.

	DWORD dwFlags = m_CrashInfo.m_dwVideoFlags;	  

	// Show notification dialog
	if((dwFlags & CR_AV_NO_GUI) == 0)
	{
		CVideoRecDlg dlg;
		INT_PTR res = dlg.DoModal(
			IsWindow(m_CrashInfo.m_hWndVideoParent)?m_CrashInfo.m_hWndVideoParent:NULL);
		if(res!=IDOK)
			return FALSE;
	}

    // Determine screenshot type.
    SCREENSHOT_TYPE type = SCREENSHOT_TYPE_VIRTUAL_SCREEN;
    if((dwFlags&CR_AV_MAIN_WINDOW)!=0) // We need to capture the main window
		type = SCREENSHOT_TYPE_MAIN_WINDOW;
    else if((dwFlags&CR_AV_PROCESS_WINDOWS)!=0) // Capture all process windows
		type = SCREENSHOT_TYPE_ALL_PROCESS_WINDOWS;
    else // (dwFlags&CR_AV_VIRTUAL_SCREEN)!=0 // Capture the virtual screen
		type = SCREENSHOT_TYPE_VIRTUAL_SCREEN;

	// Determine what encoding quality to use
	int quality = 10;
	if((dwFlags&CR_AV_QUALITY_GOOD)!=0)
		quality = 40;
	else if((dwFlags&CR_AV_QUALITY_BEST)!=0)
		quality = 63;
	
	// Add a message to log
	CString sMsg;
	sMsg.Format(_T("Start video recording."));
	m_Assync.SetProgress(sMsg, 0, false);

	// Open the event we will use for synchronization with the parent process
	CString sEventName;
    sEventName.Format(_T("Local\\CrashRptEvent_%s_2"), GetCrashInfo()->GetReport(0)->GetCrashGUID());
    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, sEventName);
	if(hEvent==NULL)
	{
		// Add a message to log
		sMsg.Format(_T("Error opening event."));
		m_Assync.SetProgress(sMsg, 0, false);
		return FALSE;
	}
    
	// Init video recorder object
	if(!m_VideoRec.Init(m_CrashInfo.GetReport(m_nCurReport)->GetErrorReportDirName(),
				type, m_CrashInfo.m_dwProcessId, m_CrashInfo.m_nVideoDuration,
				m_CrashInfo.m_nVideoFrameInterval,
				quality, &m_CrashInfo.m_DesiredFrameSize))
	{
		// Add a message to log
		sMsg.Format(_T("Error initializing video recorder."));
		m_Assync.SetProgress(sMsg, 0, false);
		return FALSE;
	}

	// Video recording loop.
	for(;;)
	{
		// Wait for a while
		BOOL bExitLoop = WAIT_OBJECT_0==WaitForSingleObject(hEvent, m_CrashInfo.m_nVideoFrameInterval);

		// This will record a single BMP file
		m_VideoRec.RecordVideoFrame();

		if(bExitLoop)
			break; // Event is signaled; break the loop
					
		// Check if the client app is still alive
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, m_CrashInfo.m_dwProcessId);
		if(hProcess==NULL)
			return FALSE; // Process seems to be terminated!

		// If process handle is still accessible, check its exit code
		DWORD dwExitCode = 1;
		if(GetExitCodeProcess(hProcess, &dwExitCode) && dwExitCode!=STILL_ACTIVE)
		{
			CloseHandle(hProcess);
			return FALSE; // Process seems to exit!
		}

		CloseHandle(hProcess);
	}

	// Add a message to log
	sMsg.Format(_T("Video recording completed."));
	m_Assync.SetProgress(sMsg, 0, false);

	// Return TRUE to indicate video recording completed successfully.
	return TRUE;
}

BOOL CErrorReportSender::EncodeVideo()
{
	// Add a message to log
    m_Assync.SetProgress(_T("[encoding_video]"), 0);    

    // Check if video capture is allowed
    if(!m_VideoRec.IsInitialized())
    {
        // Add a message to log
        m_Assync.SetProgress(_T("Desktop video recording disabled; skipping."), 0);    
        // Exit, nothing to do here
        return TRUE;
    }
	
	 // Add a message to log
    m_Assync.SetProgress(_T("Encoding recorded video, please wait..."), 1);    
	
	// Encode recorded video to a webm file
	if(!m_VideoRec.EncodeVideo())
	{
		// Add a message to log
		m_Assync.SetProgress(_T("Error encoding video."), 100, false);    
		return FALSE;
	}

	bool bAllowDelete = (m_CrashInfo.m_dwVideoFlags&CR_AV_ALLOW_DELETE)!=0;

	// Add file to crash report
	ERIFileItem fi;
	fi.m_sSrcFile = m_VideoRec.GetOutFile();
	fi.m_sDestFile = Utility::GetFileName(fi.m_sSrcFile);
    fi.m_sDesc = Utility::GetINIString(m_CrashInfo.m_sLangFileName, _T("DetailDlg"), _T("DescVideo"));  
	fi.m_bAllowDelete = bAllowDelete;
    m_CrashInfo.GetReport(m_nCurReport)->AddFileItem(&fi);

	// Add a message to log
    m_Assync.SetProgress(_T("Finished encoding video."), 100, false);    

	return TRUE;
}


