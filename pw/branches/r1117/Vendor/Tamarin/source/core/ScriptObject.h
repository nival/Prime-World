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

#ifndef __avmplus_ScriptObject__
#define __avmplus_ScriptObject__


namespace avmplus
{
	/**
	 * one actionscript object.  might or might not be a function.
	 * Base class for all objects visible to script code.
	 */
	class ScriptObject : public AvmPlusScriptableObject
	{
	public:
	
		ScriptObject(VTable* vtable, ScriptObject* delegate);
		ScriptObject(VTable* vtable, ScriptObject* delegate, int capacity);
		~ScriptObject();

		ScriptObject* getDelegate() const { return delegate; }
		void setDelegate(ScriptObject *d) { delegate = d; }

		Atom atom() const {
			return kObjectType|(uintptr)this; 
		}

		virtual Atom toAtom() const {
			return atom();
		}

		Traits* traits() const {
			return vtable->traits;
		}

		AvmCore* core() const {
			return vtable->traits->core;
		}

		MMgc::GC* gc() const {
			return core()->GetGC();
		}

		Toplevel* toplevel() const {
			return vtable->toplevel();
		}

		InlineHashtable* getTable() const;
		
		inline InlineHashtable* getTableNoInit() const
		{
			union {
				uint8_t* p;
				InlineHashtable* iht;
				HeapHashtable** hht;
			};
			p = (uint8_t*)this + vtable->traits->getHashtableOffset();
			if(!vtable->traits->isDictionary)
			{
				return iht;
			}
			else
			{
				//DictionaryObjects store pointer to HeapHashtable at
				//the hashtable offset
				return (*hht)->get_ht();
			}
		}		
		
		Atom getSlotAtom(uint32_t slot);
		
		// like getSlotAtom, but assume the resulting Atom is a ScriptObject...
		// if it is not, return NULL. useful for callers that expect only
		// a ScriptObject and reject other types (eg callproperty). If the
		// slot in question is usually a ScriptObject, it's substantially faster
		// to call this (vs getSlotAtom).
		ScriptObject* getSlotObject(uint32_t slot);

		// NOTE, this now does the equivalent of Toplevel::coerce() internally;
		// it is not necessary to call coerce() prior to calling this!
		void coerceAndSetSlotAtom(uint32_t slot, Atom atom);

		virtual Atom getDescendants(const Multiname* name) const;

		// argv[0] = receiver
		virtual Atom callProperty(const Multiname* name, int argc, Atom* argv);
		virtual Atom constructProperty(const Multiname* name, int argc, Atom* argv);

		// common set/set/has/delete/etc virtual methods renamed to explicitly name the expected arg types,
		// to avoid potentially hidden virtual functions
		virtual Atom getAtomProperty(Atom name) const;
		virtual Atom getAtomPropertyFromProtoChain(Atom name, ScriptObject* protochain, Traits *origObjTraits) const;
		virtual void setAtomProperty(Atom name, Atom value);
		virtual bool deleteAtomProperty(Atom name);
		virtual bool hasAtomProperty(Atom name) const;
		virtual bool getAtomPropertyIsEnumerable(Atom name) const;
		virtual void setAtomPropertyIsEnumerable(Atom name, bool enumerable);

		virtual Atom getMultinameProperty(const Multiname* name) const;
		virtual void setMultinameProperty(const Multiname* name, Atom value);
		virtual bool deleteMultinameProperty(const Multiname* name);
		virtual bool hasMultinameProperty(const Multiname* name) const;

		virtual Atom getUintProperty(uint32 i) const;
		virtual void setUintProperty(uint32 i, Atom value);
		virtual bool delUintProperty(uint32 i);
		virtual bool hasUintProperty(uint32 i) const;

		// convenience wrappers for passing Stringp instead of Atom
		// inline, not virtual (should never need overriding)
		inline Atom getStringProperty(Stringp name) const 
		{
			AvmAssert(name != NULL && name->isInterned());
			return getAtomProperty(name->atom());
		}
		inline Atom getStringPropertyFromProtoChain(Stringp name, ScriptObject* protochain, Traits *origObjTraits) const
		{
			return getAtomPropertyFromProtoChain(name->atom(), protochain, origObjTraits);
		}
		inline void setStringProperty(Stringp name, Atom value) 
		{
			setAtomProperty(name->atom(), value);
		}
		inline bool deleteStringProperty(Stringp name) 
		{
			return deleteAtomProperty(name->atom());
		}
		inline bool hasStringProperty(Stringp name) const 
		{
			AvmAssert(name != NULL && name->isInterned());
			return hasAtomProperty(name->atom());
		}
		inline bool getStringPropertyIsEnumerable(Stringp name) const
		{
			AvmAssert(name != NULL && name->isInterned());
			return getAtomPropertyIsEnumerable(name->atom());
		}
		inline void setStringPropertyIsEnumerable(Stringp name, bool enumerable)
		{
			setAtomPropertyIsEnumerable(name->atom(), enumerable);
		}

		virtual Atom defaultValue();		// ECMA [[DefaultValue]]
		virtual Atom toString();
		
		// argv[0] = receiver
		virtual Atom call(int argc, Atom* argv);

		// argv[0] = receiver(ignored)
		virtual Atom construct(int argc, Atom* argv);

		// TODO make this const
		virtual Atom nextName(int index);

		// TODO make this const
		virtual Atom nextValue(int index);

		// TODO make this const
		virtual int nextNameIndex(int index);

		virtual Atom applyTypeArgs(int argc, Atom* argv);

		// HACK; we need this so we can compare MethodClosures that
		// have the same instance and method.
		virtual bool isMethodClosure() { return false; }

		virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype);

		// The maximum integer key we can use with our ScriptObject
		// HashTable must fit within 28 bits.  Any integer larger
		// than 28 bits will use a string key.
		static const uint32 MAX_INTEGER_MASK = 0xF0000000;

		// return true iff the object is a toplevel script init object.
        bool isGlobalObject() const;

		virtual Stringp implToString() const;

		// this really shouldn't exist here, but AIR currently plays some games with subclassing
		// "Function" that use C++ classes that don't descend from FunctionObject. Easier to fix
		// by rooting this method here than by fixing AIR at this time. 
		virtual CodeContext* getFunctionCodeContext() const { AvmAssert(0); return NULL; }

		// this really shouldn't exist here, but is the simplest solution to the divergent
        // versions of ByteArray between Tamarin and Flash/AIR. When we someday unify them,
        // this should be able to go away.
		virtual GlobalMemoryProvider* getGlobalMemoryProvider() { AvmAssert(0); return NULL; }
		
#ifdef AVMPLUS_VERBOSE
	public:
		virtual Stringp format(AvmCore* core) const;
#endif
		
#ifdef DEBUGGER
	public:
		virtual uint64 size() const;
#endif
#if defined(DEBUGGER) || defined(VMCFG_AOT)
	public:
		virtual MethodEnv* getCallMethodEnv() { return NULL; }
#endif
		
	private:
		void initHashtable(int capacity = InlineHashtable::kDefaultCapacity);
		
	// ------------------------ DATA SECTION BEGIN
	public:		VTable* const			vtable;
	private:	DRCWB(ScriptObject*)	delegate;     // __proto__ in AS2, archetype in semantics
	// ------------------------ DATA SECTION END
	};
}

#endif /* __avmplus_ScriptObject__ */
