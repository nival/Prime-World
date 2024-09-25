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
#include "AdaptActiveScriptSite.h"
#include "mscom.h"

#include <stdlib.h>

namespace axtam
{
	AdaptActiveScriptSite::AdaptActiveScriptSite(VTable* vtable, ScriptObject* prototype, IActiveScriptSite *pSite)
		: ScriptObject(vtable, prototype)
	{
		// MarkH is quite confused about this - we are never constructed - presumably due to the
		// fact AS code is what creates us.
		//site = pSite;
	}

	ArrayObject *AdaptActiveScriptSite::GetItemInfo(Stringp name, unsigned flags)
	{
		AXTam* core = (AXTam *)this->core();
		CComPtr<IActiveScriptSite> site;
		HRESULT hr = core->as->GetScriptSite(IID_IActiveScriptSite, (void **)&site);
		if (FAILED(hr))
			core->throwCOMConsumerError(hr);
		CComPtr<IUnknown> unk;
		CComPtr<ITypeInfo> tlb;
		hr = site->GetItemInfo((OLECHAR *)name->c_str(), flags, &unk, &tlb);
		if (FAILED(hr))
			core->throwCOMConsumerError(hr);
		Atom vals[2] = {nullObjectAtom, nullObjectAtom};
		if (unk) {
			CComQIPtr<IDispatch, &IID_IDispatch> disp(unk);
			AvmAssert(disp!=0); // expect only IDispatch objects back!
			vals[0] = core->toAtom(disp);
		}
		if (tlb)
			vals[1] = core->toAtom((IUnknown *)tlb, __uuidof(ITypeInfo));
		ArrayObject *ret = toplevel()->arrayClass->newArray(2);
		ret->push(vals, 2);
		return ret;
	}


	int AdaptActiveScriptSite::OnEnterScript()
	{
		AXTam* core = (AXTam *)this->core();
		CComPtr<IActiveScriptSite> site;
		HRESULT hr = core->as->GetScriptSite(IID_IActiveScriptSite, (void **)&site);
		if (FAILED(hr))
			core->throwCOMConsumerError(hr);
		hr = site->OnEnterScript();
		return hr;
	}

	int AdaptActiveScriptSite::OnLeaveScript()
	{
		AXTam* core = (AXTam *)this->core();
		CComPtr<IActiveScriptSite> site;
		HRESULT hr = core->as->GetScriptSite(IID_IActiveScriptSite, (void **)&site);
		if (FAILED(hr))
			core->throwCOMConsumerError(hr);
		hr = site->OnLeaveScript();
		return hr;
	}

	int AdaptActiveScriptSite::OnStateChange(unsigned state)
	{
		AXTam* core = (AXTam *)this->core();
		CComPtr<IActiveScriptSite> site;
		HRESULT hr = core->as->GetScriptSite(IID_IActiveScriptSite, (void **)&site);
		if (FAILED(hr))
			core->throwCOMConsumerError(hr);
		hr = site->OnStateChange((SCRIPTSTATE)state);
		return hr;
	}

	BEGIN_NATIVE_MAP(AdaptActiveScriptSiteClass)
		NATIVE_METHOD(axtam_com_adaptors_consumer_IActiveScriptSite_GetItemInfo, AdaptActiveScriptSite::GetItemInfo)
		NATIVE_METHOD(axtam_com_adaptors_consumer_IActiveScriptSite_GetDocVersionString, AdaptActiveScriptSite::GetDocVersionString)
		NATIVE_METHOD(axtam_com_adaptors_consumer_IActiveScriptSite_OnEnterScript, AdaptActiveScriptSite::OnEnterScript)
		NATIVE_METHOD(axtam_com_adaptors_consumer_IActiveScriptSite_OnLeaveScript, AdaptActiveScriptSite::OnLeaveScript)
		NATIVE_METHOD(axtam_com_adaptors_consumer_IActiveScriptSite_OnStateChange, AdaptActiveScriptSite::OnStateChange)
	END_NATIVE_MAP()

	AdaptActiveScriptSiteClass::AdaptActiveScriptSiteClass(VTable *cvtable)
		: ClassClosure(cvtable)
    {
//		AXTam* core = (AXTam*)this->core();
		// should only be initialized once!
//		AvmAssert(!core->AdaptActiveScriptSiteClass);
//		core->AdaptActiveScriptSiteClass = this;

		createVanillaPrototype();
	}

	AdaptActiveScriptSiteClass::~AdaptActiveScriptSiteClass()
	{
	}

    /**
	// Function called as constructor ... not supported from user code
	AdaptActiveScriptSite* AdaptActiveScriptSiteClass::create(IUnknown* p, Atom obj)
	{
		VTable* ivtable = this->ivtable();
		AdaptActiveScriptSite *o = new (core()->GetGC(), ivtable->getExtraSize()) AdaptActiveScriptSite(ivtable, prototype, p);
		return o;
	}
***/
}
