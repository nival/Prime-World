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

#ifndef __GCAlloc_inlines__
#define __GCAlloc_inlines__

// Inline functions for GCAlloc, GCAlloc::GCBlock, and GCAllocIterator

namespace MMgc
{
	REALLY_INLINE GCBlockHeader* GetBlockHeader(const void* item)
	{
		return (GCBlockHeader*)(uintptr_t(item) & ~0xFFF);
	}

	/*static*/
	REALLY_INLINE GCAlloc::GCBlock *GCAlloc::GetBlock(const void *item)
	{ 
		return (GCBlock*)GetBlockHeader(item);
	}
	
	/*static*/
	REALLY_INLINE GCAlloc::GCBlock* GCAlloc::Next(GCAlloc::GCBlock* b)
	{
		return (GCBlock*)b->next;
	}
	
	REALLY_INLINE int GCAlloc::SetMark(const void *item)
	{
		GCBlock *block = GetBlock(item);
		int index = GetIndex(block, item);
		int mask = kMark << ((index&7)<<2);
		uint32_t *bits = &block->GetBits()[index>>3];
		int set = *bits & mask;
		*bits |= mask;
		*bits &= ~(kQueued << ((index&7)<<2));
		return set;
	}

	/*static*/
	REALLY_INLINE int GCAlloc::SetFinalize(const void *item)
	{
		GCBlock *block = GetBlock(item);
		return SetBit(block, GetIndex(block, item), kFinalize);
	}

	/*static*/
	REALLY_INLINE int GCAlloc::GetMark(const void *item)
	{
		GCBlock *block = GetBlock(item);
		return GetBit(block, GetIndex(block, item), kMark);
	}

	/*static*/
	REALLY_INLINE void *GCAlloc::FindBeginning(const void *item)
	{
		GCBlock *block = GetBlock(item);
		return block->items + block->size * GetIndex(block, item);
	}

	/*static*/
	REALLY_INLINE bool GCAlloc::IsMarkedThenMakeQueued(const void *item)
	{
		GCBlock *block = GetBlock(item);
		int index = GetIndex(block, item);
		uint32_t* bits = block->GetBits() + (index >> 3);
		if (*bits & (kMark << ((index&7)<<2))) {
			*bits ^= (kMark|kQueued) << ((index&7)<<2);
			return true;
		}
		return false;
	}

	/*static*/
	REALLY_INLINE bool GCAlloc::IsQueued(const void *item)
	{
		GCBlock *block = GetBlock(item);
		int index = GetIndex(block, item);
		uint32_t* bits = block->GetBits() + (index >> 3);
		return (*bits & (kQueued << ((index&7)<<2))) != 0;
	}

	/*static*/
	REALLY_INLINE void GCAlloc::ClearFinalized(const void *item)
	{
		GCBlock *block = GetBlock(item);
		ClearBits(block, GetIndex(block, item), kFinalize);
	}		

	/*static*/
	REALLY_INLINE int GCAlloc::IsFinalized(const void *item)
	{
		GCBlock *block = GetBlock(item);
		return GetBit(block, GetIndex(block, item), kFinalize);
	}

	/*static*/
	REALLY_INLINE int GCAlloc::HasWeakRef(const void *item)
	{
		GCBlock *block = GetBlock(item);
		return GetBit(block, GetIndex(block, item), kHasWeakRef);
	}		
	
	/*static*/
	REALLY_INLINE bool GCAlloc::ContainsPointers(const void *item)
	{
		GCBlock *block = GetBlock(item);
		return block->alloc->ContainsPointers();
	}

	/*static*/
	REALLY_INLINE bool GCAlloc::IsRCObject(const void *item)
	{
		GCBlock *block = GetBlock(item);
		return item >= block->items && block->alloc->ContainsRCObjects();
	}

	/*static*/
	REALLY_INLINE void GCAlloc::SetHasWeakRef(const void *item, bool to)
	{
		GCBlock *block = GetBlock(item);
		if(to) {
			SetBit(block, GetIndex(block, item), kHasWeakRef);
		} else {
			ClearBits(block, GetIndex(block, item), kHasWeakRef);
		}
	}
	
	REALLY_INLINE void GCAlloc::AddToFreeList(GCBlock *b)
	{
		GCAssert(!IsOnEitherList(b) && !b->needsSweeping);
		b->prevFree = NULL;
		b->nextFree = m_firstFree;
		if (m_firstFree) {
			GCAssert(m_firstFree->prevFree == 0 && m_firstFree != b);
			m_firstFree->prevFree = b;
		}
		m_firstFree = b;			
	}

	REALLY_INLINE void GCAlloc::RemoveFromFreeList(GCBlock *b)
	{
		GCAssert(m_firstFree == b || b->prevFree != NULL);
		if ( m_firstFree == b )
			m_firstFree = b->nextFree;
		else
			b->prevFree->nextFree = b->nextFree;
		
		if (b->nextFree)
			b->nextFree->prevFree = b->prevFree;
		b->nextFree = b->prevFree = NULL;
	}

	REALLY_INLINE void GCAlloc::AddToSweepList(GCBlock *b)
	{
		GCAssert(!IsOnEitherList(b) && !b->needsSweeping);
		b->prevFree = NULL;
		b->nextFree = m_needsSweeping;
		if (m_needsSweeping) {
			GCAssert(m_needsSweeping->prevFree == 0);
			m_needsSweeping->prevFree = b;
		}
		m_needsSweeping = b;
		b->needsSweeping = true;
	}

