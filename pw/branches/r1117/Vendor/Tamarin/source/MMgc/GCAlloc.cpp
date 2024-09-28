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
	GCAlloc::GCAlloc(GC* _gc, int _itemSize, bool _containsPointers, bool _isRC, int _sizeClassIndex) : 
		m_sizeClassIndex(_sizeClassIndex),
		containsPointers(_containsPointers), 
		containsRCObjects(_isRC),
		m_gc(_gc)
	{
		// Round itemSize to the nearest boundary of 8
		_itemSize = (_itemSize+7)&~7;

		m_firstBlock    = NULL;
		m_lastBlock     = NULL;
		m_firstFree     = NULL;
		m_needsSweeping = NULL;
		m_numAlloc      = 0;
		m_maxAlloc      = 0;
		m_itemSize      = _itemSize;
		m_numBlocks = 0;
		m_finalized = false;

#ifdef MMGC_MEMORY_PROFILER
		m_totalAskSize = 0;
#endif

		// The number of items per block is kBlockSize minus
		// the # of pointers at the base of each page.

		m_itemsPerBlock = (kBlockSize - sizeof(GCBlock)) / m_itemSize;

		m_numBitmapBytes = (m_itemsPerBlock>>1) + (m_itemsPerBlock & 1);
		// round up to 4 bytes so we can go through the bits 8 items at a time
		m_numBitmapBytes = (m_numBitmapBytes+3)&~3;

		GCAssert(m_numBitmapBytes<<1 >= m_itemsPerBlock);

		int usedSpace = m_itemsPerBlock * m_itemSize + sizeof(GCBlock);
		GCAssert(usedSpace <= kBlockSize);
		GCAssert(kBlockSize - usedSpace < (int)m_itemSize);
		
		// never store the bits in the page for !containsPointers b/c we don't want
		// to force pages into memory for bit marking purposes when we don't need
		// to bring them in for scanning purposes
		// ISSUE: is this bitsInPage stuff really worth it?  Maybe simplicity and 
		// locality suggest otherwise?
		m_bitsInPage = containsPointers && kBlockSize - usedSpace >= m_numBitmapBytes;

		// compute values that let us avoid division
		GCAssert(m_itemSize <= 0xffff);
		ComputeMultiplyShift((uint16_t)m_itemSize, multiple, shift);
	}

	GCAlloc::~GCAlloc()
	{   
		// Free all of the blocks
		GCAssertMsg(GetNumAlloc() == 0, "You have leaks");

		while (m_firstBlock) {
#ifdef MMGC_MEMORY_INFO
			//check where any item within this block wasn't written to after being poisoned
			VerifyFreeBlockIntegrity(m_firstBlock->firstFree, m_firstBlock->size);
#endif //MMGC_MEMORY_INFO

			GCBlock *b = m_firstBlock;
			UnlinkChunk(b);
			FreeChunk(b);
		}
	}

	GCAlloc::GCBlock* GCAlloc::CreateChunk(int flags)
	{
		// Get space in the bitmap.  Do this before allocating the actual block,
		// since we might call GC::AllocBlock for more bitmap space and thus
		// cause some incremental marking.
		uint32_t* bits = NULL;

		if(!m_bitsInPage) {
			// Note, bits will leak if AllocBlock aborts due to OOM, but that isn't much of a problem
			bits = m_gc->GetBits(m_numBitmapBytes, m_sizeClassIndex);
		}

		// Allocate a new block

		GCAssert(uint32_t(kBlockSize) == GCHeap::kBlockSize);
		GCBlock* b = (GCBlock*) m_gc->AllocBlock(1, GC::kGCAllocPage, /*zero*/true,  (flags&GC::kCanFail) != 0);

		if (b) 
		{
			m_maxAlloc += m_itemsPerBlock;
			m_numBlocks++;

			b->firstFree = 0;
			b->gc = m_gc;
			b->alloc = this;
			b->size = m_itemSize;
			b->needsSweeping = false;
			if(m_gc->collecting && m_finalized)
				b->finalizeState = m_gc->finalizedValue;
			else 
				b->finalizeState = !m_gc->finalizedValue;
			
			union {
				char* b_8;
				uint32_t* b_32;
			};
			b_8 = (char*)b + sizeof(GCBlock);
			b->bits = m_bitsInPage ? b_32 : bits;

			// Link the block at the end of the list
			b->prev = m_lastBlock;
			b->next = 0;
			
			if (m_lastBlock) {
				m_lastBlock->next = b;
			}
			if (!m_firstBlock) {
				m_firstBlock = b;
			}
			m_lastBlock = b;

			// Add our new ChunkBlock to the firstFree list (which should be empty)
			if (m_firstFree)
			{
				GCAssert(m_firstFree->prevFree == 0);
				m_firstFree->prevFree = b;
			}
			b->nextFree = m_firstFree;
			b->prevFree = 0;
			m_firstFree = b;

			// calculate back from end (better alignment, no dead space at end)
			b->items = (char*)b+GCHeap::kBlockSize - m_itemsPerBlock * m_itemSize;
			b->nextItem = b->items;
			b->numItems = 0;
		}
		else {
			if (bits)
				m_gc->FreeBits(bits, m_sizeClassIndex);
		}

		return b;
	}

	void GCAlloc::UnlinkChunk(GCBlock *b)
	{
		GCAssert(!b->needsSweeping);
		m_maxAlloc -= m_itemsPerBlock;
		m_numBlocks--;

		// Unlink the block from the list
		if (b == m_firstBlock) {
			m_firstBlock = Next(b);
		} else {
			b->prev->next = Next(b);
		}
		
		if (b == m_lastBlock) {
			m_lastBlock = b->prev;
		} else {
			Next(b)->prev = b->prev;
		}

		if(b->nextFree || b->prevFree || b == m_firstFree) {
			RemoveFromFreeList(b);
		}
#ifdef _DEBUG
		b->next = b->prev = NULL;
		b->nextFree = b->prevFree = NULL;
#endif
	}

	void GCAlloc::FreeChunk(GCBlock* b)
	{
		GCAssert(b->numItems == 0);
		if(!m_bitsInPage) {
			VMPI_memset(b->GetBits(), 0, m_numBitmapBytes);
			m_gc->FreeBits(b->GetBits(), m_sizeClassIndex);
			b->bits = NULL;
		}

		// Free the memory
		m_gc->FreeBlock(b, 1);
	}

