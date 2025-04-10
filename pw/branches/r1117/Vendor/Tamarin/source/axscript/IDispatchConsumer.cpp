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
#include "IDispatchConsumer.h"

#include <stdlib.h>

namespace axtam
{
	IDispatchConsumer::IDispatchConsumer(VTable* vtable, ScriptObject* prototype, IDispatch *pDisp)
		: IUnknownConsumer(vtable, prototype, pDisp, __uuidof(IDispatch))
	{
		AvmAssert(traits()->sizeofInstance == sizeof(IDispatchConsumer));
	}

	Atom IDispatchConsumer::call(int argc, Atom* argv)
	{
		CComVariant ret;
		EXCEPINFO ei = {0,0,0,0,0};
		AXTam *axcore = (AXTam *)core();
		DISPPARAMS_helper params(axcore, argc, argv);
		IDispatch *disp = (IDispatch *)getDispatch();
		HRESULT hr = disp->Invoke(DISPID_VALUE, IID_NULL, 0, DISPATCH_METHOD, params, &ret, &ei, NULL);
		if (FAILED(hr)) {
			// EXCEPINFO ownership taken by throwCOMConsumerError
			ret.Clear();
			params.clear();
			axcore->throwCOMConsumerError(hr, &ei);
		}
		return axcore->toAtom(ret);
	}

	Atom IDispatchConsumer::callProperty(avmplus::Multiname *name, int argc, avmplus::Atom *argv)
	{
		// Prevent recursion death due to global being the IDispatchConsumer 
		// (we ask window for object, it asks  our IDispatch, etc), existing
		// expandos get preference.
		if (hasMultinameProperty(name))
			return ScriptObject::callProperty(name, argc, argv);

		// Not sure how to best handle this re 'builtin' names, such as toString()
		// XXX - need a map of DISPIDs to speed things up, and/or optimizations
		// using the typelib.
		DISPID id;
		AXTam *axcore = (AXTam *)core();
		IDispatch *disp = (IDispatch *)getDispatch();
		OLECHAR *olename = (OLECHAR *)name->getName()->c_str();
		HRESULT hr = disp->GetIDsOfNames(IID_NULL, &olename, 1, 0, &id);
		if (hr == DISP_E_UNKNOWNNAME) {
			// not a name this object has - see if its builtin/expando.
			return ScriptObject::callProperty(name, argc, argv);
		}
		if (FAILED(hr))
			axcore->throwCOMConsumerError(hr);
		// Now create args for the call.
		EXCEPINFO ei = {0,0,0,0,0};
		DISPPARAMS_helper params(axcore, argc, argv);
		CComVariant ret;
		hr = disp->Invoke(id, IID_NULL, 0, DISPATCH_METHOD, params, &ret, &ei, NULL);
		// Consider, eg, 'WSH.Arguments(0)' - we are here attempting to call an
		// 'Arguments' method - but what we actually *want* is a property-get for
		// 'Arguments', then a DISPID_DEFAULT call on that.  So do that :)
		if (hr == DISP_E_MEMBERNOTFOUND) {
			DISPPARAMS get_params = {NULL, NULL, 0, 0};
			CComVariant sub;
			hr = disp->Invoke(id, IID_NULL, 0, DISPATCH_PROPERTYGET, &get_params, &sub, &ei, NULL);
			if (SUCCEEDED(hr)) {
				CComPtr<IDispatch> disp_sub;
				if (sub.vt == VT_DISPATCH)
					disp_sub = (IDispatch *)sub.pdispVal;
				else if (sub.vt == VT_UNKNOWN)
					disp_sub = CComQIPtr<IDispatch, &IID_IDispatch>(sub.punkVal);
				if (disp_sub==0) {
					// Its a normal value (eg, string, int - but not "callable")
					AvmDebugMsg(false, "property get for '%S' returned something not callable (vt=%d)",
					            olename, sub.vt);
					ret.Clear();
					params.clear();
					axcore->toplevel->throwTypeError(kCallOfNonFunctionError, axcore->toErrorString(name));
				}
				// finally have an IDispatch we can retry the call on.
				hr = disp_sub->Invoke(DISPID_VALUE, IID_NULL, 0, DISPATCH_METHOD, params, &ret, &ei, NULL);
			}
		}
		if (FAILED(hr)) {
			ret.Clear();
			params.clear();
			// EXCEPINFO ownership taken by throwCOMConsumerError
			axcore->throwCOMConsumerError(hr, &ei);
		}
		return axcore->toAtom(ret);
	}

