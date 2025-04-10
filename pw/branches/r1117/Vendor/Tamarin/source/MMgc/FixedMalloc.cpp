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


#include "MMgc.h"

namespace MMgc
{
	// kSizeClassIndex[] is an array that lets us quickly determine the allocator
	// to use for a given size, without division. A given allocation is rounded
	// up to the nearest multiple of 8, then downshifted 3 bits, and the index
	// tells us which allocator to use. (a special case is made for <= 4 bytes on
	// 32-bit systems in FindSizeClass to keep the table small.)

	// code to generate the table:
	//
	//		const int kMaxSizeClassIndex = (kLargestAlloc>>3)+1;
	//		uint8_t kSizeClassIndex[kMaxSizeClassIndex];
	//		printf("static const unsigned kMaxSizeClassIndex = %d;\n",kMaxSizeClassIndex);
	//		printf("static const uint8_t kSizeClassIndex[kMaxSizeClassIndex] = {\n");
	//		for (int size = 0; size <= kLargestAlloc; size += 8)
	//		{
	//			int i = 0;
	//			while (kSizeClasses[i] < size)
	//			{
	//				++i;
	//				AvmAssert(i < kNumSizeClasses);
	//			}
	//			AvmAssert((size>>3) < kMaxSizeClassIndex);
	//			kSizeClassIndex[(size>>3)] = i;
	//			if (size > 0) printf(",");
	//			if (size % (16*8) == 0) printf("\n");
	//			printf(" %d",i);
	//		}
	//		printf("};\n");

#ifdef MMGC_64BIT
	const int16_t FixedMalloc::kSizeClasses[kNumSizeClasses] = {
		8, 16, 24, 32, 40, 48, 56, 64, 72, 80, //0-9
		88, 96, 104, 112, 120, 128,	136, 144, 152, 160, //10-19
		168, 176, 192, 208, 224, 232, 248, 264, 288, 304, //20-29
		336, 360, 400, 448, 504, 576, 672, 800, 1008, 1344, //30-39
		2016, //40
	};

	/*static*/ const uint8_t FixedMalloc::kSizeClassIndex[kMaxSizeClassIndex] = {
		 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
		 15, 16, 17, 18, 19, 20, 21, 22, 22, 23, 23, 24, 24, 25, 26, 26,
		 27, 27, 28, 28, 28, 29, 29, 30, 30, 30, 30, 31, 31, 31, 32, 32,
		 32, 32, 32, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34,
		 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36,
		 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
		 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
		 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 39,
		 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
		 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
		 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40,
		 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
		 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
		 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
		 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
		 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40
	};

#else
	const int16_t FixedMalloc::kSizeClasses[kNumSizeClasses] = {
		4, 8, 16, 24, 32, 40, 48, 56, 64, 72, //0-9
		80, 88, 96, 104, 112, 120, 128,	144, 160, 176, //10-19
        184, 192, 200, 208, 224, 232, 248, 264, 288, 312, //20-29
		336, 368, 400, 448, 504, 576, 672, 808, 1016, 1352, //30-39
		2032, //40
	};

	/*static*/ const uint8_t FixedMalloc::kSizeClassIndex[kMaxSizeClassIndex] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 
		16, 17, 17, 18, 18, 19, 19, 20, 21, 22, 23, 24, 24, 25, 26, 26, 
		27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 31, 31, 32, 
		32, 32, 32, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 
		35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 
		36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 
		37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 
		38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 
		39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 
		39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 
		39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 
		40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 
		40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 
		40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 
		40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 
		40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40
	};

