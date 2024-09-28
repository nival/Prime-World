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

#ifdef AVMPLUS_SAMPLER
namespace avmplus
{
	void recordAllocationSample(const void* item, size_t size);
	void recordDeallocationSample(const void* item, size_t size);	
}
#endif

#if defined MMGC_POLICY_PROFILING && !defined AVMSHELL_BUILD
extern void RedirectLogOutput(void (*)(const char*));
static FILE* fp = NULL;

void logToFile(const char* s)
{
	fprintf(fp, "%s", s);
	fflush(fp);
}

static void startGCLogToFile()
{
	fp = fopen("gcbehavior.txt", "w");
	if (fp != NULL)
		RedirectLogOutput(logToFile);
}

static void endGCLogToFile()
{
	RedirectLogOutput(NULL);
	if (fp != NULL) {
		fclose(fp);
		fp = NULL;
	}
}
#endif // MMGC_POLICY_PROFILING && !AVMSHELL_BUILD

namespace MMgc
{
	GCHeap *GCHeap::instance = NULL;
	bool GCHeap::instanceEnterLockInitialized = false;
	vmpi_spin_lock_t GCHeap::instanceEnterLock;

	// GCHeap instance has the C++ runtime call dtor which causes problems
	AVMPLUS_ALIGN8(uint8_t) heapSpace[sizeof(GCHeap)];

	size_t GCHeap::leakedBytes;

#ifdef MMGC_MEMORY_PROFILER
	MemoryProfiler* GCHeap::profiler = (MemoryProfiler*)-1;
#endif

	GCHeapConfig::GCHeapConfig() : 
		initialSize(512), 
		heapLimit(kDefaultHeapLimit), 
		heapSoftLimit(0),
		OOMExitCode(0),
		useVirtualMemory(VMPI_useVirtualMemory()),
		trimVirtualMemory(true),
		mergeContiguousRegions(VMPI_canMergeContiguousRegions()),
		verbose(false),
		returnMemory(true),
		gcstats(false), // tracking
		autoGCStats(false), // auto printing
#ifdef AVMSHELL_BUILD
		gcbehavior(false),	// controlled by command line switch
#else
		gcbehavior(true),	// unconditional, if MMGC_POLICY_PROFILING is on
#endif
		eagerSweeping(false),
#ifdef MMGC_HEAP_GRAPH
		dumpFalsePositives(false),
#endif
		gcLoad(2.0),
		gcLoadCeiling(1.0),	// 1.0 is probably OK for desktop, maybe less so for mobile - more experiments needed
		gcEfficiency(0.25)
	{
#ifdef MMGC_64BIT
		trimVirtualMemory = false; // no need
#endif
		const char *envValue = VMPI_getenv("MMGC_HEAP_LIMIT");
		if(envValue)
			heapLimit = VMPI_strtol(envValue, 0, 10);
		envValue = VMPI_getenv("MMGC_HEAP_SOFT_LIMIT");
		if(envValue)
			heapSoftLimit = VMPI_strtol(envValue, 0, 10);
	}

	void GCHeap::Init(const GCHeapConfig& config)
	{
		GCAssert(instance == NULL);
		void *p = (void*)heapSpace;
		instance = new (p) GCHeap(config);
	}

	size_t GCHeap::Destroy()
	{
		EnterLock();	
		GCAssert(instance != NULL);
		instance->DestroyInstance();
		instance = NULL;
		EnterRelease();		
		return leakedBytes;
	}

	GCHeap::GCHeap(const GCHeapConfig& c)
		: kNativePageSize(VMPI_getVMPageSize()),
		  lastRegion(NULL),
		  freeRegion(NULL),
		  nextRegion(NULL),
		  blocks(NULL),
		  blocksLen(0),
		  numDecommitted(0),
		  numRegionBlocks(0),
		  numAlloc(0),
		  codeMemory(0),
		  externalPressure(0),
		  config(c),
 		  status(kMemNormal),
		  statusNotificationBeingSent(false),
		  enterCount(0),
	#ifdef MMGC_MEMORY_PROFILER
		  hasSpy(false),
	#endif
		  maxTotalHeapSize(0),
	#ifdef MMGC_POLICY_PROFILING
 		  maxPrivateMemory(0),
	#endif
    #ifdef MMGC_HOOKS
		  hooksEnabled(false),
    #endif
		  entryChecksEnabled(true),
		  abortStatusNotificationSent(false)
	{		
		VMPI_lockInit(&m_spinlock);
		VMPI_lockInit(&list_lock);
		VMPI_lockInit(&gclog_spinlock);

		// Initialize free lists
		HeapBlock *block = freelists;
		for (uint32_t i=0; i<kNumFreeLists; i++) {
			block->FreelistInit();
			block++;
		}
		
		// Create the initial heap
		{
			MMGC_LOCK(m_spinlock);
			ExpandHeap((int)config.initialSize);
		}

		fixedMalloc.InitInstance(this);

		instance = this;

#ifdef MMGC_MEMORY_PROFILER
		//create profiler if turned on and if it is not already created
		if(!IsProfilerInitialized())
		{
			InitProfiler();
		}

		if(profiler)
		{
			hooksEnabled = true; // set only after creating profiler
			hasSpy = VMPI_spySetup();
		}
#endif
		
#ifdef MMGC_MEMORY_INFO
		hooksEnabled = true; // always track allocs in DEBUG builds
#endif

#if defined MMGC_POLICY_PROFILING && !defined AVMSHELL_BUILD
		startGCLogToFile();
#endif
	}

	void GCHeap::DestroyInstance()
	{
#if defined MMGC_POLICY_PROFILING && !defined AVMSHELL_BUILD
		endGCLogToFile();
#endif

		gcManager.destroy();
		callbacks.Destroy();

		leakedBytes = GetFixedMalloc()->GetBytesInUse();
		fixedMalloc.DestroyInstance();
		GCAssertMsg(leakedBytes == 0 || GetStatus() == kMemAbort, "Leaks!");

		instance = NULL;

		size_t internalNum = AddrToBlock(blocks)->size + numRegionBlocks;		
		
		// numAlloc should just be the size of the HeapBlock's space
		if(numAlloc != internalNum && status != kMemAbort)
		{
			for (unsigned int i=0; i<blocksLen; i++) 
			{
				HeapBlock *block = &blocks[i];
				if(block->inUse() && block->baseAddr && block->baseAddr != (char*)blocks)
				{
#ifndef DEBUG
					if (config.verbose)
#endif
					{
						GCLog("Block 0x%x not freed\n", block->baseAddr);
					}
#if defined(MMGC_MEMORY_PROFILER) && defined(MMGC_MEMORY_INFO)
					if(block->allocTrace)
						PrintStackTrace(block->allocTrace);
#endif
				}
			}	
			GCAssert(false);
		}

#ifdef MMGC_MEMORY_PROFILER
		hooksEnabled = false;
		if(profiler)
			delete profiler;
		if(hasSpy)
			VMPI_spyTeardown();
		profiler = NULL;
#endif

		FreeAll();
		
		//  Acquire all the locks before destroying them to make absolutely sure we're the last consumers.
		VMPI_lockAcquire(&m_spinlock);
		VMPI_lockDestroy(&m_spinlock);

		VMPI_lockAcquire(&gclog_spinlock);
		VMPI_lockDestroy(&gclog_spinlock);
		
		VMPI_lockAcquire(&list_lock);
		VMPI_lockDestroy(&list_lock);
		
		if(enterFrame)
			enterFrame->Destroy();
	}

	void* GCHeap::Alloc(size_t size, uint32_t flags)
	{
		GCAssert(size > 0);

		char *baseAddr = 0;
		bool zero = (flags & kZero) != 0;
		// nested block to keep memset/memory commit out of critical section
		{
			MMGC_LOCK(m_spinlock);

			HeapBlock *block = AllocBlock(size, zero);

			if(!block) {
				if((flags & kExpand) == 0)
					return NULL;

				ExpandHeap(size, (flags & kCanFail) != 0);
				block = AllocBlock(size, zero);
				if(!block) {
					if (!(flags & kCanFail))
					{
						GCAssertMsg(0, "Internal error: ExpandHeap should have aborted if it can't satisfy the request");
						SignalInconsistentHeapState("Failed to abort");
						/*NOTREACHED*/
					}
					return NULL;
				}
			}

			GCAssert(block->size == size);
			
			numAlloc += size;
			
			// copy baseAddr to a stack variable to fix :
			// http://flashqa.macromedia.com/bugapp/detail.asp?ID=125938
			baseAddr = block->baseAddr;
			
#if defined(MMGC_MEMORY_PROFILER) && defined(MMGC_MEMORY_INFO)
			if(profiler)
				block->allocTrace = profiler->GetStackTrace();
#endif
			
#ifdef MMGC_MEMORY_PROFILER
			if((flags & kProfile) && HooksEnabled() && profiler) {
				profiler->RecordAllocation(baseAddr, size * kBlockSize, size * kBlockSize);
			}
#endif
			if((flags & kCanFail) == 0)
				CheckForSoftLimitExceeded(size);
		}

		// Zero out the memory, if requested to do so
		if (zero) {
			VMPI_memset(baseAddr, 0, size * kBlockSize);
		}

		// fail the allocation if we hit soft limit and canFail
		if(status == kMemSoftLimit && (flags & kCanFail) != 0) {
			FreeInternal(baseAddr, true);
			return NULL;
		}				   
		
		return baseAddr;
	}

