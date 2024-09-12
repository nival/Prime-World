#include "stdafx.h"

#include "newdelete.h"
#include "SymAccess.h"
#ifndef NEW_NOT_THROWS
#include "NewHandlerDetails.h"
#endif // NEW_NOT_THROWS

#include "System/nvector.h"
#include "System/nhash_map.h"
#include "Vendor/DTW/inc/dbghelp.h"

// malloc implementation: 1 - CRT, 2 - nedmalloc
#ifndef NI_MALLOC_IMPL
#define NI_MALLOC_IMPL 2
#endif

#if NI_MALLOC_IMPL == 1
#include <crtdbg.h>
#include <errno.h>
#elif NI_MALLOC_IMPL == 2
#include "nedmalloc.h"
#endif

// there is some predefined values for MAX_STACK_SIZE
// <0 : just calculate (new - delete) amount
// 0  : do not collect call stack but show unfree memory
// >0 : specify depth of collected callstack
#ifndef MAX_STACK_SIZE
  #if defined( _TESTRUN )
    #define MAX_STACK_SIZE 10
  #elif defined( _DEBUG )
    //In Windows XP and Windows Server 2003, the sum of the FramesToSkip and FramesToCapture parameters must be less than 63.
    #define MAX_STACK_SIZE -1
  #else
    #define MAX_STACK_SIZE -1
  #endif
#endif

#define BREAK_MALLOC_INDEX0 -1
#define BREAK_MALLOC_INDEX1 -1
#define BREAK_MALLOC_INDEX2 -1
#define BREAK_MALLOC_INDEX3 -1

// Uncomment this define to enable logging of new/delete for PerformanceDebugVar. see "monitor_pdv <performance_debug_var_name>" command
//#define PERF_LOG_NEWDELETE

static const int BIN_DUMP_LINES = 3;
static const int BIN_DUMP_BYTES = 16;
#ifdef NI_DUMP_LEAKS_TO_FILE
  static const bool DUMP_LEAKS_TO_FILE = true;
#else
  static const bool DUMP_LEAKS_TO_FILE = false;
#endif

static const int MAX_LEAKS_TO_DUMP = 50;

static unsigned long g_mallocIndex = 0;
static long g_totalMaloc = 0;
static long g_unfreeMaloc = 0;
static long g_mallocSize = 0;
static bool g_isInternal = false;
static bool g_dumpOnlyAmount = false;
static bool g_outputPhase = false;

static CRITICAL_SECTION g_block;
static bool g_blockInitialized = false;

static unsigned long g_mallocThreadMask = 0; 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct AllocInfo
{
  int mallocIndex;
  int size;
  void *pData;
#if MAX_STACK_SIZE > 0
  DWORD stack[MAX_STACK_SIZE];
#endif
};
static nstl::hash_map<void*, AllocInfo> *g_allocs = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef PERF_LOG_NEWDELETE
#define MAX_PERFORMANCE_STACK_SIZE 16

static LogAllocCallback g_perfLogAllocCallback = NULL;
static LogFreeCallback  g_perfLogFreeCallback  = NULL;
static ThreadLocal<bool> g_performaceLogOn(false);

DWORD g_stackPerf[MAX_PERFORMANCE_STACK_SIZE];
#endif // PERF_LOG_NEWDELETE
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *StrFmt( const char *pszFormat, ... )
{
  static char charBuff[1024] = { '\0' };
  va_list va;
  va_start( va, pszFormat );
  _vsnprintf_s( charBuff, 1024 - 1, pszFormat, va );
  va_end( va );
  return charBuff;
}


const static size_t MaxCommonMemoryCallbacks = 4;

static ni_detail::TCommonMemoryCallback s_allocCallbacks[MaxCommonMemoryCallbacks];
static ni_detail::TCommonMemoryCallback s_freeCallbacks[MaxCommonMemoryCallbacks];


