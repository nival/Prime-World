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

#include "avmplus.h"

using namespace MMgc;

namespace avmplus
{
	void MultinameHashtable::grow()
	{
		// double our table
		int capacity = numQuads*2;
		MMgc::GC* gc = MMgc::GC::GetGC(this);
		MMGC_MEM_TYPE(this);
		Quad* newAtoms = (Quad *) gc->Calloc(capacity, sizeof(Quad), GC::kContainsPointers|GC::kZero);
		rehash(m_quads, numQuads, newAtoms, capacity);
		gc->Free(m_quads);
		WB(gc, this, &m_quads, newAtoms);
		numQuads = capacity;
	}

	Binding MultinameHashtable::getMulti(const Multiname* mname) const
	{
		// multiname must not be an attr name, have wildcards, or have runtime parts.
		AvmAssert(mname->isBinding() && !mname->isAnyName());

		if (!mname->isNsset())
			return get(mname->getName(), mname->getNamespace());
		else
			return get(mname->getName(), mname->getNsset());
	}

	// return the NS that unambigously matches in "match" (or null for none/ambiguous)
	Binding MultinameHashtable::getMulti(const Multiname& mname, Namespacep& match) const
	{
		// multiname must not be an attr name, have wildcards, or have runtime parts.
		AvmAssert(mname.isBinding() && !mname.isAnyName());

		if (!mname.isNsset())
		{
			Binding b = get(mname.getName(), mname.getNamespace());
			match = (b != BIND_NONE) ? mname.getNamespace() : NULL;
			return b;
		}
		else
		{
			const Quad* q = getNSSet(mname.getName(), mname.getNsset()); 
			match = q->ns; 
			return q->value; 
		}
	}

	void MultinameHashtable::add(Stringp name, Namespacep ns, Binding value)
	{
		if (isFull())
		{
			grow();
		}
		put(name, ns, value);
	}

	MultinameHashtable::MultinameHashtable(int capacity) : 
		m_quads(NULL),
		size(0),
		numQuads(0)
	{
		Init(capacity);
	}

	void MultinameHashtable::Init(int capacity)
	{
		if (capacity)
		{
			numQuads = MathUtils::nextPowerOfTwo(capacity);

			MMgc::GC* gc = MMgc::GC::GetGC(this);

			AvmAssert(numQuads > 0);
			MMGC_MEM_TYPE(this);
			Quad* newAtoms = (Quad *) gc->Alloc (sizeof(Quad) * numQuads, GC::kContainsPointers|GC::kZero);
			WB(gc, this, &m_quads, newAtoms);
		}
	}

	MultinameHashtable::~MultinameHashtable()
	{
		GC *gc = GC::GetGC(this);
		gc->Free(m_quads);
	}

	bool MultinameHashtable::isFull() const
	{ 
		// 0.80 load factor
		return 5*(size+1) >= numQuads*4; 
	}

	int MultinameHashtable::find(Stringp name, Namespacep ns, const Quad* t, unsigned m)
	{
		AvmAssert(ns->getURI()->isInterned());
		AvmAssert(name != NULL && ns != NULL);
		AvmAssert(name->isInterned());

		// this is a quadratic probe but we only hit every third slot since those hold keys.
		int n = 7;

		int bitmask = (m - 1);

		// Note: Mask off MSB to avoid negative indices.  Mask off bottom
		// 3 bits because it doesn't contribute to hash.  Quad it
		// because names, namespaces, and values are stored adjacently.
		unsigned i = ((0x7FFFFFF8 & (uintptr)name) >> 3) & bitmask;

		Stringp k;
		while (((k=t[i].name) != name || !(t[i].ns == ns || matchNS(t[i].ns->m_uri, t[i].apis, ns))) && k != NULL)
		{
			i = (i + (n++)) & bitmask;			// quadratic probe
		}
		return i;
	}

	/**
	 * since identifiers are always interned strings, they can't be 0,
	 * so we can use 0 as the empty value.
	 */
	static const Stringp EMPTY = NULL;

	const MultinameHashtable::Quad* MultinameHashtable::getNSSet(Stringp mnameName, NamespaceSetp nsset) const
	{
	#ifdef AVMPLUS_64BIT
		static const Quad kBindNone = { NULL, NULL, BIND_NONE, 0, 0 };
		static const Quad kBindAmbiguous = { NULL, NULL, BIND_AMBIGUOUS, 0, 0 };
	#else
		static const Quad kBindNone = { NULL, NULL, BIND_NONE, 0, 0 };
		static const Quad kBindAmbiguous = { NULL, NULL, BIND_AMBIGUOUS, 0, 0 };
	#endif
	
		int nsCount = nsset->count();
		int j;

		const Quad* match = &kBindNone;
		Binding matchValue = match->value;

		// this is a quadratic probe but we only hit every third slot since those hold keys.
		int n = 7;
		int bitMask = numQuads - 1;

		// Note: Mask off MSB to avoid negative indices.  Mask off bottom
		// 3 bits because it doesn't contribute to hash.  Quad it
		// because names, namespaces, and values are stored adjacently.
		unsigned i = ((0x7FFFFFF8 & (uintptr)mnameName)>>3) & bitMask;
		Stringp atomName;

		const Quad* t = m_quads;
		while ((atomName = t[i].name) != EMPTY)
		{
			if (atomName == mnameName)
			{
				Namespacep probeNS = t[i].ns;
				AvmAssert(probeNS->getURI()->isInterned());
				API probeAPIs = t[i].apis;
				uintptr probeURI = probeNS ? probeNS->m_uri : 0;
				for (j=0; j < nsCount; j++)
				{
					Namespacep ns = nsset->nsAt(j);
					AvmAssert(ns->getURI()->isInterned());
					if (probeNS==ns || (probeURI == ns->m_uri && (probeAPIs & ns->m_api)))
					{
						match = &t[i];
						matchValue = match->value;
						goto found1;
					}
				}
			}

			i = (i + (n++)) & bitMask;			// quadratic probe
		}

		return &kBindNone;

found1:
		if (t[i].multiNS)
		{
			int k = (i + (n++)) & bitMask;			// quadratic probe
			while ((atomName = t[k].name) != EMPTY)
			{
				if (atomName == mnameName)
				{
					Namespacep probeNS = t[k].ns;
					AvmAssert(probeNS->getURI()->isInterned());
					API probeAPIs = t[k].apis;
					uintptr probeURI = t[k].ns->m_uri;
					for (j=0; j < nsCount; j++)
					{
						Namespacep ns = nsset->nsAt(j);
						if ((probeNS==ns || matchNS(probeURI, probeAPIs, ns)) && matchValue != t[k].value)
						{
							return &kBindAmbiguous;

						}
					}
				}
				k = (k + (n++)) & bitMask;			// quadratic probe
			}
		}
		return match;
	}


