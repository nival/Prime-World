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
#include "mscom.h"

using namespace axtam;

static MMgc::FixedMalloc* fm = NULL;

class ATL_NO_VTABLE CActiveScript :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CActiveScript, &CLSID_ActiveScript>,
	public IActiveScript, // is this correct?
	public IActiveScriptParseProcedure2,
	public IActiveScriptParse,
	public IObjectSafety
	// it appears IE also queries us for ICallFactory, so some asynch
	// operations may be possible.
	// IActiveScriptProperty - but its not documented.

{
public:
	CActiveScript();
	virtual ~CActiveScript() {;}

	// Our AvmCore instance.
	AXTam *core;

	// we hold a pointer to a script object for delegation, but can't subclass
	// as the MMgc did not allocate our mem.
	MMgc::GCRoot *root; 

	DECLARE_REGISTRY_RESOURCEID(IDR_ACTIVESCRIPT)

	BEGIN_COM_MAP(CActiveScript)
		COM_INTERFACE_ENTRY(IActiveScript)
		COM_INTERFACE_ENTRY(IActiveScriptParseProcedure2)
		COM_INTERFACE_ENTRY(IActiveScriptParse)
		COM_INTERFACE_ENTRY(IObjectSafety)
	END_COM_MAP()

	BEGIN_CATEGORY_MAP(CActiveScript)
		IMPLEMENTED_CATEGORY(AXT_CATID_ActiveScript)
		IMPLEMENTED_CATEGORY(AXT_CATID_ActiveScriptParse)
	END_CATEGORY_MAP()

	// IActiveScript
    STDMETHOD(SetScriptSite)( 
        /* [in] */ IActiveScriptSite *pass);
    
    STDMETHOD(GetScriptSite)( 
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ void **ppvObject);
    
    STDMETHOD(SetScriptState)( 
        /* [in] */ SCRIPTSTATE ss);

    STDMETHOD(GetScriptState)( 
        /* [out] */ SCRIPTSTATE *pssState);

    STDMETHOD(Close)(void);

    STDMETHOD(AddNamedItem)( 
        /* [in] */ LPCOLESTR pstrName,
        /* [in] */ DWORD dwFlags);

    STDMETHOD(AddTypeLib)( 
        /* [in] */ REFGUID rguidTypeLib,
        /* [in] */ DWORD dwMajor,
        /* [in] */ DWORD dwMinor,
        /* [in] */ DWORD dwFlags);

    STDMETHOD(GetScriptDispatch)( 
        /* [in] */ LPCOLESTR pstrItemName,
        /* [out] */ IDispatch **ppdisp);

    STDMETHOD(GetCurrentScriptThreadID)( 
        /* [out] */ SCRIPTTHREADID *pstidThread);

    STDMETHOD(GetScriptThreadID)( 
        /* [in] */ DWORD dwWin32ThreadId,
        /* [out] */ SCRIPTTHREADID *pstidThread);
    
    STDMETHOD(GetScriptThreadState)( 
        /* [in] */ SCRIPTTHREADID stidThread,
        /* [out] */ SCRIPTTHREADSTATE *pstsState);

    STDMETHOD(InterruptScriptThread)( 
        /* [in] */ SCRIPTTHREADID stidThread,
        /* [in] */ const EXCEPINFO *pexcepinfo,
        /* [in] */ DWORD dwFlags);

    STDMETHOD(Clone)( 
        /* [out] */ IActiveScript **ppscript);

	// IActiveScriptParseProcedure2
	STDMETHOD(ParseProcedureText)( 
            /* [in] */ LPCOLESTR pstrCode,
            /* [in] */ LPCOLESTR pstrFormalParams,
            /* [in] */ LPCOLESTR pstrProcedureName,
            /* [in] */ LPCOLESTR pstrItemName,
            /* [in] */ IUnknown *punkContext,
            /* [in] */ LPCOLESTR pstrDelimiter,
            /* [in] */ DWORD dwSourceContextCookie,
            /* [in] */ ULONG ulStartingLineNumber,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDispatch **ppdisp);


	// IActiveScriptParse
	STDMETHOD(InitNew)(void);

	STDMETHOD(AddScriptlet)( 
            /* [in] */ LPCOLESTR pstrDefaultName,
            /* [in] */ LPCOLESTR pstrCode,
            /* [in] */ LPCOLESTR pstrItemName,
            /* [in] */ LPCOLESTR pstrSubItemName,
            /* [in] */ LPCOLESTR pstrEventName,
            /* [in] */ LPCOLESTR pstrDelimiter,
            /* [in] */ DWORD dwSourceContextCookie,
            /* [in] */ ULONG ulStartingLineNumber,
            /* [in] */ DWORD dwFlags,
            /* [out] */ BSTR *pbstrName,
            /* [out] */ EXCEPINFO *pexcepinfo);
        
	STDMETHOD(ParseScriptText)( 
            /* [in] */ LPCOLESTR pstrCode,
            /* [in] */ LPCOLESTR pstrItemName,
            /* [in] */ IUnknown *punkContext,
            /* [in] */ LPCOLESTR pstrDelimiter,
            /* [in] */ DWORD dwSourceContextCookie,
            /* [in] */ ULONG ulStartingLineNumber,
            /* [in] */ DWORD dwFlags,
            /* [out] */ VARIANT *pvarResult,
            /* [out] */ EXCEPINFO *pexcepinfo);

	// IObjectSafety
    STDMETHOD(GetInterfaceSafetyOptions)( 
            /* [in] */ REFIID riid,
            /* [out] */ DWORD *pdwSupportedOptions,
            /* [out] */ DWORD *pdwEnabledOptions);

	STDMETHOD(SetInterfaceSafetyOptions)( 
            /* [in] */ REFIID riid,
            /* [in] */ DWORD dwOptionSetMask,
            /* [in] */ DWORD dwEnabledOptions);
protected:
	// call engine, no exception handling.
	HRESULT callEngineRaw(Atom *ret, const char *name, ...);
	// call engine, handling exceptions.
	HRESULT callEngine(Atom *ret, const char *name, ...);
	// the worker...
	HRESULT callEngineRawVA(Atom *ret, const char *name, va_list va);

	Atom engine; // The ES implemented engine we delegate to
	DWORD safetyOptions;
	bool initialized;
};

