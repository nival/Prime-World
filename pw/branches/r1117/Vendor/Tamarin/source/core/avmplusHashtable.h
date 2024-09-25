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

#ifndef __avmplus_Hashtable__
#define __avmplus_Hashtable__


namespace avmplus
{
	/**
	 * common base class for hashtable-like objects.
	 */
	// NOTE NOTE NOTE NOTE
	// NOTE NOTE NOTE NOTE
	// NOTE NOTE NOTE NOTE
	// NOTE NOTE NOTE NOTE
	//
	// InlineHashtable is designed to never have its ctors or dtors called directly; it can't be allocated
	// either on the stack or the heap. For a standalong heap allocation, use HeapHashtable instead.
	//
	// The reason for this oddity is that InlineHashtable can be grafted "inline" to a ScriptObject, and
	// will be manually initialized and destroyed (but not via its ctor/dtor). We also don't want
	// to descend from any class that might force us to have a vtable (eg by way of a virtual dtor) because
	// we neither need one nor want to account for the extra pointer-sized space in every instance of ScriptObject.
	// (It's not large, but it adds up...)
	//
	// NOTE NOTE NOTE NOTE
	// NOTE NOTE NOTE NOTE
	// NOTE NOTE NOTE NOTE
	// NOTE NOTE NOTE NOTE
	class InlineHashtable
	{
	private:
		friend class HeapHashtable;
		friend class HeapHashtableRC;
		friend class WeakKeyHashtable;
		friend class WeakValueHashtable;
		
		inline InlineHashtable() : m_atomsAndFlags(0), m_size(0), m_logCapacity(0)
		{
			// nothing, here only for HeapHashtable, which explicitly calls initialize()
		}

		// do NOT make this virtual; we want InlineHashtable to NOT have ANY virtual methods, not even a dtor
		inline ~InlineHashtable()
		{
			// nothing, here only for HeapHashtable, which explicitly calls destroy()
		}

	public:
		/**
		 * since identifiers are always interned strings, they can't be 0,
		 * so we can use 0 as the empty value.
		 */
		const static Atom EMPTY = 0;

		/** DELETED is stored as the key for deleted items */
		const static Atom DELETED = undefinedAtom;

		/** kDefaultCapacity must be a power of 2 */
		const static int kDefaultCapacity = 2;

		uint32_t getSize() const { return m_size; }
		uint32_t getCapacity() const { return m_logCapacity ? 1UL<<(m_logCapacity-1) : 0; }

		uintptr_t hasDontEnumSupport() const { return (m_atomsAndFlags & kDontEnumBit); }
		void setDontEnumSupport() { m_atomsAndFlags |= kDontEnumBit; }
		//void clrDontEnumSupport() { m_atomsAndFlags &= ~kDontEnumBit; }	// never currently called.
		Atom removeDontEnumMask(Atom a) const { return Atom(uintptr_t(a) & ~(m_atomsAndFlags & kDontEnumBit)); }
		bool enumerable(Atom a) const { return a != EMPTY && a != DELETED && !(uintptr_t(a) & (m_atomsAndFlags & kDontEnumBit)); }
		
		bool getAtomPropertyIsEnumerable(Atom name) const;
		void setAtomPropertyIsEnumerable(Atom name, bool enumerable);

#ifdef DEBUGGER
		inline uint64 size() const
		{
			return m_size * 2 * sizeof(Atom);
		}
#endif

	private:
		// kDontEnumBit is or'd into atoms to indicate that the property is {DontEnum},
		// and ALSO or'd into m_atomsAndFlags to indicate that the InlineHashtable as a whole supports DontEnum.
		static const uintptr_t kDontEnumBit		= 0x01;
		// kHasDeletedItems is or'd into m_atomsAndFlags (but not individual atoms) 
		static const uintptr_t kHasDeletedItems	= 0x02;

		static const uintptr_t kAtomFlags			= (kDontEnumBit | kHasDeletedItems);

		uintptr_t hasDeletedItems() const { return (m_atomsAndFlags & kHasDeletedItems); }

		void setCapacity(uint32_t cap)
		{
			m_logCapacity = cap ? (FindOneBit(cap)+1) : 0;
			AvmAssert(getCapacity() == cap);
		}

#if defined(AVMPLUS_IA32) || defined(AVMPLUS_AMD64)
		static inline uint32_t FindOneBit(uint32_t value)
		{

#ifndef __GNUC__
			#if defined(_MSC_VER) && defined(AVMPLUS_64BIT)
			unsigned long index;
			_BitScanReverse(&index, value);
			return (uint32)index;
			#elif defined(__SUNPRO_C)||defined(__SUNPRO_CC)
			for (int i=0; i < 32; i++)
				if (value & (1<<i))
					return i;
			// asm versions of this function are undefined if no bits are set
			AvmAssert(false);
			return 0;
			#else
  			_asm
  			{
  				bsr eax,[value];
  			}
			#endif
#else
			// DBC - This gets rid of a compiler warning and matchs PPC results where value = 0
			register int	result = ~0;
			
			if (value)
			{
				asm (
					"bsr %1, %0"
					: "=r" (result)
					: "m"(value)
					);
			}
			return result;
#endif
		}
	#elif defined(AVMPLUS_PPC)

