/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: t; tab-width: 4 -*- */
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

#include "MMgc.h"

#ifdef MMGC_MEMORY_PROFILER

#include <Msgqueue.h>

/**
* compiled with the /W4 warning level
* which is quite picky.  Disable warnings we don't care about.
*/
#ifdef _MSC_VER
#pragma warning(disable:4127) //conditional expression is constant
#endif

class SignalData : public MMgc::GCAllocObject
{
public:
	SignalData(uint32_t *addr, HANDLE handle) 
		: profilerAddr(addr), eventHandle(handle) {}
	uint32_t *profilerAddr;
	HANDLE eventHandle;
};

void WriteOnNamedSignal(const char* name, uint32_t *addr);

static SignalData *sig_data=NULL;
static bool spyRunning=false;

DWORD WINAPI WaitForMemorySignal(LPVOID)
{
	SignalData *sd = sig_data;
	while(spyRunning) {
		WaitForSingleObject(sig_data->eventHandle, INFINITE);	
		// For some reason ReadMsgQueue does not clear the signal on the handle (even though it should), and we 
		// end up setting the profilerAddr constantly, which makes the VM hang, since all it is doing is writing out profile data.
		// so we have to call CloseMsgQueue, and then open a new queue, and wait on that.  
		//char buff[256];
		//DWORD bytesread;
		//ReadMsgQueue(sig_data->eventHandle, buff, 256, &bytesread, INFINITE, 0);
		CloseMsgQueue(sd->eventHandle);
		if(spyRunning) {
			*(sig_data->profilerAddr) = true;		
			WriteOnNamedSignal("MMgc::MemoryProfiler::DumpFatties", sd->profilerAddr);
			break;
		}
	}		
	delete sd;
	return 0;
}

void WriteOnNamedSignal(const char *name, uint32_t *addr)
{
	HANDLE m_namedSharedObject;

	MSGQUEUEOPTIONS msgopts;

	msgopts.dwFlags = MSGQUEUE_NOPRECOMMIT;
	msgopts.dwMaxMessages = 1;
	msgopts.cbMaxMessage = 256;
	msgopts.bReadAccess = TRUE;
	msgopts.dwSize = sizeof(MSGQUEUEOPTIONS);

	WCHAR wName[256];
	
	MultiByteToWideChar(CP_ACP, 0, name, -1, wName, 256);

	m_namedSharedObject = CreateMsgQueue(wName, &msgopts);

	sig_data = new SignalData(addr, m_namedSharedObject);
	spyRunning = true;
	CreateThread(NULL, 0, WaitForMemorySignal, NULL, 0, NULL);
}

#include "windows.h"

#ifdef _MSC_VER
	#pragma warning(disable: 4995) //disabling warning for deprecated _snprintf
#endif


static uint32_t mmgc_spy_signal = 0;

FILE* spyStream = NULL;

void SpyLog(const char* message)
{
	fprintf(spyStream, "%s", message);
}

extern void RedirectLogOutput(void (*)(const char*));

void VMPI_spyCallback()
{
	if(mmgc_spy_signal) 
	{
		mmgc_spy_signal = 0;

		spyStream = fopen("Temp\\gcstats.txt", "w");

		GCAssert(spyStream != NULL);
		RedirectLogOutput(SpyLog);

		MMgc::GCHeap::GetGCHeap()->DumpMemoryInfoLocked();

		fflush(spyStream);

		fclose(spyStream);
		RedirectLogOutput(NULL);
		spyStream = NULL;	
 	}
}

bool VMPI_spySetup()
{
	WriteOnNamedSignal("MMgc::MemoryProfiler::DumpFatties", &mmgc_spy_signal);
	return true;
}

void VMPI_spyTeardown()
{
	spyRunning = false;
}

bool VMPI_hasSymbols()
{
	return false;
}

#endif //MMGC_MEMORY_PROFILER
