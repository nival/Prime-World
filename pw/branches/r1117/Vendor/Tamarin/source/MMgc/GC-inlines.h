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
 *   leon.sha@sun.com
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

#ifndef __GC_inlines__
#define __GC_inlines__

// Inline functions for GCRoot, GCPolicyManager, GC, GC::AllocaAutoPtr, GCWorkItem, Cleaner
// Policy manager should probably move to its own file.
// Inline functions for the write barrier are in WriteBarrier.h for now.

namespace MMgc
{
	// GCRoot
	
	REALLY_INLINE void *GCRoot::operator new(size_t size)
	{
		return FixedMalloc::GetFixedMalloc()->Alloc(size, MMgc::kZero);
	}
        
	REALLY_INLINE void GCRoot::operator delete (void *object)
	{
		FixedMalloc::GetFixedMalloc()->Free(object);
	}

	REALLY_INLINE GCWorkItem GCRoot::GetWorkItem() const
	{
		return GCWorkItem(object, (uint32_t)size, false);
	}

	// GCPolicyManager
	// A number of the inline functions for this class are currently in GC.cpp

#ifdef MMGC_POLICY_PROFILING
	REALLY_INLINE void GCPolicyManager::signalWriteBarrierWork(int stage)
	{
		GCAssert(ARRAY_SIZE(barrierStageLastCollection) > size_t(stage));
		barrierStageLastCollection[stage]++;
	}
#endif

#ifdef MMGC_REFCOUNT_PROFILING
	REALLY_INLINE void GCPolicyManager::signalIncrementRef()
	{
		incrementRefLastCollection++;
	}
	
	REALLY_INLINE void GCPolicyManager::signalDecrementRef()
	{
		decrementRefLastCollection++;
	}
	
	REALLY_INLINE void GCPolicyManager::signalZCTAdd(bool initial, uint32_t population)
	{
		addZCTLastCollection++;
		if (initial)
			addZCTInitialTotal++;
		if (population > zctPeakSize)
			zctPeakSize = population;
	}
	
	REALLY_INLINE void GCPolicyManager::signalZCTRemove(bool final)
	{
		removeZCTLastCollection++;
		if (final)
			removeZCTFinalTotal++;
	}
#endif
	
	REALLY_INLINE bool GCPolicyManager::signalAllocWork(size_t nbytes)
	{
#ifdef MMGC_POLICY_PROFILING
		objectsAllocated++;
		bytesAllocated += nbytes;
#endif
		remainingMinorAllocationBudget -= int32_t(nbytes);
 		return remainingMinorAllocationBudget <= 0;
	}

	// GC
	
	REALLY_INLINE void *GC::GetGCContextVariable(int var) const
	{
		return m_contextVars[var];
	}
	
	REALLY_INLINE void GC::SetGCContextVariable(int var, void *val)
	{
		m_contextVars[var] = val;
	}
	
	REALLY_INLINE avmplus::AvmCore *GC::core() const
	{
		return (avmplus::AvmCore*)GetGCContextVariable(GCV_AVMCORE);
	}

	REALLY_INLINE void GC::QueueCollection()
	{
		policy.queueFullCollection();
	}

	REALLY_INLINE void GC::SignalAllocWork(size_t size)
	{
		if (policy.signalAllocWork(size))
			CollectionWork();
	}
	
	REALLY_INLINE void *GC::PleaseAlloc(size_t size, int flags)
	{
		return Alloc(size, flags | kCanFail);			
	}

	// Normally extra will not be zero (overloaded 'new' operators take care of that)
	// so the overflow check is not actually redundant.

	REALLY_INLINE void *GC::AllocExtra(size_t size, size_t extra, int flags)
	{
		return Alloc(GCHeap::CheckForAllocSizeOverflow(size, extra), flags);
	}
	
	REALLY_INLINE void *GC::Calloc(size_t count, size_t elsize, int flags)
	{
		return Alloc(GCHeap::CheckForCallocSizeOverflow(count, elsize), flags);
	}

#if defined _DEBUG || defined MMGC_MEMORY_PROFILER
	#define SIZEARG size ,
#else
	#define SIZEARG 
#endif
	
	// See comments around GC::Alloc that explain why the guard and table lookup for the
	// small-allocator cases are correct.

