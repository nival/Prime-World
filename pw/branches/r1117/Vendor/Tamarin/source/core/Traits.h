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

#ifndef __avmplus_Traits__
#define __avmplus_Traits__


namespace avmplus
{
	// Note: we rely on being able to store this in 3 bits. 
	enum TraitsPosType
	{
		TRAITSTYPE_INSTANCE					= 0,	// instance info in abc (non-interface)
		TRAITSTYPE_CLASS					= 1,	// class info in abc
		TRAITSTYPE_SCRIPT					= 2,	// script info in abc
		TRAITSTYPE_CATCH					= 3,	// synthetic catch type
		TRAITSTYPE_ACTIVATION				= 4,	// activation info from abc
		TRAITSTYPE_NVA						= 5,	// null/void/any -- traitsPos will always be null
		TRAITSTYPE_RT						= 6,	// Traits defined at runtime, e.g. instantiated parameterized types
		TRAITSTYPE_INTERFACE				= 7		// instance info in abc (interface)
	};
	
	const uint32_t NOT_DERIVED_OR_XML_MASK = 
// commented out, why?
//		(1<<BUILTIN_array) |
//		(1<<BUILTIN_date) |
//		(1<<BUILTIN_regexp) |
		(1<<BUILTIN_boolean) |
		(1<<BUILTIN_class) |
		(1<<BUILTIN_function) |
		(1<<BUILTIN_int) |
		(1<<BUILTIN_methodClosure) |
		(1<<BUILTIN_namespace) |
		(1<<BUILTIN_null) |
		(1<<BUILTIN_number) |
		(1<<BUILTIN_object) |
		(1<<BUILTIN_qName) |
		(1<<BUILTIN_string) |
		(1<<BUILTIN_uint) |
		(1<<BUILTIN_void) |
		(1<<BUILTIN_xmlList) |
		(1<<BUILTIN_xml);

	const uint32_t MACHINE_TYPE_MASK = (1<<BUILTIN_object) | (1<<BUILTIN_void) | (1<<BUILTIN_int) | (1<<BUILTIN_uint) | (1<<BUILTIN_boolean) | (1<<BUILTIN_number);
	const uint32_t NUMERIC_TYPE_MASK = (1<<BUILTIN_int) | (1<<BUILTIN_uint) | (1<<BUILTIN_number);
	const uint32_t XML_TYPE_MASK = (1<<BUILTIN_xml) | (1<<BUILTIN_xmlList);
#ifdef VMCFG_AOT
    const uint32_t SSTOBJECT_TYPE_MASK = ~ ((1<<BUILTIN_int) | (1<<BUILTIN_uint) | (1<<BUILTIN_number) | (1<<BUILTIN_boolean) | (1<<BUILTIN_any) | (1<<BUILTIN_object) | (1<<BUILTIN_string) | (1<<BUILTIN_namespace));
    const uint32_t SSTATOM_TYPE_MASK = (1<<BUILTIN_object) | (1<<BUILTIN_any);
#endif

	typedef const uint8_t* TraitsPosPtr;

	// Note: we rely on this being <= 8 entries.
	enum SlotStorageType
	{
		// we rely on these 4 being first, so we can do <= SST_scriptobject in isAtomOrRCObjectSlot.
		// SST_atom is most frequently encountered, so value of zero is best
		SST_atom,
		SST_string,
		SST_namespace,
		SST_scriptobject,
		
		SST_int32,
		SST_uint32,
		SST_bool32,
		SST_double
	};
	bool isAtomOrRCObjectSlot(SlotStorageType sst);
	
	class TraitsBindings : public QCachedItem
	{
		friend class Traits;
		friend class StTraitsBindingsIterator;
	
	private:
		struct SlotInfo
		{
			Traitsp type;	
			uint32_t offsetAndSST;	// lower 3 bits: SlotStorageType, upper 29 bits: offset div 4
			#ifdef AVMPLUS_64BIT
			uint32_t padding;	// alignment to power-of-two boundary is a Good Thing here
			#endif
			SlotStorageType sst() const;	// get just the storage type of this slot
			uint32_t offset() const;		// get just the offset of this slot
		};

