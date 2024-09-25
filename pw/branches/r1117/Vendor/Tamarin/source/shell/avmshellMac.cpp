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

//mac

#include "avmshell.h"
#include "PosixPartialPlatform.h"

#include <sys/signal.h>
#include <unistd.h>
#include <sys/resource.h>

namespace avmshell
{
	class MacPlatform : public PosixPartialPlatform
	{
	public:
		MacPlatform(void* stackbase) : stackbase(stackbase) {}
		virtual ~MacPlatform() {}
		
		virtual void setTimer(int seconds, AvmTimerCallback callback, void* callbackData);
		virtual uintptr_t getMainThreadStackLimit();
		
	private:
		void* stackbase;
	};

	uintptr_t MacPlatform::getMainThreadStackLimit()
	{
		struct rlimit r;
		size_t stackheight = avmshell::kStackSizeFallbackValue;
		// https://bugzilla.mozilla.org/show_bug.cgi?id=504976: setting the height to kStackSizeFallbackValue
		// is not ideal if the stack is meant to be unlimited but is an OK workaround for the time being.
		if (getrlimit(RLIMIT_STACK, &r) == 0 && r.rlim_cur != RLIM_INFINITY)
			stackheight = size_t(r.rlim_cur);
		return uintptr_t(stackbase) - stackheight + avmshell::kStackMargin;
	}

	AvmTimerCallback pCallbackFunc = 0;
	void* pCallbackData = 0;
	
	void MacPlatform::setTimer(int seconds, AvmTimerCallback callback, void* callbackData)
	{
		extern void alarmProc(int);
		
		pCallbackFunc = callback;
		pCallbackData = callbackData;
		
		signal(SIGALRM, alarmProc);
		alarm(seconds);
		
	}
	
	void alarmProc(int /*signum*/)
	{
		pCallbackFunc(pCallbackData);
	}	
}

avmshell::MacPlatform* gPlatformHandle = NULL;

avmshell::Platform* avmshell::Platform::GetInstance()
{
	AvmAssert(gPlatformHandle != NULL);
	return gPlatformHandle;
}

int main(int argc, char *argv[])
{
#ifdef AVMPLUS_MACH_EXCEPTIONS
	GenericGuard::staticInit();
#endif

	char* dummy;
	avmshell::MacPlatform platformInstance(&dummy);
	gPlatformHandle = &platformInstance;
	
	int code = avmshell::Shell::run(argc, argv);
	if (code == avmshell::OUT_OF_MEMORY)
		write(1, "OUT OF MEMORY\n", 14);

#ifdef AVMPLUS_MACH_EXCEPTIONS
	GenericGuard::staticDestroy();
#endif	

	return code;
}