	REALLY_INLINE void *GC::AllocPtrZero(size_t size)
	{
#if !defined _DEBUG && !defined AVMPLUS_SAMPLER
		if (size <= kLargestAlloc)
			return GetUserPointer(containsPointersAllocs[sizeClassIndex[(size-1)>>3]]->Alloc(SIZEARG GC::kContainsPointers|GC::kZero));
#endif
		return Alloc(size, GC::kContainsPointers|GC::kZero);
	}

	REALLY_INLINE void *GC::AllocPtrZeroFinalized(size_t size)
	{
#if !defined _DEBUG && !defined AVMPLUS_SAMPLER
		if (size <= kLargestAlloc)
			return GetUserPointer(containsPointersAllocs[sizeClassIndex[(size-1)>>3]]->Alloc(SIZEARG GC::kContainsPointers|GC::kZero|GC::kFinalize));
#endif
		return Alloc(size, GC::kContainsPointers|GC::kZero|GC::kFinalize);
	}
	
	REALLY_INLINE void *GC::AllocRCObject(size_t size)
	{
#if !defined _DEBUG && !defined AVMPLUS_SAMPLER
		if (size <= kLargestAlloc)
			return GetUserPointer(containsPointersRCAllocs[sizeClassIndex[(size-1)>>3]]->Alloc(SIZEARG GC::kContainsPointers|GC::kZero|GC::kRCObject|GC::kFinalize));
#endif
		return Alloc(size, GC::kContainsPointers|GC::kZero|GC::kRCObject|GC::kFinalize);
	}
	
	REALLY_INLINE void* GC::AllocDouble()
	{
#if !defined _DEBUG && !defined AVMPLUS_SAMPLER && !defined MMGC_MEMORY_PROFILER
		return GetUserPointer(noPointersAllocs[0]->Alloc(0));
#else
		return Alloc(8,0);
#endif
	}

	// For AllocExtra the trick is that we can compute (size|extra) quickly without risk of overflow
	// and compare it to half the maximum small-alloc size (rounded down to 8 bytes), and if the guard
	// passes then we can definitely take the quick path.  Most allocations are small.
	//
	// As 'extra' won't usually be known at compile time the fallback case won't usually compile away,
	// though, so we risk bloating the code slightly here.

	REALLY_INLINE void *GC::AllocExtraPtrZero(size_t size, size_t extra)
	{
#if !defined _DEBUG && !defined AVMPLUS_SAMPLER
		if ((size|extra) <= (kLargestAlloc/2 & ~7)) {
			size += extra;
			return GetUserPointer(containsPointersAllocs[sizeClassIndex[(size-1)>>3]]->Alloc(SIZEARG GC::kContainsPointers|GC::kZero));
		}
#endif
		return OutOfLineAllocExtra(size, extra, GC::kContainsPointers|GC::kZero);
	}
	
	REALLY_INLINE void *GC::AllocExtraPtrZeroFinalized(size_t size, size_t extra)
	{
#if !defined _DEBUG && !defined AVMPLUS_SAMPLER
		if ((size|extra) <= (kLargestAlloc/2 & ~7)) {
			size += extra;
			return GetUserPointer(containsPointersAllocs[sizeClassIndex[(size-1)>>3]]->Alloc(SIZEARG GC::kContainsPointers|GC::kZero|GC::kFinalize));
		}
#endif
		return OutOfLineAllocExtra(size, extra, GC::kContainsPointers|GC::kZero|GC::kFinalize);
	}
	
	REALLY_INLINE void *GC::AllocExtraRCObject(size_t size, size_t extra)
	{
#if !defined _DEBUG && !defined AVMPLUS_SAMPLER
		if ((size|extra) <= kLargestAlloc/2) {
			size += extra;
			return GetUserPointer(containsPointersRCAllocs[sizeClassIndex[(size-1)>>3]]->Alloc(SIZEARG GC::kContainsPointers|GC::kZero|GC::kRCObject|GC::kFinalize));
		}
#endif
		return OutOfLineAllocExtra(size, extra, GC::kContainsPointers|GC::kZero|GC::kRCObject|GC::kFinalize);
	}
	
#undef SIZEARG

	// Implementations of operator delete call FreeNotNull directly.
	REALLY_INLINE void GC::Free(const void *item)
	{
		if(item == NULL)
			return;
		FreeNotNull(item);
	}

