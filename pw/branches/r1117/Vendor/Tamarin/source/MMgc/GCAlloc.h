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

#ifndef __GCAlloc__
#define __GCAlloc__


namespace MMgc
{
	// Some common functionality for GCAlloc and GCLargeAlloc follows.  (Could be
	// in a separate header file.)
	
	/**
	 * Common block header for GCAlloc and GCLargeAlloc.
	 */
	struct GCBlockHeader
	{
		GC*				gc;		// The GC that owns this block
		GCBlockHeader*	next;	// The next block in the list of blocks for the allocator
		uint32_t		size;	// Size of objects stored in this block
	};
	
	GCBlockHeader* GetBlockHeader(const void* item);

	/**
	 *
	 * This is a fast, fixed-size memory allocator for garbage-collected
	 * objects.
	 *
	 * Memory is allocated from the system on 4096-byte aligned boundaries,
	 * which corresponds to the size of an OS page in Windows XP.  Allocation
	 * of pages is performed via the GCPageAlloc class.
	 *
	 * In each 4096-byte block, there is a block header with marked bits,
	 * finalize bits, the pointer to the next free item and "recycling"
	 * free item linked list.
	 *
	 * The bits of the "marked" bitmap are controlled by the SetMark method.
	 *
	 * The bits of the "finalize" bitmap are set when an item is
	 * allocated.  The value for the finalize bit is passed in as a
	 * parameter to the allocation call.
	 *
	 * When the Sweep method is invoked, all objects that are not marked
	 * with the specified mark flag are disposed of.  If the corresponding
	 * finalize bit is set, the GCObject destructor is invoked on that
	 * item.
	 *
	 * When an allocation is requested and there are no more free
	 * entries, GCAlloc will request that a garbage collection take
	 * place.  It will allocate new blocks if more than 20% of its
	 * blocks are used after the collection, targeting a 5:1
	 * heap size / minimim heap size ratio.
	 * 
	 */
	class GCAlloc 
	{
		friend class GC;
		friend class GCAllocIterator;
	public:
		enum ItemBit { kMark=1, kQueued=2, kFinalize=4, kHasWeakRef=8, kFreelist=kMark|kQueued };

		GCAlloc(GC* gc, int itemSize, bool containsPointers, bool isRC, int sizeClassIndex);
		~GCAlloc();
		
#if defined DEBUG || defined MMGC_MEMORY_PROFILER
		void* Alloc(size_t size, int flags);
#else
		void* Alloc(int flags);
#endif
		static void Free(const void *ptr);
		
		void Finalize();
		void ClearMarks();
#ifdef _DEBUG
		void CheckMarks();
		void CheckFreelist();
#endif

		static int SetMark(const void *item);

		// Not a hot method
		static int SetFinalize(const void *item);
		
#ifdef _DEBUG
		static bool IsWhite(const void *item);
#endif // _DEBUG

		static int GetMark(const void *item);

		static void *FindBeginning(const void *item);

		static bool IsMarkedThenMakeQueued(const void *item);

		static bool IsQueued(const void *item);

		// not a hot method
		static void ClearFinalized(const void *item);

		// not a hot method
		static int IsFinalized(const void *item);

		// not a hot method
		static int HasWeakRef(const void *item);
		
		// Very hot: called in the inner loop of GC::MarkItem
		static bool ContainsPointers(const void *item);

		// Can be hot - used by PinStackObjects
		static bool IsRCObject(const void *item);

		static bool IsUnmarkedPointer(const void *val);
		
		REALLY_INLINE uint32_t GetItemSize() { return m_itemSize; }
		REALLY_INLINE int GetNumAlloc() const { return m_numAlloc; }
		REALLY_INLINE int GetMaxAlloc() const { return m_maxAlloc; }
		REALLY_INLINE int GetNumBlocks() const { return m_numBlocks; }

		REALLY_INLINE bool ContainsPointers() const { return containsPointers; }
		REALLY_INLINE bool ContainsRCObjects() const { return containsRCObjects; }

		void GetBitsPages(void **pages);

		// not a hot method
		static void SetHasWeakRef(const void *item, bool to);

		//This method returns the number bytes allocated for GC objects
		size_t GetBytesInUse();
		
