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

#ifndef __GCMemoryProfiler__
#define __GCMemoryProfiler__

namespace MMgc
{
	void PrintAllocStackTrace(const void *item);
	void PrintDeleteStackTrace(const void *item);
	const char* GetAllocationName(const void *obj);

#ifdef MMGC_MEMORY_PROFILER

	const int kMaxStackTrace = 16; // RtlCaptureStackBackTrace stops working when this is 32

#define MMGC_MEM_TAG(_x) if(MMgc::GCHeap::GetGCHeap()->HooksEnabled()) MMgc::SetMemTag(_x)
#define MMGC_MEM_TYPE(_x) if(MMgc::GCHeap::GetGCHeap()->HooksEnabled()) MMgc::SetMemType(_x)
	
	class StackTrace;

	void SetMemTag(const char *memtag);
	void SetMemType(const void *memtype);
	void PrintStackTrace(StackTrace *trace);

	class GCStackTraceHashtableKeyHandler
	{
	public:
		inline static uint32_t hash(const void* k)
		{
			const int* array = (const int*)k;
			int hash = 0;
			for(int i=0;i<kMaxStackTrace; i++)
				hash += array[i];
			return uint32_t(hash);
		}

		inline static bool equal(const void* k1, const void* k2)
		{
			if (k1 == NULL || k2 == NULL)
				return false;
			return VMPI_memcmp(k1, k2, kMaxStackTrace * sizeof(void*)) == 0;
		}
	};

	typedef GCHashtableBase<GCStackTraceHashtableKeyHandler,GCHashtableAllocHandler_VMPI> GCStackTraceHashtable_VMPI;

	class MemoryProfiler : public GCAllocObject
	{
	public:
		MemoryProfiler();
		~MemoryProfiler();
		void RecordAllocation(const void *item, size_t askSize, size_t gotSize);
		void RecordDeallocation(const void *item, size_t size);
		void DumpFatties();
		void DumpSimple();
		const char *GetAllocationName(const void *obj);
		StackTrace *GetAllocationTrace(const void *obj);
		StackTrace *GetDeletionTrace(const void *obj);
		StackTrace *GetStackTrace();
		size_t GetAskSize(const void* item);

	private:
		const char *Intern(const char *name, size_t len);
		const char *GetPackage(StackTrace *trace);
		const char *GetAllocationNameFromTrace(StackTrace *trace);
		const char *GetAllocationCategory(StackTrace *trace);

		// Note: it's important to use the VMPI variant of GCHashtable for all of these.

		// intern table of StackTrace*
		GCStackTraceHashtable_VMPI stackTraceMap;

		// intern table of strings used by Profiler
		GCStringHashtable_VMPI stringsTable;

		// hash table for address -> name lookup
		GCHashtable_VMPI nameTable;

		//table to store allocation specific information
		GCHashtable_VMPI allocInfoTable;
	};

#else // MMGC_MEMORY_PROFILER

#define MMGC_MEM_TAG(_x)
#define MMGC_MEM_TYPE(_x)

#endif // !MMGC_MEMORY_PROFILER

#ifndef MMGC_MEMORY_INFO

#define GetRealPointer(_x) _x
#define GetUserPointer(_x) _x
#define DebugSize() 0

#else 

	/**
	* How much extra size does DebugDecorate need?
	*/
	size_t DebugSize();

	/**
	* decorate memory with debug information, return pointer to memory to return to caller
	*/
	void DebugDecorate(const void *item, size_t size);
	
	/** 
	* Given a pointer to user memory do debug checks and return pointer to real memory
	*/
	void *DebugFree(const void *item, int poison, size_t size);		

	/**
	* Given a user pointer back up to real beginning
	*/
	inline void *GetRealPointer(const void *item) { return (void*)((uintptr_t) item -  2 * sizeof(int32_t)); }

	/**
	* Given a real pointer return pointer to user memory
	*/
	inline void *GetUserPointer(const void *item) { return (void*)((uintptr_t) item +  2 * sizeof(int32_t)); }

	/**
	* Print errorr messsage and stack traces for allocation/free of memory
	* that has been written over after being deleted
	*/
	void ReportDeletedMemoryWrite(const void* item);

#endif //MMGC_MEMORY_INFO

} // namespace MMgc

#endif //!__GCMemoryProfiler__

