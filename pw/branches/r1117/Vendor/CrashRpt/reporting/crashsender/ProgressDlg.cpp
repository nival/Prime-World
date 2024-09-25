/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#include "stdafx.h"
#include "ProgressDlg.h"
#include "Utility.h"
#include "CrashInfoReader.h"


LRESULT CProgressDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{   
    // Check if current UI language is an RTL language
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	CString sRTL = pSender->GetLangStr(_T("Settings"), _T("RTLReading"));
    if(sRTL.CompareNoCase(_T("1"))==0)
    {
        // Mirror this window
        Utility::SetLayoutRTL(m_hWnd);
    }

    HICON hIcon = NULL;

    // Try to load custom icon
    hIcon = pSender->GetCrashInfo()->GetCustomIcon();
    // If there is no custom icon, load the default one
    if(hIcon==NULL)
        hIcon = ::LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME));

    // Set dialog icon
    SetIcon(hIcon, FALSE);
    SetIcon(hIcon, TRUE);

    // Set status text
    m_statText = GetDlgItem(IDC_TEXT);
	m_statText.SetWindowText(pSender->GetLangStr(_T("ProgressDlg"), _T("CollectingCrashInfo")));        

    // Set progress bar style
    m_prgProgress = GetDlgItem(IDC_PROGRESS);  
    m_prgProgress.SetRange(0, 100);
    m_prgProgress.ModifyStyle(0, PBS_MARQUEE);

    // Set up list view
    m_listView = GetDlgItem(IDC_LIST); 
    m_listView.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
    m_listView.InsertColumn(0, _T("Status"), LVCFMT_LEFT, 2048);

    // Set up Cancel button
    m_btnCancel = GetDlgItem(IDCANCEL);
	m_btnCancel.SetWindowText(pSender->GetLangStr(_T("ProgressDlg"), _T("Cancel")));

	// Init flags
    m_ActionOnCancel = DONT_CLOSE;
    m_ActionOnClose = CLOSE_MYSELF;  

    // Init dialog resize functionality
    DlgResize_Init();

    return TRUE;
}

LRESULT CProgressDlg::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{   
	// This method is called when user clicks the close (x) button
	// on the dialog.

    if(m_ActionOnClose==CLOSE_MYSELF_AND_PARENT)
    {
        // Hide this window smoothly
        AnimateWindow(m_hWnd, 200, AW_HIDE|AW_BLEND); 

        // Request parent window to close
        HWND hWndParent = ::GetParent(m_hWnd);
        ::PostMessage(hWndParent, WM_CLOSE, 0, 0);
        return 0;
    }
    else if(m_ActionOnClose==CLOSE_MYSELF)
    {
        // Hide this window smoothly
        AnimateWindow(m_hWnd, 200, AW_HIDE|AW_BLEND); 	  
        return 0;
    }

    return 0;
}


LRESULT CProgressDlg::OnCancel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{ 
	// This method is called when user clicks the "Cancel" button
	// on the dialog.

    if(m_ActionOnCancel==CLOSE_MYSELF_AND_PARENT)
    {
        // Hide this window smoothly
        AnimateWindow(m_hWnd, 200, AW_HIDE|AW_BLEND); 

        // Request parent window to close
        HWND hWndParent = ::GetParent(m_hWnd);
        ::PostMessage(hWndParent, WM_CLOSE, 0, 0);
        return 0;
    }
    else if(m_ActionOnCancel==CLOSE_MYSELF)
    {
        // Hide this window smoothly
        AnimateWindow(m_hWnd, 200, AW_HIDE|AW_BLEND); 	  
        return 0;
    }

    // Start cancelling the worker thread
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
    pSender->Cancel();  

    // Disable Cancel button
    m_btnCancel.EnableWindow(0);

    return 0;
}