	void GCHeap::FreeInternal(const void *item, bool profile)
	{
		(void)profile;
		MMGC_LOCK(m_spinlock);

		HeapBlock *block = AddrToBlock(item);
		GCAssertMsg(block != NULL, "Bogus item");

		// Update metrics
		GCAssert(numAlloc >= (unsigned int)block->size);
		numAlloc -= block->size;
		
#if defined(MMGC_MEMORY_PROFILER) && defined(MMGC_MEMORY_INFO)
		if(profiler)
			block->freeTrace = profiler->GetStackTrace();
#endif
	
#ifdef MMGC_MEMORY_PROFILER
		if(profile && HooksEnabled() && profiler) {
			profiler->RecordDeallocation(item, block->size * kBlockSize);
		}
#endif

		FreeBlock(block);
	}

	void GCHeap::Decommit()
	{
		// keep at least initialSize free 
		if(!config.returnMemory)
			return;
		
		size_t heapSize = GetTotalHeapSize();
		size_t freeSize = GetFreeHeapSize();
		
		size_t decommitSize;
		// commit if > kDecommitThresholdPercentage is free
		if(freeSize * 100 > heapSize * kDecommitThresholdPercentage)
			decommitSize = int((freeSize * 100 - heapSize * kDecommitThresholdPercentage) / 100);
		else
			return;
				
		//  Don't decommit more than our initial config size.
		if (heapSize - decommitSize < config.initialSize)
		{
			decommitSize = heapSize - config.initialSize;
		}

		// don't trifle
		if(decommitSize < (size_t)kMinHeapIncrement)
			return;

		MMGC_LOCK(m_spinlock);

	restart:

		// search from the end of the free list so we decommit big blocks
		HeapBlock *freelist = freelists+kNumFreeLists-1;

		HeapBlock *endOfBigFreelists = &freelists[GetFreeListIndex(1)];

		for (; freelist >= endOfBigFreelists && decommitSize > 0; freelist--)
		{
			HeapBlock *block = freelist;
			while ((block = block->prev) != freelist && decommitSize > 0)
			{
				// decommitting already decommitted blocks doesn't help
				// temporary replacement for commented out conditional below
				GCAssert(block->size != 0);
				if(!block->committed /*|| block->size == 0*/)
					continue;

				if(config.useVirtualMemory)
				{
					RemoveFromList(block);
					if((size_t)block->size > decommitSize)
					{
						HeapBlock *newBlock = Split(block, (int)decommitSize);
						AddToFreeList(newBlock);
					}
					
					Region *region = AddrToRegion(block->baseAddr);
					if(config.trimVirtualMemory &&
					   freeSize * 100 > heapSize * kReleaseThresholdPercentage &&
					   // if block is as big or bigger than a region, free the whole region
					   block->baseAddr <= region->baseAddr && 
					   region->reserveTop <= block->endAddr() )
	   				{

						if(block->baseAddr < region->baseAddr)
						{
							HeapBlock *newBlock = Split(block, int((region->baseAddr - block->baseAddr) / kBlockSize));
							AddToFreeList(block);
							block = newBlock;
						}
						if(block->endAddr() > region->reserveTop)
						{
							HeapBlock *newBlock = Split(block, int((region->reserveTop - block->baseAddr) / kBlockSize));
							AddToFreeList(newBlock);
						}

						decommitSize -= block->size;
						RemoveBlock(block);
						goto restart;
					}
					else if(VMPI_decommitMemory(block->baseAddr, block->size * kBlockSize))
					{
						block->committed = false;
						block->dirty = false;
						decommitSize -= block->size;
						if(config.verbose) {
							GCLog("decommitted %d page block from %p\n", block->size, block->baseAddr);
						}
					}
					else
					{
#ifdef MMGC_MAC
						// this can happen on mac where we release and re-reserve the memory and another thread may steal it from us
						RemovePartialBlock(block);
						goto restart;
#else
						// if the VM API's fail us bail
						VMPI_abort(); 
#endif
					}
					
					numDecommitted += block->size;
					
					// merge with previous/next if not in use and not committed
					HeapBlock *prev = block - block->sizePrevious;
					if(block->sizePrevious != 0 && !prev->committed && !prev->inUse()) {
						RemoveFromList(prev);
						
						prev->size += block->size;
						
						block->size = 0;
						block->sizePrevious = 0;
						block->baseAddr = 0;
						
						block = prev;
					}
					
					HeapBlock *next = block + block->size;
					if(next->size != 0 && !next->committed && !next->inUse()) {
						RemoveFromList(next);
						
						block->size += next->size;
						
						next->size = 0;
						next->sizePrevious = 0;
						next->baseAddr = 0;
					}
					
					next = block + block->size;
					next->sizePrevious = block->size;
					
					// add this block to the back of the bus to make sure we consume committed memory
					// first
					HeapBlock *backOfTheBus = &freelists[kNumFreeLists-1];
					HeapBlock *pointToInsert = backOfTheBus;
					while ((pointToInsert = pointToInsert->next) !=  backOfTheBus) {
						if (pointToInsert->size >= block->size && !pointToInsert->committed) {
							break;
						}
					}
					AddToFreeList(block, pointToInsert);
					
					// so we keep going through freelist properly
					block = freelist;

				} else { // not using virtual memory

					// if we aren't using mmap we can only do something if the block maps to a region
					// that is completely empty
					Region *region = AddrToRegion(block->baseAddr);
					if(block->baseAddr == region->baseAddr && // beginnings match
					   region->commitTop == block->baseAddr + block->size*kBlockSize) {
						
						RemoveFromList(block);
						
						RemoveBlock(block);
						
						goto restart;
					}
				}
			}
		}

		if(config.verbose)
			DumpHeapRep();
		CheckForStatusReturnToNormal();
	}

	// m_spinlock is held
	void GCHeap::CheckForHardLimitExceeded()
	{
		if (!HardLimitExceeded())
			return;
		
		// if we're already failing then fail hard
		if (status == kMemHardLimit)
			Abort();
			
		// bail on double faults
		if(statusNotificationBeingSent)
			Abort();
				
		// invoke callbacks to free up memory
		StatusChangeNotify(kMemHardLimit);
	}

	// m_spinlock is held
	void GCHeap::CheckForSoftLimitExceeded(size_t request)
	{
		if(config.heapSoftLimit == 0 || status != kMemNormal || !SoftLimitExceeded())
			return;

		size_t externalBlocks = externalPressure / kBlockSize;
		GCDebugMsg(false, "*** Alloc exceeded softlimit: ask for %u, usedheapsize =%u, totalHeap =%u, of which external =%u\n", 
				   unsigned(request), 
				   unsigned(GetUsedHeapSize() + externalBlocks), 
				   unsigned(GetTotalHeapSize() + externalBlocks),
				   unsigned(externalBlocks));
		StatusChangeNotify(kMemSoftLimit);
	}
	
	// m_spinlock is held
	void GCHeap::CheckForStatusReturnToNormal()
	{
		if(!statusNotificationBeingSent && statusNotNormalOrAbort())
		{
			size_t externalBlocks = externalPressure / kBlockSize;
			size_t total = GetTotalHeapSize() + externalBlocks;

			// return to normal if we drop below heapSoftLimit
			if(config.heapSoftLimit != 0 && status == kMemSoftLimit)
			{
				if (!SoftLimitExceeded())
				{
					size_t used = GetUsedHeapSize() + externalBlocks;
					GCDebugMsg(false, "### Alloc dropped below softlimit: usedheapsize =%u, totalHeap =%u, of which external =%u\n", 
							   unsigned(used), 
							   unsigned(total),
							   unsigned(externalBlocks) );
					StatusChangeNotify(kMemNormal);
				}
			}
			// or if we shrink to below %10 of the max
			else if ((maxTotalHeapSize / kBlockSize + externalBlocks) * 9 > total * 10)
				StatusChangeNotify(kMemNormal);
		}
	}

#ifdef MMGC_MAC

