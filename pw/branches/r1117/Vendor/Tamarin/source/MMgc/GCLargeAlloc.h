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

#ifndef __GCLargeAlloc__
#define __GCLargeAlloc__

namespace MMgc
{
	/**
	 * This is a garbage collecting allocator for large memory blocks.
	 */
	class GCLargeAlloc
	{
		friend class GC;
		friend class GCLargeAllocIterator;
	private:
		enum {
			kMarkFlag         = 0x1,
			kQueuedFlag       = 0x2,
			kFinalizeFlag     = 0x4,
			kHasWeakRef       = 0x8,
			kContainsPointers = 0x10,
			kRCObject         = 0x20
		};

	public:
		GCLargeAlloc(GC* gc);
		~GCLargeAlloc();

#if defined DEBUG || defined MMGC_MEMORY_PROFILER
		void* Alloc(size_t originalSize, size_t requestSize, int flags);
#else
		void* Alloc(size_t requestSize, int flags);
#endif
		void Free(const void *ptr);

		void Finalize();
		void ClearMarks();

		// not a hot method
		static void SetHasWeakRef(const void *item, bool to);

		// not a hot method
		static bool HasWeakRef(const void *item);

		static bool IsLargeBlock(const void *item);

		static bool SetMark(const void *item);

		// Not a hot method but always inlining probably shrinks the code
		static void SetFinalize(const void *item);
		
		static bool GetMark(const void *item);

#ifdef _DEBUG
		static bool IsWhite(const void *item);
#endif
	
		static bool IsMarkedThenMakeQueued(const void *item);

		static bool IsQueued(const void *item);

		static void* FindBeginning(const void *item);

		// not a hot method
		static void ClearFinalized(const void *item);

		// Not hot, because GC::MarkItem open-codes it
		static bool ContainsPointers(const void *item);
		
		// not a hot method
		static bool IsFinalized(const void *item);

		// Can be hot - used by PinStackObjects
		static bool IsRCObject(const void *item);

		//This method returns the number bytes allocated by FixedMalloc
		size_t GetBytesInUse();
		
		//This method is for more fine grained allocation details
		//It reports the total number of bytes requested (i.e. ask size) and
		//the number of bytes actually allocated.  The latter is the same
		//number as reported by GetBytesInUse()
		void GetUsageInfo(size_t& totalAskSize, size_t& totalAllocated);

	private:
		struct LargeBlock : GCBlockHeader
		{
			uint32_t flags;

			int GetNumBlocks() const;
		};

		static LargeBlock* GetLargeBlock(const void *addr);
		
		// not a hot method
		static bool NeedsFinalize(LargeBlock *block);
		
		// not a hot method
		static void ClearQueued(const void *item);
		
		// The list of chunk blocks
		LargeBlock* m_blocks;
#ifdef MMGC_MEMORY_PROFILER
		size_t m_totalAskSize;
#endif

		bool m_startedFinalize;
		
#ifdef _DEBUG
		static bool ConservativeGetMark(const void *item, bool bogusPointerReturnValue);
#endif

	protected:
		GC *m_gc;

	public:
		static LargeBlock* Next(LargeBlock* b);
	};

	/**
	 * A utility class used by the marker to handle mark stack overflow: it abstracts
	 * iterating across marked, non-free objects in one allocator instance.
	 *
	 * No blocks must be added or removed during the iteration.  If an object's
	 * bits are changed, those changes will visible to the iterator if the object has
	 * not yet been reached by the iteration. 
	 */
	class GCLargeAllocIterator
	{
	public:
		GCLargeAllocIterator(MMgc::GCLargeAlloc* alloc);
		
		bool GetNextMarkedObject(void*& out_ptr, uint32_t& out_size);
		
	private:
		GCLargeAlloc* const alloc;
		GCLargeAlloc::LargeBlock* block;
	};
}

#endif /* __GCLargeAlloc__ */
