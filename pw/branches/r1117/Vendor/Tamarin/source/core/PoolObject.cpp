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

#ifdef VMCFG_NANOJIT
#  include "CodegenLIR.h"
#endif

namespace avmplus
{
	PoolObject::PoolObject(AvmCore* core, ScriptBuffer& sb, const byte* startPos, uint32_t api) :
		core(core),
		cpool_int(0),
		cpool_uint(0),
		cpool_double(core->GetGC(), 0),
		cpool_ns(core->GetGC(), 0),
		cpool_ns_set(core->GetGC(), 0),
#ifndef AVMPLUS_64BIT
		cpool_int_atoms(core->GetGC(), 0),
		cpool_uint_atoms(core->GetGC(), 0),
#endif
		cpool_mn_offsets(0),
		metadata_infos(0),
		bugFlags(0),
		_namedTraits(new(core->GetGC()) MultinameHashtable()),
		_privateNamedScripts(new(core->GetGC()) MultinameHashtable()),
		_code(sb.getImpl()),
		_abcStart(startPos),
		_abcStringStart(NULL),
		_abcStringEnd(NULL),
		_abcStrings(core->GetGC()),
		_classes(core->GetGC(), 0),
		_scripts(core->GetGC(), 0),
		_methods(core->GetGC(), 0)
#ifdef DEBUGGER
		, _method_dmi(core->GetGC(), 0)
#endif
#if VMCFG_METHOD_NAMES
		, _method_name_indices(0)
#endif
		, api(api)
#ifdef VMCFG_AOT
		, aotInfo(NULL)
#endif
	{
		version = AvmCore::readU16(&code()[0]) | AvmCore::readU16(&code()[2])<<16;
		core->addLivePool(this);
		core->setActiveAPI(api);
	}

	PoolObject::~PoolObject()
	{
		#ifdef VMCFG_PRECOMP_NAMES
		delete precompNames;
		#endif

		#ifdef VMCFG_NANOJIT
		mmfx_delete( codeMgr );
		#endif
	}
	
	void PoolObject::dynamicizeStrings()
	{
		if (!MMgc::GC::GetGC(this)->Destroying())
		{
			// make all strings created so far dynamic,
			// making sure that no pointers into ABC data persist
			// (string 0 is always core->kEmptyString: skip it)
			ConstantStringData* dataP = _abcStrings.data;
			for (uint32_t i = 1; i < constantStringCount; i++)
			{
				++dataP;
				
				if (dataP->abcPtr >= _abcStringStart && dataP->abcPtr < _abcStringEnd)
				{
					// it's still a raw ABC ptr, not a String
					continue;
				}

				Stringp s = dataP->str;

				// in theory, only index 0 should be the empty string... but in practice,
				// any index could be empty, and makeDynamic doesn't work on zero-length strings.
				// since that call doesn't have easy access to an AvmCore, do the check here.
                // (s can be null in the obscure case of a fuzzed ABC)
				if (!s || s->isEmpty())
				{
					// all zero-length strings should be kEmptyString.
					AvmAssert(!s || s == core->kEmptyString);
					continue;
				}
				
				s->makeDynamic(_abcStringStart, uint32_t(_abcStringEnd - _abcStringStart));
			}
		}
	}

	Traits* PoolObject::getBuiltinTraits(Stringp name) const
	{
		AvmAssert(BIND_NONE == 0);
		return (Traits*) _namedTraits->getName(name);
	}

	Traits* PoolObject::getTraits(Stringp name, Namespace* ns, bool recursive/*=true*/) const
	{
		// look for class in VM-wide type table
		Traits* t = domain->getNamedTraits(name, ns, recursive);

		// look for class in current ABC file
		if (t == NULL)
			t = (Traits*) _namedTraits->get(name, ns);
		return t;
	}

	Traits* PoolObject::getTraits(Stringp name, bool recursive/*=true*/) const
	{
		return getTraits(name, core->getPublicNamespace((PoolObject*) this), recursive);
	}

