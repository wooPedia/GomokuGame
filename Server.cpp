#include <string>
#include <queue>

#include "Assert.h"
#include "Network.h"

extern std::queue<std::pair<std::string, SOCKET>> buffers;
extern CRITICAL_SECTION cs;

namespace gomokuGame
{
	unsigned __stdcall RecvPacket(void* pSocket);

	// 클라이언트의 요청을 받고 새 소켓에 대한 스레드를 생성해 줍니다.
	SOCKET WaitConnectionRequest()
	{
		// winsock 초기화
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			return INVALID_SOCKET;
		}

<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======

>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		// 소켓 생성
		SOCKET listeningSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (listeningSock == INVALID_SOCKET)
		{
			WSACleanup();
			return INVALID_SOCKET;
		}

<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======

>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		// 소켓에 ip 주소와 port 번호 바인딩
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		hint.sin_addr.S_un.S_addr = INADDR_ANY;
		hint.sin_port = htons(PORT);

		int bindResult = bind(listeningSock, reinterpret_cast<sockaddr*>(&hint), sizeof(hint));
		if (bindResult == SOCKET_ERROR)
		{
			closesocket(listeningSock);
			WSACleanup();
			return INVALID_SOCKET;
		}

		// 소켓이 연결을 accept할 수 있는 상태가 되도록 합니다.
		int listeningResult = listen(listeningSock, SOMAXCONN);
		if (listeningResult == SOCKET_ERROR)
		{
			closesocket(listeningSock);
			WSACleanup();
			return INVALID_SOCKET;
		}

<<<<<<< HEAD
<<<<<<< HEAD
		// 클라이언트의 요청을 받아 소켓을 생성합니다.
		sockaddr_in clSockInfo;
		int clSockInfoSize = sizeof(clSockInfo);

		SOCKET newSocket = accept(listeningSock, reinterpret_cast<sockaddr*>(&clSockInfo), &clSockInfoSize);
=======

		// 클라이언트의 요청을 받아 소켓을 생성합니다.
		SOCKET newSocket = accept(listeningSock, NULL, NULL);
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======

		// 클라이언트의 요청을 받아 소켓을 생성합니다.
		SOCKET newSocket = accept(listeningSock, NULL, NULL);
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		if (newSocket == INVALID_SOCKET) // 소켓 생성에 성공하면 해당 소켓을 담당할 스레드를 생성합니다. 
		{
			closesocket(listeningSock);
			WSACleanup();
			return INVALID_SOCKET;
		}

<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		closesocket(listeningSock);

		return newSocket;
	}


	// 해당 소켓과 연결된 상대 호스트로부터 패킷을 계속해서 받습니다.
	// 받은 데이터는 큐에 저장합니다.
	unsigned __stdcall RecvPacket(void* pSocket)
	{
		SOCKET socket = (SOCKET)pSocket;
		constexpr size_t BUF_SIZE = 128;
		char buf[BUF_SIZE];

		while (true)
		{
			auto len = recv(socket, buf, BUF_SIZE, 0);

			if (len >= 0)
			{
				// 메인 스레드에 데이터 전송
				// buffers는 공유 자원이므로 잠금 필요
				EnterCriticalSection(&cs);
				buffers.emplace(std::make_pair(std::string(buf), socket));
				LeaveCriticalSection(&cs);
			}
			else
			{
				assert(false);
			}

			ZeroMemory(buf, BUF_SIZE);
		}

		closesocket(socket);
	}
}

//int CreateRoom(HWND hWnd, std::unordered_map<USHORT, bool>* ports)
//{
//	if (ports->size() == MAX_PORT_COUNT)
//	{
//		return NOT_ENOUGH_PORT;
//	}
//
//	assert(ports->size() < 100);
//
//
//	// winsock 초기화
//	WSADATA wsaData;
//	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
//	{
//		return -1;
//	}
//
//
//	// 소켓 생성
//	SOCKET listeningSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (listeningSock == INVALID_SOCKET)
//	{
//		WSACleanup();
//		return -1;
//	}
//
//
//	// [1024, 49151] 범위의 port 번호를 랜덤으로 생성합니다.
//	//std::random_device rng;
//	//std::uniform_int_distribution<USHORT> dist(1025, 49151);
//
//	//// 중복되지 않는 포트를 포트 목록에 추가합니다.
//	//USHORT port;
//	//while (true)
//	//{
//	//	port = dist(rng);
//	//	if (ports->find(port) == ports->end()) // 랜덤으로 생성한 포트가 사용 가능하다면
//	//	{
//	//		auto pair = ports->insert(std::make_pair(port, false)); // 포트 추가
//	//		assert(pair.second == true);
//	//		break;
//	//	}
//	//}
//
//	assert(ports->size() <= 100);
//
//
//	// 소켓에 ip 주소와 port 번호 바인딩
//	sockaddr_in hint;
//	hint.sin_family = AF_INET;
//	hint.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	hint.sin_port = htons(PORT);
//
//	int bindResult = bind(listeningSock, reinterpret_cast<sockaddr*>(&hint), sizeof(hint));
//	if (bindResult == SOCKET_ERROR)
//	{
//		closesocket(listeningSock);
//		WSACleanup();
//		//ports->erase(port);
//		return -1;
//	}
//
//
//	// 소켓이 연결을 accept할 수 있는 상태가 되도록 합니다.
//	int listeningResult = listen(listeningSock, SOMAXCONN);
//	if (listeningResult == SOCKET_ERROR)
//	{
//		closesocket(listeningSock);
//		WSACleanup();
//		//ports->erase(port);
//		return -1;
//	}
//
//
//	// 클라이언트의 연결 요청이 들어오면 accept 함수를 통해 연결을 수락
//	// 연결 요청이 없다면 호출 스레드는 block 됩니다.
//	sockaddr_in clientSock;
//	int clientSize = sizeof(clientSock);
//	SOCKET clientSocket = accept(listeningSock, reinterpret_cast<sockaddr*>(&clientSock), &clientSize);
//	if (clientSocket == INVALID_SOCKET)
//	{
//		closesocket(listeningSock);
//		WSACleanup();
//		//ports->erase(port);
//		return -1;
//	}
//
//
//	int closeResult = closesocket(listeningSock);
//
//
//	char host[NI_MAXHOST];
//	char service[NI_MAXHOST];
//	ZeroMemory(host, NI_MAXHOST);
//	ZeroMemory(service, NI_MAXHOST);
//
//
//	if (getnameinfo((sockaddr*)&clientSock, sizeof(clientSock), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
//	{
//		std::wstring str = std::to_wstring(PORT);
//		str += L"from Server";
//		MessageBox(hWnd, str.c_str(), L"Message", MB_OK);
//	}
//
//
//	return 0;
//}
