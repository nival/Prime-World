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

#ifndef __GCHeap__
#define __GCHeap__

namespace MMgc
{
	class GCHeapConfig
	{
	public:
		GCHeapConfig();
		
		size_t initialSize;
		/**
		 * if the heap gets this big we stop expanding
		 */
		size_t heapLimit;

		/**
		 * if the heap gets this big we fire memory status 
		 * notifications and engage collection activities
		 */
		size_t heapSoftLimit;
		/**
		 * If the application wants the allocator to exit when memory
		 * runs out and reclamation efforts fail set this to a
		 * non-zero value.   Defaults to zero.
		 */
		uint32_t OOMExitCode;
		bool useVirtualMemory;
		bool trimVirtualMemory;
		bool mergeContiguousRegions;
		bool verbose;
		bool returnMemory;
		bool gcstats;
		bool autoGCStats;
		bool gcbehavior;		// Print gross history and policy decisions (MMGC_POLICY_PROFILING)
		bool eagerSweeping;     // Enable full-heap sweeping at the end of Sweep()
#ifdef MMGC_HEAP_GRAPH
		bool dumpFalsePositives;
#endif
		double gcLoad;			// GC load factor: policy aims for a heap size that is gcLoad*H where H is the live size following GC
		double gcLoadCeiling;	// Max multiple of gcLoad policy should use after adjusting L for various factors (0=unlimited)
		double gcEfficiency;    // Max fraction of time to spend in the collector while the incremental collector is active
		static const size_t kDefaultHeapLimit = (size_t)-1;
	};
	
	/**
	 * The GCManager centralizes management of all the memory allocators in the
	 * system, and provides iteration facilities.
	 *
	 * The GCHeap singleton holds the only instance of this manager.
	 */	 
	class GCManager
	{
	public:
		GCManager() {}
		
		/**
		 * Can't have a destructor as it'll be called too late, call destroy to
		 * free any resources.
		 */
		void destroy();

		/**
		 * Register the GC with the manager.  GC must not already be registered.
		 */
		bool tryAddGC(GC* gc) { return collectors.TryAdd(gc); }
		
		/**
		 * Unregister the GC with the manager.  The GC must be registered.
		 */
		void removeGC(GC* gc) { collectors.Remove(gc); }
		
		/**
		 * Tell every other GC that 'gc' is starting a collection (ie there may be memory pressure there).
		 */
		void signalStartCollection(GC* gc);
		
		/**
		 * Tell every other GC that 'gc' is finished with its collection.
		 */
		void signalEndCollection(GC* gc);
		
		BasicList<GC*>& gcs() { return collectors; }

	private:
		BasicList<GC*> collectors;			// array of collectors
	};

	/**
	 * GCHeap is a heap manager for the Flash Player's garbage collector.
	 *
	 * Memory is allocated from the operating system in large chunks
	 * aligned on page boundaries (4096-byte aligned).  All allocation
	 * requests are specified in numbers of 4096-byte pages.  The first
	 * 4 bytes of each page is reserved for GCHeap's use.
	 *
	 * Allocations may fail if there is no free block large enough
	 * to satisfy the request.  When this occurs, the GC class will
	 * choose to either garbage collect or expand the heap, and then
	 * call GCHeap again to retry the allocation.
	 *
	 * When blocks are freed, they are coalesced with their neighbors
	 * when possible to reduce fragmentation.  A "boundary tag" scheme
	 * similar to Doug Lea's malloc is used to make coalescing fast.
	 * To keep things simple, coalescing is always performed immediately
	 * when a block is freed, and not deferred.
	 *
	 * Allocations are performed using multiple free lists.  Blocks that
	 * are <= kUniqueThreshold pages in size get their own free list.
	 * Blocks above the threshold get mapped to more granular free lists,
	 * and all blocks above kHugeThreshold get mapped to the last free list.
	 * This approach is borrowed from Hans Boehm's C/C++ Garbage Collector.
	 * 
	 * Free lists are doubly-linked lists sorted in size order.  The
	 * sorting is done to ensure best-fit allocation.  Each free list
	 * is itself a list node, and the lists are circular, in a technique
	 * also borrowed from Doug Lea's malloc.  This makes for very simple
	 * logic to insert/remove nodes.
	 *
	 * Only Windows is currently supported, although this should be easy
	 * to get working on other platforms.  Memory is allocated in large
	 * (64K minimum) chunks using the VirtualAlloc API.  Every time the
	 * heap is expanded, a new heap region is created corresponding to
	 * the address space returned by VirtualAlloc.  Heap regions are
	 * allocated contiguously if possible to reduce fragmentation.
	 */
	class GCHeap 
	{
		friend class GC;
		friend class FixedAlloc;		
		friend class FixedMalloc;		
		friend class GCPolicyManager;
	public:
		// -- Constants
		
