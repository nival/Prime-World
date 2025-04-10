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

#include "MMgc.h"
#include "StaticAssert.h"

#ifdef AVMPLUS_SAMPLER
 //sampling support
#include "avmplus.h"
#else
#define SAMPLE_FRAME(_x, _s) 
#define SAMPLE_CHECK() 
#endif

namespace MMgc
{
#ifdef MMGC_64BIT
	const uintptr_t MAX_UINTPTR = 0xFFFFFFFFFFFFFFFF;
#else
	const uintptr_t MAX_UINTPTR = 0xFFFFFFFF;
#endif	

#ifdef MMGC_MEMORY_PROFILER
	// get detailed info on each size class allocators
	const bool dumpSizeClassState = false;
#endif

#ifndef max	// good grief
	inline uint64_t max(uint64_t a, uint64_t b) { return a > b ? a : b; }
#endif

	/*virtual*/
	void GCCallback::presweep() {}
	
	/*virtual*/
	void GCCallback::postsweep() {}
	
	/*virtual*/
	void GCCallback::prereap() {}
	
	/*virtual*/
	void GCCallback::postreap() {}
	
	/*virtual*/
	void GCCallback::prereap(void* /*rcobj*/) {}
	
	// Scanning rates (bytes/sec).
	//
	// Less than R_LOWER_LIMIT is not credible and is probably a measurement error / measurement
	// noise.  A too low value will tend to throw policy out of whack.
	// 
	// 10MB/sec is the typical observed rate on the HTC Fuze, a mid-range 2009 smartphone.
	// 400MB/sec is the typical observed rate on a 2.6GHz MacBook Pro.
	// 100MB/sec seems like a reasonable approximation to let the application get off the ground.

#define R_LOWER_LIMIT (10*1024*1024)
#define R_INITIAL_VALUE (10*R_LOWER_LIMIT)
#define GREEDY_TRIGGER (-(INT_MAX/2))				// must be <= 0 but should never go positive as a result of a single alloc action or multiple free actions

	GCPolicyManager::GCPolicyManager(GC* gc, GCHeap* heap)
		// public
		: timeStartIncrementalMark(0)
		, timeIncrementalMark(0)
		, timeFinalRootAndStackScan(0)
		, timeFinalizeAndSweep(0)
		, timeReapZCT(0)
		, timeInLastCollection(0)
		, timeEndToEndLastCollection(0)
		, timeReapZCTLastCollection(0)
		, timeMaxStartIncrementalMark(0)
		, timeMaxIncrementalMark(0)
		, timeMaxFinalRootAndStackScan(0)
		, timeMaxFinalizeAndSweep(0)
		, timeMaxReapZCT(0)
		, timeMaxStartIncrementalMarkLastCollection(0)
		, timeMaxIncrementalMarkLastCollection(0)
		, timeMaxFinalRootAndStackScanLastCollection(0)
		, timeMaxFinalizeAndSweepLastCollection(0)
		, timeMaxReapZCTLastCollection(0)
		, countStartIncrementalMark(0)
		, countIncrementalMark(0)
		, countFinalRootAndStackScan(0)
		, countFinalizeAndSweep(0)
		, countReapZCT(0)
		// private
		, gc(gc)
		, heap(heap)
		, timeEndOfLastIncrementalMark(0)
		, timeStartOfLastCollection(0)
		, timeEndOfLastCollection(0)
		, blocksOwned(0)
		, maxBlocksOwned(0)
		, objectsScannedTotal(0)
		, objectsScannedLastCollection(0)
		, bytesScannedTotal(0)
		, bytesScannedLastCollection(0)
		, start_time(0)
		, start_event(NO_EVENT)
		, collectionThreshold(256) // 4KB blocks, that is, 1MB
		, fullCollectionQueued(false)
		, pendingClearZCTStats(false)
#ifdef MMGC_POLICY_PROFILING
		, heapAllocatedBeforeSweep(0)
		, heapUsedBeforeSweep(0)
		, gcAllocatedBeforeSweep(0)
		, gcBytesUsedBeforeSweep(0)
		, objectsReaped(0)
		, bytesReaped(0)
		, objectsPinned(0)
		, objectsAllocated(0)
		, bytesAllocated(0)
#endif
#ifdef MMGC_POINTINESS_PROFILING
		, candidateWords(0)
		, couldBePointer(0)
		, actuallyIsPointer(0)
#endif
#ifdef MMGC_REFCOUNT_PROFILING
		, incrementRefTotal(0)
		, incrementRefLastCollection(0)
		, decrementRefTotal(0)
		, decrementRefLastCollection(0)
		, zctPeakSize(0)
		, addZCTTotal(0)
		, addZCTLastCollection(0)
		, removeZCTTotal(0)
		, removeZCTLastCollection(0)
		, addZCTInitialTotal(0)
		, removeZCTFinalTotal(0)
#endif
		, P(0.005)				// seconds; 5ms.  The marker /will/ overshoot this significantly
		, R(R_INITIAL_VALUE)	// bytes/second; will be updated on-line
		, L_ideal(heap->Config().gcLoad)
		, L_actual(L_ideal)
		, T(1.0-(1.0/L_ideal))
		, G(heap->Config().gcEfficiency)
		, X(heap->Config().gcLoadCeiling)
		, remainingMajorAllocationBudget(0)
		, minorAllocationBudget(0)
		, remainingMinorAllocationBudget(0)
		, adjustR_startTime(0)
		, adjustR_totalTime(0)
	{
#ifdef MMGC_POLICY_PROFILING
		for ( size_t i=0 ; i < ARRAY_SIZE(barrierStageTotal) ; i++ ) {
			barrierStageTotal[i] = 0;
			barrierStageLastCollection[i] = 0;
		}
#endif
		adjustPolicyInitially();
	}
	
	void GCPolicyManager::shutdown()
	{
#ifdef MMGC_POLICY_PROFILING
		if (summarizeGCBehavior())
			PrintGCBehaviorStats(false);
#endif
	}

	// Garbage collection policy.
	//
	// Garbage collection is incremental and driven by allocation, heap pressure, and a
	// number of parameter settings.  The policy is documented and analyzed in doc/mmgc/policy.pdf,
	// this is a recap.
	//
	// Parameters fixed in the code:
	//
	// P (max pause)  can be tuned but within a limited range, but we treat it as
	//   constant.  Right now we use it to limit pauses in incremental marking only;
	//   it does not control ZCT reaping, final root and stack scan, or finalize
	//   and sweep.  (Those are all bugs.)  On a desktop system the marker sticks
	//   to P pretty well; on phones it has trouble with that, either because of
	//   clock resolution (P=5ms normally) or because of its recursive behavior
	//   that means the timeout is not checked sufficiently often, or because large
	//   objects take a long time to scan.
	// F (floor)  size of heap below which we don't collect, can be tuned but in limited ways,
	//   host code actually changes it.  Returned by lowerLimitCollectionThreshold().
	// R (rate of marking) is given by the hardware mainly (MB/s), updated on-line
	// V (voracity of new block allocation) is given by the program, ratio of blocks
	//   gcheap allocates from OS to ratio it allocates from already committed memory
	// H (heap)  size of heap at the end of one collection cycle
	// X (multiplier)  largest multiple of L to which the effective L should be allowed to
	//   grow to meet G.
	// T (allocation trigger) fraction of allocation budget to use before triggering
	//   the first mark increment (range 0..1).  With T=1 we have nonincremental GC;
	//   with T=0 the GC is always running.  A low T is desirable except that it puts
	//   more pressure on the write barrier.  A good T is (1-(1/L)) where L is the
	//   initial or given L.
	//
	// Tunable parameters:
	//
	// L (load factor)  ratio of heap size just before finishing a collection
	//   (before any reclamation) to the heap size just after finishing the previous
	//   collection (following any reclamation) (range 1..infty).  Effectively expresses
	//   the ratio of memory used to live program data.
	//
	// G (max GC fraction of time)  ceiling on ratio of GC time to total time in the
	//   interval when the incremental GC is running.  This controls pause clustering
	//   to some extent by recomputing a new and larger L if the GC time does not
	//   stay below the ceiling.  (It /could/ be used to reduce T if L can't be
	//   increased because it is up against its own ceiling, but experiments have
	//   not shown that to be fruitful so we don't do it yet.)
	//
	// We wish the heap size just before finishing a collection cycle to be HL, and
	// the allocation budget following a collection is H(L-1), and we work to make
	// that true in the steady state.
	//
	// Facts:
	//
	// W = L/((1-T)(L-1)) : bytes to be scanned per byte allocated when gc is active
	// M = PR : max mark work per mark increment
	// A = M/W : max bytes allocated between mark increments (because W work is
	//   needed for every allocated byte); if allocation proceeds faster than this then
	//   the marker cannot keep up to honor both L and P in the steady state
	//
	// How these constrain each other:
	//
	// If T is too high or L is too low then sticking to P may be futile as we will have
	// excessive pause clustering, which is no better.
	//
	// G is meant to constrain L: if G can't be met then L is effectively raised so 
	// that G can be met.  This is typically the case during system warmup, where a lot
	// of allocation in a smallish heap leads to a lot of GC activity with little gain.
	// The computation is like this:
	//    a = t(end of FinishIncrementalMark) - t(start of StartIncrementalMark)
	//    b = sum of time spent in StartIncrementalMark, IncrementalMark, FinishIncrementalMark
	// If b > aG then we must throttle GC activity for the next cycle.  G controls clustering.

	// Open issues / to do:
	//  - precise semantics of V, specifically, what is the interval over which it's computed
	//  - incorporate V in the computations

	double GCPolicyManager::W()
	{
		return L_actual / ((1 - T) * (L_actual - 1)); 
  	}

	// Warning: GIGO applies with full force: if R is badly mispredicted (based on too little data) 
	// or the marker is too far off from P, then the value of A can be bad.  In particular A may be
	// very low, which will tend to increase GC overhead because the marker will run too often.

	double GCPolicyManager::A() {
		return P * R / W();
	}

  	// Called when an incremental mark starts
	
	void GCPolicyManager::startAdjustingR()
	{
		adjustR_startTime = now();
	}

	// Called when an incremental mark ends
	
	void GCPolicyManager::endAdjustingR()
	{
		adjustR_totalTime += now() - adjustR_startTime;
		R = double(bytesScannedTotal) / (double(adjustR_totalTime) / double(VMPI_getPerformanceFrequency()));
		if (R < R_LOWER_LIMIT)
			R = R_LOWER_LIMIT;
	}

	// The throttles here guard against excessive growth.

	void GCPolicyManager::adjustL()
	{
		double a = double(timeEndToEndLastCollection);
  		double b = double(timeInLastCollection);
		if (b > a*G) {
			double growth = (L_actual - 1) * (1 + timeInLastCollection/timeEndToEndLastCollection);
			if (growth > 1)
				growth = 1;
			L_actual = L_actual + growth;
			if (X != 0 && L_actual > X*L_ideal)
				L_actual = X*L_ideal;
		}
 		else
 			L_actual = (L_actual + L_ideal) / 2;
 	}

	// Called at the start
	void GCPolicyManager::adjustPolicyInitially()
	{
		remainingMajorAllocationBudget = double(lowerLimitCollectionThreshold()) * 4096.0;
		remainingMinorAllocationBudget = minorAllocationBudget = int32_t(remainingMajorAllocationBudget * T);
 		remainingMajorAllocationBudget -= remainingMinorAllocationBudget;
		if (gc->greedy)
			remainingMinorAllocationBudget = GREEDY_TRIGGER;
	}
	
 	// Called when a collection ends
 	void GCPolicyManager::adjustPolicyForNextMajorCycle()
 	{
  		// Compute L_actual, which takes into account how much time we spent in GC
		// during the last cycle
		adjustL();

  		// The budget is H(L-1), with a floor
		double H = double(gc->GetBytesInUse());
		double remainingBeforeGC = double(lowerLimitCollectionThreshold()) * 4096.0 - H;
		remainingMajorAllocationBudget = H * (L_actual - 1.0);
		if (remainingMajorAllocationBudget < remainingBeforeGC)
			remainingMajorAllocationBudget = remainingBeforeGC;
  		remainingMinorAllocationBudget = minorAllocationBudget = int32_t(remainingMajorAllocationBudget * T);
#ifdef MMGC_POLICY_PROFILING
		if (summarizeGCBehavior())
			GCLog("[gcbehavior] policy: mark-rate=%.2f (MB/sec) adjusted-L=%.2f kbytes-live=%.0f kbytes-target=%.0f\n", 
				  R / (1024*1024),
				  L_actual, 
				  H / 1024.0, 
				  (H+remainingMajorAllocationBudget) / 1024.0);
#endif
 		remainingMajorAllocationBudget -= remainingMinorAllocationBudget;
		
		if (gc->greedy)
			remainingMinorAllocationBudget = GREEDY_TRIGGER;
  	}

 	// Called when an incremental mark ends
 	void GCPolicyManager::adjustPolicyForNextMinorCycle()
 	{
		if (remainingMinorAllocationBudget < 0) {
			// We overshot the allocation budget.  Sometimes this overshoot can be
			// much greater than A, if a single large object is allocated, so the
			// clean solution is to adjust the major budget by the overshoot first.
			remainingMajorAllocationBudget -= -remainingMinorAllocationBudget;
			remainingMinorAllocationBudget = 0;
		}
 		remainingMinorAllocationBudget = int32_t(A());
		minorAllocationBudget = remainingMinorAllocationBudget;
 		remainingMajorAllocationBudget -= remainingMinorAllocationBudget;
		
		if (gc->greedy)
			remainingMinorAllocationBudget = GREEDY_TRIGGER;
 	}

 	// Called when an incremental mark is about to start.  The premise is that if the
 	// application stays within the budget then the value returned here will correspond
 	// to the desired time slice.  But if the application allocates some huge block that
 	// blows the budget then we up the mark work here, /even if/ that means violating
 	// the budget.  The idea is that that won't happen very often, and that it's more
 	// important not to overshoot the total heap size target than to stick to the
 	// time slice always.  The other alternative is to adjust the amount of allocation
 	// allowed before the next mark downward, but as soon as we do that aggressively
 	// we get into pause clustering issues and it will seem like one long GC pause anyway.
 
 	uint32_t GCPolicyManager::incrementalMarkMilliseconds()
 	{
		// Bad to divide by 0 here.
		GCAssert(minorAllocationBudget != 0);
 		return uint32_t(P * 1000.0 * double(minorAllocationBudget - remainingMinorAllocationBudget) / double(minorAllocationBudget));
 	}
 
 	bool GCPolicyManager::queryEndOfCollectionCycle()
 	{
 		return remainingMajorAllocationBudget <= 0;
  	}

	void GCPolicyManager::setLowerLimitCollectionThreshold(uint32_t blocks) {
		collectionThreshold = blocks;
	}

	inline uint32_t GCPolicyManager::lowerLimitCollectionThreshold() {
		return collectionThreshold;
	}

	inline uint64_t GCPolicyManager::now() {
		return VMPI_getPerformanceCounter();
	}

#ifdef MMGC_POLICY_PROFILING
	inline bool GCPolicyManager::summarizeGCBehavior() {
		return GCHeap::GetGCHeap()->Config().gcbehavior;
	}
	
	inline double GCPolicyManager::ticksToMillis(uint64_t ticks) {
		return double(ticks) * 1000.0 / double(VMPI_getPerformanceFrequency());
	}
#endif

	size_t GCPolicyManager::blocksOwnedByGC() {
		return blocksOwned;
	}
	
	uint64_t GCPolicyManager::bytesMarked() {
		return bytesScannedTotal + bytesScannedLastCollection;
	}
	
	uint64_t GCPolicyManager::objectsMarked() {
		return objectsScannedTotal + objectsScannedLastCollection;
	}

	uint32_t GCPolicyManager::queryZCTBudget(uint32_t zctSizeBlocks)
	{
		(void)zctSizeBlocks;
		return 1;
	}

	void GCPolicyManager::SignalImminentAbort()
	{
		start_event = NO_EVENT;
	}

