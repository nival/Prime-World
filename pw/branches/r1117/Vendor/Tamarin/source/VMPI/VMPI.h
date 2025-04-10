/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 1993-2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef __avmplus_VMPI__
#define __avmplus_VMPI__

// Belt and suspenders...

#ifdef DEBUG
    #ifndef _DEBUG
        #define _DEBUG
    #endif
#endif

#ifdef _DEBUG
    #ifndef DEBUG
        #define DEBUG
    #endif
#endif

// Include feature settings.  These also perform platform sniffing if platform
// settings are not provided eg on the command line.

#ifdef AVMSHELL_BUILD
  #include "avmshell-features.h"
#else
  /* The embedding host must provide this file in some directory that's included in
   * header search paths.  It must define a value (0 or 1) for every feature
   * required by avmplus, see shell/avmshell-features.h for a model, also see
   * core/avmfeatures.as for documentation of the feature system.
   */
  #include "avmhost-features.h"
#endif

// Include the feature system here so that the platform files can depend on
// the internal (VMCFG_, etc) names rather than feature names.  Eases
// maintainability.

#include "avmfeatures.h"

// used by platform headers below
typedef void * vmpi_thread_t;

#if AVMSYSTEM_WIN32
  #include "win32/win32-platform.h"
#elif AVMSYSTEM_UNIX
  #include "unix/unix-platform.h"
#elif AVMSYSTEM_MAC
  #include "mac/mac-platform.h"
#elif AVMSYSTEM_SYMBIAN
  #include "symbian/symbian-platform.h"
#endif

// Catchall, though in general the platform files are really responsible for giving
// REALLY_INLINE and FASTCALL a definition.

#ifndef REALLY_INLINE
    #define REALLY_INLINE inline
#endif
#ifndef FASTCALL
    #define FASTCALL 
#endif


#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

// Legacy types used by some embedding host code, eg avmplus::uint64.
// These types are not to be used inside the avm code.
namespace avmplus
{
typedef int64_t		int64;
typedef int64_t		sint64;
typedef uint64_t	uint64;
typedef uint32_t	uint32;
typedef int32_t		int32;
typedef int32_t		sint32;
typedef uint16_t	uint16;

typedef int16_t		int16;

typedef int16_t		sint16;
typedef uint8_t		uint8;
typedef int8_t		int8;
typedef int8_t		sint8;
typedef uintptr_t	uintptr;
typedef intptr_t	sintptr;

typedef uint8_t		byte;
}
/* wchar is our version of wchar_t, since wchar_t is different sizes
 on different platforms, but we want to use UTF-16 uniformly. */
typedef uint16_t wchar;

/**
* This method should return the difference in milliseconds between local time and UTC
* @return offset in milliseconds
*/
extern double		VMPI_getLocalTimeOffset();

/**
* This method should return the Daylight Savings time adjustment in milliseconds
* @return number of milliseconds corresponding to daylight savings adjustment when active, 0 otherwise
*/
extern double		VMPI_getDaylightSavingsTA(double time);

/**
* This method should return the current UTC date and time in milliseconds
* @return UTC date and time in milliseconds
*/
extern double		VMPI_getDate();

/**
* This method should return the system time in milliseconds
* The implementation of this method could either return the time elapsed since the system started or since epoc
* @return number of milliseconds elapsed
*/
extern uint64_t		VMPI_getTime();

/**
* This method is called to output log messages
* The implementation of this method is platform-defined
*  @param message NULL-terminated UTF8-encoded string
* @return none
*/
extern void VMPI_log(const char* message);

/**
* This method is called to output debugging messages
* This method is specifically for debugging purposes and is invoked to output useful debug informaton
* The implementation of this method is platform-defined.  For example, it could be used to output the message to an IDE
* @param message NULL-terminated UTF8-encoded string
* @return none
*/
extern void VMPI_debugLog(const char* message);

/**
* This method is called to interrupt the program execution during debugging
* Upon a call to this method, the platform execution should interrupt the program execution
* while maintaining the current call stack and associated program information such as the registers
* and return the control back to the user/developer
* This method is specifically for debugging purposes and is invoked to enter a debug interrupt to examine information like the variable values or call stack
* The implementation of this method is platform-defined.
* On platforms that cannot support debug interrupts the program execution should be aborted
* @return none
*/
extern void VMPI_debugBreak();

