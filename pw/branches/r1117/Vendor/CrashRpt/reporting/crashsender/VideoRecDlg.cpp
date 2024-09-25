/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: VideoRecDlg.cpp
// Description: Video Recording Dialog.
// Authors: zexspectrum
// Date: Sep 2013

#include "stdafx.h"
#include "resource.h"
#include "VideoRecDlg.h"
#include "ErrorReportSender.h"

LRESULT CVideoRecDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{  	
	m_statText = GetDlgItem(IDC_TEXT);
	m_btnAllow = GetDlgItem(IDOK);
	m_btnCancel = GetDlgItem(IDCANCEL);

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	// Set dialog caption.
	CString sMsg;
	sMsg.Format(pSender->GetLangStr(_T("VideoRecDlg"), _T("DlgCaption")), 
		pSender->GetCrashInfo()->m_sAppName);
    SetWindowText(sMsg);

	sMsg.Format(pSender->GetLangStr(_T("VideoRecDlg"), _T("Text")),
		pSender->GetCrashInfo()->m_sAppName);
	m_statText.SetWindowText(sMsg);


	m_btnAllow.SetWindowText(pSender->GetLangStr(_T("VideoRecDlg"), _T("Allow")));
	m_btnCancel.SetWindowText(pSender->GetLangStr(_T("VideoRecDlg"), _T("Cancel")));

    // Center the dialog on the screen.
    CenterWindow();
	   
    return TRUE;
}

LRESULT CVideoRecDlg::OnOK(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{   
	EndDialog(IDOK);
    return 0;
}

LRESULT CVideoRecDlg::OnCancel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{   
	EndDialog(IDCANCEL);
    return 0;
}



