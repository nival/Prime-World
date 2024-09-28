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
#include "EXCEPINFO.h"

namespace axtam
{
	EXCEPINFOObject::~EXCEPINFOObject()
	{
		if (ei.bstrDescription)
			::SysFreeString(ei.bstrDescription);
		if (ei.bstrHelpFile)
			::SysFreeString(ei.bstrHelpFile);
		if (ei.bstrSource)
			::SysFreeString(ei.bstrSource);
	}

	uint32 EXCEPINFOObject::getCode()
	{
		return ei.wCode;
	}
	Stringp EXCEPINFOObject::getSource()
	{
		return core()->newString((wchar *)ei.bstrSource);
	}

	Stringp EXCEPINFOObject::getDescription()
	{
		return core()->newString((wchar *)ei.bstrDescription);
	}
	Stringp EXCEPINFOObject::getHelpFile()
	{
		return core()->newString((wchar *)ei.bstrHelpFile);
	}
	uint32 EXCEPINFOObject::getHelpContext()
	{
		return ei.dwHelpContext;
	}
	uint32 EXCEPINFOObject::getScode()
	{
		return ei.scode;
	}

	BEGIN_NATIVE_MAP(EXCEPINFOClass)
		NATIVE_METHOD(axtam_com_EXCEPINFO_code_get, EXCEPINFOObject::getCode)
		NATIVE_METHOD(axtam_com_EXCEPINFO_source_get, EXCEPINFOObject::getSource)
		NATIVE_METHOD(axtam_com_EXCEPINFO_description_get, EXCEPINFOObject::getDescription)
		NATIVE_METHOD(axtam_com_EXCEPINFO_helpFile_get, EXCEPINFOObject::getHelpFile)
		NATIVE_METHOD(axtam_com_EXCEPINFO_helpContext_get, EXCEPINFOObject::getHelpContext)
		NATIVE_METHOD(axtam_com_EXCEPINFO_scode_get, EXCEPINFOObject::getScode)
	END_NATIVE_MAP()

	EXCEPINFOClass::EXCEPINFOClass(VTable *cvtable)
		: ClassClosure(cvtable)
    {
		AXTam* core = (AXTam*)this->core();
		// should only be initialized once, but is currently done each time
		// we init builtins for a new domainenv.
		if (!core->excepinfoClass)
			core->excepinfoClass = this;
		createVanillaPrototype();
	}

	EXCEPINFOClass::~EXCEPINFOClass()
	{
	}

	// Function called as constructor ... not supported from user code
	// NOTE: Takes ownership of strings inside the EXCEPINFO!
	EXCEPINFOObject* EXCEPINFOClass::create(EXCEPINFO *pei)
	{
		VTable* ivtable = this->ivtable();
		EXCEPINFOObject *o = new (core()->GetGC(), ivtable->getExtraSize()) EXCEPINFOObject(ivtable, prototype, pei);
		return o;
	}
}
