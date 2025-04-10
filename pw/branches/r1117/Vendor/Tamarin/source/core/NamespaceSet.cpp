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

namespace avmplus
{
	/*static*/ NamespaceSet* NamespaceSet::_create(MMgc::GC* gc, uint32_t count)
	{
        AvmAssert(count <= 0x7fffffff); // should be impossible since ABC only allow U30...
		size_t extra = (count >= 1 ? count-1 : 0)*sizeof(Namespacep);
		NamespaceSet* nsset = new (gc, extra) NamespaceSet;
        nsset->_countAndFlags = count<<1;
        return nsset;
	}

	/*static*/ const NamespaceSet* NamespaceSet::create(MMgc::GC* gc, Namespacep ns)
	{
		NamespaceSet* nsset = new (gc) NamespaceSet;
        nsset->_countAndFlags = (1<<1) | (ns->isPublic() ? 1 : 0);
        nsset->_namespaces[0] = ns;
        return nsset;
	}

//#ifdef AVMPLUS_VERBOSE
	// Made available in non-AVMPLUS_VERBOSE builds for describeType
	Stringp NamespaceSet::format(AvmCore* core) const
	{
		Stringp s = core->newConstantStringLatin1("{");
        bool comma = false;
		for (NamespaceSetIterator iter(this); iter.hasNext();) 
		{
            if (comma)
				s = core->concatStrings(s, core->newConstantStringLatin1(","));
            Namespacep ns = iter.next();
			if (ns->isPublic())
				s = core->concatStrings(s, core->newConstantStringLatin1("public"));
			else
				s = core->concatStrings(s, ns->getURI());
			comma = true;
		}
		s = core->concatStrings(s, core->newConstantStringLatin1("}"));
		return s;
	}
//#endif
}
