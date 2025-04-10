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
 *   Mark Hammond.
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
#include "IDispatchProvider.h"

using namespace axtam;

// IDispatch

STDMETHODIMP IDispatchProvider::GetTypeInfoCount(UINT* pctinfo)
{
	ATLTRACENOTIMPL(_T("IDispatchProvider::GetTypeInfoCount"));
}
STDMETHODIMP IDispatchProvider::GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
{
	ATLTRACENOTIMPL(_T("IDispatchProvider::GetTypeInfo"));
}
STDMETHODIMP IDispatchProvider::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
                LCID lcid, DISPID* rgdispid)
{
	if (cNames != 1) {
		ATLTRACENOTIMPL(_T("IDispatchProvider::GetIDsOfNames (for more than 1 name)"));
		AvmAssert(0); // not reached.
	}
	return GetDispID(rgszNames[0], 0, rgdispid);
}

STDMETHODIMP IDispatchProvider::Invoke(DISPID dispidMember, REFIID riid,
				LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,
				EXCEPINFO* pexcepinfo, UINT* puArgErr)
{
	return InvokeEx(dispidMember, lcid, wFlags, pdispparams, pvarResult, pexcepinfo, NULL);
}

STDMETHODIMP IDispatchProvider::GetDispID(
			/* [in] */ BSTR bstrName,
			/* [in] */ DWORD grfdex,
			/* [out] */ DISPID *pid)
{
	Atom name = core->constant((wchar *)bstrName);

	stdext::hash_map<Atom, int>::iterator it = name2dispid.find(name);
	if(it != name2dispid.end()) {
		// this name already was assigned
		*pid = it->second;
		DISPID_ENTRY entry = dispid2info[*pid];
		if (entry.deleted) {
			AvmDebugMsg(false, "IDispatchProvider::GetDispID - name '%S' is deleted\n", bstrName);
			return DISP_E_UNKNOWNNAME;
		}
	} else {
		bool exists = ob->hasAtomProperty(name);
		if (exists || grfdex & fdexNameEnsure) {
			// must allocate one
			if (!exists)
				ob->setAtomProperty(name, undefinedAtom);
			*pid = allocNewDispid();
			name2dispid[name] = *pid;
			DISPID_ENTRY entry;
			entry.name = name;
			entry.deleted = false;
			dispid2info[*pid] = entry;
		} else {
			AvmDebugMsg(false, "IDispatchProvider::GetDispID - unknown name '%S'\n", bstrName);
			return DISP_E_UNKNOWNNAME;
		}
	}
	AvmDebugMsg(false, "IDispatchProvider::GetDispID - name '%S' has dispid=%d\n", bstrName, *pid);
	return S_OK;
}


