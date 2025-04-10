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
	GCLargeAlloc::GCLargeAlloc(GC* gc) : m_gc(gc)
	{
		m_blocks = NULL;
		m_startedFinalize = false;
#ifdef MMGC_MEMORY_PROFILER
		m_totalAskSize = 0;
#endif
	}

#if defined DEBUG || defined MMGC_MEMORY_PROFILER
	void* GCLargeAlloc::Alloc(size_t originalSize, size_t requestSize, int flags)
#else
	void* GCLargeAlloc::Alloc(size_t requestSize, int flags)
#endif
	{
		GCHeap::CheckForAllocSizeOverflow(requestSize, sizeof(LargeBlock)+GCHeap::kBlockSize);

		int blocks = (int)((requestSize+sizeof(LargeBlock)+GCHeap::kBlockSize-1) / GCHeap::kBlockSize);
		uint32_t computedSize = blocks*GCHeap::kBlockSize - sizeof(LargeBlock);
		
		// Allocation must be signalled before we allocate because no GC work must be allowed to
		// come between an allocation and an initialization - if it does, we may crash, as 
		// GCFinalizedObject subclasses may not have a valid vtable, but the GC depends on them
		// having it.  In principle we could signal allocation late but only set the object
		// flags after signaling, but we might still cause trouble for the profiler, which also
		// depends on non-interruptibility.

		m_gc->SignalAllocWork(computedSize);
		
		LargeBlock *block = (LargeBlock*) m_gc->AllocBlock(blocks, GC::kGCLargeAllocPageFirst, 
														   (flags&GC::kZero) != 0, (flags&GC::kCanFail) != 0);
		void *item = NULL;

		if (block)
		{
			block->flags = ((flags&GC::kFinalize) != 0) ? kFinalizeFlag : 0;
			block->flags |= ((flags&GC::kContainsPointers) != 0) ? kContainsPointers : 0;
			block->flags |= ((flags&GC::kRCObject) != 0) ? kRCObject : 0;
			block->gc = this->m_gc;
			block->next = m_blocks;
			block->size = computedSize;
			m_blocks = block;
			
			item = (void*)(block+1);

			if(m_gc->collecting && !m_startedFinalize)
				block->flags |= kMarkFlag;

#ifdef _DEBUG
			(void)originalSize;
			if (flags & GC::kZero)
			{
				// AllocBlock should take care of this
				for(int i=0, n=(int)(requestSize/sizeof(int)); i<n; i++) {
					if(((int*)item)[i] != 0)
						GCAssert(false);
				}
			}
#endif

#ifdef MMGC_HOOKS
			GCHeap* heap = GCHeap::GetGCHeap();
			if(heap->HooksEnabled()) {
				size_t userSize = block->size - DebugSize();
#ifdef MMGC_MEMORY_PROFILER
				m_totalAskSize += originalSize;
				heap->AllocHook(GetUserPointer(item), originalSize, userSize);
#else
				heap->AllocHook(GetUserPointer(item), 0, userSize);
#endif
			}
#endif
		}
		return item;
	}

	
	void GCLargeAlloc::Free(const void *item)
	{
		GCAssertMsg(!m_startedFinalize, "GCLargeAlloc::Free is not allowed during finalization; caller must guard against this.");

		LargeBlock *b = GetLargeBlock(item);

#ifdef MMGC_HOOKS
		GCHeap* heap = GCHeap::GetGCHeap();
		if(heap->HooksEnabled())
		{
			const void* p = GetUserPointer(item);
			size_t userSize = GC::Size(p);
			heap->FreeHook(p, userSize, 0xca);
#ifdef MMGC_MEMORY_PROFILER
			if(heap->GetProfiler())
				m_totalAskSize -= heap->GetProfiler()->GetAskSize(p);
#endif
			heap->FinalizeHook(p, userSize);
		}
#endif

		if(b->flags & kHasWeakRef)
			b->gc->ClearWeakRef(GetUserPointer(item));

		LargeBlock **prev = &m_blocks;
		while(*prev)
		{
			if(b == *prev)
			{
				*prev = Next(b);
				m_gc->FreeBlock(b, b->GetNumBlocks());
				return;
			}
			prev = (LargeBlock**)(&(*prev)->next);
		}
		GCAssertMsg(false, "Bad free!");
	}

	void GCLargeAlloc::ClearMarks()
	{
		LargeBlock *block = m_blocks;
		while (block) {
			block->flags &= ~(kMarkFlag|kQueuedFlag);
			block = Next(block);
		}
	}

	void GCLargeAlloc::Finalize()
	{
		m_startedFinalize = true;
		LargeBlock **prev = &m_blocks;
		while (*prev) {			
			LargeBlock *b = *prev;
			if ((b->flags & kMarkFlag) == 0) {
				GCAssert((b->flags & kQueuedFlag) == 0);
				GC* gc = b->gc;
				
				// Large blocks may be allocated by finalizers for large blocks, creating contention
				// for the block list.  Yet the block list must be live, since eg GetUsageInfo may be
				// called by the finalizers (or their callees).
				//
				// Unlink the block from the list early to avoid contention.
				
				*prev = Next(b);
				b->next = NULL;

				void *item = b+1;
				if (NeedsFinalize(b)) {
					GCFinalizedObject *obj = (GCFinalizedObject *) item;
					obj = (GCFinalizedObject *) GetUserPointer(obj);
					obj->~GCFinalizedObject();
#if defined(_DEBUG)
					if((b->flags & kRCObject) != 0) {
						gc->RCObjectZeroCheck((RCObject*)obj);
					}
#endif
				}
				if(b->flags & kHasWeakRef) {
					gc->ClearWeakRef(GetUserPointer(item));
				}
				
#ifdef MMGC_HOOKS
				if(m_gc->heap->HooksEnabled())
				{
				#ifdef MMGC_MEMORY_PROFILER
					if(GCHeap::GetGCHeap()->GetProfiler())
						m_totalAskSize -= GCHeap::GetGCHeap()->GetProfiler()->GetAskSize(GetUserPointer(item));
				#endif

					m_gc->heap->FinalizeHook(GetUserPointer(item), b->size - DebugSize());
				}
#endif
				
				// The block is not empty until now, so now add it.
				gc->AddToLargeEmptyBlockList(b);
				continue;
			}
			// clear marks
			b->flags &= ~(kMarkFlag|kQueuedFlag);
			prev = (LargeBlock**)(&b->next);
		}
		m_startedFinalize = false;
	}

	GCLargeAlloc::~GCLargeAlloc()
	{
		GCAssert(!m_blocks);
	}

#ifdef _DEBUG
	/* static */
	bool GCLargeAlloc::ConservativeGetMark(const void *item, bool bogusPointerReturnValue)
	{
		if(((uintptr_t) item & 0xfff) == sizeof(LargeBlock))
		{
			return GetMark(item);
		}
		return bogusPointerReturnValue;
	}
#endif
	
	void GCLargeAlloc::GetUsageInfo(size_t& totalAskSize, size_t& totalAllocated)
	{
		totalAskSize = 0;
		totalAllocated = 0;

		LargeBlock *block = m_blocks;
		while (block) {
			totalAllocated += block->size;
			block = Next(block);
		}		
	
#ifdef MMGC_MEMORY_PROFILER
		totalAskSize += m_totalAskSize;
#endif
	}
}
