#pragma once

namespace gomokuGame
{
	class OutputMemoryStream;
	class InputMemoryStream;

	// �÷��̾� ����
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