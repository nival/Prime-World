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
//#define DOPROF
//#include "../vprof/vprof.h"

namespace avmplus
{
	ScriptObject::ScriptObject(VTable* _vtable, ScriptObject* _delegate) :
#ifdef DEBUGGER 
		AvmPlusScriptableObject(sotObject(_vtable)), 
#endif // DEBUGGER
		vtable(_vtable),
		// note that it's substantially more efficient to initialize this in the ctor
		// list vs. a later explicit call to setDelegate, as we don't have to check for marking
		// nor decrement an existing value...
		delegate(_delegate)
	{
		AvmAssert(vtable->traits->isResolved());

		// Ensure that our object is large enough to hold its extra traits data.
		AvmAssert(MMgc::GC::Size(this) >= vtable->traits->getTotalSize());
	}

	ScriptObject::ScriptObject(VTable* _vtable, ScriptObject* _delegate, int capacity) :
#ifdef DEBUGGER 
		AvmPlusScriptableObject(sotObject(_vtable)), 
#endif // DEBUGGER
		vtable(_vtable),
		// note that it's substantially more efficient to initialize this in the ctor
		// list vs. a later explicit call to setDelegate, as we don't have to check for marking
		// nor decrement an existing value...
		delegate(_delegate)
	{
		AvmAssert(vtable->traits->isResolved());

		// Ensure that our object is large enough to hold its extra traits data.
		AvmAssert(MMgc::GC::Size(this) >= vtable->traits->getTotalSize());

		//if capacity not specified then initialize the hashtable lazily
		if (vtable->traits->needsHashtable() && capacity)
		{
			initHashtable(capacity);
		}
	}

	ScriptObject::~ScriptObject()
	{
		//setDelegate(NULL); -- no longer necessary
		vtable->traits->destroyInstance(this);
	}
	
	void ScriptObject::initHashtable(int capacity /*=InlineHashtable::kDefaultCapacity*/)
	{
		AvmAssert(vtable->traits->isDictionary == 0); //should not be called DictionaryObject uses HeapHashtable
		
		MMGC_MEM_TYPE(this);
		union {
			uint8_t* p;
			InlineHashtable* iht;
		};
		p = (uint8_t*)this + vtable->traits->getHashtableOffset();
		iht->initialize(this->gc(), capacity);
		iht->setDontEnumSupport();
	}
	
	InlineHashtable* ScriptObject::getTable() const
	{
		AvmAssert(vtable->traits->getHashtableOffset() != 0);
		union {
			uint8_t* p;
			InlineHashtable* iht;
			HeapHashtable** hht;
		};
		p = (uint8_t*)this + vtable->traits->getHashtableOffset();
		if(!vtable->traits->isDictionary)
		{
			if (iht->getCapacity() == 0)
				const_cast<ScriptObject*>(this)->initHashtable(); 
			return iht;
		}
		else
		{
			//DictionaryObjects store pointer to HeapHashtable at
			//the hashtable offset
			return (*hht)->get_ht();
		}
	}
	
    /**
     * traverse the delegate chain looking for a value.
     * [ed] it's okay to look only at the HT's in the delegate chain because
     * delegate values may only be instances of Object.  They cannot be objects
     * with slots.  We don't need to look at traits at each step.
     * todo - enforce this rule
     * @param name
     * @return
     */
	Atom ScriptObject::getAtomProperty(Atom name) const
	{
		if (!traits()->needsHashtable())
		{
			return getAtomPropertyFromProtoChain(name, delegate, traits());
		}
		else
		{
			Stringp s = core()->atomToString(name);
			AvmAssert(s->isInterned());
			Atom ival = s->getIntAtom();
			if (ival)
			{
				name = ival;
			}

			// dynamic lookup on this object
			const ScriptObject *o = this;
			do
			{
				InlineHashtable *table = o->getTable();
				const Atom* atoms = table->getAtoms();
				int i = table->find(name, atoms, table->getCapacity());
				if (atoms[i] != InlineHashtable::EMPTY)
					return atoms[i+1];
			}
			while ((o = o->delegate) != NULL);
			return undefinedAtom;
		}			
	}
	
