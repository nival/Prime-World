#include "StdAfx.h"

#include "../MemoryLib/SymAccess.h"
#include "StackWalk.h"
#include "BSUtil.h"
#include "BSResources.h"
#include "BSDialogFunctions.h"
#include "FileSystem/FilePath.h"
#include <CommCtrl.h>


namespace NBSU
{

static int	nSplitter = -1;
static bool isMore = false;


//static bool needSaveLog = true;
static BOOL CALLBACK ReportAssertionDlgProc( HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam );
static bool ReportAssertionDlgProcCommand( HWND hwndDlg, WORD wCtrlID );




struct SAssertionDlgParams
{
  const char *pszFileName;
  int nLineNumber;
  string szDescription;
  const vector<SCallStackEntry> &entries;
  //
  SAssertionDlgParams( const char *_pszFileName, int _nLineNumber, const char *pszDescription, const vector<SCallStackEntry> &_entries ) :
  pszFileName( _pszFileName ), nLineNumber( _nLineNumber ), szDescription( pszDescription ), entries( _entries )
  {
  }
private:
  DUMMY_ASSIGNMENT( SAssertionDlgParams );
};




EBSUReport ShowAssertionDlg( const char *pszFileName, int nLineNumber, const char *pszDescription, const vector<SCallStackEntry> &entries, bool dataAssert )
{
	// remember old cursor before dialog box call
	HCURSOR hCursor = GetCursor();
	// fill start params and execute dialog
	SAssertionDlgParams params( pszFileName, nLineNumber, pszDescription, entries );
	const int nResult = DialogBoxParam( NBSU::GetBSUInstance(), dataAssert ? "IDD_DATA_ASSERTION_REPORT" : "IDD_ASSERTION_REPORT", 0,
		reinterpret_cast<DLGPROC>( ReportAssertionDlgProc ), reinterpret_cast<LPARAM>( &params ) );
	// restore old cursor after message box usage
	SetCursor( hCursor );

	switch ( nResult )
	{
	case IDC_ASSERTION_DEBUG:
		return BSU_DEBUG;
	case IDC_ASSERTION_ABORT:
		return BSU_ABORT;
	case IDC_ASSERTION_CONTINUE:
		return BSU_CONTINUE;
	case IDC_ASSERTION_IGNORE:
		return BSU_IGNORE;
	case IDC_ASSERTION_IGNORE_ALL:
		return BSU_IGNORE_ALL;
	case IDC_ASSERTION_NORMAL_MINIDUMP:
		return BSU_MAKE_MINI_MINIDUMP;
	default:
		return BSU_DEBUG;
	}
}



inline static SAssertionDlgParams *GetParams( LPARAM lParam )
{
	return reinterpret_cast<SAssertionDlgParams*>( lParam );
}




static void FillIgnoreList( HWND hwndDlg )
{
	HWND hwndList = GetDlgItem( hwndDlg, IDC_ASSERTION_IGNORES_LIST );
	if ( hwndList == NULL )
		return;

	SendMessage( hwndList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)LVS_EX_FULLROWSELECT );
	RECT rc;
	GetClientRect( hwndList, &rc );
	int nPart5 = (rc.right - rc.left) / 5;
	ListView_AddColumn( hwndList, "Method", nPart5 * 2 );
	ListView_AddColumn( hwndList, "File", nPart5 * 2 );
	ListView_AddColumn( hwndList, "Line", nPart5 );
	for( TIgnoresList::const_iterator it = GetIgnoresList().begin(); it != GetIgnoresList().end(); ++it )
	{
		const int nNewLine = ListView_AddItem( hwndList, NFile::GetFileName( it->szFileName ), LPARAM( &(*it) ) );
		ListView_SetItemText( hwndList, nNewLine, 1, const_cast<char*>( it->szFunctionName.c_str() ) );

		char szLineNumber[16];
		_itoa_s( it->nLineNumber, szLineNumber, 16, 10 );
		ListView_SetItemText( hwndList, nNewLine, 2, szLineNumber );
	}
}




static BOOL CALLBACK ReportAssertionDlgProc( HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam ) 
{ 
	switch (message)
	{ 
	case WM_INITDIALOG:
		{			
			// Calculate splitter
			RECT rcDlg, rc;
			GetWindowRect( hwndDlg, &rcDlg );
			GetWindowRect( GetDlgItem( hwndDlg, IDC_STATIC_SPLITTER ), &rc );
			nSplitter = rcDlg.bottom - rcDlg.top - rc.top;
			if ( !isMore )
				rcDlg.bottom -= nSplitter;
			MoveWindow( hwndDlg, (GetSystemMetrics(SM_CXFULLSCREEN) - rcDlg.right + rcDlg.left) / 2,
				(GetSystemMetrics(SM_CYFULLSCREEN) - rcDlg.bottom + rcDlg.top) / 2,
				rcDlg.right - rcDlg.left, rcDlg.bottom - rcDlg.top, true );

			SAssertionDlgParams *pParams = GetParams(lParam);
			SetDlgUserData( hwndDlg, pParams );

      PutProcessInWindowTitle( hwndDlg );

			SetWindowText( hwndDlg, IDC_ASSERTION_DESCRIPTION, pParams->szDescription.c_str() );

			HWND hwndCallStack = GetDlgItem( hwndDlg, IDC_ASSERTION_CALLSTACK );
			FillStackList( hwndCallStack, pParams->entries );
			FillIgnoreList( hwndDlg );
		}
		break;

	case WM_NOTIFY:
		{
			int idCtrl = (int) wParam;
			if ( IDC_ASSERTION_IGNORES_LIST == idCtrl )
			{
				LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)lParam;
				HWND hwndList = GetDlgItem( hwndDlg, IDC_ASSERTION_IGNORES_LIST );
				switch( lpnmitem->hdr.code )
				{
				case NM_DBLCLK:
					{
						LVITEM Item;
						memset( &Item, 0, sizeof(Item) );
						Item.mask = LVIF_PARAM | LVIF_TEXT;
						Item.iItem = lpnmitem->iItem;

						ListView_GetItem( hwndList, &Item );
						SIgnoresEntry* pIgnoresEntry = reinterpret_cast<SIgnoresEntry*>( Item.lParam );
						RemoveIgnore( pIgnoresEntry->szFileName.c_str(), pIgnoresEntry->nLineNumber );
						
						ListView_DeleteItem( hwndList, lpnmitem->iItem );
					}
					break;
				}
			}
		}
		break;

	case WM_COMMAND:
		return ReportAssertionDlgProcCommand( hwndDlg, LOWORD(wParam) );
	} 
	return false;
}



bool ReportAssertionDlgProcCommand( HWND hwndDlg, WORD wCtrlID )
{
	switch(wCtrlID)
	{ 
	case IDC_BUTTON_MORE:
		{
			isMore = !isMore;
			RECT rc;
			GetWindowRect( hwndDlg, &rc );
			rc.bottom += isMore ? nSplitter : -nSplitter;
			MoveWindow( hwndDlg, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, true );
			SetWindowText( hwndDlg, IDC_BUTTON_MORE, isMore ? "&More <<" : "&More >>" );
		}
		break;
	case IDC_ASSERTION_DEBUG:
	case IDC_ASSERTION_ABORT:
	case IDC_ASSERTION_CONTINUE:
	case IDC_ASSERTION_NORMAL_MINIDUMP:
	case IDC_ASSERTION_IGNORE:
	case IDC_ASSERTION_IGNORE_ALL:
		EndDialog( hwndDlg, wCtrlID );
		return true;
	}
	return false;
}

} //namespace NBSU