	void MultinameHashtable::put(Stringp name, Namespacep ns, Binding value)
	{
		AvmAssert(!isFull());
		AvmAssert(name->isInterned());
		AvmAssert(ns->getURI()->isInterned());

		GC* gc = GC::GetGC(m_quads);

		uint32_t multiNS = 0;
		
		// inlined version of find(), so that we can sniff for the multiNS
		// case (and update as necessary) in a single pass (rather than the 
		// two extra passes we used to do)... this relies on the fact that
		// the quadratic probe will walk thru every existing entry with the same
		// same name in order to find an empty slot, thus if there are any existing
		// entries with a different ns than what we are adding, all of those name
		// entries should be marked as multiNS.
		Quad* cur;
		Quad* const quadbase = m_quads;
		{
			int n = 7;
			int const bitmask = (numQuads - 1);
			unsigned i = ((0x7FFFFFF8 & (uintptr)name) >> 3) & bitmask;
			cur = quadbase + i;
			for (;;)
			{
				Stringp probeName = cur->name;
				if (!probeName)
				{
					// found the hole.
					break;
				}

				if (probeName == name)
				{
					// there's at least one existing entry with this name in the MNHT.
					if (cur->ns == ns || matchNS(cur->ns->m_uri, cur->apis, ns))
					{
						// it's the one we're looking for, just update the value.
						goto write_value;
					}

					// it's not the one we're looking for, thus we are now multiNS on this name.
					if (cur->ns->m_uri != ns->m_uri) {
						cur->multiNS = multiNS = 1;
					}
				}

				i = (i + (n++)) & bitmask;			// quadratic probe
				cur = quadbase + i;
			}
		}
		
		AvmAssert(cur->name == NULL);

		// New table entry for this <name,ns> pair
		size++;
		//quads[i].name = name;
		WBRC(gc, quadbase, &cur->name, name);
		//quads[i].ns = ns;
		WBRC(gc, quadbase, &cur->ns, ns);
		cur->multiNS = multiNS;

write_value:
		//quads[i].value = value;
		WB(gc, quadbase, &cur->value, value);
		cur->apis |= ns->getAPI();
	}

	Binding MultinameHashtable::get(Stringp name, Namespacep ns) const
	{
		AvmAssert(ns->getURI()->isInterned());
		const Quad* t = m_quads;
		int i = find(name, ns, t, numQuads);
		if (t[i].name == name)
		{
			const Quad& tf = t[i];
			AvmAssert(tf.ns==ns || matchNS(tf.ns->m_uri, tf.apis, ns));
			return tf.value;
		}
		return BIND_NONE;
	}

	Binding MultinameHashtable::getName(Stringp name) const
	{
		const Quad* t = m_quads;
		for (int i=0, n=numQuads; i < n; i++)
		{
			if (t[i].name == name)
			{
				const Quad& tf = t[i];

				return tf.value;
			}
		}
		return BIND_NONE;
	}

	void MultinameHashtable::rehash(const Quad* oldAtoms, int oldTriplet, Quad* newAtoms, int newTriplet)
	{
		for (int i=0, n=oldTriplet; i < n; i++)
		{
			Stringp oldName;
			if ((oldName=oldAtoms[i].name) != EMPTY)
			{
				// inlined & simplified version of put()
				int j = find(oldName, oldAtoms[i].ns, newAtoms, newTriplet);
				// don't need WBRC/WB here because we are just moving pointers
				newAtoms[j].name = oldName;
				newAtoms[j].ns = oldAtoms[i].ns;
				newAtoms[j].value = oldAtoms[i].value;
				newAtoms[j].multiNS = oldAtoms[i].multiNS;
				newAtoms[j].apis = oldAtoms[i].apis;
			}
		}
	}

	// call this method using the previous value returned
	// by this method starting with 0, until 0 is returned.
	int FASTCALL MultinameHashtable::next(int index) const
	{
		// Advance to first non-empty slot.
		const Quad* t = m_quads;
		while (index < numQuads) {
			if (t[index++].name != NULL) {
				return index;
			}
		}
		return 0;
	}	
}

