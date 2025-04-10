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
	using namespace MMgc;

	// -------------------------------------------------------------------
	// -------------------------------------------------------------------
	// -------------------------------------------------------------------
	// -------------------------------------------------------------------

	/*static*/ TraitsBindings* TraitsBindings::alloc(GC* gc, 
												Traits* _owner, 
												TraitsBindingsp _base, 
												MultinameHashtable* _bindings, 
												uint32_t slotCount, 
												uint32_t methodCount)
	{
		const uint32_t extra = slotCount * sizeof(SlotInfo) + 
						methodCount * sizeof(MethodInfo);

		TraitsBindings* tb = new (gc, extra) TraitsBindings(_owner, _base, _bindings, slotCount, methodCount);
		if (_base)
		{
			if (_base->slotCount)
			{
				const SlotInfo* src = &_base->getSlots()[0];
				SlotInfo* dst = &tb->getSlots()[0];
				VMPI_memcpy(dst, src, _base->slotCount * sizeof(SlotInfo));
				AvmAssert(((_owner->isMachineType()) || (tb->owner->m_sizeofInstance >= _base->owner->m_sizeofInstance)));
			}
			if (_base->methodCount)
				VMPI_memcpy(&tb->getMethods()[0], &_base->getMethods()[0], _base->methodCount * sizeof(MethodInfo));
		}
		return tb;
	}

	Binding TraitsBindings::findBinding(Stringp name) const
	{
		for (TraitsBindingsp self = this; self; self = self->base)
		{
			const Binding b = self->m_bindings->getName(name);
			if (b != BIND_NONE)
				return b;
		}
		return BIND_NONE;
	}

	Binding TraitsBindings::findBinding(Stringp name, Namespacep ns) const
	{
		for (TraitsBindingsp self = this; self; self = self->base)
		{
			const Binding b = self->m_bindings->get(name, ns);
			if (b != BIND_NONE)
				return b;
		}
		return BIND_NONE;
	}

	Binding TraitsBindings::findBinding(Stringp name, NamespaceSetp nsset) const
	{
		for (TraitsBindingsp self = this; self; self = self->base)
		{
			const Binding b = self->m_bindings->get(name, nsset);
			if (b != BIND_NONE)
				return b;
		}
		return BIND_NONE;
	}

	Binding TraitsBindings::findBindingAndDeclarer(const Multiname& mn, Traitsp& declarer) const
	{
		if (mn.isBinding())
		{
			for (TraitsBindingsp self = this; self; self = self->base)
			{
				Namespacep foundns = NULL;
				Binding const b = self->m_bindings->getMulti(mn, foundns);
				if (b != BIND_NONE)
				{
					declarer = self->owner;

					// if the member is 'protected' then we have to do extra work,
					// as we may have found it in a descendant's protected namespace -- 
					// we have to bounce up the inheritance chain and check our parent's 
					// protected namespace.
					while (foundns == declarer->protectedNamespace)
					{
						Traitsp declParent = declarer->base;
						if (!declParent || declParent->protectedNamespace == NULL)
							break;

						Binding const bp = declParent->getTraitsBindings()->findBinding(mn.getName(), declParent->protectedNamespace);
						if (bp != b)
							break;

						// self->owner->core->console<<"bounce "<<declarer<<" to "<<declParent<<"\n";
						declarer = declParent;
						foundns = declParent->protectedNamespace;
					}

					// self->owner->core->console<<"final declarer is "<<declarer<<"\n";
					return b;
				}
			}
		}
		declarer = NULL;
		return BIND_NONE;
	}

	void TraitsBindings::buildSlotDestroyInfo(MMgc::GC* gc, FixedBitSet& slotDestroyInfo, uint32_t slotAreaCount, uint32_t slotAreaSize) const
	{
		MMGC_STATIC_ASSERT(kUnusedAtomTag == 0 && kObjectType == 1 && kStringType == 2 && kNamespaceType == 3);
		AvmAssert(slotAreaCount <= slotCount);
		
		// not the same as slotCount since a slot of type double
		// takes two bits (in 32-bit builds). note that the bits are
		// always 4-byte chunks even in 64-bit builds!
		const uint32_t bitsNeeded = slotAreaSize / sizeof(uint32_t);	// not sizeof(Atom)!
		AvmAssert(bitsNeeded * sizeof(uint32_t) == slotAreaSize);		// should be even multiple!
		// allocate one extra bit and use it for "all-zero"
		slotDestroyInfo.resize(gc, bitsNeeded+1);
		if (slotAreaSize > 0)
		{
			const uint32_t sizeofInstance = this->owner->getSizeOfInstance();
			const TraitsBindings::SlotInfo* tbs		= getSlots() + (slotCount - slotAreaCount);
			const TraitsBindings::SlotInfo* tbs_end = tbs + slotAreaCount;
			for ( ; tbs < tbs_end; ++tbs) 
			{
				// offset is pointed off the end of our object
				if (isAtomOrRCObjectSlot(tbs->sst())) 
				{
					//owner->core->console<<"SDI "<<owner<<" "<<sizeofInstance<<" "<<tbs->type<<" "<<tbs->offset()<<"\n";
					AvmAssert(tbs->offset() >= sizeofInstance);
					const uint32_t off = tbs->offset() - sizeofInstance;
					AvmAssert((off % 4) == 0);
					// if slot is "big" then this is the bit of the first 4 bytes. that's fine.
					slotDestroyInfo.set((off>>2)+1);	// +1 to leave room for bit 0
					slotDestroyInfo.set(0);				// bit 0 is "anyset" flag
				} 
				// otherwise leave the bit zero
			}
		}
		else
		{
			AvmAssert(slotAreaCount == 0);
			AvmAssert(bitsNeeded == 0);
		}

		// if nothing set, blow away what we built and realloc as single clear bit -- smaller and faster
		if (!slotDestroyInfo.test(0))
		{
			slotDestroyInfo.resize(gc, 1);
			AvmAssert(!slotDestroyInfo.test(0));
		}
	}

	bool TraitsBindings::checkOverride(AvmCore* core, MethodInfo* virt, MethodInfo* over) const
	{
		if (over == virt)
			return true;
			
		MethodSignaturep overms = over->getMethodSignature();
		MethodSignaturep virtms = virt->getMethodSignature();

		Traits* overTraits = overms->returnTraits();
		Traits* virtTraits = virtms->returnTraits();

		if (overTraits != virtTraits)
		{
#ifdef AVMPLUS_VERBOSE
			core->console << "\n";
			core->console << "return types dont match\n";
			core->console << "   virt " << virtTraits << " " << virt << "\n";
			core->console << "   over " << overTraits << " " << over << "\n";
#endif
			return false;
		}
		
		if (overms->param_count() != virtms->param_count() ||
			overms->optional_count() != virtms->optional_count())
		{
#ifdef AVMPLUS_VERBOSE
			core->console << "\n";
			core->console << "param count mismatch\n";
			core->console << "   virt params=" << virtms->param_count() << " optional=" << virtms->optional_count() << " " << virt << "\n";
			core->console << "   over params=" << overms->param_count() << " optional=" << overms->optional_count() << " " << virt << "\n";
#endif
			return false;
		}

		// allow subclass param 0 to implement or extend base param 0
		virtTraits = virtms->paramTraits(0);
		if (!owner->subtypeof(virtTraits) || !Traits::isMachineCompatible(this->owner, virtTraits))
		{
			if (!this->owner->isMachineType() && virtTraits == core->traits.object_itraits)
			{
				over->setUnboxThis();
			}
			else
			{
				#ifdef AVMPLUS_VERBOSE
				core->console << "\n";
				core->console << "param 0 incompatible\n";
				core->console << "   virt " << virtTraits << " " << virt << "\n";
				core->console << "   over " << this->owner << " " << over << "\n";
				#endif
				return false;
			}
		}

		for (int k=1, p=overms->param_count(); k <= p; k++)
		{
			overTraits = overms->paramTraits(k);
			virtTraits = virtms->paramTraits(k);
			if (overTraits != virtTraits)
			{
				#ifdef AVMPLUS_VERBOSE
				core->console << "\n";
				core->console << "param " << k << " incompatible\n";
				core->console << "   virt " << virtTraits << " " << virt << "\n";
				core->console << "   over " << overTraits << " " << over << "\n";
				#endif
				return false;
			}
		}

		if (virt->unboxThis())
		{
			// the UNBOX_THIS flag is sticky, all the way down the inheritance tree
			over->setUnboxThis();
		}

		return true;
	}

	static bool isCompatibleOverrideKind(BindingKind baseKind, BindingKind overKind)
	{
		static const uint8_t kCompatibleBindingKinds[8] = 
		{
			0,														// BKIND_NONE
			(1<<BKIND_METHOD),										// BKIND_METHOD
			0,														// BKIND_VAR
			0,														// BKIND_CONST
			0,														// unused
			(1<<BKIND_GET) | (1<<BKIND_SET) | (1<<BKIND_GETSET),	// BKIND_GET
			(1<<BKIND_GET) | (1<<BKIND_SET) | (1<<BKIND_GETSET),	// BKIND_SET
			(1<<BKIND_GET) | (1<<BKIND_SET) | (1<<BKIND_GETSET)		// BKIND_GETSET
		};
		return (kCompatibleBindingKinds[baseKind] & (1<<overKind)) != 0;
	}

	bool TraitsBindings::checkLegalInterfaces(AvmCore* core) const
	{
		// make sure every interface method is implemented
		for (InterfaceIterator ifc_iter(this); ifc_iter.hasNext();)
		{
			Traits* ifc = ifc_iter.next();

			// don't need to bother checking interfaces in our parent.
			if (this->base && this->base->owner->subtypeof(ifc))
				continue;

			TraitsBindingsp ifcd = ifc->getTraitsBindings();
			StTraitsBindingsIterator iter(ifcd);
			while (iter.next())
			{
				Stringp name = iter.key();
				if (!name) continue;
				Namespacep ns = iter.ns();
				Binding iBinding = iter.value();
				const BindingKind iBindingKind = AvmCore::bindingKind(iBinding);

				Binding cBinding = this->findBinding(name, ns);
				if (!isCompatibleOverrideKind(iBindingKind, AvmCore::bindingKind(cBinding)))
				{
					// Try again with public namespace that matches the version of the current traits
					const Binding pBinding = this->findBinding(name, core->getPublicNamespace(owner->pool));
					if (isCompatibleOverrideKind(iBindingKind, AvmCore::bindingKind(pBinding)))
						cBinding = pBinding;
				}

				if (iBinding == cBinding) 
					continue;

				if (!isCompatibleOverrideKind(iBindingKind, AvmCore::bindingKind(cBinding)))
					return false;

				switch (iBindingKind)
				{
					default:
					{
						AvmAssert(0);	// interfaces shouldn't have anything but methods, getters, and setters
						return false;
					}
					case BKIND_METHOD:
					{
						MethodInfo* virt = ifcd->getMethod(AvmCore::bindingToMethodId(iBinding));
						MethodInfo* over = this->getMethod(AvmCore::bindingToMethodId(cBinding));
						if (!checkOverride(core, virt, over))
							return false;
						break;
					}
					case BKIND_GET:
					case BKIND_SET:
					case BKIND_GETSET:
					{
						// check getter & setter overrides
						if (AvmCore::hasGetterBinding(iBinding))
						{
							if (!AvmCore::hasGetterBinding(cBinding))
								return false;
							
							MethodInfo* virt = ifcd->getMethod(AvmCore::bindingToGetterId(iBinding));
							MethodInfo* over = this->getMethod(AvmCore::bindingToGetterId(cBinding));
							if (!checkOverride(core, virt, over))
								return false;
						}

						if (AvmCore::hasSetterBinding(iBinding))
						{
							if (!AvmCore::hasSetterBinding(cBinding))
								return false;
								
							MethodInfo* virt = ifcd->getMethod(AvmCore::bindingToSetterId(iBinding));
							MethodInfo* over = this->getMethod(AvmCore::bindingToSetterId(cBinding));
							if (!checkOverride(core, virt, over))
								return false;
						}
					}
					break;
				} // switch
			} // for j
		} // for tbi
		return true;
	}
	
	void TraitsBindings::fixOneInterfaceBindings(Traitsp ifc)
	{
		AvmAssert(!owner->isInterface());
		AvmAssert(ifc->linked);

		TraitsBindingsp ifcd = ifc->getTraitsBindings();
		StTraitsBindingsIterator iter(ifcd);
		while (iter.next())
		{
			Stringp name = iter.key();
			if (!name) continue;
			Namespacep ns = iter.ns();
			Binding iBinding = iter.value();
			const BindingKind iBindingKind = AvmCore::bindingKind(iBinding);
			const Binding cBinding = this->findBinding(name, ns);
			if (!isCompatibleOverrideKind(iBindingKind, AvmCore::bindingKind(cBinding)))
			{
				// Try again with public namespace that matches the version of the current traits
				const Binding pBinding = this->findBinding(name, ifc->core->getPublicNamespace(owner->pool));
				if (isCompatibleOverrideKind(iBindingKind, AvmCore::bindingKind(pBinding)))
				{
					this->m_bindings->add(name, ns, pBinding);
				}
			}
		}
	}
		
	void Traits::addVersionedBindings(MultinameHashtable* bindings,
									  Stringp name,
									  NamespaceSetp nss,
									  Binding binding) const
	{
		int32_t apis = 0;
		for (NamespaceSetIterator iter(nss); iter.hasNext();) 
        {
            Namespacep ns = iter.next();
			 apis |= ApiUtils::getCompatibleAPIs(core, ns->getAPI());
		}
		Namespacep ns = ApiUtils::getVersionedNamespace(core, nss->nsAt(0), apis);
		bindings->add(name, ns, binding);
	}
		
	// -------------------------------------------------------------------
	// -------------------------------------------------------------------

	TraitsMetadata::MetadataPtr TraitsMetadata::getSlotMetadataPos(uint32_t i, PoolObject*& residingPool) const
	{
		AvmAssert(i < slotCount);
		residingPool = NULL;
		for (TraitsMetadatap self = this; self && (i < self->slotCount); self = self->base)
		{
			MetadataPtr pos = self->slotMetadataPos[i];
			if (pos)
			{
				residingPool = self->residingPool;
				return pos;
			}
		}
		return NULL;
	}

	TraitsMetadata::MetadataPtr TraitsMetadata::getMethodMetadataPos(uint32_t i, PoolObject*& residingPool) const
	{
		AvmAssert(i < methodCount);
		residingPool = NULL;
		for (TraitsMetadatap self = this; self && (i < self->methodCount); self = self->base)
		{
			MetadataPtr pos = self->methodMetadataPos[i];
			if (pos)
			{
				residingPool = self->residingPool;
				return pos;
			}
		}
		return NULL;
	}

	// -------------------------------------------------------------------
	// -------------------------------------------------------------------

	Traits::Traits(PoolObject* _pool, 
				   Traits* _base,
				   uint16_t _sizeofInstance,
				   uint16_t _offsetofSlots,
				   TraitsPosPtr traitsPos,
				   TraitsPosType posType) :
		core(_pool->core),
		base(_base),
		pool(_pool),
		m_traitsPos(traitsPos),
		m_tbref(_pool->core->GetGC()->emptyWeakRef),
		m_tmref(_pool->core->GetGC()->emptyWeakRef),
		m_sizeofInstance(_sizeofInstance),
		m_offsetofSlots(_offsetofSlots),
		builtinType(BUILTIN_none),
		m_posType(uint8_t(posType)),
        // assume everything in builtin pools have custom construct unless stated otherwise
        hasCustomConstruct(_pool->isBuiltin)    
	{
		AvmAssert(m_tbref->get() == NULL);
		AvmAssert(m_tmref->get() == NULL);
		AvmAssert(BUILTIN_COUNT <= 32);
		AvmAssert(m_slotDestroyInfo.allocatedSize() == 0);
#ifdef _DEBUG
		switch (posType)
		{
			case TRAITSTYPE_NVA:
			case TRAITSTYPE_RT:
				AvmAssert(m_traitsPos == 0);
				break;
			default:
				AvmAssert(m_traitsPos != 0);
				break;
		}
#endif
		build_primary_supertypes();
		build_secondary_supertypes();
    }

	/*static*/ Traits* Traits::newTraits(PoolObject* pool,
							Traits *base,
							uint16_t objectSize,
							uint16_t offsetOfSlots,
							TraitsPosPtr traitsPos,
							TraitsPosType posType)
	{
		AvmAssert(posType != TRAITSTYPE_CATCH);
		AvmAssert(pool != NULL);
		Traits* traits = new (pool->core->GetGC()) Traits(pool, base, objectSize, offsetOfSlots, traitsPos, posType);
		return traits;
	}

	/*static*/ Traits* Traits::newCatchTraits(const Toplevel* toplevel, PoolObject* pool, TraitsPosPtr traitsPos, Stringp name, Namespacep ns)
	{
		AvmAssert(pool != NULL);
		Traits* traits = new (pool->core->GetGC()) Traits(pool, NULL, sizeof(ScriptObject), sizeof(ScriptObject), traitsPos, TRAITSTYPE_CATCH);
		traits->final = true;
		traits->set_names(ns, name);
		traits->resolveSignatures(toplevel);
		return traits;
	}

	Traits* Traits::_newParameterizedTraits(Stringp name, Namespacep ns, Traits* _base)
	{
		Traits* newtraits = Traits::newTraits(this->pool, _base, this->getSizeOfInstance(), this->m_offsetofSlots, NULL, TRAITSTYPE_RT);
		newtraits->m_needsHashtable = this->m_needsHashtable;
		newtraits->set_names(ns, name);
		return newtraits;
	}

	TraitsPosPtr Traits::traitsPosStart() const
	{
		TraitsPosPtr pos = m_traitsPos;
		switch (posType())
		{
			case TRAITSTYPE_INTERFACE:	
			case TRAITSTYPE_INSTANCE:	
				pos = skipToInstanceInitPos(pos);
				// fall thru, no break

			case TRAITSTYPE_CLASS:
			case TRAITSTYPE_SCRIPT:
				AvmCore::skipU30(pos, 1);		// skip in init_index
				break;

			case TRAITSTYPE_ACTIVATION:
				// nothing to do
				break;

			case TRAITSTYPE_CATCH:
			case TRAITSTYPE_NVA:
			case TRAITSTYPE_RT:
				pos = NULL;
				break;
		}
		return pos;
	}

	TraitsPosPtr Traits::skipToInstanceInitPos(TraitsPosPtr pos) const
	{
		AvmAssert(isInstanceType() && pos != NULL);
		AvmCore::skipU30(pos, 2);		// skip the QName & base traits 
		const uint8_t theflags = *pos++;		
		const bool hasProtected = (theflags & 8) != 0;
		if (hasProtected)
		{
			AvmCore::skipU30(pos);
		}
		const uint32_t interfaceCount = AvmCore::readU30(pos);
		AvmCore::skipU30(pos, interfaceCount);
		return pos;
	}

	static bool is8ByteSlot(Traits* slotTE)
	{
		#ifdef AVMPLUS_64BIT
		const uint32_t BIG_TYPE_MASK = ~((1U<<BUILTIN_int) | (1U<<BUILTIN_uint) | (1U<<BUILTIN_boolean));
		#else
		const uint32_t BIG_TYPE_MASK = (1U<<BUILTIN_number);
		#endif
		
		return ((1 << Traits::getBuiltinType(slotTE)) & BIG_TYPE_MASK) != 0;
	}

    // Sun compilers don't allow static and REALLY_INLINE
	/*static*/ REALLY_INLINE int32_t pad8(int32_t nextSlotOffset)
	{
		// 8-aligned, 8-byte field
		if (nextSlotOffset & 7)
		{
			AvmAssert((nextSlotOffset % 4) == 0);	// should always be a multiple of 4
			nextSlotOffset += 4;
		}
		int32_t slotOffset = nextSlotOffset;
		nextSlotOffset += 8;
		return slotOffset;
	}

	static SlotStorageType bt2sst(BuiltinType bt)
	{
		AvmAssert(bt != BUILTIN_void);
		switch (bt)
		{
			case BUILTIN_int:		return SST_int32;
			case BUILTIN_uint:		return SST_uint32;
			case BUILTIN_number:	return SST_double;
			case BUILTIN_boolean:	return SST_bool32;
			case BUILTIN_any:		return SST_atom;
			case BUILTIN_object:	return SST_atom;
			case BUILTIN_string:	return SST_string;
			case BUILTIN_namespace: return SST_namespace;
			default:				return SST_scriptobject;
		}
	}

    // Sun compilers don't allow static and REALLY_INLINE
	/*static*/ REALLY_INLINE bool isPointerSlot(Traits* slotTE)
	{
		BuiltinType bt = Traits::getBuiltinType(slotTE);
		AvmAssert(bt != BUILTIN_void);
		
		MMGC_STATIC_ASSERT(BUILTIN_COUNT < (sizeof(int) * 8));
		int const IS_POINTER = ~((1<<BUILTIN_int)|(1<<BUILTIN_uint)|(1<<BUILTIN_number)|(1<<BUILTIN_boolean));
		
		return ((1 << bt) & IS_POINTER) != 0;
	}

	// the logic for assigning slot id's is used in several places, so it's now collapsed here
	// rather than redundantly sprinkled thru several bits of code.
	class SlotIdCalcer
	{
	private:
		uint32_t m_slotCount;
		bool m_earlySlotBinding;
	public:
		SlotIdCalcer(uint32_t _baseSlotCount, bool _earlySlotBinding) : 
			m_slotCount(_baseSlotCount), 
			m_earlySlotBinding(_earlySlotBinding) 
		{
		}

		uint32_t calc_id(uint32_t id)
		{
			if (!id || !m_earlySlotBinding)
			{
				id = ++m_slotCount;
			}
			if (m_slotCount < id)
				m_slotCount = id;
			return id - 1;
		}
		
		uint32_t slotCount() const { return m_slotCount; }
	};
	
	struct NameEntry
	{
		const uint8_t* meta_pos;
		uint32_t qni, id, info, value_index;
		CPoolKind value_kind;
		TraitKind kind;
		uint8_t tag;
		
		void readNameEntry(const uint8_t*& pos);
	};
	
	void NameEntry::readNameEntry(const uint8_t*& pos)
	{
		qni = AvmCore::readU30(pos);
		tag = *pos++;
		kind = (TraitKind) (tag & 0x0f);
		value_kind = CONSTANT_unused_0x00;
		value_index = 0;

		// Read in the trait entry.
		switch (kind)
		{
			case TRAIT_Slot:
			case TRAIT_Const:
				id = AvmCore::readU30(pos);				// slot id
				info = AvmCore::readU30(pos);			// value type
				value_index = AvmCore::readU30(pos);	// value index
				if (value_index)
					value_kind = (CPoolKind)*pos++;		// value kind
				break;
			case TRAIT_Class:
				id = AvmCore::readU30(pos);		// slot id
				info = AvmCore::readU30(pos);	// classinfo
				break;
			case TRAIT_Getter:
			case TRAIT_Setter:
			case TRAIT_Method:
				AvmCore::skipU30(pos);			// disp id (never used)
				id = AvmCore::readU30(pos);		// method index
				info = 0;
				break;
			default:
				// unsupported traits type -- can't happen, caught in AbcParser::parseTraits
				AvmAssert(0);
				break;
		}
		meta_pos = pos;
		if (tag & ATTR_metadata)
		{
			uint32_t metaCount = AvmCore::readU30(pos);
			AvmCore::skipU30(pos, metaCount);
		}
	}
	
	bool Traits::allowEarlyBinding() const
	{
		// the compiler can early bind to a type's slots when it's defined
		// or when the base class came from another abc file and has zero slots
		// this ensures you cant use the early opcodes to access an external type's
		// private members.
		TraitsBindingsp tb = this->base ? this->base->getTraitsBindings() : NULL;
		while (tb != NULL && tb->slotCount > 0)
		{
			if (tb->owner->pool != this->pool && tb->slotCount > 0)
			{
				return false;
			}
			tb = tb->base;
		}
		return true;
	}

	void Traits::buildBindings(TraitsBindingsp basetb, 
								MultinameHashtable* bindings, 
								uint32_t& slotCount, 
								uint32_t& methodCount,
								uint32_t& n32BitNonPointerSlots,
								uint32_t& n64BitNonPointerSlots,
								const Toplevel* toplevel) const
	{
		const uint8_t* pos = traitsPosStart();

		const uint32_t baseSlotCount = basetb ? basetb->slotCount : 0;
		const uint32_t baseMethodCount = basetb ? basetb->methodCount : 0;

		//slotCount = baseSlotCount;
		methodCount = baseMethodCount;
		
		SlotIdCalcer sic(baseSlotCount, this->allowEarlyBinding());

		NameEntry ne;
		const uint32_t nameCount = pos ? AvmCore::readU30(pos) : 0;
		for (uint32_t i = 0; i < nameCount; i++)
		{
			ne.readNameEntry(pos);
			Multiname mn;
			this->pool->resolveQName(ne.qni, mn, toplevel);
			Stringp name = mn.getName();
			Namespacep ns;
			NamespaceSetp compat_nss;
			if (mn.namespaceCount() > 1) {
				ns = mn.getNsset()->nsAt(0);
				compat_nss = mn.getNsset();
			}
			else {
				ns = mn.getNamespace();
				compat_nss = NamespaceSet::create(core->GetGC(), ns);
			}
			
			switch (ne.kind)
			{
				case TRAIT_Slot:
				case TRAIT_Const:
				case TRAIT_Class:
				{
					uint32_t slot_id = sic.calc_id(ne.id);
					if (toplevel)
					{
						AvmAssert(!this->linked);
						
						// first time thru, we must do some additional verification checks... these were formerly 
						// done in AbcParser::parseTraits but require the base class to be resolved first, so we
						// now defer it to here.
						
						// illegal raw slot id.
						if (ne.id > nameCount)
							toplevel->throwVerifyError(kCorruptABCError);
						
						// slots are final.
						if (basetb && slot_id < basetb->slotCount) 
							toplevel->throwVerifyError(kIllegalOverrideError, core->toErrorString(mn), core->toErrorString(base));

						// a slot cannot override anything else.
						if (bindings->get(name, ns) != BIND_NONE)
							toplevel->throwVerifyError(kCorruptABCError);

						// In theory we should reject duplicate slots here; 
						// in practice we don't, as it causes problems with some existing content
						//if (basetb->findBinding(name, ns) != BIND_NONE)
						//	toplevel->throwVerifyError(kIllegalOverrideError, toplevel->core()->toErrorString(qn), toplevel->core()->toErrorString(this));
						
						// Interfaces cannot have slots.
						if (this->isInterface())
							toplevel->throwVerifyError(kIllegalSlotError, core->toErrorString(this));

					}
					AvmAssert(!(ne.id > nameCount));						// unhandled verify error
					AvmAssert(!(basetb && slot_id < basetb->slotCount));	// unhandled verify error
					AvmAssert(!(bindings->get(name, ns) != BIND_NONE));		// unhandled verify error
					addVersionedBindings(bindings, name, compat_nss, AvmCore::makeSlotBinding(slot_id, ne.kind==TRAIT_Slot ? BKIND_VAR : BKIND_CONST));
					Traitsp slotType = (ne.kind == TRAIT_Class) ? 
										pool->getClassTraits(ne.info) :
										pool->resolveTypeName(ne.info, toplevel);
					if (!isPointerSlot(slotType))
					{
						if (is8ByteSlot(slotType))
							++n64BitNonPointerSlots;
						else
							++n32BitNonPointerSlots;
					}
					break;
				}
				case TRAIT_Method:
				{
					Binding baseBinding = this->getOverride(basetb, ns, name, ne.tag, toplevel);
					if (baseBinding == BIND_NONE)
					{
						addVersionedBindings(bindings, name, compat_nss, AvmCore::makeMGSBinding(methodCount, BKIND_METHOD));
						// accessors require 2 vtable slots, methods only need 1.
						methodCount += 1;
					}
					else if (AvmCore::isMethodBinding(baseBinding))
					{
						// something got overridden, need new name entry for this subclass
						// but keep the existing disp_id
						addVersionedBindings(bindings, name, compat_nss, baseBinding);
					}
					else
					{
						if (toplevel)
							toplevel->throwVerifyError(kCorruptABCError);
						AvmAssert(!"unhandled verify error");
					}
					break;
				}
				case TRAIT_Getter:
				case TRAIT_Setter:
				{
					// if nothing already is defined in this class, use base class in case getter/setter has already been defined.
					Binding baseBinding = bindings->get(name, ns);
					if (baseBinding == BIND_NONE)
						baseBinding = this->getOverride(basetb, ns, name, ne.tag, toplevel);
						
					const BindingKind us = (ne.kind == TRAIT_Getter) ? BKIND_GET : BKIND_SET;
					const BindingKind them = (ne.kind == TRAIT_Getter) ? BKIND_SET : BKIND_GET;
					if (baseBinding == BIND_NONE)
					{
						addVersionedBindings(bindings, name, compat_nss, AvmCore::makeMGSBinding(methodCount, us));
						// accessors require 2 vtable slots, methods only need 1.
						methodCount += 2;
					}
					else if (AvmCore::isAccessorBinding(baseBinding))
					{
						// something maybe got overridden, need new name entry for this subclass
						// but keep the existing disp_id
						// both get & set bindings use the get id.	set_id = get_id + 1.
						if (AvmCore::bindingKind(baseBinding) == them)
						{
							baseBinding = AvmCore::makeGetSetBinding(baseBinding);
						}
						addVersionedBindings(bindings, name, compat_nss, baseBinding);
					}
					else
					{
						if (toplevel)
							toplevel->throwVerifyError(kCorruptABCError);
						AvmAssert(!"unhandled verify error");
					}
					break;
				}

				default:
					// unsupported traits type -- can't happen, caught in AbcParser::parseTraits
					AvmAssert(0);
					break;
			}
		} // for i
		slotCount = sic.slotCount();
	}
		
	namespace
	{
		// Don't mess with the order of the members of the
		// following struct.
		//
		// This struct is never actually instantiated, it is
		// only used to determine the default padding that C++
		// compiler will insert between 32 bit member variables and
		// 64 bit member variables.
		struct GlueClassTest_Slots
		{
			int32_t m_intSlot;
			double m_numberSlot;
			int32_t m_otherIntSlot;
			void* m_ptrSlot;
		};
		static const bool align8ByteSlots = (offsetof(GlueClassTest_Slots, m_numberSlot) == 8);
		static const bool alignPointersTo8Bytes = (offsetof(GlueClassTest_Slots, m_ptrSlot) == 24);
		static const bool is64Bit = sizeof(void*) == 8;
	}
	
    // Sun compilers don't allow static and REALLY_INLINE
	/*static*/ REALLY_INLINE int32_t computeSlotOffset(Traits* slotType, int32_t& next32BitSlotOffset, int32_t& nextPointerSlotOffset, int32_t& next64BitSlotOffset)
	{
		if (isPointerSlot(slotType))
		{
			int32_t const result = nextPointerSlotOffset;
			nextPointerSlotOffset += sizeof(void*);
			return result;
		}
		else if (is8ByteSlot(slotType))
		{
			int32_t const result = next64BitSlotOffset;
			next64BitSlotOffset += 8;
			return result;
		}
		else
		{
			int32_t const result = next32BitSlotOffset;
			next32BitSlotOffset += 4;
			return result;
		}
	}

    void Traits::computeSlotAreaCountAndSize(TraitsBindings* tb, uint32_t& slotCount, uint32_t& size) const
	{
		const TraitsBindings* prevBindings = tb;
		const TraitsBindings* currBindings = tb->base;
		uint32_t thisSize = getSizeOfInstance();
		while ((currBindings != NULL) && (currBindings->owner->getSizeOfInstance() == thisSize))
		{
			const TraitsBindings* baseBindings = currBindings->base;
			AvmAssert((baseBindings == 0) || (baseBindings->owner->getSizeOfInstance() <= thisSize)); (void)baseBindings;
			prevBindings = currBindings;
			currBindings = currBindings->base;
		}
		
		// currBindings is first ancestor class that is native with at least one slot or native member variable
		// or null if there is no native ancenstor class
		
		if (currBindings == NULL)
		{
			// We could not find a ancestor class that is native.
			slotCount = tb->slotCount;
			size = tb->m_slotSize;
		}
		else if (currBindings == tb->base)
		{
			AvmAssert(tb->base != NULL);
			AvmAssert((tb->base->slotCount == 0) || (tb->base->owner->getSizeOfInstance() <= thisSize));
			// "this" is a native class.
			slotCount = 0;
			size = 0;
		}
		else
		{
			AvmAssert(tb->base != NULL);
			AvmAssert(currBindings != NULL);
			AvmAssert(currBindings->owner->getSizeOfInstance() <= thisSize);
			AvmAssert(tb->slotCount >= prevBindings->slotCount);
			AvmAssert(tb->m_slotSize >= prevBindings->m_slotSize);
			slotCount = tb->slotCount - prevBindings->slotCount;
			size = tb->m_slotSize - prevBindings->m_slotSize;
		}
	}
	
	inline uint32_t Traits::computeSlotAreaStart(uint32_t nPointerSlots, uint32_t n32BitNonPointerSlots, uint32_t n64BitNonPointerSlots) const
	{
		// Actual size of slots can be larger because of padding inserted at beginning of slot area and between 4 byte slots and 8 byte slots.
		uint32_t minSizeOfSlots = (nPointerSlots * sizeof(void*)) + (n32BitNonPointerSlots * 4) + (n64BitNonPointerSlots * 8);
        uint32_t result = 0;
		if (base && minSizeOfSlots)
		{
			if (getSizeOfInstance() == base->getSizeOfInstance())
			{
				// we are not a native subclass or if we are, we don't have any slots.
				// Our slots start right after our base class slots.
				// The end of our base class slots is the same offset at which
				// our base class put its hash table.
				
				if (base->m_hashTableOffset)
					result = base->m_hashTableOffset;
				else
					result = base->getTotalSize();
			}
			else
			{
				// We are a native subclass
				// We should be bigger than our base class
				// Our slots are at the end of our instance class.
				AvmAssert(base->getSizeOfInstance() < getSizeOfInstance());
				AvmAssert((getSizeOfInstance() - base->getSizeOfInstance()) >= static_cast<intptr_t>(minSizeOfSlots));
				result = m_offsetofSlots;
				
				// result is an offset to a C++ class instance embedded in a glue class instance
				// If the C++ class instance containing the slot values contains 8 byte types that
				// are supposed to be 8 byte aligned, then result should also be 8 byte aligned.
				//
				// If either of these asserts fail, the slot offset calculation code in finishSlotsAndMethods
				// will most likely produce incorrect slot offsets for 8 byte slots.
                AvmAssert(((result % 8) == 0) || (!align8ByteSlots) || (n64BitNonPointerSlots == 0));
                AvmAssert(((result % 8) == 0) || (!alignPointersTo8Bytes) || (nPointerSlots == 0));
			}
		}
		else
		{
			AvmAssert((getSizeOfInstance() == sizeof(ScriptObject)) || (minSizeOfSlots == 0));
			result = getSizeOfInstance();
		}
        return result;
	}

	uint32_t Traits::finishSlotsAndMethods(TraitsBindingsp basetb, 
									TraitsBindings* tb, 
									const Toplevel* toplevel,
									AbcGen* abcGen,
									uint32_t n32BitNonPointerSlots,
									uint32_t n64BitNonPointerSlots) const
	{
		const uint8_t* pos = traitsPosStart();
		
		SlotIdCalcer sic(basetb ? basetb->slotCount : 0, this->allowEarlyBinding());
		uint32_t nBaseSlots = tb->base ? tb->base->slotCount : 0;
		uint32_t nPointerSlots = tb->slotCount - (n32BitNonPointerSlots + n64BitNonPointerSlots + nBaseSlots);
		
		int32_t slotAreaStart = computeSlotAreaStart(nPointerSlots, n32BitNonPointerSlots, n64BitNonPointerSlots);
		
		int32_t next32BitSlotOffset = slotAreaStart;
		int32_t endOf32BitSlots = next32BitSlotOffset + (n32BitNonPointerSlots * 4);
		int32_t nextPointerSlotOffset = alignPointersTo8Bytes && (nPointerSlots != 0) ? pad8(endOf32BitSlots) : endOf32BitSlots;
		int32_t endOfPointerSlots = nextPointerSlotOffset + (nPointerSlots * sizeof(void*));
		int32_t next64BitSlotOffset = align8ByteSlots && (n64BitNonPointerSlots != 0) ? pad8(endOfPointerSlots) : endOfPointerSlots;
		int32_t endOf64BitSlots = next64BitSlotOffset + (n64BitNonPointerSlots * 8);

		NameEntry ne;
		const uint32_t nameCount = pos ? AvmCore::readU30(pos) : 0;
		for (uint32_t i = 0; i < nameCount; i++)
		{
            AvmAssert(next32BitSlotOffset <= endOf32BitSlots);
            AvmAssert(nextPointerSlotOffset <= endOfPointerSlots);
			AvmAssert(next64BitSlotOffset <= endOf64BitSlots); (void)endOf64BitSlots;
			ne.readNameEntry(pos);
			Multiname mn;
			this->pool->resolveQName(ne.qni, mn, toplevel);
			Namespacep ns = mn.getNamespace();
			Stringp name = mn.getName();
			// NOTE only one versioned namespace from the set needed here

			switch (ne.kind)
			{
				case TRAIT_Slot:
				case TRAIT_Const:
				case TRAIT_Class:
				{
					AvmAssert(endOf64BitSlots > slotAreaStart);
					uint32_t slotid = sic.calc_id(ne.id);
					// note, for TRAIT_Class, AbcParser::parseTraits has already verified that pool->cinits[ne.info] is not null
					Traitsp slotType = (ne.kind == TRAIT_Class) ? 
										pool->getClassTraits(ne.info) :
										pool->resolveTypeName(ne.info, toplevel);
					uint32_t slotOffset = computeSlotOffset(slotType, next32BitSlotOffset, nextPointerSlotOffset, next64BitSlotOffset);
					AvmAssert(slotOffset >= sizeof(ScriptObject));
					tb->setSlotInfo(slotid, slotType, bt2sst(getBuiltinType(slotType)), slotOffset);
					
					if (abcGen)
						genDefaultValue(ne.value_index, slotid, toplevel, slotType, ne.value_kind, *abcGen);
					break;
				}
				case TRAIT_Getter:
				case TRAIT_Setter:
				case TRAIT_Method:
				{
					const Binding b = tb->m_bindings->get(name, ns);
					AvmAssert(b != BIND_NONE);
					const uint32 disp_id = uint32(uintptr_t(b) >> 3) + (ne.kind == TRAIT_Setter);
					MethodInfo* f = this->pool->getMethodInfo(ne.id);
					//AvmAssert(f->declaringTraits() == this);
					tb->setMethodInfo(disp_id, f);
					break;
				}

				default:
					// unsupported traits type -- can't happen, caught in AbcParser::parseTraits
					AvmAssert(0);
					break;
			}
		} // for i
		
		// check for sparse slot table -- anything not specified will default to * (but we must allocate space for it)
		for (uint32_t i = 0; i < tb->slotCount; i++)
		{
			if (tb->getSlotOffset(i) > 0)
				continue;

			#ifdef AVMPLUS_VERBOSE
			if (pool->isVerbose(VB_traits))
			{
				core->console << "WARNING: slot " << i+1 << " on " << this << " not defined by compiler.  Using *\n";
			}
			#endif

			const Traitsp slotType = NULL;
			const uint32_t slotOffset = nextPointerSlotOffset;
			nextPointerSlotOffset += sizeof(void*);
			AvmAssert(slotOffset >= sizeof(ScriptObject));
			tb->setSlotInfo(i, slotType, SST_atom, slotOffset);
		}
		
		AvmAssert(next32BitSlotOffset == endOf32BitSlots);
		AvmAssert(nextPointerSlotOffset == endOfPointerSlots);
		AvmAssert(next64BitSlotOffset == endOf64BitSlots);
		AvmAssert(endOf64BitSlots >= slotAreaStart);
		return endOf64BitSlots - slotAreaStart;
	}

	static const uint8_t* skipToInterfaceCount(const uint8_t* pos)
	{
		AvmAssert(pos != NULL);
		AvmCore::skipU30(pos, 2);		// skip the QName + basetraits
		const uint8_t theflags = *pos++;		
		if (theflags & 8)
			AvmCore::skipU30(pos);	// skip protected namespace
		return pos;
	}

	// Apps often have many interfaces redundantly listed, so first time thru,
	// eliminate redundant ones.  We do this by only adding new interfaces to
	// the "seen" list and only traversing new super-interfaces.  An interface
	// is NEW if our base class does not implement it.
	uint32_t Traits::countNewInterfaces(List<Traitsp, LIST_GCObjects>& seen)
	{
		// each Traits* added to this list is rooted via Domain and PoolObject,
		// so it is okay for this Stack to be opaque to the GC.
		Stack<Traits*> pending;
		pending.add(this);
		while (!pending.isEmpty()) {
			Traits* t = pending.pop();
			const uint8_t* pos = skipToInterfaceCount(t->m_traitsPos);
			const uint32_t interfaceCount = AvmCore::readU30(pos);
			for (uint32_t j = 0; j < interfaceCount; j++) {
				// we know all interfaces have been resolved already, it is done
				// before traits construction in AbcParser::parseInstanceInfos().
				Traitsp intf = t->pool->resolveTypeName(pos, NULL);
				AvmAssert(intf && intf->isInterface() && intf->base == NULL);
				// an interface can "extend" multiple other interfaces, so we must recurse here.
				if ((!base || !base->subtypeof(intf)) && seen.indexOf(intf) < 0) {
					seen.add(intf);
					pending.add(intf);
				}
			}
		}
		return seen.size();
	}

	static uint8_t calcLog2(uint32_t cap)
	{
		uint8_t capLog = 1; // start with at least 2 entries
		while ((1U<<capLog) < cap)
		{
			++capLog;
		}
		AvmAssert((1U<<capLog) >= cap);
		return capLog;
	}

	TraitsBindings* Traits::_buildTraitsBindings(const Toplevel* toplevel, AbcGen* abcGen)
	{
		// no, this can be called before the resolved bit is set
		//AvmAssert(this->linked);
#ifdef AVMPLUS_VERBOSE
		if (pool->isVerbose(VB_traits))
		{
			core->console << "Generate TraitsBindings for "<<this<<"\n";
		}
#endif
		TraitsBindings* thisData = NULL;

		// if we know the cap we need, go there right away, otherwise start at small power of 2
		// this saves tremendously on subsequent builds of this set of bindings since we don't have to
		// waste time growing the MNHT as we build it
		const int32_t bindingCap = m_bindingCapLog2 ? (1 << m_bindingCapLog2) : 2;

		MMgc::GC* gc = core->GetGC();
		MultinameHashtable* bindings = new (gc) MultinameHashtable(bindingCap);
		AvmAssert(bindings->numQuads == bindingCap);
		
		if (this->posType() == TRAITSTYPE_CATCH)
		{
			const uint8_t* pos = m_traitsPos;

			Traits* t = this->pool->resolveTypeName(pos, toplevel);

			// this assumes we save name/ns in all builds, not just verbose
			NamespaceSetp nss = NamespaceSet::create(core->GetGC(), this->ns());
			NamespaceSetp compat_nss = nss;
			addVersionedBindings(bindings, this->name(), compat_nss, AvmCore::makeSlotBinding(0, BKIND_VAR));
			// bindings just need room for one slot binding
			thisData = TraitsBindings::alloc(gc, this, /*base*/NULL, bindings, /*slotCount*/1, /*methodCount*/0);
			thisData->setSlotInfo(0, t, bt2sst(getBuiltinType(t)), this->m_sizeofInstance);
			thisData->m_slotSize = is8ByteSlot(t) ? 8 : 4;
		}
		else
		{
			TraitsBindingsp basetb = this->base ? this->base->getTraitsBindings() : NULL;

			// Copy protected traits from base class into new protected namespace
			if (basetb && base->protectedNamespace && this->protectedNamespace)
			{
				StTraitsBindingsIterator iter(basetb);
				while (iter.next())
				{
					if (!iter.key()) continue;
					if (iter.ns() == base->protectedNamespace)
					{
						bindings->add(iter.key(), this->protectedNamespace, iter.value());
					}
				}
			}
			
			uint32_t slotCount = 0;
			uint32_t methodCount = 0;
			uint32_t n32BitNonPointerSlots = 0;
			uint32_t n64BitNonPointerSlots = 0;
			buildBindings(basetb, bindings, slotCount, methodCount, n32BitNonPointerSlots, n64BitNonPointerSlots, toplevel);
			
			thisData = TraitsBindings::alloc(gc, this, basetb, bindings, slotCount, methodCount);
			thisData->m_slotSize = finishSlotsAndMethods(basetb, thisData, toplevel, abcGen, n32BitNonPointerSlots, n64BitNonPointerSlots);

			if (basetb) {
				thisData->m_slotSize += basetb->m_slotSize;
			}

			if (!isInterface() && m_implementsNewInterfaces) {
				// fix up interface bindings
				for (InterfaceIterator it(this); it.hasNext(); ) {
					Traits* t = it.next();
					if (!base || !base->subtypeof(t)) {
						// new interface not implemented in base.
						thisData->fixOneInterfaceBindings(t);
					}
				}
			}
		}

		// hashtable (if we have one) must start on pointer-sized boundary...
		// much easier to always round slotsize up unconditionally rather than
		// only for cases with hashtable, so that's what we'll do. (MMgc currently
		// allocate in 8-byte increments anyway, so we're not really losing any space.)
		thisData->m_slotSize = (thisData->m_slotSize + (sizeof(uintptr_t)-1)) & ~(sizeof(uintptr_t)-1);
		
		// remember the cap we need
		if (m_bindingCapLog2 == 0)
			m_bindingCapLog2 = calcLog2(thisData->m_bindings->numQuads);	// remember capacity, not count
		AvmAssert(m_bindingCapLog2 > 0);

#ifdef AVMPLUS_VERBOSE
		if (pool->isVerbose(VB_traits))
		{
			core->console << this << " bindings\n";
			StTraitsBindingsIterator iter(thisData);
			while (iter.next())
			{
				core->console << iter.key() << ":" << (uint32_t)(uintptr_t)(iter.value()) << "\n";
			}
			core->console << this << " end bindings \n";
		}
#endif
		
		AvmAssert(m_tbref->get() == NULL);
		m_tbref = thisData->GetWeakRef();
		core->tbCache()->add(thisData);
		return thisData;
	}

	TraitsMetadata* Traits::_buildTraitsMetadata()
	{
		AvmAssert(this->linked);

#ifdef AVMPLUS_VERBOSE
		if (pool->isVerbose(VB_traits))
		{
			core->console << "Generate TraitsMetadata for "<<this<<"\n";
		}
#endif
		TraitsBindingsp td = this->getTraitsBindings();
		
		MMgc::GC* gc = core->GetGC();
		
		TraitsMetadatap basetm = this->base ? this->base->getTraitsMetadata() : NULL;

		const uint32_t extra = td->slotCount * sizeof(TraitsMetadata::MetadataPtr) + td->methodCount * sizeof(TraitsMetadata::MetadataPtr);

		TraitsMetadata* tm = new (gc, extra) TraitsMetadata(basetm, this->pool, this->metadata_pos, td->slotCount, td->methodCount);
		tm->slotMetadataPos = (TraitsMetadata::MetadataPtr*)(tm + 1);
		tm->methodMetadataPos = (TraitsMetadata::MetadataPtr*)(tm->slotMetadataPos + tm->slotCount);

		const uint8_t* pos = traitsPosStart();
		const uint32_t nameCount = pos ? AvmCore::readU30(pos) : 0;
		SlotIdCalcer sic(td->base ? td->base->slotCount : 0, this->allowEarlyBinding());
		NameEntry ne;
		for (uint32_t i = 0; i < nameCount; i++)
		{
			ne.readNameEntry(pos);
			switch (ne.kind)
			{
				case TRAIT_Class:
					AvmAssert(0);
					// classes shouldn't have metadata, but just fall thru just in case
				case TRAIT_Slot:
				case TRAIT_Const:
				{
					const uint32_t slot_id = sic.calc_id(ne.id);
					if (ne.tag & ATTR_metadata)
						tm->slotMetadataPos[slot_id] = ne.meta_pos;
					break;
				}
				case TRAIT_Getter:
				case TRAIT_Setter:
				case TRAIT_Method:
				{
					if (ne.tag & ATTR_metadata)
					{
						Multiname qn;
						// passing NULL for toplevel here, since it's only used if a verification error occurs -- 
						// but if there was one, we would have encountered it during AbcParser::parseTraits.
						this->pool->resolveQName(ne.qni, qn, /*toplevel*/NULL);
						const Binding b = td->findBinding(qn.getName(), qn.getNamespace());
						AvmAssert(b != BIND_NONE);
						const uint32 disp_id = uint32(uintptr_t(b) >> 3) + (ne.kind == TRAIT_Setter);
						tm->methodMetadataPos[disp_id] = ne.meta_pos;
					}
					break;
				}

				default:
					// unsupported traits type -- can't happen, caught in AbcParser::parseTraits
					AvmAssert(0);
					break;
			}
		} // for i
			
		AvmAssert(m_tmref->get() == NULL);
		m_tmref = tm->GetWeakRef();
		core->tmCache()->add(tm);
		return tm;
	}

	void Traits::init_declaringScopes(const ScopeTypeChain* stc) 
	{ 
		AvmAssert(linked);
		if (!linked)
			return;
		
		if (this->init)
			this->init->init_declaringScope(stc);

		{
			TraitsBindingsp tb = this->getTraitsBindings();
			const TraitsBindings::BindingMethodInfo* tbm		= tb->getMethods();
			const TraitsBindings::BindingMethodInfo* tbm_end	= tbm + tb->methodCount;
			for ( ; tbm < tbm_end; ++tbm) 
			{
				if (tbm->f == NULL)
					continue;
					
				if (tbm->f->declaringTraits() == this)
				{
					tbm->f->init_declaringScope(stc);
				}
			}
		}
	}

	/**
	 * add t to pending[] ahead of any existing entries that are
	 * subtypes or implementers of t, so that when we iterate through
	 * pending[] we will traverse the inheritance DAG top-down.
	 */
	void insertSupertype(Traits* t, List<Traits*> &pending) 
	{
		uint32_t i = 0; 
		for (uint32_t n = pending.size(); i < n; i++) {
			if (pending[i]->subtypeof(t)) {
				pending.insert(i, t);
				return;
			}
		}
		pending.add(t);
	}

	/**
	 * resolve this traits signatures by visiting all supertypes in
	 * top-down toplogical order, then resolving our own signatures.  The top-down
	 * order ensures that we resolve base classes and interfaces first, while
	 * avoiding recursion.
	 */
	void Traits::resolveSignatures(const Toplevel* toplevel)
	{
		// toplevel actually can be null, when resolving the builtin classes...
		// but they should never cause verification errors in functioning builds
		if (linked)
			return;

		List<Traits*> pending(core->gc);
		// copy primary supertypes into pending.
		// primary_supertypes[] is already in top-down order.
		for (int32_t i = 0; i < MAX_PRIMARY_SUPERTYPE; i++) {
			Traits* t = m_primary_supertypes[i];
			if (t == NULL || t == this)
				break;
			if (!t->linked)
				pending.add(t);
		}

		// copy other base types, and interfaces, into pending[] by 
		// and maintaining the partial ordering that each type's bases and
		// interfaces are visited before that type itself is visited.
		for (Traits** st = m_secondary_supertypes; *st != NULL; st++) {
			Traits* t = *st;
			if (t != this && !t->linked)
				insertSupertype(t, pending);
		}

		for (uint32_t i = 0, n = pending.size(); i < n; i++) {
			AvmAssert(!pending[i]->linked);
			pending[i]->resolveSignaturesSelf(toplevel);
		}

		this->resolveSignaturesSelf(toplevel);
	}

	/**
	 * This must be called before any method is verified or any
	 * instances are created.  It is not done eagerly in AbcParser
	 * because doing so would prevent circular type references between
	 * slots of cooperating classes.
	 *
	 * Resolve the type and position/width of each slot.
	 */
	void Traits::resolveSignaturesSelf(const Toplevel* toplevel)
	{
#ifdef DEBUG
		AvmAssert(!linked);
		// make sure our supertypes are resolved. (must be done before calling _buildTraitsBindings)
		for (Traits* t = this->base; t != NULL; t = t->base)
			AvmAssert(t->linked);
		for (Traits** st = this->m_secondary_supertypes; *st != NULL; st++)
			AvmAssert(*st == this || (*st)->linked);
#endif

		MMgc::GC* gc = core->GetGC();
		AbcGen gen(gc); 
		AbcGen *pgen;
#if defined(VMCFG_AOT)
         pgen = (!(this->init)) || (!(this->init->isCompiledMethod())) ? &gen : 0; 
#else
         pgen = &gen;
#endif	
 		TraitsBindings* tb = _buildTraitsBindings(toplevel, pgen);
		this->genInitBody(toplevel, gen);

		// leave m_tmref as empty, we don't need it yet

		uint32_t slotAreaSize = 0;
		uint32_t slotAreaCount = 0;

		switch (posType())
		{
			case TRAITSTYPE_INTERFACE:
			case TRAITSTYPE_INSTANCE:
			case TRAITSTYPE_CLASS:
			case TRAITSTYPE_SCRIPT:
			case TRAITSTYPE_ACTIVATION:
			case TRAITSTYPE_CATCH:
				computeSlotAreaCountAndSize(tb, slotAreaCount, slotAreaSize);
				m_totalSize = getSizeOfInstance() + slotAreaSize;
				break;
			case TRAITSTYPE_NVA:
			case TRAITSTYPE_RT:
				m_totalSize = getSizeOfInstance();
				break;
		}
		AvmAssert(m_totalSize >= m_sizeofInstance);
		if (m_needsHashtable || (base && base->base && base->m_hashTableOffset && !isXMLType()))
		{
			// round up total size to multiple of pointer size.
			m_totalSize = ((m_totalSize+(sizeof(uintptr_t)-1))&~(sizeof(uintptr_t)-1));
			m_hashTableOffset = m_totalSize;
			m_totalSize += sizeof(InlineHashtable);
			AvmAssert(builtinType == BUILTIN_boolean ? true : (m_hashTableOffset & 3) == 0);
			AvmAssert((m_hashTableOffset & (sizeof(uintptr_t)-1)) == 0);
			AvmAssert((m_totalSize & (sizeof(uintptr_t)-1)) == 0);
		}

		// make sure all the methods have resolved types
		{
			const TraitsBindings::BindingMethodInfo* tbm		= tb->getMethods();
			const TraitsBindings::BindingMethodInfo* tbm_end	= tbm + tb->methodCount;
			for ( ; tbm < tbm_end; ++tbm) 
			{
				// don't assert: could be null if only one of a get/set pair is implemented
				//AvmAssert(tbm->f != NULL);
				if (tbm->f != NULL)
				{
					tbm->f->resolveSignature(toplevel);
				}
			}
		}

		if (this->init != NULL)
			this->init->resolveSignature(toplevel);

		bool legal = true;
		TraitsBindingsp tbbase = tb->base;	// might be null

		if (tbbase && tbbase->methodCount > 0)
		{
			// check concrete overrides
			const TraitsBindings::BindingMethodInfo* basetbm		= tbbase->getMethods();
			const TraitsBindings::BindingMethodInfo* basetbm_end	= basetbm + tbbase->methodCount;
			const TraitsBindings::BindingMethodInfo* tbm			= tb->getMethods();
			for ( ; basetbm < basetbm_end; ++basetbm, ++tbm) 
			{
				if (basetbm->f != NULL && basetbm->f != tbm->f)
					legal &= tb->checkOverride(core, basetbm->f, tbm->f);
			}
		}

		if (legal && !this->isInterface())
		{
			legal &= tb->checkLegalInterfaces(core);
		}

		if (!legal)
		{
			AvmAssert(!linked);
			Multiname qname(ns(), name());
			if (toplevel)
				toplevel->throwVerifyError(kIllegalOverrideError, core->toErrorString(&qname), core->toErrorString(this));
			AvmAssert(!"unhandled verify error");
		}

		tb->buildSlotDestroyInfo(gc, m_slotDestroyInfo, slotAreaCount, slotAreaSize);

		linked = true;
	}
    