void CProgressDlg::Start(BOOL bCollectInfo, BOOL bMakeVisible)
{   
	// This method displays the progress dialog and starts the timer
	// that will update the dialog periodically and react on 
	// incoming events.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	// Set up correct dialog caption
    if(bCollectInfo)
    {
        CString sCaption;
		sCaption.Format(pSender->GetLangStr(_T("ProgressDlg"), _T("DlgCaption2")), pSender->GetCrashInfo()->m_sAppName);
        SetWindowText(sCaption);    
    }
    else
    {
        CString sCaption;
		sCaption.Format(pSender->GetLangStr(_T("ProgressDlg"), _T("DlgCaption")), pSender->GetCrashInfo()->m_sAppName);
        SetWindowText(sCaption);    
    }

    // Show the window on top of other windows
    SetWindowPos(HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

    // Center the dialog on the screen
    CenterWindow();

	// Check if we need to make the dialog visible
    if(bMakeVisible)
    {
		// Show the dialog and set focus on it
        ShowWindow(SW_SHOW); 
        SetFocus();    
    }

    if(!bCollectInfo)
    {
		// If we are not collecting crash information now, than hide this dialog in 3 sec.
        SetTimer(1, 3000); 
    }

	// Update this dialog each 200 ms.
    SetTimer(0, 200); 

	// If user clicks the Close button (x), do not close the window.
    m_ActionOnCancel = DONT_CLOSE;
}

void CProgressDlg::Stop()
{
    // Stop timers
    KillTimer(0);
    KillTimer(1);
}

LRESULT CProgressDlg::OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// This method is called when a timer ticks.

    WORD wTimerId = (WORD)wParam;
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

    if(wTimerId==0) // Dialog update timer
    {
        // Get current progress
        int nProgressPct = 0;
        std::vector<CString> messages;
        pSender->GetCurOpStatus(nProgressPct, messages);

        // Update progress bar
        m_prgProgress.SetPos(nProgressPct);

        int attempt = 0; // Sending attempt

        // Walk through incoming messages and look for special ones (enclosed in [ ])
        unsigned i;
        for(i=0; i<messages.size(); i++)
        {  
            if(messages[i].CompareNoCase(_T("[creating_dump]"))==0)
            { 
                // Creating minidump
                m_ActionOnCancel = DONT_CLOSE;
                m_ActionOnClose = CLOSE_MYSELF_AND_PARENT;
				m_statText.SetWindowText(pSender->GetLangStr(_T("ProgressDlg"), _T("CollectingCrashInfo")));        
            }
            else if(messages[i].CompareNoCase(_T("[copying_files]"))==0)
            { 
                // Copying files
                m_ActionOnCancel = DONT_CLOSE;
                m_ActionOnClose = CLOSE_MYSELF_AND_PARENT;
                // Remove marquee style from progress bar
                m_prgProgress.ModifyStyle(PBS_MARQUEE, 0);        
            }
            else if(messages[i].CompareNoCase(_T("[confirm_send_report]"))==0)
            {
                // User should consent to send error report, so we hide this dialog
				// and send a message to our parent dialog that will receive user input.
                m_ActionOnCancel = CLOSE_MYSELF_AND_PARENT;

				ShowWindow(SW_HIDE);

                HWND hWndParent = ::GetParent(m_hWnd);        
                ::PostMessage(hWndParent, WM_COMPLETECOLLECT, 0, 0);
            }
            else if(messages[i].CompareNoCase(_T("[exporting_report]"))==0)
            {
                // Exporting error report as a ZIP archive
                m_ActionOnCancel = DONT_CLOSE;
                m_ActionOnClose = DONT_CLOSE;
                CString sCaption;
				sCaption.Format(pSender->GetLangStr(_T("ProgressDlg"), _T("DlgCaptionExport")), 
					pSender->GetCrashInfo()->m_sAppName);
                SetWindowText(sCaption);    

				m_statText.SetWindowText(pSender->GetLangStr(_T("ProgressDlg"), _T("CompressingFiles")));        

				m_btnCancel.SetWindowText(pSender->GetLangStr(_T("ProgressDlg"), _T("Cancel")));

                ShowWindow(SW_SHOW);
            }
            else if(messages[i].CompareNoCase(_T("[end_exporting_report_ok]"))==0)
            { 
                // End exporting error report
                m_ActionOnCancel = CLOSE_MYSELF;
                ShowWindow(SW_HIDE);
            }
            else if(messages[i].CompareNoCase(_T("[end_exporting_report_failed]"))==0)
            { 
                // Failed to export error report
                m_ActionOnCancel = CLOSE_MYSELF;
                m_ActionOnClose = CLOSE_MYSELF;
				m_statText.SetWindowText(pSender->GetLangStr(_T("ProgressDlg"), _T("ExportedWithErrors")));        
                m_btnCancel.EnableWindow(1);
				m_btnCancel.SetWindowText(pSender->GetLangStr(_T("ProgressDlg"), _T("Close")));
            }
            else if(messages[i].CompareNoCase(_T("[compressing_files]"))==0)
            {         
                // Compressing error report files
                m_ActionOnCancel = DONT_CLOSE; 
                m_ActionOnClose = CLOSE_MYSELF;
				m_statText.SetWindowText(pSender->GetLangStr(_T("ProgressDlg"), _T("CompressingFiles")));        
				m_btnCancel.SetWindowText(pSender->GetLangStr(_T("ProgressDlg"), _T("Cancel")));
            }      
            else if(messages[i].CompareNoCase(_T("[end_compressing_files]"))==0)
            { 
                // File compression finished
				if(!pSender->GetCrashInfo()->m_bSendErrorReport && pSender->GetCrashInfo()->m_bStoreZIPArchives)
                {
                    m_ActionOnCancel = CLOSE_MYSELF;
                    m_ActionOnClose = CLOSE_MYSELF;
                    HWND hWndParent = ::GetParent(m_hWnd);        
                    ::PostMessage(hWndParent, WM_CLOSE, 0, 0);
                }
            }
            else if(messages[i].CompareNoCase(_T("[status_success]"))==0)
            {         
                // Error report has been delivered ok
                m_ActionOnCancel = CLOSE_MYSELF_AND_PARENT;        
                m_ActionOnClose = CLOSE_MYSELF_AND_PARENT;        

				// Close the parent dialog.
                HWND hWndParent = ::GetParent(m_hWnd);        
                ::PostMessage(hWndParent, WM_CLOSE, 0, 0);
            }
            else if(messages[i].CompareNoCase(_T("[status_failed]"))==0)
            {         
                // Error report delivery has failed
                m_ActionOnCancel = CLOSE_MYSELF_AND_PARENT;
                m_ActionOnClose = CLOSE_MYSELF_AND_PARENT;        
                
				// Stop timer
				KillTimer(1);

				// Update status text.
				m_statText.SetWindowText(pSender->GetLangStr(_T("ProgressDlg"), _T("CompletedWithErrors")));

				// Enable "Close" button
                m_btnCancel.EnableWindow(1);
				m_btnCancel.SetWindowText(pSender->GetLangStr(_T("ProgressDlg"), _T("Close")));

				// Show the dialog
				ShowWindow(SW_SHOW);        
            }
            else if(messages[i].CompareNoCase(_T("[exit_silently]"))==0)
            {         
                // Silent exit
                m_ActionOnCancel = CLOSE_MYSELF_AND_PARENT;
                m_ActionOnClose = CLOSE_MYSELF_AND_PARENT;

				// Stop timer
                KillTimer(1);        

				// Close the parent dialog.
                HWND hWndParent = ::GetParent(m_hWnd);        
                ::PostMessage(hWndParent, WM_CLOSE, 0, 0);
            }
            else if(messages[i].CompareNoCase(_T("[cancelled_by_user]"))==0)
            { 
                // The operation was cancelled by user
				m_statText.SetWindowText(pSender->GetLangStr(_T("ProgressDlg"), _T("Cancelling")));
            }
            else if(messages[i].CompareNoCase(_T("[sending_attempt]"))==0)
            {
                // Trying to send error report using another method
                attempt ++;      
                CString str;
				str.Format(pSender->GetLangStr(_T("ProgressDlg"), _T("StatusText")), attempt);
                m_statText.SetWindowText(str);
            }
            else if(messages[i].CompareNoCase(_T("[confirm_launch_email_client]"))==0)
            {       
                // User should confirm he allows to launch email client
                KillTimer(1);        
                
				// Show the dialog
				ShowWindow(SW_SHOW);

				// Determine window mirroring settings.
                DWORD dwFlags = 0;
				CString sRTL = pSender->GetLangStr(_T("Settings"), _T("RTLReading"));
                if(sRTL.CompareNoCase(_T("1"))==0)
                    dwFlags = MB_RTLREADING;

				// Display the message box, so user to be able to confirm.
                CString sMailClientName;        
                CMailMsg::DetectMailClient(sMailClientName);
                CString msg;
				msg.Format(pSender->GetLangStr(_T("ProgressDlg"), _T("ConfirmLaunchEmailClient")), sMailClientName);

				CString sCaption = pSender->GetLangStr(_T("ProgressDlg"), _T("DlgCaption"));
                CString sTitle;
				sTitle.Format(sCaption, pSender->GetCrashInfo()->m_sAppName);
                INT_PTR result = MessageBox(msg, 
                    sTitle,
                    MB_OKCANCEL|MB_ICONQUESTION|dwFlags);

				// Unblock worker thread.
                pSender->FeedbackReady(result==IDOK?0:1);       

				// Hide the dialog
                ShowWindow(SW_HIDE);                
            }

            // Ensure the last item of the log is visible
            int count = m_listView.GetItemCount();
            int indx = m_listView.InsertItem(count, messages[i]);
            m_listView.EnsureVisible(indx, TRUE);

        }
    }
    else if(wTimerId==1) // The timer that hides this window
    {
		// Hide the window smoothly
		AnimateWindow(m_hWnd, 200, AW_HIDE|AW_BLEND); 
		// Stop the timer
        KillTimer(1);
    }

    return 0;
}