#endif

	/*static*/
	FixedMalloc *FixedMalloc::instance;

	void FixedMalloc::InitInstance(GCHeap* heap)
	{
		m_heap = heap;
		numLargeChunks = 0;
	#ifdef MMGC_MEMORY_PROFILER
		totalAskSizeLargeAllocs = 0;
	#endif
	#ifdef _DEBUG
		largeObjects = NULL;
	#endif

		// Create all the allocators up front (not lazy)
		// so that we don't have to check the pointers for
		// NULL on every allocation.
		for (int i=0; i<kNumSizeClasses; i++) {
			// FIXME: by default FixedAlloc uses 4K chunks, for the
			// more common size classes maybe we should use 8/16/32.
			// FIXME: we could use FixedAllocLarge for the bigger size 
			// classes but how to call the right Free would need to be work out
			m_allocs[i].Init((uint32_t)kSizeClasses[i], heap);
		}

		FixedMalloc::instance = this;
	}

	void FixedMalloc::DestroyInstance()
	{
		for (int i=0; i<kNumSizeClasses; i++) {
			m_allocs[i].Destroy();
		}		
		FixedMalloc::instance = NULL;
	}
	
	void* FASTCALL FixedMalloc::OutOfLineAlloc(size_t size, FixedMallocOpts flags)
	{
		// OPTIMIZEME?  Alloc() is inlined, as are some functions
		// it calls, but we could inline massively here.  As it
		// is, Alloc(size) expands to three calls: VMPI_lockAcquire,
		// FixedAlloc::Alloc/LargeAlloc, and VMPI_lockRelease.

		return Alloc(size, flags);
	}
	
	void FASTCALL FixedMalloc::OutOfLineFree(void* p)
	{
		// OPTIMIZEME?  Free() is inlined, as are some functions
		// it calls, but we could inline massively here.  As it is,
		// Free(p) expands into three calls: VMPI_lockAcquire,
		// FixedAlloc::Free/LargeFree, and VMPI_lockRelease.

		Free(p);
	}
	
	void FixedMalloc::GetUsageInfo(size_t& totalAskSize, size_t& totalAllocated)
	{
		totalAskSize = 0;
		totalAllocated = 0;
		for (int i=0; i<kNumSizeClasses; i++) {
			size_t allocated = 0;
			size_t ask = 0;
			m_allocs[i].GetUsageInfo(ask, allocated);
			totalAskSize += ask;
			totalAllocated += allocated;
		}

#ifdef MMGC_MEMORY_PROFILER
		totalAskSize += totalAskSizeLargeAllocs;
#endif

		// not entirely accurate, assumes large allocations using all of last page (large ask size not stored)
		totalAllocated += numLargeChunks * GCHeap::kBlockSize;
	}

	void *FixedMalloc::LargeAlloc(size_t size, FixedMallocOpts flags)
	{
		GCHeap::CheckForAllocSizeOverflow(size, GCHeap::kBlockSize+DebugSize());
		
		size += DebugSize();

		int blocksNeeded = (int)GCHeap::SizeToBlocks(size);
		uint32_t gcheap_flags = GCHeap::kExpand;

		if((flags & kCanFail) != 0)
			gcheap_flags |= GCHeap::kCanFail;
		if((flags & kZero) != 0)
			gcheap_flags |= GCHeap::kZero;

		void *item = m_heap->Alloc(blocksNeeded, gcheap_flags);
		if(item)
		{
			numLargeChunks += blocksNeeded;
			
			item = GetUserPointer(item);
#ifdef MMGC_HOOKS
			if(m_heap->HooksEnabled())
			{
#ifdef MMGC_MEMORY_PROFILER
				totalAskSizeLargeAllocs += (size - DebugSize());
#endif
				m_heap->AllocHook(item, size - DebugSize(), Size(item));
			}
#endif // MMGC_HOOKS
		
#ifdef _DEBUG
		// fresh memory poisoning
			if((flags & kZero) == 0)
				memset(item, 0xfa, size - DebugSize());

		// enregister
			AddToLargeObjectTracker(item);
#endif
		}
		return item;
	}
	
	
	void FixedMalloc::LargeFree(void *item)
	{
#ifdef _DEBUG
		RemoveFromLargeObjectTracker(item);
#endif
#ifdef MMGC_HOOKS
		if(m_heap->HooksEnabled()) {
	#ifdef MMGC_MEMORY_PROFILER
			if(m_heap->GetProfiler())
				totalAskSizeLargeAllocs -= m_heap->GetProfiler()->GetAskSize(item);
	#endif
			m_heap->FinalizeHook(item, Size(item));
			m_heap->FreeHook(item, Size(item), 0xfa);
		}
#endif
		numLargeChunks -= GCHeap::SizeToBlocks(LargeSize(item));
		m_heap->FreeNoProfile(GetRealPointer(item));
	}
	
	size_t FixedMalloc::LargeSize(const void *item)
	{
		return m_heap->Size(item) * GCHeap::kBlockSize;
	}

	void *FixedMalloc::Calloc(size_t count, size_t elsize, FixedMallocOpts opts)
	{
		return Alloc(GCHeap::CheckForCallocSizeOverflow(count, elsize), opts);
	}
	
	size_t FixedMalloc::GetTotalSize()
	{
		size_t total = numLargeChunks;
		for (int i=0; i<kNumSizeClasses; i++) {
			total += m_allocs[i].GetNumChunks();
		}	
		return total;
	}

#ifdef MMGC_MEMORY_PROFILER
	void FixedMalloc::DumpMemoryInfo()
	{
		size_t inUse, ask;
		GetUsageInfo(ask, inUse);
		GCLog("[mem] FixedMalloc total %d pages inuse %d bytes ask %d bytes\n", GetTotalSize(), inUse, ask);
		for (int i=0; i<kNumSizeClasses; i++) {
			m_allocs[i].GetUsageInfo(ask, inUse);
			if( m_allocs[i].GetNumChunks() > 0)
				GCLog("[mem] FixedMalloc[%d] total %d pages inuse %d bytes ask %d bytes\n", kSizeClasses[i], m_allocs[i].GetNumChunks(), inUse, ask);
		}
		GCLog("[mem] FixedMalloc[large] total %d pages\n", numLargeChunks);
	}
#endif

#ifdef _DEBUG
	// If this returns then item was definitely allocated by an allocator
	// owned by this FixedMalloc.
	void FixedMalloc::EnsureFixedMallocMemory(const void* item)
	{
		for (int i=0; i<kNumSizeClasses; i++) 
			if (m_allocs[i].QueryOwnsObject(item))
				return;
		
		for ( LargeObject* lo=largeObjects; lo != NULL ; lo=lo->next)
			if (lo->item == item)
				return;
		
		GCAssertMsg(false, "Trying to delete an object with FixedMalloc::Free that was not allocated with FixedMalloc::Alloc\n");
	}

	void FixedMalloc::AddToLargeObjectTracker(const void* item)
	{
		LargeObject* lo = (LargeObject*)Alloc(sizeof(LargeObject));
		lo->item = item;
		lo->next = largeObjects;
		largeObjects = lo;
	}
	
	void FixedMalloc::RemoveFromLargeObjectTracker(const void* item)
	{
		LargeObject *lo, *prev;
		for ( prev=NULL, lo=largeObjects ; lo != NULL ; prev=lo, lo=lo->next ) {
			if (lo->item == item) {
				if (prev != NULL)
					prev->next = lo->next;
				else
					largeObjects = lo->next;
				Free(lo);
				return;
			}
		}
	}
#endif
	
}

