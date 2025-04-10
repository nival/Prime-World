/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#include "stdafx.h"
#include "DetailDlg.h"
#include "Utility.h"
#include "CrashInfoReader.h"
#include "ErrorReportSender.h"
#include "strconv.h"

LRESULT CDetailDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// The dialog will be resizable, init resize map now.
    DlgResize_Init();

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

    // Mirror this window if RTL language is in use
	CString sRTL = pSender->GetLangStr(_T("Settings"), _T("RTLReading"));
    if(sRTL.CompareNoCase(_T("1"))==0)
    {
        Utility::SetLayoutRTL(m_hWnd);
    }

	// Set dialog caption text.
    SetWindowText(pSender->GetLangStr(_T("DetailDlg"), _T("DlgCaption")));

	// Set up file preview control.
    m_previewMode = PREVIEW_AUTO;
    m_filePreview.SubclassWindow(GetDlgItem(IDC_PREVIEW));
    m_filePreview.SetBytesPerLine(10);
	m_filePreview.SetEmptyMessage(pSender->GetLangStr(_T("DetailDlg"), _T("NoDataToDisplay")));

    // Init "Privacy Policy" link.
    m_linkPrivacyPolicy.SubclassWindow(GetDlgItem(IDC_PRIVACYPOLICY));
	m_linkPrivacyPolicy.SetHyperLink(pSender->GetCrashInfo()->m_sPrivacyPolicyURL);
	m_linkPrivacyPolicy.SetLabel(pSender->GetLangStr(_T("DetailDlg"), _T("PrivacyPolicy")));
		
	if(!pSender->GetCrashInfo()->m_sPrivacyPolicyURL.IsEmpty())
        m_linkPrivacyPolicy.ShowWindow(SW_SHOW);
    else
        m_linkPrivacyPolicy.ShowWindow(SW_HIDE);

	// Set up header text
    CStatic statHeader = GetDlgItem(IDC_HEADERTEXT);
	statHeader.SetWindowText(pSender->GetLangStr(_T("DetailDlg"), _T("DoubleClickAnItem")));  

	// Set up the list control
    m_list = GetDlgItem(IDC_FILE_LIST);
    m_list.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, pSender->GetLangStr(_T("DetailDlg"), _T("FieldName")), LVCFMT_LEFT, 150);
	m_list.InsertColumn(1, pSender->GetLangStr(_T("DetailDlg"), _T("FieldDescription")), LVCFMT_LEFT, 180);
	m_list.InsertColumn(3, pSender->GetLangStr(_T("DetailDlg"), _T("FieldSize")), LVCFMT_RIGHT, 60);

	// Init icons for the list
    m_iconList.Create(16, 16, ILC_COLOR32|ILC_MASK, 3, 1);
    m_list.SetImageList(m_iconList, LVSIL_SMALL);
	    
	FillFileItemList();
	    
    // Init "Preview" static control
    m_statPreview = GetDlgItem(IDC_PREVIEWTEXT);
	m_statPreview.SetWindowText(pSender->GetLangStr(_T("DetailDlg"), _T("Preview")));  

    // Init "OK" button
    m_btnClose = GetDlgItem(IDOK);
	m_btnClose.SetWindowText(pSender->GetLangStr(_T("DetailDlg"), _T("Close")));  

    // Init "Export..." button
    m_btnExport = GetDlgItem(IDC_EXPORT);
	m_btnExport.SetWindowText(pSender->GetLangStr(_T("DetailDlg"), _T("Export")));  

    // center the dialog on the screen
    CenterWindow();  

    return TRUE;
}

LRESULT CDetailDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_filePreview.SetFile(NULL);
	return NULL;
}

