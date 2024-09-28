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
#include "SystemClass.h"

#include <stdlib.h>

namespace axtam
{
	BEGIN_NATIVE_MAP(SystemClass)
		NATIVE_METHOD(axtam_System_getAvmplusVersion, SystemClass::getAvmplusVersion)
		NATIVE_METHOD(axtam_System_write, SystemClass::write)
		NATIVE_METHOD(axtam_System_trace, SystemClass::trace)
		NATIVE_METHOD(axtam_System_debugger, SystemClass::debugger)
		NATIVE_METHOD(axtam_System_isDebugger, SystemClass::isDebugger)
		NATIVE_METHOD(axtam_System_nativeDebugBreak, SystemClass::nativeDebugBreak)
	END_NATIVE_MAP()

	SystemClass::SystemClass(VTable *cvtable)
		: ClassClosure(cvtable)
    {
//		AXTam* core = (AXTam*)this->core();
//		if (core->systemClass == NULL) {
//			core->systemClass = this;
//		}
		
		createVanillaPrototype();
	}

	SystemClass::~SystemClass()
	{
	}

	Stringp SystemClass::getAvmplusVersion()
	{
		return core()->newString(AVMPLUS_VERSION_USER " " AVMPLUS_BUILD_CODE);
	}

	void SystemClass::write(Stringp s)
	{
		if (s)
			core()->console << s;
		else
			core()->console << "<null>";
	}

	void SystemClass::trace(ArrayObject* a)
	{
		if (!a)
			toplevel()->throwArgumentError(kNullArgumentError, "array");
		AvmCore* core = this->core();
		PrintWriter& console = core->console;
		for (int i=0, n = a->getLength(); i < n; i++)
		{
			if (i > 0)
                console << ' ';
			Stringp s = core->string(a->getUintProperty(i));
			for (int j = 0; j < s->length(); j++)
			{
				wchar c = (*s)[j];
				// '\r' gets converted into '\n'
				// '\n' is left alone
				// '\r\n' is left alone
				if (c == '\r')
				{
					if (((j+1) < s->length()) && (*s)[j+1] == '\n')
					{
						console << '\r';	
						j++;
					}

					console << '\n';
				}
				else
				{
					console << c;
				}
			}
		}
		console << '\n';
	}

	void SystemClass::debugger()
	{
		#ifdef DEBUGGER
		core()->debugger->enterDebugger();
		#endif
	}

	bool SystemClass::isDebugger()
	{
		#ifdef DEBUGGER
		return true;
		#else
		return false;
		#endif
	}

	void SystemClass::nativeDebugBreak()
	{
		#ifdef DEBUG
			DebugBreak();
		#endif
	}
}
