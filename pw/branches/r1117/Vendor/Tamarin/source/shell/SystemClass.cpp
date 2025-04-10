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
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
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


#include "avmshell.h"

namespace avmshell
{
	SystemClass::SystemClass(VTable *cvtable)
		: ClassClosure(cvtable)
    {
		ShellCore* core = (ShellCore*)this->core();
		if (core->systemClass == NULL) {
			core->systemClass = this;
		}
		
		createVanillaPrototype();

		// initialTime: support for getTimer
		// todo note this is currently routed to the performance counter
		// for benchmark purposes.
		#ifdef PERFORMANCE_GETTIMER
		initialTime = VMPI_getPerformanceCounter();
		#else
		initialTime = VMPI_getTime();		
		#endif // PERFORMANCE_GETTIMER

	}

	SystemClass::~SystemClass()
	{
		initialTime = 0;
	}

	void SystemClass::exit(int status)
	{
		Platform::GetInstance()->exit(status);
	}

	int SystemClass::exec(Stringp command)
	{
		if (!command) {
			toplevel()->throwArgumentError(kNullArgumentError, "command");
		}
		#ifdef UNDER_CE
		AvmAssert(0);
		return 0;
		#else
		StUTF8String commandUTF8(command);
		return system(commandUTF8.c_str());
		#endif
	}
	
	Stringp SystemClass::getAvmplusVersion()
	{
		return core()->newConstantStringLatin1(AVMPLUS_VERSION_USER " " AVMPLUS_BUILD_CODE);
	}

	void SystemClass::write(Stringp s)
	{
		if (!s)
			toplevel()->throwArgumentError(kNullArgumentError, "string");
		core()->console << s;
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
			StringIndexer s(core->string(a->getUintProperty(i)));
			for (int j = 0; j < s->length(); j++)
			{
				wchar c = s[j];
				// '\r' gets converted into '\n'
				// '\n' is left alone
				// '\r\n' is left alone
				if (c == '\r')
				{
					if (((j+1) < s->length()) && s[j+1] == '\n')
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
		if (core()->debugger())
			core()->debugger()->enterDebugger();
		#endif
	}

	bool SystemClass::isDebugger()
	{
		#ifdef DEBUGGER
		return core()->debugger() != NULL;
		#else
		return false;
		#endif
	}

	unsigned SystemClass::getTimer()
	{
#ifdef PERFORMANCE_GETTIMER
		double time = ((double) (VMPI_getPerformanceCounter() - initialTime) * 1000.0 /
					   (double)VMPI_getPerformanceFrequency());
		return (uint32_t)time;
#else
		return (uint32_t)(VMPI_getTime() - initialTime);
#endif /* PERFORMANCE_GETTIMER */

    }

	int SystemClass::user_argc;
	char **SystemClass::user_argv;

	ArrayObject * SystemClass::getArgv()
	{
		// get VTable for avmplus.System
		Toplevel *toplevel = this->toplevel();
		AvmCore *core = this->core();

		ArrayObject *array = toplevel->arrayClass->newArray();
		for(int i=0; i<user_argc;i++)
			array->setUintProperty(i, core->newStringUTF8(user_argv[i])->atom());

		return array;
	}

	Stringp SystemClass::readLine()
	{
		AvmCore* core = this->core();
		Stringp s = core->kEmptyString;
		wchar wc[64];
		int i=0;
		for (int c = getchar(); c != '\n' && c != EOF; c = getchar())
		{
			wc[i++] = (wchar)c;
			if (i == 63) {
				wc[i] = 0;
				s = s->append16(wc);
				i = 0;
			}
		}
		if (i > 0) {
			wc[i] = 0;
			s = s->append16(wc);
		}
		return s;
	}

	double SystemClass::get_totalMemory()
	{
		MMgc::GCHeap* gcheap = MMgc::GCHeap::GetGCHeap();
		return double(gcheap->GetTotalHeapSize() * MMgc::GCHeap::kBlockSize);
	}

	double SystemClass::get_freeMemory()
	{
		MMgc::GCHeap* gcheap = MMgc::GCHeap::GetGCHeap();
		return double(gcheap->GetFreeHeapSize() * MMgc::GCHeap::kBlockSize);
	}
	
	double SystemClass::get_privateMemory()
	{
		return double(VMPI_getPrivateResidentPageCount() * VMPI_getVMPageSize());
	}

	void SystemClass::forceFullCollection()
	{
		core()->GetGC()->Collect();
	}

	void SystemClass::queueCollection()
	{
		core()->GetGC()->QueueCollection();
	}

	bool SystemClass::isGlobal(Atom o)
	{
		return AvmCore::isObject(o) ? AvmCore::atomToScriptObject(o)->isGlobalObject() : false;
	}
}