		struct BindingMethodInfo
		{
			MethodInfo* f;
		};
		
	private:
		TraitsBindings(Traits* _owner, 
							TraitsBindingsp _base, 
							MultinameHashtable* _bindings,
							uint32_t _slotCount, 
							uint32_t _methodCount);

	public:
		static const uint32_t MAX_SLOT_OFFSET = (1U << 31) - 1;

	public:
		
		static TraitsBindings* alloc(MMgc::GC* gc, Traits* _owner, TraitsBindingsp _base, MultinameHashtable* _bindings, uint32_t slotCount, uint32_t methodCount);

		void buildSlotDestroyInfo(MMgc::GC* gc, FixedBitSet& slotDestroyInfo, uint32_t slotAreaCount, uint32_t sizeOfSlotArea) const;

		Traitsp getSlotTraits(uint32_t i) const;
		uint32_t getSlotOffset(uint32_t i) const;
		// if you need SST you probably want offset too
		SlotStorageType calcSlotAddrAndSST(uint32_t i, void* pin, void*& pout) const;
		MethodInfo* getMethod(uint32_t i) const;
		Binding findBinding(Stringp key) const;
		Binding findBinding(Stringp name, Namespacep ns) const;
		Binding findBinding(Stringp name, NamespaceSetp nsset) const;
		Binding findBindingAndDeclarer(const Multiname& mn, Traitsp& declarer) const;

		// note: if you are just doing a single iteration thru a single TraitsBindings,
		// it's more efficient (and easier) to use StTraitsBindingsIterator instead.
		int32_t next(int32_t index) const;
		Stringp keyAt(int32_t index) const;
		Namespacep nsAt(int32_t index) const;
		Binding valueAt(int32_t index) const;

	private:
		SlotInfo* getSlots();
		const SlotInfo* getSlots() const;

		BindingMethodInfo* getMethods();
		const BindingMethodInfo* getMethods() const;

		void setSlotInfo(uint32_t i, Traits* t, SlotStorageType sst, uint32_t offset);

		void setMethodInfo(uint32_t i, MethodInfo* f);

		bool checkOverride(AvmCore* core, MethodInfo* virt, MethodInfo* over) const;
		bool checkLegalInterfaces(AvmCore* core) const;
		void fixOneInterfaceBindings(Traitsp ifc);

	// ------------------------ DATA SECTION BEGIN
		public:		const Traitsp					owner;
		public:		const TraitsBindingsp			base; 
		private:	MultinameHashtable* const		m_bindings;
		private:    Traits**						m_interfaces;
		public:		const uint32_t					slotCount;			// including slots in our base classes
		public:		const uint32_t					methodCount;		// including methods in our base classes
		private:	uint32_t						m_slotSize;			// size of slot area in bytes, including base classes
		// plus extra at end
	// ------------------------ DATA SECTION END

	};

	// NOTE: caller must check for null key, eg,
	//
	//		StTraitsBindingsIterator iter(mnht);
	//		while (iter.next()) {
	//			if (!iter.key()) continue;
	//			.. rest of loop ..
	//		}
	//
	class StTraitsBindingsIterator : public StMNHTIterator
	{
	private:
		TraitsBindingsp const volatile _tb;	// kept just to ensure it doesn't get collected -- must be volatile!
	public:
		StTraitsBindingsIterator(TraitsBindingsp tb);
	};

	class TraitsMetadata : public QCachedItem
	{
		friend class Traits;

	public:
		typedef const uint8_t* MetadataPtr;

	private:
		TraitsMetadata(TraitsMetadatap _base, PoolObject* _residingPool, MetadataPtr _metadata_pos, uint32_t _slotCount, uint32_t _methodCount);

	public:
		MetadataPtr getMetadataPos(PoolObject*& residingPool) const;
		MetadataPtr getSlotMetadataPos(uint32_t i, PoolObject*& residingPool) const;
		MetadataPtr getMethodMetadataPos(uint32_t i, PoolObject*& residingPool) const;

