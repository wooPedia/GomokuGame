#include <string>
#include <queue>

#include "Assert.h"
#include "Network.h"

extern std::queue<std::pair<std::string, SOCKET>> buffers;
extern CRITICAL_SECTION cs;

namespace gomokuGame
{
	unsigned __stdcall RecvPacket(void* pSocket);

	// Ŭ���̾�Ʈ�� ��û�� �ް� �� ���Ͽ� ���� �����带 ������ �ݴϴ�.
	SOCKET WaitConnectionRequest()
	{
		// winsock �ʱ�ȭ
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
		// ���� ����
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
		// ���Ͽ� ip �ּҿ� port ��ȣ ���ε�
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

		// ������ ������ accept�� �� �ִ� ���°� �ǵ��� �մϴ�.
		int listeningResult = listen(listeningSock, SOMAXCONN);
		if (listeningResult == SOCKET_ERROR)
		{
			closesocket(listeningSock);
			WSACleanup();
			return INVALID_SOCKET;
		}

<<<<<<< HEAD
<<<<<<< HEAD
		// Ŭ���̾�Ʈ�� ��û�� �޾� ������ �����մϴ�.
		sockaddr_in clSockInfo;
		int clSockInfoSize = sizeof(clSockInfo);

		SOCKET newSocket = accept(listeningSock, reinterpret_cast<sockaddr*>(&clSockInfo), &clSockInfoSize);
=======

		// Ŭ���̾�Ʈ�� ��û�� �޾� ������ �����մϴ�.
		SOCKET newSocket = accept(listeningSock, NULL, NULL);
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======

		// Ŭ���̾�Ʈ�� ��û�� �޾� ������ �����մϴ�.
		SOCKET newSocket = accept(listeningSock, NULL, NULL);
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		if (newSocket == INVALID_SOCKET) // ���� ������ �����ϸ� �ش� ������ ����� �����带 �����մϴ�. 
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


	// �ش� ���ϰ� ����� ��� ȣ��Ʈ�κ��� ��Ŷ�� ����ؼ� �޽��ϴ�.
	// ���� �����ʹ� ť�� �����մϴ�.
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
				// ���� �����忡 ������ ����
				// buffers�� ���� �ڿ��̹Ƿ� ��� �ʿ�
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
//	// winsock �ʱ�ȭ
//	WSADATA wsaData;
//	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
//	{
//		return -1;
//	}
//
//
//	// ���� ����
//	SOCKET listeningSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (listeningSock == INVALID_SOCKET)
//	{
//		WSACleanup();
//		return -1;
//	}
//
//
//	// [1024, 49151] ������ port ��ȣ�� �������� �����մϴ�.
//	//std::random_device rng;
//	//std::uniform_int_distribution<USHORT> dist(1025, 49151);
//
//	//// �ߺ����� �ʴ� ��Ʈ�� ��Ʈ ��Ͽ� �߰��մϴ�.
//	//USHORT port;
//	//while (true)
//	//{
//	//	port = dist(rng);
//	//	if (ports->find(port) == ports->end()) // �������� ������ ��Ʈ�� ��� �����ϴٸ�
//	//	{
//	//		auto pair = ports->insert(std::make_pair(port, false)); // ��Ʈ �߰�
//	//		assert(pair.second == true);
//	//		break;
//	//	}
//	//}
//
//	assert(ports->size() <= 100);
//
//
//	// ���Ͽ� ip �ּҿ� port ��ȣ ���ε�
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
//	// ������ ������ accept�� �� �ִ� ���°� �ǵ��� �մϴ�.
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
//	// Ŭ���̾�Ʈ�� ���� ��û�� ������ accept �Լ��� ���� ������ ����
//	// ���� ��û�� ���ٸ� ȣ�� ������� block �˴ϴ�.
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