	Atom ScriptObject::getAtomPropertyFromProtoChain(Atom name, ScriptObject* o, Traits *origObjTraits) const
	{
        // todo will delegate always be non-null here?
		if (o != NULL)
		{
			Atom searchname = name;
			Stringp s = core()->atomToString(name);
			AvmAssert(s->isInterned());
			Atom ival = s->getIntAtom();
			if (ival)
			{
				searchname = ival;
			}
			do
			{
				const Atom* atoms = o->getTable()->getAtoms();
				int i = o->getTable()->find(searchname, atoms, o->getTable()->getCapacity());
				if (atoms[i] != InlineHashtable::EMPTY)
					return atoms[i+1];
			}
			while ((o = o->delegate) != NULL);
		}
		// NOTE use default public since name is not used
		Multiname multiname(core()->getAnyPublicNamespace(), AvmCore::atomToString(name));
		toplevel()->throwReferenceError(kReadSealedError, &multiname, origObjTraits);
		// unreached
		return undefinedAtom;
	}

	bool ScriptObject::hasMultinameProperty(const Multiname* multiname) const
	{
		if (traits()->needsHashtable() && multiname->isValidDynamicName())
			{
				return hasAtomProperty(multiname->getName()->atom());
			}
			else
			{
			// ISSUE should this walk the proto chain?
			return false;
		}
	}

	bool ScriptObject::hasAtomProperty(Atom name) const
	{
		if (traits()->needsHashtable())
		{
			Stringp s = core()->atomToString(name);
			AvmAssert(s->isInterned());
			Atom ival = s->getIntAtom();
			if (ival)
			{
				name = ival;
			}

			return getTable()->contains(name);
		}
		else
		{
			// ISSUE should this walk the proto chain?
			return false;
		}
	}

    void ScriptObject::setAtomProperty(Atom name, Atom value)
    {
		if (traits()->needsHashtable())
		{
			Stringp s = core()->atomToString(name);
			AvmAssert(s->isInterned());
			Atom ival = s->getIntAtom();
			if (ival)
			{
				name = ival;
			}

			MMGC_MEM_TYPE(this);
			getTable()->add (name, value);
			MMGC_MEM_TYPE(NULL);
		}
		else
		{
			// NOTE use default public since name is not used
			Multiname multiname(core()->getAnyPublicNamespace(), AvmCore::atomToString(name));

			// cannot create properties on a sealed object.
			toplevel()->throwReferenceError(kWriteSealedError, &multiname, traits());
		}
    }

	void ScriptObject::setMultinameProperty(const Multiname* name, Atom value)
	{
		if (traits()->needsHashtable() && name->isValidDynamicName())
		{
			setStringProperty(name->getName(), value);
		}
		else
		{
			// cannot create properties on a sealed object.
			toplevel()->throwReferenceError(kWriteSealedError, name, traits());
		}
	}

	bool ScriptObject::getAtomPropertyIsEnumerable(Atom name) const
	{
		if (traits()->needsHashtable())
		{
			Stringp s = core()->atomToString(name);
			AvmAssert(s->isInterned());
			Atom ival = s->getIntAtom();
			if (ival)
			{
				name = ival;
			}

			return getTable()->getAtomPropertyIsEnumerable(name);
		}
		else
		{
			// ISSUE should this walk the proto chain?
			return false;
		}
	}

	void ScriptObject::setAtomPropertyIsEnumerable(Atom name, bool enumerable)
	{
		if (traits()->needsHashtable())
		{
			Stringp s = core()->atomToString(name);
			AvmAssert(s->isInterned());
			Atom ival = s->getIntAtom();
			if (ival)
			{
				name = ival;
			}

			getTable()->setAtomPropertyIsEnumerable(name, enumerable);
		}
		else
		{
			// cannot create properties on a sealed object. just use any public
			Multiname multiname(core()->getAnyPublicNamespace(), AvmCore::atomToString(name));
			toplevel()->throwReferenceError(kWriteSealedError, &multiname, traits());
		}
	}
	
	bool ScriptObject::deleteAtomProperty(Atom name)
	{
		if (traits()->needsHashtable())
		{
			Stringp s = core()->atomToString(name);
			AvmAssert(s->isInterned());
			Atom ival = s->getIntAtom();
			if (ival)
			{
				name = ival;
			}

			getTable()->remove(name);
			return true;
		}
		else
		{
			return false;
		}
	}
	
