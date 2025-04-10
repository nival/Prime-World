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

#include <e32std.h>
#include <hal.h>

#include "MMgc.h"

/**
* Experimental code to use RChunk to enable virtual allocation.
* As JIT is currently off on Symbian it is not required and allocateAlignedMemory is used instead.
*/
//#define SYMBIAN_JIT_TEST
#define USE_RCHUNK
#ifdef USE_RCHUNK
	class SymbianHeap
	{
	public:
		
		SymbianHeap(TInt size)
		{
			ok = false;
			startAddr = 0;
			endAddr = 0;
			next = 0;
#ifdef SYMBIAN_JIT_TEST // make all memory executable to quickly test JIT
			if(chunk.CreateLocalCode(0,size,EOwnerProcess) == KErrNone)
#else
			if(chunk.CreateDisconnectedLocal(0,0,size,EOwnerProcess) == KErrNone)
#endif // SYMBIAN_JIT
			{
				ok = true;
				startAddr = (TInt)chunk.Base();
				endAddr = startAddr + size;
			}
		}
		
		~SymbianHeap()
		{
			chunk.Close();
		}
		
		void Close()
		{
			chunk.Close();
		}
		
		bool Commit(TInt addr, TInt size)
		{
			bool result = false;
			if(chunk.Commit(addr - startAddr, size) == KErrNone)
			{
				result = true;
			}
			return result;
		}
		
		bool Decommit(TInt addr, TInt size)
		{
			bool result = false;
			if(chunk.Decommit(addr - startAddr, size) == KErrNone)
			{
				result = true;
			}
			return result;
		}
		
		RChunk chunk;
		TInt startAddr;
		TInt endAddr;
		SymbianHeap* next;
		bool ok;
	};
	
	static SymbianHeap* heapListRoot = 0;
	
	static SymbianHeap* FindHeap(TInt addr)
	{
		SymbianHeap* retHeap = 0;
		SymbianHeap* heap = heapListRoot;
		while(heap)
		{
			if((addr >= heap->startAddr) && (addr < heap->endAddr))
			{
				retHeap = heap;
				break;
			}
			heap = heap->next;
		}
		return retHeap;
	}
#endif // USE_RCHUNK

size_t VMPI_getVMPageSize()
{
	TInt pageSize;
	HAL::Get(HAL::EMemoryPageSize, pageSize);
	return pageSize;
}

bool VMPI_canMergeContiguousRegions()
{
	return false;
}

bool VMPI_useVirtualMemory()
{
#ifdef USE_RCHUNK
	return true;
#else // USE_RCHUNK
	return false;
#endif // USE_RCHUNK
}

bool VMPI_areNewPagesDirty()
{
	return true;
}

void* VMPI_reserveMemoryRegion(void* address, size_t size)
{
	void* ptr = 0;
#ifdef USE_RCHUNK
	// After reading the RChunk Symbian API it looks like we can not allocate contiguous memory.
	// Reserve only when address is null. MMgc should handle the rest.
	if(address == NULL)
	{
		SymbianHeap* newHeap = new SymbianHeap(size);
		if(newHeap && newHeap->ok)
		{
			newHeap->next = heapListRoot;
			heapListRoot = newHeap;
			ptr = (void*)newHeap->startAddr;
		}
	}
#endif // USE_RCHUNK
	return ptr;
}

bool VMPI_releaseMemoryRegion(void* address, size_t size)
{
#ifdef USE_RCHUNK
	SymbianHeap* heap = FindHeap((TInt)address);
	if(heap)
	{
		// close does not have a return value
		heap->Close();
		
		// remove from list
		SymbianHeap* list = heapListRoot;
		SymbianHeap* prev = NULL;
		while(list)
		{
			if(list == heap)
			{
				if(prev)
				{
					prev->next = heap->next;
				} else
				{
					heapListRoot = heap->next;
				}
				delete heap;
				break;
			}
			prev = list;
			list = list->next;
		}
		return true;
	}
#endif // USE_RCHUNK
	return false;
}

