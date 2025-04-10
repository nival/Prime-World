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

#ifndef __FixedAlloc__
#define __FixedAlloc__

namespace MMgc
{
	/**
	 * FixedAlloc is a fast, non-thread-safe, fixed-size memory allocator for manually
	 * freed objects.
	 *
	 * Memory is allocated from the system in 4096 byte chunks via the GCHeap
	 * class and then carved into smaller objects.  For larger objects we have
	 * the FixedAllocLarge allocator.  See FixedMalloc.cpp for details on
	 * the cutoffs etc.
	 */
	class FixedAlloc 
	{
		friend class FixedMalloc;
		friend class FastAllocator;
		friend class GC;

	public:
		/**
		 * Initialize the allocator.
		 *
		 * @param itemSize          The size of items managed by this allocator.
		 * @param heap              The block manager from which we obtain memory.
		 * @param isFixedAllocSafe  If true, this allocator's concrete instance
		 *                          is FixedAllocSafe, and certain unlocking operations
		 *                          will be performed in out-of-memory situations.
		 */
		FixedAlloc(uint32_t itemSize, GCHeap* heap, bool isFixedAllocSafe=false);
		
		/**
		 * Destroy the allocator, returning all blocks to the block manager.
		 * Check for and report storage leaks in MMGC_MEMORY_INFO mode.
		 */
		~FixedAlloc();

		/**
		 * Allocate one object from this allocator.
		 *
		 * @param size   The size of the object; this is used for debugging only, as the
		 *               size allocated is fixed by the allocator.
		 * @param flags  A bit vector of allocation options.
		 *
		 * @return  A pointer to the object.  The pointer may be NULL only if kCanFail is
		 *          part of flags.  The memory is zeroed only if kZero is part of flags.
		 */
		void* Alloc(size_t size, FixedMallocOpts flags=kNone);
		
		/**
		 * Free an object allocated with a FixedAlloc instance.  The object is returned
		 * to the FixedAlloc that provided it.
		 *
		 * @param item  The object to free.
		 */
		static void Free(void *item);

		/**
		 * @return the number bytes currently allocated by this FixedAlloc
		 */
		size_t GetBytesInUse();
		
		/**
		 * Obtain current (not running total) allocation information for this FixedAlloc.
		 *
		 * @param totalAsk        (out) The total number of bytes requested
		 * @param totalAllocated  (out) The number of bytes actually allocated
		 */
		void GetUsageInfo(size_t& totalAsk, size_t& totalAllocated);
		
		/**
		 * @return the size of objects managed by this allocator
		 */
		size_t GetItemSize() const;
		
		/**
		 * @return the number of objects (free and allocated) held by this allocator.
		 */
		size_t GetMaxAlloc() const;

		/**
		 * @return the number of blocks held by this allocator.
		 */
		size_t GetNumChunks();	

		/**
		 * Obtain the allocator used to allocate a particular FixedAlloc item.
		 *
		 * @param item  An object allocated with FixedAlloc.
		 *
		 * @return   The allocator used to allocate the item
		 */
		static FixedAlloc *GetFixedAlloc(void *item);

#ifdef MMGC_HEAP_GRAPH
		// used by back pointer facility to find beginning of
		// GC root derived pointers
		static const void *FindBeginning(const void *addr);
#endif

	protected:

		// A no-argument constructor used only by FixedAllocSafe
		FixedAlloc();
#ifdef _DEBUG
		bool QueryOwnsObject(const void* item);
#endif
		
	public:		// Really private, but Symbian compiler requires this structure to be public

		struct FixedBlock
		{
			void*  firstFree;        // first item on free list
			void*  nextItem;         // next free item
			FixedBlock* next;
			FixedBlock* prev;
			uint16_t numAlloc;
			uint16_t size;
			FixedBlock *prevFree;
			FixedBlock *nextFree;
			FixedAlloc *alloc;
			char   items[1];
		};

	private:

		void Init(uint32_t itemSize, GCHeap *heap);
		void Destroy();

		GCHeap *m_heap;
		uint32_t m_itemsPerBlock;
		uint32_t m_itemSize;

		// The list of chunk blocks
		FixedBlock* m_firstBlock; 
		FixedBlock* m_lastBlock;

		// The lowest priority block that has free items		
		FixedBlock* m_firstFree;

		size_t    m_maxAlloc;
	#ifdef MMGC_MEMORY_PROFILER
		size_t m_totalAskSize;
	#endif 
		bool const m_isFixedAllocSafe;

		// @return true iff there are no free items in the block.
		bool IsFull(FixedBlock *b) const;
		
		void CreateChunk(bool canFail);
		void FreeChunk(FixedBlock* b);

		// @return the FixedBlock for any item allocated by FixedAlloc
		static FixedBlock *GetFixedBlock(const void *item);

		// @return the size of any item allocated by FixedAlloc.
		static size_t Size(const void *item);

#ifdef MMGC_MEMORY_INFO
		static void VerifyFreeBlockIntegrity(const void* item, uint32_t size);
#endif

		bool IsOnFreelist(FixedBlock *b, void *item);
		bool IsInUse(FixedBlock *b, void *item);
	};

	/**
	 * FixedAlloc is a fast, thread-safe, fixed-size memory allocator for manually
	 * freed objects.
	 */
	class FixedAllocSafe : public FixedAlloc
	{
		friend class FixedAlloc;
		friend class FixedMalloc;
	public:
		FixedAllocSafe(int itemSize, GCHeap* heap);
		
		~FixedAllocSafe();

		void* Alloc(size_t size, FixedMallocOpts flags=kNone);

		void Free(void *ptr);

#ifdef _DEBUG
		bool QueryOwnsObject(const void* item);
#endif
		
		static FixedAllocSafe *GetFixedAllocSafe(void *item);

	private:
		// default ctor used only by FixedMalloc
		FixedAllocSafe();

		vmpi_spin_lock_t m_spinlock;
	};

	/**
	 * FastAllocator is a fast, non-thread-safe, fixed-size memory allocator for
	 * manually freed objects using 'new' and 'delete' operators for object management.
	 */
	class FastAllocator 
	{		
	public:
		static void *operator new(size_t size, FixedAlloc *alloc);
		static void operator delete (void *item);
		static void *operator new[](size_t size);		
		static void operator delete [](void *item);
	};
}

#endif /* __FixedAlloc__ */
