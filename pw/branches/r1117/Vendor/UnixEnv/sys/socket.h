#pragma once
#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#define F_GETFL     3
#define F_SETFL     4
#define O_NONBLOCK  5 

#define SHUT_RDWR  SD_BOTH

struct sockaddr_un
{
	short int sun_family;
	char sun_path[108];
};

namespace nsocket
{
	inline int Initialize()
	{
		WORD wVersionRequested;
		WSADATA wsaData;
		wVersionRequested = MAKEWORD(2, 2);
		return WSAStartup(wVersionRequested, &wsaData);
	}
}


inline void close(int handle)
{
  ::closesocket(handle);
}
inline int fcntl(int handle, int flag, int )
{
  return 0;
}

inline int socketpair(int domain, int type, int protocol, int sock[2])
{
	struct sockaddr_in address;
	SOCKET redirect;
	int size = sizeof(address);

	sock[0]				= socket(domain, type, protocol);
	
	address.sin_addr.s_addr		= INADDR_ANY;
	address.sin_family		= AF_INET;
	address.sin_port		= 0;

	bind(sock[0], (struct sockaddr*)&address, sizeof(address));
	

	if(getsockname(sock[0], (struct sockaddr *)&address, &size) != 0) {
	}

	listen(sock[0], 2);

	sock[1] = socket(domain, type, protocol);	
	address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	connect(sock[1], (struct sockaddr*)&address, sizeof(address));
	redirect = accept(sock[0],(struct sockaddr*)&address, &size);

	closesocket(sock[0]);
	sock[0] = redirect;

	if(sock[0] == INVALID_SOCKET ) {
		closesocket(sock[0]);
		closesocket(sock[1]);
		WSASetLastError(WSAECONNABORTED);
		return -1;
	}
	
	return 0;
}
#endif