	void GCPolicyManager::signal(PolicyEvent ev) {
		switch (ev) {
			case START_StartIncrementalMark:
				heap->gcManager.signalStartCollection(gc);
				timeStartOfLastCollection = now();
				timeInLastCollection = 0;
				timeMaxStartIncrementalMarkLastCollection = 0;
				timeMaxIncrementalMarkLastCollection = 0;
				timeMaxFinalRootAndStackScanLastCollection = 0;
				timeMaxFinalizeAndSweepLastCollection = 0;
				objectsScannedTotal += objectsScannedLastCollection;
				objectsScannedLastCollection = 0;
				bytesScannedTotal += bytesScannedLastCollection;
				bytesScannedLastCollection = 0;
#ifdef MMGC_POINTINESS_PROFILING
				candidateWords = 0;
				couldBePointer = 0;
				actuallyIsPointer = 0;
#endif
				startAdjustingR();
				goto clear_zct_stats;
			case START_IncrementalMark:
				startAdjustingR();
				goto common_actions;
			case START_FinalRootAndStackScan:
				startAdjustingR();
				goto common_actions;
			case START_FinalizeAndSweep:
#ifdef MMGC_POLICY_PROFILING
				heapAllocatedBeforeSweep = heap->GetTotalHeapSize();
				heapUsedBeforeSweep = (heap->GetTotalHeapSize() - heap->GetFreeHeapSize());
				gcAllocatedBeforeSweep = gc->GetNumBlocks();
				gcBytesUsedBeforeSweep = gc->GetBytesInUse();
#endif
				goto common_actions;
			case START_ReapZCT:
			clear_zct_stats:
				if (pendingClearZCTStats) {
					pendingClearZCTStats = false;
					timeReapZCTLastCollection = 0;
					timeMaxReapZCTLastCollection = 0;
				}
				/*FALLTHROUGH*/
			common_actions:
#ifdef DEBUG
				if (start_event != NO_EVENT)
					GCDebugMsg(true, "Should not have a start_event but had start_event=%d, ev=%d\n", (int)start_event, (int)ev);
#endif
				start_time = now();
				start_event = ev;
				return;	// to circumvent resetting of start_event below
		}
		
#ifdef DEBUG
		if (start_event != (PolicyEvent)(ev - 1))
			GCDebugMsg(true, "Should have had a matching start_event but instead had start_event=%d, ev=%d\n", (int)start_event, (int)ev);
#endif
		start_event = NO_EVENT;
		
		uint64_t t = now();
		uint64_t elapsed = t - start_time;  
		
		switch (ev) {
			case END_StartIncrementalMark:
				countStartIncrementalMark++;
				timeStartIncrementalMark += elapsed;
				timeMaxStartIncrementalMark = max(timeMaxStartIncrementalMark, elapsed);
				timeMaxStartIncrementalMarkLastCollection = max(timeMaxStartIncrementalMarkLastCollection, elapsed);
				endAdjustingR();
				break;
			case END_FinalRootAndStackScan:
				countFinalRootAndStackScan++;
				timeFinalRootAndStackScan += elapsed;
				timeMaxFinalRootAndStackScan = max(timeMaxFinalRootAndStackScan, elapsed);
				timeMaxFinalRootAndStackScanLastCollection = max(timeMaxFinalRootAndStackScanLastCollection, elapsed);
				endAdjustingR();
				break;
			case END_ReapZCT:
				countReapZCT++;
				timeReapZCT += elapsed;
				timeReapZCTLastCollection += elapsed;
				timeMaxReapZCT = max(timeMaxReapZCT, elapsed);
				timeMaxReapZCTLastCollection = max(timeMaxReapZCTLastCollection, elapsed);
				break;
			case END_IncrementalMark:
				countIncrementalMark++;
				timeIncrementalMark += elapsed;
				timeMaxIncrementalMark = max(timeMaxIncrementalMark, elapsed);
				timeMaxIncrementalMarkLastCollection = max(timeMaxIncrementalMarkLastCollection, elapsed);
				timeEndOfLastIncrementalMark = t;
				endAdjustingR();
				break;
			case END_FinalizeAndSweep:
				countFinalizeAndSweep++;
				timeFinalizeAndSweep += elapsed;
				timeMaxFinalizeAndSweep = max(timeMaxFinalizeAndSweep, elapsed);
				timeMaxFinalizeAndSweepLastCollection = max(timeMaxFinalizeAndSweepLastCollection, elapsed);
				timeEndOfLastCollection = t;
				timeEndToEndLastCollection = timeEndOfLastCollection - timeStartOfLastCollection;
				pendingClearZCTStats = true;
				heap->gcManager.signalEndCollection(gc);
				break;
		}
		if (ev != END_ReapZCT)
			timeInLastCollection += elapsed;
		
#ifdef MMGC_POLICY_PROFILING
		if (summarizeGCBehavior() && ev == END_FinalizeAndSweep)
			PrintGCBehaviorStats();
#endif // MMGC_POLICY_PROFILING
#ifdef MMGC_POLICY_PROFILING
		// Need to clear these before any writes can occur, so that means right here: if earlier,
		// we'd not have them for reporting.
		if (ev == END_FinalizeAndSweep) {
			for ( size_t i=0 ; i < ARRAY_SIZE(barrierStageTotal) ; i++ ) {
				barrierStageTotal[i] += barrierStageLastCollection[i];
				barrierStageLastCollection[i] = 0;
			}
		}
#endif
#ifdef MMGC_REFCOUNT_PROFILING
		// Need to clear these before any refcount operations can occur, so that means right here:
		// if earlier, we'd not have them for reporting.
		incrementRefTotal += incrementRefLastCollection;
		incrementRefLastCollection = 0;
		decrementRefTotal += decrementRefLastCollection;
		decrementRefTotal = 0;
		addZCTTotal += addZCTLastCollection;
		addZCTLastCollection = 0;
		removeZCTTotal += removeZCTLastCollection;
		removeZCTLastCollection = 0;
#endif
		switch (ev) {
			case END_IncrementalMark:
				adjustPolicyForNextMinorCycle();
				break;
			case END_FinalizeAndSweep:
				adjustPolicyForNextMajorCycle();
				break;
		}
	}
	
#ifdef MMGC_POLICY_PROFILING
	/**
	 * Note, gcno=0 is special and means statistics dumped at the end of the run,
	 * just as the GC is about to shut down.
	 *
	 * Note that a lot of the stats for the last GC cycle do make sense even if
	 * afterCollection is false, because they would be stats for an unfinished
	 * incremental collection.  But they only make sense if gc->IncrementalMarking()
	 * is true.
	 *
	 * TODO: alloc/free volumes might be helpful.
	 */
	void GCPolicyManager::PrintGCBehaviorStats(bool afterCollection)
	{
		size_t bytesInUse = gc->GetBytesInUse();
		size_t heapAllocated = heap->GetTotalHeapSize();
		char buf[256];
		uint32_t utotal;
		double dtotal;
		
		GCLog("--------------------\n");
		GCLog("[gcbehavior] tag: gc=%p gcno=%u incremental-marks=%u\n", (void*)gc, afterCollection ? (unsigned)countFinalizeAndSweep : 0, (unsigned)countIncrementalMark);
		GCLog("[gcbehavior] allocation-work: objects=%.0f bytes=%.0f\n", 
			  double(objectsAllocated),
			  double(bytesAllocated));
		if (afterCollection)
		{
			GCLog("[gcbehavior] occupancy-before: blocks-heap-allocated=%u blocks-heap-used=%u blocks-gc-allocated=%u blocks-gc-used=%u\n",
				  (unsigned)heapAllocatedBeforeSweep, (unsigned)heapUsedBeforeSweep,
				  (unsigned)gcAllocatedBeforeSweep, (unsigned)(gcBytesUsedBeforeSweep + 4095)/4096);
			GCLog("[gcbehavior] occupancy-after: blocks-heap-allocated=%u blocks-heap-used=%u blocks-gc-allocated=%u blocks-gc-used=%u\n",
				  (unsigned)heapAllocated, (unsigned)(heapAllocated - heap->GetFreeHeapSize()), 
				  (unsigned)gc->GetNumBlocks(), (unsigned)(bytesInUse + 4095)/4096);
			GCLog("[gcbehavior] user-data: kbytes-before-sweep=%u kbytes-after-sweep=%u ratio=%.2f\n", 
				  unsigned(gcBytesUsedBeforeSweep/1024), 
				  unsigned(bytesInUse/1024),
				  double(gcBytesUsedBeforeSweep)/double(bytesInUse));
		}
		else
		{
			size_t maxHeapBlocks;
			size_t maxPrivateBlocks;
			
			heap->GetMaxTotalHeapSize(maxHeapBlocks, maxPrivateBlocks);
			GCLog("[gcbehavior] peak-occupancy: blocks-heap-allocated=%u blocks-gc-allocated=%u blocks-private=%u\n",
				  (unsigned)maxHeapBlocks,
				  (unsigned)maxBlocksOwned,
				  (unsigned)maxPrivateBlocks);
			GCLog("[gcbehavior] occupancy: blocks-heap-allocated=%u blocks-heap-used=%u blocks-gc-allocated=%u blocks-gc-used=%u, blocks-gc-peak=%u\n",
				  (unsigned)heapAllocated, 
				  (unsigned)(heapAllocated - heap->GetFreeHeapSize()), 
				  (unsigned)gc->GetNumBlocks(),
				  (unsigned)(bytesInUse + 4095)/4096,
				  (unsigned)maxBlocksOwned);
			GCLog("[gcbehavior] user-data: kbytes=%u\n", 
				  unsigned(bytesInUse/1024));
		}
#ifdef MMGC_POINTINESS_PROFILING
		GCLog("[gcbehavior] pointiness: candidates=%u inrange=%u actual=%u\n",
			  unsigned(candidateWords),
			  unsigned(couldBePointer),
			  unsigned(actuallyIsPointer));
#endif
#ifdef MMGC_MARKSTACK_DEPTH
		GCLog("[gcbehavior] mark-stack: stack-max-depth=%u barrier-max-depth=%u\n", 
			  gc->m_incrementalWork.MaxCount(),
			  gc->m_barrierWork.MaxCount());
#endif
		if (afterCollection || gc->IncrementalMarking())
		{
			GCLog("[gcbehavior] markitem-last-gc: objects=%u bytes=%u\n",
				  unsigned(objectsScannedLastCollection),
				  unsigned(bytesScannedLastCollection));
		}
		GCLog("[gcbehavior] markitem-all-gc: objects=%.0f bytes=%.0f\n",
			  double(objectsScannedLastCollection + objectsScannedTotal),
			  double(bytesScannedLastCollection + bytesScannedTotal));

		size_t blimit = ARRAY_SIZE(barrierStageLastCollection);
		utotal = 0;
		VMPI_sprintf(buf, "[gcbehavior] barrier-last-gc:");
		for ( size_t i=0 ; i < blimit ; i++ )
			utotal += barrierStageLastCollection[i];
		VMPI_sprintf(buf + strlen(buf), " total=%u", unsigned(utotal));
		for ( size_t i=0 ; i < blimit ; i++ )
			VMPI_sprintf(buf + strlen(buf), " stage%d=%u", unsigned(i), unsigned(barrierStageLastCollection[i]));
		VMPI_sprintf(buf + strlen(buf), " hit-ratio=%.2f\n", 
					 double(barrierStageLastCollection[blimit-1])/double(utotal));
		GCLog(buf);
	
		dtotal = 0;
		VMPI_sprintf(buf, "[gcbehavior] barrier-all-gc: ");
		for ( size_t i=0 ; i < blimit ; i++ )
			dtotal += double(barrierStageLastCollection[i] + barrierStageTotal[i]);
		VMPI_sprintf(buf + strlen(buf), " total=%.0f", dtotal);
		for ( size_t i=0 ; i < blimit ; i++ )
			VMPI_sprintf(buf + strlen(buf), " stage%d=%.0f", unsigned(i), double(barrierStageLastCollection[i] + barrierStageTotal[i]));
		VMPI_sprintf(buf + strlen(buf), " hit-ratio=%.2f\n", 
					 double(barrierStageLastCollection[blimit-1] + barrierStageTotal[blimit-1])/double(dtotal));
		GCLog(buf);

#ifdef MMGC_REFCOUNT_PROFILING
		GCLog("[gcbehavior] refcount-last-gc: increment=%.0f decrement=%.0f\n",
			  double(incrementRefLastCollection),
			  double(decrementRefLastCollection));
		GCLog("[gcbehavior] refcount-all-gc: increment=%.0f decrement=%.0f\n",
			  double(incrementRefLastCollection + incrementRefTotal),
			  double(decrementRefLastCollection + decrementRefTotal));
		GCLog("[gcbehavior] zct-traffic-last-gc: add=%.0f remove=%.0f\n",
			  double(addZCTLastCollection),
			  double(removeZCTLastCollection));
		GCLog("[gcbehavior] zct-traffic-all-gc: peak=%u add=%.0f add-initial-ratio=%.3f remove=%.0f remove-final-ratio=%.3f\n",
			  unsigned(zctPeakSize),
			  double(addZCTLastCollection + addZCTTotal),
			  double(addZCTInitialTotal) / double(addZCTLastCollection + addZCTTotal),
			  double(removeZCTLastCollection + removeZCTTotal),
			  double(removeZCTFinalTotal) / double(removeZCTLastCollection + removeZCTTotal));
#endif

		GCLog("[gcbehavior] time-zct-reap: last-cycle=%.1f total=%.1f\n",
			  ticksToMillis(timeReapZCTLastCollection),
			  ticksToMillis(timeReapZCT));
		GCLog("[gcbehavior] work-zct-reap: reaps=%u objects-reaped=%.0f kbytes-reaped=%.0f objects-pinned=%.0f reaped-to-pinned=%.2f objects-reaped-per-ms=%.2f kbytes-reaped-per-ms=%.1f\n",
			  unsigned(countReapZCT),
			  double(objectsReaped),
			  double(bytesReaped)/1024,
			  double(objectsPinned),
			  countReapZCT > 0 ? double(objectsReaped)/double(objectsPinned) : 0,
			  countReapZCT > 0 ? double(objectsReaped)/ticksToMillis(timeReapZCT) : 0,
			  countReapZCT > 0 ? (double(bytesReaped)/1024)/ticksToMillis(timeReapZCT) : 0);
		GCLog("[gcbehavior] pause-zct-reap: last-cycle=%.1f overall=%.1f\n",
			  pendingClearZCTStats ? 0.0 : ticksToMillis(timeMaxReapZCTLastCollection),
			  ticksToMillis(timeMaxReapZCT));
		if (afterCollection)
		{
			GCLog("[gcbehavior] time-last-gc: in-gc=%.1f end2end=%.1f mutator-efficiency=%.2f%%\n", 
				  ticksToMillis(timeInLastCollection),
				  ticksToMillis(timeEndToEndLastCollection),
				  (timeEndToEndLastCollection == 0.0 ?	// edge cases
				   100.0 :
				   double(timeEndToEndLastCollection - timeInLastCollection) * 100.0 / double(timeEndToEndLastCollection)));
		}
		else
		{
			GCLog("[gcbehavior] time-last-gc: in-gc=%.1f\n", ticksToMillis(timeInLastCollection));
		}
		GCLog("[gcbehavior] time-all-gc: total=%.1f start-incremental-mark=%.1f incremental-mark=%.1f final-root-stack-scan=%.1f finalize-sweep=%.1f\n",
			  ticksToMillis(timeStartIncrementalMark + timeIncrementalMark + timeFinalRootAndStackScan + timeFinalizeAndSweep),
			  ticksToMillis(timeStartIncrementalMark),
			  ticksToMillis(timeIncrementalMark),
			  ticksToMillis(timeFinalRootAndStackScan),
			  ticksToMillis(timeFinalizeAndSweep));
		if (afterCollection || gc->IncrementalMarking()) {
			GCLog("[gcbehavior] pause-last-gc: start-incremental-mark=%.1f incremental-mark=%.1f final-root-stack-scan=%.1f finalize-sweep=%.1f\n",
				  ticksToMillis(timeMaxStartIncrementalMarkLastCollection),
				  ticksToMillis(timeMaxIncrementalMarkLastCollection),
				  ticksToMillis(timeMaxFinalRootAndStackScanLastCollection),
				  ticksToMillis(timeMaxFinalizeAndSweepLastCollection));
		}
		GCLog("[gcbehavior] pause-all-gc: start-incremental-mark=%.1f incremental-mark=%.1f final-root-stack-scan=%.1f finalize-sweep=%.1f\n",
			  ticksToMillis(timeMaxStartIncrementalMark),
			  ticksToMillis(timeMaxIncrementalMark),
			  ticksToMillis(timeMaxFinalRootAndStackScan),
			  ticksToMillis(timeMaxFinalizeAndSweep));
	}
#endif // MMGC_POLICY_PROFILING
	
#ifdef MMGC_POINTINESS_PROFILING
	inline void GCPolicyManager::signalDemographics(size_t candidate_words, size_t could_be_pointer, size_t actually_is_pointer)
	{
		candidateWords += candidate_words;
		couldBePointer += could_be_pointer;
		actuallyIsPointer += actually_is_pointer;
	}
#endif

	REALLY_INLINE void GCPolicyManager::signalFreeWork(size_t nbytes)
	{
		remainingMinorAllocationBudget += int32_t(nbytes);
	}
	
	void GCPolicyManager::signalBlockAllocation(size_t blocks) {
		blocksOwned += blocks;
		if (blocksOwned > maxBlocksOwned)
			maxBlocksOwned = blocksOwned;
	}
	
	void GCPolicyManager::signalBlockDeallocation(size_t blocks) {
		blocksOwned -= blocks;
	}

	void GCPolicyManager::signalMemoryStatusChange(MemoryStatus from, MemoryStatus to) {
		(void)from;
		(void)to;
		// do nothing for the moment
	}

	void GCPolicyManager::signalStartCollection(GC* gc) {
		(void)gc;
		// do nothing for the moment
	}
	
	void GCPolicyManager::signalEndCollection(GC* gc) {
		(void)gc;
		// do nothing for the moment
	}
	
	REALLY_INLINE void GCPolicyManager::signalMarkWork(size_t nbytes)
	{
		objectsScannedLastCollection++;
		bytesScannedLastCollection += uint32_t(nbytes);
	}

#ifdef MMGC_POLICY_PROFILING
	void GCPolicyManager::signalReapWork(uint32_t objects_reaped, uint32_t bytes_reaped, uint32_t objects_pinned)
	{
		objectsReaped += objects_reaped;
		bytesReaped += bytes_reaped;
		objectsPinned += objects_pinned;
 	}
#endif

