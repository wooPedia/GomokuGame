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

	// 논블로킹 (메인 스레드가 호출하기 때문에)
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

	// 블로킹(작업 스레드가 호출하기 때문에)
	void SignalManager::RecvSignal(SOCKET sock)
	{
		recv(sock, mBuffer, eSignalSize::SIG_SIZE, 0);

		// 상대방으로부터 받은 시그널을 저장합니다.
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