		static inline int FindOneBit(uint32 value)
		{
			register int index;
			#ifdef __GNUC__
			asm ("cntlzw %0,%1" : "=r" (index) : "r" (value));
			#else
			register uint32 in = value;
			asm { cntlzw index, in; }
			#endif
			return 31-index;
		}

		#else // generic platform

		static int FindOneBit(uint32 value)
		{
			for (int i=0; i < 32; i++)
				if (value & (1<<i))
					return i;
			// asm versions of this function are undefined if no bits are set
			AvmAssert(false);
			return 0;
		}

#endif
		
		void setAtoms(Atom* atoms);

	public:

		Atom* getAtoms() { return (Atom*)(m_atomsAndFlags & ~kAtomFlags); }
		const Atom* getAtoms() const { return (const Atom*)(m_atomsAndFlags & ~kAtomFlags); }
	
		void destroy(); 

		void reset()
		{
			MMgc::GC* gc = MMgc::GC::GetGC(getAtoms());
			destroy();
			initialize(gc);
		}
		
		void initialize(MMgc::GC *gc, int capacity = kDefaultCapacity);

		/* See CPP for load factor variants. */
		bool isFull() const;
		
		/**
		 * @name operations on name/value pairs
		 */
		/*@{*/
		Atom get(Atom name) const;
		Atom remove(Atom name);

		bool contains(Atom name) const
		{
			const Atom* atoms = getAtoms();
			return removeDontEnumMask(atoms[find(name, atoms, getCapacity())]) == name;
		}
		/*@}*/

		/**
		 * Finds the hash bucket corresponding to the key x
		 * in the hash table starting at t, containing tLen
		 * atoms.
		 *
		 * This is a quadratic probe, but we only hit even-numbered
		 * slots since those hold keys.
		 */
		int find(Atom x, const Atom *t, uint32_t tLen) const;
		int find(Stringp x, const Atom *t, uint32_t tLen) const;
		int find(Atom x) const { return find(x, getAtoms(), getCapacity()); }

		/**
		 * Adds a name/value pair to a hash table.  Automatically
		 * grows the hash table if it is full.
		 */
		void add(Atom name, Atom value);

		/**
		 * Called to grow the InlineHashtable, particularly by add.
		 *
		 * - Calculates the needed size for the new InlineHashtable
		 *   (typically 2X the current size)
		 * - Creates a new array of Atoms
		 * - Rehashes the current table into the new one
		 * - Deletes the old array of Atoms and sets the Atom
		 *   pointer to our new array of Atoms
		 */
		bool grow();

		/**
		 * Allow caller to enumerate all entries in the table.
		 */
		int next(int index);
		Atom keyAt(int index);
		Atom valueAt(int index);
		//void removeAt(int index);

		void setHasDeletedItems() { m_atomsAndFlags |= kHasDeletedItems; }
		void clrHasDeletedItems() { m_atomsAndFlags &= ~kHasDeletedItems; }

	private:
		void put(Atom name, Atom value);
		int rehash(const Atom *oldAtoms, int oldlen, Atom *newAtoms, int newlen) const;

	private:
		//
		// "capacity" is the total number of atoms we allocate.
		// we use that capacity as name-value pairs, thus the maximum size at any time is always half the capacity.
		// for 32-bit builds, we want to limit the maximum number of entries to (1<<27)-1,
		// thus we the max capacity we need is (1<<28)-2. but since capacity is always limited
		// to a power of two, we'll actually limit capacity to 1<<27... which in turn will limit
		// maximum number of entries to (1<<26)-1. this has the downside of halving our maximum size,
		// but the upside of avoiding the need to check m_size for overflow on every put (we only
		// need to check capacity for overflow on every grow).
		//
		// (note: for consistency between 32 and 64-bit builds, we'll artificially limit 64-bit systems
		// to the same size, even though the m_size field can hold more.)
		//
		// How does this compare with pre-existing behavior on 32-bit systems?
		// theoretically, capacity could have been an allocation of 1<<32 == 4GB max (it's always a power of two)...
		// but some memory is of course used for other purposes, thus effectively 2GB max.
		// divide by sizeof(Atom) == 4 to find we had an actual max-capacity of 1<<29 entries.
		// So it is mathematically possible that a hashtable that was previously possible 
		// will now prematurely run out of memory... but extraordinarily unlikely.
		//
		// (In practice, Win32 limits each process to 2GB, so we can halve the above for those systems,
		// thus "portable" ABC/SWF code could only rely on a max capacity of 1<<28 entries.)
		// 
		// 
		static const uint32_t MAX_CAPACITY = (1UL<<27);

