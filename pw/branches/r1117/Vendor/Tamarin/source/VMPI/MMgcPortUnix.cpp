/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: t; tab-width: 4 -*- */
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
* Portions created by the Initial Developer are Copyright (C) 2004-2006
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "MMgc.h"

#include <sys/mman.h>
#include <sys/time.h>

#if !defined(MAP_ANONYMOUS) && defined(MAP_ANON)
	#define MAP_ANONYMOUS MAP_ANON
#endif // !defined(MAP_ANONYMOUS) && defined(MAP_ANON)

#if defined(MMGC_MEMORY_INFO) && defined(AVMPLUS_UNIX)
	#ifndef _GNU_SOURCE
		#define _GNU_SOURCE
	#endif
	#include <dlfcn.h>
#endif

#ifdef SOLARIS
	#include <procfs.h>
	#include <sys/stat.h>
	typedef caddr_t maddr_ptr;
#else
	typedef void *maddr_ptr;
#endif

#include <fcntl.h>

#ifdef MMGC_SPARC
static size_t pagesize = 4096;
#else
static size_t pagesize = size_t(sysconf(_SC_PAGESIZE));
#endif

size_t VMPI_getVMPageSize()
{
	return pagesize;
}

bool VMPI_canMergeContiguousRegions()
{
	return true;
}

bool VMPI_useVirtualMemory()
{
#ifdef MMGC_SPARC
	return false;
#endif
	return true;
}

bool VMPI_areNewPagesDirty()
{
	return false;
}

void* VMPI_reserveMemoryRegion(void* address, size_t size)
{
	char *addr = (char*)mmap((maddr_ptr)address,
							 size,
							 PROT_NONE,
							 MAP_PRIVATE | MAP_ANONYMOUS,
							 -1, 0);
	if (addr == MAP_FAILED) {
		return NULL;
	}
	if(address && address != addr) {
		// behave like windows and fail if we didn't get the right address
		VMPI_releaseMemoryRegion(addr, size);
		return NULL;
	}
	return addr;
}

bool VMPI_releaseMemoryRegion(void* address, size_t size)
{
	int result = munmap((maddr_ptr)address, size);
	return (result == 0);
}

bool VMPI_commitMemory(void* address, size_t size)
{
	char *addr = (char*)mmap((maddr_ptr)address,
							 size,
							 PROT_READ | PROT_WRITE,
							 MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS,
							 -1, 0);
	
	size_t pageSize = VMPI_getVMPageSize();
	char* temp_addr = addr;
	while( temp_addr < (addr+size))
	{
		// Touch each page
		*temp_addr = 0;
		temp_addr += pageSize; //verify rishit
	}
	return addr == address;
}

bool VMPI_decommitMemory(char *address, size_t size)
{
	// re-map it as PROT_NONE

	// NOTE: we don't release it hear like Mac does, if we do another thread in the process
	// could reserve it after we munmap it and even worse if that happened the mmap call would
	// still work causing both mmap callers to think they mapped the memory.  Mac does have
	// to release first but it can tell that the following reserve succeeded or not.
	char *addr = (char*)mmap((maddr_ptr)address,
							 size,
							 PROT_NONE,
							 MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
							 -1, 0);
	return addr == address;
}

void* VMPI_allocateAlignedMemory(size_t size)
{
	return valloc(size);
}

void VMPI_releaseAlignedMemory(void* address)
{
	free(address);
}

#define state_newline  1
#define state_skipline  2
#define state_P 3
#define state_Pr 4
#define state_Private 6
#define state_size 7

#ifdef LINUX

size_t VMPI_getPrivateResidentPageCount()
{
	char buff[32];
	VMPI_snprintf(buff, sizeof(buff), "/proc/%d/smaps", getpid());
	int smap_hndl = open(buff, O_RDONLY);
	if (smap_hndl == -1)
		return 0;
	
	size_t priv_pages = 0;
	size_t pageSize = VMPI_getVMPageSize();
	uint32_t state = state_newline;
	char size_buff[16];
	uint32_t size_idx = 0;
	int read_size = 0;
	while( (read_size = read(smap_hndl, buff, 32)) )
	{
		int i = 0;
		while(i < read_size )
		{
			char c = buff[i++];
			switch( state )
			{
			case state_newline:
				if( c == 'P' )
					state = state_P;
				else
					state = state_skipline;
				break;

			case state_skipline:
				if( c == '\n' )
					state = state_newline;
				break;

			case state_P:
				if( c == 'r' )
					state = state_Pr;
				else
					state = state_skipline;
				break;

			case state_Pr:
				if( c == 'i' )  // Good enough, nothing else in smaps starts with Pr
					state = state_Private;
				else
					state = state_skipline;
				break;

			case state_Private:
				if ( c >= '0' && c <= '9' )
				{
					state = state_size;
					size_buff[size_idx++] = c;
				}
				else if ( c == '\n')
					state = state_newline;
				break;

			case state_size:
				if( c >= '0' && c <= '9' )
					size_buff[size_idx++] = c;
				else
				{
					size_buff[size_idx] = 0;
					size_idx = 0;
					uint32_t size = VMPI_atoi(size_buff)*1024;
					uint32_t blocks = size/pageSize;
					if( size % pageSize != 0 )
						++blocks;
					priv_pages += blocks;
					
					if ( c == '\n' )
						state = state_newline;
					else
						state = state_skipline;
				}
				break;
			}
		}
	} 
	close(smap_hndl);

	return priv_pages; 
}