	Traits* PoolObject::getTraits(const Multiname& mname, const Toplevel* toplevel, bool recursive/*=true*/) const
	{
		// do full lookup of multiname, error if more than 1 match
		// return Traits if 1 match, NULL if 0 match, throw ambiguity error if >1 match
		Traits* match = NULL;
		if (mname.isBinding())
		{
			// multiname must not be an attr name, have wildcards, or have runtime parts.
			for (int32_t i=0, n=mname.namespaceCount(); i < n; i++)
			{
				Traits* t = getTraits(mname.getName(), mname.getNamespace(i), recursive);
				if (t != NULL)
				{
					if (match == NULL)
					{
						match = t;
					}
					else if (match != t)
					{
						// ambiguity
						if (toplevel)
							toplevel->throwReferenceError(kAmbiguousBindingError, mname);
						AvmAssert(!"unhandled ambiguous binding");
					}
				}
			}
		}
		return match;
	}

	void PoolObject::addNamedTraits(Stringp name, Namespace* ns, Traits* traits)
	{
		_namedTraits->add(name, ns, (Binding)traits);
	}

	Namespace* PoolObject::getNamespace(int32_t index) const
	{
		return cpool_ns[index];  
	}

	NamespaceSetp PoolObject::getNamespaceSet(int32_t index) const
	{
		return cpool_ns_set[index];  
	}

	////////////////////////////////////////////////////////////////////

	void PoolObject::setupConstantStrings(uint32_t count)
	{
		_abcStrings.setup(count);
		constantStringCount = count;
	}

	Stringp PoolObject::getString(int32_t index) const
	{
		ConstantStringData* dataP = _abcStrings.data + index;
		if (dataP->abcPtr >= _abcStringStart && dataP->abcPtr < _abcStringEnd)
		{
			// String not created yet; grab the pointer to the (verified) ABC data
			uint32_t len = AvmCore::readU30(dataP->abcPtr);
			Stringp s = core->internStringUTF8((const char*) dataP->abcPtr, len, true);
			// must be made sticky for now...
			s->Stick();
			dataP->str = s;
		}
		return dataP->str;
	}

	/*static*/ bool PoolObject::isLegalDefaultValue(BuiltinType bt, Atom value)
	{
		switch (bt)
		{
			case BUILTIN_any:
				return true;

			case BUILTIN_object:
				return (value != undefinedAtom);

			case BUILTIN_number:
				return AvmCore::isNumber(value);

			case BUILTIN_boolean:
				return AvmCore::isBoolean(value);

			case BUILTIN_uint:
				if (AvmCore::isDouble(value))
				{
					const double d = AvmCore::number_d(value);
					if (d == (uint32_t)d) 
						return true;
				}

				return atomIsIntptr(value) && atomCanBeUint32(value);

			case BUILTIN_int:
				if (AvmCore::isDouble(value))
				{
					const double d = AvmCore::number_d(value);
					if (d == (int32_t)d) 
						return true;
				}

				return atomIsIntptr(value) && atomCanBeInt32(value);

			case BUILTIN_string:
				return AvmCore::isNull(value) || AvmCore::isString(value);

			case BUILTIN_namespace:
				return AvmCore::isNull(value) || AvmCore::isNamespace(value);

			default:
				return AvmCore::isNull(value);
		}

		//return false; // unreachable
	}

