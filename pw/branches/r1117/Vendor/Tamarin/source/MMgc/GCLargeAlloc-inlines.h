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

#ifndef __GCLargeAlloc_inlines__
#define __GCLargeAlloc_inlines__

namespace MMgc
{
	/*static*/
	REALLY_INLINE GCLargeAlloc::LargeBlock* GCLargeAlloc::GetLargeBlock(const void *addr)
	{
		return (LargeBlock*)GetBlockHeader(addr);
	}
	
	/*static*/
	REALLY_INLINE GCLargeAlloc::LargeBlock* GCLargeAlloc::Next(LargeBlock* b)
	{
		return (LargeBlock*)b->next;
	}
	
	/*static*/
	REALLY_INLINE void GCLargeAlloc::SetHasWeakRef(const void *item, bool to)
	{
		if(to) {
			GetLargeBlock(item)->flags |= kHasWeakRef;
		} else {
			GetLargeBlock(item)->flags &= ~kHasWeakRef;
		}
	}

	/*static*/
	REALLY_INLINE bool GCLargeAlloc::HasWeakRef(const void *item)
	{
		return (GetLargeBlock(item)->flags & kHasWeakRef) != 0;
	}

	/*static*/
	REALLY_INLINE bool GCLargeAlloc::IsLargeBlock(const void *item)
	{
		// The pointer should be 4K aligned plus 16 bytes
		// Mac inserts 16 bytes for new[] so make it more general
		return (((uintptr_t)item & 0xFFF) == sizeof(LargeBlock));
	}

	/*static*/
	REALLY_INLINE bool GCLargeAlloc::SetMark(const void *item)
	{
		LargeBlock *block = GetLargeBlock(item);
		bool oldMark = (block->flags & kMarkFlag) != 0;
		block->flags |= kMarkFlag;
		block->flags &= ~kQueuedFlag;
		return oldMark;
	}

	/*static*/
	REALLY_INLINE void GCLargeAlloc::SetFinalize(const void *item)
	{
		LargeBlock *block = GetLargeBlock(item);
		block->flags |= kFinalizeFlag;
	}
	
	/*static*/
	REALLY_INLINE bool GCLargeAlloc::GetMark(const void *item)
	{
		LargeBlock *block = GetLargeBlock(item);
		return (block->flags & kMarkFlag) != 0;
	}

#ifdef _DEBUG
	/*static*/
	REALLY_INLINE bool GCLargeAlloc::IsWhite(const void *item)
	{
		LargeBlock *block = GetLargeBlock(item);
		if(!IsLargeBlock(item))
			return false;
		return (block->flags & (kMarkFlag|kQueuedFlag)) == 0;
	}
#endif

	/*static*/
	REALLY_INLINE bool GCLargeAlloc::IsMarkedThenMakeQueued(const void *item)
	{
		LargeBlock *block = GetLargeBlock(item);
		if ((block->flags & kMarkFlag) != 0) {
			block->flags ^= kMarkFlag|kQueuedFlag;
			return true;
		}
		return false;
	}

	/*static*/
	REALLY_INLINE bool GCLargeAlloc::IsQueued(const void *item)
	{
		LargeBlock *block = GetLargeBlock(item);
		return (block->flags & kQueuedFlag) != 0;
	}

	/*static*/
	REALLY_INLINE void* GCLargeAlloc::FindBeginning(const void *item)
	{
		LargeBlock *block = GetLargeBlock(item);
		return (void*) (block+1);
	}

	/*static*/
	REALLY_INLINE void GCLargeAlloc::ClearFinalized(const void *item)
	{
		LargeBlock *block = GetLargeBlock(item);
		block->flags &= ~kFinalizeFlag;
	}

	/*static*/
	REALLY_INLINE bool GCLargeAlloc::ContainsPointers(const void *item)
	{
		LargeBlock *block = GetLargeBlock(item);
		return (block->flags & kContainsPointers) != 0;
	}
	
	/*static*/
	REALLY_INLINE bool GCLargeAlloc::IsFinalized(const void *item)
	{
		LargeBlock *block = GetLargeBlock(item);
		return (block->flags & kFinalizeFlag) != 0;
	}

	/*static*/
	REALLY_INLINE bool GCLargeAlloc::IsRCObject(const void *item)
	{
		LargeBlock *block = GetLargeBlock(item);
		return (block->flags & kRCObject) != 0;
	}

	/*static*/
	REALLY_INLINE bool GCLargeAlloc::NeedsFinalize(LargeBlock *block)
	{
		return (block->flags & kFinalizeFlag) != 0;
	}			
	
	/*static*/
	REALLY_INLINE void GCLargeAlloc::ClearQueued(const void *item)
	{
		LargeBlock *block = GetLargeBlock(item);
		block->flags &= ~kQueuedFlag;
	}
	
	REALLY_INLINE int GCLargeAlloc::LargeBlock::GetNumBlocks() const
	{
		return (size + sizeof(LargeBlock)) / GCHeap::kBlockSize;
	}

	REALLY_INLINE GCLargeAllocIterator::GCLargeAllocIterator(MMgc::GCLargeAlloc* alloc) 
		: alloc(alloc)
		, block(alloc->m_blocks)
	{
	}

	REALLY_INLINE bool GCLargeAllocIterator::GetNextMarkedObject(void*& out_ptr, uint32_t& out_size)
	{
		while (block != NULL) {
			GCLargeAlloc::LargeBlock* b = block;
			block = GCLargeAlloc::Next(block);
			if ((b->flags & (GCLargeAlloc::kContainsPointers|GCLargeAlloc::kMarkFlag)) == (GCLargeAlloc::kContainsPointers|GCLargeAlloc::kMarkFlag)) {
				out_ptr = GetUserPointer(b+1);
				out_size = b->size - (uint32_t)DebugSize();
				return true;
			}
		}
		return false;
	}
}

#endif /* __GCLargeAlloc_inlines__ */