		/** Size of a block */
		const static uint32_t kBlockSize = 4096;

		/** 
		 * Max allowable size for any allocation = 2^32 - 1  bytes
		 * This value is based on the max value on 32-bit systems
		 * and acts as a cap on the size of an allocation request
		 * Overflow detection routines CheckForAllocSizeOverflow()
		 * use this value to check for overflows
		 */
		const static size_t kMaxObjectSize = 0xFFFFFFFF; 
		
		/** Default size of address space reserved per region in blocks */
#ifdef MMGC_64BIT
		const static uint32_t kDefaultReserve = 4096;
#else
		const static uint32_t kDefaultReserve = 512;
#endif
		
		/** Sizes up to this many blocks each have their own free list. */
		const static uint32_t kUniqueThreshold = 16;

		/**
		 * Sizes of at least this many heap blocks are mapped to a
		 * single free list.
		 */
		const static uint32_t kHugeThreshold = 128;

		/** In between sizes map this many distinct sizes to a single bin. */
		const static uint32_t kFreeListCompression = 8;

		/** Calculated number of free lists */
		const static uint32_t kNumFreeLists = (kHugeThreshold-kUniqueThreshold)/kFreeListCompression+kUniqueThreshold;

		/** Minimum heap increment, in blocks */
		const static uint32_t kMinHeapIncrement = 32;

		/** if this much of the heap is free decommit some memory */
		const static uint32_t kDecommitThresholdPercentage = 25;
		/** if this much of the heap is free un-reserve it */
		const static uint32_t kReleaseThresholdPercentage = 50;

		/**
		 * Init must be called to set up the GCHeap singleton
		 */
		static void Init(const GCHeapConfig& props);

		/* legacy API */
		static void Init(GCMallocFuncPtr malloc = NULL, GCFreeFuncPtr free = NULL, int initialSize=128)
		{
			(void)malloc;
			(void)free;
			GCHeapConfig props;
			props.initialSize = initialSize;
			Init(props);
		}

		/**
		 * Destroy the GCHeap singleton, returns the number of bytes still allocated in FixedMalloc (ie leaked)
		 */
		static size_t Destroy();

		/**
		 * Get the GCHeap singleton
		 */
		inline static GCHeap *GetGCHeap() 
		{
			// when OOM occurs the last EnterFrame macro destroys the
			// heap so this can be NULL, clients should detect NULL
			// and re-create the heap if desired
			return instance; 
		}

		static void EnterLockInit();
		static void EnterLockDestroy();

		inline static bool EnterLock()
		{
			GCAssert(instanceEnterLockInitialized); 
			return VMPI_lockAcquire(&instanceEnterLock);
		}

		inline static bool EnterRelease()
		{
			GCAssert(instanceEnterLockInitialized); 
			return VMPI_lockRelease(&instanceEnterLock);
		}

		/**
		 * Signal a too-large allocation request.  This /will/ cause an immediate shutdown of
		 * the entire system.  (The alternative is to return a NULL pointer, which has the
		 * same effect but with considerably less grace.)  Clients that allocate arbitrarily
		 * large objects based on application or end-user data may wish to be concerned about
		 * checking whether the object might be too large.
		 */
#if defined (__GNUC__)
		static void SignalObjectTooLarge() __attribute__((noreturn));
#else
		static void SignalObjectTooLarge();
#endif

		/**
		 * Signal an inconsistent heap state (an unrecoverable program error).  This /will/
		 * cause an immediate shutdown of the entire system.  (The alternative is to return
		 * a NULL pointer, which has the same effect but with considerably less grace.)
		 */
#if defined (__GNUC__)
		static void SignalInconsistentHeapState(const char* reason) __attribute__((noreturn));
#else
		static void SignalInconsistentHeapState(const char* reason);
#endif