	Atom PoolObject::getLegalDefaultValue(const Toplevel* toplevel, uint32_t index, CPoolKind kind, Traits* t) 
	{
		// toplevel actually can be null, when resolving the builtin classes...
		// but they should never cause verification errors in functioning builds
		//AvmAssert(toplevel != NULL);
		
		const BuiltinType bt = Traits::getBuiltinType(t);
		uint32_t maxcount = 0;
		Atom value;
		if (index)
		{
			// Look in the cpool specified by kind
			switch (kind)
			{
			case CONSTANT_Int:
			{
				if (index >= (maxcount = constantIntCount))
					goto range_error;
				const int32_t i = cpool_int[index];
#ifdef AVMPLUS_64BIT
				value = core->intToAtom(i);
				AvmAssert(atomIsIntptr(value) && atomCanBeInt32(value));
#else
				// LIR relies on the return values from this being "sticky" so it can insert them inline.
				// that's true for everything but int/uints that overflow, so special-case them.
				// @todo this can/should go away when we convert to 64-bit Box atoms.
				if (!cpool_int_atoms.size())
				{
					cpool_int_atoms.ensureCapacity(constantIntCount);
					for (uint32_t j = 0; j < constantIntCount; ++j)
						cpool_int_atoms.set(j, 0);
					AvmAssert(cpool_int_atoms.size() == constantIntCount);
				}
				value = (Atom)cpool_int_atoms[index];
				if (value == 0)
				{
					value = core->intToAtom(i);
					if (AvmCore::isDouble(value))
					{
						cpool_int_atoms.set(index, value);
					}
					AvmAssert(AvmCore::isNumber(value));
				}
				else
				{
					AvmAssert(AvmCore::isDouble(value));
				}
#endif
				break;
			}
			case CONSTANT_UInt:
			{
				if (index >= (maxcount = constantUIntCount))
					goto range_error;
				const int32_t u = cpool_int[index];
#ifdef AVMPLUS_64BIT
				value = core->uintToAtom(u);
				AvmAssert(atomIsIntptr(value) && atomCanBeUint32(value));
#else
				// LIR relies on the return values from this being "sticky" so it can insert them inline.
				// that's true for everything but int/uints that overflow, so special-case them.
				// @todo this can/should go away when we convert to 64-bit Box atoms.
				if (!cpool_uint_atoms.size())
				{
					cpool_uint_atoms.ensureCapacity(constantUIntCount);
					for (uint32_t j = 0; j < constantUIntCount; ++j)
						cpool_uint_atoms.set(j, 0);
					AvmAssert(cpool_uint_atoms.size() == constantUIntCount);
				}
				value = (Atom)cpool_uint_atoms[index];
				if (value == 0)
				{
					value = core->uintToAtom(u);
					if (AvmCore::isDouble(value))
					{
						cpool_uint_atoms.set(index, value);
					}
					AvmAssert(AvmCore::isNumber(value));
				}
				else
				{
					AvmAssert(AvmCore::isDouble(value));
				}
#endif
				break;
			}
			case CONSTANT_Double:
				if (index >= (maxcount = constantDoubleCount))
					goto range_error;
				value = kDoubleType|(uintptr)cpool_double[index];
				break;

			case CONSTANT_Utf8:
				if (index >= (maxcount = constantStringCount))
					goto range_error;
				value = getString(index)->atom();
				break;

			case CONSTANT_True:
				value = trueAtom;
				break;

			case CONSTANT_False:
				value = falseAtom;
				break;

			case CONSTANT_Namespace:
			case CONSTANT_PackageNamespace:
			case CONSTANT_PackageInternalNs:
			case CONSTANT_ProtectedNamespace:
			case CONSTANT_ExplicitNamespace:
			case CONSTANT_StaticProtectedNs:
			case CONSTANT_PrivateNs:
				if (index >= (maxcount = constantNsCount))
					goto range_error;
				value = cpool_ns[index]->atom();
				break;

			case CONSTANT_Null:
				value = nullObjectAtom;
				break;

			default:
				// Multinames & NamespaceSets are invalid default values.
				goto illegal_default_error;
			}
		}
		else
		{
			switch (bt)
			{
				case BUILTIN_any:
					value = undefinedAtom;
					break;
				case BUILTIN_number:
					value = core->kNaN;
					break;
				case BUILTIN_boolean:
					value = falseAtom;
					break;
				case BUILTIN_int:
				case BUILTIN_uint:
					value = (zeroIntAtom);
					break;
				case BUILTIN_string:
					value = nullStringAtom;
					break;
				case BUILTIN_namespace:
					value = nullNsAtom;
					break;
				case BUILTIN_object:
				default:
					value = nullObjectAtom;
					break;
			}
		}

		if (!isLegalDefaultValue(bt, value))
			goto illegal_default_error;
		
		return value;

illegal_default_error:
		if (toplevel)
		{
			if (t)
			{
				toplevel->throwVerifyError(kIllegalDefaultValue, core->toErrorString(Multiname(t->ns(), t->name())));
			}
			else
			{
				toplevel->throwVerifyError(kCorruptABCError);
			}
		}
		AvmAssert(!"unhandled verify error");
		return undefinedAtom; // not reached

range_error:
		if (toplevel)
			toplevel->throwVerifyError(kCpoolIndexRangeError, core->toErrorString(index), core->toErrorString(maxcount));
		AvmAssert(!"unhandled verify error");
		return undefinedAtom; // not reached
	}

