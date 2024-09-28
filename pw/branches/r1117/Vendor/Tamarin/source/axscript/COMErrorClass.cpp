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
#include "axtam.h"
#include "COMErrorClass.h"
#include "ExcepInfo.h"

namespace axtam
{
	/* *sob* - tamarin throws exceptions if I try and define this in the base class
	BEGIN_NATIVE_MAP(COMErrorClass)
		NATIVE_METHOD(axtam_com_Error_getErrorMessage, COMErrorClass::getErrorMessage)
	END_NATIVE_MAP()
	*/

	COMErrorClass::COMErrorClass(VTable* cvtable)
		: ClassClosure(cvtable)
	{
//		AvmAssert(traits()->sizeofInstance == sizeof(COMErrorClass));
//		prototype = createInstance(ivtable(), toplevel()->objectClass->prototype);
	}
	

	void COMErrorClass::throwError(HRESULT hr, EXCEPINFO *pei /* = NULL */)
	{
		AXTam *core = (AXTam *)this->core();
		Atom args[] = { nullObjectAtom, core->intToAtom(hr), pei ? core->excepinfoClass->create(pei)->atom() : nullObjectAtom };
		core->throwAtom(construct(2, args));
	}

	Stringp COMErrorClass::getErrorMessage(int errorID) const
	{
		DWORD flags = FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER;
		wchar *buffer;
		if (::FormatMessageW(flags, 0, errorID, 0, (LPWSTR)&buffer, 0, NULL )<=0)
			return core()->kEmptyString;
		// FormatMessage always sticks a trailing \r\n.
		size_t len = wcslen((wchar_t *)buffer);
		if (len > 2)
			buffer[len-2] = '\0';
		Stringp ret = core()->newString(buffer);
		LocalFree(buffer);
		return ret;
	}

	// override ctor just so we can get 'hresult' :(
	Atom COMErrorClass::construct(int argc, Atom* argv)
	{
		Atom ret = ClassClosure::construct(argc, argv);
		AvmAssert(argc>=1);
		AvmAssert(core()->istype(ret, traits()->itraits));
		COMErrorObject *o = (COMErrorObject *)core()->atomToScriptObject(ret);
		o->atomhresult = argv[1];
		return ret;
	}

	COMErrorObject::COMErrorObject(VTable* vtable,
							 ScriptObject *delegate)
		: ScriptObject(vtable, delegate), atomhresult(0)
	{
		AvmAssert(traits()->sizeofInstance == sizeof(COMErrorObject));

		#ifdef DEBUGGER
		AvmCore *core = this->core();
		// Copy the stack trace
		stackTrace = core->newStackTrace();
		#endif
	}

	HRESULT COMErrorObject::getHRESULT() const
	{
		// *sob* - why can't I fetch it from the instance?
		// XXX - fixme
		// Atom r = getStringProperty(core()->constantString("hresult"));
		const Atom &r = atomhresult;
		return (HRESULT)core()->toUInt32(r);
	}
	// the subclasses.
	// COMConsumerErrorClass
	BEGIN_NATIVE_MAP(COMConsumerErrorClass)
		NATIVE_METHOD(axtam_com_ConsumerError_getErrorMessage, COMErrorClass::getErrorMessage)
	END_NATIVE_MAP()
	COMConsumerErrorClass::COMConsumerErrorClass(VTable* cvtable)
		: COMErrorClass(cvtable)
	{
		AvmAssert(traits()->sizeofInstance == sizeof(COMConsumerErrorClass));
		prototype = createInstance(ivtable(), toplevel()->objectClass->prototype);

		AXTam* core = (AXTam*)this->core();
		if (!core->comConsumerErrorClass)
			core->comConsumerErrorClass = this;
	}

	ScriptObject* COMConsumerErrorClass::createInstance(VTable *ivtable,
														ScriptObject *prototype)
	{
		return new (ivtable->gc(), ivtable->getExtraSize()) COMConsumerErrorObject(ivtable, prototype);
	}

	// COMProviderErrorClass
	BEGIN_NATIVE_MAP(COMProviderErrorClass)
		NATIVE_METHOD(axtam_com_ProviderError_getErrorMessage, COMErrorClass::getErrorMessage)
	END_NATIVE_MAP()

	COMProviderErrorClass::COMProviderErrorClass(VTable* cvtable)
		: COMErrorClass(cvtable)
	{
		AvmAssert(traits()->sizeofInstance == sizeof(COMProviderErrorClass));
		prototype = createInstance(ivtable(), toplevel()->objectClass->prototype);
		AXTam* core = (AXTam*)this->core();
		if (!core->comProviderErrorClass)
			core->comProviderErrorClass = this;
	}

	ScriptObject* COMProviderErrorClass::createInstance(VTable *ivtable,
														ScriptObject *prototype)
	{
		return new (ivtable->gc(), ivtable->getExtraSize()) COMProviderErrorObject(ivtable, prototype);
	}

}
