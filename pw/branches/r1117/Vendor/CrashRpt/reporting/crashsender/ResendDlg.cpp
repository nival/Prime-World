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
#include "CrashInfoReader.h"
#include "ResendDlg.h"
#include "Utility.h"
#include "strconv.h"
#include "DetailDlg.h"
#include "ErrorReportSender.h"


LRESULT CActionProgressDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{   
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	// Determine window mirroring settings.
	CString sRTL = pSender->GetLangStr(_T("Settings"), _T("RTLReading"));
    if(sRTL.CompareNoCase(_T("1"))==0)
    {
        Utility::SetLayoutRTL(m_hWnd);
    }

	// The dialog will be resizable, so init resize map now.
    DlgResize_Init(false);

	// Init "current action" static
    m_statCurAction = GetDlgItem(IDC_CURRENTACTION);
    m_statCurAction.SetWindowText(
		pSender->GetLangStr(_T("ResendDlg"), _T("CurrentAction")));

	// Init "description" static
    m_statActionDesc = GetDlgItem(IDC_ACTIONDESC);

	// Init progress bar.
    m_prgProgress = GetDlgItem(IDC_PROGRESS);
    m_prgProgress.SetRange(0, 100);

    return 0;
}

LRESULT CActionProgressDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    return 0;
}


BOOL CResendDlg::PreTranslateMessage(MSG* pMsg)
{
    return CWindow::IsDialogMessage(pMsg);
}

