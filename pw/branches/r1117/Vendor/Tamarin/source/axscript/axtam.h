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
 * The Original Code is [axtam].
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

// axtam.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

// Not defining either of _ATL_SINGLE_THREADED or _ATL_APARTMENT_THREADED 
// appears to default to a multi-thread model, which is what we want.

#include "resource.h"

// Useful #defines before including atl:
// Send info about QI calls to the debugger.
// #define _ATL_DEBUG_QI

// ATL, COM, ActiveScripting etc related headers.
#include <atlbase.h>
#include <atlcom.h>
#include <ActivScp.h>
#include <ObjSafe.h>
#include <DispEx.h>
using namespace ATL;

#include <hash_map>


// Tamarin headers
#include "avmplus.h"
#include "AvmCore.h"
#include "OutputStream.h"
#include "Exception.h"
#include "avmplusDebugger.h"
using namespace avmplus;

// We use a DRC on IDispatchConsumer, so a fwd decl doesn't work.
#include "IDispatchConsumer.h"

// The NATIVE_CLASS macros etc expect an avmplus::NativeID namespace.
namespace avmplus
{
	namespace NativeID
	{
        #include "axtoplevel.h"
    }
}

//extern "C" const __declspec(selectany) CLSID  = {0x44EC053A,0x400F,0x11D0,{0x9D,0xCD,0x00,0xA0,0xC9,0x03,0x91,0xD3}};

// suck in the GUIDs we need to link with.
#include "initguid.h"

// The GUID for our main COM object.
// {9D593E46-B5EC-44c3-A64C-81C88887263B}
DEFINE_GUID(CLSID_ActiveScript, 0x9d593e46, 0xb5ec, 0x44c3, 0xa6, 0x4c, 0x81, 0xc8, 0x88, 0x87, 0x26, 0x3b);

// These suck - not sure what the right thing to avoid linker errors is...
// They are clones of the values in ActiveScp.h
DEFINE_GUID(AXT_CATID_ActiveScript, 0xf0b7a1a1, 0x9847, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);
DEFINE_GUID(AXT_CATID_ActiveScriptParse, 0xf0b7a1a2, 0x9847, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);

// TODO: move some of these to a better header.
namespace axtam
{
	class IUnknownConsumerClass;
	class COMConsumerErrorClass;
	class COMProviderErrorClass;
	class EXCEPINFOClass;

	// CodeContext is used to track which security context we are in.
	// When an AS3 method is called, the AS3 method will set core->codeContext to its code context.
	class CodeContext : public avmplus::CodeContext
	{
	  public:
		CodeContext(DomainEnv* domainEnv) : _domainEnv(domainEnv) { ; }
		DWB(DomainEnv*) _domainEnv;
#ifdef DEBUGGER
		virtual Toplevel *toplevel() const { return _domainEnv->toplevel(); }
		virtual DomainEnv *domainEnv() const { return _domainEnv; }
#else
		DomainEnv *domainEnv() const { return _domainEnv; }
#endif
	};

	// The "core" - one core per script engine.
	class AXTam : public AvmCore
	{
	public:
		AXTam(MMgc::GC *gc);
		~AXTam() {Close();}

		// XXX - is it appropriate for toplevel to be stored here 
		// (ie, is it really per 'core'?)
		Toplevel* toplevel;
		CComPtr<IActiveScript> as;
		static HINSTANCE hinstance;

		void interrupt(MethodEnv *env);
		void stackOverflow(MethodEnv *env);

		Atom toAtom(LPCOLESTR s) {
			if (!s)
				return undefinedAtom;
			return AvmCore::internAlloc((const avmplus::wchar *)s, wcslen(s))->atom();
		};

		Atom toAtom(DWORD v) {
			return internUint32(v)->atom();
		}

		Atom toAtom(VARIANT &var);
		Atom toAtom(IDispatch *disp);
		Atom toAtom(IUnknown *pUnk, const IID &iid = __uuidof(0));

		// Convert an atom to the specifically requested variant type.
		CComVariant atomToTypedVARIANT(Atom val, VARTYPE vt);
		// Convert an atom to any variant type.
		CComVariant atomToVARIANT(Atom val);
		void *atomToIUnknown(Atom val, const IID &iid);
		// Convert an atom - but catch exceptions and translate to a COM
		// HRESULT.  Suitable for use when no tamarin exception handler is
		// setup (eg, when returning results to COM objects).  Note that if
		// these fail, they will generally cause debug output to be written
		HRESULT atomToTypedVARIANT(Atom val, VARTYPE vt, CComVariant *pResult);
		// Convert an atom to any variant type.
		HRESULT atomToVARIANT(Atom val, CComVariant *pResult);
		HRESULT atomToIUnknown(Atom val, const IID &iid, void **ret);

//		DispatchConsumerClass *dispatchClass;

