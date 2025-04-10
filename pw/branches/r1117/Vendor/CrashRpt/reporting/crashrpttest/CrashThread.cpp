/************************************************************************************* 
  This file is a part of CrashRpt library.

  Copyright (c) 2003, Michael Carruth
  All rights reserved.
 
  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:
 
   * Redistributions of source code must retain the above copyright notice, this 
     list of conditions and the following disclaimer.
 
   * Redistributions in binary form must reproduce the above copyright notice, 
     this list of conditions and the following disclaimer in the documentation 
     and/or other materials provided with the distribution.
 
   * Neither the name of the author nor the names of its contributors 
     may be used to endorse or promote products derived from this software without 
     specific prior written permission.
 

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************************/

#include "stdafx.h"
#include "CrashThread.h"
#include <exception>
#include <signal.h>
#include <assert.h>

// Tests crExceptionFilter
void test_seh()
{
  __try
  {
    int nResult = crEmulateCrash(CR_NONCONTINUABLE_EXCEPTION);
    if(nResult!=0)
    {      
      MessageBox(NULL, _T("Error raising noncontinuable exception!"), _T("Error"), 0);    
    }
  }
  __except(crExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
  {    
    // Terminate program
    ExitProcess(1);
  }
}

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
    else if(pInfo->m_ExceptionType==CR_NONCONTINUABLE_EXCEPTION)
    {
      // Test crExceptionFilter
      test_seh();
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




