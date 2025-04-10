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

using namespace MMgc;

// WARNING:
// WARNING:
// WARNING:
// Never do "MMgc::GC::GetGC(this)" in the HashTable object.  It is dynamically
// placed at the end of a ScriptObject following traits data which can extend
// greater than 4k off the starting pointer.  This will cause GetGC(this) to fail.
// WARNING:
// WARNING:
// WARNING:

namespace avmplus
{	
	void InlineHashtable::initialize(GC *gc, int capacity)
	{
		MMGC_STATIC_ASSERT(sizeof(InlineHashtable) == (sizeof(void*) * 2));

		capacity = MathUtils::nextPowerOfTwo(capacity);
		setCapacity(capacity*2);
		AvmAssert(getCapacity());
		MMGC_MEM_TYPE(gc->FindBeginningGuarded(this));
		setAtoms((Atom *)gc->Calloc(getCapacity(), sizeof(Atom), GC::kContainsPointers|GC::kZero));
	}

	void InlineHashtable::destroy()
	{
		Atom* atoms = getAtoms();
		if(atoms) {
			GC *gc = GC::GetGC(atoms);
			AvmCore::decrementAtomRegion(atoms, getCapacity());
			gc->Free (atoms);
		}
		m_atomsAndFlags = 0;
		m_size = 0;
		m_logCapacity = 0;
	}

	void InlineHashtable::setAtoms(Atom *newAtoms)
	{
		GC *gc = GC::GetGC(newAtoms);
		uintptr_t newVal = uintptr_t(newAtoms) | (m_atomsAndFlags & kAtomFlags);
		WB(gc, gc->FindBeginningFast(this), &m_atomsAndFlags, (void*)newVal);
	}

	void InlineHashtable::put(Atom name, Atom value)
	{
		Atom* atoms = getAtoms();
		int i = find(name, atoms, getCapacity());
		GC *gc = GC::GetGC(atoms);
		if (removeDontEnumMask(atoms[i]) != name) {
			AvmAssert(!isFull());			
			//atoms[i] = name;
			WBATOM(gc, atoms, &atoms[i], name);
			m_size++;
		}
		//atoms[i+1] = value;
		WBATOM( gc, atoms, &atoms[i+1], value);
	}

    Atom InlineHashtable::get(Atom name) const
    {
		int i;
		const Atom* atoms = getAtoms();
		return atoms[i = find(name, atoms, getCapacity())] == name ? atoms[i+1] : undefinedAtom;
    }

	int InlineHashtable::find(Stringp x, const Atom *t, uint32_t tLen) const
	{
		AvmAssert(x != NULL);
		return find(x->atom(), t, tLen);
	}

	int InlineHashtable::find(Atom x, const Atom *t, uint32_t m) const
	{
		uintptr_t mask = ~(m_atomsAndFlags & kDontEnumBit);
		x &= mask;
		
		#if 0 // debug code to print out the strings we're searching for
		static int debug =0;
		if (debug && AvmCore::isString(x))
		{
			Stringp s = AvmCore::atomToString(x);
			AvmDebugMsg (s->c_str(), false);
			AvmDebugMsg ("\n", false);
		}
		#endif

		uintptr_t bitmask = (m - 1) & ~0x1;

		AvmAssert(x != EMPTY && x != DELETED);
        // this is a quadratic probe but we only hit even numbered slots since those hold keys.
        int n = 7 << 1;
		#ifdef _DEBUG
		uint32_t loopCount = 0;
		#endif
		// Note: Mask off MSB to avoid negative indices.  Mask off bottom
		// 3 bits because it doesn't contribute to hash.  Double it
		// because names, values stored adjacently.
        uint32_t i = ((0x7FFFFFF8 & x)>>2) & bitmask;  
        Atom k;
        while ((k=t[i]&mask) != x && k != EMPTY)
		{
			i = (i + (n += 2)) & bitmask;		// quadratic probe
			AvmAssert(loopCount++ < m);			// don't scan forever
		}
		AvmAssert(i <= ((m-1)&~0x1));
        return i;
	}
		
	Atom InlineHashtable::remove(Atom name)
	{
		Atom* atoms = getAtoms();
        int i = find(name, atoms, getCapacity());
		Atom val = undefinedAtom;
        if (removeDontEnumMask(atoms[i]) == name)
        {
			val = atoms[i+1];
            // decrement refcount as necessary.
            AvmCore::atomWriteBarrier_dtor(&atoms[i]);
            AvmCore::atomWriteBarrier_dtor(&atoms[i+1]);
            // calls above set the slot to 0, we want DELETED
            atoms[i] = DELETED;
			atoms[i+1] = DELETED;
			setHasDeletedItems();
        }
		return val;
	}