	// ------------------------ DATA SECTION BEGIN
		public:		const TraitsMetadatap			base; 
		private:	PoolObject* const				residingPool;
		public:		const uint32_t					slotCount;			// including slots in our base classes
		public:		const uint32_t					methodCount;		// including methods in our base classes
		private:	MetadataPtr						metadataPos;
		private:	MetadataPtr*					slotMetadataPos;
		private:	MetadataPtr*					methodMetadataPos;
	// ------------------------ DATA SECTION END
	};

	typedef ClassClosure* (*CreateClassClosureProc)(VTable*);
	
	/**
	 * Traits objects describe the layout of objects.  Traits are
	 * used to describe a variety of things in the VM, such as
	 * classes, global objects, and activation objects.
	 *
	 * A Traits object contains a hash table with the names of
	 * all properties and methods.  Each name maps to a binding.
	 *
	 * There are several types of binding: binding to a slot,
	 * binding to an accessor, binding to a virtual function,
	 * binding to a final function.
	 */
	class Traits : public MMgc::GCObject 
	{
		friend class TraitsBindings;	// for m_sizeofInstance
		friend class InterfaceIterator;
		#if defined FEATURE_NANOJIT
		friend class CodegenLIR;
		#endif

	public:
        
		uint16_t getSizeOfInstance() const;
		uint32_t getTotalSize() const;		
		uint32_t getHashtableOffset() const;

		// in bytes. includes size for all base classes too.
		uint32_t getExtraSize() const;

		// sadly, it's still more efficient to stash this in Traits itself, as it's nontrivial to recover when
		// we rebuild the TraitMethodInfo. 
		void setMetadataPos(const byte* pos);

	private:
        
		// in bytes. size of the slots not included in the size of instance.  Includes size of slots for bases classes that are not native.
		uint32_t getSlotAreaSize() const;

		void computeSlotAreaCountAndSize(TraitsBindings* tb, uint32_t& slotCount, uint32_t& size) const; 
        
		uint32_t computeSlotAreaStart(uint32_t nPointerSlots, uint32_t n32BitNonPointerSlots, uint32_t n64BitNonPointerSlots) const;
		
		void buildBindings(TraitsBindingsp basetb, 
							MultinameHashtable* bindings, 
							uint32_t& slotCount, 
							uint32_t& methodCount,
							uint32_t& n32BitNonPointerSlots,
							uint32_t& n64BitNonPointerSlots,
							const Toplevel* toplevel) const;
		uint32_t finishSlotsAndMethods(TraitsBindingsp basetb, 
									TraitsBindings* tb, 
									const Toplevel* toplevel,
									AbcGen* abcGen,
									uint32_t n32BitNonPointerSlots,
									uint32_t n64BitNonPointerSlots) const;
		TraitsBindings* _buildTraitsBindings(const Toplevel* toplevel, AbcGen* abcGen);

		TraitsMetadata* _buildTraitsMetadata();

		TraitsPosPtr traitsPosStart() const;
		TraitsPosPtr skipToInstanceInitPos(TraitsPosPtr pos) const;
		Binding getOverride(TraitsBindingsp basetb, Namespacep ns, Stringp name, int tag, const Toplevel *toplevel) const;

		void addVersionedBindings(MultinameHashtable* bindings,
								  Stringp name,
								  NamespaceSetp compat_nss,
								  Binding binding) const;

	private:

		/**
		 * Constructor for traits.  base != NULL means inheritance.
		 */
		Traits(PoolObject* pool,
			   Traits* base,
			   uint16_t sizeofInstance,
			   uint16_t offsetofSlots,
			   TraitsPosPtr traitsPos,
			   TraitsPosType posType);

		Traits* _newParameterizedTraits(Stringp name, Namespacep ns, Traits* _base);

	public:
		/**
		 * traits with base traits (inheritance)
		 */
		static Traits* newTraits(PoolObject* pool,
			   Traits *base,
				uint16_t sizeofInstance,
				uint16_t offsetofSlots,
				TraitsPosPtr traitsPos,
				TraitsPosType posType);
		
		static Traits* newCatchTraits(const Toplevel* toplevel, PoolObject* pool, TraitsPosPtr traitsPos, Stringp name, Namespacep ns);
		Traits* newParameterizedITraits(Stringp name, Namespacep ns);
		Traits* newParameterizedCTraits(Stringp name, Namespacep ns);

