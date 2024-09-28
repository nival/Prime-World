#include "stdafx.h"

#if defined( NV_WIN_PLATFORM )

	#include <windows.h>
	#include <Winternl.h>

#endif

#include "ThreadLocal.h"

#if defined( NV_WIN_PLATFORM )

	#pragma pack(push, 1)
	typedef struct _CLIENT_ID
	{
	  PVOID UniqueProcess;
	  PVOID UniqueThread;
	} CLIENT_ID, *PCLIENT_ID;

	typedef struct My_TEB 
	{
	  NT_TIB Tib; 
	  PVOID EnvironmentPointer; 
	  CLIENT_ID Cid; 
	  PVOID ActiveRpcInfo; 
	  PVOID ThreadLocalStoragePointer; 
	  PPEB Peb; 
	  ULONG LastErrorValue; 
	  ULONG CountOfOwnedCriticalSections; 
	  PVOID CsrClientThread; 
	  PVOID Win32ThreadInfo; 
	  ULONG Win32ClientInfo[0x1F]; 
	  PVOID WOW32Reserved; 
	  ULONG CurrentLocale; 
	  ULONG FpSoftwareStatusRegister; 
	  PVOID SystemReserved1[0x36]; 
	  PVOID Spare1; 
	  ULONG ExceptionCode; 
	  ULONG SpareBytes1[0x28]; 
	  PVOID SystemReserved2[0xA]; 
	  ULONG GdiRgn; 
	  ULONG GdiPen; 
	  ULONG GdiBrush; 
	  CLIENT_ID RealClientId; 
	  PVOID GdiCachedProcessHandle; 
	  ULONG GdiClientPID; 
	  ULONG GdiClientTID; 
	  PVOID GdiThreadLocaleInfo; 
	  PVOID UserReserved[5]; 
	  PVOID GlDispatchTable[0x118]; 
	  ULONG GlReserved1[0x1A]; 
	  PVOID GlReserved2; 
	  PVOID GlSectionInfo; 
	  PVOID GlSection; 
	  PVOID GlTable; 
	  PVOID GlCurrentRC; 
	  PVOID GlContext; 
	  NTSTATUS LastStatusValue; 
	  UNICODE_STRING StaticUnicodeString; 
	  WCHAR StaticUnicodeBuffer[0x105]; 
	  PVOID DeallocationStack; 
	  PVOID TlsSlots[0x40]; 
	  LIST_ENTRY TlsLinks; 
	  PVOID Vdm; 
	  PVOID ReservedForNtRpc; 
	  PVOID DbgSsReserved[0x2]; 
	  ULONG HardErrorDisabled; 
	  PVOID Instrumentation[0x10]; 
	  PVOID WinSockData; 
	  ULONG GdiBatchCount; 
	  ULONG Spare2; 
	  ULONG Spare3; 
	  ULONG Spare4; 
	  PVOID ReservedForOle; 
	  ULONG WaitingOnLoaderLock; 
	  PVOID StackCommit; 
	  PVOID StackCommitMax; 
	  PVOID StackReserved;
	} MyTEB, *PMyTEB;

	typedef int KPRIORITY;

	typedef struct _THREAD_BASIC_INFORMATION {

	  NTSTATUS  ExitStatus; 
	  PTEB      TebBaseAddress; 
	  CLIENT_ID ClientId; 
	  KAFFINITY AffinityMask; 
	  KPRIORITY Priority; 
	  KPRIORITY BasePriority;

	} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

	typedef struct _PEB_LDR_DATA
	{
	  ULONG Length;
	  UCHAR Initialized;
	  PVOID SsHandle;
	  LIST_ENTRY InLoadOrderModuleList;
	  LIST_ENTRY InMemoryOrderModuleList;
	  LIST_ENTRY InInitializationOrderModuleList;
	  PVOID EntryInProgress;
	} PEB_LDR_DATA, *PPEB_LDR_DATA;

	typedef struct _CURDIR
	{
	  UNICODE_STRING DosPath;
	  PVOID Handle;
	} CURDIR, *PCURDIR;

	typedef struct _RTL_DRIVE_LETTER_CURDIR
	{
	  WORD Flags;
	  WORD Length;
	  ULONG TimeStamp;
	  STRING DosPath;
	} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

	typedef struct _RTL_USER_PROCESS_PARAMETERS
	{
	  ULONG MaximumLength;
	  ULONG Length;
	  ULONG Flags;
	  ULONG DebugFlags;
	  PVOID ConsoleHandle;
	  ULONG ConsoleFlags;
	  PVOID StandardInput;
	  PVOID StandardOutput;
	  PVOID StandardError;
	  CURDIR CurrentDirectory;
	  UNICODE_STRING DllPath;
	  UNICODE_STRING ImagePathName;
	  UNICODE_STRING CommandLine;
	  PVOID Environment;
	  ULONG StartingX;
	  ULONG StartingY;
	  ULONG CountX;
	  ULONG CountY;
	  ULONG CountCharsX;
	  ULONG CountCharsY;
	  ULONG FillAttribute;
	  ULONG WindowFlags;
	  ULONG ShowWindowFlags;
	  UNICODE_STRING WindowTitle;
	  UNICODE_STRING DesktopInfo;
	  UNICODE_STRING ShellInfo;
	  UNICODE_STRING RuntimeData;
	  RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32];
	  ULONG EnvironmentSize;
	} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

	typedef struct _PEB_FREE_BLOCK
	{
	  struct _PEB_FREE_BLOCK* Next;
	  ULONG Size;
	} PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;

	//Copied from Visual Studio debugger. Debugger perfectly see through PEB, while C is not, i dunno why.
	typedef struct _MyPEB {
	  UCHAR InheritedAddressSpace;
	  UCHAR ReadImageFileExecOptions;
	  UCHAR BeingDebugged;
	  UCHAR SpareBits;
	  PVOID Mutant;
	  PVOID ImageBaseAddress;
	  PPEB_LDR_DATA Ldr;
	  PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
	  PVOID SubSystemData;
	  PVOID ProcessHeap;
	  PRTL_CRITICAL_SECTION FastPebLock;
	  PVOID AtlThunkSListPtr;
	  PVOID IFEOKey;
	  ULONG EnvironmentUpdateCount;
	  PVOID KernelCallbackTable;
	  PVOID EventLogSection;
	  PVOID EventLog;
	  PPEB_FREE_BLOCK FreeList;
	  ULONG TlsExpansionCounter;
	  PVOID TlsBitmap;
	  ULONG TlsBitmapBits[2];
	  PVOID ReadOnlySharedMemoryBase;
	  PVOID HotpatchInformation;
	  VOID * * ReadOnlyStaticServerData;
	  PVOID AnsiCodePageData;
	  PVOID OemCodePageData;
	  PVOID UnicodeCaseTableData;
	  ULONG NumberOfProcessors;
	  ULONG NtGlobalFlag;
	  LARGE_INTEGER CriticalSectionTimeout;
	  ULONG HeapSegmentReserve;
	  ULONG HeapSegmentCommit;
	  ULONG HeapDeCommitTotalFreeThreshold;
	  ULONG HeapDeCommitFreeBlockThreshold;
	  ULONG NumberOfHeaps;
	  ULONG MaximumNumberOfHeaps;
	  VOID * * ProcessHeaps;
	  PVOID GdiSharedHandleTable;
	  PVOID ProcessStarterHelper;
	  ULONG GdiDCAttributeList;
	  PRTL_CRITICAL_SECTION LoaderLock;
	  ULONG OSMajorVersion;
	  ULONG OSMinorVersion;
	  WORD OSBuildNumber;
	  WORD OSCSDVersion;
	  ULONG OSPlatformId;
	  ULONG ImageSubsystem;
	  ULONG ImageSubsystemMajorVersion;
	  ULONG ImageSubsystemMinorVersion;
	  ULONG ImageProcessAffinityMask;
	  ULONG GdiHandleBuffer[34];
	  PVOID PostProcessInitRoutine;
	  PVOID TlsExpansionBitmap;
	  ULONG TlsExpansionBitmapBits[32];
	  ULONG SessionId;
	  ULARGE_INTEGER AppCompatFlags;
	  ULARGE_INTEGER AppCompatFlagsUser;
	  PVOID pShimData;
	  PVOID AppCompatInfo;
	  UNICODE_STRING CSDVersion;
	  PVOID * ActivationContextData;
	  PVOID * ProcessAssemblyStorageMap;
	  PVOID * SystemDefaultActivationContextData;
	  PVOID * SystemAssemblyStorageMap;
	  ULONG MinimumStackCommit;
	  PVOID * FlsCallback;
	  LIST_ENTRY FlsListHead;
	  PVOID FlsBitmap;
	  ULONG FlsBitmapBits[4];
	  ULONG FlsHighIndex;
	  PVOID WerRegistrationData;
	  PVOID WerShipAssertPtr;
	} MyPEB, *PMyPEB;
	#pragma pack(pop)