	////////////// GC //////////////////////////////////////////////////////////

	// Size classes for our GC.  From 8 to 128, size classes are spaced
	// evenly 8 bytes apart.  The finest granularity we can achieve is
	// 8 bytes, as pointers must be 8-byte aligned thanks to our use
	// of the bottom 3 bits of 32-bit atoms for Special Purposes.
	// Above that, the size classes have been chosen to maximize the
	// number of items that fit in a 4096-byte block, given our block
	// header information.
	const int16_t GC::kSizeClasses[kNumSizeClasses] = {
		8, 16, 24, 32, 40, 48, 56, 64, 72, 80, //0-9
		88, 96, 104, 112, 120, 128,	144, 160, 168, 176,  //10-19
		184, 192, 200, 216, 224, 240, 256, 280, 296, 328, //20-29
		352, 392, 432, 488, 560, 656, 784, 984, 1312, 1968 //30-39
	};

	/* kSizeClassIndex[] generated with this code:
	    kSizeClassIndex[0] = 0;
	    for (var i:int = 1; i < kNumSizeClasses; i++)
			for (var j:int = (kSizeClasses[i-1]>>3), n=(kSizeClasses[i]>>3); j < n; j++)
				kSizeClassIndex[j] = i;
	*/

	// index'd by size>>3 - 1
	const uint8_t GC::kSizeClassIndex[246] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10, 11, 12, 13, 14, 15, 16, 16, 17, 17,
		18, 19, 20, 21, 22, 23, 23, 24, 25, 25,
		26, 26, 27, 27, 27, 28, 28, 29, 29, 29,
		29, 30, 30, 30, 31, 31, 31, 31, 31, 32,
		32, 32, 32, 32, 33, 33, 33, 33, 33, 33,
		33, 34, 34, 34, 34, 34, 34, 34, 34, 34,
		35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
		35, 35, 36, 36, 36, 36, 36, 36, 36, 36,
		36, 36, 36, 36, 36, 36, 36, 36, 37, 37,
		37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
		37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
		37, 37, 37, 38, 38, 38, 38, 38, 38, 38,
		38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
		38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
		38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
		38, 38, 38, 38, 39, 39, 39, 39, 39, 39,
		39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
		39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
		39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
		39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
		39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
		39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
		39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
		39, 39, 39, 39, 39, 39	
	};

#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable:4355) // 'this': used in base member initializer list
#endif 

	GC::GC(GCHeap *gcheap, GCMode mode)
		:
		greedy(mode == kGreedyGC),
		nogc(mode == kDisableGC),
		incremental(mode == kIncrementalGC),
		findUnmarkedPointers(false),
		validateDefRef(false),
		keepDRCHistory(false),
		dontAddToZCTDuringCollection(false),
		incrementalValidation(false),
#ifdef _DEBUG
		// check for missing write barriers at every Alloc
		incrementalValidationPedantic(false),
#endif
		rcRootSegments(NULL),
		policy(this, gcheap),
		t0(VMPI_getPerformanceCounter()),
		lastStartMarkIncrementCount(0),
		sweeps(0),
		sweepStart(0),
		emptyWeakRef(0),

		m_gcThread(NULL),
		destroying(false),
		marking(false),
		collecting(false),
		stackCleaned(true),
		rememberedStackTop(0),
		stackEnter(0),
		emptyWeakRefRoot(0),
		m_markStackOverflow(false),
		mark_item_recursion_control(20),	// About 3KB as measured with GCC 4.1 on MacOS X (144 bytes / frame), May 2009
 		sizeClassIndex(kSizeClassIndex),	// see comment in GC.h
		memStart(MAX_UINTPTR),
		memEnd(0),
		heap(gcheap),
		finalizedValue(true),
		smallEmptyPageList(NULL),
		largeEmptyPageList(NULL),
		m_roots(0),
		m_callbacks(0),
		zct()
#ifdef DEBUGGER
		, m_sampler(NULL)
#endif
	{
		// sanity check for all our types
		MMGC_STATIC_ASSERT(sizeof(int8_t) == 1);
		MMGC_STATIC_ASSERT(sizeof(uint8_t) == 1);		
		MMGC_STATIC_ASSERT(sizeof(int16_t) == 2);
		MMGC_STATIC_ASSERT(sizeof(uint16_t) == 2);
		MMGC_STATIC_ASSERT(sizeof(int32_t) == 4);
		MMGC_STATIC_ASSERT(sizeof(uint32_t) == 4);
		MMGC_STATIC_ASSERT(sizeof(int64_t) == 8);
		MMGC_STATIC_ASSERT(sizeof(uint64_t) == 8);
		MMGC_STATIC_ASSERT(sizeof(intptr_t) == sizeof(void *));
		MMGC_STATIC_ASSERT(sizeof(uintptr_t) == sizeof(void *));
		#ifdef MMGC_64BIT
		MMGC_STATIC_ASSERT(sizeof(intptr_t) == 8);
		MMGC_STATIC_ASSERT(sizeof(uintptr_t) == 8);	
		#else	
		MMGC_STATIC_ASSERT(sizeof(intptr_t) == 4);
		MMGC_STATIC_ASSERT(sizeof(uintptr_t) == 4);	
		#endif		

		GCAssert(!(greedy && incremental));
		zct.SetGC(this);

		VMPI_lockInit(&m_gcLock);
		VMPI_lockInit(&m_rootListLock);

		// Create all the allocators up front (not lazy)
		// so that we don't have to check the pointers for
		// NULL on every allocation.
		for (int i=0; i<kNumSizeClasses; i++) {			
			containsPointersAllocs[i] = mmfx_new(GCAlloc(this, kSizeClasses[i], true, false, i));
			containsPointersRCAllocs[i] = mmfx_new(GCAlloc(this, kSizeClasses[i], true, true, i));
			noPointersAllocs[i] = mmfx_new(GCAlloc(this, kSizeClasses[i], false, false, i));
		}
		
		largeAlloc = mmfx_new(GCLargeAlloc(this));

		// See comment in GC.h
		allocsTable[kRCObject] = containsPointersRCAllocs;
		allocsTable[kContainsPointers] = containsPointersAllocs;
		allocsTable[kRCObject|kContainsPointers] = containsPointersRCAllocs;
		allocsTable[0] = noPointersAllocs;

		pageMap = (unsigned char*) heapAlloc(1);

		VMPI_memset(m_bitsFreelists, 0, sizeof(uint32_t*) * kNumSizeClasses);
		m_bitsNext = (uint32_t*)heapAlloc(1);

		// precondition for emptyPageList 
		GCAssert(offsetof(GCLargeAlloc::LargeBlock, next) == offsetof(GCAlloc::GCBlock, next));

		
		for(int i=0; i<GCV_COUNT; i++)
		{
			SetGCContextVariable(i, NULL);
		}

 		allocaInit();

		emptyWeakRefRoot = new GCRoot(this, &this->emptyWeakRef, sizeof(this->emptyWeakRef));
		MMGC_GCENTER(this);
		emptyWeakRef = new (this) GCWeakRef(NULL);

		gcheap->AddGC(this);
		gcheap->AddOOMCallback(this);

	}

#ifdef _MSC_VER
#  pragma warning(pop)
#endif 

	GC::~GC()
	{
		policy.shutdown();
 		allocaShutdown();
		heap->RemoveGC(this);
		heap->RemoveOOMCallback(this);

		// Force all objects to be destroyed
		destroying = true;

		{
			MMGC_GCENTER(this);
			ForceSweepAtShutdown();
		}

		for (int i=0; i < kNumSizeClasses; i++) {
 			mmfx_delete( containsPointersAllocs[i]);
			mmfx_delete(containsPointersRCAllocs[i]);
			mmfx_delete(noPointersAllocs[i]);
		}

		if (largeAlloc) {
			mmfx_delete(largeAlloc);
		}

		// Go through m_bitsFreelist and collect list of all pointers
		// that are on page boundaries into new list, pageList
		void **pageList = NULL;
		for(int i=0, n=kNumSizeClasses; i<n; i++) {
			uint32_t* bitsFreelist = m_bitsFreelists[i];
			while(bitsFreelist) {
				uint32_t *next = *(uint32_t**)bitsFreelist;
				if(((uintptr_t)bitsFreelist & 0xfff) == 0) {
					*((void**)bitsFreelist) = pageList;
					pageList = (void**)bitsFreelist;
				}
				bitsFreelist = next;
			} 
		}
		
		// Go through page list and free all pages on it
		while (pageList) {
			void **next = (void**) *pageList;
			heapFree((void*)pageList);
			pageList = next;
		}

		heapFree(pageMap);

		delete emptyWeakRefRoot;
		GCAssert(!m_roots);
		GCAssert(!m_callbacks);

		// apparently the player can't be made to clean up so keep it from crashing at least
		while(m_roots) {
			m_roots->Destroy();
		}

		while(m_callbacks) {
			m_callbacks->Destroy();			
		}
		
		zct.Destroy();
			
		GCAssertMsg(GetNumBlocks() == 0, "GC accounting off");

		if(stackEnter != NULL) {
			VMPI_lockRelease(&m_gcLock);	
			stackEnter->Destroy();
		}

		VMPI_lockDestroy(&m_gcLock);
		VMPI_lockDestroy(&m_rootListLock);
	}

	void GC::Collect(bool scanStack)
	{
		GCAssertMsg(!scanStack || onThread(), "Full collection with stack scan requested however the GC isn't associated with a thread, missing MMGC_GCENTER macro.");

		if (nogc || collecting || Reaping()) {
			return;
		}
		
		ReapZCT(scanStack);

		if(!marking)
			StartIncrementalMark();
		if(marking)
			FinishIncrementalMark(scanStack);

#ifdef _DEBUG
		// Dumping the stack trace at GC time can be very helpful with stack walk bugs
		// where something was created, stored away in untraced, unmanaged memory and not 
		// reachable by the conservative stack walk
		//DumpStackTrace();
		FindUnmarkedPointers();
#endif
			
		policy.fullCollectionComplete();
	}

#ifdef RECURSIVE_MARK
	REALLY_INLINE void GC::PushWorkItem(GCWorkItem item)
	{
		GCAssert(item.ptr != NULL);
		MarkItem(item);
	}
#else	
	REALLY_INLINE void GC::PushWorkItem(GCWorkItem item)
	{
		GCAssert(item.ptr != NULL);
		GCAssert(!item.IsGCItem() || IsPointerToGCObject(GetRealPointer(item.ptr)));
		if (!m_incrementalWork.Push(item))
			SignalMarkStackOverflow(item);
	}
#endif
	
	void GC::PushWorkItem_MayFail(GCWorkItem &item)
	{
		if (item.ptr)
			PushWorkItem(item);
	}

#ifdef _DEBUG
	bool GC::Trace(const void *stackStart/*=NULL*/, uint32_t stackSize/*=0*/)
	{
		SAMPLE_FRAME("[mark]", core());

		// Kill incremental mark since we're gonna wipe the marks.
		marking = false;
		m_incrementalWork.Clear();
		m_barrierWork.Clear();
		
		// Clear all mark bits.
		ClearMarks();

		SAMPLE_CHECK();

		MarkAllRoots();

		SAMPLE_CHECK();

		if(stackStart == NULL) {
 			// grab the stack, push it, and 
			MarkQueueAndStack();
		} else {
			GCWorkItem item(stackStart, stackSize, false);
			PushWorkItem(item);
			Mark();
		}
		
		SAMPLE_CHECK();

		bool failure = m_markStackOverflow;
		
		ClearMarks();
		
		return !failure;
	}
#endif

	GC::RCRootSegment::RCRootSegment(GC* gc, void* mem, size_t size) 
		: GCRoot(gc, mem, size)
		, mem(mem)
		, size(size)
		, prev(NULL)
		, next(NULL)
	{}

	void* GC::AllocRCRoot(size_t size)
	{
		const int hdr_size = (sizeof(void*) + 7) & ~7;

		GCHeap::CheckForAllocSizeOverflow(size, hdr_size);
		
		union {
			char* block;
			uintptr_t* block_u;
		};
		block = mmfx_new_array_opt(char, size + hdr_size, MMgc::kZero);
		void* mem = (void*)(block + hdr_size);
		RCRootSegment *segment = new RCRootSegment(this, mem, size);
		*block_u = (uintptr_t)segment;
		AddRCRootSegment(segment);
		return mem;
	}
	
	void GC::FreeRCRoot(void* mem)
	{
		const int hdr_size = (sizeof(void*) + 7) & ~7;
		union {
			char* block;
			RCRootSegment** segmentp;
		};
		block = (char*)mem - hdr_size;
		RCRootSegment* segment = *segmentp;
		RemoveRCRootSegment(segment);
		delete segment;
		mmfx_delete_array(block);
	}

	void GC::CollectionWork()
	{
		if (nogc)
			return;
		
		if (incremental) {
			if (!collecting) {
				if (!marking)
					StartIncrementalMark();
				else if (policy.queryEndOfCollectionCycle())
					FinishIncrementalMark(true);
				else
					IncrementalMark();
			}
		}
		else {
			// non-incremental collection
			Collect();
		}
	}

	// Note, the interaction with the policy manager in Alloc() should
	// be the same as in AllocDouble(), which is defined in GC.h.

	// In Alloc we have separate cases for large and small objects.  We want
	// small-object allocation to be as fast as possible.  Hence the relative
	// mess of #ifdefs below, and the following explanation.
	//
	// Normally we round up size to 8 bytes and add DebugSize and that sum is
	// the size that determines whether we use the small-object allocator or
	// the large-object one:
	//
	//   requestSize = ((size + 7) & ~7) + DebugSize()
	//
	// Then we shift that three places and subtract 1 to obtain the allocator
	// index:
	//
	//   index = (requestSize >> 3) - 1
	//         = ((((size + 7) & ~7) + DebugSize()) >> 3) - 1
	//
	// We want to optimize this.  Consider the case of a Release build where
	// DebugSize() == 0:
	//
	//         = (((size + 7) & ~7) >> 3) - 1
	//
	// Observe that the & ~7 is redundant because those bits will be lost,
	// and that 1 = (8 >> 3)
	//
	//         = ((size + 7) >> 3) - (8 >> 3)
	//         = (size + 7 - 8) >> 3
	//   index = (size - 1) >> 3
	//
	// In Release builds, the guard for small object allocation is
	//
	//   guard = requestSize <= kLargestAlloc
	//         = ((size + 7) & ~7) <= kLargestAlloc
	//
	// Yet the /effective/ guard, given that not all the bits of size are used
	// subsequently, is simply
	//
	//   guard = size <= kLargestAlloc
	//
	// To see this, consider that if size < kLargestAlloc then requestSize <= kLargestAlloc
	// and if size > kLargestAlloc then requestSize > kLargestAlloc, because requestSize
	// is rounded up to an 8-byte boundary and kLargestAlloc is already rounded to an 8-byte
	// boundary.
	//
	// So in the small-object case in Release builds we use the simpler guard, and defer
	// the rounding and allocation overflow checking to the large-object case.

#ifdef MMGC_MEMORY_INFO
	#ifndef _DEBUG
		#error "Really need MMGC_MEMORY_INFO to imply _DEBUG"
	#endif
#endif
#ifdef MMGC_MEMORY_PROFILER
	#ifndef MMGC_HOOKS
		#error "Really need MMGC_MEMORY_PROFILER to imply MMGC_HOOKS"
	#endif