		/**
		 * Signal that the caller is about to longjmp to or past an MMGC_ENTER, and that
		 * actions should be taken to leave the heap in a consistent state.
		 *
		 * MMgc code does not use this, it's intended for use by external agents.  It can
		 * be called without ill effect even if there is no active GC or GCHeap.
		 *
		 * longjmp'ing to or past an MMGC_ENTER is not supported in all contexts: host code
		 * should never do it on call-backs on allocation, deallocation, and finalization hooks.
		 */
		static void SignalImminentAbort();
		
		/**
		 * Signal that client code has performed an allocation from memory known not to be
		 * controlled by MMgc, and wants this memory accounted for.  (A typical case is when
		 * system memory is allocated for rendering buffers.)
		 *
		 * Let 'total memory volume' be the sum of the memory volume controlled by MMgc,
		 * plus the volume added by SignalExternalAllocation, minus the volume subtracted
		 * by SignalExternalDeallocation.  MMgc performs its out-of-memory avoidance
		 * actions (actions for crossing the soft and hard limits) based on total memory
		 * volume.
		 */
		static void SignalExternalAllocation(size_t nbytes);
		
		/**
		 * Signal that client code has performed a deallocation of memory known not to be
		 * controlled by MMgc, and wants this memory accounted for.
		 *
		 * @see SignalExternalAllocation
		 */
		static void SignalExternalDeallocation(size_t nbytes);
		
		inline FixedMalloc* GetFixedMalloc() { return FixedMalloc::GetFixedMalloc(); }

		/**
		* flags to be passed as second argument to alloc
		*/
		enum AllocFlags
		{
			kExpand=1,
			kZero=2,
			kProfile=4,
			kCanFail=8
		};

		/**
		 * Allocates a block from the heap.
		 * @param size the number of pages (kBlockSize bytes apiece)
		 *             to allocate.
		 * @return pointer to beginning of block, or NULL if failed.
		 */
		void *Alloc(size_t size, uint32_t flags=kExpand | kZero | kProfile);

		/**
		 * Allocate memory that the JIT will use for object code.
		 * @param size the number of blocks
		 */
		void *AllocCodeMemory(size_t size)
		{
			codeMemory += size;
			return Alloc(size);
		}
		
		/**
		 * Frees a block.
		 * @param item the block to free.  This must be the same
		 *             pointer that was previously returned by
		 *             a call to Alloc.
		 */
		void Free(void *item) { FreeInternal(item, true); }
		void FreeNoProfile(void *item) { FreeInternal(item, false); }

		/**
		 * Free memory allocated from AllocCodeMemory.
		 */
		void FreeCodeMemory(void* item)
		{
			HeapBlock *block = AddrToBlock(item);
			codeMemory -= block->size;
			Free(item);
		}
		
		/**
		 * Added for NJ's portability needs cause it doesn't always MMgc 
		 */
		void Free(void *item, size_t /*ignore*/) { FreeInternal(item, true); }


		size_t Size(const void *item);

		/**
		 * Returns the used heap size, that is, the total
		 * space actually used by allocated objects.
		 * @return the minimum heap size in pages (kBlockSize bytes apiece)
		 */
		size_t GetUsedHeapSize() const { return numAlloc; }

		/**
		 * Returns the "free heap size", that is, the difference in the
		 * total heap size and the used heap size
		 * @return the minimum heap size in pages (kBlockSize bytes apiece)
		 */
		size_t GetFreeHeapSize() const { return GetTotalHeapSize()-numAlloc; }

		/**
		 * @return the amount of code memory currently allocated.  GCHeap does not
		 * have a notion of "free" and "used" code memory.
		 */
		size_t GetTotalCodeSize() const { return codeMemory; }

#ifdef MMGC_POLICY_PROFILING
		/**
		 * Returns the peak value for the total amount of space managed by the heap
		 * and the amount of private memory at the point where the maximum heap
		 * number was recorded.
		 */
		void GetMaxTotalHeapSize(size_t& heapBlocks, size_t& privateBlocks)
		{
			heapBlocks = maxTotalHeapSize / kBlockSize;
			privateBlocks = maxPrivateMemory / kBlockSize;
		}
#endif

