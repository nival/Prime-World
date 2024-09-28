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

// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "MainDlg.h"
#include "CrashThread.h"
#include <assert.h>

#define MANUAL_REPORT 128

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	return FALSE;
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

  int nItem = 0;

  m_cboThread = GetDlgItem(IDC_THREAD);

  nItem = m_cboThread.AddString(_T("Main thread"));
  m_cboThread.SetItemData(nItem, 0);
  
  nItem = m_cboThread.AddString(_T("Worker thread"));
  m_cboThread.SetItemData(nItem, 1);

  m_cboThread.SetCurSel(0);

  m_cboExcType = GetDlgItem(IDC_EXCTYPE);
  
  nItem = m_cboExcType.AddString(_T("SEH exception"));
  m_cboExcType.SetItemData(nItem, CR_SEH_EXCEPTION);

  nItem = m_cboExcType.AddString(_T("terminate"));
  m_cboExcType.SetItemData(nItem, CR_CPP_TERMINATE_CALL);

  nItem = m_cboExcType.AddString(_T("unexpected"));
  m_cboExcType.SetItemData(nItem, CR_CPP_UNEXPECTED_CALL);

  nItem = m_cboExcType.AddString(_T("pure virtual method call"));
  m_cboExcType.SetItemData(nItem, CR_CPP_PURE_CALL);

  nItem = m_cboExcType.AddString(_T("new operator fault"));
  m_cboExcType.SetItemData(nItem, CR_CPP_NEW_OPERATOR_ERROR);

  nItem = m_cboExcType.AddString(_T("buffer overrun"));
  m_cboExcType.SetItemData(nItem, CR_CPP_SECURITY_ERROR);

  nItem = m_cboExcType.AddString(_T("invalid parameter"));
  m_cboExcType.SetItemData(nItem, CR_CPP_INVALID_PARAMETER);

  nItem = m_cboExcType.AddString(_T("SIGABRT"));
  m_cboExcType.SetItemData(nItem, CR_CPP_SIGABRT);

  nItem = m_cboExcType.AddString(_T("SIGFPE"));
  m_cboExcType.SetItemData(nItem, CR_CPP_SIGFPE);

  nItem = m_cboExcType.AddString(_T("SIGILL"));
  m_cboExcType.SetItemData(nItem, CR_CPP_SIGILL);

  nItem = m_cboExcType.AddString(_T("SIGINT"));
  m_cboExcType.SetItemData(nItem, CR_CPP_SIGINT);

  nItem = m_cboExcType.AddString(_T("SIGSEGV"));
  m_cboExcType.SetItemData(nItem, CR_CPP_SIGSEGV);

  nItem = m_cboExcType.AddString(_T("SIGTERM"));
  m_cboExcType.SetItemData(nItem, CR_CPP_SIGTERM);

  nItem = m_cboExcType.AddString(_T("throw C++ typed exception"));
  m_cboExcType.SetItemData(nItem, CR_THROW);

  nItem = m_cboExcType.AddString(_T("Manual report"));
  m_cboExcType.SetItemData(nItem, MANUAL_REPORT);

  m_cboExcType.SetCurSel(0);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

  if(m_bRestarted)
  {
    PostMessage(WM_POSTCREATE);    
  }

	return TRUE;
}

LRESULT CMainDlg::OnPostCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
  MessageBox(_T("The application was restarted after crash."), _T("Restarted"), MB_OK);
  return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoCrash();
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog(wID);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

void CMainDlg::DoCrash()
{
  int nSel = m_cboThread.GetCurSel();
  int nThread = (int)m_cboThread.GetItemData(nSel);

  nSel = m_cboExcType.GetCurSel();
  int nExcType = (int)m_cboExcType.GetItemData(nSel);
  
  if(nThread==0) // The main thread
  {    
    if(nExcType==MANUAL_REPORT)
    {
        test_generate_report();
        return;
    }
    else
    {
      int nResult = crEmulateCrash(nExcType);
      if(nResult!=0)
      {
        TCHAR szErrorMsg[256];
        CString sError = _T("Error creating exception situation!\nErrorMsg:");
        crGetLastErrorMsg(szErrorMsg, 256);
        sError+=szErrorMsg;
        MessageBox(sError);
      }
    }  
  }
  else // Worker thread
  {
    extern CrashThreadInfo g_CrashThreadInfo;
    g_CrashThreadInfo.m_ExceptionType = nExcType;
    SetEvent(g_CrashThreadInfo.m_hWakeUpEvent); // wake up the working thread
  }
}