OBJECT_ENTRY_AUTO(CLSID_ActiveScript, CActiveScript)

// Constructor
CActiveScript::CActiveScript() : 
	root(NULL),
	safetyOptions(0),
	engine(undefinedAtom),
	initialized(false)
{
		// move this to DLL init?
	if (!fm) {
		MMgc::GCHeap::Init();
		MMgc::FixedMalloc::Init();

		fm = MMgc::FixedMalloc::GetInstance();
	}

	MMgc::GCHeap* heap = MMgc::GCHeap::GetGCHeap();

	// XXX - memory exceptions?
	MMgc::GC *gc = new MMgc::GC(heap); // XXX - delete this pointer??
	core = new AXTam(gc);

	// hrmph - this doesn't look correct...
	// XXX - surely I must delete this root?
	root = new MMgc::GCRoot(gc, this, sizeof(*this));
}

HRESULT CActiveScript::callEngineRawVA(Atom *ppret, const char *name, va_list va)
{
	AvmAssert(ppret == NULL || *ppret == NULL || *ppret == undefinedAtom); // please init this out param
	static const int maxAtoms = 64;
	Atom args[maxAtoms];

	if (!core) {
		AvmDebugMsg(false, "callEngine('%s') - early exit due to null core\r\n", name);
		return E_OUTOFMEMORY;
	}
	if (!initialized) {
		core->Initialize(this);
		// fetch and store the 'engine' ES object.
		// Get the object named 'engine' - XXX - cache this?
		DomainEnv *domEnv = core->toplevel ? core->toplevel->domainEnv() : NULL;
		if (!domEnv) {
			AvmDebugMsg(false, "callEngine('%s') - early exit due to null core/toplevel/domainEnv\r\n", name);
			return E_FAIL;
		}
		Multiname multiname(core->publicNamespace, core->constantString("engine"));
		ScriptEnv *se = (ScriptEnv *)domEnv->getScriptInit(&multiname);
		ScriptObject *global = se->global;
		if (!se || !global) {
			AvmDebugMsg(true, "callEngine('%s') - early exit due to no ScriptEnv\r\n", name);
			return E_FAIL;
		}
		AvmAssert(engine==undefinedAtom); // already initialized?
		engine = core->toplevel->getproperty(global->atom(), &multiname, core->toplevel->toVTable(global->atom()));

		initialized = true;
	}
	// fetch the function from the object.
	Multiname multiname_ani(core->publicNamespace, core->constantString(name));
	Atom ani = core->toplevel->getproperty(engine, &multiname_ani, core->toplevel->toVTable(engine));
	if (!core->isObject(ani)) {
		AvmDebugMsg(true, "callEngine('%s') - no property\r\n");
		return E_FAIL;
	}
	// prepare the args
	int argc = 1;
	args[0] = engine;
	Atom arg = va_arg (va, Atom);
	while (arg != (Atom)-1) {
		args[argc] = arg;
		argc++;
		arg = va_arg (va, Atom);
		AvmAssert(argc<maxAtoms);
	}
	// Now call the method.
	AvmDebugMsg(false, "Calling engine::%s\r\n", name);
	Atom ret = AvmCore::atomToScriptObject(ani)->call(argc-1, args);
	if (ppret)
		*ppret = ret;
	return S_OK;
}

