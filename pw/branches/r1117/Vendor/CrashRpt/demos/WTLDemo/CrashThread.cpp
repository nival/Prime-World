/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#include "stdafx.h"
#include "CrashThread.h"
#include <exception>
#include <signal.h>
#include <assert.h>

// Tests crGenerateErrorReport
void test_generate_report()
{
    CR_EXCEPTION_INFO ei;
    memset(&ei, 0, sizeof(CR_EXCEPTION_INFO));
    ei.cb = sizeof(CR_EXCEPTION_INFO);
    ei.exctype = CR_SEH_EXCEPTION;
    ei.code = 0x1234;
    ei.pexcptrs = NULL;
    ei.bManual = TRUE; // Signal the report is being generated manually.

    int nResult = crGenerateErrorReport(&ei);
    if(nResult!=0)
    {
        TCHAR szErrorMsg[256];
        CString sError = _T("Error generating error report!\nErrorMsg:");
        crGetLastErrorMsg(szErrorMsg, 256);
        sError+=szErrorMsg;
        MessageBox(NULL, sError, 0, 0);
    }
}

DWORD WINAPI CrashThread(LPVOID pParam)
{
    CrashThreadInfo* pInfo = (CrashThreadInfo*)pParam;

    // Install per-thread exception handlers
    CrThreadAutoInstallHelper cr_install_helper(0);

    for(;;)
    {
        // Wait until wake up event is signaled
        WaitForSingleObject(pInfo->m_hWakeUpEvent, INFINITE);   

        if(pInfo->m_bStop)
            break; // Exit the loop

        if(pInfo->m_ExceptionType==128)
        {
            // Test generate report manually
            test_generate_report();
        }
        else if(crEmulateCrash(pInfo->m_ExceptionType)!=0)
        {
            // Test exception handler
            TCHAR szErrorMsg[256];
            CString sError = _T("Error creating exception situation!\nErrorMsg:");
            crGetLastErrorMsg(szErrorMsg, 256);
            sError+=szErrorMsg;
            MessageBox(NULL, sError, _T("Error"), 0);    
        }
    }

    // Exit this thread
    return 0;
}