#if defined DEBUG || defined MMGC_MEMORY_PROFILER
	void* GCAlloc::Alloc(size_t size, int flags)
#else
	void* GCAlloc::Alloc(int flags)
#endif
	{
		GCAssertMsg(((size_t)m_itemSize >= size), "allocator itemsize too small");

		// Allocation must be signalled before we allocate because no GC work must be allowed to
		// come between an allocation and an initialization - if it does, we may crash, as 
		// GCFinalizedObject subclasses may not have a valid vtable, but the GC depends on them
		// having it.  In principle we could signal allocation late but only set the object
		// flags after signaling, but we might still cause trouble for the profiler, which also
		// depends on non-interruptibility.

		m_gc->SignalAllocWork(m_itemSize);
		
		GCBlock* b = m_firstFree;
	start:
		if (b == NULL) {
			if (m_needsSweeping && !m_gc->collecting) {
				Sweep(m_needsSweeping);
				b = m_firstFree;
				goto start;
			}
			
			bool canFail = (flags & GC::kCanFail) != 0;
			CreateChunk(canFail);
			b = m_firstFree;
			if (b == NULL) {
				GCAssert(canFail);
				return NULL;
			}
		}
		
		GCAssert(!b->needsSweeping);
		GCAssert(b == m_firstFree);
		GCAssert(b && !b->IsFull());
		
		void *item;
		if(b->firstFree) {
			item = b->firstFree;
			b->firstFree = *((void**)item);
			// clear free list pointer, the rest was zero'd in free
			*(intptr_t*) item = 0;
#ifdef MMGC_MEMORY_INFO
			//check for writes on deleted memory
			VerifyFreeBlockIntegrity(item, b->size);
#endif
		} else {
			item = b->nextItem;
			if(((uintptr_t)((char*)item + b->size) & 0xfff) != 0) {
				b->nextItem = (char*)item + b->size;
			} else {
				b->nextItem = NULL;
			}
		}

		// set up bits, items start out white and whether they need finalization
		// is determined by the caller

		// make sure we ended up in the right place
		GCAssert(((flags&GC::kContainsPointers) != 0) == ContainsPointers());

		// this assumes what we assert
		GCAssert((unsigned long)GC::kFinalize == (unsigned long)GCAlloc::kFinalize);
		
		int index = GetIndex(b, item);
		GCAssert(index >= 0);
		Clear4BitsAndSet(b, index, flags & kFinalize);

		b->numItems++;
#ifdef MMGC_MEMORY_INFO
		m_numAlloc++;
#endif

		// If we're out of free items, be sure to remove ourselves from the
		// list of blocks with free items.  TODO Minor optimization: when we
		// carve an item off the end of the block, we don't need to check here
		// unless we just set b->nextItem to NULL.

		if (b->IsFull()) {
			m_firstFree = b->nextFree;
			b->nextFree = NULL;
			GCAssert(b->prevFree == NULL);

			if (m_firstFree)
				m_firstFree->prevFree = 0;
		}

		// prevent mid-collection (ie destructor) allocations on un-swept pages from
		// getting swept.  If the page is finalized and doesn't need sweeping we don't want
		// to set the mark otherwise it will be marked when we start the next marking phase
		// and write barriers won't fire (since its black)
		if(m_gc->collecting)
		{ 
			if((b->finalizeState != m_gc->finalizedValue) || b->needsSweeping)
				SetBit(b, index, kMark);
		}

		GCAssert((uintptr_t(item) & ~0xfff) == (uintptr_t) b);
		GCAssert((uintptr_t(item) & 7) == 0);

#ifdef MMGC_HOOKS
		GCHeap* heap = GCHeap::GetGCHeap();
		if(heap->HooksEnabled())
		{
			size_t userSize = m_itemSize - DebugSize();
#ifdef MMGC_MEMORY_PROFILER
			m_totalAskSize += size;
			heap->AllocHook(GetUserPointer(item), size, userSize);
#else
			heap->AllocHook(GetUserPointer(item), 0, userSize);
#endif
		}
#endif

		return item;
	}

	/* static */
	void GCAlloc::Free(const void *item)
	{
		GCBlock *b = GetBlock(item);
		GCAlloc *a = b->alloc;
	
#ifdef MMGC_HOOKS
		GCHeap* heap = GCHeap::GetGCHeap();
		if(heap->HooksEnabled())
		{
			const void* p = GetUserPointer(item);
			size_t userSize = GC::Size(p);
#ifdef MMGC_MEMORY_PROFILER
			if(heap->GetProfiler())
				a->m_totalAskSize -= heap->GetProfiler()->GetAskSize(p);
#endif
			heap->FinalizeHook(p, userSize);
			heap->FreeHook(p, userSize, 0xca);
		}
#endif

#ifdef _DEBUG		
		// check that its not already been freed
		void *free = b->firstFree;
		while(free) {
			GCAssert(free != item);
			free = *((void**) free);
		}
#endif

		int index = GetIndex(b, item);
		if(GetBit(b, index, kHasWeakRef)) {
			b->gc->ClearWeakRef(GetUserPointer(item));
		}

		bool wasFull = b->IsFull();

		if(b->needsSweeping) {
#ifdef _DEBUG
			bool gone =
#endif
				a->Sweep(b);
			GCAssertMsg(!gone, "How can a page I'm about to free an item on be empty?");
			wasFull = false;
		}

		if(wasFull) {
			a->AddToFreeList(b);
		}

		b->FreeItem(item, index);

		if(b->numItems == 0) {
			a->UnlinkChunk(b);
			a->FreeChunk(b);
		}
	}

	void GCAlloc::Finalize()
	{
		m_finalized = true;
		// Go through every item of every block.  Look for items
		// that are in use but not marked as reachable, and delete
		// them.
		
		GCBlock *next = NULL;
		for (GCBlock* b = m_firstBlock; b != NULL; b = next)
		{
			// we can unlink block below
			next = Next(b);

			GCAssert(!b->needsSweeping);

			// remove from freelist to avoid mutator destructor allocations
			// from using this block
			bool putOnFreeList = false;
			if(m_firstFree == b || b->prevFree != NULL || b->nextFree != NULL) {
				putOnFreeList = true;
				RemoveFromFreeList(b);
			}

			GCAssert(kMark == 0x1 && kFinalize == 0x4 && kHasWeakRef == 0x8);

			int numMarkedItems = 0;

			// TODO: MMX version for IA32
			uint32_t *bits = (uint32_t*) b->GetBits();
			uint32_t count = b->nextItem ? GetIndex(b, b->nextItem) : m_itemsPerBlock;
			// round up to eight
			uint32_t numInts = ((count+7)&~7) >> 3;
			for(uint32_t i=0; i < numInts; i++) 
			{
				uint32_t marks = bits[i];					
				// hmm, is it better to screw around with exact counts or just examine
				// 8 items on each pass, with the later we open the door to unrolling
				uint32_t subCount = i==(numInts-1) ? ((count-1)&7)+1 : 8;
				for(uint32_t j=0; j<subCount;j++,marks>>=4)
				{
					int mq = marks & kFreelist;
					if(mq == kFreelist)
						continue;

					if(mq == kMark) {
						numMarkedItems++;
						continue;
					}

					GCAssertMsg(mq != kQueued, "No queued objects should exist when finalizing");

					void* item = (char*)b->items + m_itemSize*((i*8)+j);

#ifdef MMGC_HOOKS
					if(m_gc->heap->HooksEnabled())
					{
					#ifdef MMGC_MEMORY_PROFILER
						if(m_gc->heap->GetProfiler())
							m_totalAskSize -= m_gc->heap->GetProfiler()->GetAskSize(GetUserPointer(item));
					#endif

 						m_gc->heap->FinalizeHook(GetUserPointer(item), m_itemSize - DebugSize());
					}
#endif

					if(!(marks & (kFinalize|kHasWeakRef)))
						continue;
        
					if (marks & kFinalize)
					{     
						GCFinalizedObject *obj = (GCFinalizedObject*)GetUserPointer(item);
						GCAssert(*(intptr_t*)obj != 0);
						bits[i] &= ~(kFinalize<<(j*4));		// Clear bits first so we won't get second finalization if finalizer longjmps out
						obj->~GCFinalizedObject();

#if defined(_DEBUG)
						if(b->alloc->ContainsRCObjects()) {
							m_gc->RCObjectZeroCheck((RCObject*)obj);
						}
#endif
					}

					if (marks & kHasWeakRef) {							
						b->gc->ClearWeakRef(GetUserPointer(item));
					}
				}
			}

			// 3 outcomes:
			// 1) empty, put on list of empty pages
			// 2) no freed items, partially empty or full, return to free if partially empty
			// 3) some freed item add to the to be swept list
			if(numMarkedItems == 0) {
				// add to list of block to be returned to the Heap after finalization
				// we don't do this during finalization b/c we want finalizers to be able
				// to reference the memory of other objects being finalized
				UnlinkChunk(b);
				b->gc->AddToSmallEmptyBlockList(b);
				putOnFreeList = false;
			} else if(numMarkedItems == b->numItems) {
				// nothing changed on this page, clear marks
				// note there will be at least one free item on the page (otherwise it
				// would not have been scanned) so the page just stays on the freelist
				ClearMarks(b);
			} else if(!b->needsSweeping) {
				// free'ing some items but not all
				if(b->nextFree || b->prevFree || b == m_firstFree) {
					RemoveFromFreeList(b);
					b->nextFree = b->prevFree = NULL;
				}
				AddToSweepList(b);
				putOnFreeList = false;
			}
			b->finalizeState = m_gc->finalizedValue;
			if(putOnFreeList)
				AddToFreeList(b);
		}
	}

	void GCAlloc::SweepGuts(GCBlock *b)
	{	
		// TODO: MMX version for IA32
		uint32_t *bits = (uint32_t*) b->GetBits();
		uint32_t count = b->nextItem ? GetIndex(b, b->nextItem) : m_itemsPerBlock;
		// round up to eight
		uint32_t numInts = ((count+7)&~7) >> 3;
		for(uint32_t i=0; i < numInts; i++) 
		{
			uint32_t marks = bits[i];
			// hmm, is it better to screw around with exact counts or just examine
			// 8 items on each pass, with the later we open the door to unrolling
			uint32_t subCount = i==(numInts-1) ? ((count-1)&7)+1 : 8;
			for(uint32_t j=0; j<subCount;j++,marks>>=4)
			{
				int mq = marks & kFreelist;
				if(mq == kMark || mq == kQueued)	// Sweeping is lazy; don't sweep objects on the mark stack
				{
					// live item, clear bits
					bits[i] &= ~(kFreelist<<(j*4));
					continue;					
				}

				 if(mq == kFreelist)
					 continue; // freelist item, ignore

				// garbage, freelist it
				void *item = (char*)b->items + m_itemSize*(i*8+j);
#ifdef MMGC_HOOKS
				if(m_gc->heap->HooksEnabled())
					m_gc->heap->FreeHook(GetUserPointer(item), b->size - DebugSize(), 0xba);
#endif
				b->FreeItem(item, (i*8+j));
			}
		}
	}

	bool GCAlloc::Sweep(GCBlock *b)
	{	
		GCAssert(b->needsSweeping);
		RemoveFromSweepList(b);

		SweepGuts(b);

		if(b->numItems == 0)
		{
			UnlinkChunk(b);
			FreeChunk(b);
			return true;
		} 

		AddToFreeList(b);

		return false;
	}
		
	void GCAlloc::SweepNeedsSweeping()
	{
		GCBlock* next;
		for (GCBlock* b = m_needsSweeping; b != NULL; b = next)
		{
			next = b->nextFree;	
			Sweep(b);
		}
		GCAssert(m_needsSweeping == NULL);
	}

	void GCAlloc::ClearMarks(GCAlloc::GCBlock* block)
	{
        // Clear all the mark bits
		uint32_t *pbits = block->GetBits();
		const static uint32_t mq32 = 0x33333333;
		GCAssert((kMark|kQueued) == 0x3);
		// TODO: MMX version for IA32
		for(int i=0, n=m_numBitmapBytes>>2; i < n; i++) {
			pbits[i] &= ~mq32;
        }
		
		const void *item = block->firstFree;
		while(item != NULL) {
			// set freelist bit pattern
			SetBit(block, GetIndex(block, item), kFreelist);
			item = *(const void**)item;
		}
	}

	void GCAlloc::ClearMarks()
	{
		for ( GCBlock *block=m_firstBlock, *next ; block ; block=next ) {
			next = Next(block);
			
			if (block->needsSweeping && Sweep(block)) 
				continue;

			ClearMarks(block);
		}
	}	

