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

REALLY_INLINE bool MultinameHashtable::matchNS(uintptr uri, API apis, Namespacep ns)
{
    AvmAssert(ns->getURI()->isInterned());
    return (apis & ns->m_api) && uri == ns->m_uri;
}

REALLY_INLINE Binding MultinameHashtable::get(Stringp name, NamespaceSetp nsset) const
{
    return getNSSet(name, nsset)->value;
}

REALLY_INLINE Binding MultinameHashtable::getMulti(const Multiname& name) const
{
    return getMulti(&name);
}

REALLY_INLINE Stringp MultinameHashtable::keyAt(int index) const
{
    AvmAssert(m_quads[index-1].name != NULL); return m_quads[index-1].name;
}

REALLY_INLINE Namespacep MultinameHashtable::nsAt(int index) const
{
    return m_quads[index-1].ns;
}

REALLY_INLINE Binding MultinameHashtable::valueAt(int index) const
{
    return m_quads[index-1].value;
}

REALLY_INLINE API MultinameHashtable::apisAt(int index) const
{
    return m_quads[index-1].apis;
}

REALLY_INLINE size_t MultinameHashtable::allocatedSize() const
{
    return numQuads * sizeof(Quad);
}

REALLY_INLINE StMNHTIterator::StMNHTIterator(MultinameHashtable* mnht) :
    m_mnht(mnht),
    m_cur(mnht->m_quads - 1),
    m_end(mnht->m_quads + mnht->numQuads)
{ }

REALLY_INLINE bool StMNHTIterator::next()
{
    return ++m_cur < m_end;
}

REALLY_INLINE Stringp StMNHTIterator::key() const
{
    AvmAssert(m_cur < m_end);
    return m_cur->name;
}

REALLY_INLINE Namespacep StMNHTIterator::ns() const
{
    return m_cur->ns;
}

REALLY_INLINE Binding StMNHTIterator::value() const
{
    return m_cur->value;
}

REALLY_INLINE API StMNHTIterator::apis() const
{
    return m_cur->apis;
}

} // namespace avmplus