void CDetailDlg::FillFileItemList()
{
	// Walk through files included into error report
	// Insert items to the list        
	
	m_iconList.RemoveAll();
	m_list.DeleteAllItems();

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	int nCount = pSender->GetCrashInfo()->GetReport(m_nCurReport)->GetFileItemCount();
    int i;	
    for (i = 0; i<nCount; i++)
    {     
		    ERIFileItem* pfi = pSender->GetCrashInfo()->GetReport(m_nCurReport)->GetFileItemByIndex(i);
		    CString sDestFile = pfi->m_sDestFile;
        CString sSrcFile = pfi->m_sSrcFile;
        CString sFileDesc = pfi->m_sDesc;
		    HICON hIcon = NULL;
		    CString sTypeName;
		    LONGLONG lFileSize = 0;
		    CString sSize;
        
		    // Get file info
		    pfi->GetFileInfo(hIcon, sTypeName, lFileSize);

        int iImage = -1;
        if(hIcon!=NULL)
        {
		      	// If icon loaded, add its copy to imagelist
            iImage = m_iconList.AddIcon(hIcon);
			      // and destroy the original icon.
            DestroyIcon(hIcon);
        }

		    // Insert an item to the list control
        int nItem = m_list.InsertItem(i, sDestFile, iImage);
    		m_list.SetItemData(nItem, i);
		        
        m_list.SetItemText(nItem, 1, sFileDesc);    

    		sSize = Utility::FileSizeToStr(lFileSize);
    		m_list.SetItemText(nItem, 2, sSize);            
    }

	// Select the first list item
    m_list.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

}

