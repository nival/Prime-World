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

#ifndef __avmplus_NamespaceSet_inlines__
#define __avmplus_NamespaceSet_inlines__


namespace avmplus
{
    REALLY_INLINE NamespaceSetIterator::NamespaceSetIterator(const NamespaceSet* n) : 
        nsset(n), i(0) 
    { 
    }

    REALLY_INLINE bool NamespaceSetIterator::hasNext() const
    {
        return i < nsset->count();
    }

    REALLY_INLINE Namespacep NamespaceSetIterator::next()
    {
        AvmAssert(i < nsset->count());
        return nsset->nsAt(i++);
    }

    REALLY_INLINE NamespaceSet::NamespaceSet() 
    { 
        /* nothing */ 
    }

    REALLY_INLINE bool NamespaceSet::containsAnyPublicNamespace() const
    {
        return (_countAndFlags & 1) != 0;
    }

    REALLY_INLINE bool NamespaceSet::contains(Namespace* ns) const
    {
        for (uint32_t i=0,n=count(); i < n; i++)
            if (_namespaces[i] == ns)
                return true;
        return false;
    }

    REALLY_INLINE uint32_t NamespaceSet::count() const
    {
        return (_countAndFlags >> 1);
    }

    REALLY_INLINE Namespacep NamespaceSet::nsAt(uint32_t i) const
    {
        AvmAssert(i < count());
        AvmAssert(_namespaces[i] != NULL);
        return _namespaces[i];
    }

    REALLY_INLINE void NamespaceSet::_initNsAt(uint32_t i, Namespacep ns)
    {
        AvmAssert(i < count());
        AvmAssert(_namespaces[i] == NULL);
        AvmAssert(ns != NULL);
		WBRC(MMgc::GC::GetGC(this), this, &_namespaces[i], ns);
        // note that this flag is 'sticky'; it relies on a given slot being
        // initialized exactly once. (NamespaceSets are immutable once created,
        // but creation involves multiple calls to this method.)
        if (ns->isPublic())
            _countAndFlags |= 1;
    }
}

#endif /* __avmplus_NamespaceSet_inlines__ */