		/**
		 * Returns the total heap size, that is, the total amount
		 * of space managed by the heap, including all used and
		 * free space.
		 * @return the total heap size in pages (kBlockSize bytes apiece)
		 */
		size_t GetTotalHeapSize() const { return blocksLen - numDecommitted; }
		
		/**
		 * gives memory back to the OS when there hasn't been any memory activity in a while
		 * and we have lots of free memory
		 */
		void Decommit();

		static size_t SizeToBlocks(size_t bytes) { return ((bytes + kBlockSize - 1) & ~(kBlockSize-1)) / kBlockSize; }

#ifdef MMGC_HOOKS
		/* Hooks are normally disabled in RELEASE builds, as there is a slight cost added
		   to some hot paths.  */
		/* controls whether AllocHook and FreeHook are called */
		void EnableHooks() { hooksEnabled = true; }
		REALLY_INLINE bool HooksEnabled() const { return hooksEnabled; }
		void AllocHook(const void *item, size_t askSize, size_t gotSize);
		// called when object is determined to be garbage but we can't write to it yet
		void FinalizeHook(const void *item, size_t size);
		// called when object is really dead and can be poisoned
		void FreeHook(const void *item, size_t size, int poison);
#endif

#ifdef MMGC_MEMORY_PROFILER
		MemoryProfiler *GetProfiler() { return profiler; }
		void DumpFatties() { profiler->DumpFatties(); }
#endif

		// Every new GC must register itself with the GCHeap.
		void AddGC(GC *gc);
		
		// When the GC is destroyed it must remove itself from the GCHeap.
		void RemoveGC(GC *gc);

		void AddOOMCallback(OOMCallback *p);

		void RemoveOOMCallback(OOMCallback *p);
		
#ifdef MMGC_USE_SYSTEM_MALLOC
		// Signal a failure to allocate 'size' bytes from the system heap (VMPI_alloc).
		// The value 'attempt' denotes the number of previous attempts made to satisfy
		// this particular memory request; the implementation is at liberty to have
		// a cutoff for the number of attempts and must signal an abort if the number
		// of attempts exceeds the cutoff.  (Normally the cutoff would be one previous
		// attempt.)
		void SystemOOMEvent(size_t size, int attempt);
#endif

#if defined (__GNUC__)
		void Abort() __attribute__((noreturn));
#else
		void Abort();
#endif

		MemoryStatus GetStatus() { return status; }

		/**
		 * CheckForAllocSizeOverflow checks whether an allocation request
		 * would request an object larger than what MMgc can accomodate.
		 *
		 * Overflow detection logic: 
		 * Currently, in MMgc all object allocations are capped to 2^32-1 (=kMaxObjectSize)
		 * which is the largest object size on 32-bit systems.  To detect overflow
		 * the standard way is to add the values and look for wraparound by checking if
		 * the result is less than either of the operands.  However, on 64-bit systems
		 * sizeof(size_t) == 8 bytes and the wraparound check would not work.  So this
		 * method also checks if the result exceeds 2^32-1 to conform our allocation size cap.
		 * Requirement:
		 * All allocation routines and methods that add extra payload (such as headers) to 
		 * allocation requests should call this method for overflow detection.
		 * @param size requested size pertaining to object being allocated
		 * @param extra amount of extra bytes accompanying an allocation
		 * @return:  The sum of size and extra.
		 * @note This method may not return.  It is designed to terminate
		 * the program if an overflow is detected.
		 */
		REALLY_INLINE static size_t CheckForAllocSizeOverflow(size_t size, size_t extra)
		{
			//calculate the total requested size
			uint64_t total = (uint64_t)size + (uint64_t)extra;
			
			//check if request size exceeds kMaxObjectSize
			// or for sizeof(size_t) = 8 bytes check for wraparound on the total value
#ifdef MMGC_64BIT
			if ((total > (uint64_t)kMaxObjectSize) || (total < size) || (total < extra))
				SignalObjectTooLarge();
#else
			// This is the 32-bit implementation, it avoids unnecessary checks for overflow.
			if (total > (uint64_t)kMaxObjectSize)
				SignalObjectTooLarge();
#endif
			return size_t(total);
		}
		
