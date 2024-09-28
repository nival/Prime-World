/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
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

namespace avmplus
{

REALLY_INLINE bool isAtomOrRCObjectSlot(SlotStorageType sst)
{
    return sst <= SST_scriptobject;
}

REALLY_INLINE SlotStorageType TraitsBindings::SlotInfo::sst() const
{
    return SlotStorageType(offsetAndSST & 7);
}

REALLY_INLINE uint32_t TraitsBindings::SlotInfo::offset() const
{
    return (offsetAndSST >> 3) << 2;
}

REALLY_INLINE TraitsBindings::TraitsBindings(Traits* _owner,
                    TraitsBindingsp _base,
                    MultinameHashtable* _bindings,
                    uint32_t _slotCount,
                    uint32_t _methodCount) :
    owner(_owner),
    base(_base),
    m_bindings(_bindings),
    slotCount(_slotCount),
    methodCount(_methodCount),
    m_slotSize(0)
{ }

REALLY_INLINE Traitsp TraitsBindings::getSlotTraits(uint32_t i) const
{
    AvmAssert(i < slotCount);
    return getSlots()[i].type;
}

REALLY_INLINE uint32_t TraitsBindings::getSlotOffset(uint32_t i) const
{
    AvmAssert(i < slotCount);
    return getSlots()[i].offset();
}

REALLY_INLINE SlotStorageType TraitsBindings::calcSlotAddrAndSST(uint32_t i, void* pin, void*& pout) const
{
    AvmAssert(i < slotCount);
    uint32_t offsetAndSST = getSlots()[i].offsetAndSST;
    pout = (void*)(((uint32_t*)pin) + (offsetAndSST >> 3));
    return SlotStorageType(offsetAndSST & 7);
}

REALLY_INLINE MethodInfo* TraitsBindings::getMethod(uint32_t i) const
{
    AvmAssert(i < methodCount);
    return getMethods()[i].f;
}

REALLY_INLINE int32_t TraitsBindings::next(int32_t index) const
{
    return m_bindings->next(index);
}

REALLY_INLINE Stringp TraitsBindings::keyAt(int32_t index) const
{
    return m_bindings->keyAt(index);
}

REALLY_INLINE Namespacep TraitsBindings::nsAt(int32_t index) const
{
    return m_bindings->nsAt(index);
}

REALLY_INLINE Binding TraitsBindings::valueAt(int32_t index) const
{
    return m_bindings->valueAt(index);
}

REALLY_INLINE TraitsBindings::SlotInfo* TraitsBindings::getSlots()
{
    return (SlotInfo*)(this + 1);
}

REALLY_INLINE const TraitsBindings::SlotInfo* TraitsBindings::getSlots() const
{
    return (const SlotInfo*)(this + 1);
}

REALLY_INLINE TraitsBindings::BindingMethodInfo* TraitsBindings::getMethods()
{
    return (BindingMethodInfo*)(getSlots() + slotCount);
}

REALLY_INLINE const TraitsBindings::BindingMethodInfo* TraitsBindings::getMethods() const
{
    return (const BindingMethodInfo*)(getSlots() + slotCount);
}

REALLY_INLINE void TraitsBindings::setSlotInfo(uint32_t i, Traits* t, SlotStorageType sst, uint32_t offset)
{
    AvmAssert(i < slotCount);
    // don't need WB here
    getSlots()[i].type = t;
    // offset is always a multiple of 4 so skip those, gives us a max of 1<<31-1
    AvmAssert((offset & 3) == 0);
    AvmAssert(offset <= MAX_SLOT_OFFSET);
    getSlots()[i].offsetAndSST = (offset<<1) | uint32_t(sst);
}

REALLY_INLINE void TraitsBindings::setMethodInfo(uint32_t i, MethodInfo* f)
{
    AvmAssert(i < methodCount);
    // don't need WB here
    getMethods()[i].f = f;
}

REALLY_INLINE StTraitsBindingsIterator::StTraitsBindingsIterator(TraitsBindingsp tb)
    : StMNHTIterator(tb->m_bindings), _tb(tb)
{ }

REALLY_INLINE TraitsMetadata::TraitsMetadata(TraitsMetadatap _base, PoolObject* _residingPool, MetadataPtr _metadata_pos, uint32_t _slotCount, uint32_t _methodCount)
    : base(_base),
    residingPool(_residingPool),
    slotCount(_slotCount),
    methodCount(_methodCount),
    metadataPos(_metadata_pos),
    slotMetadataPos(NULL),
    methodMetadataPos(NULL)
{ }

REALLY_INLINE TraitsMetadata::MetadataPtr TraitsMetadata::getMetadataPos(PoolObject*& residingPool) const
{
    residingPool = this->residingPool;
    return metadataPos;
}

REALLY_INLINE uint16_t Traits::getSizeOfInstance() const
{
    return m_sizeofInstance;
}

REALLY_INLINE uint32_t Traits::getHashtableOffset() const
{
    AvmAssert(linked);
    return m_hashTableOffset;
}

REALLY_INLINE uint32_t Traits::getTotalSize() const
{
    AvmAssert(linked);
    return m_totalSize;
}

REALLY_INLINE uint32_t Traits::getSlotAreaSize() const
{
    AvmAssert(linked);
    return getTotalSize() - m_sizeofInstance - (m_hashTableOffset ? sizeof(InlineHashtable) : 0);
}

// in bytes. includes size for all base classes too.
REALLY_INLINE uint32_t Traits::getExtraSize() const
{
    AvmAssert(linked);
    AvmAssert(getTotalSize() >= m_sizeofInstance);
    return getTotalSize() - m_sizeofInstance;
}

// sadly, it's still more efficient to stash this in Traits itself, as it's nontrivial to recover when
// we rebuild the TraitMethodInfo.
REALLY_INLINE void Traits::setMetadataPos(const byte* pos)
{
    AvmAssert(metadata_pos == NULL);
    metadata_pos = pos;
}

REALLY_INLINE Traits* Traits::newParameterizedITraits(Stringp name, Namespacep ns)
{
    return _newParameterizedTraits(name, ns, this);
}

REALLY_INLINE Traits* Traits::newParameterizedCTraits(Stringp name, Namespacep ns)
{
    return _newParameterizedTraits(name, ns, this->base);
}

REALLY_INLINE TraitsBindingsp Traits::getTraitsBindings()
{
    AvmAssert(this->linked);
    AvmAssert(m_tbref != NULL);
    TraitsBindings* tb;
    if ((tb = (TraitsBindings*)m_tbref->get()) == NULL)
        tb = _getTraitsBindings();
    return tb;
}

REALLY_INLINE TraitsMetadatap Traits::getTraitsMetadata()
{
    AvmAssert(this->linked);
    AvmAssert(m_tmref != NULL);
    TraitsMetadata* tm;
    if ((tm = (TraitsMetadata*)m_tmref->get()) == NULL)
        tm = _getTraitsMetadata();
    return tm;
}

REALLY_INLINE bool Traits::containsInterface(Traitsp t)
{
    return subtypeof(t);
}

REALLY_INLINE bool Traits::subtypeof(Traitsp t)
{
    // test primary supertypes or positive cache hit
    size_t off = t->m_supertype_offset;
    if (t == *((Traits**)(uintptr_t(this)+off)))
        return true;

    // return false if t was primary and not found, or if negative cache hit
    if (off != offsetof(Traits, m_supertype_cache) || t == m_supertype_neg_cache)
        return false;

    // check self because it won't be in m_secondary_supertypes
    if (this == t)
        return true;

    return secondary_subtypeof(t);
}

REALLY_INLINE bool Traits::isPrimary() const
{
    return m_supertype_offset != offsetof(Traits, m_supertype_cache);
}

REALLY_INLINE BuiltinType Traits::getBuiltinType(const Traitsp t)
{
    return t ? BuiltinType(t->builtinType) : BUILTIN_any;
}

REALLY_INLINE bool Traits::notDerivedObjectOrXML() const
{
    return ((1<<builtinType) & NOT_DERIVED_OR_XML_MASK) != 0;
}

REALLY_INLINE bool Traits::isMachineType() const
{
    return ((1<<builtinType) & MACHINE_TYPE_MASK) != 0;
}

REALLY_INLINE bool Traits::isNumeric() const
{
    return ((1<<builtinType) & NUMERIC_TYPE_MASK) != 0;
}

REALLY_INLINE bool Traits::isXMLType() const
{
    return ((1<<builtinType) & XML_TYPE_MASK) != 0;
}

REALLY_INLINE bool Traits::isInstanceType() const
{
    return posType() == TRAITSTYPE_INSTANCE || posType() == TRAITSTYPE_INTERFACE;
}

REALLY_INLINE bool Traits::isInterface() const
{
    return posType() == TRAITSTYPE_INTERFACE;
}

REALLY_INLINE TraitsPosType Traits::posType() const
{
    return (TraitsPosType)(uint32_t)m_posType;
}

REALLY_INLINE bool Traits::isResolved() const
{
    return linked;
}

REALLY_INLINE bool Traits::isActivationTraits() const
{
    return posType() == TRAITSTYPE_ACTIVATION;
}

REALLY_INLINE bool Traits::needsHashtable() const
{
    AvmAssert(linked);
    return m_needsHashtable;
}

REALLY_INLINE void Traits::set_needsHashtable(bool v)
{
    AvmAssert(!linked);
    m_needsHashtable = v;
}

REALLY_INLINE void Traits::setCreateClassClosureProc(CreateClassClosureProc p)
{
    this->m_createClassClosure = p;
}

REALLY_INLINE CreateClassClosureProc Traits::getCreateClassClosureProc() const
{
    return m_createClassClosure;
}

REALLY_INLINE Namespacep Traits::ns() const
{
    return _ns;
}

REALLY_INLINE Stringp Traits::name() const
{
    return _name;
}

REALLY_INLINE void Traits::set_names(Namespacep p_ns, Stringp p_name)
{
    _ns = p_ns;
    _name = p_name;
}

// this returns true iff we implement an interface that is not implemented by our parent.
// essential for efficient building of IMT thunks.
REALLY_INLINE bool Traits::implementsNewInterfaces() const
{
    AvmAssert(linked);
    return m_implementsNewInterfaces;
}

REALLY_INLINE InterfaceIterator::InterfaceIterator(Traits* t)
{
    st = t->m_secondary_supertypes;
}

REALLY_INLINE InterfaceIterator::InterfaceIterator(const TraitsBindings* tb)
{
    st = tb->owner->m_secondary_supertypes;
}

REALLY_INLINE bool InterfaceIterator::hasNext()
{
    while (*st != NULL && !(*st)->isInterface())
        st++;
    return *st != NULL;
}

REALLY_INLINE Traits* InterfaceIterator::next()
{
    AvmAssert(*st != NULL && (*st)->isInterface());
    return *st++;
}

} // namespace avmplus
