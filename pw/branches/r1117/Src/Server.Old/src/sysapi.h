/*
 * sysapi.h
 *
 *  Created on: 15.10.2008
 *      Author: earnol
 */

#ifndef SYSAPI_H_
#define SYSAPI_H_

//precompiled header file

#if (!defined(_XBOX) && defined(_MSC_VER) && defined (_M_IX86)) || (defined(__MWERKS__) && defined(__INTEL__))
  #define NI_PLATF_WIN
  #ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
    #define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
  #endif
#else
  #if (defined(NI_PLATF_WIN))
    #error "Wrong definition"
  #endif
  #define NI_PLATF_LINUX
#endif

#ifdef NI_PLATF_LINUX

//include Linux API headers
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <syslog.h>
#include <signal.h>
#include <string.h>
#include <wchar.h>
#include <memory.h>
#include <ctype.h>
#include <iconv.h>

#endif

#ifdef NI_PLATF_WIN

#include <errno.h>
#include <WS2TCPIP.H>
#include <windows.h>
#include <stdio.h>

#endif

#endif /* SYSAPI_H_ */