	void GCHeap::RemovePartialBlock(HeapBlock *block)
	{
		if(config.verbose) {
			GCLog("Removing block %p %d\n", block->baseAddr, block->size);
			DumpHeapRep();
		}

		{
			Region *region = AddrToRegion(block->baseAddr);
			if(region->baseAddr == block->baseAddr && region->reserveTop == block->endAddr()) {
				RemoveBlock(block);
				return;
			}
		}

		while(AddrToRegion(block->baseAddr) != AddrToRegion(block->endAddr()-1)) {
			// split block into parts mapping to regions
			Region *r = AddrToRegion(block->baseAddr);
			size_t numBlocks = (r->commitTop - block->baseAddr) / kBlockSize;
			char *next = Split(block, numBlocks)->baseAddr;
			// remove it
			RemovePartialBlock(block);
			block = AddrToBlock(next);
		}

		Region *region = AddrToRegion(block->baseAddr);
		// save these off since we'll potentially shift region
		char *regionBaseAddr = region->baseAddr;
		size_t regionBlockId = region->blockId;

		// if we don't line up with beginning or end we need a new region
		if(block->baseAddr != region->baseAddr && region->commitTop != block->endAddr()) {
			if(nextRegion == NULL) {
				// usually this is handled in ExpandHeap but could run out here
				bool zero = false;
				block = AllocBlock(1, zero);
				if(block) {
					nextRegion = (Region*)(void *)block->baseAddr;	
				} else {
					ExpandHeap(1, false);
					// just calling ExpandHeap should set nextRegion
					GCAssertMsg(nextRegion != NULL, "ExpandHeap didn't set nextRegion");
				}
			}

			NewRegion(block->endAddr(), region->reserveTop, 
					  region->commitTop > block->endAddr() ? region->commitTop : block->endAddr(),
					  region->blockId + (block->endAddr() - region->baseAddr) / kBlockSize);
			
			if(region->baseAddr != block->baseAddr) {
				// end this region at the start of block going away
				region->reserveTop = block->baseAddr;			
				if(region->commitTop > block->baseAddr)
					region->commitTop = block->baseAddr;
			}

		} else if(region->baseAddr == block->baseAddr) {
			region->blockId += block->size;
			region->baseAddr = block->endAddr();
		} else if(region->commitTop == block->endAddr()) {
			// end this region at the start of block going away
			region->reserveTop = block->baseAddr;
			if(region->commitTop > block->baseAddr)
				region->commitTop = block->baseAddr;			
		} else {
			GCAssertMsg(false, "This shouldn't be possible");
		}


		// create temporary region for this block
		Region temp(this, block->baseAddr, block->endAddr(), block->endAddr(), regionBlockId +  (block->baseAddr - regionBaseAddr) / kBlockSize);

		RemoveBlock(block);
		
		// pop temp from freelist, put there by RemoveBlock
		freeRegion = *(Region**)freeRegion;

		

#ifdef DEBUG
		// doing this here is an extra validation step
		if(config.verbose) 
		{
			DumpHeapRep();
		}
#endif
	}

#endif

	void GCHeap::RemoveBlock(HeapBlock *block)
	{	
		Region *region = AddrToRegion(block->baseAddr);
		
		GCAssert(region->baseAddr == block->baseAddr);
		GCAssert(region->reserveTop == block->endAddr());
		
		size_t newBlocksLen = blocksLen - block->size;

		HeapBlock *nextBlock = block + block->size;

		bool need_sentinel = false;
		bool remove_sentinel = false;

		if( block->sizePrevious && nextBlock->size ) {
			// This block is contiguous with the blocks before and after it
			// so we need to add a sentinel
			need_sentinel = true;
		}
		else if ( !block->sizePrevious && !nextBlock->size ) {
			// the block is not contigous with the block before or after it - we need to remove a sentinel
			// since there would already be one on each side.
			remove_sentinel = true;
		}

		// update nextblock's sizePrevious
		nextBlock->sizePrevious = need_sentinel ? 0 : block->sizePrevious;
		
		// Add space for the sentinel - the remaining blocks won't be contiguous
		if(need_sentinel)
			++newBlocksLen;
		else if(remove_sentinel)
			--newBlocksLen;

		// just re-use blocks; small wastage possible
		HeapBlock *newBlocks = blocks;

		// the memmove will overwrite this so save it
		size_t blockSize = block->size;

		size_t offset = int(block-blocks);
		int32_t sen_offset = 0;
		HeapBlock *src = block + block->size;

		if( need_sentinel ) {
			offset = int(block-blocks)+1;
			sen_offset = 1;
			HeapBlock* sentinel = newBlocks + (block-blocks);
			sentinel->baseAddr = NULL;
			sentinel->size = 0;
			sentinel->sizePrevious = block->sizePrevious;
			sentinel->prev = NULL;
			sentinel->next = NULL;
#if defined(MMGC_MEMORY_PROFILER) && defined(MMGC_MEMORY_INFO)
			sentinel->allocTrace = 0;
#endif
		}
		else if( remove_sentinel ) {
			// skip trailing sentinel
			src++;
			sen_offset = -1;
		}
		
		// copy blocks after
		int lastChunkSize = int((blocks + blocksLen) - src);
		GCAssert(lastChunkSize + offset == newBlocksLen);
		memmove(newBlocks + offset, src, lastChunkSize * sizeof(HeapBlock));

		// Fix up the prev/next pointers of each freelist.  This is a little more complicated
		// than the similiar code in ExpandHeap because blocks after the one we are free'ing
		// are sliding down by block->size
		HeapBlock *fl = freelists;
		for (uint32_t i=0; i<kNumFreeLists; i++) {
			HeapBlock *temp = fl;
			do {
				if (temp->prev != fl) {
					if(temp->prev > block) {
						temp->prev = newBlocks + (temp->prev-blocks-blockSize) + sen_offset;
					}
				}
				if (temp->next != fl) {
					if(temp->next > block) {
						temp->next = newBlocks + (temp->next-blocks-blockSize) + sen_offset;
					}
				}
			} while ((temp = temp->next) != fl);
			fl++;
		}
		
		// Need to decrement blockId for regions in blocks after block
		Region *r = lastRegion;
		while(r) {
			if(r->blockId > region->blockId) {
				r->blockId -= (blockSize-sen_offset);
			}
			r = r->prev;
		}

		blocksLen = newBlocksLen;
		RemoveRegion(region);

		// make sure we did everything correctly
		CheckFreelist();
		ValidateHeapBlocks();
	}

	void GCHeap::ValidateHeapBlocks()
	{
#ifdef _DEBUG
		// iterate through HeapBlocks making sure:
		// non-contiguous regions have a sentinel
		HeapBlock *block = blocks;
		while(block - blocks < (intptr_t)blocksLen) {
			Region *r = AddrToRegion(block->baseAddr);
			if(r && r->baseAddr == block->baseAddr)
				GCAssert(r->blockId == (size_t)(block-blocks));

			HeapBlock *next = NULL;
			if(block->size) {
				next = block + block->size;
				GCAssert(next->sizePrevious == block->size);
			}
			HeapBlock *prev = NULL;
			if(block->sizePrevious) {
				prev = block - block->sizePrevious;
				GCAssert(prev->size == block->sizePrevious);
			} else if(block != blocks) {
				// I have no prev and I'm not the first, check sentinel
				HeapBlock *sentinel = block-1;
				GCAssert(sentinel->baseAddr == NULL);
				GCAssert(sentinel->size == 0);
				GCAssert(sentinel->sizePrevious != 0);
			}
			if(block->baseAddr) {
				if(prev)
					GCAssert(block->baseAddr == prev->baseAddr + (kBlockSize * prev->size));
				block = next;
				// we should always end on a sentinel
				GCAssert(next - blocks < (int)blocksLen);
			} else {
				// block is a sentinel
				GCAssert(block->size == 0);
				// FIXME: the following asserts are firing and we need to understand why, could be bugs
				// make sure last block ends at commitTop
				Region *prevRegion = AddrToRegion(prev->baseAddr + (prev->size*kBlockSize) - 1);
				GCAssert(prev->baseAddr + (prev->size*kBlockSize) == prevRegion->commitTop);
				block++;
				// either we've reached the end or the next isn't a sentinel
				GCAssert(block - blocks == (intptr_t)blocksLen || block->size != 0);
			}
		}
		GCAssert(block - blocks == (intptr_t)blocksLen);
#endif
	}

	GCHeap::Region *GCHeap::AddrToRegion(const void *item) const
	{
		// Linear search of regions list to find this address.
		// The regions list should usually be pretty short.
		for (Region *region = lastRegion;
			 region != NULL;
			 region = region->prev)
		{
			if (item >= region->baseAddr && item < region->reserveTop) {
				return region;
			}
		}
		return NULL;
	}

	GCHeap::HeapBlock* GCHeap::AddrToBlock(const void *item) const
	{
		Region *region = AddrToRegion(item);
		if(region) {
			size_t index = ((char*)item - region->baseAddr) / kBlockSize;
			HeapBlock *b = blocks + region->blockId + index;
			GCAssert(item >= b->baseAddr && item < b->baseAddr + b->size * GCHeap::kBlockSize);
			return b;
		}
		return NULL;
	}
	
