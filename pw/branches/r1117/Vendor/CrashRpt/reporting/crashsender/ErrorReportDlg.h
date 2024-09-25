/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: ErrorReportDlg.h
// Description: Error Report Dialog.
// Authors: mikecarruth, zexspectrum
// Date: 

#pragma once
#include "stdafx.h"
#include "MailMsg.h"
#include "DetailDlg.h"
#include "ProgressDlg.h"
#include "SequenceLayout.h"

// This message is sent by the system to the Error Report dialog when user clicks the tray icon
#define WM_TRAYICON (WM_USER+128)

// class CErrorReportDlg
// Implements Error Report dialog.
class CErrorReportDlg : 
    public CDialogImpl<CErrorReportDlg>, 
    public CUpdateUI<CErrorReportDlg>,
    public CMessageFilter    
{
public:
    enum { IDD = IDD_MAINDLG };

    CStatic m_statIcon; 
    CStatic m_statSubHeader;
    CHyperLink  m_link;           
    CHyperLink m_linkMoreInfo;
    CStatic m_statIndent;
    CStatic m_statEmail;
    CEdit m_editEmail;
    CStatic m_statDesc;  
    CEdit m_editDesc;
    CButton m_chkRestart;
    CStatic m_statConsent;
    CHyperLink  m_linkPrivacyPolicy;           
    CStatic m_statHorzLine;
    CStatic m_statCrashRpt;
    CButton m_btnOk;
    CButton m_btnCancel;    
    CFont m_HeadingFont;
    CIcon m_HeadingIcon;
    CSequenceLayout m_Layout;

    CProgressDlg m_dlgProgress;    

    virtual BOOL PreTranslateMessage(MSG* pMsg);    

    BEGIN_UPDATE_UI_MAP(CErrorReportDlg)
    END_UPDATE_UI_MAP()

    BEGIN_MSG_MAP(CErrorReportDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)    
        MESSAGE_HANDLER(WM_COMPLETECOLLECT, OnCompleteCollectCrashInfo)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)        
        MESSAGE_HANDLER(WM_TRAYICON, OnTrayIcon)
		MESSAGE_HANDLER(WM_REPORTSIZECHANGED, OnReportSizeChanged)

        COMMAND_ID_HANDLER(IDC_LINK, OnLinkClick)
        COMMAND_ID_HANDLER(IDC_MOREINFO, OnMoreInfoClick)    
        COMMAND_ID_HANDLER(IDC_RESTART, OnRestartClick)    
        COMMAND_HANDLER(IDC_EMAIL, EN_KILLFOCUS, OnEmailKillFocus)
        COMMAND_HANDLER(IDC_DESCRIPTION, EN_KILLFOCUS, OnEmailKillFocus)
        COMMAND_ID_HANDLER(IDOK, OnSendClick)
        COMMAND_ID_HANDLER(IDC_CANCEL, OnCancel)            
        COMMAND_ID_HANDLER(ID_MENU5_SENDREPORTLATER, OnPopupSendReportLater)            
        COMMAND_ID_HANDLER(ID_MENU5_CLOSETHEPROGRAM, OnPopupCloseTheProgram)            
    END_MSG_MAP()

    // Handler prototypes (uncomment arguments if needed):
    //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnCompleteCollectCrashInfo(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);	
    LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);	
    LRESULT OnTrayIcon(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);	
	LRESULT OnReportSizeChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);	

    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnEmailKillFocus(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);  
    LRESULT OnLinkClick(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnMoreInfoClick(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);  
    LRESULT OnSendClick(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnRestartClick(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnCtlColorStatic(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
    LRESULT OnPopupSendReportLater(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnPopupCloseTheProgram(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	// This method is used to close this dialog with some return code.
    void CloseDialog(int nVal); 

	// This method hides or displays some input fields.
    void ShowMoreInfo(BOOL bShow);
	
	// This method creates or destroys the tray icon.
    int CreateTrayIcon(bool bCreate, HWND hWndParent);	
};