	public:
		bool allowEarlyBinding() const;

	private:
		TraitsBindings* FASTCALL _getTraitsBindings();
		TraitsMetadata* FASTCALL _getTraitsMetadata();

	public:
		TraitsBindingsp getTraitsBindings();
		TraitsMetadatap getTraitsMetadata();
		bool containsInterface(Traitsp t); // legacy name
		bool subtypeof(Traitsp t);
		static Traits** allocSupertypeList(MMgc:: GC*, uint32_t size);

	private:
		void build_primary_supertypes();
		void build_secondary_supertypes();
		bool FASTCALL secondary_subtypeof(Traitsp t);	// slow path called by subtypeof()
		bool isPrimary() const;
		uint32_t countNewInterfaces(List<Traitsp, LIST_GCObjects>& seen);
		void resolveSignaturesSelf(const Toplevel* toplevel);

	public:
		void genDefaultValue(uint32_t value_index, uint32_t slot_id, const Toplevel* toplevel, Traits* slotType, CPoolKind kind, AbcGen& gen) const;
		void genInitBody(const Toplevel* toplevel, AbcGen& gen);
		
		void resolveSignatures(const Toplevel* toplevel);

#ifdef VMCFG_AOT
        void initActivationTraits(Toplevel *toplevel);
#endif

		// convenient wrapper to check for null (returns "BUILTIN_any")
		static BuiltinType getBuiltinType(const Traitsp t);

		bool notDerivedObjectOrXML() const;
		bool isMachineType() const;
		bool isNumeric() const;
		bool isXMLType() const;
		bool isInterface() const;		// true if this is an interface type
		bool isInstanceType() const;	// interface type or class instance type
#ifdef VMCFG_AOT
        // returns true, if the slot storage type for this traits is ScriptObject*.
        inline bool isSSTObject() const { return ((1<<builtinType) & SSTOBJECT_TYPE_MASK) != 0; }
        inline static bool isSSTAtom(Traits* t) { return ((1<<getBuiltinType(t)) & SSTATOM_TYPE_MASK) != 0; }
#endif

		TraitsPosType posType() const;
		bool isResolved() const;
		bool isActivationTraits() const;

		bool needsHashtable() const;
		void set_needsHashtable(bool v);

		static bool isMachineCompatible(const Traits* a, const Traits* b);

		void setCreateClassClosureProc(CreateClassClosureProc p);
		CreateClassClosureProc getCreateClassClosureProc() const;

		Stringp formatClassName();

		void destroyInstance(ScriptObject *obj) const;

	public:
#if VMCFG_METHOD_NAMES
		Stringp format(AvmCore* core, bool includeAllNamespaces = false) const;
#endif

		// call init_declaringScope for each method that we own. this should be
		// called exactly once per Traits, *after* the Traits has been resolved.
		void init_declaringScopes(const ScopeTypeChain* stc);
		
		Namespacep ns() const;
		Stringp name() const;
		void set_names(Namespacep p_ns, Stringp p_name);
		
		// this returns true iff we implement an interface that is not implemented by our parent.
		// essential for efficient building of IMT thunks.
		bool implementsNewInterfaces() const;

