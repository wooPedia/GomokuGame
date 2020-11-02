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


	// PlayerInfo�� ����� ostream�� ����ȭ�� �����մϴ�. 
	void PlayerInfo::Write(OutputMemoryStream& ostream)
	{
		uint8_t idLength = static_cast<uint8_t>(strlen(mID));
		ostream.WriteInBuffer(idLength);
		ostream.WriteInBuffer(mID, idLength);

		// PlayerInfo�� ����� �߰��Ǹ�(����ȭ�� �����Ͱ� �߰��Ǹ�)
		// ���⿡ WriteInBuffer�� �߰��ϼ���.
		// Ÿ���� ���� �ʴ´ٸ� WriteInBuffer �Լ��� �����ε��� �߰��ϼ���.
	}

	// istream�� ����ȭ �� �����͸� �ش� ��ü�� ������ȭ�Ͽ� �����մϴ�.
	void PlayerInfo::Read(InputMemoryStream& istream)
	{
		uint8_t idLength = 0;
		istream.ReadFromBuffer(&idLength);
		mID = static_cast<char*>(malloc(idLength + 1)); // �ι��� ����
		istream.ReadFromBuffer(mID, idLength, true);	// istream���� mID�� idLength ����Ʈ��ŭ �о�ɴϴ�.
		
		// PlayerInfo�� ����� �߰��Ǹ�(�о�� �����Ͱ� �߰��Ǹ�) 
		// ���⿡ ReadFromBuffer�� �߰��ϼ���.
		// Ÿ���� ���� �ʴ´ٸ� ReadFromBuffer �Լ��� �����ε��� �߰��ϼ���.
	}

	const char* PlayerInfo::GetID() const
	{
		return mID;
	}
}