#endif
	
	void *GC::Alloc(size_t size, int flags/*0*/)
	{
#ifdef _DEBUG
		GCAssertMsg(size > 0, "cannot allocate a 0 sized block\n");
		GCAssertMsg(onThread(), "GC called from different thread!");
		
		if(!nogc && stackEnter == NULL) {
			GCAssertMsg(false, "A MMGC_GCENTER macro must exist on the stack");
			GCHeap::SignalInconsistentHeapState("MMGC_GCENTER missing");
			/*NOTREACHED*/
			return NULL;
		}
		
		// always be marking in pedantic mode
		if(incrementalValidationPedantic) {
			if(!marking)
				StartIncrementalMark();
		}
#endif
#ifdef AVMPLUS_SAMPLER
		avmplus::AvmCore *core = (avmplus::AvmCore*)GetGCContextVariable(GCV_AVMCORE);
		if(core)
			core->sampleCheck();
#endif

#if defined _DEBUG || defined MMGC_MEMORY_PROFILER
		const size_t askSize = size;	// preserve this for statistics gathering and profiling
#endif
#if defined _DEBUG
		GCHeap::CheckForAllocSizeOverflow(size, 7+DebugSize());
		size = (size+7)&~7;				// round up to multiple of 8
		size += DebugSize();			// add in some (possibly zero) multiple of 8 bytes for debug information
#endif

		void *item;						// the allocated object (a user pointer!), or NULL
		
		// In Release builds the calls to the underlying Allocs should end up being compiled
		// as tail calls with reasonable compilers.  Try to keep it that way.

		if (size <= kLargestAlloc)
		{
			// This is the fast lookup table implementation to find the right allocator.
			// The table has been lifted into an instance variable because the Player is
			// compiled with PIC and GCC generates somewhat gnarly code for that.
#ifdef _DEBUG
			const unsigned index = sizeClassIndex[(size>>3)-1];
#else
			const unsigned index = sizeClassIndex[(size-1)>>3];
#endif

			// The table avoids a thre-way decision tree.
			GCAlloc **allocs = allocsTable[flags & (kRCObject|kContainsPointers)];

			// assert that I fit 
			GCAssert(size <= allocs[index]->GetItemSize());
			
			// assert that I don't fit (makes sure we don't waste space)
			GCAssert( (index==0) || (size > allocs[index-1]->GetItemSize()));
			
#if defined _DEBUG || defined MMGC_MEMORY_PROFILER
			item = allocs[index]->Alloc(askSize, flags);
#else
			item = allocs[index]->Alloc(flags);
#endif
		}
		else
		{
#ifndef _DEBUG
			GCHeap::CheckForAllocSizeOverflow(size, 7+DebugSize());
			size = (size+7)&~7; // round up to multiple of 8
			size += DebugSize();
#endif
#if defined _DEBUG || defined MMGC_MEMORY_PROFILER
			item = largeAlloc->Alloc(askSize, size, flags);
#else
			item = largeAlloc->Alloc(size, flags);
#endif
		}

		// Hooks are run by the lower-level allocators, which also signal
		// allocation work and trigger GC.

		GCAssert(item != NULL || (flags & kCanFail) != 0);

#ifdef _DEBUG
		// Note GetUserPointer(item) only required for DEBUG builds and for non-NULL pointers.
		
		if(item != NULL) {
			item = GetUserPointer(item);
			bool shouldZero = (flags & kZero) || incrementalValidationPedantic;
			
			// in debug mode memory is poisoned so we have to clear it here
			// in release builds memory is zero'd to start and on free/sweep
			// in pedantic mode uninitialized data can trip the write barrier 
			// detector, only do it for pedantic because otherwise we want the
			// mutator to get the poisoned data so it crashes if it relies on 
			// uninitialized values
			if(shouldZero) {
				VMPI_memset(item, 0, Size(item));
			}
		}
#endif

		return item;
	}

	// Mmmm.... gcc -O3 inlines Alloc into this in Release builds :-)

	void *GC::OutOfLineAllocExtra(size_t size, size_t extra, int flags)
	{
		return AllocExtra(size, extra, flags);
	}

	void GC::FreeNotNull(const void *item)
	{
		GCAssert(item != NULL);
		GCAssertMsg(onThread(), "GC called from a different thread or not associated with a thread, missing MMGC_GCENTER macro perhaps.");

		// Collecting is true only if marking is true (global invariant), so subsume the test,
		// collecting is almost never true anyway.
		
		GCAssert(collecting == false || marking == true);

		if (marking) {
			// We can't allow free'ing something during Sweeping, otherwise alloc counters
			// get decremented twice and destructors will be called twice.

			if(collecting)
				goto bail;
			
			// If its on the work queue don't delete it, if this item is
			// really garbage we're just leaving it for the next sweep.
			//
			// OPTIMIZEME: IsQueued() is pretty expensive, because it computes
			// the bits index and reads the bits array.  If marking is true much
			// of the time then this could become a bottleneck.  As we improve
			// GC incrementality, marking /is/ expected to be true much of the time.
			//
			// Could we optimize by having a flag that's set when the mark queue
			// isn't empty?  We'd need to worry about the barrier queue too and that
			// will usually not be empty.  So:
			//
			//  - short term do nothing, or maybe land the bit vector improvement
			//  - with a card marking barrier the barrier queue doesn't matter,
			//    maybe the mark queue flag will help then (but then we'll also have
			//    the bit vector improvement)
			//
			// A further observation is that we only care about objects owned by
			// a particular allocator being queued or not.  Since we can spend a little
			// more effort when pushing something on the barrier stack, perhaps we
			// could have a quick test on "anything on the mark stack for any allocator,
			// or anything on the barrier stack belonging to this allocator?".
			// Again, future work.

			if(IsQueued(item)) 
				goto bail;
		}

#ifdef _DEBUG
		// RCObject have contract that they must clean themselves, since they 
		// have to scan themselves to decrement other RCObjects they might as well
		// clean themselves too, better than suffering a memset later
		if(IsRCObject(item))
		{
			 RCObjectZeroCheck((RCObject*)item);
		}
#endif

		// All hooks are called inside the Free functions.  The calls to Free should
		// be tail calls on reasonable compilers.

		policy.signalFreeWork(Size(item));
		
		if (GCLargeAlloc::IsLargeBlock(GetRealPointer(item))) {
			largeAlloc->Free(GetRealPointer(item));
		} else {
			GCAlloc::Free(GetRealPointer(item));
		}
		return;

bail:

		// this presumes we got here via delete, maybe we should have
		// delete call something other than the public Free to distinguish
		if(IsFinalized(item))
			ClearFinalized(item);
		if(HasWeakRef(item))
			ClearWeakRef(item);
	}

	void GC::ClearMarks()
	{
		for (int i=0; i < kNumSizeClasses; i++) {
			containsPointersRCAllocs[i]->ClearMarks();
			containsPointersAllocs[i]->ClearMarks();
			noPointersAllocs[i]->ClearMarks();
		}
		largeAlloc->ClearMarks();
		m_markStackOverflow = false;
	}

	void GC::Finalize()
	{
		for(int i=0; i < kNumSizeClasses; i++) {
			containsPointersRCAllocs[i]->Finalize();
			containsPointersAllocs[i]->Finalize();
			noPointersAllocs[i]->Finalize();
		}
		largeAlloc->Finalize();
		finalizedValue = !finalizedValue;

		
		for(int i=0; i < kNumSizeClasses; i++) {
			containsPointersRCAllocs[i]->m_finalized = false;
			containsPointersAllocs[i]->m_finalized = false;
			noPointersAllocs[i]->m_finalized = false;
		}
	}

	void GC::SweepNeedsSweeping()
	{
		// clean up any pages that need sweeping
		for(int i=0; i < kNumSizeClasses; i++) {
			containsPointersRCAllocs[i]->SweepNeedsSweeping();
			containsPointersAllocs[i]->SweepNeedsSweeping();
			noPointersAllocs[i]->SweepNeedsSweeping();
		}
	}

	void GC::ForceSweepAtShutdown()
	{
		// There are two preconditions for Sweep: the mark stacks must be empty, and
		// the queued bits must all be clear (except as part of kFreelist).  
		//
		// We are doing this at shutdown, so don't bother with pushing the marking through
		// to the end; just clear the stacks, clear the mark bits, and sweep.  The objects
		// will be finalized and deallocated and the blocks will be returned to the block
		// manager.

		m_incrementalWork.Clear();
		m_barrierWork.Clear();
		
		ClearMarks();

		// System invariant: collecting == false || marking == true
		marking = true;
		Sweep();
		marking = false;
	}

	void GC::Sweep()
	{	
		// 'collecting' must be true because it indicates allocations should
		// start out marked and the write barrier should short-circuit (not
		// record any hits).  We can't rely on write barriers to mark objects
		// during finalization below since presweep or finalization could write
		// a new GC object to a root.

		GCAssert(m_incrementalWork.Count() == 0);
		GCAssert(m_barrierWork.Count() == 0);
		
		collecting = true;
		zct.StartCollecting();
		
		SAMPLE_FRAME("[sweep]", core());
		sweeps++;

		size_t heapSize = heap->GetUsedHeapSize();

#ifdef MMGC_MEMORY_PROFILER
		if(heap->Config().autoGCStats) {
			GCLog("Before sweep memory info:\n");
			DumpMemoryInfo();
		}
#endif

		GCAssert(m_incrementalWork.Count() == 0);
		GCAssert(m_barrierWork.Count() == 0);
		
		// invoke presweep on all callbacks
		for ( GCCallback *cb = m_callbacks; cb ; cb = cb->nextCB )
			cb->presweep();

		SAMPLE_CHECK();

		// The presweep callbacks can't drive marking or trigger write barriers as the barrier is disabled, 
		// but they can cause elements to be pushed onto the mark stack explicitly and it's necessary to call mark.
		// One example of callback that pushes work items is the Sampler::presweep().
		do {
			if (m_markStackOverflow) {
				m_markStackOverflow = false;
				HandleMarkStackOverflow();
			}
			Mark();
		} while (m_markStackOverflow);

		SAMPLE_CHECK();

		GCAssert(m_incrementalWork.Count() == 0);
		GCAssert(m_barrierWork.Count() == 0);

#ifdef MMGC_HEAP_GRAPH
		pruneBlacklist();
#endif

		Finalize();

		SAMPLE_CHECK();

		GCAssert(m_incrementalWork.Count() == 0);
		GCAssert(m_barrierWork.Count() == 0);

		int sweepResults = 0;

		// ISSUE: this could be done lazily at the expense other GC's potentially expanding
		// unnecessarily, not sure its worth it as this should be pretty fast
		GCAlloc::GCBlock *b = smallEmptyPageList;
		while(b) {
			GCAlloc::GCBlock *next = GCAlloc::Next(b);
#ifdef _DEBUG
			b->alloc->SweepGuts(b);
#endif
			b->alloc->FreeChunk(b);

			sweepResults++;
			b = next;
		}
		smallEmptyPageList = NULL;

		SAMPLE_CHECK();

		GCLargeAlloc::LargeBlock *lb = largeEmptyPageList;		
		while(lb) {
			GCLargeAlloc::LargeBlock *next = GCLargeAlloc::Next(lb);
#ifdef MMGC_HOOKS
			if(heap->HooksEnabled())
				heap->FreeHook(GetUserPointer(lb+1), lb->size - DebugSize(), 0xba);
#endif
			int numBlocks = lb->GetNumBlocks();
			sweepResults += numBlocks;
			FreeBlock(lb, numBlocks);
			lb = next;
		}
		largeEmptyPageList = NULL;
		
		if (heap->Config().eagerSweeping)
			SweepNeedsSweeping();

		// we potentially freed a lot of memory, tell heap to regulate
		heap->Decommit();

		SAMPLE_CHECK();

#ifdef MMGC_MEMORY_PROFILER
		if(heap->Config().autoGCStats) {			
			GCLog("After sweep memory info:\n");
			DumpMemoryInfo();
		}
#endif

		// don't want postsweep to fire WB's
		collecting = false;
		marking = false;
		zct.EndCollecting();
		
		// invoke postsweep callback
		for ( GCCallback *cb = m_callbacks; cb ; cb = cb->nextCB )
			cb->postsweep();

		SAMPLE_CHECK();

		if(heap->Config().gcstats) {
			// include large pages given back
			sweepResults += int(heapSize - heap->GetUsedHeapSize());
			double millis = duration(sweepStart);
			gclog("[mem] sweep(%d) reclaimed %d whole pages (%d kb) in %.2f millis (%.4f s)\n", 
				sweeps, sweepResults, sweepResults*GCHeap::kBlockSize>>10, millis,
				duration(t0)/1000);
		}
		
#ifdef MMGC_HEAP_GRAPH
		printBlacklist();
#endif

	}

	void* GC::AllocBlock(int size, int pageType, bool zero, bool canFail)
	{
		GCAssert(size > 0);
	
		void *item = heapAlloc(size, zero ? GCHeap::kZero : 0);

		if(!item)
			item = heapAlloc(size, GCHeap::kExpand| (zero ? GCHeap::kZero : 0) | (canFail ? GCHeap::kCanFail : 0));

		// mark GC pages in page map, small pages get marked one,
		// the first page of large pages is 3 and the rest are 2
		if(item) {
			MarkGCPages(item, 1, pageType);
			if(pageType == kGCLargeAllocPageFirst) {
				MarkGCPages((char*)item+GCHeap::kBlockSize, size - 1, kGCLargeAllocPageRest);
			}
		}

		return item;
	}

	void GC::FreeBlock(void *ptr, uint32_t size)
	{
		heapFree(ptr, size, false);
		UnmarkGCPages(ptr, size);
	}

	REALLY_INLINE void GC::SetPageMapValue(uintptr_t addr, int val)
	{
		uintptr_t index = (addr-memStart) >> 12;
#ifdef MMGC_64BIT
		GCAssert((index >> 2) < uintptr_t(64*65536) * uintptr_t(GCHeap::kBlockSize));
#else
		GCAssert(index >> 2 < 64 * GCHeap::kBlockSize);
#endif
		pageMap[index >> 2] |= (val<<((index&0x3)*2));
	}	

	REALLY_INLINE void GC::ClearPageMapValue(uintptr_t addr)
	{
		uintptr_t index = (addr-memStart) >> 12;
#ifdef MMGC_64BIT
		GCAssert((index >> 2) < uintptr_t(64*65536) * uintptr_t(GCHeap::kBlockSize));
#else
		GCAssert((index >> 2) < 64 * GCHeap::kBlockSize);
#endif
		pageMap[index >> 2] &= ~(3<<((index&0x3)*2));
	}	

	void *GC::FindBeginningGuarded(const void *gcItem, bool allowGarbage)
	{
		(void)allowGarbage;
		void *realItem = NULL;
		int bits = GetPageMapValueGuarded((uintptr_t)gcItem);
		switch(bits)
		{
			case kGCAllocPage:
				realItem = GCAlloc::FindBeginning(gcItem);
				break;
			case kGCLargeAllocPageFirst:
				realItem = GCLargeAlloc::FindBeginning(gcItem);
				break;
			case kGCLargeAllocPageRest:
				while(bits == kGCLargeAllocPageRest)
				{
					gcItem = (void*) ((uintptr_t)gcItem - GCHeap::kBlockSize);
					bits = GetPageMapValue((uintptr_t)gcItem);
				}
				realItem = GCLargeAlloc::FindBeginning(gcItem);
				break;
			default:
				GCAssertMsg(allowGarbage, "FindBeginningGuarded must not be called on non-managed addresses");
				// The NULL return is a documented effect of this function, and is desired, despite 
				// the assert above.
				return NULL;
		}		
		return GetUserPointer(realItem);
	}
	
	void GC::Mark()
	{
		while(m_incrementalWork.Count()) {
 			GCWorkItem item = m_incrementalWork.Pop();
			MarkItem(item);
		}
	}

	void GC::MarkGCPages(void *item, uint32_t numPages, int to)
	{
		uintptr_t addr = (uintptr_t)item;
		size_t shiftAmount=0;
		unsigned char *dst = pageMap;

		// save the current live range in case we need to move/copy
		size_t numBytesToCopy = (memEnd-memStart)>>14;

		if(addr < memStart) {
			// round down to nearest 16k boundary, makes shift logic work cause it works
			// in bytes, ie 16k chunks
			addr &= ~0x3fff;
			// marking earlier pages
			if(memStart != MAX_UINTPTR) {
				shiftAmount = (memStart - addr) >> 14;
			}
			memStart = addr;
		} 
		
		if(addr + (numPages+1)*GCHeap::kBlockSize > memEnd) {
			// marking later pages
			memEnd = addr + (numPages+1)*GCHeap::kBlockSize;
			// round up to 16k 
			memEnd = (memEnd+0x3fff)&~0x3fff;
		}

        uint32_t numPagesNeeded = (uint32_t)(((memEnd-memStart)>>14)/GCHeap::kBlockSize + 1);
		if(numPagesNeeded > heap->Size(pageMap)) {
			dst = (unsigned char*)heapAlloc(numPagesNeeded);
		}

		if(shiftAmount || dst != pageMap) {
			VMPI_memmove(dst + shiftAmount, pageMap, numBytesToCopy);
			if ( shiftAmount ) {
				VMPI_memset(dst, 0, shiftAmount);
			}
			if(dst != pageMap) {
				heapFree(pageMap);
				pageMap = dst;
			}
		}

		addr = (uintptr_t)item;
		while(numPages--)
		{
			GCAssert(GetPageMapValue(addr) == 0);
			SetPageMapValue(addr, to);
			addr += GCHeap::kBlockSize;
		}
	}

	void GC::UnmarkGCPages(void *item, uint32_t numpages)
	{
		uintptr_t addr = (uintptr_t) item;

		while(numpages--)
		{
			ClearPageMapValue(addr);
			addr += GCHeap::kBlockSize;
		}
	}
	

	void GC::CleanStack(bool force)
	{
		if(!force && (stackCleaned || rememberedStackTop == 0))
			return;

		stackCleaned = true;
		
		register void *stackP = 0;
		size_t size;

		MMGC_GET_STACK_EXTENTS(this, stackP, size);

		if( ((char*) stackP > (char*)rememberedStackTop) && ((char *)stackEnter > (char*)stackP)) {
			size_t amount = (char*) stackP - (char*)rememberedStackTop;
			VMPI_cleanStack(amount);
		}
	}

	#if defined(MMGC_PPC) && defined(__GNUC__)
	__attribute__((noinline)) 
	#endif
	void GC::MarkQueueAndStack(bool scanStack)
	{
		if(scanStack) {
			GCWorkItem item;
			MMGC_GET_STACK_EXTENTS(this, item.ptr, item._size);
			GCAssert(item.ptr != NULL);

			// this is where we will clear to when CleanStack is called
			if(rememberedStackTop < item.ptr) {
				rememberedStackTop = item.ptr;
			}
			PushWorkItem(item);
		}
		Mark();
	}

	void GCRoot::init(GC* _gc, const void *_object, size_t _size)
	{
		gc = _gc;
		object = _object;
		size = _size;
		GCAssert(size % 2 == 0);
		gc->AddRoot(this);
	}

	GCRoot::GCRoot(GC * _gc)
	{
		init(_gc, this, FixedMalloc::GetFixedMalloc()->Size(this));
	}

	GCRoot::GCRoot(GC * _gc, const void * _object, size_t _size)
	{
		init(_gc, _object, _size);
	}

	GCRoot::~GCRoot()
	{
		if(gc) {
			gc->RemoveRoot(this);
		}
	}

	void GCRoot::Set(const void * _object, size_t _size)
	{
		this->object = _object;
		this->size = _size;
	}

	void GCRoot::Destroy()
	{
		Set(NULL, 0);
		if(gc) {
			gc->RemoveRoot(this);
		}
		gc = NULL;
	}

	GCCallback::GCCallback(GC * _gc) : gc(_gc)
	{
		gc->AddCallback(this);
	}

	GCCallback::~GCCallback()
	{
		if(gc) {
			gc->RemoveCallback(this);
		}
	}

	void GCCallback::Destroy()
	{
		if(gc) {
			gc->RemoveCallback(this);
		}
		gc = NULL;
	}