HRESULT CActiveScript::callEngine(Atom *ppret, const char *name, ...)
{
	HRESULT hr;
	va_list va;
	va_start (va, name); 
	TRY(core, kCatchAction_ReportAsError) {
		hr = callEngineRawVA(ppret, name, va);
	} CATCH(Exception * exception) {
		return core->handleException(exception);
	}
	END_CATCH
	END_TRY
	va_end(va);

	return hr;
}

HRESULT CActiveScript::callEngineRaw(Atom *ppret, const char *name, ...)
{
	HRESULT hr;
	va_list va;
	va_start (va, name); 
	hr = callEngineRawVA(ppret, name, va);
	// XXX - is this a problem when an exception happens?
	va_end(va);

	return hr;
}


// Implementation methods.
STDMETHODIMP CActiveScript::SetScriptSite( 
            /* [in] */ IActiveScriptSite *pass)
{
	if (!pass)
		return E_POINTER;
	AvmAssert(core->activeScriptSite==0); // already have a site??
	// XXX - todo - construct an object and pass it.  The site code currently
	// has workaround that means this still works.
	HRESULT hr = callEngine(NULL, "SetScriptSite", undefinedAtom, (Atom)-1);
	if (SUCCEEDED(hr))
		core->activeScriptSite = pass;
	return hr;
}

STDMETHODIMP CActiveScript::GetScriptSite( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject)
{
	if (!core->activeScriptSite) {
		AvmDebugMsg(false, "GetScriptSite with no site!\r\n");
		return E_FAIL;
	}
	return core->activeScriptSite.p->QueryInterface(riid, ppvObject);
}

STDMETHODIMP CActiveScript::SetScriptState( 
            /* [in] */ SCRIPTSTATE ss)
{
	HRESULT hr;
	Atom rc = NULL;
	hr = callEngine(&rc, "SetScriptState", core->toAtom(ss), (Atom)-1);
	if (SUCCEEDED(hr)) {
		if (core->isInteger(rc)) {
			hr = core->toUInt32(rc);
		} else {
			AvmDebugMsg(true, "expecting integer result from SetScriptState\r\n");
			hr = E_UNEXPECTED;
		}
	}
	return hr;
}

STDMETHODIMP CActiveScript::GetScriptState( 
            /* [out] */ SCRIPTSTATE *pssState)
{
	Atom ret = undefinedAtom;
	if (!pssState)
		return E_POINTER;
	HRESULT hr = callEngine(&ret, "GetScriptState", (Atom)-1);
	if (FAILED(hr))
		return hr;
	*pssState = (SCRIPTSTATE)core->toUInt32(ret);
	return S_OK;
}

