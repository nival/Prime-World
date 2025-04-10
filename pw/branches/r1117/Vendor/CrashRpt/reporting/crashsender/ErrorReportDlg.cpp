/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#include "stdafx.h"
#include "resource.h"
#include "ErrorReportDlg.h"
#include "Utility.h"
#include "tinyxml.h"
#include "zip.h"
#include "unzip.h"
#include "CrashInfoReader.h"
#include "strconv.h"

BOOL CErrorReportDlg::PreTranslateMessage(MSG* pMsg)
{
    return CWindow::IsDialogMessage(pMsg);
}

LRESULT CErrorReportDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{   	
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	CCrashInfoReader* pCrashInfo = pSender->GetCrashInfo();

    // Mirror this window if RTL language is in use.
    CString sRTL = pSender->GetLangStr(_T("Settings"), _T("RTLReading"));
    if(sRTL.CompareNoCase(_T("1"))==0)
    {
        Utility::SetLayoutRTL(m_hWnd);
    }

	// Set dialog caption.
    SetWindowText(pSender->GetLangStr(_T("MainDlg"), _T("DlgCaption")));

    // Center the dialog on the screen.
    CenterWindow();

    HICON hIcon = NULL;

    // Get custom icon.
    hIcon = pCrashInfo->GetCustomIcon();
    if(hIcon==NULL)
    {
        // Use default icon, if custom icon is not provided.
        hIcon = ::LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME));
    }

    // Set window icon.
    SetIcon(hIcon, 0);

    // Get the first icon in the EXE image and use it for header.
    m_HeadingIcon = ExtractIcon(NULL, pCrashInfo->GetReport(pSender->GetCurReport())->GetImageName(), 0);

    // If there is no icon in crashed EXE module, use default IDI_APPLICATION system icon.
    if(m_HeadingIcon == NULL)
    {
        m_HeadingIcon = ::LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
    }  

	// Init controls.

    m_statSubHeader = GetDlgItem(IDC_SUBHEADER);

    m_link.SubclassWindow(GetDlgItem(IDC_LINK));   
    m_link.SetHyperLinkExtendedStyle(HLINK_COMMANDBUTTON);
	m_link.SetLabel(pSender->GetLangStr(_T("MainDlg"), _T("WhatDoesReportContain")));

    m_linkMoreInfo.SubclassWindow(GetDlgItem(IDC_MOREINFO));
    m_linkMoreInfo.SetHyperLinkExtendedStyle(HLINK_COMMANDBUTTON);
	m_linkMoreInfo.SetLabel(pSender->GetLangStr(_T("MainDlg"), _T("ProvideAdditionalInfo")));

    m_statEmail = GetDlgItem(IDC_STATMAIL);
    m_statEmail.SetWindowText(pSender->GetLangStr(_T("MainDlg"), _T("YourEmail")));

    m_editEmail = GetDlgItem(IDC_EMAIL);
	m_editEmail.SetWindowText(pSender->GetCrashInfo()->GetPersistentUserEmail());

    m_statDesc = GetDlgItem(IDC_DESCRIBE);
    m_statDesc.SetWindowText(pSender->GetLangStr(_T("MainDlg"), _T("DescribeProblem")));

    m_editDesc = GetDlgItem(IDC_DESCRIPTION);

    m_statIndent =  GetDlgItem(IDC_INDENT);

    m_chkRestart = GetDlgItem(IDC_RESTART);
    CString sCaption;
    sCaption.Format(pSender->GetLangStr(_T("MainDlg"), _T("RestartApp")), pSender->GetCrashInfo()->m_sAppName);
    m_chkRestart.SetWindowText(sCaption);
    m_chkRestart.SetCheck(BST_CHECKED);
    m_chkRestart.ShowWindow(pSender->GetCrashInfo()->m_bAppRestart?SW_SHOW:SW_HIDE);

    m_statConsent = GetDlgItem(IDC_CONSENT);

    // Init font for consent string.
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));
    lf.lfHeight = 11;
    lf.lfWeight = FW_NORMAL;
    lf.lfQuality = ANTIALIASED_QUALITY;
    _TCSCPY_S(lf.lfFaceName, 32, _T("Tahoma"));
    CFontHandle hConsentFont;
    hConsentFont.CreateFontIndirect(&lf);
    m_statConsent.SetFont(hConsentFont);

	// Set text of the static
    if(pSender->GetCrashInfo()->m_sPrivacyPolicyURL.IsEmpty())
        m_statConsent.SetWindowText(pSender->GetLangStr(_T("MainDlg"), _T("MyConsent2")));
    else
        m_statConsent.SetWindowText(pSender->GetLangStr(_T("MainDlg"), _T("MyConsent")));

	// Init Privacy Policy link
    m_linkPrivacyPolicy.SubclassWindow(GetDlgItem(IDC_PRIVACYPOLICY));
    m_linkPrivacyPolicy.SetHyperLink(pSender->GetCrashInfo()->m_sPrivacyPolicyURL);
    m_linkPrivacyPolicy.SetLabel(pSender->GetLangStr(_T("MainDlg"), _T("PrivacyPolicy")));

    BOOL bShowPrivacyPolicy = !pSender->GetCrashInfo()->m_sPrivacyPolicyURL.IsEmpty();  
    m_linkPrivacyPolicy.ShowWindow(bShowPrivacyPolicy?SW_SHOW:SW_HIDE);

    m_statCrashRpt = GetDlgItem(IDC_CRASHRPT);
    m_statHorzLine = GetDlgItem(IDC_HORZLINE);  

	// Init OK button
    m_btnOk = GetDlgItem(IDOK);
    m_btnOk.SetWindowText(pSender->GetLangStr(_T("MainDlg"), _T("SendReport")));

	// Init Cancel button
    m_btnCancel = GetDlgItem(IDC_CANCEL);  
    if(pSender->GetCrashInfo()->m_bQueueEnabled)
        m_btnCancel.SetWindowText(pSender->GetLangStr(_T("MainDlg"), _T("OtherActions")));
    else
        m_btnCancel.SetWindowText(pSender->GetLangStr(_T("MainDlg"), _T("CloseTheProgram")));

	// If send procedure is mandatory...
	if(pSender->GetCrashInfo()->m_bSendMandatory) 
	{
		// Hide Cancel button
		m_btnCancel.ShowWindow(SW_HIDE);
		// Remove Close button
		SetWindowLong(GWL_STYLE, GetWindowLong(GWL_STYLE) & ~WS_SYSMENU);
	}

    // Init font for heading text
    memset(&lf, 0, sizeof(LOGFONT));
    lf.lfHeight = 25;
    lf.lfWeight = FW_NORMAL;
    lf.lfQuality = ANTIALIASED_QUALITY;
    _TCSCPY_S(lf.lfFaceName, 32, _T("Tahoma"));
    m_HeadingFont.CreateFontIndirect(&lf);

	// Init control positions
    m_Layout.SetContainerWnd(m_hWnd);
    m_Layout.Insert(m_linkMoreInfo);
    m_Layout.Insert(m_statIndent);
    m_Layout.Insert(m_statEmail, TRUE);
    m_Layout.Insert(m_editEmail, TRUE);
    m_Layout.Insert(m_statDesc, TRUE);
    m_Layout.Insert(m_editDesc, TRUE);
    m_Layout.Insert(m_chkRestart);
    m_Layout.Insert(m_statConsent);
    m_Layout.Insert(m_linkPrivacyPolicy);  
    m_Layout.Insert(m_statCrashRpt);
    m_Layout.Insert(m_statHorzLine, TRUE);
    m_Layout.Insert(m_btnOk);
    m_Layout.Insert(m_btnCancel, TRUE);

	// By default, hide the email & description fields.
	// But user may override the default.
	ShowMoreInfo(pSender->GetCrashInfo()->m_bShowAdditionalInfoFields);

	// Create progress dialog
    m_dlgProgress.Create(m_hWnd);
    m_dlgProgress.Start(TRUE);

    // register object for message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    if(pLoop)
    {
        pLoop->AddMessageFilter(this);        
    }

    UIAddChildWindowContainer(m_hWnd);

    return TRUE;
}