#ifdef _DEBUG
	void GCAlloc::CheckMarks()
	{
		GCBlock *b = m_firstBlock;

		while (b) {
			GCBlock *next = Next(b);
			GCAssertMsg(!b->needsSweeping, "All needsSweeping should have been swept at this point.");

			// TODO: MMX version for IA32
			uint32_t *bits = b->GetBits();
			uint32_t count = b->nextItem ? GetIndex(b, b->nextItem) : m_itemsPerBlock;

			// round up to eight
			uint32_t numInts = ((count+7)&~7) >> 3;
			for(uint32_t i=0; i < numInts; i++) 
			{
				uint32_t marks = bits[i];
				// hmm, is it better to screw around with exact counts or just examine
				// 8 items on each pass, with the later we open the door to unrolling
				uint32_t subCount = i==(numInts-1) ? ((count-1)&7)+1 : 8;
				for(uint32_t j=0; j<subCount;j++,marks>>=4)
				{
					uint32_t m = marks&kFreelist;
					GCAssertMsg(m == 0 || m == kFreelist, "All items should be free or clear, nothing should be marked or queued.");
				}
			}
			
			// Advance to next block
			b = next;
		}
	}	

	/*static*/
	int GCAlloc::ConservativeGetMark(const void *item, bool bogusPointerReturnValue)
	{
		GCBlock *block = GetBlock(item);

#ifdef MMGC_MEMORY_INFO
		item = GetRealPointer(item);
#endif

		// guard against bogus pointers to the block header
		if (item < block->items)
			return bogusPointerReturnValue;

		// floor value to start of item
		// FIXME: do this w/o division if we can
		int itemNum = GetIndex(block, item);

		// skip pointers into dead space at end of block
		if (itemNum > block->alloc->m_itemsPerBlock - 1)
			return bogusPointerReturnValue;

		// skip pointers into objects
		if(block->items + itemNum * block->size != item)
			return bogusPointerReturnValue;

		return GetMark(item);
	}
	
	void GCAlloc::CheckFreelist()
	{	
		GCBlock *b = m_firstFree;
		while(b)
		{
			void *freelist = b->firstFree;
			while(freelist)
			{			
				// b->firstFree should be either 0 end of free list or a pointer into b, otherwise, someone
				// wrote to freed memory and hosed our freelist
				GCAssert(freelist == 0 || ((uintptr_t) freelist >= (uintptr_t) b->items && (uintptr_t) freelist < (uintptr_t) b + GCHeap::kBlockSize));
				freelist = *((void**)freelist);
			}
			b = b->nextFree;
		}
	}
	
