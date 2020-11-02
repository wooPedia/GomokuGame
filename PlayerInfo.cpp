#include "PlayerInfo.h"
#include "OutputMemoryStream.h"
#include "InputMemoryStream.h"


namespace gomokuGame
{
	PlayerInfo::PlayerInfo()
		: mID(nullptr)
	{
	}

	PlayerInfo::PlayerInfo(const char* id)
	{
		size_t idLengthIncludeNull = strlen(id) + 1;
		mID = static_cast<char*>(malloc(idLengthIncludeNull));
		if (mID != NULL)
		{
			strcpy_s(mID, idLengthIncludeNull, id);
		}
	}

	PlayerInfo::~PlayerInfo()
	{
		free(mID);
		mID = nullptr;
	}


	// PlayerInfo의 멤버를 ostream에 직렬화해 저장합니다. 
	void PlayerInfo::Write(OutputMemoryStream& ostream)
	{
		uint8_t idLength = static_cast<uint8_t>(strlen(mID));
		ostream.WriteInBuffer(idLength);
		ostream.WriteInBuffer(mID, idLength);

		// PlayerInfo의 멤버가 추가되면(직렬화할 데이터가 추가되면)
		// 여기에 WriteInBuffer를 추가하세요.
		// 타입이 맞지 않는다면 WriteInBuffer 함수의 오버로딩을 추가하세요.
	}

	// istream에 직렬화 된 데이터를 해당 객체에 역직렬화하여 저장합니다.
	void PlayerInfo::Read(InputMemoryStream& istream)
	{
		uint8_t idLength = 0;
		istream.ReadFromBuffer(&idLength);
		mID = static_cast<char*>(malloc(idLength + 1)); // 널문자 포함
		istream.ReadFromBuffer(mID, idLength, true);	// istream에서 mID로 idLength 바이트만큼 읽어옵니다.
		
		// PlayerInfo의 멤버가 추가되면(읽어올 데이터가 추가되면) 
		// 여기에 ReadFromBuffer를 추가하세요.
		// 타입이 맞지 않는다면 ReadFromBuffer 함수의 오버로딩을 추가하세요.
	}

	const char* PlayerInfo::GetID() const
	{
		return mID;
	}
}