	bool ScriptObject::deleteMultinameProperty(const Multiname* name)
	{
		if (traits()->needsHashtable() && name->isValidDynamicName())
		{
			return deleteStringProperty(name->getName());
		}
		else
		{
			return false;
		}
	}

	Atom ScriptObject::getUintProperty(uint32 i) const
	{
		AvmCore* core = this->core();

		if (!(i&MAX_INTEGER_MASK))
		{
			if (!traits()->needsHashtable())
			{
				Atom name = core->internUint32(i)->atom();
				return getAtomPropertyFromProtoChain(name, delegate, traits());
			}
			else
			{
				// dynamic lookup on this object
				Atom name = core->uintToAtom (i);
				const ScriptObject *o = this;
				do
				{
					InlineHashtable *table = o->getTable();
					const Atom* atoms = table->getAtoms();
					int i = table->find(name, atoms, table->getCapacity());
					if (atoms[i] != InlineHashtable::EMPTY)
						return atoms[i+1];
				}
				while ((o = o->delegate) != NULL);
				return undefinedAtom;
			}			
		}
		else
		{
			return getAtomProperty(core->internUint32(i)->atom());
		}		
	}

	void ScriptObject::setUintProperty(uint32 i, Atom value)
	{
		AvmCore* core = this->core();
		if (!(i&MAX_INTEGER_MASK)) 
		{
			Atom name = core->uintToAtom (i);
			if (traits()->needsHashtable())
			{
				MMGC_MEM_TYPE(this);
				getTable()->add(name, value);
				MMGC_MEM_TYPE(NULL);
			}
			else
			{
				// NOTE use default public since name is not used
				Multiname multiname(core->getAnyPublicNamespace(), core->string(name));

				// cannot create properties on a sealed object.
				toplevel()->throwReferenceError(kWriteSealedError, &multiname, traits());
			}
		}
		else
		{
			setAtomProperty(core->internUint32(i)->atom(), value);
		}
	}

