#include "Assert.h"
#include "OutputMemoryStream.h"

using namespace std;

namespace gomokuGame
{
	OutputMemoryStream::OutputMemoryStream()
		: mBuffer(nullptr)
		, mHead(0)
		, mCapacity(0)
	{
		reallocBuffer(32);
	}

	OutputMemoryStream::~OutputMemoryStream()
	{
		free(mBuffer);
		mBuffer = nullptr;
	}

	const char* OutputMemoryStream::GetBuffer() const
	{
		return mBuffer;
	}

	size_t OutputMemoryStream::GetSize() const
	{
		return mHead;
	}

	void OutputMemoryStream::WriteInBuffer(const void* pArg, size_t sizeInByte)
	{
		// 현재 버퍼에 write할 수 없다면
		// 버퍼의 크기를 재조정 후 저장합니다.
		auto totalSize = mHead + sizeInByte;
		if (totalSize > mCapacity)
		{
			size_t newSize = max(mCapacity * 2, totalSize);
			reallocBuffer(newSize);
		}

		// 버퍼의 head부터 sizeInByte만큼 데이터를 복사합니다.
		memcpy(mBuffer + mHead, pArg, sizeInByte);
		mHead += sizeInByte;
	}

	void OutputMemoryStream::WriteInBuffer(uint8_t data)
	{
		WriteInBuffer(&data, sizeof(data));
	}

<<<<<<< HEAD
<<<<<<< HEAD
	void OutputMemoryStream::WriteInBuffer(uint16_t data)
	{
		WriteInBuffer(&data, sizeof(data));
	}

	void OutputMemoryStream::WriteInBuffer(bool data)
	{
		WriteInBuffer(&data, sizeof(data));
	}


=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

	void OutputMemoryStream::reallocBuffer(const size_t newSizeInByte)
	{
		char* backupPtr = mBuffer;

		mBuffer = static_cast<char*>(realloc(mBuffer, newSizeInByte));
		if (mBuffer == NULL)
		{
			free(backupPtr);
			backupPtr = nullptr;
			Assert(false, "Failed to reallocBuffer...");
			exit(-1);
		}

		mCapacity = newSizeInByte;
	}
<<<<<<< HEAD
<<<<<<< HEAD

	// 버퍼의 내용만 비웁니다.
	void OutputMemoryStream::ClearBuffer()
	{
		memset(mBuffer, 0, mHead);
		mHead = 0;
	}
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
}