	GCHeap::HeapBlock* GCHeap::AllocBlock(size_t size, bool& zero)
	{
		uint32_t startList = GetFreeListIndex(size);
		HeapBlock *freelist = &freelists[startList];

		HeapBlock *decommittedSuitableBlock = NULL;
		HeapBlock *blockToUse = NULL;

		for (uint32_t i = startList; i < kNumFreeLists; i++)
		{
			// Search for a big enough block in free list
			HeapBlock *block = freelist;
			while ((block = block->next) != freelist)
			{
				if (block->size >= size && block->committed) 
				{
					blockToUse = block;
					goto foundone;
				}

				if(config.useVirtualMemory)
				{
					// if the block isn't committed see if this request can be met with by committing
					// it and combining it with its neighbors
					if(!block->committed && !decommittedSuitableBlock)
					{
						size_t totalSize = block->size;
						
						// first try predecessors
						HeapBlock *firstFree = block;
						
						// loop because we could have interleaved committed/non-committed blocks
						while(totalSize < size && firstFree->sizePrevious != 0)
						{	
							HeapBlock *prevBlock = firstFree - firstFree->sizePrevious;
							if(!prevBlock->inUse() && prevBlock->size > 0) {
								totalSize += prevBlock->size;
								firstFree = prevBlock;
							} else {
								break;
							}
						}
						
						if(totalSize > size) {
							decommittedSuitableBlock = firstFree;
						} else {
							// now try successors
							HeapBlock *nextBlock = block + block->size;
							while(nextBlock->size > 0 && !nextBlock->inUse() && totalSize < size) {
								totalSize += nextBlock->size;
								nextBlock = nextBlock + nextBlock->size;
							}
							
							if(totalSize > size) {
								decommittedSuitableBlock = firstFree;
							}
						}
					}
				}
			}
			freelist++;
		}	
		
	foundone:

		if(blockToUse)
		{				
			RemoveFromList(blockToUse);

			if(blockToUse->size > size)
			{
				HeapBlock *newBlock = Split(blockToUse, size);
							
				// Add the newly created block to the free list
				AddToFreeList(newBlock);
			}
							
			CheckFreelist();
			
			zero = blockToUse->dirty && zero;
			
			#ifdef _DEBUG
			if (!blockToUse->dirty)
			{
				union {
					const char* base_c;
					const uint32_t* base_u;
				};
				base_c = blockToUse->baseAddr;
				GCAssert(*base_u == 0);
			}
			#endif
			return blockToUse;
		}

		if(config.useVirtualMemory && decommittedSuitableBlock)
		{
			// first handle case where its too big
			if(decommittedSuitableBlock->size > size)
			{				
				size_t toCommit = size > kMinHeapIncrement ? size : kMinHeapIncrement;

				if(toCommit > decommittedSuitableBlock->size)
					toCommit = decommittedSuitableBlock->size;

				RemoveFromList(decommittedSuitableBlock);
				
				// first split off part we're gonna commit
				if(decommittedSuitableBlock->size > toCommit) {
					HeapBlock *newBlock = Split(decommittedSuitableBlock, toCommit);

					// put the still uncommitted part back on freelist
					AddToFreeList(newBlock);
				}
				
				Commit(decommittedSuitableBlock);

				if(toCommit > size) {
					HeapBlock *newBlock = Split(decommittedSuitableBlock, size);
					AddToFreeList(newBlock);
				}
			}
			else // too small
			{
				// need to stitch blocks together committing uncommitted blocks
				HeapBlock *block = decommittedSuitableBlock;
				RemoveFromList(block);

				size_t amountRecommitted = block->committed ? 0 : block->size;
					
				while(block->size < size)
				{
					HeapBlock *nextBlock = block + block->size;

					RemoveFromList(nextBlock);
						
					// Increase size of current block
					block->size += nextBlock->size;
					amountRecommitted += nextBlock->committed ? 0 : nextBlock->size;

					nextBlock->size = 0;
					nextBlock->baseAddr = 0;
					nextBlock->sizePrevious = 0;

					block->dirty |= nextBlock->dirty;
				}

				GCAssert(amountRecommitted > 0);

				if(!VMPI_commitMemory(block->baseAddr, block->size * kBlockSize)) 
				{
					GCAssert(false);
				}
				if(config.verbose)
					GCLog("recommitted %d pages\n", amountRecommitted);
				numDecommitted -= amountRecommitted;
				block->committed = true;

				GCAssert(decommittedSuitableBlock->size >= size);

				// split last block
				if(block->size > size)
				{
					HeapBlock *newBlock = Split(block, size);
					AddToFreeList(newBlock);
				}
			}

			GCAssert(decommittedSuitableBlock->size == size);

			// update sizePrevious in next block
			HeapBlock *nextBlock = decommittedSuitableBlock + size;
			nextBlock->sizePrevious = size;

			CheckFreelist();

			return decommittedSuitableBlock;
		}
	
		CheckFreelist();
		return 0;
	}

	GCHeap::HeapBlock *GCHeap::Split(HeapBlock *block, size_t size)
	{
		GCAssert(block->size > size);
		HeapBlock *newBlock = block + size;
		newBlock->baseAddr = block->baseAddr + kBlockSize * size;

		newBlock->size = block->size - size;
		newBlock->sizePrevious = size;
		newBlock->committed = block->committed;
		newBlock->dirty = block->dirty;
		block->size = size;

		// Update sizePrevious in block after that
		HeapBlock *nextBlock = newBlock + newBlock->size;
		nextBlock->sizePrevious = newBlock->size;
	
		return newBlock;
	}

	void GCHeap::Commit(HeapBlock *block)
	{
		if(!block->committed)
		{
			if(!VMPI_commitMemory(block->baseAddr, block->size * kBlockSize)) 
			{
				GCAssert(false);
			}
			if(config.verbose) {
				GCLog("recommitted %d pages\n", block->size);
				DumpHeapRep();
			}
			numDecommitted -= block->size;
			block->committed = true;
			block->dirty = false;
		}
	}

#ifdef _DEBUG
	// Non-debug version in GCHeap.h
	void GCHeap::CheckFreelist()
	{
		HeapBlock *freelist = freelists;
		for (uint32_t i = 0; i < kNumFreeLists; i++)
		{
			HeapBlock *block = freelist;
			while((block = block->next) != freelist)
			{
				GCAssert(block != block->next);
				GCAssert(block != block->next->next || block->next == freelist);
				if(block->sizePrevious)
				{
					HeapBlock *prev = block - block->sizePrevious;
					GCAssert(block->sizePrevious == prev->size);
				}
			}
			freelist++;
		}
#if 0
// Debugging code to find problems with block/region layout
// This code is slow, but can be useful for tracking down issues
// It verifies that the memory for each block corresponds to one or more regions
// and that each region points to a valid starting block
  		Region* r = lastRegion;

		int block_idx = 0;
		bool errors =false;
		for(block_idx = 0; block_idx < blocksLen; ++block_idx){
			HeapBlock* b = blocks + block_idx;
			
			if( !b->size )
				continue;

			int contig_size = 0;
			r = lastRegion;

			while( r ){
				if(b->baseAddr >= r->baseAddr && b->baseAddr < r->reserveTop ) {
					// starts in this region
					char* end = b->baseAddr + b->size*kBlockSize;
					if(end > (r->reserveTop + contig_size) ){
						GCLog("error, block %d %p %d did not find a matching region\n", block_idx, b->baseAddr, b->size);
						GCLog("Started in region %p - %p, contig size: %d\n", r->baseAddr, r->reserveTop, contig_size);
						errors = true;
						break;
					}
				}
				else if( r->prev && r->prev->reserveTop==r->baseAddr){
					contig_size +=r->reserveTop - r->baseAddr;
				}
				else{
					contig_size = 0;
				}
						
				r = r->prev;
			}
		}

		while(r)
			{
				if(!blocks[r->blockId].size){
                    for( int i = r->blockId-1; i >= 0 ; --i )
                        if( blocks[i].size){
							//Look for spanning blocks
                            if( ((blocks[i].baseAddr + blocks[i].size*kBlockSize) <= r->baseAddr) ) {
                                GCLog("Invalid block id for region %p-%p %d\n", r->baseAddr, r->reserveTop, i);
								errors =true;
								break;
							}
                            else
                                break;
                        }
				}
				r = r->prev;
		   }
		if( errors ){
			r = lastRegion;
			while(r) {
				GCLog("%p - %p\n", r->baseAddr, r->reserveTop);
				r = r->prev;
			}
			for(int b = 0; b < blocksLen; ++b ){
				if(!blocks[b].size)
					continue;
				GCLog("%d %p %d\n", b, blocks[b].baseAddr, blocks[b].size); 
			}
			asm("int3");
		}
#endif	
	}
#endif // DEBUG

	bool GCHeap::BlocksAreContiguous(void *item1, void *item2)
	{
		Region *r1 = AddrToRegion(item1);
		Region *r2 = AddrToRegion(item2);
		return r1 == r2 || r1->reserveTop == r2->baseAddr;
	}

	void GCHeap::AddToFreeList(HeapBlock *block)
	{
		int index = GetFreeListIndex(block->size);
		HeapBlock *freelist = &freelists[index];

		HeapBlock *pointToInsert = freelist;
		
		// Note: We don't need to bother searching for the right
		// insertion point if we know all blocks on this free list
		// are the same size.
		if (block->size >= kUniqueThreshold) {
			while ((pointToInsert = pointToInsert->next) != freelist) {
				if (pointToInsert->size >= block->size) {
					break;
				}
			}
		}

		AddToFreeList(block, pointToInsert);
	}
		
	void GCHeap::AddToFreeList(HeapBlock *block, HeapBlock* pointToInsert)
	{
		CheckFreelist();

		block->next = pointToInsert;
		block->prev = pointToInsert->prev;
		block->prev->next = block;
		pointToInsert->prev = block;

		CheckFreelist();
	}						   

