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

#ifndef __FixedMalloc_inlines__
#define __FixedMalloc_inlines__

// Inline function definitions for FixedMalloc.

namespace MMgc
{
	/*static*/
	REALLY_INLINE FixedMalloc* FixedMalloc::GetInstance() { return instance; }

	/*static*/
	REALLY_INLINE FixedMalloc* FixedMalloc::GetFixedMalloc() { return instance; }

	REALLY_INLINE void* FixedMalloc::Alloc(size_t size, FixedMallocOpts flags)
	{
		// Observe that no size overflow check is needed for small allocations;
		// the large-object allocator performs the necessary checking in that case.

		if (size <= (size_t)kLargestAlloc) {
			return FindSizeClass(size)->Alloc(size, flags);
		} else {
			return LargeAlloc(size, flags);
		}
	}

	REALLY_INLINE void *FixedMalloc::PleaseAlloc(size_t size)
	{	
		return Alloc(size, kCanFail);
	}

	REALLY_INLINE void FixedMalloc::Free(void *item)
	{
		if(item == 0)
			return;

#ifdef _DEBUG
		EnsureFixedMallocMemory(item);
#endif

		// small things are never allocated on the 4K boundary b/c the block
		// header structure is stored there, large things always are		
		if(IsLargeAlloc(item)) {
			LargeFree(item);
		} else {		
			FixedAllocSafe::GetFixedAllocSafe(item)->Free(item);
		}
	}

	REALLY_INLINE size_t FixedMalloc::Size(const void *item)
	{
		size_t size;
		if(IsLargeAlloc(item)) {
			size = LargeSize(item);
		} else {		
			size = FixedAlloc::Size(item);
		}
#ifdef MMGC_MEMORY_INFO
		size -= DebugSize();
#endif
		return size;
	}

	REALLY_INLINE size_t FixedMalloc::GetBytesInUse()
	{
		size_t totalAskSize, totalAllocated;  
		GetUsageInfo(totalAskSize, totalAllocated);
		return totalAllocated;			
	}

	/*static*/ 
	REALLY_INLINE bool FixedMalloc::IsLargeAlloc(const void *item)
	{
		// space made in ctor
		item = GetRealPointer(item);
		return ((uintptr_t) item & 0xFFF) == 0;
	}

	REALLY_INLINE FixedAllocSafe* FixedMalloc::FindSizeClass(size_t size)
	{
		GCAssertMsg(size > 0, "cannot allocate a 0 sized block\n");

#ifdef _DEBUG
		uint32_t const size8 = (uint32_t)((size+7)&~7); // round up to multiple of 8
		GCAssert((size8 >> 3) < kMaxSizeClassIndex);
		GCAssert(size8 <= (uint32_t)kLargestAlloc);
#endif

		// index is (conceptually) "(size8>>3)" but this allows
		// us to skip the &~7 that is redundant for nondebug builds...
#ifdef MMGC_64BIT
		unsigned const index = kSizeClassIndex[((size+7)>>3)];
#else
		// first bucket is 4 on 32-bit, so just special case that rather than
		// double the size-class-index table
		unsigned const index = (size <= 4) ? 0 : kSizeClassIndex[((size+7)>>3)];
#endif

		// assert that I fit
		GCAssert(size <= m_allocs[index].GetItemSize());

		// assert that I don't fit (makes sure we don't waste space
		GCAssert(index == 0 || size > m_allocs[index-1].GetItemSize());

		return &m_allocs[index];
	}

}

#endif /* __FixedMalloc_inlines__ */
