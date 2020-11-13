/*
	��ü ����ȭ ������ Reading�� ���� �Է¿� ��Ʈ�� Ŭ�����Դϴ�.
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

		// ������ȭ�� ������ Ÿ���� �� ���� ��� �����ε��� �߰��մϴ�.
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