/**
* This method is used to request a block of memory from the system
* @param size size, in bytes, of memory block requested
* @return pointer to the start of memory block if allocation was successful, NULL otherwise
*/
extern void*		VMPI_alloc(size_t size);

/**
* This method is used to free a previously allocated block
* @param ptr pointer to the memory that needs to be released
* @return none
*/
extern void			VMPI_free(void* ptr);


/**
* This method is used to free a previously allocated block
* @param ptr pointer to the memory that needs to be released
* @return none
*/
extern size_t			VMPI_size(void* ptr);


/**
* This method is used to get the size of the memory page of the system
* @return return the size, if bytes, of memory page
*/
extern size_t		VMPI_getVMPageSize();

/**
* Method to retrieve number of VM pages in virtual address space of a process
* @return number of pages
* @see VMPI_getVMPageSize()
*/
extern size_t		VMPI_getPrivateResidentPageCount();

/**
* Method to find whether the platform supports merging of contiguous memory regions from heap
* @return true if heap merging is supported, false otherwise	
*/
extern bool			VMPI_canMergeContiguousHeapRegions();

/**
* This method is used to reserve region(s) of memory, i.e. one or more memory pages, in the system's virtual address space
* This method is recommended to be supported on platforms with virtual memory
* @param address optional argument, indicating the base address of the region to be reserved.
* The system should treat this address as a hint and try to reserve a region as close to this address as possible
* If NULL, the system can determine the address of the region.
* @param size size of region, in bytes, to reserve
* @return point to base address of the reserved region, NULL otherwise
* @see VMPI_ReleaseMemoryRegion(), VMPI_CommitMemory()
*/
extern void*		VMPI_reserveMemoryRegion(void* address, size_t size);

/**
* This method is called to release region(s) of memory previously reserved.
* @param address base address of the region to be released
* @param size size, in bytes, of the region
* @return true if the function succeeds, false otherwise
*/
extern bool			VMPI_releaseMemoryRegion(void* address, size_t size);

/**
* This method is used to commit a pages(s) of memory in a previously reserved region
* @param address base address of the memory region to commit
* @param size size, in bytes, of the memory to commit 
* @return true if the function succeeds, false otherwise
* @see VMPI_ReserveMemoryRegion()
*/
extern bool			VMPI_commitMemory(void* address, size_t size);

/**
* This method is used to de-commit a pages(s) of memory that were previously commited
* @param address base address of the memory region to decommit
* @param size, in bytes, of the memory region to decommit
* @return true if the function succeeds, false otherwise
* @see VMPI_CommitMemory()
*/
extern bool			VMPI_decommitMemory(char *address, size_t size);

/**
 * SetPageProtection changes the page access protections on a block of pages,
 * to make JIT-ted code executable or not.
 *
 * @param address pointer to start of memory block.  It is possible that the memory block pointed to by address
 * could be acquired from more than one calls to VMPI_reserveMemoryRegion.  The implementation of this method 
 * is expected to handle such cases and identify the region boundaries if the underlying system requires
 * setting the protection flags on blocks individually if they were allocated separately.
 * @param executableFlag If executableFlag is true, the memory is made executable and read-only.
 * If executableFlag is false, the memory is made non-executable and read-write.
 * @param writeableFlag If true memory block is made read-write
 */
extern void VMPI_setPageProtection(void *address, size_t size, bool executeFlag, bool writeableFlag);

/**
* This method is used to allocate a block of memory with the base address aligned to the system page size
* This method should be implemented in systems that do not have virtual memory in lieu of APIs to reserve and commit memory regions
* @param size size, in bytes, of the block of memory to allocate
* @return pointer to start of the memory block if allocation was successful, NULL otherwise
* @see VMPI_ReleaseAlignedMemory()
*/
extern void*		VMPI_allocateAlignedMemory(size_t size);

/**
* This method is used to release a block of memory via VMPI_AllocateAlignedMemory
* @param address pointer to the start of the memory block to be released
* @return none
*/
extern void			VMPI_releaseAlignedMemory(void* address);