		// Data Structures for fast subtype checking (edwsmith 11/17/09):
		// subtypeof(S,T) is frequently used by the (often implicit) "is" and "coerce"
		// operators and therefore is critical to optimize.
		//
		// We have the following data structure in each Traits:
		//   * primary_supertypes: a fixed-sized array of the first several base classes
		//   * MAX_PRIMARY_SUPERTYPE: a tunable policy constant, currently 8 from testing
		//   * secondary_supertypes: a possibly shared null terminated array of any
		//     remaining base classes, plus all interfaces implemented by this Traits
		//   * supertype_cache: a one-entry positive-hit cache
		//   * supertype_neg_cache: a one-entry negative-hit cache
		//   * supertype_offset: if this traits is a shallowly-inherited class, holds
		//     the byte offset of this traits in any subclass's primary_supertypes array.
		//     otherwise, holds the byte offset of supertype_cache.
		//
		// secondary_supertypes is shared as follows:
		//   * if a class is primary with no interfaces, we share an empty-list singleton
		//   * if a class is primary and doesn't add interfaces, list is shared with base class.
		//   * if a class is a leaf class and doesn't add interfaces, we share the list between
		//     the non-leaf base class and each other non-interface-adding leaf subclass
		//
		// supertype_offset cleverly encodes whether the traits is "primary" and expected
		// to be in subclass's primary_supertypes list, or "secondary" and expected to be
		// in the secondary_supertypes list.  When it points to the cache, this type is
		// a secondary type.  Using this encoding allows step 1 (below) to be fast.
		//
		// primary_supertypes and secondary_supertypes are initialized in the Traits
		// constructor.  primary_supertypes is never modified.  secondary_supertypes can
		// be replaced once when a base class's list is shared by one or more leaf-subclasses.
		// (see build_primary_supertypes() and build_secondary_supertype()).
		//
		// In a large app with thousands of classes and hundreds of interfaces,
		// The combined memory of the shared secondary_supertypes lists is often
		// <1% of the overall traits memory.  The "big knob" affecting memory vs performance
		// is the MAX_PRIMARY_SUPERTYPE policy constant.
		//
		// the operation subtypeof(S,T) that tests whether S is a subtype of T is:
		//   1. if S[T.offset] == T, return true
		//   2. if T.offset != offsetof(supertype_cache), return false
		//   3. if S.supertype_neg_cache == T, return false
		//   4. if S == T, return true
		//   5. if T in S.secondary_supertypes, set S.supertype_cache == T and return true
		//   6. else, set S.supertype_neg_cache == T and return false.
		//
		// These tests are ordered by frequency based on empirical testing.
		//
		// step 1 combines the ordinary base-class test when T is primary with 
		// the cache-hit test when T is secondary.  Step 2 exits fast when T is primary.
		//
		// when T is a known primary class, steps 1 & 2 collapse into a simple
		// load and compare.
		// 
		// when T is a known interface or deeply inherited class, step 1 & 3 (both cache tests)
		// become two loads+compares and step 2 can be skipped.
		//
		// Step 4 allows us to omit "self" from secondary_supertypes, which allows more
		// sharing of that list.  Step 4 can be skipped when T is a known interface.
		// When T is final, only step 4 is needed; this is not common in practice but
		// worth noting for jit-compilation.
		//
		// supertype_neg_cache is a hidden pointer because when S is *not* a subtype of
		// T, then S and T are unrelated and we do not want the edge S->T to pin T in memory.
		// However, in subtype_cache, and primary/secondary_supertypes[], entries *are* all
		// supertypes of S and therefore the extra references do not uniquely pin T in memory.
		//
		// primary_supertypes[] does not have a write barrier because it is initialized in
		// the constructor before other memory is allocated, like base.
		// 
		// more ideas to optimize:
		// 
		// The final search in step 5 is a linear null terminated search and is used
		// well under 1% of the time in a range of apps tested.  If necessary it could
		// be further optimized by a) moving found items to the front; b) padding to 
		// the next power of two and using a quadradic probe; c) comparing several items
		// at once using SIMD instructions (essentially a fast strchr operation on pointers)
		//
		// we could save one load per subtypeof() operation by moving all these
		// structures to VTable.  Emperically, there are about 1.2 VTables per Traits,
		// so we'd expect to see a slight increase in overhead to save that load-per-test.
		//
		// to save memory or better handle deep class heirarchies we can tune MAX_PRIMARY_SUPERTYPE.
		// the value 8 was picked after emperical testing on a range of Flash and Flex applications.
		//
		// The "base" field is redundant; if accessing base is not frequent we can
		// encapsulate access and get it from either primary_supertypes or seconary_supertypes.
		// (this can be O(1) for secondary_supertypes if base is always the 1st or 2nd entry).
		// we can even walk up the class tree using secondary_supertypes and primary_supertypes
		// in sequence.  (best to encapsulate this in an iterator class).

		// size of the fixed-sized primary supertype list
		private:	static const int		MAX_PRIMARY_SUPERTYPE = 8;

