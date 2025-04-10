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
 * The Original Code is [Open Source Virtual Machine].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2007
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
 
// avmremote.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <rapi.h>
#include <Msgqueue.h>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}


STDAPI StartAVMShell(
   DWORD cbInput,
   BYTE  *pInput,
   DWORD *pcbOutput,
   BYTE  **ppOutput,
   IRAPIStream *pIRAPIStream )
{
    WCHAR wShell[1024];
	char shell[1024];
	WCHAR wCmdline[1024];
	DWORD dwLen;
	char cmdline[1024];
	strcpy(shell,(char *)pInput);
	if (cbInput>0) {
		shell[cbInput]=0;
		char *match;
		match=strchr(shell,'\t');
		if (match!=NULL) {
			strcpy(cmdline,match+1);
			shell[cbInput-strlen(match)]=0;
			cmdline[cbInput-strlen(shell)-1]=0;
			dwLen=MultiByteToWideChar(CP_ACP,0, (LPCSTR)shell, -1, wShell, 256);
		} else {
			wcscpy(wShell,L"\\Program Files\\shell\\avmshell.exe");
			strcpy(cmdline,shell);
		}
   		dwLen=MultiByteToWideChar(CP_ACP,0, (LPCSTR)cmdline, -1, wCmdline, 1024);
	} else {
		wcscpy(wShell,L"\\Program Files\\shell\\avmshell.exe");
		wcscpy(wCmdline, L"-log \\Temp\\remoteshell.abc \\Temp\\avmfile.abc");
	}
	PROCESS_INFORMATION processInfo;
	// program live in \\Program Files\\shell\\avmshell.exe
	BOOL bResult = CreateProcess(wShell,
								wCmdline,
								NULL, NULL, FALSE,
								CREATE_NEW_CONSOLE,
								NULL, NULL, NULL,
								&processInfo);
	
	if (!bResult) {
		DebugBreak();
		return E_FAIL;
	}

	if (pcbOutput)
	{
		*ppOutput = (BYTE*)LocalAlloc(LPTR, sizeof(HANDLE));

		*(HANDLE*)*ppOutput = processInfo.hProcess;

		*pcbOutput = sizeof(HANDLE);
	}

	return S_OK;
}

typedef struct _wait_info
{
	HANDLE proc_id;
	DWORD dwTimeout;
} wait_info;

STDAPI WaitForAVMShell(
   DWORD cbInput,
   BYTE  *pInput,
   DWORD *pcbOutput,
   BYTE  **ppOutput,
   IRAPIStream *pIRAPIStream )
{
	if (cbInput!=sizeof(wait_info))
		return E_FAIL;

	wait_info* info = (wait_info*)pInput;

	DWORD dwWait = WaitForSingleObject(info->proc_id, info->dwTimeout);
	if (dwWait==WAIT_FAILED)
		return E_FAIL;
    
    DWORD exitCode;
    if (dwWait==WAIT_TIMEOUT)
        exitCode=STILL_ACTIVE;
    else
    {
        GetExitCodeProcess(info->proc_id,&exitCode);
	}
	*ppOutput = (BYTE*)LocalAlloc(LPTR, sizeof(DWORD));
	*((DWORD*)*ppOutput) = exitCode;
	*pcbOutput = sizeof(DWORD);

	return S_OK;
}

STDAPI KillAVMShell(
   DWORD cbInput,
   BYTE  *pInput,
   DWORD *pcbOutput,
   BYTE  **ppOutput,
   IRAPIStream *pIRAPIStream )
{
	HANDLE hProcess = (HANDLE)*pInput;
	TerminateProcess(hProcess, 0);

	return S_OK;
}

STDAPI RunMemProfiler(
	DWORD cbInput,
	BYTE  *pInput,
	DWORD *pcbOutput,
	BYTE  **ppOutput,
	IRAPIStream *pIRAPIStream )
{
	HANDLE m_queue;
	MSGQUEUEOPTIONS msgopts;
	
	msgopts.dwFlags = MSGQUEUE_NOPRECOMMIT;
	msgopts.dwMaxMessages = 1;
	msgopts.cbMaxMessage = 256;
	msgopts.bReadAccess = false;
	msgopts.dwSize = sizeof(MSGQUEUEOPTIONS);

	WCHAR* wName = L"MMgc::MemoryProfiler::DumpFatties";

	m_queue = CreateMsgQueue(wName, &msgopts);
	
	char buff = 'P';
	WriteMsgQueue(m_queue, &buff, 1, 0, 0);

	CloseMsgQueue(m_queue);
	return S_OK;
}