#ifdef VMCFG_AOT

    static inline void hookUpActivationTraitsInitMethodForTraitsMethod(AvmCore* core, Toplevel *toplevel, MethodInfo* m)
    {
        AvmAssert(m->needActivation());
		
		const AOTInfo* aotInfo = m->pool()->aotInfo;
        Traits* activationTraits = m->activationTraits();
        AvmAssert(activationTraits != NULL);
		
        AvmAssert(aotInfo->activationTraits != NULL);
		AvmAssert(m->method_id() < aotInfo->nActivationTraits);
        AvmAssert(aotInfo->activationTraits[m->method_id()] == activationTraits);
		
		AvmAssert(aotInfo->activationTraitsInitFunctions != NULL);
		// See comment in initActivationTraits about why this can be called more than once per Traits
		if (activationTraits->init == NULL) {
		if (aotInfo->activationTraitsInitFunctions[m->method_id()]) {
            NativeMethodInfo compiledMethodInfo;
            compiledMethodInfo.thunker = aotThunker;
            compiledMethodInfo.handler.function = aotInfo->activationTraitsInitFunctions[m->method_id()];
            activationTraits->init = new (core->gc) MethodInfo(MethodInfo::kInitMethodStub, activationTraits, &compiledMethodInfo);
        }
		m->resolveActivation(toplevel);
    }
    }

    void Traits::initActivationTraits(Toplevel *toplevel)
    {
		// Note: this can be called multiple times per Traits from initScript, which must call this in case it's needed
		// but is itself called once per Toplevel
        const uint8_t* pos = traitsPosStart();

        if (this->init->needActivation()) {
            MethodInfo* m = this->init;
            hookUpActivationTraitsInitMethodForTraitsMethod(core, toplevel, this->init);
        }

		NameEntry ne;
		const uint32_t nameCount = pos ? AvmCore::readU30(pos) : 0;
		for (uint32_t i = 0; i < nameCount; i++)
        {
			ne.readNameEntry(pos);

			switch (ne.kind)
            {
				case TRAIT_Slot:
				case TRAIT_Const:
				case TRAIT_Class:
                    break;
				case TRAIT_Method:
				case TRAIT_Getter:
				case TRAIT_Setter:
				{
					MethodInfo* m = pool->getMethodInfo(ne.id);
                    if (m->needActivation()) {
                        hookUpActivationTraitsInitMethodForTraitsMethod(core, toplevel, m);
                    }
                    break;
				}
				default:
					// unsupported traits type -- can't happen, caught in AbcParser::parseTraits
					AvmAssert(0);
					break;
            }
        } // for i
    }
