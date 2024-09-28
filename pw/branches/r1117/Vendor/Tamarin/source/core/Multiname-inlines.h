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
 * Portions created by the Initial Developer are Copyright (C) 2009
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

REALLY_INLINE Stringp Multiname::getName() const
{
    AvmAssert(!isAnyName() && !isRtname());
    return name;
}

REALLY_INLINE void Multiname::setName(Stringp _name)
{
    AvmAssert(_name && _name->isInterned());
    this->flags &= ~RTNAME;
    this->name = _name;
}

REALLY_INLINE void Multiname::setName(const Multiname* other)
{
    // copy name settings from other
    flags &= ~RTNAME;
    flags |= other->flags & RTNAME;
    this->name = other->name;
}

REALLY_INLINE int32_t Multiname::namespaceCount() const
{
    return (nsset && (flags & NSSET)) ? nsset->count() : 1;
}

REALLY_INLINE Namespacep Multiname::getNamespace() const
{
    return getNamespace(0);
}

REALLY_INLINE void Multiname::setNamespace(Namespacep _ns)
{
    flags &= ~(NSSET|RTNS);
    AvmAssert(_ns != NULL);
    this->ns = _ns;
}

REALLY_INLINE void Multiname::setNamespace(const Multiname* other)
{
    // copy namespace settings from other
    flags &= ~(NSSET|RTNS);
    flags |= other->flags & (NSSET|RTNS);
    this->ns = other->ns;
}

REALLY_INLINE NamespaceSetp Multiname::getNsset() const
{
    AvmAssert(!isRtns() && (flags&NSSET));
    return nsset;
}

REALLY_INLINE void Multiname::setNsset(NamespaceSetp _nsset)
{
    flags &= ~RTNS;
    flags |= NSSET;
    AvmAssert(_nsset != NULL);
    this->nsset = _nsset;
}

REALLY_INLINE uint32_t Multiname::getTypeParameter() const
{
    AvmAssert(isParameterizedType());
    return next_index;
}

REALLY_INLINE void Multiname::setTypeParameter(uint32_t index)
{
    flags |= TYPEPARAM;
    this->next_index = index;
}

REALLY_INLINE Multiname::Multiname()
{
    this->name = NULL;
    this->ns = NULL;
    this->flags = 0;
    this->next_index = 0;
}

REALLY_INLINE Multiname::Multiname(NamespaceSetp nsset)
{
    this->name = NULL;
    this->nsset = nsset;
    this->flags = NSSET;
    this->next_index = 0;
}

REALLY_INLINE Multiname::Multiname(const Multiname &other)
{
    *this = other;
}

REALLY_INLINE Multiname::Multiname(Namespacep ns, Stringp name)
{
    AvmAssert(name && name->isInterned());
    this->name = name;
    this->ns = ns;
    this->flags = 0;
    this->next_index = 0;
}

REALLY_INLINE Multiname::Multiname(Namespacep ns, Stringp name, bool qualified)
{
    AvmAssert(name && name->isInterned());
    this->name = name;
    this->ns = ns;
    this->flags = 0;
    this->next_index = 0;
    if (qualified)
        setQName();
}

REALLY_INLINE Multiname::~Multiname()
{
    name = NULL;
    nsset = NULL;
    flags = 0;
    next_index = 0;
}

REALLY_INLINE bool Multiname::containsAnyPublicNamespace() const
{
    if (!nsset)
        return false; // note, also handles this->ns == null

    if (flags & NSSET)
    {
        return this->nsset->containsAnyPublicNamespace();
    }
    else
    {
        return this->ns->isPublic();
    }
}


/**
 * return the flags we want to keep when copying a compile-time
 * multiname into a runtime temporary multiname
 */
REALLY_INLINE int32_t Multiname::ctFlags() const
{
    return flags & ~(RTNS|RTNAME);
}

/**
 * returns true if this multiname could resolve to a binding.  Attributes,
 * wildcards, and runtime parts mean it can't match any binding.
 */
REALLY_INLINE int32_t Multiname::isBinding() const
{
    return !(flags & (ATTR|RTNS|RTNAME)) && name && ns;
}

REALLY_INLINE int32_t Multiname::isRuntime() const
{
    return flags & (RTNS|RTNAME);
}

REALLY_INLINE int32_t Multiname::isRtns() const
{
    return flags & RTNS;
}

REALLY_INLINE int32_t Multiname::isRtname() const
{
    return flags & RTNAME;
}

REALLY_INLINE int32_t Multiname::isQName() const
{
    return flags & QNAME;
}

REALLY_INLINE bool Multiname::isAttr() const
{
    return (bool) (flags & ATTR);
}

REALLY_INLINE bool Multiname::isAnyName() const
{
    return !isRtname() && !name;
}

REALLY_INLINE bool Multiname::isAnyNamespace() const
{
    return !isRtns() && !(flags&NSSET) && ns == NULL;
}

REALLY_INLINE int32_t Multiname::isNsset() const
{
    return flags & NSSET;
}