	REALLY_INLINE void GC::AddRCRootSegment(RCRootSegment *segment)
	{
		segment->next = rcRootSegments;
		if (rcRootSegments)
			rcRootSegments->prev = segment;
		rcRootSegments = segment;
	}

	REALLY_INLINE void GC::RemoveRCRootSegment(RCRootSegment *segment)
	{
		if (segment->next != NULL)
			segment->next->prev = segment->prev;
		if (segment->prev != NULL)
			segment->prev->next = segment->next;
		else
			rcRootSegments = segment->next;
	}

	/*static*/
	REALLY_INLINE size_t GC::Size(const void *ptr)
	{
		return GetBlockHeader(ptr)->size - DebugSize();
	}

	/*static*/
	REALLY_INLINE GC* GC::GetGC(const void *item)
	{
		GC *gc = GetBlockHeader(item)->gc;
		// we don't want to rely on the gcheap thread local but it makes a good
		// sanity check against misuse of this function
//		GCAssert(gc == GCHeap::GetGCHeap()->GetActiveGC());
		return gc;
	}
	
	/*static*/
	REALLY_INLINE int GC::GetMark(const void *item)
	{
		item = GetRealPointer(item);
		if (GCLargeAlloc::IsLargeBlock(item)) {
			return GCLargeAlloc::GetMark(item);
		} else {
			return GCAlloc::GetMark(item);
		}
	}
	
	/*static*/
	REALLY_INLINE int GC::SetMark(const void *item)
	{
		item = GetRealPointer(item);
		GCAssert(GetGC(item)->IsPointerToGCObject(item));
		if (GCLargeAlloc::IsLargeBlock(item)) {
			return GCLargeAlloc::SetMark(item);
		} else {
			return GCAlloc::SetMark(item);
		}
	}

	REALLY_INLINE void GC::ClearQueued(const void *item)
	{
		item = GetRealPointer(item);
		GCAssert(IsPointerToGCObject(item));
		if (GCLargeAlloc::IsLargeBlock(item)) {
			GCLargeAlloc::ClearQueued(item);
		} else {
			GCAlloc::ClearQueued(item);
		}
	}
	
	/*static*/
	REALLY_INLINE void GC::ClearFinalized(const void *item)
	{
		item = GetRealPointer(item);
		GCAssert(GetGC(item)->IsPointerToGCObject(item));
		if (GCLargeAlloc::IsLargeBlock(item)) {
			GCLargeAlloc::ClearFinalized(item);
		} else {
			GCAlloc::ClearFinalized(item);
		}
	}

	/*static*/
	REALLY_INLINE void GC::SetFinalize(const void *item)
	{
		item = GetRealPointer(item);
		GCAssert(GetGC(item)->IsPointerToGCObject(item));
		if (GCLargeAlloc::IsLargeBlock(item)) {
			GCLargeAlloc::SetFinalize(item);
		} else {
			GCAlloc::SetFinalize(item);
		}
	}

	/*static*/
	REALLY_INLINE int GC::IsFinalized(const void *item)
	{
		item = GetRealPointer(item);
		GCAssert(GetGC(item)->IsPointerToGCObject(item));
		if (GCLargeAlloc::IsLargeBlock(item)) {
			return GCLargeAlloc::IsFinalized(item);
		} else {
			return GCAlloc::IsFinalized(item);
		}
	}

	/*static*/
	REALLY_INLINE int GC::HasWeakRef(const void *item)
	{
		item = GetRealPointer(item);
		GCAssert(GetGC(item)->IsPointerToGCObject(item));
		if (GCLargeAlloc::IsLargeBlock(item)) {
			return GCLargeAlloc::HasWeakRef(item);
		} else {
			return GCAlloc::HasWeakRef(item);
		}
	}

	REALLY_INLINE GCHeap *GC::GetGCHeap() const
	{ 
		return heap;
	}

	REALLY_INLINE void GC::ReapZCT(bool scanStack)
	{
		zct.Reap(scanStack);
	}
	
	REALLY_INLINE bool GC::Reaping()
	{
		return zct.IsReaping();
	}

	REALLY_INLINE bool GC::IncrementalMarking()
	{
		return marking;
	}
	
