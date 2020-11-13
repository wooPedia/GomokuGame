/*
	객체 직렬화 데이터 Reading을 위한 입력용 스트림 클래스입니다.
*/

#pragma once

#include <memory>

namespace gomokuGame
{
	class InputMemoryStream final
	{
	public:
		InputMemoryStream(size_t maxPacketSize); 
		~InputMemoryStream();

		void ReadFromBuffer(void* to, size_t sizeInByte);
		void ReadFromBuffer(char* to, size_t sizeInByte, bool isCharPtrType);
		void ReadFromBuffer(uint8_t* data);
		void ReadFromBuffer(uint16_t* data);
		void ReadFromBuffer(bool* data);

		// 역직렬화할 데이터 타입이 더 있을 경우 오버로딩을 추가합니다.
		// i.e. void ReadFromBuffer(uint32_t* num);

		char* GetBufferPtr() const;

		void ClearBuffer();

	private:
		InputMemoryStream() = delete;

		char*    mBuffer;
		uint32_t mHead;
		size_t   mCapacity;
	};
}