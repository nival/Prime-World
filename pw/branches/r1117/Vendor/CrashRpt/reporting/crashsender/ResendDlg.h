/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: ResendDlg.h
// Description: 
// Authors: zexspectrum
// Date: 

#pragma once
#include "stdafx.h"
#include "ProgressDlg.h"
#include "DetailDlg.h"

// Notification code of tray icon
#define WM_RESENDTRAYICON (WM_USER+500)

class CResendDlg;

class CActionProgressDlg : 
    public CDialogImpl<CActionProgressDlg>,   	
    public CDialogResize<CActionProgressDlg>
{
public:
    enum { IDD = IDD_ACTIONPROGRESS };

    BEGIN_DLGRESIZE_MAP(CActionProgressDlg)    
        DLGRESIZE_CONTROL(IDC_CURRENTACTION, DLSZ_SIZE_X)    
        DLGRESIZE_CONTROL(IDC_PROGRESS, DLSZ_SIZE_X)    
        DLGRESIZE_CONTROL(IDC_ACTIONDESC, DLSZ_SIZE_X)        
    END_DLGRESIZE_MAP()

    BEGIN_MSG_MAP(CProgressMultiDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

        CHAIN_MSG_MAP(CDialogResize<CActionProgressDlg>)
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);      
    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);	    

    void CloseDialog(int nVal);

    CStatic m_statCurAction;
    CStatic m_statActionDesc;
    CProgressBarCtrl m_prgProgress;

    CResendDlg* m_pParent;

};


class CResendDlg : 
    public CDialogImpl<CResendDlg>,   
    public CMessageFilter,
    public CDialogResize<CResendDlg>
{
public:
    enum { IDD = IDD_RESEND };

	enum eActionOnClose 
	{
		HIDE, 
		EXIT
	};

    virtual BOOL PreTranslateMessage(MSG* pMsg);

    BEGIN_DLGRESIZE_MAP(CResendDlg)    
        DLGRESIZE_CONTROL(IDC_TEXT, DLSZ_SIZE_X)    
        DLGRESIZE_CONTROL(IDC_LIST, DLSZ_SIZE_X|DLSZ_SIZE_Y)    
        DLGRESIZE_CONTROL(IDC_SELSIZE, DLSZ_SIZE_X|DLSZ_MOVE_Y)    
        DLGRESIZE_CONTROL(IDC_CONSENT, DLSZ_SIZE_X|DLSZ_MOVE_Y)    
        DLGRESIZE_CONTROL(IDC_PRIVACYPOLICY, DLSZ_SIZE_X|DLSZ_MOVE_Y)    
        DLGRESIZE_CONTROL(IDC_LINE, DLSZ_SIZE_X|DLSZ_MOVE_Y)    
        DLGRESIZE_CONTROL(IDC_CRASHRPT, DLSZ_MOVE_X|DLSZ_MOVE_Y)    
        DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_Y)    
        DLGRESIZE_CONTROL(IDC_OTHERACTIONS, DLSZ_MOVE_Y)    
        DLGRESIZE_CONTROL(IDC_SHOWLOG, DLSZ_MOVE_Y)    
        DLGRESIZE_CONTROL(IDD_ACTIONPROGRESS, DLSZ_MOVE_Y|DLSZ_SIZE_X)    
    END_DLGRESIZE_MAP()

    BEGIN_MSG_MAP(CResendDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)
        MESSAGE_HANDLER(WM_TIMER, OnTimer)
        MESSAGE_HANDLER(WM_RESENDTRAYICON, OnTrayIcon)    
		MESSAGE_HANDLER(WM_NEXT_ITEM_HINT, OnNextItemHint)    
		MESSAGE_HANDLER(WM_ITEM_STATUS_CHANGED, OnItemStatusChanged)    
		MESSAGE_HANDLER(WM_DELIVERY_COMPLETE, OnDeliveryComplete)   
		MESSAGE_HANDLER(WM_REPORTSIZECHANGED, OnReportSizeChanged)
        COMMAND_ID_HANDLER(IDOK, OnSendNow)
        COMMAND_ID_HANDLER(IDC_OTHERACTIONS, OnOtherActions)
        COMMAND_ID_HANDLER(IDC_SHOWLOG, OnShowLog)
        COMMAND_ID_HANDLER(ID_MENU3_SHOW, OnPopupShow)
        COMMAND_ID_HANDLER(ID_MENU3_EXIT, OnPopupExit)
        COMMAND_ID_HANDLER(ID_MENU4_REMINDLATER, OnRemindLater)
        COMMAND_ID_HANDLER(ID_MENU4_NEVERREMIND, OnNeverRemind)
		COMMAND_ID_HANDLER(ID_MENU6_SELECTALL, OnPopupSelectAll)
		COMMAND_ID_HANDLER(ID_MENU6_DESELECTALL, OnPopupDeselectAll)
		COMMAND_ID_HANDLER(ID_MENU6_DELETESELECTED, OnPopupDeleteSelected)
		COMMAND_ID_HANDLER(ID_MENU6_DELETEALL, OnPopupDeleteAll)
        NOTIFY_HANDLER(IDC_LIST, LVN_ITEMCHANGING, OnListItemChanging)
        NOTIFY_HANDLER(IDC_LIST, LVN_ITEMCHANGED, OnListItemChanged)
        NOTIFY_HANDLER(IDC_LIST, NM_DBLCLK, OnListDblClick)
		NOTIFY_HANDLER(IDC_LIST, NM_RCLICK, OnListRClick)

        CHAIN_MSG_MAP(CDialogResize<CResendDlg>)
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);  
    LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);	    
    LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);	    
    LRESULT OnTrayIcon(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);	
	LRESULT OnReportSizeChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);	
	LRESULT OnNextItemHint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);  
	LRESULT OnItemStatusChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);  
	LRESULT OnDeliveryComplete(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);  
    LRESULT OnPopupShow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnPopupExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnListItemChanging(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/);
    LRESULT OnListItemChanged(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/);
    LRESULT OnListDblClick(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/);
	LRESULT OnListRClick(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/);
    LRESULT OnSendNow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnOtherActions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnRemindLater(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnNeverRemind(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnShowLog(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnPopupSelectAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnPopupDeselectAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnPopupDeleteSelected(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnPopupDeleteAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	// This method closes the dialog and exits the app
    void CloseDialog(int nVal);

	// Adds or removes tray icon
    void AddTrayIcon(BOOL bAdd);

	// Calculates size of selected error reports and updates the text.
    void UpdateSelectionSize();

	// Shows the balloon
    void DoBalloonTimer();

	// Updates window periodically
    void DoProgressTimer();

	// Hides the window
    void DoHideWindowTimer();

	// Determines what list item is associated with given error report
    int FindListItemByReportIndex(int nReport);

	/* Internal variables */

    CStatic m_statText;
    CCheckListViewCtrl m_listReports;
    CSortListViewCtrl m_listReportsSort;
    CStatic m_statSize;
    CStatic m_statConsent;
    CHyperLink m_linkPrivacyPolicy;
    CButton m_btnSendNow;
    CButton m_btnOtherActions;
    CButton m_btnShowLog;
    CActionProgressDlg m_dlgActionProgress;
    CProgressDlg m_dlgProgress;

	int m_nSendAttempt;
    int m_nTimerTick; // Timer tick counter     
	eActionOnClose m_ActionOnClose; // What to do on dialog close
};

