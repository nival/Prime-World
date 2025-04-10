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

#ifndef __GCZCT__
#define __GCZCT__

namespace MMgc
{
	class GCWorkItem;

	/**
	 * The Zero Count Table used by deferred reference counting.
	 *
	 * Objects whose reference counts are zero are entered into the ZCT; they are
	 * removed if their reference counts transition from zero to one.  This is all
	 * taken care of in RCObject's constructor, destructor, and reference counting
	 * operations.
	 *
	 * When Reap() is called the ZCT is traversed; objects that are not pinned are
	 * destroyed.  Reap runs finalizers, which means more objects may be entered
	 * into the ZCT and visited by Reap.  The process is not currently time-bounded.
	 */
	class ZCT
	{
	public:
		ZCT();
		
		/**
		 * Free the resources associated with the ZCT.
		 *
		 * Not a destructor because the ZCT is a part-object of its associated GC, and 
		 * ZCT destruction must occur at a better defined time than GC destruction allows
		 * for, typically while the GC is still operational.
		 */
		void Destroy();
		
		/**
		 * Associate the ZCT with 'gc' and perform final initialization of the ZCT.
		 *
		 * To be called exactly once after the GC has been properly constructed: SetGC()
		 * uses 'gc' to allocate memory.
		 */
		void SetGC(GC* gc);

		/**
		 * MUST be called by the collector when the collector sets collecting=true
		 */
		void StartCollecting();
		
		/**
		 * MUST be called by the collector when the colletor sets collecting=false
		 */
		void EndCollecting();

		/**
		 * Will be called by the collector when the collector is notified of an imminent abort
		 */
		void SignalImminentAbort();

		/**
		 * Add obj to the ZCT; it must not already be in the ZCT.  This method can fail silently,
		 * leaving the GC to reap the object in case its reference count stays zero.
		 *
		 * If 'initial' is true then this is the call from RCObject's constructor.
		 */
		void Add(RCObject *obj REFCOUNT_PROFILING_ARG(bool initial=false));

		/**
		 * Remove obj from the ZCT; it must already be in the ZCT.
		 *
		 * If 'final' is true then this is the call from RCObject's destructor.
		 */
		void Remove(RCObject *obj REFCOUNT_PROFILING_ARG(bool final=false));

		/**
		 * Reap the ZCT: destroy every non-pinned object in the ZCT.  If scanStack
		 * is true then the program stack is traversed and objects conservatively
		 * referenced from it are pinned.  Auxiliary auto-pinning memory (think of
		 * them as ZCT roots; see AllocaStackSegment in GC.h) is always traversed
		 * and reachable objects pinned.
		 *
		 * Reap always unpins those objects in the ZCT that were found to be pinned,
		 * whether they were pinned by Reap or explicitly from the prereap() callback
		 * or even earlier.  Reap does not unpin any pinned objects that were not in
		 * the ZCT.
		 */
		void Reap(bool scanStack=true);

		/**
		 * Throw away unused memory (discretionary); to be called at the end of
		 * a GC cycle.
		 */
		void Prune();
		
		/**
		 * @return true if reaping is ongoing, otherwise false.
		 */
		bool IsReaping();

	private:
		// Slow path for Add().  The trick is that the slow path will be entered
		// if top==limit; in that case, we either have a simple overflow or the
		// system is in a "slow" state where additional checks are necessary
		// (such as during sweeping), and the state is kept in other variables.
		void AddSlow(RCObject *obj);
		
		// @return true iff the table can grow by at least one more block.
		bool CanGrow();
		
		// @return the value stored at 'idx'
		RCObject* Get(uint32_t idx);

		// Store 'value' at 'idx'
		void Put(uint32_t idx, RCObject* value);

		// @return the block number for 'idx'
		uint32_t BlockNumber(uint32_t idx);

		// @return the entry within a block for 'idx'
		uint32_t EntryNumber(uint32_t idx);
		
