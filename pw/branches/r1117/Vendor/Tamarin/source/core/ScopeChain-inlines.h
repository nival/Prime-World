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

REALLY_INLINE ScopeTypeChain::ScopeTypeChain(int32_t _size, int32_t _fullsize, Traits* traits)
    : size(_size), fullsize(_fullsize), _traits(traits)
{ }

REALLY_INLINE const ScopeTypeChain* ScopeTypeChain::createEmpty(MMgc::GC* gc, Traits* traits)
{
    return create(gc, traits, NULL, NULL, NULL, NULL);
}

REALLY_INLINE Traits* ScopeTypeChain::traits() const
{
    return _traits;
}

REALLY_INLINE Traits* ScopeTypeChain::getScopeTraitsAt(uint32_t i) const
{
    return (Traits*)(_scopes[i] & ~ISWITH);
}

REALLY_INLINE bool ScopeTypeChain::getScopeIsWithAt(uint32_t i) const
{
    return (_scopes[i] & ISWITH) != 0;
}

REALLY_INLINE void ScopeTypeChain::setScopeAt(uint32_t i, Traits* t, bool w)
{
    _scopes[i] = uintptr_t(t) | (w ? ISWITH : 0);
}

REALLY_INLINE ScopeChain::ScopeChain(VTable* vtable, AbcEnv* abcEnv, const ScopeTypeChain* scopeTraits, Namespacep dxns)
    : _vtable(vtable), _abcEnv(abcEnv), _scopeTraits(scopeTraits), _defaultXmlNamespace(dxns)
{ }

REALLY_INLINE VTable* ScopeChain::vtable() const
{
    return _vtable;
}

REALLY_INLINE AbcEnv* ScopeChain::abcEnv() const
{
    return _abcEnv;
}

REALLY_INLINE const ScopeTypeChain* ScopeChain::scopeTraits() const
{
    return _scopeTraits;
}

REALLY_INLINE int32_t ScopeChain::getSize() const
{
    return _scopeTraits->size;
}

REALLY_INLINE Atom ScopeChain::getScope(int32_t i) const
{
    AvmAssert(i >= 0 && i < _scopeTraits->size);
    return _scopes[i];
}

REALLY_INLINE Namespacep ScopeChain::getDefaultNamespace() const
{
    return _defaultXmlNamespace;
}

} // namespace avmplus