#endif // _DEBUG
	
	// allows us to avoid division in GetItemIndex, kudos to Tinic
	void GCAlloc::ComputeMultiplyShift(uint16_t d, uint16_t &muli, uint16_t &shft) 
	{
		uint32_t s = 0;
		uint32_t n = 0;
		uint32_t m = 0;
		for ( ; n < ( 1 << 13 ) ; s++) {
			m = n;
			n = ( ( 1 << ( s + 1 ) ) / d ) + 1;
		}
		shft = (uint16_t) s - 1;
		muli = (uint16_t) m;
	}

	REALLY_INLINE void GCAlloc::GCBlock::FreeItem(const void *item, int index)
	{
#ifdef MMGC_MEMORY_INFO
		GCAssert(alloc->m_numAlloc != 0);
#endif

#ifdef _DEBUG		
		// check that its not already been freed
		void *free = firstFree;
		while(free) {
			GCAssert(free != item);
			free = *((void**) free);
		}
#endif

		void *oldFree = firstFree;
		firstFree = (void*)item;
#ifdef MMGC_MEMORY_INFO
		alloc->m_numAlloc--;
#endif
		numItems--;

		GCAssert(!GetBit(this, index, kQueued));
		SetBit(this, index, kFreelist);

#ifndef _DEBUG
		// memset rest of item not including free list pointer, in _DEBUG
		// we poison the memory (and clear in Alloc)
		// FIXME: can we do something faster with MMX here?
		//
		// BTW, experiments show that clearing on alloc instead of on free 
		// benefits microbenchmark that do massive amounts of double-boxing,
		// but nothing else enough to worry about it.  (The trick is that
		// no clearing on alloc is needed when carving objects off the end
		// of a block, whereas every object is cleared on free even if the
		// page is subsequently emptied out and returned to the block manager.
		// Massively boxing programs have alloc/free patterns that are biased
		// toward non-RC objects carved off the ends of blocks.)
		if(!alloc->ContainsRCObjects())
			VMPI_memset((char*)item, 0, size);
#endif
		// Add this item to the free list
		*((void**)item) = oldFree;	
	}
	
	void GCAlloc::GetUsageInfo(size_t& totalAskSize, size_t& totalAllocated)	
	{
		totalAskSize = totalAllocated = 0;

		GCBlock *b=m_firstBlock;
		while (b) {
			totalAllocated += b->numItems * m_itemSize;
			b = Next(b);
		}		
	
#ifdef MMGC_MEMORY_PROFILER
		totalAskSize = m_totalAskSize;
#endif
	}

#ifdef MMGC_MEMORY_INFO

	/* static */
	void GCAlloc::VerifyFreeBlockIntegrity(const void* item, uint32_t size)
	{
		// go through every item on the free list and make sure it wasn't written to
		// after being poisoned.
		while(item) 
		{
#ifdef MMGC_64BIT
			int n = (size >> 2) - 3;
#else
			int n = (size >> 2) - 1;
#endif

			int startIndex = (int)((uint32_t*)item - (uint32_t*)GetRealPointer(item));

			for(int i=startIndex; i<n; i++)
			{
				uint32_t data = ((uint32_t*)item)[i];
				if(data != 0xbabababa && data != 0xcacacaca)
				{
					ReportDeletedMemoryWrite(item);
					break;
				}
			}
			// next free item
			item = *((const void**)item);
		}
	}

#endif //MMGC_MEMORY_INFO
}
