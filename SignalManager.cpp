<<<<<<< HEAD
#include "Assert.h"
#include "SignalManager.h"

extern CRITICAL_SECTION cs;
=======
#include "SignalManager.h"

#include "Assert.h"
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

namespace gomokuGame
{
	SignalManager::SignalManager()
		: mSignal()
		, mBuffer{0, }
	{
	}

	SignalManager::SignalManager(eSignal signal)
		: mSignal(signal)
		, mBuffer {0, }
	{
		sig_type intSignal = static_cast<sig_type>(mSignal);
		memcpy(mBuffer, &intSignal, eSignalSize::SIG_SIZE);
	}

<<<<<<< HEAD
	// ����ŷ (���� �����尡 ȣ���ϱ� ������)
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	void SignalManager::SendSignal(SOCKET sock)
	{
		Assert(mSignal != (eSignal)NULL, "mSignal must be set before calling SendSignal().");

<<<<<<< HEAD
		//EnterCriticalSection(&cs);
		//SetNonBlockingMode(sock);
		send(sock, mBuffer, eSignalSize::SIG_SIZE, 0);
		//SetBlockingMode(sock);
		//LeaveCriticalSection(&cs);

		//MessageBoxW(NULL, L"Send", L"Error", MB_OK);
	}

	// ���ŷ(�۾� �����尡 ȣ���ϱ� ������)
	void SignalManager::RecvSignal(SOCKET sock)
	{
		recv(sock, mBuffer, eSignalSize::SIG_SIZE, 0);

		// �������κ��� ���� �ñ׳��� �����մϴ�.
=======
		SetNonBlockingMode(sock);
		send(sock, mBuffer, eSignalSize::SIG_SIZE, 0);
		SetBlockingMode(sock);
	}

	void SignalManager::RecvSignal(SOCKET sock)
	{
		SetNonBlockingMode(sock);
		recv(sock, mBuffer, eSignalSize::SIG_SIZE, 0);

		fd_set readSet;
		FD_ZERO(&readSet);
		FD_SET(sock, &readSet);
		timeval tval{ 0, 0 };

		// �����͸� �������� ���ߴٸ� �ٷ� ��ȯ�մϴ�.
		if (0 == select(0, &readSet, nullptr, nullptr, &tval))
		{
			SetBlockingMode(sock);
			return;
		}

		// �������κ��� ���� �ñ׳��� �����մϴ�.
		SetBlockingMode(sock);
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		sig_type intSignal = 0;
		memcpy(&intSignal, mBuffer, eSignalSize::SIG_SIZE);
		mSignal = static_cast<eSignal>(intSignal);
	}

	void SignalManager::SetSignal(eSignal signal)
	{
		mSignal = signal;
		sig_type intSignal = static_cast<sig_type>(mSignal);
		memcpy(mBuffer, &intSignal, eSignalSize::SIG_SIZE);
	}

	SignalManager::eSignal SignalManager::GetSignal() const
	{
		return mSignal;
	}
}