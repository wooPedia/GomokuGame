#include <string>

#include "Network.h"

#define NOT_EXIST_ROOM -2



namespace gomokuGame
{
	u_long blockingMode = 0;
	u_long nonBlockingMode = 1;

	SOCKET ConnectToServer()
	{
		const char* serverIpAddr = "127.0.0.1";

		// WinSock을 초기화합니다.
		WSADATA wsData;
		if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
		{
			return INVALID_SOCKET;
		}


		// 소켓을 생성합니다.
		SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == INVALID_SOCKET)
		{
			WSACleanup();
			return INVALID_SOCKET;
		}


		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(PORT);
		int convResult = inet_pton(AF_INET, serverIpAddr, &hint.sin_addr);
		if (convResult != 1)
		{
			WSACleanup();
			return INVALID_SOCKET;
		}


		// 해당 소켓을 Non-blocking 모드로 변경합니다.
		if (SOCKET_ERROR == SetNonBlockingMode(sock))
		{
			WSACleanup();
			return INVALID_SOCKET;
		}

		// 논블로킹 모드로 서버에 연결을 요청합니다.
		connect(sock, reinterpret_cast<sockaddr*>(&hint), sizeof(hint));

		// 소켓이 서버에 연결 되었는지 확인을 위해 select 함수를 사용합니다.
		// 반환값은 연결된 소켓의 수이며, 타임 아웃 시 0을 반환합니다.
		// nullptr로 설정한 옵션은 검사하지 않으며,
		// 타임 옵션을 nullptr로 설정할 경우 최소 1개의 소켓을 발견할 때까지
		// 무한히 블로킹 상태에 들어갑니다.
		fd_set writeSet;
		FD_ZERO(&writeSet);
		FD_SET(sock, &writeSet);
		timeval tval{ 0, 500000 }; // 최대 0.5초 blocking
		if (0 == select(0, nullptr, &writeSet, nullptr, &tval))
		{
			// 소켓이 서버와 연결에 실패한 경우
			closesocket(sock);
			WSACleanup();
			return INVALID_SOCKET;
		}

		// 소켓을 다시 blocking 모드로 변경합니다.
		SetBlockingMode(sock);

		return sock;
	}


	INT SendData(const SOCKET sock)
	{
		std::string str = std::to_string(sock);
		str = "hello from client";
		int len = send(sock, str.c_str(), str.size() + 1, 0);
		if (len >= 0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
}

