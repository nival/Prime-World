#ifndef ERRORS_H_073040C0_328C_4CBD_98D1
#define ERRORS_H_073040C0_328C_4CBD_98D1

namespace Network
{
	/** get socket error code */
	int GetSocketError();

	/** get readable form for an error */
	const char* SocketErrorToString( int error );
}

#endif //#define ERRORS_H_073040C0_328C_4CBD_98D1