#endif // defined( NV_WIN_PLATFORM )

void ClearThreadTLSData()
{
#if defined( NV_WIN_PLATFORM )

  THREAD_BASIC_INFORMATION threadInfo;
  HMODULE hNTDll = GetModuleHandleA("ntdll.dll");
  FARPROC pNtQueryInformationThread = GetProcAddress(hNTDll, "NtQueryInformationThread");
  NTSTATUS nRet = ((NTSTATUS (CALLBACK *)(HANDLE, THREADINFOCLASS, PVOID, ULONG, PULONG))pNtQueryInformationThread)(GetCurrentThread(), (THREADINFOCLASS)0 /*ThreadBasicInformation*/, &threadInfo, sizeof(threadInfo), NULL);
  if(nRet != 0)
    return;
  //find out what slots really require to be freed
  //TBD: Earnol
  //verify data is free
  //TBD: Earnol

#endif
}

UINT64 ThreadLocalGetTLSBitmap()
{
#if defined( NV_WIN_PLATFORM )

  UINT64 nMap;
  //access module: it is always loaded in windows
  HMODULE hNTDll = GetModuleHandleA("ntdll.dll");
  FARPROC pNtQueryInformationProcess = GetProcAddress(hNTDll, "NtQueryInformationProcess");
  PROCESS_BASIC_INFORMATION procInfo;
  //Do not link export library but call directly instead. Ivn are the way too sensitive to such kind of stuff.
  NTSTATUS nRet = ((NTSTATUS (WINAPI *)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG))pNtQueryInformationProcess)(GetCurrentProcess(), ProcessBasicInformation, &procInfo, sizeof(procInfo), NULL);
  //cast to type taken from Visual Studio SDK
  PMyPEB pPEB = (PMyPEB)procInfo.PebBaseAddress;
  NI_VERIFY(nRet == 0, "Failure calling NtQueryInformationProcess", return 0;);
  //return two DWORDs as one 64 bit int. I'm too lasy to declate struct here 
  nMap = *(UINT64 *)&pPEB->TlsBitmapBits[0];
  return nMap;