LRESULT CProgressDlg::OnListRClick(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
{  
	// User right-clicks the log area. We should display context menu.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
    LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pnmh;

    POINT pt;
    GetCursorPos(&pt);

    CMenu popup_menu;
    popup_menu.LoadMenu(IDR_POPUPMENU);

    CMenu submenu = popup_menu.GetSubMenu(0);  

    if(lpnmitem->iItem<0)
    {    
        submenu.EnableMenuItem(ID_MENU1_COPYSEL, MF_BYCOMMAND|MF_GRAYED);
    }

    CString sCopySelLines = pSender->GetLangStr(_T("ProgressDlg"), _T("CopySelectedLines"));
	CString sCopyWholeLog = pSender->GetLangStr(_T("ProgressDlg"), _T("CopyTheWholeLog"));

    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STRING;

    mii.dwTypeData = sCopySelLines.GetBuffer(0);
    mii.cch = sCopySelLines.GetLength();
    submenu.SetMenuItemInfo(ID_MENU1_COPYSEL, FALSE, &mii);

    mii.dwTypeData = sCopyWholeLog.GetBuffer(0);
    mii.cch = sCopyWholeLog.GetLength();
    submenu.SetMenuItemInfo(ID_MENU1_COPYLOG, FALSE, &mii);

    submenu.TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, m_hWnd); 
    return 0;
}

