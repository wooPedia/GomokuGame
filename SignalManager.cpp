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

		// �����͸� �������� ���ߴٸ� �ٷ� ��ȯ�մϴ�.
		if (0 == select(0, &readSet, nullptr, nullptr, &tval))
		{
			SetBlockingMode(sock);
			return;
		}

		// �������κ��� ���� �ñ׳��� �����մϴ�.
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