	REALLY_INLINE bool GC::Collecting()
	{
		return collecting;
	}
	
	REALLY_INLINE void *GC::FindBeginning(const void *gcItem)
	{
		return FindBeginningGuarded(gcItem);
	}

	REALLY_INLINE void *GC::FindBeginningFast(const void *gcItem)
	{
		int bits = GetPageMapValue((uintptr_t)gcItem);
		if (bits == kGCAllocPage)
			return GetUserPointer(GCAlloc::FindBeginning(gcItem));
		while (bits == kGCLargeAllocPageRest)
		{
			gcItem = (void*) ((uintptr_t)gcItem - GCHeap::kBlockSize);
			bits = GetPageMapValue((uintptr_t)gcItem);
		}
		return GetUserPointer(GCLargeAlloc::FindBeginning(gcItem));
	}

	REALLY_INLINE bool GC::IsPointerToGCPage(const void *item)
	{
		return GetPageMapValueGuarded((uintptr_t)item) != 0;
	}

	REALLY_INLINE bool GC::IsPointerToGCObject(const void *realPtr)
	{
		GCAssert(realPtr != NULL);
		return GetRealPointer(FindBeginningGuarded(realPtr)) == realPtr;
	}
	
	/*static*/
	REALLY_INLINE double GC::duration(uint64_t start) 
	{
		return (double(VMPI_getPerformanceCounter() - start) * 1000) / VMPI_getPerformanceFrequency();
	}

	/*static*/
	REALLY_INLINE uint64_t GC::ticksToMicros(uint64_t ticks) 
	{ 
		return (ticks*1000000)/VMPI_getPerformanceFrequency();
	}

	/*static*/
	REALLY_INLINE uint64_t GC::ticksToMillis(uint64_t ticks) 
	{ 
		return (ticks*1000)/VMPI_getPerformanceFrequency();
	}

	REALLY_INLINE uint64_t GC::bytesMarked()
	{
		return policy.bytesMarked();
	}

	REALLY_INLINE uint64_t GC::markTicks()
	{
		return policy.timeStartIncrementalMark + policy.timeIncrementalMark;
	}

	REALLY_INLINE uint32_t GC::markIncrements()
	{
		return (uint32_t)policy.countIncrementalMark;
	}

	REALLY_INLINE bool GC::Destroying()
	{
		return destroying;
	}

	REALLY_INLINE uintptr_t GC::GetStackTop() const
	{
		// temporary crutch until we're moved over to the MMGC_GCENTER system
		if(stackEnter == NULL)
			return GetOSStackTop();
		return GetStackEnter();
	}

	REALLY_INLINE uintptr_t GC::GetStackEnter() const 
	{ 
		return (uintptr_t)stackEnter; 
	}

	REALLY_INLINE GCAutoEnter *GC::GetAutoEnter()
	{
		return stackEnter;
	}

	REALLY_INLINE bool GC::onThread()
	{
		return VMPI_currentThread() == m_gcThread;
	}

	REALLY_INLINE void GC::FreeBits(uint32_t *bits, int sizeClass)
	{
#ifdef _DEBUG
		for(int i=0, n=noPointersAllocs[sizeClass]->m_numBitmapBytes; i<n;i++) 
			GCAssert(((uint8_t*)bits)[i] == 0);
#endif
		*(uint32_t**)bits = m_bitsFreelists[sizeClass];
		m_bitsFreelists[sizeClass] = bits;
	}

	REALLY_INLINE bool GC::IsMarkedThenMakeQueued(const void* userptr)
	{
		const void* realptr = GetRealPointer(userptr);
		if (GCLargeAlloc::IsLargeBlock(realptr))
			return GCLargeAlloc::IsMarkedThenMakeQueued(realptr);
		else
			return GCAlloc::IsMarkedThenMakeQueued(realptr);
	}

	REALLY_INLINE bool GC::IsQueued(const void* userptr)
	{
		const void* realptr = GetRealPointer(userptr);
		if (GCLargeAlloc::IsLargeBlock(realptr))
			return GCLargeAlloc::IsQueued(realptr);
		else
			return GCAlloc::IsQueued(realptr);
	}