LRESULT CDetailDlg::OnItemChanged(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
{
    LPNMLISTVIEW lpItem = (LPNMLISTVIEW)pnmh; 
    int iItem = lpItem->iItem;

    if (lpItem->uChanged & LVIF_STATE
        && lpItem->uNewState & LVIS_SELECTED)
    {
        SelectItem(iItem);
    }

    return 0;
}

LRESULT CDetailDlg::OnItemDblClicked(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
{
	// This method is called when user double-clicks an item in the list control.
	// We need to open the file with an appropriate program.

    LPNMLISTVIEW lpItem           = (LPNMLISTVIEW)pnmh; 
    int iItem                     = lpItem->iItem;
    DWORD_PTR dwRet               = 0;

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	CCrashInfoReader* pCrashInfo = pSender->GetCrashInfo();

	// Check if double-clicked on empty space.
    if (iItem < 0)
	{
		// Do nothing
        return 0;
	}

	// Look for n-th item
	ERIFileItem* pFileItem = pCrashInfo->GetReport(m_nCurReport)->GetFileItemByIndex(iItem);
	if(pFileItem==NULL)
		return 0;
    
	// Get file name
    CString sFileName = pFileItem->m_sSrcFile;

	// Open the file with shell-provided functionality
    dwRet = (DWORD_PTR)::ShellExecute(0, _T("open"), sFileName,
        0, 0, SW_SHOWNORMAL);
    ATLASSERT(dwRet > 32);

    return 0;
}

void CDetailDlg::SelectItem(int iItem)
{
	// This method is called when user selects an item.
	// We need to open the item for preview.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	CCrashInfoReader* pCrashInfo = pSender->GetCrashInfo();

    // Look for n-th item
	ERIFileItem* pFileItem = pCrashInfo->GetReport(m_nCurReport)->GetFileItemByIndex(iItem);
	if(pFileItem==NULL)
		return;
    
	// Update preview control
    m_previewMode = PREVIEW_AUTO;
    m_textEncoding = ENC_AUTO;
    m_filePreview.SetFile(pFileItem->m_sSrcFile, m_previewMode);
}

LRESULT CDetailDlg::OnOK(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// Close button clicked - close the dialog.
    EndDialog(0);
    return 0;
}

LRESULT CDetailDlg::OnExport(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// This method is called when user clicks the "Export" button. 
	// We should export crash report contents as a ZIP archive to
	// user-specified folder.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	CCrashInfoReader* pCrashInfo = pSender->GetCrashInfo();

	// Format file name for the output ZIP archive.
    CString sFileName = pCrashInfo->GetReport(m_nCurReport)->GetCrashGUID() + _T(".zip");

	// Display "Save File" dialog.
    CFileDialog dlg(FALSE, _T("*.zip"), sFileName,
        OFN_PATHMUSTEXIST|OFN_OVERWRITEPROMPT,
        _T("ZIP Files (*.zip)\0*.zip\0All Files (*.*)\0*.*\0\0"), m_hWnd);

    INT_PTR result = dlg.DoModal();
    if(result==IDOK)
    {
		// Determine what destination user chosen
        CString sExportFileName = dlg.m_szFileName;

		// Export crash report assynchronously
        pSender->ExportReport(sExportFileName);
    }

    return 0;
}

LRESULT CDetailDlg::OnPreviewRClick(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
{
	// This method is called when user right-clicks the preview area.
	// We need to display popup menu.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	
    CPoint pt;
    GetCursorPos(&pt);

    CMenu menu;
    menu.LoadMenu(IDR_POPUPMENU);

    CMenu submenu = menu.GetSubMenu(1);
    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STRING;

    strconv_t strconv;
	CString sAuto = pSender->GetLangStr(_T("DetailDlg"), _T("PreviewAuto"));
	CString sText = pSender->GetLangStr(_T("DetailDlg"), _T("PreviewText"));
	CString sHex = pSender->GetLangStr(_T("DetailDlg"), _T("PreviewHex"));
	CString sImage = pSender->GetLangStr(_T("DetailDlg"), _T("PreviewImage"));
	CString sVideo = pSender->GetLangStr(_T("DetailDlg"), _T("PreviewVideo"));
	CString sEncoding = pSender->GetLangStr(_T("DetailDlg"), _T("Encoding"));

    mii.dwTypeData = sAuto.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_PREVIEW_AUTO, FALSE, &mii);

    mii.dwTypeData = sHex.GetBuffer(0);
    submenu.SetMenuItemInfo(ID_PREVIEW_HEX, FALSE, &mii);

    mii.dwTypeData = sText.GetBuffer(0);
    submenu.SetMenuItemInfo(ID_PREVIEW_TEXT, FALSE, &mii);

    mii.dwTypeData = sImage.GetBuffer(0);
    submenu.SetMenuItemInfo(ID_PREVIEW_IMAGE, FALSE, &mii);

    mii.dwTypeData = sVideo.GetBuffer(0);
    submenu.SetMenuItemInfo(ID_PREVIEW_VIDEO, FALSE, &mii);

    UINT uItem = ID_PREVIEW_AUTO;
    if(m_previewMode==PREVIEW_HEX)
        uItem = ID_PREVIEW_HEX;
    else if(m_previewMode==PREVIEW_TEXT)
        uItem = ID_PREVIEW_TEXT;
    else if(m_previewMode==PREVIEW_IMAGE)
        uItem = ID_PREVIEW_IMAGE;
	else if(m_previewMode==PREVIEW_VIDEO)
        uItem = ID_PREVIEW_VIDEO;

    submenu.CheckMenuRadioItem(ID_PREVIEW_AUTO, ID_PREVIEW_VIDEO, uItem, MF_BYCOMMAND); 

    if(m_filePreview.GetPreviewMode()!=PREVIEW_TEXT)
    {
        submenu.DeleteMenu(6, MF_BYPOSITION);
        submenu.DeleteMenu(5, MF_BYPOSITION);
    }
    else
    {
        CMenuHandle TextEncMenu = submenu.GetSubMenu(6);
        mii.dwTypeData = sEncoding.GetBuffer(0);
        submenu.SetMenuItemInfo(6, TRUE, &mii);


        UINT uItem2 = ID_ENCODING_AUTO;
        if(m_textEncoding==ENC_AUTO)
            uItem2 = ID_ENCODING_AUTO;
        else if(m_textEncoding==ENC_ASCII)
            uItem2 = ID_ENCODING_ASCII;
        else if(m_textEncoding==ENC_UTF8)
            uItem2 = ID_ENCODING_UTF8;
        else if(m_textEncoding==ENC_UTF16_LE)
            uItem2 = ID_ENCODING_UTF16;
        else if(m_textEncoding==ENC_UTF16_BE)
            uItem2 = ID_ENCODING_UTF16BE;

        TextEncMenu.CheckMenuRadioItem(ID_ENCODING_AUTO, ID_ENCODING_UTF16BE, uItem2, MF_BYCOMMAND); 
    }

    submenu.TrackPopupMenu(TPM_LEFTBUTTON, pt.x, pt.y, m_hWnd);

    return 0;
}

LRESULT CDetailDlg::OnPreviewModeChanged(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// User changes file preview mode.
	// Update the preview control state.

    PreviewMode mode = PREVIEW_AUTO;
    if(wID==ID_PREVIEW_TEXT)
        mode = PREVIEW_TEXT;
    else if(wID==ID_PREVIEW_HEX)
        mode = PREVIEW_HEX;
    else if(wID==ID_PREVIEW_IMAGE)
        mode = PREVIEW_IMAGE;
	else if(wID==ID_PREVIEW_VIDEO)
        mode = PREVIEW_VIDEO;
    m_previewMode = mode;
    m_textEncoding = ENC_AUTO;
    m_filePreview.SetPreviewMode(mode);
    return 0;
}

LRESULT CDetailDlg::OnTextEncodingChanged(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// User changes file preview encoding (for text files).
	// Update the preview control state.

    TextEncoding enc = ENC_AUTO;
    if(wID==ID_ENCODING_AUTO)
        enc = ENC_AUTO; 
    else if(wID==ID_ENCODING_ASCII)
        enc = ENC_ASCII; 
    else if(wID==ID_ENCODING_UTF8)
        enc = ENC_UTF8; 
    else if(wID==ID_ENCODING_UTF16)
        enc = ENC_UTF16_LE; 
    else if(wID==ID_ENCODING_UTF16BE)
        enc = ENC_UTF16_BE; 
    m_textEncoding = enc;
    m_filePreview.SetTextEncoding(enc);
    return 0;
}

LRESULT CDetailDlg::OnListRClick(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
{
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	CPoint pt;
    GetCursorPos(&pt);
    CMenu menu = LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_POPUPMENU));  
    CMenu submenu = menu.GetSubMenu(6);

    strconv_t strconv;
	CString sOpen = pSender->GetLangStr(_T("DetailDlg"), _T("Open"));
	CString sDeleteSelected = pSender->GetLangStr(_T("DetailDlg"), _T("DeleteSelected"));
	CString sAttachMoreFiles = pSender->GetLangStr(_T("DetailDlg"), _T("AttachMoreFiles"));
	

    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STRING;

    mii.dwTypeData = sOpen.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_MENU7_OPEN, FALSE, &mii);
	    
	mii.dwTypeData = sDeleteSelected.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_MENU7_DELETESELECTEDFILE, FALSE, &mii);

	mii.dwTypeData = sAttachMoreFiles.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_MENU7_ATTACHMOREFILES, FALSE, &mii);

	// Get count of selected list items
	int nItems = 0;
	int nSelected = 0;
	BOOL bAllowDelete = TRUE;
	int i;
    for(i=0; i<m_list.GetItemCount(); i++)
    {
		nItems++;

		// If list item checked
		if(m_list.GetItemState(i, LVIS_SELECTED)!=0)
			nSelected++;
		else
			continue;

		// Find file item in error report
		int nItem = (int)m_list.GetItemData(i);
		ERIFileItem* pfi = pSender->GetCrashInfo()->GetReport(m_nCurReport)->GetFileItemByIndex(nItem);
		if(!pfi->m_bAllowDelete)
			bAllowDelete = FALSE;
	}
	
	submenu.EnableMenuItem(ID_MENU7_OPEN, (nSelected==1)?MF_ENABLED:MF_DISABLED);
	submenu.EnableMenuItem(ID_MENU7_DELETESELECTEDFILE, (nSelected>0 && bAllowDelete)?MF_ENABLED:MF_DISABLED);	

	if(!pSender->GetCrashInfo()->m_bAllowAttachMoreFiles)
	{
		submenu.DeleteMenu(ID_MENU7_ATTACHMOREFILES, MF_BYCOMMAND);	
	}

	submenu.TrackPopupMenu(0, pt.x, pt.y, m_hWnd);
    return 0;
}

