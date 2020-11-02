#include "SignalManager.h"

#include "Assert.h"

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

	void SignalManager::SendSignal(SOCKET sock)
	{
		Assert(mSignal != (eSignal)NULL, "mSignal must be set before calling SendSignal().");

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