	void PoolObject::parseMultiname(const byte *pos, Multiname& m) const
	{
		// the multiname has already been validated so we don't do
		// any checking here, we just fill in the Multiname object
		// with the information we have parsed.

		int32_t index;
		CPoolKind kind = (CPoolKind) *(pos++);
        switch (kind)
        {
		case CONSTANT_Qname: 
		case CONSTANT_QnameA:
		{
			// U16 namespace_index
            // U16 name_index
			// parse a multiname with one namespace (aka qname)

			index = AvmCore::readU30(pos);
			if (!index)
				m.setAnyNamespace();
			else
				m.setNamespace(getNamespace(index));

			index = AvmCore::readU30(pos);
			if (!index)
				m.setAnyName();
			else
				m.setName(getString(index));

			m.setQName();
			m.setAttr(kind==CONSTANT_QnameA);
			break;
		}

		case CONSTANT_RTQname:
		case CONSTANT_RTQnameA: 
		{
			// U16 name_index
			// parse a multiname with just a name; ns fetched at runtime

			index = AvmCore::readU30(pos);
			if (!index)
				m.setAnyName();
			else
				m.setName(getString(index));

			m.setQName();
			m.setRtns();
			m.setAttr(kind==CONSTANT_RTQnameA);
			break;
		}

		case CONSTANT_RTQnameL:
		case CONSTANT_RTQnameLA:
		{
			m.setQName();
			m.setRtns();
			m.setRtname();
			m.setAttr(kind==CONSTANT_RTQnameLA);
			break;
		}

		case CONSTANT_Multiname:
		case CONSTANT_MultinameA:
		{
			index = AvmCore::readU30(pos);
			if (!index)
				m.setAnyName();
			else
				m.setName(getString(index));

			index = AvmCore::readU30(pos);
			AvmAssert(index != 0);
			m.setNsset(getNamespaceSet(index));
			m.setAttr(kind==CONSTANT_MultinameA);
			break;
		}

		case CONSTANT_MultinameL:
		case CONSTANT_MultinameLA:
		{
			m.setRtname();

			index = AvmCore::readU30(pos);
			AvmAssert(index != 0);
			m.setNsset(getNamespaceSet(index));

			m.setAttr(kind==CONSTANT_MultinameLA);
			break;
		}

		case CONSTANT_TypeName:
		{
			index = AvmCore::readU30(pos);
			parseMultiname(_abcStart + cpool_mn_offsets[index], m);
			index = AvmCore::readU30(pos);
			AvmAssert(index==1);
			m.setTypeParameter(AvmCore::readU30(pos));
			break;
		}
		
		default:
			AvmAssert(false);
		}

		return;
	}


	void PoolObject::resolveQName(uint32_t index, Multiname &m, const Toplevel* toplevel) const
	{
		if (index == 0 || index >= cpool_mn_offsets.size())
		{
			if (toplevel)
				toplevel->throwVerifyError(kCpoolIndexRangeError, core->toErrorString(index), core->toErrorString(cpool_mn_offsets.size()));
			AvmAssert(!"unhandled verify error");
		}

		parseMultiname(m, index);

		if (!isBuiltin && !m.isQName())
		{
			if (toplevel)
				toplevel->throwVerifyError(kCpoolEntryWrongTypeError, core->toErrorString(index));
			AvmAssert(!"unhandled verify error");
		}
	}

	Traits* PoolObject::resolveTypeName(uint32_t index, const Toplevel* toplevel, bool allowVoid/*=false*/) const
	{
		// only save the type name for now.  verifier will resolve to traits
		if (index == 0)
		{
			return NULL;
		}

		// check contents is a multiname.  in the cpool, and type system, kObjectType means multiname.
		if (index >= cpool_mn_offsets.size())
		{
			if (toplevel)
				toplevel->throwVerifyError(kCpoolIndexRangeError, core->toErrorString(index), core->toErrorString(cpool_mn_offsets.size()));
			AvmAssert(!"unhandled verify error");
		}

		Multiname m;
		parseMultiname(m, index);
		
		Traits* t = getTraits(m, toplevel);
		if(m.isParameterizedType())
		{
			Traits* param_traits = resolveTypeName(m.getTypeParameter(), toplevel);
			t = resolveParameterizedType(toplevel, t, param_traits);
		}
		if (!t)
		{
			#ifdef AVMPLUS_VERBOSE
			if (!toplevel || !toplevel->verifyErrorClass())
				core->console << "class not found: " << m << " index=" << (uint32_t)index << "\n";
			#endif
			if (toplevel)
				toplevel->throwVerifyError(kClassNotFoundError, core->toErrorString(&m));
			AvmAssert(!"unhandled verify error");
		}
		if (!allowVoid && t == VOID_TYPE)
		{
			if (toplevel)
				toplevel->throwVerifyError(kIllegalVoidError);
			AvmAssert(!"unhandled verify error");
		}

		return t;
	}