	// ------------------------ DATA SECTION BEGIN
	private:
		uintptr_t m_atomsAndFlags;	/** property hashtable, this has no DWB on purpose, setAtoms contains the WB */
	#ifdef AVMPLUS_64BIT
		// on 64-bit systems, padding will force us to 16 bytes here anyway, so let's just use unpacked ints
		uint32_t m_size;			// number of properties
		uint32_t m_logCapacity;		// (log2 of capacity) + 1
	#else
		uint32_t m_size:27;			// number of properties 
		uint32_t m_logCapacity:5;	// (log2 of capacity) + 1 -- gives us enough space for 2^32 entries
	#endif
	// ------------------------ DATA SECTION END
	};

	class HeapHashtable : public MMgc::GCFinalizedObject
	{
	protected:
		InlineHashtable ht;

	public:
		/**
		 * initialize with a known capacity.  i.e. we can fit minSize
		 * elements in without rehashing.
		 * @param heap
		 * @param capacity  # of logical slots
		 */
		HeapHashtable(MMgc::GC* gc, int32_t capacity = InlineHashtable::kDefaultCapacity)
		{ 
			ht.initialize(gc, capacity); 
		}
		virtual ~HeapHashtable() { ht.destroy(); }
		inline InlineHashtable* get_ht() { return &ht; }

		inline void reset() { ht.reset(); }
		inline uint32_t getCapacity() const { return ht.getCapacity(); }
		inline uint32_t getSize() const { return ht.getSize(); }
		inline int next(int index) { return ht.next(index); }
		inline Atom keyAt(int index) { return ht.keyAt(index); }
		inline Atom valueAt(int index) { return ht.valueAt(index); }
		virtual void add(Atom name, Atom value) { ht.add(name, value); }
		virtual Atom get(Atom name) { return ht.get(name); }
		virtual Atom remove(Atom name) { return ht.remove(name); }
		virtual bool contains(Atom name) const { return ht.contains(name); }
		virtual bool weakKeys() const { return false; }
		virtual bool weakValues() const { return false; }
	};

	// Holds RCObject values, not Atom values.  Otherwise like HeapHashtable.
	class HeapHashtableRC : public MMgc::GCFinalizedObject
	{
	private:
		InlineHashtable ht;
		
	public:
		HeapHashtableRC(MMgc::GC* gc, int32_t capacity = InlineHashtable::kDefaultCapacity)
		{ 
			ht.initialize(gc, capacity); 
		}
		virtual ~HeapHashtableRC() { ht.destroy(); }
	
		inline void reset() { ht.reset(); }
		inline uint32_t getCapacity() const { return ht.getCapacity(); }
		inline uint32_t getSize() const { return ht.getSize(); }
		inline int next(int index) { return ht.next(index); }
		inline Atom keyAt(int index) { return ht.keyAt(index); }
		inline MMgc::RCObject* valueAt(int index) { return untagAtom(ht.valueAt(index)); }
		void add(Atom name, MMgc::RCObject* value) { ht.add(name, tagObject(value)); }
		MMgc::RCObject* get(Atom name) { return untagAtom(ht.get(name)); }
		MMgc::RCObject* remove(Atom name) { return untagAtom(ht.remove(name)); }
		bool contains(Atom name) const { return ht.contains(name); }
		
	private:
		inline Atom tagObject(MMgc::RCObject* obj) { return (Atom)obj | kObjectType; }
		inline MMgc::RCObject* untagAtom(Atom a) { return (MMgc::RCObject*)atomPtr(a); }
	};

	/** 
	 * If key is an object weak ref's are used
	 */
	class WeakKeyHashtable : public HeapHashtable
	{
	public:
		WeakKeyHashtable(MMgc::GC* _gc) : HeapHashtable(_gc) { }
		virtual void add(Atom key, Atom value);
		virtual Atom get(Atom key) { return ht.get(getKey(key)); }
		virtual Atom remove(Atom key) { return ht.remove(getKey(key)); }
		virtual bool contains(Atom key) const { return ht.contains(getKey(key)); }
		virtual bool weakKeys() const { return true; }
	private:
		Atom getKey(Atom key) const;
		void prune();
	};	

	/** 
	 * If value is an object weak ref's are used
	 */
	class WeakValueHashtable : public HeapHashtable
	{
	public:
		WeakValueHashtable(MMgc::GC* _gc) : HeapHashtable(_gc) { }
		virtual void add(Atom key, Atom value);
		virtual Atom get(Atom key) { return getValue(key, ht.get(key)); }
		virtual Atom remove(Atom key) { return getValue(key, ht.remove(key)); }
		virtual bool weakValues() const { return true; }
	private:
		Atom getValue(Atom key, Atom value);
		void prune();
	};	
}

#endif /* __avmplus_Hashtable__ */
