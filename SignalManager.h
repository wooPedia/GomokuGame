#pragma once

#include "Network.h"

namespace gomokuGame
{
	class SignalManager final
	{
	public:
		using sig_type = UINT16;

		enum class eSignal
		{
			// If you need more signal
			// add in range 100~999
			// SIG_NULL is same with NULL in here.
			SIG_NULL = 100,
			SIG_READY,
		};

		SignalManager();
		SignalManager(eSignal signal);
		~SignalManager() = default;

		void SendSignal(SOCKET sock);
		void RecvSignal(SOCKET sock);
		void SetSignal(eSignal signal);
		eSignal GetSignal() const;

	private:
		enum eSignalSize { SIG_SIZE = 2 };
		static_assert(eSignalSize::SIG_SIZE == sizeof(sig_type)
			, "SIG_SIZE must be same with sig_type.");

		eSignal mSignal;
		char mBuffer[eSignalSize::SIG_SIZE];
	};
}