LRESULT CResendDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{ 
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	// Determine window mirroring settings.
	CString sRTL = pSender->GetLangStr(_T("Settings"), _T("RTLReading"));
    if(sRTL.CompareNoCase(_T("1"))==0)
    {
        Utility::SetLayoutRTL(m_hWnd);
    }
	
	// Set dialog caption
    CString sTitle;
	sTitle.Format(pSender->GetLangStr(_T("ResendDlg"), _T("DlgCaption")), 
		pSender->GetCrashInfo()->m_sAppName);
    SetWindowText(sTitle);

    // center the dialog on the screen
    CenterWindow();

    // Set window icon
	HICON hIcon = pSender->GetCrashInfo()->GetCustomIcon();
    if(!hIcon)
        hIcon = ::LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME));
    SetIcon(hIcon, 0);

    // register object for message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->AddMessageFilter(this);

	// Set up controls
    m_statText = GetDlgItem(IDC_TEXT);
	m_statText.SetWindowText(pSender->GetLangStr(_T("ResendDlg"), _T("ClickForDetails")));

	// Init size static
    m_statSize = GetDlgItem(IDC_SELSIZE);
	m_statSize.SetWindowText(pSender->GetLangStr(_T("ResendDlg"), _T("SelectedSize")));

	// Init "Send Now" button
    m_btnSendNow = GetDlgItem(IDOK);
	m_btnSendNow.SetWindowText(pSender->GetLangStr(_T("ResendDlg"), _T("SendNow")));

	// Init "Other actions..." button
    m_btnOtherActions = GetDlgItem(IDC_OTHERACTIONS);
	m_btnOtherActions.SetWindowText(pSender->GetLangStr(_T("MainDlg"), _T("OtherActions")));  

	// Init "Show Log" button
    m_btnShowLog = GetDlgItem(IDC_SHOWLOG);
	m_btnShowLog.SetWindowText(pSender->GetLangStr(_T("ResendDlg"), _T("ShowLog")));
    m_btnShowLog.ShowWindow(SW_HIDE);

    // Init list control
    m_listReportsSort.SubclassWindow(GetDlgItem(IDC_LIST));  
    m_listReports.SubclassWindow(m_listReportsSort.m_hWnd);
	m_listReports.InsertColumn(0, pSender->GetLangStr(_T("ResendDlg"), _T("ColumnCreationDate")), LVCFMT_LEFT, 170);
	m_listReports.InsertColumn(1, pSender->GetLangStr(_T("ResendDlg"), _T("ColumnSize")), LVCFMT_RIGHT, 90);
	m_listReports.InsertColumn(2, pSender->GetLangStr(_T("ResendDlg"), _T("ColumnStatus")), LVCFMT_LEFT, 170);
    m_listReports.ModifyStyleEx(0, LVS_EX_FULLROWSELECT);
    m_listReportsSort.SetSortColumn(0); // Sort by creation date

	// Add items to the list.
    int i;
	for(i=0; i<pSender->GetCrashInfo()->GetReportCount(); i++)
    {
        CErrorReportInfo* eri = pSender->GetCrashInfo()->GetReport(i);

        SYSTEMTIME st;
        Utility::UTC2SystemTime(eri->GetSystemTimeUTC(), st);
        CString sCreationDate;
        sCreationDate.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), 
            st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
        int nItem = m_listReports.InsertItem(i, sCreationDate);
        m_listReports.SetItemData(nItem, i);

        CString sTotalSize = Utility::FileSizeToStr(eri->GetTotalSize());

        m_listReports.SetItemText(nItem, 1, sTotalSize);

        m_listReports.SetCheckState(nItem, eri->IsSelected());
    }

    UpdateSelectionSize();

    m_statConsent = GetDlgItem(IDC_CONSENT);

	// Create font used for the static
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));
    lf.lfHeight = 11;
    lf.lfWeight = FW_NORMAL;
    lf.lfQuality = ANTIALIASED_QUALITY;
    _TCSCPY_S(lf.lfFaceName, 32, _T("Tahoma"));
    CFontHandle hConsentFont;
    hConsentFont.CreateFontIndirect(&lf);
    m_statConsent.SetFont(hConsentFont);

	if(pSender->GetCrashInfo()->m_sPrivacyPolicyURL.IsEmpty())
    	m_statConsent.SetWindowText(pSender->GetLangStr(_T("ResendDlg"), _T("MyConsent2")));
    else
    	m_statConsent.SetWindowText(pSender->GetLangStr(_T("ResendDlg"), _T("MyConsent")));
    
	// Init Privacy Policy link
    m_linkPrivacyPolicy.SubclassWindow(GetDlgItem(IDC_PRIVACYPOLICY));
	m_linkPrivacyPolicy.SetHyperLink(pSender->GetCrashInfo()->m_sPrivacyPolicyURL);
	m_linkPrivacyPolicy.SetLabel(pSender->GetLangStr(_T("MainDlg"), _T("PrivacyPolicy")));
    m_linkPrivacyPolicy.ShowWindow(pSender->GetCrashInfo()->m_sPrivacyPolicyURL.IsEmpty()?SW_HIDE:SW_SHOW);

	// Init progress bar
    m_dlgProgress.Create(m_hWnd);
    m_dlgProgress.ShowWindow(SW_HIDE);

	// Init child dialog
    m_dlgActionProgress.m_pParent = this;
    m_dlgActionProgress.Create(m_hWnd);
    m_dlgActionProgress.SetWindowLong(GWL_ID, IDD_PROGRESSMULTI); 

	// Position child dialog.
    CRect rc;
    m_listReports.GetWindowRect(&rc);
    ScreenToClient(&rc);
    m_dlgActionProgress.SetWindowPos(HWND_TOP, rc.left, rc.bottom, 0, 0, SWP_NOZORDER|SWP_NOSIZE);

	// Init resize map.
    DlgResize_Init();
	
	m_nSendAttempt = 0;

	// By default, we will exit if user closes the dialog.
    m_ActionOnClose = EXIT;

	// Register on notifications from sender 
	pSender->SetNotificationWindow(m_hWnd);

	// Show balloon in 3 seconds.
    m_nTimerTick = 0;
    SetTimer(0, 3000);
    
    return TRUE;
}

LRESULT CResendDlg::OnTrayIcon(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	// This method is called when user clicks the tray icon.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	// If user clicks or right-clicks the tray icon or clicks the balloon,
	// then show the dialog.
    if(LOWORD(lParam)==WM_LBUTTONDOWN || 
        LOWORD(lParam)==WM_LBUTTONDBLCLK ||
        LOWORD(lParam)==NIN_BALLOONUSERCLICK)
    {
        KillTimer(0);
        ShowWindow(SW_SHOW);
    }

	// If user right-clicks the icon, display context menu.
    if(LOWORD(lParam)==WM_RBUTTONDOWN)
    {
        CPoint pt;
        GetCursorPos(&pt);
        CMenu menu = LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_POPUPMENU));
        CMenu submenu = menu.GetSubMenu(2);

        strconv_t strconv;
		CString sShow = pSender->GetLangStr(_T("ResendDlg"), _T("PopupShow"));
		CString sExit = pSender->GetLangStr(_T("ResendDlg"), _T("PopupExit"));

        MENUITEMINFO mii;
        memset(&mii, 0, sizeof(MENUITEMINFO));
        mii.cbSize = sizeof(MENUITEMINFO);
        mii.fMask = MIIM_STRING;

        mii.dwTypeData = sShow.GetBuffer(0);  
        submenu.SetMenuItemInfo(ID_MENU3_SHOW, FALSE, &mii);

        mii.dwTypeData = sExit.GetBuffer(0);  
        submenu.SetMenuItemInfo(ID_MENU3_EXIT, FALSE, &mii);

        submenu.TrackPopupMenu(0, pt.x, pt.y, m_hWnd);
    }

    return 0;
}

