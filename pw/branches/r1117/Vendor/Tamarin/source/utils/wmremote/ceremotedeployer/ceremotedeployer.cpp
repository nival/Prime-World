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
 
// ceremoteshell.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <rapi.h>

typedef struct _wait_info
{
	HANDLE proc_id;
	DWORD dwTimeout;
} wait_info;

#define PROCESS_TIMEOUT 60000

int _tmain(int argc, _TCHAR* argv[])
{
	
	// Initialize RAPI
	HRESULT hr = CeRapiInit();

	WCHAR destFile[MAX_PATH];
    WCHAR sourceFile[MAX_PATH];

	if (argc>2) {
		wcscpy(destFile,argv[2]);
	    wcscpy(sourceFile,argv[1]);
	} else if (argc>1) {
   	    wcscpy(destFile,L"\\Program Files\\shell\\avmshell.exe");
		wcscpy(sourceFile,argv[1]);
	} else {
		printf("Usage: ceremotedeployer.exe [source] [dest]\n");
		CeRapiUninit();
		return -1;
	}
	HANDLE hFile = ::CreateFile(sourceFile, 
								GENERIC_READ, FILE_SHARE_READ,
								NULL, OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile==INVALID_HANDLE_VALUE)
	{
		printf("Error copying file %s to device",sourceFile);
		CeRapiUninit();
		return -1;
	}

	hr = CeDeleteFile(destFile);

	// Create the file on the device in the temp directory
	WCHAR ceFilename[MAX_PATH];
	DWORD dwmblen = ::MultiByteToWideChar(CP_ACP, MB_COMPOSITE, (const char *)sourceFile, strlen((const char *)sourceFile), ceFilename, MAX_PATH); 
	ceFilename[dwmblen] = 0;


	HANDLE ceFile = CeCreateFile(destFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

	char localBuf[4096];
	DWORD dwBufsize=4096, dwFilesize = ::GetFileSize(hFile, NULL);
	if (dwFilesize<4096)
		dwBufsize = dwFilesize;


	DWORD dwCeBytes=0, dwRead;
	while (ReadFile(hFile, localBuf, dwBufsize, &dwRead, NULL))
	{
		hr = CeWriteFile(ceFile, (void*)localBuf, dwRead, &dwCeBytes, NULL);
		dwFilesize -= dwRead;
		if (dwFilesize<4096)
			dwBufsize = dwFilesize;
		if (dwBufsize<=0)
			break;
	}

	// Uninitialize RAPI
	CeRapiUninit();
	return 0;
}

