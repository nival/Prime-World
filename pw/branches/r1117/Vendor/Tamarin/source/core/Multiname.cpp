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
	Namespacep Multiname::getNamespace(int32_t i) const
	{
		AvmAssert(!isRtns() && !isAnyNamespace());
		if (flags&NSSET)
		{
			AvmAssert(i >= 0 && i < namespaceCount());
			return nsset ? nsset->nsAt(i) : NULL;
		}
		else
		{
			AvmAssert(i == 0);
			return ns;
		}
	}

	bool Multiname::contains(Namespacep ns) const
	{
		if (flags & NSSET)
		{
            return nsset && nsset->contains(ns);
		}
		else
		{
			return this->ns == ns;
		}
	}

	bool Multiname::matches(const Multiname* qname) const
	{
		// For attributes (XML::getprop page 12)
		//if (((n.[[Name]].localName == "*") || (n.[[Name]].localName == a.[[Name]].localName)) &&
		//	((n.[[Name]].uri == nulll) || (n.[[Name]].uri == a.[[Name]].uri)))

		// For regular element props (XML::getprop page 12)
		//	if (n.localName = "*" OR m2 and (m2.localName == n.localName)
		//	and (!n.uri) or (m2) and (n.uri == m2.uri)))

		//Stringp n1 = core->string(this->name);

		if (qname)
		{
			//Stringp n2 = core->string(m2->name);

			if (this->isAttr() != qname->isAttr())
				return false;
		}

		// An anyName that is not qualified matches all properties
		if (this->isAnyName() && !this->isQName())
			return true;

		// Not an anyName, if m2 is valid, verify names are identical
		if (!this->isAnyName() && qname && (this->name != qname->getName()))
			return false;

		if (!qname)
			return false;

		if (this->isAnyNamespace())
			return true;

		// find a matching namespace between m2 and this
		// if no match return false
		Stringp u2 = qname->getNamespace()->getURI();
        uint8 type2 = (uint8)(qname->getNamespace()->getType());
		//Stringp s2 = core->string(u2);
		
		for (int i = 0; i < this->namespaceCount(); i++)
		{
			// We'd like to just compare namespace objects but we need
			// to check URIs since two namespaces with different prefixes
			// are considered a match
			Stringp u1 = getNamespace(i)->getURI();
            uint8 type1 = (uint8)(getNamespace(i)->getType());
			//Stringp s1 = core->string(u1);
			if (u1 == u2 && type1 == type2)
				return true;
		}

		return false;
	}

	/* static */ 
	Stringp Multiname::format(AvmCore *core, Namespacep ns, Stringp name, bool attr, bool hideNonPublicNamespaces)
	{
		if (ns->isPublic() ||
			(hideNonPublicNamespaces && // backwards compatibility
			ns->getType() != Namespace::NS_Public))
		{
			return name;
		}
		else
		{
			Stringp uri = ns->getURI();
			if (attr)
			{
				return core->concatStrings(core->newConstantStringLatin1("@"), core->concatStrings(uri,
					core->concatStrings(core->newConstantStringLatin1("::"), name)));
			}
			else
			{
				return core->concatStrings(uri,
					core->concatStrings(core->newConstantStringLatin1("::"), name));
			}
		}
	}

//#ifdef AVMPLUS_VERBOSE
	// Made available in non-AVMPLUS_VERBOSE builds for describeType
	Stringp Multiname::format(AvmCore* core , MultiFormat form) const
	{
		Stringp attr = this->isAttr() ? core->newConstantStringLatin1("@") : (Stringp)core->kEmptyString;
		Stringp name = this->isAnyName() 
			? core->newConstantStringLatin1("*") 
			: (this->isRtname()
				? core->newConstantStringLatin1("[]")
				: getName());

		if (isAnyNamespace())
		{
			return core->concatStrings(attr, core->concatStrings(core->newConstantStringLatin1("*::"), name));
		}
		else if (isRtns())
		{
			return core->concatStrings(attr, core->concatStrings(core->newConstantStringLatin1("[]::"), name));
		}
		else if (namespaceCount() == 1 && isQName()) 
		{
			return format(core, getNamespace(), core->concatStrings(attr,name), false, false);
		}
		else
		{
			// various switches
			bool showNs = (form == MULTI_FORMAT_FULL) || (form == MULTI_FORMAT_NS_ONLY);
			bool showName = (form == MULTI_FORMAT_FULL) || (form == MULTI_FORMAT_NAME_ONLY);
			bool showBrackets = (form == MULTI_FORMAT_FULL);
			Stringp s = attr;
			if (showNs)
			{
				if (showBrackets)
					s = core->concatStrings(s, core->newConstantStringLatin1("{"));

				for (int i=0,n=namespaceCount(); i < n; i++) 
				{			
					if (getNamespace(i)->isPublic())
						s = core->concatStrings(s, core->newConstantStringLatin1("public"));
					else
						s = core->concatStrings(s, getNamespace(i)->getURI());
					if (i+1 < n)
						s = core->concatStrings(s, core->newConstantStringLatin1(","));
				}

				if (showBrackets)
					s = core->concatStrings(s, core->newConstantStringLatin1("}::"));
			}

			if (showName)
				s = core->concatStrings(s, name);
			return s;
		}
	}
//#endif

	// NOTE NOTE NOTE
	// Write barrier note: the container for a HeapMultiname is *not* 'this'; 
	// HeapMultiname figures as a field in eg QNameObject and XMLListObject.
	// You *must* call FindBeginningFast(this) to get the right container.
	
	void HeapMultiname::setMultiname(const Multiname& that)
	{
		MMgc::GC* gc = this->gc();
		const void *container = gc->FindBeginningFast(this);
		WBRC(gc, container, &name.name, that.name);
		
		bool const this_nsset = name.isNsset() != 0;
		bool const that_nsset = that.isNsset() != 0;

		if (this_nsset != that_nsset)
		{
			// gc->rc or vice versa... we have to explicitly null out
			// any existing value (before setting a new one) because WB/WBRC
			// assume any existing value is a GCObject/RCObject respectively.
			if (this_nsset)
				WB_NULL(&name.ns);
			else
				WBRC_NULL(&name.ns);
		}

		if (that_nsset) 
		{
			WB(gc, container, &name.nsset, that.nsset);
		} 
		else 
		{
			WBRC(gc, container, &name.ns, that.ns);
		}

		name.flags = that.flags;
		name.next_index = that.next_index;
	}

	HeapMultiname::~HeapMultiname()
	{
		// Our embedded Multiname will zero itself, but we should call WBRC to 
		// adjust the refcounts correctly...
		WBRC_NULL(&name.name);
		if (!name.isNsset())
			WBRC_NULL(&name.ns);
	}
	
}