	bool ScriptObject::delUintProperty(uint32 i)
	{
		AvmCore* core = this->core();
		if (!(i&MAX_INTEGER_MASK)) 
		{
			Atom name = core->uintToAtom (i);
			if (traits()->needsHashtable())
			{
				getTable()->remove(name);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return deleteAtomProperty(core->internUint32(i)->atom());
		}
	}

	bool ScriptObject::hasUintProperty(uint32 i) const
	{
		AvmCore* core = this->core();
		if (!(i&MAX_INTEGER_MASK)) 
		{
			Atom name = core->uintToAtom (i);
			if (traits()->needsHashtable())
			{
				return getTable()->contains(name);
			}
			else
			{
				// ISSUE should this walk the proto chain?
				return false;
			}
		}
		else
		{
			return hasAtomProperty(core->internUint32(i)->atom());
		}
	}

	Atom ScriptObject::getMultinameProperty(const Multiname* multiname) const
	{
		if (multiname->isValidDynamicName())
		{
			return getStringProperty(multiname->getName());
		}
		else
		{
			Toplevel* toplevel = this->toplevel();

			if (multiname->isNsset())
				toplevel->throwReferenceError(kReadSealedErrorNs, multiname, traits());
			else
				toplevel->throwReferenceError(kReadSealedError, multiname, traits());
			return undefinedAtom;
		}
	}

	// this = argv[0] (ignored)
	// arg1 = argv[1]
	// argN = argv[argc]
	Atom ScriptObject::callProperty(const Multiname* multiname, int argc, Atom* argv)
	{
		Toplevel* toplevel = this->toplevel();
		Atom method = getMultinameProperty(multiname);
		if (!AvmCore::isObject(method))
			toplevel->throwTypeError(kCallOfNonFunctionError, core()->toErrorString(multiname));
		argv[0] = atom(); // replace receiver
		return toplevel->op_call(method, argc, argv);
	}

	Atom ScriptObject::constructProperty(const Multiname* multiname, int argc, Atom* argv)
	{
		Atom ctor = getMultinameProperty(multiname);
		argv[0] = atom(); // replace receiver
		return toplevel()->op_construct(ctor, argc, argv);
	}
	
	Atom ScriptObject::getDescendants(const Multiname* /*name*/) const
	{
		toplevel()->throwTypeError(kDescendentsError, core()->toErrorString(traits()));
		return undefinedAtom;// not reached
	}

    bool ScriptObject::isGlobalObject() const
    {
        AvmAssert(vtable != 0);
        AvmAssert(vtable->init != 0);
		MethodEnv* init = vtable->init;
		if (!init->isScriptEnv())
			return false;
        const ScriptEnv* const scriptInitForVTable = static_cast<const ScriptEnv*>(init);
        return scriptInitForVTable->global == this;
    }

#ifdef AVMPLUS_VERBOSE
	Stringp ScriptObject::format(AvmCore* core) const
	{
		if (traits()->name() != NULL) {
			return core->concatStrings(traits()->format(core),
									   core->concatStrings(core->newConstantStringLatin1("@"),
														   core->formatAtomPtr(atom())));
		} else {
			return core->concatStrings(core->newConstantStringLatin1("{}@"),
									   core->formatAtomPtr(atom()));
		}
	}
#endif

	Atom ScriptObject::defaultValue()
	{
		AvmCore *core = this->core();
		Toplevel* toplevel = this->toplevel();

		Atom atomv_out[1];

		// call this.valueOf()
		// NOTE use callers versioned public to get correct valueOf
		Multiname tempname(core->findPublicNamespace(), core->kvalueOf);
		atomv_out[0] = atom();
		Atom result = toplevel->callproperty(atom(), &tempname, 0, atomv_out, vtable);

		// if result is primitive, return it
		if (atomKind(result) != kObjectType)
			return result;

		// otherwise call this.toString()
		tempname.setName(core->ktoString);
		atomv_out[0] = atom();
		result = toplevel->callproperty(atom(), &tempname, 0, atomv_out, vtable);

		// if result is primitive, return it
		if (atomKind(result) != kObjectType)
			return result;

		// could not convert to primitive.
		toplevel->throwTypeError(kConvertToPrimitiveError, core->toErrorString(traits()));
		return undefinedAtom;
	}

	// Execute the ToString algorithm as described in ECMA-262 Section 9.8.
	// This is ToString(ToPrimitive(input argument, hint String))
	// ToPrimitive(input argument, hint String) calls [[DefaultValue]]
	// described in ECMA-262 8.6.2.6.  The [[DefaultValue]] algorithm
	// with hint String is inlined here.
	Atom ScriptObject::toString()
	{
		AvmCore *core = this->core();
		Toplevel* toplevel = this->toplevel();

		Atom atomv_out[1];

		// call this.toString()
		// NOTE use callers versioned public to get correct toString
		Multiname tempname(core->findPublicNamespace(), core->ktoString);
		atomv_out[0] = atom();
		Atom result = toplevel->callproperty(atom(), &tempname, 0, atomv_out, vtable);

		// if result is primitive, return its ToString
		if (atomKind(result) != kObjectType)
			return core->string(result)->atom();

		// otherwise call this.valueOf()
		tempname.setName(core->kvalueOf);
		atomv_out[0] = atom();
		result = toplevel->callproperty(atom(), &tempname, 0, atomv_out, vtable);

		// if result is primitive, return it
		if (atomKind(result) != kObjectType)
			return core->string(result)->atom();

		// could not convert to primitive.
		toplevel->throwTypeError(kConvertToPrimitiveError, core->toErrorString(traits()));
		return undefinedAtom;
	}

	// this = argv[0] (ignored)
	// arg1 = argv[1]
	// argN = argv[argc]
	Atom ScriptObject::call(int /*argc*/, Atom* /*argv*/)
	{
		// TypeError in ECMA to execute a non-function
		// NOTE use default public since name is not used
		Multiname name(core()->getAnyPublicNamespace(), core()->internConstantStringLatin1("value"));
		toplevel()->throwTypeError(kCallOfNonFunctionError, core()->toErrorString(&name));
		return undefinedAtom;
	}

	// this = argv[0] (ignored)
	// arg1 = argv[1]
	// argN = argv[argc]
	Atom ScriptObject::construct(int /*argc*/, Atom* /*argv*/)
	{
		// TypeError in ECMA to execute a non-function
		toplevel()->throwTypeError(kConstructOfNonFunctionError);
		return undefinedAtom;
	}

	Atom ScriptObject::applyTypeArgs(int /*argc*/, Atom* /*argv*/)
	{
		toplevel()->throwTypeError(kTypeAppOfNonParamType);
		return undefinedAtom;
	}
	
	Atom ScriptObject::getSlotAtom(uint32_t slot)
	{
		Traits* traits = this->traits();
		const TraitsBindingsp td = traits->getTraitsBindings();
		// repeated if-else is actually more performant than a switch statement in this case.
		// SST_atom is most common case, put it first
		void* p;
		const SlotStorageType sst = td->calcSlotAddrAndSST(slot, (void*)this, p);
		if (sst == SST_atom)
		{
			return *((const Atom*)p);
		}
		else if (sst == SST_double)
		{
			return traits->core->doubleToAtom(*((const double*)p));				
		}
		else if (sst == SST_int32)
		{
			return traits->core->intToAtom(*((const int32_t*)p));
		}
		else if (sst == SST_uint32)
		{
			return traits->core->uintToAtom(*((const int32_t*)p));
		}
		else if (sst == SST_bool32)
		{
			return (*((const int32_t*)p)<<3)|kBooleanType;
		}
		else if (sst == SST_string)
		{
			return (*((const Stringp*)p))->atom(); // may be null|kStringType, that's ok
		}
		else if (sst == SST_namespace)
		{
			return (*((const Namespacep*)p))->atom(); // may be null|kNamespaceType, no problemo
		}
		else // if (sst == SST_scriptobject)
		{
			AvmAssert(sst == SST_scriptobject);
			return (*((const ScriptObject**)p))->atom(); // may be null|kObjectType, copacetic
		}
	}

	ScriptObject* ScriptObject::getSlotObject(uint32_t slot)
	{
		Traits* traits = this->traits();
		const TraitsBindingsp td = traits->getTraitsBindings();
		void* p;
		const SlotStorageType sst = td->calcSlotAddrAndSST(slot, (void*)this, p);

		// based on profiling of Flex apps, it's *much* more common for the slot in this case
		// to have a type (vs "atom"), so check for that first...
		if (sst == SST_scriptobject)
		{
			return *((ScriptObject**)p);
		}
		else if (sst == SST_atom)
		{
			Atom const a = *((const Atom*)p);

			// don't call AvmCore::isObject(); it checks for null, which we don't care about here
			if (atomKind(a) == kObjectType)
				return (ScriptObject*)atomPtr(a);
			
			// else fall thru and return null
		} 

		return NULL;
	}

	// note: coerceAndSetSlotAtom now includes a simplified and streamlined version
	// of Toplevel::coerce. If you modify that code, you might need to modify this code.
	void ScriptObject::coerceAndSetSlotAtom(uint32_t slot, Atom value)
	{
		Traits* traits = this->traits();
		const TraitsBindingsp td = traits->getTraitsBindings();
		void* p;
		const SlotStorageType sst = td->calcSlotAddrAndSST(slot, (void*)this, p);
		// repeated if-else is actually more performant than a switch statement in this case.
		// SST_atom is most common case, put it first
		if (sst == SST_atom)
		{
			// no call to coerce() needed, since anything will fit here... with one exception:
			// BUILTIN_object needs to convert undefined->null (though BUILTIN_any does not).
			// it's cheaper to do that here than call out to coerce().
			AvmAssert(td->getSlotTraits(slot) == NULL || td->getSlotTraits(slot)->builtinType == BUILTIN_object);
			if (value == undefinedAtom && td->getSlotTraits(slot) != NULL)
				value = nullObjectAtom;
			WBATOM(traits->core->GetGC(), this, (Atom*)p, value);
		}
		else if (sst == SST_double)
		{
			*((double*)p) = AvmCore::number(value);
		}
		else if (sst == SST_int32)
		{
			*((int32_t*)p) = AvmCore::integer(value);
		}
		else if (sst == SST_uint32)
		{
			*((uint32_t*)p) = AvmCore::toUInt32(value);
		}
		else if (sst == SST_bool32)
		{
			*((int32_t*)p) = AvmCore::boolean(value);
		}
		else 
		{
			// null/undefined -> NULL for all of these
			if (AvmCore::isNullOrUndefined(value))
			{
				value = (Atom)0; // don't bother setting tag bits 
			}
			else if (sst == SST_string)
			{
				value = (Atom)traits->core->string(value); // don't bother setting tag bits 
			}
			else if (sst == SST_namespace)
			{
				// Namespace is final, so we don't have to do the hard work
				if (atomKind(value) != kNamespaceType)
					goto failure;
			}
			else // if (sst == SST_scriptobject)
			{
				AvmAssert(sst == SST_scriptobject);
				if (atomKind(value) != kObjectType || !AvmCore::atomToScriptObject(value)->traits()->subtypeof(td->getSlotTraits(slot)))
					goto failure;
			}
			WBRC(traits->core->GetGC(), this, p, atomPtr(value));
		}
		return;

	failure:
		toplevel()->throwTypeError(kCheckTypeFailedError, traits->core->atomToErrorString(value), traits->core->toErrorString(td->getSlotTraits(slot)));
		return;
	}

	Atom ScriptObject::nextName(int index)
	{
		AvmAssert(traits()->needsHashtable());
		AvmAssert(index > 0);

		InlineHashtable *ht = getTable();
		if (uint32_t(index)-1 >= ht->getCapacity()/2)
			return nullStringAtom;
		const Atom* atoms = ht->getAtoms();
		Atom m = ht->removeDontEnumMask(atoms[(index-1)<<1]);
		if (AvmCore::isNullOrUndefined(m))
			return nullStringAtom;
		return m;
	}

	Atom ScriptObject::nextValue(int index)
	{
		AvmAssert(traits()->needsHashtable());
		AvmAssert(index > 0);

		InlineHashtable *ht = getTable();
		if (uint32_t(index)-1 >= ht->getCapacity()/2)
			return undefinedAtom;
		const Atom* atoms = ht->getAtoms();
		Atom m = ht->removeDontEnumMask(atoms[(index-1)<<1]);
		if (AvmCore::isNullOrUndefined(m))
			return nullStringAtom;
		return atoms[((index-1)<<1)+1];
	}

	int ScriptObject::nextNameIndex(int index)
	{
		AvmAssert(index >= 0);

		if (!traits()->needsHashtable())
			return 0;

		// todo clean this up.
		if (index != 0) {
			index = index<<1;
		}
		// Advance to first non-empty slot.
		InlineHashtable* table = getTable();
		const Atom* atoms = table->getAtoms();
		int numAtoms = table->getCapacity();
		while (index < numAtoms) {
			Atom m = atoms[index];
			if (table->enumerable(m))
				return (index>>1)+1;
			index += 2;
		}
		return 0;
	}

	/**
	 * the default implementation calls the delegate (should be the base class objects) 
	 * so that derived classes delegate object allocation to the base class.  If you 
	 * are overriding createInstance and your base class is Object, unconditionally allocate
	 * the instance object using the given vtable and prototype.
	 */
	ScriptObject* ScriptObject::createInstance(VTable* ivtable, ScriptObject* prototype)
	{
		if (ivtable->base)
		{
			ScopeChain* scope = vtable->init->scope();
			if (scope->getSize())
			{
				Atom baseAtom = scope->getScope(scope->getSize()-1);
				if (!AvmCore::isObject(baseAtom))
					toplevel()->throwVerifyError(kCorruptABCError);

				ScriptObject *base = AvmCore::atomToScriptObject(baseAtom);
				// make sure scope object is base type's class object
				AvmAssert(base->traits()->itraits == this->traits()->itraits->base);
				return base->createInstance(ivtable, prototype);
			}
		}

		return core()->newObject(ivtable, prototype);
	}

	
#ifdef DEBUGGER
	uint64 ScriptObject::size() const
	{
		uint64 size = traits()->getTotalSize();
		if(traits()->needsHashtable())
		{
			size += getTable()->size();
		}
		size -= sizeof(AvmPlusScriptableObject);
		return size;
	}

	
#endif

	Stringp ScriptObject::implToString() const
	{
		AvmCore* core = this->core();
		Traits* t = this->traits();
		Stringp s = core->concatStrings(core->newConstantStringLatin1("[object "), t->name());
		return core->concatStrings(s, core->newConstantStringLatin1("]"));
	}
}
