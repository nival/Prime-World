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

#ifndef __avmplus_Sampler__
#define __avmplus_Sampler__

namespace avmplus
{
#ifdef DEBUGGER

    //
    // Note that "SamplerObjectType" is atomlike, but is NOT an Atom: 
    //
    // -- the lower three bits are SamplerObjectTypeKind
    // -- if kind is kSOT_Object, upper bits are a VTable*
    // -- if kind is kSOT_String or kSOT_Namespace, upper bits are a Toplevel*
    // -- if kind is kSOT_Empty, upper bits are zero
    //
    // note that for efficiency, the Toplevel* in the String/Namespace case is filled in lazily downstream
    // (via sotSetToplevel), to avoid having String/Namespace ctors look up the proper Toplevel
    // when not sampling.
    //
    // To reinforce the fact that this Isn't An Atom, it's now its own opaque type, with 
    // lovely little accessors. Please use them now, rather than casting to intptr and
    // dancing on the bits directly.
    //

    enum SamplerObjectTypeKind
    {
        kSOT_Object = 0,
        kSOT_String = 1,
        kSOT_Namespace = 2,
        kSOT_Empty = 3
    };

    REALLY_INLINE SamplerObjectType sotNamespace()
    {
        // start with Toplevel == NULL, filled in implicitly later
        return SamplerObjectType(kSOT_Namespace);
    }

    REALLY_INLINE SamplerObjectType sotString()
    {
        // start with Toplevel == NULL, filled in implicitly later
        return SamplerObjectType(kSOT_String);
    }

    REALLY_INLINE SamplerObjectType sotEmpty()
    {
        return SamplerObjectType(kSOT_Empty);
    }

    REALLY_INLINE SamplerObjectType sotObject(VTable* vt)
    {
        MMGC_STATIC_ASSERT(kSOT_Object == 0);
        return SamplerObjectType(uintptr_t(vt) | uintptr_t(kSOT_Object));
    }

    REALLY_INLINE SamplerObjectTypeKind sotGetKind(SamplerObjectType sot)
    {
        return SamplerObjectTypeKind(uintptr_t(sot) & 7);
    }

    REALLY_INLINE VTable* sotGetVTable(SamplerObjectType sot)
    {
        MMGC_STATIC_ASSERT(kSOT_Object == 0);
        AvmAssert(sotGetKind(sot) == kSOT_Object);
        return (VTable*)(sot);
    }

    REALLY_INLINE Toplevel* sotGetToplevel(SamplerObjectType sot)
    {
        AvmAssert(sotGetKind(sot) == kSOT_String || sotGetKind(sot) == kSOT_Namespace);
        return (Toplevel*)(uintptr_t(sot) & ~7);
    }

    REALLY_INLINE SamplerObjectType sotSetToplevel(SamplerObjectType sot, Toplevel* toplevel)
    {
        SamplerObjectTypeKind const sk = sotGetKind(sot);
        if (sk == kSOT_String || sk == kSOT_Namespace)
        {
            sot = SamplerObjectType(uintptr_t(toplevel) | uintptr_t(sk));
        }
        return sot;
    }

    // return value will be a VTable* or a Toplevel* -- intended only for use in adding GC work items
    REALLY_INLINE void* sotGetGCPointer(SamplerObjectType sot)
    {
        return (void*)(uintptr_t(sot) & ~7);
    }

	// This structure is used to read/write data to the sample stream.
	// The fields are written out to the sample stream as they are defined here.  
	struct Sample
	{
		uint64 micros;
		uint32 sampleType;
		union {
			// not filled in for sampleType==DELETED_OBJECT_SAMPLE
			struct {
				// Number of StackTraceElements in the trace
				uint32 depth;
				// Beginning of an array of StackTraceElement.  Basically, an MethodInfo*, Stringp, Stringp, uint32 for each entry. 
				void *trace; 
			} stack;
			// deleted object size record, instead of stack
			uint64 size; 
		};
		// filled for DELETED_OBJECT_SAMPLE + NEW_OBJECT_SAMPLE
		uint64 id; 

		// Following three fields are only filled in for sampleType==NEW_OBJECT_SAMPLE or NEW_AUX_SAMPLE
		// They are not present in the sample stream for other sample types
		SamplerObjectType sot;
		void *ptr;
		uint64 alloc_size; // size for new mem sample
	};

	class Sampler : public MMgc::GCRoot
	{
	public:
		Sampler(AvmCore*);
		virtual ~Sampler();

		enum SampleType 
		{ 
			RAW_SAMPLE=0x55555555,
			NEW_OBJECT_SAMPLE=0xaaaaaaaa, 
			DELETED_OBJECT_SAMPLE=0xdddddddd,
			NEW_AUX_SAMPLE=0xeeeeeeee
		};
		
		// should use opaque Cursor type instead of byte*
		byte *getSamples(uint32 &num);
		void readSample(byte *&p, Sample &s);
		
		void init(bool sampling, bool autoStart);
		void sampleCheck() { if(takeSample) sample(); }

		uint64 recordAllocationInfo(AvmPlusScriptableObject *obj, SamplerObjectType sot);
		uint64 recordAllocationSample(const void* item, uint64_t size, bool callback_ok = true, bool forceWrite = false);
		void recordDeallocationSample(const void* item, uint64_t size);

		virtual void startSampling();
		virtual void stopSampling();
		virtual void clearSamples();
		virtual void pauseSampling();

		void sampleInternalAllocs(bool b);

		void setCallback(ScriptObject* callback);

		
		// called by VM after initBuiltin's
		void initSampling();

		void createFakeFunction(const char *name);
		Stringp getFakeFunctionName(const char* name);

		void presweep();
		void postsweep();

		inline uint32_t sampleCount() const { return numSamples; }
		inline bool activelySampling() { return samplingNow; }
		inline bool sampling() const { return _sampling; }

	private:	
		
		void sample();

		void rewind(byte*&b, uint32 amount)
		{
			b -= amount;
		}

		int sampleSpaceCheck(bool callback_ok = true);
		
		void writeRawSample(SampleType sampleType);

	// ------------------------ DATA SECTION BEGIN
	public:
		VTable*				sampleIteratorVTable;
		VTable*				slotIteratorVTable;
	protected:
		AvmCore*			core;
	private:
		List<Stringp>		fakeMethodNames; 
		uint64_t			allocId;
		uint8_t*			samples;
		uint8_t*			currentSample;
		uint8_t*			lastAllocSample;
		DRC(ScriptObject*)	callback;
		uintptr_t			timerHandle;
		MMgc::GCHashtable_VMPI		uids;		// important to use the VMPI variant for non-MMGC-based memory allocation.
		MMgc::GCHashtable_VMPI*		ptrSamples;	// important to use the VMPI variant for non-MMGC-based memory allocation.
		int32_t				takeSample;
		uint32_t			numSamples;
		uint32_t			samples_size;
		bool				samplingNow;
		bool				samplingAllAllocs;
		bool				runningCallback;
		bool				autoStartSampling;	// if true we call startSampling as early as possible during startup
		bool				_sampling;			// are we sampling at all
	// ------------------------ DATA SECTION END
	};

	#define SAMPLE_FRAME(_strp, _core)	avmplus::CallStackNode __fcsn((avmplus::AvmCore*)_core, _strp)
	#define SAMPLE_CHECK()				__fcsn.sampleCheck();

#else

	#define SAMPLE_FRAME(_x, _s) 
	#define SAMPLE_CHECK()

#endif // DEBUGGER
}
#endif // __avmplus_Sampler__
