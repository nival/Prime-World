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
 * The Original Code is [ActiveScripting implemented with Tamarin].
 *
 * The Initial Developer of the Original Code is Mozilla Corp.
 * Portions created by the Initial Developer are Copyright (C) 2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Mark Hammond
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

#include "axtam.h"
#include "IUnknownConsumer.h"

#include <stdlib.h>

namespace axtam
{
	// On success, returns a new COM reference
	HRESULT IUnknownConsumer::get(const IID &iid, void **ret)
	{
		if (iid==this->iid) {
			ob.p->AddRef();
			*ret = (void **) ob.p;
		}
		return ob.p->QueryInterface(iid, ret);
	}

	BEGIN_NATIVE_MAP(IUnknownConsumerClass)
	END_NATIVE_MAP()

	IUnknownConsumerClass::IUnknownConsumerClass(VTable *cvtable)
		: ClassClosure(cvtable)
    {
		AXTam* core = (AXTam*)this->core();
		// should only be initialized once, but is currently done each time
		// we init builtins for a new domainenv.
		if (!core->unknownClass)
			core->unknownClass = this;

		createVanillaPrototype();
	}

	IUnknownConsumerClass::~IUnknownConsumerClass()
	{
	}

	// Function called as constructor ... not supported from user code
	IUnknownConsumer* IUnknownConsumerClass::create(IUnknown* p, const IID &iid)
	{
		VTable* ivtable = this->ivtable();
		IUnknownConsumer *o = new (core()->GetGC(), ivtable->getExtraSize()) IUnknownConsumer(ivtable, prototype, p, iid);
		return o;
	}
}