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
 * Portions created by the Initial Developer are Copyright (C) 1993-2006
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


#include "avmplus.h"

namespace avmplus
{
	Domain::Domain(AvmCore* core, Domain* base) : 
            m_base(base),
		    m_core(core),
            m_namedTraits(new (core->GetGC()) MultinameHashtable()),
            m_namedScripts(new (core->GetGC()) MultinameHashtable()),
	        m_globalMemoryScratch(mmfx_new0(Scratch)),
            m_globalMemoryBase(m_globalMemoryScratch->scratch),
		    m_globalMemorySize(GLOBAL_MEMORY_MIN_SIZE)
	{
	}

	Domain::~Domain()
	{
        mmfx_delete(m_globalMemoryScratch);
	}

	Traits* Domain::getNamedTraits(Stringp name, Namespacep ns, bool recursive/*=true*/)
	{
		Traits *traits = NULL;
		if (recursive && m_base) {
			traits = m_base->getNamedTraits(name, ns, true);
		}
		if (!traits) {
			traits = (Traits*) m_namedTraits->get(name, ns);
		}
		return traits;
	}

	Traits* Domain::getNamedTraits(const Multiname *multiname, bool recursive/*=true*/)
	{
		Traits *traits = NULL;
		if (recursive && m_base) {
			traits = m_base->getNamedTraits(multiname, true);
		}
		if (!traits) {
			traits = (Traits*) m_namedTraits->getMulti(multiname);
		}
		return traits;
	}
	
	MethodInfo* Domain::getNamedScript(Stringp name, Namespacep ns)
	{
		MethodInfo* f = NULL;
		if (m_base) {
			f = m_base->getNamedScript(name, ns);
		}
		if (!f) {
			f = (MethodInfo*)m_namedScripts->get(name, ns);
		}
		return f;
	}

	MethodInfo* Domain::getNamedScript(const Multiname *multiname)
	{
		MethodInfo* f = NULL;
		if (m_base) {
			f = m_base->getNamedScript(multiname);
		}
		if (!f) {
			f = (MethodInfo*)m_namedScripts->getMulti(multiname);
		}
		return f;
	}

	bool Domain::set_globalMemory(ScriptObject* providerObject)
	{
		if (!providerObject || !providerObject->getGlobalMemoryProvider())
		{
			// null obj -- use scratch
			if (m_globalMemoryProviderObject) // unsubscribe from current if any
				globalMemoryUnsubscribe(m_globalMemoryProviderObject);
			// remember NULL obj
			m_globalMemoryProviderObject = NULL;
			// point at scratch mem
			notifyGlobalMemoryChanged(m_globalMemoryScratch->scratch, GLOBAL_MEMORY_MIN_SIZE);
		}
		else if (!globalMemorySubscribe(providerObject))
		{
			// failed... do nothing
			return false;
		}
		else
		{
			// success on globalMemorySubscribe would have led to notifyGlobalMemoryChanged
			// success... unsubscribe from original
			if (m_globalMemoryProviderObject)
				globalMemoryUnsubscribe(m_globalMemoryProviderObject);
			// remember the new one
			m_globalMemoryProviderObject = providerObject;
		}
		return true;
	}

	// record that this uint8_t** refers to a pointer to the
	// global memory backing store
	void Domain::addGlobalMemoryBaseRef(uint8_t** baseRef)
	{
		AvmAssert(baseRef != NULL);

		// find the not slot in a given chunk
		uint32_t mod = m_globalMemoryBaseRefNum % REFS_PER_CHUNK;

		BaseRefChunk* refs;

		// if the slot is zero, we need a new chunk
		if (!mod)
		{
			refs = new (core()->GetGC()) BaseRefChunk();
			refs->next = m_globalMemoryBaseRefs;
			m_globalMemoryBaseRefs = refs;
		}
		else
        {
			refs = m_globalMemoryBaseRefs;
        }
		// put it in the right slot
		refs->refs[mod] = baseRef;
		// and remember we added one
		m_globalMemoryBaseRefNum++;
	}

	// same as addGlobalMemoryBaseRef but for references to the
	// size of the global memory object
	void Domain::addGlobalMemorySizeRef(uint32_t* sizeRef)
	{
		AvmAssert(sizeRef != NULL);

		uint32_t mod = m_globalMemorySizeRefNum % REFS_PER_CHUNK;

		SizeRefChunk* refs;

		if (!mod)
		{
			refs = new (core()->GetGC()) SizeRefChunk();
			refs->next = m_globalMemorySizeRefs;
			m_globalMemorySizeRefs = refs;
		}
		else
			refs = m_globalMemorySizeRefs;
		refs->refs[mod] = sizeRef;
		m_globalMemorySizeRefNum++;
	}

	// memory changed so go through and update all reference to both the base
	// and the size of the global memory
	void Domain::notifyGlobalMemoryChanged(uint8_t* newBase, uint32_t newSize)
	{
		AvmAssert(newBase != NULL); // real base address
		AvmAssert(newSize >= GLOBAL_MEMORY_MIN_SIZE); // big enough

		// ensure a real change happened...
		if (newBase != m_globalMemoryBase || newSize != m_globalMemorySize)
		{
			// if a real change happened to backing store base address...
			if (newBase != m_globalMemoryBase)
			{
				BaseRefChunk *baseRefs = m_globalMemoryBaseRefs;

				// go through each reference
				for(uint32_t n = 0; n < m_globalMemoryBaseRefNum; n++)
				{
					// get the slot
					int mod = n % REFS_PER_CHUNK;

					// if it's zero, get the NEXT slot
					// this means we start with the SECOND chunk
					if (!mod)
					{
						baseRefs = baseRefs->next;
						// and when we get to the end, THEN do the first chunk
						if (!baseRefs)
							baseRefs = m_globalMemoryBaseRefs;
					}
					uint8_t** p = (baseRefs->refs[mod]);
					// and do a difference instead of a simple write
					// as it may be offset from the base
                    // printf("update base %p: %p -> %p\n",p,*p,*p - m_globalMemoryBase + newBase);
					*p = *p - m_globalMemoryBase + newBase;
				}
			}

			// same as above but for size
			if (newSize != m_globalMemorySize)
			{
				SizeRefChunk* sizeRefs = m_globalMemorySizeRefs;

				for(uint32_t n = 0; n < m_globalMemorySizeRefNum; n++)
				{
					int mod = n % REFS_PER_CHUNK;

					if (!mod) // start with SECOND chunk
					{
						sizeRefs = sizeRefs->next;
						// and when we get to the end, THEN do the first chunk
						if (!sizeRefs)
							sizeRefs = m_globalMemorySizeRefs;
					}
					uint32_t* p = (sizeRefs->refs[mod]);
                    // printf("update size %p: %d -> %d\n",p,*p,*p - m_globalMemorySize + newSize);
					*p = *p - m_globalMemorySize + newSize;
				}
			}

			// record the new base and size
			m_globalMemoryBase = newBase;
			m_globalMemorySize = newSize;
		}
	}

 	bool Domain::globalMemorySubscribe(ScriptObject* providerObject) 
 	{
        GlobalMemoryProvider* provider = providerObject->getGlobalMemoryProvider();
        return provider ? provider->addSubscriber(this) : false;
 	}
 
 	bool Domain::globalMemoryUnsubscribe(ScriptObject* providerObject)
 	{
        GlobalMemoryProvider* provider = providerObject->getGlobalMemoryProvider();
        return provider ? provider->removeSubscriber(this) : false;
 	}
}