	void GCHeap::FreeBlock(HeapBlock *block)
	{
		GCAssert(block->inUse());
	
		// big block's that map to a region are free'd right away
		Region *r = AddrToRegion(block->baseAddr);
		if(block->baseAddr == r->baseAddr && block->endAddr() == r->reserveTop)
		{
			RemoveBlock(block);
			return;
		}
		
#ifdef _DEBUG
		// trash it. fb == free block
		VMPI_memset(block->baseAddr, 0xfb, block->size * kBlockSize);
#endif
		
		// Try to coalesce this block with its predecessor
		if(block->sizePrevious)
		{
			HeapBlock *prevBlock = block - block->sizePrevious;
			if (!prevBlock->inUse() && prevBlock->committed) 
			{
				// Remove predecessor block from free list
				RemoveFromList(prevBlock);
				
				// Increase size of predecessor block
				prevBlock->size += block->size;
				
				block->size = 0;
				block->sizePrevious = 0;
				block->baseAddr = 0;				
				
				block = prevBlock;
			}
		}

		// Try to coalesce this block with its successor
		HeapBlock *nextBlock = block + block->size;

		GCAssert(block->size != 0);

		if (!nextBlock->inUse() && nextBlock->committed) {
			// Remove successor block from free list
			RemoveFromList(nextBlock);

			// Increase size of current block
			block->size += nextBlock->size;
			nextBlock->size = 0;
			nextBlock->baseAddr = 0;
			nextBlock->sizePrevious = 0;
		}

		// Update sizePrevious in the next block
		nextBlock = block + block->size;
		nextBlock->sizePrevious = block->size;

		// Add this block to the right free list
		block->dirty = true;

		AddToFreeList(block);

		CheckFreelist();
	}

	void GCHeap::ExpandHeap(size_t askSize, bool canFail)
	{
		if (canFail) {
			// once we hit soft limit don't allow canFail allocs
			if(status == kMemSoftLimit)
				return;

			// random policy choice: don't invoke OOM callbacks for canFail allocs
			if (HardLimitExceeded())
				return;
		}
		
		// Check the hard limit, trigger cleanup if hit
		CheckForHardLimitExceeded();
		
		if (!ExpandHeapInternal(askSize))
			Abort();
		
		// The guard on instance being non-NULL is a hack, to be fixed later (now=2009-07-20).
		// Some VMPI layers (WinMo is at least one of them) try to grab the GCHeap instance to get
		// at the map of private pages.  But the GCHeap instance is not available during the initial
		// call to ExpandHeap.  So sidestep that problem here.

		if (instance != NULL) {
			// GetTotalHeapSize is probably fairly cheap; even so this strikes me
			// as a bit of a hack.
			size_t heapSizeNow = GetTotalHeapSize() * kBlockSize;
			if (heapSizeNow > maxTotalHeapSize) {
				maxTotalHeapSize = heapSizeNow;
#ifdef MMGC_POLICY_PROFILING
				maxPrivateMemory = VMPI_getPrivateResidentPageCount() * VMPI_getVMPageSize();
#endif
			}
		}
	} 

	bool GCHeap::HardLimitExceeded()
	{
		return GetTotalHeapSize() + externalPressure/kBlockSize > config.heapLimit;
	}
	
	bool GCHeap::SoftLimitExceeded()
	{
		return GetTotalHeapSize() + externalPressure/kBlockSize > config.heapSoftLimit;
	}
	
#define roundUp(_s, _inc) (((_s + _inc - 1) / _inc) * _inc)
	 
	bool GCHeap::ExpandHeapInternal(size_t askSize)
	{
		size_t size = askSize;

#ifdef _DEBUG
		// Turn this switch on to test bridging of contiguous
		// regions.
		bool test_bridging = false;
		size_t defaultReserve = test_bridging ? (size+kMinHeapIncrement) : kDefaultReserve;
#else
		const size_t defaultReserve = kDefaultReserve;
#endif

		if (HardLimitExceeded())
			return false;

		char *baseAddr = NULL;
		char *newRegionAddr = NULL;
		size_t newRegionSize = 0;
		bool contiguous = false;
		size_t commitAvail = 0;

		// Round up to the nearest kMinHeapIncrement
		size = roundUp(size, kMinHeapIncrement);

		// when we allocate a new region the space needed for the HeapBlocks, if it won't fit 
		// in existing space it must fit in new space so we may need to increase the new space

		HeapBlock *newBlocks = blocks;
		
		if(blocksLen != 0 || // first time through just take what we need out of initialSize instead of adjusting
		   config.initialSize == 0) // unless initializeSize is zero of course
		{
			int extraBlocks = 1; // for potential new sentinel
			if(nextRegion == NULL) {
				extraBlocks++; // may need a new page for regions
			}
			size_t curHeapBlocksSize = blocks ? AddrToBlock(blocks)->size : 0;
			size_t newHeapBlocksSize = numHeapBlocksToNumBlocks(blocksLen + size + extraBlocks);

			// size is based on newSize and vice versa, loop to settle (typically one loop, sometimes two)
			while(newHeapBlocksSize > curHeapBlocksSize) 
			{
				// use askSize so HeapBlock's can fit in rounding slop
				size = roundUp(askSize + newHeapBlocksSize + extraBlocks, kMinHeapIncrement);

				// tells us use new memory for blocks below
				newBlocks = NULL;

				// since newSize is based on size we have to repeat in case it changes
				curHeapBlocksSize = newHeapBlocksSize;
				newHeapBlocksSize = numHeapBlocksToNumBlocks(blocksLen + size + extraBlocks);
			}
		}		

		if(config.useVirtualMemory)
		{
			Region *region = lastRegion;
			if (region != NULL)
			{
				commitAvail = (int)((region->reserveTop - region->commitTop) / kBlockSize);
				
				// Can this request be satisfied purely by committing more memory that
				// is already reserved?
				if (size <= commitAvail) {
					if (VMPI_commitMemory(region->commitTop, size * kBlockSize))
					{
						// Succeeded!
						baseAddr = region->commitTop;

						// check for continuity, we can only be contiguous with the end since
						// we don't have a "block insert" facility
						HeapBlock *last = &blocks[blocksLen-1] - blocks[blocksLen-1].sizePrevious;
						contiguous = last->baseAddr + last->size * kBlockSize == baseAddr;
						
						// Update the commit top.
						region->commitTop += size*kBlockSize;
						
						// Go set up the block list.
						goto gotMemory;
					}
					else
					{
						// If we can't commit memory we've already reserved,
						// no other trick is going to work.  Fail.
						return false;
					}
				}
				
				// Try to reserve a region contiguous to the last region.
				
				// - Try for the "default reservation size" if it's larger than
				//   the requested block.
				if (defaultReserve > size) {
					newRegionAddr = (char*) VMPI_reserveMemoryRegion(region->reserveTop,
												  defaultReserve * kBlockSize);
					newRegionSize = defaultReserve;
				}
				
				// - If the default reservation size didn't work or isn't big
				//   enough, go for the exact amount requested, minus the
				//   committable space in the current region.
				if (newRegionAddr == NULL) {
					newRegionAddr = (char*) VMPI_reserveMemoryRegion(region->reserveTop,
												  (size - commitAvail)*kBlockSize);
					newRegionSize = size - commitAvail;
				}
				
				if (newRegionAddr != NULL) {
					// We were able to reserve some space.
					
					// Commit available space from the existing region.
					if (commitAvail != 0) {
						if (!VMPI_commitMemory(region->commitTop, commitAvail * kBlockSize))
						{
							// We couldn't commit even this space.  We're doomed.
							// Un-reserve the space we just reserved and fail.
							ReleaseMemory(newRegionAddr, newRegionSize);
							return false;
						}
					}
					
					// Commit needed space from the new region.
					if (!VMPI_commitMemory(newRegionAddr, (size - commitAvail) * kBlockSize))
					{
						// We couldn't commit this space.  We can't meet the
						// request.  Un-commit any memory we just committed,
						// un-reserve any memory we just reserved, and fail.
						if (commitAvail != 0) {
							VMPI_decommitMemory(region->commitTop,
										   commitAvail * kBlockSize);
						}
						ReleaseMemory(newRegionAddr,
									  (size-commitAvail)*kBlockSize);
						return false;
					}
					
					// We successfully reserved a new contiguous region
					// and committed the memory we need.  Finish up.
					baseAddr = region->commitTop;
					region->commitTop = lastRegion->reserveTop;

					// check for continuity, we can only be contiguous with the end since
					// we don't have a "block insert" facility
					HeapBlock *last = &blocks[blocksLen-1] - blocks[blocksLen-1].sizePrevious;
					contiguous = last->baseAddr + last->size * kBlockSize == baseAddr;
					
					goto gotMemory;
				}
			}

			// We were unable to allocate a contiguous region, or there
			// was no existing region to be contiguous to because this
			// is the first-ever expansion.  Allocate a non-contiguous region.
			
			// Don't use any of the available space in the current region.
			commitAvail = 0;
			
			// - Go for the default reservation size unless the requested
			//   size is bigger.
			if (size < defaultReserve) {
				newRegionAddr = (char*) VMPI_reserveMemoryRegion(NULL,
												  defaultReserve*kBlockSize);
				newRegionSize = defaultReserve;
			}
			
			// - If that failed or the requested size is bigger than default,
			//   go for the requested size exactly.
			if (newRegionAddr == NULL) {
				newRegionAddr = (char*) VMPI_reserveMemoryRegion(NULL,
											  size*kBlockSize);
				newRegionSize = size;
			}
			
			// - If that didn't work, give up.
			if (newRegionAddr == NULL) {
				return false;
			}
			
			// - Try to commit the memory.
			if (VMPI_commitMemory(newRegionAddr,
							 size*kBlockSize) == 0)
			{
				// Failed.  Un-reserve the memory and fail.
				ReleaseMemory(newRegionAddr, newRegionSize*kBlockSize);
				return false;
			}
			
			// If we got here, we've successfully allocated a
			// non-contiguous region.
			baseAddr = newRegionAddr;
			contiguous = false;

		}
		else
		{		
			// Allocate the requested amount of space as a new region.
			newRegionAddr = (char*)VMPI_allocateAlignedMemory(size * kBlockSize);
			baseAddr = newRegionAddr;
			newRegionSize = size;
			
			// If that didn't work, give up.
			if (newRegionAddr == NULL) {
				return false;
			}
		}

	gotMemory:

		// If we were able to allocate a contiguous block, remove
		// the old top sentinel.
		if (contiguous) {
			blocksLen--;
		}

		// Expand the block list.
		size_t newBlocksLen = blocksLen + size;

		// Add space for the "top" sentinel
		newBlocksLen++;

		if (!newBlocks) {
 			newBlocks = (HeapBlock*)(void *)baseAddr;
		}
		
		// Copy all the existing blocks.
		if (blocks && blocks != newBlocks) {
			VMPI_memcpy(newBlocks, blocks, blocksLen * sizeof(HeapBlock));

			// Fix up the prev/next pointers of each freelist.
			HeapBlock *freelist = freelists;
			for (uint32_t i=0; i<kNumFreeLists; i++) {
				HeapBlock *temp = freelist;
				do {
					if (temp->prev != freelist) {
						temp->prev = newBlocks + (temp->prev-blocks);
					}
					if (temp->next != freelist) {
						temp->next = newBlocks + (temp->next-blocks);
					}
				} while ((temp = temp->next) != freelist);
				freelist++;
			}
			CheckFreelist();
		}

		// Create a single free block for the new space,
		// and add it to the free list.
		HeapBlock *block = newBlocks+blocksLen;
		block->baseAddr = baseAddr;
		block->size = size;
		block->sizePrevious = 0;

		// link up contiguous blocks
		if(blocksLen && contiguous)
		{
			// search backwards for first real block
			HeapBlock *b = &blocks[blocksLen-1];
			while(b->size == 0) 
			{
				b--;
				GCAssert(b >= blocks);
			}
			block->sizePrevious = b->size;
			GCAssert((block - block->sizePrevious)->size == b->size);
		}
		block->prev = NULL;
		block->next = NULL;
		block->committed = true;
		block->dirty = config.useVirtualMemory ? VMPI_areNewPagesDirty() : true;

#if defined(MMGC_MEMORY_PROFILER) && defined(MMGC_MEMORY_INFO)
		block->allocTrace = 0;
		block->freeTrace = 0;
#endif

		// if baseAddr was used for HeapBlocks split
		if((char*)newBlocks == baseAddr)
		{
			size_t numBlocksNeededForHeapBlocks = numHeapBlocksToNumBlocks(newBlocksLen);
			HeapBlock *next = Split(block, numBlocksNeededForHeapBlocks);
			// this space counts as used space
			numAlloc += numBlocksNeededForHeapBlocks;
			block = next;
		}

		// get space for region allocations
		if(nextRegion == NULL) {
			nextRegion = (Region*)(void *)block->baseAddr;
			HeapBlock *next = Split(block, 1);
			// this space counts as used space
			numAlloc++;
			numRegionBlocks++;
			block = next;
		}

		AddToFreeList(block);

		// Initialize the rest of the new blocks to empty.
		size_t freeBlockSize = block->size;

		for (uint32_t i=1; i < freeBlockSize; i++) {
			block++;
			block->baseAddr = NULL;
			block->size = 0;
			block->sizePrevious = 0;
			block->prev = NULL;
			block->next = NULL;
			block->committed = false;
			block->dirty = false;
#if defined(MMGC_MEMORY_PROFILER) && defined(MMGC_MEMORY_INFO)
			block->allocTrace = 0;
			block->freeTrace = 0;
#endif
		}

		// Fill in the sentinel for the top of the heap.
		block++;
		block->baseAddr     = NULL;
		block->size         = 0;
		block->sizePrevious = freeBlockSize;
		block->prev         = NULL;
		block->next         = NULL;
		block->committed    = false;
		block->dirty        = false;
#if defined(MMGC_MEMORY_PROFILER) && defined(MMGC_MEMORY_INFO)
		block->allocTrace = 0;
		block->freeTrace = 0;
#endif

		// save for free'ing
		void *oldBlocks = blocks;

		blocks = newBlocks;
		blocksLen = newBlocksLen;

		// free old blocks space using new blocks (FreeBlock poisons blocks so can't use old blocks)
		if (oldBlocks && oldBlocks != newBlocks) {
			HeapBlock *oldBlocksHB = AddrToBlock(oldBlocks);
			numAlloc -= oldBlocksHB->size;
			FreeBlock(oldBlocksHB);
		}

		// If we created a new region, save the base address so we can free later.		
		if (newRegionAddr) {
			/*	The mergeContiguousRegions bit is broken, since we
				loop over all regions we may be contiguous with an
				existing older HeapBlock and we don't support inserting a
				new address range arbritrarily into the HeapBlock
				array (contiguous regions must be contiguous heap
				blocks vis-a-vie the region block id) 
			if(contiguous &&
				config.mergeContiguousRegions) {
				lastRegion->reserveTop += newRegionSize*kBlockSize;
				lastRegion->commitTop +=
				(size-commitAvail)*kBlockSize;
				} else
			*/ {
				Region *newRegion = NewRegion(newRegionAddr,  // baseAddr
											  newRegionAddr+newRegionSize*kBlockSize, // reserve top
											  newRegionAddr+(size-commitAvail)*kBlockSize, // commit top
											  newBlocksLen-(size-commitAvail)-1); // block id
				
				if(config.verbose)
					GCLog("reserved new region, %p - %p %s\n",
						  newRegion->baseAddr,
						  newRegion->reserveTop,
						  contiguous ? "contiguous" : "non-contiguous");
			}
		}

		CheckFreelist();
		
		if(config.verbose) {
			GCLog("heap expanded by %d pages\n", size);
			DumpHeapRep();
		}
		ValidateHeapBlocks();
			
		// Success!
		return true;
	}

