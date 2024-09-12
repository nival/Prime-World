#include "StdAfx.h"
#include "SymAccess.h"

#include <Vendor/DTW/inc/dbghelp.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class TYPE>
inline void ZeroSA( TYPE &val )
{
	memset( &val, 0, sizeof(val) );
}
inline void Clear( CSymString *p ) 
{ 
  if ( p ) *p = "?"; 
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static void Assign( ADDRESS64 *pRes, DWORD /*dwSeg*/, DWORD64 dwOffset )
{
  pRes->Mode = AddrModeFlat;
  pRes->Offset = dwOffset;
  pRes->Segment = 0;//dwSeg;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSymEngine::CSymEngine()
{
  InitializeCriticalSection( &block );
  Init();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSymEngine::~CSymEngine()
{
  Term();
  DeleteCriticalSection( &block );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CSymEngine::Lock()
{
  EnterCriticalSection( &block );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CSymEngine::Unlock()
{
  LeaveCriticalSection( &block );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CSymEngine::Init( )
{
  DWORD options = SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES | SYMOPT_UNDNAME;
  if ( !hProcess )
  {
    hProcess = GetCurrentProcess();
    if ( !SymInitialize( hProcess, 0, TRUE ) )
    {
      hProcess = 0;
      return;
    }
  }

  if ( options != SymGetOptions() )
    SymSetOptions( options );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CSymEngine::Term()
{
  if ( hProcess )
    SymCleanup( hProcess );
  hProcess = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CSymEngine::GetSymbol( DWORD64 dwAddress, CSymString *pszModule, CSymString *pszFile, int *pnLine, CSymString *pszFunc )
{
	Clear( pszModule );
	Clear( pszFile );
	Clear( pszFunc );
	if ( pnLine )
		*pnLine = 0;
	if ( !hProcess )
		return false;
	const int N_MAX_NAME_LENG = 1000;
	const int N_BUF_SIZE = sizeof(SYMBOL_INFO) + N_MAX_NAME_LENG;
	char szBuf[ N_BUF_SIZE ];
	memset( szBuf, 0, N_BUF_SIZE );
	if ( pszModule )
	{
    IMAGEHLP_MODULE64 moduleInfo;
    ZeroSA( moduleInfo );
    moduleInfo.SizeOfStruct = sizeof(moduleInfo);
    if ( SymGetModuleInfo64( hProcess, dwAddress, &moduleInfo ) )
      *pszModule = moduleInfo.ImageName;
	}
	
	if ( pszFunc )
	{
		DWORD64	dwDisplacement;

		ULONG64 buffer[(sizeof(SYMBOL_INFO) +
			MAX_SYM_NAME*sizeof(TCHAR) +
			sizeof(ULONG64) - 1) /
			sizeof(ULONG64)];
		PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;

		pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		pSymbol->MaxNameLen = MAX_SYM_NAME;
		
		if ( SymFromAddr( hProcess, dwAddress, &dwDisplacement, pSymbol ) )
			*pszFunc = pSymbol->Name;
	  else
	    sprintf_s( pszFunc->szStr, pszFunc->N_STRING_CHARS, "??? (0x%X)", dwAddress ); 
	}

	if ( pnLine || pszFile )
	{
		IMAGEHLP_LINE64 lineInfo;
		ZeroSA( lineInfo );
		lineInfo.SizeOfStruct = sizeof(lineInfo);
		DWORD dwDisp;
		if ( SymGetLineFromAddr64( hProcess, dwAddress, &dwDisp, &lineInfo ) )
		{
			if ( pnLine )
				*pnLine = lineInfo.LineNumber;
			if ( pszFile )
				*pszFile = lineInfo.FileName;
		}
    else
      return false;
	}
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int CSymEngine::QuickCollectCallStack( DWORD *addresses, int maxEntries, int skipEntries )
{
  return RtlCaptureStackBackTrace( skipEntries, maxEntries, (PVOID*)addresses, 0 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CSymEngine::CollectCallStack( SCallStackEntry *callStack, int maxEntries, int skipEntries, const CONTEXT* context )
{
  STACKFRAME64 stkFrame;

  ZeroSA( stkFrame );
  Assign( &stkFrame.AddrPC, context->SegCs, context->Eip );
  Assign( &stkFrame.AddrFrame, context->SegSs, context->Ebp );
  Assign( &stkFrame.AddrStack, context->SegSs, context->Eip );

  int nEntry = 0;
  for ( nEntry = -skipEntries; nEntry < maxEntries; ++nEntry )
  {
    BOOL bRes = StackWalk64( IMAGE_FILE_MACHINE_I386, hProcess, GetCurrentThread(), &stkFrame, (PVOID)context, 0, SymFunctionTableAccess64, SymGetModuleBase64, 0 );
    if ( !bRes || stkFrame.AddrPC.Offset == 0 )
      break;
    SCallStackEntry &res = callStack[nEntry];
    res.dwAddress = (DWORD)stkFrame.AddrPC.Offset;

    GetSymbol( res.dwAddress, 0, &res.szFile, &res.nLine, &res.szFunc );
  }

  return nEntry;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma warning( disable : 4740 ) //warning C4740: flow in or out of inline asm code suppresses global optimization
int CSymEngine::CollectCallStack( SCallStackEntry *callStack, int maxEntries, int skipEntries )
{
  DWORD dwAddr, dwEbp, dwEsp;
  __asm
  {
    call nxt
nxt:
    pop [dwAddr]
    mov dwEbp, ebp
    mov dwEsp, esp
  }

  CONTEXT ctx;
  ctx.Eip = dwAddr;
  ctx.Ebp = dwEbp;
  ctx.Esp = dwEsp;

  return CollectCallStack( callStack, maxEntries, skipEntries, &ctx );
}
#pragma warning( default : 4740 ) 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static CSymEngine* globalSymEngine = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AssignSymEngine( CSymEngine* symEngine )
{
  globalSymEngine = symEngine;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSymEngine& LockSymEngine()
{
  globalSymEngine->Lock();
  return *globalSymEngine;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void ReleaseSymEngine()
{
  globalSymEngine->Unlock();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