void CErrorReportDlg::ShowMoreInfo(BOOL bShow)
{
	// Hide/show email & description fields

    CRect rc1, rc2;

    m_statEmail.ShowWindow(bShow?SW_SHOW:SW_HIDE);
    m_editEmail.ShowWindow(bShow?SW_SHOW:SW_HIDE);
    m_statDesc.ShowWindow(bShow?SW_SHOW:SW_HIDE);
    m_editDesc.ShowWindow(bShow?SW_SHOW:SW_HIDE);
    m_statIndent.ShowWindow(bShow?SW_SHOW:SW_HIDE);

    m_Layout.Update();

    if(bShow)
	{
		m_linkMoreInfo.EnableWindow(0);
        m_editEmail.SetFocus();
	}
    else
        m_btnOk.SetFocus();
	
}

LRESULT CErrorReportDlg::OnEraseBkgnd(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// Here we want to draw a white header of the dialog

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

    CDCHandle dc((HDC)wParam);

    RECT rcClient;
    GetClientRect(&rcClient);

    RECT rc;
    CStatic statUpperHorzLine = GetDlgItem(IDC_UPPERHORZ);
    statUpperHorzLine.GetWindowRect(&rc);
    ScreenToClient(&rc);

    COLORREF cr = GetSysColor(COLOR_3DFACE);
    CBrush brush;
    brush.CreateSolidBrush(cr);  

    RECT rcHeading = {0, 0, rcClient.right, rc.bottom};
    dc.FillRect(&rcHeading, (HBRUSH)GetStockObject(WHITE_BRUSH));

    RECT rcBody = {0, rc.bottom, rcClient.right, rcClient.bottom};
    dc.FillRect(&rcBody, brush);

    rcHeading.left = 60;
    rcHeading.right -= 10;

	// Draw header text over background
    CString sHeading;
    sHeading.Format(pSender->GetLangStr(_T("MainDlg"), _T("HeaderText")), pSender->GetCrashInfo()->m_sAppName);
    dc.SelectFont(m_HeadingFont);
    dc.DrawTextEx(sHeading.GetBuffer(0), sHeading.GetLength(), &rcHeading, 
        DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);  

	// Check if we should draw the icon on the header area
    if(m_HeadingIcon)
    {
		// Draw the icon left to the text
        ICONINFO ii;
        m_HeadingIcon.GetIconInfo(&ii);
        dc.DrawIcon(16, rcHeading.bottom/2 - ii.yHotspot, m_HeadingIcon);
    }

    return TRUE;
}

