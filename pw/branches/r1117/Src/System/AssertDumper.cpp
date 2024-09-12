#include "stdafx.h"

#include "AssertDumper.h"
#include "../MemoryLib/SymAccess.h"
#include "StackWalk.h"
#include "MiniDump.h"
#include "BSUtil.h"
#include "BSDialogFunctions.h"
#include "FileSystem/FilePath.h"
#include "Commands.h"

#include "TimeUtils.h"


namespace
{
bool ignoreWarnings = false;
bool ignoreAsserts = false;
bool showMessageBox = true;
}

namespace NLogg
{


void CAssertDumper::EnableAssertMessageBox(bool enable)
{
  showMessageBox = enable;
}


CAssertDumper::CAssertDumper( CLogger *pDefaultLogger )
  : CDumper( pDefaultLogger )
{
  //AddLevel( NLogg::LEVEL_WARNING );
  //AddLevel( NLogg::LEVEL_ERROR );
  AddLevel( NLogg::LEVEL_ASSERT );
  AddLevel( NLogg::LEVEL_CRITICAL );
}

static int dummy = 0;
static int CatchException( const struct tm &tim, EXCEPTION_POINTERS* pExceptionInfo )
{
  CreateMiniDump( tim, pExceptionInfo, MINI_DUMP, EXCEPTION_ASSERT );
  pExceptionInfo->ContextRecord->Eax = (DWORD)&dummy;
  return EXCEPTION_CONTINUE_EXECUTION;
}

static void GenerateException(const struct tm & tim)
{
  __try
  {
    __asm
    {
      mov eax, 0
        mov dword ptr [eax], 0
    }
  }
  __except( CatchException( tim, GetExceptionInformation() ) )
  {
  }
}

//collect call stack and remove entries from top of it to read file/line
static void CollectClearCallStack( vector<SCallStackEntry>* pEntries, const char *szFileName, const DWORD dwLine )
{
  CollectCallStack( pEntries );
  int nRemoveEntries = 0;
  bool bNeedRemove = false;
  const string szFileNameOnly = NFile::GetFileName( nstl::string(szFileName));
  for( vector<SCallStackEntry>::const_iterator it = pEntries->begin(); it != pEntries->end() && !bNeedRemove; ++it, ++nRemoveEntries )
    bNeedRemove = NStr::SearchFirst( it->szFile.szStr, szFileNameOnly, NStr::SASCIICharsComparer() ) != -1 && it->nLine > (int)dwLine - 1 && it->nLine <= (int)dwLine + 1;
  if ( bNeedRemove )
    pEntries->erase( pEntries->begin(), pEntries->begin() + nRemoveEntries - 1 );	
}

void CAssertDumper::OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  if ( NBSU::IsIgnore( entryInfo.filename, entryInfo.line ) )
    return;

  threading::MutexLock lock( mutex );

  vector<SCallStackEntry> entries;
  CollectClearCallStack( &entries, entryInfo.filename, entryInfo.line );

  const bool assert = ( entryInfo.level != NLogg::LEVEL_WARNING );

  //static SYSTEMTIME localTime;
  //::GetLocalTime( &localTime );

  struct tm t;
  GetOsUtcTime(&t);

  NBSU::WriteAssertLogFile( t , headerAndText, entries, !assert );

  bool ignore = assert ? ignoreAsserts : ignoreWarnings;
  if ( ignore )
  {
    NBSU::AddIgnore( entries.empty() ? "<UNKNOWN>" : entries[0].szFunc.szStr, entryInfo.filename, entryInfo.line );
    return;
  }

  if ( showMessageBox )
  {
    switch ( NBSU::ShowAssertionDlg( entryInfo.filename, entryInfo.line, textOnly, entries, !assert ) )
    {
    case NBSU::BSU_CONTINUE:
      break;
    case NBSU::BSU_IGNORE:
      NBSU::AddIgnore( entries.empty() ? "<UNKNOWN>" : entries[0].szFunc.szStr, entryInfo.filename, entryInfo.line );
      break;
    case NBSU::BSU_IGNORE_ALL:
      {
        NBSU::AddIgnore( entries.empty() ? "<UNKNOWN>" : entries[0].szFunc.szStr, entryInfo.filename, entryInfo.line );
        if ( assert )
          ignoreAsserts = true;
        else
          ignoreWarnings = true;
        break;
      }
    case NBSU::BSU_DEBUG:
      __debugbreak();
      break;
    case NBSU::BSU_ABORT:
      FatalExit( 0xDEAD );
      break;
    case NBSU::BSU_MAKE_MINI_MINIDUMP:
      struct tm tim;
      GetOsUtcTime( &tim );
      GenerateException( tim );
      break;
    }
  }
}

REGISTER_DEV_VAR( "ignoreAsserts", ignoreAsserts, STORAGE_NONE );
REGISTER_DEV_VAR( "ignoreWarnings", ignoreWarnings, STORAGE_NONE );

}
