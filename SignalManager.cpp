#include "Assert.h"
#include "SignalManager.h"

extern CRITICAL_SECTION cs;

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

	// ����ŷ (���� �����尡 ȣ���ϱ� ������)
	void SignalManager::SendSignal(SOCKET sock)
	{
		Assert(mSignal != (eSignal)NULL, "mSignal must be set before calling SendSignal().");

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