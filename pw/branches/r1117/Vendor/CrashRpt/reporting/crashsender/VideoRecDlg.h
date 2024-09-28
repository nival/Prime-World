/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: VideoRecDlg.h
// Description: Video Recording Dialog.
// Authors: zexspectrum
// Date: Sep 2013

#pragma once
#include "stdafx.h"
#include "resource.h"

// class CVideoRecDlg
// Implements video recording notification dialog.
class CVideoRecDlg : 
    public CDialogImpl<CVideoRecDlg>    
{
public:
    enum { IDD = IDD_VIDEOREC };

    BEGIN_MSG_MAP(CVideoRecDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDOK, OnOK)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)            
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	CStatic m_statText;
	CButton m_btnAllow;
	CButton m_btnCancel;
};