void CResendDlg::CloseDialog(int nVal)
{
	// Close the dialog and exit message loop.
    DestroyWindow();
    AddTrayIcon(FALSE);

    // Exit the message loop
    ::PostQuitMessage(nVal);
}

LRESULT CResendDlg::OnPopupShow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// User chosen "Show" item from the popup menu.
	// Show the dialog.
    KillTimer(0);
    ShowWindow(SW_SHOW);
    return 0;
}

LRESULT CResendDlg::OnPopupExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// User chosen "Exit" item from the popup menu.
	// Exit the app.
    KillTimer(0);
    CloseDialog(0);

    return 0;
}

LRESULT CResendDlg::OnListItemChanging(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
{  
	// User clicks a list item's checkbox.
	// Depending on current state, we should
	// either allow or prevent changing the item
    NMLISTVIEW* pnmlv = (NMLISTVIEW *)pnmh;
    if(pnmlv->iItem>=0 && (pnmlv->uChanged&LVIF_STATE) && 
        ((pnmlv->uNewState&LVIS_STATEIMAGEMASK)!=(pnmlv->uOldState&LVIS_STATEIMAGEMASK)))
    {
		// If we are currently send error reports, than prevent 
		// modifying check box state.
		CErrorReportSender* pSender = CErrorReportSender::GetInstance();
		if(pSender->IsSendingNow())
            return TRUE;    
    }

	// Allow modifying item state
    return 0;
}

LRESULT CResendDlg::OnListItemChanged(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
{  
	// User clicks a list item's checkbox.
	// We need to update total size of selected crash reports.
    NMLISTVIEW* pnmlv = (NMLISTVIEW *)pnmh;
    if(pnmlv->iItem>=0 && (pnmlv->uChanged&LVIF_STATE) && 
        ((pnmlv->uNewState&LVIS_STATEIMAGEMASK)!=(pnmlv->uOldState&LVIS_STATEIMAGEMASK)))
    {    
        UpdateSelectionSize();
    }
    return 0;
}

LRESULT CResendDlg::OnListDblClick(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
{
	// User double-clicks a list item.
	// We need to open details dialog for the selected crash report.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	if(pSender->IsSendingNow())    
        return 0; // Do nothing if in progress of sending

    NMITEMACTIVATE* pia = (NMITEMACTIVATE*)pnmh;
    if(pia->iItem>=0)
    {
        int nReport = (int)m_listReports.GetItemData(pia->iItem);

		// Show Error Report Details dialog
        CDetailDlg dlg;
        dlg.m_nCurReport = nReport;
        dlg.DoModal(m_hWnd);        
    }
    return 0;
}

LRESULT CResendDlg::OnListRClick(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
{
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	CPoint pt;
    GetCursorPos(&pt);
    CMenu menu = LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_POPUPMENU));  
    CMenu submenu = menu.GetSubMenu(5);

    strconv_t strconv;
	CString sSelectAll = pSender->GetLangStr(_T("ResendDlg"), _T("SelectAll"));
	CString sDeselectAll = pSender->GetLangStr(_T("ResendDlg"), _T("DeselectAll"));
	CString sDeleteSelected = pSender->GetLangStr(_T("ResendDlg"), _T("DeleteSelected"));
	CString sDeleteAll = pSender->GetLangStr(_T("ResendDlg"), _T("DeleteAll"));

    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STRING;

    mii.dwTypeData = sSelectAll.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_MENU6_SELECTALL, FALSE, &mii);

    mii.dwTypeData = sDeselectAll.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_MENU6_DESELECTALL, FALSE, &mii);

	mii.dwTypeData = sDeleteSelected.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_MENU6_DELETESELECTED, FALSE, &mii);

	mii.dwTypeData = sDeleteAll.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_MENU6_DELETEALL, FALSE, &mii);

	BOOL bSendingNow = pSender->IsSendingNow();

	// Get count of checked list items
	int nItems = 0;
	int nChecked = 0;
	int i;
    for(i=0; i<m_listReports.GetItemCount(); i++)
    {
		nItems++;

		// If list item checked
		if(m_listReports.GetCheckState(i))
			nChecked++;
	}
	
	submenu.EnableMenuItem(ID_MENU6_SELECTALL, (!bSendingNow && nItems>0)?MF_ENABLED:MF_DISABLED);
	submenu.EnableMenuItem(ID_MENU6_DESELECTALL, (!bSendingNow && nItems>0)?MF_ENABLED:MF_DISABLED);	
	submenu.EnableMenuItem(ID_MENU6_DELETESELECTED, (!bSendingNow && nChecked>0)?MF_ENABLED:MF_DISABLED);
	submenu.EnableMenuItem(ID_MENU6_DELETEALL, (!bSendingNow && nItems>0)?MF_ENABLED:MF_DISABLED);

	submenu.TrackPopupMenu(0, pt.x, pt.y, m_hWnd);
    
	return 0;
}

