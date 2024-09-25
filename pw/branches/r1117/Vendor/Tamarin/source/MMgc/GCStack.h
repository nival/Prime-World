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

#ifndef __GCStack__
#define __GCStack__

namespace MMgc
{	
	/**
	 * Conservative collector unit of work
	 */
	class GCWorkItem
	{
	public:
		// FIXME? The initialization is redundant for most locals and for the mark stack we
		// don't want to have to init all the elements in the array as it makes allocating a mark
		// stack segment expensive.  I believe we could safely get rid of the two initializing
		// clauses here.  --lars
		GCWorkItem() : ptr(NULL), _size(0) { }
		inline GCWorkItem(const void *p, uint32_t s, bool isGCItem);
		
		uint32_t GetSize() const { return _size & ~1; }
		uint32_t IsGCItem() const { return _size & 1; }
		
		// If a WI is a GC item, `ptr` is the UserPointer; it must not
		// be the RealPointer nor an interior pointer
		const void *ptr;
		
		// The low bit of _size stores whether this is a GC item.
		// Always access this through `GetSize` and `IsGCItem`
		uint32_t _size;
	};
	
	// Each GCWorkItem is two words.  There's a one-word overhead in the segment data
	// structure, and on a 32-bit system there's one word of alignment.  Ergo we have
	// space for (4k-8)/2w items in a block, where w(ordsize) is 4 or 8.  (FixedMalloc 
	// does not add further overhead in Release builds.)
#ifdef AVMPLUS_64BIT
	enum { kMarkStackItems=255 };
#else
	enum { kMarkStackItems=511 };
#endif

	// Invariant: m_topSegment, m_base, m_top, and m_limit are never NULL following construction.
	// Invariant: m_base <= m_top <= m_limit
	// Invariant: m_base == m_topSegment->m_items
	// Invariant: m_limit == m_topSegment->m_items + kMarkStackItems
	
	class GCMarkStack
	{
	public:
		GCMarkStack();
		~GCMarkStack();

		/** 
		 * Push 'item' onto the stack. 
		 *
		 * This should only ever be called from GC::PushWorkItem, because
		 * that function does extra processing and may push various derived
		 * items (for large objects).
		 *
		 * @return true if the item could be pushed, false if the system
		 *		   is out of memory and the item was not pushed.
		 */
		bool Push(GCWorkItem item);

		/**
		 * Pop one item off the stack.  Precondition: The stack must not be empty.
		 * @return the popped element.
		 */
		GCWorkItem Pop();

		/** @return the number of elements on the stack. */
		uint32_t Count();

		/** Pop all elements off the stack, discard the cached extra segment. */
		void Clear();

		/** @return the number of elements in a segment */
		uint32_t ElementsPerSegment();
	
		/** @return the number of entirely full segments */
		uint32_t EntirelyFullSegments();

		/** 
		 * Move one entirely full segment from 'other' and insert it into our segment list.
		 * @return true if the transfer was successful, false if an out-of-memory condition
		 *         prevented reestablishing invariants in 'other' following the transfer.
		 *         (In the latter case the stacks remain unchanged.)
		 */
		bool TransferOneFullSegmentFrom(GCMarkStack& other);

#ifdef MMGC_MARKSTACK_DEPTH
		/** @return the number of elements on the stack when its depth was the greatest */
		uint32_t MaxCount();
#endif
	
	protected:
		// no implementation of these
		GCMarkStack(const GCMarkStack& other);
		GCMarkStack& operator=(const GCMarkStack& other);

	private:
		
		struct GCStackSegment
		{
			GCWorkItem		m_items[kMarkStackItems];
			GCStackSegment* m_prev;
		};
		
		GCWorkItem*			m_base;			// first entry in m_topSegment
		GCWorkItem*			m_top;			// first free entry in m_topSegment
		GCWorkItem*			m_limit;		// first entry following m_topSegment
		GCStackSegment*	    m_topSegment;	// current stack segment, older segments linked through 'prev'
		uint32_t			m_hiddenCount;	// number of elements in those older segments
		GCStackSegment*		m_extraSegment;	// single-element cache used to avoid hysteresis
#ifdef MMGC_MARKSTACK_DEPTH
		uint32_t			m_maxDepth;		// max depth of mark stack
#endif

		/**
		 * The current segment must be NULL or full (top == limit).  Push a new segment onto the 
		 * stack, and update all instance vars.
		 * @param mustSucceed  If true, the allocation must not fail.  This is true during initialization.
		 *                     Failure in this case is signaled through the normal OOM mechanism.
		 * @return true if the segment could be pushed or false if not (if it could not be allocated).
		 */
		bool PushSegment(bool mustSucceed=false);
		
		// The current segment is discarded and the previous segment, if any, reinstated.
		// Update all instance vars.
		void PopSegment();

#ifdef _DEBUG
		// Check as many invariants as possible
		bool Invariants();
#endif
	};
	
	REALLY_INLINE bool GCMarkStack::Push(GCWorkItem item)
	{
		GCAssert(item.ptr != NULL);
		if (m_top == m_limit) 
			if (!PushSegment())
				return false;
		GCAssert(m_top < m_limit);
		*m_top++ = item;
#ifdef MMGC_MARKSTACK_DEPTH
		uint32_t depth = Count();
		if (depth > m_maxDepth)
			m_maxDepth = depth;
#endif
		GCAssert(Invariants());
		return true;
	}
	
	REALLY_INLINE GCWorkItem GCMarkStack::Pop()
	{
		GCAssert(m_top > m_base);
		GCWorkItem t = *--m_top;
		GCAssert(t.ptr != NULL);
#ifdef _DEBUG
		VMPI_memset(m_top, 0, sizeof(GCWorkItem));
#endif
		if (m_top == m_base)
			if (m_topSegment->m_prev != NULL)
				PopSegment();
		GCAssert(Invariants());
		return t;
	}
	
	REALLY_INLINE uint32_t GCMarkStack::Count()
	{
		return uint32_t(m_top - m_base) + m_hiddenCount;
	}

	REALLY_INLINE uint32_t GCMarkStack::ElementsPerSegment()
	{
		return kMarkStackItems;
	}

	REALLY_INLINE uint32_t GCMarkStack::EntirelyFullSegments()
	{
		return Count() / kMarkStackItems;
	}

#ifdef MMGC_MARKSTACK_DEPTH
	REALLY_INLINE uint32_t GCMarkStack::MaxCount()
	{
		return m_maxDepth;
	}
#endif
}

#endif /* __GCStack__ */
