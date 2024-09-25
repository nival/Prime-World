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

#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/select.h>
#include <sys/un.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

const char* spy_socket_channel = "/tmp/MMgc_Spy"; //name of unix domain for spy connections

bool spy_connected  = false; 
bool spy_running = false;

pthread_cond_t spy_cond; //condition variable for synchronizing spy signalling and socket communication
pthread_mutex_t spy_mutex; //mutex for spy_signal and spy_cond condition variable
pthread_t spy_thread;

int serverSocket = -1; //fd for spy server socket
int clientSocket = -1; //fd for spy socket connection (one at a time)

void* SpyConnectionLoop(void*)
{
	struct sockaddr_un sockAddr;

	socklen_t len = sizeof(sockAddr.sun_family) + strlen(sockAddr.sun_path)+1;
	while(spy_running)
	{
		//wait for spy socket connection
		if((clientSocket = accept(serverSocket, (struct sockaddr*)&sockAddr, &len)) >= 0)
		{
			fd_set fds;
			FD_ZERO(&fds);
			FD_SET(clientSocket, &fds);

			select(clientSocket+1, NULL, &fds, NULL, NULL);

			if(FD_ISSET(clientSocket, &fds))
			{
				pthread_cond_signal(&spy_cond);
				
				pthread_mutex_lock(&spy_mutex);
				spy_connected = true; //set the 

				//wait until we are woken up my the main program thread
				//we do this to avoid processing any new incoming spy request
				pthread_cond_wait(&spy_cond, &spy_mutex);
				pthread_mutex_unlock(&spy_mutex);
			}
			close(clientSocket); //we are done, close this connection
		}
	}
	
	return NULL;
}

bool SetupSpyServer()
{
	//clear remnants of previous execution
	unlink(spy_socket_channel);

	struct sockaddr_un sockAddr;

	//open a server socket
	if((serverSocket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		return false;

	memset(&sockAddr, 0, sizeof(struct sockaddr_un));

	sockAddr.sun_family = AF_UNIX;
	strcpy(sockAddr.sun_path, spy_socket_channel);

	//bind and listen
	socklen_t len = sizeof(sockAddr.sun_family) + strlen(sockAddr.sun_path) + 1;
	if( (bind(serverSocket, (struct sockaddr*)&sockAddr, len) < 0) || (listen(serverSocket, 5) < 0))
	{
		close(serverSocket);
		return false;
	}

	//initialize synchronization variables
	pthread_mutex_init(&spy_mutex, NULL);
	pthread_cond_init(&spy_cond, NULL);
	
	//wait for spy connections on a separate thread
	if(pthread_create(&spy_thread, NULL, SpyConnectionLoop, NULL))
	{
		close(serverSocket);
		return false;
	}

	return true;
}

//log redirector function for outputting log messages to the spy
void SpyLog(const char* message)
{
	send(clientSocket, message, VMPI_strlen(message)+1, 0);
}

extern void RedirectLogOutput(void (*)(const char*));

void VMPI_spyCallback()
{
	pthread_mutex_lock(&spy_mutex);

	if(spy_connected)
	{
		spy_connected = false;

		RedirectLogOutput(SpyLog);
		MMgc::GCHeap::GetGCHeap()->DumpMemoryInfoLocked();
		RedirectLogOutput(NULL);
		
		//we are done dumping memory info to the spy
		//signal the condition variable to 
		//wake up SpyConnectionLoop thread
		pthread_cond_signal(&spy_cond);
	}
	
	pthread_mutex_unlock(&spy_mutex);	
}

bool VMPI_spySetup()
{
	//setup server socket for spy connections
	return SetupSpyServer();
}

void VMPI_spyTeardown()
{
	spy_running = false;

	if(spy_connected)
	{
		spy_connected = false;
		pthread_cond_signal(&spy_cond);
	}		
}

bool VMPI_hasSymbols()
{
	return true;
}

#endif //MMGC_MEMORY_PROFILER