LRESULT CErrorReportDlg::OnCtlColorStatic(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	// This method is used to set background and text color for m_statIcon control

    if((HWND)lParam!=m_statIcon)
        return 0;

    HDC hDC = (HDC)wParam;
    SetBkColor(hDC, RGB(0, 255, 255));
    SetTextColor(hDC, RGB(0, 255, 255));
    return (LRESULT)TRUE;
}

LRESULT CErrorReportDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{   
	// This method is called when user clicks "Close the program" or "Other actions..." button 
	// (the button is the same, its caption may differ)

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

    if(pSender->GetCrashInfo()->m_bQueueEnabled)
    {    
		// Show popup menu on "Other actions..." button click.
        CPoint pt;
        GetCursorPos(&pt);
        CMenu menu = LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_POPUPMENU));
        CMenu submenu = menu.GetSubMenu(4);

        strconv_t strconv;
        CString sSendLater = pSender->GetLangStr(_T("MainDlg"), _T("SendReportLater"));
		CString sCloseTheProgram = pSender->GetLangStr(_T("MainDlg"), _T("CloseTheProgram"));

        MENUITEMINFO mii;
        memset(&mii, 0, sizeof(MENUITEMINFO));
        mii.cbSize = sizeof(MENUITEMINFO);
        mii.fMask = MIIM_STRING;

        mii.dwTypeData = sSendLater.GetBuffer(0);  
        submenu.SetMenuItemInfo(ID_MENU5_SENDREPORTLATER, FALSE, &mii);

        mii.dwTypeData = sCloseTheProgram.GetBuffer(0);  
        submenu.SetMenuItemInfo(ID_MENU5_CLOSETHEPROGRAM, FALSE, &mii);

        submenu.TrackPopupMenu(0, pt.x, pt.y, m_hWnd);    
    }  
    else // "Close the program" button clicked
    {
        // Close dialog.
        CloseDialog(wID);  
    }

    return 0;
}