	void GCHeap::RemoveRegion(Region *region)
	{
		Region **next = &lastRegion;
		while(*next != region) 
			next = &((*next)->prev);
		*next = region->prev;
		ReleaseMemory(region->baseAddr,
					  region->reserveTop-region->baseAddr);		
		if(config.verbose) {
			GCLog("unreserved region 0x%p - 0x%p (commitTop: %p)\n", region->baseAddr, region->reserveTop, region->commitTop);
			DumpHeapRep();
		}
		FreeRegion(region);
	}

	void GCHeap::FreeAll()
	{
		// Release all of the heap regions
		while (lastRegion != NULL) {
			Region *region = lastRegion;
			lastRegion = lastRegion->prev;
			ReleaseMemory(region->baseAddr,
						  region->reserveTop-region->baseAddr);
		}
	}
	
#ifdef MMGC_HOOKS
	void GCHeap::AllocHook(const void *item, size_t askSize, size_t gotSize)
	{
		(void)item;
		(void)askSize;
		(void)gotSize;
		{
#ifdef MMGC_MEMORY_PROFILER
			MMGC_LOCK(m_spinlock);
			if(hasSpy) {
				VMPI_spyCallback();
			}
			if(profiler)
				profiler->RecordAllocation(item, askSize, gotSize);
#endif

		}
#ifdef MMGC_MEMORY_INFO
		DebugDecorate(item, gotSize);
#endif
#ifdef AVMPLUS_SAMPLER
		// this can't be called with the heap lock locked.
		avmplus::recordAllocationSample(item, gotSize);
#endif
	}

	void GCHeap::FinalizeHook(const void *item, size_t size)
	{
		(void)item,(void)size;
		{
#ifdef MMGC_MEMORY_PROFILER
			MMGC_LOCK(m_spinlock);
			if(profiler)
				profiler->RecordDeallocation(item, size);
#endif
		}
		
#ifdef AVMPLUS_SAMPLER
		avmplus::recordDeallocationSample(item, size);
#endif
	}

	void GCHeap::FreeHook(const void *item, size_t size, int poison)
	{
		(void)poison,(void)item,(void)size;
#ifdef MMGC_MEMORY_INFO
		DebugFree(item, poison, size);
#endif
	}
#endif // MMGC_HOOKS

	EnterFrame::EnterFrame() : m_heap(NULL), m_gc(NULL), m_collectingGC(NULL)
	{
		GCHeap *heap = GCHeap::GetGCHeap();
		if(heap->GetStackEntryAddress() == NULL) {
			m_heap = heap;
			heap->Enter(this);
		}
	}
	
	// this is the first thing we run after the Abort longjmp
	EnterFrame::~EnterFrame()
	{
		if(m_heap) {
			GCHeap *heap = m_heap;
			// this prevents us from doing multiple jumps in case leave results in more allocations
			m_heap = NULL;
			heap->Leave();
		}
	}
	
#ifdef MMGC_USE_SYSTEM_MALLOC
	void GCHeap::SystemOOMEvent(size_t size, int attempt)
	{
		(void)size;
		if (attempt == 0 && !statusNotificationBeingSent)
			StatusChangeNotify(kMemHardLimit);
		else
			Abort();
	}
#endif

	/*static*/
	void GCHeap::SignalObjectTooLarge()
	{
		GCLog("Implementation limit exceeded: attempting to allocate too-large object\n");
		GetGCHeap()->Abort();
	}