#endif

	// static
	bool Traits::isMachineCompatible(const Traits* a, const Traits* b)
	{
		return (a == b) ||
			// *, Object, and Void are each represented as Atom
			((!a || a->builtinType == BUILTIN_object || a->builtinType == BUILTIN_void) &&
			(!b || b->builtinType == BUILTIN_object || b->builtinType == BUILTIN_void)) ||
			// all other non-pointer types have unique representations
			(a && b && !a->isMachineType() && !b->isMachineType());
	}

#if VMCFG_METHOD_NAMES
	Stringp Traits::format(AvmCore* core, bool includeAllNamespaces) const
	{
		if (name() != NULL)
			return Multiname::format(core, ns(), name(), false, !includeAllNamespaces);

		return core->concatStrings(core->newConstantStringLatin1("Traits@"),
									core->formatAtomPtr((uintptr)this));
	}
#endif

	void Traits::genDefaultValue(uint32_t value_index, uint32_t slot_id, const Toplevel* toplevel, Traitsp slotType, CPoolKind kind, AbcGen& gen) const
	{
		// toplevel actually can be null, when resolving the builtin classes...
		// but they should never cause verification errors in functioning builds
		//AvmAssert(toplevel != NULL);

		Atom value = pool->getLegalDefaultValue(toplevel, value_index, kind, slotType);
		switch (Traits::getBuiltinType(slotType))
		{
			case BUILTIN_any:
			case BUILTIN_object:
			{
				if (value == 0)
					return;

				break;
			}
			case BUILTIN_number:
			{
				if (AvmCore::number_d(value) == 0)
					return;
				break;
			}
			case BUILTIN_boolean:
			{
				AvmAssert((uintptr_t(falseAtom)>>3) == 0);
				if (value == falseAtom)
					return;
				
				AvmAssert(value == trueAtom);
				break;
			}
			case BUILTIN_uint:
			case BUILTIN_int:
			{
				if (value == (zeroIntAtom))
					return;

				break;
			}
			case BUILTIN_namespace:
			case BUILTIN_string:
			default:
			{
				if (AvmCore::isNull(value))
					return;

				break;
			}
		}

		gen.getlocalN(0);
		if (value == undefinedAtom)
			gen.pushundefined();
		else if (AvmCore::isNull(value))
			gen.pushnull();
		else if (value == core->kNaN)
			gen.pushnan();
		else if (value == trueAtom)
			gen.pushtrue();
		else
			gen.pushconstant(kind, value_index);
		gen.setslot(slot_id);				
	}

	void Traits::genInitBody(const Toplevel* toplevel, AbcGen& gen)
	{
		// if initialization code gen is required, create a new method body and write it to traits->init->body_pos
		if (gen.size() == 0)
			return;
		
		MMgc::GC* gc = core->GetGC();
		AbcGen newMethodBody(gc, uint32_t(16 + gen.size()));	// @todo 16 is a magic value that was here before I touched the code -- I don't know the significance

		// insert body preamble
		if (this->init) 
		{
			const uint8_t* pos = this->init->abc_body_pos();
			if (!pos) 
				toplevel->throwVerifyError(kCorruptABCError);

			uint32_t maxStack = AvmCore::readU30(pos);
			// the code we're generating needs at least 2
			maxStack = maxStack > 1 ? maxStack : 2;
			newMethodBody.writeInt(maxStack); // max_stack
			newMethodBody.writeInt(AvmCore::readU30(pos)); //local_count
			newMethodBody.writeInt(AvmCore::readU30(pos)); //init_scope_depth
			newMethodBody.writeInt(AvmCore::readU30(pos)); //max_scope_depth

			// skip real code length
			uint32_t code_length = AvmCore::readU30(pos);
		
			// if first instruction is OP_constructsuper keep it as first instruction
			if (*pos == OP_constructsuper)
			{
				gen.getBytes().insert(0, OP_constructsuper);
				// don't invoke it again later
				pos++;
				code_length--;
			}
			gen.abs_jump(pos, code_length); 
			
			// this handles an obscure case: we have already resolved the signature for this
			// and have a MethodSignature cached, but we just (potentially) increased the value of
			// max_stack above. This updates the cached value of max_stack (iff we have
			// a MethodSignature cached for this->init)
			this->init->update_max_stack(maxStack);
		}
		else 
		{
			// make one
			this->init = new (gc) MethodInfo(MethodInfo::kInitMethodStub, this);

			newMethodBody.writeInt(2); // max_stack
			newMethodBody.writeInt(1); //local_count
			newMethodBody.writeInt(1); //init_scope_depth
			newMethodBody.writeInt(1); //max_scope_depth

			gen.returnvoid();
		}

		newMethodBody.writeInt((uint32_t)gen.size()); // code length
		newMethodBody.writeBytes(gen.getBytes());

		// no exceptions, when we jump to the real code, we'll read the exceptions for that code
		newMethodBody.writeInt(0);

		// the verifier and interpreter don't read the activation traits so stop here
		uint8_t* newBytes = (uint8_t*) gc->Alloc(newMethodBody.size());
		VMPI_memcpy(newBytes, newMethodBody.getBytes().getData(), newMethodBody.size());
		this->init->set_abc_body_pos_wb(gc, newBytes);
	}

	void Traits::destroyInstance(ScriptObject* obj) const
	{
		AvmAssert(linked);

		InlineHashtable* ht = m_hashTableOffset ? obj->getTableNoInit() : NULL;

		// start by clearing native space to zero (except baseclasses)
		union {
			char* p_8;
			uint32_t* p;
		};
		p_8 = (char*)obj + sizeof(AvmPlusScriptableObject);
		AvmAssert((uintptr_t(p) % sizeof(uint32_t)) == 0);
		
		if (!m_slotDestroyInfo.test(0))
		{
			AvmAssert(m_slotDestroyInfo.cap() == 1);
			AvmAssert(m_totalSize >= (sizeof(AvmPlusScriptableObject) + (ht ? sizeof(InlineHashtable) : 0)));
			uint32_t sizeToZero = m_totalSize - (sizeof(AvmPlusScriptableObject) + (ht ? sizeof(InlineHashtable) : 0));
			AvmAssert((sizeToZero % sizeof(uint32_t)) == 0); // we assume all sizes are multiples of sizeof(uint32_t)
			
			// no RCObjects, so just zero it all... my, that was easy
			VMPI_memset(p, 0, sizeToZero);
		}
		else
		{
			uint32_t sizeToZero = m_sizeofInstance - uint32_t(sizeof(AvmPlusScriptableObject));
			AvmAssert((sizeToZero % sizeof(uint32_t)) == 0); // we assume all sizes are multiples of sizeof(uint32_t)
			VMPI_memset(p, 0, sizeToZero);
			p += (sizeToZero / sizeof(uint32_t));

			AvmAssert(m_slotDestroyInfo.cap() >= 1);
			AvmAssert((uintptr_t(p) % sizeof(uint32_t)) == 0);
			
			const uint32_t slotAreaSize = getSlotAreaSize();
			const uint32_t bitsUsed = slotAreaSize / sizeof(uint32_t);	// not sizeof(Atom)!
			for (uint32_t bit = 1; bit <= bitsUsed; bit++) 
			{
				if (m_slotDestroyInfo.test(bit))
				{
					#ifdef AVMPLUS_64BIT
					AvmAssert((uintptr_t(p) & 7) == 0);     // we had better be on an 8-byte boundary...
					#endif
					Atom a = *(const Atom*)p;
					RCObject* rc = NULL;
					if (atomKind(a) <= kNamespaceType)
					{
						rc = (RCObject*)atomPtr(a);
						if (rc)
						{
							AvmAssert(GC::GetGC(obj)->IsRCObject(rc));
							rc->DecrementRef();
						}
					}
				}
				*p++ = 0;
			}
		}

		// finally, zap the hashtable (if any)
		if(ht)
		{
			ht->destroy();
		}
		//for DictionaryObject also zero out the 
		//hashtable pointer stored at the offset address;
		if(isDictionary)
		{
			union {
				char* p_8;
				uintptr_t* ptr;
			};
			p_8 = (char*)obj + m_hashTableOffset;
			*ptr = 0;
		}
	}

	Stringp Traits::formatClassName()
	{
#ifdef VMCFG_CACHE_GQCN
        if (_fullname != NULL)
            return _fullname;
#endif

        Multiname qname(ns(), name());
        qname.setQName();
        StringBuffer buffer(core);
        buffer << qname;
        int length = buffer.length();
        if (length && buffer.c_str()[length-1] == '$') 
        {
            length--;
        } 
#ifndef VMCFG_CACHE_GQCN
        Stringp _fullname;
#endif
        _fullname = core->newStringUTF8(buffer.c_str(), length);
        return _fullname;
	}


	Binding Traits::getOverride(TraitsBindingsp basetb, Namespacep ns, Stringp name, int tag, const Toplevel* toplevel) const
	{
		Binding baseBinding = BIND_NONE;
		if (base)
		{
			const Namespacep lookupNS = (protectedNamespace == ns && base->protectedNamespace) ? (Namespacep)base->protectedNamespace : ns;
			AvmAssert(basetb != NULL);
			baseBinding = basetb->findBinding(name, lookupNS);
		}
		const BindingKind baseBindingKind = AvmCore::bindingKind(baseBinding);

		const TraitKind kind = TraitKind(tag & 0x0f);
		// some extra-picky compilers will complain about the values being out of
		// range for the comparison (if we use "kind") even with explicit int casting.
		// so recycle the expression for the assert.
		AvmAssert((tag & 0x0f) >= 0 && (tag & 0x0f) < TRAIT_COUNT); 

		static const uint8_t kDesiredKind[TRAIT_COUNT] = 
		{
			BKIND_NONE,						// TRAIT_Slot
			BKIND_METHOD,					// TRAIT_Method
			BKIND_GET,						// TRAIT_Getter
			BKIND_SET,						// TRAIT_Setter
			BKIND_NONE,						// TRAIT_Class
			BKIND_NONE,						// TRAIT_Function
			BKIND_NONE						// TRAIT_Const
		};

		const BindingKind desiredKind = BindingKind(kDesiredKind[kind]);
		const uint8_t dkMask = uint8_t(1 << desiredKind);

		// given baseBindingKind, what are legal desiredKinds?
		static const uint8_t kLegalBaseKinds[8] = 
		{
			(1<<BKIND_METHOD) | (1<<BKIND_GET) | (1<<BKIND_SET),	// BKIND_NONE
			(1<<BKIND_METHOD),										// BKIND_METHOD
			0,														// BKIND_VAR
			0,														// BKIND_CONST
			0,														// unused
			(1<<BKIND_GET) | (1<<BKIND_SET),						// BKIND_GET
			(1<<BKIND_GET) | (1<<BKIND_SET),						// BKIND_SET
			(1<<BKIND_GET) | (1<<BKIND_SET)							// BKIND_GETSET
		};

		if ((kLegalBaseKinds[baseBindingKind] & dkMask) == 0)
			goto failure;

		// given baseBindingKind, which desiredKinds *require* override?
		static const uint8_t kOverrideRequired[8] = 
		{
			0,														// BKIND_NONE
			(1<<BKIND_METHOD),										// BKIND_METHOD
			0,														// BKIND_VAR
			0,														// BKIND_CONST
			0,														// unused
			(1<<BKIND_GET),											// BKIND_GET
			(1<<BKIND_SET),											// BKIND_SET
			(1<<BKIND_GET) | (1<<BKIND_SET)							// BKIND_GETSET
		};
		
		if (((kOverrideRequired[baseBindingKind] & dkMask) ? ATTR_override : 0) != (tag & ATTR_override))
			goto failure;

		return baseBinding;

failure:

#ifdef AVMPLUS_VERBOSE
   		if (pool->isVerbose(VB_traits))
			core->console << "illegal override in "<< this << ": " << Multiname(ns,name) <<"\n";
#endif
		if (toplevel)
			toplevel->throwVerifyError(kIllegalOverrideError, toplevel->core()->toErrorString(Multiname(ns,name)), toplevel->core()->toErrorString(this));
		AvmAssert(!"unhandled verify error");
		return BIND_NONE;
	}

	TraitsBindings* FASTCALL Traits::_getTraitsBindings() 
	{ 
		AvmAssert(this->linked);
		// note: TraitsBindings are always built the first time in resolveSignature; this is only 
		// executed for subsequent re-buildings. Thus we pass NULL for toplevel (it's only used
		// for verification errors, but those will have been caught prior to this) and for
		// abcGen (since it only needs to be done once).
		TraitsBindings* tb = _buildTraitsBindings(/*toplevel*/NULL, /*abcGen*/NULL);
		return tb;
	}

	TraitsMetadata* FASTCALL Traits::_getTraitsMetadata() 
	{ 
		AvmAssert(this->linked);
		TraitsMetadata* tm = _buildTraitsMetadata();
		return tm;
	}

	// Count supertypes in the given list, like strlen().
	static uint32_t countSupertypes(Traits** list)
	{
		uint32_t n = 0;
		for (Traits** t = list; *t != NULL; t++)
			n++;
		return n;
	}

	// Initialize the m_primary_supertypes array by copying down the entries
	// from our base class (if it exists), and adding this traits if there is room.
	void Traits::build_primary_supertypes()
	{
		MMGC_STATIC_ASSERT(offsetof(Traits, m_primary_supertypes) + sizeof(m_primary_supertypes) < 256);
		MMGC_STATIC_ASSERT(offsetof(Traits, m_supertype_cache) < 256);

		// compute m_supertype_offset and fill in m_primary_supertypes
		if (!base) {
			// class roots and interfaces
			m_supertype_offset = isInterface() ? offsetof(Traits, m_supertype_cache) : offsetof(Traits, m_primary_supertypes);
			WB(core->gc, this, &m_primary_supertypes[0], this);
		} else {
			// single inherited classes
			AvmAssert(!isInterface());
			for (int i=0; i < MAX_PRIMARY_SUPERTYPE; i++)
				WB(core->gc, this, &m_primary_supertypes[i], base->m_primary_supertypes[i]);
			size_t off = base->m_supertype_offset;
			if (off != offsetof(Traits, m_supertype_cache) &&
				(off += sizeof(Traits*)) - offsetof(Traits, m_primary_supertypes) < sizeof(m_primary_supertypes)) {
				AvmAssert(off == (uint8_t) off);
				m_supertype_offset = uint8_t(off);
				WB(core->gc, this, (Traits*)(uintptr_t(this)+off), this);
			} else {
				// Inheritance is too deep to add this traits to m_primary_supertypes.
				// Make this traits "secondary", set m_supertype_offset to the cache.
				m_supertype_offset = offsetof(Traits, m_supertype_cache);
			}
		}
	}

	// Initialize the m_secondary_supertypes array as follows:
	//   * if this traits adds a new interface, create a new list with all
	//     the entries from the base class, plus the base class itself,
	//     plus the new interfaces
	//   * if we do not add new interfaces and there's no base class,
	//     use the empty list.
	//   * if there is a base class, and the base class is primary, just
	//     copy base->m_secondary_supertypes (containing any base interfaces)
	//   * otherwise create a new secondary_supertypes list with everything
	//     from the base class, plus the base class itself.  Install this list
	//     back in the base class so it can be shared by other leaf classes.
	void Traits::build_secondary_supertypes()
	{
		MMgc::GC* gc = core->GetGC();
		List<Traitsp, LIST_GCObjects> seen(gc);
		uint32_t count;
		if (!isInstanceType() || (count = countNewInterfaces(seen)) == 0) {
			// no new interfaces, attempt to share the base type's secondary list
			if (!base) {
				this->m_secondary_supertypes = core->_emptySupertypeList;
			} else {
				Traits** base_list = base->m_secondary_supertypes;
				// If we require base in our secondary_supertypes list, so will other
				// sibling leaf types.  Try to share the seconary_supertypes list by
				// inserting base at position 0.
				if (base->isPrimary() || base_list[0] == base) {
					// just copy the base list.
					this->m_secondary_supertypes = base_list;
				} else {
					// must prepend base to base_list, save the copy on this type and base.
					count = countSupertypes(base_list);
					Traits** list = allocSupertypeList(gc, count + 1);
					WB(gc, list, list, base);
					for (uint32_t i=0; i < count; i++)
						WB(gc, list, list+i+1, base_list[i]);
					base->m_secondary_supertypes = list;
					this->m_secondary_supertypes = list;
				}
			}
		} else {
			// this type implements new interfaces so we need a new list
			this->m_implementsNewInterfaces = true;
			if (base && !base->isPrimary() && base->m_secondary_supertypes[0] != base) {
				seen.add(base);
				count++;
			}
			Traits** list;
			uint32_t baseCount = base ? countSupertypes(base->m_secondary_supertypes) : 0;
			if (baseCount > 0) {
				uint32_t total = count + baseCount;
				list = allocSupertypeList(gc, total);
				for (Traits **d = list, **s = base->m_secondary_supertypes; *s != NULL; s++, d++)
					WB(gc, list, d, *s);
			} else {
				list = allocSupertypeList(gc, count);
			}
			this->m_secondary_supertypes = list;
			for (uint32_t i=0; i < count; i++) {
				WB(gc, list, list+baseCount+i, seen[i]);
			}
		}

#ifdef DEBUG
		// sanity check to make sure we don't have any duplicate supertypes.
		List<Traitsp, LIST_GCObjects> supertypes(gc);
		for (int i = 0; i < MAX_PRIMARY_SUPERTYPE; i++) {
			Traits* t = m_primary_supertypes[i];
			if (t != NULL) {
				if (supertypes.indexOf(t) != -1) {
					core->console << "t " << this << " dup primary " << t << "\n";
					AvmAssert(false);
				}
				supertypes.add(t);
			}
		}
		for (Traits** st = m_secondary_supertypes; *st != NULL; st++) {
			Traits* t = *st;
			if (supertypes.indexOf(t) != -1) {
				core->console << "t " << this << " dup secondary " << t << "\n";
				AvmAssert(false);
			}
			supertypes.add(t);
		}
#endif
	}

	// search interfaces and bases that didn't fit in m_primary_supertypes,
	// and cache positive/negative results
	bool Traits::secondary_subtypeof(Traits* t)
	{
		for (Traits** s = m_secondary_supertypes; *s != NULL; s++) {
			if (t == *s) {
				m_supertype_cache = t;
				return true;
			}
		}
		m_supertype_neg_cache = t;
		return false;
	}

	// create a new supertype list of the given length
	Traits** Traits::allocSupertypeList(GC* gc, uint32_t size)
	{
		return (Traits**) gc->Alloc((size+1) * sizeof(Traits*), MMgc::GC::kZero);
	}
}
