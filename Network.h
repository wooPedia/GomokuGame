#ifndef _NETWORK_HEADER_
#define _NETWORK_HEADER_

#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

<<<<<<< HEAD
<<<<<<< HEAD
#define SetBlockingMode(socket)    ioctlsocket(socket, FIONBIO, &blockingMode) 
#define SetNonBlockingMode(socket) ioctlsocket(socket, FIONBIO, &nonBlockingMode)

#define PORT 34000

extern CRITICAL_SECTION cs;

namespace gomokuGame
{

=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
#define SetBlockingMode(socket)    ioctlsocket(sock, FIONBIO, &blockingMode) 
#define SetNonBlockingMode(socket) ioctlsocket(sock, FIONBIO, &nonBlockingMode)

#define PORT 34000

namespace gomokuGame
{
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	extern u_long blockingMode;
	extern u_long nonBlockingMode;

	SOCKET WaitConnectionRequest();
	SOCKET ConnectToServer();
}

#endif // !_NETWORK_HEADER_