bool VMPI_commitMemory(void* address, size_t size)
{
	bool result = false;
#ifdef USE_RCHUNK
	SymbianHeap* heap = FindHeap((TInt)address);
	if(heap)
	{
		result = heap->Commit((TInt)address, (TInt)size);
// TEMPORARY FIX: MMgc should zero initialize the memory, but it does not seem to do it in all cases.
		if(result)
		{
			memset(address, 0, size);
		}
// TEMPORARY FIX: MMgc should zero initialize the memory, but it does not seem to do it in all cases.
	}
#if 1
	if(result)
	{
		size_t pageSize = VMPI_getVMPageSize();
		char* addr = (char*)address;
		char* temp_addr = addr;
		while( temp_addr < (addr+size))
		{
			// Touch each page
			*temp_addr = 0;
			temp_addr += pageSize;
		}
	}
#endif // 1

#endif // USE_RCHUNK
	return result;
}

bool VMPI_decommitMemory(char *address, size_t size)
{
	bool result = false;
#ifdef USE_RCHUNK
	SymbianHeap* heap = FindHeap((TInt)address);
	if(heap)
	{
		result = heap->Decommit((TInt)address, (TInt)size);
	}
#endif // USE_RCHUNK
	return result;
}

void* VMPI_allocateAlignedMemory(size_t size)
{
#ifndef USE_RCHUNK
	char *ptr, *ptr2, *aligned_ptr;
	size_t align_size = VMPI_getVMPageSize();
	size_t align_mask = align_size - 1;

	size_t alloc_size = size + align_size + sizeof(int);
	ptr = (char *)malloc(alloc_size);

	if(ptr==NULL) return(NULL);

	ptr2 = ptr + sizeof(int);
	aligned_ptr = ptr2 + (align_size - ((size_t)ptr2 & align_mask));

	ptr2 = aligned_ptr - sizeof(int);
	*((int *)ptr2)=(int)(aligned_ptr - ptr);

	return(aligned_ptr);
#else
	return 0;
#endif // USE_RCHUNK
}

void VMPI_releaseAlignedMemory(void* address)
{
#ifndef USE_RCHUNK
	int *ptr2=(int *)address - 1;
	char *unaligned_ptr = (char*) address - *ptr2;
	free(unaligned_ptr);
#endif // USE_RCHUNK
}

size_t VMPI_getPrivateResidentPageCount()
{
	size_t pageSize = VMPI_getVMPageSize();
	if(pageSize > 0)
	{
		TInt freeRAM;
		HAL::Get(HAL::EMemoryRAMFree, freeRAM);
		return freeRAM/pageSize;
	} else
	{
		return 0;
	}
}

uint64_t VMPI_getPerformanceFrequency()
{
	TInt tickPeriod;
	HAL::Get(HALData::EFastCounterFrequency, tickPeriod);
	return (uint64_t)tickPeriod;
}

uint64_t VMPI_getPerformanceCounter()
{
// Alternative way:
/*
	TTime t;
	t.UniversalTime ();
	TInt64 lt = t.Int64 ();
	return (uint64_t) (lt & 0x7FFFFFFF);
*/
	TUint32 counter = User::FastCounter();
	return counter;
}

void VMPI_cleanStack(size_t amt)
{
	// TODO
}

void VMPI_setupPCResolution()
{
	// TODO
}

void VMPI_desetupPCResolution()
{
	// TODO
}

#ifdef MMGC_MEMORY_PROFILER

	bool VMPI_captureStackTrace(uintptr_t* buffer, size_t bufferSize, uint32_t framesToSkip)
	{
		(void) buffer;
		(void) bufferSize;
		(void) framesToSkip;
		return false;
	}

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
	}

#endif //MEMORY_PROFILER