LRESULT CResendDlg::OnPopupSelectAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	if(pSender->IsSendingNow())    
        return 0; // Do nothing if in progress of sending

	int i;
    for(i=0; i<m_listReports.GetItemCount(); i++)
    {
		m_listReports.SetCheckState(i, TRUE);
    }

	UpdateSelectionSize();
	return 0;
}

LRESULT CResendDlg::OnPopupDeselectAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	if(pSender->IsSendingNow())    
        return 0; // Do nothing if in progress of sending

	int i;
    for(i=0; i<m_listReports.GetItemCount(); i++)
    {
		m_listReports.SetCheckState(i, FALSE);
    }

	UpdateSelectionSize();	
	return 0;
}

LRESULT CResendDlg::OnPopupDeleteSelected(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();	
	if(pSender->IsSendingNow())    
        return 0; // Do nothing if in progress of sending

	// Walk through error reports
	int i;
    for(i=0; i<m_listReports.GetItemCount(); i++)
    {
		// If list item checked
		if(m_listReports.GetCheckState(i))
		{
			// Get error report index from item data
			int nReport = (int)m_listReports.GetItemData(i);

			// Delete report
			pSender->GetCrashInfo()->DeleteReport(nReport);   			
		}
    }

	// Delete selected list items
	BOOL bFound = TRUE;
	while(bFound)
	{
		bFound = FALSE;

		int i;
		for(i=0; i<m_listReports.GetItemCount(); i++)
		{
			// If list item checked
			if(m_listReports.GetCheckState(i))
			{
				bFound = TRUE;
				m_listReports.DeleteItem(i);
				break;
			}
		}
	}

	UpdateSelectionSize();	
	return 0;
}

LRESULT CResendDlg::OnPopupDeleteAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// Delete all error reports
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	if(pSender->IsSendingNow())    
        return 0; // Do nothing if in progress of sending

	pSender->GetCrashInfo()->DeleteAllReports();               		
    
	// Delete all list items
	m_listReports.DeleteAllItems();

	UpdateSelectionSize();	
	return 0;
}