STDMETHODIMP CActiveScript::Close(void)
{
	if (core) {
		// ignore failure - everyone gets to close
		callEngine(NULL, "Close", (Atom)-1);
		core->Close();
	}
	return S_OK;
}

STDMETHODIMP CActiveScript::AddNamedItem( 
            /* [in] */ LPCOLESTR pstrName,
            /* [in] */ DWORD dwFlags)
{
	return callEngine(NULL, "AddNamedItem", core->toAtom(pstrName), core->toAtom(dwFlags), (Atom)-1);
}

STDMETHODIMP CActiveScript::AddTypeLib( 
            /* [in] */ REFGUID rguidTypeLib,
            /* [in] */ DWORD dwMajor,
            /* [in] */ DWORD dwMinor,
            /* [in] */ DWORD dwFlags)
{
	ATLTRACENOTIMPL(_T("CActiveScript::AddTypeLib"));
}

STDMETHODIMP CActiveScript::GetScriptDispatch( 
            /* [in] */ LPCOLESTR pstrItemName,
            /* [out] */ IDispatch **ppdisp)
{
	HRESULT hr;
	Atom ret = undefinedAtom;
	hr = callEngine(&ret, "GetScriptDispatch",
	                core->toAtom(pstrItemName),
	                (Atom)-1);
	if (FAILED(hr))
		return hr;
	return core->atomToIUnknown(ret, IID_IDispatch, (void **)ppdisp);
}

STDMETHODIMP CActiveScript::GetCurrentScriptThreadID( 
            /* [out] */ SCRIPTTHREADID *pstidThread)
{
	ATLTRACENOTIMPL(_T("CActiveScript::GetCurrentScriptThreadID"));
}

STDMETHODIMP CActiveScript::GetScriptThreadID( 
            /* [in] */ DWORD dwWin32ThreadId,
            /* [out] */ SCRIPTTHREADID *pstidThread)
{
	ATLTRACENOTIMPL(_T("CActiveScript::GetScriptThreadID"));
}

STDMETHODIMP CActiveScript::GetScriptThreadState( 
            /* [in] */ SCRIPTTHREADID stidThread,
            /* [out] */ SCRIPTTHREADSTATE *pstsState)
{
	ATLTRACENOTIMPL(_T("CActiveScript::GetScriptThreadState"));
}

STDMETHODIMP CActiveScript::InterruptScriptThread( 
            /* [in] */ SCRIPTTHREADID stidThread,
            /* [in] */ const EXCEPINFO *pexcepinfo,
            /* [in] */ DWORD dwFlags)
{
	if (!core) {
		AvmDebugMsg(true, "CActiveScript::InterruptScriptThread - but no core!\n");
		return E_UNEXPECTED;
	}
	// hrm - how to abort a specific thread?
	AvmDebugMsg(false, "CActiveScript::InterruptScriptThread for thread %x, flags=%x\n", stidThread, dwFlags);
	if (stidThread != SCRIPTTHREADID_ALL) {
		return E_FAIL;
	}
	core->interrupted = true;
	// XXX - we should try and work out what SCRIPTINTERRUPT_RAISEEXCEPTION
	// really means - it seems to mean that we should throw an exception 
	// which can be caught by code. IE doesn't seem to call this function 
	// though (it doesn't appear to have a way to kill scripts that don't 
	// respond - unless ICallFactory is necessary?), and WSH passes that 
	// flag both when the script times out (via /T: param) *and* when script 
	// code calls WSH.Exit(0)
	return S_OK;
}

STDMETHODIMP CActiveScript::Clone( 
            /* [out] */ IActiveScript **ppscript)
{
	ATLTRACENOTIMPL(_T("CActiveScript::Clone"));
}

	// IActiveScriptParseProcedure2
