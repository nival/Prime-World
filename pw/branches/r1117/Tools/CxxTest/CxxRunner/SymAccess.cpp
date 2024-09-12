#include <windows.h>
#include <stdio.h>
#include "SymAccess.h"

#include <DbgHelp.h>
#pragma comment( lib, "DbgHelp.lib" )
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int MAX_FUNCTION_NAME_LEN = 256;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline static void Zero( T &value )
{
	memset( &value, 0, sizeof( value ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NHelpers
{
////////////////////////////////////////////////////////////////////////////////////////////////////
class CSymbolEngine
{
	void operator=( const CSymbolEngine & ) {}
	HANDLE hProcess;
public:
	CSymbolEngine();
	~CSymbolEngine();
	bool GetSymbol( DWORD dwAddress, CSimpleString *pszModule, CSimpleString *pszFile, int *pnLine, CSimpleString *pszFunc );
	HANDLE GetProcess() const { return hProcess; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSymbolEngine::CSymbolEngine()
{
	hProcess = GetCurrentProcess();
	SymSetOptions ( SymGetOptions() | SYMOPT_LOAD_LINES | SYMOPT_DEFERRED_LOADS );
	if ( !SymInitialize( hProcess, 0, TRUE ) )
		hProcess = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSymbolEngine::~CSymbolEngine()
{
	if ( hProcess )
		SymCleanup( hProcess );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CSymbolEngine::GetSymbol( DWORD dwAddress, CSimpleString *pszModule, CSimpleString *pszFile, int *pnLine, CSimpleString *pszFunc )
{
	if ( !hProcess )
		return false;
	
	const int N_MAX_NAME_LENG = 1000;
	const int N_BUF_SIZE = sizeof( SYMBOL_INFO ) + N_MAX_NAME_LENG;
	char szBuf[ N_BUF_SIZE ];
	memset( szBuf, 0, N_BUF_SIZE );

	if ( pszModule )
	{
		pszModule->clear();
		IMAGEHLP_MODULE64 moduleInfo;
		Zero( moduleInfo );
		moduleInfo.SizeOfStruct = sizeof( moduleInfo );
		if ( SymGetModuleInfo64( hProcess, dwAddress, &moduleInfo ) )
			*pszModule = moduleInfo.ImageName;
	}

	if ( pszFunc )
	{
		pszFunc->clear();

		char buffer[sizeof( SYMBOL_INFO ) + MAX_FUNCTION_NAME_LEN];
		Zero( buffer );

		SYMBOL_INFO *pInfo = (SYMBOL_INFO*)szBuf;
		pInfo->SizeOfStruct = sizeof( SYMBOL_INFO ) + MAX_FUNCTION_NAME_LEN;
		pInfo->MaxNameLen = MAX_FUNCTION_NAME_LEN;
		if ( SymFromAddr( hProcess, dwAddress, 0, pInfo ) )
			*pszFunc = pInfo->Name;
	}

	if ( pnLine || pszFile )
	{
		IMAGEHLP_LINE64 lineInfo;
		Zero( lineInfo );
		lineInfo.SizeOfStruct = sizeof( lineInfo );
		DWORD dwDisp;
		if ( SymGetLineFromAddr64( hProcess, dwAddress, &dwDisp, &lineInfo ) )
		{
			if ( pnLine )
				*pnLine = lineInfo.LineNumber;
			if ( pszFile )
				*pszFile = lineInfo.FileName;
		}
		else
		{
			if ( pnLine )
				*pnLine = -1;
			if ( pszFile )
				pszFile->clear();
		}
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void AssignAddress64( ADDRESS64 *pRes, DWORD /*dwSeg*/, DWORD64 dwOffset )
{
	pRes->Mode = AddrModeFlat;
	pRes->Offset = dwOffset;
	pRes->Segment = 0;//dwSeg;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CollectCallStack( SCallStackEntry *pRes, int nMaxEntries, const EXCEPTION_POINTERS *pExPtrs )
{
	CSymbolEngine se;
	
	STACKFRAME64 stkFrame;
	CONTEXT ctx;

	Zero( stkFrame );
	AssignAddress64( &stkFrame.AddrPC, pExPtrs->ContextRecord->SegCs, pExPtrs->ContextRecord->Eip );
	AssignAddress64( &stkFrame.AddrFrame, pExPtrs->ContextRecord->SegSs, pExPtrs->ContextRecord->Ebp );
	AssignAddress64( &stkFrame.AddrStack, pExPtrs->ContextRecord->SegSs, pExPtrs->ContextRecord->Eip );

	bool bValidEntry = true;
	int nEntry = 0;
	for ( int i = 0; i < nMaxEntries; ++i, ++nEntry )
	{
		if ( bValidEntry )
		{
			BOOL bResult = StackWalk64( IMAGE_FILE_MACHINE_I386, se.GetProcess(), GetCurrentThread(), &stkFrame, &ctx, 0, 
				SymFunctionTableAccess64, SymGetModuleBase64, 0 );
			bValidEntry = ( bResult == TRUE ) && ( stkFrame.AddrPC.Offset != 0 );
		}
		
		SCallStackEntry &res = pRes[i];
		if ( bValidEntry )
		{
			res.dwAddress = (DWORD)stkFrame.AddrPC.Offset;
			se.GetSymbol( res.dwAddress, 0, &res.szFile, &res.nLine, &res.szFunc );
		}
		else
			res.clear();
	}
	return nEntry;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}