LRESULT CResendDlg::OnSendNow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// User clicked "Send Now"/"Cancel" button.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	if(!pSender->IsSendingNow()) // "Send Now" clicked.
    {
		m_nSendAttempt ++;

        int i;
        for(i=0; i<m_listReports.GetItemCount(); i++)
        {
			int nReport = (int)m_listReports.GetItemData(i);        
			BOOL bSelected = m_listReports.GetCheckState(i);

			CErrorReportInfo* eri = pSender->GetCrashInfo()->GetReport(nReport);            
			eri->Select(bSelected);
			
			// Mark failed reports as pending to resend them
			if(eri->GetDeliveryStatus() == FAILED)
				eri->SetDeliveryStatus(PENDING);

            if(bSelected)
            {                
				if(eri->GetDeliveryStatus() == PENDING)
                {
                    m_listReports.SetItemText(i, 2, 
						Utility::GetINIString(pSender->GetCrashInfo()->m_sLangFileName, _T("ResendDlg"), _T("StatusPending")));
                }				
            }    
			else
			{
				m_listReports.SetItemText(i, 2, _T(""));
			}
        }

        m_ActionOnClose = HIDE;

		m_statText.SetWindowText(pSender->GetLangStr(_T("ResendDlg"), _T("DeliveryingReports")));

        m_statSize.ShowWindow(SW_HIDE);
        m_statConsent.ShowWindow(SW_HIDE);
        m_linkPrivacyPolicy.ShowWindow(SW_HIDE);  
        m_btnOtherActions.ShowWindow(SW_HIDE);
        m_btnShowLog.ShowWindow(SW_HIDE);
        m_dlgActionProgress.ShowWindow(SW_SHOW);  
		m_btnSendNow.SetWindowText(pSender->GetLangStr(_T("ProgressDlg"), _T("Cancel")));

        SetTimer(1, 250); // Update this dialog every 250 ms

		if(m_nSendAttempt==1)
			SetTimer(2, 3000); // Hide this dialog in 3 sec.  

		// Send error reports
		pSender->Run();
    }
    else // "Cancel" clicked
    {
        m_btnSendNow.EnableWindow(0);
        KillTimer(2); // Don't hide window 
        pSender->Cancel();    
    }

    return 0;
}

LRESULT CResendDlg::OnShowLog(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	HINSTANCE hInst = ShellExecute(m_hWnd, _T("open"), pSender->GetLogFilePath(), NULL, NULL, SW_SHOW);
    ATLASSERT((int)hInst>32);
    hInst;
    return 0;
}

int CResendDlg::FindListItemByReportIndex(int nReport)
{
    int i;
    for(i=0; i<m_listReports.GetItemCount(); i++)
    {
        int nData = (int)m_listReports.GetItemData(i);
        if(nData==nReport)
            return i;
    }

    return -1;
}

LRESULT CResendDlg::OnOtherActions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// This method is called when user clicks the "Other actions..." button.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

    CPoint pt;
    GetCursorPos(&pt);
    CMenu menu = LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_POPUPMENU));  
    CMenu submenu = menu.GetSubMenu(3);

    strconv_t strconv;
	CString sRemindLater = pSender->GetLangStr(_T("ResendDlg"), _T("PopupRemindLater"));
	CString sNeverRemind = pSender->GetLangStr(_T("ResendDlg"), _T("PopupNeverRemind"));

    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STRING;

    mii.dwTypeData = sRemindLater.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_MENU4_REMINDLATER, FALSE, &mii);

    mii.dwTypeData = sNeverRemind.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_MENU4_NEVERREMIND, FALSE, &mii);

    submenu.TrackPopupMenu(0, pt.x, pt.y, m_hWnd);
    return 0;
}

LRESULT CResendDlg::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// This method is called when user clicks the Close (x) button on the dialog.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	// Either hide the dialog or close it.
    if(m_ActionOnClose==EXIT)
    {        
		pSender->GetCrashInfo()->SetLastRemindDateToday();
        CloseDialog(0);
        return 0;
    }
    else if(m_ActionOnClose==HIDE)
    {
        AnimateWindow(m_hWnd, 200, AW_HIDE|AW_BLEND); 	  
        return 0;
    }

    return 0;
}