	// ------------------------ DATA SECTION BEGIN
	public:		AvmCore* const			core;		// @todo remove, can get from pool->core
	public:		Traits* const			base;		// Pointer to the base traits; that is, the traits of the base class
	private:	DWB(Traits*)			m_supertype_cache;	  // 1-entry cache for subtypeof=true
	private:	MMgc::GCHiddenPointer<Traits*>
	                                    m_supertype_neg_cache;  // 1-entry cache for subtypeof=false (hidden to avoid pinning)
	private:	Traits* 				m_primary_supertypes[MAX_PRIMARY_SUPERTYPE]; // contains the first several base classes, written with explicit WB's
	private:	DWB(Traits**)			m_secondary_supertypes;
	public:		PoolObject* const		pool;		// The constant pool owning this definition. never null.
	public:		Traits*					itraits;	// if this type is a factory, itraits is non-null and points to the type created by this factory.
	private:	DRCWB(Namespacep)		_ns;			// The namespace of the class described by this traits object
	private:	DRCWB(Stringp)			_name;		// The name of the class described by this traits object
	public:		DRCWB(Namespacep)		protectedNamespace;	// protected namespace, if any
	public:		DWB(MethodInfo*)		init;				// not a call/init union b/c smart pointers and union's don't mix
	private:	CreateClassClosureProc	m_createClassClosure;
	private:	const TraitsPosPtr		m_traitsPos;		// ptr into our ABC definition, depending on m_posType
	private:	const byte*				metadata_pos;
	private:	FixedBitSet				m_slotDestroyInfo;	
	private:	DWB(MMgc::GCWeakRef*)	m_tbref;				// our TraitsBindings 
	private:	DWB(MMgc::GCWeakRef*)	m_tmref;				// our TraitsMetadata
#ifdef VMCFG_CACHE_GQCN
	private:	DRCWB(Stringp)			_fullname;		// value returned by formatClassName
#endif
 	private:	uint16_t				m_sizeofInstance;	// sizeof implementation class, e.g. ScriptObject, etc. < 64k. Not counting extra room for slots.
 	private:	uint16_t				m_offsetofSlots;	// offset of first slot.
	private:	uint32_t				m_hashTableOffset;	// offset to our hashtable (or 0 if none)
	private:	uint32_t				m_totalSize;		// total size, including sizeofInstance + slots + hashtable
	public:		uint8_t					builtinType;				// BuiltinType enumeration -- only need 5 bits but stored in byte for faster access
	private:	const uint8_t			m_posType;					// TraitsPosType enumeration -- only need 3 bits but stored in byte for faster access
	private:	uint8_t					m_bindingCapLog2;			// if nonzero, log2 of the cap needed for bindings
	private:    uint8_t					m_supertype_offset;			// if this traits is primary, == offset in primary_supertypes array; otherwise == offset of supertype_cache
	// 7 bits follow
	private:	uint32_t				m_needsHashtable:1;			// If true, the class needs a hash table. Typically true for dynamic classes, but will be false for XML
	private:	uint32_t				linked:1;					// set once signature types have been resolved */
	public:		uint32_t				final:1;					// set when the class cannot be extended */
	public:		uint32_t				commonBase:1;				// used for Verify::findCommonBase */
	public:		uint32_t				isDictionary:1;				// how we implement dictionary or strict style lookups
							// If hasCustomConstruct is false, the JIT will early bind to the AS defined constructor. 
	public:		uint32_t				hasCustomConstruct:1;		// does this type use the default ClassClosure::construct method or not?
							// If the traits are for a type that implements its own construct method, m_immplementsNewInterfaces must be set to true.  
	private:	uint32_t				m_implementsNewInterfaces:1; // does this type implement interfaces not implemented by its base?
	// ------------------------ DATA SECTION END
	};

	// iterates over each interface supertype of the given traits.
	class InterfaceIterator
	{
		Traits** st;
	public:
		InterfaceIterator(Traits*);
		InterfaceIterator(const TraitsBindings*);
		bool hasNext();		// returns true if there are more interfaces
		Traits* next();		// get the next one (moves iterator forward)
	};
}

#endif /* __avmplus_Traits__ */