	/*static*/
	void GCHeap::SignalInconsistentHeapState(const char* reason)
	{
		GCAssert(!"Inconsistent heap state; aborting");
		GCLog("Inconsistent heap state: %s\n", reason);
		GetGCHeap()->Abort();
	}
	
	/*static*/
	void GCHeap::SignalExternalAllocation(size_t nbytes)
	{
		GCHeap* heap = GetGCHeap();
		
		MMGC_LOCK(heap->m_spinlock);
		
		heap->externalPressure += nbytes;

		// cleanup actions if necessary
		heap->CheckForHardLimitExceeded();
			
		// check again - if we still can't allocate then fail hard
		if (heap->HardLimitExceeded())
			heap->Abort();

		heap->CheckForSoftLimitExceeded((nbytes + kBlockSize - 1) / kBlockSize);	// size only used for GC messages, OK to round up
	}
	
	/*static*/
	void GCHeap::SignalExternalDeallocation(size_t nbytes)
	{
		GCHeap* heap = GetGCHeap();
		
		MMGC_LOCK(heap->m_spinlock);
		
		heap->externalPressure -= nbytes;
		heap->CheckForStatusReturnToNormal();
	}

	// This can *always* be called.  It will clean up the state on the current thread
	// if appropriate, otherwise do nothing.  It *must* be called by host code if the
	// host code jumps past an MMGC_ENTER instance.  (The Flash player does that, in
	// some circumstances.)
	
	/*static*/
	void GCHeap::SignalImminentAbort()
	{
		if (instance == NULL)
			return;
		EnterFrame* ef = GetGCHeap()->GetEnterFrame();
		if (ef == NULL)
			return;

		// We don't know if we're holding the lock but we can release it anyhow,
		// on the assumption that this operation will not cause problems if the
		// lock is not held or is held by another thread.
		//
		// Release lock so we don't deadlock if exit or longjmp end up coming
		// back to GCHeap (all callers must have this lock).

		VMPI_lockRelease(&instance->m_spinlock);
		
		// If the current thread is holding a lock for a GC that's not currently active on the thread
		// then break the lock: the current thread is collecting in that GC, but the Abort has cancelled
		// the collection.

		if (ef->m_collectingGC)
		{
			ef->m_collectingGC->SignalImminentAbort();
			ef->m_collectingGC = NULL;
		}

		if(ef->m_gc)
			ef->m_gc->SignalImminentAbort();
		
		// Clear the enterFrame because we're jumping past MMGC_ENTER.
		GetGCHeap()->enterFrame = NULL;
	}
	
	void GCHeap::Abort()
	{
		status = kMemAbort;
		EnterFrame *ef = enterFrame;
		GCLog("error: out of memory\n");
		
		// release lock so we don't deadlock if exit or longjmp end up coming
		// back to GCHeap (all callers must have this lock)
		VMPI_lockRelease(&m_spinlock);
		
		// Lock must not be held when we call VMPI_exit, deadlocks ensue on Linux
		if(config.OOMExitCode != 0) 
		{
			VMPI_exit(config.OOMExitCode);
		}

		if (ef != NULL)
		{
			// If the current thread is holding a lock for a GC that's not currently active on the thread
			// then break the lock: the current thread is collecting in that GC, but the Abort has cancelled
			// the collection.
			if (ef->m_collectingGC)
			{
				ef->m_collectingGC->SignalImminentAbort();
				ef->m_collectingGC = NULL;
			}
			if(ef->m_gc)
			{
				ef->m_gc->SignalImminentAbort();
			}
			// Guard against repeated jumps: ef->m_heap doubles as a flag.  We go Abort->longjmp->~EnterFrame->Leave
			// and Leave calls StatusChangeNotify and the host code might do another allocation during shutdown
			// in which case we want to go to VMPI_abort instead.  At that point m_heap will be NULL and the right
			// thing happens.
			if (ef->m_heap != NULL)
			{
				VMPI_longjmpNoUnwind(ef->jmpbuf, 1);
			}
		}
		GCAssertMsg(false, "MMGC_ENTER missing or we allocated more memory trying to shutdown");
		VMPI_abort();
	}
	
	void GCHeap::Enter(EnterFrame *frame)
	{
		enterCount++;
		enterFrame = frame;
	}

	void GCHeap::Leave()
	{
		GCHeap *heapToDestroy=NULL;
		{
			MMGC_LOCK(m_spinlock);

			if(status == kMemAbort && !abortStatusNotificationSent) {
				abortStatusNotificationSent = true;
				StatusChangeNotify(kMemAbort);
			}
		}
	
		EnterLock();				
		// do this after StatusChangeNotify it affects ShouldNotEnter
		enterFrame = NULL;

		enterCount--;

		if(status == kMemAbort && enterCount == 0 && abortStatusNotificationSent) {
			// last one out of the pool pulls the plug
			heapToDestroy = instance;
			instance = NULL;
		}
		if(heapToDestroy != NULL) {
			// any thread can call this, just need to make sure all other
			// threads are done, hence the ref counting
			heapToDestroy->DestroyInstance();
		}
		EnterRelease();				
	}
	void GCHeap::log_percentage(const char *name, size_t bytes, size_t bytes_compare)
	{
		bytes_compare = size_t((bytes*100.0)/bytes_compare);
		if(bytes > 1<<20) {
			GCLog("%s %u (%.1fM) %u%%\n", name, (unsigned int)(bytes / GCHeap::kBlockSize), bytes * 1.0 / (1024*1024), (unsigned int)(bytes_compare));
		} else {
			GCLog("%s %u (%uK) %u%%\n", name, (unsigned int)(bytes / GCHeap::kBlockSize), (unsigned int)(bytes / 1024), (unsigned int)(bytes_compare));
		}
	}
	
	void GCHeap::DumpMemoryInfo()
	{
		MMGC_LOCK(m_spinlock);
		DumpMemoryInfoLocked();
	}

	void GCHeap::DumpMemoryInfoLocked()
	{
		size_t priv = VMPI_getPrivateResidentPageCount() * VMPI_getVMPageSize();
		size_t mmgc = GetTotalHeapSize() * GCHeap::kBlockSize;
		size_t unmanaged = GetFixedMalloc()->GetTotalSize() * GCHeap::kBlockSize;
		size_t fixed_alloced;
		size_t fixed_asksize;
		GetFixedMalloc()->GetUsageInfo(fixed_asksize, fixed_alloced);

		size_t gc_total=0;
		size_t gc_allocated_total =0;
		size_t gc_ask_total = 0;
		size_t gc_count = 0;
		BasicListIterator<GC*> iter(gcManager.gcs());
		GC* gc;
		while((gc = iter.next()) != NULL)
		{
#ifdef MMGC_MEMORY_PROFILER
			GCLog("[mem] GC 0x%p:%s\n", (void*)gc, GetAllocationName(gc));
#else
			GCLog("[mem] GC 0x%p\n", (void*)gc);
#endif
			gc->DumpMemoryInfo();
			
			size_t ask;
			size_t allocated;
			gc->GetUsageInfo(ask, allocated);
			gc_ask_total += ask;
			gc_allocated_total += allocated;
			gc_count += 1;
			
			gc_total += gc->GetNumBlocks() * kBlockSize;
		}

#ifdef MMGC_MEMORY_PROFILER
		fixedMalloc.DumpMemoryInfo();
#endif

		// Gross stats are not meaningful if the profiler is running, see bugzilla 490014.
		// Disabling their printing is just an expedient fix to avoid misleading data being
		// printed.  There are other, more complicated, fixes we should adopt.

		GCLog("[mem] ------- gross stats -----\n");
#ifdef MMGC_MEMORY_PROFILER
		if (GCHeap::GetGCHeap()->GetProfiler() == NULL)
#endif
		{
			log_percentage("[mem] private", priv, priv);
			log_percentage("[mem]\t mmgc", mmgc, priv);
			log_percentage("[mem]\t\t unmanaged", unmanaged, priv);
			log_percentage("[mem]\t\t managed", gc_total, priv);
			log_percentage("[mem]\t\t free",  (size_t)GetFreeHeapSize() * GCHeap::kBlockSize, priv);
			log_percentage("[mem]\t other",  priv - mmgc, priv);
			log_percentage("[mem] \tunmanaged overhead ", unmanaged-fixed_alloced, unmanaged);
			log_percentage("[mem] \tmanaged overhead ", gc_total - gc_allocated_total, gc_total);
#ifdef MMGC_MEMORY_PROFILER
			if(HooksEnabled())
			{
				log_percentage("[mem] \tunmanaged internal wastage", fixed_alloced - fixed_asksize, fixed_alloced);
				log_percentage("[mem] \tmanaged internal wastage", gc_allocated_total - gc_ask_total, gc_allocated_total);
			}
#endif
			GCLog("[mem] number of collectors %u\n", unsigned(gc_count));
		}
#ifdef MMGC_MEMORY_PROFILER
		else
			GCLog("[mem] No gross stats available when profiler is enabled.\n");
#endif
		GCLog("[mem] -------- gross stats end -----\n");

#ifdef MMGC_MEMORY_PROFILER
		if(hasSpy)
			DumpFatties();
#endif

		if (config.verbose)
			DumpHeapRep();
	}

