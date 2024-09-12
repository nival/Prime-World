#ifndef _MEMINFO_H_
#define _MEMINFO_H_
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHIPPING
namespace NDebug
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const long GetHeapAllocCount();
const long GetUnfreeHeapAllocCount();

const long GetVirtualAllocCount();
const long GetUnfreeVirtualAllocCount();

const long GetTotalHeapAllocSize();
const long GetTotalVirtualAllocSize();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
  LPVOID  WINAPI DetourHeapAlloc( HANDLE hHeap, DWORD dwFlags, DWORD_PTR dwBytes );
  LPVOID  WINAPI DetourHeapReAlloc( HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes );
  BOOL    WINAPI DetourHeapFree( HANDLE hHeap, DWORD dwFlags, LPVOID lpMem );
	LPVOID  WINAPI DetourVirtualAllocEx( HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect );
  BOOL    WINAPI DetourVirtualFreeEx( HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flFreeType );
  LPVOID  WINAPI DetourVirtualAlloc( LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect );
  BOOL    WINAPI DetourVirtualFree( LPVOID lpAddress, SIZE_T dwSize, DWORD flFreeType );
#endif  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NDebug

#endif
#endif