LRESULT CErrorReportDlg::OnPopupSendReportLater(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// User has clicked the popup menu's "Close the program and send report later".

	// Update our remind policy to "Remind me later".
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	pSender->GetCrashInfo()->SetRemindPolicy(REMIND_LATER);

    CloseDialog(wID);  
    return 0;
}

LRESULT CErrorReportDlg::OnPopupCloseTheProgram(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// User has clicked the popup menu's "Close the program".
		
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	// The following line will prevent from queueing the report
	pSender->GetCrashInfo()->m_bQueueEnabled = FALSE;

    CloseDialog(wID);  
    return 0;
}

LRESULT CErrorReportDlg::OnCompleteCollectCrashInfo(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{  
	// This method is called when the worker thread has finished with collection
	// of crash report data. Now we display the "Error Report" dialog
	// and offer user to send error report.
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
    
    if(pSender->GetCrashInfo()->m_bSendErrorReport) // If we should send error report now
    {   
		// Get the total size of the report.
		LONG64 lTotalSize = pSender->GetCrashInfo()->GetReport(pSender->GetCurReport())->GetTotalSize();  
        CString sTotalSize = Utility::FileSizeToStr(lTotalSize);    
		
		// Format the text for dialog subheader.
        CString sSubHeader;
		sSubHeader.Format(pSender->GetLangStr(_T("MainDlg"), _T("SubHeaderText")), sTotalSize);
		
		// Update the subheader text
        m_statSubHeader.SetWindowText(sSubHeader);

		// Show "Error Report" dialog
        ShowWindow(SW_SHOW);
		SetWindowPos(HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW); 
		
		// Make it flash
		FlashWindow(TRUE);
    } 
    else // If we shouldn't send error report now.
    {
        // Exit the app.
        SendMessage(WM_CLOSE);
    }    

    return 0;
}

LRESULT CErrorReportDlg::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{   
	// This method is called when user clicks the close (x) button. 
    CloseDialog(0);  
    return 0;
}

void CErrorReportDlg::CloseDialog(int nVal)
{
    // Remove tray icon.  
    CreateTrayIcon(FALSE, m_hWnd);

	// Destroy window
    DestroyWindow();

	// Exit the message loop
    ::PostQuitMessage(nVal);
}

LRESULT CErrorReportDlg::OnLinkClick(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{  
	// This method is called when user clicks the 
	// "What does this report contain?" link.
    
	// Show "Error Report Details" dialog.
    CDetailDlg dlg;
    dlg.m_nCurReport = 0;
    dlg.DoModal();

    return 0;
}

LRESULT CErrorReportDlg::OnMoreInfoClick(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// This method is called when user clicks the 
	// "Provide additional info (recommended)" link.

    // Expand dialog
    m_linkMoreInfo.EnableWindow(0);
    ShowMoreInfo(TRUE);

    return 0;
}

LRESULT CErrorReportDlg::OnRestartClick(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{  
	// This method is called when user clicks the "Restart the application" checkbox.
    
	// Determine checkbox state
	BOOL bRestart = m_chkRestart.GetCheck()==BST_CHECKED?TRUE:FALSE;

	// Update the restart flag
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
    pSender->GetCrashInfo()->m_bAppRestart = bRestart;

    return 0;
}

LRESULT CErrorReportDlg::OnEmailKillFocus(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{ 
	// This method is called when user removes focus from "Your E-mail" field.
		
	TCHAR szBuffer[1024] = _T("");
    CString sEmail;	
	CString sDesc;
	// Get E-mail field's text
	m_editEmail.GetWindowText(szBuffer, 1024);	
	sEmail = szBuffer;
	// Get description field's text
	m_editDesc.GetWindowText(szBuffer, 1024);
	sDesc = szBuffer;

	// Update those fields in crash report data
    CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	pSender->GetCrashInfo()->UpdateUserInfo(sEmail, sDesc);

    return 0;
}

LRESULT CErrorReportDlg::OnSendClick(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{  
	// This method is called when user clicks the "Send Report" button
	    
	TCHAR szBuffer[1024] = _T("");
    CString sEmail;	
	CString sDesc;
	// Get E-mail field's text
	m_editEmail.GetWindowText(szBuffer, 1024);	
	sEmail = szBuffer;
	// Get description field's text
	m_editDesc.GetWindowText(szBuffer, 1024);
	sDesc = szBuffer;
		
	// Update those fields in crash report data and check the result
    CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	if(!pSender->GetCrashInfo()->UpdateUserInfo(sEmail, sDesc))
	{
		// Failure - display alert message and repeat again

		// Check window mirroring settings
        DWORD dwFlags = 0;
		CString sRTL = pSender->GetLangStr(_T("Settings"), _T("RTLReading"));
        if(sRTL.CompareNoCase(_T("1"))==0)
            dwFlags = MB_RTLREADING;

        // Alert user     
        MessageBox(
			pSender->GetLangStr(_T("MainDlg"), _T("InvalidEmailText")), 
            pSender->GetLangStr(_T("MainDlg"), _T("InvalidEmailCaption")), 
            MB_OK|dwFlags);

        // Set focus to Email field
        ::SetFocus(m_editEmail);

		return 0;
	}
	
	/* Now we are ready to send error report in background. */

	// Hide the dialog
    ShowWindow(SW_HIDE);

	// Display tray icon
    CreateTrayIcon(true, m_hWnd);
    
	// Show progress dialog
	m_dlgProgress.Start(FALSE);        

	// Run worker thread that will compress and send error report.
	pSender->Run();
    
    return 0;
}

int CErrorReportDlg::CreateTrayIcon(bool bCreate, HWND hWndParent)
{
	// This method creates (bCreate==TRUE) or destroys (bCreate==FALSE)
	// the tray icon.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	// Prepare icon info
    NOTIFYICONDATA nf;
    memset(&nf,0,sizeof(NOTIFYICONDATA));
    nf.cbSize = sizeof(NOTIFYICONDATA);
    nf.hWnd = hWndParent;
    nf.uID = 0;

    if(bCreate==true) // add icon to tray
    {
        nf.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
        nf.uCallbackMessage = WM_TRAYICON;
#if _MSC_VER>=1300		
        nf.uVersion = NOTIFYICON_VERSION;
#endif

        // Try to load custom icon
		HICON hIcon = pSender->GetCrashInfo()->GetCustomIcon();
        if(hIcon==NULL)
            hIcon = ::LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME));
        nf.hIcon = hIcon;
        _TCSCPY_S(nf.szTip, 128, _T("Sending Error Report"));

        Shell_NotifyIcon(NIM_ADD, &nf);
    }
    else // delete icon
    {
        Shell_NotifyIcon(NIM_DELETE, &nf);
    }
    return 0;
}


LRESULT CErrorReportDlg::OnTrayIcon(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	// This method is called when user does something with (e.g. clicks) the tray icon.

    UINT uMouseMsg = (UINT)lParam; 

    if(uMouseMsg==WM_LBUTTONDBLCLK)
    {
		// User clicked the left mouse button over the icon,
		// so we need to show the dialog if it is hidden and set focus on it
        m_dlgProgress.ShowWindow(SW_SHOW);  	
        m_dlgProgress.SetFocus();
    }	

    return 0;
}

LRESULT CErrorReportDlg::OnReportSizeChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	// Get the total size of the report.
	LONG64 lTotalSize = pSender->GetCrashInfo()->GetReport(pSender->GetCurReport())->GetTotalSize();  
    CString sTotalSize = Utility::FileSizeToStr(lTotalSize);    
		
	// Format the text for dialog subheader.
    CString sSubHeader;
	sSubHeader.Format(pSender->GetLangStr(_T("MainDlg"), _T("SubHeaderText")), sTotalSize);
		
	// Update the subheader text
    m_statSubHeader.SetWindowText(sSubHeader);

	return 0;
}

