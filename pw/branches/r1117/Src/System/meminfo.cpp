#include "stdafx.h"

#ifndef _SHIPPING
#include "meminfo.h"
#include "LogFileName.h"

#include "Vendor/Detour/include/detours.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//uncomment DETOUR_MEMORY_HOOK_ENABLED to collect allocation through detour. Check Game.cpp for corresponded debug variable
//better to disable collecting memory leaks via newdelete.h (comment CHECK_MEMORY_LEAKS, set MAX_STACK_SIZE to -1 and NI_MALLOC_IMPL to 1)
//#define DETOUR_MEMORY_HOOK_ENABLED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
volatile long heapAllocCount = 0;
volatile long unfreeHeapAllocCount = 0;
volatile long virtualAllocCount = 0;
volatile long unfreeVirtualAllocCount = 0;
volatile long heapAllocSize = 0;
volatile long virtualAllocSize = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDebug
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void* (WINAPI *TrampolineHeapAlloc)( HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes ) = HeapAlloc;
static void* (WINAPI *TrampolineHeapReAlloc)( HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes ) = HeapReAlloc;
static BOOL  (WINAPI *TrampolineHeapFree)( HANDLE hHeap, DWORD dwFlags, LPVOID lpMem ) = HeapFree;

static void* (WINAPI *TrampolineVirtualAllocEx)( HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect ) = VirtualAllocEx;
static BOOL  (WINAPI *TrampolineVirtualFreeEx)( HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flFreeType ) = VirtualFreeEx;