#ifdef _DEBUG
    bool GC::IsPointerIntoGCObject(const void *item)
	{
		int bits = GetPageMapValueGuarded((uintptr_t)item); 
		switch(bits) {
			case kGCAllocPage:
				return GCAlloc::IsPointerIntoGCObject(item);
			case kGCLargeAllocPageFirst:
				return item >= GCLargeAlloc::FindBeginning(item);
			case kGCLargeAllocPageRest:
				return true;
			default:
				return false;
		}
    }
#endif

#if 0
	// this is a release ready tool for hunting down freelist corruption
	void GC::CheckFreelists()
	{
		GCAlloc **allocs = containsPointersAllocs;
		for (int l=0; l < GC::kNumSizeClasses; l++) {
			GCAlloc *a = allocs[l];
			GCAlloc::GCBlock *_b = a->m_firstBlock;	
			while(_b) {
				void *fitem = _b->firstFree;
				void *prev = 0;
				while(fitem) {
					if((uintptr(fitem) & 7) != 0) {
						_asm int 3;
						break;
					}
					if((uintptr(fitem) & ~0xfff) != uintptr(_b))
						_asm int 3;
					prev = fitem;
					fitem = *(void**)fitem;
				}		
				_b = _b->next;
			}
		}
	}
#endif

#ifdef _DEBUG

	void GC::RCObjectZeroCheck(RCObject *item)
	{
		size_t size = Size(item)/sizeof(uint32_t);
		uint32_t *p = (uint32_t*)item;
		uint32_t *limit = p+size;
		// skip vtable, first 4 bytes are cleared in Alloc
		p++;
#ifdef MMGC_64BIT
		p++; // vtable is 8-bytes
		size--; 
#endif		
		// in incrementalValidation mode manually deleted items
		// aren't put on the freelist so skip them
		if(incrementalValidation) {
			if(*p == 0xcacacaca)
				return;
		}
		for ( ; p < limit ; p++ )
		{
			if(*p)
			{
				PrintAllocStackTrace(item);
				GCAssertMsg(false, "RCObject didn't clean up itself.");
				// If you hit this assert, use the debugger to cast 'item' to the type indicated by the call stack 
				// in the output (you'll have to qualify the scope - (coreplayer::View*) rather than (View*)
				// and check to see that all fields are 0 (even boolean members). This Is a 
				// performance optimization that lets the GC avoid zero'ing the whole thing itself.
			}
		}	
	}

#endif
	
#ifdef WIN32

	uintptr_t GC::GetOSStackTop() const
	{
		MEMORY_BASIC_INFORMATION __mib;
		VirtualQuery(&__mib, &__mib, sizeof(MEMORY_BASIC_INFORMATION));
		return (uintptr_t)__mib.BaseAddress + __mib.RegionSize;
	}

#elif defined(SOLARIS)
#include <ucontext.h>
#include <sys/frame.h>
#include <sys/stack.h>

#ifdef MMGC_SPARC
#define FLUSHWIN() asm("ta 3"); 
#else
#define FLUSHWIN() 
#endif
	pthread_key_t stackTopKey = NULL;

	uintptr_t	GC::GetOSStackTop() const
	{
		FLUSHWIN();

		if(stackTopKey == NULL)
			{
				int res = pthread_key_create(&stackTopKey, NULL);
				GCAssert(res == 0);
			}

		void *stackTop = pthread_getspecific(stackTopKey);
		if(stackTop)
			return (uintptr_t)stackTop;

		struct frame *sp;
		int i;
		int *iptr;

		stack_t st;
		stack_getbounds(&st);
		uintptr_t stack_base = (uintptr_t)st.ss_sp + st.ss_size;
		pthread_setspecific(stackTopKey, (void*)stack_base);
		return (uintptr_t)stack_base;
	}
#elif defined(AVMPLUS_UNIX) // SOLARIS
	pthread_key_t stackTopKey = 0;

	uintptr_t GC::GetOSStackTop() const
	{
		if(stackTopKey == 0)
		{
#ifdef DEBUG		  
			int res = 
#endif
			  pthread_key_create(&stackTopKey, NULL);
			GCAssert(res == 0);
		}

		void *stackTop = pthread_getspecific(stackTopKey);
		if(stackTop)
			return (uintptr_t)stackTop;

		size_t sz;
		void *s_base;
		pthread_attr_t attr;
		
		pthread_attr_init(&attr);
		// WARNING: stupid expensive function, hence the TLS
		int res = pthread_getattr_np(pthread_self(),&attr);
		GCAssert(res == 0);
		
		if(res)
		{
			// not good
			return 0;
		}

		res = pthread_attr_getstack(&attr,&s_base,&sz);
		GCAssert(res == 0);
		pthread_attr_destroy(&attr);

		stackTop = (void*) ((size_t)s_base + sz);
		// stackTop has to be greater than current stack pointer
		GCAssert(stackTop > &sz);
		pthread_setspecific(stackTopKey, stackTop);
		return (uintptr_t)stackTop;
		
	}
#endif // AVMPLUS_UNIX

#if defined(_MAC) || defined(MMGC_MAC_NO_CARBON)
	uintptr_t GC::GetOSStackTop() const
	{
		return (uintptr_t)pthread_get_stackaddr_np(pthread_self());
	}
#endif

#if defined(LINUX) && defined(MMGC_ARM) && !defined(AVMPLUS_UNIX)
	uintptr_t GC::GetOSStackTop() const
	{
		void* sp;
		pthread_attr_t attr;
		pthread_getattr_np(pthread_self(), &attr);
		pthread_attr_getstackaddr(&attr, &sp);
		return (uintptr_t)sp;
	}
#endif

#ifdef VMCFG_SYMBIAN
	uintptr_t GC::GetOSStackTop() const
	{
		TThreadStackInfo info;
		RThread mythread;
		mythread.StackInfo(info);
		return uintptr_t(info.iBase);
	}
#endif // VMCFG_SYMBIAN

	void GC::gclog(const char *format, ...)
	{
		(void)format;
		char buf[4096];
		va_list argptr;

		va_start(argptr, format);
		vsprintf(buf, format, argptr);
		va_end(argptr);

		GCAssert(VMPI_strlen(buf) < 4096);

		VMPI_log(buf);

		// log gross stats any time anything interesting happens
		static bool g_in_gclog = false;
		
		bool was_in_gclog;
		{
			MMGC_LOCK(heap->gclog_spinlock);
			was_in_gclog = g_in_gclog;
			g_in_gclog = true;
		}

		if(!was_in_gclog && !destroying)
			heap->DumpMemoryInfo();

		{
			MMGC_LOCK(heap->gclog_spinlock);
			g_in_gclog = was_in_gclog;
		}
	}

	bool GC::IsRCObject(const void *item)
	{
		if ((uintptr_t)item < memStart || (uintptr_t)item >= memEnd || ((uintptr_t)item&0xfff) == 0)
			return false;
		
		int bits = GetPageMapValue((uintptr_t)item);
		item = GetRealPointer(item);
		switch(bits)
		{
		case kGCAllocPage:
			return GCAlloc::IsRCObject(item);
		case kGCLargeAllocPageFirst:
			return GCLargeAlloc::IsRCObject(item);
		default:
			return false;
		}
	}

	void GC::DumpAlloc(GCAlloc *a, size_t& internal_waste, size_t& overhead)
	{
		int inUse =  a->GetNumAlloc() * a->GetItemSize();
		int maxAlloc =  a->GetMaxAlloc()* a->GetItemSize();

		overhead = maxAlloc-inUse;
		internal_waste = 0;

		int efficiency = maxAlloc > 0 ? inUse * 100 / maxAlloc : 100;
		if(inUse) {
			const char *name = a->ContainsPointers() ? a->ContainsRCObjects() ? "rc" : "gc" : "opaque";
			if(heap->config.verbose)
				GCLog("[mem] gc[%d] %s allocator:   %d%% efficiency %d bytes (%d kb) in use out of %d bytes (%d kb)\n", a->GetItemSize(), name, efficiency, inUse, inUse>>10, maxAlloc, maxAlloc>>10);
#ifdef MMGC_MEMORY_PROFILER
			if(heap->HooksEnabled())
			{
				size_t askSize = a->GetTotalAskSize();
				internal_waste = inUse - askSize;
				size_t internal_efficiency = askSize * 100 / inUse;
				if(heap->config.verbose)
					GCLog("\t\t\t\t %u%% internal efficiency %u bytes (%u kb) actually requested out of %d bytes(%d kb)\n", internal_efficiency, (uint32_t) askSize, (uint32_t)(askSize>>10), inUse, inUse>>10);
			}
#endif
		}
	}

	void GC::DumpMemoryInfo()
	{
		size_t total = GetNumBlocks() * GCHeap::kBlockSize;

		size_t ask;
		size_t allocated;
		GetUsageInfo(ask, allocated);

		heap->log_percentage("[mem] \tmanaged overhead ", total-allocated, total);
#ifdef MMGC_MEMORY_PROFILER
		if(heap->HooksEnabled())
			heap->log_percentage("[mem] \tmanaged internal wastage", allocated-ask, allocated);
#endif

		if(ticksToMillis(markTicks()) != 0 && bytesMarked() != 0) {
			uint32_t markRate = (uint32_t) (bytesMarked() / (1024 * ticksToMillis(markTicks()))); // kb/ms == mb/s
			GCLog("[mem] \tmark rate %u mb/s\n", markRate);
		}
		GCLog("[mem] \tmark increments %d\n", markIncrements());
		GCLog("[mem] \tsweeps %d \n", sweeps);
		
		size_t total_overhead = 0;
		size_t total_internal_waste = 0;
		GCAlloc** allocators[] = {containsPointersRCAllocs, containsPointersAllocs, noPointersAllocs};
		for(int j = 0;j<3;j++)
		{
			GCAlloc** gc_alloc = allocators[j]; 

			for(int i=0; i < kNumSizeClasses; i++)
			{
				size_t internal_waste;
				size_t overhead;
				DumpAlloc(gc_alloc[i], internal_waste, overhead);
				total_internal_waste += internal_waste;
				total_overhead += overhead;
			}
		}
		GCLog("Overhead %u bytes (%u kb)\n", (uint32_t)total_overhead, (uint32_t)(total_overhead>>10));
#ifdef MMGC_MEMORY_PROFILER
		if(heap->HooksEnabled())
			GCLog("Internal Wastage %u bytes (%u kb)\n", (uint32_t)total_internal_waste, (uint32_t)(total_internal_waste>>10));
#endif
	}

#ifdef MMGC_MEMORY_PROFILER
	// It only makes sense to call this after a END_FinalizeAndSweep event and
	// before the next START_StartIncrementalMark event.
	void GC::DumpPauseInfo()
	{
		if (!nogc && incremental) {
			GCLog("[mem] \tpauses in GC, most recent (ms): startmark=%.2f incrementalmark=%.2f finalscan=%.2f finishmark=%.2f reap=%.2f\n",
				  double(ticksToMicros(policy.timeMaxStartIncrementalMarkLastCollection)) / 1000.0,
				  double(ticksToMicros(policy.timeMaxIncrementalMarkLastCollection)) / 1000.0,
				  double(ticksToMicros(policy.timeMaxFinalRootAndStackScanLastCollection)) / 1000.0,
				  double(ticksToMicros(policy.timeMaxFinalizeAndSweepLastCollection)) / 1000.0,
				  double(ticksToMicros(policy.timeMaxReapZCTLastCollection)) / 1000.0);
			GCLog("[mem] \tpauses in GC, entire run (ms): startmark=%.2f incrementalmark=%.2f finalscan=%.2f finishmark=%.2f reap=%.2f\n",
				  double(ticksToMicros(policy.timeMaxStartIncrementalMark)) / 1000.0,
				  double(ticksToMicros(policy.timeMaxIncrementalMark)) / 1000.0,
				  double(ticksToMicros(policy.timeMaxFinalRootAndStackScan)) / 1000.0,
				  double(ticksToMicros(policy.timeMaxFinalizeAndSweep)) / 1000.0,
				  double(ticksToMicros(policy.timeMaxReapZCT)) / 1000.0);
			GCLog("[mem] \tpause clustering in GC, most recent: gctime=%.2fms end-to-end=%.2fms;  mutator efficacy: %.2f%%\n", 
				  double(ticksToMicros(policy.timeInLastCollection)) / 1000.0,
				  double(ticksToMicros(policy.timeEndToEndLastCollection)) / 1000.0,
				  policy.timeInLastCollection == 0 ? // Sometimes there are no collections
				  100.0 :
				  double(policy.timeEndToEndLastCollection - policy.timeInLastCollection) * 100.0 / double(policy.timeEndToEndLastCollection));
		}
	}
#endif // MMGC_MEMORY_PROFILER

