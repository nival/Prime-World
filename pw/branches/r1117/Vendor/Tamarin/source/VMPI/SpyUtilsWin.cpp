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

#include <io.h>

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

static bool spyRunning=false;
static SignalData *sig_data;

DWORD WINAPI WaitForMemorySignal(LPVOID)
{
	while(spyRunning) {
		WaitForSingleObject(sig_data->eventHandle, INFINITE);
		if(spyRunning)
			*(sig_data->profilerAddr) = true;
	}
	CloseHandle(sig_data->eventHandle);
	delete sig_data;
	return 0;
}

void WriteOnNamedSignal(const char *name, uint32_t *addr)
{
	HANDLE m_namedSharedObject;

	SECURITY_DESCRIPTOR sd;
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&sd, TRUE, 0, FALSE);

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;
	sa.lpSecurityDescriptor = &sd;

	m_namedSharedObject = CreateEventA(&sa, FALSE, FALSE, name);
	if(m_namedSharedObject == NULL){
		LPVOID lpMsgBuf;
		FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPSTR) &lpMsgBuf, 0, NULL );
		fputs((const char*)lpMsgBuf, stderr);
		return;
	}
	sig_data = new SignalData(addr, m_namedSharedObject);
	spyRunning = true;
	CreateThread(NULL, 0, WaitForMemorySignal, NULL, 0, NULL);
}

#include "windows.h"

#ifdef _MSC_VER
	#pragma warning(disable: 4995) //disabling warning for deprecated _snprintf
#endif


FILE *HandleToStream(void *handle)
{
	return _fdopen(_open_osfhandle((intptr_t)handle, 0), "w");
}

void* OpenAndConnectToNamedPipe(const char *pipeName)
{
	char name[256];
	VMPI_snprintf(name, sizeof(name), "\\\\.\\pipe\\%s", pipeName);

	HANDLE pipe = CreateNamedPipeA((LPCSTR)name, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 4096, 4096, 100, NULL);
	ConnectNamedPipe(pipe, NULL);
	return (void*)pipe;
}


void CloseNamedPipe(void *handle)
{
	FlushFileBuffers(handle);
	CloseHandle((HANDLE)handle);
}

static uint32_t mmgc_spy_signal = 0;

//log redirector function for outputting log messages to the spy
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

		void *pipe = OpenAndConnectToNamedPipe("MMgc_Spy");

		spyStream = HandleToStream(pipe);
		GCAssert(spyStream != NULL);
		RedirectLogOutput(SpyLog);

		MMgc::GCHeap::GetGCHeap()->DumpMemoryInfoLocked();

		fflush(spyStream);

		CloseNamedPipe(pipe);
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
	return true;
}

#endif //MMGC_MEMORY_PROFILER
