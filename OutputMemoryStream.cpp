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
		// ���� ���ۿ� write�� �� ���ٸ�
		// ������ ũ�⸦ ������ �� �����մϴ�.
		auto totalSize = mHead + sizeInByte;
		if (totalSize > mCapacity)
		{
			size_t newSize = max(mCapacity * 2, totalSize);
			reallocBuffer(newSize);
		}

		// ������ head���� sizeInByte��ŭ �����͸� �����մϴ�.
		memcpy(mBuffer + mHead, pArg, sizeInByte);
		mHead += sizeInByte;
	}

	void OutputMemoryStream::WriteInBuffer(uint8_t data)
	{
		WriteInBuffer(&data, sizeof(data));
	}


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
}