#ifdef _DEBUG

	void GC::CheckFreelists()
	{
		for(int i=0; i < kNumSizeClasses; i++)
		{
			containsPointersAllocs[i]->CheckFreelist();
			containsPointersRCAllocs[i]->CheckFreelist();
			noPointersAllocs[i]->CheckFreelist();
		}
	}

	void GC::UnmarkedScan(const void *mem, size_t size)
	{
		uintptr_t lowerBound = memStart;
		uintptr_t upperBound = memEnd;
		
		uintptr_t *p = (uintptr_t *) mem;
		uintptr_t *end = p + (size / sizeof(void*));

		while(p < end)
		{
			uintptr_t val = *p++;
			
			if(val < lowerBound || val >= upperBound)
				continue;
			
			// normalize and divide by 4K to get index
			int bits = GetPageMapValue(val);
			switch(bits)
			{
			case kNonGC:
				continue;
			case kGCAllocPage:
				GCAssert(GCAlloc::ConservativeGetMark((const void*) (val&~7), true));
				break;
			case kGCLargeAllocPageFirst:
				GCAssert(GCLargeAlloc::ConservativeGetMark((const void*) (val&~7), true));
				break;
			default:
				GCAssertMsg(false, "Invalid pageMap value");
				break;
			}
		}
	}

	// For every page in the address range known to this GC, scan the page conservatively
	// for pointers and assert that anything that looks like a pointer to an object
	// points to an object that's marked.
	//
	// FIXME: This looks like it could be prone to signaling false positives and crashes:
	// it scans memory that's marked kNonGC, and some of that memory could even be
	// unmapped at the VM level?
	
	void GC::FindUnmarkedPointers()
	{
		if(findUnmarkedPointers)
		{
			uintptr_t m = memStart;

			while(m < memEnd)
			{
				// divide by 4K to get index
				int bits = GetPageMapValue(m);
				if(bits == kNonGC) {
					UnmarkedScan((const void*)m, GCHeap::kBlockSize);
					m += GCHeap::kBlockSize;
				} else if(bits == kGCLargeAllocPageFirst) {
					GCLargeAlloc::LargeBlock *lb = (GCLargeAlloc::LargeBlock*)m;
					const void *item = GetUserPointer((const void*)(lb+1));
					if(GCLargeAlloc::GetMark(item) && GCLargeAlloc::ContainsPointers(GetRealPointer(item))) {
						UnmarkedScan(item, Size(item));
					}
					m += lb->GetNumBlocks() * GCHeap::kBlockSize;
				} else if(bits == kGCAllocPage) {
					// go through all marked objects
					GCAlloc::GCBlock *b = (GCAlloc::GCBlock *) m;
                    for (int i=0; i < b->alloc->m_itemsPerBlock; i++) {
                        // If the mark is 0, delete it.
                        int marked = GCAlloc::GetBit(b, i, GCAlloc::kMark);
                        if (!marked) {
                            void* item = (char*)b->items + b->alloc->m_itemSize*i;
                            if(GCAlloc::ContainsPointers(item)) {
								UnmarkedScan(GetUserPointer(item), b->alloc->m_itemSize - DebugSize());
							}
						}
					}
					
					m += GCHeap::kBlockSize;
				}				 
			}
		}
	}

	void GC::ProbeForMatch(const void *mem, size_t size, uintptr_t value, int recurseDepth, int currentDepth)
	{
		uintptr_t lowerBound = memStart;
		uintptr_t upperBound = memEnd;
		
		uintptr_t *p = (uintptr_t *) mem;
		uintptr_t *end = p + (size / sizeof(void*));

		int bits = GetPageMapValue((uintptr_t)mem);

		while(p < end)
		{
			uintptr_t val = *p++;
			
			if(val < lowerBound || val >= upperBound)
				continue;

			// did we hit ?
			if (val == value)
			{
				// ok so let's see where we are 
				uintptr_t* where = p-1;
				GCHeap::HeapBlock* block = heap->AddrToBlock(where);
				//GCAssertMsg(block->inUse(), "Not sure how we got here if the block is not in use?");
				GCAssertMsg(block->committed, "Means we are probing uncommitted memory. not good");
				int* ptr;			  

				switch(bits)
				{
				case kNonGC:
					{
						if (block->size == 1)
						{
							// fixed sized entries find out the size of the block
							union { 
								char* fixed_c;
								FixedAlloc::FixedBlock* fixed;
							};
							fixed_c = block->baseAddr;
							int fixedsize = fixed->size;

							// now compute which element we are 
							uintptr_t startAt = (uintptr_t) &(fixed->items[0]);
							uintptr_t item = ((uintptr_t)where-startAt) / fixedsize;

							ptr = (int*) ( startAt + (item*fixedsize) );
						}
						else
						{
							// fixed large allocs ; start is after the block 
							union { 
								char* ptr_c;
								int* ptr_i;
							};
							ptr_c = block->baseAddr;
							ptr = ptr_i;
						}
					}
					break;

				default:
					ptr = ((int*)FindBeginningGuarded(where)) - 2;
					break;
				}

				int  taggedSize = *ptr;
				int* real = (ptr+2);

				GCDebugIndent(currentDepth*3);
				GCDebugMsg(false, "Location: 0x%08x  Object: 0x%08x (size %d)\n", where, real, taggedSize);
				GCDebugIndent(currentDepth*3);
				PrintAllocStackTrace(real);

				if (recurseDepth > 0)
					WhosPointingAtMe(real, recurseDepth-1, currentDepth+1);
			}
		}
	}

	/**
	 * This routine searches through all of GC memory looking for references to 'me' 
	 * It ignores already claimed memory thus locating active references only.
	 * recurseDepth can be set to a +ve value in order to follow the chain of 
	 * pointers arbitrarily deep.  Watch out when setting it since you may see
	 * an exponential blow-up (usu. 1 or 2 is enough).	'currentDepth' is for
	 * indenting purposes and should be left alone.
	 */
	void GC::WhosPointingAtMe(void* me, int recurseDepth, int currentDepth)
	{
		uintptr_t val = (uintptr_t)me;
		uintptr_t m = memStart;

		GCDebugIndent(currentDepth*3);
		GCDebugMsg(false, "[%d] Probing for pointers to : 0x%08x\n", currentDepth, me);
		while(m < memEnd)
		{
			// divide by 4K to get index
			int bits = GetPageMapValue(m);
			if(bits == kNonGC) 
			{
				ProbeForMatch((const void*)m, GCHeap::kBlockSize, val, recurseDepth, currentDepth);
				m += GCHeap::kBlockSize;
			} 
			else if(bits == kGCLargeAllocPageFirst) 
			{
				GCLargeAlloc::LargeBlock *lb = (GCLargeAlloc::LargeBlock*)m;
				const void *item = GetUserPointer((const void*)(lb+1));
				bool marked = GCLargeAlloc::GetMark(item);
				if (marked)
				{
					if(GCLargeAlloc::ContainsPointers(GetRealPointer(item))) 
					{
						ProbeForMatch(item, Size(item), val, recurseDepth, currentDepth);
					}
				}
				m += lb->GetNumBlocks() * GCHeap::kBlockSize;
			} 
			else if(bits == kGCAllocPage) 
			{
				// go through all marked objects
				GCAlloc::GCBlock *b = (GCAlloc::GCBlock *) m;
                for (int i=0; i < b->alloc->m_itemsPerBlock; i++) 
				{
                    int marked = GCAlloc::GetBit(b, i, GCAlloc::kMark);
                    if (marked) 
					{
                        void* item = (char*)b->items + b->alloc->m_itemSize*i;
                        if(GCAlloc::ContainsPointers(item)) 
						{
							ProbeForMatch(GetUserPointer(item), b->alloc->m_itemSize - DebugSize(), val, recurseDepth, currentDepth);
						}
					}
				}				
				m += GCHeap::kBlockSize;
			}
			else
			{
				GCAssertMsg(false, "Oh seems we missed a case...Tom any ideas here?");
			
			}
		}
	}
#undef ALLOCA_AND_FILL_WITH_SPACES
#endif


	void GC::StartIncrementalMark()
	{
		policy.signal(GCPolicyManager::START_StartIncrementalMark);		// garbage collection starts
		
		GCAssert(!marking);
		GCAssert(!collecting);

		lastStartMarkIncrementCount = markIncrements();

		// set the stack cleaning trigger
		stackCleaned = false;

		marking = true;

		GCAssert(m_incrementalWork.Count() == 0);
		GCAssert(m_barrierWork.Count() == 0);
	
		SweepNeedsSweeping();

		// at this point every object should have no marks or be marked kFreelist
#ifdef _DEBUG		
		for(int i=0; i < kNumSizeClasses; i++) {
			containsPointersRCAllocs[i]->CheckMarks();
			containsPointersAllocs[i]->CheckMarks();
			noPointersAllocs[i]->CheckMarks();
		}
#endif

#ifdef MMGC_HEAP_GRAPH
		markerGraph.clear();
#endif

		MarkAllRoots();
		
		policy.signal(GCPolicyManager::END_StartIncrementalMark);
		
		// FIXME (policy): arguably a bug to do this here if StartIncrementalMark has exhausted its quantum
		// doing eager sweeping.

		IncrementalMark();
	}

	// The mark stack overflow logic depends on this calling MarkItem directly 
	// for each of the roots.

	void GC::MarkAllRoots(bool deep)
	{
		// Need to do this while holding the root lock so we don't end 
		// up trying to scan a deleted item later, another reason to keep
		// the root set small.
		
		MMGC_LOCK(m_rootListLock);
		GCRoot *r = m_roots;
		while(r) {
			GCWorkItem item = r->GetWorkItem();
			if(item.ptr) {
				MarkItem(item);
				if (deep)
					Mark();
			}
			r = r->next;
		}
	}

	// Recover from a mark stack overflow.
	//
	// Mark stack overflow occurs when an item cannot be pushed onto the mark stack because
	// the top mark stack segment is full and a new segment can't be allocated.  In
	// practice, any call to GC::PushWorkItem (or its callers, such as GC::Mark, GC::MarkItem,
	// GC::MarkAllRoots, GC::MarkQueueAndStack, and not least the write barrier GC::TrapWrite)
	// can cause a mark stack overflow.
	//
	// Since garbage collection cannot be allowed to abort the program as a result of
	// the allocation failure, but must run to completion, overflow is handled specially.
	// The mark stack Push method returns an error code, which is detected in GC::PushWorkItem,
	// which in turn calls GC::SignalMarkStackOverflow to handle the overflow.  Overflow
	// is handled by discarding some elements and setting the global m_markStackOverflow flag.
	//
	// Any code that needs to drive marking to completion - FinishIncrementalMark and Sweep
	// do, as they depend on the heap having been marked before running finalizers and
	// clearing out empty blocks - must test m_markStackOverflow: if it is set then it must
	// be cleared and the present method, GC::HandleMarkStackOverflow, is called to mop up.
	// The caller must perform this test repeatedly until the flag is no longer set.
	//
	// The job of HandleMarkStackOverflow is to find marked heap objects that point to
	// unmarked objects, and to mark those objects.  Effectively it uses the heap as a
	// queue of candidate objects, thus minimizing the use of the mark stack.  Since marking
	// uses the mark stack the marking performed by HandleMarkStackOverflow may also
	// overflow the mark stack, but once a marked object has been visited by 
	// HandleMarkStackOverflow it will not point to any unmarked objects.  There are object
	// graphs containing pointers from objects visited later to objects skipped earlier
	// that may require recovery to be run multiple times, if marking overflows the mark
	// stack, but each recovery pass will mark all objects where the reference is from
	// an earlier object to a later object, and all non-overflowing subgraphs of those
	// objects in either direction.
	//
	// Performance might be an issue as the restart may happen several times and the
	// scanning performed by HandleMarkStackOverflow covers the entire heap every time.  It could
	// be more efficient to interleave restarting and marking (eg, never fill the mark stack
	// during restarting, but mark after filling it partly, and remember the place in the heap
	// where scanning left off, and then iterate), but we should cross that bridge if and when
	// restarting turns out to be a problem in practice.  (If it does, caching more mark stack
	// segments may be a better first fix, too.)

	void GC::HandleMarkStackOverflow()
	{
		// Crucial for completion that we do not push marked items.  MarkItem handles this
		// for us: it pushes referenced objects that are not marked.  (MarkAllRoots calls
		// MarkItem on each root.)

		MarkAllRoots(true);

		// For all iterator types, GetNextMarkedObject returns true if 'item' has been
		// updated to reference a marked, non-free object to mark, false if the allocator
		// instance has been exhausted.

		void* ptr;
		uint32_t size;
		
		for(int i=0; i < kNumSizeClasses; i++) {
			GCAllocIterator iter1(containsPointersRCAllocs[i]);
			while (iter1.GetNextMarkedObject(ptr, size)) {
				GCWorkItem item(ptr, size, true);
				MarkItem(item);
				Mark();
			}
			GCAllocIterator iter2(containsPointersAllocs[i]);
			while (iter2.GetNextMarkedObject(ptr, size)) {
				GCWorkItem item(ptr, size, true);
				MarkItem(item);
				Mark();
			}
		}

		GCLargeAllocIterator iter3(largeAlloc);
		while (iter3.GetNextMarkedObject(ptr, size)) {
			GCWorkItem item(ptr, size, true);
			MarkItem(item);
			Mark();
		}
	}

	// Signal that attempting to push 'item' onto 'stack' overflowed 'stack'.
	//
	// Either 'item' must be pushed onto the stack, replacing some other item there,
	// or any state information in the item that indicates that it is stacked must
	// be cleared, since it will not be pushed onto the stack.  What to do?
	//
	// The literature (Jones & Lins) does not provide a lot of guidance.  Intuitively it
	// seems that we want to maximize the number of items that remain on the stack so
	// that the marker will finish processing the maximal number of objects before we
	// enter the stack overflow recovery code (in HandleMarkStackOverflow, above).  Ergo
	// we drop 'item' on the floor.

	void GC::SignalMarkStackOverflow(GCWorkItem& item)
	{
		GCAssert(item.ptr != NULL);
 		if (item.IsGCItem())
			ClearQueued(item.ptr);
		m_markStackOverflow = true;
 	}

#if 0
	// TODO: SSE2 version
	void GC::MarkItem_MMX(const void *ptr, size_t size)
	{
		 uintptr *p = (uintptr*) ptr;
		// deleted things are removed from the queue by setting them to null
		if(!p)
			return;

		bytesMarked += size;
		marks++;

		uintptr *end = p + (size / sizeof(void*));
		uintptr thisPage = (uintptr)p & ~0xfff;

		// since MarkItem recurses we have to do this before entering the loop
		if(IsPointerToGCPage(ptr)) 
		{
			int b = SetMark(ptr);
#if defined(_DEBUG) && !defined(AVMPLUS_SAMPLER) // sampler does some marking which triggers this
			// def ref validation does a Trace which can 
			// cause things on the work queue to be already marked
			// in incremental GC
			if(!validateDefRef) {
				GCAssert(!b);
			}
#endif
		}

		_asm {
			// load memStart and End into mm0
			movq mm0,memStart			
		}

		while(p < end) 
		{		
			_asm {
				mov       ebx, [p]
				mov       ecx, [count]
				sar       ecx, 1
				mov       eax, dword ptr [lowerBound]
				dec       eax
				movd      mm1, eax
				movd      mm2, dword ptr [upperBound]
				punpckldq mm1, mm1
				punpckldq mm2, mm2
				mov		  eax, 3
				movd	  mm5, eax
				punpckldq mm5, mm5				
			  MarkLoop:
				movq      mm0, qword ptr [ebx]
				movq      mm3, mm0
				pcmpgtd   mm3, mm1
				movq      mm4, mm2
				pcmpgtd   mm4, mm0
				pand      mm3, mm4
				packssdw  mm3, mm3
				movd      eax, mm3
				or        eax, eax
				jz        Advance

				// normalize and divide by 4K to get index
				psubd	  mm0, mm1
				psrld     mm0, 12

				// shift amount to determine position in the byte (times 2 b/c 2 bits per page)
				movq      mm6, mm0
				pand      mm6, mm5
				pslld     mm6, 1
				packssdw  mm6, mm6

				// index = index >> 2 for pageMap index
				psrld     mm0, 2
				packssdw  mm0, mm0

				// check 
				push      ecx

				

				push	  [workAddr]
				movd	  edx, mm6
				push      edx // packShiftAmount
				movd	  edx, mm0
				push	  edx // packIndex4
				push	  eax // packTest
				push	  dword ptr [ebx+4] // val2
				push	  dword ptr [ebx] // val1
				mov		  ecx, [this]
				call	  ConservativeMarkMMXHelper
					
				pop		  ecx

			Advance:
				add       ebx, 8
				loop      MarkLoop
				mov       dword ptr [p], ebx				
			}
		}
	}

#endif

#ifdef MMGC_INTERIOR_PTRS
	inline bool IsLargeAllocPage(int bits) {
		return (bits == GC::kGCLargeAllocPageFirst
				|| bits == GC::kGCLargeAllocPageRest);
	}
#else
	inline bool IsLargeAllocPage(int bits) {
		return bits == GC::kGCLargeAllocPageFirst;
	}