LRESULT CDetailDlg::OnPopupOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{	
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	CCrashInfoReader* pCrashInfo = pSender->GetCrashInfo();

	// Get count of selected list items
	int nItem = -1;
	int nSelected = 0;
	int i;
    for(i=0; i<m_list.GetItemCount(); i++)
    {
		// If list item selected
		if(m_list.GetItemState(i, LVIS_SELECTED)!=0)
		{
			nItem=i;
			nSelected++;
		}		
	}

	if(nSelected!=1)
		return 0; // Should be exactly one item selected

	// Look for n-th item
	ERIFileItem* pFileItem = pCrashInfo->GetReport(m_nCurReport)->GetFileItemByIndex(nItem);
	if(pFileItem==NULL)
		return 0;
    
	// Get file name
    CString sFileName = pFileItem->m_sSrcFile;

	// Open the file with shell-provided functionality
    DWORD_PTR dwRet = (DWORD_PTR)::ShellExecute(0, _T("open"), sFileName,
        0, 0, SW_SHOWNORMAL);
    ATLASSERT(dwRet > 32);
	dwRet;
	
	return 0;
}

LRESULT CDetailDlg::OnPopupDeleteSelected(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CErrorReportSender* pSender = CErrorReportSender::GetInstance();

	// Walk through selected list items
	std::vector<CString> asFilesToRemove;
	int i;
    for(i=0; i<m_list.GetItemCount(); i++)
    {
		// If list item is not selected
		if(m_list.GetItemState(i, LVIS_SELECTED)==0)
			continue;

		// Determine appropriate file item
		int nItem = (int)m_list.GetItemData(i);		
		ERIFileItem* pfi = pSender->GetCrashInfo()->GetReport(m_nCurReport)->GetFileItemByIndex(nItem);
		if(pfi)
		{
			// Add this file to remove list
			asFilesToRemove.push_back(pfi->m_sDestFile);
		}
	}

	// Reset preview control to avoid locking the file being previewed.
	m_filePreview.SetFile(NULL);

	// Delete selected files from error report
	pSender->GetCrashInfo()->RemoveFilesFromCrashReport(m_nCurReport, asFilesToRemove);

	// Update file items list
	FillFileItemList();

	// Force parent to recalculate report size
	HWND hWndParent = GetParent();
	if(::IsWindow(hWndParent))
		::SendMessage(hWndParent, WM_REPORTSIZECHANGED, m_nCurReport, 0);

	return 0;
}

