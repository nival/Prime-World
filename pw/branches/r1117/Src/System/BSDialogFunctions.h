#pragma once

struct SCallStackEntry;
namespace NBSU
{

void ListView_AddColumn( HWND hwnd, const string &strCaption, int nWidth );
int ListView_AddItem( HWND hwnd, const string &strText, LPARAM lParam, int nItem = 0 );
string GetFileName( const string &strFullPath );


bool SetWindowText( HWND hwndDlg, const int nElementID, const char *pszString );
void PutProcessInWindowTitle( HWND hWnd );

void* SetWindowUserData( HWND hwndDlg, const int nElementID, void *pUserData );
void* GetWindowUserData( HWND hwndDlg, const int nElementID );
void* SetDlgUserData( HWND hwndDlg, void *pUserData );
void* GetDlgUserData( HWND hwndDlg );


void FillStackList( HWND hwndCallStack, const vector<SCallStackEntry> &entries );


const char* ExceptionCodeToString( DWORD dwExceptionCode );
const char* RegistersToString( const EXCEPTION_POINTERS *pExceptionPointers );


EBSUReport ShowAssertionDlg( const char *pszFileName, int nLineNumber, const char *pszDescription, const vector<SCallStackEntry> &entries, bool dataAssert );
EBSUReport __cdecl ShowExceptionDlg( const vector<SCallStackEntry> &entries, const EXCEPTION_POINTERS *pExceptionPointers );

} //namespace NBSU