	void IDispatchConsumer::setMultinameProperty(Multiname* name, Atom value)
	{
		// its possible we should just call setStringProperty(), which calls
		// setAtomProperty(), and we should add our impl there - but let's see
		// if we can get away without that for now...
		DISPID id;
		AXTam *axcore = (AXTam *)core();
		OLECHAR *olename = (OLECHAR *)name->getName()->c_str();
		IDispatch *disp = (IDispatch *)getDispatch();
		HRESULT hr = disp->GetIDsOfNames(IID_NULL, &olename, 1, 0, &id);
		if (hr == DISP_E_UNKNOWNNAME) {
			// not a name this object has - set it as an 'expando'
			return ScriptObject::setMultinameProperty(name, value);
		}
		if (FAILED(hr))
			axcore->throwCOMConsumerError(hr);
		// Set the value into a DISPPARAMS and set it.
		EXCEPINFO ei = {0,0,0,0,0};
		CComVariant arg = axcore->atomToVARIANT(value);
		DISPPARAMS params = {&arg, NULL, 1, 0};
		hr = disp->Invoke(id, IID_NULL, 0, DISPATCH_PROPERTYPUT, &params, NULL, &ei, NULL);
		if (FAILED(hr))
			axcore->throwCOMConsumerError(hr, &ei);
	}

	Atom IDispatchConsumer::getAtomProperty(Atom name) const {
		AXTam *axcore = (AXTam *)core();
		IDispatch *disp = (IDispatch *)getDispatch();
		if (!axcore->isString(name))
			axcore->toplevel->throwTypeError(kCheckTypeFailedError);
		DISPID id;

		// Prevent recursion death due to global being the IDispatchConsumer 
		// (we ask window for object, it asks  our IDispatch, etc), existing
		// expandos get preference.
		if (hasAtomProperty(name))
			return ScriptObject::getAtomProperty(name);

		OLECHAR *olename = (OLECHAR *)axcore->atomToString(name)->c_str();
		HRESULT hr = disp->GetIDsOfNames(IID_NULL, &olename, 1, 0, &id);
		if (hr == DISP_E_UNKNOWNNAME) {
			// not a name this object has and already checked expandos
			return undefinedAtom;
		}
		if (FAILED(hr))
			axcore->throwCOMConsumerError(hr);
		EXCEPINFO ei = {0,0,0,0,0};
		DISPPARAMS params = {NULL, NULL, 0, 0};
		CComVariant ret;
		hr = disp->Invoke(id, IID_NULL, 0, DISPATCH_PROPERTYGET, &params, &ret, &ei, NULL);
		if (FAILED(hr)) {
			ret.Clear();
			axcore->throwCOMConsumerError(hr, &ei);
		}
		return axcore->toAtom(ret);
	}

	BEGIN_NATIVE_MAP(IDispatchConsumerClass)
	END_NATIVE_MAP()

	IDispatchConsumerClass::IDispatchConsumerClass(VTable *cvtable)
		: ClassClosure(cvtable)
    {
		AvmAssert(traits()->sizeofInstance == sizeof(IDispatchConsumerClass));
		AXTam* core = (AXTam*)this->core();
		// should only be initialized once - but see above
		if (!core->dispatchClass)
			core->dispatchClass= this;

		createVanillaPrototype();
	}

	IDispatchConsumerClass::~IDispatchConsumerClass()
	{
	}

	IDispatchConsumer* IDispatchConsumerClass::create(IDispatch* p)
	{
		VTable* ivtable = this->ivtable();
		IDispatchConsumer *o = new (core()->GetGC(), ivtable->getExtraSize()) IDispatchConsumer(ivtable, prototype, p);
		return o;
	}

	void DISPPARAMS_helper::fill(AXTam *core, int argc, Atom* argv)
	{
		// must only be called once.
		AvmAssert(params.cArgs==0 && params.cNamedArgs==0 && params.rgvarg==NULL && vars==NULL);
		// XXX - Note: not using mmGC here - it dies at delete time
		vars = new CComVariant[argc];
		int i;
		for (i=0;i<argc;i++) {
			// args are in reversed order in DISPPARAMS, and we
			// don't pass |this|
			vars[argc-i-1] = core->atomToVARIANT(argv[i+1]);
		}
		params.rgvarg = vars;
		params.cArgs = argc;
	}
}