LRESULT CDetailDlg::OnPopupAddMoreFiles(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// Display "Open File" dialog.
    CFileDialog dlg(TRUE, _T("*.*"), NULL,
        OFN_PATHMUSTEXIST|OFN_ALLOWMULTISELECT,
        _T("All Files (*.*)\0*.*\0\0"), m_hWnd);

    INT_PTR result = dlg.DoModal();
    if(result==IDOK)
    {		
		// Parse the list of files
		TCHAR* str = dlg.m_ofn.lpstrFile;
		std::vector<CString> asItems;		
		CString sItem;
		int i;
		for(i=0; ; i++)
		{
			if(str[i]==0)
			{
				// End of item
				if(sItem.IsEmpty())
					break; // End of multi-string
				asItems.push_back(sItem);
				sItem.Empty();
				continue;
			}
			sItem += str[i];
		}

		std::vector<ERIFileItem> aFiles;
		if(asItems.size()==1)
		{
			// Single file to add
			CString sFileName = asItems[0];
			
			ERIFileItem fi;
			fi.m_bAllowDelete = true;
			fi.m_bMakeCopy = true;
			fi.m_sDestFile = Utility::GetFileName(sFileName);
			fi.m_sSrcFile = sFileName;			
			aFiles.push_back(fi);
		}
		else if(asItems.size()>1)
		{
			// Several files to add
			unsigned j;
			for(j=1; j<asItems.size(); j++)
			{
				CString sFileName = asItems[0]+_T("\\")+asItems[j];
			
				ERIFileItem fi;
				fi.m_bAllowDelete = true;	
				fi.m_bMakeCopy = true;
				fi.m_sDestFile = Utility::GetFileName(sFileName);
				fi.m_sSrcFile = sFileName;			
				aFiles.push_back(fi);
			}
		}

		// Add files to crash report
		CErrorReportSender* pSender = CErrorReportSender::GetInstance();
		CCrashInfoReader* pCrashInfo = pSender->GetCrashInfo();
		pCrashInfo->AddFilesToCrashReport(m_nCurReport, aFiles);

		// Update file items list
		FillFileItemList();

		// Force parent to recalculate report size
		HWND hWndParent = GetParent();
		if(::IsWindow(hWndParent))
			::SendMessage(hWndParent, WM_REPORTSIZECHANGED, m_nCurReport, 0);
	}
	
	return 0;
}