#elif defined SOLARIS

size_t VMPI_getPrivateResidentPageCount()
{
	char mapname[32];
	int mapfd, nmap, i;
	prxmap_t *prmapp, *pmp;
	struct stat st;
	ssize_t n;
	size_t priv_pages = 0;

	VMPI_snprintf(mapname, sizeof (mapname), "/proc/%d/xmap", getpid());

	if ((mapfd = open(mapname, O_RDONLY)) < 0 || fstat(mapfd, &st) != 0) {
		if (mapfd >= 0)
			(void) close(mapfd);
		return 0;
	}

	nmap = st.st_size / sizeof (prxmap_t);
	nmap *= 2;
again:
	prmapp = (prxmap_t *)malloc((nmap + 1) * sizeof (prxmap_t));

	if ((n = pread(mapfd, prmapp, (nmap + 1) * sizeof (prxmap_t), 0)) < 0) {
		(void) close(mapfd);
		free(prmapp);
		return 0;
	}

	if (nmap < n / sizeof (prxmap_t)) {
		free(prmapp);
		nmap *= 2;
		goto again;
	}

	(void) close(mapfd);
	nmap = n / sizeof (prxmap_t);

	for (i = 0, pmp = prmapp; i < nmap; i++, pmp++) {
		priv_pages += pmp->pr_anon;
	}
	free(prmapp);
	return priv_pages;
}

#else

size_t VMPI_getPrivateResidentPageCount()
{
	return 0;
}

#endif

uint64_t VMPI_getPerformanceFrequency()
{
	return 1000000;
}

uint64_t VMPI_getPerformanceCounter()
{
#ifdef SOLARIS
	uint64_t retval = gethrtime();
	return retval;
#elif defined(AVMPLUS_UNIX)
	struct timeval tv;
	::gettimeofday(&tv, NULL);

	uint64_t seconds = (uint64_t)tv.tv_sec * 1000000;
	uint64_t microseconds = (uint64_t)tv.tv_usec;
	uint64_t result = seconds + microseconds;
	
	return result;
#else
	#error "High resolution timer needs to be defined for this platform"
#endif
}

#ifdef MMGC_MEMORY_PROFILER


	#ifdef MMGC_SPARC
		bool VMPI_captureStackTrace(uintptr_t* buffer, size_t bufferSize, uint32_t framesToSkip)
		{
		  // TODO for sparc.
			GCAssert(false);
			return false;
		}
	#endif

	#ifdef MMGC_PPC
		bool VMPI_captureStackTrace(uintptr_t* buffer, size_t bufferSize, uint32_t framesToSkip)
		{
		  register int stackp;
		  sintptr pc;
		  asm("mr %0,%%r1" : "=r" (stackp));
		  while(framesToSkip--) {
			stackp = *(int*)stackp;
		  }
		  int i=0;
		  // save space for 0 terminator
		  bufferSize--;
		  while(i<bufferSize && stackp) {
			pc = *((sintptr*)stackp+2);
			buffer[i++]=pc;
			stackp = *(int*)stackp;
		  }
		  buffer[i] = 0;

		  return true;
		}
	#endif

	#ifdef MMGC_IA32
		bool VMPI_captureStackTrace(uintptr_t* buffer, size_t bufferSize, uint32_t framesToSkip)
		{
			void **ebp;
			asm("mov %%ebp, %0" : "=r" (ebp));

			while(framesToSkip-- && *ebp)
			{
				ebp = (void**)(*ebp);
			}

			/* save space for 0 terminator */
			bufferSize--;

			int i = 0;

			while (i < bufferSize && *ebp)
			{
				/* store the current frame pointer */
				buffer[i++] = *((sintptr*) ebp + 1);
				/* get the next frame pointer */
				ebp = (void**)(*ebp);
			}

			buffer[i] = 0;

			return true;
		}
	#endif

	#ifdef MMGC_ARM
		bool VMPI_captureStackTrace(uintptr_t* buffer, size_t bufferSize, uint32_t framesToSkip)
		{
			(void) buffer;
			(void) bufferSize;
			(void) framesToSkip;
			return false;
		}
	#endif

	bool VMPI_getFunctionNameFromPC(uintptr_t pc, char *buffer, size_t bufferSize)
	{
		(void)pc;
		(void)buffer;
		(void)bufferSize;
		return false;
	}

	bool VMPI_getFileAndLineInfoFromPC(uintptr_t /*pc*/, char */*buffer*/, size_t /*bufferSize*/, uint32_t* /*lineNumber*/) 
	{
		return false;
	//#ifdef AVMPLUS_UNIX
	//	Dl_info dlip;
	//	dladdr((void *const)pc, &dlip);
	//	VMPI_sprintf(buffer, "0x%p:%s", (void *)pc, dlip.dli_sname);
	//	return true;
	//#else
	//	return false;
	//#endif
	}


	void VMPI_setupPCResolution() { }
	
	void VMPI_desetupPCResolution() { }

#endif //MEMORY_PROFILER


void VMPI_cleanStack(size_t amt)
{
	void *space = alloca(amt);
	if(space)
	{
		VMPI_memset(space, 0, amt);
	}
}
