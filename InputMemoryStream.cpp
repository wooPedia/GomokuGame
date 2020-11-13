#include "Assert.h"
#include "InputMemoryStream.h"

namespace gomokuGame
{
	InputMemoryStream::InputMemoryStream(size_t maxPacketSize) // recv로 받은 버퍼
		: mBuffer(nullptr)
		, mHead(0)
		, mCapacity(maxPacketSize)
	{
		mBuffer = static_cast<char*>(malloc(maxPacketSize));
		Assert(mBuffer != NULL, "Failed to malloc in InputMemoryStream()");
	}

	InputMemoryStream::~InputMemoryStream()
	{
		free(mBuffer);
		mBuffer = nullptr;
	}


	// to에 mHead부터 sizeInByte만큼 복사합니다.
	void InputMemoryStream::ReadFromBuffer(void* to, size_t sizeInByte)
	{
		Assert(mHead <= mCapacity, "mHead can't greater than mCapacity.");

		memcpy(to, mBuffer + mHead, sizeInByte);
		mHead += sizeInByte;
	}

	void InputMemoryStream::ReadFromBuffer(char* to, size_t sizeInByte, bool isCharPtrType)
	{
		Assert(mHead <= mCapacity, "mHead can't greater than mCapacity.");

		memcpy(to, mBuffer + mHead, sizeInByte);
		to[sizeInByte] = '\0';
		mHead += sizeInByte;
	}

	void InputMemoryStream::ReadFromBuffer(uint8_t* data)
	{
		ReadFromBuffer(data, sizeof(*data));
	}

<<<<<<< HEAD
<<<<<<< HEAD
	void InputMemoryStream::ReadFromBuffer(uint16_t* data)
	{
		ReadFromBuffer(data, sizeof(*data));
	}

	void InputMemoryStream::ReadFromBuffer(bool* data)
	{
		ReadFromBuffer(data, sizeof(*data));
	}


=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	char* InputMemoryStream::GetBufferPtr() const
	{
		return mBuffer;
	}
<<<<<<< HEAD
<<<<<<< HEAD

	void InputMemoryStream::ClearBuffer()
	{
		memset(mBuffer, 0, mHead);
		mHead = 0;
	}
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
}