		// @return the address corresponding to ZCT offset 'idx'
		RCObject** PointerTo(uint32_t idx);
		
		// @return the number of ZCT slots available between top and limit or
		//         slowTop and slowLimit, as the case may be, following a reap.
		uint32_t AvailableInCurrentSegment();
		
		// If CanGrow is true and AvailableInCurrentSegment returns zero then add
		// a block of memory to the ZCT.
		//
		// @return true if the block was allocated, false otherwise.
		bool Grow();

		// Capture the stack extent; then scan the stack and pin objects from it
		// only if scanStack is true
		GCWorkItem PinProgramStack(bool scanStack);
		
		// Scan the AllocaStackSegments and pin all objects directly reachable from them.
		void PinRootSegments();
		
		// Conservatively scan memory starting at 'start' for 'len' bytes, examining each
		// aligned word.  If the value stored can be interpreted as a (possibly tagged)
		// pointer to the start of an RCObject, then pin that RCObject.  The value of
		// 'start' must itself be aligned.
		void PinStackObjects(const void *start, size_t len);
		
		// The object was pinned, leave it in the ZCT by moving it to the pinning memory.
		void PinObject(RCObject* obj);
		
		// The object was not pinned, finalize & reclaim it.
		void ReapObject(RCObject* obj);

		// Get ready for reaping: setup pointers for the pinning memory so that pinned
		// objects can be preserved.
		void SetupPinningMemory();
		
		// Add a block of memory to the pinning memory.
		//
		// @return true if the block was allocated, false otherwise.
		bool GrowPinningMemory();
		
		// Replace the ZCT memory blocks by the pinning memory blocks, and setup the
		// ZCT pointers to point into the new blocks.
		void UsePinningMemory();

		// Discard the pinning memory
		void ClearPinningMemory();
		
		// Discard a block that is no longer used because ZCT popping during reaping
		// has gone below the block's beginning.
		void PopFastSegment();
		
		// Discard all blocks in the ZCT block table (second-level blocks).
		void ClearBlockTable();
		
		// Actually free all the blocks on the ZCT block free list.
		void ClearFreeList();

		// @return a new block, NULL if it could not be allocated.
		RCObject** PleaseAllocBlock();
		
		// Discard the block (return it to the free list).
		void FreeBlock(RCObject** block);

#ifdef _DEBUG
		// Debugging code that needs to be validated: reference count validation during reaping
		void SetupDefRefValidation(GCWorkItem& stack);
		void FinishDefRefValidation();
		void DefRefValidate(RCObject* obj);
#endif // _DEBUG
		
		// Private data

		GC *gc;
		RCObject ***blocktable;		// Table of pointers to individual blocks
		RCObject ***blocktop;		// Next free item in blocktable
		bool reaping;				// Are we reaping the zct?
		
		uint32_t budget;			// Remaining number of full blocks to grow by before reaping
		
		// Fast path state
		RCObject **bottom;			// Current segment
		RCObject **top;				// Next location at which to insert a pointer
		RCObject **limit;			// Element beyond last available location
		uint32_t topIndex;			// Index to give to next inserted pointer

		// Slow path state - when slowState==true
		bool     slowState;			// In slow state iff this is true
		RCObject **slowBottom;		// Current segment
		RCObject **slowTop;			// Next location at which to insert a pointer
		RCObject **slowLimit;		// Element beyond last available location
		uint32_t slowTopIndex;		// Index to give to next inserted pointer
		
		// Used during reaping
		RCObject **pinTop;			// Next location at which to insert a non-reaped pointer
		RCObject **pinLimit;		// Element beyond last available location
		uint32_t pinIndex;			// Index to give to next inserted pointer
		
		// List of blocks of pinned objects
		RCObject** pinList;			// First block in list; element 0 is next
		RCObject** pinLast;			// Last block in list
		
		// Block free list
		void** freeList;			// Linked list of blocks; element 0 is next
	};
}

#endif /* __GCZCT__ */