	void GCHeap::LogChar(char c, size_t count)
	{
		char tmp[100];
		char* buf = count < 100 ? tmp : (char*)VMPI_alloc(count+1);
		if (buf == NULL)
			return;
		VMPI_memset(buf, c, count);
		buf[count] = '\0';

		GCLog(buf);
		if (buf != tmp)
			VMPI_free(buf);
	}

	void GCHeap::DumpHeapRep()
	{
		Region **regions = NULL;
		Region *r = lastRegion;
		int numRegions = 0;

		GCLog("Heap representation format: \n");
		GCLog("region base address - commitTop/reserveTop\n");
		GCLog("[0 == free, 1 == committed, - = uncommitted]*\n");

		// count and sort regions
		while(r) {
			numRegions++;
			r = r->prev;
		}
		regions = (Region**) VMPI_alloc(sizeof(Region*)*numRegions);
		if (regions == NULL)
			return;
		r = lastRegion;
		for(int i=0; i < numRegions; i++, r = r->prev) {
			int insert = i;
			for(int j=0; j < i; j++) {
				if(r->baseAddr < regions[j]->baseAddr) {
					memmove(&regions[j+1], &regions[j], sizeof(Region*) * (i - j));
					insert = j;
					break;
				}
			}
			regions[insert] = r;
		}

		HeapBlock *spanningBlock = NULL;
		for(int i=0; i < numRegions; i++)
		{
			r = regions[i];
			GCLog("0x%p -  0x%p/0x%p\n", r->baseAddr, r->commitTop, r->reserveTop);
			char c;
			char *addr = r->baseAddr;
			
			if(spanningBlock) {
				GCAssert(spanningBlock->baseAddr + (spanningBlock->size * kBlockSize) > r->baseAddr);
				GCAssert(spanningBlock->baseAddr < r->baseAddr);				
				char *end = spanningBlock->baseAddr + (spanningBlock->size * kBlockSize);
				if(end > r->reserveTop)
					end = r->reserveTop;

				LogChar(spanningBlock->inUse() ? '1' : '0', (end - addr)/kBlockSize);
				addr = end;

				if(addr == spanningBlock->baseAddr + (spanningBlock->size * kBlockSize))
					spanningBlock = NULL;
			}
			HeapBlock *hb;
			while(addr != r->commitTop && (hb = AddrToBlock(addr)) != NULL) {
				GCAssert(hb->size != 0);

				if(hb->inUse())
					c = '1';
				else if(hb->committed)
					c = '0';
				else 
					c = '-';
				size_t i, n;
				for(i=0, n=hb->size; i < n; i++, addr += GCHeap::kBlockSize) {
					if(addr == r->reserveTop) {
						// end of region!
						spanningBlock = hb;
						break;
					}
				}

				LogChar(c, i);
			}

			LogChar('-', (r->reserveTop - addr) / kBlockSize);

			GCLog("\n");
		}
		VMPI_free(regions);
	}
	
#ifdef MMGC_MEMORY_PROFILER

	/* static */
	void GCHeap::InitProfiler()
	{
		GCAssert(IsProfilerInitialized() == false);
		profiler = NULL;

#ifdef MMGC_MEMORY_INFO
		bool profilingEnabled = true;
#else
		bool profilingEnabled = VMPI_isMemoryProfilingEnabled();
#endif
		if(profilingEnabled)
		{
			profiler = new MemoryProfiler();
		}
	}

#endif //MMGC_MEMORY_PROFILER

#ifdef MMGC_MEMORY_PROFILER
#ifdef MMGC_USE_SYSTEM_MALLOC

	void GCHeap::TrackSystemAlloc(void *addr, size_t askSize)
	{
		MMGC_LOCK(m_spinlock);
		if(!IsProfilerInitialized())
			InitProfiler();
		if(profiler)
			profiler->RecordAllocation(addr, askSize, VMPI_size(addr));
	}

	void GCHeap::TrackSystemFree(void *addr)
	{
		MMGC_LOCK(m_spinlock);
		if(addr && profiler)
			profiler->RecordDeallocation(addr, VMPI_size(addr));
	}

#endif //MMGC_USE_SYSTEM_MALLOC
#endif // MMGC_MEMORY_PROFILER
	
	void GCHeap::ReleaseMemory(char *address, size_t size)
	{
		if(config.useVirtualMemory) {
			bool success = VMPI_releaseMemoryRegion(address, size);
			GCAssert(success);
			(void)success;
		} else {
			VMPI_releaseAlignedMemory(address);
		}
	}

	void GCManager::destroy()
	{
		collectors.Destroy();
	}
	
	void GCManager::signalStartCollection(GC* gc)
	{
		BasicListIterator<GC*> iter(collectors);
		GC* otherGC;
		while((otherGC = iter.next()) != NULL) 
			otherGC->policy.signalStartCollection(gc);
	}
	
	void GCManager::signalEndCollection(GC* gc)
	{
		BasicListIterator<GC*> iter(collectors);
		GC* otherGC;
		while((otherGC = iter.next()) != NULL) 
			otherGC->policy.signalStartCollection(gc);
	}

	/* this method is the heart of the OOM system.
	   its here that we call out to the mutator which may call
	   back in to free memory or try to get more.
	*/
	void GCHeap::StatusChangeNotify(MemoryStatus to)
	{
		statusNotificationBeingSent = true;
		MemoryStatus oldStatus = status;
		status = to;
		
		// unlock the heap so that memory operations are allowed

		// this isn't right, really what we want is to allow this
		// thread to call Free but keep other threads out, so what we
		// really want is a lock operation that allows repeated same
		// thread locks
		VMPI_lockRelease(&m_spinlock);
		
		BasicListIterator<OOMCallback*> iter(callbacks);
		OOMCallback *cb = NULL;
		do {
			{
				MMGC_LOCK(list_lock);
				cb = iter.next();
			}
			if(cb)
				cb->memoryStatusChange(oldStatus, to);
		} while(cb != NULL);

		statusNotificationBeingSent = false;

		VMPI_lockAcquire(&m_spinlock);

		CheckForStatusReturnToNormal();
	}

 	/*static*/
	bool GCHeap::ShouldNotEnter()
	{
		// don't enter if the heap is already gone or we're aborting but not on the aborting call stack in a nested enter call
		if(GetGCHeap() == NULL || 
		   (MMgc::GCHeap::GetGCHeap()->GetStatus() == MMgc::kMemAbort && MMgc::GCHeap::GetGCHeap()->GetEnterFrame() == NULL))
			return true;
		return false;
	}

	bool GCHeap::IsAddressInHeap(void *addr)
	{
		return AddrToBlock(addr) != NULL;
	}

	// Every new GC must register itself with the GCHeap.
	void GCHeap::AddGC(GC *gc)
	{ 
		bool bAdded = false;
		{
			MMGC_LOCK(list_lock);
			bAdded = gcManager.tryAddGC(gc);
		}
		if (!bAdded)
		{
			Abort();
		}
	}		
		
	// When the GC is destroyed it must remove itself from the GCHeap.
	void GCHeap::RemoveGC(GC *gc) 
	{ 
		MMGC_LOCK(list_lock);
		gcManager.removeGC(gc); 
		EnterFrame* ef = GetEnterFrame();
		if (ef && ef->GetActiveGC() == gc)
			ef->SetActiveGC(NULL);
	}
	
	void GCHeap::AddOOMCallback(OOMCallback *p) 
	{
		bool bAdded = false;
		{
			MMGC_LOCK(list_lock);
			bAdded = callbacks.TryAdd(p);
		}
		if (!bAdded)
		{
			Abort();
		}
	}
	
	void GCHeap::RemoveOOMCallback(OOMCallback *p) 
	{ 
		MMGC_LOCK(list_lock);
		callbacks.Remove(p); 
	}

	GCHeap::Region *GCHeap::NewRegion(char *baseAddr, char *rTop, char *cTop, size_t blockId)
	{
		Region *r = freeRegion;
		if(r) {
			freeRegion = *(Region**)freeRegion;
		} else {
			r = nextRegion++;
			if(roundUp((uintptr_t)nextRegion, kBlockSize) - (uintptr_t)nextRegion < sizeof(Region))
				nextRegion = NULL; // fresh page allocated in ExpandHeap
		}			
		new (r) Region(this, baseAddr, rTop, cTop, blockId);
		return r;
	}

	void GCHeap::FreeRegion(Region *r)
	{
		if(r == lastRegion)
			lastRegion = r->prev;
		*(Region**)r = freeRegion;
		freeRegion = r;		

	}
	
	/*static*/ 
	void GCHeap::EnterLockInit()
	{ 
		if (!instanceEnterLockInitialized)
		{
			instanceEnterLockInitialized = true; 
			VMPI_lockInit(&instanceEnterLock); 
		}
	}

	/*static*/ 
	void GCHeap::EnterLockDestroy()
	{  
		GCAssert(instanceEnterLockInitialized);
		VMPI_lockDestroy(&instanceEnterLock);
	}

	GCHeap::Region::Region(GCHeap *heap, char *baseAddr, char *rTop, char *cTop, size_t blockId)
		: prev(heap->lastRegion), 
		  baseAddr(baseAddr), 
		  reserveTop(rTop), 
		  commitTop(cTop), 
		  blockId(blockId)
	{
		heap->lastRegion = this;
	}
}
