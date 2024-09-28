#include "StdAfx.h"
#include "../MemoryLib/SymAccess.h"
#include "StackWalk.h"
#include "BSUtil.h"
#include "BSDialogFunctions.h"
#include "FileSystem/FilePath.h"
#include <CommCtrl.h>
#include <Shlwapi.h>

namespace NBSU
{

void ListView_AddColumn( HWND hwnd, const string &strCaption, int nWidth )
{
	LV_COLUMN	Column;
	memset( &Column, 0, sizeof( LV_COLUMN) );

	Column.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	Column.pszText = const_cast<char*>(strCaption.c_str());
	Column.cx = nWidth;
	//Column.iSubItem = nNumber;

	ListView_InsertColumn( hwnd, 1000, &Column );
}



int ListView_AddItem( HWND hwnd, const string &strText, LPARAM lParam, int nItem )
{
	LVITEM Item;
	memset( &Item, 0, sizeof(Item) );
	Item.mask = LVIF_PARAM | LVIF_TEXT;
	Item.iItem = nItem;
	Item.lParam = lParam;
	Item.pszText = const_cast<char*>(strText.c_str());
	Item.cchTextMax = strText.size();
	return ListView_InsertItem( hwnd, &Item );
}



bool SetWindowText( HWND hwndDlg, const int nElementID, const char *pszString )
{
	return SetWindowText( GetDlgItem(hwndDlg, nElementID), pszString ) != FALSE;
}



void PutProcessInWindowTitle( HWND hWnd )
{
  //Set dialog title to exe file name
  const DWORD BUF_SZ = 512;
  TCHAR procName[BUF_SZ * 2 + 4] = TEXT( "" );
  DWORD len = GetModuleFileName( NULL, procName, BUF_SZ );
  procName[ Min( len, BUF_SZ - 1 ) ] = 0;

  TCHAR windowTtl[BUF_SZ] = TEXT( "" );
  DWORD ttlLen = GetWindowText( hWnd, windowTtl, BUF_SZ );
  windowTtl[ Min( ttlLen, BUF_SZ - 1 ) ] = 0;

  StrCat( procName, TEXT( ": " ) );
  StrCat( procName, windowTtl );

  SetWindowText( hWnd, procName );
}



void* SetWindowUserData( HWND hwndDlg, const int nElementID, void *pUserData )
{
	return reinterpret_cast<void*>( SetWindowLong( GetDlgItem(hwndDlg, nElementID), 
																								 GWL_USERDATA, reinterpret_cast<LONG>(pUserData) ) );
}



void* GetWindowUserData( HWND hwndDlg, const int nElementID )
{
	return reinterpret_cast<void*>( GetWindowLong( GetDlgItem(hwndDlg, nElementID), GWL_USERDATA ) );
}



void* SetDlgUserData( HWND hwndDlg, void *pUserData )
{
	return reinterpret_cast<void*>( SetWindowLong( hwndDlg, DWL_USER, reinterpret_cast<LONG>(pUserData) ) );
}



void* GetDlgUserData( HWND hwndDlg )
{
	return reinterpret_cast<void*>( GetWindowLong( hwndDlg, DWL_USER ) );
}



void FillStackList( HWND hwndCallStack, const vector<SCallStackEntry> &entries )
{
	SendMessage( hwndCallStack, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)LVS_EX_FULLROWSELECT );
	RECT rc;
	GetClientRect( hwndCallStack, &rc );
	int nPart5 = (rc.right - rc.left) / 5;
	ListView_AddColumn( hwndCallStack, "Method", nPart5 * 2 );		// 1
	ListView_AddColumn( hwndCallStack, "File",	 nPart5 * 2 );		// 0
	ListView_AddColumn( hwndCallStack, "Line",	 nPart5		 );		// 2
	for ( int i = 0; i < entries.size(); ++i )
	{
		const SCallStackEntry &e = entries[i];
		int nNewLine = ListView_AddItem( hwndCallStack, e.szFunc.szStr, LPARAM(&e), 2000000 );
    string szFileName = NFile::GetFileName( nstl::string(e.szFile.szStr) );
		ListView_SetItemText( hwndCallStack, nNewLine, 1, const_cast<char*>( szFileName.c_str() ) );
		
		char szLineNumber[64];
		_itoa_s( e.nLine, szLineNumber, 64, 10 );
		ListView_SetItemText( hwndCallStack, nNewLine, 2, szLineNumber );
	}
}

} //namespace NBSU