LRESULT CResendDlg::OnRemindLater(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{  
	// This method is called when user clicks "Remind me later" item from the popup menu.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
    pSender->GetCrashInfo()->SetLastRemindDateToday();
    pSender->GetCrashInfo()->SetRemindPolicy(REMIND_LATER);

    KillTimer(0);
    CloseDialog(0);
    return 0;
}

LRESULT CResendDlg::OnNeverRemind(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// This method is called when user clicks "Never Remind" item from the popup menu.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	pSender->GetCrashInfo()->SetLastRemindDateToday();
	pSender->GetCrashInfo()->SetRemindPolicy(NEVER_REMIND);

    KillTimer(0);
    CloseDialog(0);
    return 0;
}

void CResendDlg::AddTrayIcon(BOOL bAdd)
{
	// This method adds or removes tray icon.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
    
	// Set up icon data
	NOTIFYICONDATA nf;
    memset(&nf,0,sizeof(NOTIFYICONDATA));
    nf.cbSize = sizeof(NOTIFYICONDATA);
    nf.hWnd = m_hWnd;
    nf.uID = 0;

    if(bAdd) // Add icon to tray
    {	
        nf.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO ;
        nf.uCallbackMessage = WM_RESENDTRAYICON;
        nf.uVersion = NOTIFYICON_VERSION;

		// Format balloon tip caption
        CString sTip; 
		sTip.Format(pSender->GetLangStr(_T("ResendDlg"), _T("DlgCaption")), pSender->GetCrashInfo()->m_sAppName);

#if (NTDDI_VERSION >= NTDDI_WIN2K)
		// Truncate the string if it is too long.
		sTip = Utility::AddEllipsis(sTip, 127);
        _TCSCPY_S(nf.szTip, 127, sTip);
#else
		// Truncate the string if it is too long.
		sTip = Utility::AddEllipsis(sTip, 63);
        _TCSCPY_S(nf.szTip, 63, sTip);
#endif
		// Set balloon icon
		HICON hIcon = pSender->GetCrashInfo()->GetCustomIcon();
        if(!hIcon)
            hIcon = ::LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME));    
        nf.hIcon = hIcon;
		// Format balloon text
        CString sInfo;
		sInfo.Format(pSender->GetLangStr(_T("ResendDlg"), _T("BalloonText")), 
			pSender->GetCrashInfo()->m_sAppName, pSender->GetCrashInfo()->m_sAppName);
		// Truncate the string if it is too long.
		sInfo = Utility::AddEllipsis(sInfo, 255);
        _TCSCPY_S(nf.szInfo, 255, sInfo.GetBuffer(0));

        CString sInfoTitle;
		sInfoTitle.Format(pSender->GetLangStr(_T("ResendDlg"), _T("BalloonCaption")), 
			pSender->GetCrashInfo()->m_sAppName);
		// Truncate the string if it is too long.
		sInfoTitle = Utility::AddEllipsis(sInfoTitle, 63);
        _TCSCPY_S(nf.szInfoTitle, 63, sInfoTitle.GetBuffer(0));

        Shell_NotifyIcon(NIM_ADD,&nf);
    }
    else // Delete icon
    {
        Shell_NotifyIcon(NIM_DELETE,&nf);
    }	
}

void CResendDlg::UpdateSelectionSize()
{
	// This method is called when user checks/unchecks an item
	// in the list. We should update the total selected size text.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
    int nItemsSelected = 0;
    ULONG64 uSelectedFilesSize = 0;

	// Walk through items
    int i;
    for(i=0; i<m_listReports.GetItemCount(); i++)
    {
        if(m_listReports.GetCheckState(i)) // If item checked
        {
			// Determine the index of crash report associated with the item.
            int nReport = (int)m_listReports.GetItemData(i);

			// Increment item counter
            nItemsSelected++;
			// Update totals
			uSelectedFilesSize += pSender->GetCrashInfo()->GetReport(nReport)->GetTotalSize();
        }
    }

	// Update the text
    CString sText;
	sText.Format(pSender->GetLangStr(_T("ResendDlg"), _T("SelectedSize")), nItemsSelected, 
        Utility::FileSizeToStr(uSelectedFilesSize).GetBuffer(0));
    m_statSize.SetWindowText(sText);

	// Enable/disable "Send Now button", depending on selected item count.
    m_btnSendNow.EnableWindow(nItemsSelected>0?TRUE:FALSE);
}

LRESULT CResendDlg::OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{ 
	// This method is called when a timer ticks.

    if(wParam==0)
        DoBalloonTimer();
    else if(wParam==1)
        DoProgressTimer();
    else if(wParam==2)
        DoHideWindowTimer();

    return 0;
}

void CResendDlg::DoBalloonTimer()
{
    if(m_nTimerTick==0)
    {
        // Show tray icon and balloon.
        AddTrayIcon(TRUE);

		// Stop timer
        KillTimer(0);

        // Wait for one minute. If user doesn't want to click the balloon, exit.
        SetTimer(0, 60000);
    }
    else if(m_nTimerTick==1)
    {
		// Stop timer
        KillTimer(0);
		// Close the app
        CloseDialog(0);
    }

	// Increment counter
    m_nTimerTick ++;
}

