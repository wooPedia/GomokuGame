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
	// 논블로킹 (메인 스레드가 호출하기 때문에)
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

	// 블로킹(작업 스레드가 호출하기 때문에)
	void SignalManager::RecvSignal(SOCKET sock)
	{
		recv(sock, mBuffer, eSignalSize::SIG_SIZE, 0);

		// 상대방으로부터 받은 시그널을 저장합니다.
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

		// 데이터를 수신하지 못했다면 바로 반환합니다.
		if (0 == select(0, &readSet, nullptr, nullptr, &tval))
		{
			SetBlockingMode(sock);
			return;
		}

		// 상대방으로부터 받은 시그널을 저장합니다.
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