#elif defined( NV_LINUX_PLATFORM )

	return 0;

#endif
}

#ifndef LINUX
  #ifndef PTHREAD_KEYS_MAX
    #define PTHREAD_KEYS_MAX 128
  #endif
#endif

GetOSClass::GetOSClass(): tType(WINXP)
{
#if defined( NV_WIN_PLATFORM )

  OSVERSIONINFOEX sysInfo;

  ZeroMemory(&sysInfo, sizeof(OSVERSIONINFOEX));
  sysInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
  if(0 == GetVersionEx ((OSVERSIONINFO *) &sysInfo))
  {
    sysInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    if(!GetVersionEx((OSVERSIONINFO *) &sysInfo)) 
      NI_ALWAYS_ASSERT("Impossible.");
  }
  if(sysInfo.dwMajorVersion == 4 && sysInfo.dwMinorVersion == 0 && sysInfo.dwPlatformId  == VER_PLATFORM_WIN32_NT)
  {
    tType = WINNT;
  }
  else if(sysInfo.dwMajorVersion == 4 && sysInfo.dwMinorVersion == 0 && sysInfo.dwPlatformId  == VER_PLATFORM_WIN32_WINDOWS)
  {
    tType = WIN95;
  }
  else if(sysInfo.dwMajorVersion == 5 && sysInfo.dwMinorVersion == 0)
  {
    tType = WIN2000;
  }
  else if(sysInfo.dwMajorVersion == 5 && sysInfo.dwMinorVersion == 2)
  {
    tType = WIN2003;
  }
  else if(sysInfo.dwMajorVersion == 5 && sysInfo.dwMinorVersion == 1)
  {
    tType = WINXP;
  }
  else if(sysInfo.dwMajorVersion == 6)
  {
    tType = VISTA;
  }
  else if(sysInfo.dwMinorVersion == 10)
  {
    tType = WIN98;
  }
  else if(sysInfo.dwMinorVersion == 90)
  {
    tType = WINME;
  }

#elif defined( NV_WIN_PLATFORM )

  tType = LINUX;

#endif
}

unsigned int GetOSClass::GetMaxTls() const
{
  static int _tlsVals[OS_LAST] = {1088, 1088, 1088, 1088, 80, 80, 64, 64, PTHREAD_KEYS_MAX};
  return _tlsVals[tType];
}

GetOSClass const *GetOSClassType()
{
  static GetOSClass osClass;

  return &osClass;
}
