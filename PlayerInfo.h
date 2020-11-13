#pragma once

namespace gomokuGame
{
	class OutputMemoryStream;
	class InputMemoryStream;

	// 플레이어 정보
	class PlayerInfo final
	{
	public:
		PlayerInfo();				 // for Read
		PlayerInfo(const char* id);  // for Write
		~PlayerInfo();

		void Write(OutputMemoryStream& ostream);
		void Read(InputMemoryStream& istream);

		const char* GetID() const;

	private:
		char* mID;
	};
}