	Traits* PoolObject::resolveParameterizedType(const Toplevel* toplevel, Traits* base, Traits* param_traits) const
	{
		Traits* r = NULL;
		if (base == core->traits.vector_itraits)
		{
			// Only vector is parameterizable for now...
			switch (Traits::getBuiltinType(param_traits))
			{
				case BUILTIN_any:
					r = core->traits.vectorobj_itraits;  
					break;
				case BUILTIN_int:
					r = core->traits.vectorint_itraits;
					break;
				case BUILTIN_uint:
					r = core->traits.vectoruint_itraits;
					break;
				case BUILTIN_number:
					r = core->traits.vectordouble_itraits;
					break;
				default:
				{
					Stringp fullname = VectorClass::makeVectorClassName(core, param_traits);
					r = param_traits->pool->getTraits(Multiname(base->ns(), fullname), toplevel);

					if (!r)
					{
						r = core->traits.vectorobj_itraits->newParameterizedITraits(fullname, base->ns());
						param_traits->pool->domain->addNamedTrait(fullname, base->ns(), r);
					}
					break;
				}
			}
		}
		return r;
	}

	void PoolObject::addPrivateNamedScript(Stringp name, Namespace* ns, MethodInfo *script)
	{
		_privateNamedScripts->add(name, ns, (Binding)script);
	}

	MethodInfo* PoolObject::getNamedScript(const Multiname* multiname) const
	{
		MethodInfo* f = domain->getNamedScript(multiname);
		if (!f)
		{
			f = (MethodInfo*)_privateNamedScripts->getMulti(multiname);
		}
		return f;
	}
	
#ifdef VMCFG_PRECOMP_NAMES
	void PoolObject::initPrecomputedMultinames()
	{
		if (this->precompNames == NULL)
        {
            size_t const s = sizeof(PrecomputedMultinames) - sizeof(Multiname) + this->cpool_mn_offsets.size() * sizeof(Multiname);
			this->precompNames = new (s) PrecomputedMultinames(core->GetGC(), this);
        }
    }

	PrecomputedMultinames::PrecomputedMultinames(MMgc::GC* gc, PoolObject* pool)
		: MMgc::GCRoot(gc)
		, nNames (0)
	{
		nNames = pool->cpool_mn_offsets.size();
		for (uint32_t i=1; i < nNames; i++) {
			Multiname mn;
			pool->parseMultiname(mn, i);
			mn.IncrementRef();
			multinames[i] = mn;
		}
	}
	
	PrecomputedMultinames::~PrecomputedMultinames() {
		for (uint32_t i=1; i < nNames; i++) 
			multinames[i].DecrementRef();
	}
#endif
	
#if VMCFG_METHOD_NAMES
	Stringp PoolObject::getMethodInfoName(uint32_t i)
	{
		Stringp name = NULL;
		if (core->config.methodNames && (uint32_t(i) < uint32_t(this->_method_name_indices.size())))
		{
			const int32_t index = this->_method_name_indices[i];
			if (index >= 0)
			{
				name = this->getString(index);
			}
			else
			{
#ifdef VMCFG_PRECOMP_NAMES
				// PrecomputedMultinames may not be inited yet, but we'll need them eventually,
				// so go ahead and init them now
				this->initPrecomputedMultinames();
				const Multiname& mn = this->precompNames->multinames[-index];
#else
				Multiname mn;
				this->parseMultiname(mn, -index);
#endif
				name = Multiname::format(core, mn.getNamespace(), mn.getName());
			}
		}
		return name;
	}
#endif	
}