#endif
	
	// This will mark the item whether the item was previously marked or not.
	// The mark stack overflow logic depends on that.

	void GC::MarkItem(GCWorkItem &wi)
	{
		size_t size = wi.GetSize();
		uintptr_t *p = (uintptr_t*) wi.ptr;

		// Control mark stack growth:
		// Here we consider whether to split the object into multiple pieces.
		// A cutoff of 400 is somewhat arbitrary; it can't be too small
		// because then we'll split too many objects, and it can't be too large
		// because then the mark stack growth won't be throttled properly.
		//
		// See bugzilla #495049 for a discussion of this problem.
		//
		// If the cutoff is exceeded split the work item into two chunks:
		// a small head (which we mark now) and a large tail (which we push
		// onto the stack).  The tail is a non-gcobject regardless of whether
		// the head is a gcobject.  The head must be marked first because this
		// ensures that the mark on the object is set immediately; that is
		// necessary for write barrier correctness.
		//
		// If a mark stack overflow occurs the large tail may be popped
		// and discarded.  This is not a problem: the object as a whole
		// is marked, but points to unmarked storage, and the latter
		// objects will be picked up as per normal.  Discarding the
		// tail is entirely equivalent to discarding the work items that
		// would result from scanning the tail.
		const size_t markstackCutoff = 400;
		if (size > markstackCutoff)
		{
			PushWorkItem(GCWorkItem(p + markstackCutoff / sizeof(uintptr_t), uint32_t(size - markstackCutoff), false));
			size = markstackCutoff;
		}

		policy.signalMarkWork(size);

		uintptr_t *end = p + (size / sizeof(void*));
		uintptr_t thisPage = (uintptr_t)p & ~0xfff;
#ifdef MMGC_POINTINESS_PROFILING
		uint32_t could_be_pointer = 0;
		uint32_t actually_is_pointer = 0;
#endif

		// set the mark bits on this guy
		if(wi.IsGCItem())
		{
			int b = SetMark(wi.ptr);
			(void)b;
#ifdef _DEBUG
			// def ref validation does a Trace which can 
			// cause things on the work queue to be already marked
			// in incremental GC
			if(!validateDefRef) {
				//GCAssert(!b);
			}
#endif			
		}

		uintptr_t _memStart = memStart;
		uintptr_t _memEnd = memEnd;
		
		while(p < end) 
		{
			uintptr_t val = *p++;  
			
			if(val < _memStart || val >= _memEnd)
				continue;

#ifdef MMGC_POINTINESS_PROFILING
			could_be_pointer++;
#endif

			// normalize and divide by 4K to get index
			int bits = GetPageMapValue(val); 
						
			if (bits == kGCAllocPage)
			{
				const void *item;
				GCAlloc::GCBlock *block = (GCAlloc::GCBlock*) (val & ~0xFFF);

#ifdef MMGC_INTERIOR_PTRS
				item = (void*) val;
#else
				// back up to real beginning
				item = GetRealPointer((const void*) (val & ~7));
#endif

				// guard against bogus pointers to the block header
				if(item < block->items)
					continue;

				int itemNum = GCAlloc::GetIndex(block, item);
#ifdef MMGC_INTERIOR_PTRS
				// adjust |item| to the beginning of the allocation
				item = block->items + itemNum * block->size;
#else
				// if |item| doesn't point to the beginning of an allocation,
				// it's not considered a pointer.
				if (block->items + itemNum * block->size != item)
				{
#ifdef MMGC_64BIT
// Doubly-inherited classes have two vtables so are offset 8 more bytes than normal. 
// Handle that here (shows up with PlayerScriptBufferImpl object in the Flash player)
					if ((block->items + itemNum * block->size + sizeof(void *)) == item)
						item = block->items + itemNum * block->size;
					else
#endif // MMGC_64BIT
						continue;
				}
#endif

#ifdef MMGC_POINTINESS_PROFILING
				actually_is_pointer++;
#endif


				// inline IsWhite/SetBit
				// FIXME: see if using 32 bit values is faster
				uint32_t *pbits = &block->GetBits()[itemNum>>3];
				int shift = (itemNum&0x7)<<2;
				int bits2 = *pbits;
				//if(GCAlloc::IsWhite(block, itemNum)) 
				if((bits2 & ((GCAlloc::kMark|GCAlloc::kQueued)<<shift)) == 0)
				{
					uint32_t itemSize = block->size - (uint32_t)DebugSize();
					if(block->alloc->ContainsPointers())
					{
						const void *realItem = GetUserPointer(item);
						GCWorkItem newItem(realItem, itemSize, true);
						if(((uintptr_t)realItem & ~0xfff) != thisPage || mark_item_recursion_control == 0)
						{							
							*pbits = bits2 | (GCAlloc::kQueued << shift);
							PushWorkItem(newItem);
						}
						else
						{
							mark_item_recursion_control--;
							MarkItem(newItem);
							mark_item_recursion_control++;
						}
					}
					else
					{
						//GCAlloc::SetBit(block, itemNum, GCAlloc::kMark);
						*pbits = bits2 | (GCAlloc::kMark << shift);
						policy.signalMarkWork(itemSize);
					}
#ifdef MMGC_HEAP_GRAPH
					markerGraph.edge(p-1, GetUserPointer(item));
#endif				
				}
			}
			else if (IsLargeAllocPage(bits))
			{
				//largeAlloc->ConservativeMark(work, (void*) (val&~7), workitem.ptr);
				const void* item;

#ifdef MMGC_INTERIOR_PTRS
				if (bits == kGCLargeAllocPageFirst)
				{
					// guard against bogus pointers to the block header
					if ((val & 0xffff) < sizeof(GCLargeAlloc::LargeBlock))
						continue;

					item = (void *) ((val & ~0xfff) |
									 sizeof(GCLargeAlloc::LargeBlock));
				}
				else
				{
					item = GetRealPointer(FindBeginning((void *) val));
				}
#else
				// back up to real beginning
				item = GetRealPointer((const void*) (val & ~7));

				// If |item| doesn't point to the start of the page, it's not
				// really a pointer.
				if(((uintptr_t) item & 0xfff) != sizeof(GCLargeAlloc::LargeBlock))
					continue;
#endif

#ifdef MMGC_POINTINESS_PROFILING
				actually_is_pointer++;
#endif

				GCLargeAlloc::LargeBlock *b = GCLargeAlloc::GetLargeBlock(item);
				if((b->flags & (GCLargeAlloc::kQueuedFlag|GCLargeAlloc::kMarkFlag)) == 0) 
				{
					uint32_t itemSize = b->size - (uint32_t)DebugSize();
					if((b->flags & GCLargeAlloc::kContainsPointers) != 0) 
					{
						b->flags |= GCLargeAlloc::kQueuedFlag;
						PushWorkItem(GCWorkItem(GetUserPointer(item), itemSize, true));
					} 
					else
					{
						// doesn't need marking go right to black
						b->flags |= GCLargeAlloc::kMarkFlag;
						policy.signalMarkWork(itemSize);
					}
#ifdef MMGC_HEAP_GRAPH
					markerGraph.edge(p-1, GetUserPointer(item));
#endif				
				}
			}
		}
#ifdef MMGC_POINTINESS_PROFILING
		policy.signalDemographics(size/sizeof(void*), could_be_pointer, actually_is_pointer);
#endif
	}

	void GC::IncrementalMark()
	{
		uint32_t time = incrementalValidation ? 1 : policy.incrementalMarkMilliseconds();
#ifdef _DEBUG
		time = 1;
#endif

		SAMPLE_FRAME("[mark]", core());

		// Don't force collections to finish if the mark stack is empty; 
		// let the allocation budget be used up.

		if(m_incrementalWork.Count() == 0) {
			CheckBarrierWork();
			if (m_incrementalWork.Count() == 0) {
				// Policy triggers off these signals, so we still need to send them.
				policy.signal(GCPolicyManager::START_IncrementalMark);
				policy.signal(GCPolicyManager::END_IncrementalMark);
				return;
			}
		}
		
		policy.signal(GCPolicyManager::START_IncrementalMark);
		
		// FIXME: tune this so that getPerformanceCounter() overhead is noise
		//
		// *** NOTE ON THREAD SAFETY ***
		//
		// If anyone feels like writing code that updates checkTimeIncrements (it
		// used to be 'static' instead of 'const'), beware that using a static var
		// here requires a lock.  It may also be wrong to have one shared global for
		// the value, and in any case it may belong in the policy manager.
		const unsigned int checkTimeIncrements = 100;
		uint64_t start = VMPI_getPerformanceCounter();

		uint64_t numObjects=policy.objectsMarked();
		uint64_t objSize=policy.bytesMarked();

		uint64_t ticks = start + time * VMPI_getPerformanceFrequency() / 1000;
		do {
			unsigned int count = m_incrementalWork.Count();
			if (count == 0) {
				CheckBarrierWork();
				count = m_incrementalWork.Count();
				if (count == 0)
					break;
			}
			if (count > checkTimeIncrements) {
				count = checkTimeIncrements;
			}
			for(unsigned int i=0; i<count; i++) 
			{
				GCWorkItem item = m_incrementalWork.Pop();
 				MarkItem(item);
			}
			SAMPLE_CHECK();
		} while(VMPI_getPerformanceCounter() < ticks);

		policy.signal(GCPolicyManager::END_IncrementalMark);

		if(heap->Config().gcstats) {
			numObjects = policy.objectsMarked() - numObjects;
			objSize = policy.bytesMarked() - objSize;
			double millis = duration(start);
			size_t kb = size_t(objSize)>>10;
			gclog("[mem] mark(%d) %d objects (%d kb %d mb/s) in %.2f millis (%.4f s)\n", 
				  markIncrements() - lastStartMarkIncrementCount, int(numObjects), kb, 
				  uint32_t(double(kb)/millis), millis, duration(t0)/1000);
		}
	}

	void GC::FinishIncrementalMark(bool scanStack)
	{
		// Don't finish an incremental mark (i.e., sweep) if we
		// are in the midst of a ZCT reap.
		if (Reaping())
		{
			return;
		}
		
		// Force repeated restarts and marking until we're done.  For discussion
		// of completion, see the comments above HandleMarkStackOverflow.

		while (m_markStackOverflow) {
			m_markStackOverflow = false;
			HandleMarkStackOverflow();		// may set
			FlushBarrierWork();				//    m_markStackOverflow
			Mark();							//       to true again
		}

		// finished in Sweep
		sweepStart = VMPI_getPerformanceCounter();
		
		// mark roots again, could have changed (alternative is to put WB's on the roots
		// which we may need to do if we find FinishIncrementalMark taking too long)
		
		policy.signal(GCPolicyManager::START_FinalRootAndStackScan);
		
		GCAssert(!m_markStackOverflow);
		
		FlushBarrierWork();
		MarkAllRoots();
		MarkQueueAndStack(scanStack);
		
		// Force repeated restarts and marking until we're done.  For discussion
		// of completion, see the comments above HandleMarkStackOverflow.  Note
		// that we must use MarkQueueAndStack rather than plain Mark because there
		// is no guarantee that the stack was actually pushed onto the mark stack.
		// If we iterate several times there may be a performance penalty as a
		// consequence of that, but it's not likely that that will in fact happen,
		// and it's not obvious how to fix it.
		
		while (m_markStackOverflow) {
			m_markStackOverflow = false;
			HandleMarkStackOverflow();							// may set
			FlushBarrierWork();									//    m_markStackOverflow
			MarkQueueAndStack(scanStack);						//       to true again
		}
		m_incrementalWork.Clear();				// Frees any cached resources
		m_barrierWork.Clear();
		zct.Prune();							// Frees unused memory
		
		policy.signal(GCPolicyManager::END_FinalRootAndStackScan);
		
#ifdef _DEBUG
		// need to traverse all marked objects and make sure they don't contain
		// pointers to unmarked objects
		FindMissingWriteBarriers();
#endif

		policy.signal(GCPolicyManager::START_FinalizeAndSweep);
		GCAssert(!collecting);

		// Sweep is responsible for setting and clearing GC::collecting.
		// It also clears GC::marking.
		
		GCAssert(m_incrementalWork.Count() == 0);
		GCAssert(m_barrierWork.Count() == 0);
		Sweep();
		GCAssert(m_incrementalWork.Count() == 0);
		GCAssert(m_barrierWork.Count() == 0);

		policy.signal(GCPolicyManager::END_FinalizeAndSweep);	// garbage collection is finished
#ifdef MMGC_MEMORY_PROFILER
		if(heap->Config().autoGCStats)
			DumpPauseInfo();
#endif
		
	}

#ifdef _DEBUG
	bool GC::IsWhite(const void *item)
	{
		// back up to real beginning
		item = GetRealPointer((const void*) item);

		int bits = GetPageMapValueGuarded((uintptr_t)item);	
		switch(bits) {
		case kGCAllocPage:
			return GCAlloc::IsWhite(item);
		case kGCLargeAllocPageFirst:
			return GCLargeAlloc::IsWhite(item);
		}
		return false;
	}
#endif // _DEBUG

	// Here the purpose is to shift some work from the barrier mark stack to the regular
	// mark stack /provided/ the barrier mark stack seems very full.  The regular mark stack
	// is normally empty.
	//
	// To avoid copying data, we will only move entire (full) segments, because they can
	// be moved by changing some pointers and counters.  We will never move a non-full
	// segment.

	void GC::CheckBarrierWork()
	{
		if (m_barrierWork.EntirelyFullSegments() < 9)	// 9 is pretty arbitrary
			return;
		m_incrementalWork.TransferOneFullSegmentFrom(m_barrierWork);
	}
	
	// Here the purpose is to shift all the work from the barrier mark stack to the regular
	// mark stack, unconditionally.  This may mean copying mark work from one stack to
	// the other (for work that's in a non-full segment), but full segments can just be
	// moved by changing some pointers and counters.
	//
	// Note it's possible for this to cause a mark stack overflow, and the caller must
	// deal with that.

	void GC::FlushBarrierWork()
	{
		for ( uint32_t numfull = m_barrierWork.EntirelyFullSegments() ; numfull > 0 ; --numfull )
			if (!m_incrementalWork.TransferOneFullSegmentFrom(m_barrierWork))
				break;
		while (m_barrierWork.Count() > 0) {
			GCWorkItem item = m_barrierWork.Pop();
			PushWorkItem(item);
		}
	}
	
	void GC::WriteBarrierTrap(const void *container)
	{
		if (marking)
			InlineWriteBarrierTrap(container);
	}
	
	void GC::privateWriteBarrier(const void *container, const void *address, const void *value)
	{
		privateInlineWriteBarrier(container, address, value);
	}
	
	void GC::privateWriteBarrierRC(const void *container, const void *address, const void *value)
	{
		privateInlineWriteBarrierRC(container, address, value);
	}

	/* static */ void GC::WriteBarrierRC(const void *address, const void *value)
	{
		GC* gc = GC::GetGC(address);
		gc->privateInlineWriteBarrierRC(address, value);
	}
	
	/* static */ void GC::WriteBarrierRC_ctor(const void *address, const void *value)
	{
		GC* gc = GC::GetGC(address);
		if (gc->marking)
			gc->InlineWriteBarrierTrap(gc->FindBeginningFast(address));
		gc->WriteBarrierWriteRC_ctor(address, value);
	}
	
	/* static */ void GC::WriteBarrierRC_dtor(const void *address)
	{
		GC* gc = GC::GetGC(address);
		gc->WriteBarrierWriteRC_dtor(address);
	}
	
	/* static */ void GC::WriteBarrier(const void *address, const void *value)
	{
		GC* gc = GC::GetGC(address);
		gc->privateInlineWriteBarrier(address, value);
	}

	// It might appear that this can be optimized easily, but not so - there's a
	// lot of logic hiding here, and little to gain from hand-inlining.

	void GC::privateConservativeWriteBarrierNoSubstitute(const void *address)
	{
		GCAssert(marking);
		if(IsPointerToGCPage(address))
		   InlineWriteBarrierTrap(FindBeginningFast(address));
	}
	
	void GC::WriteBarrierNoSubstitute(const void *container, const void *value)
	{
		(void)value;  // Can't get rid of this parameter now; part of an existing API
		
		GCAssert(container != NULL);
		GCAssert(IsPointerToGCPage(container));
		GCAssert(FindBeginningGuarded(container) == container);
		if (marking)
			InlineWriteBarrierTrap(container);
	}

	// Add 'container' to the remembered set.
	//
	// IncrementalMark may move a segment off the remembered set;
	// FinishIncrementalMark will take care of what remains.
	//
	// Observe that if adding the item to the remembered set (a secondary mark stack)
	// fails, then the item is just pushed onto the regular mark stack; if that too
	// fails then normal stack overflow handling takes over.  That is what we want,
	// as it guarantees that the item will be traced again.
	
	void GC::WriteBarrierHit(const void* container)
	{
		GCAssert(IsPointerToGCObject(GetRealPointer(container)));
		if (collecting)
		{
			// It's the job of the allocators to make sure the rhs is marked if
			// it is allocated on a page that's not yet swept.  In particular,
			// the barrier is not needed to make sure that that object is kept
			// alive.
			//
			// Ergo all we need to do here is revert the lhs to marked and return.
			SetMark(container);
			return;
		}
		GCWorkItem item(container, (uint32_t)Size(container), true);
		// Note, pushing directly here works right now because PushWorkItem never
		// performs any processing (breaking up a large object into shorter
		// segments, for example).  If that changes, we must probably introduce
		// PushBarrierItem to do the same thing for m_barrierWork.
		if (!m_barrierWork.Push(item))
			PushWorkItem(item);
	}
	
	bool GC::ContainsPointers(const void *item)
	{
		item = GetRealPointer(item);
		if (GCLargeAlloc::IsLargeBlock(item)) {
			return GCLargeAlloc::ContainsPointers(item);
		} else {
			return GCAlloc::ContainsPointers(item);
		}
	}

	uint32_t *GC::GetBits(int numBytes, int sizeClass)
	{
		uint32_t *bits;

		GCAssert(numBytes % 4 == 0);

		#ifdef MMGC_64BIT // we use first 8-byte slot for the free list
		if (numBytes == 4)
			numBytes = 8;
		#endif

		// hit freelists first
		if(m_bitsFreelists[sizeClass]) {
			bits = m_bitsFreelists[sizeClass];
			m_bitsFreelists[sizeClass] = *(uint32_t**)bits;
			VMPI_memset(bits, 0, sizeof(uint32_t*));
			return bits;
		}

		if(!m_bitsNext)
			m_bitsNext = (uint32_t*)heapAlloc(1);

		int leftOver = GCHeap::kBlockSize - ((uintptr_t)m_bitsNext & 0xfff);
		if(leftOver >= numBytes) {
			bits = m_bitsNext;
			if(leftOver == numBytes) 
				m_bitsNext = 0;
			else 
				m_bitsNext += numBytes/sizeof(uint32_t);
		} else {
			if(leftOver>=int(sizeof(void*))) {
				// put waste in freelist
				for(int i=0, n=kNumSizeClasses; i<n; i++) {
					GCAlloc *a = noPointersAllocs[i];
					if(!a->m_bitsInPage && a->m_numBitmapBytes <= leftOver) {
						FreeBits(m_bitsNext, a->m_sizeClassIndex);
						break;
					}
				}
			}
			m_bitsNext = 0;
			// recurse rather than duplicating code
			return GetBits(numBytes, sizeClass);
		}
		return bits;
	}

	void GC::AddRoot(GCRoot *root)
	{
		MMGC_LOCK(m_rootListLock);
		root->prev = NULL;
		root->next = m_roots;
		if(m_roots)
			m_roots->prev = root;
		m_roots = root;
	}

	void GC::RemoveRoot(GCRoot *root)
	{	
		MMGC_LOCK(m_rootListLock);
		if( m_roots == root )
			m_roots = root->next;
		else
			root->prev->next = root->next;

		if(root->next)
			root->next->prev = root->prev;
	}
	
	void GC::AddCallback(GCCallback *cb)
	{
		cb->prevCB = NULL;
		cb->nextCB = m_callbacks;
		if(m_callbacks)
			m_callbacks->prevCB = cb;
		m_callbacks = cb;
	}

	void GC::RemoveCallback(GCCallback *cb)
	{
		if( m_callbacks == cb )
			m_callbacks = cb->nextCB;
		else
			cb->prevCB->nextCB = cb->nextCB;

		if(cb->nextCB)
			cb->nextCB->prevCB = cb->prevCB;
	}

	GCWeakRef* GC::GetWeakRef(const void *item) 
	{
		GC *gc = GetGC(item);
		GCWeakRef *ref = (GCWeakRef*) gc->weakRefs.get(item);

		if(ref == NULL) {
			ref = new (gc) GCWeakRef(item);
			gc->weakRefs.put(item, ref);
			item = GetRealPointer(item);
			if (GCLargeAlloc::IsLargeBlock(item)) {
				GCLargeAlloc::SetHasWeakRef(item, true);
			} else {
				GCAlloc::SetHasWeakRef(item, true);
			}
		} else {
			GCAssert(ref->get() == item);
		}
		return ref;
	}

	void GC::ClearWeakRef(const void *item)
	{
		GCWeakRef *ref = (GCWeakRef*) weakRefs.remove(item);
		GCAssert(weakRefs.get(item) == NULL);
		GCAssert(ref != NULL || heap->GetStatus() == kMemAbort);
		if(ref) {
			GCAssert(ref->get() == item || ref->get() == NULL);
			ref->m_obj = NULL;
			item = GetRealPointer(item);
			if (GCLargeAlloc::IsLargeBlock(item)) {
				GCLargeAlloc::SetHasWeakRef(item, false);
			} else {
				GCAlloc::SetHasWeakRef(item, false);
			}
		}
	}

