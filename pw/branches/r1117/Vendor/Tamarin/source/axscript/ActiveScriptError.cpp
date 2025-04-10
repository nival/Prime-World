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
#include "ActiveScriptError.h"

using namespace axtam;

bool CActiveScriptError::isSyntaxError()
{
	using namespace avmplus::NativeID;
	Traits *tse = core->toplevel->getBuiltinClass(abcclass_SyntaxError)->traits()->itraits;
	return exception->isValid() && core->istype(exception->atom, tse);
}
// IActiveScriptError
STDMETHODIMP CActiveScriptError::GetExceptionInfo( 
            /* [out] */ EXCEPINFO *pexcepinfo)
{
	if (!pexcepinfo)
		return E_POINTER;

	// SyntaxErrors don't get a stack-trace - it's just to the compiler.
	core->fillEXCEPINFO(exception, pexcepinfo, !isSyntaxError());
	return S_OK;
}

STDMETHODIMP CActiveScriptError::GetSourcePosition(
            /* [out] */ DWORD *pdwSourceContext,
            /* [out] */ ULONG *pulLineNumber,
            /* [out] */ LONG *plCharacterPosition)
{
	if (pdwSourceContext)
		*pdwSourceContext = dwSourceContextCookie;
	// WSH doesn't initialize either of these variables
	if (pulLineNumber)
		*pulLineNumber = 0;
	if (plCharacterPosition)
		*plCharacterPosition = 0;

	if (isSyntaxError()) {
		// ESC may set 'line', 'column'attributes
		if (pulLineNumber) {
			Multiname multiname(core->publicNamespace, core->constantString("line"));
			Atom line = core->toplevel->getproperty(exception->atom, &multiname,
			                                        core->toplevel->toVTable(exception->atom));
			AvmAssert(line != undefinedAtom); // line can't be 0, so should exist
			*pulLineNumber = core->toUInt32(line) - 1; // zero based, as below.
		}
		// ESC doesn't do character positions :(
		return S_OK;
	} else {
#ifdef DEBUGGER
		StackTrace *st = exception->getStackTrace();
		if (pulLineNumber && st) {
			// although not documented as such, linenum is zero based for
			// axscript engines - its pretty easy to demonstrate with IE.
			*pulLineNumber = st->elements[0].linenum-1;
		}
		// No column numbers available from runtime exceptions.
		return S_OK;
#else
		return E_NOTIMPL;
#endif
	}
	AvmAssert(false); // not reached!
}

STDMETHODIMP CActiveScriptError::GetSourceLineText(
            /* [out] */ BSTR *pbstrSourceLine)
{
	return E_NOTIMPL;
}