		//This method is for more fine grained allocation details
		//It reports the total number of bytes requested (i.e. ask size) and
		//the number of bytes actually allocated.  The latter is the same
		//number as reported by GetBytesInUse()
		void GetUsageInfo(size_t& totalAskSize, size_t& totalAllocated);
		
#ifdef MMGC_MEMORY_PROFILER	
		size_t GetTotalAskSize() { return m_totalAskSize; }
#endif

	private:
		const static int kBlockSize = 4096;

		struct GCBlock : GCBlockHeader
		{
			GCAlloc *alloc;			
			GCBlock* prev;
			char*  nextItem;
			void*  firstFree;        // first item on free list
			GCBlock *prevFree;
			GCBlock *nextFree;
			uint32_t* bits;
			short numItems;
			bool needsSweeping:1; 
			bool finalizeState:1;  // whether we've been visited during the Finalize stage
			char   *items;

			int GetCount() const;

			uint32_t *GetBits() const;

			void FreeItem(const void *item, int index);

			bool IsFull();
		};
		
		static GCBlock *GetBlock(const void *item);
		
#ifdef MMGC_MEMORY_INFO
		static void VerifyFreeBlockIntegrity(const void* item, uint32_t size);
#endif

		// The list of chunk blocks
		GCBlock* m_firstBlock; 
		GCBlock* m_lastBlock;

		// The lowest priority block that has free items		
		GCBlock* m_firstFree;

		// List of blocks that need sweeping
		GCBlock* m_needsSweeping;

		int    m_itemsPerBlock;
		uint32_t    m_itemSize;
		int m_numBitmapBytes;
		int m_sizeClassIndex;

#ifdef MMGC_MEMORY_PROFILER
		size_t m_totalAskSize;
#endif

		bool m_bitsInPage; 

		int    m_maxAlloc;
		int    m_numAlloc;
		int    m_numBlocks;

		// fast divide numbers
		uint16_t multiple;
		uint16_t shift;

		bool containsPointers;
		bool containsRCObjects;
		bool m_finalized;
		
#ifdef _DEBUG
		bool IsOnEitherList(GCBlock *b);
#endif

		GCBlock* CreateChunk(int flags);
		void UnlinkChunk(GCBlock *b);
		void FreeChunk(GCBlock* b);
		
		// not a hot method
		void AddToFreeList(GCBlock *b);

		// not a hot method
		void RemoveFromFreeList(GCBlock *b);

		// not a hot method
		void AddToSweepList(GCBlock *b);

		// not a hot method
		void RemoveFromSweepList(GCBlock *b);

		bool Sweep(GCBlock *b);
		void SweepGuts(GCBlock *b);

		void ClearMarks(GCAlloc::GCBlock* block);
		void SweepNeedsSweeping();

#ifdef _DEBUG
		static int ConservativeGetMark(const void *item, bool bogusPointerReturnValue);
#endif

		// very hot
		static int GetIndex(const GCBlock *block, const void *item);

		static int SetBit(GCBlock *block, int index, int bit);

		static int GetBit(GCBlock *block, int index, int bit);

		static void ClearBits(GCBlock *block, int index, int bits);

		static void Clear4BitsAndSet(GCBlock *block, int index, int bit);
		
		// not a hot method
		static void ClearQueued(const void *item);
		
#ifdef _DEBUG
		static bool IsPointerIntoGCObject(const void *item);

		static bool IsWhite(GCBlock *block, int index);
#endif

		void ComputeMultiplyShift(uint16_t d, uint16_t &muli, uint16_t &shft);

	protected:
		GC *m_gc;

	public:
		static GCBlock* Next(GCBlock* b);
	};

	/**
	 * A utility class used by the marker to handle mark stack overflow: it abstracts
	 * iterating across marked, non-free objects in one allocator instance.
	 *
	 * No blocks must be added or removed during the iteration.  If an object's
	 * bits are changed, those changes will visible to the iterator if the object has
	 * not yet been reached by the iteration. 
	 */
	class GCAllocIterator
	{
	public:
		GCAllocIterator(MMgc::GCAlloc* alloc);
		
		bool GetNextMarkedObject(void*& out_ptr, uint32_t& out_size);
		
	private:
		GCAlloc* const alloc;
		GCAlloc::GCBlock* block;
		uint32_t idx;
		uint32_t limit;
		uint32_t size;
	};
}

#endif /* __GCAlloc__ */