void CResendDlg::DoProgressTimer()
{   
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

    // Get current progress
    int nProgressPct = 0;
    std::vector<CString> messages;
    pSender->GetCurOpStatus(nProgressPct, messages);

    // Update progress bar
    m_dlgActionProgress.m_prgProgress.SetPos(nProgressPct);

	int nCurItem = FindListItemByReportIndex(pSender->GetCurReport());

    unsigned i;
    for(i=0; i<messages.size(); i++)
    { 
        m_dlgActionProgress.m_statActionDesc.SetWindowText(messages[i]);
		
        if(messages[i].CompareNoCase(_T("[status_success]"))==0)
        {
            m_listReports.SetItemText(nCurItem, 2, 
				pSender->GetLangStr(_T("ResendDlg"), _T("StatusSucceeded")));
            
        }
        else if(messages[i].CompareNoCase(_T("[status_failed]"))==0)
        {            
            m_listReports.SetItemText(nCurItem, 2, 
				pSender->GetLangStr(_T("ResendDlg"), _T("StatusFailed")));            
        }        
        else if(messages[i].CompareNoCase(_T("[confirm_launch_email_client]"))==0)
        {       
			// We need to display message box to get user
			// confirmation on launching mail program.

			// Stop the timer that hides the window in 3 sec.
            KillTimer(2);        
			  
			// Save visibility state (to restore it later).
			BOOL bVisible = IsWindowVisible();

			// Display the dialog.
            ShowWindow(SW_SHOW);
			// Position it on top of other windows.
            SetWindowPos(HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
			// Set focus to it.
            SetFocus();  
			// Update it.
            RedrawWindow(0, 0, RDW_ERASE|RDW_FRAME|RDW_INVALIDATE);
            m_listReports.RedrawWindow(0, 0, RDW_ERASE|RDW_FRAME|RDW_INVALIDATE);  

			// Determine window mirroring flags (language specific).
            DWORD dwFlags = 0;
			CString sRTL = Utility::GetINIString(pSender->GetCrashInfo()->m_sLangFileName, _T("Settings"), _T("RTLReading"));
            if(sRTL.CompareNoCase(_T("1"))==0)
                dwFlags = MB_RTLREADING;

			// Get mail program name.
            CString sMailClientName;        
            CMailMsg::DetectMailClient(sMailClientName);
            CString msg;
			msg.Format(pSender->GetLangStr(_T("ProgressDlg"), _T("ConfirmLaunchEmailClient")), sMailClientName);

			// Display message box.
            CString sCaption = pSender->GetLangStr(_T("ProgressDlg"), _T("DlgCaption"));
            CString sTitle;
			sTitle.Format(sCaption, pSender->GetCrashInfo()->m_sAppName);
            INT_PTR result = MessageBox(msg, 
                sTitle,
                MB_OKCANCEL|MB_ICONQUESTION|dwFlags);

			// Update window
            RedrawWindow(0, 0, RDW_ERASE|RDW_FRAME|RDW_INVALIDATE);
            m_listReports.RedrawWindow(0, 0, RDW_ERASE|RDW_FRAME|RDW_INVALIDATE);  
			            
			// Unblock worker thread.
            pSender->FeedbackReady(result==IDOK?0:1);       

			// Restore window visibility
            ShowWindow(bVisible?SW_SHOW:SW_HIDE);            
        }    
    }
}

LRESULT CResendDlg::OnNextItemHint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// This method determines what error report should be sent next.
	// Error reports are being sent in the order they appear in the list.
	
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	// Walk through items and look for pending one
	int i;
    for(i=0; i<m_listReports.GetItemCount(); i++)
    {
        if(m_listReports.GetCheckState(i)) // If item checked
        {
			// Determine the index of crash report associated with the item.
            int nReport = (int)m_listReports.GetItemData(i);

			CErrorReportInfo* pERI = pSender->GetCrashInfo()->GetReport(nReport);
			if(pERI==NULL)
				continue;

			if(pERI->GetDeliveryStatus()!=PENDING)
				continue;
			
			return nReport;
        }
    }

	// No pending items found
	return -1;
}