    int InlineHashtable::rehash(const Atom *oldAtoms, int oldlen, Atom *newAtoms, int newlen) const
    {
		int newSize = 0;
        for (int i=0, n=oldlen; i < n; i += 2)
        {
            Atom oldAtom;
            if ((oldAtom=oldAtoms[i]) != EMPTY && oldAtom != DELETED)
            {
                // inlined & simplified version of put()
                int j = find(oldAtom, newAtoms, newlen);
                newAtoms[j] = oldAtom;
                newAtoms[j+1] = oldAtoms[i+1];
				newSize++;
			}
        }

		return newSize;
    }

	/**
		* load factor is 0.75 so we're full if size >= M*0.75
		* where M = atoms.length/2<br>
        *     size >= M*3/4<br>
        *     4*size >= 3*M<br>
        *     4*size >= 3*atoms.length/2<br>
        *     8*size >= 3*atoms.length<br>
        *     size<<3 >= 3*atoms.length
		*/
	/**
		* load factor is 0.9 so we're full if size >= M*0.9
		* where M = atoms.length/2<br>
        *     size >= M*9/10<br>
        *     10*size >= 9*M<br>
        *     10*size >= 9*atoms.length/2<br>
        *     20*size >= 9*atoms.length<br>
		*/
	bool InlineHashtable::isFull() const 
	{ 
		// This seems to work very well and the Intel compiler converts both the multiplies
		// into shift+add operations.
		return uint32_t((5*(m_size+1))) >= uint32_t(2*getCapacity()); // 0.80
		#if 0
		//return ((size<<3)+1) >= 3*getCapacity(); // 0.75
		//return ((40*size)+1) >= 19*getCapacity(); // 0.95
		//return ((40*size)+1) >= 18*getCapacity(); // 0.90
		//return ((40*size)+1) >= 17*getCapacity(); // 0.85
		//return ((40*size)+1) >= 15*getCapacity(); // 0.75
		//Edwins suggestion - if (size > max - max>>N)) grow  (N = 5, 4, 3, 2)
		//#define SHIFTFACTOR 4
		//NOT CORRECT
		//return ( ( size << SHIFTFACTOR ) + size > (getCapacity() << (SHIFTFACTOR-1)) );
		#endif
	}

	void InlineHashtable::add(Atom name, Atom value)
	{
		if (isFull())
		{
			if (!grow())
				return;
		}
		put(name, value);
	}

	bool InlineHashtable::grow()
	{
		// grow the table by 2N+1
		//     new = 2*old+1 ; old == o.atoms.length/2
		//         = 2*(o.atoms.length/2)+1
		//         = o.atoms.length + 1
		// If we have deleted slots, we don't grow our HT because our rehash will clear
		// out spots for us. 
		const uint32_t oldCapacity = getCapacity();
		const uint32_t newCapacity = hasDeletedItems() ? oldCapacity : MathUtils::nextPowerOfTwo(oldCapacity+1);
		if (newCapacity > MAX_CAPACITY)
		{
			AvmAssert(!"InlineHashtable::grow attempted to grow to %d capacity, rejecting\n");
			return false;
		}
		const Atom* atoms = getAtoms();
		GC* gc = GC::GetGC(atoms);
		MMGC_MEM_TYPE(gc->FindBeginningGuarded(this));
		Atom* newAtoms = (Atom*)gc->Calloc(newCapacity, sizeof(Atom), GC::kContainsPointers|GC::kZero);
		m_size = rehash(atoms, oldCapacity, newAtoms, newCapacity);
		gc->Free(atoms);
		setAtoms(newAtoms);
		setCapacity(newCapacity);
		clrHasDeletedItems();
		return true;
	}

	Atom InlineHashtable::keyAt(int index)
	{
		const Atom* atoms = getAtoms();
		return atoms[(index-1)<<1];
	}

	Atom InlineHashtable::valueAt(int index)
	{
		const Atom* atoms = getAtoms();
		return atoms[((index-1)<<1)+1];
	}

/*	void InlineHashtable::removeAt(int index)
	{
		int i = (index-1)<<1;
        atoms[i] = DELETED;
		atoms[i+1] = DELETED;
		setHasDeletedItems(true);
	}*/

