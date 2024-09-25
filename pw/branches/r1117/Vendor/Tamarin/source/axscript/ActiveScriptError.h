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

#ifndef __axtam_ActiveScriptError__
#define __axtam_ActiveScriptError__

namespace axtam {
	// Class for reporting avm exceptions to the script host.  It is hoped we 
	// can replace this with a script version, or at least integrate with our 
	// script impl, so GetSourcePosition() and possibly the script context, 
	// can be delegated.
	// XXX - think about this some more.
	class ATL_NO_VTABLE CActiveScriptError :
		public CComObjectRootEx<CComSingleThreadModel>,
		public IActiveScriptError,
	//	public IActiveScriptError64,
		// Any pointers to a GCObject from unmanaged memory require the unmanaged object to be a GCRoot.
		// We are an unmanaged object, and 'exception' is (presumably) a GCObject.
		public MMgc::GCRoot
	{
	public:
		CActiveScriptError(AXTam *_core) : 
		  MMgc::GCRoot(_core->GetGC()), core(_core), dwSourceContextCookie(0), exception(0) {;}
		virtual ~CActiveScriptError() {;}
		bool isSyntaxError();
		avmplus::Exception *exception; // is this GCRoot really enough?
		AXTam *core;
		DWORD_PTR dwSourceContextCookie;
	protected:

	BEGIN_COM_MAP(CActiveScriptError)
		COM_INTERFACE_ENTRY(IActiveScriptError)
	//	COM_INTERFACE_ENTRY(IActiveScriptError64)
	END_COM_MAP()

	// IActiveScriptError
	STDMETHOD(GetExceptionInfo)( 
			/* [out] */ EXCEPINFO *pexcepinfo);

	STDMETHOD(GetSourcePosition)(
			/* [out] */ DWORD *pdwSourceContext,
			/* [out] */ ULONG *pulLineNumber,
			/* [out] */ LONG *plCharacterPosition);

	STDMETHOD(GetSourceLineText)(
			/* [out] */ BSTR *pbstrSourceLine);

	// IActiveScriptError64

	//   STDMETHOD(GetSourcePosition64)(
	//            /* [out] */ DWORDLONG *pdwSourceContext,
	//            /* [out] */ ULONG *pulLineNumber,
	//            /* [out] */ LONG *plCharacterPosition);

	};

};

#endif // __axtam_ActiveScriptError__