REALLY_INLINE bool Multiname::isValidDynamicName() const
{
    // return !isAnyName() && !isAttr() && containsAnyPublicNamespace();
    // consolidate the above to insure against compiler stupidity
    return ((flags & (ATTR|RTNAME)) == 0) && name != NULL && containsAnyPublicNamespace();
}

REALLY_INLINE int32_t Multiname::isParameterizedType() const
{
    return flags&TYPEPARAM;
}

REALLY_INLINE void Multiname::setAttr(bool b)
{
    if (b)
        flags |= ATTR;
    else
        flags &= ~ATTR;
}

REALLY_INLINE void Multiname::setQName()
{
    AvmAssert(namespaceCount()==1 && !(flags&NSSET));
    flags |= QNAME;
}

REALLY_INLINE void Multiname::setRtns()
{
    flags |= RTNS;
    flags &= ~NSSET;
    ns = NULL;
}

REALLY_INLINE void Multiname::setRtname()
{
    flags |= RTNAME;
    name = NULL;
}

REALLY_INLINE void Multiname::setAnyName()
{
    flags &= ~RTNAME;
    name = NULL;
}

REALLY_INLINE void Multiname::setAnyNamespace()
{
    flags &= ~(NSSET|RTNS);
    ns = NULL;
}

#ifdef VMCFG_PRECOMP_NAMES
REALLY_INLINE void Multiname::IncrementRef()
{
    if (name != NULL)
        name->IncrementRef();
    if (ns != NULL && (flags & NSSET) == 0)
        ns->IncrementRef();
}

REALLY_INLINE void Multiname::DecrementRef()
{
    if (name != NULL)
        name->DecrementRef();
    if (ns != NULL && (flags & NSSET) == 0)
        ns->DecrementRef();
}
#endif

REALLY_INLINE HeapMultiname::HeapMultiname()
{ /* our embedded Multiname inits itself to all zero */ }

REALLY_INLINE HeapMultiname::HeapMultiname(const Multiname& other)
{
    setMultiname(other);
}

REALLY_INLINE HeapMultiname::operator const Multiname* () const
{
    return &name;
}

REALLY_INLINE HeapMultiname::operator const Multiname& () const
{
    return name;
}

REALLY_INLINE const HeapMultiname& HeapMultiname::operator=(const HeapMultiname& that)
{
    if (this != &that)
    {
        setMultiname(that.name);
    }
    return *this;
}

REALLY_INLINE const HeapMultiname& HeapMultiname::operator=(const Multiname& that)
{
    setMultiname(that);
    return *this;
}

REALLY_INLINE Stringp HeapMultiname::getName() const
{
    return name.getName();
}

REALLY_INLINE int32_t HeapMultiname::namespaceCount() const
{
    return name.namespaceCount();
}

REALLY_INLINE Namespacep HeapMultiname::getNamespace(int32_t i) const
{
    return name.getNamespace(i);
}

REALLY_INLINE Namespacep HeapMultiname::getNamespace() const
{
    return name.getNamespace();
}

REALLY_INLINE NamespaceSetp HeapMultiname::getNsset() const
{
    return name.getNsset();
}

REALLY_INLINE bool HeapMultiname::contains(Namespacep ns) const
{
    return name.contains(ns);
}

REALLY_INLINE int32_t HeapMultiname::ctFlags() const
{
    return name.ctFlags();
}

REALLY_INLINE int32_t HeapMultiname::isBinding() const
{
    return name.isBinding();
}

REALLY_INLINE int32_t HeapMultiname::isRuntime() const
{
    return name.isRuntime();
}

REALLY_INLINE int32_t HeapMultiname::isRtns() const
{
    return name.isRtns();
}

REALLY_INLINE int32_t HeapMultiname::isRtname() const
{
    return name.isRtname();
}

REALLY_INLINE int32_t HeapMultiname::isQName() const
{
    return name.isQName();
}

REALLY_INLINE bool HeapMultiname::isAttr() const
{
    return name.isAttr();
}

REALLY_INLINE bool HeapMultiname::isAnyName() const
{
    return name.isAnyName();
}

REALLY_INLINE bool HeapMultiname::isAnyNamespace() const
{
    return name.isAnyNamespace();
}

REALLY_INLINE int32_t HeapMultiname::isNsset() const
{
    return name.isNsset();
}

REALLY_INLINE bool HeapMultiname::matches(const Multiname *mn) const
{
    return name.matches(mn);
}

REALLY_INLINE Stringp HeapMultiname::format(AvmCore* core, Multiname::MultiFormat form) const
{
    return name.format(core, form);
}

REALLY_INLINE Stringp HeapMultiname::format(AvmCore* core, Namespacep ns, Stringp name, bool attr,
                                            bool hideNonPublicNamespaces)
{
    return format(core, ns, name, attr, hideNonPublicNamespaces);
}

REALLY_INLINE MMgc::GC* HeapMultiname::gc() const
{
    return MMgc::GC::GetGC(this);
}

} // namespace avmplus