inline static void InitializeAndEnterCritical()
{
  if ( !g_blockInitialized )
  {
    g_blockInitialized = true;
    InitializeCriticalSection( &g_block );
  }

  EnterCriticalSection( &g_block );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RegisterMalloc( size_t size, void *p )
{
  if ( g_outputPhase )
  {
    OutputDebugString( "Malloc during output phase\n" );
    if( IsDebuggerPresent() )
      __debugbreak();
  }

  InitializeAndEnterCritical();

  if ( g_isInternal )
  {
    LeaveCriticalSection( &g_block );
    return;
  }

  g_isInternal = true;
  InterlockedIncrement( &g_totalMaloc );

#if MAX_STACK_SIZE >= 0
  if ( !g_allocs )
  {
    LeaveCriticalSection( &g_block );
    g_allocs = ::new nstl::hash_map<void*, AllocInfo>;
    EnterCriticalSection( &g_block );
  }

  nstl::hash_map<void*, AllocInfo>::const_iterator pos = g_allocs->find( p );
  if ( pos == g_allocs->end() )
  {
    InterlockedIncrement( &g_unfreeMaloc );
    InterlockedExchangeAdd( &g_mallocSize, (long)size );
  }

  AllocInfo &allocInfo = (*g_allocs)[p];
  allocInfo.size = size;
  allocInfo.mallocIndex = ++g_mallocIndex;
  allocInfo.pData = p;

#if MAX_STACK_SIZE > 0
  LockSymEngine().QuickCollectCallStack( allocInfo.stack, MAX_STACK_SIZE, 1 );
  ReleaseSymEngine();
#endif // #if MAX_STACK_SIZE > 0
#ifdef PERF_LOG_NEWDELETE
  if ( g_performaceLogOn.GetValue() )
  {
    LockSymEngine().QuickCollectCallStack( g_stackPerf, MAX_PERFORMANCE_STACK_SIZE, 1 );
    ReleaseSymEngine();

    g_perfLogAllocCallback( allocInfo.mallocIndex, size, p, g_stackPerf, MAX_PERFORMANCE_STACK_SIZE );
  }
#endif // #ifdef PERF_LOG_NEWDELETE
#endif // #if MAX_STACK_SIZE >= 0

  g_isInternal = false;

  for ( int i = 0; i < MaxCommonMemoryCallbacks; ++i )
    if ( s_allocCallbacks[i] )
      (*s_allocCallbacks[i])( g_mallocIndex, size );
    else
      break;

  LeaveCriticalSection( &g_block );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RegisterFree( void *p )
{
  if ( g_outputPhase )
  {
    OutputDebugString( "Free during output phase" );
    if( IsDebuggerPresent() )
        __debugbreak();
  }

  if ( p == 0 )
    return;

  EnterCriticalSection( &g_block );

  if ( g_isInternal )
  {
    LeaveCriticalSection( &g_block );
    return;
  }

  g_isInternal = true;
  InterlockedDecrement( &g_unfreeMaloc );

  size_t allocSize = 0;

#if MAX_STACK_SIZE >= 0
  nstl::hash_map<void*, AllocInfo>::iterator allocInfo = g_allocs->find( p );

#ifdef PERF_LOG_NEWDELETE
  if ( g_performaceLogOn.GetValue() )
    g_perfLogFreeCallback( (*allocInfo).second.mallocIndex );
#endif // #ifdef PERF_LOG_NEWDELETE

  if ( allocInfo != g_allocs->end() )
  {
    allocSize = (*allocInfo).second.size;
    InterlockedExchangeAdd( &g_mallocSize, -(long)(*allocInfo).second.size );
    g_allocs->erase( allocInfo );
  }
  else
  {
    OutputDebugString( "FREEING UNREGISTERED ALLOCATION!\n" );
    if( IsDebuggerPresent() )
      __debugbreak();
  }

  if ( g_allocs->empty() )
  {
    LeaveCriticalSection( &g_block );
    delete g_allocs;
    g_allocs = 0;

    if ( g_unfreeMaloc != 0 )
    {
      OutputDebugString( StrFmt( "g_allocs is null but g_unfreeMaloc is %d\n", g_unfreeMaloc ) );
      if( IsDebuggerPresent() )
        __debugbreak();
    }

    EnterCriticalSection( &g_block );
  }
#endif // #if MAX_STACK_SIZE >= 0
  g_isInternal = false;

  for ( int i = 0; i < MaxCommonMemoryCallbacks; ++i )
    if ( s_freeCallbacks[i] )
      (*s_freeCallbacks[i])( g_mallocIndex, allocSize );
    else
      break;

  LeaveCriticalSection( &g_block );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetMemoryLeaksDumpLevel( bool dumpOnlyAmount )
{
  g_dumpOnlyAmount = dumpOnlyAmount;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetPerformanceAllocsEnabled( bool enabled, LogAllocCallback allocCallback, LogFreeCallback freeCallback )
{
#ifdef PERF_LOG_NEWDELETE
  InitializeAndEnterCritical();

  g_performaceLogOn.SetValue(enabled);
  g_perfLogAllocCallback = allocCallback;
  g_perfLogFreeCallback  = freeCallback;

  LeaveCriticalSection( &g_block );
#else
  (void)(enabled);
  (void)(allocCallback);
  (void)(freeCallback);
#endif
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetMallocThreadMask( unsigned long threadId )
{
  g_mallocThreadMask = threadId;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
long GetMallocsUnfree()
{
  return g_unfreeMaloc;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
long GetMallocsTotal()
{
  return g_totalMaloc;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
long GetMallocsSize()
{
  return g_mallocSize;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef CHECK_MEMORY_LEAKS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if MAX_STACK_SIZE >= 0
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static HANDLE logFile = INVALID_HANDLE_VALUE;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OpenLogFile()
{
  static SYSTEMTIME time;
  ::GetLocalTime( &time );

  static wchar_t moduleName[_MAX_PATH];
  ::GetModuleFileNameW(NULL, moduleName, sizeof(moduleName) - 1);
  wchar_t* p = &moduleName[0];
  while(*p) ++p;
  while(*p != L'\\' && p != moduleName) --p;
  if (p != moduleName) ++p;

  static wchar_t logFileName[256];
  logFileName[sizeof(logFileName) - 1] = 0;
  swprintf_s( logFileName, sizeof(logFileName) - 1, L"MemoryLeaks-%04d.%02d.%02d-%02d.%02d.%02d-%s.log"
      , time.wYear, time.wMonth, time.wDay
      , time.wHour, time.wMinute, time.wSecond, p);

  logFile = CreateFileW( logFileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void CloseLogFile()
{
  if ( logFile != INVALID_HANDLE_VALUE )
  {
    CloseHandle( logFile );
    logFile = INVALID_HANDLE_VALUE;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void DumpString( const char* message )
{
  if ( logFile == INVALID_HANDLE_VALUE )
    OutputDebugString( message );
  else
  {
    int bytesToWrite = strlen( message );
    DWORD bytesWritten = 0;
    WriteFile( logFile, message, bytesToWrite, &bytesWritten, 0 );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool CompareAllocInfo( const AllocInfo &a1, const AllocInfo &a2 )
{
  return a1.mallocIndex < a2.mallocIndex;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char hex[17] = "0123456789ABCDEF";
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OutputDebugData( char *pData, int size )
{
    int index = 0;
    if ( IsBadReadPtr( pData, size ) )
    {
        DumpString( "CANNOT READ DATA\n" );
        return;
    }
    for( int line = 0; line < BIN_DUMP_LINES && index < size; ++line )
    {
        char lineBuffer[BIN_DUMP_BYTES * 4 + 2];
        memset( lineBuffer, ' ', BIN_DUMP_BYTES * 4 + 2 );
        lineBuffer[BIN_DUMP_BYTES * 4 + 1] = 0;
        for( int pos = 0; pos < BIN_DUMP_BYTES && index < size; ++pos, ++index )
        {
            char value = pData[index];
            if ( value > ' ' )
                lineBuffer[pos] = (char)value;
            else
                lineBuffer[pos] = '.' ;
            lineBuffer[BIN_DUMP_BYTES + 2 + pos * 3] = hex[(pData[index] >> 4) & 0x0F];
            lineBuffer[BIN_DUMP_BYTES + 2 + pos * 3 + 1] = hex[pData[index] & 0x0F];
        }
        DumpString( lineBuffer );
        DumpString( "\n" );
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void DumpMemoryLeaks()
{
  printf( "Memory leaks info START\n" );
  if ( g_unfreeMaloc == 0 )
  {
    printf( "No memory leaks detected. Looks like everything is fine ;-).\n" );
    OutputDebugString( "No memory leaks detected. Looks like everything is fine ;-).\n" );
    return;
  }

#if MAX_STACK_SIZE >= 0
  g_isInternal = true;

  if ( !g_dumpOnlyAmount )
  {
    if ( DUMP_LEAKS_TO_FILE )
      OpenLogFile();
    nstl::vector<AllocInfo> sortedAllocs;
    sortedAllocs.resize( g_allocs->size() );
    int index = 0;
    for( nstl::hash_map<void*, AllocInfo>::const_iterator it = g_allocs->begin(); it != g_allocs->end(); ++it, ++index )
        sortedAllocs[index] = it->second;

    nstl::sort( sortedAllocs.begin(), sortedAllocs.end(), CompareAllocInfo );

    g_outputPhase = true;
    int bytesLeaked = 0;
    int leaksCount = sortedAllocs.size();
    int leaks2Show;
    if (leaksCount <= MAX_LEAKS_TO_DUMP)
    {   
      leaks2Show = leaksCount;
    }
    else
    {
      leaks2Show = MAX_LEAKS_TO_DUMP;
      char const *cp = StrFmt( "Found %d. Showing only first %d.\n", leaksCount, leaks2Show );
      printf("%s", cp);
      DumpString(cp);
    }
    int i;
#if MAX_STACK_SIZE > 0
    CSymEngine& en = LockSymEngine();
#endif // #if MAX_STACK_SIZE > 0
    for( i = 0; i < leaks2Show; ++i )
    {
      AllocInfo *it = &sortedAllocs[i];

      bytesLeaked += it->size;
      char const *cp = StrFmt( "[%d]: leaked %d bytes at 0x%08X:\n", it->mallocIndex, it->size, it->pData );
      printf("%s", cp);
      DumpString(cp);
      OutputDebugData( (char*)(it->pData), it->size );
#if MAX_STACK_SIZE > 0
      for ( int stackPos = 0; stackPos < MAX_STACK_SIZE && it->stack[stackPos] != 0; ++stackPos )
      {
        int sourceLine;
        CSymString fileName;

        if ( en.GetSymbol( it->stack[stackPos], 0, &fileName, &sourceLine, 0 ) )
        {
          printf( StrFmt( "%s(%d):\n", fileName.szStr, sourceLine ) );
          DumpString( StrFmt( "%s(%d):\n", fileName.szStr, sourceLine ) );
        }
        else
        {
          const DWORD lastError = GetLastError();
          printf( StrFmt( "0x%08X (SymGetLineFromAddr64 returns %d)\n", it->stack[stackPos], lastError ) );
          DumpString( StrFmt( "0x%08X (SymGetLineFromAddr64 returns %d)\n", it->stack[stackPos], lastError ) );
        }

      }
#endif // #if MAX_STACK_SIZE > 0
      printf( "\n" );
      DumpString( "\n" );
    }

    ReleaseSymEngine();

    for( ; i < leaksCount; ++i )
      bytesLeaked += sortedAllocs[i].size;

    g_outputPhase = false;
    char const *cp = StrFmt( "Total leaked %d bytes in %d calls of %d calls total\n", bytesLeaked, sortedAllocs.size(), g_mallocIndex );
    printf("%s", cp);
    DumpString(cp);
    CloseLogFile();
  }
  else
  {
    char const *cp = StrFmt( "%d new(s) has no appropriate delete\n", g_unfreeMaloc );
    printf("%s", cp);
    OutputDebugString( cp );
  }

  g_isInternal = false;
#else // #if MAX_STACK_SIZE >= 0
  OutputDebugString( StrFmt( "%d new(s) has no appropriate delete\n", g_unfreeMaloc ) );
#endif // #if MAX_STACK_SIZE >= 0
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if NI_MALLOC_IMPL == 1
#define NI_MALLOC(s)               malloc(s)
#define NI_MALLOC_ALIGNED(s,a)     _aligned_malloc(s,a)
#define NI_FREE(p)                 free(p)
#define NI_FREE_ALIGNED(p)         _aligned_free(p)
#define NI_REALLOC(p,s)            realloc(p,s)
#elif NI_MALLOC_IMPL == 2
#define NI_MALLOC(s)               nedalloc::nedmalloc(s)
#define NI_MALLOC_ALIGNED(s,a)     nedalloc::nedmemalign(a,s)
#define NI_FREE(p)                 nedalloc::nedfree(p)
#define NI_FREE_ALIGNED(p)         nedalloc::nedfree(p)
#define NI_REALLOC(p,s)            nedalloc::nedrealloc(p,s)
#else
#error You must choose malloc implementation in NI_MALLOC_IMPL
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<bool align> 
void *__cdecl MAlloc( size_t size, size_t alignment )
{
  if ( size == 0 )
      return 0;
  void* p = 0;
  if(align)
    p = NI_MALLOC_ALIGNED( size, alignment );
  else
    p = NI_MALLOC( size );
#if MAX_STACK_SIZE >= 0
  RegisterMalloc( size, p );
#else
  InterlockedIncrement( &g_totalMaloc );
  InterlockedIncrement( &g_unfreeMaloc );
#endif

#ifndef NEW_NOT_THROWS
  ni_detail::CheckPtr(p);
#endif // NEW_NOT_THROWS

  return p;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<bool align>
void Free(void* p)
{
  if ( p == 0 )
    return;

#if MAX_STACK_SIZE >= 0
  RegisterFree( p );
#else
  InterlockedDecrement( &g_unfreeMaloc );
#endif

  if( p != (void*)0xcdcdcdcd )
  {
    if(align)
      NI_FREE_ALIGNED( p );
    else
      NI_FREE( p );
  }
  else
    __debugbreak(); //double free bug
}

void* __cdecl Realloc( void* p, size_t size )
{
	if ( size == 0 )
		return 0;

	if ( p == 0 )
		return 0;

	return NI_REALLOC( p, size );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* Aligned_MAlloc(size_t size, size_t alignment)
{
  return MAlloc<true>(size, alignment);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Aligned_Free(void* ptr)
{
  Free<true>(ptr);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ForcedDeleteHack( void *p )
{
  Free<false>(p);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32)
  enum { MALLOC_STD_ALIGN = 8 };
#elif defined(_WIN64)
   enum { MALLOC_STD_ALIGN = 16 };
#endif

struct DebugHeader
{
  size_t user_size;
  unsigned char padding[ MALLOC_STD_ALIGN - sizeof(size_t) ];
};

void* NEWDEL_CCDECL operator new( size_t count )
{
  #ifndef ALLOC_DATA_DEBUG_INIT
    return MAlloc<false>(count, 0);
  #else
    //На LittleEndian архитектурах, для всех типов, достаточно одного байта для определения 
    //изменения младших разрядов справа от выделенной памяти
    //Кроме того, для char, не надо отдельно заботится о выравнивании
    //При проверки затирания памяти слева от запрошенной памяти становится острой проблема выравнивания.
    //Дело в том, что malloc обеспечивает выравнивание памяти по 8/16 байтовой границе в 32/64
    //разрядных системах (http://msdn.microsoft.com/en-us/library/ycsb6wwf(v=VS.100).aspx)
    //и тратить на такую проверку дополнительно 8-16 байт на каждую аллокацию достаточно расточительно,
    //но кроме того nedalloc::nedblksize возвращает размер >= запрошенному и для того чтобы гарантированно отловить 
    //выход за границы хранить размер всё же придётся, тогда и проверку слева можно осуществить
    
    const size_t allocSize = sizeof(DebugHeader) + count + sizeof(unsigned char);
    void * const pRes = MAlloc<false>(allocSize, 0);
  
    if( pRes != 0 )
    {
      DebugHeader * const pHeader = static_cast<DebugHeader *>(pRes);
      pHeader->user_size = count;  
      memset( pHeader->padding, 0xED, sizeof(pHeader->padding) );  
      
      unsigned char * const pNewRes = static_cast<unsigned char *>(pRes) + sizeof(DebugHeader);
      memset( pNewRes, 0xCD, count );
      
      pNewRes[count] = 0xED;
          
      return pNewRes;
    }
      
    return 0;
  #endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static inline bool mempatcmp( const unsigned char * ptr, int value, size_t num )
{
  const unsigned char * const end = ptr + num;

  while( ptr != end )
    if( *ptr++ != value )
      return false;
      
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NEWDEL_CCDECL operator delete( void *pRes )
{
  #ifndef ALLOC_DATA_DEBUG_INIT
    Free<false>(pRes); 
  #else
    if( pRes != 0 )
    {
      unsigned char * const pStart = static_cast<unsigned char *>(pRes) - sizeof(DebugHeader); 
      const DebugHeader * const pHeader = static_cast<const DebugHeader *>( static_cast<const void *>(pStart) );
      
      if( !mempatcmp(pHeader->padding, 0xED, sizeof(pHeader->padding)) )
      {
        OutputDebugString( StrFmt("Detected access over the left border of allocated block with size %d", pHeader->user_size) );

        if( IsDebuggerPresent() )
          __debugbreak();        
      }
           
      const unsigned char * const pLast = static_cast<const unsigned char *>(pRes) + pHeader->user_size;
      
      if( *pLast != 0xED )
      {
        OutputDebugString( StrFmt("Detected access over the right border of allocated block with size %d", pHeader->user_size) );
        
        if( IsDebuggerPresent() )
          __debugbreak();        
      }
      
      memset( pStart, 0xDC, sizeof(DebugHeader) + pHeader->user_size + sizeof(unsigned char) ); 
      
      Free<false>(pStart);  
    } 
  #endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void *NEWDEL_CCDECL operator new[]( size_t size )
{
  return operator new( size );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NEWDEL_CCDECL operator delete[]( void * p )
{
  operator delete(p);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* NEWDEL_CCDECL operator new( size_t size, const char *, int )
{
  return operator new( size );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* NEWDEL_CCDECL operator new( size_t size, int , const char *, int )
{
  return operator new( size );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* NEWDEL_CCDECL operator new[]( size_t size, const char *, int )
{
  return operator new( size );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* NEWDEL_CCDECL operator new[]( size_t size, int , const char *, int )
{
  return operator new( size );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace std
{
const nothrow_t nothrow = nothrow_t();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void *NEWDEL_CCDECL operator new(size_t size, const std::nothrow_t&)
{
  return operator new( size );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void *NEWDEL_CCDECL operator new[](size_t size, const std::nothrow_t&)
{
  return operator new( size );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NEWDEL_CCDECL operator delete(void * p, const std::nothrow_t&)
{
  operator delete(p);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NEWDEL_CCDECL operator delete[](void * p, const std::nothrow_t&)
{
  operator delete(p);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct RegisterDumpMemoryLeaks
{
  CSymEngine se;  

  RegisterDumpMemoryLeaks()
  {
    AssignSymEngine( &se );
  }

  ~RegisterDumpMemoryLeaks()
  {
    DumpMemoryLeaks();
    AssignSymEngine( 0 );
  }

} dumpMemoryLeaks;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#else
void* Aligned_MAlloc(size_t size, size_t alignment) { return _aligned_malloc(size,alignment); }
void Aligned_Free(void* ptr) { _aligned_free(ptr); }
void ForcedDeleteHack( void *p ) { free( p ); }
#endif // #ifdef CHECK_MEMORY_LEAKS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
size_t GetAllocatedFootprint()
{
#if NI_MALLOC_IMPL == 1
  _CrtMemState ms = {0};
  memset( &ms, 0, sizeof( ms ) );
  _CrtMemCheckpoint(&ms);
  return ms.lTotalCount;
#elif NI_MALLOC_IMPL == 2
  // nedmalloc
  return nedalloc::nedmalloc_footprint();
#else
#error Unknown malloc implementation chosen in NI_MALLOC_IMPL
#endif
}



namespace ni_detail
{

bool AddMemoryCallback( TCommonMemoryCallback callback, bool forAllocs )
{
  InitializeAndEnterCritical();

  bool result = false;

  TCommonMemoryCallback * arr = forAllocs ? s_allocCallbacks : s_freeCallbacks;

  for ( int i = 0; i < MaxCommonMemoryCallbacks; ++i )
    if ( arr[i] == callback )
    {
      result = true;
      break;
    }

  if ( !result )
  {
    for ( int i = 0; i < MaxCommonMemoryCallbacks; ++i )
      if ( !arr[i] )
      {
        arr[i] = callback;
        result = true;
        break;
      }
  }

  LeaveCriticalSection( &g_block );
  return result;
}



bool RemoveMemoryCallback( TCommonMemoryCallback callback, bool forAllocs )
{
  InitializeAndEnterCritical();

  TCommonMemoryCallback * arr = forAllocs ? s_allocCallbacks : s_freeCallbacks;

  int l = 0;
  for ( ; l < MaxCommonMemoryCallbacks; ++l )
    if ( !arr[l] )
      break;

  bool result = false;
  for ( int i = 0; i < MaxCommonMemoryCallbacks; ++i )
    if ( arr[i] == callback )
    {
      arr[i] = 0;
      if ( ( i != l ) && ( l < MaxCommonMemoryCallbacks ) )
        nstl::swap( arr[i], arr[l] );
      result = true;
      break;
    }

  LeaveCriticalSection( &g_block );
  return result;
}


} //namespace ni_detail


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef DO_NOT_USE_DLLMAIN
BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
  if((DLL_PROCESS_DETACH == fdwReason) && g_blockInitialized)
  {
    g_blockInitialized = false;
    DeleteCriticalSection(&g_block);
  }
  return TRUE;
}
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