STDMETHODIMP CActiveScript::ParseProcedureText( 
            /* [in] */ LPCOLESTR pstrCode,
            /* [in] */ LPCOLESTR pstrFormalParams,
            /* [in] */ LPCOLESTR pstrProcedureName,
            /* [in] */ LPCOLESTR pstrItemName,
            /* [in] */ IUnknown *punkContext,
            /* [in] */ LPCOLESTR pstrDelimiter,
            /* [in] */ DWORD dwSourceContextCookie,
            /* [in] */ ULONG ulStartingLineNumber,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDispatch **ppdisp)
{
	ATLTRACENOTIMPL(_T("CActiveScript::ParseProcedureText"));
}

// IActiveScriptParse implementation
STDMETHODIMP CActiveScript::InitNew(void)
{
	return callEngine(NULL, "InitNew", (Atom)-1);
}

STDMETHODIMP CActiveScript::AddScriptlet( 
            /* [in] */ LPCOLESTR pstrDefaultName,
            /* [in] */ LPCOLESTR pstrCode,
            /* [in] */ LPCOLESTR pstrItemName,
            /* [in] */ LPCOLESTR pstrSubItemName,
            /* [in] */ LPCOLESTR pstrEventName,
            /* [in] */ LPCOLESTR pstrDelimiter,
            /* [in] */ DWORD dwSourceContextCookie,
            /* [in] */ ULONG ulStartingLineNumber,
            /* [in] */ DWORD dwFlags,
            /* [out] */ BSTR *pbstrName,
            /* [out] */ EXCEPINFO *pexcepinfo)
{
	ATLTRACENOTIMPL(_T("CActiveScript::AddScriptlet"));
}

STDMETHODIMP CActiveScript::ParseScriptText( 
            /* [in] */ LPCOLESTR pstrCode,
            /* [in] */ LPCOLESTR pstrItemName,
            /* [in] */ IUnknown *punkContext,
            /* [in] */ LPCOLESTR pstrDelimiter,
            /* [in] */ DWORD dwSourceContextCookie,
            /* [in] */ ULONG ulStartingLineNumber,
            /* [in] */ DWORD dwFlags,
            /* [out] */ VARIANT *pvarResult,
            /* [out] */ EXCEPINFO *pexcepinfo)
{
	return callEngine(NULL, "ParseScriptText",
	                  core->toAtom(pstrCode),
	                  core->toAtom(pstrItemName),
	                  undefinedAtom, // XXX - punkContext,
	                  core->toAtom(pstrDelimiter),
	                  core->toAtom(dwSourceContextCookie),
	                  core->toAtom(ulStartingLineNumber),
	                  core->toAtom(dwFlags),
	                  (Atom)-1);
}

// IObjectSafety
STDMETHODIMP CActiveScript::GetInterfaceSafetyOptions( 
            /* [in] */ REFIID riid,
            /* [out] */ DWORD *pdwSupportedOptions,
            /* [out] */ DWORD *pdwEnabledOptions)
{
	// XXX - we must look at this in detail!
	AvmDebugMsg(false, "CActiveScript::GetInterfaceSafetyOptions\r\n");
	if (!pdwSupportedOptions || !pdwEnabledOptions)
		return E_POINTER;
	*pdwSupportedOptions = (DWORD)-1;//INTERFACESAFE_FOR_UNTRUSTED_DATA | INTERFACESAFE_FOR_UNTRUSTED_CALLER;
	*pdwEnabledOptions = safetyOptions;
	return S_OK;
}

STDMETHODIMP CActiveScript::SetInterfaceSafetyOptions( 
            /* [in] */ REFIID riid,
            /* [in] */ DWORD dwOptionSetMask,
            /* [in] */ DWORD dwEnabledOptions)
{
	AvmDebugMsg(false, "CActiveScript::SetInterfaceSafetyOptions(...,0x%x, 0x%x)\r\n", dwOptionSetMask, dwEnabledOptions);
	// XXX - check interfaces
	safetyOptions &= ~dwOptionSetMask;
	safetyOptions |= dwEnabledOptions;
	return S_OK;
}