		/**
		 * CheckForCallocSizeOverflow
		 * This method is designed to check whether an allocation request
		 * of N objects for a given size might result in numeric overflow.  
		 * Overflow detection logic:
		 * In this method we detect overflow occurring from result of (N * M) where
		 * N = number of objects and M = size of one object.
		 * Currently, in MMgc all object allocations are capped to 2^32-1 (=kMaxObjectSize)
		 * which is the largest object size on 32-bit systems.  
		 * To detect overflow, we first check if either of N or M exceeds kMaxObjectSize.  
		 * This check is a guard against overflow on 64-bit systems where sizeof(size_t) is
		 * greater than 4 bytes.  If this check succeeds then we perform a 64-bit based
		 * product i.e. (N * M) and check if the result exceeds kMaxObjectSize.
		 * Requirement:
		 * All allocation routines and methods that are servicing allocation requests
		 * based on a product of object size and a number of objects should call this method prior to allocation
		 * @param count number of objects being allocated
		 * @param elsize requested size pertaining to a single object being allocated
		 * @return: None.  This method is designed to call Abort() which in turn terminates
		 * the program if an overflow is detected.
		 */		
		REALLY_INLINE static size_t CheckForCallocSizeOverflow(size_t count, size_t elsize)
		{
			//If either of the size of requested bytes
			//or the number of requested size 
			//or if their product exceeds kMaxObjectSize 
			//we treat that as overflow and abort
			uint64_t total = (uint64_t)elsize * (uint64_t)count;
#ifdef MMGC_64BIT
			if(   elsize > kMaxObjectSize 
			   || count >= kMaxObjectSize
			   || total > (uint64_t)kMaxObjectSize)
				SignalObjectTooLarge();
#else
			if(total > (uint64_t)kMaxObjectSize)
				SignalObjectTooLarge();
#endif
			return size_t(total);
		}

		/** The native VM page size (in bytes) for the current architecture */
		const size_t kNativePageSize;

		GCHeapConfig &Config() { return config; }

		void log_percentage(const char *, size_t bytes, size_t relativeTo);

		void DumpMemoryInfo();
		void DumpMemoryInfoLocked();

#ifdef MMGC_MEMORY_PROFILER
#ifdef MMGC_USE_SYSTEM_MALLOC
		void TrackSystemAlloc(void *addr, size_t askSize);
		void TrackSystemFree(void *addr);
#endif //MMGC_USE_SYSTEM_MALLOC
#endif

		void *GetStackEntryAddress() { return (void*)GetEnterFrame(); }
		EnterFrame *GetEnterFrame() { return enterFrame; }

		void SetActiveGC(GC *gc) { if(enterFrame) enterFrame->SetActiveGC(gc); }
		inline bool StackEnteredCheck() { return !entryChecksEnabled || GetEnterFrame() != NULL; }
		
		// remove this and make them always enabled once its possible
		inline void SetEntryChecks(bool to) { entryChecksEnabled = to; }

		// Heap regions
		// (ought to be private but some VMPI implementations 
		// currently need to peek at it)
		class Region
		{
		public:
			Region(GCHeap *heap, char *baseAddr, char *rTop, char *cTop, size_t blockId);
			Region *prev;
			char *baseAddr;
			char *reserveTop;
			char *commitTop;
			size_t blockId;
		};
		Region *lastRegion;
		
		static bool ShouldNotEnter();

		bool IsAddressInHeap(void *);

	private:

		GCHeap(const GCHeapConfig &config);
		void DestroyInstance();

#ifdef MMGC_MEMORY_PROFILER
		static void InitProfiler();
		inline static bool IsProfilerInitialized()
		{
			return profiler != (MemoryProfiler*)-1;
		}
#endif