STDMETHODIMP IDispatchProvider::InvokeEx(
			/* [in] */ DISPID id,
			/* [in] */ LCID lcid,
			/* [in] */ WORD wFlags,
			/* [in] */ DISPPARAMS *pdp,
			/* [out] */ VARIANT *pvarRes,
			/* [out] */ EXCEPINFO *pei,
			/* [unique][in] */ IServiceProvider *pspCaller)
{
	TRY(core, kCatchAction_ReportAsError) {
		HRESULT hr = S_OK;
		Atom ret = undefinedAtom;
		// handle the special DISPIDs first.
		if (id==DISPID_VALUE) {
			if (wFlags & DISPATCH_METHOD) {
				if (pdp->cNamedArgs != 0) {
					return DISP_E_NONAMEDARGS;
				}
				Atom *argv = new (core->GetGC()) Atom[pdp->cArgs+1];
				argv[0] = ob->atom();
				// fill backwards
				for (unsigned i=0;i<pdp->cArgs;i++) {
					argv[i+1] = core->toAtom(pdp->rgvarg[pdp->cArgs-i-1]);
				}
				ret = ob->call(pdp->cArgs, argv);
			} else if (wFlags & DISPATCH_PROPERTYGET) {
				if (pdp->cArgs != 0 || pdp->cNamedArgs != 0) {
					return DISP_E_BADPARAMCOUNT; // todo: DISP_E_NONAMEDARGS?
				}
				ret = ob->defaultValue();
			} else {
				AvmDebugMsg(false, "Ignoring invoke flags 0x%x for DISPID_DEFAULT", wFlags);
				return E_FAIL;
			}
		} else {
			// Not a special dispid
			// find the entry for this dispid.
			stdext::hash_map<int, DISPID_ENTRY>::iterator it = dispid2info.find(id);
			if(it == dispid2info.end()) {
				AvmDebugMsg(false, "IDispatchProvider::InvokeEx - bad dispid %d\n", id);
				return DISP_E_BADINDEX;
			}
			DISPID_ENTRY &entry = it->second;
			if (entry.deleted) {
				AvmDebugMsg(false, "IDispatchProvider::InvokeEx - dispid %d has been deleted\n", id);
				return DISP_E_BADINDEX;
			}
			AvmDebugMsg(false, "IDispatchProvider::InvokeEx for '%S', flags=0x%x\n",
						core->atomToString(entry.name)->getData(), wFlags);
			// do it
			// *sob* - vbscript calls all properties with DISPATCH_METHOD
			// and DISPATCH_PROPERTYGET - it's syntax can't tell the
			// difference.  We need to get smarter here, but this will do
			// for now (it will fail when trying to call a method without params - 
			// see failing test testDispatchLikeVBScript)
			if (wFlags & (DISPATCH_PROPERTYGET | DISPATCH_METHOD) && pdp->cArgs != 0)
				wFlags = DISPATCH_METHOD;
			if (wFlags & DISPATCH_PROPERTYGET) {
				if (pdp->cArgs != 0 || pdp->cNamedArgs != 0) {
					return DISP_E_BADPARAMCOUNT; // todo: DISP_E_NONAMEDARGS?
				}
				ret = ob->getAtomProperty(entry.name);
			} else if (wFlags & DISPATCH_PROPERTYPUT) {
				if (pdp->cArgs != 1 || pdp->cNamedArgs != 1) {
					return DISP_E_BADPARAMCOUNT;  // todo: DISP_E_NONAMEDARGS?
				}
				ob->setAtomProperty(entry.name, core->toAtom(pdp->rgvarg[0]));
			} else if (wFlags & DISPATCH_METHOD) {
				// no named args support.
				if (pdp->cNamedArgs != 0) {
					return DISP_E_NONAMEDARGS;
				}
				Atom *argv = new (core->GetGC()) Atom[pdp->cArgs+1];
				argv[0] = ob->atom();
				// fill backwards
				for (unsigned i=0;i<pdp->cArgs;i++) {
					argv[i+1] = core->toAtom(pdp->rgvarg[pdp->cArgs-i-1]);
				}
				Multiname mn(core->publicNamespace, core->atomToString(entry.name));
				ret = ob->callProperty(&mn, pdp->cArgs, argv);
				// XXX - explicitly free argv here to help the gc?
			} else {
				AvmDebugMsg(false, "Ignoring invoke flags 0x%x", wFlags);
				return E_FAIL;
			}
		}
		if (pvarRes) {
			CComVariant res;
			hr = core->atomToVARIANT(ret, &res);
			if (SUCCEEDED(hr))
				hr = res.Detach(pvarRes);
		}
		return hr;
	} CATCH(Exception *exception) {
		return core->handleException(exception, pei);
	}
	END_CATCH
	END_TRY
}

STDMETHODIMP IDispatchProvider::DeleteMemberByName(
			/* [in] */ BSTR bstrName,
			/* [in] */ DWORD grfdex)
{
	ATLTRACENOTIMPL(_T("IDispatchProvider::DeleteMemberByName"));
}

STDMETHODIMP IDispatchProvider::DeleteMemberByDispID(
			/* [in] */ DISPID id)
{
	ATLTRACENOTIMPL(_T("IDispatchProvider::DeleteMemberByDispID"));
}

STDMETHODIMP IDispatchProvider::GetMemberProperties(
			/* [in] */ DISPID id,
			/* [in] */ DWORD grfdexFetch,
			/* [out] */ DWORD *pgrfdex)
{
	ATLTRACENOTIMPL(_T("IDispatchProvider::GetMemberProperties"));
}

STDMETHODIMP IDispatchProvider::GetMemberName(
			/* [in] */ DISPID id,
			/* [out] */ BSTR *pbstrName)
{
	ATLTRACENOTIMPL(_T("IDispatchProvider::GetMemberName"));
}

STDMETHODIMP IDispatchProvider::GetNextDispID(
			/* [in] */ DWORD grfdex,
			/* [in] */ DISPID id,
			/* [out] */ DISPID *pid)
{
	ATLTRACENOTIMPL(_T("IDispatchProvider::GetNextDispID"));
}


STDMETHODIMP IDispatchProvider::GetNameSpaceParent(
			/* [out] */ IUnknown **ppunk)
{
	ATLTRACENOTIMPL(_T("IDispatchProvider::GetNameSpaceParent"));
}
