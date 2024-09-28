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

#ifndef __Malloc__
#define __Malloc__

namespace MMgc
{
	/**
	 * A general purpose memory allocator.
	 *
	 * FixedMalloc is a singleton, obtainable by calling FixedMalloc::GetFixedMalloc.
	 * The "owner" of the FixedMalloc is GCHeap, the block manager.
	 *
	 * FixedMalloc uses size classes; each size class is handled by a FixedAllocSafe
	 * instance.  Large objects are handled specially.  All objects are headerless.
	 */
	class FixedMalloc 
	{
		friend class GCHeap;

	public:
		/**
		 * @return the FixedMalloc singleton.
		 */
		static FixedMalloc *GetFixedMalloc();

		// Backward compatible name for GetFixedMalloc, not used by Tamarin
		static FixedMalloc *GetInstance();

		/**
		 * Allocate one object from this allocator.
		 *
		 * @param size   The size of the object.
		 * @param flags  A bit vector of allocation options.
		 *
		 * @return  A pointer to the object.  The pointer may be NULL only if kCanFail is
		 *          part of flags.  The memory is zeroed only if kZero is part of flags.
		 */
		void* Alloc(size_t size, FixedMallocOpts flags=kNone);

		// Exactly like Alloc with flags=kCanFail
		void *PleaseAlloc(size_t size);

		// Exactly like Alloc, but guaranteed not to be inlined - used by ::new etc
		void* FASTCALL OutOfLineAlloc(size_t size, FixedMallocOpts flags=kNone);

		/**
		 * Allocate space for an array of objects from this allocator.
		 *
		 * @param count  The number of objects
		 * @param size   The size of each part object
		 * @param flags  A bit vector of allocation options
		 *
		 * @return  A pointer to the aggregate object.  The pointer may be NULL only if
		 *          kCanFail is part of flags.  The memory is zeroed only if kZero is part
		 *          of flags.
		 *
		 * @note  Unlike 'calloc' in the C library, this does /not/ zero the memory
		 *        unless kZero is passed in flags.  The name 'Calloc' comes from the
		 *        shape of the API.
		 */
		void *Calloc(size_t count, size_t size, FixedMallocOpts flags=kNone);
		
		/**
		 * Free an object allocated with FixedMalloc.
		 *
		 * @param item  The object to free.
		 */
		void Free(void *item);

		// Exactly like Free, but guaranteed not to be inlined - used by ::delete etc
		void FASTCALL OutOfLineFree(void* p);
		
		/**
		 * @param  item  An object allocated with FixedMalloc.
		 * @return the allocated size of 'item'
		 */
		size_t Size(const void *item);

		/**
		 * @return the total number of /blocks/ managed by FixedMalloc.
		 */
		size_t GetTotalSize();
		
		/**
		 * Obtain current (not running total) allocation information for FixedMalloc.
		 *
		 * @param totalAskSize    (out) The total number of bytes requested
		 * @param totalAllocated  (out) The number of bytes actually allocated
		 */
		void GetUsageInfo(size_t& totalAskSize, size_t& totalAllocated);
		
		/**
		 * @return the number bytes currently allocated by FixedMalloc
		 */
		size_t GetBytesInUse();

#ifdef MMGC_MEMORY_PROFILER
		void DumpMemoryInfo();
#endif

	private:
		// Initialize FixedMalloc.  Must be called from GCHeap during GCHeap setup.
		void InitInstance(GCHeap *heap);
		
		// Destroy FixedMalloc and free all resources.
		void DestroyInstance();
		
#ifdef MMGC_64BIT
		const static int kLargestAlloc = 2016;	
#else
		const static int kLargestAlloc = 2032;	
#endif
		const static int kNumSizeClasses = 41;
		const static int16_t kSizeClasses[kNumSizeClasses];

		const static unsigned kMaxSizeClassIndex = (kLargestAlloc>>3)+1;
		const static uint8_t kSizeClassIndex[kMaxSizeClassIndex];
		
		static FixedMalloc *instance;

		GCHeap *m_heap;
		FixedAllocSafe m_allocs[kNumSizeClasses];	
		size_t numLargeChunks;
		
#ifdef MMGC_MEMORY_PROFILER
		size_t totalAskSizeLargeAllocs;
#endif
		
#ifdef _DEBUG
		// For debugging we track live large objects in this list.  If there are a lot
		// of large objects then a list may slow down debug builds too much; in that
		// case we can move to a tree or similar structure.  (It's useful to avoid using
		// large objects in this data structure.)
		struct LargeObject
		{
			const void *item;		// Start of a block
			LargeObject* next;		// Next object
		};
		LargeObject *largeObjects;	// Initially NULL 
#endif
		
#ifdef _DEBUG
		// If this returns then item was definitely allocated by an allocator
		// owned by this FixedMalloc.
		void EnsureFixedMallocMemory(const void* item);
		
		// Track large object
		void AddToLargeObjectTracker(const void* item);
		
		// Untrack large object
		void RemoveFromLargeObjectTracker(const void* item);
#endif
		
		// @return a thread-safe allocator for objects of the given size.
		FixedAllocSafe* FindSizeClass(size_t size);

		// @return true if item is a large-object allocation.  item must have been
		//         returned from one of the allocation functions.
		static bool IsLargeAlloc(const void *item);

		// @return an object of at least the requested size, allocated with the given
		//         flags.  The object's real size will be an integral number of blocks.
		void *LargeAlloc(size_t size, FixedMallocOpts flags=kNone);	
		
		// Free the item returned from LargeAlloc.
		void LargeFree(void *item);
		
		// @return the allocated size (in bytes) of 'item', which must have been returned
		//         from LargeAlloc.
		size_t LargeSize(const void *item);
	};
}
#endif /* __Malloc__ */