	REALLY_INLINE int GC::GetPageMapValue(uintptr_t addr) const
	{
		GCAssert(addr >= memStart && addr < memEnd);
		uintptr_t index = (addr-memStart) >> 12;
#ifdef MMGC_64BIT
		GCAssert((index >> 2) < uintptr_t(64*65536) * uintptr_t(GCHeap::kBlockSize));
#else
		GCAssert(index >> 2 < 64 * GCHeap::kBlockSize);
#endif
		// shift amount to determine position in the byte (times 2 b/c 2 bits per page)
		uint32_t shiftAmount = (index&0x3) * 2;
		// 3 ... is mask for 2 bits, shifted to the left by shiftAmount
		// finally shift back by shift amount to get the value 0, 1 or 3
		//return (pageMap[addr >> 2] & (3<<shiftAmount)) >> shiftAmount;
		return (pageMap[index >> 2] >> shiftAmount) & 3;
	}

	REALLY_INLINE int GC::GetPageMapValueGuarded(uintptr_t addr)
	{
		if(addr >= memStart && addr < memEnd)
			return GetPageMapValue(addr);
		return 0;
	}

	REALLY_INLINE void GC::AddToSmallEmptyBlockList(GCAlloc::GCBlock *b)
	{
		b->next = smallEmptyPageList;
		smallEmptyPageList = b;
	}

	REALLY_INLINE void GC::AddToLargeEmptyBlockList(GCLargeAlloc::LargeBlock *lb)
	{
		lb->next = largeEmptyPageList;
		largeEmptyPageList = lb;
	}

#ifdef MMGC_REFCOUNT_PROFILING
	REALLY_INLINE void GC::AddToZCT(RCObject *obj, bool initial=false)
	{
		zct.Add(obj, initial);
	}
	
	REALLY_INLINE void GC::RemoveFromZCT(RCObject *obj, bool final=false)
	{
		zct.Remove(obj, final);
	}
#else
	REALLY_INLINE void GC::AddToZCT(RCObject *obj)
	{
		zct.Add(obj);
	}
	
	REALLY_INLINE void GC::RemoveFromZCT(RCObject *obj)
	{
		zct.Remove(obj);
	}
#endif

	/*static*/
	REALLY_INLINE const void *GC::Pointer(const void *p) 
	{
		return (const void*)(((uintptr_t)p)&~7);
	}

	REALLY_INLINE size_t GC::GetNumBlocks()
	{
		return policy.blocksOwnedByGC();
	}

	REALLY_INLINE void* GC::allocaTop() 
	{
		return stacktop;
	}
	
	REALLY_INLINE void GC::allocaPopTo(void* top)
	{ 
		if (top >= top_segment->start && top <= top_segment->limit)
			stacktop = top;
		else
			allocaPopToSlow(top);
	}

#ifdef DEBUGGER
	REALLY_INLINE void* GC::GetAttachedSampler()
	{
		return m_sampler;
	}
	
	REALLY_INLINE void GC::SetAttachedSampler(void *sampler)
	{
		m_sampler = sampler;
	}
#endif
	
	REALLY_INLINE GC::AllocaAutoPtr::AllocaAutoPtr()
		: gc(NULL)
		, unwindPtr(NULL)
	{
	}
	
	REALLY_INLINE GC::AllocaAutoPtr::~AllocaAutoPtr()
	{
		if (unwindPtr)
			gc->allocaPopTo(unwindPtr);
	}

	REALLY_INLINE Cleaner::Cleaner()
	{
	}

	REALLY_INLINE Cleaner::~Cleaner() 
	{ 
		if(v) 
			VMPI_memset(v, 0, size);
		v = 0; 
		size = 0;
	}

	// Disable copying
	REALLY_INLINE Cleaner& Cleaner::operator=(const Cleaner& /*rhs*/)
	{
		return *this;
	}
	
	REALLY_INLINE void Cleaner::set(const void * _v, size_t _size)
	{
		this->v = (int*)_v;
		this->size = _size;
	}
	
	REALLY_INLINE GCWorkItem::GCWorkItem(const void *p, uint32_t s, bool isGCItem)
		: ptr(p)
		, _size(s | uint32_t(isGCItem))
	{
#ifdef _DEBUG
		if (IsGCItem()) {
			GCAssert(GC::GetGC(p)->FindBeginningGuarded(p) == p);
		}
#endif
	}
}

#endif /* __GC_inlines__ */
