#include "stdafx.h"

#include "../MemoryLib/SymAccess.h"
#include "StackWalk.h"
#include "BSUtil.h"
#include "BSDialogFunctions.h"
#include "BSResources.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NBSU
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ExceptionCodeToString( DWORD dwExceptionCode )
{
	switch ( dwExceptionCode )
	{
	case EXCEPTION_ACCESS_VIOLATION: 
		return "The thread tried to read from or write to a virtual address for which it does not have the appropriate access.";
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: 
		return "The thread tried to access an array element that is out of bounds and the underlying hardware supports bounds checking.";
	case EXCEPTION_BREAKPOINT: 
		return "A breakpoint was encountered.";
	case EXCEPTION_DATATYPE_MISALIGNMENT: 
		return "The thread tried to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries; 32-bit values on 4-byte boundaries, and so on.";
	case EXCEPTION_FLT_DENORMAL_OPERAND: 
		return "One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value.";
	case EXCEPTION_FLT_DIVIDE_BY_ZERO: 
		return "The thread tried to divide a floating-point value by a floating-point divisor of zero.";
	case EXCEPTION_FLT_INEXACT_RESULT: 
		return "The result of a floating-point operation cannot be represented exactly as a decimal fraction.";
	case EXCEPTION_FLT_INVALID_OPERATION: 
		return "This exception represents any floating-point exception not included in this list.";
	case EXCEPTION_FLT_OVERFLOW: 
		return "The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type.";
	case EXCEPTION_FLT_STACK_CHECK: 
		return "The stack overflowed or underflowed as the result of a floating-point operation.";
	case EXCEPTION_FLT_UNDERFLOW: 
		return "The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type.";
	case EXCEPTION_ILLEGAL_INSTRUCTION: 
		return "The thread tried to execute an invalid instruction.";
	case EXCEPTION_IN_PAGE_ERROR: 
		return "The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network.";
	case EXCEPTION_INT_DIVIDE_BY_ZERO: 
		return "The thread tried to divide an integer value by an integer divisor of zero.";
	case EXCEPTION_INT_OVERFLOW: 
		return "The result of an integer operation caused a carry out of the most significant bit of the result.";
	case EXCEPTION_INVALID_DISPOSITION: 
		return "An exception handler returned an invalid disposition to the exception dispatcher.";
	case EXCEPTION_NONCONTINUABLE_EXCEPTION: 
		return "The thread tried to continue execution after a noncontinuable exception occurred.";
	case EXCEPTION_PRIV_INSTRUCTION: 
		return "The thread tried to execute an instruction whose operation is not allowed in the current machine mode.";
	case EXCEPTION_SINGLE_STEP: 
		return "A trace trap or other single-instruction mechanism signaled that one instruction has been executed.";
	case EXCEPTION_STACK_OVERFLOW: 
		return "The thread used up its stack.";
	case 0xE06D7363:
		return "Microsoft C++ Exception";
	default:
		{
			static char buffer[64];
			sprintf_s( buffer, "Exception 0x%08X", dwExceptionCode );
			return buffer;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
const char *RegistersToString( const EXCEPTION_POINTERS *pExPtrs )
{
#ifdef _WIN64
	NI_ALWAYS_ASSERT( "x64 is not supported" );
#else
	// Check the parameter.
	NI_VERIFY( IsBadReadPtr( pExPtrs, sizeof ( EXCEPTION_POINTERS ) ) == FALSE, "Invalid parameter", return "Cannot extract registers" );
	static char buff[256];
	sprintf_s( buff, 
		"EAX=0x%08X\tEBX=0x%08X\tECX=0x%08X\tEDX=0x%08X\tESI=0x%08X\n"\
		"EDI=0x%08X\tEBP=0x%08X\tESP=0x%08X\tEIP=0x%08X\tFLG=0x%08X\n"\
		"CS=0x%04X\tDS=0x%04X\tSS=0x%04X\tES=0x%04X\tFS=0x%04X\tGS=0x%04X",
		pExPtrs->ContextRecord->Eax,
		pExPtrs->ContextRecord->Ebx,
		pExPtrs->ContextRecord->Ecx,
		pExPtrs->ContextRecord->Edx,
		pExPtrs->ContextRecord->Esi,
		pExPtrs->ContextRecord->Edi,
		pExPtrs->ContextRecord->Ebp,
		pExPtrs->ContextRecord->Esp,
		pExPtrs->ContextRecord->Eip,
		pExPtrs->ContextRecord->EFlags,
		pExPtrs->ContextRecord->SegCs,
		pExPtrs->ContextRecord->SegDs,
		pExPtrs->ContextRecord->SegSs,
		pExPtrs->ContextRecord->SegEs,
		pExPtrs->ContextRecord->SegFs,
		pExPtrs->ContextRecord->SegGs ) ;
#endif
	return buff;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static BOOL CALLBACK ReportExceptionDlgProc( HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SExceptionDlgInitParams
{
	const vector<SCallStackEntry> &entries;
	const EXCEPTION_POINTERS *pExceptionPointers;
	//
	SExceptionDlgInitParams( const vector<SCallStackEntry> &_entries, const EXCEPTION_POINTERS *_pExceptionPointers )
		: entries( _entries ), pExceptionPointers( _pExceptionPointers ) {}
private:
	DUMMY_ASSIGNMENT( SExceptionDlgInitParams );
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EBSUReport __cdecl ShowExceptionDlg( const vector<SCallStackEntry> &entries, const EXCEPTION_POINTERS *pExceptionPointers ) 
{
	// remember old cursor before dialog box call
	HCURSOR hCursor = GetCursor();
	// fill start params and execute dialog
	SExceptionDlgInitParams params( entries, pExceptionPointers );
	int nRetVal = DialogBoxParam( NBSU::GetBSUInstance(),	"IDD_EXCEPTION_REPORT",	0,
		reinterpret_cast<DLGPROC>( ReportExceptionDlgProc ), reinterpret_cast<LPARAM>( &params ) );
	// restore old cursor after message box usage
	SetCursor( hCursor );

	switch ( nRetVal )
	{
	case IDC_EXCEPTION_DEBUG:
		return BSU_DEBUG;
	case IDC_EXCEPTION_ABORT:
		return BSU_ABORT;
	case IDC_EXCEPTION_FULL_MINIDUMP:
		return BSU_MAKE_FULL_MINIDUMP;
	default:
		return BSU_DEBUG;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static BOOL CALLBACK ReportExceptionDlgProc( HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam ) 
{ 
	switch (message) 
	{ 
	case WM_INITDIALOG:
		{
			RECT rcDlg;
			GetWindowRect( hwndDlg, &rcDlg );
			MoveWindow( hwndDlg, (GetSystemMetrics(SM_CXFULLSCREEN) - rcDlg.right + rcDlg.left) / 2,
				(GetSystemMetrics(SM_CYFULLSCREEN) - rcDlg.bottom + rcDlg.top) / 2,
				rcDlg.right - rcDlg.left, rcDlg.bottom - rcDlg.top, true );


			SExceptionDlgInitParams *pParams = reinterpret_cast<SExceptionDlgInitParams*>( lParam );
			SetDlgUserData( hwndDlg, pParams );
			FillStackList( GetDlgItem( hwndDlg, IDC_EXCEPTION_CALLSTACK ), pParams->entries );

      PutProcessInWindowTitle( hwndDlg );

			static char buff[1024];
			if ( !pParams->entries.empty() )
				sprintf_s( buff, "First-chance exception in %s: 0x%08X", pParams->entries[0].szFile.szStr, pParams->pExceptionPointers->ExceptionRecord->ExceptionCode );
			else
				sprintf_s( buff, "Unhandled Exception (0x%X) at the 0x%08X", pParams->pExceptionPointers->ExceptionRecord->ExceptionCode, pParams->pExceptionPointers->ExceptionRecord->ExceptionAddress );
			SetDlgItemText( hwndDlg, IDC_STATIC_COND, buff );

			SetDlgItemText( hwndDlg, IDC_STATIC_DESCR, ExceptionCodeToString( pParams->pExceptionPointers->ExceptionRecord->ExceptionCode ) );
		}
		break;
	case WM_COMMAND: 
		switch ( LOWORD(wParam) ) 
		{ 
			case IDC_EXCEPTION_DEBUG:
			case IDC_EXCEPTION_ABORT:
				EndDialog( hwndDlg, LOWORD(wParam) ); 
				return TRUE;
			case IDC_EXCEPTION_FULL_MINIDUMP:
				EndDialog( hwndDlg, LOWORD(wParam) );
				return TRUE;
			case IDC_EXCEPTION_DETAILS:
				{
					SExceptionDlgInitParams *pParams = reinterpret_cast<SExceptionDlgInitParams*>( GetDlgUserData( hwndDlg ) );
					MessageBox( hwndDlg, RegistersToString( pParams->pExceptionPointers ), "Registers", MB_OK | MB_ICONINFORMATION );
				}
				break;
		} 
		break;
	} 
	return FALSE; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