		void Initialize(IActiveScript *as);
		void Close();
		// Dump an exception for the benefit of the person developing/debugging the
		// engine rather than the author of the actual script code
		void dumpException(Exception *exc);
		// Some "class" pointers - getBuiltinClass() doesn't work for our "extension" classes...
		IDispatchConsumerClass *dispatchClass;
		IUnknownConsumerClass *unknownClass;
		COMConsumerErrorClass *comConsumerErrorClass;
		COMProviderErrorClass *comProviderErrorClass;
		// Get an Atom for a previously seen IUnknown object, or undefinedAtom.
		IDispatchConsumer *getExistingConsumer(IUnknown *pUnk);
		EXCEPINFOClass *excepinfoClass;

		// Ownership of EXCEPINFO is taken by this function.
		void throwCOMConsumerError(HRESULT hr, EXCEPINFO *pei = NULL);

		// Used by objects which delegate COM interfaces to script code, but
		// after delegation fail to convert the result to the native COM type.
		HRESULT handleConversionFailure(const Exception *);
		// Use this to check if script code has thrown an exception with a HRESULT
		// that should be returned to the COM method being called.
		bool isCOMProviderError(Exception *exc);
		// You almost never need to know if it is a consumer error - treat that as a "normal" exception.
		bool isCOMConsumerError(Exception *exc);
		// fill an EXCEPINFO with a tamarin exception
		void fillEXCEPINFO(const Exception *exception, EXCEPINFO *pexcepinfo, bool includeStackTrace = true);

		// handle an exception by a "top-level" COM entry-point.
		HRESULT handleException(Exception *exc, EXCEPINFO *pei = NULL, int depth=0);

		Toplevel* initAXTamBuiltins(bool load_esc);
		// Create IDispatch wrappers around script objects (dispatch providers)
		// The native method version for script code.
		CComPtr<IDispatch> createDispatchProvider(Atom ob);
		// ack - something is wrong with this - |this| is always a ScriptObject * :(
		ScriptObject *createDispatchProviderMethod(Atom ob);
		//

		Atom constant(const avmplus::wchar *s)
		{
			return constantString(s)->atom();
		}

		Stringp constantString(const avmplus::wchar *s)
		{
			return internString(newString(s));
		}
		// ack - we shadow these... - XXX - todo - get the above in the core!
		Atom constant(const char *s) {return AvmCore::constant(s);}
		Stringp constantString(const char *s) {return AvmCore::constantString(s);}

		CComPtr<IActiveScriptSite> activeScriptSite;

	private:
		DECLARE_NATIVE_CLASSES()
		DECLARE_NATIVE_SCRIPTS()

		// A hashtable of IDispatchConsumerObjects, keyed by the address of the IUnknown
		// it wraps.  MarkH failed to beat any of the avm hashtables into compliance.
		stdext::hash_map<IUnknown *, DRC(IDispatchConsumer *)> dispatchConsumers;

		bool gracePeriod;
		bool inStackOverflow;
		// what is the pool for?
		PoolObject* pool;

		void computeStackBase();

		void initAXPool();
		void initESC(Toplevel *toplevel);

		#ifdef DEBUGGER
		//Debugger *debugger;
		#endif
	};

	// Not sure what this does??  Initializing the core initializes
	// this.
	class AxtamScript : public ScriptObject
	{

	public:
		AxtamScript(VTable *vtable, ScriptObject* delegate)
			: ScriptObject(vtable, delegate)
		{
		}
		DECLARE_NATIVE_SCRIPT(AxtamScript)
	};

	// A clone of CComObject that allows the COM object to be a GC root - 
	// necessary when the COM object has a pointer to a GC'd object.
	// Example: our IActiveScriptError holds a pointer to an Exception object.
	template <class Base>
	class CGCRootComObject : public Base
	{
	public:
		typedef Base _BaseClass;
		CGCRootComObject(AXTam *core) throw() : _BaseClass(core)
		{
			_pAtlModule->Lock();
		}
		// Set refcount to -(LONG_MAX/2) to protect destruction and 
		// also catch mismatched Release in debug builds
		virtual ~CGCRootComObject() throw()
		{
			m_dwRef = -(LONG_MAX/2);
			FinalRelease();
	#ifdef _ATL_DEBUG_INTERFACES
			_AtlDebugInterfacesModule.DeleteNonAddRefThunk(_GetRawUnknown());
	#endif
			_pAtlModule->Unlock();
		}
		//If InternalAddRef or InternalRelease is undefined then your class
		//doesn't derive from CComObjectRoot
		STDMETHOD_(ULONG, AddRef)() {return InternalAddRef();}
		STDMETHOD_(ULONG, Release)()
		{
			ULONG l = InternalRelease();
			if (l == 0)
				delete this;
			return l;
		}
		//if _InternalQueryInterface is undefined then you forgot BEGIN_COM_MAP
		STDMETHOD(QueryInterface)(REFIID iid, void ** ppvObject) throw()
		{return _InternalQueryInterface(iid, ppvObject);}
		template <class Q>
		HRESULT STDMETHODCALLTYPE QueryInterface(Q** pp) throw()
		{
			return QueryInterface(__uuidof(Q), (void**)pp);
		}

		//static HRESULT WINAPI CreateInstance(CComObject<Base>** pp) throw();
	};
	// End of CComObject clone

}; // end of axtam namespace.