static void* (WINAPI *TrampolineVirtualAlloc)( LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect ) = VirtualAlloc;
static BOOL  (WINAPI *TrampolineVirtualFree)( LPVOID lpAddress, SIZE_T dwSize, DWORD flFreeType ) = VirtualFree;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LPVOID WINAPI DetourHeapAlloc(HANDLE hHeap, DWORD dwFlags, DWORD_PTR dwBytes)
{
	if ( ( dwFlags & 0xFFFFFF00 ) == 0 )
  {
    InterlockedIncrement( &heapAllocCount );
	  InterlockedIncrement( &unfreeHeapAllocCount );
		InterlockedExchangeAdd( &heapAllocSize, dwBytes );
  }

	LPVOID result = TrampolineHeapAlloc( hHeap, dwFlags, dwBytes );
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LPVOID  WINAPI DetourHeapReAlloc( HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes )
{
  if ( lpMem != 0 )
  {
	  long dwOldBytes = (long)HeapSize( hHeap, 0, lpMem );
	  if ( dwOldBytes > 0 )
		  InterlockedExchangeAdd( &heapAllocSize, -dwOldBytes );
  }
	InterlockedExchangeAdd( &heapAllocSize, dwBytes );
	
	LPVOID result = TrampolineHeapReAlloc( hHeap, dwFlags, lpMem, dwBytes );
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL WINAPI DetourHeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem)
{
  InterlockedDecrement( &unfreeHeapAllocCount );
  if ( lpMem != 0 )
  {
	  long dwOldBytes = (long)HeapSize( hHeap, 0, lpMem );
	  if ( dwOldBytes > 0 )
		  InterlockedExchangeAdd( &heapAllocSize, -dwOldBytes );
  }

	return TrampolineHeapFree( hHeap, dwFlags, lpMem );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LPVOID WINAPI DetourVirtualAllocEx( HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect )
{
  InterlockedIncrement( &virtualAllocCount );
  InterlockedIncrement( &unfreeVirtualAllocCount );

	LPVOID result = TrampolineVirtualAllocEx( hProcess, lpAddress, dwSize, flAllocationType, flProtect );
  MEMORY_BASIC_INFORMATION mbi;
  if ( VirtualQuery( result, &mbi, sizeof( MEMORY_BASIC_INFORMATION ) ) > 0 )
  	InterlockedExchangeAdd( &virtualAllocSize, mbi.RegionSize );
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL WINAPI DetourVirtualFreeEx( HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flFreeType )
{
  InterlockedDecrement( &unfreeVirtualAllocCount );

  MEMORY_BASIC_INFORMATION mbi;
  if ( VirtualQuery( lpAddress, &mbi, sizeof( MEMORY_BASIC_INFORMATION ) ) > 0 )
    InterlockedExchangeAdd( &virtualAllocSize, -(long)mbi.RegionSize );

	return TrampolineVirtualFreeEx( hProcess, lpAddress, dwSize, flFreeType );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LPVOID WINAPI DetourVirtualAlloc( LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect )
{
  InterlockedIncrement( &virtualAllocCount );
  InterlockedIncrement( &unfreeVirtualAllocCount );

	LPVOID result = TrampolineVirtualAlloc( lpAddress, dwSize, flAllocationType, flProtect );
  MEMORY_BASIC_INFORMATION mbi;
  if ( VirtualQuery( result, &mbi, sizeof( MEMORY_BASIC_INFORMATION ) ) > 0 )
  	InterlockedExchangeAdd( &virtualAllocSize, mbi.RegionSize );
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL WINAPI DetourVirtualFree( LPVOID lpAddress, SIZE_T dwSize, DWORD flFreeType )
{
  InterlockedDecrement( &unfreeVirtualAllocCount );

  MEMORY_BASIC_INFORMATION mbi;
  if ( VirtualQuery( lpAddress, &mbi, sizeof( MEMORY_BASIC_INFORMATION ) ) > 0 )
    InterlockedExchangeAdd( &virtualAllocSize, -(long)mbi.RegionSize );

	return TrampolineVirtualFree( lpAddress, dwSize, flFreeType );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const long GetHeapAllocCount()
{
	return heapAllocCount;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const long GetUnfreeHeapAllocCount()
{
	return unfreeHeapAllocCount;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const long GetVirtualAllocCount()
{
	return virtualAllocCount;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const long GetUnfreeVirtualAllocCount()
{
	return unfreeVirtualAllocCount;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const long GetTotalHeapAllocSize()
{
	return heapAllocSize;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const long GetTotalVirtualAllocSize()
{
	return virtualAllocSize;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef DETOUR_MEMORY_HOOK_ENABLED
#pragma init_seg(user)
static struct DetourInitialization
{
	DetourInitialization()
	{               
		//null the counters
		InterlockedExchange( &heapAllocCount, 0 );
		InterlockedExchange( &unfreeHeapAllocCount, 0 );
		InterlockedExchange( &virtualAllocCount, 0 );
		InterlockedExchange( &unfreeVirtualAllocCount, 0 );

		//set the hook
		DetourTransactionBegin();
		DetourUpdateThread( GetCurrentThread() );
		DetourAttach( &(PVOID&)TrampolineVirtualAllocEx, DetourVirtualAllocEx );
		DetourAttach( &(PVOID&)TrampolineVirtualFreeEx, DetourVirtualFreeEx );
		DetourAttach( &(PVOID&)TrampolineVirtualAlloc, DetourVirtualAlloc );
		DetourAttach( &(PVOID&)TrampolineVirtualFree, DetourVirtualFree );
		DetourAttach( &(PVOID&)TrampolineHeapAlloc, DetourHeapAlloc );
		DetourAttach( &(PVOID&)TrampolineHeapReAlloc, DetourHeapReAlloc );
		DetourAttach( &(PVOID&)TrampolineHeapFree, DetourHeapFree );
		DetourTransactionCommit();
	}

	~DetourInitialization()
	{
		//remove the hook
		DetourTransactionBegin();
		DetourUpdateThread( GetCurrentThread() );
		DetourDetach( &(PVOID&)TrampolineHeapFree, DetourHeapFree );
		DetourDetach( &(PVOID&)TrampolineHeapReAlloc, DetourHeapReAlloc );
		DetourDetach( &(PVOID&)TrampolineHeapAlloc, DetourHeapAlloc );
		DetourDetach( &(PVOID&)TrampolineVirtualFree, DetourVirtualFree );
		DetourDetach( &(PVOID&)TrampolineVirtualAlloc, DetourVirtualAlloc );
		DetourDetach( &(PVOID&)TrampolineVirtualFreeEx, DetourVirtualFreeEx );
		DetourDetach( &(PVOID&)TrampolineVirtualAllocEx, DetourVirtualAllocEx );
		DetourTransactionCommit();
	}
} _detourInitialization;
#endif //DETOUR_MEMORY_HOOK_ENABLED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NDebug
#endif