LRESULT CResendDlg::OnItemStatusChanged(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{	
	int nReport = (int)wParam;
	DELIVERY_STATUS Status = (DELIVERY_STATUS)lParam;

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	CString sStatus;
	if(Status==PENDING)
		sStatus = pSender->GetLangStr(_T("ResendDlg"), _T("StatusPending"));
	else if(Status==INPROGRESS)
		sStatus = pSender->GetLangStr(_T("ResendDlg"), _T("StatusInProgress"));
	else if(Status==DELIVERED)
		sStatus = pSender->GetLangStr(_T("ResendDlg"), _T("StatusSucceeded"));
	else if(Status==FAILED)
		sStatus = pSender->GetLangStr(_T("ResendDlg"), _T("StatusFailed"));	
	
	int nItem = FindListItemByReportIndex(nReport);

	m_listReports.SetItemText(nItem, 2, sStatus);
	m_listReports.EnsureVisible(nItem, TRUE);
	m_listReports.SetItemState(nItem, LVIS_SELECTED, LVIS_SELECTED);

	return 0;
}
	
LRESULT CResendDlg::OnDeliveryComplete(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	m_ActionOnClose = EXIT;
    
	// Stop timers
	KillTimer(1);
    KillTimer(2);

	// Update control states.
    
	m_btnSendNow.EnableWindow(1);
    m_btnOtherActions.ShowWindow(SW_SHOW);
    m_btnShowLog.ShowWindow(SW_SHOW);  
    m_statSize.ShowWindow(SW_SHOW);
    m_statConsent.ShowWindow(SW_SHOW);
    m_linkPrivacyPolicy.ShowWindow(SW_SHOW);  
    m_btnOtherActions.ShowWindow(SW_SHOW);
    m_dlgActionProgress.ShowWindow(SW_HIDE);  

    m_btnSendNow.SetWindowText(pSender->GetLangStr(_T("ResendDlg"), _T("SendNow")));
	m_statText.SetWindowText(pSender->GetLangStr(_T("ResendDlg"), _T("ClickForDetails")));

	// Update Status column of the list view
    int i;
    for(i=0; i<m_listReports.GetItemCount(); i++)
    {
        BOOL bSelected = m_listReports.GetCheckState(i);  
        if(bSelected)
        {
            int nReport = (int)m_listReports.GetItemData(i);

			DELIVERY_STATUS status = pSender->GetCrashInfo()->GetReport(nReport)->GetDeliveryStatus();
            if(status==PENDING)
            {
                m_listReports.SetItemText(i, 2, _T(""));
            }            
        }
    }
	
	// Determine window mirroring settings
    DWORD dwFlags = 0;
	CString sRTL = pSender->GetLangStr(_T("Settings"), _T("RTLReading"));
    if(sRTL.CompareNoCase(_T("1"))==0)
        dwFlags = MB_RTLREADING;

    CString sCaption;
	sCaption.Format(pSender->GetLangStr(_T("ResendDlg"), _T("DlgCaption")), 
		pSender->GetCrashInfo()->m_sAppName);

	if(pSender->HasErrors())
    {
		// Show dialog
        ShowWindow(SW_SHOW);
		// Display it on top of other windows
        SetWindowPos(HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		// Set focus to it
        SetFocus();  
		// Redraw it
        RedrawWindow(0, 0, RDW_ERASE|RDW_FRAME|RDW_INVALIDATE);
        m_listReports.RedrawWindow(0, 0, RDW_ERASE|RDW_FRAME|RDW_INVALIDATE);  

		// Display message box
		MessageBox(pSender->GetLangStr(_T("ResendDlg"), _T("DeliveryFailed")), 
            sCaption, 
            MB_OK|MB_ICONINFORMATION|dwFlags);  

    }
    else 
    {
        if(IsWindowVisible())
        {
			// Display message box
            MessageBox(pSender->GetLangStr(_T("ResendDlg"), _T("DeliverySucceeded")), 
                sCaption, 
                MB_OK|MB_ICONINFORMATION|dwFlags);
        }

		// Close the dialog
        SendMessage(WM_CLOSE);
    }

	return 0;
}

void CResendDlg::DoHideWindowTimer()
{
	// Hide the dialog smoothly
	AnimateWindow(m_hWnd, 200, AW_HIDE|AW_BLEND);         
	// Stop the timer
    KillTimer(2);
}

LRESULT CResendDlg::OnReportSizeChanged(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	int nReport = (int)wParam;
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	// Update list
	int nItem = FindListItemByReportIndex(nReport);
	CString sTotalSize = Utility::FileSizeToStr(pSender->GetCrashInfo()->GetReport(nReport)->GetTotalSize());
    m_listReports.SetItemText(nItem, 1, sTotalSize);

	// Update the selection size
	UpdateSelectionSize();

	return 0;
}
