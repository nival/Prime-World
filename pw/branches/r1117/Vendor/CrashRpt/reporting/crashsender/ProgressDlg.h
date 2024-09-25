/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#pragma once

#include "resource.h"
#include "ErrorReportSender.h"

#define WM_COMPLETECOLLECT (WM_APP+1)

class CProgressDlg : 
	public CDialogImpl<CProgressDlg>,
    public CDialogResize<CProgressDlg>
{
public:

    enum { IDD = IDD_PROGRESSDLG };
		
    enum ActionOnCancel
	{
		DONT_CLOSE, 
		CLOSE_MYSELF, 
		CLOSE_MYSELF_AND_PARENT
	};

    CProgressBarCtrl m_prgProgress;
    CListViewCtrl m_listView;
    CButton m_btnCancel;
    CStatic m_statText;    

    BEGIN_DLGRESIZE_MAP(CProgressDlg)
        DLGRESIZE_CONTROL(IDC_PROGRESS, DLSZ_SIZE_X)
        DLGRESIZE_CONTROL(IDC_LIST, DLSZ_SIZE_X|DLSZ_SIZE_Y)
        DLGRESIZE_CONTROL(IDCANCEL, DLSZ_MOVE_Y)    
    END_DLGRESIZE_MAP()

    BEGIN_MSG_MAP(CProgressDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)
        MESSAGE_HANDLER(WM_TIMER, OnTimer)        
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)    
        COMMAND_ID_HANDLER(ID_MENU1_COPYSEL, OnCopySel)
        COMMAND_ID_HANDLER(ID_MENU1_COPYLOG, OnCopyLog)
        NOTIFY_HANDLER(IDC_LIST, NM_RCLICK, OnListRClick)

        CHAIN_MSG_MAP(CDialogResize<CProgressDlg>)
    END_MSG_MAP()

    // Handler prototypes (uncomment arguments if needed):
    //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnListRClick(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/);
    LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);  
    LRESULT OnCopySel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);  
    LRESULT OnCopyLog(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);  

	// Displays the dialog and starts the timer.
    void Start(BOOL bCollectInfo, BOOL bMakeVisible=TRUE);

	// Stops the timer.
    void Stop();

	// Closes the dialog.
    void CloseDialog(int nVal);

	// This method places the data to clipboard.
    int SetClipboard(CString& sData);

	// Internal variables.
    ActionOnCancel m_ActionOnCancel;  // What to do on cancel.
    ActionOnCancel m_ActionOnClose;   // What to do on close.
};