#ifdef _DEBUG	
	void GC::WhitePointerScan(const void *mem, size_t size)
	{		
		uintptr_t *p = (uintptr_t *) mem;
		// the minus 8 skips the deadbeef and back pointer 
		uintptr_t *end = p + ((size) / sizeof(void*));

		while(p < end)
		{
			uintptr_t val = *p;		
			if(val == 0xdeadbeef)
				break;
			if(IsWhite((const void*) (val&~7)) && 
			   *(((int32_t*)(val&~7))+1) != (int32_t)0xcacacaca && // Free'd
			   *(((int32_t*)(val&~7))+1) != (int32_t)0xbabababa) // Swept
			{
				GCDebugMsg(false, "Object 0x%x allocated here:\n", mem);
				PrintAllocStackTrace(mem);
				GCDebugMsg(false, "Didn't mark pointer at 0x%x, object 0x%x allocated here:\n", p, val);
				PrintAllocStackTrace((const void*)(val&~7));
				GCAssert(false);
			}
			p++;
		}
	}

	void GC::FindMissingWriteBarriers()
	{
		if(!incrementalValidation)
			return;

		uintptr_t m = memStart;
		while(m < memEnd)
		{
			// divide by 4K to get index
			int bits = GetPageMapValue(m);
			switch(bits)
			{
			case kNonGC:
				m += GCHeap::kBlockSize;
				break;
			case kGCLargeAllocPageFirst:
				{
					GCLargeAlloc::LargeBlock *lb = (GCLargeAlloc::LargeBlock*)m;
					const void *item = GetUserPointer((const void*)(lb+1));
					if(GCLargeAlloc::GetMark(item) && GCLargeAlloc::ContainsPointers(item)) {
						WhitePointerScan(item, lb->size - DebugSize());
					}
					m += lb->GetNumBlocks() * GCHeap::kBlockSize;
				}
				break;
			case kGCAllocPage:
				{
					// go through all marked objects in this page
					GCAlloc::GCBlock *b = (GCAlloc::GCBlock *) m;
                    for (int i=0; i< b->alloc->m_itemsPerBlock; i++) {
                        // find all marked objects and search them
                        if(!GCAlloc::GetBit(b, i, GCAlloc::kMark))
                            continue;

						if(b->alloc->ContainsPointers()) {
	                        void* item = (char*)b->items + b->alloc->m_itemSize*i;
							WhitePointerScan(GetUserPointer(item), b->alloc->m_itemSize - DebugSize());
						}
					}
					m += GCHeap::kBlockSize;
				}
				break;
			default:
				GCAssert(false);
				break;
			}
		}
	}
#endif //_DEBUG

	void *GC::heapAlloc(size_t siz, int flags)
	{
		void *ptr = heap->Alloc((int)siz, flags);
		if(ptr)
			policy.signalBlockAllocation(siz);
		return ptr;
	}
	
	void GC::heapFree(void *ptr, size_t siz, bool profile)
	{
		if(!siz)
			siz = heap->Size(ptr);
		policy.signalBlockDeallocation(siz);
		heap->FreeInternal(ptr, profile);
	}
	
	size_t GC::GetBytesInUse()
	{
		size_t ask;
		size_t allocated;
		GetUsageInfo(ask, allocated);
		(void)ask;
		return allocated;
	}
	
	void GC::GetUsageInfo(size_t& totalAskSize, size_t& totalAllocated)
	{
		totalAskSize = 0;
		totalAllocated = 0;

		size_t ask;
		size_t allocated;

		GCAlloc** allocators[] = {containsPointersRCAllocs, containsPointersAllocs, noPointersAllocs};
		for(int j = 0;j<3;j++)
		{
			GCAlloc** gc_alloc = allocators[j]; 

			for(int i=0; i < kNumSizeClasses; i++) 
			{
				gc_alloc[i]->GetUsageInfo(ask, allocated);
				totalAskSize += ask;
				totalAllocated += allocated;
			}
		}
		
		largeAlloc->GetUsageInfo(ask, allocated);
		totalAskSize += ask;
		totalAllocated += allocated;
	}

 	void GC::allocaInit()
 	{
 		top_segment = NULL;
 		stacktop = NULL;
 #ifdef _DEBUG
 		stackdepth = 0;
 #endif
 		pushAllocaSegment(AVMPLUS_PARAM_ALLOCA_DEFSIZE);
 	}
 	
 	void GC::allocaShutdown()
 	{
 		while (top_segment != NULL)
 			popAllocaSegment();
 		top_segment = NULL;
 		stacktop = NULL;
 	}

	void GC::allocaUnwind()
	{
		allocaShutdown();
		allocaInit();
	}

	void* GC::allocaPush(size_t nbytes, AllocaAutoPtr& x) 
	{
		GCAssert(x.unwindPtr == NULL);
		x.gc = this;
		x.unwindPtr = stacktop;
		nbytes = GCHeap::CheckForAllocSizeOverflow(nbytes, 7) & ~7;
		if ((char*)stacktop + nbytes <= top_segment->limit) {
			stacktop = (char*)stacktop + nbytes;
			return x.unwindPtr;
		}
		return allocaPushSlow(nbytes);
	}
	
 	void GC::allocaPopToSlow(void* top)
 	{
 		GCAssert(top_segment != NULL);
 		GCAssert(!(top >= top_segment->start && top <= top_segment->limit));
 		while (!(top >= top_segment->start && top <= top_segment->limit))
 			popAllocaSegment();
 		GCAssert(top_segment != NULL);
 	}
 	
 	void* GC::allocaPushSlow(size_t nbytes)
 	{
 		size_t alloc_nbytes = nbytes;
 		if (alloc_nbytes < AVMPLUS_PARAM_ALLOCA_DEFSIZE)
 			alloc_nbytes = AVMPLUS_PARAM_ALLOCA_DEFSIZE;
 		pushAllocaSegment(alloc_nbytes);
 		void *p = stacktop;
 		stacktop = (char*)stacktop + nbytes;
 		return p;
 	}
 	
 	void GC::pushAllocaSegment(size_t nbytes)
 	{
 		GCAssert(nbytes % 8 == 0);
 #ifdef _DEBUG
 		stackdepth += nbytes;
 #endif
 		void* memory = AllocRCRoot(nbytes);
 		AllocaStackSegment* seg = mmfx_new(AllocaStackSegment);
 		seg->start = memory;
 		seg->limit = (void*)((char*)memory + nbytes);
 		seg->top = NULL;
 		seg->prev = top_segment;
 		if (top_segment != NULL)
 			top_segment->top = stacktop;
 		top_segment = seg;
 		stacktop = memory;
 	}
 	
 	void GC::popAllocaSegment()
 	{
 #ifdef _DEBUG
 		stackdepth -= (char*)top_segment->limit - (char*)top_segment->start;
 #endif
 		FreeRCRoot(top_segment->start);
 		AllocaStackSegment* seg = top_segment;
 		top_segment = top_segment->prev;
 		if (top_segment != NULL)
 			stacktop = top_segment->top;
 		mmfx_delete(seg);
 	} 

	GCAutoEnter::GCAutoEnter(GC *gc) : gc(NULL) 
	{ 
		if(gc && gc->GetStackEnter() == 0) {
			this->gc = gc;
			gc->heap->SetActiveGC(gc);
			gc->SetStackEnter(this);
		}
	}
	
	GCAutoEnter::~GCAutoEnter() 
	{ 
		if(gc) {
			gc->SetStackEnter(NULL); 
			gc->heap->SetActiveGC(NULL);
			gc = NULL;
		}
	}

	GCAutoEnterPause::GCAutoEnterPause(GC *gc) : gc(gc), enterSave(gc->GetAutoEnter())
	{ 
		GCAssertMsg(gc->GetStackEnter() != 0, "Invalid MMGC_GC_ROOT_THREAD usage, GC not already entered, random crashes will ensue");
		gc->SetStackEnter(NULL, false);
	}
	
	GCAutoEnterPause::~GCAutoEnterPause() 
	{ 
		GCAssertMsg(gc->GetStackEnter() == 0, "Invalid MMGC_GC_ROOT_THREAD usage, GC not exitted properly, random crashes will ensue");
		gc->SetStackEnter(enterSave, false); 
	}

 	void GC::SetStackEnter(GCAutoEnter *enter, bool doCollectionWork) 
	{
		bool edge = false;
		bool releaseThread = false;
 		if(enter == NULL) {
			// don't clear this yet: we want to retain the value
			// until after Collect() is called, in case a presweep()
			// hook needs to make an allocation.
 			// stackEnter = NULL;
			edge = true;
			releaseThread = true;
 		} else if(stackEnter == NULL) {
 			stackEnter = enter;
			edge = true;
			VMPI_lockAcquire(&m_gcLock);
			m_gcThread = VMPI_currentThread();
 		}

		if(edge && doCollectionWork && !destroying) {
			if(policy.queryFullCollectionQueued())
				Collect(false);
			else
				ReapZCT(false);

			if(!stackCleaned)
				CleanStack();			
		}

		if(releaseThread) {
			GCAssert(enter == NULL);
 			stackEnter = NULL;
			// cleared so we remain thread ambivalent
			rememberedStackTop = NULL; 					
			m_gcThread = NULL;
			VMPI_lockRelease(&m_gcLock);
		}
	}
 
 	void GC::memoryStatusChange(MemoryStatus, MemoryStatus to)
 	{
 		// ZCT blockage: what if we get here from zct growth?
 		
 		// Mark/sweep blockage: what about mark stack,
 		// presweep,post-sweep,finalize allocations?
 		
 		// if ZCT or GC can't complete we can't free memory! currently
 		// we do nothing, which means we rely on reserve or other
 		// listeners to free memory or head straight to abort
 
 		if(to == kMemHardLimit || to == kMemSoftLimit) {
 			if(onThread()) {
 				Collect();
 			} else {
				//  If we're not already in the middle of collecting from another thread's GC, then try to...
 				if(m_gcThread == NULL && heap->GetEnterFrame()->GetCollectingGC() == NULL && VMPI_lockTestAndAcquire(&m_gcLock)) {
					
					// got it
					m_gcThread = VMPI_currentThread();
 					
					//  Tell the heap that we are temporarily invoking a "collect" on this GC, and have locked the gcLock.  
					//  This will allow "GCHeap::Abort" to release the lock if Abort is thrown while collecting
					heap->GetEnterFrame()->SetCollectingGC(this);

					//  If collect fails due to allocation here, then we'll end up leaving this thread, need to store off this gclock so that if abort is called
					//  we know whassup
					Collect(false);

					//  Set collecting GC back to NULL now that we are finished
					heap->GetEnterFrame()->SetCollectingGC(NULL);
					
					m_gcThread = NULL;;

 					VMPI_lockRelease(&m_gcLock);
 				}		
 				// else nothing can be done
 			}
		}
	}

#ifdef DEBUG
	void GC::ShouldBeInactive()
	{
		GCAssert(m_gcThread == NULL);
		GCAssert(stackEnter == NULL);
		GCAssert(top_segment != NULL && top_segment->prev == NULL && top_segment->start == stacktop);
		GCAssert(VMPI_lockTestAndAcquire(&m_gcLock) && VMPI_lockRelease(&m_gcLock));
	}
#endif

	void GC::SignalImminentAbort()
	{
		policy.SignalImminentAbort();
		zct.SignalImminentAbort();
		
		if (collecting || marking)
		{
			m_incrementalWork.Clear();
			m_barrierWork.Clear();
			ClearMarks();
			m_markStackOverflow = false;
			collecting = false;
			marking = false;
		}

		// Make it squeaky clean
		SetStackEnter(NULL,false);
		VMPI_lockRelease(&m_gcLock);
		m_gcThread = NULL;		
	}
	
	GC::AutoRCRootSegment::AutoRCRootSegment(GC* gc, void* mem, size_t size)
		: RCRootSegment(gc, mem, size)
	{
		gc->AddRCRootSegment(this);
	}

	GC::AutoRCRootSegment::~AutoRCRootSegment()
	{
		GetGC()->RemoveRCRootSegment(this);
	}

#ifdef MMGC_HEAP_GRAPH

	void GC::addToBlacklist(const void *gcptr)
	{
		blacklist.add(gcptr, gcptr);
	}

	void GC::removeFromBlacklist(const void *gcptr)
	{
		blacklist.remove(gcptr);
	}

	const void *GC::findGCGraphBeginning(const void *addr, bool &wasDeletedGCRoot)
	{
		/* These are all the possibilities
		   1) GC small object
		   2) GC large object
		   3) GCRoot
		   4) OS stack
		*/
		if(!IsPointerToGCPage(addr)) {
			GCRoot *r = m_roots;
			while(r)  {
				if(addr >= r->Get() && addr < r->End())
					return r->Get();
				r = r->next;
			}

			// could be a deleted GCRoot
			GCHeap::HeapBlock *b = heap->AddrToBlock(addr);
			if(b) {
				wasDeletedGCRoot = true;
				if(b->size == 1) {
					return FixedAlloc::FindBeginning(addr);
				} else {
					return GetUserPointer(b->baseAddr);
				}
			}
		}
		return FindBeginningGuarded(addr, true); // will return NULL for OS stack
	}
	
	void GC::dumpBackPointerChain(const void *p, HeapGraph& g)
	{
		GCLog("Dumping back pointer chain for 0x%p\n", p);
		PrintAllocStackTrace(p);
		dumpBackPointerChainHelper(p, g);
		GCLog("End back pointer chain for 0x%p\n", p);
	}

	void GC::dumpBackPointerChainHelper(const void *p, HeapGraph& g)
	{
		GCHashtable *pointers = g.getPointers(p);
		if(pointers) {
			GCHashtable::Iterator iter(pointers);
			const void *addr = iter.nextKey();
			if(addr) {
				bool wasDeletedGCRoot=false;
				const void *container = findGCGraphBeginning(addr, wasDeletedGCRoot);
				const void *displayContainer =  container ? container : addr;
				uint32_t offset = container ? (char*)addr - (char*)container : 0;
				const char *containerDescription = IsPointerToGCPage(container) ? "gc" : (container ? "gcroot" : "stack");
				if(wasDeletedGCRoot)
					containerDescription = "gcroot-deleted";
				GCLog("0x%p(%x)(%s) -> 0x%p\n", displayContainer, offset, containerDescription, p);
				if(container) {
					PrintAllocStackTrace(container);
					dumpBackPointerChainHelper(container, g);
				}
			}
		}
	}

	void HeapGraph::edge(const void *addr, const void *newValue)
	{
		const void *oldValue = GC::Pointer(*(void**)addr);
		newValue = GC::Pointer(newValue);
		GCHashtable *addresses;
		if(oldValue) {
			addresses = (GCHashtable*)backEdges.get(oldValue);
			if(addresses) {
				addresses->remove(addr);
			}
		}
		if(newValue) {
			addresses = (GCHashtable*)backEdges.get(newValue);
			if(!addresses) {
				addresses = mmfx_new(GCHashtable());
				backEdges.put(newValue, addresses);
			}
			addresses->add(addr, addr);
		}
	}
	
	void HeapGraph::clear()
	{
		GCHashtable_VMPI::Iterator iter(&backEdges);
		const void *key;
		while((key = iter.nextKey()) != NULL) {
			GCHashtable *addresses = (GCHashtable*)iter.value();
			mmfx_delete(addresses);
		}
		backEdges.clear();
	}

	GCHashtable *HeapGraph::getPointers(const void *obj)
	{
		return (GCHashtable*)backEdges.get(obj);
	}

	void GC::pruneBlacklist()
	{
		if(blacklist.count() > 0) {
			GCHashtable::Iterator iter(&blacklist);
			const void *p;
			while((p = iter.nextKey()) != NULL) {
				if(!GetMark(p)) {
					removeFromBlacklist(p);
				}		
			}			
		}
	}

	void GC::printBlacklist()
	{
		if(blacklist.count() > 0) {
			GCHashtable::Iterator iter(&blacklist);
			const void *p;
			while((p = iter.nextKey()) != NULL) {
				GCLog("Blacklist item 0x%p %s found in marker graph\n", p, markerGraph.getPointers(p) ? "was" : "wasn't");
				GCLog("Blacklist item 0x%p %s found in mutator graph\n", p, mutatorGraph.getPointers(p) ? "was" : "wasn't");
				dumpBackPointerChain(p, markerGraph);
			}
		}
	}
#endif
}
		