		/**
		 * Expands the heap by size pages.
		 *
		 * Expands the heap by "size" blocks, such that a single contiguous
		 * allocation of "size" blocks can be performed.  This method is
		 * also called to create the initial heap.
		 *
		 * On Windows, this uses the VirtualAlloc API to obtain memory.
		 * VirtualAlloc can _reserve_ memory, _commit_ memory or both at
		 * the same time.  Reserved memory is just virtual address space.
		 * It consumes the address space of the process but isn't really
		 * allocated yet; there are no pages committed to it yet.
		 * Memory allocation really occurs when reserved pages are
		 * committed.  Our strategy in GCHeap is to reserve a fairly large
		 * chunk of address space, and then commit pages from it as needed.
		 * By doing this, we're more likely to get contiguous regions in
		 * memory for our heap.
		 *
		 * By default, we reserve 16MB (4096 pages) per heap region.
		 * The amount to reserve by default is controlled by kDefaultReserve.
		 * That shouldn't be a big deal, as the process address space is 2GB.
		 * As we're usually a plug-in, however, we don't want to make it too
		 * big because it's not all our memory.
		 *
		 * The goal of reserving so much address space is so that subsequent
		 * expansions of the heap are able to obtain contiguous memory blocks.
		 * If we can keep the heap contiguous, that reduces fragmentation
		 * and the possibility of many small "Balkanized" heap regions.
		 *
		 * Algorithm: When an allocation is requested,
		 * 1. If there is enough reserved but uncommitted memory in the
		 *    last-created region to satisfy the request, commit that memory
		 *    and exit with success, also check decommitted list
		 * 2. Try to reserve a new region contiguous with the last-created
		 *    region.  Go for a 16MB reservation or the requested size,
		 *    whichever is bigger.
		 * 3. If we tried for 16MB reserved space and it didn't work, try
		 *    to reserve again, but for the requested size.
		 * 4. If we were able to retrieve a contiguous region in Step 2 or 3,
		 *    commit any leftover memory from the last-created region,
		 *    commit the remainer from the newly created region, and exit
		 *    with success.
		 * 5. OK, the contiguous region didn't work out, so allocate a
		 *    non-contiguous region.  Go for 16MB or the requested size
		 *    again, whichever is bigger.
		 * 6. If we tried for 16MB reserved space and it didn't work, try
		 *    to reserve again, but for the requested size.
		 * 7. Commit the requested size out of the newly created region
		 *    and exit with success.
		 *
		 * If we are able to reserve memory but can't commit it, then, well
		 * there isn't enough memory.  We free the reserved memory and
		 * exit with failure.
		 *
		 * @param size the number of pages to expand the heap by
		 */	 
		void ExpandHeap(size_t size, bool canFail=false);
		bool ExpandHeapInternal(size_t size);
		
		// Block struct used for free lists and memory traversal
		class HeapBlock 
		{
		public:
			char *baseAddr;   // base address of block's memory
			size_t size;         // size of this block
			size_t sizePrevious; // size of previous block
			HeapBlock *prev;      // prev entry on free list
			HeapBlock *next;      // next entry on free list
			bool committed;   // is block fully committed?
			bool dirty;		  // needs zero'ing, only valid if committed
#if defined(MMGC_MEMORY_PROFILER) && defined(MMGC_MEMORY_INFO)
			StackTrace *allocTrace;
			StackTrace *freeTrace;
#endif
			bool inUse() const { return prev == NULL; }
			char *endAddr() const { return baseAddr + size*kBlockSize; }
			void FreelistInit()
			{
				baseAddr     = NULL;
				size         = 0;
				sizePrevious = 0;
				prev         = this;
				next         = this;
				committed    = true;
				dirty 	    = true;
			}
		};

		// Core methods
		void AddToFreeList(HeapBlock *block);
		void AddToFreeList(HeapBlock *block, HeapBlock* pointToInsert);
		HeapBlock *AllocBlock(size_t size, bool& zero);
		void FreeBlock(HeapBlock *block);
		void FreeAll();

		void FreeInternal(const void *item, bool profile);
	
		HeapBlock *Split(HeapBlock *block, size_t size);

		// abandon a block of memory that may maps completely to the committed portion of region
		void RemoveBlock(HeapBlock *block);
		
#ifdef MMGC_MAC
		// Abandon a block of memory that may be in the middle of a
		// region.  On mac decommit is a two step process, release and
		// reserve, another thread could steal the memory between the
		// two operations so we have to be prepared to ditch a block
		// we try to decommit.  This is a horrible hack that can go
		// away if OS X fixes its mmap impl to be like windows, linux
		// and solaris (atomic decommit with VirtualFree/mmap)
		void RemovePartialBlock(HeapBlock *block);
#endif

		void Commit(HeapBlock *block);

		HeapBlock *AddrToBlock(const void *item) const;
		Region *AddrToRegion(const void *item) const;
		void RemoveRegion(Region *r);

