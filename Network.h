#ifndef _NETWORK_HEADER_
#define _NETWORK_HEADER_

#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define SetBlockingMode(socket)    ioctlsocket(socket, FIONBIO, &blockingMode) 
#define SetNonBlockingMode(socket) ioctlsocket(socket, FIONBIO, &nonBlockingMode)

#define PORT 34000

extern CRITICAL_SECTION cs;

namespace gomokuGame
{

	extern u_long blockingMode;
	extern u_long nonBlockingMode;

	SOCKET WaitConnectionRequest();
	SOCKET ConnectToServer();
}

#endif // !_NETWORK_HEADER_