/**
* This method is used to determind should MMgc zero initalize newly allocated memory,
* either allocated with VMPI_commitMemory or VMPI_allocateAlignedMemory.
* @return false if the memory is zero initialized by the OS, otherwise true
*/
extern bool			VMPI_areNewPagesDirty();

/**
* Method to get the frequency of a high performance counter/timer on the system
* On platforms where no API to retrieve this information should return a number that closely
* matches its timer frequency
* @return 64-bit value indicating the frequency of the system's performance counter or clock with highest resolution
* @see VMPI_getPerformanceCounter()
*/
extern uint64_t 	VMPI_getPerformanceFrequency();

/**
* Method to get the current value of the system's performance counter/timer
* Platforms that support a high performance counter should return its current value
* Platforms that do not have a high performance counter should return the current timer/clock
* value that was used as a basis to calculate the frequency returned from VMPI_getPerformanceFrequency()
* @return 64-bit value indicating the current value of the counter
* @see VMPI_getPerformanceFrequency()
*/extern uint64_t 	VMPI_getPerformanceCounter();

/**
* Method to obtain the stack backtrace
* Used by the MMgc memory profiler to get call stack information
* @param buffer buffer to fill the call stack data with
* @param bufferSize size, in bytes, of the buffer passed
* @param framesToSkip number of function frames to skip from the start of trace 
* @return true if back trace was captured successfully, false otherwise
*/
extern bool			VMPI_captureStackTrace(uintptr_t* buffer, size_t bufferSize, uint32_t framesToSkip);

/**
* Method to retrieve the name of the method/function given a specific address in code space
* Used by the MMgc memory profiler to get and display function names
* This method is expected to write a null terminated string representing the function name 
* in to the buffer
* @param pc address whose corresponding function name should be returned
* @param buffer buffer to write the function name to
* @param bufferSize size, in bytes, of the buffer passed
* @return true if the function name was retrieved, false otherwise
*/
extern bool			VMPI_getFunctionNameFromPC(uintptr_t pc, char *buffer, size_t bufferSize);

/**
* Method to retrieve the source filename and line number given a specific address in a code space
* Used by the MMgc memory profiler to display location info of source code
* This method is expected to write a null terminated string representing the file name 
* in to the buffer
* @param pc address of code whose corresponding location should be returned
* @param buffer buffer to write the filename to
* @param bufferSize size, in bytes, of the buffer for filename
* @param out param to write the line number to
* @return true if the file and line number info was retrieved successfully, false otherwise
*/
extern bool			VMPI_getFileAndLineInfoFromPC(uintptr_t pc, char *buffer, size_t bufferSize, uint32_t* lineNumber);

/**
* Method to create a new instance of vmpi_spin_lock_t
* This instance will subsequently be passed to acquire/release lock methods
* @return newly created vmpi_spin_lock_t instance
*/
extern void			VMPI_lockInit(vmpi_spin_lock_t* lock);

/**
* Method to destroy the vmpi_spin_lock_t instance
* This method is called when MMgc no longer intends to use the vmpi_spin_lock_t
* instance created and return via VMPI_lockCreate.
* The implementation can safely destroy the lock instance.
* It is allowed for the caller to have acquired the lock when this function is called.
* @param lock instance of vmpi_spin_lock_t to be destroyed
* @return none
* @see VMPI_lockCreate
*/
extern void			VMPI_lockDestroy(vmpi_spin_lock_t* lock);

/**
* Method to acquire a lock on a vmpi_spin_lock_t instance
* If this method returns true, MMgc assumes that the lock was acquired successfully
* During a call to this method, if the lock was held by some other thread then the
* implementation should wait until the lock becomes available
* Return value of false is considered to be an error condition and should only happen
* in exception situations
* @param lock instance to acquire the lock on
* @return true if lock was successfully acquired, false in event of failure
*/
extern bool			VMPI_lockAcquire(vmpi_spin_lock_t* lock);

/**
* Method to release a lock on a vmpi_spin_lock_t instance
* @param lock instance to release the lock on
* @return true if lock was successfully release, false in event of failure
*/
extern bool			VMPI_lockRelease(vmpi_spin_lock_t* lock);