		// debug only freelist consistency checks
#ifdef _DEBUG
		void CheckFreelist();
#else
		REALLY_INLINE void CheckFreelist()
		{
			// nothing
		}
#endif

		bool BlocksAreContiguous(void *item1, void *item2);
		
		// textual heap representation, very nice!
		void DumpHeapRep();
		
		//log a character for "count" times
		void LogChar(char c, size_t count);

		// Remove a block from a free list (inlined for speed)
		inline void RemoveFromList(HeapBlock *block)
		{
			GCAssert(!block->inUse());
			block->prev->next = block->next;
			block->next->prev = block->prev;
			block->next = block->prev = 0;
		}			

		// Map a number of blocks to the appropriate large block free list index
		// (inlined for speed)
		inline uint32_t GetFreeListIndex(size_t size)
		{
			if (size <= kUniqueThreshold) {
				return (uint32_t)size-1;
			} else if (size >= kHugeThreshold) {
				return kNumFreeLists-1;
			} else {
				return (uint32_t) ((size-kUniqueThreshold)/kFreeListCompression+kUniqueThreshold-1);
			}
		}

		bool HardLimitExceeded();
		bool SoftLimitExceeded();
		void StatusChangeNotify(MemoryStatus to);
		void CheckForStatusReturnToNormal();
		void CheckForHardLimitExceeded();
		void CheckForSoftLimitExceeded(size_t request);

		void ValidateHeapBlocks();

		void ReleaseMemory(char *address, size_t size);

 		void Enter(EnterFrame *frame);
 		void Leave();

		bool statusNotNormalOrAbort()
		{
			return status != kMemNormal && status != kMemAbort;
		}

 		size_t numHeapBlocksToNumBlocks(size_t numBlocks)
 		{
 			size_t bytes = numBlocks * sizeof(HeapBlock);
 			// round up to nearest block
 			bytes = (bytes + kBlockSize - 1) & ~(kBlockSize-1);
 			return bytes / kBlockSize;
 		}

		/**
		 * Regions are allocated from the blocks GCHeap manages
		 * similar to the HeapBlocks.  Regions can come and go so we
		 * maintain a freelist although in practice they come and go
		 * rarely we want don't want any longevity bugs
		 */
		Region *NewRegion(char *baseAddr, char *rTop, char *cTop, size_t blockId);
		void FreeRegion(Region *r);

		// data section
		static GCHeap *instance;
		static size_t leakedBytes;

		static vmpi_spin_lock_t instanceEnterLock;
		static bool instanceEnterLockInitialized;
	
		FixedMalloc fixedMalloc;
		Region *freeRegion;
		Region *nextRegion;
		HeapBlock *blocks;
		size_t blocksLen;
		size_t numDecommitted;
		size_t numRegionBlocks;
		HeapBlock freelists[kNumFreeLists];
		size_t numAlloc;
		size_t codeMemory;
		size_t externalPressure;
		vmpi_spin_lock_t m_spinlock;
		GCHeapConfig config;
		GCManager gcManager;		
 		BasicList<OOMCallback*> callbacks;
 		vmpi_spin_lock_t list_lock;

		GCThreadLocal<EnterFrame*> enterFrame;
		friend class EnterFrame;
		MemoryStatus status;
		bool statusNotificationBeingSent;
 		uint32_t enterCount;

		vmpi_spin_lock_t gclog_spinlock;	// a lock used by GC::gclog for exclusive access to GCHeap::DumpMemoryInfo

#ifdef MMGC_MEMORY_PROFILER
		static MemoryProfiler *profiler;
		bool hasSpy; //flag indicating whether profiler spy is active or not.  If active, AllocHook will call VMPI_spyCallback
#endif

		size_t maxTotalHeapSize;	// in bytes
#ifdef MMGC_POLICY_PROFILING
		size_t maxPrivateMemory;	// in bytes
#endif

#ifdef MMGC_HOOKS
		bool hooksEnabled;
#endif

		bool entryChecksEnabled;
 		bool abortStatusNotificationSent;
	};
	
	// Move the following to GCHeap-inlines.h when we have it.

	REALLY_INLINE size_t GCHeap::Size(const void *item)
	{
		MMGC_LOCK(m_spinlock);
		HeapBlock *block = AddrToBlock(item);
		return block->size;
	}
}

#endif /* __GCHeap__ */