	REALLY_INLINE void GCAlloc::RemoveFromSweepList(GCBlock *b)
	{
		GCAssert(m_needsSweeping == b || b->prevFree != NULL);
		if ( m_needsSweeping == b )
			m_needsSweeping = b->nextFree;
		else
			b->prevFree->nextFree = b->nextFree;
		
		if (b->nextFree)
			b->nextFree->prevFree = b->prevFree;
		b->needsSweeping = false;
		b->nextFree = b->prevFree = NULL;
	}

	/*static*/
	REALLY_INLINE int GCAlloc::GetIndex(const GCBlock *block, const void *item)
	{
		int index = (int)((((char*) item - block->items) * block->alloc->multiple) >> block->alloc->shift);
#ifdef _DEBUG
		GCAssert(((char*) item - block->items) / block->size == (uint32_t) index);
#endif
		return index;
	}			
	
	/*static*/
	REALLY_INLINE int GCAlloc::SetBit(GCBlock *block, int index, int bit)
	{
		int mask = bit << ((index&7)<<2);
		int set = (block->GetBits()[index>>3] & mask);
		block->GetBits()[index>>3] |= mask;
		return set;
	}
	
	/*static*/
	REALLY_INLINE int GCAlloc::GetBit(GCBlock *block, int index, int bit)
	{
		int mask = bit << ((index&7)<<2);
		return block->GetBits()[index>>3] & mask;
	}
	
	/*static*/
	REALLY_INLINE void GCAlloc::ClearBits(GCBlock *block, int index, int bits)
	{
		int mask = bits << ((index&7)<<2);
		block->GetBits()[index>>3] &= ~mask;
	}
	
	/*static*/
	REALLY_INLINE void GCAlloc::Clear4BitsAndSet(GCBlock *block, int index, int bit)
	{
		uint32_t *bitp = &(block->GetBits()[index>>3]);
		*bitp = (*bitp & ~(15 << ((index & 7) << 2))) | (bit << ((index & 7) << 2));
	}
	
	/*static*/
	REALLY_INLINE void GCAlloc::ClearQueued(const void *item)
	{
		GCBlock *block = GetBlock(item);
		ClearBits(block, GetIndex(block, item), kQueued);
	}
	
#ifdef _DEBUG
	/*static*/
	REALLY_INLINE bool GCAlloc::IsPointerIntoGCObject(const void *item)
	{
		GCBlock *block = GetBlock(item);
		if(item < block->items)
			return false;
		return GetBit(block, GetIndex(block, item), kFreelist) != kFreelist;
	}
	
	/*static*/
	REALLY_INLINE bool GCAlloc::IsWhite(GCBlock *block, int index)
	{
		return (block->GetBits()[index>>3] & ((kMark|kQueued)<<((index&7)<<2))) == 0;
	}

	/*static*/
	REALLY_INLINE bool GCAlloc::IsWhite(const void *item)
	{
		GCBlock *block = GetBlock(item);
		// not a real item
		if(item < block->items)
			return false;
		
		if(FindBeginning(item) != item)
			return false;
		
		return IsWhite(block, GetIndex(block, item));
	}
	
	REALLY_INLINE bool GCAlloc::IsOnEitherList(GCBlock *b)
	{
		return b->nextFree != NULL || b->prevFree != NULL || b == m_firstFree || b == m_needsSweeping;
	}
#endif // _DEBUG
	

	REALLY_INLINE int GCAlloc::GCBlock::GetCount() const
	{
		if (nextItem) {
			return GCAlloc::GetIndex(this, nextItem);
		} else {
			return alloc->m_itemsPerBlock;
		}
	}

	REALLY_INLINE uint32_t *GCAlloc::GCBlock::GetBits() const
	{
		return bits;
	}

	REALLY_INLINE bool GCAlloc::GCBlock::IsFull()
	{
		bool full = (nextItem == firstFree);
		// the only time nextItem and firstFree should be equal is when they
		// are both zero which is also when we are full, assert to be sure
		GCAssert(!full || nextItem==0);
		GCAssert(!full || numItems == alloc->m_itemsPerBlock);
		return full;
	}

	REALLY_INLINE GCAllocIterator::GCAllocIterator(MMgc::GCAlloc* alloc) 
		: alloc(alloc)
		, block(alloc->m_firstBlock)
		, idx(0)
		, limit(alloc->m_itemsPerBlock)
		, size(alloc->m_itemSize)
	{
	}
		
	REALLY_INLINE bool GCAllocIterator::GetNextMarkedObject(void*& out_ptr, uint32_t& out_size)
	{
		for (;;) {
			if (idx == limit) {
				idx = 0;
				block = GCAlloc::Next(block);
			}
			if (block == NULL)
				return false;
			uint32_t i = idx++;
			if (GCAlloc::GetBit(block, i, MMgc::GCAlloc::kMark) && !GCAlloc::GetBit(block, i, MMgc::GCAlloc::kQueued)) {
				out_ptr = GetUserPointer(block->items + i*size);
				out_size = size - (uint32_t)DebugSize();
				return true;
			}
		}
	}
}

#endif /* __GCAlloc_inlines__ */