/**
* Method to obtain a lock on a vmpi_spin_lock_t instance if it isn't locked
* @param lock instance to release the lock on
* @return true if lock was successfully aqcuired, false if another thread has it
*/
extern bool			VMPI_lockTestAndAcquire(vmpi_spin_lock_t* lock);

/**
 * can two consecutive calls to VMPI_reserveMemoryRegion be freed with one VMP_releaseMemoryRegion call?
 * @return true if it can
 */
extern bool VMPI_canMergeContiguousRegions();

/**
 * are the virtual memory API's implemented and usable for this platform/OS?
 * @return true if they are
 */
extern bool VMPI_useVirtualMemory();

/**
* Method to check whether MMgc memory profiling is turned on or not
* @return true if profiling is enabled, false otherwise
*/
extern bool VMPI_isMemoryProfilingEnabled();

/** 
 * Method to setup a spy channel on MMgc/avmplus
 * If the platform intends to periodically retrieve information from MMgc/avmplus
 * then it can perform the necessary setup during this function call and return true
 * @return true if the spy is setup successfully else false
 * @see VMPI_spyCallback
*/
extern bool VMPI_spySetup();

/** 
 * Callback method for spy
 * Currently called on every allocation in MMgc if VMPI_spySetup returned true
 * @return none
*/
extern void VMPI_spyCallback();

/**
 * Clean from the current stack pointer amt bytes
 * @param the amout of bytes to clear
 */
extern void VMPI_cleanStack(size_t amt);

/** 
 * MEthod to determine whether we have access to symbol information
 * @return a bool indicating whether we have 
*/
extern bool VMPI_hasSymbols();

/** 
 * Method to create a thread local storage (TLS) identifier 
 * This identifier will be used as a key to set/get thread-specific data
 * @param [out] pointer to store the value of newly created TLS identifier
 * @return true if TLS identifier was created successfully, false otherwise
*/
extern bool VMPI_tlsCreate(uintptr_t* tlsId);

/** 
 * Method to destroy a previously created TLS identifier
 * @param tlsId TLS identifier to be destroyed
 * @return none
 * @see VMPI_tlsCreate()
*/
extern void VMPI_tlsDestroy(uintptr_t tlsId);

/** 
 * Method to associate a thread-specific data with a TLS identifier
 * previously created by VMPI_tlsCreate
 * @param tlsId TLS identifier to associate the data with
 * @param value data to be associated with id
 * @return true if value was set successfully, false otherwise
*/
extern bool VMPI_tlsSetValue(uintptr_t tlsId, void* value);

/** 
 * Method to retrieve a data associated with a TLS identifier
 * that may have been previously set via VMPI_tlsSetValue
 * @param tlsId TLS identifier for which the associated data should be retrieved
 * @return the associated data, else NULL if no value was set
 * @see VMPI_tlsSetValue
*/
extern void* VMPI_tlsGetValue(uintptr_t tlsId);

/**
 * Obtain current thread identifier
 * @return thread id
 */
extern vmpi_thread_t VMPI_currentThread();

/**
 * Method to setup a spy channel on MMgc/avmplus
 * If the platform intends to periodically retrieve information from MMgc/avmplus
 * then it can perform the necessary setup during this function call and return true
 * @return true if the spy is setup successfully else false
 * @see VMPI_spyCallback
*/
extern bool VMPI_spySetup();
extern void VMPI_spyTeardown();

/** 
 * Callback method for spy
 * Currently called on every allocation in MMgc if VMPI_spySetup returned true
 * @return none
*/
extern void VMPI_spyCallback();

/*
 * Method to perform any initialization activities to assist
 * the program counter to symbols resolution for MMgc memory profiler
 * @return none
 */
extern void VMPI_setupPCResolution();

/**
 * Method to perform any cleanup of items that were created/setup
 * for program counter to symbols resolution for MMgc memory profiler
 * @return none
 * @see VMPI_setupPCResolution
*/
extern void VMPI_desetupPCResolution();

/**
 * wrapper around getenv function, return's NULL on platforms with no env vars
 * @return value of env var
 */
extern const char *VMPI_getenv(const char *name);

#endif /* __avmplus_VMPI__ */
