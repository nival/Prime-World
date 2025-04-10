/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#include "stdafx.h"
#include "Tests.h"
#include "CrashRpt.h"
#include "Utility.h"
#include "strconv.h"
#include "TestUtils.h"
#include "strconv.h"
#include "CrashRptProbe.h"

#ifndef _DEBUG

class ExceptionHandlerTests : public CTestSuite
{
    BEGIN_TEST_MAP(ExceptionHandlerTests, "Exception handler tests")
        REGISTER_TEST(Test_CatchException)
        

    END_TEST_MAP()

    void SetUp();
    void TearDown();

    void Test_CatchException();	
};

REGISTER_TEST_SUITE( ExceptionHandlerTests );

void ExceptionHandlerTests::SetUp()
{
}

void ExceptionHandlerTests::TearDown()
{
}

void ExceptionHandlerTests::Test_CatchException()
{       
	// This test is aimed to check if a CrashRpt-enabled client application catches
	// the exceptions in its main and worker threads. This test runs the test app
	// with special command line args to cause different types of exceptions in
	// test app's main and worker thread and checks if crash report is generated
	// and if exception type is correct.

	CString sExePath = Utility::GetModuleName(NULL);
	CString sTmpFolder;

	struct _exception_param
	{
		LPCTSTR szCmdLine;           // Command line arguments
		LPCTSTR szExceptionType;     // Expected exception type read from crash report (for main thread)
		LPCTSTR szExceptionTypeInWorkerThread; // Expected exception type read from crash report (for worker thread)
	};

	const int PARAM_COUNT = 13;
	_exception_param aParams[PARAM_COUNT] = 
	{		
		{_T("/exception /seh"), _T("11 SIGSEGV signal"), _T("0 SEH exception")},
		{_T("/exception /terminate"), _T("1 terminate call"), _T("1 terminate call")},
		{_T("/exception /unexpected"), _T("2 unexpected call"), _T("2 unexpected call")},
		{_T("/exception /purecall"), _T("3 pure virtual call"), _T("3 pure virtual call")},
		{_T("/exception /new"), _T("4 new operator fault"), _T("4 new operator fault")},
		//{_T("/exception /security"), _T("5 security error"), _T("5 security error")},
		{_T("/exception /invparam"), _T("6 invalid parameter"), _T("6 invalid parameter")},
		{_T("/exception /sigabrt"), _T("7 SIGABRT signal"), _T("7 SIGABRT signal")},		
		{_T("/exception /sigfpe"), _T("8 SIGFPE signal"), _T("0 SEH exception")},
		{_T("/exception /sigill"), _T("9 SIGILL signal"), _T("9 SIGILL signal")},
		{_T("/exception /sigint"), _T("10 SIGINT signal"), _T("10 SIGINT signal")},
		{_T("/exception /sigsegv"), _T("11 SIGSEGV signal"), _T("11 SIGSEGV signal")},
		{_T("/exception /sigterm"), _T("12 SIGTERM signal"), _T("12 SIGTERM signal")},	
		{_T("/manual_report"), _T("0 SEH exception"), _T("0 SEH exception")}	
	};

	int j;
	for(j=0; j<2; j++)
	{
		int i;
		for(i=0; i<PARAM_COUNT; i++)
		{
			if(j==0)
				printf(".");
			else
				printf(",");
			fflush(stdout);

			// Create a temporary folder 
			CString sAppDataFolder;
					
			Utility::GetSpecialFolder(CSIDL_APPDATA, sAppDataFolder);
			sTmpFolder = sAppDataFolder+_T("\\CrashRptExceptionTest");
			Utility::RecycleFile(sTmpFolder, TRUE); // remove folder if exists
			BOOL bCreateFolder = Utility::CreateFolder(sTmpFolder);
			strconv_t strconv;
			TEST_ASSERT_MSG(bCreateFolder, "Error creating temp folder %s", strconv.t2a(sTmpFolder.GetBuffer(0)));

			// Format command line
			TCHAR szCmdLine[_MAX_PATH]=_T("");
			_tcscat_s(szCmdLine, _MAX_PATH, _T("\""));
			_tcscat_s(szCmdLine, _MAX_PATH, sExePath.GetBuffer(0));
			_tcscat_s(szCmdLine, _MAX_PATH, _T("\" "));    
			_tcscat_s(szCmdLine, _MAX_PATH, aParams[i].szCmdLine);		
			if(j==1)
			{
				_tcscat_s(szCmdLine, _MAX_PATH, _T(" /exception_in_worker_thread"));    
			}

			STARTUPINFO si;
			memset(&si, 0, sizeof(STARTUPINFO));
			si.cb = sizeof(STARTUPINFO);

			PROCESS_INFORMATION pi;
			memset(&pi, 0, sizeof(PROCESS_INFORMATION)); 
		
			// Launch this executable with special params causing crash
			BOOL bCreateProcess = CreateProcess(
				sExePath, (LPWSTR)strconv.t2w(szCmdLine), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
			TEST_ASSERT_MSG(bCreateProcess, "Error creating process %s", strconv.t2a(szCmdLine));

			// Wait until process terminates
			WaitForSingleObject(pi.hProcess, INFINITE);
		
			int k;
			for(k=0; k<50; k++)
			{
				// Wait some more time to let CrashRpt create error report file
				Sleep(100);

				// Look for crash report file		
				CFindFile ff;
				BOOL bFind = ff.FindFile(sTmpFolder+_T("\\*.zip"));	

				if(!bFind)
					continue;

				// Try to open file
				FILE* f = NULL;
				_TFOPEN_S(f, ff.GetFileName(), _T("rb"));
				if(f!=NULL)
				{
					fclose(f);
					break;
				}
			}

			{
				// Look for crash report file		
				CFindFile ff;
				BOOL bFind = ff.FindFile(sTmpFolder+_T("\\*.zip"));		
				TEST_ASSERT_MSG(bFind, "Could not find generated crash report file for exception type: %s", strconv.w2a(aParams[i].szExceptionType));

				// Open crash report		
				CString sReportName = sTmpFolder + _T("\\");
				sReportName += ff.m_fd.cFileName;
				CrpHandle hReport;
				int nOpenResult = crpOpenErrorReport(sReportName, NULL, NULL, 0, &hReport);
				TEST_ASSERT_MSG(nOpenResult==0 && hReport!=0, "Error opening error report file %s", strconv.t2a(sReportName.GetBuffer(0)));

				// Get exception type from report
				const int BUFF_SIZE = 256;
				TCHAR szBuffer[BUFF_SIZE];		
				int nResult = crpGetPropertyW(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_EXCEPTION_TYPE, 0, szBuffer, BUFF_SIZE, NULL);
				TEST_ASSERT_MSG(nResult==0, "Error getting property from error report");

				int nCompareResult = _tcscmp(szBuffer, j==0?aParams[i].szExceptionType:aParams[i].szExceptionTypeInWorkerThread);
				TEST_ASSERT_MSG(nCompareResult==0, "Invalid exception type: %s, while expected: %s", strconv.w2a(szBuffer), strconv.w2a(aParams[i].szExceptionType));

				// Get exception thread ID
				nResult = crpGetPropertyW(hReport, CRP_TBL_MDMP_MISC, CRP_COL_EXCEPTION_THREAD_ROWID, 0, szBuffer, BUFF_SIZE, NULL);
				TEST_ASSERT_MSG(nResult==0, "Error getting exception thread ID");
				int nExceptionThreadRowId = _ttoi(szBuffer);

				// Get exception thread's stack table ID
				nResult = crpGetPropertyW(hReport, CRP_TBL_MDMP_THREADS, CRP_COL_THREAD_STACK_TABLEID, nExceptionThreadRowId, szBuffer, BUFF_SIZE, NULL);
				TEST_ASSERT_MSG(nResult==0, "Error getting thread's stack table ID");
				CString sStackTraceTableId = szBuffer;

#ifndef _WIN64
				if(j==0)
				{
					if(i==0) // SEH
					{
						// Get stack frames
						int nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 0, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT_MSG(nResult==0, "Error getting symbol name");
						TEST_ASSERT(_tcscmp(szBuffer, _T("crEmulateCrash"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 1, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT_MSG(nResult==0, "Error getting symbol name");
						TEST_ASSERT(_tcscmp(szBuffer, _T("wmain"))==0);
					}
					else if(i==1) // terminate
					{
						// Get stack frames
						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 0, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("CCrashHandler::GenerateErrorReport"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 1, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("CCrashHandler::TerminateHandler"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 3, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("crEmulateCrash"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 4, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("wmain"))==0);					
					}
					else if(i==2) // unexpected
					{
						// Get stack frames
						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 0, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("CCrashHandler::GenerateErrorReport"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 1, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("CCrashHandler::UnexpectedHandler"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 3, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
#ifndef CRASHRPT_LIB
						TEST_ASSERT(_tcscmp(szBuffer, _T("wmain"))==0);		
#else
						TEST_ASSERT(_tcscmp(szBuffer, _T("crEmulateCrash"))==0);					
#endif
					}
					else if(i==3) // pure call
					{
						// Get stack frames
						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 0, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("CCrashHandler::GenerateErrorReport"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 1, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("CCrashHandler::PureCallHandler"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 3, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
#ifndef CRASHRPT_LIB
						TEST_ASSERT(_tcscmp(szBuffer, _T("CDerived::~CDerived"))==0);		
#else
						TEST_ASSERT(_tcscmp(szBuffer, _T("CBase::~CBase"))==0);					
#endif
					}
					else if(i==13) // manual
					{
						// Get stack frames
						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 0, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("CCrashHandler::GenerateErrorReport"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 1, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("crGenerateErrorReport"))==0);
												
						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 2, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);

						TEST_ASSERT(_tcscmp(szBuffer, _T("wmain"))==0);					
					}
				}
				else if(j==1)
				{
					if(i==0) // SEH
					{
						// Get stack frames
						int nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 0, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("crEmulateCrash"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 1, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("CrashThread"))==0);					
					}
					else if(i==1) // terminate
					{
						// Get stack frames
						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 0, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("CCrashHandler::GenerateErrorReport"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 1, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("CCrashHandler::TerminateHandler"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 3, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("crEmulateCrash"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 4, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("CrashThread"))==0);					
					}					
					else if(i==13) // manual
					{
						// Get stack frames
						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 0, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("CCrashHandler::GenerateErrorReport"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 1, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("crGenerateErrorReport"))==0);

						nResult = crpGetPropertyW(hReport, sStackTraceTableId, CRP_COL_STACK_SYMBOL_NAME, 2, szBuffer, BUFF_SIZE, NULL);
						TEST_ASSERT(nResult==0);
						TEST_ASSERT(_tcscmp(szBuffer, _T("CrashThread"))==0);					
					}
				}
#endif //!_WIN64

				// Close report
				crpCloseErrorReport(hReport);
							
			}

			// Remove folder
			Utility::RecycleFile(sTmpFolder, TRUE);
		}
	}

    __TEST_CLEANUP__;

	// Remove folder
	Utility::RecycleFile(sTmpFolder, TRUE);
}


#endif