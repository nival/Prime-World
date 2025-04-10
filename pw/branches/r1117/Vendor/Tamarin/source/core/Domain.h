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

#ifndef __avmplus_Domain__
#define __avmplus_Domain__

namespace avmplus
{
    // needs to be a subclass of GCObject so we can convert to/from a WeakRef...
    // Domain wants to be a finalized object anyway so let's use GCFinalizedObject
    class GlobalMemorySubscriber : public MMgc::GCFinalizedObject
    {
    public:
        virtual void notifyGlobalMemoryChanged(uint8_t* newBase, uint32_t newSize) = 0;
    };

    // an ABC
    class GlobalMemoryProvider
    {
    public:
        virtual ~GlobalMemoryProvider() {}
        virtual bool addSubscriber(GlobalMemorySubscriber* subscriber) = 0;
        virtual bool removeSubscriber(GlobalMemorySubscriber* subscriber) = 0;
    };

	class Domain : public GlobalMemorySubscriber
	{
	public:
		Domain(AvmCore* core, Domain* base);
		~Domain();
		
		Traits* getNamedTraits(Stringp name, Namespacep ns, bool recursive/*=true*/);
		Traits* getNamedTraits(const Multiname* multiname, bool recursive/*=true*/);
		MethodInfo* getNamedScript(Stringp name, Namespacep ns);
		MethodInfo* getNamedScript(const Multiname* multiname);
		
		Traits* getNamedTrait(Stringp name, Namespace* ns) { return (Traits*)m_namedTraits->get(name, ns); }
		void addNamedTrait(Stringp name, Namespace* ns, Traits* v) { m_namedTraits->add(name, ns, (Binding)v); }
		void addNamedScript(Stringp name, Namespace* ns, MethodInfo* v) { m_namedScripts->add(name, ns, (Binding)v); }

		/**
		 * global memory access glue
		 */
		enum {
			GLOBAL_MEMORY_MIN_SIZE =
// if we have JIT support for MOPS we can optimize range checks
// against ranges that can fit within the minimum memory size
// so it's worth burning a little space
//#ifdef AVMPLUS_IA32
//				1024
//#else
				8
//#endif
		};

		REALLY_INLINE Domain* base() const { return m_base; }
		REALLY_INLINE AvmCore* core() const { return m_core; }
		REALLY_INLINE uint8_t* globalMemoryBase() const { return m_globalMemoryBase; }
		REALLY_INLINE uint32_t globalMemorySize() const { return m_globalMemorySize; }

		// global memory object accessor (will always be a ByteArray but
		// ByteArray isn't part of AVMPlus proper so plumbing is a little
		// weird...)
		ScriptObject* get_globalMemory() const { return m_globalMemoryProviderObject; }
		bool set_globalMemory(ScriptObject* providerObject);

		// mark a pointer to pointer as being a reference to the global memory
		// so that it gets updated if the global memory moves
		void addGlobalMemoryBaseRef(uint8_t** baseRef);
		// mark a pointer to uint32_t as being a reference to
		// the current size of the global memory so it can get updated
		void addGlobalMemorySizeRef(uint32_t* sizeRef);

        // from GlobalMemorySubscriber
		/*virtual*/ void notifyGlobalMemoryChanged(uint8_t* newBase, uint32_t newSize);

	private:
		// subscribes to the memory object "mem" such that "mem" will call our
		// notifyGlobalMemoryChanged when it moves
		bool globalMemorySubscribe(ScriptObject* providerObject);
		// stops "mem" from notifying us if it moves
		bool globalMemoryUnsubscribe(ScriptObject* providerObject);

	private:

        // number of memory base or size references per "chunk"
        // these references are stored in linked list with each link
        // storing REFS_PER_CHUNK values to minimize overhead
        enum { REFS_PER_CHUNK = 254 }; // TODO chunk size is right?

        // chunk link for references to global memory base
        struct BaseRefChunk : public MMgc::GCObject
        {
            uint8_t** refs[REFS_PER_CHUNK];
            DWB(BaseRefChunk *) next;
        };

        // same as above but for reference to global memory size
        struct SizeRefChunk : public MMgc::GCObject
        {
            uint32_t* refs[REFS_PER_CHUNK];
            DWB(SizeRefChunk *) next;
        };

        // allocate "scratch" as a struct to make it easier to allocate pre-zeroed
        struct Scratch
        {
            uint8_t scratch[GLOBAL_MEMORY_MIN_SIZE];
        };

	private:
		Domain* const                   m_base;
		AvmCore* const                  m_core;
		/** The domain-wide traits table (type name => instance Traits) */
		DWB(MultinameHashtable*)        m_namedTraits;
		/** domain-wide type table of scripts, indexed by definition name */
		DWB(MultinameHashtable*)        m_namedScripts;
		// scratch memory to use if the memory object is NULL...
        // allocated via mmfx_new, which is required by nanojit
        Scratch*                        m_globalMemoryScratch;
		// backing store / current size for global memory
		uint8_t*                        m_globalMemoryBase;
		uint32_t                        m_globalMemorySize;
        // the actual memory object (can be NULL)
        DRCWB(ScriptObject*)            m_globalMemoryProviderObject;
        DWB(BaseRefChunk *)             m_globalMemoryBaseRefs;
		DWB(SizeRefChunk *)             m_globalMemorySizeRefs;
        uint32_t                        m_globalMemoryBaseRefNum;
		uint32_t                        m_globalMemorySizeRefNum;
	};

}

#endif /* __avmplus_Domain__ */