	// call this method using the previous value returned
	// by this method starting with 0, until 0 is returned.
	int InlineHashtable::next(int index)
	{
		if (index != 0) {
			index = index<<1;
		}
		// Advance to first non-empty slot.
		const Atom* atoms = getAtoms();
		int cap = getCapacity();
		while (index < cap) {
			if (enumerable(atoms[index])) {
				return (index>>1)+1;
			}
			index += 2;
		}
		return 0;
	}

	bool InlineHashtable::getAtomPropertyIsEnumerable(Atom name) const
	{
		if (hasDontEnumSupport())
		{
			const Atom* atoms = getAtoms();
			int i = find(name, atoms, getCapacity());
			if (Atom(atoms[i]&~kDontEnumBit) == name)
			{
				return (atoms[i]&kDontEnumBit) == 0;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return contains(name);
		}
	}

	void InlineHashtable::setAtomPropertyIsEnumerable(Atom name, bool enumerable)
	{
		if (hasDontEnumSupport())
		{
			Atom* atoms = getAtoms();
			int i = find(name, atoms, getCapacity());
			if (Atom(atoms[i]&~kDontEnumBit) == name)
			{
				atoms[i] = (atoms[i]&~kDontEnumBit) | (enumerable ? 0 : kDontEnumBit);
			}
		}
	}
	
	Atom WeakKeyHashtable::getKey(Atom key) const
	{
		// this gets a weak ref number, ie double keys, okay I guess
		if(AvmCore::isPointer(key)) {
			// Don't know if key is GCObject or GCFinalizedObject so can't go via the
			// GetWeakRef methods on those classes; go directly to GC
			GCWeakRef *weakRef = GC::GetWeakRef(atomPtr(key));
			key = AvmCore::genericObjectToAtom(weakRef);
		}
		return key;
	}

	void WeakKeyHashtable::add(Atom key, Atom value)
	{
		if (ht.isFull()) {
			prune();
			if (!ht.grow())
				return;
		}
		ht.put(getKey(key), value);
	}

	void WeakKeyHashtable::prune()
	{
		Atom* atoms = ht.getAtoms();
		for(int i=0, n=ht.getCapacity(); i<n; i+=2) {
			if(AvmCore::isGenericObject(atoms[i])) {
				GCWeakRef *ref = (GCWeakRef*)AvmCore::atomToGenericObject(atoms[i]);
				if(ref && ref->get() == NULL) {
                    // decrement refcount as necessary.
                    AvmCore::atomWriteBarrier_dtor(&atoms[i]);
                    AvmCore::atomWriteBarrier_dtor(&atoms[i+1]);
					// inlined delete
					atoms[i] = InlineHashtable::DELETED;
					atoms[i+1] = InlineHashtable::DELETED;
					ht.setHasDeletedItems();
				}
			}
		}
	}
	
	Atom WeakValueHashtable::getValue(Atom key, Atom value)
	{
		if(AvmCore::isGenericObject(value)) {
			GCWeakRef *wr = (GCWeakRef*)AvmCore::atomToGenericObject(value);
			if(wr->get() != NULL) {
				// note wr could be a pointer to a double, that's what this is for
				Atom* atoms = ht.getAtoms();
				if(GC::GetGC(atoms)->IsRCObject(wr->get())) {
					union {
						GCObject* o;
						AvmPlusScriptableObject* so;
					};
					o = wr->get();
					value = so->toAtom();
				} else {
					AvmAssert(false);
				}
			} else {
				remove(key);
				value = undefinedAtom;
			}
		}
		return value;
	}

	void WeakValueHashtable::add(Atom key, Atom value)
	{
		if (ht.isFull()) {
			prune();
			if (!ht.grow())
				return;
		}
		if(AvmCore::isPointer(value)) {
			// Don't know if value is GCObject or GCFinalizedObject so can't go via the
			// GetWeakRef methods on those classes; go directly to GC
			GCWeakRef *wf = GC::GetWeakRef(atomPtr(value));
			value = AvmCore::genericObjectToAtom(wf);
		}
		ht.put(key, value);
	}

	void WeakValueHashtable::prune()
	{
		Atom* atoms = ht.getAtoms();
		for(int i=0, n=ht.getCapacity(); i<n; i+=2) {
			if(AvmCore::isPointer(atoms[i+1])) {
				GCWeakRef *ref = (GCWeakRef*)atomPtr(atoms[i+1]);
				if(ref && ref->get() == NULL) {
					// inlined delete
					atoms[i] = InlineHashtable::DELETED;
					atoms[i+1] = InlineHashtable::DELETED;
					ht.setHasDeletedItems();
				}
			}
		}
	}
}
