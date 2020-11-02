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

		// WinSock�� �ʱ�ȭ�մϴ�.
		WSADATA wsData;
		if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
		{
			return INVALID_SOCKET;
		}


		// ������ �����մϴ�.
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


		// �ش� ������ Non-blocking ���� �����մϴ�.
		if (SOCKET_ERROR == SetNonBlockingMode(sock))
		{
			WSACleanup();
			return INVALID_SOCKET;
		}

		// ����ŷ ���� ������ ������ ��û�մϴ�.
		connect(sock, reinterpret_cast<sockaddr*>(&hint), sizeof(hint));

		// ������ ������ ���� �Ǿ����� Ȯ���� ���� select �Լ��� ����մϴ�.
		// ��ȯ���� ����� ������ ���̸�, Ÿ�� �ƿ� �� 0�� ��ȯ�մϴ�.
		// nullptr�� ������ �ɼ��� �˻����� ������,
		// Ÿ�� �ɼ��� nullptr�� ������ ��� �ּ� 1���� ������ �߰��� ������
		// ������ ���ŷ ���¿� ���ϴ�.
		fd_set writeSet;
		FD_ZERO(&writeSet);
		FD_SET(sock, &writeSet);
		timeval tval{ 0, 500000 }; // �ִ� 0.5�� blocking
		if (0 == select(0, nullptr, &writeSet, nullptr, &tval))
		{
			// ������ ������ ���ῡ ������ ���
			closesocket(sock);
			WSACleanup();
			return INVALID_SOCKET;
		}

		// ������ �ٽ� blocking ���� �����մϴ�.
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