LRESULT CProgressDlg::OnCopySel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// User wants to copy selected lines to clipboard.

    CString sData;
    int i;
    for(i=0; i<m_listView.GetItemCount(); i++)
    {
        DWORD dwState = m_listView.GetItemState(i, LVIS_SELECTED);
        if(dwState==0)
            continue;

        TCHAR buf[4096];
        buf[0]=0;
        int n = m_listView.GetItemText(i, 0, buf, 4095);
        sData += CString(buf,n);
        sData += "\r\n";
    }

    SetClipboard(sData);  

    return 0;
}

LRESULT CProgressDlg::OnCopyLog(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// User wants to copy the entire log to clipboard.

    CString sData;
    int i;
    for(i=0; i<m_listView.GetItemCount(); i++)
    {
        TCHAR buf[4096];
        buf[0]=0;
        int n = m_listView.GetItemText(i, 0, buf, 4095);
        sData += CString(buf,n);
        sData += "\r\n";
    }

    SetClipboard(sData);  

    return 0;
}

int CProgressDlg::SetClipboard(CString& sData)
{
	// This method places the data to clipboard.

    if (OpenClipboard())
    {
        EmptyClipboard();
        HGLOBAL hClipboardData;
        DWORD dwSize = (sData.GetLength()+1)*sizeof(TCHAR);
        hClipboardData = GlobalAlloc(GMEM_DDESHARE, dwSize);
        TCHAR* pszData = (TCHAR*)GlobalLock(hClipboardData);
        if(pszData!=NULL)
        {      
            _TCSNCPY_S(pszData, dwSize/sizeof(TCHAR), sData, sData.GetLength()*sizeof(TCHAR));
            GlobalUnlock(hClipboardData);
#ifdef _UNICODE
            SetClipboardData(CF_UNICODETEXT, hClipboardData);
#else
            SetClipboardData(CF_TEXT, hClipboardData);    
#endif
            CloseClipboard();
            return 0;
        }
        CloseClipboard();
    }

    return 1;
}